// SPDX-License-Identifier: AGPL-3.0-or-later
use std::{env, fs, path::Path};

const VB_SLOT_SIZE: usize = 0xE190;
const VH_SIZE: usize = 0x1020;
// original rate is 8k which fits in the psx vab
const TARGET_RATE: u32 = 8_000;
const VAB_CENTER_NOTE: u8 = 90;
const VAB_PITCH_SHIFT: u8 = 64;
const VOICE_FIRST: usize = 10;
const VOICE_COUNT: usize = 16;
// lookup table for sd_mar2 and SsUtKeyOnV D_psp_089640DC
const MAR2_KEYS: [(u8, u8); 26] = [
    (0, 0),
    (0, 1),
    (0, 2),
    (0, 3),
    (0, 4),
    (0, 5),
    (0, 6),
    (0, 7),
    (0, 8),
    (0, 9),
    (1, 0),
    (1, 2),
    (1, 4),
    (1, 6),
    (1, 8),
    (1, 10),
    (1, 12),
    (1, 14),
    (2, 0),
    (2, 2),
    (2, 4),
    (2, 6),
    (2, 8),
    (2, 10),
    (2, 12),
    (2, 14),
];
// maria IDs 0x8E6..0x8F5 map to sd_mar2 10..25
const SFX_VAG_MAP: [u16; VOICE_COUNT] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16];
const VOICE_NAMES: [&str; VOICE_COUNT] = [
    "MARY2A", "MARY2B", "MARY2C", "MARY2D", "MARY2E", "MARY2F", "MARY2G", "MARY2Q", "MARY2P",
    "MARY2N", "MARY2O", "MARY2M", "MARY2R", "MARY2T", "MARY2V", "MARY2W",
];

#[derive(Clone)]
struct Sample {
    name: String,
    rate: u32,
    adpcm: Vec<u8>,
}

fn le16(d: &[u8], o: usize) -> Result<u16, String> {
    let b = d.get(o..o + 2).ok_or("truncated u16")?;
    Ok(u16::from_le_bytes([b[0], b[1]]))
}
fn le32(d: &[u8], o: usize) -> Result<u32, String> {
    let b = d.get(o..o + 4).ok_or("truncated u32")?;
    Ok(u32::from_le_bytes([b[0], b[1], b[2], b[3]]))
}
fn be32(d: &[u8], o: usize) -> Result<u32, String> {
    let b = d.get(o..o + 4).ok_or("truncated u32")?;
    Ok(u32::from_be_bytes([b[0], b[1], b[2], b[3]]))
}
fn put16(d: &mut [u8], o: usize, v: u16) {
    d[o..o + 2].copy_from_slice(&v.to_le_bytes());
}
fn put32(d: &mut [u8], o: usize, v: u32) {
    d[o..o + 4].copy_from_slice(&v.to_le_bytes());
}

fn reversed_text(d: &[u8]) -> String {
    let mut b = d.to_vec();
    b.reverse();
    String::from_utf8_lossy(&b).trim_matches('\0').to_string()
}

fn sepk_offsets(res: &[u8]) -> Result<Vec<(u32, usize, usize)>, String> {
    if res.get(..4) != Some(b"RESC") {
        return Err("not a RESC file".into());
    }
    let count = le32(res, 4)? as usize;
    let mut out = Vec::new();
    for i in 0..count {
        let o = 0x10 + i * 0x20;
        let desc = res.get(o..o + 0x20).ok_or("truncated RESC directory")?;
        if reversed_text(&desc[8..12]) == "spk" {
            let size = le32(desc, 12)? as usize;
            let offset = le32(desc, 16)? as usize;
            let variant = le32(desc, 20)?;
            if res.get(offset..offset + size).is_none() {
                return Err("SEPK outside RESC".into());
            }
            out.push((variant, offset, size));
        }
    }
    if out.is_empty() {
        Err("RESC has no spk entries".into())
    } else {
        Ok(out)
    }
}

