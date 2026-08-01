//! round trip retail SD*.PCM
//!
//! a couple of files by default, set SATURN_AUDIO_ALL=1 for all of them

use saturn_assets::{adpcm, audio};
use std::path::{Path, PathBuf};

fn repo_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR"))
        .ancestors()
        .nth(3)
        // CARGO_MANIFEST_DIR is <repo>/tools/saturn/assets
        .expect("crate is three levels below the repo root")
        .to_path_buf()
}

fn audio_dir() -> Option<PathBuf> {
    let dir = repo_root().join("disks/saturn/SD");
    dir.is_dir().then_some(dir)
}

/// (codec, file)
fn streams(dir: &Path) -> Vec<(&'static str, PathBuf)> {
    let mut out = Vec::new();
    for entry in std::fs::read_dir(dir).expect("read SD dir") {
        let path = entry.expect("dir entry").path();
        let Some(name) = path.file_name().and_then(|n| n.to_str()) else {
            continue;
        };
        if !name.ends_with(".PCM") {
            continue;
        }
        let codec = if name.starts_with("SDD") || name.starts_with("SDE") {
            "voice"
        } else if name == "SDF0.PCM" {
            "mono"
        } else {
            "stereo"
        };
        out.push((codec, path));
    }
    out.sort_by(|a, b| a.1.cmp(&b.1));
    out
}

fn check_every_file() -> bool {
    matches!(
        std::env::var("SATURN_AUDIO_ALL").as_deref(),
        Ok("1") | Ok("true")
    )
}

/// one of each codec, the whole set takes minutes
fn sample(streams: Vec<(&'static str, PathBuf)>) -> Vec<(&'static str, PathBuf)> {
    if check_every_file() {
        return streams;
    }
    let mut seen = Vec::new();
    streams
        .into_iter()
        .filter(|(codec, _)| {
            if seen.contains(codec) {
                return false;
            }
            seen.push(codec);
            true
        })
        .collect()
}

fn scratch(name: &str) -> PathBuf {
    let dir = std::env::temp_dir().join(format!("saturn-audio-{name}-{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    std::fs::create_dir_all(&dir).expect("create scratch dir");
    dir
}

#[test]
fn retail_streams_round_trip_byte_for_byte() {
    let Some(dir) = audio_dir() else {
        eprintln!("skipping: disks/saturn/SD not present");
        return;
    };
    let all = streams(&dir);
    assert!(!all.is_empty(), "no SD*.PCM found in {}", dir.display());
    let streams = sample(all);

    let mut failures = Vec::new();
    for (codec, path) in &streams {
        let name = path.file_name().unwrap().to_string_lossy().into_owned();
        let out = scratch(&name);
        match audio::extract(codec, path, &out, adpcm::SAMPLE_RATE) {
            Ok(_) => {
                if let Err(e) = audio::verify(&out.join(audio::MANIFEST_NAME), path) {
                    failures.push(format!("{name} ({codec}): {e}"));
                }
            }
            Err(e) => failures.push(format!("{name} ({codec}): extract: {e}")),
        }
        std::fs::remove_dir_all(&out).ok();
    }

    assert!(
        failures.is_empty(),
        "{} of {} streams did not round-trip:\n  {}",
        failures.len(),
        streams.len(),
        failures.join("\n  ")
    );
    eprintln!("{} streams round-tripped byte-exactly", streams.len());
}

#[test]
fn an_edited_sample_reaches_the_stream_and_verify_refuses() {
    let Some(dir) = audio_dir() else {
        eprintln!("skipping: disks/saturn/SD not present");
        return;
    };
    // one of each codec
    for (codec, file) in [
        ("voice", "SDD0.PCM"),
        ("mono", "SDF0.PCM"),
        ("stereo", "SD01.PCM"),
    ] {
        let source = dir.join(file);
        if !source.exists() {
            eprintln!("skipping {file}: not present");
            continue;
        }
        let out = scratch(&format!("edit-{file}"));
        let manifest_data =
            audio::extract(codec, &source, &out, adpcm::SAMPLE_RATE).expect("extract");
        let manifest = out.join(audio::MANIFEST_NAME);
        audio::verify(&manifest, &source).expect("unedited verify");

        // edit a sample
        let wav_path = out.join(&manifest_data.audio);
        let mut wav = saturn_assets::wav::read(&wav_path).expect("read wav");
        let index = wav.samples.len() / 2;
        wav.samples[index] = wav.samples[index].saturating_add(4000);
        saturn_assets::wav::write(&wav_path, &wav).expect("write wav");

        let rebuilt = audio::rebuild_bytes(&manifest).expect("rebuild");
        let retail = std::fs::read(&source).expect("read retail");
        assert_eq!(rebuilt.len(), retail.len(), "{file} changed size");
        assert_ne!(rebuilt, retail, "{file} ignored the edit");
        assert!(
            audio::verify(&manifest, &source).is_err(),
            "{file}: verify passed on edited audio"
        );

        std::fs::remove_dir_all(&out).ok();
    }
}
