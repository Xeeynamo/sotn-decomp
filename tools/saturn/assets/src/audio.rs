use crate::adpcm;
use crate::wav::{self, Audio};
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::path::Path;

pub const FORMAT: &str = "sotn-saturn-adpcm";
pub const VERSION: u32 = 1;
pub const AUDIO_NAME: &str = "audio.wav";
pub const HEADER_NAME: &str = "header.bin";
pub const TRAILER_NAME: &str = "trailer.bin";
pub const MANIFEST_NAME: &str = "manifest.json";

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
#[serde(rename_all = "lowercase")]
pub enum Codec {
    /// "DVI." container, block-interleaved stereo ADPCM
    Stereo,
    /// headerless mono ADPCM, SDF0.PCM etc.
    Mono,
    /// headerless 8-bit signed DPCM, SDD*/SDE*
    Voice,
}

impl Codec {
    pub fn parse(name: &str) -> Result<Codec> {
        match name {
            "stereo" => Ok(Codec::Stereo),
            "mono" => Ok(Codec::Mono),
            "voice" => Ok(Codec::Voice),
            _ => Err(Error::Format(format!(
                "unknown codec {name:?}; known: stereo, mono, voice"
            ))),
        }
    }

    pub fn channels(self) -> u16 {
        match self {
            Codec::Stereo => 2,
            Codec::Mono | Codec::Voice => 1,
        }
    }
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Source {
    pub name: String,
    pub size: usize,
    pub sha256: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Manifest {
    pub format: String,
    pub version: u32,
    pub codec: Codec,
    pub channels: u16,
    /// not in file for mono and voice
    pub sample_rate: u32,
    pub samples: usize,
    pub audio: String,
    /// "DVI." header
    #[serde(skip_serializing_if = "Option::is_none")]
    pub header: Option<adpcm::StereoHeader>,
    /// if json can't specify header bytes
    #[serde(skip_serializing_if = "Option::is_none")]
    pub header_raw: Option<String>,
    /// possible trailing incomplete block (not found in sotn)
    #[serde(skip_serializing_if = "Option::is_none")]
    pub trailer: Option<String>,
    pub source: Source,
}

fn decode(codec: Codec, payload: &[u8]) -> Vec<i16> {
    match codec {
        Codec::Stereo => adpcm::decode_stereo(payload),
        Codec::Mono => adpcm::decode_mono(payload),
        Codec::Voice => adpcm::decode_voice(payload),
    }
}

fn encode(codec: Codec, samples: &[i16]) -> Vec<u8> {
    match codec {
        Codec::Stereo => adpcm::encode_stereo(samples),
        Codec::Mono => adpcm::encode_mono(samples),
        Codec::Voice => adpcm::encode_voice(samples),
    }
}

fn split<'a>(codec: Codec, data: &'a [u8]) -> Result<(&'a [u8], &'a [u8], &'a [u8])> {
    match codec {
        Codec::Stereo => {
            let header = adpcm::parse_stereo_header(data)?;
            let payload = &data[header.headlen..];
            // can only decode 8 bytes at a time
            let decodable = payload.len() / 8 * 8;
            Ok((
                &data[..header.headlen],
                &payload[..decodable],
                &payload[decodable..],
            ))
        }
        Codec::Mono | Codec::Voice => Ok((&[], data, &[])),
    }
}

pub fn extract(codec: &str, source_path: &Path, output_dir: &Path, rate: u32) -> Result<Manifest> {
    let codec = Codec::parse(codec)?;
    let data = std::fs::read(source_path)?;
    let (header, payload, trailer) = split(codec, &data)?;
    let samples = decode(codec, payload);

    std::fs::create_dir_all(output_dir)?;
    wav::write(
        &output_dir.join(AUDIO_NAME),
        &Audio {
            channels: codec.channels(),
            sample_rate: rate,
            samples: samples.clone(),
        },
    )?;
    // fall back to raw bytes if header not specified
    let mut modelled = None;
    let mut raw = None;
    if !header.is_empty() {
        let parsed = adpcm::parse_stereo_header(&data)?;
        if parsed.to_bytes(payload.len() as u32) == header {
            modelled = Some(parsed);
        } else {
            std::fs::write(output_dir.join(HEADER_NAME), header)?;
            raw = Some(HEADER_NAME.to_string());
        }
    }
    if !trailer.is_empty() {
        std::fs::write(output_dir.join(TRAILER_NAME), trailer)?;
    }

    let manifest = Manifest {
        format: FORMAT.to_string(),
        version: VERSION,
        codec,
        channels: codec.channels(),
        sample_rate: rate,
        samples: samples.len(),
        audio: AUDIO_NAME.to_string(),
        header: modelled,
        header_raw: raw,
        trailer: (!trailer.is_empty()).then(|| TRAILER_NAME.to_string()),
        source: Source {
            name: source_path
                .file_name()
                .map(|n| n.to_string_lossy().into_owned())
                .unwrap_or_else(|| source_path.display().to_string()),
            size: data.len(),
            sha256: sha256_hex(&data),
        },
    };
    let mut json = serde_json::to_string_pretty(&manifest)?;
    json.push('\n');
    std::fs::write(output_dir.join(MANIFEST_NAME), json)?;
    Ok(manifest)
}

pub fn load_manifest(manifest_path: &Path) -> Result<Manifest> {
    let manifest: Manifest = serde_json::from_str(&std::fs::read_to_string(manifest_path)?)?;
    if manifest.format != FORMAT {
        return Err(Error::Format(format!(
            "{} is not a {FORMAT} manifest",
            manifest_path.display()
        )));
    }
    Ok(manifest)
}

pub fn rebuild_bytes(manifest_path: &Path) -> Result<Vec<u8>> {
    let manifest = load_manifest(manifest_path)?;
    let dir = manifest_path.parent().unwrap_or_else(|| Path::new("."));
    let audio = wav::read(&dir.join(&manifest.audio))?;
    if audio.channels != manifest.channels {
        return Err(Error::Format(format!(
            "{} has {} channels, expected {}",
            manifest.audio, audio.channels, manifest.channels
        )));
    }

    let payload = encode(manifest.codec, &audio.samples);
    let mut out = Vec::new();
    match (&manifest.header, &manifest.header_raw) {
        // handle loop point
        (Some(header), _) => out.extend_from_slice(&header.to_bytes(payload.len() as u32)),
        // handle other parts of header
        (None, Some(name)) => {
            let mut header = std::fs::read(dir.join(name))?;
            if header.len() >= 12 {
                header[8..12].copy_from_slice(&(payload.len() as u32).to_be_bytes());
            }
            out.extend_from_slice(&header);
        }
        (None, None) => {}
    }
    out.extend_from_slice(&payload);
    if let Some(trailer) = &manifest.trailer {
        out.extend_from_slice(&std::fs::read(dir.join(trailer))?);
    }
    Ok(out)
}

pub fn rebuild(manifest_path: &Path, output_path: &Path) -> Result<Vec<u8>> {
    let data = rebuild_bytes(manifest_path)?;
    if let Some(parent) = output_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(output_path, &data)?;
    Ok(data)
}

pub fn verify(manifest_path: &Path, source_path: &Path) -> Result<()> {
    let rebuilt = rebuild_bytes(manifest_path)?;
    let retail = std::fs::read(source_path)?;
    if rebuilt == retail {
        return Ok(());
    }
    let detail = if rebuilt.len() != retail.len() {
        format!("{} bytes rebuilt vs {} retail", rebuilt.len(), retail.len())
    } else {
        let at = rebuilt
            .iter()
            .zip(&retail)
            .position(|(a, b)| a != b)
            .unwrap_or(0);
        format!("first difference at offset 0x{at:X}")
    };
    Err(Error::Mismatch(format!(
        "rebuilt audio does not match {} ({detail})",
        source_path.display()
    )))
}