fn parse_sepk(res: &[u8], base: usize, size: usize) -> Result<Vec<Sample>, String> {
    let sepk = res.get(base..base + size).ok_or("truncated SEPK")?;
    if !matches!(sepk.get(..8), Some(b"SEPK1.20") | Some(b"SEPK1.30")) {
        return Err("unsupported SEPK magic".into());
    }
    let count = le32(sepk, 8)? as usize;
    let mut out = Vec::new();
    for i in 0..count {
        let d = 0x20 + i * 0x20;
        let vag_off = le32(sepk, d)? as usize;
        let vag = sepk.get(vag_off..).ok_or("VAG offset outside SEPK")?;
        if vag.get(..4) != Some(b"VAGp") {
            return Err(format!("sample {i}: missing VAGp"));
        }
        let data_size = be32(vag, 0x0c)? as usize;
        let rate = be32(vag, 0x10)?;
        let adpcm = vag
            .get(0x30..0x30 + data_size)
            .ok_or("truncated VAG payload")?
            .to_vec();
        let raw_name = vag.get(0x20..0x30).ok_or("truncated VAG name")?;
        let name = String::from_utf8_lossy(raw_name)
            .trim_matches('\0')
            .to_string();
        out.push(Sample { name, rate, adpcm });
    }
    Ok(out)
}

fn decode_adpcm(data: &[u8]) -> Result<Vec<i16>, String> {
    if data.len() % 16 != 0 {
        return Err("ADPCM payload is not block aligned".into());
    }
    let filters: [(i32, i32); 5] = [(0, 0), (60, 0), (115, -52), (98, -55), (122, -60)];
    let (mut h1, mut h2) = (0i32, 0i32);
    let mut pcm = Vec::with_capacity(data.len() / 16 * 28);
    for block in data.chunks_exact(16) {
        let filter = (block[0] >> 4) as usize;
        let shift = (block[0] & 15) as i32;
        if filter >= filters.len() || shift > 12 {
            return Err("invalid ADPCM block header".into());
        }
        let scale = 1i32 << (12 - shift);
        for i in 0..28 {
            let n = if i & 1 == 0 {
                block[2 + i / 2] & 15
            } else {
                block[2 + i / 2] >> 4
            };
            let q = if n & 8 != 0 { n as i32 - 16 } else { n as i32 };
            let pred = ((h1 * filters[filter].0) >> 6) + ((h2 * filters[filter].1) >> 6);
            let s = (q * scale + pred).clamp(-32768, 32767);
            pcm.push(s as i16);
            h2 = h1;
            h1 = s;
        }
        // there may be a block of 0x07/0x77 aterwards so we stop at the end flag
        if block[1] & 1 != 0 {
            break;
        }
    }
    Ok(pcm)
}

fn resample_linear(input: &[i16], source_rate: u32, target_rate: u32) -> Vec<i16> {
    if input.is_empty() || source_rate == target_rate {
        return input.to_vec();
    }
    let len = ((input.len() as u64 * target_rate as u64 + source_rate as u64 / 2)
        / source_rate as u64) as usize;
    let mut out = Vec::with_capacity(len);
    for i in 0..len {
        let pos_num = i as u64 * source_rate as u64;
        let a = (pos_num / target_rate as u64) as usize;
        let frac = (pos_num % target_rate as u64) as i64;
        let x = input[a.min(input.len() - 1)] as i64;
        let y = input[(a + 1).min(input.len() - 1)] as i64;
        out.push(
            (x + ((y - x) * frac + target_rate as i64 / 2) / target_rate as i64)
                .clamp(-32768, 32767) as i16,
        );
    }
    out
}

fn trim_silence(input: &[i16], rate: u32) -> &[i16] {
    const THRESHOLD: i16 = 64;
    let margin = (rate / 50) as usize; // preserve 20 ms around audible material
    let first = input.iter().position(|x| x.abs() > THRESHOLD).unwrap_or(0);
    let last = input
        .iter()
        .rposition(|x| x.abs() > THRESHOLD)
        .map(|x| x + 1)
        .unwrap_or(input.len());
    let start = first.saturating_sub(margin);
    let end = (last + margin).min(input.len());
    &input[start..end.max(start)]
}

