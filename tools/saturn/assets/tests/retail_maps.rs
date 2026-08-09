
use saturn_assets::{map, map_render};
use std::path::{Path, PathBuf};

fn repo_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR"))
        .ancestors()
        .nth(3)
        .expect("crate is three levels below the repo root")
        .to_path_buf()
}

fn pairs() -> Vec<(String, PathBuf, PathBuf)> {
    let dir = repo_root().join("disks/saturn");
    let Ok(entries) = std::fs::read_dir(&dir) else {
        return Vec::new();
    };
    let mut out: Vec<(String, PathBuf, PathBuf)> = entries
        .filter_map(|entry| entry.ok().map(|e| e.path()))
        .filter(|path| path.extension().is_some_and(|e| e == "MAP"))
        .filter_map(|path| {
            let stem = path.file_stem()?.to_str()?.to_string();
            let (stage, _) = map::stage_of(&stem);
            let prg = dir.join(format!("{stage}.PRG"));
            prg.exists().then_some((stem, prg, path))
        })
        .collect();
    out.sort();
    out
}

const KNOWN_UNREACHABLE: &[&str] = &["BOSS_R14", "TITLE"];

fn scratch(name: &str) -> PathBuf {
    let dir = std::env::temp_dir().join(format!("saturn-map-{name}-{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    std::fs::create_dir_all(&dir).expect("create scratch dir");
    dir
}

#[test]
fn every_reachable_map_round_trips_byte_for_byte() {
    let pairs = pairs();
    if pairs.is_empty() {
        eprintln!("skipping: no stage MAP/PRG pairs present");
        return;
    }

    let mut failures = Vec::new();
    let mut unreachable = Vec::new();
    let mut streams = 0;
    let mut references = 0;
    for (stem, prg, map_path) in &pairs {
        let out = scratch(stem);
        match map::extract(prg, map_path, &out) {
            Ok(manifest) => {
                streams += manifest.streams.len();
                references += manifest
                    .streams
                    .iter()
                    .map(|s| s.references.len())
                    .sum::<usize>();
                let manifest_path = out.join(map::MANIFEST_NAME);
                if stem != "STAGE_07" && !out.join(map_render::COMPOSITE_NAME).is_file() {
                    failures.push(format!("{stem}: extract did not write a composite preview"));
                    continue;
                }
                if let Err(e) = map::verify(&manifest_path, map_path) {
                    failures.push(format!("{stem}: {e}"));
                }
                let repacked = out.join("repacked.MAP");
                match map::repack(
                    &manifest_path,
                    map_path,
                    &repacked,
                    &out.join(map::LAYOUT_NAME),
                ) {
                    Ok(layout) => {
                        if layout.streams.iter().any(|entry| entry.moved) {
                            failures.push(format!("{stem}: an unedited repack moved a stream"));
                        } else if std::fs::read(&repacked).ok() != std::fs::read(map_path).ok() {
                            failures.push(format!("{stem}: an unedited repack changed the MAP"));
                        }
                    }
                    Err(e) => failures.push(format!("{stem}: repack: {e}")),
                }
            }
            Err(e) => unreachable.push((stem.clone(), e.to_string())),
        }
        std::fs::remove_dir_all(&out).ok();
    }

    assert!(
        failures.is_empty(),
        "{} maps extracted but did not round-trip:\n  {}",
        failures.len(),
        failures.join("\n  ")
    );

    let mut names: Vec<&str> = unreachable.iter().map(|(name, _)| name.as_str()).collect();
    names.sort();
    let mut expected: Vec<&str> = KNOWN_UNREACHABLE.to_vec();
    expected.sort();
    assert_eq!(
        names,
        expected,
        "the set of unreachable maps changed:\n  {}",
        unreachable
            .iter()
            .map(|(name, why)| format!("{name}: {why}"))
            .collect::<Vec<_>>()
            .join("\n  ")
    );

    eprintln!(
        "{} of {} maps round-tripped byte-exactly, {streams} distinct streams \
         behind {references} descriptors",
        pairs.len() - unreachable.len(),
        pairs.len()
    );
}

#[test]
fn substage_maps_extract_through_their_shared_overlay() {
    let dir = repo_root().join("disks/saturn");
    if !dir.exists() {
        eprintln!("skipping: disks/saturn is absent");
        return;
    }
    let mut checked = 0;
    for stem in [
        "STAGE_7B", "STAGE_9B", "STAGE_9C", "STAGE06B", "STAGE13B", "RSTAGE6B", "RSTAGE7B",
        "RSTAGE9B", "RSTAGE9C", "RSTAG13B",
    ] {
        let map_path = dir.join(format!("{stem}.MAP"));
        let (stage, substage) = map::stage_of(stem);
        let prg = dir.join(format!("{stage}.PRG"));
        if !map_path.exists() || !prg.exists() {
            continue;
        }
        assert!(substage > 0, "{stem} should be a non-zero sub-stage");
        let out = scratch(stem);
        let manifest = map::extract(&prg, &map_path, &out).expect("extract");
        assert_eq!(manifest.tables.substage, substage);
        map::verify(&out.join(map::MANIFEST_NAME), &map_path).expect("verify");
        std::fs::remove_dir_all(&out).ok();
        checked += 1;
    }
    if checked == 0 {
        eprintln!("skipping: no sub-stage maps present");
    } else {
        eprintln!("{checked} sub-stage maps reached through their shared overlay");
    }
}

#[test]
fn composite_batch_discovers_substages_and_the_boss_r14_override() {
    let dir = repo_root().join("disks/saturn");
    if !dir.is_dir() {
        eprintln!("skipping: disks/saturn is absent");
        return;
    }
    let jobs = map_render::discover(&dir).expect("discover renderable stage maps");
    let names: Vec<&str> = jobs.iter().map(|job| job.name.as_str()).collect();
    assert!(names.contains(&"STAGE_7A"));
    assert!(names.contains(&"STAGE_7B"));
    assert!(names.contains(&"BOSS_R14"));
    assert!(!names.contains(&"STAGE_07"));
    assert!(!names.contains(&"TITLE"));

    let boss = jobs.iter().find(|job| job.name == "BOSS_R14").unwrap();
    assert_eq!(boss.map.file_name().unwrap(), "RSTAGE14.MAP");
    let image =
        map_render::render_composite(&boss.prg, &boss.map).expect("the BOSS_R14 override renders");
    assert!(image.width > 0 && image.height > 0);
}

#[test]
fn an_edited_stream_reaches_the_map_and_is_reported_as_moved() {
    let Some((stem, prg, map_path)) = pairs().into_iter().find(|(stem, _, _)| stem == "STAGE_02")
    else {
        eprintln!("skipping: STAGE_02 is absent");
        return;
    };
    let out = scratch("edit");
    let manifest_data = map::extract(&prg, &map_path, &out).expect("extract");
    let manifest = out.join(map::MANIFEST_NAME);
    map::verify(&manifest, &map_path).expect("unedited verify");

    let repacked = out.join("repacked.MAP");
    let layout = out.join(map::LAYOUT_NAME);
    let result = map::repack(&manifest, &map_path, &repacked, &layout).expect("repack");
    assert_eq!(result.changed, 0, "an unedited repack recompressed streams");
    assert_eq!(
        std::fs::read(&repacked).unwrap(),
        std::fs::read(&map_path).unwrap(),
        "an unedited repack changed the MAP"
    );

    let text = std::fs::read_to_string(&manifest).expect("read manifest");
    let mut document: serde_json::Value = serde_json::from_str(&text).expect("parse");
    let index = manifest_data
        .streams
        .iter()
        .position(|s| s.kind == map::Kind::Palette)
        .expect("a palette stream");
    document["streams"][index]["words"][0] = serde_json::Value::String("0x7FFF".into());
    std::fs::write(&manifest, serde_json::to_string_pretty(&document).unwrap()).unwrap();

    let result = map::repack(&manifest, &map_path, &repacked, &layout).expect("repack");
    assert_eq!(result.changed, 1, "exactly one stream should recompress");
    assert_ne!(
        std::fs::read(&repacked).unwrap(),
        std::fs::read(&map_path).unwrap(),
        "the edit was dropped"
    );
    assert!(
        !result.streams.iter().any(|entry| entry.moved),
        "a same-size edit moved streams it did not have to"
    );
    assert_eq!(
        result.map_size,
        std::fs::metadata(&map_path).unwrap().len() as usize,
        "a same-size edit changed the MAP size"
    );
    assert!(
        map::verify(&manifest, &map_path).is_err(),
        "verify passed on an edited stream"
    );
    eprintln!("{stem}: edit recompressed 1 stream, layout reported");
    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn a_stream_several_rooms_read_is_extracted_once() {
    let Some((_, prg, map_path)) = pairs().into_iter().find(|(s, _, _)| s == "STAGE_02") else {
        eprintln!("skipping: STAGE_02 is absent");
        return;
    };
    let out = scratch("shared");
    let manifest = map::extract(&prg, &map_path, &out).expect("extract");

    let descriptors: usize = manifest.streams.iter().map(|s| s.references.len()).sum();
    assert!(
        descriptors > manifest.streams.len(),
        "STAGE_02 should have shared streams"
    );
    let widest = manifest
        .streams
        .iter()
        .map(|s| s.references.len())
        .max()
        .unwrap_or(0);
    assert_eq!(
        widest, 7,
        "the most-shared STAGE_02 stream feeds seven rooms"
    );

    let mut offsets: Vec<usize> = manifest.streams.iter().map(|s| s.offset).collect();
    offsets.sort_unstable();
    let distinct = {
        let mut d = offsets.clone();
        d.dedup();
        d.len()
    };
    assert_eq!(distinct, offsets.len(), "a stream is listed twice");
    eprintln!(
        "STAGE_02: {} descriptors over {} streams",
        descriptors,
        manifest.streams.len()
    );
    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn growing_a_stream_moves_the_map_and_regenerates_the_prg_tables() {
    let Some((_, prg, map_path)) = pairs().into_iter().find(|(s, _, _)| s == "STAGE_02") else {
        eprintln!("skipping: STAGE_02 is absent");
        return;
    };
    let out = scratch("resize");
    let extracted = map::extract(&prg, &map_path, &out).expect("extract");
    let manifest = out.join(map::MANIFEST_NAME);
    let repacked = out.join("repacked.MAP");
    let layout_path = out.join(map::LAYOUT_NAME);

    let before = map::repack(&manifest, &map_path, &repacked, &layout_path).expect("repack");
    assert_eq!(before.map_size, extracted.source.map_size);

    let last = before
        .streams
        .iter()
        .map(|entry| entry.offset)
        .max()
        .unwrap_or(0);
    let index = extracted
        .streams
        .iter()
        .position(|stream| stream.kind == map::Kind::Tilemap && stream.offset < last)
        .expect("a tilemap that is not last");
    let target = &extracted.streams[index];
    assert!(
        target
            .references
            .iter()
            .all(|r| r.compressed_size.is_none()),
        "the chosen stream is read short by some room"
    );

    let text = std::fs::read_to_string(&manifest).expect("read manifest");
    let mut document: serde_json::Value = serde_json::from_str(&text).expect("parse");
    let words = document["streams"][index]["words"]
        .as_array()
        .expect("words")
        .len();
    let noisy: Vec<serde_json::Value> = (0..words)
        .map(|i| serde_json::Value::String(format!("0x{:04X}", (i as u32 * 2654435761) >> 16)))
        .collect();
    document["streams"][index]["words"] = serde_json::Value::Array(noisy);
    std::fs::write(&manifest, serde_json::to_string_pretty(&document).unwrap()).unwrap();

    let after = map::repack(&manifest, &map_path, &repacked, &layout_path).expect("repack");
    assert_eq!(after.changed, 1, "exactly one stream should recompress");
    assert!(
        after.map_size > before.map_size,
        "the noisy tilemap should not fit in its old slot: {} -> {}",
        before.map_size,
        after.map_size
    );
    let grown = after.map_size - before.map_size;

    let edited = after
        .streams
        .iter()
        .find(|entry| entry.original_offset == target.offset)
        .expect("the edited stream");
    for entry in &after.streams {
        if entry.original_offset < target.offset {
            assert!(!entry.moved, "a stream before the edit moved");
            assert_eq!(entry.offset, entry.original_offset);
        } else if entry.original_offset > target.offset {
            assert_eq!(
                entry.offset,
                entry.original_offset + grown,
                "a stream after the edit did not follow it"
            );
        }
    }
    assert!(edited.moved);

    for entry in &after.streams {
        for reference in &entry.references {
            let index = map::Tables::entry(reference.room, reference.layer, entry.kind);
            assert_eq!(after.map_offsets[index] as usize, entry.offset);
            assert_eq!(
                after.compressed_sizes[index] as usize,
                reference.compressed_size.unwrap_or(entry.compressed_size)
            );
        }
    }
    for (room, (old, new)) in before
        .room_graphics
        .iter()
        .zip(&after.room_graphics)
        .enumerate()
    {
        assert_eq!(new.size, old.size, "room {room} collision size changed");
        assert_eq!(
            new.offset as usize,
            old.offset as usize + grown,
            "room {room} collision data did not follow the streams"
        );
    }

    let layer = out.join("stlayer.h");
    let graphics = out.join("strmgfx.h");
    map::generate_headers(&layout_path, "g_Stage02", &layer, &graphics).expect("generate");
    map::verify_headers(&layout_path, "g_Stage02", &layer, &graphics).expect("verify");
    let emitted = std::fs::read_to_string(&graphics).expect("read");
    assert!(
        emitted.contains(&format!("{{0x{:05X},", after.room_graphics[0].offset)),
        "the generated collision table does not carry the new offsets"
    );

    eprintln!(
        "STAGE_02: tilemap grew, MAP {} -> {} (+{grown}), tables regenerated",
        before.map_size, after.map_size
    );
    std::fs::remove_dir_all(&out).ok();
}
