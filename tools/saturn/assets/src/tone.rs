
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::path::Path;

pub const FORMAT: &str = "sotn-saturn-tone-bank";
pub const VERSION: u32 = 1;
pub const SAMPLES_NAME: &str = "samples.bin";

const HEADER_SIZE: usize = 8;
const LAYER_SIZE: usize = 0x20;
const VOICE_HEADER_SIZE: usize = 4;
const CURVE_SIZE: usize = 10;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
pub struct CurveSegment {
    pub velocity: u8,
    pub level: u8,
    pub coefficient: u8,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
pub struct VelocityCurve {
    pub coefficient: u8,
    pub segments: [CurveSegment; 3],
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
pub struct Layer {
    pub start_note: u8,
    pub end_note: u8,
    pub source_address: u32,
    pub loop_start: u16,
    pub loop_end: u16,
    pub envelope: u32,
    pub sound_direct: u8,
    pub total_level: u8,
    pub modulation: u16,
    #[serde(default, skip_serializing_if = "is_zero_u16")]
    pub reserved_12: u16,
    pub lfo: u16,
    pub effect_input: u16,
    pub direct_pan: u8,
    pub base_note: u8,
    pub fine_tune: i8,
    #[serde(default, skip_serializing_if = "is_zero_u16")]
    pub reserved_1b: u16,
    pub velocity_curve: u8,
    #[serde(default, skip_serializing_if = "is_zero_u16")]
    pub reserved_1e: u16,
}

#[derive(Debug, Clone, PartialEq, Eq, Serialize, Deserialize)]
pub struct Voice {
    pub play_mode_and_bend_range: u8,
    pub portamento_time: u8,
    pub volume_bias: i8,
    pub layers: Vec<Layer>,
}

#[derive(Debug, Clone, PartialEq, Eq, Serialize, Deserialize)]
pub struct Samples {
    pub offset: usize,
    pub size: usize,
    pub sha256: String,
    pub file: String,
}

#[derive(Debug, Clone, PartialEq, Eq, Serialize, Deserialize)]
pub struct Bank {
    pub format: String,
    pub version: u32,
    pub size: usize,
    pub mixer: String,
    pub velocity_curves: Vec<VelocityCurve>,
    pub unknown_4: String,
    pub unknown_6: String,
    pub voices: Vec<Voice>,
    pub samples: Samples,
}

fn is_zero_u16(value: &u16) -> bool {
    *value == 0
}

fn to_hex(bytes: &[u8]) -> String {
    bytes.iter().map(|b| format!("{b:02x}")).collect()
}

fn from_hex(text: &str, what: &str) -> Result<Vec<u8>> {
    if !text.len().is_multiple_of(2) {
        return Err(Error::Format(format!(
            "{what} is {} hex digits, which is not a whole number of bytes",
            text.len()
        )));
    }
    (0..text.len())
        .step_by(2)
        .map(|at| {
            u8::from_str_radix(&text[at..at + 2], 16)
                .map_err(|_| Error::Format(format!("{what} is not hexadecimal: {text}")))
        })
        .collect()
}

fn read_u16(data: &[u8], at: usize) -> Result<u16> {
    data.get(at..at + 2)
        .map(|b| u16::from_be_bytes([b[0], b[1]]))
        .ok_or_else(|| Error::Format(format!("tone bank is truncated at 0x{at:X}")))
}

fn read_u32(data: &[u8], at: usize) -> Result<u32> {
    data.get(at..at + 4)
        .map(|b| u32::from_be_bytes([b[0], b[1], b[2], b[3]]))
        .ok_or_else(|| Error::Format(format!("tone bank is truncated at 0x{at:X}")))
}

fn block<'a>(data: &'a [u8], from: usize, to: usize, what: &str) -> Result<&'a [u8]> {
    if to < from {
        return Err(Error::Format(format!(
            "the tone bank's {what} block ends at 0x{to:X}, before it starts at 0x{from:X}"
        )));
    }
    data.get(from..to)
        .ok_or_else(|| Error::Format(format!("the tone bank's {what} block runs past its end")))
}

