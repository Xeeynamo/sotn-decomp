use glob::glob;
use regex::Regex;
use serde::Deserialize;
use std::collections::HashSet;
use std::fs;
use std::fs::File;
use std::io::BufReader;
use std::io::Read;
use std::io::Write;
use std::path::{Path, PathBuf};
use std::process::exit;

mod levenshtein_hashmap;
mod types;

use levenshtein_hashmap::LevenshteinHashMap;
use types::{DupsFile, Function, Instruction};

use clap::{Parser, ValueEnum};

#[derive(Clone, Copy, Debug, ValueEnum)]
enum Cpu {
    Mips,
    Superh,
}

fn duplicate_key(instructions: &[Instruction], cpu: Cpu) -> Vec<u8> {
    match cpu {
        Cpu::Mips => {
            // use opcode field (bits 31-26)
            instructions
                .iter()
                .map(|num| (num.op >> 26) as u8)
                .collect()
        }

        Cpu::Superh => {
            // 16 bit instructions
            instructions
                .iter()
                .flat_map(|num| {
                    let masked = mask_superh_instruction(num.op as u16);

                    vec![(masked >> 8) as u8, masked as u8]
                })
                .collect()
        }
    }
}
fn mask_superh_instruction(op: u16) -> u16 {
    match op {
        // exact opcodes
        0x0009 | // nop
        0x000B | // rts
        0x002B | // rte
        0x0018 | // sett
        0x0008 | // clrt
        0x0019 | // div0u
        0x0028 | // clrmac
        0x001B   // sleep
            => op,

        _ => match op & 0xF000 {
            // match_ni_f
            0x7000 | 0xE000 => op & 0xF000,

            // match_nd8_f
            0x9000 | 0xD000 => op & 0xF000,

            // match_d12_f
            0xA000 | 0xB000 => op & 0xF000,

            _ => match op & 0xFF00 {
                // match_i_f
                0x8800 | 0xC300 | 0xC800 | 0xC900 | 0xCA00 | 0xCB00
                | 0xCC00 | 0xCD00 | 0xCE00 | 0xCF00 => op & 0xFF00,

                // match_d_f
                0x8900 | 0x8B00 | 0x8D00 | 0x8F00
                | 0xC000 | 0xC100 | 0xC200
                | 0xC400 | 0xC500 | 0xC600 => op & 0xFF00,

                // two registers
                _ => op & 0xF00F,
            },
        },
    }
}

// parse .s file to get instructions and function name
fn parse_instructions(input: &str, dir: &str, file: &str, cpu: Cpu) -> Function {
    let mut instructions = Vec::new();
    let mut func_name = "";
    let mut section = ".text";

    for line in input.lines() {
        let parts: Vec<&str> = line.split_whitespace().collect();

        // find the function name
        if parts.len() == 2 {
            match parts[0] {
                "glabel" => func_name = parts[1],
                ".section" => section = parts[1],
                _ => (),
            }
        }

        match cpu {
            Cpu::Mips => {
                if section != ".text" {
                    // ignore non-code sections
                    continue;
                }
            }
            Cpu::Superh => {
                // no text sections
            }
        };

        if parts.len() < 3 {
            continue; // Skip lines that don't have enough parts
        }
        match cpu {
            Cpu::Mips => {
                if let Ok(file_addr) = u64::from_str_radix(parts[1], 16) {
                    if let Ok(vram_addr) = u64::from_str_radix(parts[2], 16) {
                        if let Ok(op) = u32::from_str_radix(parts[3], 16) {
                            // splat's output for MIPS is little-endian
                            let reversed_num = ((op >> 24) & 0xFF)
                                | (((op >> 16) & 0xFF) << 8)
                                | (((op >> 8) & 0xFF) << 16)
                                | ((op & 0xFF) << 24);

                            instructions.push(Instruction {
                                file_addr,
                                vram_addr,
                                op: reversed_num,
                            });
                        }
                    }
                }
            }

            Cpu::Superh => {
                if parts.len() >= 3
                    && parts[0] == "/*"
                    && parts[1].starts_with("0x")
                    && parts[2].starts_with("0x")
                {
                    if let Ok(addr) = u64::from_str_radix(&parts[1][2..], 16) {
                        if let Ok(op) = u16::from_str_radix(&parts[2][2..], 16) {
                            instructions.push(Instruction {
                                file_addr: addr,
                                vram_addr: addr,
                                op: op as u32,
                            });
                        }
                    }
                }
            }
        }
    }

    let key = duplicate_key(&instructions, cpu);

    Function {
        ops: instructions,
        name: func_name.to_string(),
        key,
        dir: dir.to_string(),
        file: file.to_string(),
        similarity: 0.0,
        decompiled: file.contains("/matchings/"),
    }
}

