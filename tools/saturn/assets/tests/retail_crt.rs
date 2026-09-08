
use saturn_assets::{crt, midi, seq};
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
    let mut layers = 0;
    for (name, path) in &packages {
        let out = scratch(name);
        match crt::extract(&game, path, &out) {
            Ok(manifest) => {
                areas += manifest.areas.len();
                for area in &manifest.areas {
                    match area.contents {
                        crt::Contents::Sequence => {
                            sequences += 1;
                            songs += area.entries;
                        }
                        crt::Contents::Tone => layers += area.entries,
                    }
                }
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
                if let Err(e) = crt::verify_banks(&out.join(crt::MANIFEST_NAME)) {
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
    assert_eq!(areas, 161, "sound areas across the disc");
    assert_eq!(sequences, 106, "sequence banks");
    assert_eq!(songs, 6137, "songs");
    assert_eq!(layers, 795, "tone layers");
    eprintln!(
        "{} packages round-tripped byte-exactly, areas and banks both: {areas} sound areas, \
         {songs} songs across {sequences} sequence banks, {layers} layers across the rest",
        packages.len()
    );
}

#[test]
fn every_song_exports_as_a_standard_midi_file() {
    let packages = packages();
    if packages.is_empty() {
        eprintln!("skipping: no SD_*.CRT files present");
        return;
    }
    let game = disc().join("0.BIN");

    let mut songs = 0;
    let mut notes = 0;
    let mut failures = Vec::new();
    for (name, path) in &packages {
        let out = scratch(&format!("midi-{name}"));
        let manifest = crt::extract(&game, path, &out).expect("extract");
        for area in &manifest.areas {
            if area.contents != crt::Contents::Sequence {
                continue;
            }
            let bank = seq::load(&out.join(&area.decoded)).expect("load seq.json");
            for (index, song) in bank.songs.iter().enumerate() {
                songs += 1;
                match midi::song_to_smf(song) {
                    Ok(smf) => {
                        if &smf[..4] != b"MThd" {
                            failures.push(format!("{name} area 0x{:02X} song {index}: not an SMF", area.id));
                            continue;
                        }
                        let (on, off) = count_notes(&smf);
                        notes += on;
                        if on != off {
                            failures.push(format!(
                                "{name} area 0x{:02X} song {index}: {on} note-ons, {off} note-offs",
                                area.id
                            ));
                        }
                    }
                    Err(e) => {
                        failures.push(format!("{name} area 0x{:02X} song {index}: {e}", area.id))
                    }
                }
            }
        }
        std::fs::remove_dir_all(&out).ok();
    }

    assert!(
        failures.is_empty(),
        "{} songs failed to export:\n  {}",
        failures.len(),
        failures.join("\n  ")
    );
    assert_eq!(songs, 6137);
    eprintln!("{songs} songs exported as MIDI, {notes} notes in total");
}

fn count_notes(smf: &[u8]) -> (usize, usize) {
    let mut at = 14;
    let (mut on, mut off) = (0, 0);
    while at + 8 <= smf.len() {
        let size =
            u32::from_be_bytes([smf[at + 4], smf[at + 5], smf[at + 6], smf[at + 7]]) as usize;
        let body = &smf[at + 8..at + 8 + size];
        let mut cursor = 0;
        while cursor < body.len() {
            while body[cursor] & 0x80 != 0 {
                cursor += 1; 
            }
            cursor += 1;
            let status = body[cursor];
            cursor += match status {
                0xFF => {
                    let length = body[cursor + 2] as usize;
                    3 + length
                }
                _ if status & 0xF0 == 0xC0 || status & 0xF0 == 0xD0 => 2,
                _ => 3,
            };
            match status & 0xF0 {
                0x90 => on += 1,
                0x80 => off += 1,
                _ => {}
            }
        }
        at += 8 + size;
    }
    (on, off)
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
