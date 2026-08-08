use saturn_assets::{bitmap, image};
use std::path::{Path, PathBuf};

fn repo_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR"))
        .ancestors()
        .nth(3)
        .expect("crate is three levels below the repo root")
        .to_path_buf()
}

fn available() -> Vec<(&'static bitmap::Profile, PathBuf, PathBuf)> {
    let dir = repo_root().join("disks/saturn");
    bitmap::PROFILES
        .iter()
        .filter_map(|profile| {
            let source = dir.join(profile.source_file);
            let chr = dir.join(profile.chr);
            (source.exists() && chr.exists()).then_some((profile, source, chr))
        })
        .collect()
}

fn scratch(name: &str) -> PathBuf {
    let dir = std::env::temp_dir().join(format!("saturn-bitmap-{name}-{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    std::fs::create_dir_all(&dir).expect("create scratch dir");
    dir
}

fn one(name: &str) -> Option<(PathBuf, PathBuf, bitmap::Manifest)> {
    let (profile, source, chr) = available().into_iter().next()?;
    let out = scratch(name);
    let manifest = bitmap::extract(profile.name, &source, &chr, &out).expect("extract");
    Some((out, source, manifest))
}

#[test]
fn every_packed_bitmap_round_trips_byte_for_byte() {
    let profiles = available();
    if profiles.is_empty() {
        eprintln!("skipping: no player overlays present");
        return;
    }

    let mut failures = Vec::new();
    for (profile, source, chr) in &profiles {
        let out = scratch(profile.name);
        match bitmap::extract(profile.name, source, chr, &out) {
            Ok(manifest) => {
                if (manifest.width, manifest.height) != (320, 240) {
                    failures.push(format!(
                        "{}: {}x{}, expected 320x240",
                        profile.name, manifest.width, manifest.height
                    ));
                }
                if !out.join(&manifest.file).exists() {
                    failures.push(format!("{}: {} missing", profile.name, manifest.file));
                }
                if let Err(e) = bitmap::verify(&out.join(bitmap::MANIFEST_NAME), source) {
                    failures.push(format!("{}: {e}", profile.name));
                }
            }
            Err(e) => failures.push(format!("{}: extract: {e}", profile.name)),
        }
        std::fs::remove_dir_all(&out).ok();
    }

    assert!(
        failures.is_empty(),
        "{} of {} bitmaps did not round-trip:\n  {}",
        failures.len(),
        profiles.len(),
        failures.join("\n  ")
    );
    eprintln!(
        "{} packed bitmaps round-tripped byte-exactly",
        profiles.len()
    );
}

#[test]
fn the_recorded_offset_still_points_at_the_castle_map() {
    let profiles = available();
    if profiles.is_empty() {
        eprintln!("skipping: no player overlays present");
        return;
    }
    for (profile, source, chr) in &profiles {
        let out = scratch(&format!("offset-{}", profile.name));
        let manifest = bitmap::extract(profile.name, source, chr, &out).expect("extract");
        assert_eq!(manifest.source.size, 38400);
        assert_eq!(manifest.palette.words.len(), 16);
        assert_eq!(manifest.palette.preview_rgb555.len(), 16);
        assert_eq!(manifest.palette.preview_rgb555[1], 0x7DCA);
        assert_eq!(manifest.palette.preview_rgb555[4], 0x001F);
        assert_eq!(manifest.palette.preview_rgb555[6], 0x021F);
        assert_eq!(manifest.palette.words[1], 0xA040);
        assert_eq!(manifest.palette.words[9], 0xFDCA);
        assert_eq!(manifest.palette.words[12], 0x801F);
        assert_eq!(manifest.palette.words[14], 0x821F);

        let picture = image::read_indexed(&out.join(&manifest.file)).expect("read bitmap");
        let used: std::collections::BTreeSet<u8> = picture.pixels.iter().copied().collect();
        assert!(
            used.len() <= 6,
            "{}: {} distinct indices, this does not look like the map",
            profile.name,
            used.len()
        );
        let background = picture.pixels.iter().filter(|&&p| p == 0).count();
        assert!(
            background > picture.pixels.len() / 2,
            "{}: only {background} background pixels",
            profile.name
        );
        std::fs::remove_dir_all(&out).ok();
    }
}

#[test]
fn all_retail_sources_carry_identical_castle_maps() {
    let profiles = available();
    if profiles.len() < 2 {
        eprintln!("skipping: need both player overlays");
        return;
    }
    let mut arrays = Vec::new();
    for (profile, source, chr) in &profiles {
        let out = scratch(&format!("same-{}", profile.name));
        bitmap::extract(profile.name, source, chr, &out).expect("extract");
        arrays.push(bitmap::rebuild_bytes(&out.join(bitmap::MANIFEST_NAME)).expect("rebuild"));
        std::fs::remove_dir_all(&out).ok();
    }
    for array in &arrays[1..] {
        assert_eq!(arrays[0], *array, "the retail castle maps diverged");
    }
}

#[test]
fn an_edited_pixel_reaches_exactly_one_nibble() {
    let Some((out, source, manifest_data)) = one("edit") else {
        eprintln!("skipping: no player overlays present");
        return;
    };
    let manifest = out.join(bitmap::MANIFEST_NAME);
    bitmap::verify(&manifest, &source).expect("unedited verify");

    let picture_path = out.join(&manifest_data.file);
    let mut picture = image::read_indexed(&picture_path).expect("read bitmap");
    let before = picture.get(5, 7);
    picture.set(5, 7, if before == 15 { 0 } else { before + 1 });
    image::write_indexed(&picture_path, &picture).expect("write bitmap");

    let rebuilt = bitmap::rebuild_bytes(&manifest).expect("rebuild");
    let retail = {
        let data = std::fs::read(&source).expect("read source");
        bitmap::retail_bytes(manifest_data.profile().unwrap(), &data).expect("slice")
    };
    assert_eq!(rebuilt.len(), retail.len(), "the array changed size");
    let moved: Vec<usize> = rebuilt
        .iter()
        .zip(&retail)
        .enumerate()
        .filter(|(_, (a, b))| a != b)
        .map(|(i, _)| i)
        .collect();
    assert_eq!(moved.len(), 1, "one pixel touched {} bytes", moved.len());
    assert_eq!(
        (rebuilt[moved[0]] ^ retail[moved[0]]) & 0xF0,
        0,
        "an even-x pixel must be the low nibble"
    );
    assert!(
        bitmap::verify(&manifest, &source).is_err(),
        "verify passed on an edited bitmap"
    );
    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn a_resized_bitmap_is_refused() {
    let Some((out, _source, manifest_data)) = one("resize") else {
        eprintln!("skipping: no player overlays present");
        return;
    };
    let manifest = out.join(bitmap::MANIFEST_NAME);
    let smaller = image::Indexed::new(manifest_data.width, manifest_data.height - 1);
    image::write_indexed(&out.join(&manifest_data.file), &smaller).expect("write bitmap");
    let err = bitmap::rebuild_bytes(&manifest).expect_err("a resized bitmap was accepted");
    assert!(err.to_string().contains("resizing"), "{err}");
    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn the_generated_array_is_deterministic_and_matches_the_build() {
    let profiles = available();
    if profiles.is_empty() {
        eprintln!("skipping: no player overlays present");
        return;
    }
    for (profile, source, chr) in &profiles {
        let out = scratch(&format!("header-{}", profile.name));
        let manifest_data = bitmap::extract(profile.name, source, chr, &out).expect("extract");
        let manifest = out.join(bitmap::MANIFEST_NAME);
        let data = bitmap::rebuild_bytes(&manifest).expect("rebuild");

        let emitted = bitmap::emit_header(&manifest_data, &data).expect("emit");
        let again = bitmap::emit_header(&manifest_data, &data).expect("emit");
        assert_eq!(emitted, again, "header emission is not deterministic");
        assert!(emitted.contains(profile.symbol), "the symbol is missing");

        let built = match profile.name {
            "maria-castle-map" => Some("src/saturn/maria/gen/castmap.h"),
            "richter-castle-map" => Some("src/saturn/ric/gen/castmap.h"),
            _ => None,
        };
        if let Some(built) = built {
            let built = repo_root().join(built);
            if built.exists() {
                bitmap::verify_header(&manifest, &built)
                    .expect("the array in the tree is not what regenerates");
            } else {
                eprintln!("note: no built array in the tree; run ./sotn.sh build saturn");
            }
        }
        std::fs::remove_dir_all(&out).ok();
    }
}

#[test]
fn an_edited_pixel_reaches_the_generated_array() {
    let Some((out, _source, manifest_data)) = one("header-edit") else {
        eprintln!("skipping: no player overlays present");
        return;
    };
    let manifest = out.join(bitmap::MANIFEST_NAME);
    let before = out.join("reference.h");
    bitmap::generate_header(&manifest, &before).expect("generate reference");
    bitmap::verify_header(&manifest, &before).expect("unedited header verify");

    let picture_path = out.join(&manifest_data.file);
    let mut picture = image::read_indexed(&picture_path).expect("read bitmap");
    picture.set(0, 0, 6);
    image::write_indexed(&picture_path, &picture).expect("write bitmap");

    let data = bitmap::rebuild_bytes(&manifest).expect("rebuild");
    assert_eq!(data[0] >> 4, 6, "the edit did not reach the array bytes");
    let after = bitmap::emit_header(&manifest_data, &data).expect("emit");
    assert!(
        after.contains("0x60,"),
        "the edited byte is not in the emitted array"
    );
    assert!(
        bitmap::verify_header(&manifest, &before).is_err(),
        "verify-header passed on an edited bitmap"
    );
    std::fs::remove_dir_all(&out).ok();
}
