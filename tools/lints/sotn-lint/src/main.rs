use std::fs::File;
use std::io::{BufRead, BufReader, Write};
use std::path::Path;
use std::process::ExitCode;

mod attackelement;
mod bit_flag_line_transformer;
mod c;
mod collider_effects;
mod blendmodes;
mod drawflags;
mod drawmodes;
mod einit;
mod enum_line_transformer;
mod enum_statement;
mod file_transformer;
mod fixed;
mod flags;
mod item_drops;
mod line_transformer;
mod linter;
mod palette_flag;
mod palette_indices;
mod player_status;
mod primitive_type;
mod relics;
mod rot;
mod sfx;
mod vram_flag;

use attackelement::AttackElementTransformer;
use blendmodes::BlendModeTransformer;
use collider_effects::ColliderEffectsTransformer;
use drawflags::DrawFlagsTransformer;
use drawmodes::DrawModeTransformer;
use einit::EInitTransformer;
use file_transformer::FileTransformer;
use fixed::FixedTransformer;
use flags::FlagsTransformer;
use item_drops::ItemDropsTransformer;
use line_transformer::LineTransformer;
use linter::EntityRangeLinter;
use linter::Linter;
use linter::LocalExternLinter;
use linter::RegexLinter;
use palette_flag::PaletteFlagTransformer;
use palette_indices::PaletteIndicesTransformer;
use player_status::PlayerStatusTransformer;
use primitive_type::PrimitiveTypeTransformer;
use rayon::prelude::*;
use relics::RelicsTransformer;
use rot::RotationTransformer;
use sfx::SfxLineTransformer;
use vram_flag::PlayerVramFlagTransformer;

fn transform_file(
    file_path: &str,
    file_transformers: &Vec<Box<dyn FileTransformer>>,
    transformers: &Vec<Box<dyn LineTransformer>>,
    linters: &Vec<Box<dyn Linter>>,
) -> (usize, bool) {
    let mut alterations = 0;
    let mut lines = Vec::new();
    let mut lint_passed = true;

    let file = File::open(file_path).expect("Unable to open file");
    let reader = BufReader::new(file);
    let original_lines: Vec<String> = reader.lines().map(|line| line.unwrap()).collect();

    // File transformers may change the number of lines, so they go first and
    // the line transformers work on their output.
    let mut restructured_lines = original_lines.clone();
    for transformer in file_transformers {
        restructured_lines = transformer.transform_file(Path::new(file_path), restructured_lines);
    }
    if restructured_lines != original_lines {
        alterations += 1;
        println!(
            "{}: {} lines -> {} lines",
            file_path,
            original_lines.len(),
            restructured_lines.len()
        );
    }

    for (i, line) in restructured_lines.iter().enumerate() {
        let mut line_str = line.clone();

        if !line_str.contains("sotn-lint-ignore") {
            for transformer in transformers {
                line_str = transformer.transform_line(&line_str);
            }

            for linter in linters {
                match linter.check_line(&line_str) {
                    Ok(_) => (),
                    Err(msg) => {
                        eprintln!(
                            "{}:{} \x1b[31m{}\x1b[0m -> {}",
                            file_path,
                            i + 1,
                            msg,
                            line_str
                        );
                        lint_passed = false;
                    }
                }
            }
        }

        lines.push(line_str);
    }

    if lines != original_lines {
        let mut file = File::create(file_path).expect("Unable to create file");
        for (i, line) in lines.iter().enumerate() {
            if lines[i] != restructured_lines[i] {
                alterations += 1;
                println!("{}:{} {} -> {}", file_path, i, restructured_lines[i], lines[i]);
            }
            writeln!(file, "{}", line).expect("Unable to write line to file");
        }
    }

    (alterations, lint_passed)
}

const SKIPPED_DIRS: [&str; 2] = ["mednafen", "saturn"];

fn process_directory(dir_path: &str) -> bool {
    let fixed_transformer = FixedTransformer;
    let relics_transformer = RelicsTransformer;
    let rotation_transformer = RotationTransformer;
    let draw_mode_transformer = DrawModeTransformer::new();
    let blend_mode_transformer = BlendModeTransformer::new();
    let flags_transformer = FlagsTransformer::new();
    let draw_flags_transformer = DrawFlagsTransformer::new();
    let primitive_type_transformer = PrimitiveTypeTransformer::new();
    let player_status_transformer = PlayerStatusTransformer::new();
    let attack_element_transformer = AttackElementTransformer::new();
    let vram_flag_transformer = PlayerVramFlagTransformer::new();

    let transformers: Vec<Box<dyn LineTransformer>> = vec![
        Box::new(fixed_transformer),
        Box::new(relics_transformer),
        Box::new(rotation_transformer),
        Box::new(ColliderEffectsTransformer::new()),
        Box::new(draw_mode_transformer),
        Box::new(blend_mode_transformer),
        Box::new(flags_transformer),
        Box::new(draw_flags_transformer),
        Box::new(primitive_type_transformer),
        Box::new(player_status_transformer),
        Box::new(attack_element_transformer),
        Box::new(vram_flag_transformer),
        Box::new(SfxLineTransformer::new()),
        Box::new(ItemDropsTransformer::new()),
        // PAL_FLAG must wrap the value before PaletteIndices can name it
        Box::new(PaletteFlagTransformer),
        Box::new(PaletteIndicesTransformer::new()),
    ];

    let file_transformers: Vec<Box<dyn FileTransformer>> = vec![Box::new(EInitTransformer::new())];

    let linters: Vec<Box<dyn Linter>> = vec![
        Box::new(EntityRangeLinter),
        Box::new(LocalExternLinter),
        Box::new(RegexLinter::new("Static String Reference", r"FntPrint\(D_")),
        Box::new(RegexLinter::new(
            "CreateEntity With Int",
            r"Create[^(]*Entity[^(]*\((?:(?:0x[0-9A-F]+)|(?:[0-9]+)),",
        )),
        Box::new(RegexLinter::new(
            "ILLEGAL Entity Extension",
            r"ext\.ILLEGAL",
        )),
    ];

    let entries = std::fs::read_dir(dir_path).expect("Unable to read directory");

    entries
        .par_bridge()
        .fold(
            || true,
            |mut lint_passed, entry| {
                if let Ok(entry) = entry {
                    let item_path = entry.path();
                    if item_path.is_file()
                        && (item_path.to_string_lossy().ends_with(".c")
                            || item_path.to_string_lossy().ends_with(".h"))
                    {
                        let (_, passed) = transform_file(
                            &item_path.to_string_lossy(),
                            &file_transformers,
                            &transformers,
                            &linters,
                        );

                        lint_passed &= passed
                    } else if item_path.is_dir() {
                        let name = item_path.file_name().unwrap().to_string_lossy();
                        if !SKIPPED_DIRS.contains(&name.as_ref()) {
                            lint_passed &= process_directory(&item_path.to_string_lossy());
                        }
                    }
                }
                lint_passed
            },
        )
        .reduce(|| true, |a, b| a & b)
}

fn main() -> ExitCode {
    if process_directory(&std::env::args().nth(1).expect("Missing directory path")) {
        ExitCode::SUCCESS
    } else {
        ExitCode::from(1)
    }
}