fn process_directory(dir_path: &str, funcs: &mut Vec<Function>, cpu: Cpu) {
    match std::fs::read_dir(dir_path) {
        Ok(entries) => {
            entries.for_each(|entry| {
                if let Ok(entry) = entry {
                    let item_path = entry.path();

                    if item_path.is_file() && item_path.to_string_lossy().ends_with(".s") {
                        println!("checking {:?}", item_path);

                        let mut file = fs::File::open(item_path.clone()).unwrap();
                        let mut buffer = String::new();

                        file.read_to_string(&mut buffer).unwrap();

                        let func = parse_instructions(
                            &buffer,
                            &dir_path,
                            &item_path.to_string_lossy(),
                            cpu,
                        );

                        // jr $ra, nop
                        let is_null = func.ops.len() == 2
                            && func.ops[0].op == 0x03E00008
                            && func.ops[1].op == 0x00000000;

                        if !is_null {
                            funcs.push(func.clone());
                        }
                    } else if item_path.is_dir() {
                        process_directory(&item_path.to_string_lossy(), funcs, cpu);
                    }
                }
            });
        }

        Err(error) => {
            eprintln!("Unable to read directory: {}", error);
            println!("Directory path: {}", dir_path);
        }
    }
}

#[derive(Parser, Debug)]
#[command(
    author,
    version,
    about = "\n
Finds duplicates in two asm directories and prints them out in order to identify patterns

Usage:

Do a 2-way compare with ordering
cargo run --release -- --dir ../../asm/us/st/nz0/nonmatchings/ --dir ../../asm/us/st/np3/nonmatchings/ --threshold .94

Clustering report using paths from splat configs
cargo run --release -- --threshold .94 --splat-config-glob '../../config/splat.us.*.yaml' --output-file output.txt

Saturn clustering report (legacy)
cargo run --release -- --threshold .94 --cpu superh --output-file output.txt
"
)]
struct Args {
    /// Levenshtein similarity threshold
    #[arg(short, long)]
    threshold: f64,

    /// Directory to parse asm from (2 required)
    #[arg(short, long)]
    dir: Vec<String>,

    /// File to write output to
    #[arg(short, long)]
    output_file: Option<String>,

    /// Base of source directory
    #[arg(short, long)]
    src_base: Option<String>,

    /// Derive source and assembly paths from matching splat YAML files
    #[arg(long, value_name = "GLOB", conflicts_with = "dir")]
    splat_config_glob: Option<String>,

    /// CPU architecture for duplicate detection
    #[arg(short, long, value_enum, default_value_t = Cpu::Mips)]
    cpu: Cpu,
}

#[derive(Clone, Debug, PartialEq)]
pub struct IncludeAsmEntry {
    pub line: String,
    pub path: String,
    pub asm_path: String,
}