pub fn decode(data: &[u8], samples_file: &str) -> Result<Bank> {
    let mixer_offset = read_u16(data, 0)? as usize;
    let velocity_offset = read_u16(data, 2)? as usize;
    let unknown_4_offset = read_u16(data, 4)? as usize;
    let unknown_6_offset = read_u16(data, 6)? as usize;
    if mixer_offset < HEADER_SIZE || !(mixer_offset - HEADER_SIZE).is_multiple_of(2) {
        return Err(Error::Format(format!(
            "a voice table ending at 0x{mixer_offset:X} is not a whole number of offsets"
        )));
    }
    let count = (mixer_offset - HEADER_SIZE) / 2;
    if count == 0 {
        return Err(Error::Format("tone bank has no voices".to_string()));
    }

    let mut voice_offsets = Vec::with_capacity(count);
    for index in 0..count {
        voice_offsets.push(read_u16(data, HEADER_SIZE + index * 2)? as usize);
    }
    let first_voice = voice_offsets[0];

    let mixer = block(data, mixer_offset, velocity_offset, "mixer")?;
    let curves = block(data, velocity_offset, unknown_4_offset, "velocity curve")?;
    let unknown_4 = block(data, unknown_4_offset, unknown_6_offset, "unknown_4")?;
    let unknown_6 = block(data, unknown_6_offset, first_voice, "unknown_6")?;
    if !curves.len().is_multiple_of(CURVE_SIZE) {
        return Err(Error::Format(format!(
            "the velocity curve table is {} bytes, not a whole number of {CURVE_SIZE}-byte curves",
            curves.len()
        )));
    }
    let velocity_curves = curves
        .chunks_exact(CURVE_SIZE)
        .map(|curve| VelocityCurve {
            coefficient: curve[0],
            segments: std::array::from_fn(|i| CurveSegment {
                velocity: curve[1 + i * 3],
                level: curve[2 + i * 3],
                coefficient: curve[3 + i * 3],
            }),
        })
        .collect();

    let mut voices = Vec::with_capacity(count);
    let mut at = first_voice;
    for (index, &offset) in voice_offsets.iter().enumerate() {
        if offset != at {
            return Err(Error::Format(format!(
                "voice {index} is at 0x{offset:X}, but the voices before it end at 0x{at:X}; \
                 every tone bank on the disc packs them end to end"
            )));
        }
        let header = data
            .get(offset..offset + VOICE_HEADER_SIZE)
            .ok_or_else(|| Error::Format(format!("voice {index} lies outside the bank")))?;
        let layer_count_minus_one = header[2] as i8;
        if layer_count_minus_one < 0 {
            return Err(Error::Format(format!("voice {index} has no layers")));
        }
        let layer_count = layer_count_minus_one as usize + 1;
        let mut layers = Vec::with_capacity(layer_count);
        for layer in 0..layer_count {
            let base = offset + VOICE_HEADER_SIZE + layer * LAYER_SIZE;
            if base + LAYER_SIZE > data.len() {
                return Err(Error::Format(format!(
                    "voice {index}'s layers run past the end of the bank"
                )));
            }
            layers.push(Layer {
                start_note: data[base],
                end_note: data[base + 0x01],
                source_address: read_u32(data, base + 0x02)?,
                loop_start: read_u16(data, base + 0x06)?,
                loop_end: read_u16(data, base + 0x08)?,
                envelope: read_u32(data, base + 0x0A)?,
                sound_direct: data[base + 0x0E],
                total_level: data[base + 0x0F],
                modulation: read_u16(data, base + 0x10)?,
                reserved_12: read_u16(data, base + 0x12)?,
                lfo: read_u16(data, base + 0x14)?,
                effect_input: read_u16(data, base + 0x16)?,
                direct_pan: data[base + 0x18],
                base_note: data[base + 0x19],
                fine_tune: data[base + 0x1A] as i8,
                reserved_1b: read_u16(data, base + 0x1B)?,
                velocity_curve: data[base + 0x1D],
                reserved_1e: read_u16(data, base + 0x1E)?,
            });
        }
        at = offset + VOICE_HEADER_SIZE + layer_count * LAYER_SIZE;
        voices.push(Voice {
            play_mode_and_bend_range: header[0],
            portamento_time: header[1],
            volume_bias: header[3] as i8,
            layers,
        });
    }

    let samples = data
        .get(at..)
        .ok_or_else(|| Error::Format("the voices run past the end of the bank".to_string()))?;
    Ok(Bank {
        format: FORMAT.to_string(),
        version: VERSION,
        size: data.len(),
        mixer: to_hex(mixer),
        velocity_curves,
        unknown_4: to_hex(unknown_4),
        unknown_6: to_hex(unknown_6),
        voices,
        samples: Samples {
            offset: at,
            size: samples.len(),
            sha256: sha256_hex(samples),
            file: samples_file.to_string(),
        },
    })
}

