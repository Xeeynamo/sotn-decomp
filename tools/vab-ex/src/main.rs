use std::env;
use std::fs;
use std::fs::File;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Write;
use std::io::{Read, Result};
use std::path::Path;
use std::path::PathBuf;
use serde::{Serialize, Deserialize};
use serde_json;

// Resources

// vabtool at https://archive.org/details/Sony-PSX-tools

// https://psx.arthus.net/sdk/Psy-Q/DOCS/Devrefs/Filefrmt.pdf
// pdf page 213

// https://github.com/ColdSauce/psxsdk/blob/master/tools/vag2wav.c

// https://github.com/vgmtrans/vgmtrans/blob/3840a224e22fc1d7b7c1eecb0e341a5c651f3fa8/src/main/formats/Vab.cpp#L9

fn read_u8(file: &mut File) -> Result<u8> {
    let mut buffer = [0; 1];
    file.read_exact(&mut buffer)?;
    Ok(u8::from_le_bytes(buffer))
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 4 {
        eprintln!("Usage: {} <in_vh> <in_vb> <out_dir>", args[0]);
        return;
    }

    let in_vh = &args[1];
    let in_vb = &args[2];
    let out_dir = &args[3];

    let in_vh_path = PathBuf::from(in_vh);
    let in_vb_path = PathBuf::from(in_vb);

    // Check if the input files exist
    if !in_vh_path.exists() {
        eprintln!("Error: Input VH file not found.");
        return;
    }

    if !in_vb_path.exists() {
        eprintln!("Error: Input VB file not found.");
        return;
    }

    let out_dir_path = Path::new(out_dir);

    // Create the output directory if it doesn't exist
    if !out_dir_path.exists() {
        match fs::create_dir_all(out_dir_path) {
            Ok(()) => println!("Output directory created: {out_dir_path:?}"),
            Err(err) => {
                eprintln!("Error creating output directory: {err}");
                return;
            }
        }
    }

    if let Err(err) = read_data_from_file(&in_vh, &in_vb, &out_dir) {
        eprintln!("Error: {err}");
    }
}

