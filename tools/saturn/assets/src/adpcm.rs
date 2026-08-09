//!   3 saturn streaming audio formats
//!   stereo ADPCM  func_06013538  _convertDVI_STE   music, "DVI." container
//!   mono ADPCM    func_060133CC  _conve            SDF0.PCM, no container
//!   voice DPCM    --             SDD*/SDE*         8-bit signed differential

use crate::{Error, Result};

pub const MAGIC: &[u8; 4] = b"DVI.";
pub const SAMPLE_RATE: u32 = 44100;
pub const STEREO_HEADER_LEN: usize = 0x800;

/// src/saturn/zero/adpcm.c: IMA_ADPCM_ROW expanded
const STEP_TABLE: [i32; 89] = [
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31, 34, 37, 41, 45, 50, 55, 60, 66,
    73, 80, 88, 97, 107, 118, 130, 143, 157, 173, 190, 209, 230, 253, 279, 307, 337, 371, 408, 449,
    494, 544, 598, 658, 724, 796, 876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272,
    2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358, 5894, 6484, 7132, 7845, 8630, 9493,
    10442, 11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767,
];

/// g_AdpcmIndexAdjust 0x06043C08
const INDEX_ADJUST: [i32; 16] = [-1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8];

const MAX_SCALE: i32 = STEP_TABLE.len() as i32 - 1;

/// g_AdpcmDeltaTable 0x060425C8
fn delta_table() -> [[i32; 16]; 89] {
    let mut table = [[0i32; 16]; 89];
    for (row, &step) in table.iter_mut().zip(STEP_TABLE.iter()) {
        let positive = [
            step >> 3,
            (step >> 3) + (step >> 2),
            (step >> 3) + (step >> 1),
            (step >> 3) + (step >> 1) + (step >> 2),
            (step >> 3) + step,
            (step >> 3) + step + (step >> 2),
            (step >> 3) + step + (step >> 1),
            (step >> 3) + step + (step >> 1) + (step >> 2),
        ];
        for (i, &value) in positive.iter().enumerate() {
            row[i] = value;
            row[i + 8] = -value;
        }
    }
    table
}

fn clamp(value: i32, low: i32, high: i32) -> i32 {
    value.clamp(low, high)
}

#[derive(Default, Clone, Copy)]
struct ChannelState {
    scale: i32,
    accumulator: i32,
}

impl ChannelState {
    fn decode(&mut self, table: &[[i32; 16]; 89], nibble: usize) -> i16 {
        self.accumulator = clamp(
            self.accumulator + table[self.scale as usize][nibble],
            -0x8000,
            0x7FFF,
        );
        self.scale = clamp(self.scale + INDEX_ADJUST[nibble], 0, MAX_SCALE);
        self.accumulator as i16
    }

    fn encode(&mut self, table: &[[i32; 16]; 89], target: i32) -> usize {
        let row = &table[self.scale as usize];
        let mut best_nibble = 0;
        let mut best_error = i32::MAX;
        for (nibble, &delta) in row.iter().enumerate() {
            let landed = clamp(self.accumulator + delta, -0x8000, 0x7FFF);
            let error = (target - landed).abs();
            if error < best_error {
                best_error = error;
                best_nibble = nibble;
            }
        }
        self.decode(table, best_nibble);
        best_nibble
    }
}

/// handle loop points. have to use accumulator and step index
#[derive(Debug, Clone, Copy, Default, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub struct ChannelLoopState {
    /// accumulator
    pub predictor: i16,
    /// 0x7FFF on channel 0 and 0 on channel 1 in every example so far
    pub limit: i16,
    /// 0..88
    pub step: u8,
}

/// the "DVI." header
///
/// only the first 0x28 bytes are ever non-zero in all 49 retail files, and
/// every one of them is a field here, so the header can be rebuilt from the
/// json instead of kept as a blob. that's what makes the loop point editable.
#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub struct StereoHeader {
    /// start of the payload, 0x800 in every retail file
    pub headlen: usize,
    /// byte offset to resume from, none if it plays once (0xFFFFFFFF on disc)
    pub loop_point: Option<u32>,
    pub channels: [ChannelLoopState; 2],
}

const CHANNEL_BLOCK: [usize; 2] = [0x10, 0x20];

pub fn parse_stereo_header(data: &[u8]) -> Result<StereoHeader> {
    if data.len() < 0x28 || &data[0..4] != MAGIC {
        return Err(Error::Format(format!(
            "not a {:?} ADPCM stream",
            std::str::from_utf8(MAGIC).unwrap_or("DVI.")
        )));
    }
    let u32_at = |o: usize| u32::from_be_bytes([data[o], data[o + 1], data[o + 2], data[o + 3]]);
    let i16_at = |o: usize| i16::from_be_bytes([data[o], data[o + 1]]);

    let headlen = u32_at(4) as usize;
    if headlen > data.len() || headlen < 0x28 {
        return Err(Error::Format(format!(
            "header length {headlen} does not fit the {} byte file",
            data.len()
        )));
    }
    let loop_raw = u32_at(0x0C);
    let mut channels = [ChannelLoopState::default(); 2];
    for (channel, &base) in CHANNEL_BLOCK.iter().enumerate() {
        channels[channel] = ChannelLoopState {
            predictor: i16_at(base),
            limit: i16_at(base + 2),
            step: data[base + 7],
        };
        if channels[channel].step as i32 > MAX_SCALE {
            return Err(Error::Format(format!(
                "channel {channel} loop step {} is outside 0..={MAX_SCALE}",
                channels[channel].step
            )));
        }
    }
    Ok(StereoHeader {
        headlen,
        loop_point: (loop_raw != NO_LOOP).then_some(loop_raw),
        channels,
    })
}

