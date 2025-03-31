use clap::{arg, Arg, Command};
use std::fs::File;
use std::io::{self,BufRead,BufWriter};
use regex::Regex;
use std::path::Path;
use std::io::Write;
use serde::{Serialize, Deserialize};
use serde_with::{self, serde_as};
use serde_yaml::{self};
use serde_hex::{SerHex,StrictPfx,CompactPfx};
use std::collections::HashMap;

/*
#[derive(Parser, Debug)]
#[command(
    author,
    version,
    about,
    long_about = "\n
Finds common sections of code and provides offsets for well known code segments.

Usage:

    sotn-match evaluate [map] [bin] ...
    sotn-match match [match-file] [bin] ...
")]
struct Args {
}
*/

struct Options {
    coefficient: u64,
    radix: u64,
    writer: Box<dyn Write>,
}

#[derive(Debug, PartialEq, Serialize, Deserialize)]
struct FunctionEntry {
    name: String,
    offset: usize,
    vram: usize,
}

#[derive(Debug, PartialEq, Serialize, Deserialize)]
struct ObjectMap {
    object: String,
    offset: usize,
    vram: usize,
    size: usize,
    text_symbols: Vec<FunctionEntry>,
}

impl ObjectMap {
    fn name(&self) -> &str {
        // this can be done with experimental file_prefix
        // function, but replicating logic here for stable
        Path::new(&self.object)
            .file_name().expect("object name")
            .to_str().unwrap()
            .strip_suffix(".c.o").unwrap()
    }
}

#[serde_as]
#[derive(Debug, PartialEq, Serialize, Deserialize)]
struct FunctionSignature {
    name: String,
    // #[serde_as(as = "serde_with::hex::Hex<serde_with::formats::Uppercase>")]
    signature: u64,
    size: usize,
}

#[serde_as]
#[derive(Debug, PartialEq, Serialize, Deserialize)]
struct SegmentSignature {
    name: String,
    // #[serde_as(as = "serde_with::hex::Hex<serde_with::formats::Uppercase>")]
    signature: u64,
    size: usize,
    functions: Vec<FunctionSignature>,
}

#[serde_as]
#[derive(Debug, PartialEq, Serialize, Deserialize)]
struct SegmentOffset {
    name: String,
    offset: usize,
    size: usize,
    symbols: HashMap<String, usize>,
}



fn find(signature: u64, size: usize, instructions: &Vec<u32>, start: usize, end: usize, options: &mut Options) -> Option<usize> {

    let mut i = start;
    let mut found = false;
    let mut offset = -1;
    let mut count = 0;

    let mut hash: u64 = 0;
    let mut rm: u64 = 1;

    for _ in 0..(size - 1) {
        rm = (options.radix * rm) % options.coefficient;
    }
    // println!("rm {:08x} size: {}, count: {}", rm, size, count);


    while count < size && i < end {
        hash = ((options.radix * hash) + instructions[i] as u64) % options.coefficient;

        count += 1;
        i += 1;
    }

    // println!("count: {}", count);
    if i >= instructions.len() {
        return None;
    }

    while hash != signature && i < end {
        hash = (hash + options.coefficient - (rm * instructions[i - count] as u64) % options.coefficient) % options.coefficient;
        hash = ((options.radix * hash) + instructions[i] as u64) % options.coefficient;
        i += 1;

    }

    if hash == signature {
        Some((i - count) * 4)
    } else {
        // println!("sig: {} hash: {}, i: {}", signature, hash, i);
        None
    }
}

