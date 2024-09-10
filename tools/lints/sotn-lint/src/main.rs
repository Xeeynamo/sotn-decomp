use std::fs::File;
use std::io::{BufRead, BufReader, Write};

mod fixed;
mod line_transformer;
mod bit_flag_line_transformer;
mod relics;
mod drawmodes;
mod flags;
mod drawflags;

use line_transformer::LineTransformer;
use fixed::FixedTransformer;
use relics::RelicsTransformer;
use drawmodes::DrawModeTransformer;
use flags::FlagsTransformer;
use drawflags::DrawFlagsTransformer;
use rayon::prelude::*;

fn transform_file(file_path: &str, transformers: &Vec<Box<dyn LineTransformer>>) -> usize {
    let mut alterations = 0;
    let mut lines = Vec::new();
    let mut original_lines = Vec::new();

    let file = File::open(file_path).expect("Unable to open file");
    let reader = BufReader::new(file);
    for line in reader.lines() {
        let mut line_str = line.unwrap();
        original_lines.push(line_str.clone());

        for transformer in transformers {
            line_str = transformer.transform_line(&line_str);
        }

        lines.push(line_str);
    }

    if let Some(_) = original_lines.iter().zip(lines.iter()).position(|(a, b)| a != b) {

        let mut file = File::create(file_path).expect("Unable to create file");
        for (i, line) in lines.iter().enumerate() {
            if lines[i] != original_lines[i] {
                alterations += 1;
                println!("{}: {} -> {}", i, original_lines[i], lines[i]);
            }
            writeln!(file, "{}", line).expect("Unable to write line to file");
        }
    }

    alterations
}

fn process_directory(dir_path: &str) {
    let fixed_transformer = FixedTransformer;
    let relics_transformer = RelicsTransformer;
    let draw_mode_transformer = DrawModeTransformer::new();
    let flags_transformer = FlagsTransformer::new();
    let draw_flags_transformer = DrawFlagsTransformer::new();

    let transformers: Vec<Box<dyn LineTransformer>> = vec![
        Box::new(fixed_transformer),
        Box::new(relics_transformer),
        Box::new(draw_mode_transformer),
        Box::new(flags_transformer),
        Box::new(draw_flags_transformer),
        ];

    let entries = std::fs::read_dir(dir_path).expect("Unable to read directory");

    entries.par_bridge().for_each(|entry| {
        if let Ok(entry) = entry {
            let item_path = entry.path();
            if item_path.is_file() &&
                (item_path.to_string_lossy().ends_with(".c") ||
                 item_path.to_string_lossy().ends_with(".h")) {
                println!("checking {:?}", item_path);
                transform_file(&item_path.to_string_lossy(), &transformers);
            } else if item_path.is_dir() {
                if item_path.file_name().unwrap() != "mednafen" {
                    process_directory(&item_path.to_string_lossy());
                }
            }
        }
    });
}

fn main() {
    process_directory(&std::env::args().nth(1).expect("Missing directory path"));
}
