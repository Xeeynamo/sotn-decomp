
use saturn_assets::stage;
use std::path::{Path, PathBuf};

fn repo_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR"))
        .ancestors()
        .nth(3)
        .expect("crate is three levels below the repo root")
        .to_path_buf()
}

fn disc() -> PathBuf {
    repo_root().join("disks/saturn")
}

fn pairs() -> Vec<(String, PathBuf, PathBuf)> {
    let dir = disc();
    let Ok(entries) = std::fs::read_dir(&dir) else {
        return Vec::new();
    };
    let mut out: Vec<(String, PathBuf, PathBuf)> = entries
        .filter_map(|entry| entry.ok().map(|e| e.path()))
        .filter(|path| path.extension().is_some_and(|e| e == "CHR"))
        .filter_map(|chr| {
            let stem = chr.file_stem()?.to_str()?.to_string();
            let prg = dir.join(format!("{stem}.PRG"));
            prg.exists().then_some((stem, prg, chr))
        })
        .collect();
    out.sort();
    out
}

const NOT_STAGES: &[&str] = &[
    "ALUCARD", "ENDING", "MARIA", "RICHTER", "RICHTER2", "TITLE", "T_BAT", "T_DEVIL", "T_DEVIL2",
    "T_FAIRY", "T_FAIRY2", "T_GHOST", "T_SWORD", "WEAPON0", "WEAPON1",
];

