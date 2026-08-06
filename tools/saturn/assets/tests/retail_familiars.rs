use saturn_assets::{familiar, image};
use std::path::{Path, PathBuf};

fn repo_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR"))
        .ancestors()
        .nth(3)
        .expect("crate is three levels below the repo root")
        .to_path_buf()
}

fn available() -> Vec<(&'static familiar::Profile, PathBuf, PathBuf)> {
    let dir = repo_root().join("disks/saturn");
    familiar::PROFILES
        .iter()
        .filter_map(|profile| {
            let chr = dir.join(profile.chr);
            let prg = dir.join(profile.prg);
            (chr.exists() && prg.exists()).then_some((profile, prg, chr))
        })
        .collect()
}

fn scratch(name: &str) -> PathBuf {
    let dir = std::env::temp_dir().join(format!("saturn-familiar-{name}-{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    std::fs::create_dir_all(&dir).expect("create scratch dir");
    dir
}

fn bat(name: &str) -> Option<(PathBuf, PathBuf, familiar::Manifest)> {
    let (profile, prg, chr) = available()
        .into_iter()
        .find(|(profile, _, _)| profile.header.is_some())?;
    let out = scratch(name);
    let manifest = familiar::extract(profile.name, &prg, &chr, &out).expect("extract");
    Some((out, chr, manifest))
}

#[test]
fn every_retail_familiar_chr_round_trips_byte_for_byte() {
    let profiles = available();
    if profiles.is_empty() {
        eprintln!("skipping: no familiar CHR/PRG pairs present");
        return;
    }

    let mut failures = Vec::new();
    for (profile, prg, chr) in &profiles {
        let out = scratch(profile.name);
        match familiar::extract(profile.name, prg, chr, &out) {
            Ok(manifest) => {
                if manifest.images.is_empty() {
                    failures.push(format!("{}: no image records", profile.name));
                }
                let declared = manifest.resource.terminator_units * 8;
                if declared != manifest.source.chr_size {
                    failures.push(format!(
                        "{}: table declares {declared} bytes, CHR is {}",
                        profile.name, manifest.source.chr_size
                    ));
                }
                for record in &manifest.images {
                    if !out.join(&record.file).exists() {
                        failures.push(format!("{}: {} missing", profile.name, record.file));
                    }
                }
                if let Err(e) = familiar::verify(&out.join(familiar::MANIFEST_NAME), chr) {
                    failures.push(format!("{}: {e}", profile.name));
                }
            }
            Err(e) => failures.push(format!("{}: extract: {e}", profile.name)),
        }
        std::fs::remove_dir_all(&out).ok();
    }

    assert!(
        failures.is_empty(),
        "{} of {} familiars did not round-trip:\n  {}",
        failures.len(),
        profiles.len(),
        failures.join("\n  ")
    );
    eprintln!(
        "{} familiar CHRs round-tripped byte-exactly",
        profiles.len()
    );
}

#[test]
fn the_located_resource_matches_the_decompiled_symbol() {
    let Some((out, _chr, manifest)) = bat("resource") else {
        eprintln!("skipping: T_BAT is absent");
        return;
    };
    let expected = manifest
        .profile()
        .unwrap()
        .known_resource
        .expect("the bat profile names its resource");
    assert_eq!(manifest.resource.address, expected);
    assert!(manifest.resource.allocation == 0xFFFF && manifest.resource.flags == 0xFFFF);
    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn an_edited_sprite_reaches_exactly_its_own_bytes() {
    let Some((profile, prg, chr)) = available().into_iter().next() else {
        eprintln!("skipping: no familiar CHR/PRG pairs present");
        return;
    };
    let out = scratch("sprite-edit");
    let manifest_data = familiar::extract(profile.name, &prg, &chr, &out).expect("extract");
    let manifest = out.join(familiar::MANIFEST_NAME);
    familiar::verify(&manifest, &chr).expect("unedited verify");

    let record = manifest_data
        .images
        .iter()
        .max_by_key(|record| record.byte_count)
        .expect("at least one image record");
    let sprite_path = out.join(&record.file);
    let mut sprite = image::read_indexed(&sprite_path).expect("read sprite");
    let before = sprite.get(1, 1);
    sprite.set(1, 1, if before == 15 { 0 } else { before + 1 });
    image::write_indexed(&sprite_path, &sprite).expect("write sprite");

    let rebuilt = familiar::rebuild_bytes(&manifest).expect("rebuild");
    let retail = std::fs::read(&chr).expect("read CHR");
    assert_eq!(rebuilt.len(), retail.len(), "CHR changed size");
    let moved: Vec<usize> = rebuilt
        .iter()
        .zip(&retail)
        .enumerate()
        .filter(|(_, (a, b))| a != b)
        .map(|(i, _)| i)
        .collect();
    assert_eq!(moved.len(), 1, "one pixel touched {} bytes", moved.len());
    let inside = record.file_offset..record.file_offset + record.byte_count;
    assert!(inside.contains(&moved[0]), "edit landed outside its record");
    assert!(
        familiar::verify(&manifest, &chr).is_err(),
        "verify passed on an edited sprite"
    );
    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn the_linear_dump_owns_the_unclaimed_bytes_and_nothing_else() {
    let Some((out, chr, manifest_data)) = bat("linear") else {
        eprintln!("skipping: T_BAT is absent");
        return;
    };
    let manifest = out.join(familiar::MANIFEST_NAME);
    let linear_path = out.join(&manifest_data.linear);

    let gap = manifest_data
        .images
        .iter()
        .find(|record| record.allocation_size > record.byte_count)
        .map(|record| record.file_offset + record.byte_count)
        .expect("T_BAT's image table leaves gaps");

    let paint = |at: usize| {
        let mut linear = image::read_indexed(&linear_path).expect("read linear dump");
        let pixel = at * 2;
        let (x, y) = (
            pixel as u32 % manifest_data.linear_width,
            pixel as u32 / manifest_data.linear_width,
        );
        let before = linear.get(x, y);
        linear.set(x, y, if before == 15 { 0 } else { before + 1 });
        image::write_indexed(&linear_path, &linear).expect("write linear dump");
    };

    paint(gap);
    let rebuilt = familiar::rebuild_bytes(&manifest).expect("rebuild");
    let retail = std::fs::read(&chr).expect("read CHR");
    assert_ne!(
        rebuilt[gap], retail[gap],
        "the linear-dump edit was dropped"
    );
    assert_eq!(
        rebuilt.iter().zip(&retail).filter(|(a, b)| a != b).count(),
        1,
        "an edit in a gap touched more than its own byte"
    );

    let record = &manifest_data.images[0];
    paint(record.file_offset);
    let err = familiar::rebuild_bytes(&manifest).expect_err("two writers were accepted");
    assert!(
        err.to_string().contains(&record.file),
        "the refusal must name the sprite to edit, got: {err}"
    );

    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn the_generated_header_is_deterministic_and_matches_the_build() {
    let Some((out, _chr, manifest_data)) = bat("header") else {
        eprintln!("skipping: T_BAT is absent");
        return;
    };
    let manifest = out.join(familiar::MANIFEST_NAME);

    let emitted = familiar::emit_header(&manifest_data).expect("emit");
    let again = familiar::emit_header(&familiar::load_manifest(&manifest).unwrap()).expect("emit");
    assert_eq!(emitted, again, "header emission is not deterministic");

    let built = repo_root().join("src/saturn/t_bat/gen/batgfx.h");
    if built.exists() {
        familiar::verify_header(&manifest, &built)
            .expect("the header in the tree is not what regenerates");
    } else {
        eprintln!("note: no built header in the tree; run ./sotn.sh build saturn");
    }

    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn an_edited_clut_reaches_the_generated_header() {
    let Some((out, _chr, _)) = bat("clut") else {
        eprintln!("skipping: T_BAT is absent");
        return;
    };
    let manifest = out.join(familiar::MANIFEST_NAME);
    let before = out.join("reference.h");
    familiar::generate_header(&manifest, &before).expect("generate reference");
    familiar::verify_header(&manifest, &before).expect("unedited header verify");

    let text = std::fs::read_to_string(&manifest).expect("read manifest");
    let mut document: serde_json::Value = serde_json::from_str(&text).expect("parse manifest");
    document["clut"]["words"][1] = serde_json::Value::String("0x801F".to_string());
    std::fs::write(&manifest, serde_json::to_string_pretty(&document).unwrap())
        .expect("write manifest");

    let emitted =
        familiar::emit_header(&familiar::load_manifest(&manifest).unwrap()).expect("emit");
    assert!(
        emitted.contains("0x801F"),
        "the CLUT edit did not reach the header"
    );
    assert!(
        familiar::verify_header(&manifest, &before).is_err(),
        "verify-header passed on an edited CLUT"
    );

    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn an_undecompiled_familiar_has_no_header() {
    let Some((profile, prg, chr)) = available()
        .into_iter()
        .find(|(profile, _, _)| profile.header.is_none())
    else {
        eprintln!("skipping: no undecompiled familiar present");
        return;
    };
    let out = scratch("no-header");
    let manifest = familiar::extract(profile.name, &prg, &chr, &out).expect("extract");
    let err = familiar::emit_header(&manifest).expect_err("emitted a header with no symbols");
    assert!(err.to_string().contains("not decompiled"), "{err}");
    std::fs::remove_dir_all(&out).ok();
}
