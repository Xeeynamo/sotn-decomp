use crate::image::{self, Indexed};
use crate::sheet;
use crate::sprite::{
    self, display_palette, pack, parse_image_table, read_palette_banks, to_linear, unpack, Resource,
};
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::path::{Path, PathBuf};

pub const FORMAT: &str = "sotn-saturn-familiar-chr";
pub const VERSION: u32 = 1;
pub const MANIFEST_NAME: &str = "manifest.json";
pub const LINEAR_NAME: &str = "linear.png";
pub const CONTACT_NAME: &str = "contact.png";
pub const SPRITES_DIR: &str = "sprites";
pub const ENCODING: &str = "indexed4-linear-high-nibble-first";

pub const LOAD_ADDRESS: u32 = 0x060C_F000;

pub struct HeaderSymbols {
    pub slices: &'static str,
    pub clut_count: &'static str,
    pub clut: &'static str,
    pub clut_padding: &'static str,
    pub resource: &'static str,
    pub descriptors: &'static str,
}

#[derive(Clone, Copy)]
pub struct Profile {
    pub name: &'static str,
    pub chr: &'static str,
    pub prg: &'static str,
    pub known_resource: Option<u32>,
    pub header: Option<&'static HeaderSymbols>,
}

static BAT_SYMBOLS: HeaderSymbols = HeaderSymbols {
    slices: "g_BatTextureSlices",
    clut_count: "g_BatClutCount",
    clut: "g_ServantClut",
    clut_padding: "g_BatClutPadding",
    resource: "g_BatTextureResource",
    descriptors: "g_BatResourceDescriptors",
};

pub const PROFILES: &[Profile] = &[
    Profile {
        name: "bat",
        chr: "T_BAT.CHR",
        prg: "T_BAT.PRG",
        known_resource: Some(0x060D_1B70),
        header: Some(&BAT_SYMBOLS),
    },
    Profile {
        name: "devil",
        chr: "T_DEVIL.CHR",
        prg: "T_DEVIL.PRG",
        known_resource: None,
        header: None,
    },
    Profile {
        name: "devil2",
        chr: "T_DEVIL2.CHR",
        prg: "T_DEVIL2.PRG",
        known_resource: None,
        header: None,
    },
    Profile {
        name: "fairy",
        chr: "T_FAIRY.CHR",
        prg: "T_FAIRY.PRG",
        known_resource: None,
        header: None,
    },
    Profile {
        name: "fairy2",
        chr: "T_FAIRY2.CHR",
        prg: "T_FAIRY2.PRG",
        known_resource: None,
        header: None,
    },
    Profile {
        name: "ghost",
        chr: "T_GHOST.CHR",
        prg: "T_GHOST.PRG",
        known_resource: None,
        header: None,
    },
    Profile {
        name: "sword",
        chr: "T_SWORD.CHR",
        prg: "T_SWORD.PRG",
        known_resource: None,
        header: None,
    },
];