fn write_vag(vag_name: String, pcm_name: String, start_pos: u64, data_size: u64) -> Result<()> {
    let mut vag = File::open(&vag_name)?;
    let mut pcm = File::create(&pcm_name)?;

    // TODO figure out actual rates
    let samp_freq: u32 = 44100 / 4;

    // Write header chunk
    pcm.write_all(b"RIFF")?;
    // Skip file size field for now
    pcm.seek(SeekFrom::Current(4))?;

    pcm.write_all(b"WAVE")?;
    // Write fmt chunk
    pcm.write_all(b"fmt ")?;
    // Write chunk 1 size in little endian format
    pcm.write_all(&[0x10, 0, 0, 0])?;
    // Write audio format (1 = PCM)
    pcm.write_all(&[1, 0])?;
    // Number of channels (1)
    pcm.write_all(&[1, 0])?;
    // Write sample rate
    pcm.write_all(&[(samp_freq & 0xff) as u8, (samp_freq >> 8) as u8, 0, 0])?;
    // Write byte rate (SampleRate * NumChannels * BitsPerSample/8)
    pcm.write_all(&[
        (samp_freq * 2) as u8,
        (samp_freq * 2 >> 8) as u8,
        (samp_freq * 2 >> 16) as u8,
        (samp_freq * 2 >> 24) as u8,
    ])?;
    // Write block align (NumChannels * BitsPerSample/8), thus 2
    pcm.write_all(&[2, 0])?;
    // Write BitsPerSample
    pcm.write_all(&[16, 0])?;

    // Write data chunk
    pcm.write_all(b"data")?;
    // Skip SubChunk2Size, we will return to it later
    pcm.seek(SeekFrom::Current(4))?;

    // Now write data...
    let mut samples = [0.0; 28];
    let mut s_1 = 0.0;
    let mut s_2 = 0.0;

    let f: [[f64; 2]; 5] = [
        [0.0, 0.0],
        [60.0 / 64.0, 0.0],
        [115.0 / 64.0, -52.0 / 64.0],
        [98.0 / 64.0, -55.0 / 64.0],
        [122.0 / 64.0, -60.0 / 64.0],
    ];

    let _pos = vag.seek(SeekFrom::Start(start_pos));

    while vag.seek(SeekFrom::Current(0))? < (data_size + 48 + start_pos) {
        let predict_nr = read_u8(&mut vag)?;
        let shift_factor = predict_nr & 0xf;
        let predict_nr = predict_nr >> 4;
        let mut d: i32;
        let mut s: i32;
        let flags = read_u8(&mut vag)?;

        if flags == 7 {
            break;
        }

        for i in (0..28).step_by(2) {
            d = read_u8(&mut vag)? as i32;
            // print!("{d} , ");
            s = (d & 0xf) << 12;
            if s & 0x8000 != 0 {
                s |= 0xffff_0000u32 as i32;
            }
            samples[i] = (s >> shift_factor) as f64;
            s = (d & 0xf0) << 8;
            if s & 0x8000 != 0 {
                s |= 0xffff_0000u32 as i32;
            }
            samples[i + 1] = (s >> shift_factor) as f64;
        }

        for i in 0..28 {
            samples[i] =
                samples[i] + s_1 * f[predict_nr as usize][0] + s_2 * f[predict_nr as usize][1];
            s_2 = s_1;
            s_1 = samples[i];
            d = (samples[i] + 0.5) as i32;
            pcm.write_all(&[d as u8, (d >> 8) as u8])?;
        }
    }

    // Get file size
    let sz = pcm.seek(SeekFrom::Current(0))? as i32;

    // Now write ChunkSize
    pcm.seek(SeekFrom::Start(4))?;
    pcm.write_all(&[
        (sz - 8) as u8,
        ((sz - 8) >> 8) as u8,
        ((sz - 8) >> 16) as u8,
        ((sz - 8) >> 24) as u8,
    ])?;

    // Now write Subchunk2Size
    pcm.seek(SeekFrom::Start(40))?;
    pcm.write_all(&[
        (sz - 44) as u8,
        ((sz - 44) >> 8) as u8,
        ((sz - 44) >> 16) as u8,
        ((sz - 44) >> 24) as u8,
    ])?;

    Ok(())
}

#[derive(Debug, Clone)]
#[derive(Serialize, Deserialize)]
#[allow(dead_code)]
struct HeaderStruct {
    id: String,
    version: u32,
    vab_id: u32,
    total_size: u32,
    reserved_1: u16,
    num_programs: u16,
    num_tones: u16,
    num_vags: u16,
    master_volume: u8,
    master_pan: u8,
    bank_attr_1: u8,
    bank_attr_2: u8,
    reserved_2: u32,
}

fn read_header(file: &Vec<u8>) -> Result<HeaderStruct> {
    let id = little_endian_ascii_to_str(file, 0, 4)?;
    println!("ID: {id}");

    let version = read_u32_at_offset(file, 4)?;
    println!("Version: {version}");

    let vab_id = read_u32_at_offset(file, 8)?;
    println!("VAB ID: {vab_id}");

    let total_size = read_u32_at_offset(file, 12)?;
    println!("Total Size: {total_size}");

    let reserved_1 = read_u16_at_offset(file, 16)?;
    println!("Reserved: {reserved_1}");

    let num_programs = read_u16_at_offset(file, 18)?;
    println!("Number of Programs: {num_programs}");

    let num_tones = read_u16_at_offset(file, 20)?;
    println!("Number of Tones: {num_tones}");

    let num_vags = read_u16_at_offset(file, 22)?;
    println!("Number of VAGs: {num_vags}");

    let master_volume = read_u8_at_offset(file, 24)?;
    println!("Master Volume: {master_volume}");

    let master_pan = read_u8_at_offset(file, 25)?;
    println!("Master Pan: {master_pan}");

    let bank_attr_1 = read_u8_at_offset(file, 26)?;
    println!("Bank Attributes 1: {bank_attr_1}");

    let bank_attr_2 = read_u8_at_offset(file, 27)?;
    println!("Bank Attributes 2: {bank_attr_2}");

    let reserved_2 = read_u32_at_offset(file, 28)?;
    println!("Reserved2: {reserved_2}");

    Ok(HeaderStruct {
        id,
        version,
        vab_id,
        total_size,
        reserved_1,
        num_programs,
        num_tones,
        num_vags,
        master_volume,
        master_pan,
        bank_attr_1,
        bank_attr_2,
        reserved_2,
    })
}

