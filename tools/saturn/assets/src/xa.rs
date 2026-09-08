use crate::adpcm;
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::path::Path;

pub const SAMPLE_RATE: u32 = 37_800;
pub const SECTOR_SIZE: usize = 2_352;
pub const FRAMES_PER_SECTOR: usize = 2_016;
const GROUPS_PER_SECTOR: usize = 18;
const GROUP_SIZE: usize = 128;

const FILTER_POS: [i32; 4] = [0, 60, 115, 98];
const FILTER_NEG: [i32; 4] = [0, 0, -52, -55];

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Manifest {
    pub format: String,
    pub version: u32,
    pub source: String,
    pub source_sha256: String,
    pub sample_rate: u32,
    pub file_number: u8,
    pub channel: u8,
    pub sectors: usize,
    pub frames: usize,
    pub loop_source_frame: usize,
    pub loop_frame: usize,
    pub loop_sector: usize,
    pub intro_vsync: usize,
    pub loop_vsync: usize,
    pub xa: String,
    pub cue: String,
    pub config_header: String,
}

#[derive(Clone, Copy, Default)]
struct History {
    old: i32,
    older: i32,
}

fn clamp16(value: i32) -> i32 {
    value.clamp(i16::MIN as i32, i16::MAX as i32)
}

fn resample_stereo(samples: &[i16], source_rate: u32) -> Vec<i16> {
    let source_frames = samples.len() / 2;
    if source_frames == 0 {
        return Vec::new();
    }
    let output_frames = source_frames * SAMPLE_RATE as usize / source_rate as usize;
    let mut out = Vec::with_capacity(output_frames * 2);
    for frame in 0..output_frames {
        let position = frame as u64 * source_rate as u64;
        let base = (position / SAMPLE_RATE as u64) as usize;
        let fraction = (position % SAMPLE_RATE as u64) as i64;
        let next = (base + 1).min(source_frames - 1);
        for channel in 0..2 {
            let a = samples[base * 2 + channel] as i64;
            let b = samples[next * 2 + channel] as i64;
            let value = a + ((b - a) * fraction + SAMPLE_RATE as i64 / 2) / SAMPLE_RATE as i64;
            out.push(value.clamp(i16::MIN as i64, i16::MAX as i64) as i16);
        }
    }
    out
}

fn encode_unit(samples: &[i16], history: &mut History) -> (u8, [u8; 28]) {
    let mut best_error = i64::MAX;
    let mut best_header = 0u8;
    let mut best_nibbles = [0u8; 28];
    let mut best_history = *history;

    for filter in 0..4 {
        for shift in 0..=12 {
            let mut candidate = *history;
            let mut nibbles = [0u8; 28];
            let mut error = 0i64;
            let scale = 1i32 << (12 - shift);
            for (index, &sample) in samples.iter().enumerate() {
                let prediction = (candidate.old * FILTER_POS[filter]
                    + candidate.older * FILTER_NEG[filter]
                    + 32)
                    / 64;
                let residual = sample as i32 - prediction;
                let mut nibble = if residual >= 0 {
                    (residual + scale / 2) / scale
                } else {
                    (residual - scale / 2) / scale
                };
                nibble = nibble.clamp(-8, 7);
                let decoded = clamp16(nibble * scale + prediction);
                let delta = sample as i64 - decoded as i64;
                error += delta * delta;
                nibbles[index] = (nibble & 0xF) as u8;
                candidate.older = candidate.old;
                candidate.old = decoded;
            }
            if error < best_error {
                best_error = error;
                best_header = ((filter as u8) << 4) | shift as u8;
                best_nibbles = nibbles;
                best_history = candidate;
            }
        }
    }
    *history = best_history;
    (best_header, best_nibbles)
}

fn bcd(value: usize) -> u8 {
    (((value / 10) << 4) | (value % 10)) as u8
}