fn process_directory_for_include_asm(dir: &str) -> Vec<IncludeAsmEntry> {
    let entries = std::fs::read_dir(dir).expect("Unable to read directory");
    let mut output = Vec::new();

    entries.for_each(|entry| {
        if let Ok(entry) = entry {
            let item_path = entry.path();

            if item_path.is_file() && item_path.to_string_lossy().ends_with(".c") {
                println!("checking {:?}", item_path);

                let file = File::open(item_path.clone()).expect("Unable to open file");

                let mut reader = BufReader::new(file);
                let mut buffer = String::new();

                reader
                    .read_to_string(&mut buffer)
                    .expect("Unable to read file");

                output.append(&mut process_buffer_for_include_asm(
                    &buffer,
                    &item_path.to_string_lossy(),
                ));
            } else if item_path.is_dir() {
                output.append(&mut process_directory_for_include_asm(
                    &item_path.to_string_lossy(),
                ));
            }
        }
    });

    output
}

fn process_buffer_for_include_asm(file_content: &str, file_path: &str) -> Vec<IncludeAsmEntry> {
    let re = Regex::new(r#"INCLUDE_ASM(?:_NO_ALIGN)?\((?:\s+)?"([^"]*)", ([^)]*)\)"#).unwrap();

    let mut output = Vec::new();
    let mut buffer = String::new();

    for line_str in file_content.lines() {
        if line_str.contains("INCLUDE_ASM") || !buffer.is_empty() {
            buffer.push_str(line_str);

            if !line_str.contains(';') {
                buffer.push_str(" ");
                println!("INCLUDE_ASM line did not contain ;, buffering input to subsequent lines");
                continue;
            }

            if let Some(captures) = re.captures(&buffer) {
                let (_, [asm_dir, asm_file]) = captures.extract();

                output.push(IncludeAsmEntry {
                    line: buffer.clone(),
                    path: file_path.to_string(),
                    asm_path: format!("../../asm/us/{}/{}.s", asm_dir, asm_file),
                });
            } else {
                println!("Failed to match regex on line: {}", buffer);
            }

            buffer.clear();
        }
    }

    output
}

fn get_all_include_asm(dir: &str) -> Vec<IncludeAsmEntry> {
    process_directory_for_include_asm(dir)
}

#[derive(Clone)]
struct SrcAsmPair {
    asm_dir: String,
    src_dir: String,
    overlay_name: String,
    include_asm: Vec<IncludeAsmEntry>,
    path_matcher: String,
}

#[derive(Debug, Deserialize)]
struct SplatConfig {
    options: SplatOptions,
}

#[derive(Debug, Deserialize)]
struct SplatOptions {
    asm_path: String,
    src_path: String,
    basename: String,
}

fn repository_root(splat_config_path: &Path) -> Result<PathBuf, String> {
    let config_path = splat_config_path.canonicalize().map_err(|error| {
        format!(
            "unable to resolve splat config {}: {error}",
            splat_config_path.display()
        )
    })?;
    let config_dir = config_path
        .parent()
        .ok_or_else(|| format!("splat config has no parent: {}", config_path.display()))?;

    if config_dir.file_name().is_some_and(|name| name == "config") {
        config_dir
            .parent()
            .map(Path::to_path_buf)
            .ok_or_else(|| format!("config directory has no parent: {}", config_dir.display()))
    } else {
        Ok(config_dir.to_path_buf())
    }
}

fn resolve_repo_path(repository_root: &Path, path: &str) -> PathBuf {
    let path = Path::new(path);
    if path.is_absolute() {
        path.to_path_buf()
    } else {
        repository_root.join(path)
    }
}

fn display_asm_path(path: &str) -> String {
    let path = Path::new(path);
    let mut trimmed = PathBuf::new();
    let mut found_asm = false;

    for component in path.components() {
        if component.as_os_str() == "asm" {
            found_asm = true;
        }
        if found_asm {
            trimmed.push(component.as_os_str());
        }
    }

    let displayed = if found_asm {
        trimmed.to_string_lossy().into_owned()
    } else {
        path.strip_prefix("../../")
            .unwrap_or(path)
            .to_string_lossy()
            .into_owned()
    };

    displayed.replace('\\', "/")
}

fn pairs_from_splat_glob(pattern: &str) -> Result<Vec<SrcAsmPair>, String> {
    let mut seen = HashSet::new();
    let mut pairs = Vec::new();
    let mut splat_paths = glob(pattern)
        .map_err(|error| format!("invalid splat config glob {pattern:?}: {error}"))?
        .collect::<Result<Vec<_>, _>>()
        .map_err(|error| format!("unable to read splat config glob entry: {error}"))?;
    splat_paths.sort();

    if splat_paths.is_empty() {
        return Err(format!("splat config glob matched no files: {pattern}"));
    }

    for splat_path in splat_paths {
        let repository_root = repository_root(&splat_path)?;
        let splat_contents = fs::read_to_string(&splat_path).map_err(|error| {
            format!(
                "unable to read splat config {}: {error}",
                splat_path.display()
            )
        })?;
        let splat: SplatConfig = serde_yaml::from_str(&splat_contents).map_err(|error| {
            format!(
                "unable to parse splat config {}: {error}",
                splat_path.display()
            )
        })?;

        let src_dir = resolve_repo_path(&repository_root, &splat.options.src_path);
        let asm_root = resolve_repo_path(&repository_root, &splat.options.asm_path);
        let asm_dir = asm_root.join("matchings");
        let nonmatchings_dir = asm_root.join("nonmatchings");

        // Fully decompiled or unextracted entries have nothing for this tool to scan.
        if !asm_dir.is_dir() && !nonmatchings_dir.is_dir() {
            continue;
        }

        let key = (src_dir.clone(), asm_root.clone());
        if !seen.insert(key) {
            continue;
        }

        pairs.push(SrcAsmPair {
            asm_dir: asm_dir.to_string_lossy().into_owned(),
            src_dir: src_dir.to_string_lossy().into_owned(),
            overlay_name: splat.options.basename.to_uppercase(),
            // old report data
            include_asm: Vec::new(),
            path_matcher: splat.options.src_path,
        });
    }

    Ok(pairs)
}

fn do_dups_report(
    output_file: Option<String>,
    threshold: f64,
    cpu: Cpu,
    splat_config_glob: Option<String>,
) {
    // full dups report
    let mut hash_map = LevenshteinHashMap::new(threshold);

    let mut files = Vec::new();

    let pairs: Vec<SrcAsmPair> = if let Some(splat_config_glob) = splat_config_glob {
        if !matches!(cpu, Cpu::Mips) {
            eprintln!("--splat-config-glob currently supports only MIPS configurations");
            exit(2);
        }
        pairs_from_splat_glob(&splat_config_glob).unwrap_or_else(|error| {
            eprintln!("{error}");
            exit(2);
        })
    } else {
        match cpu {
            Cpu::Mips => {
                eprintln!("MIPS report mode requires --splat-config-glob");
                exit(2);
            }
            // just put everything in the same bucket for saturn
            Cpu::Superh => vec![SrcAsmPair {
                asm_dir: "../../asm/saturn".into(),
                src_dir: "../../src/saturn".into(),
                overlay_name: "all".into(),
                include_asm: get_all_include_asm("../../src/saturn"),
                path_matcher: "/saturn/".into(),
            }],
        }
    };

    for pair in pairs.clone() {
        let dir = pair.asm_dir;
        process_asm_directory(&dir, &mut files, cpu);

        // saturn uses f_match and f_nomat due to DOS filename limitations
        if matches!(cpu, Cpu::Mips) {
            let nonmatchings = dir.replace("matchings", "nonmatchings");
            process_asm_directory(&nonmatchings, &mut files, cpu);
        }
    }

    files.sort_by(|a, b| {
        // First, sort by whether the name contains "nonmatching" (false before true)
        a.name
            .contains("nonmatching")
            .cmp(&b.name.contains("nonmatching"))
            .then_with(|| a.name.cmp(&b.name)) // Then, sort alphabetically by name
    });

    for file in &files {
        println!("file {}", file.name);
        for func in &file.funcs {
            println!(
                "\t{} {} {} {}",
                func.name,
                func.ops.len(),
                func.dir,
                func.file
            );
        }
    }

    for file in &files {
        for func in &file.funcs {
            hash_map.insert(func.key.clone(), func.clone());
        }
    }

    let mut entries: Vec<(&Vec<u8>, &Vec<Function>)> = hash_map.map.iter().collect();

    // sort by filename
    entries.sort_by(|(_, functions1), (_, functions2)| functions1[0].file.cmp(&functions2[0].file));

    // Then sort by the length of functions in reverse order
    entries.sort_by_key(|(_, functions)| std::cmp::Reverse(functions.len()));

    if let Some(o_file) = output_file {
        let mut output_file = File::create(o_file).expect("Unable to create file");
        writeln!(
            output_file,
            "| {:<4} | {:<8} | {:<35} | {:<2} ",
            "%", "Decomp?", "Name", "Asm Path"
        )
        .expect("Error writing to file");

        for (_, functions) in entries {
            if functions.len() > 1 {
                // Write separator to file
                writeln!(output_file, "-------------------------------------------------------------------------------")
                        .expect("Error writing to file");

                let mut temp_functions = functions.clone();

                // sort by the filename then the similarity
                temp_functions.sort_by(|a, b| {
                    b.decompiled
                        .cmp(&a.decompiled)
                        .then_with(|| a.file.cmp(&b.file))
                        .then_with(|| {
                            a.similarity
                                .partial_cmp(&b.similarity)
                                .unwrap_or(std::cmp::Ordering::Equal)
                        })
                });

                for function in &mut temp_functions {
                    // Write function details to file
                    writeln!(
                        output_file,
                        "| {:<4.2} | {:<8} | {:<35} | {:<2} ",
                        function.similarity,
                        function.decompiled,
                        function.name,
                        display_asm_path(&function.file)
                    )
                    .expect("Error writing to file");
                }
            }
        }
    } else {
        for (_, functions) in entries {
            if functions.len() > 1 {
                println!("------------------------");

                for function in functions {
                    println!(
                        "{:.2} {:?} {:?} {:?}",
                        function.similarity,
                        function.decompiled,
                        function.name,
                        display_asm_path(&function.file)
                    );
                }
            }
        }
    }
}

fn do_ordered_compare(dirs: Vec<String>, threshold: f64, cpu: Cpu) {
    let mut files = Vec::new();

    for dir in dirs {
        let mut funcs = Vec::new();
        process_directory(&dir, &mut funcs, cpu);

        // sort functions by vram address
        funcs.sort_by_key(|function| {
            function
                .ops
                .first()
                .map_or(u64::MAX, |instr| instr.vram_addr)
        });

        files.push(DupsFile {
            name: dir.to_string(),
            funcs: funcs.clone(),
        });
    }

    for file in &files {
        println!("file {}", file.name);
        for func in &file.funcs {
            println!("\t{} {}", func.name, func.ops.len());
        }
    }

    // 2 way comparison for determining patterns in overlays
    let mut pairs: Vec<Vec<Function>> = Vec::new();

    // print out all found duplicates with their similarity values
    let hyphens = "-".repeat(80);
    println!("{}", hyphens);
    println!("Duplicates and similarity");
    println!("{}", hyphens);

    for func_0 in &files[0].funcs {
        for func_1 in &files[1].funcs {
            let result = levenshtein_similarity(&func_0.key, &func_1.key);

            if result >= threshold {
                println!(
                    "{:<width$} | {:<width$} | {:<width$}",
                    func_0.name,
                    func_1.name,
                    result,
                    width = 40
                );
                let mut temp = Vec::new();
                temp.push(func_0.clone());
                temp.push(func_1.clone());
                pairs.push(temp.clone());
            }
        }
    }

    // print out functions as they are seen in order by the first file. Indicate if it's a
    // duplicate if the second function is non-blank

    println!("{}", hyphens);
    println!("Functions in file order");
    println!("{}", hyphens);
    println!(
        "{:<width$} | {:<width$}",
        files[0].name,
        files[1].name,
        width = 40
    );
    println!("{}", hyphens);

    for func_0 in &files[0].funcs {
        let mut dup_name = "";
        for pair in &pairs {
            if func_0.name == pair[0].name {
                dup_name = &pair[1].name;
            }
        }

        println!("{:<width$} | {:<width$}", func_0.name, dup_name, width = 40);
    }
}

fn main() {
    let args = Args::parse();

    let threshold = args.threshold;
    let dirs = args.dir;
    let output_file = args.output_file;
    let num_dirs = dirs.len();
    let _src_base_dir = args.src_base;
    let cpu = args.cpu;
    let splat_config_glob = args.splat_config_glob;

    if num_dirs == 2 {
        do_ordered_compare(dirs, threshold, cpu);
    } else {
        do_dups_report(output_file, threshold, cpu, splat_config_glob);
    }
}

fn levenshtein_similarity(s1: &[u8], s2: &[u8]) -> f64 {
    let len1 = s1.len();
    let len2 = s2.len();
    let mut dp = vec![vec![0; len2 + 1]; len1 + 1];

    for i in 0..=len1 {
        dp[i][0] = i;
    }

    for j in 0..=len2 {
        dp[0][j] = j;
    }

    for (i, x) in s1.iter().enumerate() {
        for (j, y) in s2.iter().enumerate() {
            dp[i + 1][j + 1] = if x == y {
                dp[i][j]
            } else {
                dp[i][j].min(dp[i][j + 1]).min(dp[i + 1][j]) + 1
            };
        }
    }

    let max_len = len1.max(len2) as f64;
    let result = (max_len - dp[len1][len2] as f64) / max_len;
    result
}

fn process_asm_directory(dir: &str, files: &mut Vec<DupsFile>, cpu: Cpu) {
    let mut funcs = Vec::new();
    process_directory(&dir, &mut funcs, cpu);

    // sort functions by vram address
    funcs.sort_by_key(|function| {
        function
            .ops
            .first()
            .map_or(u64::MAX, |instr| instr.vram_addr)
    });

    files.push(DupsFile {
        name: dir.to_string(),
        funcs: funcs.clone(),
    });
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_pairs_from_splat_glob() {
        let temp_root = std::env::temp_dir().join(format!("dups-test-{}", std::process::id()));
        let config_dir = temp_root.join("config");
        let asm_dir = temp_root.join("asm/test/overlay/matchings");
        fs::create_dir_all(&config_dir).unwrap();
        fs::create_dir_all(&asm_dir).unwrap();
        let canonical_temp_root = temp_root.canonicalize().unwrap();

        let splat_config = config_dir.join("splat.test.overlay.yaml");
        fs::write(
            &splat_config,
            "options:\n  basename: test\n  asm_path: asm/test/overlay\n  src_path: src/st/test\n",
        )
        .unwrap();

        let pattern = config_dir.join("splat.test.*.yaml");
        let pairs = pairs_from_splat_glob(&pattern.to_string_lossy()).unwrap();
        assert_eq!(pairs.len(), 1);
        assert_eq!(
            pairs[0].asm_dir,
            canonical_temp_root
                .join("asm/test/overlay/matchings")
                .to_string_lossy()
        );
        assert_eq!(
            pairs[0].src_dir,
            canonical_temp_root.join("src/st/test").to_string_lossy()
        );
        assert_eq!(pairs[0].overlay_name, "TEST");

        fs::remove_dir_all(&temp_root).unwrap();
    }

    #[test]
    fn test_display_asm_path() {
        assert_eq!(
            display_asm_path("/test/path/asm/us/boss/bo0/matchings/test.s"),
            "asm/us/boss/bo0/matchings/test.s"
        );
        assert_eq!(
            display_asm_path("../../asm/us/st/nz0/nonmatchings/test.s"),
            "asm/us/st/nz0/nonmatchings/test.s"
        );
    }

    // two equal strings
    #[test]
    fn test_levenshtein_similarity_1() {
        let s1 = "hello".as_bytes();
        let s2 = "hello".as_bytes();
        let similarity = levenshtein_similarity(s1, s2);
        assert_eq!(similarity, 1.0);
    }

    // almost the same (swap)
    #[test]
    fn test_levenshtein_similarity_09() {
        let s1 = "hello hello hello".as_bytes();
        let s2 = "hello hello hellu".as_bytes();
        let similarity = levenshtein_similarity(s1, s2);
        assert!(similarity >= 0.9);
        assert!(similarity < 1.0);
    }

    // almost the same (insertion)
    #[test]
    fn test_levenshtein_similarity_09_2() {
        let s1 = "hello hello hello".as_bytes();
        let s2 = "hello hell o hello".as_bytes();
        let similarity = levenshtein_similarity(s1, s2);
        assert!(similarity >= 0.9);
        assert!(similarity < 1.0);
    }

    // totally different
    #[test]
    fn test_levenshtein_similarity_0() {
        let s1 = "hello".as_bytes();
        let s2 = "world".as_bytes();
        let similarity = levenshtein_similarity(s1, s2);
        assert_eq!(similarity, 0.2);
    }

    // INCLUDE_ASM on a single line
    #[test]
    fn test_process_buffer_for_include_asm() {
        let file_content = r#"INCLUDE_ASM("foo/bar/do_something", DoSomething);

INCLUDE_ASM("foo/bar/do_something", DoSomethingElse);"#;

        let result = process_buffer_for_include_asm(file_content, "test.c");

        assert_eq!(result.len(), 2);
        assert_eq!(
            result[0],
            IncludeAsmEntry {
                line: r#"INCLUDE_ASM("foo/bar/do_something", DoSomething);"#.to_string(),
                path: "test.c".to_string(),
                asm_path: "../../asm/us/foo/bar/do_something/DoSomething.s".to_string(),
            }
        );

        assert_eq!(
            result[1],
            IncludeAsmEntry {
                line: r#"INCLUDE_ASM("foo/bar/do_something", DoSomethingElse);"#.to_string(),
                path: "test.c".to_string(),
                asm_path: "../../asm/us/foo/bar/do_something/DoSomethingElse.s".to_string(),
            }
        );
    }

    // INCLUDE_ASM lint formatted to concurrent lines
    #[test]
    fn test_process_buffer_for_include_asm_with_multiline() {
        let file_content = r#"INCLUDE_ASM("foo/bar/do_something", DoSomething);

INCLUDE_ASM(
    "foo/bar/do_something", DoSomethingWithSomethingElse);"#;

        let result = process_buffer_for_include_asm(file_content, "test_multiline.c");

        assert_eq!(result.len(), 2);
        assert_eq!(
            result[0],
            IncludeAsmEntry {
                line: r#"INCLUDE_ASM("foo/bar/do_something", DoSomething);"#.to_string(),
                path: "test_multiline.c".to_string(),
                asm_path: "../../asm/us/foo/bar/do_something/DoSomething.s".to_string(),
            }
        );
        assert_eq!(
            result[1],
            IncludeAsmEntry {
                line: r#"INCLUDE_ASM(     "foo/bar/do_something", DoSomethingWithSomethingElse);"#
                    .to_string(),
                path: "test_multiline.c".to_string(),
                asm_path: "../../asm/us/foo/bar/do_something/DoSomethingWithSomethingElse.s"
                    .to_string(),
            }
        );
    }
}