fn write_string_to_file(file_path: &str, content: &str) -> std::io::Result<()> {
    let mut file = File::create(file_path)?;
    file.write_all(content.as_bytes())?;
    Ok(())
}

fn read_data_from_file(in_vh: &str, in_vb: &str, out_dir: &str) -> Result<()> {
    match fs::read(in_vh) {
        Ok(file_data) => {
            let header = read_header(&file_data).unwrap();

            let vag_offset_table_start = 0x20 + (32 * 16 * header.num_programs);
            println!("vag_offset_table_start {vag_offset_table_start}");

            let off_progs = 0 + 0x20;
            let off_tone_attrs = off_progs + (16 * 128);
            let off_vag_offsets = off_tone_attrs + (32 * 16 * header.num_programs);
            let mut vag_offset = 0;

            for vag_num in 1..header.num_vags + 1 {
                let off = off_vag_offsets + vag_num * 2;
                let vag_size = (read_u16_at_offset(&file_data, off.into())?) as u32 * 8;

                println!("vag offset {vag_offset} size {vag_size}");

                write_vag(
                    in_vb.to_string(),
                    format!("{out_dir}/out{vag_num}.wav"),
                    vag_offset,
                    vag_size as u64,
                )
                .unwrap();
                vag_offset += vag_size as u64;
            }

            let programs = read_programs(&file_data, &header).unwrap();
            let tone_attrs = read_tone_attrs(&file_data, &header).unwrap();
        
            let vh_file = VhFile{
                header: header.clone(),
                programs: programs,
                tone_attrs: tone_attrs
            };
        
            let vh_file_json = serde_json::to_string_pretty(&vh_file).unwrap();

            let json_path = format!("{out_dir}/vh.json");

            match write_string_to_file(&json_path, &vh_file_json) {
                Ok(()) => println!("String successfully written to the file."),
                Err(e) => eprintln!("Error writing to the file: {e}"),
            }            
        }
        Err(e) => {
            println!("Error reading the file: {e}");
        }
    }

    Ok(())
}

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
#[allow(dead_code)]
struct Program {
    num_tones: u8,
    volume: u8,
    priority: u8,
    mode: u8,
    pan: u8,
    attr: u8,
    name: String,
}

