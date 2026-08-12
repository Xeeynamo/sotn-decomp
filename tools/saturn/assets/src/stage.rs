
use crate::image::{self, Indexed};
use crate::player;
use crate::sheet;
use crate::sprite::{self, display_palette, pack, read_palette_banks, to_linear};
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::collections::BTreeMap;
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
    pub base: u32,
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
        Self::with_base(LOAD_ADDRESS, stage, zero)
    }

    pub fn with_base(base: u32, stage: &'a [u8], zero: Option<&'a [u8]>) -> Self {
        Overlay { base, stage, zero }
    }

    pub fn resolve(&self, address: u32) -> Option<(Region, &'a [u8], usize)> {
        if let Some(offset) = address.checked_sub(self.base) {
            let offset = offset as usize;
            if offset < self.stage.len() {
                return Some((Region::Stage, self.stage, offset));
            }
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

pub(crate) struct Record {
    pub(crate) index: usize,
    pub(crate) stored_width: u8,
    pub(crate) stored_height: u8,
    pub(crate) stored_offset: usize,
    pub(crate) byte_count: usize,
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


const HEADER_ENTITY_ENTRIES: usize = 0x00;
const MAX_ENTITIES: usize = 256;
const MAX_FRAMES: usize = 256;

fn overlay_bytes<'a>(overlay: &Overlay<'a>, address: u32, len: usize) -> Result<&'a [u8]> {
    let (_, data, offset) = overlay
        .resolve(address)
        .ok_or_else(|| Error::Format(format!("address 0x{address:08X} is outside the overlay")))?;
    data.get(offset..offset + len).ok_or_else(|| {
        Error::Format(format!(
            "address 0x{address:08X}+{len} runs past the end of its region"
        ))
    })
}

fn overlay_u8(overlay: &Overlay, address: u32) -> Result<u8> {
    Ok(overlay_bytes(overlay, address, 1)?[0])
}

fn overlay_u32(overlay: &Overlay, address: u32) -> Result<u32> {
    Ok(u32::from_be_bytes(
        overlay_bytes(overlay, address, 4)?.try_into().unwrap(),
    ))
}

fn overlay_u16(overlay: &Overlay, address: u32) -> Result<u16> {
    Ok(u16::from_be_bytes(
        overlay_bytes(overlay, address, 2)?.try_into().unwrap(),
    ))
}

fn overlay_s16(overlay: &Overlay, address: u32) -> Result<i16> {
    Ok(overlay_u16(overlay, address)? as i16)
}

fn wrap(items: &[String], indent: &str) -> Vec<String> {
    const WIDTH: usize = 79;
    let mut lines = Vec::new();
    let mut current = indent.to_string();
    for item in items {
        let candidate = if current.trim().is_empty() {
            format!("{indent}{item}")
        } else {
            format!("{current} {item}")
        };
        if !current.trim().is_empty() && candidate.len() > WIDTH {
            lines.push(current);
            current = format!("{indent}{item}");
        } else {
            current = candidate;
        }
    }
    if !current.trim().is_empty() {
        lines.push(current);
    }
    lines
}

struct EntityEntry {
    index: usize,
    resource_address: u32,
}

fn entity_entries(overlay: &Overlay, limit: usize) -> Result<Vec<EntityEntry>> {
    let table = read_u32(overlay.stage, HEADER_ENTITY_ENTRIES)?;
    let table = resolve(overlay.stage, table).ok_or_else(|| {
        Error::Format(format!(
            "the entity entry table at 0x{table:08X} is outside the overlay"
        ))
    })?;
    let mut entries = Vec::new();
    for index in 0..limit {
        let Ok(entry_address) = read_u32(overlay.stage, table + index * 4) else {
            break;
        };
        if entry_address == 0 || !overlay.holds(entry_address) {
            break;
        }
        let resource_address = overlay_u32(overlay, entry_address)?;
        entries.push(EntityEntry {
            index,
            resource_address,
        });
    }
    Ok(entries)
}

fn entity_entry(overlay: &Overlay, index: usize) -> Result<EntityEntry> {
    entity_entries(overlay, (index + 1).min(MAX_ENTITIES))?
        .into_iter()
        .find(|entry| entry.index == index)
        .ok_or_else(|| {
            Error::Format(format!(
                "entity index {index} is past the end of the entity entry table"
            ))
        })
}

#[derive(Debug, Clone)]
struct FramePart {
    attributes: u16,
    x: i16,
    y: i16,
    image: u16,
}

impl FramePart {
    fn palette(&self) -> u16 {
        (self.attributes >> 8) & 0x3F
    }
}

#[derive(Debug, Clone)]
struct Frame {
    header_word: u16,
    command_flags: u16,
    parts: Vec<FramePart>,
}

fn frame_part_count(overlay: &Overlay, address: u32) -> Result<u16> {
    Ok((overlay_u16(overlay, address)? >> 8) & 0x3F)
}

fn frame_size(overlay: &Overlay, address: u32) -> Result<u32> {
    Ok(4 + u32::from(frame_part_count(overlay, address)?) * 8)
}

fn frame_parts(overlay: &Overlay, address: u32) -> Result<Vec<FramePart>> {
    let count = frame_part_count(overlay, address)?;
    let mut parts = Vec::with_capacity(count as usize);
    for index in 0..u32::from(count) {
        let part = address + 4 + index * 8;
        parts.push(FramePart {
            attributes: overlay_u16(overlay, part)?,
            x: overlay_s16(overlay, part + 2)?,
            y: overlay_s16(overlay, part + 4)?,
            image: overlay_u16(overlay, part + 6)?,
        });
    }
    Ok(parts)
}

fn read_frame(overlay: &Overlay, address: u32) -> Result<Frame> {
    Ok(Frame {
        header_word: overlay_u16(overlay, address)?,
        command_flags: overlay_u16(overlay, address + 2)?,
        parts: frame_parts(overlay, address)?,
    })
}

fn frame_struct_type(part_count: usize) -> String {
    if part_count == 0 {
        "SaturnSpriteFrameHeader".to_string()
    } else {
        format!("SaturnSpriteFrame{part_count}")
    }
}

fn render_frame(name: &str, frame: &Frame) -> Vec<String> {
    let type_name = frame_struct_type(frame.parts.len());
    let header = format!("0x{:04X}, 0x{:04X}", frame.header_word, frame.command_flags);
    if frame.parts.is_empty() {
        return vec![format!("{type_name} {name} = {{{header}}};")];
    }
    let mut lines = vec![format!("{type_name} {name} = {{"), format!("    {{{header}}},"), "    {".to_string()];
    for part in &frame.parts {
        lines.push(format!(
            "        {{0x{:04X}, {}, {}, {}}},",
            part.attributes, part.x, part.y, part.image
        ));
    }
    lines.push("    },".to_string());
    lines.push("};".to_string());
    lines
}

fn frame_table_shape(
    overlay: &Overlay,
    address: u32,
    image_count: usize,
    palette_count: usize,
    cap: usize,
) -> (usize, bool) {
    let mut count = 0usize;
    let mut previous: Option<u32> = None;
    let mut clean = true;
    while count < cap {
        let descriptor = match overlay_u32(overlay, address + (count * 4) as u32) {
            Ok(value) if value != 0 && overlay.holds(value) => value,
            _ => break,
        };
        if previous.is_some_and(|previous| descriptor <= previous) {
            break;
        }
        let parts = match frame_parts(overlay, descriptor) {
            Ok(parts) => parts,
            Err(_) => {
                clean = false;
                break;
            }
        };
        if parts.iter().any(|part| {
            part.image as usize >= image_count || part.palette() as usize >= palette_count
        }) {
            clean = false;
            break;
        }
        previous = Some(descriptor);
        count += 1;
    }
    (count, clean)
}

fn frame_table(overlay: &Overlay, address: u32, count: usize) -> Result<Vec<u32>> {
    (0..count)
        .map(|index| overlay_u32(overlay, address + (index * 4) as u32))
        .collect()
}

fn palette_banks(overlay: &Overlay, address: u32) -> Result<u32> {
    Ok(u32::from(overlay_u16(overlay, address)? & 0x3FFF))
}

fn palette_size(overlay: &Overlay, address: u32, padding_words: u32) -> Result<u32> {
    Ok(2 + palette_banks(overlay, address)? * 32 + padding_words * 2)
}

fn raw_palette(overlay: &Overlay, address: u32, padding_words: u32) -> Result<(u16, Vec<[u16; 16]>, Vec<u16>)> {
    let count_field = overlay_u16(overlay, address)?;
    let bank_count = palette_banks(overlay, address)? as usize;
    let mut banks = Vec::with_capacity(bank_count);
    for bank in 0..bank_count {
        let base = address + 2 + (bank * 32) as u32;
        let mut colors = [0u16; 16];
        for (index, color) in colors.iter_mut().enumerate() {
            *color = overlay_u16(overlay, base + (index * 2) as u32)?;
        }
        banks.push(colors);
    }
    let padding_base = address + 2 + (bank_count * 32) as u32;
    let mut padding = Vec::with_capacity(padding_words as usize);
    for index in 0..padding_words {
        padding.push(overlay_u16(overlay, padding_base + index * 2)?);
    }
    Ok((count_field, banks, padding))
}

fn render_palette(name: &str, count_field: u16, banks: &[[u16; 16]], padding: &[u16]) -> Vec<String> {
    let bank_count = banks.len();
    let mut lines = vec![
        "struct {".to_string(),
        "    u16 countAndFlags;".to_string(),
        format!("    u16 colors[{bank_count}][16];"),
    ];
    if !padding.is_empty() {
        lines.push(format!("    u16 padding[{}];", padding.len()));
    }
    lines.push(format!("}} {name} = {{"));
    lines.push(format!("    0x{count_field:04X},"));
    lines.push("    {".to_string());
    for bank in banks {
        let values: Vec<String> = bank.iter().map(|value| format!("0x{value:04X},")).collect();
        lines.push("        {".to_string());
        lines.extend(wrap(&values, "            "));
        lines.push("        },".to_string());
    }
    lines.push("    },".to_string());
    if !padding.is_empty() {
        let values: Vec<String> = padding.iter().map(|value| format!("0x{value:04X}")).collect();
        lines.push(format!("    {{{}}},", values.join(", ")));
    }
    lines.push("};".to_string());
    lines
}

fn images_with_sentinel(overlay: &Overlay, address: u32) -> Result<(Vec<Record>, u32)> {
    let (_, data, offset) = overlay
        .resolve(address)
        .ok_or_else(|| Error::Format(format!("image table at 0x{address:08X} is outside the overlay")))?;
    let mut records = image_table(data, offset)?;
    let real_count = records.len();
    let terminator = address + (real_count as u32) * 4;
    let terminator_units = overlay_u16(overlay, terminator + 2)?;
    records.push(Record {
        index: real_count,
        stored_width: 0,
        stored_height: 0,
        stored_offset: terminator_units as usize * sprite::OFFSET_UNIT,
        byte_count: 0,
    });
    Ok((records, (real_count as u32 + 1) * 4))
}

fn render_images(name: &str, records: &[Record]) -> Vec<String> {
    let items: Vec<String> = records
        .iter()
        .map(|record| {
            format!(
                "{{{}, {}, 0x{:04X}}},",
                record.stored_width,
                record.stored_height,
                record.stored_offset / sprite::OFFSET_UNIT
            )
        })
        .collect();
    let mut lines = vec![format!("SaturnSpriteImage {name}[{}] = {{", records.len())];
    lines.extend(wrap(&items, "    "));
    lines.push("};".to_string());
    lines
}

struct EntityHeaderData {
    prefix: String,
    images: Vec<Record>,
    palette_count_field: u16,
    palette_banks: Vec<[u16; 16]>,
    palette_padding: Vec<u16>,
    resource: sprite::Resource,
    frames: Vec<Frame>,
}

fn collect_entity_header(
    overlay: &Overlay,
    entity_index: usize,
    frames_address: u32,
    prefix: &str,
) -> Result<EntityHeaderData> {
    let entry = entity_entry(overlay, entity_index)?;
    let (_, resource_data, resource_offset) =
        overlay.resolve(entry.resource_address).ok_or_else(|| {
            Error::Format(format!(
                "entity {entity_index}'s resource at 0x{:08X} is outside the overlay",
                entry.resource_address
            ))
        })?;
    let resource = sprite::Resource::read(resource_data, resource_offset).ok_or_else(|| {
        Error::Format(format!(
            "entity {entity_index}'s resource at 0x{:08X} does not fit in its region",
            entry.resource_address
        ))
    })?;

    let (images, _) = images_with_sentinel(overlay, resource.images_address).map_err(|error| {
        Error::Format(format!("entity {entity_index}'s image table: {error}"))
    })?;
    let real_image_count = images.len() - 1;

    let (palette_count_field, palette_banks, palette_padding) =
        raw_palette(overlay, resource.palette_address, 1)?;

    let (frame_count, clean) = frame_table_shape(
        overlay,
        frames_address,
        real_image_count,
        palette_banks.len(),
        MAX_FRAMES,
    );
    if !clean || frame_count == 0 {
        return Err(Error::Format(format!(
            "entity {entity_index}'s frame table at 0x{frames_address:08X} does not end \
             cleanly; refusing to generate a header from it"
        )));
    }
    let mut frames = Vec::with_capacity(frame_count);
    for pointer in frame_table(overlay, frames_address, frame_count)? {
        frames.push(read_frame(overlay, pointer)?);
    }

    Ok(EntityHeaderData {
        prefix: prefix.to_string(),
        images,
        palette_count_field,
        palette_banks,
        palette_padding,
        resource,
        frames,
    })
}

fn emit_entity_header(data: &EntityHeaderData) -> String {
    let prefix = &data.prefix;
    let mut out = String::new();
    out.push_str("// SPDX-License-Identifier: AGPL-3.0-or-later\n");
    out.push_str("// Generated by tools/saturn/assets: stage entity-header.\n");
    out.push_str("// Edit the entity's images/palette/frames and regenerate this file;\n");
    out.push_str("// do not hand-edit it.\n");
    out.push_str("#include \"sattypes.h\"\n");
    out.push_str("#include <saturn_sprite.h>\n\n");

    for (index, frame) in data.frames.iter().enumerate() {
        for line in render_frame(&format!("{prefix}Frame{index}"), frame) {
            out.push_str(&line);
            out.push('\n');
        }
        out.push('\n');
    }

    out.push_str(&format!(
        "SaturnSpriteFrameHeader* {prefix}Frames[{}] = {{\n",
        data.frames.len()
    ));
    for index in 0..data.frames.len() {
        out.push_str(&format!(
            "    (SaturnSpriteFrameHeader*)&{prefix}Frame{index},\n"
        ));
    }
    out.push_str("};\n\n");

    for line in render_palette(
        &format!("{prefix}Palettes"),
        data.palette_count_field,
        &data.palette_banks,
        &data.palette_padding,
    ) {
        out.push_str(&line);
        out.push('\n');
    }
    out.push('\n');

    for line in render_images(&format!("{prefix}Images"), &data.images) {
        out.push_str(&line);
        out.push('\n');
    }
    out.push('\n');

    out.push_str(&format!("SaturnSpriteResource {prefix}Resource = {{\n"));
    out.push_str(&format!("    {prefix}Images,\n"));
    out.push_str(&format!("    (u16*)&{prefix}Palettes,\n"));
    out.push_str(&format!("    {},\n", data.resource.allocation as i16));
    out.push_str(&format!("    0x{:04X},\n", data.resource.flags));
    out.push_str("};\n");

    out
}

fn open_entity_overlay(prg_path: &Path, zero_path: Option<&Path>) -> Result<(Vec<u8>, Option<Vec<u8>>)> {
    let prg = std::fs::read(prg_path)?;
    if !looks_like_stage(&prg) {
        return Err(Error::Format(format!(
            "{} does not open with a stage data header",
            file_name(prg_path)
        )));
    }
    let zero = zero_path.map(std::fs::read).transpose()?;
    Ok((prg, zero))
}

pub fn generate_entity_header(
    prg_path: &Path,
    zero_path: Option<&Path>,
    entity_index: usize,
    frames_address: u32,
    prefix: &str,
    output_path: &Path,
) -> Result<String> {
    let (prg, zero) = open_entity_overlay(prg_path, zero_path)?;
    let overlay = Overlay::new(&prg, zero.as_deref());
    let data = collect_entity_header(&overlay, entity_index, frames_address, prefix)?;
    let text = emit_entity_header(&data);
    if let Some(parent) = output_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(output_path, &text)?;
    Ok(text)
}

pub fn verify_entity_header(
    prg_path: &Path,
    zero_path: Option<&Path>,
    entity_index: usize,
    frames_address: u32,
    prefix: &str,
    output_path: &Path,
) -> Result<()> {
    let (prg, zero) = open_entity_overlay(prg_path, zero_path)?;
    let overlay = Overlay::new(&prg, zero.as_deref());
    let data = collect_entity_header(&overlay, entity_index, frames_address, prefix)?;
    let text = emit_entity_header(&data);
    let existing = std::fs::read_to_string(output_path)?;
    if existing != text {
        let at = text
            .lines()
            .zip(existing.lines())
            .position(|(a, b)| a != b)
            .map(|line| format!("first difference at line {}", line + 1))
            .unwrap_or_else(|| "line counts differ".to_string());
        return Err(Error::Mismatch(format!(
            "regenerating does not reproduce {} ({at}); it must never be hand-edited",
            output_path.display()
        )));
    }
    Ok(())
}


const GENERATED_PACKAGE_HEADER: [&str; 4] = [
    "// SPDX-License-Identifier: AGPL-3.0-or-later",
    "// Generated by tools/saturn/assets: sprite-package generate-header.",
    "// Edit the sprite images/palette/frames and regenerate this file;",
    "// do not hand-edit it.",
];

#[derive(Debug, Deserialize)]
struct AssetsConfig {
    assets: Vec<PackageSpec>,
}

#[derive(Debug, Deserialize, Clone)]
pub struct PackageSpec {
    pub name: String,
    #[serde(default)]
    pub kind: String,
    #[serde(default)]
    pub prg: String,
    #[serde(default)]
    pub zero: String,
    #[serde(default)]
    pub base: String,
    #[serde(default)]
    pub address: String,
    #[serde(default)]
    pub symbols: Vec<SymbolSpec>,
    #[serde(default)]
    pub include: String,
}

#[derive(Debug, Deserialize, Clone)]
pub struct SymbolSpec {
    #[serde(default)]
    pub name: String,
    pub kind: String,
    #[serde(default)]
    pub padding: u32,
    #[serde(default)]
    pub count: u32,
    #[serde(default)]
    pub prefix: String,
}

pub fn load_packages(path: &Path) -> Result<Vec<PackageSpec>> {
    let text = std::fs::read_to_string(path)?;
    let config: AssetsConfig = serde_yaml::from_str(&text)
        .map_err(|error| Error::Format(format!("{}: {error}", path.display())))?;
    Ok(config
        .assets
        .into_iter()
        .filter(|a| a.kind == "sprite-package")
        .collect())
}

fn find_package<'a>(packages: &'a [PackageSpec], name: &str) -> Result<&'a PackageSpec> {
    packages
        .iter()
        .find(|p| p.name == name)
        .ok_or_else(|| Error::Format(format!("{name} is not a sprite-package asset")))
}

