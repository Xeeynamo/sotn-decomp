use saturn_assets::{image, weapon};
use std::path::{Path, PathBuf};

fn repo_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR"))
        .ancestors()
        .nth(3)
        .expect("crate is three levels below the repo root")
        .to_path_buf()
}

fn available() -> Vec<(&'static weapon::Profile, PathBuf, PathBuf)> {
    let dir = repo_root().join("disks/saturn");
    weapon::PROFILES
        .iter()
        .filter_map(|profile| {
            let chr = dir.join(profile.file);
            let prg = dir.join(profile.prg);
            (chr.exists() && prg.exists()).then_some((profile, chr, prg))
        })
        .collect()
}

fn scratch(name: &str) -> PathBuf {
    let dir = std::env::temp_dir().join(format!("saturn-weapon-{name}-{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    std::fs::create_dir_all(&dir).expect("create scratch dir");
    dir
}

fn one_extract(name: &str) -> Option<(PathBuf, PathBuf, weapon::Manifest)> {
    let (profile, chr, prg) = available().into_iter().next()?;
    let out = scratch(name);
    let manifest = weapon::extract(profile.name, &chr, Some(&prg), &out).expect("extract");
    Some((out, chr, manifest))
}

#[test]
fn every_retail_weapon_chr_round_trips_byte_for_byte() {
    let profiles = available();
    if profiles.is_empty() {
        eprintln!("skipping: no weapon CHR/PRG pairs present");
        return;
    }

    let mut failures = Vec::new();
    for (profile, chr, prg) in &profiles {
        let out = scratch(profile.name);
        match weapon::extract(profile.name, chr, Some(prg), &out) {
            Ok(manifest) => {
                if manifest.packages.is_empty() {
                    failures.push(format!("{}: no packages found", profile.name));
                }
                let covered: usize = manifest.packages.iter().map(|p| p.byte_count).sum();
                if covered != manifest.source.size {
                    failures.push(format!(
                        "{}: packages cover {covered} of {} bytes",
                        profile.name, manifest.source.size
                    ));
                }
                for (_, record) in manifest.records() {
                    if !out.join(&record.file).exists() {
                        failures.push(format!("{}: {} missing", profile.name, record.file));
                    }
                }
                if let Err(e) = weapon::verify(&out.join(weapon::MANIFEST_NAME), chr) {
                    failures.push(format!("{}: {e}", profile.name));
                }
            }
            Err(e) => failures.push(format!("{}: extract: {e}", profile.name)),
        }
        std::fs::remove_dir_all(&out).ok();
    }

    assert!(
        failures.is_empty(),
        "{} of {} weapon CHRs did not round-trip:\n  {}",
        failures.len(),
        profiles.len(),
        failures.join("\n  ")
    );
    eprintln!("{} weapon CHRs round-tripped byte-exactly", profiles.len());
}

#[test]
fn an_edited_sprite_reaches_exactly_its_own_bytes() {
    let Some((out, chr, manifest_data)) = one_extract("sprite-edit") else {
        eprintln!("skipping: no weapon CHR/PRG pairs present");
        return;
    };
    let manifest = out.join(weapon::MANIFEST_NAME);
    weapon::verify(&manifest, &chr).expect("unedited verify");

    let (_, record) = manifest_data
        .records()
        .max_by_key(|(_, record)| record.byte_count)
        .expect("at least one image record");
    let sprite_path = out.join(&record.file);
    let mut sprite = image::read_indexed(&sprite_path).expect("read sprite");
    let before = sprite.get(1, 1);
    sprite.set(1, 1, if before == 15 { 0 } else { before + 1 });
    image::write_indexed(&sprite_path, &sprite).expect("write sprite");

    let rebuilt = weapon::rebuild_bytes(&manifest).expect("rebuild");
    let retail = std::fs::read(&chr).expect("read CHR");
    assert_eq!(rebuilt.len(), retail.len(), "CHR changed size");
    assert_ne!(rebuilt, retail, "the sprite edit was dropped");

    let moved: Vec<usize> = rebuilt
        .iter()
        .zip(&retail)
        .enumerate()
        .filter(|(_, (a, b))| a != b)
        .map(|(i, _)| i)
        .collect();
    assert_eq!(moved.len(), 1, "one pixel touched {} bytes", moved.len());
    let inside = record.file_offset..record.file_offset + record.byte_count;
    assert!(
        inside.contains(&moved[0]),
        "edit landed at 0x{:X}, outside {} at 0x{:X}..0x{:X}",
        moved[0],
        record.file,
        inside.start,
        inside.end
    );
    assert!(
        weapon::verify(&manifest, &chr).is_err(),
        "verify passed on an edited sprite"
    );

    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn a_linear_edit_in_an_unclaimed_byte_reaches_the_file() {
    let Some((out, chr, manifest_data)) = one_extract("linear-gap") else {
        eprintln!("skipping: no weapon CHR/PRG pairs present");
        return;
    };
    let manifest = out.join(weapon::MANIFEST_NAME);

    let gap = manifest_data.records().find_map(|(_, record)| {
        (record.allocation_size > record.byte_count)
            .then_some(record.file_offset + record.byte_count)
    });
    let Some(gap) = gap else {
        eprintln!("skipping: this build's image tables leave no gaps");
        std::fs::remove_dir_all(&out).ok();
        return;
    };

    let linear_path = out.join(&manifest_data.linear);
    let mut linear = image::read_indexed(&linear_path).expect("read linear dump");
    let pixel = gap * 2;
    let (x, y) = (
        pixel as u32 % manifest_data.linear_width,
        pixel as u32 / manifest_data.linear_width,
    );
    let before = linear.get(x, y);
    linear.set(x, y, if before == 15 { 0 } else { before + 1 });
    image::write_indexed(&linear_path, &linear).expect("write linear dump");

    let rebuilt = weapon::rebuild_bytes(&manifest).expect("rebuild");
    let retail = std::fs::read(&chr).expect("read CHR");
    assert_eq!(rebuilt.len(), retail.len(), "CHR changed size");
    assert_ne!(
        rebuilt[gap], retail[gap],
        "the linear-dump edit was dropped"
    );
    assert_eq!(
        rebuilt.iter().zip(&retail).filter(|(a, b)| a != b).count(),
        1,
        "a linear-dump edit in a gap touched more than its own byte"
    );

    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn a_linear_edit_inside_a_record_is_refused_by_name() {
    let Some((out, _chr, manifest_data)) = one_extract("linear-claimed") else {
        eprintln!("skipping: no weapon CHR/PRG pairs present");
        return;
    };
    let manifest = out.join(weapon::MANIFEST_NAME);
    let (_, record) = manifest_data
        .records()
        .max_by_key(|(_, record)| record.byte_count)
        .expect("at least one image record");

    let linear_path = out.join(&manifest_data.linear);
    let mut linear = image::read_indexed(&linear_path).expect("read linear dump");
    let pixel = record.file_offset * 2;
    let (x, y) = (
        pixel as u32 % manifest_data.linear_width,
        pixel as u32 / manifest_data.linear_width,
    );
    let before = linear.get(x, y);
    linear.set(x, y, if before == 15 { 0 } else { before + 1 });
    image::write_indexed(&linear_path, &linear).expect("write linear dump");

    let err = weapon::rebuild_bytes(&manifest).expect_err("rebuild accepted a two-writer edit");
    let message = err.to_string();
    assert!(
        message.contains(&record.file),
        "the refusal must name the file to edit instead, got: {message}"
    );

    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn an_edit_to_the_linear_padding_is_refused() {
    let row_bytes = weapon::LINEAR_WIDTH as u64 / 2;
    let Some((profile, chr, prg)) = available()
        .into_iter()
        .find(|(_, chr, _)| std::fs::metadata(chr).is_ok_and(|meta| meta.len() % row_bytes != 0))
    else {
        eprintln!("skipping: no weapon CHR has a partial final row");
        return;
    };
    let out = scratch("padding");
    let manifest_data = weapon::extract(profile.name, &chr, Some(&prg), &out).expect("extract");
    assert!(manifest_data.padding_pixels > 0, "expected padding");
    let manifest = out.join(weapon::MANIFEST_NAME);
    weapon::verify(&manifest, &chr).expect("unedited verify");

    let linear_path = out.join(&manifest_data.linear);
    let mut linear = image::read_indexed(&linear_path).expect("read linear dump");
    let pixel = manifest_data.valid_pixels;
    linear.set(
        pixel as u32 % manifest_data.linear_width,
        pixel as u32 / manifest_data.linear_width,
        7,
    );
    image::write_indexed(&linear_path, &linear).expect("write linear dump");

    let err = weapon::rebuild_bytes(&manifest).expect_err("rebuild accepted painted padding");
    assert!(
        err.to_string().contains("padding"),
        "the refusal must explain the padding, got: {err}"
    );

    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn the_contact_sheet_is_written_and_owns_nothing() {
    let Some((out, chr, manifest_data)) = one_extract("contact") else {
        eprintln!("skipping: no weapon CHR/PRG pairs present");
        return;
    };
    let manifest = out.join(weapon::MANIFEST_NAME);
    let name = manifest_data
        .contact
        .as_ref()
        .expect("a sheet was declared");
    let sheet = out.join(name);
    assert!(sheet.exists(), "{name} was declared but not written");

    let mut scribbled = image::Rgba::new(64, 64, [255, 0, 255, 255]);
    scribbled.fill_rect(0, 0, 64, 64, [0, 255, 0, 255]);
    image::write_rgba(&sheet, &scribbled).expect("overwrite sheet");
    weapon::verify(&manifest, &chr).expect("a derived sheet must not affect the rebuild");

    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn an_extract_without_a_prg_still_round_trips() {
    let Some((profile, chr, _)) = available().into_iter().next() else {
        eprintln!("skipping: no weapon CHR present");
        return;
    };
    let out = scratch("no-prg");
    let manifest_data = weapon::extract(profile.name, &chr, None, &out).expect("extract");
    assert!(manifest_data.packages.is_empty());
    assert!(manifest_data.prg.is_none());
    assert!(manifest_data.contact.is_none());
    weapon::verify(&out.join(weapon::MANIFEST_NAME), &chr).expect("verify");
    std::fs::remove_dir_all(&out).ok();
}