fn read_programs(file: &Vec<u8>, header: &HeaderStruct) -> Result<Vec<Program>> {
    let mut result = Vec::<Program>::new();

    // have to ignore the header value header.num_programs.
    // Always 128 entries
    for program_num in 0..128 {
        let offset = 0x20 + program_num * 16;

        println!("----- Program {program_num} -----");

        let num_tones = read_u8_at_offset(file, (offset + 0).try_into().unwrap())?;
        println!(" Number of Tones: {num_tones}");

        let volume = read_u8_at_offset(file, (offset + 1).try_into().unwrap())?;
        println!(" Volume: {volume}");

        let priority = read_u8_at_offset(file, (offset + 2).try_into().unwrap())?;
        println!(" Priority: {priority}");

        let mode = read_u8_at_offset(file, (offset + 3).try_into().unwrap())?;
        println!(" Mode: {mode}");

        let pan = read_u8_at_offset(file, (offset + 4).try_into().unwrap())?;
        println!(" Pan: {pan}");

        let attr = read_u8_at_offset(file, (offset + 5).try_into().unwrap())?;
        println!(" Attr: {attr}");

        let name = little_endian_ascii_to_str(file, (offset + 6).try_into().unwrap(), 10)?;
        println!(" Name: {name:?}");

        result.push(Program {
            num_tones,
            volume,
            priority,
            mode,
            pan,
            attr,
            name,
        });
    }
    Ok(result)
}

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
#[derive(Clone)]
#[allow(dead_code)]
struct ToneAttr {
    prior: u8,
    mode: u8,
    volume: u8,
    pan: u8,
    center: u8,
    shift: u8,
    min: u8,
    max: u8,
    vib_w: u8,
    vib_t: u8,
    por_w: u8,
    por_t: u8,
    pb_min: u8,
    pb_max: u8,
    unk14: u8,
    unk15: u8,
    adsr_1: u16,
    adsr_2: u16,
    prog: u8,
    vag: u8,
    tone_name: String,
}

fn read_tone_attrs(file: &Vec<u8>, header: &HeaderStruct) -> Result<Vec<Vec<ToneAttr>>> {
    let mut result: Vec<Vec<ToneAttr>> = vec![Vec::new(); (header.num_programs + 1).into()];

    for program_num in 0..header.num_programs+1 {
        let off_progs = 0 + 0x20;
        let off_tone_attrs = off_progs + (16 * 128);

        for tone_attr_num in 0..16 {
            let tone_attr_size = 32;
            let tone_attrs_per_program_size = 32 * 16;

            let off_current_tone_attr = 
                off_tone_attrs + 
                tone_attrs_per_program_size * program_num + 
                tone_attr_size * tone_attr_num;

            println!(
                "----- Program {} - ToneAttr {} -----",
                program_num, tone_attr_num
            );

            let prior = read_u8_at_offset(file, (off_current_tone_attr + 0).into())?;
            println!(" prior: {prior}");

            let mode = read_u8_at_offset(file, (off_current_tone_attr + 1).into())?;
            println!(" mode: {mode}");

            let volume = read_u8_at_offset(file, (off_current_tone_attr + 2).into())?;
            println!(" volume: {volume}");

            let pan = read_u8_at_offset(file, (off_current_tone_attr + 3).into())?;
            println!(" pan: {pan}");

            let center = read_u8_at_offset(file, (off_current_tone_attr + 4).into())?;
            println!(" center: {center}");

            let shift = read_u8_at_offset(file, (off_current_tone_attr + 5).into())?;
            println!(" shift: {shift}");

            let min = read_u8_at_offset(file, (off_current_tone_attr + 6).into())?;
            println!(" min: {min}");

            let max = read_u8_at_offset(file, (off_current_tone_attr + 7).into())?;
            println!(" max: {max}");

            let vib_w = read_u8_at_offset(file, (off_current_tone_attr + 8).into())?;
            println!(" vib_w: {vib_w}");

            let vib_t = read_u8_at_offset(file, (off_current_tone_attr + 9).into())?;
            println!(" vib_t: {vib_t}");

            let por_w = read_u8_at_offset(file, (off_current_tone_attr + 10).into())?;
            println!(" por_w: {por_w}");

            let por_t = read_u8_at_offset(file, (off_current_tone_attr + 11).into())?;
            println!(" por_t: {por_t}");

            let pb_min = read_u8_at_offset(file, (off_current_tone_attr + 12).into())?;
            println!(" pb_min: {pb_min}");

            let pb_max = read_u8_at_offset(file, (off_current_tone_attr + 13).into())?;
            println!(" pb_max: {pb_max}");

            let unk14 = read_u8_at_offset(file, (off_current_tone_attr + 14).into())?;
            println!(" unk14: {unk14}");

            let unk15 = read_u8_at_offset(file, (off_current_tone_attr + 15).into())?;
            println!(" unk15: {unk15}");

            let adsr_1 = read_u16_at_offset(file, (off_current_tone_attr + 16).into())?;
            println!(" adsr_1: {adsr_1}");

            let adsr_2 = read_u16_at_offset(file, (off_current_tone_attr + 18).into())?;
            println!(" adsr_2: {adsr_2}");

            // 1-based in editor?
            let prog = read_u8_at_offset(file, (off_current_tone_attr + 20).into())?;
            println!(" prog: {prog}");

            // 1-based in editor?
            let vag = read_u8_at_offset(file, (off_current_tone_attr + 21).into())?;
            println!(" vag: {vag}");

            let tone_name =
                little_endian_ascii_to_str(file, (off_current_tone_attr + 22).into(), 10)?;
            println!(" Tone Name: {tone_name:?}");

            result[program_num as usize].push(ToneAttr {
                prior,
                mode,
                volume,
                pan,
                center,
                shift,
                min,
                max,
                vib_w,
                vib_t,
                por_w,
                por_t,
                pb_min,
                pb_max,
                unk14,
                unk15,
                adsr_1,
                adsr_2,
                prog,
                vag,
                tone_name,
            });
        }
    }
    Ok(result)
}