fn div_round(n: i32, d: i32) -> i32 {
    if n >= 0 {
        (n + d / 2) / d
    } else {
        (n - d / 2) / d
    }
}

fn encode_adpcm(pcm: &[i16]) -> Vec<u8> {
    let filters: [(i32, i32); 5] = [(0, 0), (60, 0), (115, -52), (98, -55), (122, -60)];
    let blocks = pcm.len().div_ceil(28).max(1);
    let mut out = Vec::with_capacity(blocks * 16);
    let (mut history1, mut history2) = (0i32, 0i32);
    for bi in 0..blocks {
        let mut source = [0i16; 28];
        let start = bi * 28;
        let take = (pcm.len().saturating_sub(start)).min(28);
        source[..take].copy_from_slice(&pcm[start..start + take]);
        let mut best = (u64::MAX, 0usize, 0i32, [0i8; 28], history1, history2);
        for (fi, &(f0, f1)) in filters.iter().enumerate() {
            for shift in 0..=12 {
                let scale = 1i32 << (12 - shift);
                let (mut h1, mut h2, mut err) = (history1, history2, 0u64);
                let mut qs = [0i8; 28];
                for (j, &sample) in source.iter().enumerate() {
                    let pred = ((h1 * f0) >> 6) + ((h2 * f1) >> 6);
                    let q = div_round(sample as i32 - pred, scale).clamp(-8, 7);
                    let reconstructed = (pred + q * scale).clamp(-32768, 32767);
                    let delta = sample as i64 - reconstructed as i64;
                    err = err.saturating_add((delta * delta) as u64);
                    qs[j] = q as i8;
                    h2 = h1;
                    h1 = reconstructed;
                }
                if err < best.0 {
                    best = (err, fi, shift, qs, h1, h2);
                }
            }
        }
        let mut block = [0u8; 16];
        block[0] = ((best.1 as u8) << 4) | best.2 as u8;
        block[1] = if bi + 1 == blocks { 1 } else { 0 };
        for j in 0..14 {
            block[2 + j] = (best.3[j * 2] as u8 & 15) | ((best.3[j * 2 + 1] as u8 & 15) << 4);
        }
        history1 = best.4;
        history2 = best.5;
        out.extend_from_slice(&block);
    }
    out
}

fn build_vh(sizes: &[usize]) -> Result<Vec<u8>, String> {
    if sizes.len() != VOICE_COUNT {
        return Err("bank requires 16 samples".into());
    }
    let mut vh = vec![0u8; VH_SIZE];
    vh[..4].copy_from_slice(b"pBAV");
    put32(&mut vh, 4, 7);
    put32(&mut vh, 8, 1);
    put32(&mut vh, 12, (VH_SIZE + VB_SLOT_SIZE) as u32);
    put16(&mut vh, 16, 0xEEEE);
    put16(&mut vh, 18, 3); // 3 tone-table blocks
    put16(&mut vh, 20, VOICE_COUNT as u16);
    put16(&mut vh, 22, VOICE_COUNT as u16);
    vh[24] = 127;
    vh[25] = 64;
    put32(&mut vh, 28, 0xFFFF_FFFF);
    for prog in 1..=2 {
        let p = 0x20 + prog * 16;
        // psp table uses even numbers
        vh[p] = 16;
        vh[p + 1] = 127;
        vh[p + 2] = 80;
        vh[p + 4] = 64;
    }
    for i in 0..VOICE_COUNT {
        let prog = 1 + i / 8;
        let tone = (i % 8) * 2;
        // program 1: block 0, program 2: block 1
        let o = 0x820 + (prog - 1) * 0x200 + tone * 0x20;
        vh[o] = if i == VOICE_COUNT - 1 { 90 } else { 80 };
        vh[o + 2] = 127;
        vh[o + 3] = 64;
        // approx 8khz note
        vh[o + 4] = VAB_CENTER_NOTE;
        vh[o + 5] = VAB_PITCH_SHIFT;
        vh[o + 6] = 0;
        vh[o + 7] = 127;
        vh[o + 12] = 12;
        vh[o + 13] = 12;
        put16(&mut vh, o + 16, 0x80FF);
        put16(&mut vh, o + 18, 0x5FC0);
        put16(&mut vh, o + 20, prog as u16);
        put16(&mut vh, o + 22, SFX_VAG_MAP[i]);
    }
    let used: usize = sizes.iter().sum();
    if used > VB_SLOT_SIZE {
        return Err("sample data exceeds the fixed VB slot".into());
    }
    let offsets = 0xE20;
    put16(&mut vh, offsets, 0);
    for (i, &size) in sizes.iter().enumerate() {
        // the vab size is hardcoded in DRA so pad
        let extent = if i + 1 == sizes.len() {
            size + VB_SLOT_SIZE - used
        } else {
            size
        };
        if extent % 8 != 0 {
            return Err("sample size is not 8-byte aligned".into());
        }
        put16(&mut vh, offsets + (i + 1) * 2, (extent / 8) as u16);
    }
    Ok(vh)
}

