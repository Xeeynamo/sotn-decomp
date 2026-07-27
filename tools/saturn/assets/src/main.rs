//! Saturn asset tool CLI
//!
//! Driven from tools/sotn-assets and config/assets.saturn.yaml

use clap::{Parser, Subcommand};
use saturn_assets::font;
use std::path::PathBuf;
use std::process::ExitCode;

#[derive(Parser)]
#[command(name = "saturn-assets", about, version)]
struct Cli {
    #[command(subcommand)]
    command: Command,
}

#[derive(Subcommand)]
enum Command {
    /// ASCII.FON / KANJI.FON glyph pixels
    #[command(subcommand)]
    Font(FontCommand),
}

#[derive(Subcommand)]
enum FontCommand {
    Extract {
        /// profile: ascii or kanji
        profile: String,
        /// original retail file path
        font_path: PathBuf,
        /// directory for atlas and json
        output_dir: PathBuf,
    },
    /// reassemble from json and atlas
    Rebuild { manifest: PathBuf, output: PathBuf },
    Verify {
        manifest: PathBuf,
        /// retail fon path
        font_path: PathBuf,
    },
}

fn run(cli: Cli) -> saturn_assets::Result<()> {
    match cli.command {
        Command::Font(FontCommand::Extract {
            profile,
            font_path,
            output_dir,
        }) => {
            let manifest = font::extract(&profile, &font_path, &output_dir)?;
            println!("{} glyphs -> {}", manifest.glyphs, output_dir.display());
        }
        Command::Font(FontCommand::Rebuild { manifest, output }) => {
            let data = font::rebuild(&manifest, &output)?;
            println!("wrote {} bytes -> {}", data.len(), output.display());
        }
        Command::Font(FontCommand::Verify {
            manifest,
            font_path,
        }) => {
            font::verify(&manifest, &font_path)?;
            println!("verify passed: exact retail match");
        }
    }
    Ok(())
}

fn main() -> ExitCode {
    if let Err(err) = run(Cli::parse()) {
        eprintln!("error: {err}");
        return ExitCode::FAILURE;
    }
    ExitCode::SUCCESS
}
