
use crate::seq::{Bank, Event, Song};
use crate::{Error, Result};
use std::path::{Path, PathBuf};

const OPERATION_LIMIT: usize = 1 << 20;

struct Message {
    tick: u64,
    order: usize,
    port: u8,
    bytes: Vec<u8>,
}

fn variable_length(value: u32, out: &mut Vec<u8>) {
    let mut buffer = [0u8; 4];
    let mut count = 0;
    let mut value = value;
    loop {
        buffer[count] = (value & 0x7F) as u8;
        count += 1;
        value >>= 7;
        if value == 0 {
            break;
        }
    }
    for index in (0..count).rev() {
        out.push(buffer[index] | if index == 0 { 0 } else { 0x80 });
    }
}

fn chunk(tag: &[u8; 4], body: &[u8], out: &mut Vec<u8>) {
    out.extend_from_slice(tag);
    out.extend_from_slice(&(body.len() as u32).to_be_bytes());
    out.extend_from_slice(body);
}

fn track(messages: &mut Vec<Message>) -> Vec<u8> {
    messages.sort_by_key(|message| (message.tick, message.order));
    let mut body = Vec::new();
    let mut previous = 0u64;
    for message in messages.iter() {
        variable_length((message.tick - previous) as u32, &mut body);
        body.extend_from_slice(&message.bytes);
        previous = message.tick;
    }
    variable_length(0, &mut body);
    body.extend_from_slice(&[0xFF, 0x2F, 0x00]);
    body
}

fn meta(kind: u8, payload: &[u8]) -> Vec<u8> {
    let mut bytes = vec![0xFF, kind];
    variable_length(payload.len() as u32, &mut bytes);
    bytes.extend_from_slice(payload);
    bytes
}

fn offsets(song: &Song) -> Result<Vec<usize>> {
    let mut out = Vec::with_capacity(song.events.len());
    let mut at = 0;
    for event in &song.events {
        out.push(at);
        at += crate::seq::encoded_size(event)?;
    }
    Ok(out)
}

fn play(song: &Song) -> Result<(Vec<Message>, Vec<Message>)> {
    let offsets = offsets(song)?;
    let mut events = Vec::new();
    let mut markers = Vec::new();
    let mut order = 0usize;
    let mut now = 0u64;
    let mut gate = 0u32;
    let mut delta = 0u32;
    let mut cursor = 0usize;
    let mut return_to = 0usize;
    let mut reference_count = 0u8;
    let mut loop_point: Option<usize> = None;

    let mut emit = |messages: &mut Vec<Message>, tick: u64, port: u8, bytes: Vec<u8>| {
        order += 1;
        messages.push(Message {
            tick,
            order,
            port,
            bytes,
        });
    };

    for _ in 0..OPERATION_LIMIT {
        let Some(event) = song.events.get(cursor) else {
            return Err(Error::Format(
                "the song runs off the end of its event list".to_string(),
            ));
        };
        cursor += 1;

        let (port, message, advance) = match *event {
            Event::GateAdd { value } => {
                gate += u32::from(value);
                continue;
            }
            Event::DeltaAdd { value } => {
                delta += u32::from(value);
                continue;
            }
            Event::Reference { target, count } => {
                if reference_count != 0 {
                    return Err(Error::Format(
                        "a referenced run contains a reference of its own, which the driver \
                         cannot nest"
                        .to_string(),
                    ));
                }
                let Some(index) = offsets.iter().position(|&at| at == usize::from(target)) else {
                    return Err(Error::Format(format!(
                        "a reference targets 0x{target:X}, which is not the start of an event"
                    )));
                };
                return_to = cursor;
                reference_count = count;
                cursor = index;
                continue;
            }
            Event::Loop { delta: step } => {
                delta += u32::from(step);
                match loop_point {
                    None => {
                        emit(&mut markers, now, 0, meta(0x06, b"loop start"));
                        loop_point = Some(cursor);
                    }
                    Some(_) => {
                        emit(&mut markers, now, 0, meta(0x06, b"loop end"));
                        break;
                    }
                }
                continue;
            }
            Event::End => break,
            Event::Note {
                channel,
                port,
                key,
                velocity,
                gate: own_gate,
                delta: own_delta,
            } => {
                let held = gate + u32::from(own_gate);
                emit(
                    &mut events,
                    now,
                    port,
                    vec![0x90 | channel, key, velocity.max(1)],
                );
                emit(
                    &mut events,
                    now + u64::from(held),
                    port,
                    vec![0x80 | channel, key, 0x40],
                );
                (port, None, delta + u32::from(own_delta))
            }
            Event::Aftertouch {
                channel,
                port,
                key,
                pressure,
                delta: own_delta,
            } => (
                port,
                Some(vec![0xA0 | channel, key, pressure]),
                delta + u32::from(own_delta),
            ),
            Event::Control {
                channel,
                port,
                controller,
                value,
                delta: own_delta,
            } => (
                port,
                Some(vec![0xB0 | channel, controller, value]),
                delta + u32::from(own_delta),
            ),
            Event::Program {
                channel,
                port,
                program,
                delta: own_delta,
            } => (
                port,
                Some(vec![0xC0 | channel, program]),
                delta + u32::from(own_delta),
            ),
            Event::Pressure {
                channel,
                port,
                pressure,
                delta: own_delta,
            } => (
                port,
                Some(vec![0xD0 | channel, pressure]),
                delta + u32::from(own_delta),
            ),
            Event::Bend {
                channel,
                value,
                delta: own_delta,
            } => (
                0,
                Some(vec![0xE0 | channel, 0x00, value & 0x7F]),
                delta + u32::from(own_delta),
            ),
        };

        if let Some(bytes) = message {
            emit(&mut events, now, port, bytes);
        }
        now += u64::from(advance);
        gate = 0;
        delta = 0;

        if reference_count != 0 {
            reference_count -= 1;
            if reference_count == 0 {
                cursor = return_to;
            }
        }
        continue;
    }

    Ok((events, markers))
}