fn parse_hex(text: &str) -> Result<u32> {
    let digits = text.strip_prefix("0x").or_else(|| text.strip_prefix("0X")).unwrap_or(text);
    u32::from_str_radix(digits, 16)
        .map_err(|error| Error::Format(format!("{text:?} is not a hex number: {error}")))
}

struct PackageFiles {
    zero_bytes: Vec<u8>,
    prg_bytes: BTreeMap<String, Vec<u8>>,
}

impl PackageFiles {
    fn load(packages: &[PackageSpec]) -> Result<Self> {
        let zero_path = packages
            .first()
            .map(|p| if p.zero.is_empty() { p.prg.clone() } else { p.zero.clone() })
            .ok_or_else(|| Error::Format("no sprite-package assets declared".to_string()))?;
        let zero_bytes = std::fs::read(&zero_path)?;
        let mut prg_bytes = BTreeMap::new();
        for package in packages {
            if !prg_bytes.contains_key(&package.prg) {
                prg_bytes.insert(package.prg.clone(), std::fs::read(&package.prg)?);
            }
        }
        Ok(PackageFiles { zero_bytes, prg_bytes })
    }

    fn overlay(&self, package: &PackageSpec) -> Result<Overlay<'_>> {
        let base = parse_hex(&package.base)?;
        let data = self
            .prg_bytes
            .get(&package.prg)
            .ok_or_else(|| Error::Format(format!("{} was not loaded", package.prg)))?;
        let zero = (!package.zero.is_empty()).then_some(self.zero_bytes.as_slice());
        Ok(Overlay::with_base(base, data, zero))
    }
}

