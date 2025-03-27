use clap::{arg, Arg, Command};
use std::fs::File;
use std::io::{self,BufRead,BufWriter};
use regex::Regex;
use std::path::Path;
use std::io::Write;

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

#[derive(Debug)]
struct FunctionEntry {
    name: String,
    offset: usize,
    vram: usize,
}

#[derive(Debug)]
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

fn do_match(match_file: &String, bin_file: &String, options: &mut Options) {
    eprintln!("matching {match_file}, {bin_file}");
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
                eprintln!("{i}: {line}");
                if let Some(address) = capture.get(1).map(|m| m.as_str().to_string()) {
                    rom_start = usize::from_str_radix(address.as_str(), 16).expect("hex string");
                    eprintln!("rom_start {rom_start}")
                }
                continue;
            }

            if let Some(capture) = vramRE.captures(&line) {
                eprintln!("{i}: {line}");
                if let Some(address) = capture.get(1).map(|m| m.as_str().to_string()) {
                    vram = usize::from_str_radix(address.as_str(), 16).expect("hex string");
                    eprintln!("vram {vram}")
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

                eprintln!("{i}: new entry {segment_object} #{segment_offset} #{segment_size}");

                continue;
            }

            let offset = usize::from_str_radix(parts.get(0).expect("symbol offset").strip_prefix("0x").unwrap(), 16).expect("symbol offset base 16");
            let function = parts.get(1).expect("symbol text");

            if function.ends_with(".NON_MATCHING") {
                continue;
            }

            eprintln!("    -> {function} {offset}");
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

        eprintln!("segments: {segments:?}")

    }

    return segments;
}

fn sig_for_range(bytes: &Vec<u8>, offset: usize, size: usize, options: &Options) -> u64 {
    let q: u64 = 0xFFFFFFEF;
    let radix: u64 = 4294967296;

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
    // eprintln!("{} size: {} key: 0x{object_hash:08x}", map.name(), map.size);
    writeln!(*options.writer, "{}:", map.name());

    for i in (0..map.text_symbols.len()) {
        let segment = &map.text_symbols[i];
        let size = if i < (map.text_symbols.len() - 1) {
            map.text_symbols[i + 1].offset - segment.offset
        } else {
            map.offset + map.size - segment.offset
        };

        let segment_hash = sig_for_range(&bytes, segment.offset, size, options);
        writeln!(*options.writer, "    {}: [{}, 0x{segment_hash:08x}]", segment.name, size / 4);

    }
}

fn evaluate(map_file: &String, bin_file: &String, options: &mut Options) {
    eprintln!("evaluating {map_file}, {bin_file}");
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
        .subcommand(Command::new("match")
            .arg(Arg::new("granularity")
                .short('g')
                .help("The level match granularity should occur (segment, function)"))
            .arg(Arg::new("MATCH"))
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
    eprintln!("{matches:#?}");

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
            eprintln!("evaluate {cmd:#?}");
            let map_file = cmd.get_one::<String>("MAP").expect("required");
            let bin_file = cmd.get_one::<String>("BIN").expect("required");
            eprintln!("map {map_file:#?}");
            eprintln!("bin {bin_file:#?}");

            evaluate(map_file, bin_file, &mut options);
        },
        Some(("match", cmd)) =>  {
            eprintln!("match {cmd:#?}");
            let match_file = cmd.get_one::<String>("MATCH").expect("required");
            let bin_file = cmd.get_one::<String>("BIN").expect("required");
            do_match(match_file, bin_file, &mut options);
        },
        _ => unreachable!("Invalid command"),
    }
}
