//! ASCII.FON and KANJI.FON.
//!
//! 1 bit per pixel
//!
//!   ASCII.FON   8x16 glyphs, 16 bytes each,  256 glyphs (ASCII + Latin-1)
//!   KANJI.FON  16x16 glyphs, 32 bytes each, 7806 glyphs (JIS)
//!
//! g_SaturnFontGlyphMappings defines shift-jis codes for KANJI.FON (src/saturn/zero/fontmap.c)

use crate::image::{self, Bilevel};
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::path::Path;

pub const FORMAT: &str = "sotn-saturn-font";
pub const VERSION: u32 = 1;
pub const ATLAS_NAME: &str = "atlas.png";
pub const MANIFEST_NAME: &str = "manifest.json";

#[derive(Clone, Copy)]
pub struct Profile {
    pub name: &'static str,
    pub file: &'static str,
    pub width: u32,
    pub height: u32,
    // number columns in atlas (layout decision)
    pub columns: u32,
}

pub const PROFILES: &[Profile] = &[
    Profile {
        name: "ascii",
        file: "ASCII.FON",
        width: 8,
        height: 16,
        columns: 32,
    },
    Profile {
        name: "kanji",
        file: "KANJI.FON",
        width: 16,
        height: 16,
        columns: 64,
    },
];

impl Profile {
    pub fn row_bytes(&self) -> usize {
        (self.width / 8) as usize
    }

    pub fn bytes_per_glyph(&self) -> usize {
        self.row_bytes() * self.height as usize
    }
}

pub fn profile(name: &str) -> Result<&'static Profile> {
    PROFILES.iter().find(|p| p.name == name).ok_or_else(|| {
        let known: Vec<&str> = PROFILES.iter().map(|p| p.name).collect();
        Error::Format(format!(
            "unknown font {name:?}; known: {}",
            known.join(", ")
        ))
    })
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Source {
    pub name: String,
    pub size: usize,
    pub sha256: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Manifest {
    pub format: String,
    pub version: u32,
    pub font: String,
    pub width: u32,
    pub height: u32,
    pub columns: u32,
    pub glyphs: usize,
    pub source: Source,
    pub atlas: String,
}

impl Manifest {
    pub fn profile(&self) -> Result<&'static Profile> {
        profile(&self.font)
    }

    pub fn rows(&self) -> u32 {
        let columns = self.columns as usize;
        ((self.glyphs + columns - 1) / columns) as u32
    }
}

fn build_manifest(profile: &Profile, source_name: &str, data: &[u8]) -> Result<Manifest> {
    let bytes_per_glyph = profile.bytes_per_glyph();
    if data.len() % bytes_per_glyph != 0 {
        return Err(Error::Format(format!(
            "{source_name} size {} is not a whole number of {}x{} glyphs",
            data.len(),
            profile.width,
            profile.height
        )));
    }
    Ok(Manifest {
        format: FORMAT.to_string(),
        version: VERSION,
        font: profile.name.to_string(),
        width: profile.width,
        height: profile.height,
        columns: profile.columns,
        glyphs: data.len() / bytes_per_glyph,
        source: Source {
            name: source_name.to_string(),
            size: data.len(),
            sha256: sha256_hex(data),
        },
        atlas: ATLAS_NAME.to_string(),
    })
}

/// unpack into columns # of glyphs per row
pub fn to_atlas(profile: &Profile, glyphs: usize, data: &[u8]) -> Bilevel {
    let columns = profile.columns;
    let rows = ((glyphs as u32) + columns - 1) / columns;
    let mut atlas = Bilevel::new(columns * profile.width, rows * profile.height);
    let row_bytes = profile.row_bytes();
    for glyph in 0..glyphs {
        let origin_x = (glyph as u32 % columns) * profile.width;
        let origin_y = (glyph as u32 / columns) * profile.height;
        let base = glyph * profile.bytes_per_glyph();
        for y in 0..profile.height {
            for byte in 0..row_bytes {
                let packed = data[base + (y as usize) * row_bytes + byte];
                for bit in 0..8u32 {
                    let x = (byte as u32) * 8 + bit;
                    let on = packed & (0x80 >> bit) != 0;
                    atlas.set(origin_x + x, origin_y + y, u8::from(on));
                }
            }
        }
    }
    atlas
}

/// repack into fon
pub fn from_atlas(profile: &Profile, glyphs: usize, atlas: &Bilevel) -> Result<Vec<u8>> {
    let columns = profile.columns;
    let rows = ((glyphs as u32) + columns - 1) / columns;
    let expected = (columns * profile.width, rows * profile.height);
    if (atlas.width, atlas.height) != expected {
        return Err(Error::Format(format!(
            "atlas is {}x{}, expected {}x{} (resizing glyphs is not supported)",
            atlas.width, atlas.height, expected.0, expected.1
        )));
    }
    let row_bytes = profile.row_bytes();
    let mut out = vec![0u8; glyphs * profile.bytes_per_glyph()];
    for glyph in 0..glyphs {
        let origin_x = (glyph as u32 % columns) * profile.width;
        let origin_y = (glyph as u32 / columns) * profile.height;
        let base = glyph * profile.bytes_per_glyph();
        for y in 0..profile.height {
            for byte in 0..row_bytes {
                let mut packed = 0u8;
                for bit in 0..8u32 {
                    let x = (byte as u32) * 8 + bit;
                    if atlas.get(origin_x + x, origin_y + y) != 0 {
                        packed |= 0x80 >> bit;
                    }
                }
                out[base + (y as usize) * row_bytes + byte] = packed;
            }
        }
    }
    Ok(out)
}

