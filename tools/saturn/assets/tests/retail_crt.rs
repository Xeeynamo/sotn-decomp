
use saturn_assets::crt;
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

fn packages() -> Vec<(String, PathBuf)> {
    let Ok(entries) = std::fs::read_dir(disc().join("SD")) else {
        return Vec::new();
    };
    let mut out: Vec<(String, PathBuf)> = entries
        .filter_map(|entry| entry.ok().map(|e| e.path()))
        .filter(|path| path.extension().is_some_and(|e| e == "CRT"))
        .filter_map(|path| {
            let name = path.file_name()?.to_str()?.to_string();
            Some((name, path))
        })
        .collect();
    out.sort();
    out
}

fn scratch(name: &str) -> PathBuf {
    let dir = std::env::temp_dir().join(format!("saturn-crt-{name}-{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    std::fs::create_dir_all(&dir).expect("create scratch dir");
    dir
}

#[test]
fn every_package_round_trips_byte_for_byte() {
    let packages = packages();
    if packages.is_empty() {
        eprintln!("skipping: no SD_*.CRT files present");
        return;
    }
    let game = disc().join("0.BIN");
    assert!(game.exists(), "0.BIN is missing from the disc");

    let mut failures = Vec::new();
    let mut areas = 0;
    let mut sequences = 0;
    let mut songs = 0;
    for (name, path) in &packages {
        let out = scratch(name);
        match crt::extract(&game, path, &out) {
            Ok(manifest) => {
                areas += manifest.areas.len();
                sequences += manifest
                    .areas
                    .iter()
                    .filter(|area| area.contents == crt::Contents::Sequence)
                    .count();
                songs += manifest
                    .areas
                    .iter()
                    .map(|area| area.songs.len())
                    .sum::<usize>();
                let total: usize = manifest.areas.iter().map(|area| area.size).sum();
                if total != manifest.source.crt_size {
                    failures.push(format!(
                        "{name}: areas cover {total} of {} bytes",
                        manifest.source.crt_size
                    ));
                }
                if let Err(e) = crt::verify(&out.join(crt::MANIFEST_NAME), path) {
                    failures.push(format!("{name}: {e}"));
                }
            }
            Err(e) => failures.push(format!("{name}: {e}")),
        }
        std::fs::remove_dir_all(&out).ok();
    }

    assert!(
        failures.is_empty(),
        "{} of {} packages failed:\n  {}",
        failures.len(),
        packages.len(),
        failures.join("\n  ")
    );
    eprintln!(
        "{} packages round-tripped byte-exactly: {areas} sound areas, \
         {songs} songs across the {sequences} areas that probe as sequence banks",
        packages.len()
    );
}

#[test]
fn the_sound_tables_come_from_a_recognised_driver() {
    let game_path = disc().join("0.BIN");
    if !game_path.exists() {
        eprintln!("skipping: 0.BIN is absent");
        return;
    }
    let game = std::fs::read(&game_path).expect("read 0.BIN");
    let areas = crt::area_map(&game).expect("area map");
    assert_eq!(areas.len(), 7, "retail has seven sound areas");
    assert!(areas.iter().all(|area| area.loadable));

    let files = crt::sound_files(&game).expect("sound files");
    assert_eq!(files.len(), 57);
    for (name, area) in &files {
        assert!(
            areas.iter().any(|entry| entry.id == *area),
            "{name} loads into area 0x{area:02X}, which is not in the map"
        );
    }

    let named: std::collections::BTreeSet<String> =
        files.iter().map(|(name, _)| name.clone()).collect();
    let present: std::collections::BTreeSet<String> =
        packages().into_iter().map(|(name, _)| name).collect();
    if !present.is_empty() {
        assert!(
            present.is_subset(&named),
            "the disc has packages 0.BIN does not name: {:?}",
            present.difference(&named).collect::<Vec<_>>()
        );
        let missing: Vec<&String> = named.difference(&present).collect();
        assert_eq!(
            missing,
            vec!["SD_BAT.CRT", "SD_HONE.CRT"],
            "the set of named-but-absent packages changed"
        );
    }

    let mut wrong = game.clone();
    wrong[crt::DRIVER_OFFSET + 0x400] ^= 0xFF;
    assert!(crt::area_map(&wrong).is_err());
}

#[test]
fn a_resized_area_is_refused() {
    let game = disc().join("0.BIN");
    let package = disc().join("SD/SD_ALK.CRT");
    if !game.exists() || !package.exists() {
        eprintln!("skipping: SD_ALK.CRT is absent");
        return;
    }
    let out = scratch("resize");
    let manifest_data = crt::extract(&game, &package, &out).expect("extract");
    let manifest = out.join(crt::MANIFEST_NAME);
    crt::verify(&manifest, &package).expect("unedited verify");

    let area = &manifest_data.areas[0];
    let path = out.join(&area.file);
    let mut bytes = std::fs::read(&path).expect("read area");
    bytes.push(0);
    std::fs::write(&path, &bytes).expect("write area");

    let error = crt::rebuild_bytes(&manifest)
        .expect_err("a longer area was accepted")
        .to_string();
    assert!(
        error.contains("area map"),
        "the refusal does not say why a resize is not allowed: {error}"
    );

    bytes.pop();
    bytes[0] ^= 0xFF;
    std::fs::write(&path, &bytes).expect("write area");
    let rebuilt = crt::rebuild_bytes(&manifest).expect("rebuild");
    let retail = std::fs::read(&package).expect("read package");
    assert_eq!(rebuilt.len(), retail.len());
    assert_ne!(rebuilt, retail, "the edit was dropped");
    assert!(crt::verify(&manifest, &package).is_err());
    eprintln!("SD_ALK.CRT: {error}");
    std::fs::remove_dir_all(&out).ok();
}
