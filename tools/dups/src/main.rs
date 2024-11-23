use regex::Regex;
use std::fs;
use std::fs::File;
use std::io::BufReader;
use std::io::Read;
use std::io::Write;
use std::process::exit;

mod levenshtein_hashmap;
mod types;
use levenshtein_hashmap::LevenshteinHashMap;
use types::{DupsFile, Function, Instruction};
// parse .s file to get instructions and function name
fn parse_instructions(input: &str, dir: &str, file: &str) -> Function {
    let mut instructions = Vec::new();
    let mut func_name = "";

    for line in input.lines() {
        let parts: Vec<&str> = line.split_whitespace().collect();

        // find the function name
        if parts.len() == 2 {
            if parts[0] == "glabel" {
                func_name = parts[1];
            }
        }

        if parts.len() < 3 {
            continue; // Skip lines that don't have enough parts
        }

        if let Ok(file_addr) = u64::from_str_radix(parts[1], 16) {
            if let Ok(vram_addr) = u64::from_str_radix(parts[2], 16) {
                if let Ok(op) = u32::from_str_radix(parts[3], 16) {
                    // splat's output for the instruction is apparently little-endian
                    let reversed_num = ((op >> 24) & 0xFF)
                        | (((op >> 16) & 0xFF) << 8)
                        | (((op >> 8) & 0xFF) << 16)
                        | ((op & 0xFF) << 24);

                    // if the file address, vram address, and instruction parsed, add it
                    let instruction = Instruction {
                        file_addr,
                        vram_addr,
                        op: reversed_num,
                    };

                    instructions.push(instruction);
                }
            }
        }
    }

    // use the 'op' part of the instruction to find duplicates
    // (bits above the 26th)
    let key: Vec<u8> = instructions
        .iter()
        .map(|num| (num.op >> 26) as u8)
        .collect();

    Function {
        ops: instructions,
        name: func_name.to_string(),
        key: key,
        dir: dir.to_string(),
        file: file.to_string(),
        similarity: 0.0,
        decompiled: file.contains("/matchings/"),
    }
}

fn process_directory(dir_path: &str, funcs: &mut Vec<Function>) {
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

                        let func =
                            parse_instructions(&buffer, &dir_path, &item_path.to_string_lossy());

                        // jr $ra, nop
                        let is_null = func.ops.len() == 2
                            && func.ops[0].op == 0x03E00008
                            && func.ops[1].op == 0x00000000;
                        if !is_null {
                            funcs.push(func.clone());
                        }
                    } else if item_path.is_dir() {
                        process_directory(&item_path.to_string_lossy(), funcs);
                    }
                }
            });
        }
        Err(error) => {
            eprintln!("Unable to read directory: {}", error);
            println!("Directory path: {}", dir_path);
            exit(1);
        }
    }
}

use clap::Parser;

#[derive(Parser, Debug)]
#[command(
    author,
    version,
    about,
    long_about = "\n
Finds duplicates in two asm directories and prints them out in order to identify patterns

Usage:

Do a 2-way compare with ordering
cargo run --release -- --dir ../../asm/us/st/nz0/nonmatchings/ --dir ../../asm/us/st/np3/nonmatchings/ --threshold .94

Clustering report for all overlays
cargo run --release -- --threshold .94 --output-file output.txt
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
                process_directory_for_include_asm(&item_path.to_string_lossy());
            }
        }
    });
    output
}