fn write_tone_attrs(file: & mut Vec<u8>, 
    header: &HeaderStruct, tone_attrs: &Vec<Vec<ToneAttr>>) -> Result<()> {

    for program_num in 0..header.num_programs+1 {
        let off_progs = 0 + 0x20;
        let off_tone_attrs = off_progs + (16 * 128);

        for tone_attr_num in 0..16 {
            let tone_attr_size = 32;
            let tone_attrs_per_program_size = 32 * 16;

            let off_current_tone_attr = 
                off_tone_attrs + 
                tone_attrs_per_program_size * program_num + 
                tone_attr_size * tone_attr_num;

            let current_tone_attr = &tone_attrs[program_num as usize][tone_attr_num as usize];

            println!("writing program {program_num} tone_attr {tone_attr_num} to {off_current_tone_attr}");

            write_u8_at_offset(file, (off_current_tone_attr + 0).try_into().unwrap(), &current_tone_attr.prior)?;
            write_u8_at_offset(file, (off_current_tone_attr + 1).try_into().unwrap(), &current_tone_attr.mode)?;
            write_u8_at_offset(file, (off_current_tone_attr + 2).try_into().unwrap(), &current_tone_attr.volume)?;
            write_u8_at_offset(file, (off_current_tone_attr + 3).try_into().unwrap(), &current_tone_attr.pan)?;
            write_u8_at_offset(file, (off_current_tone_attr + 4).try_into().unwrap(), &current_tone_attr.center)?;
            write_u8_at_offset(file, (off_current_tone_attr + 5).try_into().unwrap(), &current_tone_attr.shift)?;
            write_u8_at_offset(file, (off_current_tone_attr + 6).try_into().unwrap(), &current_tone_attr.min)?;
            write_u8_at_offset(file, (off_current_tone_attr + 7).try_into().unwrap(), &current_tone_attr.max)?;
            write_u8_at_offset(file, (off_current_tone_attr + 8).try_into().unwrap(), &current_tone_attr.vib_w)?;
            write_u8_at_offset(file, (off_current_tone_attr + 9).try_into().unwrap(), &current_tone_attr.vib_t)?;
            write_u8_at_offset(file, (off_current_tone_attr + 10).try_into().unwrap(), &current_tone_attr.por_w)?;
            write_u8_at_offset(file, (off_current_tone_attr + 11).try_into().unwrap(), &current_tone_attr.por_t)?;
            write_u8_at_offset(file, (off_current_tone_attr + 12).try_into().unwrap(), &current_tone_attr.pb_min)?;
            write_u8_at_offset(file, (off_current_tone_attr + 13).try_into().unwrap(), &current_tone_attr.pb_max)?;
            write_u8_at_offset(file, (off_current_tone_attr + 14).try_into().unwrap(), &current_tone_attr.unk14)?;
            write_u8_at_offset(file, (off_current_tone_attr + 15).try_into().unwrap(), &current_tone_attr.unk15)?;
            write_u16_at_offset(file, (off_current_tone_attr + 16).try_into().unwrap(), &current_tone_attr.adsr_1)?;
            write_u16_at_offset(file, (off_current_tone_attr + 18).try_into().unwrap(), &current_tone_attr.adsr_2)?;
            write_u8_at_offset(file, (off_current_tone_attr + 20).try_into().unwrap(), &current_tone_attr.prog)?;
            write_u8_at_offset(file, (off_current_tone_attr + 21).try_into().unwrap(), &current_tone_attr.vag)?;
            string_to_little_endian_bytes(&current_tone_attr.tone_name, file, (off_current_tone_attr + 22).try_into().unwrap());
        }
    }
    Ok(())
}