/// no loop, at offset 0x0C
pub const NO_LOOP: u32 = 0xFFFF_FFFF;

impl StereoHeader {
    /// write the header back out. payload_len refreshes the length field,
    /// retail already agrees with it so an unedited rebuild is unchanged
    pub fn to_bytes(&self, payload_len: u32) -> Vec<u8> {
        let mut out = vec![0u8; self.headlen];
        out[0..4].copy_from_slice(MAGIC);
        out[4..8].copy_from_slice(&(self.headlen as u32).to_be_bytes());
        out[8..12].copy_from_slice(&payload_len.to_be_bytes());
        out[12..16].copy_from_slice(&self.loop_point.unwrap_or(NO_LOOP).to_be_bytes());
        for (channel, &base) in CHANNEL_BLOCK.iter().enumerate() {
            let state = &self.channels[channel];
            out[base..base + 2].copy_from_slice(&state.predictor.to_be_bytes());
            out[base + 2..base + 4].copy_from_slice(&state.limit.to_be_bytes());
            out[base + 7] = state.step;
        }
        out
    }
}

/// decode stereo, samples come back interleaved by channel
///
/// 8 byte blocks, bytes 0-3 channel 0, 4-7 channel 1, high nibble first.
/// a trailing partial block can't be decoded, caller keeps it
pub fn decode_stereo(payload: &[u8]) -> Vec<i16> {
    let table = delta_table();
    let mut states = [ChannelState::default(); 2];
    let blocks = payload.len() / 8;
    let mut out = Vec::with_capacity(blocks * 16);
    for block in 0..blocks {
        let base = block * 8;
        for step in 0..8 {
            for channel in 0..2 {
                let byte = payload[base + (channel << 2) + (step >> 1)];
                let nibble = if step % 2 == 0 {
                    (byte >> 4) & 0xF
                } else {
                    byte & 0xF
                };
                out.push(states[channel].decode(&table, nibble as usize));
            }
        }
    }
    out
}

pub fn encode_stereo(samples: &[i16]) -> Vec<u8> {
    let table = delta_table();
    let mut states = [ChannelState::default(); 2];
    let frames = (samples.len() + 1) / 2;
    let blocks = (frames + 7) / 8;
    let mut payload = vec![0u8; blocks * 8];
    let mut frame = 0usize;
    for block in 0..blocks {
        for step in 0..8 {
            for channel in 0..2 {
                let index = frame * 2 + channel;
                let target = samples.get(index).copied().unwrap_or(0) as i32;
                let nibble = states[channel].encode(&table, target) as u8;
                let position = block * 8 + (channel << 2) + (step >> 1);
                if step % 2 == 0 {
                    payload[position] |= nibble << 4;
                } else {
                    payload[position] |= nibble;
                }
            }
            frame += 1;
        }
    }
    payload
}

/// headerless mono, just walks the nibbles in order
pub fn decode_mono(payload: &[u8]) -> Vec<i16> {
    let table = delta_table();
    let mut state = ChannelState::default();
    let mut out = Vec::with_capacity(payload.len() * 2);
    for &byte in payload {
        out.push(state.decode(&table, ((byte >> 4) & 0xF) as usize));
        out.push(state.decode(&table, (byte & 0xF) as usize));
    }
    out
}

pub fn encode_mono(samples: &[i16]) -> Vec<u8> {
    let table = delta_table();
    let mut state = ChannelState::default();
    let nibbles: Vec<u8> = samples
        .iter()
        .map(|&s| state.encode(&table, s as i32) as u8)
        .collect();
    let mut payload = Vec::with_capacity((nibbles.len() + 1) / 2);
    for pair in nibbles.chunks(2) {
        payload.push(match pair {
            [high, low] => (high << 4) | low,
            [high] => high << 4,
            _ => unreachable!(),
        });
    }
    payload
}

/// 8-bit signed DPCM -> samples, clamped running sum of the deltas
pub fn decode_voice(data: &[u8]) -> Vec<i16> {
    let mut accumulator = 0i32;
    data.iter()
        .map(|&byte| {
            accumulator = clamp(accumulator + (byte as i8) as i32, -0x8000, 0x7FFF);
            accumulator as i16
        })
        .collect()
}

