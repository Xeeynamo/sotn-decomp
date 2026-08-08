
use crate::image::{self, Indexed};
use crate::lzss;
use crate::sheet;
use crate::sprite::{display_palette, pack, unpack, PALETTE_BANK_SIZE};
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::path::{Path, PathBuf};

pub const FORMAT: &str = "sotn-saturn-player-chr";
pub const VERSION: u32 = 1;
pub const MANIFEST_NAME: &str = "manifest.json";
pub const CONTACT_NAME: &str = "contact.png";
pub const SPRITES_DIR: &str = "sprites";
pub const ENCODING: &str = "indexed4-linear-high-nibble-first";

pub const LOAD_ADDRESS: u32 = 0x060A_5000;
pub const DIRECTORY_POINTER: usize = 0x40;
pub const ARENA_END: usize = 0x2_0000;
pub const CHARACTER_UNIT: usize = 8;

pub struct HeaderSymbols {
    pub directory: &'static str,
    pub palette: &'static str,
}

#[derive(Clone, Copy)]
pub struct Profile {
    pub name: &'static str,
    pub prg: &'static str,
    pub chr: &'static str,
    pub image_table: u32,
    pub palette_table: u32,
    pub stream_entry_base: usize,
    pub header: Option<&'static HeaderSymbols>,
}

static MARIA_SYMBOLS: HeaderSymbols = HeaderSymbols {
    directory: "g_MariaPlayerGraphicsRecords",
    palette: "g_MariaPalette",
};
static RICHTER_SYMBOLS: HeaderSymbols = HeaderSymbols {
    directory: "g_RichterPlayerGraphicsRecords",
    palette: "g_RichterSpritePackage1Palette",
};

pub const PROFILES: &[Profile] = &[
    Profile {
        name: "maria",
        prg: "MARIA.PRG",
        chr: "MARIA.CHR",
        image_table: 0x060C_51A8,
        palette_table: 0x060C_398C,
        stream_entry_base: 0,
        header: Some(&MARIA_SYMBOLS),
    },
    Profile {
        name: "richter",
        prg: "RICHTER.PRG",
        chr: "RICHTER.CHR",
        image_table: 0x060C_12EC,
        palette_table: 0x060C_0240,
        stream_entry_base: 0,
        header: Some(&RICHTER_SYMBOLS),
    },
    Profile {
        name: "richter2",
        prg: "RICHTER2.PRG",
        chr: "RICHTER2.CHR",
        image_table: 0x060C_120C,
        palette_table: 0x060C_0240,
        stream_entry_base: 0,
        header: None,
    },
    Profile {
        name: "alucard",
        prg: "ALUCARD.PRG",
        chr: "ALUCARD.CHR",
        image_table: 0x060C_9990,
        palette_table: 0x060C_897C,
        stream_entry_base: 3,
        header: None,
    },
];