pub fn song_to_smf(song: &Song) -> Result<Vec<u8>> {
    let (events, mut markers) = play(song)?;
    let tempo = song.tempo.last().ok_or_else(|| {
        Error::Format("a song with no tempo record has no tempo to export".to_string())
    })?;
    let microseconds = tempo.microseconds_per_quarter;
    if microseconds == 0 || microseconds > 0x00FF_FFFF {
        return Err(Error::Format(format!(
            "{microseconds} microseconds per quarter does not fit a MIDI tempo"
        )));
    }

    markers.push(Message {
        tick: 0,
        order: 0,
        port: 0,
        bytes: meta(0x51, &microseconds.to_be_bytes()[1..]),
    });
    let mut tracks = vec![track(&mut markers)];

    let mut ports: Vec<u8> = events.iter().map(|message| message.port).collect();
    ports.sort_unstable();
    ports.dedup();
    if ports.is_empty() {
        ports.push(0);
    }
    for port in ports {
        let mut on_port: Vec<Message> = events
            .iter()
            .filter(|message| message.port == port)
            .map(|message| Message {
                tick: message.tick,
                order: message.order,
                port,
                bytes: message.bytes.clone(),
            })
            .collect();
        let mut body = meta(0x03, format!("port {port}").as_bytes());
        body.insert(0, 0x00);
        body.extend_from_slice(&track(&mut on_port));
        tracks.push(body);
    }

    let mut out = Vec::new();
    let mut header = Vec::new();
    header.extend_from_slice(&1u16.to_be_bytes());
    header.extend_from_slice(&(tracks.len() as u16).to_be_bytes());
    header.extend_from_slice(&song.resolution.to_be_bytes());
    chunk(b"MThd", &header, &mut out);
    for body in &tracks {
        chunk(b"MTrk", body, &mut out);
    }
    Ok(out)
}