/// samples -> 8-bit signed DPCM, differences from a zero start
///
/// a delta too big for a signed byte can't be represented. step the
/// accumulator by the clamped delta so the encoder stays with the decoder,
/// unedited audio stays exact and a bad edit doesn't desync the rest
pub fn encode_voice(samples: &[i16]) -> Vec<u8> {
    let mut accumulator = 0i32;
    samples
        .iter()
        .map(|&value| {
            let delta = clamp(value as i32 - accumulator, -128, 127);
            accumulator = clamp(accumulator + delta, -0x8000, 0x7FFF);
            (delta as i8) as u8
        })
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_delta_table_is_antisymmetric() {
        let table = delta_table();
        for row in table.iter() {
            for nibble in 0..8 {
                assert_eq!(row[nibble], -row[nibble + 8]);
            }
        }
        // check the first row against the macro by hand, step 7
        assert_eq!(table[0][0], 0);
        assert_eq!(table[0][4], 7);
        assert_eq!(
            table[88][7],
            (32767 >> 3) + 32767 + (32767 >> 1) + (32767 >> 2)
        );
    }

    /// once a stream has been through the encoder, decode and re-encode has
    /// to give the same bytes back. this is what the round trip relies on.
    ///
    /// arbitrary nibbles do NOT survive, a stream can hold a nibble that
    /// isn't the closest choice for its target and the encoder always picks
    /// the closest. retail came out of an encoder so it's fine, see
    /// tests/retail_audio.rs
    fn assert_encoder_output_is_stable<D, E>(samples: &[i16], decode: D, encode: E)
    where
        D: Fn(&[u8]) -> Vec<i16>,
        E: Fn(&[i16]) -> Vec<u8>,
    {
        let encoded = encode(samples);
        assert_eq!(
            encode(&decode(&encoded)),
            encoded,
            "re-encoding changed the stream"
        );
    }

    fn ramp(count: usize) -> Vec<i16> {
        // slow slopes and sharp steps
        (0..count)
            .map(|i| {
                let t = i as f64 / 16.0;
                ((t.sin() * 12000.0) + ((i % 97) as f64 * 40.0)) as i16
            })
            .collect()
    }

    #[test]
    fn stereo_encoding_is_stable() {
        assert_encoder_output_is_stable(&ramp(1024), decode_stereo, encode_stereo);
    }

    #[test]
    fn mono_encoding_is_stable() {
        assert_encoder_output_is_stable(&ramp(1024), decode_mono, encode_mono);
    }

    #[test]
    fn voice_round_trips_arbitrary_bytes() {
        // voice is one to one on deltas so unlike adpcm every byte survives
        let payload: Vec<u8> = (0..1024).map(|i| (i * 29 + 17) as u8).collect();
        assert_eq!(encode_voice(&decode_voice(&payload)), payload);
    }

    #[test]
    fn stereo_channels_are_independent() {
        // channel 1 bytes only, channel 0 silent
        let mut payload = vec![0u8; 16];
        payload[4] = 0x40;
        let samples = decode_stereo(&payload);
        let left: Vec<i16> = samples.iter().step_by(2).copied().collect();
        assert!(left.iter().all(|&s| s == 0), "channel 0 leaked: {left:?}");
        assert!(samples.iter().skip(1).step_by(2).any(|&s| s != 0));
    }

    #[test]
    fn voice_deltas_integrate() {
        assert_eq!(decode_voice(&[1, 1, 1, 0xFF]), vec![1, 2, 3, 2]);
        assert_eq!(encode_voice(&[1, 2, 3, 2]), vec![1, 1, 1, 0xFF]);
    }

    #[test]
    fn a_non_dvi_stream_is_refused() {
        assert!(parse_stereo_header(b"RIFF").is_err(), "wrong magic");
        assert!(parse_stereo_header(&[0u8; 0x40]).is_err(), "no magic");
    }

    #[test]
    fn a_header_survives_parse_and_render() {
        let header = StereoHeader {
            headlen: 0x800,
            loop_point: Some(0x000E3000),
            channels: [
                ChannelLoopState {
                    predictor: -1570,
                    limit: 0x7FFF,
                    step: 47,
                },
                ChannelLoopState {
                    predictor: -2219,
                    limit: 0,
                    step: 35,
                },
            ],
        };
        let bytes = header.to_bytes(0x0057E800);
        assert_eq!(bytes.len(), 0x800);
        assert_eq!(&bytes[0..4], MAGIC);
        assert_eq!(parse_stereo_header(&bytes).unwrap(), header);
        // rest of the header stays zero
        assert!(bytes[0x28..].iter().all(|&b| b == 0));
    }

    #[test]
    fn a_stream_that_plays_once_has_no_loop_point() {
        let header = StereoHeader {
            headlen: 0x800,
            loop_point: None,
            channels: [ChannelLoopState::default(); 2],
        };
        let bytes = header.to_bytes(64);
        assert_eq!(&bytes[12..16], &NO_LOOP.to_be_bytes());
        assert_eq!(parse_stereo_header(&bytes).unwrap().loop_point, None);
    }

    #[test]
    fn an_impossible_loop_step_is_refused() {
        let mut bytes = StereoHeader {
            headlen: 0x800,
            loop_point: None,
            channels: [ChannelLoopState::default(); 2],
        }
        .to_bytes(64);
        bytes[0x17] = 89; // one past the step table
        assert!(parse_stereo_header(&bytes).is_err());
    }
}
