use std::fs::{self, File};
use std::io::{self, BufRead, BufReader, BufWriter, Write};
use std::path::{Path, PathBuf};
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

fn transform_file(file_path: &PathBuf, transformers: &[&dyn LineTransformer], linters: &[&dyn Linter]) -> (usize, bool) {
    let mut alterations = 0;
    let mut lines = Vec::new();
    let mut original_lines = Vec::new();
    let mut lint_passed = true;
    let mut file_changed = false;

    let file = File::open(file_path).expect("Unable to open file");
    let reader = BufReader::new(file);
    
    for (i, line) in reader.lines().into_iter().enumerate() {
        let mut line_str = line.unwrap();
        original_lines.push(line_str.clone());

        if !line_str.contains("sotn-lint-ignore") {
            for transformer in transformers {
                line_str = match transformer.transform_line(&line_str) {
                    Some(s) => {
                        if line_str != s {
                            file_changed = true;
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
                        println!("{file_path:?}:{i} \x1b[31m{msg}\x1b[0m -> {line_str}");
                        lint_passed = false;
                    }
                }
            }
        }

        lines.push(line_str);
    }
    if file_changed {
        let file = File::create(file_path).expect("Unable to create file");
        let mut file = BufWriter::new(file);
        for (i, line) in lines.iter().enumerate() {
            if lines[i] != original_lines[i] {
                alterations += 1;
                println!("{file_path:?}:{i} {} -> {}", original_lines[i], lines[i]);
            }
            writeln!(file, "{line}").expect("Unable to write line to file");
        }
    }

    (alterations, lint_passed)
}



fn collect_files(d: &Path) -> io::Result<Vec<PathBuf>> {
    let mut v = vec![];
    for f in fs::read_dir(d)?.flatten() {
        let t = f.file_type()?;
        let p = f.path();
        if t.is_file() {
            if [Some("c"), Some("h")].contains(&p.extension().and_then(|ext| ext.to_str())) {
                v.push(p);
            }
            continue;
        }
        if t.is_dir() {
            if f.file_name().to_str() != Some("mednafen") {
                v.extend_from_slice(&collect_files(&f.path())?);
            }
            continue;
        }
        eprintln!("Unexpected path: {f:?}");
    }
    Ok(v)
}
fn run(dir: &str) -> bool {

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

    collect_files(&Path::new(dir))
        .expect("failed to find files")
        .par_iter()
        .map(|file| {
            let (_, passed) = transform_file(file, transformers, linters);
            passed
        })
        .reduce(|| true, |a, b| a & b)
}


fn main() -> ExitCode {
    if run(&std::env::args().nth(1).expect("Missing directory path")) {
        ExitCode::SUCCESS
    } else {
        ExitCode::from(1)
    }
}
