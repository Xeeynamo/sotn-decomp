use std::collections::BTreeMap;
use std::fs::{self, File};
use std::io::{self, BufRead, BufReader};
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
    let mut lines = Vec::new();
    let mut lint_passed = true;
    let mut diffs = BTreeMap::<usize, (String, String)>::new();

    let file = File::open(file_path).expect("Unable to open file");
    let reader = BufReader::new(file);
    
    for (i, line) in reader.lines().into_iter().enumerate() {
        let mut line = line.unwrap();
        let old = line.clone();

        if line.contains("sotn-lint-ignore") {
            lines.push(line);
            continue;
        }

        for transformer in transformers {
            line = match transformer.transform_line(&line) {
                Some(s) => {
                    if line != s {
                        diffs.insert(i, (old.clone(), line.clone()));
                    }
                    s
                },
                None => line,
            };
        }

        for linter in linters {
            let errors = linter.check_line(&line);

            for error in errors {
                println!("{file_path:?}:{i} \x1b[31m{error}\x1b[0m -> {line}");
                lint_passed = false;
            }
        }

        lines.push(line);
    }

    if !diffs.is_empty() {
        fs::write(file_path, lines.join("\n"))
            .expect("failed to write changed file");

        for (i, (old, new)) in diffs.iter() {
            println!("{file_path:?}:{i} {old} -> {new}");
        }
    }

    (diffs.len(), lint_passed)
}



fn collect_files(d: &Path) -> io::Result<Vec<PathBuf>> {
    let mut v = vec![];

    for entry in fs::read_dir(d)?.flatten() {
        let t = entry.file_type()?;
        let p = entry.path();
        if t.is_file() {
            if [Some("c"), Some("h")].contains(&p.extension().and_then(|ext| ext.to_str())) {
                v.push(p);
            }
            continue;
        }
        if t.is_dir() {
            if entry.file_name().to_str() != Some("mednafen") {
                v.extend_from_slice(&collect_files(&entry.path())?);
            }
            continue;
        }
        eprintln!("Unexpected path: {p:?}");
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
