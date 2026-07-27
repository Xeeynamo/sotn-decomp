//! verify round trip works

use saturn_assets::{font, image};
use std::path::{Path, PathBuf};

fn repo_root() -> PathBuf {
    // CARGO_MANIFEST_DIR is <repo>/tools/saturn/assets
    Path::new(env!("CARGO_MANIFEST_DIR"))
        .ancestors()
        .nth(3)
        .expect("crate is three levels below the repo root")
        .to_path_buf()
}

fn retail(file: &str) -> Option<PathBuf> {
    let path = repo_root().join("disks/saturn").join(file);
    path.exists().then_some(path)
}

fn scratch(name: &str) -> PathBuf {
    let dir = std::env::temp_dir().join(format!("saturn-font-{}-{}", name, std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    std::fs::create_dir_all(&dir).expect("create scratch dir");
    dir
}

const FONTS: &[(&str, &str)] = &[("ascii", "ASCII.FON"), ("kanji", "KANJI.FON")];

#[test]
fn unedited_rebuild_matches_retail_byte_for_byte() {
    for (profile, file) in FONTS {
        let Some(source) = retail(file) else {
            eprintln!("skipping {file}: not present");
            continue;
        };
        let dir = scratch(profile);
        font::extract(profile, &source, &dir).expect("extract");
        let manifest = dir.join(font::MANIFEST_NAME);

        font::verify(&manifest, &source).expect("verify");

        let rebuilt = font::rebuild_bytes(&manifest).expect("rebuild");
        let retail_bytes = std::fs::read(&source).expect("read retail");
        assert_eq!(rebuilt, retail_bytes, "{file} did not round-trip");

        std::fs::remove_dir_all(&dir).ok();
    }
}

#[test]
fn an_edited_atlas_reaches_the_font_without_resizing_it() {
    for (profile, file) in FONTS {
        let Some(source) = retail(file) else {
            eprintln!("skipping {file}: not present");
            continue;
        };
        let dir = scratch(&format!("{profile}-edited"));
        let manifest_data = font::extract(profile, &source, &dir).expect("extract");
        let manifest = dir.join(font::MANIFEST_NAME);
        let atlas_path = dir.join(&manifest_data.atlas);

        // flip a pixel
        let mut atlas = image::read(&atlas_path).expect("read atlas");
        let before = atlas.get(4, 8);
        atlas.set(4, 8, u8::from(before == 0));
        image::write(&atlas_path, &atlas).expect("write atlas");

        let rebuilt = font::rebuild_bytes(&manifest).expect("rebuild");
        let retail_bytes = std::fs::read(&source).expect("read retail");

        assert_eq!(
            rebuilt.len(),
            retail_bytes.len(),
            "{file} changed size after a pixel edit"
        );
        assert_ne!(rebuilt, retail_bytes, "{file} ignored the edit");

        // check if it changed
        let differing: Vec<usize> = rebuilt
            .iter()
            .zip(&retail_bytes)
            .enumerate()
            .filter(|(_, (a, b))| a != b)
            .map(|(i, _)| i)
            .collect();
        assert_eq!(differing.len(), 1, "{file}: one pixel touched >1 byte");
        let changed = differing[0];
        assert_eq!(
            (rebuilt[changed] ^ retail_bytes[changed]).count_ones(),
            1,
            "{file}: one pixel flipped >1 bit"
        );

        assert!(
            font::verify(&manifest, &source).is_err(),
            "{file}: verify passed on an edited atlas"
        );

        std::fs::remove_dir_all(&dir).ok();
    }
}

#[test]
fn a_resized_atlas_is_refused() {
    let Some(source) = retail("ASCII.FON") else {
        eprintln!("skipping: ASCII.FON not present");
        return;
    };
    let dir = scratch("ascii-resized");
    let manifest_data = font::extract("ascii", &source, &dir).expect("extract");
    let manifest = dir.join(font::MANIFEST_NAME);
    let atlas_path = dir.join(&manifest_data.atlas);

    let atlas = image::read(&atlas_path).expect("read atlas");
    let cropped = image::Bilevel::new(atlas.width, atlas.height - 1);
    image::write(&atlas_path, &cropped).expect("write atlas");

    let err = font::rebuild_bytes(&manifest).expect_err("a resized atlas must be refused");
    assert!(
        err.to_string().contains("resizing"),
        "unhelpful message: {err}"
    );

    std::fs::remove_dir_all(&dir).ok();
}