fn read_u8_at_offset(data: &Vec<u8>, offset: u64) -> Result<u8> {
    if offset >= data.len() as u64 {
        return Err(std::io::Error::new(
            std::io::ErrorKind::InvalidInput,
            "Offset is beyond the end of the data.",
        ));
    }
    Ok(data[offset as usize])
}

fn read_u16_at_offset(data: &Vec<u8>, offset: u64) -> Result<u16> {
    if offset + 2 > data.len() as u64 {
        return Err(std::io::Error::new(
            std::io::ErrorKind::InvalidInput,
            "Offset is beyond the end of the data.",
        ));
    }
    let buffer: [u8; 2] = [data[offset as usize], data[offset as usize + 1]];
    Ok(u16::from_le_bytes(buffer))
}

fn read_u32_at_offset(data: &Vec<u8>, offset: u64) -> Result<u32> {
    if offset + 4 > data.len() as u64 {
        return Err(std::io::Error::new(
            std::io::ErrorKind::InvalidInput,
            "Offset is beyond the end of the data.",
        ));
    }
    let buffer: [u8; 4] = [
        data[offset as usize],
        data[offset as usize + 1],
        data[offset as usize + 2],
        data[offset as usize + 3],
    ];
    Ok(u32::from_le_bytes(buffer))
}

fn write_u8_at_offset(data: &mut Vec<u8>, offset: u64, value: &u8) -> Result<()> {
    if offset >= data.len() as u64 {
        return Err(std::io::Error::new(
            std::io::ErrorKind::InvalidInput,
            "Offset is beyond the end of the data.",
        ));
    }
    data[offset as usize] = *value;
    Ok(())
}

fn write_u16_at_offset(data: &mut Vec<u8>, offset: u64, value: &u16) -> Result<()> {
    if offset + 2 > data.len() as u64 {
        return Err(std::io::Error::new(
            std::io::ErrorKind::InvalidInput,
            "Offset is beyond the end of the data.",
        ));
    }
    let bytes = value.to_le_bytes();
    data[offset as usize] = bytes[0];
    data[offset as usize + 1] = bytes[1];
    Ok(())
}

fn write_u32_at_offset(data: &mut Vec<u8>, offset: u64, value: &u32) -> Result<()> {
    if offset + 4 > data.len() as u64 {
        return Err(std::io::Error::new(
            std::io::ErrorKind::InvalidInput,
            "Offset is beyond the end of the data.",
        ));
    }
    let bytes = value.to_le_bytes();
    data[offset as usize] = bytes[0];
    data[offset as usize + 1] = bytes[1];
    data[offset as usize + 2] = bytes[2];
    data[offset as usize + 3] = bytes[3];
    Ok(())
}