/// write the atlas and json description
pub fn extract(font: &str, font_path: &Path, output_dir: &Path) -> Result<Manifest> {
    let profile = profile(font)?;
    let data = std::fs::read(font_path)?;
    let source_name = font_path
        .file_name()
        .map(|n| n.to_string_lossy().into_owned())
        .unwrap_or_else(|| font_path.display().to_string());
    let manifest = build_manifest(profile, &source_name, &data)?;

    std::fs::create_dir_all(output_dir)?;
    let atlas = to_atlas(profile, manifest.glyphs, &data);
    image::write(&output_dir.join(&manifest.atlas), &atlas)?;
    let mut json = serde_json::to_string_pretty(&manifest)?;
    json.push('\n');
    std::fs::write(output_dir.join(MANIFEST_NAME), json)?;
    Ok(manifest)
}

pub fn load_manifest(manifest_path: &Path) -> Result<Manifest> {
    let text = std::fs::read_to_string(manifest_path)?;
    let manifest: Manifest = serde_json::from_str(&text)?;
    if manifest.format != FORMAT {
        return Err(Error::Format(format!(
            "{} is not a {FORMAT} manifest",
            manifest_path.display()
        )));
    }
    Ok(manifest)
}

/// take manifest and atlas and produce packed bytes
pub fn rebuild_bytes(manifest_path: &Path) -> Result<Vec<u8>> {
    let manifest = load_manifest(manifest_path)?;
    let profile = manifest.profile()?;
    let atlas_path = manifest_path
        .parent()
        .unwrap_or_else(|| Path::new("."))
        .join(&manifest.atlas);
    let atlas = image::read(&atlas_path)?;
    from_atlas(profile, manifest.glyphs, &atlas)
}

pub fn rebuild(manifest_path: &Path, output_path: &Path) -> Result<Vec<u8>> {
    let data = rebuild_bytes(manifest_path)?;
    if let Some(parent) = output_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(output_path, &data)?;
    Ok(data)
}

/// check round trip
pub fn verify(manifest_path: &Path, font_path: &Path) -> Result<()> {
    let rebuilt = rebuild_bytes(manifest_path)?;
    let retail = std::fs::read(font_path)?;
    if rebuilt == retail {
        return Ok(());
    }
    let detail = if rebuilt.len() != retail.len() {
        format!("{} bytes rebuilt vs {} retail", rebuilt.len(), retail.len())
    } else {
        let at = rebuilt
            .iter()
            .zip(&retail)
            .position(|(a, b)| a != b)
            .unwrap_or(0);
        format!("first difference at offset 0x{at:X}")
    };
    Err(Error::Mismatch(format!(
        "rebuilt font does not match {} ({detail})",
        font_path.display()
    )))
}

#[cfg(test)]
mod tests {
    use super::*;

    fn synthetic(profile: &Profile, glyphs: usize) -> Vec<u8> {
        // random pattern
        (0..glyphs * profile.bytes_per_glyph())
            .map(|i| (i * 37 + 11) as u8)
            .collect()
    }

    #[test]
    fn atlas_round_trips_every_profile() {
        for profile in PROFILES {
            let glyphs = 200;
            let data = synthetic(profile, glyphs);
            let atlas = to_atlas(profile, glyphs, &data);
            assert_eq!(from_atlas(profile, glyphs, &atlas).unwrap(), data);
        }
    }

    #[test]
    fn atlas_is_laid_out_in_columns() {
        let profile = profile("ascii").unwrap();
        let glyphs = 64;
        let mut data = vec![0u8; glyphs * profile.bytes_per_glyph()];
        // set a pixel in glyph 33
        data[33 * profile.bytes_per_glyph()] = 0x80;
        let atlas = to_atlas(profile, glyphs, &data);
        assert_eq!(atlas.get(profile.width, profile.height), 1);
        assert_eq!(atlas.get(0, 0), 0);
    }

    #[test]
    fn an_edited_pixel_reaches_exactly_one_bit() {
        let profile = profile("kanji").unwrap();
        let glyphs = 128;
        let data = synthetic(profile, glyphs);
        let mut atlas = to_atlas(profile, glyphs, &data);
        let before = atlas.get(5, 7);
        atlas.set(5, 7, u8::from(before == 0));
        let rebuilt = from_atlas(profile, glyphs, &atlas).unwrap();
        assert_eq!(rebuilt.len(), data.len());
        let changed: Vec<usize> = rebuilt
            .iter()
            .zip(&data)
            .enumerate()
            .filter(|(_, (a, b))| a != b)
            .map(|(i, _)| i)
            .collect();
        assert_eq!(changed.len(), 1, "one pixel must touch one byte");
        assert_eq!((rebuilt[changed[0]] ^ data[changed[0]]).count_ones(), 1);
    }

    #[test]
    fn a_resized_atlas_is_refused() {
        let profile = profile("ascii").unwrap();
        let glyphs = 64;
        let atlas = Bilevel::new(profile.columns * profile.width, 1);
        let err = from_atlas(profile, glyphs, &atlas).unwrap_err();
        assert!(matches!(err, Error::Format(_)), "{err}");
    }

    #[test]
    fn a_partial_glyph_is_refused() {
        let profile = profile("ascii").unwrap();
        let err = build_manifest(profile, "ASCII.FON", &[0u8; 17]).unwrap_err();
        assert!(matches!(err, Error::Format(_)), "{err}");
    }
}