pub fn profile(name: &str) -> Result<&'static Profile> {
    PROFILES.iter().find(|p| p.name == name).ok_or_else(|| {
        let known: Vec<&str> = PROFILES.iter().map(|p| p.name).collect();
        Error::Format(format!(
            "unknown familiar {name:?}; known: {}",
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
pub struct ResourceInfo {
    pub address: u32,
    pub prg_offset: usize,
    pub images_address: u32,
    pub images_prg_offset: usize,
    pub palette_address: u32,
    pub palette_prg_offset: usize,
    pub allocation: u16,
    pub flags: u16,
    pub terminator_units: usize,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Clut {
    pub banks: usize,
    pub words: Vec<String>,
    pub padding: u16,
}

impl Clut {
    pub fn values(&self) -> Result<Vec<u16>> {
        if self.banks * sprite::PALETTE_BANK_SIZE != self.words.len() {
            return Err(Error::Format(format!(
                "CLUT declares {} banks but carries {} words",
                self.banks,
                self.words.len()
            )));
        }
        self.words
            .iter()
            .map(|word| {
                let digits = word.strip_prefix("0x").unwrap_or(word);
                u16::from_str_radix(digits, 16)
                    .map_err(|e| Error::Format(format!("CLUT word {word:?} is not a u16: {e}")))
            })
            .collect()
    }

    pub fn display_palette(&self) -> Option<Vec<u8>> {
        let values = self.values().ok()?;
        let bank: Vec<[u8; 3]> = values
            .iter()
            .take(sprite::PALETTE_BANK_SIZE)
            .map(|&word| sprite::rgb555(word))
            .collect();
        display_palette(&[bank])
    }
}

#[derive(Debug, Serialize, Deserialize)]
pub struct ImageRecord {
    pub index: usize,
    pub stored_width: u8,
    pub stored_height: u8,
    pub offset_units: usize,
    pub pixel_width: u32,
    pub pixel_height: u32,
    pub file_offset: usize,
    pub byte_count: usize,
    pub allocation_size: usize,
    pub sha256: String,
    pub file: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Manifest {
    pub format: String,
    pub version: u32,
    pub familiar: String,
    pub encoding: String,
    pub linear: String,
    pub linear_width: u32,
    pub linear_height: u32,
    #[serde(skip_serializing_if = "Option::is_none", default)]
    pub contact: Option<String>,
    pub valid_pixels: usize,
    pub padding_pixels: usize,
    pub source: Source,
    pub resource: ResourceInfo,
    pub clut: Clut,
    pub images: Vec<ImageRecord>,
}

impl Manifest {
    pub fn profile(&self) -> Result<&'static Profile> {
        profile(&self.familiar)
    }
}

pub fn locate_resource(prg: &[u8], chr_size: usize) -> Result<(usize, Resource, usize)> {
    let mut found: Vec<(usize, Resource, usize)> = Vec::new();
    for offset in (0..prg.len().saturating_sub(sprite::RESOURCE_STRIDE)).step_by(4) {
        let Some(resource) = Resource::read(prg, offset) else {
            continue;
        };
        if !resource.is_canonical() {
            continue;
        }
        let Some(table) = resource
            .images_address
            .checked_sub(LOAD_ADDRESS)
            .map(|offset| offset as usize)
            .filter(|&offset| offset < prg.len())
        else {
            continue;
        };
        match parse_image_table(prg, table) {
            Ok((records, total)) if total == chr_size && !records.is_empty() => {
                found.push((offset, resource, total));
            }
            _ => {}
        }
    }
    match found.len() {
        1 => Ok(found.remove(0)),
        n => Err(Error::Format(format!(
            "expected exactly one sprite resource describing a {chr_size}-byte CHR, found {n}"
        ))),
    }
}

fn record_image(data: &[u8], record: &ImageRecord) -> Indexed {
    Indexed {
        width: record.pixel_width,
        height: record.pixel_height,
        pixels: unpack(&data[record.file_offset..record.file_offset + record.byte_count]),
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

pub fn extract(
    familiar: &str,
    prg_path: &Path,
    chr_path: &Path,
    output_dir: &Path,
) -> Result<Manifest> {
    let profile = profile(familiar)?;
    let prg = std::fs::read(prg_path)?;
    let data = std::fs::read(chr_path)?;
    if data.is_empty() {
        return Err(Error::Format(format!("{} is empty", chr_path.display())));
    }

    let (resource_offset, resource, total) = locate_resource(&prg, data.len())?;
    let address = LOAD_ADDRESS + resource_offset as u32;
    if let Some(expected) = profile.known_resource {
        if address != expected {
            return Err(Error::Format(format!(
                "{}: located the resource at 0x{address:08X}, but the \
                 decompilation names 0x{expected:08X}",
                profile.name
            )));
        }
    }

    let images_prg_offset = (resource.images_address - LOAD_ADDRESS) as usize;
    let palette_prg_offset = (resource.palette_address.wrapping_sub(LOAD_ADDRESS)) as usize;
    let (records, _) = parse_image_table(&prg, images_prg_offset)?;

    let banks = sprite::bank_count(&prg, palette_prg_offset);
    let words = sprite::PALETTE_BANK_SIZE * banks;
    let clut_start = palette_prg_offset + 2;
    if clut_start + words * 2 + 2 > prg.len() {
        return Err(Error::Format(format!(
            "{}: CLUT of {banks} banks runs past the end of the PRG",
            profile.name
        )));
    }
    let clut = Clut {
        banks,
        words: (0..words)
            .map(|index| {
                let at = clut_start + index * 2;
                format!("0x{:04X}", u16::from_be_bytes([prg[at], prg[at + 1]]))
            })
            .collect(),
        padding: u16::from_be_bytes([prg[clut_start + words * 2], prg[clut_start + words * 2 + 1]]),
    };

    let images: Vec<ImageRecord> = records
        .iter()
        .map(|record| ImageRecord {
            index: record.index,
            stored_width: record.stored_width,
            stored_height: record.stored_height,
            offset_units: record.offset / sprite::OFFSET_UNIT,
            pixel_width: record.pixel_width(),
            pixel_height: record.pixel_height(),
            file_offset: record.offset,
            byte_count: record.byte_count,
            allocation_size: record.allocation_size,
            sha256: sha256_hex(&data[record.offset..record.offset + record.byte_count]),
            file: format!("{SPRITES_DIR}/{:03}.png", record.index),
        })
        .collect();

    let linear = to_linear(&data);
    let valid_pixels = data.len() * 2;
    let total_pixels = (linear.width * linear.height) as usize;

    std::fs::create_dir_all(output_dir)?;
    image::write_indexed(&output_dir.join(LINEAR_NAME), &linear)?;
    let palette = display_palette(&read_palette_banks(&prg, palette_prg_offset));
    for record in &images {
        image::write_indexed_palette(
            &safe_join(output_dir, &record.file)?,
            &record_image(&data, record),
            palette.as_deref(),
        )?;
    }

    let manifest = Manifest {
        format: FORMAT.to_string(),
        version: VERSION,
        familiar: profile.name.to_string(),
        encoding: ENCODING.to_string(),
        linear: LINEAR_NAME.to_string(),
        linear_width: linear.width,
        linear_height: linear.height,
        contact: Some(CONTACT_NAME.to_string()),
        valid_pixels,
        padding_pixels: total_pixels - valid_pixels,
        source: Source {
            chr: file_name(chr_path),
            chr_size: data.len(),
            chr_sha256: sha256_hex(&data),
            prg: file_name(prg_path),
            prg_size: prg.len(),
            prg_sha256: sha256_hex(&prg),
        },
        resource: ResourceInfo {
            address,
            prg_offset: resource_offset,
            images_address: resource.images_address,
            images_prg_offset,
            palette_address: resource.palette_address,
            palette_prg_offset,
            allocation: resource.allocation,
            flags: resource.flags,
            terminator_units: total / sprite::OFFSET_UNIT,
        },
        clut,
        images,
    };

    if let Some(name) = &manifest.contact {
        let group = sheet::Group {
            label: None,
            palette: manifest.clut.display_palette(),
            records: manifest
                .images
                .iter()
                .map(|record| sheet::Record {
                    index: record.index,
                    width: record.pixel_width,
                    height: record.pixel_height,
                    pixels: record_image(&data, record).pixels,
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
    manifest.profile()?;
    if manifest.encoding != ENCODING {
        return Err(Error::Format(format!(
            "{}: unsupported pixel encoding {:?}",
            manifest_path.display(),
            manifest.encoding
        )));
    }
    if manifest.valid_pixels != manifest.source.chr_size * 2 {
        return Err(Error::Format(format!(
            "{}: valid_pixels does not match the CHR size",
            manifest_path.display()
        )));
    }
    let mut end = 0;
    for (position, record) in manifest.images.iter().enumerate() {
        if record.index != position {
            return Err(Error::Format(format!(
                "{}: image indices are not sequential",
                manifest_path.display()
            )));
        }
        if record.file_offset < end
            || record.file_offset + record.byte_count > manifest.source.chr_size
            || record.allocation_size < record.byte_count
            || record.byte_count != record.pixel_width as usize * record.pixel_height as usize / 2
            || record.file_offset != record.offset_units * sprite::OFFSET_UNIT
        {
            return Err(Error::Format(format!(
                "{}: image {} is inconsistent",
                manifest_path.display(),
                record.index
            )));
        }
        end = record.file_offset + record.byte_count;
    }
    Ok(manifest)
}

pub fn rebuild_bytes(manifest_path: &Path) -> Result<Vec<u8>> {
    let manifest = load_manifest(manifest_path)?;
    let root = manifest_path.parent().unwrap_or_else(|| Path::new("."));

    let linear = image::read_indexed(&safe_join(root, &manifest.linear)?)?;
    if (linear.width, linear.height) != (manifest.linear_width, manifest.linear_height) {
        return Err(Error::Format(format!(
            "{} is {}x{}, expected {}x{} (resizing is not supported)",
            manifest.linear,
            linear.width,
            linear.height,
            manifest.linear_width,
            manifest.linear_height
        )));
    }
    if linear.pixels.len() != manifest.valid_pixels + manifest.padding_pixels {
        return Err(Error::Format(format!(
            "{} holds {} pixels, manifest describes {}",
            manifest.linear,
            linear.pixels.len(),
            manifest.valid_pixels + manifest.padding_pixels
        )));
    }
    if let Some(position) = linear.pixels[manifest.valid_pixels..]
        .iter()
        .position(|&pixel| pixel != 0)
    {
        let pixel = manifest.valid_pixels + position;
        return Err(Error::Format(format!(
            "{}: pixel ({}, {}) is past the end of the file -- the last row's \
             padding is visualization only and cannot be edited",
            manifest.linear,
            pixel as u32 % manifest.linear_width,
            pixel as u32 / manifest.linear_width
        )));
    }

    let mut out = pack(&linear.pixels[..manifest.valid_pixels])?;
    for record in &manifest.images {
        let start = record.file_offset;
        let end = start + record.byte_count;
        if sha256_hex(&out[start..end]) != record.sha256 {
            return Err(Error::Format(format!(
                "{} was edited at 0x{start:X}..0x{end:X}, which belongs to \
                 image {}; edit {} instead",
                manifest.linear, record.index, record.file
            )));
        }
        let sprite_image = image::read_indexed(&safe_join(root, &record.file)?)?;
        if (sprite_image.width, sprite_image.height) != (record.pixel_width, record.pixel_height) {
            return Err(Error::Format(format!(
                "{} is {}x{}, expected {}x{} (resizing is not supported)",
                record.file,
                sprite_image.width,
                sprite_image.height,
                record.pixel_width,
                record.pixel_height
            )));
        }
        out[start..end].copy_from_slice(&pack(&sprite_image.pixels)?);
    }

    if out.len() != manifest.source.chr_size {
        return Err(Error::Format(format!(
            "rebuilt {} bytes, retail is {}",
            out.len(),
            manifest.source.chr_size
        )));
    }
    Ok(out)
}

pub fn rebuild(manifest_path: &Path, output_path: &Path) -> Result<Vec<u8>> {
    let data = rebuild_bytes(manifest_path)?;
    if let Some(parent) = output_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(output_path, &data)?;
    Ok(data)
}

pub fn verify(manifest_path: &Path, chr_path: &Path) -> Result<()> {
    let rebuilt = rebuild_bytes(manifest_path)?;
    let retail = std::fs::read(chr_path)?;
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
        "rebuilt familiar CHR does not match {} ({detail})",
        chr_path.display()
    )))
}

pub fn emit_header(manifest: &Manifest) -> Result<String> {
    let profile = manifest.profile()?;
    let symbols = profile.header.ok_or_else(|| {
        Error::Format(format!(
            "{} is not decompiled; only familiars whose tables live in C have \
             a generated header",
            profile.name
        ))
    })?;
    let clut = manifest.clut.values()?;

    let mut out = String::new();
    out.push_str("// SPDX-License-Identifier: AGPL-3.0-or-later\n");
    out.push_str("// Generated by tools/saturn/assets: familiar generate-header.\n");
    out.push_str("// Edit the extracted sprites / CLUT and regenerate; do not hand-edit.\n");
    out.push_str("#include \"sattypes.h\"\n");
    out.push_str("#include <saturn_sprite.h>\n\n");

    out.push_str(&format!(
        "SaturnSpriteImage {}[{}] = {{\n",
        symbols.slices,
        manifest.images.len() + 1
    ));
    for record in &manifest.images {
        out.push_str(&format!(
            "    {{0x{:02X}, 0x{:02X}, 0x{:03X}}},\n",
            record.stored_width, record.stored_height, record.offset_units
        ));
    }
    out.push_str(&format!(
        "    {{0x00, 0x00, 0x{:03X}}},\n}};\n\n",
        manifest.resource.terminator_units
    ));

    out.push_str(&format!(
        "u16 {} = {};\n\n",
        symbols.clut_count, manifest.clut.banks
    ));
    out.push_str(&format!("u16 {}[{}] = {{\n", symbols.clut, clut.len()));
    for row in clut.chunks(8) {
        let values: Vec<String> = row.iter().map(|word| format!("0x{word:04X}")).collect();
        out.push_str(&format!("    {},\n", values.join(", ")));
    }
    out.push_str("};\n\n");
    out.push_str(&format!(
        "u16 {} = {};\n\n",
        symbols.clut_padding, manifest.clut.padding
    ));

    out.push_str(&format!(
        "SaturnSpriteResource {} = {{\n    {},\n    &{},\n    0x{:04X},\n    0x{:04X},\n}};\n\n",
        symbols.resource,
        symbols.slices,
        symbols.clut_count,
        manifest.resource.allocation,
        manifest.resource.flags
    ));
    out.push_str(&format!(
        "SaturnSpriteResource* {}[2] = {{\n    &{},\n    NULL,\n}};\n",
        symbols.descriptors, symbols.resource
    ));
    Ok(out)
}

pub fn generate_header(manifest_path: &Path, output_path: &Path) -> Result<String> {
    let text = emit_header(&load_manifest(manifest_path)?)?;
    if let Some(parent) = output_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(output_path, &text)?;
    Ok(text)
}

pub fn verify_header(manifest_path: &Path, header_path: &Path) -> Result<()> {
    let generated = emit_header(&load_manifest(manifest_path)?)?;
    let checked_in = std::fs::read_to_string(header_path)?;
    if generated == checked_in {
        return Ok(());
    }
    let at = generated
        .lines()
        .zip(checked_in.lines())
        .position(|(a, b)| a != b);
    let detail = match at {
        Some(line) => format!("first difference at line {}", line + 1),
        None => format!(
            "{} generated lines vs {} checked in",
            generated.lines().count(),
            checked_in.lines().count()
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

    #[test]
    fn every_profile_names_a_distinct_familiar_and_file() {
        for profile in PROFILES {
            assert_eq!(super::profile(profile.name).unwrap().chr, profile.chr);
        }
        assert!(super::profile("nosferatu").is_err());
        assert_eq!(PROFILES.iter().filter(|p| p.header.is_some()).count(), 1);
    }

    #[test]
    fn clut_words_parse_and_are_counted_against_their_banks() {
        let clut = Clut {
            banks: 1,
            words: (0..16).map(|i| format!("0x{:04X}", 0x8000 | i)).collect(),
            padding: 0,
        };
        assert_eq!(clut.values().unwrap()[1], 0x8001);
        assert_eq!(
            clut.display_palette().unwrap().len(),
            sprite::PALETTE_BANK_SIZE * 3
        );

        let short = Clut {
            banks: 2,
            words: vec!["0x8000".into()],
            padding: 0,
        };
        assert!(short.values().is_err());
    }

    #[test]
    fn a_clut_word_that_is_not_hex_is_refused() {
        let clut = Clut {
            banks: 1,
            words: (0..16)
                .map(|i| {
                    if i == 3 {
                        "mauve".into()
                    } else {
                        "0x8000".into()
                    }
                })
                .collect(),
            padding: 0,
        };
        assert!(clut.values().is_err());
    }

    #[test]
    fn a_non_canonical_resource_is_not_located() {
        let mut prg = vec![0u8; 256];
        prg[0x40..0x44].copy_from_slice(&[4, 4, 0, 0]);
        prg[0x44..0x48].copy_from_slice(&[0, 0, 0, 16]);
        let table_address = LOAD_ADDRESS + 0x40;

        fn write(prg: &mut [u8], at: usize, table: u32, allocation: u16, flags: u16) {
            prg[at..at + 4].copy_from_slice(&table.to_be_bytes());
            prg[at + 4..at + 8].copy_from_slice(&LOAD_ADDRESS.to_be_bytes());
            prg[at + 8..at + 10].copy_from_slice(&allocation.to_be_bytes());
            prg[at + 10..at + 12].copy_from_slice(&flags.to_be_bytes());
        }
        write(&mut prg, 0x80, table_address, 0x0600, 0xB344);
        assert!(locate_resource(&prg, 128).is_err(), "decoy was accepted");

        write(&mut prg, 0xA0, table_address, 0xFFFF, 0xFFFF);
        let (offset, resource, total) = locate_resource(&prg, 128).unwrap();
        assert_eq!(offset, 0xA0);
        assert_eq!(total, 128);
        assert!(resource.is_canonical());
    }

    #[test]
    fn two_canonical_resources_for_one_chr_are_ambiguous_and_refused() {
        let mut prg = vec![0u8; 256];
        prg[0x40..0x44].copy_from_slice(&[4, 4, 0, 0]);
        prg[0x44..0x48].copy_from_slice(&[0, 0, 0, 16]);
        for at in [0x80usize, 0xA0] {
            prg[at..at + 4].copy_from_slice(&(LOAD_ADDRESS + 0x40).to_be_bytes());
            prg[at + 4..at + 8].copy_from_slice(&LOAD_ADDRESS.to_be_bytes());
            prg[at + 8..at + 12].copy_from_slice(&[0xFF, 0xFF, 0xFF, 0xFF]);
        }
        assert!(locate_resource(&prg, 128).is_err());
    }

    #[test]
    fn a_familiar_without_a_header_profile_refuses_to_emit_one() {
        let manifest = Manifest {
            format: FORMAT.into(),
            version: VERSION,
            familiar: "ghost".into(),
            encoding: ENCODING.into(),
            linear: LINEAR_NAME.into(),
            linear_width: 320,
            linear_height: 1,
            contact: None,
            valid_pixels: 0,
            padding_pixels: 0,
            source: Source {
                chr: "T_GHOST.CHR".into(),
                chr_size: 0,
                chr_sha256: String::new(),
                prg: "T_GHOST.PRG".into(),
                prg_size: 0,
                prg_sha256: String::new(),
            },
            resource: ResourceInfo {
                address: 0,
                prg_offset: 0,
                images_address: 0,
                images_prg_offset: 0,
                palette_address: 0,
                palette_prg_offset: 0,
                allocation: 0xFFFF,
                flags: 0xFFFF,
                terminator_units: 0,
            },
            clut: Clut {
                banks: 0,
                words: Vec::new(),
                padding: 0,
            },
            images: Vec::new(),
        };
        let err = emit_header(&manifest).unwrap_err();
        assert!(matches!(err, Error::Format(_)), "{err}");
    }
}