fn select_pack(res: &[u8], variant: u32) -> Result<(usize, usize), String> {
    if matches!(res.get(..8), Some(b"SEPK1.20") | Some(b"SEPK1.30")) {
        return Ok((0, res.len()));
    }
    let packs = sepk_offsets(res)?;
    packs
        .into_iter()
        .find(|p| p.0 == variant)
        .map(|p| (p.1, p.2))
        .ok_or_else(|| format!("no SEPK language variant {variant}"))
}

fn inspect(path: &str) -> Result<(), String> {
    let res = fs::read(path).map_err(|e| e.to_string())?;
    if matches!(res.get(..8), Some(b"SEPK1.20") | Some(b"SEPK1.30")) {
        let samples = parse_sepk(&res, 0, res.len())?;
        println!(
            "raw {}: size=0x{:X} samples={}",
            String::from_utf8_lossy(&res[..8]),
            res.len(),
            samples.len()
        );
        for (i, s) in samples.iter().enumerate() {
            if path.to_ascii_lowercase().ends_with("sd_mar2.spk") {
                let &(program, tone) = MAR2_KEYS
                    .get(i)
                    .ok_or("sd_mar2 has more descriptors than its lookup table")?;
                println!(
                    "  {i:02} P:{program} T:{tone:<2} {:<20} {:5} Hz {:6} bytes",
                    s.name,
                    s.rate,
                    s.adpcm.len()
                );
            } else {
                println!(
                    "  {i:02} {:<20} {:5} Hz {:6} bytes",
                    s.name,
                    s.rate,
                    s.adpcm.len()
                );
            }
        }
        return Ok(());
    }
    for (variant, off, size) in sepk_offsets(&res)? {
        let samples = parse_sepk(&res, off, size)?;
        println!(
            "variant {variant}: offset=0x{off:X} size=0x{size:X} samples={}",
            samples.len()
        );
        for (i, s) in samples.iter().enumerate() {
            println!(
                "  {i:02} {:<20} {:5} Hz {:6} bytes",
                s.name,
                s.rate,
                s.adpcm.len()
            );
        }
    }
    Ok(())
}