fn process_buffer_for_include_asm(file_content: &str, file_path: &str) -> Vec<IncludeAsmEntry> {
    let re = Regex::new("INCLUDE_ASM\\((?:\\s+)?\"([^\"]*)\", ([^)]*)\\)").unwrap();
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
                let (full, [asm_dir, asm_file]) = captures.extract();
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

fn do_dups_report(output_file: Option<String>, threshold: f64) {
    // full dups report
    let mut hash_map = LevenshteinHashMap::new(threshold);

    let mut files = Vec::new();

    let pairs: Vec<SrcAsmPair> = vec![
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/boss/mar/matchings/"),
            src_dir: String::from("../../src/boss/mar/"),
            overlay_name: String::from("MAR"),
            include_asm: get_all_include_asm("../../src/boss/mar/"),
            path_matcher: "/mar/".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/boss/rbo3/matchings/"),
            src_dir: String::from("../../src/boss/rbo3"),
            overlay_name: String::from("RBO3"),
            include_asm: get_all_include_asm("../../src/boss/rbo3"),
            path_matcher: "/rbo3/".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/dra/matchings/"),
            src_dir: String::from("../../src/dra/"),
            overlay_name: String::from("DRA"),
            include_asm: get_all_include_asm("../../src/dra/"),
            path_matcher: "/dra/".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/main/matchings/"),
            src_dir: String::from("../../src/main/"),
            overlay_name: String::from("MAIN"),
            include_asm: get_all_include_asm("../../src/main/"),
            path_matcher: "/main/".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/ric/matchings/"),
            src_dir: String::from("../../src/ric/"),
            overlay_name: String::from("RIC"),
            include_asm: get_all_include_asm("../../src/ric/"),
            path_matcher: "/ric/".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/servant/tt_000/matchings/"),
            src_dir: String::from("../../src/servant/tt_000"),
            overlay_name: String::from("TT_000"),
            include_asm: get_all_include_asm("../../src/servant/tt_000"),
            path_matcher: "/tt_000/".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/servant/tt_001/matchings/"),
            src_dir: String::from("../../src/servant/tt_001"),
            overlay_name: String::from("TT_001"),
            include_asm: get_all_include_asm("../../src/servant/tt_001"),
            path_matcher: "/tt_001/".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/servant/tt_002/matchings/"),
            src_dir: String::from("../../src/servant/tt_002"),
            overlay_name: String::from("TT_002"),
            include_asm: get_all_include_asm("../../src/servant/tt_002"),
            path_matcher: "/tt_002/".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/servant/tt_003/matchings/"),
            src_dir: String::from("../../src/servant/tt_003"),
            overlay_name: String::from("TT_003"),
            include_asm: get_all_include_asm("../../src/servant/tt_003"),
            path_matcher: "/tt_003/".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/servant/tt_004/matchings/"),
            src_dir: String::from("../../src/servant/tt_004"),
            overlay_name: String::from("TT_004"),
            include_asm: get_all_include_asm("../../src/servant/tt_004"),
            path_matcher: "/tt_004/".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/st/cen/matchings/"),
            src_dir: String::from("../../src/st/cen/"),
            overlay_name: String::from("CEN"),
            include_asm: get_all_include_asm("../../src/st/cen/"),
            path_matcher: "st/cen".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/st/dre/matchings/"),
            src_dir: String::from("../../src/st/dre/"),
            overlay_name: String::from("DRE"),
            include_asm: get_all_include_asm("../../src/st/dre/"),
            path_matcher: "st/dre".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/st/mad/matchings/"),
            src_dir: String::from("../../src/st/mad/"),
            overlay_name: String::from("MAD"),
            include_asm: get_all_include_asm("../../src/st/mad/"),
            path_matcher: "st/mad".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/st/no0/matchings/"),
            src_dir: String::from("../../src/st/no0/"),
            overlay_name: String::from("NO0"),
            include_asm: get_all_include_asm("../../src/st/no0/"),
            path_matcher: "st/no0".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/st/no3/matchings/"),
            src_dir: String::from("../../src/st/no3/"),
            overlay_name: String::from("NO3"),
            include_asm: get_all_include_asm("../../src/st/no3/"),
            path_matcher: "st/no3".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/st/np3/matchings/"),
            src_dir: String::from("../../src/st/np3/"),
            overlay_name: String::from("NP3"),
            include_asm: get_all_include_asm("../../src/st/np3/"),
            path_matcher: "st/np3".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/st/nz0/matchings/"),
            src_dir: String::from("../../src/st/nz0/"),
            overlay_name: String::from("NZ0"),
            include_asm: get_all_include_asm("../../src/st/nz0/"),
            path_matcher: "st/nz0".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/st/rwrp/matchings/"),
            src_dir: String::from("../../src/st/rwrp/"),
            overlay_name: String::from("RWRP"),
            include_asm: get_all_include_asm("../../src/st/rwrp/"),
            path_matcher: "st/rwrp".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/st/sel/matchings/"),
            src_dir: String::from("../../src/st/sel/"),
            overlay_name: String::from("SEL"),
            include_asm: get_all_include_asm("../../src/st/sel/"),
            path_matcher: "st/sel".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/st/st0/matchings/"),
            src_dir: String::from("../../src/st/st0/"),
            overlay_name: String::from("ST0"),
            include_asm: get_all_include_asm("../../src/st/st0/"),
            path_matcher: "st/st0".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/st/wrp/matchings/"),
            src_dir: String::from("../../src/st/wrp/"),
            overlay_name: String::from("WRP"),
            include_asm: get_all_include_asm("../../src/st/wrp/"),
            path_matcher: "st/wrp".to_string(),
        },
        SrcAsmPair {
            asm_dir: String::from("../../asm/us/weapon/matchings/"),
            src_dir: String::from("../../src/weapon/"),
            overlay_name: String::from("WEAPON0"),
            include_asm: get_all_include_asm("../../src/weapon/"),
            path_matcher: "/weapon/".to_string(),
        },
    ];

    for pair in pairs.clone() {
        let dir = pair.asm_dir;
        process_asm_directory(&dir, &mut files);

        let nonmatchings = dir.replace("matchings", "nonmatchings");
        process_asm_directory(&nonmatchings, &mut files);
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
            println!("\t{} {}", func.name, func.ops.len());
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

    if let o_file = output_file.unwrap() {
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
                        function.file.strip_prefix("../../").unwrap()
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
                        function.similarity, function.decompiled, function.name, function.file
                    );
                }
            }
        }
    }
}

fn do_ordered_compare(dirs: Vec<String>, threshold: f64) {
    let mut files = Vec::new();

    for dir in dirs {
        let mut funcs = Vec::new();
        process_directory(&dir, &mut funcs);

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
        let mut has_dup = false;
        let mut dup_name = "";
        for pair in &pairs {
            if func_0.name == pair[0].name {
                has_dup = true;
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
    let src_base_dir = args.src_base;

    if num_dirs == 2 {
        do_ordered_compare(dirs, threshold);
    } else {
        do_dups_report(output_file, threshold);
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

fn process_asm_directory(dir: &str, files: &mut Vec<DupsFile>) {
    let mut funcs = Vec::new();
    process_directory(&dir, &mut funcs);

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