fn shape_of(kind: &str) -> Result<&'static str> {
    match kind {
        "images" => Ok("array"),
        "palette" => Ok("struct"),
        "resource" => Ok("struct"),
        "resource_array" => Ok("array"),
        "texture" => Ok("struct"),
        "pointers" | "frames" | "sprite_parts" => Ok("array"),
        other => Err(Error::Format(format!("unsupported kind {other:?}"))),
    }
}

fn symbol_size(overlay: &Overlay, address: u32, spec: &SymbolSpec) -> Result<u32> {
    Ok(match spec.kind.as_str() {
        "images" => images_with_sentinel(overlay, address)?.1,
        "palette" => palette_size(overlay, address, spec.padding)?,
        "resource" => 12,
        "resource_array" => spec.count * 12,
        "frames" | "pointers" | "sprite_parts" => spec.count * 4,
        "texture" => 514,
        other => return Err(Error::Format(format!("unsupported kind {other:?}"))),
    })
}

fn record_package_symbols(
    files: &PackageFiles,
    package: &PackageSpec,
    by_address: &mut BTreeMap<u32, (String, String)>,
) -> Result<()> {
    let overlay = files.overlay(package)?;
    let mut cursor = parse_hex(&package.address)?;
    for spec in &package.symbols {
        if spec.kind == "frame_group" {
            for index in 0..spec.count {
                let name = format!("{}Frame{index}", spec.prefix);
                let size = frame_size(&overlay, cursor)?;
                by_address.entry(cursor).or_insert((name, "struct".to_string()));
                cursor += size;
            }
            continue;
        }
        let size = symbol_size(&overlay, cursor, spec)?;
        let shape = shape_of(&spec.kind)?;
        by_address
            .entry(cursor)
            .or_insert((spec.name.clone(), shape.to_string()));
        cursor += size;
    }
    Ok(())
}

