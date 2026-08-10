
use crate::image::{self, Indexed};
use crate::sheet;
use crate::sprite::{self, display_palette, pack, read_palette_banks, to_linear};
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::path::{Path, PathBuf};

pub const FORMAT: &str = "sotn-saturn-stage-chr";
pub const VERSION: u32 = 1;
pub const MANIFEST_NAME: &str = "manifest.json";
pub const LINEAR_NAME: &str = "linear.png";
pub const CONTACT_NAME: &str = "contact.png";
pub const SPRITES_DIR: &str = "sprites";
pub const ENCODING: &str = "indexed4-linear-high-nibble-first";

pub const LOAD_ADDRESS: u32 = 0x060D_C000;

pub const ZERO_LOAD_ADDRESS: u32 = 0x0600_4080;

pub const ALIGNMENT: usize = 0x20;

const MAX_BANKS: usize = 256;

const HEADER_SPRITE_BANKS: usize = 0x04;
const HEADER_FIELDS: usize = 10;

#[derive(Debug, Serialize, Deserialize)]
pub struct Source {
    pub chr: String,
    pub chr_size: usize,
    pub chr_sha256: String,
    pub prg: String,
    pub prg_size: usize,
    pub prg_sha256: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ResourceInfo {
    pub bank: usize,
    pub banks: Vec<usize>,
    pub region: Region,
    pub address: u32,
    pub images_address: u32,
    pub palette_address: u32,
    pub base: usize,
    pub size: usize,
    pub resident: bool,
    pub palette_banks: usize,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ImageRecord {
    pub resource: usize,
    pub index: usize,
    pub stored_width: u8,
    pub stored_height: u8,
    pub pixel_width: u32,
    pub pixel_height: u32,
    pub stored_offset: usize,
    pub file_offset: usize,
    pub byte_count: usize,
    pub sha256: String,
    pub file: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Manifest {
    pub format: String,
    pub version: u32,
    pub stage: String,
    pub encoding: String,
    pub linear: String,
    pub linear_width: u32,
    pub linear_height: u32,
    #[serde(skip_serializing_if = "Option::is_none", default)]
    pub contact: Option<String>,
    pub valid_pixels: usize,
    pub padding_pixels: usize,
    pub source: Source,
    pub resources: Vec<ResourceInfo>,
    pub images: Vec<ImageRecord>,
}

fn file_name(path: &Path) -> String {
    path.file_name()
        .map(|n| n.to_string_lossy().into_owned())
        .unwrap_or_else(|| path.display().to_string())
}

fn file_stem(path: &Path) -> String {
    path.file_stem()
        .map(|n| n.to_string_lossy().into_owned())
        .unwrap_or_default()
}

fn safe_join(root: &Path, relative: &str) -> Result<PathBuf> {
    let path = Path::new(relative);
    if path.is_absolute()
        || path
            .components()
            .any(|c| matches!(c, std::path::Component::ParentDir))
    {
        return Err(Error::Format(format!(
            "manifest contains an unsafe path: {relative}"
        )));
    }
    Ok(root.join(path))
}

fn read_u32(data: &[u8], at: usize) -> Result<u32> {
    data.get(at..at + 4)
        .map(|b| u32::from_be_bytes([b[0], b[1], b[2], b[3]]))
        .ok_or_else(|| Error::Format(format!("u32 at 0x{at:X} lies outside the overlay")))
}

fn resolve(prg: &[u8], address: u32) -> Option<usize> {
    let offset = address.checked_sub(LOAD_ADDRESS)? as usize;
    (offset < prg.len()).then_some(offset)
}

pub struct Overlay<'a> {
    pub stage: &'a [u8],
    pub zero: Option<&'a [u8]>,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
#[serde(rename_all = "lowercase")]
pub enum Region {
    Stage,
    Zero,
}

impl<'a> Overlay<'a> {
    pub fn new(stage: &'a [u8], zero: Option<&'a [u8]>) -> Self {
        Overlay { stage, zero }
    }

    pub fn resolve(&self, address: u32) -> Option<(Region, &'a [u8], usize)> {
        if let Some(offset) = resolve(self.stage, address) {
            return Some((Region::Stage, self.stage, offset));
        }
        let zero = self.zero?;
        let offset = address.checked_sub(ZERO_LOAD_ADDRESS)? as usize;
        (offset < zero.len()).then_some((Region::Zero, zero, offset))
    }

    pub fn holds(&self, address: u32) -> bool {
        self.resolve(address).is_some()
    }
}

pub fn looks_like_stage(prg: &[u8]) -> bool {
    (0..HEADER_FIELDS).all(|field| {
        read_u32(prg, field * 4)
            .ok()
            .and_then(|address| resolve(prg, address))
            .is_some()
    })
}

pub fn sprite_banks(overlay: &Overlay) -> Result<Vec<u32>> {
    let table = read_u32(overlay.stage, HEADER_SPRITE_BANKS)?;
    let table = resolve(overlay.stage, table).ok_or_else(|| {
        Error::Format(format!(
            "the sprite bank table at 0x{table:08X} is outside the overlay"
        ))
    })?;
    let mut banks = Vec::new();
    for index in 0..MAX_BANKS {
        let Ok(address) = read_u32(overlay.stage, table + index * 4) else {
            break;
        };
        if !overlay.holds(address) {
            break;
        }
        banks.push(address);
    }
    if banks.is_empty() {
        return Err(Error::Format("the sprite bank table is empty".to_string()));
    }
    Ok(banks)
}

pub fn resources(
    overlay: &Overlay,
    chr_size: usize,
) -> Result<(Vec<ResourceInfo>, Vec<ImageRecord>)> {
    let banks = sprite_banks(overlay)?;
    let mut infos: Vec<ResourceInfo> = Vec::new();
    let mut images: Vec<ImageRecord> = Vec::new();
    let mut seen: std::collections::HashMap<u32, usize> = std::collections::HashMap::new();
    let mut cursor = 0usize;

    for (bank, &address) in banks.iter().enumerate() {
        let Some((region, data, offset)) = overlay.resolve(address) else {
            continue;
        };
        let Some(resource) = sprite::Resource::read(data, offset) else {
            continue;
        };
        if !resource.is_canonical() {
            continue;
        }
        let (Some((_, images_data, images_offset)), true) = (
            overlay.resolve(resource.images_address),
            overlay.holds(resource.palette_address),
        ) else {
            continue;
        };
        if let Some(&index) = seen.get(&resource.images_address) {
            infos[index].banks.push(bank);
            continue;
        }

        let records = image_table(images_data, images_offset)?;
        let base = cursor;
        let index = infos.len();
        let resident = base < chr_size;
        for record in &records {
            let start = cursor;
            let end = start + record.byte_count;
            if resident && end > chr_size {
                return Err(Error::Format(format!(
                    "resource {index} image {} runs to 0x{end:X}, past the end of the \
                     {chr_size}-byte CHR while the rest of the resource is inside it",
                    record.index
                )));
            }
            if !resident {
                cursor = start + record.byte_count.next_multiple_of(ALIGNMENT);
                continue;
            }
            images.push(ImageRecord {
                resource: index,
                index: record.index,
                stored_width: record.stored_width,
                stored_height: record.stored_height,
                pixel_width: record.stored_width as u32 * 2,
                pixel_height: record.stored_height as u32 * 2,
                stored_offset: record.stored_offset,
                file_offset: start,
                byte_count: record.byte_count,
                sha256: String::new(),
                file: format!("{SPRITES_DIR}/{index:02}/{:03}.png", record.index),
            });
            cursor = start + record.byte_count.next_multiple_of(ALIGNMENT);
        }

        let palette_banks = overlay
            .resolve(resource.palette_address)
            .map(|(_, data, offset)| sprite::bank_count(data, offset))
            .unwrap_or(0);
        seen.insert(resource.images_address, index);
        infos.push(ResourceInfo {
            bank,
            banks: vec![bank],
            region,
            address,
            images_address: resource.images_address,
            palette_address: resource.palette_address,
            base,
            size: cursor - base,
            resident,
            palette_banks,
        });
    }

    if infos.is_empty() {
        return Err(Error::Format(
            "the overlay's sprite banks hold no sprite resources".to_string(),
        ));
    }
    Ok((infos, images))
}

struct Record {
    index: usize,
    stored_width: u8,
    stored_height: u8,
    stored_offset: usize,
    byte_count: usize,
}

fn image_table(data: &[u8], table_offset: usize) -> Result<Vec<Record>> {
    let mut records = Vec::new();
    for index in 0..sprite::MAX_IMAGES {
        let at = table_offset + index * 4;
        let Some(entry) = data.get(at..at + 4) else {
            return Err(Error::Format(format!(
                "the image table at 0x{table_offset:X} runs past the end of the overlay"
            )));
        };
        let (stored_width, stored_height) = (entry[0], entry[1]);
        if stored_width == 0 || stored_height == 0 {
            break;
        }
        records.push(Record {
            index,
            stored_width,
            stored_height,
            stored_offset: u16::from_be_bytes([entry[2], entry[3]]) as usize * sprite::OFFSET_UNIT,
            byte_count: stored_width as usize * stored_height as usize * 2,
        });
    }
    if records.is_empty() {
        return Err(Error::Format(format!(
            "the image table at 0x{table_offset:X} is empty"
        )));
    }
    Ok(records)
}

fn record_image(data: &[u8], record: &ImageRecord) -> Indexed {
    let mut picture = Indexed::new(record.pixel_width, record.pixel_height);
    let pixels = sprite::unpack(&data[record.file_offset..record.file_offset + record.byte_count]);
    picture.pixels[..pixels.len()].copy_from_slice(&pixels);
    picture
}

pub fn extract(
    prg_path: &Path,
    chr_path: &Path,
    zero_path: Option<&Path>,
    output_dir: &Path,
) -> Result<Manifest> {
    let prg_path = if prg_path.is_dir() {
        prg_path.join(format!("{}.PRG", file_stem(chr_path)))
    } else {
        prg_path.to_path_buf()
    };
    let prg = std::fs::read(&prg_path)?;
    let zero = zero_path.map(std::fs::read).transpose()?;
    let overlay = Overlay::new(&prg, zero.as_deref());
    let data = std::fs::read(chr_path)?;
    if data.is_empty() {
        return Err(Error::Format(format!("{} is empty", chr_path.display())));
    }
    if !looks_like_stage(&prg) {
        return Err(Error::Format(format!(
            "{} does not open with a stage data header",
            file_name(&prg_path)
        )));
    }

    let (infos, mut images) = resources(&overlay, data.len())?;
    if infos.iter().all(|info| !info.resident) {
        return Err(Error::Format(format!(
            "{} holds none of the overlay's sprite resources",
            file_name(chr_path)
        )));
    }
    for record in &mut images {
        record.sha256 =
            sha256_hex(&data[record.file_offset..record.file_offset + record.byte_count]);
    }

    let linear = to_linear(&data);
    let valid_pixels = data.len() * 2;
    let total_pixels = (linear.width * linear.height) as usize;

    std::fs::create_dir_all(output_dir)?;
    image::write_indexed(&output_dir.join(LINEAR_NAME), &linear)?;
    let palettes: Vec<Option<Vec<u8>>> = infos
        .iter()
        .map(|info| {
            overlay
                .resolve(info.palette_address)
                .map(|(_, data, offset)| display_palette(&read_palette_banks(data, offset)))
                .unwrap_or(None)
        })
        .collect();
    for record in &images {
        image::write_indexed_palette(
            &safe_join(output_dir, &record.file)?,
            &record_image(&data, record),
            palettes[record.resource].as_deref(),
        )?;
    }

    let manifest = Manifest {
        format: FORMAT.to_string(),
        version: VERSION,
        stage: file_stem(chr_path),
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
            prg: file_name(&prg_path),
            prg_size: prg.len(),
            prg_sha256: sha256_hex(&prg),
        },
        resources: infos,
        images,
    };

    if let Some(name) = &manifest.contact {
        let groups: Vec<sheet::Group> = manifest
            .resources
            .iter()
            .enumerate()
            .map(|(index, _info)| sheet::Group {
                label: Some(index),
                palette: palettes[index].clone(),
                records: manifest
                    .images
                    .iter()
                    .filter(|record| record.resource == index)
                    .map(|record| sheet::Record {
                        index: record.index,
                        width: record.pixel_width,
                        height: record.pixel_height,
                        pixels: record_image(&data, record).pixels,
                    })
                    .collect(),
            })
            .collect();
        image::write_rgba(&output_dir.join(name), &sheet::build(&groups))?;
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
        if end > out.len() {
            return Err(Error::Format(format!(
                "resource {} image {} ends past the end of the arena",
                record.resource, record.index
            )));
        }
        if sha256_hex(&out[start..end]) != record.sha256 {
            return Err(Error::Format(format!(
                "{} was edited at 0x{start:X}..0x{end:X}, which belongs to \
                 resource {} image {}; edit {} instead",
                manifest.linear, record.resource, record.index, record.file
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
        "rebuilt stage CHR does not match {} ({detail})",
        chr_path.display()
    )))
}

#[cfg(test)]
mod tests {
    use super::*;

    fn overlay() -> Vec<u8> {
        let mut prg = vec![0u8; 0x200];
        let put = |prg: &mut Vec<u8>, at: usize, value: u32| {
            prg[at..at + 4].copy_from_slice(&value.to_be_bytes());
        };
        for field in 0..HEADER_FIELDS {
            put(&mut prg, field * 4, LOAD_ADDRESS + 0x40);
        }
        put(&mut prg, HEADER_SPRITE_BANKS, LOAD_ADDRESS + 0x40);
        put(&mut prg, 0x40, LOAD_ADDRESS + 0x60);
        put(&mut prg, 0x44, 0);
        put(&mut prg, 0x60, LOAD_ADDRESS + 0x80);
        put(&mut prg, 0x64, LOAD_ADDRESS + 0xC0);
        put(&mut prg, 0x68, 0xFFFF_FFFF);
        prg[0x80..0x84].copy_from_slice(&[4, 4, 0, 0]);
        prg[0x84..0x88].copy_from_slice(&[4, 4, 0, 4]);
        prg[0x88..0x8C].copy_from_slice(&[0, 0, 0, 8]);
        prg
    }

    #[test]
    fn a_stage_header_is_recognised_and_a_garbage_one_is_not() {
        assert!(looks_like_stage(&overlay()));
        assert!(!looks_like_stage(&vec![0xFF; 0x100]));
    }

    #[test]
    fn images_are_allocated_in_order_on_alignment_boundaries() {
        let prg = overlay();
        let overlay = Overlay::new(&prg, None);
        let (infos, images) = resources(&overlay, 0x100).expect("resources");
        assert_eq!(infos.len(), 1);
        assert_eq!(images.len(), 2);
        assert_eq!(images[0].file_offset, 0);
        assert_eq!(images[0].byte_count, 32);
        assert_eq!(images[1].file_offset, 32);
        assert_eq!(infos[0].size, 64);
    }

    #[test]
    fn a_resource_that_does_not_fit_the_chr_is_refused() {
        let prg = overlay();
        assert!(resources(&Overlay::new(&prg, None), 16).is_err());
    }

    #[test]
    fn a_bank_pointing_at_a_non_resource_is_skipped() {
        let mut prg = overlay();
        prg[0x68..0x6C].copy_from_slice(&[0, 1, 0, 2]);
        assert!(resources(&Overlay::new(&prg, None), 0x100).is_err());
    }

    #[test]
    fn one_resource_loaded_from_two_banks_is_allocated_once() {
        let mut prg = overlay();
        prg[0x44..0x48].copy_from_slice(&(LOAD_ADDRESS + 0x60).to_be_bytes());
        let overlay = Overlay::new(&prg, None);
        let (infos, images) = resources(&overlay, 0x100).expect("resources");
        assert_eq!(infos.len(), 1, "the same resource was allocated twice");
        assert_eq!(infos[0].banks, vec![0, 1]);
        assert_eq!(images.len(), 2);
    }
}
