use crate::image::{self, Indexed};
use crate::sprite::{pack, rgb555, unpack, PALETTE_BANK_SIZE};
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::path::{Path, PathBuf};

pub const FORMAT: &str = "sotn-saturn-packed-bitmap";
pub const VERSION: u32 = 5;
pub const MANIFEST_NAME: &str = "manifest.json";
pub const BITMAP_NAME: &str = "bitmap.png";
pub const ENCODING: &str = "indexed4-linear-high-nibble-first";

const BYTES_PER_LINE: usize = 12;

#[derive(Clone, Copy)]
pub struct Profile {
    pub name: &'static str,
    pub source_file: &'static str,
    pub source_offset: usize,
    pub rows: u32,
    pub columns: u32,
    pub symbol: &'static str,
    pub chr: &'static str,
    pub clut_offset: usize,
}

impl Profile {
    pub fn size(&self) -> usize {
        self.rows as usize * self.columns as usize
    }

    pub fn width(&self) -> u32 {
        self.columns * 2
    }

    pub fn height(&self) -> u32 {
        self.rows
    }
}

pub const PROFILES: &[Profile] = &[
    Profile {
        name: "alucard-castle-map",
        source_file: "SUB_DISP.MAP",
        source_offset: 0x0,
        rows: 240,
        columns: 160,
        symbol: "g_AlucardCastleMapBitmap",
        chr: "ALUCARD.CHR",
        clut_offset: 0x2F1E0,
    },
    Profile {
        name: "maria-castle-map",
        source_file: "MARIA.PRG",
        source_offset: 0x22D60,
        rows: 240,
        columns: 160,
        symbol: "g_MariaCastleMapBitmap",
        chr: "MARIA.CHR",
        clut_offset: 0x2F1E0,
    },
    Profile {
        name: "richter-castle-map",
        source_file: "RICHTER.PRG",
        source_offset: 0x1F11C,
        rows: 240,
        columns: 160,
        symbol: "g_RichterCastleMapBitmap",
        chr: "RICHTER.CHR",
        clut_offset: 0x2F1E0,
    },
    Profile {
        name: "richter2-castle-map",
        source_file: "RICHTER2.PRG",
        source_offset: 0x1F03C,
        rows: 240,
        columns: 160,
        symbol: "g_Richter2CastleMapBitmap",
        chr: "RICHTER2.CHR",
        clut_offset: 0x2F1E0,
    },
];