fn render_package_images(overlay: &Overlay, address: u32, name: &str) -> Result<(Vec<String>, u32)> {
    let (records, size) = images_with_sentinel(overlay, address)?;
    Ok((render_images(name, &records), size))
}

fn render_package_palette(
    overlay: &Overlay,
    address: u32,
    name: &str,
    padding_words: u32,
) -> Result<(Vec<String>, u32)> {
    let (count_field, banks, padding) = raw_palette(overlay, address, padding_words)?;
    let lines = render_palette(name, count_field, &banks, &padding);
    Ok((lines, palette_size(overlay, address, padding_words)?))
}

fn render_package_frame(overlay: &Overlay, address: u32, name: &str) -> Result<(Vec<String>, u32)> {
    let frame = read_frame(overlay, address)?;
    let size = frame_size(overlay, address)?;
    Ok((render_frame(name, &frame), size))
}

fn resource_fields(overlay: &Overlay, names: &mut Names, address: u32) -> Result<(String, String, sprite::Resource)> {
    let (_, data, offset) = overlay
        .resolve(address)
        .ok_or_else(|| Error::Format(format!("resource at 0x{address:08X} is outside the overlay")))?;
    let resource = sprite::Resource::read(data, offset)
        .ok_or_else(|| Error::Format(format!("resource at 0x{address:08X} does not fit in its region")))?;
    let images = if resource.images_address != 0 {
        names.reference(resource.images_address, Some("SaturnSpriteImage"))?
    } else {
        "NULL".to_string()
    };
    let palettes = if resource.palette_address != 0 {
        let reference = names.reference(resource.palette_address, Some("u16"))?;
        if let Some(stripped) = reference.strip_prefix('&') {
            format!("(u16*)&{stripped}")
        } else {
            reference
        }
    } else {
        "NULL".to_string()
    };
    Ok((images, palettes, resource))
}

