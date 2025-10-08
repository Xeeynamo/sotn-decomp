use std::fs::File;
use std::io::{BufRead, BufReader, Write};
use std::process::ExitCode;

mod attackelement;
mod bit_flag_line_transformer;
mod collider_effects;
mod drawflags;
mod drawmodes;
mod enum_line_transformer;
mod enum_statement;
mod fixed;
mod flags;
mod line_transformer;
mod linter;
mod player_status;
mod primitive_type;
mod relics;
mod vram_flag;

use attackelement::AttackElementTransformer;
use collider_effects::ColliderEffectsTransformer;
use drawflags::DrawFlagsTransformer;
use drawmodes::DrawModeTransformer;
use fixed::FixedTransformer;
use flags::FlagsTransformer;
use line_transformer::LineTransformer;
use linter::Linter;
use linter::EntityRangeLinter;
use linter::LocalExternLinter;
use linter::RegexLinter;
use player_status::PlayerStatusTransformer;
use primitive_type::PrimitiveTypeTransformer;
use rayon::prelude::*;
use relics::RelicsTransformer;
use vram_flag::PlayerVramFlagTransformer;

fn transform_file(file_path: &str, transformers: &Vec<Box<dyn LineTransformer>>, linters: &Vec<Box<dyn Linter>>) ->
(usize, bool) {
    let mut alterations = 0;
    let mut lines = Vec::new();
    let mut original_lines = Vec::new();
    let mut i = 0;
    let mut lint_passed = true;

    let file = File::open(file_path).expect("Unable to open file");
    let reader = BufReader::new(file);
    for line in reader.lines() {
        i += 1;
        let mut line_str = line.unwrap();
        original_lines.push(line_str.clone());

        if !line_str.contains("sotn-lint-ignore") {
            for transformer in transformers {
                line_str = transformer.transform_line(&line_str);
            }

            for linter in linters {
                match linter.check_line(&line_str) {
                    Ok(_) => (),
                    Err(msg) => {
                        println!("{}:{} \x1b[31m{}\x1b[0m -> {}", file_path, i, msg, line_str);
                        lint_passed = false;
                    }
                }
            }
        }

        lines.push(line_str);
    }

    if let Some(_) = original_lines.iter().zip(lines.iter()).position(|(a, b)| a != b) {
        let mut file = File::create(file_path).expect("Unable to create file");
        for (i, line) in lines.iter().enumerate() {
            if lines[i] != original_lines[i] {
                alterations += 1;
                println!("{}:{} {} -> {}", file_path, i, original_lines[i], lines[i]);
            }
            writeln!(file, "{}", line).expect("Unable to write line to file");
        }
    }

    (alterations, lint_passed)
}

fn process_directory(dir_path: &str) -> bool {
    let fixed_transformer = FixedTransformer;
    let relics_transformer = RelicsTransformer;
    let draw_mode_transformer = DrawModeTransformer::new();
    let flags_transformer = FlagsTransformer::new();
    let draw_flags_transformer = DrawFlagsTransformer::new();
    let primitive_type_transformer = PrimitiveTypeTransformer::new();
    let player_status_transformer = PlayerStatusTransformer::new();
    let attack_element_transformer = AttackElementTransformer::new();
    let vram_flag_transformer = PlayerVramFlagTransformer::new();

    let transformers: Vec<Box<dyn LineTransformer>> = vec![
        Box::new(fixed_transformer),
        Box::new(relics_transformer),
        Box::new(ColliderEffectsTransformer::new()),
        Box::new(draw_mode_transformer),
        Box::new(flags_transformer),
        Box::new(draw_flags_transformer),
        Box::new(primitive_type_transformer),
        Box::new(player_status_transformer),
        Box::new(attack_element_transformer),
        Box::new(vram_flag_transformer)
        ];

    let linters: Vec<Box<dyn Linter>> = vec![
        Box::new(EntityRangeLinter),
        Box::new(LocalExternLinter),
        Box::new(RegexLinter::new("Static String Reference", r"FntPrint\(D_")),
    ];

    let entries = std::fs::read_dir(dir_path).expect("Unable to read directory");

    entries.par_bridge().fold(|| true, |mut lint_passed, entry| {
        if let Ok(entry) = entry {
            let item_path = entry.path();
            if item_path.is_file() &&
                (item_path.to_string_lossy().ends_with(".c") ||
                 item_path.to_string_lossy().ends_with(".h")) {
                let (_, passed) = transform_file(&item_path.to_string_lossy(), &transformers, &linters);

                lint_passed &= passed
            } else if item_path.is_dir() {
                if item_path.file_name().unwrap() != "mednafen" {
                    lint_passed &= process_directory(&item_path.to_string_lossy());
                }
            }
        }
        lint_passed
    }).reduce(|| true, |a, b| a & b)
}

fn main() -> ExitCode {
    if process_directory(&std::env::args().nth(1).expect("Missing directory path")) {
        ExitCode::SUCCESS
    } else {
        ExitCode::from(1)
    }
}