fn little_endian_ascii_to_str(bytes: &Vec<u8>, pos: u64, len: u64) -> Result<String> {
    let mut result = String::new();
    let mut i: i64 = (pos + len - 1).try_into().unwrap();
    while i >= pos as i64 {
        result.push(bytes[i as usize] as char);
        i -= 1;
    }

    Ok(result)
}

fn string_to_little_endian_bytes(input: &str, bytes: &mut Vec<u8>, pos: usize) {
    let mut i = pos;
    for c in input.chars().rev() {
        bytes[i] = c as u8;
        i += 1;
    }
}

#[test]
fn test_header() {
    let file_path = "../../disks/us/ST/DRE/SD_ZKDRE.VH";
    match fs::read(file_path) {
        Ok(file_data) => {
            let header = read_header(&file_data).unwrap();
            assert!(header.id.as_str() == "VABp");
            assert!(header.version == 7);
            assert!(header.vab_id == 0);
            assert!(header.total_size == 113712);
            assert!(header.reserved_1 == 61166);
            assert!(header.num_programs == 6);
            assert!(header.num_tones == 96);
            assert!(header.num_vags == 15);
            assert!(header.master_volume == 127);
            assert!(header.master_pan == 64);
            assert!(header.bank_attr_1 == 0);
            assert!(header.bank_attr_2 == 0);
            assert!(header.reserved_2 == 4294967295);
        }
        Err(e) => {
            println!("Error reading the file: {e}");
        }
    }
}

#[test]
fn test_programs() {
    let file_path = "../../disks/us/ST/DRE/SD_ZKDRE.VH";
    match fs::read(file_path) {
        Ok(file_data) => {
            let header = read_header(&file_data).unwrap();
            let programs = read_programs(&file_data, &header).unwrap();

            // Vab File Editor seems to think there's 7 programs. Why?

            assert!(programs[0].num_tones == 0);
            assert!(programs[0].volume == 127);
            assert!(programs[0].priority == 255);
            assert!(programs[0].mode == 255);
            assert!(programs[0].pan == 63);
            assert!(programs[0].attr == 255);

            assert!(programs[1].num_tones == 0);
            assert!(programs[1].volume == 127);
            assert!(programs[1].priority == 255);
            assert!(programs[1].mode == 255);
            assert!(programs[1].pan == 63);
            assert!(programs[1].attr == 255);
        }
        Err(e) => {
            println!("Error reading the file: {e}");
        }
    }
}

#[test]
fn test_tone_attrs() {
    let file_path = "../../disks/us/ST/DRE/SD_ZKDRE.VH";
    match fs::read(file_path) {
        Ok(file_data) => {
            let header = read_header(&file_data).unwrap();
            let programs = read_programs(&file_data, &header).unwrap();
            let tone_attrs = read_tone_attrs(&file_data, &header).unwrap();

            // program 2, tone attr 0
            assert!(tone_attrs[2][0].prior == 8);
            assert!(tone_attrs[2][0].pan == 64);
            assert!(tone_attrs[2][0].center == 82);
            assert!(tone_attrs[2][0].shift == 109);
            assert!(tone_attrs[2][0].adsr_1 == 33023);
            assert!(tone_attrs[2][0].adsr_2 == 24512);
        }
        Err(e) => {
            println!("Error reading the file: {e}");
        }
    }
}

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
#[allow(dead_code)]
struct VhFile {
    header: HeaderStruct,
    programs: Vec<Program>,
    tone_attrs: Vec<Vec<ToneAttr>> 
}

