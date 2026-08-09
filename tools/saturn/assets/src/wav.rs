//! minimal 16-bit PCM RIFF/WAVE read and write

use crate::{Error, Result};
use std::path::Path;

pub struct Audio {
    pub channels: u16,
    pub sample_rate: u32,
    /// interleaved by channel
    pub samples: Vec<i16>,
}

fn u32_at(data: &[u8], offset: usize) -> u32 {
    u32::from_le_bytes([
        data[offset],
        data[offset + 1],
        data[offset + 2],
        data[offset + 3],
    ])
}

fn u16_at(data: &[u8], offset: usize) -> u16 {
    u16::from_le_bytes([data[offset], data[offset + 1]])
}

pub fn write(path: &Path, audio: &Audio) -> Result<()> {
    if let Some(parent) = path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    let block_align = audio.channels * 2;
    let data_len = audio.samples.len() * 2;
    let mut out = Vec::with_capacity(44 + data_len);
    out.extend_from_slice(b"RIFF");
    out.extend_from_slice(&((36 + data_len) as u32).to_le_bytes());
    out.extend_from_slice(b"WAVEfmt ");
    out.extend_from_slice(&16u32.to_le_bytes()); // PCM fmt chunk size
    out.extend_from_slice(&1u16.to_le_bytes()); // PCM
    out.extend_from_slice(&audio.channels.to_le_bytes());
    out.extend_from_slice(&audio.sample_rate.to_le_bytes());
    out.extend_from_slice(&(audio.sample_rate * block_align as u32).to_le_bytes());
    out.extend_from_slice(&block_align.to_le_bytes());
    out.extend_from_slice(&16u16.to_le_bytes()); // bits per sample
    out.extend_from_slice(b"data");
    out.extend_from_slice(&(data_len as u32).to_le_bytes());
    for sample in &audio.samples {
        out.extend_from_slice(&sample.to_le_bytes());
    }
    std::fs::write(path, out)?;
    Ok(())
}

pub fn read(path: &Path) -> Result<Audio> {
    let data = std::fs::read(path)?;
    let bad = |what: &str| Error::Format(format!("{}: {what}", path.display()));
    if data.len() < 12 || &data[0..4] != b"RIFF" || &data[8..12] != b"WAVE" {
        return Err(bad("not a RIFF/WAVE file"));
    }

    let mut channels = None;
    let mut sample_rate = None;
    let mut samples = None;
    let mut pos = 12;
    while pos + 8 <= data.len() {
        let id = &data[pos..pos + 4];
        let size = u32_at(&data, pos + 4) as usize;
        let body = pos + 8;
        if body + size > data.len() {
            return Err(bad("chunk runs past the end of the file"));
        }
        match id {
            b"fmt " => {
                if size < 16 {
                    return Err(bad("short fmt chunk"));
                }
                if u16_at(&data, body) != 1 || u16_at(&data, body + 14) != 16 {
                    return Err(bad("only 16-bit PCM is supported"));
                }
                channels = Some(u16_at(&data, body + 2));
                sample_rate = Some(u32_at(&data, body + 4));
            }
            b"data" => {
                samples = Some(
                    data[body..body + size]
                        .chunks_exact(2)
                        .map(|c| i16::from_le_bytes([c[0], c[1]]))
                        .collect::<Vec<i16>>(),
                );
            }
            _ => {}
        }
        // padding
        pos = body + size + (size & 1);
    }

    match (channels, sample_rate, samples) {
        (Some(channels), Some(sample_rate), Some(samples)) => Ok(Audio {
            channels,
            sample_rate,
            samples,
        }),
        _ => Err(bad("missing a fmt or data chunk")),
    }
}
