
use saturn_assets::{image, lzss, player};
use std::path::{Path, PathBuf};

fn repo_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR"))
        .ancestors()
        .nth(3)
        .expect("crate is three levels below the repo root")
        .to_path_buf()
}

fn available() -> Vec<(&'static player::Profile, PathBuf, PathBuf)> {
    let dir = repo_root().join("disks/saturn");
    player::PROFILES
        .iter()
        .filter_map(|profile| {
            let prg = dir.join(profile.prg);
            let chr = dir.join(profile.chr);
            (prg.exists() && chr.exists()).then_some((profile, prg, chr))
        })
        .collect()
}

fn scratch(name: &str) -> PathBuf {
    let dir = std::env::temp_dir().join(format!("saturn-player-{name}-{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    std::fs::create_dir_all(&dir).expect("create scratch dir");
    dir
}

fn maria(name: &str) -> Option<(PathBuf, PathBuf, player::Manifest)> {
    let (profile, prg, chr) = available()
        .into_iter()
        .find(|(profile, _, _)| profile.name == "maria")?;
    let out = scratch(name);
    let manifest = player::extract(profile.name, &prg, &chr, &out).expect("extract");
    Some((out, chr, manifest))
}

#[test]
fn every_retail_player_chr_round_trips_byte_for_byte() {
    let profiles = available();
    if profiles.is_empty() {
        eprintln!("skipping: no player overlays present");
        return;
    }

    let mut failures = Vec::new();
    let mut streams = 0;
    for (profile, prg, chr) in &profiles {
        let out = scratch(profile.name);
        match player::extract(profile.name, prg, chr, &out) {
            Ok(manifest) => {
                streams += manifest.images.len();
                if manifest.arena_end > player::ARENA_END {
                    failures.push(format!(
                        "{}: streams end at 0x{:X}, past the arena",
                        profile.name, manifest.arena_end
                    ));
                }
                for record in &manifest.images {
                    if !out.join(&record.file).exists() {
                        failures.push(format!("{}: {} missing", profile.name, record.file));
                    }
                }
                if let Err(e) = player::verify(&out.join(player::MANIFEST_NAME), chr) {
                    failures.push(format!("{}: {e}", profile.name));
                }
            }
            Err(e) => failures.push(format!("{}: extract: {e}", profile.name)),
        }
        std::fs::remove_dir_all(&out).ok();
    }

    assert!(
        failures.is_empty(),
        "{} of {} players did not round-trip:\n  {}",
        failures.len(),
        profiles.len(),
        failures.join("\n  ")
    );
    eprintln!(
        "{} players / {streams} compressed streams round-tripped byte-exactly",
        profiles.len()
    );
}

#[test]
fn every_stream_fills_exactly_the_allocation_its_image_table_declares() {
    let profiles = available();
    if profiles.is_empty() {
        eprintln!("skipping: no player overlays present");
        return;
    }
    for (profile, prg, chr) in &profiles {
        let out = scratch(&format!("alloc-{}", profile.name));
        let manifest = player::extract(profile.name, prg, chr, &out).expect("extract");
        let retail = std::fs::read(chr).expect("read chr");
        for record in &manifest.images {
            let stream =
                &retail[record.stream_offset..record.stream_offset + record.compressed_size];
            assert_eq!(
                lzss::decompress(stream).len(),
                record.allocation,
                "{}: image {} does not fill its allocation",
                profile.name,
                record.index
            );
            assert!(
                record.image_bytes <= record.allocation,
                "{}: image {} is larger than its allocation",
                profile.name,
                record.index
            );
        }
        std::fs::remove_dir_all(&out).ok();
    }
}

#[test]
fn alucards_mode_prefix_records_are_skipped_and_preserved() {
    let Some((profile, prg, chr)) = available()
        .into_iter()
        .find(|(profile, _, _)| profile.name == "alucard")
    else {
        eprintln!("skipping: ALUCARD is absent");
        return;
    };
    assert_eq!(profile.stream_entry_base, 3);
    let out = scratch("alucard-prefix");
    let manifest = player::extract(profile.name, &prg, &chr, &out).expect("extract");
    assert!(
        manifest.lead_bytes > 0,
        "expected mode-prefix bytes before the first image"
    );
    assert_eq!(manifest.lead_bytes, manifest.arena_start);

    let rebuilt = player::rebuild_bytes(&out.join(player::MANIFEST_NAME), &chr).expect("rebuild");
    let retail = std::fs::read(&chr).expect("read chr");
    assert_eq!(
        rebuilt.chr[..manifest.lead_bytes],
        retail[..manifest.lead_bytes],
        "the mode-prefix records were regenerated instead of copied"
    );
    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn an_unedited_rebuild_recompresses_nothing() {
    let Some((out, chr, manifest_data)) = maria("unedited") else {
        eprintln!("skipping: MARIA is absent");
        return;
    };
    let rebuilt = player::rebuild_bytes(&out.join(player::MANIFEST_NAME), &chr).expect("rebuild");
    assert_eq!(
        rebuilt.changed,
        0,
        "{} of {} streams were recompressed with no edit",
        rebuilt.changed,
        manifest_data.images.len()
    );
    assert_eq!(rebuilt.directory.len(), manifest_data.images.len());
    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn an_edited_sprite_recompresses_only_itself_and_spares_the_tail() {
    let Some((out, chr, manifest_data)) = maria("edit") else {
        eprintln!("skipping: MARIA is absent");
        return;
    };
    let manifest = out.join(player::MANIFEST_NAME);
    player::verify(&manifest, &chr).expect("unedited verify");

    let record = &manifest_data.images[0];
    let path = out.join(&record.file);
    let mut sprite = image::read_indexed(&path).expect("read sprite");
    let before = sprite.get(0, 0);
    sprite.set(0, 0, if before == 15 { 0 } else { before + 1 });
    image::write_indexed(&path, &sprite).expect("write sprite");

    let rebuilt = player::rebuild_bytes(&manifest, &chr).expect("rebuild");
    let retail = std::fs::read(&chr).expect("read chr");
    assert_eq!(rebuilt.changed, 1, "exactly one stream should recompress");
    assert_eq!(rebuilt.chr.len(), retail.len(), "the CHR changed size");
    assert_ne!(rebuilt.chr, retail, "the edit was dropped");
    assert_eq!(
        rebuilt.chr[player::ARENA_END..],
        retail[player::ARENA_END..],
        "an edit disturbed the shared tail"
    );
    assert!(
        player::verify(&manifest, &chr).is_err(),
        "verify passed on an edited sprite"
    );
    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn the_tail_is_identical_across_every_player() {
    let profiles = available();
    if profiles.len() < 2 {
        eprintln!("skipping: need at least two players");
        return;
    }
    let mut tails = Vec::new();
    for (_, _, chr) in &profiles {
        let data = std::fs::read(chr).expect("read chr");
        tails.push(data[player::ARENA_END..].to_vec());
    }
    for tail in &tails[1..] {
        assert_eq!(tail, &tails[0], "player CHR tails diverged");
    }
    eprintln!(
        "{} byte shared tail, identical across players",
        tails[0].len()
    );
}

#[test]
fn an_undecompiled_player_has_no_generated_headers() {
    let Some((profile, prg, chr)) = available()
        .into_iter()
        .find(|(profile, _, _)| profile.header.is_none())
    else {
        eprintln!("skipping: no undecompiled player present");
        return;
    };
    let out = scratch("no-header");
    let manifest = player::extract(profile.name, &prg, &chr, &out).expect("extract");
    assert!(player::emit_palette_header(&manifest).is_err());
    assert!(player::emit_directory_header(&manifest, &[]).is_err());
    std::fs::remove_dir_all(&out).ok();
}

#[test]
fn the_generated_headers_are_deterministic_and_match_the_build() {
    for (profile, directory) in [("maria", "maria"), ("richter", "ric")] {
        let Some((p, prg, chr)) = available()
            .into_iter()
            .find(|(candidate, _, _)| candidate.name == profile)
        else {
            eprintln!("skipping: {profile} is absent");
            continue;
        };
        let out = scratch(&format!("headers-{profile}"));
        let manifest_data = player::extract(p.name, &prg, &chr, &out).expect("extract");
        let manifest = out.join(player::MANIFEST_NAME);
        let rebuilt = player::rebuild_bytes(&manifest, &chr).expect("rebuild");

        let emitted = player::emit_directory_header(&manifest_data, &rebuilt.directory).unwrap();
        let again = player::emit_directory_header(&manifest_data, &rebuilt.directory).unwrap();
        assert_eq!(emitted, again, "directory emission is not deterministic");

        let built = repo_root().join(format!("src/saturn/{directory}/gen"));
        if built.join("gfxloads.h").exists() {
            player::verify_headers(
                &manifest,
                &chr,
                &built.join("gfxloads.h"),
                &built.join("palette.h"),
            )
            .expect("the headers in the tree are not what regenerates");
        } else {
            eprintln!("note: no built headers for {profile}; run ./sotn.sh build saturn");
        }
        std::fs::remove_dir_all(&out).ok();
    }
}