pub fn profile(name: &str) -> Result<&'static Profile> {
    PROFILES.iter().find(|p| p.name == name).ok_or_else(|| {
        let known: Vec<&str> = PROFILES.iter().map(|p| p.name).collect();
        Error::Format(format!(
            "unknown player {name:?}; known: {}",
            known.join(", ")
        ))
    })
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Source {
    pub chr: String,
    pub chr_size: usize,
    pub chr_sha256: String,
    pub prg: String,
    pub prg_size: usize,
    pub prg_sha256: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Directory {
    pub address: u32,
    pub prg_offset: usize,
    pub backing_base: u32,
    pub entry_base: usize,
    pub entries: usize,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Palette {
    pub address: u32,
    pub prg_offset: usize,
    pub count_and_flags: u16,
    pub banks: usize,
    pub words: Vec<String>,
    pub padding: Vec<String>,
}

impl Palette {
    pub fn values(&self) -> Result<Vec<u16>> {
        if self.banks * PALETTE_BANK_SIZE != self.words.len() {
            return Err(Error::Format(format!(
                "palette declares {} banks but carries {} words",
                self.banks,
                self.words.len()
            )));
        }
        parse_hex(&self.words)
    }

    fn display(&self) -> Option<Vec<u8>> {
        let values = self.values().ok()?;
        let bank: Vec<[u8; 3]> = values
            .iter()
            .take(PALETTE_BANK_SIZE)
            .map(|&word| crate::sprite::rgb555(word))
            .collect();
        display_palette(&[bank])
    }
}

fn parse_hex(words: &[String]) -> Result<Vec<u16>> {
    words
        .iter()
        .map(|word| {
            let digits = word.strip_prefix("0x").unwrap_or(word);
            u16::from_str_radix(digits, 16)
                .map_err(|e| Error::Format(format!("{word:?} is not a u16: {e}")))
        })
        .collect()
}

#[derive(Debug, Serialize, Deserialize)]
pub struct ImageRecord {
    pub index: usize,
    pub stored_width: u8,
    pub stored_height: u8,
    pub pixel_width: u32,
    pub pixel_height: u32,
    pub character_units: usize,
    pub allocation: usize,
    pub image_bytes: usize,
    pub stream_offset: usize,
    pub compressed_size: usize,
    pub sha256: String,
    pub file: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Manifest {
    pub format: String,
    pub version: u32,
    pub player: String,
    pub encoding: String,
    #[serde(skip_serializing_if = "Option::is_none", default)]
    pub contact: Option<String>,
    pub lead_bytes: usize,
    pub arena_start: usize,
    pub arena_end: usize,
    pub source: Source,
    pub directory: Directory,
    pub palette: Palette,
    pub images: Vec<ImageRecord>,
}

impl Manifest {
    pub fn profile(&self) -> Result<&'static Profile> {
        profile(&self.player)
    }
}

fn file_name(path: &Path) -> String {
    path.file_name()
        .map(|name| name.to_string_lossy().into_owned())
        .unwrap_or_else(|| path.display().to_string())
}

fn safe_join(root: &Path, relative: &str) -> Result<PathBuf> {
    let path = Path::new(relative);
    if path.is_absolute()
        || path
            .components()
            .any(|component| matches!(component, std::path::Component::ParentDir))
    {
        return Err(Error::Format(format!(
            "manifest contains an unsafe path: {relative}"
        )));
    }
    Ok(root.join(path))
}

fn read_u16(data: &[u8], at: usize) -> Result<u16> {
    data.get(at..at + 2)
        .map(|b| u16::from_be_bytes([b[0], b[1]]))
        .ok_or_else(|| Error::Format(format!("read past the end of the overlay at 0x{at:X}")))
}

fn read_u32(data: &[u8], at: usize) -> Result<u32> {
    data.get(at..at + 4)
        .map(|b| u32::from_be_bytes([b[0], b[1], b[2], b[3]]))
        .ok_or_else(|| Error::Format(format!("read past the end of the overlay at 0x{at:X}")))
}

struct TableEntry {
    stored_width: u8,
    stored_height: u8,
    character_units: usize,
}

fn read_image_table(prg: &[u8], profile: &Profile) -> Result<Vec<TableEntry>> {
    let base = (profile.image_table - LOAD_ADDRESS) as usize;
    let mut entries = Vec::new();
    loop {
        let at = base + entries.len() * 4;
        let dimensions = read_u16(prg, at)?;
        let units = read_u16(prg, at + 2)? as usize;
        let (stored_width, stored_height) = ((dimensions >> 8) as u8, (dimensions & 0xFF) as u8);
        entries.push(TableEntry {
            stored_width,
            stored_height,
            character_units: units,
        });
        if stored_width == 0 || stored_height == 0 {
            return Ok(entries);
        }
        if entries.len() > 4096 {
            return Err(Error::Format(format!(
                "{}: image table has no terminator",
                profile.name
            )));
        }
    }
}

fn read_palette(prg: &[u8], profile: &Profile) -> Result<Palette> {
    let offset = (profile.palette_table - LOAD_ADDRESS) as usize;
    let count_and_flags = read_u16(prg, offset)?;
    let banks = (count_and_flags & 0x3FFF) as usize;
    if banks == 0 {
        return Err(Error::Format(format!(
            "{}: palette object declares no banks",
            profile.name
        )));
    }
    let words = banks * PALETTE_BANK_SIZE;
    let values_end = offset + 2 + words * 2;
    let padding_len = (4 - ((2 + words * 2) % 4)) % 4;
    if values_end + padding_len > prg.len() {
        return Err(Error::Format(format!(
            "{}: palette object runs past the end of the PRG",
            profile.name
        )));
    }
    Ok(Palette {
        address: profile.palette_table,
        prg_offset: offset,
        count_and_flags,
        banks,
        words: (0..words)
            .map(|index| Ok(format!("0x{:04X}", read_u16(prg, offset + 2 + index * 2)?)))
            .collect::<Result<Vec<String>>>()?,
        padding: prg[values_end..values_end + padding_len]
            .iter()
            .map(|byte| format!("0x{byte:02X}"))
            .collect(),
    })
}

struct Decoded {
    entries: Vec<TableEntry>,
    allocations: Vec<Vec<u8>>,
    streams: Vec<(usize, usize)>,
    directory: Directory,
}

fn decode(prg: &[u8], chr: &[u8], profile: &Profile) -> Result<Decoded> {
    let directory_address = read_u32(prg, DIRECTORY_POINTER)?;
    let directory_offset = directory_address
        .checked_sub(LOAD_ADDRESS)
        .map(|o| o as usize)
        .filter(|&o| o + 8 <= prg.len())
        .ok_or_else(|| {
            Error::Format(format!(
                "{}: graphics directory 0x{directory_address:08X} is outside the PRG",
                profile.name
            ))
        })?;
    let backing_base = read_u32(prg, directory_offset)?;

    let entries = read_image_table(prg, profile)?;
    let count = entries.len() - 1; 

    let mut allocations = Vec::with_capacity(count);
    let mut streams = Vec::with_capacity(count);
    for index in 0..count {
        let entry = directory_offset + (profile.stream_entry_base + index) * 8;
        let address = read_u32(prg, entry)?;
        let size = read_u32(prg, entry + 4)? as usize;
        let offset = address
            .checked_sub(backing_base)
            .map(|o| o as usize)
            .filter(|&o| o + size <= chr.len())
            .ok_or_else(|| {
                Error::Format(format!(
                    "{}: image {index} stream 0x{address:08X} is outside the CHR",
                    profile.name
                ))
            })?;
        let allocation =
            (entries[index + 1].character_units - entries[index].character_units) * CHARACTER_UNIT;
        let decompressed = lzss::decompress(&chr[offset..offset + size]);
        if decompressed.len() != allocation {
            return Err(Error::Format(format!(
                "{}: image {index} decompresses to {} bytes but the image table \
                 allocates {allocation}",
                profile.name,
                decompressed.len()
            )));
        }
        allocations.push(decompressed);
        streams.push((offset, size));
    }

    Ok(Decoded {
        entries,
        allocations,
        streams,
        directory: Directory {
            address: directory_address,
            prg_offset: directory_offset,
            backing_base,
            entry_base: profile.stream_entry_base,
            entries: count,
        },
    })
}

pub fn extract(
    name: &str,
    prg_path: &Path,
    chr_path: &Path,
    output_dir: &Path,
) -> Result<Manifest> {
    let profile = profile(name)?;
    let prg = std::fs::read(prg_path)?;
    let chr = std::fs::read(chr_path)?;
    if chr.len() < ARENA_END {
        return Err(Error::Format(format!(
            "{} is {} bytes, shorter than the {ARENA_END:#X}-byte stream arena",
            chr_path.display(),
            chr.len()
        )));
    }
    let decoded = decode(&prg, &chr, profile)?;
    let palette = read_palette(&prg, profile)?;

    let arena_start = decoded.streams.iter().map(|&(o, _)| o).min().unwrap_or(0);
    let arena_end = decoded
        .streams
        .iter()
        .map(|&(o, s)| o + s)
        .max()
        .unwrap_or(0);
    if arena_end > ARENA_END {
        return Err(Error::Format(format!(
            "{}: streams end at 0x{arena_end:X}, past the arena",
            profile.name
        )));
    }
    if chr[arena_end..ARENA_END].iter().any(|&byte| byte != 0) {
        return Err(Error::Format(format!(
            "{}: arena slack at 0x{arena_end:X}..0x{ARENA_END:X} is not zero",
            profile.name
        )));
    }

    std::fs::create_dir_all(output_dir)?;
    let mut images = Vec::with_capacity(decoded.directory.entries);
    for index in 0..decoded.directory.entries {
        let entry = &decoded.entries[index];
        let allocation = &decoded.allocations[index];
        let pixel_width = entry.stored_width as u32 * 2;
        let pixel_height = entry.stored_height as u32 * 2;
        let image_bytes = 2 * entry.stored_width as usize * entry.stored_height as usize;
        if image_bytes > allocation.len() {
            return Err(Error::Format(format!(
                "{}: image {index} is {image_bytes} bytes in a {}-byte allocation",
                profile.name,
                allocation.len()
            )));
        }
        let file = format!("{SPRITES_DIR}/{index:03}.png");
        image::write_indexed_palette(
            &safe_join(output_dir, &file)?,
            &Indexed {
                width: pixel_width,
                height: pixel_height,
                pixels: unpack(&allocation[..image_bytes]),
            },
            palette.display().as_deref(),
        )?;
        images.push(ImageRecord {
            index,
            stored_width: entry.stored_width,
            stored_height: entry.stored_height,
            pixel_width,
            pixel_height,
            character_units: entry.character_units,
            allocation: allocation.len(),
            image_bytes,
            stream_offset: decoded.streams[index].0,
            compressed_size: decoded.streams[index].1,
            sha256: sha256_hex(&allocation[..image_bytes]),
            file,
        });
    }

    let manifest = Manifest {
        format: FORMAT.to_string(),
        version: VERSION,
        player: profile.name.to_string(),
        encoding: ENCODING.to_string(),
        contact: Some(CONTACT_NAME.to_string()),
        lead_bytes: arena_start,
        arena_start,
        arena_end,
        source: Source {
            chr: file_name(chr_path),
            chr_size: chr.len(),
            chr_sha256: sha256_hex(&chr),
            prg: file_name(prg_path),
            prg_size: prg.len(),
            prg_sha256: sha256_hex(&prg),
        },
        directory: decoded.directory,
        palette,
        images,
    };

    if let Some(name) = &manifest.contact {
        let group = sheet::Group {
            label: None,
            palette: manifest.palette.display(),
            records: manifest
                .images
                .iter()
                .zip(&decoded.allocations)
                .map(|(record, allocation)| sheet::Record {
                    index: record.index,
                    width: record.pixel_width,
                    height: record.pixel_height,
                    pixels: unpack(&allocation[..record.image_bytes]),
                })
                .collect(),
        };
        image::write_rgba(&output_dir.join(name), &sheet::build(&[group]))?;
    }

    let mut json = serde_json::to_string_pretty(&manifest)?;
    json.push('\n');
    std::fs::write(output_dir.join(MANIFEST_NAME), json)?;
    Ok(manifest)
}

pub fn load_manifest(manifest_path: &Path) -> Result<Manifest> {
    let text = std::fs::read_to_string(manifest_path)?;
    let manifest: Manifest = serde_json::from_str(&text)?;
    if manifest.format != FORMAT || manifest.version != VERSION {
        return Err(Error::Format(format!(
            "{} is not a {FORMAT} v{VERSION} manifest",
            manifest_path.display()
        )));
    }
    let profile = manifest.profile()?;
    if manifest.encoding != ENCODING {
        return Err(Error::Format(format!(
            "{}: unsupported pixel encoding {:?}",
            manifest_path.display(),
            manifest.encoding
        )));
    }
    if manifest.directory.entry_base != profile.stream_entry_base
        || manifest.directory.entries != manifest.images.len()
    {
        return Err(Error::Format(format!(
            "{}: directory shape does not match the {} profile",
            manifest_path.display(),
            profile.name
        )));
    }
    if manifest.palette.address != profile.palette_table {
        return Err(Error::Format(format!(
            "{}: palette object moved from its retail address",
            manifest_path.display()
        )));
    }
    manifest.palette.values()?;
    for (position, record) in manifest.images.iter().enumerate() {
        if record.index != position
            || record.image_bytes > record.allocation
            || record.image_bytes
                != 2 * record.stored_width as usize * record.stored_height as usize
            || record.pixel_width != record.stored_width as u32 * 2
            || record.pixel_height != record.stored_height as u32 * 2
        {
            return Err(Error::Format(format!(
                "{}: image {position} is inconsistent",
                manifest_path.display()
            )));
        }
    }
    Ok(manifest)
}

pub struct Rebuilt {
    pub chr: Vec<u8>,
    pub directory: Vec<(u32, u32)>,
    pub changed: usize,
}

pub fn rebuild_bytes(manifest_path: &Path, chr_path: &Path) -> Result<Rebuilt> {
    let manifest = load_manifest(manifest_path)?;
    let profile = manifest.profile()?;
    let root = manifest_path.parent().unwrap_or_else(|| Path::new("."));
    let retail = std::fs::read(chr_path)?;
    if retail.len() != manifest.source.chr_size {
        return Err(Error::Format(format!(
            "{} is {} bytes, the manifest describes {}",
            chr_path.display(),
            retail.len(),
            manifest.source.chr_size
        )));
    }

    let mut arena = retail[..manifest.arena_start].to_vec();
    let mut directory = Vec::with_capacity(manifest.images.len());
    let mut changed = 0;

    for record in &manifest.images {
        let original = &retail[record.stream_offset..record.stream_offset + record.compressed_size];
        let allocation = lzss::decompress(original);
        if allocation.len() != record.allocation {
            return Err(Error::Format(format!(
                "{}: image {} in {} no longer decompresses to its allocation",
                profile.name,
                record.index,
                chr_path.display()
            )));
        }

        let sprite = image::read_indexed(&safe_join(root, &record.file)?)?;
        if (sprite.width, sprite.height) != (record.pixel_width, record.pixel_height) {
            return Err(Error::Format(format!(
                "{} is {}x{}, expected {}x{} (resizing is not supported)",
                record.file, sprite.width, sprite.height, record.pixel_width, record.pixel_height
            )));
        }
        let pixels = pack(&sprite.pixels)?;
        if pixels.len() != record.image_bytes {
            return Err(Error::Format(format!(
                "{}: packed to {} bytes, expected {}",
                record.file,
                pixels.len(),
                record.image_bytes
            )));
        }

        let stream = if sha256_hex(&pixels) == record.sha256 {
            original.to_vec()
        } else {
            changed += 1;
            let mut replacement = pixels;
            replacement.extend_from_slice(&allocation[record.image_bytes..]);
            lzss::compress(&replacement)
        };

        directory.push((
            manifest.directory.backing_base + arena.len() as u32,
            stream.len() as u32,
        ));
        arena.extend_from_slice(&stream);
    }

    if arena.len() > ARENA_END {
        return Err(Error::Format(format!(
            "{}: the rebuilt streams need 0x{:X} bytes but the arena ends at \
             0x{ARENA_END:X}; edits must not grow the compressed total",
            profile.name,
            arena.len()
        )));
    }
    arena.resize(ARENA_END, 0);
    arena.extend_from_slice(&retail[ARENA_END..]);
    if arena.len() != manifest.source.chr_size {
        return Err(Error::Format(format!(
            "rebuilt {} bytes, retail is {}",
            arena.len(),
            manifest.source.chr_size
        )));
    }

    Ok(Rebuilt {
        chr: arena,
        directory,
        changed,
    })
}

pub fn rebuild(manifest_path: &Path, chr_path: &Path, output_path: &Path) -> Result<Rebuilt> {
    let rebuilt = rebuild_bytes(manifest_path, chr_path)?;
    if let Some(parent) = output_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(output_path, &rebuilt.chr)?;
    Ok(rebuilt)
}

pub fn verify(manifest_path: &Path, chr_path: &Path) -> Result<()> {
    let rebuilt = rebuild_bytes(manifest_path, chr_path)?;
    let retail = std::fs::read(chr_path)?;
    if rebuilt.chr == retail {
        return Ok(());
    }
    let at = rebuilt
        .chr
        .iter()
        .zip(&retail)
        .position(|(a, b)| a != b)
        .unwrap_or(0);
    Err(Error::Mismatch(format!(
        "rebuilt player CHR does not match {} (first difference at offset 0x{at:X})",
        chr_path.display()
    )))
}

pub fn emit_directory_header(manifest: &Manifest, directory: &[(u32, u32)]) -> Result<String> {
    let symbols = header_symbols(manifest)?;
    let mut out = String::with_capacity(directory.len() * 40);
    out.push_str("// SPDX-License-Identifier: AGPL-3.0-or-later\n");
    out.push_str("// Generated by tools/saturn/assets: player generate-headers.\n");
    out.push_str("// Edit the extracted sprites and regenerate; do not hand-edit.\n");
    out.push_str("#include <saturn_player.h>\n\n");
    out.push_str(&format!(
        "SaturnPlayerGraphicsRecord {}[{}] = {{\n",
        symbols.directory,
        directory.len()
    ));
    for pair in directory.chunks(2) {
        let cells: Vec<String> = pair
            .iter()
            .map(|(address, size)| format!("{{0x{address:08X}, 0x{size:08X}}}"))
            .collect();
        out.push_str(&format!("    {},\n", cells.join(", ")));
    }
    out.push_str("};\n");
    Ok(out)
}

pub fn emit_palette_header(manifest: &Manifest) -> Result<String> {
    let symbols = header_symbols(manifest)?;
    let palette = &manifest.palette;
    let values = palette.values()?;
    let padding = parse_hex_bytes(&palette.padding)?;

    let mut out = String::new();
    out.push_str("// SPDX-License-Identifier: AGPL-3.0-or-later\n");
    out.push_str("// Generated by tools/saturn/assets: player generate-headers.\n");
    out.push_str("// Edit the extracted palette and regenerate; do not hand-edit.\n");
    out.push_str("#include \"sattypes.h\"\n\n");
    out.push_str("struct {\n    u16 countAndFlags;\n");
    out.push_str(&format!("    u16 colors[{}][16];\n", palette.banks));
    if !padding.is_empty() {
        out.push_str(&format!("    u16 padding[{}];\n", padding.len() / 2));
    }
    out.push_str(&format!("}} {} = {{\n", symbols.palette));
    out.push_str(&format!("    0x{:04X},\n    {{\n", palette.count_and_flags));
    for bank in values.chunks(PALETTE_BANK_SIZE) {
        out.push_str("        {\n");
        for row in bank.chunks(8) {
            let cells: Vec<String> = row.iter().map(|word| format!("0x{word:04X}")).collect();
            out.push_str(&format!("            {},\n", cells.join(", ")));
        }
        out.push_str("        },\n");
    }
    out.push_str("    },\n");
    if !padding.is_empty() {
        let words: Vec<String> = padding
            .chunks(2)
            .map(|pair| format!("0x{:04X}", u16::from_be_bytes([pair[0], pair[1]])))
            .collect();
        out.push_str(&format!("    {{{}}},\n", words.join(", ")));
    }
    out.push_str("};\n");
    Ok(out)
}

fn header_symbols(manifest: &Manifest) -> Result<&'static HeaderSymbols> {
    manifest.profile()?.header.ok_or_else(|| {
        Error::Format(format!(
            "{} is not decompiled; only players whose tables live in C have \
             generated headers",
            manifest.player
        ))
    })
}

fn parse_hex_bytes(values: &[String]) -> Result<Vec<u8>> {
    values
        .iter()
        .map(|value| {
            let digits = value.strip_prefix("0x").unwrap_or(value);
            u8::from_str_radix(digits, 16)
                .map_err(|e| Error::Format(format!("{value:?} is not a u8: {e}")))
        })
        .collect()
}

pub fn generate_headers(
    manifest_path: &Path,
    chr_path: &Path,
    directory_header: &Path,
    palette_header: &Path,
) -> Result<()> {
    let manifest = load_manifest(manifest_path)?;
    let rebuilt = rebuild_bytes(manifest_path, chr_path)?;
    for (path, text) in [
        (
            directory_header,
            emit_directory_header(&manifest, &rebuilt.directory)?,
        ),
        (palette_header, emit_palette_header(&manifest)?),
    ] {
        if let Some(parent) = path.parent() {
            std::fs::create_dir_all(parent)?;
        }
        std::fs::write(path, text)?;
    }
    Ok(())
}

pub fn verify_headers(
    manifest_path: &Path,
    chr_path: &Path,
    directory_header: &Path,
    palette_header: &Path,
) -> Result<()> {
    let manifest = load_manifest(manifest_path)?;
    let rebuilt = rebuild_bytes(manifest_path, chr_path)?;
    for (path, text) in [
        (
            directory_header,
            emit_directory_header(&manifest, &rebuilt.directory)?,
        ),
        (palette_header, emit_palette_header(&manifest)?),
    ] {
        let existing = std::fs::read_to_string(path)?;
        if existing != text {
            let at = text
                .lines()
                .zip(existing.lines())
                .position(|(a, b)| a != b)
                .map(|line| format!("first difference at line {}", line + 1))
                .unwrap_or_else(|| "line counts differ".to_string());
            return Err(Error::Mismatch(format!(
                "regenerating does not reproduce {} ({at}); it must never be hand-edited",
                path.display()
            )));
        }
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn every_profile_resolves_and_only_decompiled_players_own_headers() {
        for profile in PROFILES {
            assert_eq!(super::profile(profile.name).unwrap().chr, profile.chr);
        }
        assert!(super::profile("dracula").is_err());
        assert_eq!(PROFILES.iter().filter(|p| p.header.is_some()).count(), 2);
        assert_eq!(
            super::profile("alucard").unwrap().stream_entry_base,
            3,
            "Alucard's three mode-prefix records must be skipped"
        );
    }

    #[test]
    fn palette_words_are_counted_against_their_banks() {
        let palette = Palette {
            address: 0x060C_398C,
            prg_offset: 0,
            count_and_flags: 2,
            banks: 2,
            words: (0..32).map(|i| format!("0x{:04X}", 0x8000 | i)).collect(),
            padding: vec!["0x00".into(), "0x00".into()],
        };
        assert_eq!(palette.values().unwrap().len(), 32);

        let short = Palette {
            banks: 3,
            ..palette
        };
        assert!(short.values().is_err());
    }

    #[test]
    fn the_emitted_palette_carries_the_objects_shape() {
        let manifest = Manifest {
            format: FORMAT.into(),
            version: VERSION,
            player: "maria".into(),
            encoding: ENCODING.into(),
            contact: None,
            lead_bytes: 0,
            arena_start: 0,
            arena_end: 0,
            source: Source {
                chr: "MARIA.CHR".into(),
                chr_size: 0,
                chr_sha256: String::new(),
                prg: "MARIA.PRG".into(),
                prg_size: 0,
                prg_sha256: String::new(),
            },
            directory: Directory {
                address: 0,
                prg_offset: 0,
                backing_base: 0x0023_2000,
                entry_base: 0,
                entries: 0,
            },
            palette: Palette {
                address: 0x060C_398C,
                prg_offset: 0,
                count_and_flags: 0x0002,
                banks: 2,
                words: (0..32).map(|_| "0x8000".to_string()).collect(),
                padding: vec!["0x00".into(), "0x00".into()],
            },
            images: Vec::new(),
        };
        let text = emit_palette_header(&manifest).unwrap();
        assert!(text.contains("u16 colors[2][16];"));
        assert!(text.contains("u16 padding[1];"));
        assert!(text.contains("} g_MariaPalette = {"));
        assert!(text.contains("0x0002,"));

        let orphan = Manifest {
            player: "alucard".into(),
            ..manifest
        };
        assert!(emit_palette_header(&orphan).is_err());
    }

    #[test]
    fn the_emitted_directory_pairs_addresses_with_sizes() {
        let manifest = Manifest {
            format: FORMAT.into(),
            version: VERSION,
            player: "richter".into(),
            encoding: ENCODING.into(),
            contact: None,
            lead_bytes: 0,
            arena_start: 0,
            arena_end: 0,
            source: Source {
                chr: "RICHTER.CHR".into(),
                chr_size: 0,
                chr_sha256: String::new(),
                prg: "RICHTER.PRG".into(),
                prg_size: 0,
                prg_sha256: String::new(),
            },
            directory: Directory {
                address: 0,
                prg_offset: 0,
                backing_base: 0x0023_2000,
                entry_base: 0,
                entries: 0,
            },
            palette: Palette {
                address: 0x060C_0240,
                prg_offset: 0,
                count_and_flags: 1,
                banks: 1,
                words: (0..16).map(|_| "0x8000".to_string()).collect(),
                padding: Vec::new(),
            },
            images: Vec::new(),
        };
        let text = emit_directory_header(&manifest, &[(0x0023_2000, 0x190), (0x0023_2190, 0x197)])
            .unwrap();
        assert!(text.contains("SaturnPlayerGraphicsRecord g_RichterPlayerGraphicsRecords[2]"));
        assert!(text.contains("{0x00232000, 0x00000190}, {0x00232190, 0x00000197},"));
    }
}
