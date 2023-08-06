use std::fs;
use std::io::Read;
use std::env::*;

#[derive(Clone)]
pub struct Function {
    name: String,
    ops: Vec<Instruction>,
    key: Vec<u8>,
}

#[derive(Clone)]
pub struct Instruction {
    file_addr: u64,
    vram_addr: u64,
    op: u32,
}

// parse .s file to get instructions and function name
fn parse_instructions(input: &str) -> Function {
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

                    // if the file address, vram address, and instruction parsed, add it
                    let instruction = Instruction {
                        file_addr,
                        vram_addr,
                        op,
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
    }
}

fn process_directory(dir_path: &str, funcs: &mut Vec<Function>) {
    let entries = std::fs::read_dir(dir_path).expect("Unable to read directory");

    entries.for_each(|entry| {
        if let Ok(entry) = entry {
            let item_path = entry.path();
            if item_path.is_file() && item_path.to_string_lossy().ends_with(".s") {
                println!("checking {:?}", item_path);

                let mut file = fs::File::open(item_path).unwrap();
                let mut buffer = String::new();
                file.read_to_string(&mut buffer).unwrap();

                let func = parse_instructions(&buffer);
                funcs.push(func.clone());
            } else if item_path.is_dir() {
                process_directory(&item_path.to_string_lossy(), funcs);
            }
        }
    });
}

struct File {
    name: String,
    funcs: Vec<Function>,
}

use clap::Parser;

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = "\n
Finds duplicates in two asm directories and prints them out in order to identify patterns

Usage:

make force_extract
cargo run --release -- --dir ../../asm/us/st/nz0/nonmatchings/ --dir ../../asm/us/st/np3/nonmatchings/ --threshold .94
")]

struct Args {
    /// Levenshtein similarity threshold
    #[arg(short, long)]
    threshold: f64,

    /// Directory to parse asm from (2 required)
    #[arg(short, long)]
    dir: Vec<String>,
}

fn main() {
    let args = Args::parse();

    let threshold = args.threshold;
    let dirs = args.dir;

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

        files.push(File {
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
                println!("{:<width$} | {:<width$} | {:<width$}", func_0.name, func_1.name, result, width = 40);
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
}
