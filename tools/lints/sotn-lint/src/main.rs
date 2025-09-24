use std::fs::File;
use std::io::{BufRead, BufReader, BufWriter, Write};
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

use attackelement::AttackElementTransformer;
use collider_effects::ColliderEffectsTransformer;
use drawflags::DrawFlagsTransformer;
use drawmodes::DrawModeTransformer;
use fixed::FixedTransformer;
use flags::FlagsTransformer;
use line_transformer::LineTransformer;
use linter::Linter;
use linter::LocalExternLinter;
use linter::RegexLinter;
use player_status::PlayerStatusTransformer;
use primitive_type::PrimitiveTypeTransformer;
use rayon::prelude::*;
use relics::RelicsTransformer;

use crate::linter::{Gentries, ObjectRangeLinker};

fn transform_file(file_path: &str, transformers: &[&dyn LineTransformer], linters: &[&dyn Linter]) ->
(usize, bool) {
    let mut alterations = 0;
    let mut lines = Vec::new();
    let mut original_lines = Vec::new();
    let mut i = 0;
    let mut lint_passed = true;

    let file = File::open(file_path).expect("Unable to open file");
    let reader = BufReader::new(file);

    let mut has_changes = false;
    for line in reader.lines() {
        i += 1;
        let mut line_str = line.unwrap();
        original_lines.push(line_str.clone());

        if !line_str.contains("sotn-lint-ignore") {
            for transformer in transformers {
                line_str = match transformer.transform_line(&line_str) {
                    Some(s) => {
                        if line_str != s {
                            has_changes = true;
                        }

                        s
                    },
                    None => line_str,
                };
            }

            for linter in linters {
                match linter.check_line(&line_str) {
                    Ok(_) => (),
                    Err(msg) => {
                        println!("{file_path}:{i} \x1b[31m{msg}\x1b[0m -> {line_str}");
                        lint_passed = false;
                    }
                }
            }
        }

        lines.push(line_str);
    }

    if has_changes {
        let file = File::create(file_path).expect("Unable to create file");
        let mut file = BufWriter::new(file);
        for (i, line) in lines.iter().enumerate() {
            if lines[i] != original_lines[i] {
                alterations += 1;
                println!("{file_path}:{i} {} -> {}", original_lines[i], lines[i]);
            }
            writeln!(file, "{line}").expect("Unable to write line to file");
        }
    }

    (alterations, lint_passed)
}

fn process_directory(dir_path: &str) -> bool {
    let fixed_transformer = FixedTransformer;
    let relics_transformer = RelicsTransformer;
    let draw_mode_transformer = DrawModeTransformer::default();
    let flags_transformer = FlagsTransformer::default();
    let draw_flags_transformer = DrawFlagsTransformer::default();
    let primitive_type_transformer = PrimitiveTypeTransformer::default();
    let player_status_transformer = PlayerStatusTransformer::default();
    let attack_element_transformer = AttackElementTransformer::default();
    let collider_effects_transform = ColliderEffectsTransformer::default();

    let transformers: &[&dyn LineTransformer] = &[
        &fixed_transformer,
        &relics_transformer,
        &collider_effects_transform,
        &draw_mode_transformer,
        &flags_transformer,
        &draw_flags_transformer,
        &primitive_type_transformer,
        &player_status_transformer,
        &attack_element_transformer,
    ];

    let g_entries = ObjectRangeLinker::<Gentries>::default();
    let regex= RegexLinter::new("Static String Reference", r"FntPrint\(D_");


    let linters: &[&dyn Linter] = &[
        &g_entries,
        &LocalExternLinter,
        &regex,
    ];

    let entries = std::fs::read_dir(dir_path).expect("Unable to read directory");

    entries.par_bridge().fold(|| true, |mut lint_passed, entry| {
        let Ok(entry) = entry else {
            return lint_passed;
        };
        let item_path = entry.path();

        let extension = item_path.extension().and_then(|s| s.to_str());
        if item_path.is_file() && [Some("c"), Some("h")].contains(&extension) {
            let (_, passed) = transform_file(&item_path.to_string_lossy(), transformers, linters);
            return lint_passed & passed;
        }

        if item_path.is_dir() && item_path.file_name().unwrap() != "mednafen" {
            lint_passed &= process_directory(&item_path.to_string_lossy());
            return lint_passed;
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
