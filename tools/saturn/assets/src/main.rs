//! Saturn asset tool CLI
//!
//! Driven from tools/sotn-assets and config/assets.saturn.yaml

use clap::{Parser, Subcommand};
use saturn_assets::{audio, bitmap, familiar, font, player, weapon};
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
    /// T_BAT / T_DEVIL / T_FAIRY / ... familiar CHR
    #[command(subcommand)]
    Familiar(FamiliarCommand),
    /// Packed 4bpp castle-map bitmaps in an overlay or SUB_DISP.MAP
    #[command(subcommand)]
    Bitmap(BitmapCommand),
    #[command(subcommand)]
    Player(PlayerCommand),
}

#[derive(Subcommand)]
enum PlayerCommand {
    Extract {
        player: String,
        prg_path: PathBuf,
        chr_path: PathBuf,
        output_dir: PathBuf,
    },
    Rebuild {
        manifest: PathBuf,
        chr_path: PathBuf,
        output: PathBuf,
    },
    Verify {
        manifest: PathBuf,
        chr_path: PathBuf,
    },
    GenerateHeaders {
        manifest: PathBuf,
        chr_path: PathBuf,
        directory_header: PathBuf,
        palette_header: PathBuf,
    },
    VerifyHeaders {
        manifest: PathBuf,
        chr_path: PathBuf,
        directory_header: PathBuf,
        palette_header: PathBuf,
    },
}

#[derive(Subcommand)]
enum BitmapCommand {
    /// Export the bitmap as an indexed PNG plus a manifest
    Extract {
        /// Bitmap profile: alucard-, maria-, richter-, or richter2-castle-map
        bitmap: String,
        /// The retail file containing the packed bitmap
        source_path: PathBuf,
        /// The matching retail main-player CHR carrying lookup table 67
        chr_path: PathBuf,
        output_dir: PathBuf,
    },
    /// Repack the PNG into the raw array bytes
    Rebuild { manifest: PathBuf, output: PathBuf },
    /// Require a byte-identical no-edit repack against the retail overlay
    Verify {
        manifest: PathBuf,
        /// The retail source file to compare against
        source_path: PathBuf,
    },
    /// Emit the array as C
    GenerateHeader { manifest: PathBuf, output: PathBuf },
    /// Require that regenerating reproduces a header already in the tree
    VerifyHeader { manifest: PathBuf, header: PathBuf },
}