fn scan(match_file: &String, bin_file: &String, options: &mut Options) {
    // eprintln!("matching {match_file}, {bin_file}");

    let bytes = std::fs::read(bin_file).expect("Could not read bin file");

    let instructions: Vec<u32> = bytes.chunks(4).map(|b| {
        // TODO: make endianness optional
        let instruction: u32 = ((b[3] as u32) << 24) |
            ((b[2] as u32) << 16) |
            ((b[1]  as u32) << 8) |
            (b[0] as u32);

        // mask any fields which may refer to global symbols. this will
        // mask false positives, but keep most immediates and local vars.
        match instruction >> 26 {
            // r-type
            0 => instruction,
            // j-type
            2 | 3 => instruction & 0xFC000000,
            // i-type
            _ => instruction & 0xFFFF0000
        }
    }).collect();


    let f = std::fs::File::open(match_file).unwrap();
    for document in serde_yaml::Deserializer::from_reader(io::BufReader::new(f)) {
        let segment = SegmentSignature::deserialize(document).unwrap();
        // println!("{:?}", segment );
        // eprintln!("segment: {}", segment.name);

        // try to find the entire object, first
        let offset = find(segment.signature,
                          segment.size / 4,
                          &instructions, 0, instructions.len(), options);

        // eprintln!("found: {} -> {:?}", segment.name, offset);

        let Some(offset) = offset else {
            continue;
        };

        let mut map = HashMap::new();

        for function in segment.functions {
            let function_offset = find(function.signature,
                                       function.size / 4,
                                       &instructions,
                                       offset / 4,
                                       (offset + segment.size) / 4,
                                       options);
            // eprintln!("    found: {} -> {:?}", function.name, function_offset);
            if let Some(function_offset) = function_offset {
                map.insert(function.name, function_offset);
            }
        }

        let so = SegmentOffset {
            name: segment.name,
            offset: offset,
            size: segment.size,
            symbols: map,
        };


        writeln!(*options.writer, "---");
        writeln!(*options.writer, "{}", serde_yaml::to_string(&so).expect("yaml"));
    }
}

enum EvaluateState {
    Start, Entry
}