pub fn encode(bank: &Bank, samples: &[u8]) -> Result<Vec<u8>> {
    if bank.format != FORMAT || bank.version != VERSION {
        return Err(Error::Format(format!("not a {FORMAT} v{VERSION} bank")));
    }
    if bank.voices.is_empty() {
        return Err(Error::Format("a tone bank has at least one voice".to_string()));
    }
    if samples.len() != bank.samples.size {
        return Err(Error::Format(format!(
            "{} is {} bytes, expected {}",
            bank.samples.file,
            samples.len(),
            bank.samples.size
        )));
    }

    let mixer = from_hex(&bank.mixer, "the mixer block")?;
    let unknown_4 = from_hex(&bank.unknown_4, "the unknown_4 block")?;
    let unknown_6 = from_hex(&bank.unknown_6, "the unknown_6 block")?;

    let mixer_offset = HEADER_SIZE + bank.voices.len() * 2;
    let velocity_offset = mixer_offset + mixer.len();
    let unknown_4_offset = velocity_offset + bank.velocity_curves.len() * CURVE_SIZE;
    let unknown_6_offset = unknown_4_offset + unknown_4.len();
    let first_voice = unknown_6_offset + unknown_6.len();

    let mut out = Vec::with_capacity(bank.size);
    for offset in [
        mixer_offset,
        velocity_offset,
        unknown_4_offset,
        unknown_6_offset,
    ] {
        let Ok(offset16) = u16::try_from(offset) else {
            return Err(Error::Format(
                "the tone bank's structure grew past its 16-bit offsets".to_string(),
            ));
        };
        out.extend_from_slice(&offset16.to_be_bytes());
    }

    let mut at = first_voice;
    for (index, voice) in bank.voices.iter().enumerate() {
        let Ok(offset16) = u16::try_from(at) else {
            return Err(Error::Format(format!(
                "voice {index} sits past the 16-bit voice offsets"
            )));
        };
        out.extend_from_slice(&offset16.to_be_bytes());
        if voice.layers.is_empty() || voice.layers.len() > 128 {
            return Err(Error::Format(format!(
                "voice {index} has {} layers; a voice holds 1 to 128",
                voice.layers.len()
            )));
        }
        at += VOICE_HEADER_SIZE + voice.layers.len() * LAYER_SIZE;
    }

    out.extend_from_slice(&mixer);
    for curve in &bank.velocity_curves {
        out.push(curve.coefficient);
        for segment in &curve.segments {
            out.extend_from_slice(&[segment.velocity, segment.level, segment.coefficient]);
        }
    }
    out.extend_from_slice(&unknown_4);
    out.extend_from_slice(&unknown_6);

    for voice in &bank.voices {
        out.extend_from_slice(&[
            voice.play_mode_and_bend_range,
            voice.portamento_time,
            (voice.layers.len() - 1) as u8,
            voice.volume_bias as u8,
        ]);
        for layer in &voice.layers {
            let mut record = [0u8; LAYER_SIZE];
            record[0x00] = layer.start_note;
            record[0x01] = layer.end_note;
            record[0x02..0x06].copy_from_slice(&layer.source_address.to_be_bytes());
            record[0x06..0x08].copy_from_slice(&layer.loop_start.to_be_bytes());
            record[0x08..0x0A].copy_from_slice(&layer.loop_end.to_be_bytes());
            record[0x0A..0x0E].copy_from_slice(&layer.envelope.to_be_bytes());
            record[0x0E] = layer.sound_direct;
            record[0x0F] = layer.total_level;
            record[0x10..0x12].copy_from_slice(&layer.modulation.to_be_bytes());
            record[0x12..0x14].copy_from_slice(&layer.reserved_12.to_be_bytes());
            record[0x14..0x16].copy_from_slice(&layer.lfo.to_be_bytes());
            record[0x16..0x18].copy_from_slice(&layer.effect_input.to_be_bytes());
            record[0x18] = layer.direct_pan;
            record[0x19] = layer.base_note;
            record[0x1A] = layer.fine_tune as u8;
            record[0x1B..0x1D].copy_from_slice(&layer.reserved_1b.to_be_bytes());
            record[0x1D] = layer.velocity_curve;
            record[0x1E..0x20].copy_from_slice(&layer.reserved_1e.to_be_bytes());
            out.extend_from_slice(&record);
        }
    }

    if out.len() != bank.samples.offset {
        return Err(Error::Format(format!(
            "the structure encodes to 0x{:X} bytes but the samples start at 0x{:X}",
            out.len(),
            bank.samples.offset
        )));
    }
    out.extend_from_slice(samples);
    if out.len() != bank.size {
        return Err(Error::Format(format!(
            "the bank encodes to {} bytes but the area is {} -- a sound area cannot change size \
             without rewriting 0.BIN's area map",
            out.len(),
            bank.size
        )));
    }
    Ok(out)
}

