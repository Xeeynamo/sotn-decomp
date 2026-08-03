//! Saturn asset tool CLI
//!
//! Driven from tools/sotn-assets and config/assets.saturn.yaml

use clap::{Parser, Subcommand};
use saturn_assets::{audio, font, weapon};
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
    /// SD*.PCM music, mono and voice streams
    #[command(subcommand)]
    Audio(AudioCommand),
    /// MAR_W / RIC_W / ALC_W secondary player CHR
    #[command(subcommand)]
    Weapon(WeaponCommand),
}

#[derive(Subcommand)]
enum WeaponCommand {
    /// Export the linear atlas and, with a PRG, the per-image sprite PNGs
    Extract {
        /// Character profile: maria, richter or alucard
        character: String,
        /// The retail MAR_W.CHR / RIC_W.CHR / ALC_W.CHR
        chr_path: PathBuf,
        output_dir: PathBuf,
        /// The player PRG whose sprite tables partition this CHR. Without it
        /// only the whole-file atlas is written.
        #[arg(long)]
        prg: Option<PathBuf>,
    },
    /// Reassemble the CHR from the atlas and the sprite PNGs
    Rebuild { manifest: PathBuf, output: PathBuf },
    /// Require a byte-identical no-edit rebuild
    Verify {
        manifest: PathBuf,
        /// The retail CHR to compare against
        chr_path: PathBuf,
    },
}

#[derive(Subcommand)]
enum AudioCommand {
    Extract {
        /// codec: stereo, mono or voice
        codec: String,
        /// original retail file path
        source_path: PathBuf,
        /// directory for wav and json
        output_dir: PathBuf,
        /// wav playback rate, not stored on disc for mono and voice
        #[arg(long, default_value_t = saturn_assets::adpcm::SAMPLE_RATE)]
        rate: u32,
    },
    /// re-encode from json and wav
    Rebuild { manifest: PathBuf, output: PathBuf },
    Verify {
        manifest: PathBuf,
        /// retail pcm path
        source_path: PathBuf,
    },
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
        Command::Audio(AudioCommand::Extract {
            codec,
            source_path,
            output_dir,
            rate,
        }) => {
            let manifest = audio::extract(&codec, &source_path, &output_dir, rate)?;
            println!("{} samples -> {}", manifest.samples, output_dir.display());
        }
        Command::Audio(AudioCommand::Rebuild { manifest, output }) => {
            let data = audio::rebuild(&manifest, &output)?;
            println!("wrote {} bytes -> {}", data.len(), output.display());
        }
        Command::Audio(AudioCommand::Verify {
            manifest,
            source_path,
        }) => {
            audio::verify(&manifest, &source_path)?;
            println!("verify passed: exact retail match");
        }
        Command::Weapon(WeaponCommand::Extract {
            character,
            chr_path,
            output_dir,
            prg,
        }) => {
            let manifest = weapon::extract(&character, &chr_path, prg.as_deref(), &output_dir)?;
            let images: usize = manifest.packages.iter().map(|p| p.images.len()).sum();
            println!(
                "{} bytes, {} package(s), {images} image record(s) -> {}",
                manifest.source.size,
                manifest.packages.len(),
                output_dir.display()
            );
        }
        Command::Weapon(WeaponCommand::Rebuild { manifest, output }) => {
            let data = weapon::rebuild(&manifest, &output)?;
            println!("wrote {} bytes -> {}", data.len(), output.display());
        }
        Command::Weapon(WeaponCommand::Verify { manifest, chr_path }) => {
            weapon::verify(&manifest, &chr_path)?;
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