fn wav_bytes(pcm: &[i16], rate: u32) -> Vec<u8> {
    let data_size = (pcm.len() * 2) as u32;
    let mut wav = Vec::with_capacity(44 + data_size as usize);
    wav.extend_from_slice(b"RIFF");
    wav.extend_from_slice(&(36 + data_size).to_le_bytes());
    wav.extend_from_slice(b"WAVEfmt ");
    wav.extend_from_slice(&16u32.to_le_bytes());
    wav.extend_from_slice(&1u16.to_le_bytes());
    wav.extend_from_slice(&1u16.to_le_bytes());
    wav.extend_from_slice(&rate.to_le_bytes());
    wav.extend_from_slice(&(rate * 2).to_le_bytes());
    wav.extend_from_slice(&2u16.to_le_bytes());
    wav.extend_from_slice(&16u16.to_le_bytes());
    wav.extend_from_slice(b"data");
    wav.extend_from_slice(&data_size.to_le_bytes());
    for &sample in pcm {
        wav.extend_from_slice(&sample.to_le_bytes());
    }
    wav
}

fn dump_wav(input: &str, output: &str, variant: u32) -> Result<(), String> {
    let res = fs::read(input).map_err(|e| e.to_string())?;
    let raw = matches!(res.get(..8), Some(b"SEPK1.20") | Some(b"SEPK1.30"));
    let (off, size) = select_pack(&res, variant)?;
    let samples = parse_sepk(&res, off, size)?;
    let is_mar2 = input.to_ascii_lowercase().ends_with("sd_mar2.spk");
    fs::create_dir_all(output).map_err(|e| e.to_string())?;
    let mut manifest = String::from("index\tprogram\ttone\tname\trate\tadpcm_bytes\n");
    for (i, sample) in samples.iter().enumerate() {
        let pcm = decode_adpcm(&sample.adpcm)?;
        let name = if sample.name.is_empty() {
            format!("sample_{i:02}")
        } else {
            sample.name.clone()
        };
        let filename = if is_mar2 {
            let &(program, tone) = MAR2_KEYS
                .get(i)
                .ok_or("sd_mar2 has more descriptors than its lookup table")?;
            manifest.push_str(&format!(
                "{i}\t{program}\t{tone}\t{name}\t{}\t{}\n",
                sample.rate,
                sample.adpcm.len()
            ));
            format!("{i:02}_p{program:02}_t{tone:02}_{name}.wav")
        } else {
            format!("{i:02}_{name}.wav")
        };
        fs::write(
            Path::new(output).join(filename),
            wav_bytes(&pcm, sample.rate),
        )
        .map_err(|e| e.to_string())?;
    }
    if is_mar2 {
        fs::write(Path::new(output).join("sfx-map.tsv"), manifest).map_err(|e| e.to_string())?;
    }
    if raw {
        println!(
            "wrote {} native PSP WAV files from raw SEPK to {output}",
            samples.len()
        );
    } else {
        println!(
            "wrote {} native PSP WAV files from variant {variant} to {output}",
            samples.len()
        );
    }
    Ok(())
}