fn encode_sector(
    frames: &[i16],
    sector_number: usize,
    file_number: u8,
    channel: u8,
    histories: &mut [History; 2],
    is_last: bool,
) -> [u8; SECTOR_SIZE] {
    let mut sector = [0u8; SECTOR_SIZE];
    sector[1..11].fill(0xFF);
    let absolute = sector_number + 150;
    sector[0x0C] = bcd(absolute / (60 * 75));
    sector[0x0D] = bcd((absolute / 75) % 60);
    sector[0x0E] = bcd(absolute % 75);
    sector[0x0F] = 2;
    let submode = 0x64 | if is_last { 0x81 } else { 0 };
    let subheader = [file_number, channel, submode, 0x01];
    sector[0x10..0x14].copy_from_slice(&subheader);
    sector[0x14..0x18].copy_from_slice(&subheader);

    for group in 0..GROUPS_PER_SECTOR {
        let group_base = 0x18 + group * GROUP_SIZE;
        for sub in 0..4 {
            let frame_base = (group * 4 + sub) * 28;
            let mut encoded = [[0u8; 28]; 2];
            for channel_id in 0..2 {
                let mut unit = [0i16; 28];
                for sample in 0..28 {
                    let frame = frame_base + sample;
                    unit[sample] = frames.get(frame * 2 + channel_id).copied().unwrap_or(0);
                }
                let (parameter, nibbles) = encode_unit(&unit, &mut histories[channel_id]);
                sector[group_base + 4 + sub * 2 + channel_id] = parameter;
                encoded[channel_id] = nibbles;
            }
            for sample in 0..28 {
                sector[group_base + 16 + sub + sample * 4] =
                    encoded[0][sample] | (encoded[1][sample] << 4);
            }
        }
    }
    sector
}

fn write_config_header(path: &Path, manifest: &Manifest) -> Result<()> {
    let text = format!(
        "#ifndef SATURN_XA_CONFIG_H\n#define SATURN_XA_CONFIG_H\n\n\
         #define SATURN_XA_FILE_NUMBER {}\n\
         #define SATURN_XA_CHANNEL {}\n\
         #define SATURN_XA_SECTORS {}\n\
         #define SATURN_XA_LOOP_SECTOR {}\n\
         #define SATURN_XA_INTRO_VSYNC {}\n\
         #define SATURN_XA_LOOP_VSYNC {}\n\n#endif\n",
        manifest.file_number,
        manifest.channel,
        manifest.sectors,
        manifest.loop_sector,
        manifest.intro_vsync,
        manifest.loop_vsync
    );
    std::fs::write(path, text)?;
    Ok(())
}