fn render_resource(overlay: &Overlay, address: u32, name: &str, names: &mut Names) -> Result<(Vec<String>, u32)> {
    let (images, palettes, resource) = resource_fields(overlay, names, address)?;
    let lines = vec![
        format!("SaturnSpriteResource {name} = {{"),
        format!("    {images},"),
        format!("    {palettes},"),
        format!("    {},", resource.allocation as i16),
        format!("    0x{:04X},", resource.flags),
        "};".to_string(),
    ];
    Ok((lines, 12))
}

fn render_resource_array(
    overlay: &Overlay,
    address: u32,
    name: &str,
    count: u32,
    names: &mut Names,
) -> Result<(Vec<String>, u32)> {
    let mut lines = vec![format!("SaturnSpriteResource {name}[{count}] = {{")];
    for index in 0..count {
        let (images, palettes, resource) = resource_fields(overlay, names, address + index * 12)?;
        lines.push(format!(
            "    {{{images}, {palettes}, {}, 0x{:04X}}},",
            resource.allocation as i16, resource.flags
        ));
    }
    lines.push("};".to_string());
    Ok((lines, count * 12))
}

fn render_pointers(
    overlay: &Overlay,
    address: u32,
    name: &str,
    count: u32,
    element_type: &str,
    names: &mut Names,
) -> Result<(Vec<String>, u32)> {
    let mut lines = vec![format!("{element_type} {name}[{count}] = {{")];
    for index in 0..count {
        let target = overlay_u32(overlay, address + index * 4)?;
        if target == 0 {
            lines.push("    NULL,".to_string());
            continue;
        }
        let reference = names.reference(target, None)?;
        lines.push(format!("    ({element_type}){reference},"));
    }
    lines.push("};".to_string());
    Ok((lines, count * 4))
}