fn scratch(name: &str) -> PathBuf {
    let dir = std::env::temp_dir().join(format!("saturn-stage-{name}-{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    std::fs::create_dir_all(&dir).expect("create scratch dir");
    dir
}

#[test]
fn every_stage_chr_round_trips_byte_for_byte() {
    let pairs = pairs();
    if pairs.is_empty() {
        eprintln!("skipping: no overlay PRG/CHR pairs present");
        return;
    }
    let zero = disc().join("0.BIN");
    assert!(zero.exists(), "0.BIN is missing from the disc");

    let mut failures = Vec::new();
    let mut refused = Vec::new();
    let mut resources = 0;
    let mut sprites = 0;
    let mut shared = 0;
    for (stem, prg, chr) in &pairs {
        let out = scratch(stem);
        match stage::extract(prg, chr, Some(&zero), &out) {
            Ok(manifest) => {
                resources += manifest.resources.len();
                sprites += manifest.images.len();
                shared += manifest
                    .resources
                    .iter()
                    .filter(|r| r.region == stage::Region::Zero)
                    .count();
                if let Err(e) = stage::verify(&out.join(stage::MANIFEST_NAME), chr) {
                    failures.push(format!("{stem}: {e}"));
                }
            }
            Err(e) => refused.push((stem.clone(), e.to_string())),
        }
        std::fs::remove_dir_all(&out).ok();
    }

    assert!(
        failures.is_empty(),
        "{} stage CHRs extracted but did not round-trip:\n  {}",
        failures.len(),
        failures.join("\n  ")
    );

    let mut names: Vec<&str> = refused.iter().map(|(name, _)| name.as_str()).collect();
    names.sort();
    let mut expected: Vec<&str> = NOT_STAGES.to_vec();
    expected.sort();
    assert_eq!(
        names,
        expected,
        "the set of overlays that are not stages changed:\n  {}",
        refused
            .iter()
            .map(|(name, why)| format!("{name}: {why}"))
            .collect::<Vec<_>>()
            .join("\n  ")
    );

    eprintln!(
        "{} of {} overlays round-tripped byte-exactly: {resources} resources \
         ({shared} shared through 0.BIN), {sprites} sprites",
        pairs.len() - refused.len(),
        pairs.len()
    );
}

#[test]
fn the_shared_overlay_sprites_head_every_arena() {
    let dir = disc();
    let zero = dir.join("0.BIN");
    if !zero.exists() {
        eprintln!("skipping: 0.BIN is absent");
        return;
    }
    let mut heads: Vec<(String, Vec<u8>)> = Vec::new();
    for stem in ["STAGE_02", "STAGE_04", "STAGE_10"] {
        let (prg, chr) = (
            dir.join(format!("{stem}.PRG")),
            dir.join(format!("{stem}.CHR")),
        );
        if !prg.exists() || !chr.exists() {
            continue;
        }
        let out = scratch(&format!("shared-{stem}"));
        let manifest = stage::extract(&prg, &chr, Some(&zero), &out).expect("extract");

        let first_own = manifest
            .resources
            .iter()
            .position(|r| r.region == stage::Region::Stage)
            .expect("a stage-owned resource");
        assert!(
            manifest.resources[..first_own]
                .iter()
                .all(|r| r.region == stage::Region::Zero),
            "{stem}: the shared resources are not contiguous at the head"
        );
        assert_eq!(
            manifest.resources[0].base, 0,
            "{stem}: the arena does not start with the first bank"
        );

        let head = manifest.resources[first_own].base;
        let data = std::fs::read(&chr).expect("read CHR");
        heads.push((stem.to_string(), data[..head].to_vec()));
        std::fs::remove_dir_all(&out).ok();
    }

    if heads.len() < 2 {
        eprintln!("skipping: fewer than two stages present");
        return;
    }
    let (first_name, first) = &heads[0];
    for (name, head) in &heads[1..] {
        let common = first.len().min(head.len());
        assert_eq!(
            &first[..common],
            &head[..common],
            "{first_name} and {name} disagree about the shared sprites"
        );
    }
    eprintln!(
        "{} stages share the first {} bytes of their arena",
        heads.len(),
        heads.iter().map(|(_, h)| h.len()).min().unwrap_or(0)
    );
}

#[test]
fn an_edited_sprite_reaches_exactly_its_own_bytes() {
    let dir = disc();
    let (prg, chr, zero) = (
        dir.join("STAGE_02.PRG"),
        dir.join("STAGE_02.CHR"),
        dir.join("0.BIN"),
    );
    if !prg.exists() || !chr.exists() || !zero.exists() {
        eprintln!("skipping: STAGE_02 is absent");
        return;
    }
    let out = scratch("edit");
    let manifest_data = stage::extract(&prg, &chr, Some(&zero), &out).expect("extract");
    let manifest = out.join(stage::MANIFEST_NAME);
    stage::verify(&manifest, &chr).expect("unedited verify");

    let record = manifest_data
        .images
        .iter()
        .find(|record| record.byte_count > 0x40)
        .expect("a sprite worth editing");
    let picture = out.join(&record.file);
    let indexed = saturn_assets::image::read_indexed(&picture).expect("read sprite");
    let mut repainted = indexed;
    for pixel in repainted.pixels.iter_mut() {
        *pixel = 7;
    }
    saturn_assets::image::write_indexed(&picture, &repainted).expect("write sprite");

    let rebuilt = stage::rebuild_bytes(&manifest).expect("rebuild");
    let retail = std::fs::read(&chr).expect("read CHR");
    assert_eq!(rebuilt.len(), retail.len(), "the arena changed size");

    let differing: Vec<usize> = rebuilt
        .iter()
        .zip(&retail)
        .enumerate()
        .filter(|(_, (a, b))| a != b)
        .map(|(index, _)| index)
        .collect();
    assert!(!differing.is_empty(), "the edit was dropped");
    let start = record.file_offset;
    let end = start + record.byte_count;
    assert!(
        differing.iter().all(|&at| (start..end).contains(&at)),
        "the edit reached bytes outside 0x{start:X}..0x{end:X}"
    );
    assert!(
        stage::verify(&manifest, &chr).is_err(),
        "verify passed on an edited sprite"
    );
    eprintln!(
        "STAGE_02: one sprite edit touched {} bytes, all inside its own record",
        differing.len()
    );
    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn a_linear_edit_inside_a_sprite_is_refused_by_name() {
    let dir = disc();
    let (prg, chr, zero) = (
        dir.join("STAGE_02.PRG"),
        dir.join("STAGE_02.CHR"),
        dir.join("0.BIN"),
    );
    if !prg.exists() || !chr.exists() || !zero.exists() {
        eprintln!("skipping: STAGE_02 is absent");
        return;
    }
    let out = scratch("linear");
    let manifest_data = stage::extract(&prg, &chr, Some(&zero), &out).expect("extract");
    let manifest = out.join(stage::MANIFEST_NAME);

    let record = &manifest_data.images[0];
    let linear = out.join(&manifest_data.linear);
    let mut dump = saturn_assets::image::read_indexed(&linear).expect("read linear");
    let pixel = record.file_offset * 2;
    dump.pixels[pixel] ^= 0xF;
    saturn_assets::image::write_indexed(&linear, &dump).expect("write linear");

    let error = stage::rebuild_bytes(&manifest)
        .expect_err("a linear edit inside a sprite was accepted")
        .to_string();
    assert!(
        error.contains(&record.file),
        "the refusal does not name the sprite to edit instead: {error}"
    );
    eprintln!("STAGE_02: {error}");
    std::fs::remove_dir_all(&out).ok();
}