fn build(input: &str, output: &str, variant: u32) -> Result<(), String> {
    let res = fs::read(input).map_err(|e| e.to_string())?;
    if res.get(..8) != Some(b"SEPK1.20") {
        return Err("build input must be the raw sd_mar2 SEPK1.20 bank".into());
    }
    let (off, size) = select_pack(&res, variant)?;
    let samples = parse_sepk(&res, off, size)?;
    if samples.len() != MAR2_KEYS.len() {
        return Err(format!(
            "sd_mar2 should have {} descriptors, found {}",
            MAR2_KEYS.len(),
            samples.len()
        ));
    }
    let selected = samples
        .get(VOICE_FIRST..VOICE_FIRST + VOICE_COUNT)
        .ok_or("sd_mar2 is missing Maria voice descriptors 10..25")?;
    let mut encoded = Vec::new();
    for sample in selected {
        let pcm = decode_adpcm(&sample.adpcm)?;
        let converted = resample_linear(trim_silence(&pcm, sample.rate), sample.rate, TARGET_RATE);
        encoded.push(encode_adpcm(&converted));
    }
    let used: usize = encoded.iter().map(Vec::len).sum();
    if used > VB_SLOT_SIZE {
        return Err(format!(
            "encoded bank is {used} bytes; slot is {VB_SLOT_SIZE} bytes"
        ));
    }
    let sizes: Vec<usize> = encoded.iter().map(Vec::len).collect();
    let vh = build_vh(&sizes)?;
    let mut vb = Vec::with_capacity(VB_SLOT_SIZE);
    for data in &encoded {
        vb.extend_from_slice(data);
    }
    vb.resize(VB_SLOT_SIZE, 0);
    fs::create_dir_all(output).map_err(|e| e.to_string())?;
    fs::write(Path::new(output).join("SD_RIH.VH"), &vh).map_err(|e| e.to_string())?;
    fs::write(Path::new(output).join("SD_RIH.VB"), &vb).map_err(|e| e.to_string())?;
    let mut manifest =
        String::from("index\tpsp_name\trate\tpcm_samples\tpsx_bytes\tprogram\ttone\tvag\n");
    for (i, &vag) in SFX_VAG_MAP.iter().enumerate() {
        let source_index = vag as usize - 1;
        let source = &selected[source_index];
        let data = &encoded[source_index];
        let decoded = decode_adpcm(&source.adpcm)?;
        let pcm_len = trim_silence(&decoded, source.rate).len();
        let samples = (pcm_len as u64 * TARGET_RATE as u64 / source.rate as u64) as usize;
        manifest.push_str(&format!(
            "{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\n",
            i,
            if source.name.is_empty() {
                VOICE_NAMES[i]
            } else {
                &source.name
            },
            source.rate,
            samples,
            data.len(),
            1 + i / 8,
            (i % 8) * 2,
            vag
        ));
    }
    manifest.push_str(&format!(
        "# source=sd_mar2.spk target_rate={TARGET_RATE} used={used} slot={VB_SLOT_SIZE}\n"
    ));
    fs::write(Path::new(output).join("maria-sfx.tsv"), manifest).map_err(|e| e.to_string())?;
    validate(output)?;
    println!(
        "wrote 16 samples: {used}/{VB_SLOT_SIZE} bytes ({:.1}%); {} bytes free",
        used as f64 * 100.0 / VB_SLOT_SIZE as f64,
        VB_SLOT_SIZE - used
    );
    Ok(())
}

fn validate(dir: &str) -> Result<(), String> {
    let vh = fs::read(Path::new(dir).join("SD_RIH.VH")).map_err(|e| e.to_string())?;
    let vb = fs::read(Path::new(dir).join("SD_RIH.VB")).map_err(|e| e.to_string())?;
    if vh.len() != VH_SIZE || vb.len() != VB_SLOT_SIZE {
        return Err("wrong fixed VH/VB size".into());
    }
    if vh.get(..4) != Some(b"pBAV") || le32(&vh, 4)? != 7 {
        return Err("invalid VAB header".into());
    }
    if le32(&vh, 12)? as usize != VH_SIZE + VB_SLOT_SIZE {
        return Err("wrong VAB total size".into());
    }
    for prog in 1..=2 {
        if vh[0x20 + prog * 16] != 16 {
            return Err(format!("program {prog} does not expose 16 tone slots"));
        }
    }
    for (i, &expected_vag) in SFX_VAG_MAP.iter().enumerate() {
        let prog = i / 8;
        let tone = (i % 8) * 2;
        let tone_offset = 0x820 + prog * 0x200 + tone * 0x20;
        let actual_vag = le16(&vh, tone_offset + 22)?;
        if actual_vag != expected_vag {
            return Err(format!(
                "SFX slot {i} tone map is VAG {actual_vag}, expected {expected_vag}"
            ));
        }
    }
    let mut previous = 0usize;
    for i in 1..=VOICE_COUNT {
        let end = previous + le16(&vh, 0xE20 + i * 2)? as usize * 8;
        if end <= previous || end > vb.len() {
            return Err(format!("invalid sample offset {i}"));
        }
        let sample = &vb[previous..end];
        decode_adpcm(sample)?;
        if !sample.chunks_exact(16).any(|block| block[1] & 1 != 0) {
            return Err(format!("sample {i} lacks end flag"));
        }
        previous = end;
    }
    if previous != vb.len() {
        return Err(format!(
            "VAG extents cover {previous} bytes; fixed VB is {} bytes",
            vb.len()
        ));
    }
    println!(
        "valid VAB: VH=0x{:X}, VB=0x{:X}, sample_data=0x{:X}",
        vh.len(),
        vb.len(),
        previous
    );
    Ok(())
}