fn read_segments(map_file: &String) -> Vec<ObjectMap> {
    let file = File::open(map_file).expect("Could not open map file");
    let mut i = 0;


    let romStartRE = Regex::new(r"(?xi)
        ^\s*
        0x([0-9A-F]+)\s+[^\s]+_ROM_START\s=\s
    ").expect("regex");

    let vramRE = Regex::new(r"(?xi)
        ^\s*
        0x([0-9A-F]+)\s+[^\s]+_VRAM\s=\s
    ").expect("regex");

    let segmentRE = Regex::new(r"(?xi)
        ^\s[\w\-_.\/]+\.c\.o\(\.([a-z.]+)\)$
    ").expect("regex");

    let mut segments = Vec::<ObjectMap>::new();

    if let lines = io::BufReader::new(file).lines() {

        let mut state = EvaluateState::Start;
        let mut rom_start: usize = 0xFFFFFFFF;
        let mut vram: usize = 0xFFFFFFFF;

        let mut first = true;
        let mut segment_object = "".to_string();
        let mut segment_size: usize = 0;
        let mut segment_offset: usize = 0;
        let mut segment_symbols = Vec::<FunctionEntry>::new();

        for line in lines.map_while(Result::ok) {
            i += 1;
            // eprintln!("{i}: {line}");
            if let Some(capture) = romStartRE.captures(&line) {
                // eprintln!("{i}: {line}");
                if let Some(address) = capture.get(1).map(|m| m.as_str().to_string()) {
                    rom_start = usize::from_str_radix(address.as_str(), 16).expect("hex string");
                    // eprintln!("rom_start {rom_start}")
                }
                continue;
            }

            if let Some(capture) = vramRE.captures(&line) {
                // eprintln!("{i}: {line}");
                if let Some(address) = capture.get(1).map(|m| m.as_str().to_string()) {
                    vram = usize::from_str_radix(address.as_str(), 16).expect("hex string");
                }
                continue;
            }

            if let Some(capture) = segmentRE.captures(&line) {
                if let Some(segment_type) = capture.get(1).map(|m| m.as_str()) {
                    // eprintln!("{i} found new segment: {segment_type}");
                    match segment_type {
                        "text" => state = EvaluateState::Entry,
                        _ => state = EvaluateState::Start,
                    }
                }
                continue;
            }

            // if we're not in a text section, continue
            let EvaluateState::Entry = state else {
                // eprintln!("{i} skipping, wrong state");
                continue;
            };

            // if this is setting vars, continue
            if line.contains(" = ") {
                // eprintln!("{i} skipping, assignment");
                continue;
            }

            let parts: Vec<&str> = line.trim().split_whitespace().collect();

            // if this is not a text section, continue
            if parts.len() == 4 && *parts.get(0).unwrap() != ".text" {
                state = EvaluateState::Start;
                // eprintln!("{i} skipping, resetting state");
                continue;
            }

            if *parts.get(0).unwrap() == ".text" {
                if !first {
                    segments.push(ObjectMap {
                        object: segment_object,
                        offset: segment_offset - vram + rom_start,
                        vram: segment_offset,
                        size: segment_size,
                        text_symbols: segment_symbols,
                    });
                    segment_symbols = Vec::new();
                }
                first = false;
                segment_offset = usize::from_str_radix(parts.get(1).expect("segment
                offset").strip_prefix("0x").unwrap(),
                16).expect("segment offset base 16");
                segment_size = usize::from_str_radix(parts.get(2).expect("segment size").strip_prefix("0x").unwrap(),
                16).expect("segment size base 16");
                segment_object = parts.get(3).expect("segment object").to_string();

                // eprintln!("{i}: new entry {segment_object} #{segment_offset} #{segment_size}");

                continue;
            }

            let offset = usize::from_str_radix(parts.get(0).expect("symbol offset").strip_prefix("0x").expect("symbol value"), 16).expect("symbol offset base 16");
            let function = parts.get(1).expect("symbol text");

            if function.ends_with(".NON_MATCHING") {
                continue;
            }

            // eprintln!("    -> {function} {offset}");
            segment_symbols.push(FunctionEntry {
                name: function.to_string(),
                vram: offset,
                offset: offset - vram + rom_start,
            });
        }
        segments.push(ObjectMap {
            object: segment_object,
            offset: segment_offset - vram + rom_start,
            vram: segment_offset,
            size: segment_size,
            text_symbols: segment_symbols,
        });

        // eprintln!("segments: {segments:?}")

    }

    return segments;
}

fn sig_for_range(bytes: &Vec<u8>, offset: usize, size: usize, options: &Options) -> u64 {
    fn horner_hash(s: u32, acc: u64, radix: u64, q: u64) -> u64 {
        ((radix * acc) + (s as u64)) % q
    }

    let mut acc: u64 = 0;

    for i in (offset..(offset + size)).step_by(4) {
        // get instruction
        // TODO: make endianness optional
        let instruction: u32 = ((bytes[i + 3] as u32) << 24) |
            ((bytes[i + 2] as u32) << 16) |
            ((bytes[i + 1]  as u32) << 8) |
            (bytes[i] as u32);


        // mask any fields which may refer to global symbols. this will
        // mask false positives, but keep most immediates and local vars.
        let masked_ins =
            match instruction >> 26 {
                // r-type
                0 => instruction,
                // j-type
                2 | 3 => instruction & 0xFC000000,
                // i-type
                _ => instruction & 0xFFFF0000
            };

        acc = horner_hash(masked_ins, acc, options.radix, options.coefficient);
    }


    return acc;
}

fn calculate_object_hashes(map: &ObjectMap, bin_file: &String, options: &mut Options) {
    let bytes = std::fs::read(bin_file).expect("Could not read bin file");

    // calculate the signature of the entire object
    let object_hash = sig_for_range(&bytes, map.offset, map.size, options);
    // eprintln!("    {}: [{}, 0x{object_hash:08x}]", map.name(), map.size / 4);
    // eprintln!("{} size: {} key: 0x{object_hash:08x}", map.name(), map.size);
    // writeln!(*options.writer, "{}:", map.name());

    let mut functions = Vec::new();

    for i in (0..map.text_symbols.len()) {
        let segment = &map.text_symbols[i];
        let size = if i < (map.text_symbols.len() - 1) {
            map.text_symbols[i + 1].offset - segment.offset
        } else {
            map.offset + map.size - segment.offset
        };

        let segment_hash = sig_for_range(&bytes, segment.offset, size, options);
        // eprintln!("    {}: [{}, 0x{segment_hash:08x}]", segment.name, size / 4);

        functions.push(FunctionSignature{ name: segment.name.clone(), signature: segment_hash, size: size });
    }

    let sig = SegmentSignature {
        name: map.name().to_string(),
        signature: object_hash,
        size: map.size,
        functions: functions
    };

    writeln!(*options.writer, "---");
    writeln!(*options.writer, "{}", serde_yaml::to_string(&sig).expect("yaml"));
}

fn evaluate(map_file: &String, bin_file: &String, options: &mut Options) {
    // eprintln!("evaluating {map_file}, {bin_file}");
    let segments = read_segments(map_file);

    for map in segments {
        // eprintln!("    - [0x{:x}, c, {}]", map.offset, map.name());
        calculate_object_hashes(&map, bin_file, options);
    }
}


fn main() {

    let command = Command::new(env!("CARGO_CRATE_NAME"))
        .subcommand(Command::new("evaluate")
            .arg(Arg::new("MAP")
                .help("A GNU Map file"))
            .arg(Arg::new("BIN")
                .help("An overlay file"))
            .about("Create a match file from an existing overlay"))
        .subcommand(Command::new("scan")
            .arg(Arg::new("granularity")
                .short('g')
                .help("The level match granularity should occur (segment, function)"))
            .arg(Arg::new("MATCH-CONFIG"))
            .arg(Arg::new("BIN"))
            .about("Use a match file to find offsets in a new overlay"))
        .subcommand_required(true)
        .arg(Arg::new("output")
            .long("output")
            .short('o')
            .help("Output file for match keys (default: console)")
            .required(false))
       .arg(Arg::new("coefficient")
            .short('c')
            .help("The Rabin-Karp rolling hash coefficient")
            .required(false));

    let matches = command.get_matches();
    // eprintln!("{matches:#?}");

    let mut options = Options {
        coefficient: 0xFFFFFFEF,
        radix: 4294967296,
        writer: match matches.get_one::<String>("output") {
            Some(ref path) => File::create(path).map(|f| Box::new(f) as Box<dyn Write>).unwrap(),
            None => Box::new(io::stdout()),
        },
    };

    match matches.subcommand() {
        Some(("evaluate", cmd)) => {
            // eprintln!("evaluate {cmd:#?}");
            let map_file = cmd.get_one::<String>("MAP").expect("required");
            let bin_file = cmd.get_one::<String>("BIN").expect("required");
            // eprintln!("map {map_file:#?}");
            // eprintln!("bin {bin_file:#?}");

            evaluate(map_file, bin_file, &mut options);
        },
        Some(("scan", cmd)) =>  {
            // eprintln!("match {cmd:#?}");
            let match_file = cmd.get_one::<String>("MATCH-CONFIG").expect("required");
            let bin_file = cmd.get_one::<String>("BIN").expect("required");
            scan(match_file, bin_file, &mut options);
        },
        _ => unreachable!("Invalid command"),
    }
}

// test
// PSP map file
//
//LOAD build/pspeu/asm/pspeu/st/lib_psp/data/61218.data.s.o
//LOAD build/pspeu/asm/pspeu/st/lib_psp/data/6D748.data.s.o
//LOAD build/pspeu/asm/pspeu/st/lib_psp/data/6DE40.bss.s.o
//LOAD build/pspeu/asm/pspeu/st/lib_psp/data/6DE60.bss.s.o
//LOAD build/pspeu/asm/pspeu/st/lib_psp/data/6E0A8.bss.s.o
//                0x0006dd80                        __romPos = 0x0
//                0x00000000                        _gp = 0x0
//                0x00000000                        mwo_header_ROM_START = __romPos
//                0x00000000                        mwo_header_VRAM = ADDR (.mwo_header)
//
//.mwo_header     0x00000000       0x80
// FILL mask 0x00000000
//                0x00000000                        mwo_header_DATA_START = .
//                0x00000000                        mwo_header_bin = .
// build/pspeu/assets/st/lib/mwo_header.bin.o(.data)
// .data          0x00000000       0x80 build/pspeu/assets/st/lib/mwo_header.bin.o
//                0x00000000                _binary_assets_st_lib_mwo_header_bin_start
//                0x00000080                _binary_assets_st_lib_mwo_header_bin_end
//                0x00000080                        mwo_header_DATA_END = .
//                0x00000080                        mwo_header_DATA_SIZE = ABSOLUTE ((mwo_header_DATA_END - mwo_header_DATA_START))
//                0x0006dd80                        __romPos = (__romPos + SIZEOF (.mwo_header))
//                0x00000080                        mwo_header_ROM_END = __romPos
//                0x00000080                        mwo_header_VRAM_END = .
//                0x00000080                        stlib_ROM_START = __romPos
//                0x09237700                        stlib_VRAM = ADDR (.stlib)
//
//.stlib          0x09237700    0x6dd00 load address 0x00000080
// FILL mask 0x00000000
//                0x09237700                        stlib_TEXT_START = .
// build/pspeu/src/st/lib/create_entity.c.o(.text)
// .text          0x09237700      0x120 build/pspeu/src/st/lib/create_entity.c.o
//                0x09237700                CreateEntityFromLayout
// .text          0x09237820      0x194 build/pspeu/src/st/lib/create_entity.c.o
//                0x09237820                CreateEntityWhenInVerticalRange
// *fill*         0x092379b4        0x4 00000000
// .text          0x092379b8      0x194 build/pspeu/src/st/lib/create_entity.c.o
//                0x092379b8                CreateEntityWhenInHorizontalRange
// *fill*         0x09237b4c        0x4 00000000
// .text          0x09237b50       0x70 build/pspeu/src/st/lib/create_entity.c.o
// .text          0x09237bc0       0x84 build/pspeu/src/st/lib/create_entity.c.o
// *fill*         0x09237c44        0x4 00000000
// .text          0x09237c48      0x140 build/pspeu/src/st/lib/create_entity.c.o
// .text          0x09237d88      0x158 build/pspeu/src/st/lib/create_entity.c.o
// .text          0x09237ee0       0x74 build/pspeu/src/st/lib/create_entity.c.o
// *fill*         0x09237f54        0x4 00000000
// .text          0x09237f58       0x88 build/pspeu/src/st/lib/create_entity.c.o
// .text          0x09237fe0      0x144 build/pspeu/src/st/lib/create_entity.c.o
// *fill*         0x09238124        0x4 00000000
// .text          0x09238128      0x15c build/pspeu/src/st/lib/create_entity.c.o
// *fill*         0x09238284        0x4 00000000
// .text          0x09238288      0x230 build/pspeu/src/st/lib/create_entity.c.o
//                0x09238288                InitRoomEntities
// .text          0x092384b8       0xe0 build/pspeu/src/st/lib/create_entity.c.o
//                0x092384b8                UpdateRoomPosition
// .text          0x09238598       0x88 build/pspeu/src/st/lib/create_entity.c.o
//                0x09238598                CreateEntityFromCurrentEntity
// .text          0x09238620       0x84 build/pspeu/src/st/lib/create_entity.c.o
//                0x09238620                CreateEntityFromEntity
// build/pspeu/src/st/lib/e_bloody_zombie.c.o(.text)
// *fill*         0x092386a4        0x4 00000000
// .text          0x092386a8      0x590 build/pspeu/src/st/lib/e_bloody_zombie.c.o
//                0x092386a8                EntityBloodSplatter
// .text          0x09238c38      0x290 build/pspeu/src/st/lib/e_bloody_zombie.c.o
//                0x09238c38                EntityBloodDrips
//
//
//
//
//
// PSX Map file
//
//
// build/us/src/st/lib/blit_char.c.o(.rodata)
// build/us/src/st/lib/e_particles.c.o(.rodata)
// build/us/src/st/lib/popup.c.o(.rodata)
// build/us/src/st/lib/e_mist_door.c.o(.rodata)
//                0x801aded0                        . = ALIGN (., 0x4)
//                0x801aded0                        stlib_RODATA_END = .
//                0x00002598                        stlib_RODATA_SIZE = ABSOLUTE ((stlib_RODATA_END - stlib_RODATA_START))
//                0x801aded0                        stlib_TEXT_START = .
// build/us/src/st/lib/st_debug.c.o(.text)
// .text          0x801aded0       0xc8 build/us/src/st/lib/st_debug.c.o
//                0x801aded0                LIB_EntityBackgroundBlock
// build/us/src/st/lib/e_lock_camera.c.o(.text)
// .text          0x801adf98      0x524 build/us/src/st/lib/e_lock_camera.c.o
//                0x801adf98                PlayerIsWithinHitbox
//                0x801ae01c                EntityLockCamera
// build/us/src/st/lib/e_breakable.c.o(.text)
// .text          0x801ae4bc      0x42c build/us/src/st/lib/e_breakable.c.o
//                0x801ae4bc                EntityBreakable
//                0x801ae7ac                func_us_801AE7AC
//                0x801ae84c                func_us_801AE84C
// build/us/src/st/lib/first_c_file.c.o(.text)
// .text          0x801ae8e8      0x998 build/us/src/st/lib/first_c_file.c.o
//