pub fn load(path: &Path) -> Result<Bank> {
    let text = std::fs::read_to_string(path)?;
    let bank: Bank = serde_json::from_str(&text)?;
    if bank.format != FORMAT || bank.version != VERSION {
        return Err(Error::Format(format!(
            "{} is not a {FORMAT} v{VERSION} bank",
            path.display()
        )));
    }
    Ok(bank)
}

pub fn write(bank: &Bank, path: &Path, samples: &[u8]) -> Result<()> {
    if let Some(parent) = path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    let mut json = serde_json::to_string_pretty(bank)?;
    json.push('\n');
    std::fs::write(path, json)?;
    let samples_path = path
        .parent()
        .unwrap_or_else(|| Path::new("."))
        .join(&bank.samples.file);
    std::fs::write(samples_path, samples)?;
    Ok(())
}

pub fn layer_count(bank: &Bank) -> usize {
    bank.voices.iter().map(|voice| voice.layers.len()).sum()
}

#[cfg(test)]
mod tests {
    use super::*;

    fn one_bank() -> Vec<u8> {
        let mixer = [0u8; 4];
        let curve = [0x00, 0x08, 0x00, 0x46, 0x0A, 0x15, 0x5E, 0x13, 0x3F, 0x70];
        let unknown_4 = [0x23u8, 0x00];
        let unknown_6 = [0x00u8, 0x24];
        let mixer_offset = HEADER_SIZE + 2 * 2;
        let velocity_offset = mixer_offset + mixer.len();
        let unknown_4_offset = velocity_offset + curve.len();
        let unknown_6_offset = unknown_4_offset + unknown_4.len();
        let first_voice = unknown_6_offset + unknown_6.len();
        let voice_size = VOICE_HEADER_SIZE + LAYER_SIZE;

        let mut out = Vec::new();
        for offset in [
            mixer_offset,
            velocity_offset,
            unknown_4_offset,
            unknown_6_offset,
        ] {
            out.extend_from_slice(&(offset as u16).to_be_bytes());
        }
        out.extend_from_slice(&(first_voice as u16).to_be_bytes());
        out.extend_from_slice(&((first_voice + voice_size) as u16).to_be_bytes());
        out.extend_from_slice(&mixer);
        out.extend_from_slice(&curve);
        out.extend_from_slice(&unknown_4);
        out.extend_from_slice(&unknown_6);
        for voice in 0..2u8 {
            out.extend_from_slice(&[0x02, 0x00, 0x00, 0x10]);
            let mut layer = [0u8; LAYER_SIZE];
            layer[0x00] = voice * 60;
            layer[0x01] = voice * 60 + 59;
            layer[0x02..0x06].copy_from_slice(&(0x0004_0000u32 + u32::from(voice)).to_be_bytes());
            layer[0x08..0x0A].copy_from_slice(&0x0100u16.to_be_bytes());
            layer[0x19] = 60;
            layer[0x1A] = 0xFF; 
            out.extend_from_slice(&layer);
        }
        out.extend_from_slice(&[0xAA; 8]);
        out
    }