fn run() -> Result<(), String> {
    let args: Vec<String> = env::args().collect();
    match args.get(1).map(String::as_str) {
        Some("inspect") if args.len() == 3 => inspect(&args[2]),
        Some("build") if args.len() == 4 || args.len() == 5 => {
            let variant = args.get(4).map(|v| v.parse()).transpose()
                .map_err(|_| "variant must be an integer")?.unwrap_or(2);
            build(&args[2], &args[3], variant)
        }
        Some("dump-wav") if args.len() == 4 || args.len() == 5 => {
            let variant = args
                .get(4)
                .map(|v| v.parse())
                .transpose()
                .map_err(|_| "variant must be an integer")?
                .unwrap_or(2);
            dump_wav(&args[2], &args[3], variant)
        }
        Some("validate") if args.len() == 3 => validate(&args[2]),
        _ => Err(format!(
            "usage:\n  {} inspect <pl01pack.res|bank.spk>\n  {} dump-wav <pl01pack.res|bank.spk> <output-dir> [variant=2]\n  {} build <sd_mar2.spk> <output-dir>\n  {} validate <output-dir>",
            args[0], args[0], args[0], args[0])),
    }
}

fn main() {
    if let Err(e) = run() {
        eprintln!("maria-sfx: {e}");
        std::process::exit(1);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn silence_roundtrip() {
        let pcm = vec![0i16; 100];
        let encoded = encode_adpcm(&pcm);
        assert_eq!(encoded.len(), 64);
        assert!(decode_adpcm(&encoded).unwrap().iter().all(|&x| x == 0));
    }
    #[test]
    fn vag_terminator_is_not_decoded_as_audio() {
        let mut data = vec![0u8; 32];
        data[1] = 1;
        data[16 + 1] = 7;
        data[16 + 2..16 + 15].fill(0x77);
        let decoded = decode_adpcm(&data).unwrap();
        assert_eq!(decoded.len(), 28);
        assert!(decoded.iter().all(|&x| x == 0));
    }
    #[test]
    fn vab_has_fixed_layout() {
        let vh = build_vh(&[16; VOICE_COUNT]).unwrap();
        assert_eq!(vh.len(), VH_SIZE);
        let total: usize = (1..=VOICE_COUNT)
            .map(|i| le16(&vh, 0xE20 + i * 2).unwrap() as usize * 8)
            .sum();
        assert_eq!(total, VB_SLOT_SIZE);
        for (i, &expected_vag) in SFX_VAG_MAP.iter().enumerate() {
            let prog = i / 8;
            let tone = (i % 8) * 2;
            let offset = 0x820 + prog * 0x200 + tone * 0x20;
            assert_eq!(le16(&vh, offset + 22).unwrap(), expected_vag);
            assert_eq!(vh[offset + 4], VAB_CENTER_NOTE);
            assert_eq!(vh[offset + 5], VAB_PITCH_SHIFT);
        }
    }
    #[test]
    fn maria_voices_use_all_generated_vags_in_order() {
        assert_eq!(
            SFX_VAG_MAP,
            [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
        );
        assert_eq!(MAR2_KEYS[VOICE_FIRST], (1, 0));
        assert_eq!(MAR2_KEYS[VOICE_FIRST + VOICE_COUNT - 1], (2, 14));
    }
    #[test]
    fn mar2_program_one_tone_zero_is_descriptor_ten() {
        assert_eq!(MAR2_KEYS[10], (1, 0));
    }
}
