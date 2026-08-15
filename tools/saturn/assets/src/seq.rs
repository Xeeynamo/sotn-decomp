
use crate::{Error, Result};
use serde::{Deserialize, Serialize};
use std::path::Path;

pub const FORMAT: &str = "sotn-saturn-sequence-bank";
pub const VERSION: u32 = 1;

const MIN_RESOLUTION: u16 = 24;
const MAX_RESOLUTION: u16 = 960;

const NOTE_MAX: u16 = 0x1FF;

const GATE_ADDENDS: [u16; 4] = [0x200, 0x800, 0x1000, 0x2000];
const DELTA_ADDENDS: [u16; 4] = [0x100, 0x200, 0x800, 0x1000];

#[derive(Debug, Clone, PartialEq, Eq, Serialize, Deserialize)]
#[serde(tag = "op", rename_all = "snake_case")]
pub enum Event {
    Note {
        channel: u8,
        port: u8,
        key: u8,
        velocity: u8,
        gate: u16,
        delta: u16,
    },
    Reference { target: u16, count: u8 },
    Loop { delta: u8 },
    End,
    GateAdd { value: u16 },
    DeltaAdd { value: u16 },
    Aftertouch {
        channel: u8,
        port: u8,
        key: u8,
        pressure: u8,
        delta: u8,
    },
    Control {
        channel: u8,
        port: u8,
        controller: u8,
        value: u8,
        delta: u8,
    },
    Program {
        channel: u8,
        port: u8,
        program: u8,
        delta: u8,
    },
    Pressure {
        channel: u8,
        port: u8,
        pressure: u8,
        delta: u8,
    },
    Bend { channel: u8, value: u8, delta: u8 },
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
pub struct Tempo {
    pub delta: u32,
    pub microseconds_per_quarter: u32,
}

#[derive(Debug, Clone, PartialEq, Eq, Serialize, Deserialize)]
pub struct Song {
    pub resolution: u16,
    pub tempo: Vec<Tempo>,
    pub events: Vec<Event>,
    #[serde(default, skip_serializing_if = "is_zero_usize")]
    pub padding: usize,
}

#[derive(Debug, Clone, PartialEq, Eq, Serialize, Deserialize)]
pub struct Bank {
    pub format: String,
    pub version: u32,
    pub size: usize,
    pub songs: Vec<Song>,
}

fn is_zero_usize(value: &usize) -> bool {
    *value == 0
}

fn read_u16(data: &[u8], at: usize) -> Result<u16> {
    data.get(at..at + 2)
        .map(|b| u16::from_be_bytes([b[0], b[1]]))
        .ok_or_else(|| Error::Format(format!("sequence bank is truncated at 0x{at:X}")))
}

fn read_u32(data: &[u8], at: usize) -> Result<u32> {
    data.get(at..at + 4)
        .map(|b| u32::from_be_bytes([b[0], b[1], b[2], b[3]]))
        .ok_or_else(|| Error::Format(format!("sequence bank is truncated at 0x{at:X}")))
}

fn track_offset(tracks: usize) -> usize {
    8 + tracks * 8
}

fn tempo_offset(tracks: usize) -> usize {
    8 + (tracks - 1) * 8
}

pub fn decode(data: &[u8]) -> Result<Bank> {
    let count = read_u16(data, 0)? as usize;
    if count == 0 {
        if data.iter().any(|&b| b != 0) {
            return Err(Error::Format(
                "sequence bank declares no songs but is not empty".to_string(),
            ));
        }
        return Ok(Bank {
            format: FORMAT.to_string(),
            version: VERSION,
            size: data.len(),
            songs: Vec::new(),
        });
    }

    let table_end = 2 + count * 4;
    let mut offsets = Vec::with_capacity(count);
    for index in 0..count {
        offsets.push(read_u32(data, 2 + index * 4)? as usize);
    }
    if offsets[0] != table_end {
        return Err(Error::Format(format!(
            "the first song starts at 0x{:X}, not directly after the {count}-song table at 0x{table_end:X}",
            offsets[0]
        )));
    }
    for pair in offsets.windows(2) {
        if pair[1] < pair[0] {
            return Err(Error::Format(
                "the song table is not in ascending offset order".to_string(),
            ));
        }
    }

    let mut songs = Vec::with_capacity(count);
    for (index, &start) in offsets.iter().enumerate() {
        let end = offsets.get(index + 1).copied().unwrap_or(data.len());
        let song = data
            .get(start..end)
            .ok_or_else(|| Error::Format(format!("song {index} lies outside the bank")))?;
        songs.push(decode_song(song, index)?);
    }

    Ok(Bank {
        format: FORMAT.to_string(),
        version: VERSION,
        size: data.len(),
        songs,
    })
}

fn decode_song(song: &[u8], index: usize) -> Result<Song> {
    let resolution = read_u16(song, 0)?;
    let tracks = read_u16(song, 2)? as usize;
    let declared_track = read_u16(song, 4)? as usize;
    let declared_tempo = read_u16(song, 6)? as usize;
    if !(MIN_RESOLUTION..=MAX_RESOLUTION).contains(&resolution) {
        return Err(Error::Format(format!(
            "song {index} has resolution {resolution}, outside the driver's {MIN_RESOLUTION}..{MAX_RESOLUTION}"
        )));
    }
    if tracks == 0 {
        return Err(Error::Format(format!("song {index} declares no tracks")));
    }
    if declared_track != track_offset(tracks) || declared_tempo != tempo_offset(tracks) {
        return Err(Error::Format(format!(
            "song {index} declares {tracks} tracks with its track at 0x{declared_track:X} and \
             tempo at 0x{declared_tempo:X}; every song on the disc puts them at 0x{:X} and 0x{:X}",
            track_offset(tracks),
            tempo_offset(tracks)
        )));
    }

    let mut tempo = Vec::with_capacity(tracks);
    for track in 0..tracks {
        let at = 8 + track * 8;
        tempo.push(Tempo {
            delta: read_u32(song, at)?,
            microseconds_per_quarter: read_u32(song, at + 4)?,
        });
    }

    let (events, track_end) = decode_track(song, declared_track, index)?;
    let padding = song.len() - track_end;
    if song[track_end..].iter().any(|&b| b != 0) {
        return Err(Error::Format(format!(
            "song {index} has {padding} bytes after its track and they are not all zero"
        )));
    }

    Ok(Song {
        resolution,
        tempo,
        events,
        padding,
    })
}

fn decode_track(song: &[u8], start: usize, index: usize) -> Result<(Vec<Event>, usize)> {
    let mut events = Vec::new();
    let mut at = start;
    loop {
        let opcode = *song
            .get(at)
            .ok_or_else(|| Error::Format(format!("song {index}'s track has no end marker")))?;
        at += 1;
        let event = match opcode {
            0x00..=0x7F => {
                let operands = song.get(at..at + 4).ok_or_else(|| {
                    Error::Format(format!("song {index} has a truncated note event"))
                })?;
                at += 4;
                Event::Note {
                    channel: opcode & 0x0F,
                    port: opcode >> 4 & 1,
                    key: operands[0],
                    velocity: operands[1],
                    gate: u16::from(operands[2]) | if opcode & 0x40 != 0 { 0x100 } else { 0 },
                    delta: u16::from(operands[3]) | if opcode & 0x20 != 0 { 0x100 } else { 0 },
                }
            }
            0x81 => {
                let target = read_u16(song, at)?;
                let count = *song.get(at + 2).ok_or_else(|| {
                    Error::Format(format!("song {index} has a truncated reference event"))
                })?;
                at += 3;
                if count == 0 {
                    return Err(Error::Format(format!(
                        "song {index} references a run of no events"
                    )));
                }
                Event::Reference { target, count }
            }
            0x82 => {
                let delta = *song.get(at).ok_or_else(|| {
                    Error::Format(format!("song {index} has a truncated loop event"))
                })?;
                at += 1;
                Event::Loop { delta }
            }
            0x83 => {
                events.push(Event::End);
                return Ok((events, at));
            }
            0x88..=0x8B => Event::GateAdd {
                value: GATE_ADDENDS[(opcode - 0x88) as usize],
            },
            0x8C..=0x8F => Event::DeltaAdd {
                value: DELTA_ADDENDS[(opcode - 0x8C) as usize],
            },
            0xA0..=0xEF => {
                let channel = opcode & 0x0F;
                let kind = opcode & 0xF0;
                let operands = 1 + usize::from(matches!(kind, 0xA0 | 0xB0));
                let bytes = song.get(at..at + operands + 1).ok_or_else(|| {
                    Error::Format(format!("song {index} has a truncated MIDI event"))
                })?;
                at += operands + 1;
                let delta = bytes[operands];
                let port = bytes[0] >> 7;
                let data1 = bytes[0] & 0x7F;
                match kind {
                    0xA0 => Event::Aftertouch {
                        channel,
                        port,
                        key: data1,
                        pressure: bytes[1],
                        delta,
                    },
                    0xB0 => Event::Control {
                        channel,
                        port,
                        controller: data1,
                        value: bytes[1],
                        delta,
                    },
                    0xC0 => Event::Program {
                        channel,
                        port,
                        program: data1,
                        delta,
                    },
                    0xD0 => Event::Pressure {
                        channel,
                        port,
                        pressure: data1,
                        delta,
                    },
                    _ => Event::Bend {
                        channel,
                        value: bytes[0],
                        delta,
                    },
                }
            }
            _ => {
                return Err(Error::Format(format!(
                    "song {index} uses opcode 0x{opcode:02X} at 0x{:X}, which no song on the \
                     retail disc uses and this decoder does not know",
                    at - 1
                )))
            }
        };
        events.push(event);
    }
}

fn addend(value: u16, addends: [u16; 4], base: u8, what: &str) -> Result<u8> {
    addends
        .iter()
        .position(|&a| a == value)
        .map(|i| base + i as u8)
        .ok_or_else(|| {
            Error::Format(format!(
                "no opcode adds 0x{value:X} to the {what}; the encodable values are {addends:X?}"
            ))
        })
}

fn field(value: u8, limit: u8, what: &str) -> Result<u8> {
    if value > limit {
        return Err(Error::Format(format!(
            "{what} is {value}, which does not fit in the {limit:#X} the format allows"
        )));
    }
    Ok(value)
}

fn encode_event(event: &Event, out: &mut Vec<u8>) -> Result<()> {
    match *event {
        Event::Note {
            channel,
            port,
            key,
            velocity,
            gate,
            delta,
        } => {
            field(channel, 0x0F, "a note's channel")?;
            field(port, 1, "a note's port")?;
            field(key, 0x7F, "a note's key")?;
            field(velocity, 0x7F, "a note's velocity")?;
            if gate > NOTE_MAX || delta > NOTE_MAX {
                return Err(Error::Format(format!(
                    "a note event carries gate {gate} and delta {delta}; a note encodes at most \
                     {NOTE_MAX} of each, and the rest belongs in gate_add and delta_add events"
                )));
            }
            out.push(
                channel
                    | port << 4
                    | if delta & 0x100 != 0 { 0x20 } else { 0 }
                    | if gate & 0x100 != 0 { 0x40 } else { 0 },
            );
            out.extend_from_slice(&[key, velocity, gate as u8, delta as u8]);
        }
        Event::Reference { target, count } => {
            if count == 0 {
                return Err(Error::Format(
                    "a reference to a run of no events cannot be encoded".to_string(),
                ));
            }
            out.push(0x81);
            out.extend_from_slice(&target.to_be_bytes());
            out.push(count);
        }
        Event::Loop { delta } => out.extend_from_slice(&[0x82, delta]),
        Event::End => out.push(0x83),
        Event::GateAdd { value } => out.push(addend(value, GATE_ADDENDS, 0x88, "gate")?),
        Event::DeltaAdd { value } => out.push(addend(value, DELTA_ADDENDS, 0x8C, "delta")?),
        Event::Aftertouch {
            channel,
            port,
            key,
            pressure,
            delta,
        } => encode_midi(out, 0xA0, channel, port, key, Some(pressure), delta)?,
        Event::Control {
            channel,
            port,
            controller,
            value,
            delta,
        } => encode_midi(out, 0xB0, channel, port, controller, Some(value), delta)?,
        Event::Program {
            channel,
            port,
            program,
            delta,
        } => encode_midi(out, 0xC0, channel, port, program, None, delta)?,
        Event::Pressure {
            channel,
            port,
            pressure,
            delta,
        } => encode_midi(out, 0xD0, channel, port, pressure, None, delta)?,
        Event::Bend {
            channel,
            value,
            delta,
        } => {
            field(channel, 0x0F, "a pitch bend's channel")?;
            out.extend_from_slice(&[0xE0 | channel, value, delta]);
        }
    }
    Ok(())
}

fn encode_midi(
    out: &mut Vec<u8>,
    kind: u8,
    channel: u8,
    port: u8,
    data1: u8,
    data2: Option<u8>,
    delta: u8,
) -> Result<()> {
    field(channel, 0x0F, "a MIDI event's channel")?;
    field(port, 1, "a MIDI event's port")?;
    field(data1, 0x7F, "a MIDI event's first data byte")?;
    out.push(kind | channel);
    out.push(data1 | port << 7);
    if let Some(data2) = data2 {
        out.push(field(data2, 0x7F, "a MIDI event's second data byte")?);
    }
    out.push(delta);
    Ok(())
}

pub fn encode(bank: &Bank) -> Result<Vec<u8>> {
    if bank.format != FORMAT || bank.version != VERSION {
        return Err(Error::Format(format!(
            "not a {FORMAT} v{VERSION} bank"
        )));
    }
    if bank.songs.is_empty() {
        return Ok(vec![0; bank.size]);
    }
    if bank.songs.len() > u16::MAX as usize {
        return Err(Error::Format(format!(
            "a sequence bank holds at most {} songs, not {}",
            u16::MAX,
            bank.songs.len()
        )));
    }

    let mut bodies = Vec::with_capacity(bank.songs.len());
    for (index, song) in bank.songs.iter().enumerate() {
        bodies.push(encode_song(song, index)?);
    }

    let mut out = Vec::with_capacity(bank.size);
    out.extend_from_slice(&(bank.songs.len() as u16).to_be_bytes());
    let mut offset = 2 + bank.songs.len() * 4;
    for body in &bodies {
        let Ok(offset32) = u32::try_from(offset) else {
            return Err(Error::Format(
                "a sequence bank grew past the 32-bit song offsets".to_string(),
            ));
        };
        out.extend_from_slice(&offset32.to_be_bytes());
        offset += body.len();
    }
    for body in &bodies {
        out.extend_from_slice(body);
    }
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

fn encode_song(song: &Song, index: usize) -> Result<Vec<u8>> {
    if !(MIN_RESOLUTION..=MAX_RESOLUTION).contains(&song.resolution) {
        return Err(Error::Format(format!(
            "song {index} has resolution {}, outside the driver's {MIN_RESOLUTION}..{MAX_RESOLUTION}",
            song.resolution
        )));
    }
    if song.tempo.is_empty() {
        return Err(Error::Format(format!(
            "song {index} has no tempo record, so it declares no tracks"
        )));
    }
    if !matches!(song.events.last(), Some(Event::End)) {
        return Err(Error::Format(format!(
            "song {index} does not end with an end event"
        )));
    }
    if song.events[..song.events.len() - 1]
        .iter()
        .any(|event| matches!(event, Event::End))
    {
        return Err(Error::Format(format!(
            "song {index} has an end event before its last"
        )));
    }

    let tracks = song.tempo.len();
    let Ok(tracks16) = u16::try_from(tracks) else {
        return Err(Error::Format(format!("song {index} declares too many tracks")));
    };
    let mut out = Vec::new();
    out.extend_from_slice(&song.resolution.to_be_bytes());
    out.extend_from_slice(&tracks16.to_be_bytes());
    out.extend_from_slice(&(track_offset(tracks) as u16).to_be_bytes());
    out.extend_from_slice(&(tempo_offset(tracks) as u16).to_be_bytes());
    for tempo in &song.tempo {
        out.extend_from_slice(&tempo.delta.to_be_bytes());
        out.extend_from_slice(&tempo.microseconds_per_quarter.to_be_bytes());
    }
    for event in &song.events {
        encode_event(event, &mut out).map_err(|e| Error::Format(format!("song {index}: {e}")))?;
    }
    out.resize(out.len() + song.padding, 0);
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

pub fn write(bank: &Bank, path: &Path) -> Result<()> {
    if let Some(parent) = path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    let mut json = serde_json::to_string_pretty(bank)?;
    json.push('\n');
    std::fs::write(path, json)?;
    Ok(())
}

pub fn event_count(bank: &Bank) -> usize {
    bank.songs.iter().map(|song| song.events.len()).sum()
}

pub fn encoded_size(event: &Event) -> Result<usize> {
    let mut out = Vec::with_capacity(5);
    encode_event(event, &mut out)?;
    Ok(out.len())
}

#[cfg(test)]
mod tests {
    use super::*;

    fn one_song() -> Vec<u8> {
        let mut track = vec![
            0xC0, 0x05, 0x00, 
            0x8C, 
            0x40, 0x3C, 0x64, 0x30, 0x18, 
            0x83,
        ];
        let mut song = vec![
            0x01, 0xE0, 
            0x00, 0x01, 
            0x00, 0x10, 
            0x00, 0x08, 
        ];
        song.extend_from_slice(&0u32.to_be_bytes());
        song.extend_from_slice(&500_000u32.to_be_bytes());
        song.append(&mut track);
        let mut bank = vec![0x00, 0x01];
        bank.extend_from_slice(&6u32.to_be_bytes());
        bank.append(&mut song);
        bank
    }

    #[test]
    fn a_song_decodes_to_the_opcodes_the_encoder_chose() {
        let bank = decode(&one_song()).expect("decode");
        assert_eq!(bank.size, one_song().len());
        let song = &bank.songs[0];
        assert_eq!(song.resolution, 480);
        assert_eq!(
            song.tempo,
            vec![Tempo {
                delta: 0,
                microseconds_per_quarter: 500_000
            }]
        );
        assert_eq!(
            song.events,
            vec![
                Event::Program {
                    channel: 0,
                    port: 0,
                    program: 5,
                    delta: 0
                },
                Event::DeltaAdd { value: 0x100 },
                Event::Note {
                    channel: 0,
                    port: 0,
                    key: 0x3C,
                    velocity: 0x64,
                    gate: 0x130,
                    delta: 0x18,
                },
                Event::End,
            ]
        );
    }

    #[test]
    fn encoding_a_decode_reproduces_the_bytes() {
        let data = one_song();
        assert_eq!(encode(&decode(&data).expect("decode")).expect("encode"), data);
    }

    #[test]
    fn a_bank_of_no_songs_is_an_empty_area() {
        let bank = decode(&[0u8; 2048]).expect("decode");
        assert!(bank.songs.is_empty());
        assert_eq!(encode(&bank).expect("encode"), vec![0u8; 2048]);
    }

    #[test]
    fn a_zero_count_over_real_data_is_refused() {
        let mut data = vec![0u8; 64];
        data[10] = 1;
        assert!(decode(&data).is_err());
    }

    #[test]
    fn an_unknown_opcode_is_refused_rather_than_skipped() {
        let mut data = one_song();
        let at = data.iter().position(|&b| b == 0xC0).expect("program change");
        data[at] = 0x84;
        let error = decode(&data).expect_err("unknown opcode").to_string();
        assert!(error.contains("0x84"), "{error}");
    }

    #[test]
    fn a_track_with_no_terminator_is_refused() {
        let mut data = one_song();
        let at = data.len() - 1;
        data[at] = 0x88;
        assert!(decode(&data).is_err());
    }

    #[test]
    fn padding_that_is_not_zero_is_refused() {
        let mut data = one_song();
        data.push(0x01);
        assert!(decode(&data).is_err());
        let at = data.len() - 1;
        data[at] = 0;
        let bank = decode(&data).expect("decode");
        assert_eq!(bank.songs[0].padding, 1);
        assert_eq!(encode(&bank).expect("encode"), data);
    }

    #[test]
    fn a_song_header_the_driver_would_not_read_is_refused() {
        let mut data = one_song();
        data[8] = 0x00;
        data[9] = 0x02;
        let error = decode(&data).expect_err("mismatched header").to_string();
        assert!(error.contains("tracks"), "{error}");
    }

    #[test]
    fn a_gate_too_large_for_a_note_is_refused_rather_than_truncated() {
        let mut bank = decode(&one_song()).expect("decode");
        let Event::Note { gate, .. } = &mut bank.songs[0].events[2] else {
            panic!("expected a note");
        };
        *gate = 0x200;
        let error = encode(&bank).expect_err("oversized gate").to_string();
        assert!(error.contains("gate_add"), "{error}");
    }

    #[test]
    fn a_bank_that_changed_size_is_refused() {
        let mut bank = decode(&one_song()).expect("decode");
        bank.songs[0].padding += 4;
        let error = encode(&bank).expect_err("resized bank").to_string();
        assert!(error.contains("area map"), "{error}");
    }
}
