use std::fs::File;
use std::io::{Read, Result};
use std::io::Seek;
use std::io::SeekFrom;
use std::path::PathBuf;
use std::env;
use std::fs;
use std::path::Path;
use std::io::{Write};
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

fn read_u8_at_offset(file: &mut File, offset: u64) -> Result<u8> {
    file.seek(SeekFrom::Start(offset))?;
    let mut buffer = [0; 1];
    file.read_exact(&mut buffer)?;
    Ok(buffer[0])
}

fn read_u16_at_offset(file: &mut File, offset: u64) -> Result<u16> {
    file.seek(SeekFrom::Start(offset))?;
    let mut buffer = [0; 2];
    file.read_exact(&mut buffer)?;
    Ok(u16::from_le_bytes(buffer))
}

fn read_u32_at_offset(file: &mut File, offset: u64) -> Result<u32> {
    file.seek(SeekFrom::Start(offset))?;
    let mut buffer = [0; 4];
    file.read_exact(&mut buffer)?;
    Ok(u32::from_le_bytes(buffer))
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
            Ok(()) => println!("Output directory created: {:?}", out_dir_path),
            Err(err) => {
                eprintln!("Error creating output directory: {}", err);
                return;
            }
        }
    }

    if let Err(err) = read_data_from_file(&in_vh, &in_vb, &out_dir) {
        eprintln!("Error: {}", err);
    }
}

fn write_vag(vag_name:String, pcm_name: String, start_pos: u64, data_size: u64) -> Result<()> {
    let mut vag = File::open(&vag_name)?;
    let mut pcm = File::create(&pcm_name)?;

    // TODO figure out actual rates
    let samp_freq: u32 = 44100/4;

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
    pcm.write_all(&[(samp_freq * 2) as u8, (samp_freq * 2 >> 8) as u8, (samp_freq * 2 >> 16) as u8, (samp_freq * 2 >> 24) as u8])?;
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
        let predict_nr = read_u8(& mut vag)?;
        let shift_factor = predict_nr & 0xf;
        let predict_nr = predict_nr >> 4;
        let mut d : i32;
        let mut s: i32;
        let flags = read_u8(& mut vag)?;

        if flags == 7 {
            break;
        }

        for i in (0..28).step_by(2) {
            d = read_u8(& mut vag)? as i32;
            // print!("{} , ", d);
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
            samples[i] = samples[i] + s_1 * f[predict_nr as usize][0] + s_2 * f[predict_nr as usize][1];
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
    pcm.write_all(&[(sz - 8) as u8, ((sz - 8) >> 8) as u8, ((sz - 8) >> 16) as u8, ((sz - 8) >> 24) as u8])?;

    // Now write Subchunk2Size
    pcm.seek(SeekFrom::Start(40))?;
    pcm.write_all(&[(sz - 44) as u8, ((sz - 44) >> 8) as u8, ((sz - 44) >> 16) as u8, ((sz - 44) >> 24) as u8])?;

    Ok(())
}

#[allow(dead_code)]
struct HeaderStruct {
    id: u32,
    version: u32,
    vab_id: u32,
    total_size: u32,
    num_programs: u16,
    num_tones: u16,
    num_vags: u16,
    master_volume: u8,
    master_pan: u8,
    bank_attr_1: u8,
    bank_attr_2: u8,
}

fn read_header(file: & mut File) -> Result<HeaderStruct> {
    let id = read_u32_at_offset(file, 0)?;
    println!("ID: {}", id);

    let version = read_u32_at_offset(file, 4)?;
    println!("Version: {}", version);

    let vab_id = read_u32_at_offset(file, 8)?;
    println!("VAB ID: {}", vab_id);

    let total_size = read_u32_at_offset(file, 12)?;
    println!("Total Size: {}", total_size);

    let reserved = read_u16_at_offset(file, 16)?;
    println!("Reserved: {}", reserved);

    let num_programs = read_u16_at_offset(file, 18)?;
    println!("Number of Programs: {}", num_programs);

    let num_tones = read_u16_at_offset(file, 20)?;
    println!("Number of Tones: {}", num_tones);

    let num_vags = read_u16_at_offset(file, 22)?;
    println!("Number of VAGs: {}", num_vags);

    let master_volume = read_u8_at_offset(file, 24)?;
    println!("Master Volume: {}", master_volume);

    let master_pan = read_u8_at_offset(file, 25)?;
    println!("Master Pan: {}", master_pan);

    let bank_attr_1 = read_u8_at_offset(file, 26)?;
    println!("Bank Attributes 1: {}", bank_attr_1);

    let bank_attr_2 = read_u8_at_offset(file, 27)?;
    println!("Bank Attributes 2: {}", bank_attr_2);

    Ok(HeaderStruct {
        id,
        version,
        vab_id,
        total_size,
        num_programs,
        num_tones,
        num_vags,
        master_volume,
        master_pan,
        bank_attr_1,
        bank_attr_2,
    })
}

fn read_data_from_file(in_vh: &str, in_vb: &str, out_dir: &str) -> Result<()> {
    let mut file = File::open(in_vh)?;

    let header = read_header(& mut file).unwrap();

    for program_num in 0..header.num_programs {
        let offset = 0x20 + program_num * 16;

        println!("----- Program {} -----", program_num);

        let num_tones = read_u8_at_offset(&mut file, (offset + 0).into() )?;
        println!(" Number of Tones: {}", num_tones);    

        let volume = read_u8_at_offset(&mut file, (offset + 1).into())?;
        println!(" Volume: {}", volume);    

        let priority = read_u8_at_offset(&mut file, (offset + 2).into())?;
        println!(" Priority: {}", priority);

        let mode = read_u8_at_offset(&mut file, (offset + 3).into())?;
        println!(" Mode: {}", mode);

        let pan = read_u8_at_offset(&mut file, (offset + 4).into())?;
        println!(" Pan: {}", pan);
    }
  
    let vag_offset_table_start = 0x20 + (32 * 16 * header.num_programs);    
    println!("vag_offset_table_start {}", vag_offset_table_start );

    let off_progs = 0 + 0x20;
    let off_tone_attrs = off_progs + (16 * 128);
    let off_vag_offsets = off_tone_attrs + (32 * 16 * header.num_programs);
    let mut vag_offset = 0;

    for vag_num in 1..header.num_vags + 1 {
        let off = off_vag_offsets + vag_num * 2;
        let vag_size = (read_u16_at_offset(&mut file, off.into() )?) as u32 * 8;

        println!("vag offset {} size {}", vag_offset, vag_size);

        write_vag(
            in_vb.to_string(),
            format!("{}/out{}.wav", out_dir, vag_num), 
            vag_offset, vag_size as u64).unwrap();
            vag_offset += vag_size as u64; 
    }
    Ok(())
}