fn write_header(file: & mut Vec<u8>, header: &HeaderStruct) -> Result<()> {
    string_to_little_endian_bytes(&header.id, file, 0);
    write_u32_at_offset(file, 4, &header.version)?;
    write_u32_at_offset(file, 8, &header.vab_id)?;
    write_u32_at_offset(file, 12, &header.total_size)?;
    write_u16_at_offset(file, 16, &header.reserved_1)?;
    write_u16_at_offset(file, 18, &header.num_programs)?;
    write_u16_at_offset(file, 20, &header.num_tones)?;
    write_u16_at_offset(file, 22, &header.num_vags)?;
    write_u8_at_offset(file, 24, &header.master_volume)?;
    write_u8_at_offset(file, 25, &header.master_pan)?;
    write_u8_at_offset(file, 26, &header.bank_attr_1)?;
    write_u8_at_offset(file, 27, &header.bank_attr_2)?;
    write_u32_at_offset(file, 28, &header.reserved_2)?;
    Ok(())
}

fn write_programs(file: & mut Vec<u8>, programs: &Vec<Program>) -> Result<()> {
    for program_num in 0..programs.len() {
        let current_program = &programs[program_num];
        let offset = 0x20 + program_num * 16;
        write_u8_at_offset(file, (offset + 0).try_into().unwrap(), &current_program.num_tones)?;
        write_u8_at_offset(file, (offset + 1).try_into().unwrap(), &current_program.volume)?;
        write_u8_at_offset(file, (offset + 2).try_into().unwrap(), &current_program.priority)?;
        write_u8_at_offset(file, (offset + 3).try_into().unwrap(), &current_program.mode)?;
        write_u8_at_offset(file, (offset + 4).try_into().unwrap(), &current_program.pan)?;
        write_u8_at_offset(file, (offset + 5).try_into().unwrap(), &current_program.attr)?;
        string_to_little_endian_bytes(&current_program.name, file, (offset + 6).into());
    }
    Ok(())
}

fn check_serialize_deserialize(file_data: &Vec<u8>)
{
    let header = read_header(&file_data).unwrap();
    let programs = read_programs(&file_data, &header).unwrap();
    let tone_attrs = read_tone_attrs(&file_data, &header).unwrap();

    let vh_file = VhFile{
        header: header.clone(),
        programs: programs,
        tone_attrs: tone_attrs
    };

    let vh_file_json = serde_json::to_string_pretty(&vh_file).unwrap();

    println!("{vh_file_json}");

    let deserialized: VhFile = serde_json::from_str(&vh_file_json).unwrap();

    // AA as sentitinel value, rarer than 0x00
    let mut test_bytes = vec![0xAA; file_data.len()];

    write_header(& mut test_bytes, &deserialized.header);

    for i in 0..0x20
    {
        assert!(test_bytes[i] == file_data[i]);
    }

    write_programs(& mut test_bytes, &deserialized.programs);
    
    println!("Checking from {} to {}",  0x20,(0x20 + 16 * deserialized.programs.len()));
    // 16 x 128 (Max programs)
    for i in 0x20..(0x20 + 16 * 128)
    {
        if(test_bytes[i] != file_data[i])
        {
            println!("mismatch i {i} test_bytes[i] {} file_data[i] {}", test_bytes[i], file_data[i]);
            assert!(test_bytes[i] == file_data[i]);
        }  
    }

    write_tone_attrs(& mut test_bytes, 
        &deserialized.header, &deserialized.tone_attrs);
    
    let off_progs = 0 + 0x20;
    let off_tone_attrs = off_progs + (16 * 128);

    println!("off_tone_attrs {off_tone_attrs}");

    for i in off_tone_attrs..test_bytes.len()
    {
        if(test_bytes[i] != file_data[i])
        {
            println!("mismatch i {i} test_bytes[i] {} file_data[i] {}", test_bytes[i], file_data[i]);
            assert!(test_bytes[i] == file_data[i]);
        }  
    }
}

#[test]
fn test_serialize() {
    let file_path = "../../disks/us/ST/DRE/SD_ZKDRE.VH";
    match fs::read(file_path) {
        Ok(file_data) => {
            check_serialize_deserialize(&file_data);
        }
        Err(e) => {
            println!("Error reading the file: {e}");
        }
    }
}