pub fn export_bank(bank: &Bank, output_dir: &Path, stem: &str) -> Result<Vec<PathBuf>> {
    std::fs::create_dir_all(output_dir)?;
    let width = bank.songs.len().to_string().len();
    let mut written = Vec::with_capacity(bank.songs.len());
    for (index, song) in bank.songs.iter().enumerate() {
        let smf = song_to_smf(song)
            .map_err(|e| Error::Format(format!("{stem} song {index}: {e}")))?;
        let path = output_dir.join(format!("{stem}_{index:0width$}.mid"));
        std::fs::write(&path, smf)?;
        written.push(path);
    }
    Ok(written)
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::seq::Tempo;

    fn song(events: Vec<Event>) -> Song {
        Song {
            resolution: 480,
            tempo: vec![Tempo {
                delta: 0,
                microseconds_per_quarter: 500_000,
            }],
            events,
            padding: 0,
        }
    }

    fn note(key: u8, gate: u16, delta: u16) -> Event {
        Event::Note {
            channel: 0,
            port: 0,
            key,
            velocity: 100,
            gate,
            delta,
        }
    }

    fn events_of(smf: &[u8], want: usize) -> Vec<(u32, Vec<u8>)> {
        let mut at = 14; 
        let mut track = 0;
        loop {
            let size = u32::from_be_bytes([smf[at + 4], smf[at + 5], smf[at + 6], smf[at + 7]])
                as usize;
            let body = &smf[at + 8..at + 8 + size];
            if track == want {
                let mut out = Vec::new();
                let mut cursor = 0;
                while cursor < body.len() {
                    let mut delta = 0u32;
                    loop {
                        let byte = body[cursor];
                        cursor += 1;
                        delta = delta << 7 | u32::from(byte & 0x7F);
                        if byte & 0x80 == 0 {
                            break;
                        }
                    }
                    let length = match body[cursor] {
                        0xFF => {
                            let payload = body[cursor + 2] as usize;
                            3 + payload
                        }
                        status if status & 0xF0 == 0xC0 || status & 0xF0 == 0xD0 => 2,
                        _ => 3,
                    };
                    out.push((delta, body[cursor..cursor + length].to_vec()));
                    cursor += length;
                }
                return out;
            }
            at += 8 + size;
            track += 1;
        }
    }

    #[test]
    fn a_note_becomes_an_on_and_an_off_a_gate_apart() {
        let smf = song_to_smf(&song(vec![note(60, 240, 480), Event::End])).expect("export");
        assert_eq!(&smf[..4], b"MThd");
        assert_eq!(&smf[8..14], &[0x00, 0x01, 0x00, 0x02, 0x01, 0xE0]);
        let events = events_of(&smf, 1);
        assert_eq!(events[1], (0, vec![0x90, 60, 100]));
        assert_eq!(events[2], (240, vec![0x80, 60, 0x40]));
    }

    #[test]
    fn the_accumulators_collapse_into_ordinary_ticks() {
        let smf = song_to_smf(&song(vec![
            Event::DeltaAdd { value: 0x100 },
            Event::GateAdd { value: 0x200 },
            note(60, 0x30, 0x18),
            note(62, 1, 1),
            Event::End,
        ]))
        .expect("export");
        let events = events_of(&smf, 1);
        assert_eq!(events[1], (0, vec![0x90, 60, 100]));
        assert_eq!(events[2], (0x118, vec![0x90, 62, 100]));
        assert_eq!(events[3], (1, vec![0x80, 62, 0x40]));
        assert_eq!(events[4], (0x230 - 0x119, vec![0x80, 60, 0x40]));
    }

    #[test]
    fn a_reference_expands_into_its_repeats() {
        let events = vec![note(60, 10, 10), note(62, 10, 10), Event::End];
        let mut with_reference = events.clone();
        with_reference.pop();
        with_reference.push(Event::Reference { target: 0, count: 2 });
        with_reference.push(Event::End);

        let smf = song_to_smf(&song(with_reference)).expect("export");
        let ons: Vec<u8> = events_of(&smf, 1)
            .into_iter()
            .filter(|(_, bytes)| bytes[0] == 0x90)
            .map(|(_, bytes)| bytes[1])
            .collect();
        assert_eq!(ons, vec![60, 62, 60, 62]);
    }

    #[test]
    fn the_second_loop_marker_ends_the_file_instead_of_looping_forever() {
        let smf = song_to_smf(&song(vec![
            Event::Loop { delta: 0 },
            note(60, 10, 10),
            Event::Loop { delta: 0 },
            Event::End,
        ]))
        .expect("export");
        let markers: Vec<Vec<u8>> = events_of(&smf, 0)
            .into_iter()
            .filter(|(_, bytes)| bytes.starts_with(&[0xFF, 0x06]))
            .map(|(_, bytes)| bytes[3..].to_vec())
            .collect();
        assert_eq!(markers.len(), 2);
        assert_eq!(markers[0], b"loop start");
        assert_eq!(markers[1], b"loop end");
        let ons = events_of(&smf, 1)
            .into_iter()
            .filter(|(_, bytes)| bytes[0] == 0x90)
            .count();
        assert_eq!(ons, 1);
    }

    #[test]
    fn a_bend_lands_in_the_high_seven_bits() {
        let smf = song_to_smf(&song(vec![
            Event::Bend {
                channel: 2,
                value: 0x40,
                delta: 0,
            },
            Event::End,
        ]))
        .expect("export");
        assert!(events_of(&smf, 1)
            .iter()
            .any(|(_, bytes)| bytes == &[0xE2, 0x00, 0x40]));
    }

    #[test]
    fn a_reference_to_the_middle_of_an_event_is_refused() {
        let error = song_to_smf(&song(vec![
            note(60, 10, 10),
            Event::Reference { target: 2, count: 1 },
            Event::End,
        ]))
        .expect_err("misaligned reference")
        .to_string();
        assert!(error.contains("start of an event"), "{error}");
    }

    #[test]
    fn a_port_that_is_used_gets_its_own_track() {
        let smf = song_to_smf(&song(vec![
            note(60, 10, 10),
            Event::Control {
                channel: 0,
                port: 1,
                controller: 7,
                value: 100,
                delta: 0,
            },
            Event::End,
        ]))
        .expect("export");
        assert_eq!(smf[11], 3, "a tempo track and one per port");
    }
}