fn render_texture(overlay: &Overlay, address: u32, name: &str) -> Result<(Vec<String>, u32)> {
    let width = overlay_u8(overlay, address)?;
    let height = overlay_u8(overlay, address + 1)?;
    let mut pixels = Vec::with_capacity(512);
    for index in 0..512u32 {
        pixels.push(format!("0x{:02X},", overlay_u8(overlay, address + 2 + index)?));
    }
    let mut lines = vec![
        format!("SaturnIndexed4Texture{width}x{height} {name} = {{"),
        format!("    {width},"),
        format!("    {height},"),
        "    {".to_string(),
    ];
    lines.extend(wrap(&pixels, "        "));
    lines.push("    },".to_string());
    lines.push("};".to_string());
    Ok((lines, 514))
}

struct Names {
    by_address: BTreeMap<u32, (String, String)>,
    local: BTreeMap<String, String>,
    external: BTreeMap<String, String>,
}

impl Names {
    fn new(by_address: BTreeMap<u32, (String, String)>, local: BTreeMap<String, String>) -> Self {
        Names { by_address, local, external: BTreeMap::new() }
    }

    fn reference(&mut self, address: u32, element_type: Option<&str>) -> Result<String> {
        let (name, _) = self.by_address.get(&address).cloned().ok_or_else(|| {
            Error::Format(format!(
                "no symbol is defined at 0x{address:08X}, so the reference to it cannot be written as C"
            ))
        })?;
        if let Some(shape) = self.local.get(&name) {
            return Ok(if shape == "struct" { format!("&{name}") } else { name });
        }
        let declared = self
            .external
            .entry(name.clone())
            .or_insert_with(|| element_type.unwrap_or("u8").to_string());
        if let Some(element_type) = element_type {
            if declared != element_type {
                return Err(Error::Format(format!(
                    "{name} is referenced as both {declared} and {element_type}"
                )));
            }
        }
        Ok(name)
    }

    fn declarations(&self) -> Vec<String> {
        self.external
            .iter()
            .map(|(name, element_type)| format!("extern {element_type} {name}[];"))
            .collect()
    }
}

fn render_package(files: &PackageFiles, package: &PackageSpec, names: &mut Names) -> Result<String> {
    let overlay = files.overlay(package)?;
    let mut cursor = parse_hex(&package.address)?;
    let mut body: Vec<Vec<String>> = Vec::new();

    for spec in &package.symbols {
        if spec.kind == "frame_group" {
            for index in 0..spec.count {
                let name = format!("{}Frame{index}", spec.prefix);
                let (lines, size) = render_package_frame(&overlay, cursor, &name)?;
                body.push(lines);
                cursor += size;
            }
            continue;
        }
        let (lines, size) = match spec.kind.as_str() {
            "images" => render_package_images(&overlay, cursor, &spec.name)?,
            "palette" => render_package_palette(&overlay, cursor, &spec.name, spec.padding)?,
            "resource" => render_resource(&overlay, cursor, &spec.name, names)?,
            "resource_array" => render_resource_array(&overlay, cursor, &spec.name, spec.count, names)?,
            "frames" => {
                render_pointers(&overlay, cursor, &spec.name, spec.count, "SaturnSpriteFrameHeader*", names)?
            }
            "pointers" => render_pointers(&overlay, cursor, &spec.name, spec.count, "void*", names)?,
            "sprite_parts" => {
                render_pointers(&overlay, cursor, &spec.name, spec.count, "struct SpriteParts*", names)?
            }
            "texture" => render_texture(&overlay, cursor, &spec.name)?,
            other => return Err(Error::Format(format!("{}: unsupported kind {other:?}", spec.name))),
        };
        body.push(lines);
        cursor += size;
    }

    let declarations = names.declarations();
    let mut lines: Vec<String> = GENERATED_PACKAGE_HEADER.iter().map(|s| s.to_string()).collect();
    lines.push("#include \"sattypes.h\"".to_string());
    lines.push("#include <saturn_sprite.h>".to_string());
    lines.push(String::new());
    if !declarations.is_empty() {
        lines.extend(declarations);
        lines.push(String::new());
    }
    for block in body {
        lines.extend(block);
        lines.push(String::new());
    }
    let mut text = lines.join("\n");
    while text.ends_with('\n') {
        text.pop();
    }
    text.push('\n');
    Ok(text)
}

fn local_shapes(package: &PackageSpec) -> BTreeMap<String, String> {
    let mut local = BTreeMap::new();
    for spec in &package.symbols {
        if spec.kind == "frame_group" {
            for index in 0..spec.count {
                local.insert(format!("{}Frame{index}", spec.prefix), "struct".to_string());
            }
            continue;
        }
        if let Ok(shape) = shape_of(&spec.kind) {
            local.insert(spec.name.clone(), shape.to_string());
        }
    }
    local
}

fn seed_external_symbols(by_address: &mut BTreeMap<u32, (String, String)>) {
    for profile in player::PROFILES {
        if let Some(header) = profile.header {
            by_address
                .entry(profile.palette_table)
                .or_insert((header.palette.to_string(), "struct".to_string()));
        }
    }
}