    #[test]
    fn a_bank_decodes_to_named_voices_and_layers() {
        let data = one_bank();
        let bank = decode(&data, SAMPLES_NAME).expect("decode");
        assert_eq!(bank.voices.len(), 2);
        assert_eq!(layer_count(&bank), 2);
        assert_eq!(bank.velocity_curves.len(), 1);
        assert_eq!(bank.velocity_curves[0].segments[1].level, 0x15);
        assert_eq!(bank.voices[1].layers[0].start_note, 60);
        assert_eq!(bank.voices[1].layers[0].fine_tune, -1);
        assert_eq!(bank.voices[1].layers[0].source_address, 0x0004_0001);
        assert_eq!(bank.samples.size, 8);
        assert_eq!(bank.samples.offset, data.len() - 8);
    }

    #[test]
    fn encoding_a_decode_reproduces_the_bytes() {
        let data = one_bank();
        let bank = decode(&data, SAMPLES_NAME).expect("decode");
        let samples = &data[bank.samples.offset..];
        assert_eq!(encode(&bank, samples).expect("encode"), data);
    }

    #[test]
    fn a_voice_table_that_is_not_end_to_end_is_refused() {
        let mut data = one_bank();
        let second = read_u16(&data, HEADER_SIZE + 2).expect("offset") + 1;
        data[HEADER_SIZE + 2..HEADER_SIZE + 4].copy_from_slice(&second.to_be_bytes());
        let error = decode(&data, SAMPLES_NAME).expect_err("gap").to_string();
        assert!(error.contains("end to end"), "{error}");
    }

    #[test]
    fn a_voice_with_no_layers_is_refused() {
        let mut data = one_bank();
        let first = read_u16(&data, HEADER_SIZE).expect("offset") as usize;
        data[first + 2] = 0xFF; 
        assert!(decode(&data, SAMPLES_NAME).is_err());
    }

    #[test]
    fn samples_of_the_wrong_length_are_refused() {
        let data = one_bank();
        let bank = decode(&data, SAMPLES_NAME).expect("decode");
        assert!(encode(&bank, &[0xAA; 7]).is_err());
    }

    #[test]
    fn a_reserved_byte_that_is_set_still_round_trips() {
        let mut data = one_bank();
        let first = read_u16(&data, HEADER_SIZE).expect("offset") as usize;
        data[first + VOICE_HEADER_SIZE + 0x12] = 0x5A;
        let bank = decode(&data, SAMPLES_NAME).expect("decode");
        assert_eq!(bank.voices[0].layers[0].reserved_12, 0x5A00);
        let samples = data[bank.samples.offset..].to_vec();
        assert_eq!(encode(&bank, &samples).expect("encode"), data);
    }
}
