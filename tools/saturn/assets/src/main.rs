//! Saturn asset tool CLI
//!
//! Driven from tools/sotn-assets and config/assets.saturn.yaml

use clap::{Parser, Subcommand};
use saturn_assets::{audio, bitmap, familiar, font, map, player, stage, weapon};
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
    #[command(subcommand)]
    Map(MapCommand),
    #[command(subcommand)]
    Stage(StageCommand),
    #[command(subcommand)]
    SpritePackage(SpritePackageCommand),
}

#[derive(Subcommand)]
enum StageCommand {
    Extract {
        prg_path: PathBuf,
        chr_path: PathBuf,
        output_dir: PathBuf,
        #[arg(long)]
        zero: Option<PathBuf>,
    },
    Rebuild { manifest: PathBuf, output: PathBuf },
    Verify {
        manifest: PathBuf,
        chr_path: PathBuf,
    },
    EntityHeader {
        prg_path: PathBuf,
        entity: usize,
        #[arg(value_parser = parse_hex_address)]
        frames: u32,
        prefix: String,
        output: PathBuf,
        #[arg(long)]
        zero: Option<PathBuf>,
    },
    VerifyEntityHeader {
        prg_path: PathBuf,
        entity: usize,
        #[arg(value_parser = parse_hex_address)]
        frames: u32,
        prefix: String,
        output: PathBuf,
        #[arg(long)]
        zero: Option<PathBuf>,
    },
}

fn parse_hex_address(text: &str) -> Result<u32, String> {
    let digits = text.strip_prefix("0x").or_else(|| text.strip_prefix("0X")).unwrap_or(text);
    u32::from_str_radix(digits, 16).map_err(|error| format!("{text:?} is not a hex address: {error}"))
}

#[derive(Subcommand)]
enum SpritePackageCommand {
    GenerateHeader {
        config: PathBuf,
        asset: String,
        output: PathBuf,
    },
    VerifyHeader {
        config: PathBuf,
        asset: String,
        output: PathBuf,
    },
}