pub fn profile(name: &str) -> Result<&'static Profile> {
    PROFILES.iter().find(|p| p.name == name).ok_or_else(|| {
        let known: Vec<&str> = PROFILES.iter().map(|p| p.name).collect();
        Error::Format(format!(
            "unknown bitmap {name:?}; known: {}",
            known.join(", ")
        ))
    })
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Source {
    pub file: String,
    pub file_size: usize,
    pub file_sha256: String,
    pub offset: usize,
    pub size: usize,
    pub sha256: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct PaletteSource {
    pub chr: String,
    pub chr_size: usize,
    pub chr_sha256: String,
    pub clut_offset: usize,
    pub clut_size: usize,
    pub clut_sha256: String,
    pub words: Vec<u16>,
    pub preview_rgb555: Vec<u16>,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Manifest {
    pub format: String,
    pub version: u32,
    pub bitmap: String,
    pub encoding: String,
    pub symbol: String,
    pub rows: u32,
    pub columns: u32,
    pub width: u32,
    pub height: u32,
    pub file: String,
    pub source: Source,
    pub palette: PaletteSource,
}

impl Manifest {
    pub fn profile(&self) -> Result<&'static Profile> {
        profile(&self.bitmap)
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

pub fn retail_bytes(profile: &Profile, source: &[u8]) -> Result<Vec<u8>> {
    let end = profile.source_offset + profile.size();
    source
        .get(profile.source_offset..end)
        .map(<[u8]>::to_vec)
        .ok_or_else(|| {
            Error::Format(format!(
                "{}: the {}-byte array at 0x{:X} runs past the end of {} ({} bytes)",
                profile.name,
                profile.size(),
                profile.source_offset,
                profile.source_file,
                source.len()
            ))
        })
}

const CLUT_SIZE: usize = PALETTE_BANK_SIZE * 2;

// runtime writes to reveal: 1->9, 4->12, 6->14, 15 for white edge
// table 67
const MAP_PREVIEW_RGB555: [u16; PALETTE_BANK_SIZE] = [
    0x0000, 0x7DCA, 0x0000, 0x0000, 0x001F, 0x0000, 0x021F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
];

fn png_palette(words: &[u16]) -> Vec<u8> {
    words.iter().flat_map(|&word| rgb555(word)).collect()
}

pub fn extract(
    name: &str,
    source_path: &Path,
    chr_path: &Path,
    output_dir: &Path,
) -> Result<Manifest> {
    let profile = profile(name)?;
    let source = std::fs::read(source_path)?;
    let data = retail_bytes(profile, &source)?;
    let chr = std::fs::read(chr_path)?;
    let clut = chr
        .get(profile.clut_offset..profile.clut_offset + CLUT_SIZE)
        .ok_or_else(|| {
            Error::Format(format!(
                "{}: lookup table 67 at 0x{:X} runs past the end of {} ({} bytes)",
                profile.name,
                profile.clut_offset,
                profile.chr,
                chr.len()
            ))
        })?;
    let raw_words: Vec<u16> = clut
        .chunks_exact(2)
        .map(|bytes| u16::from_be_bytes([bytes[0], bytes[1]]))
        .collect();
    let picture = Indexed {
        width: profile.width(),
        height: profile.height(),
        pixels: unpack(&data),
    };
    std::fs::create_dir_all(output_dir)?;
    image::write_indexed_palette(
        &output_dir.join(BITMAP_NAME),
        &picture,
        Some(&png_palette(&MAP_PREVIEW_RGB555)),
    )?;

    let manifest = Manifest {
        format: FORMAT.to_string(),
        version: VERSION,
        bitmap: profile.name.to_string(),
        encoding: ENCODING.to_string(),
        symbol: profile.symbol.to_string(),
        rows: profile.rows,
        columns: profile.columns,
        width: profile.width(),
        height: profile.height(),
        file: BITMAP_NAME.to_string(),
        source: Source {
            file: file_name(source_path),
            file_size: source.len(),
            file_sha256: sha256_hex(&source),
            offset: profile.source_offset,
            size: data.len(),
            sha256: sha256_hex(&data),
        },
        palette: PaletteSource {
            chr: file_name(chr_path),
            chr_size: chr.len(),
            chr_sha256: sha256_hex(&chr),
            clut_offset: profile.clut_offset,
            clut_size: clut.len(),
            clut_sha256: sha256_hex(clut),
            words: raw_words,
            preview_rgb555: MAP_PREVIEW_RGB555.to_vec(),
        },
    };

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
    if (manifest.rows, manifest.columns) != (profile.rows, profile.columns)
        || (manifest.width, manifest.height) != (profile.width(), profile.height())
        || manifest.symbol != profile.symbol
        || manifest.source.file != profile.source_file
        || manifest.source.offset != profile.source_offset
        || manifest.source.size != profile.size()
        || manifest.palette.chr != profile.chr
        || manifest.palette.clut_offset != profile.clut_offset
        || manifest.palette.clut_size != CLUT_SIZE
        || manifest.palette.words.len() != PALETTE_BANK_SIZE
        || manifest.palette.preview_rgb555.len() != PALETTE_BANK_SIZE
    {
        return Err(Error::Format(format!(
            "{}: shape or symbol does not match the {} profile",
            manifest_path.display(),
            profile.name
        )));
    }
    Ok(manifest)
}

pub fn rebuild_bytes(manifest_path: &Path) -> Result<Vec<u8>> {
    let manifest = load_manifest(manifest_path)?;
    let root = manifest_path.parent().unwrap_or_else(|| Path::new("."));
    let picture = image::read_indexed(&safe_join(root, &manifest.file)?)?;
    if (picture.width, picture.height) != (manifest.width, manifest.height) {
        return Err(Error::Format(format!(
            "{} is {}x{}, expected {}x{} (the array's shape is compiled into \
             the overlay, so resizing is not supported)",
            manifest.file, picture.width, picture.height, manifest.width, manifest.height
        )));
    }
    let data = pack(&picture.pixels)?;
    if data.len() != manifest.source.size {
        return Err(Error::Format(format!(
            "rebuilt {} bytes, the array is {}",
            data.len(),
            manifest.source.size
        )));
    }
    Ok(data)
}

pub fn rebuild(manifest_path: &Path, output_path: &Path) -> Result<Vec<u8>> {
    let data = rebuild_bytes(manifest_path)?;
    if let Some(parent) = output_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(output_path, &data)?;
    Ok(data)
}

pub fn verify(manifest_path: &Path, source_path: &Path) -> Result<()> {
    let manifest = load_manifest(manifest_path)?;
    let rebuilt = rebuild_bytes(manifest_path)?;
    let source = std::fs::read(source_path)?;
    let retail = retail_bytes(manifest.profile()?, &source)?;
    if rebuilt == retail {
        return Ok(());
    }
    let at = rebuilt
        .iter()
        .zip(&retail)
        .position(|(a, b)| a != b)
        .unwrap_or(0);
    Err(Error::Mismatch(format!(
        "rebuilt {} does not match {} (first difference at array offset 0x{at:X})",
        manifest.symbol,
        source_path.display()
    )))
}

pub fn emit_header(manifest: &Manifest, data: &[u8]) -> Result<String> {
    let profile = manifest.profile()?;
    if data.len() != profile.size() {
        return Err(Error::Format(format!(
            "{}: {} bytes for a {}x{} array",
            profile.name,
            data.len(),
            profile.rows,
            profile.columns
        )));
    }

    let columns = profile.columns as usize;
    let mut out = String::with_capacity(data.len() * 7);
    out.push_str("// SPDX-License-Identifier: AGPL-3.0-or-later\n");
    out.push_str("// Generated by tools/saturn/assets: bitmap generate-header.\n");
    out.push_str("// Edit the extracted PNG and regenerate; do not hand-edit.\n");
    out.push_str("#include \"sattypes.h\"\n\n");
    out.push_str(&format!(
        "u8 {}[{}][{}] = {{\n",
        profile.symbol, profile.rows, profile.columns
    ));
    for row in data.chunks(columns) {
        out.push_str("    {\n");
        for line in row.chunks(BYTES_PER_LINE) {
            out.push_str("       ");
            for byte in line {
                out.push_str(&format!(" 0x{byte:02X},"));
            }
            out.push('\n');
        }
        out.push_str("    },\n");
    }
    out.push_str("};\n");
    Ok(out)
}

pub fn generate_header(manifest_path: &Path, output_path: &Path) -> Result<String> {
    let manifest = load_manifest(manifest_path)?;
    let text = emit_header(&manifest, &rebuild_bytes(manifest_path)?)?;
    if let Some(parent) = output_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(output_path, &text)?;
    Ok(text)
}

pub fn verify_header(manifest_path: &Path, header_path: &Path) -> Result<()> {
    let manifest = load_manifest(manifest_path)?;
    let generated = emit_header(&manifest, &rebuild_bytes(manifest_path)?)?;
    let existing = std::fs::read_to_string(header_path)?;
    if generated == existing {
        return Ok(());
    }
    let detail = match generated
        .lines()
        .zip(existing.lines())
        .position(|(a, b)| a != b)
    {
        Some(line) => format!("first difference at line {}", line + 1),
        None => format!(
            "{} generated lines vs {} on disk",
            generated.lines().count(),
            existing.lines().count()
        ),
    };
    Err(Error::Mismatch(format!(
        "regenerating does not reproduce {} ({detail}); it must never be hand-edited",
        header_path.display()
    )))
}

#[cfg(test)]
mod tests {
    use super::*;

    fn maria() -> &'static Profile {
        profile("maria-castle-map").unwrap()
    }

    #[test]
    fn every_profile_is_a_whole_number_of_rows_and_resolves_by_name() {
        for profile in PROFILES {
            assert_eq!(
                profile.size(),
                profile.rows as usize * profile.columns as usize
            );
            assert_eq!(profile.width(), profile.columns * 2);
            assert_eq!(super::profile(profile.name).unwrap().symbol, profile.symbol);
        }
        assert!(super::profile("belmont-portrait").is_err());
    }

    #[test]
    fn the_castle_map_is_320x240() {
        assert_eq!((maria().width(), maria().height()), (320, 240));
        assert_eq!(maria().size(), 38400);
    }

    #[test]
    fn a_short_overlay_is_refused_rather_than_truncated() {
        let err = retail_bytes(maria(), &[0u8; 16]).unwrap_err();
        assert!(matches!(err, Error::Format(_)), "{err}");
    }

    #[test]
    fn the_emitted_array_is_rows_of_the_declared_width() {
        let profile = maria();
        let data: Vec<u8> = (0..profile.size()).map(|i| (i % 251) as u8).collect();
        let manifest = Manifest {
            format: FORMAT.into(),
            version: VERSION,
            bitmap: profile.name.into(),
            encoding: ENCODING.into(),
            symbol: profile.symbol.into(),
            rows: profile.rows,
            columns: profile.columns,
            width: profile.width(),
            height: profile.height(),
            file: BITMAP_NAME.into(),
            source: Source {
                file: profile.source_file.into(),
                file_size: 0,
                file_sha256: String::new(),
                offset: profile.source_offset,
                size: data.len(),
                sha256: String::new(),
            },
            palette: PaletteSource {
                chr: profile.chr.into(),
                chr_size: 0,
                chr_sha256: String::new(),
                clut_offset: profile.clut_offset,
                clut_size: CLUT_SIZE,
                clut_sha256: String::new(),
                words: vec![0; PALETTE_BANK_SIZE],
                preview_rgb555: MAP_PREVIEW_RGB555.to_vec(),
            },
        };
        let text = emit_header(&manifest, &data).unwrap();
        assert!(text.contains(&format!("u8 {}[240][160] = {{", profile.symbol)));
        assert_eq!(text.matches("    {\n").count(), profile.rows as usize);
        assert_eq!(
            text.matches("0x").count() - text.matches("0x{").count(),
            profile.size()
        );

        assert!(emit_header(&manifest, &data[..10]).is_err());
    }

    #[test]
    fn packing_a_picture_round_trips_through_the_nibbles() {
        let profile = maria();
        let data: Vec<u8> = (0..profile.size()).map(|i| (i % 251) as u8).collect();
        let picture = Indexed {
            width: profile.width(),
            height: profile.height(),
            pixels: unpack(&data),
        };
        assert_eq!(picture.pixels.len(), profile.size() * 2);
        assert_eq!(pack(&picture.pixels).unwrap(), data);
    }
}