#[derive(Subcommand)]
enum FamiliarCommand {
    /// Export the linear dump, the sprite PNGs and the contact sheet
    Extract {
        /// Familiar profile: bat, devil, devil2, fairy, fairy2, ghost, sword
        familiar: String,
        /// The retail T_*.PRG, which carries the image table and the CLUT
        prg_path: PathBuf,
        /// The retail T_*.CHR
        chr_path: PathBuf,
        output_dir: PathBuf,
    },
    /// Reassemble the CHR from the sprite PNGs and the linear dump
    Rebuild { manifest: PathBuf, output: PathBuf },
    /// Require a byte-identical no-edit rebuild
    Verify {
        manifest: PathBuf,
        /// The retail T_*.CHR to compare against
        chr_path: PathBuf,
    },
    /// Emit the image table, CLUT and resource wiring as C
    GenerateHeader { manifest: PathBuf, output: PathBuf },
    /// Require that regenerating reproduces a checked-in header exactly
    VerifyHeader { manifest: PathBuf, header: PathBuf },
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
        Command::Player(PlayerCommand::Extract {
            player,
            prg_path,
            chr_path,
            output_dir,
        }) => {
            let manifest = player::extract(&player, &prg_path, &chr_path, &output_dir)?;
            println!(
                "{} streams, arena 0x{:X}..0x{:X}, {} palette bank(s) -> {}",
                manifest.images.len(),
                manifest.arena_start,
                manifest.arena_end,
                manifest.palette.banks,
                output_dir.display()
            );
        }
        Command::Player(PlayerCommand::Rebuild {
            manifest,
            chr_path,
            output,
        }) => {
            let rebuilt = player::rebuild(&manifest, &chr_path, &output)?;
            println!(
                "wrote {} bytes ({} stream(s) recompressed) -> {}",
                rebuilt.chr.len(),
                rebuilt.changed,
                output.display()
            );
        }
        Command::Player(PlayerCommand::Verify { manifest, chr_path }) => {
            player::verify(&manifest, &chr_path)?;
            println!("verify passed: exact retail match");
        }
        Command::Player(PlayerCommand::GenerateHeaders {
            manifest,
            chr_path,
            directory_header,
            palette_header,
        }) => {
            player::generate_headers(&manifest, &chr_path, &directory_header, &palette_header)?;
            println!(
                "wrote {} + {}",
                directory_header.display(),
                palette_header.display()
            );
        }
        Command::Player(PlayerCommand::VerifyHeaders {
            manifest,
            chr_path,
            directory_header,
            palette_header,
        }) => {
            player::verify_headers(&manifest, &chr_path, &directory_header, &palette_header)?;
            println!("verify passed: the headers in the tree are what regenerate");
        }
        Command::Bitmap(BitmapCommand::Extract {
            bitmap,
            source_path,
            chr_path,
            output_dir,
        }) => {
            let manifest = bitmap::extract(&bitmap, &source_path, &chr_path, &output_dir)?;
            println!(
                "{}x{} ({} bytes) {} -> {}",
                manifest.width,
                manifest.height,
                manifest.source.size,
                manifest.symbol,
                output_dir.display()
            );
        }
        Command::Bitmap(BitmapCommand::Rebuild { manifest, output }) => {
            let data = bitmap::rebuild(&manifest, &output)?;
            println!("wrote {} bytes -> {}", data.len(), output.display());
        }
        Command::Bitmap(BitmapCommand::Verify {
            manifest,
            source_path,
        }) => {
            bitmap::verify(&manifest, &source_path)?;
            println!("verify passed: exact retail match");
        }
        Command::Bitmap(BitmapCommand::GenerateHeader { manifest, output }) => {
            let text = bitmap::generate_header(&manifest, &output)?;
            println!("{} lines -> {}", text.lines().count(), output.display());
        }
        Command::Bitmap(BitmapCommand::VerifyHeader { manifest, header }) => {
            bitmap::verify_header(&manifest, &header)?;
            println!("verify passed: the header in the tree is what regenerates");
        }
        Command::Familiar(FamiliarCommand::Extract {
            familiar,
            prg_path,
            chr_path,
            output_dir,
        }) => {
            let manifest = familiar::extract(&familiar, &prg_path, &chr_path, &output_dir)?;
            println!(
                "{} bytes, {} sprite(s), {} CLUT bank(s), resource 0x{:08X} -> {}",
                manifest.source.chr_size,
                manifest.images.len(),
                manifest.clut.banks,
                manifest.resource.address,
                output_dir.display()
            );
        }
        Command::Familiar(FamiliarCommand::Rebuild { manifest, output }) => {
            let data = familiar::rebuild(&manifest, &output)?;
            println!("wrote {} bytes -> {}", data.len(), output.display());
        }
        Command::Familiar(FamiliarCommand::Verify { manifest, chr_path }) => {
            familiar::verify(&manifest, &chr_path)?;
            println!("verify passed: exact retail match");
        }
        Command::Familiar(FamiliarCommand::GenerateHeader { manifest, output }) => {
            let text = familiar::generate_header(&manifest, &output)?;
            println!("{} lines -> {}", text.lines().count(), output.display());
        }
        Command::Familiar(FamiliarCommand::VerifyHeader { manifest, header }) => {
            familiar::verify_header(&manifest, &header)?;
            println!("verify passed: the checked-in header is what regenerates");
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