fn render_package_target(config_path: &Path, asset_name: &str) -> Result<String> {
    let packages = load_packages(config_path)?;
    let target = find_package(&packages, asset_name)?.clone();
    let files = PackageFiles::load(&packages)?;

    let mut by_address = BTreeMap::new();
    seed_external_symbols(&mut by_address);
    for package in &packages {
        record_package_symbols(&files, package, &mut by_address)?;
    }

    let mut names = Names::new(by_address, local_shapes(&target));
    render_package(&files, &target, &mut names)
}

pub fn generate_package_header(config_path: &Path, asset_name: &str, output_path: &Path) -> Result<String> {
    let text = render_package_target(config_path, asset_name)?;
    if let Some(parent) = output_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(output_path, &text)?;
    Ok(text)
}

pub fn verify_package_header(config_path: &Path, asset_name: &str, output_path: &Path) -> Result<()> {
    let text = render_package_target(config_path, asset_name)?;
    let existing = std::fs::read_to_string(output_path)?;
    if existing != text {
        let at = text
            .lines()
            .zip(existing.lines())
            .position(|(a, b)| a != b)
            .map(|line| format!("first difference at line {}", line + 1))
            .unwrap_or_else(|| "line counts differ".to_string());
        return Err(Error::Mismatch(format!(
            "regenerating does not reproduce {} ({at}); it must never be hand-edited",
            output_path.display()
        )));
    }
    Ok(())
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

    fn put32(buf: &mut [u8], at: usize, value: u32) {
        buf[at..at + 4].copy_from_slice(&value.to_be_bytes());
    }

    fn put16(buf: &mut [u8], at: usize, value: u16) {
        buf[at..at + 2].copy_from_slice(&value.to_be_bytes());
    }

    fn put_i16(buf: &mut [u8], at: usize, value: i16) {
        buf[at..at + 2].copy_from_slice(&value.to_be_bytes());
    }

    #[test]
    fn entity_entries_walks_the_table_and_stops_at_a_null_pointer() {
        let mut prg = vec![0u8; 0x200];
        put32(&mut prg, HEADER_ENTITY_ENTRIES, LOAD_ADDRESS + 0x50);
        put32(&mut prg, 0x50, LOAD_ADDRESS + 0x80);
        put32(&mut prg, 0x54, LOAD_ADDRESS + 0x90);
        put32(&mut prg, 0x80, LOAD_ADDRESS + 0x100);
        put32(&mut prg, 0x84, LOAD_ADDRESS + 0x10);
        put32(&mut prg, 0x90, LOAD_ADDRESS + 0x110);
        put32(&mut prg, 0x94, LOAD_ADDRESS + 0x20);

        let ov = Overlay::new(&prg, None);
        let entries = entity_entries(&ov, 10).expect("entity_entries");
        assert_eq!(entries.len(), 2);
        assert_eq!(entries[0].resource_address, LOAD_ADDRESS + 0x100);
        assert_eq!(entries[1].resource_address, LOAD_ADDRESS + 0x110);
        assert_eq!(
            entity_entry(&ov, 1).unwrap().resource_address,
            LOAD_ADDRESS + 0x110
        );
        assert!(entity_entry(&ov, 2).is_err(), "index 2 is past the table");
    }

    #[test]
    fn frame_parts_reads_attributes_signed_offsets_and_image_index() {
        let mut prg = vec![0u8; 0x80];
        put16(&mut prg, 0x40, 0x0200); 
        put16(&mut prg, 0x42, 0x0000); 
        put16(&mut prg, 0x44, 0x0305); 
        put_i16(&mut prg, 0x46, -10);
        put_i16(&mut prg, 0x48, 7);
        put16(&mut prg, 0x4A, 2);
        put16(&mut prg, 0x4C, 0x0001); 
        put_i16(&mut prg, 0x4E, 100);
        put_i16(&mut prg, 0x50, -100);
        put16(&mut prg, 0x52, 5);

        let ov = Overlay::new(&prg, None);
        let parts = frame_parts(&ov, LOAD_ADDRESS + 0x40).expect("frame_parts");
        assert_eq!(parts.len(), 2);
        assert_eq!((parts[0].palette(), parts[0].x, parts[0].y, parts[0].image), (3, -10, 7, 2));
        assert_eq!(
            (parts[1].palette(), parts[1].x, parts[1].y, parts[1].image),
            (0, 100, -100, 5)
        );
    }

    fn put_one_part_frame(prg: &mut [u8], at: usize, image: u16) {
        put16(prg, at, 0x0100); 
        put16(prg, at + 2, 0);
        put16(prg, at + 4, 0);
        put_i16(prg, at + 6, 0);
        put_i16(prg, at + 8, 0);
        put16(prg, at + 10, image);
    }

    #[test]
    fn frame_table_shape_ends_cleanly_when_the_pointers_run_out() {
        let mut prg = vec![0u8; 0x200];
        put32(&mut prg, 0x40, LOAD_ADDRESS + 0x100);
        put32(&mut prg, 0x44, LOAD_ADDRESS + 0x110);
        put_one_part_frame(&mut prg, 0x100, 0);
        put_one_part_frame(&mut prg, 0x110, 1);

        let ov = Overlay::new(&prg, None);
        let (count, clean) = frame_table_shape(&ov, LOAD_ADDRESS + 0x40, 2, 1, 10);
        assert_eq!((count, clean), (2, true));
    }

    #[test]
    fn frame_table_shape_is_unclean_when_a_part_points_past_this_resource() {
        let mut prg = vec![0u8; 0x200];
        put32(&mut prg, 0x40, LOAD_ADDRESS + 0x100);
        put32(&mut prg, 0x44, LOAD_ADDRESS + 0x110);
        put32(&mut prg, 0x48, LOAD_ADDRESS + 0x120);
        put_one_part_frame(&mut prg, 0x100, 0);
        put_one_part_frame(&mut prg, 0x110, 1);
        put_one_part_frame(&mut prg, 0x120, 5); 

        let ov = Overlay::new(&prg, None);
        let (count, clean) = frame_table_shape(&ov, LOAD_ADDRESS + 0x40, 2, 1, 10);
        assert_eq!(
            (count, clean),
            (2, false),
            "the walk should stop before adopting a neighbour's frames"
        );
    }

    #[test]
    fn an_entity_header_regenerates_byte_for_byte_from_a_synthetic_overlay() {
        let mut prg = vec![0u8; 0x300];
        for field in 0..HEADER_FIELDS {
            put32(&mut prg, field * 4, LOAD_ADDRESS + 0x50);
        }
        put32(&mut prg, HEADER_ENTITY_ENTRIES, LOAD_ADDRESS + 0x50);
        put32(&mut prg, 0x50, LOAD_ADDRESS + 0x80);
        put32(&mut prg, 0x80, LOAD_ADDRESS + 0x100); 
        put32(&mut prg, 0x84, 0); 

        put32(&mut prg, 0x100, LOAD_ADDRESS + 0x140);
        put32(&mut prg, 0x104, LOAD_ADDRESS + 0x160);
        put16(&mut prg, 0x108, 0xFFFF);
        put16(&mut prg, 0x10A, 0xFFFF);

        prg[0x140..0x144].copy_from_slice(&[4, 2, 0, 0]);
        prg[0x144..0x148].copy_from_slice(&[0, 0, 0, 7]);

        put16(&mut prg, 0x160, 0x0001);
        for index in 0..16u16 {
            put16(&mut prg, 0x162 + index as usize * 2, index);
        }
        put16(&mut prg, 0x182, 0xABCD);

        put32(&mut prg, 0x200, LOAD_ADDRESS + 0x240);
        put32(&mut prg, 0x204, LOAD_ADDRESS + 0x260);
        put16(&mut prg, 0x240, 0x0000);
        put16(&mut prg, 0x242, 0x1111);
        put16(&mut prg, 0x260, 0x0100);
        put16(&mut prg, 0x262, 0x2222);
        put16(&mut prg, 0x264, 0x0000);
        put_i16(&mut prg, 0x266, 1);
        put_i16(&mut prg, 0x268, -2);
        put16(&mut prg, 0x26A, 0);

        let ov = Overlay::new(&prg, None);
        let data = collect_entity_header(&ov, 0, LOAD_ADDRESS + 0x200, "g_Test")
            .expect("collect_entity_header");
        let text = emit_entity_header(&data);

        let expected = "\
// SPDX-License-Identifier: AGPL-3.0-or-later
// Generated by tools/saturn/assets: stage entity-header.
// Edit the entity's images/palette/frames and regenerate this file;
// do not hand-edit it.
#include \"sattypes.h\"
#include <saturn_sprite.h>

SaturnSpriteFrameHeader g_TestFrame0 = {0x0000, 0x1111};

SaturnSpriteFrame1 g_TestFrame1 = {
    {0x0100, 0x2222},
    {
        {0x0000, 1, -2, 0},
    },
};

SaturnSpriteFrameHeader* g_TestFrames[2] = {
    (SaturnSpriteFrameHeader*)&g_TestFrame0,
    (SaturnSpriteFrameHeader*)&g_TestFrame1,
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} g_TestPalettes = {
    0x0001,
    {
        {
            0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
            0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
        },
    },
    {0xABCD},
};

SaturnSpriteImage g_TestImages[2] = {
    {4, 2, 0x0000}, {0, 0, 0x0007},
};

SaturnSpriteResource g_TestResource = {
    g_TestImages,
    (u16*)&g_TestPalettes,
    -1,
    0xFFFF,
};
";
        assert_eq!(text, expected);

        let dir = std::env::temp_dir().join(format!(
            "stage-entity-header-test-{}",
            std::process::id()
        ));
        std::fs::create_dir_all(&dir).unwrap();
        let prg_path = dir.join("STAGE_TEST.PRG");
        let header_path = dir.join("gen").join("stest.h");
        std::fs::write(&prg_path, &prg).unwrap();

        generate_entity_header(&prg_path, None, 0, LOAD_ADDRESS + 0x200, "g_Test", &header_path)
            .expect("generate_entity_header");
        verify_entity_header(&prg_path, None, 0, LOAD_ADDRESS + 0x200, "g_Test", &header_path)
            .expect("verify_entity_header");

        std::fs::write(&header_path, "tampered\n").unwrap();
        assert!(
            verify_entity_header(&prg_path, None, 0, LOAD_ADDRESS + 0x200, "g_Test", &header_path)
                .is_err(),
            "a hand-edited header must fail verification"
        );

        std::fs::remove_dir_all(&dir).ok();
    }
}