pub fn export_saturn_stereo(
    source_path: &Path,
    output_dir: &Path,
    file_number: u8,
    channel: u8,
) -> Result<Manifest> {
    if channel > 31 {
        return Err(Error::Format(format!(
            "XA channel {channel} is outside 0..=31"
        )));
    }
    let source = std::fs::read(source_path)?;
    let header = adpcm::parse_stereo_header(&source)?;
    let loop_source_frame = header
        .loop_point
        .ok_or_else(|| Error::Format(format!("{} has no loop point", source_path.display())))?
        as usize;
    let payload = &source[header.headlen..];
    let samples = adpcm::decode_stereo(&payload[..payload.len() / 8 * 8]);
    let source_frames = samples.len() / 2;
    if loop_source_frame >= source_frames {
        return Err(Error::Format(format!(
            "loop frame {loop_source_frame} is outside {source_frames} source frames"
        )));
    }
    let resampled = resample_stereo(&samples, adpcm::SAMPLE_RATE);
    let requested_loop = loop_source_frame * SAMPLE_RATE as usize / adpcm::SAMPLE_RATE as usize;
    let loop_sector = requested_loop / FRAMES_PER_SECTOR;
    let loop_frame = loop_sector * FRAMES_PER_SECTOR;
    let sectors = (resampled.len() / 2 + FRAMES_PER_SECTOR - 1) / FRAMES_PER_SECTOR;
    if loop_sector >= sectors {
        return Err(Error::Format("XA loop sector is outside the stream".into()));
    }

    std::fs::create_dir_all(output_dir)?;
    let mut xa = Vec::with_capacity(sectors * SECTOR_SIZE);
    let mut histories = [History::default(); 2];
    for sector in 0..sectors {
        if sector == loop_sector {
            histories = [History::default(); 2];
        }
        let frame = sector * FRAMES_PER_SECTOR;
        xa.extend_from_slice(&encode_sector(
            &resampled[frame * 2..],
            sector,
            file_number,
            channel,
            &mut histories,
            sector + 1 == sectors,
        ));
    }

    const XA_NAME: &str = "audio.xa";
    const CUE_NAME: &str = "audio.cue";
    const HEADER_NAME: &str = "xa_config.h";
    const MANIFEST_NAME: &str = "xa_manifest.json";
    std::fs::write(output_dir.join(XA_NAME), &xa)?;
    std::fs::write(
        output_dir.join(CUE_NAME),
        format!("FILE \"{XA_NAME}\" BINARY\n  TRACK 01 MODE2/2352\n    INDEX 01 00:00:00\n"),
    )?;

    let frames = sectors * FRAMES_PER_SECTOR;
    let manifest = Manifest {
        format: "playstation-xa-adpcm".into(),
        version: 1,
        source: source_path
            .file_name()
            .map(|name| name.to_string_lossy().into_owned())
            .unwrap_or_else(|| source_path.display().to_string()),
        source_sha256: sha256_hex(&source),
        sample_rate: SAMPLE_RATE,
        file_number,
        channel,
        sectors,
        frames,
        loop_source_frame,
        loop_frame,
        loop_sector,
        intro_vsync: (loop_frame * 60 + SAMPLE_RATE as usize / 2) / SAMPLE_RATE as usize,
        loop_vsync: ((frames - loop_frame) * 60 + SAMPLE_RATE as usize / 2) / SAMPLE_RATE as usize,
        xa: XA_NAME.into(),
        cue: CUE_NAME.into(),
        config_header: HEADER_NAME.into(),
    };
    write_config_header(&output_dir.join(HEADER_NAME), &manifest)?;
    let mut json = serde_json::to_string_pretty(&manifest)?;
    json.push('\n');
    std::fs::write(output_dir.join(MANIFEST_NAME), json)?;
    Ok(manifest)
}

#[cfg(test)]
mod tests {
    use super::*;

    fn decode_unit(header: u8, nibbles: &[u8; 28], history: &mut History) -> Vec<i16> {
        let shift = 12 - (header & 0xF).min(12) as i32;
        let filter = ((header >> 4) & 3) as usize;
        nibbles
            .iter()
            .map(|&nibble| {
                let signed = if nibble & 8 != 0 {
                    nibble as i32 - 16
                } else {
                    nibble as i32
                };
                let prediction =
                    (history.old * FILTER_POS[filter] + history.older * FILTER_NEG[filter] + 32)
                        / 64;
                let decoded = clamp16((signed << shift) + prediction);
                history.older = history.old;
                history.old = decoded;
                decoded as i16
            })
            .collect()
    }

    #[test]
    fn unit_encoder_tracks_a_sine_wave() {
        let samples: [i16; 28] =
            std::array::from_fn(|i| ((i as f32 * 0.31).sin() * 20_000.0) as i16);
        let mut encode_history = History::default();
        let (header, nibbles) = encode_unit(&samples, &mut encode_history);
        let decoded = decode_unit(header, &nibbles, &mut History::default());
        let error = samples
            .iter()
            .zip(decoded)
            .map(|(&a, b)| {
                let delta = a as i64 - b as i64;
                delta * delta
            })
            .sum::<i64>() as f64
            / samples.len() as f64;
        assert!(error.sqrt() < 2_500.0, "RMSE was {}", error.sqrt());
    }

    #[test]
    fn sector_has_mode2_xa_headers() {
        let sector = encode_sector(
            &vec![0; FRAMES_PER_SECTOR * 2],
            0,
            25,
            3,
            &mut [History::default(); 2],
            true,
        );
        assert_eq!(
            &sector[..12],
            &[0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0]
        );
        assert_eq!(sector[0x0F], 2);
        assert_eq!(&sector[0x10..0x12], &[25, 3]);
        assert_eq!(&sector[0x10..0x14], &sector[0x14..0x18]);
        assert_eq!(sector[0x13], 1);
        assert_eq!(sector.len(), SECTOR_SIZE);
    }
}