#[derive(Subcommand)]
enum MapCommand {
    Extract {
        prg_path: PathBuf,
        map_path: PathBuf,
        output_dir: PathBuf,
    },
    Rebuild {
        manifest: PathBuf,
        map_path: PathBuf,
        output: PathBuf,
    },
    Verify {
        manifest: PathBuf,
        map_path: PathBuf,
    },
    Repack {
        manifest: PathBuf,
        map_path: PathBuf,
        output: PathBuf,
        layout: PathBuf,
    },
    GenerateHeaders {
        layout: PathBuf,
        prefix: String,
        layer_header: PathBuf,
        graphics_header: PathBuf,
    },
    VerifyHeaders {
        layout: PathBuf,
        prefix: String,
        layer_header: PathBuf,
        graphics_header: PathBuf,
    },
    Render {
        prg_path: PathBuf,
        map_path: PathBuf,
        output: PathBuf,
        #[arg(long, default_value_t = 0)]
        room: usize,
        #[arg(long, default_value_t = 0)]
        layer: usize,
        #[arg(long, conflicts_with = "composite")]
        whole_stage: bool,
        #[arg(long, conflicts_with = "whole_stage")]
        composite: bool,
    },
    RenderAll {
        input_dir: PathBuf,
        output_dir: PathBuf,
        #[arg(long)]
        force: bool,
    },
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
        Command::Stage(StageCommand::Extract {
            prg_path,
            chr_path,
            output_dir,
            zero,
        }) => {
            let manifest = stage::extract(&prg_path, &chr_path, zero.as_deref(), &output_dir)?;
            let shared = manifest
                .resources
                .iter()
                .filter(|resource| resource.region == stage::Region::Zero)
                .count();
            println!(
                "{} sprite resources ({shared} shared), {} images -> {}",
                manifest.resources.len(),
                manifest.images.len(),
                output_dir.display()
            );
        }
        Command::Stage(StageCommand::Rebuild { manifest, output }) => {
            let data = stage::rebuild(&manifest, &output)?;
            println!("wrote {} bytes -> {}", data.len(), output.display());
        }
        Command::Stage(StageCommand::Verify { manifest, chr_path }) => {
            stage::verify(&manifest, &chr_path)?;
            println!("verify passed: exact retail match");
        }
        Command::Stage(StageCommand::EntityHeader {
            prg_path,
            entity,
            frames,
            prefix,
            output,
            zero,
        }) => {
            let text = stage::generate_entity_header(
                &prg_path,
                zero.as_deref(),
                entity,
                frames,
                &prefix,
                &output,
            )?;
            println!("{} lines -> {}", text.lines().count(), output.display());
        }
        Command::Stage(StageCommand::VerifyEntityHeader {
            prg_path,
            entity,
            frames,
            prefix,
            output,
            zero,
        }) => {
            stage::verify_entity_header(&prg_path, zero.as_deref(), entity, frames, &prefix, &output)?;
            println!("verify passed: the header in the tree is what regenerates");
        }
        Command::SpritePackage(SpritePackageCommand::GenerateHeader { config, asset, output }) => {
            let text = stage::generate_package_header(&config, &asset, &output)?;
            println!("{} lines -> {}", text.lines().count(), output.display());
        }
        Command::SpritePackage(SpritePackageCommand::VerifyHeader { config, asset, output }) => {
            stage::verify_package_header(&config, &asset, &output)?;
            println!("verify passed: the header in the tree is what regenerates");
        }
        Command::Map(MapCommand::Extract {
            prg_path,
            map_path,
            output_dir,
        }) => {
            let manifest = map::extract(&prg_path, &map_path, &output_dir)?;
            println!(
                "{} rooms, {} streams (sub-stage {}) -> {}",
                manifest.tables.rooms,
                manifest.streams.len(),
                manifest.tables.substage,
                output_dir.display()
            );
        }
        Command::Map(MapCommand::Rebuild {
            manifest,
            map_path,
            output,
        }) => {
            let (data, changed) = map::rebuild(&manifest, &map_path, &output)?;
            println!(
                "wrote {} bytes ({changed} stream(s) recompressed) -> {}",
                data.len(),
                output.display()
            );
        }
        Command::Map(MapCommand::Verify { manifest, map_path }) => {
            map::verify(&manifest, &map_path)?;
            println!("verify passed: exact retail match");
        }
        Command::Map(MapCommand::Repack {
            manifest,
            map_path,
            output,
            layout,
        }) => {
            let result = map::repack(&manifest, &map_path, &output, &layout)?;
            let moved = result.streams.iter().filter(|entry| entry.moved).count();
            println!(
                "{} bytes, {} recompressed, {moved} moved -> {} + {}",
                result.map_size,
                result.changed,
                output.display(),
                layout.display()
            );
        }
        Command::Map(MapCommand::GenerateHeaders {
            layout,
            prefix,
            layer_header,
            graphics_header,
        }) => {
            map::generate_headers(&layout, &prefix, &layer_header, &graphics_header)?;
            println!(
                "wrote {} and {}",
                layer_header.display(),
                graphics_header.display()
            );
        }
        Command::Map(MapCommand::VerifyHeaders {
            layout,
            prefix,
            layer_header,
            graphics_header,
        }) => {
            map::verify_headers(&layout, &prefix, &layer_header, &graphics_header)?;
            println!("verify passed: the headers describe the MAP");
        }
        Command::Map(MapCommand::Render {
            prg_path,
            map_path,
            output,
            room,
            layer,
            whole_stage,
            composite,
        }) => {
            let (image, description) = if composite {
                (
                    saturn_assets::map_render::render_composite(&prg_path, &map_path)?,
                    "whole stage composite".to_string(),
                )
            } else if whole_stage {
                let (image, rooms) =
                    saturn_assets::map_render::render_stage_layer(&prg_path, &map_path, layer)?;
                (image, format!("whole stage layer {layer}: {rooms} rooms"))
            } else {
                let (image, tiles) =
                    saturn_assets::map_render::render_room(&prg_path, &map_path, room, layer)?;
                (
                    image,
                    format!("room {room} layer {layer}: {tiles} characters"),
                )
            };
            saturn_assets::image::write_rgba(&output, &image)?;
            println!(
                "rendered {description}, {}x{} -> {}",
                image.width,
                image.height,
                output.display()
            );
        }
        Command::Map(MapCommand::RenderAll {
            input_dir,
            output_dir,
            force,
        }) => {
            std::fs::create_dir_all(&output_dir)?;
            let jobs = saturn_assets::map_render::discover(&input_dir)?;
            if jobs.is_empty() {
                return Err(saturn_assets::Error::Format(format!(
                    "no renderable stage PRG/MAP pairs found in {}",
                    input_dir.display()
                )));
            }
            let total = jobs.len();
            let mut rendered = 0usize;
            let mut skipped = 0usize;
            let mut failures = Vec::new();
            for (index, job) in jobs.into_iter().enumerate() {
                let output = output_dir.join(format!("{}.png", job.name));
                let current = index + 1;
                let prefix = format!("[{current:02}/{total:02}] {}", job.name);
                if output.exists() && !force {
                    println!("{prefix}: skipped (already exists)");
                    skipped += 1;
                    continue;
                }
                match saturn_assets::map_render::render_composite(&job.prg, &job.map) {
                    Ok(image) => match saturn_assets::image::write_rgba(&output, &image) {
                        Ok(()) => {
                            println!("{prefix}: done ({}x{})", image.width, image.height);
                            rendered += 1;
                        }
                        Err(error) => failures.push(format!("{}: {error}", job.name)),
                    },
                    Err(error) => failures.push(format!("{}: {error}", job.name)),
                }
            }
            println!(
                "completed: {rendered} rendered, {skipped} skipped, {} failed; output: {}",
                failures.len(),
                output_dir.display()
            );
            if !failures.is_empty() {
                return Err(saturn_assets::Error::Format(failures.join("\n")));
            }
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
