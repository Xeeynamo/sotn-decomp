use crate::image::{self, Indexed};
use crate::lzss;
use crate::sprite::rgb555;
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::path::{Path, PathBuf};

pub const FORMAT: &str = "sotn-saturn-stage-map";
pub const VERSION: u32 = 1;
pub const MANIFEST_NAME: &str = "manifest.json";
pub const LAYOUT_NAME: &str = "layout.json";
pub const ROOMS_DIR: &str = "rooms";

pub const STAGE_LOAD_ADDRESS: u32 = 0x060D_C000;
pub const SUBSTAGE_STRIDE: usize = 0x14;
pub const ROOM_STRIDE: usize = 36;
pub const LAYERS: usize = 3;
pub const TILE_BYTES: usize = 32;
pub const ATLAS_COLUMNS: u32 = 32;
pub const PALETTE_BANK_BYTES: usize = 32;

pub fn stage_of(map_stem: &str) -> (&str, usize) {
    match map_stem {
        "STAGE_7A" => ("STAGE_07", 0),
        "STAGE_7B" => ("STAGE_07", 1),
        "STAGE_9A" => ("STAGE_09", 0),
        "STAGE_9B" => ("STAGE_09", 1),
        "STAGE_9C" => ("STAGE_09", 2),
        "STAGE06A" => ("STAGE_06", 0),
        "STAGE06B" => ("STAGE_06", 1),
        "STAGE13A" => ("STAGE_13", 0),
        "STAGE13B" => ("STAGE_13", 1),
        "RSTAGE6A" => ("RSTAGE06", 0),
        "RSTAGE6B" => ("RSTAGE06", 1),
        "RSTAGE7A" => ("RSTAGE07", 0),
        "RSTAGE7B" => ("RSTAGE07", 1),
        "RSTAGE9A" => ("RSTAGE09", 0),
        "RSTAGE9B" => ("RSTAGE09", 1),
        "RSTAGE9C" => ("RSTAGE09", 2),
        "RSTAG13A" => ("RSTAGE13", 0),
        "RSTAG13B" => ("RSTAGE13", 1),
        other => (other, 0),
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
#[serde(rename_all = "lowercase")]
pub enum Kind {
    Characters,
    Palette,
    Tilemap,
}

impl Kind {
    pub const ALL: [Kind; 3] = [Kind::Characters, Kind::Palette, Kind::Tilemap];
    pub fn name(self) -> &'static str {
        match self {
            Kind::Characters => "characters",
            Kind::Palette => "palette",
            Kind::Tilemap => "tilemap",
        }
    }
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Source {
    pub map: String,
    pub map_size: usize,
    pub map_sha256: String,
    pub prg: String,
    pub prg_size: usize,
    pub prg_sha256: String,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
pub struct RoomGraphics {
    pub offset: u32,
    pub size: u32,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Tables {
    pub substage: usize,
    pub counts_address: u32,
    pub offsets_address: u32,
    pub graphics_address: u32,
    pub rooms: usize,
    pub map_offsets: Vec<u32>,
    pub compressed_sizes: Vec<u32>,
    pub room_graphics: Vec<RoomGraphics>,
}

impl Tables {
    pub fn entry(room: usize, layer: usize, kind: Kind) -> usize {
        let index = Kind::ALL.iter().position(|&k| k == kind).unwrap_or(0);
        room * LAYERS * Kind::ALL.len() + layer * Kind::ALL.len() + index
    }
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Reference {
    pub room: usize,
    pub layer: usize,
    #[serde(skip_serializing_if = "Option::is_none", default)]
    pub compressed_size: Option<usize>,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Stream {
    pub kind: Kind,
    pub offset: usize,
    pub compressed_size: usize,
    pub decompressed_size: usize,
    pub sha256: String,
    pub references: Vec<Reference>,
    #[serde(skip_serializing_if = "Option::is_none", default)]
    pub file: Option<String>,
    #[serde(skip_serializing_if = "Vec::is_empty", default)]
    pub words: Vec<String>,
    #[serde(skip_serializing_if = "Vec::is_empty", default)]
    pub header: Vec<String>,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Manifest {
    pub format: String,
    pub version: u32,
    pub stage: String,
    pub source: Source,
    pub tables: Tables,
    pub streams: Vec<Stream>,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Layout {
    pub format: String,
    pub stage: String,
    pub substage: usize,
    pub rooms: usize,
    pub streams: Vec<LayoutEntry>,
    pub map_offsets: Vec<u32>,
    pub compressed_sizes: Vec<u32>,
    pub room_graphics: Vec<RoomGraphics>,
    pub changed: usize,
    pub map_size: usize,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct LayoutEntry {
    pub kind: Kind,
    pub original_offset: usize,
    pub offset: usize,
    pub compressed_size: usize,
    pub moved: bool,
    pub references: Vec<Reference>,
}

#[derive(Debug, Clone, Copy)]
struct Region {
    original_offset: usize,
    original_size: usize,
    offset: usize,
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

fn table_offset(prg: &[u8], substage: usize, field: usize) -> Result<usize> {
    let address = read_u32(prg, field + substage * SUBSTAGE_STRIDE)?;
    address
        .checked_sub(STAGE_LOAD_ADDRESS)
        .map(|o| o as usize)
        .filter(|&o| o < prg.len())
        .ok_or_else(|| {
            Error::Format(format!(
                "export pointer 0x{address:08X} at +0x{:X} is outside the stage PRG",
                field + substage * SUBSTAGE_STRIDE
            ))
        })
}

fn tables(prg: &[u8], substage: usize) -> Result<(usize, usize, usize, usize)> {
    let counts = table_offset(prg, substage, 0x14)?;
    let offsets = table_offset(prg, substage, 0x18)?;
    let next = table_offset(prg, substage, 0x20)?;
    let span = next as isize - counts as isize;
    if span <= 0 || span as usize % ROOM_STRIDE != 0 {
        return Err(Error::Format(
            "cannot derive room count from the stage export tables".to_string(),
        ));
    }
    let rooms = span as usize / ROOM_STRIDE;
    if next + rooms * 8 > prg.len() {
        return Err(Error::Format(
            "the collision directory lies outside the stage PRG".to_string(),
        ));
    }
    Ok((counts, offsets, next, rooms))
}

fn read_tables(prg: &[u8], substage: usize) -> Result<Tables> {
    let (counts, offsets, graphics, rooms) = tables(prg, substage)?;
    let entries = rooms * LAYERS * Kind::ALL.len();
    let mut compressed_sizes = Vec::with_capacity(entries);
    let mut map_offsets = Vec::with_capacity(entries);
    for entry in 0..entries {
        compressed_sizes.push(read_u32(prg, counts + entry * 4)?);
        map_offsets.push(read_u32(prg, offsets + entry * 4)?);
    }
    let mut room_graphics = Vec::with_capacity(rooms);
    for room in 0..rooms {
        room_graphics.push(RoomGraphics {
            offset: read_u32(prg, graphics + room * 8)?,
            size: read_u32(prg, graphics + room * 8 + 4)?,
        });
    }
    Ok(Tables {
        substage,
        counts_address: read_u32(prg, 0x14 + substage * SUBSTAGE_STRIDE)?,
        offsets_address: read_u32(prg, 0x18 + substage * SUBSTAGE_STRIDE)?,
        graphics_address: read_u32(prg, 0x20 + substage * SUBSTAGE_STRIDE)?,
        rooms,
        map_offsets,
        compressed_sizes,
        room_graphics,
    })
}

fn to_atlas(data: &[u8]) -> Indexed {
    let tiles = data.len() / TILE_BYTES;
    let rows = (tiles as u32).div_ceil(ATLAS_COLUMNS).max(1);
    let mut atlas = Indexed::new(ATLAS_COLUMNS * 8, rows * 8);
    for tile in 0..tiles {
        let ox = (tile as u32 % ATLAS_COLUMNS) * 8;
        let oy = (tile as u32 / ATLAS_COLUMNS) * 8;
        for (index, &byte) in data[tile * TILE_BYTES..(tile + 1) * TILE_BYTES]
            .iter()
            .enumerate()
        {
            let x = (index as u32 * 2) % 8;
            let y = (index as u32 * 2) / 8;
            atlas.set(ox + x, oy + y, byte >> 4);
            atlas.set(ox + x + 1, oy + y, byte & 0xF);
        }
    }
    atlas
}

fn from_atlas(atlas: &Indexed, bytes: usize) -> Result<Vec<u8>> {
    let tiles = bytes / TILE_BYTES;
    let rows = (tiles as u32).div_ceil(ATLAS_COLUMNS).max(1);
    if (atlas.width, atlas.height) != (ATLAS_COLUMNS * 8, rows * 8) {
        return Err(Error::Format(format!(
            "character atlas is {}x{}, expected {}x{} (resizing is not supported)",
            atlas.width,
            atlas.height,
            ATLAS_COLUMNS * 8,
            rows * 8
        )));
    }
    let mut out = vec![0u8; bytes];
    for tile in 0..tiles {
        let ox = (tile as u32 % ATLAS_COLUMNS) * 8;
        let oy = (tile as u32 / ATLAS_COLUMNS) * 8;
        for index in 0..TILE_BYTES {
            let x = (index as u32 * 2) % 8;
            let y = (index as u32 * 2) / 8;
            let high = atlas.get(ox + x, oy + y);
            let low = atlas.get(ox + x + 1, oy + y);
            if high > image::MAX_INDEX || low > image::MAX_INDEX {
                return Err(Error::Format(format!(
                    "tile {tile} has a palette index above {}",
                    image::MAX_INDEX
                )));
            }
            out[tile * TILE_BYTES + index] = (high << 4) | low;
        }
    }
    Ok(out)
}

fn display_from_palette(data: &[u8]) -> Option<Vec<u8>> {
    if data.len() < PALETTE_BANK_BYTES {
        return None;
    }
    Some(
        (0..16)
            .flat_map(|index| {
                let at = index * 2;
                rgb555(u16::from_be_bytes([data[at], data[at + 1]]))
            })
            .collect(),
    )
}

fn hex_words(data: &[u8]) -> Vec<String> {
    data.chunks_exact(2)
        .map(|pair| format!("0x{:04X}", u16::from_be_bytes([pair[0], pair[1]])))
        .collect()
}

fn hex_bytes(data: &[u8]) -> Vec<String> {
    data.iter().map(|byte| format!("0x{byte:02X}")).collect()
}

fn parse_words(words: &[String]) -> Result<Vec<u8>> {
    let mut out = Vec::with_capacity(words.len() * 2);
    for word in words {
        let digits = word.strip_prefix("0x").unwrap_or(word);
        let value = u16::from_str_radix(digits, 16)
            .map_err(|e| Error::Format(format!("{word:?} is not a u16: {e}")))?;
        out.extend_from_slice(&value.to_be_bytes());
    }
    Ok(out)
}

fn parse_bytes(values: &[String]) -> Result<Vec<u8>> {
    values
        .iter()
        .map(|value| {
            let digits = value.strip_prefix("0x").unwrap_or(value);
            u8::from_str_radix(digits, 16)
                .map_err(|e| Error::Format(format!("{value:?} is not a u8: {e}")))
        })
        .collect()
}

const TILEMAP_HEADER: usize = 4;

struct Decoded {
    kind: Kind,
    offset: usize,
    extent: usize,
    references: Vec<Reference>,
    data: Vec<u8>,
}

fn decode(prg: &[u8], map: &[u8], substage: usize) -> Result<(Tables, Vec<Decoded>)> {
    let tables = read_tables(prg, substage)?;
    let mut order: Vec<usize> = Vec::new();
    let mut groups: std::collections::HashMap<usize, Decoded> = std::collections::HashMap::new();
    for room in 0..tables.rooms {
        for layer in 0..LAYERS {
            for kind in Kind::ALL {
                let entry = Tables::entry(room, layer, kind);
                let size = tables.compressed_sizes[entry] as usize;
                if size == 0 {
                    continue;
                }
                let offset = tables.map_offsets[entry] as usize;
                if offset + size > map.len() {
                    return Err(Error::Format(format!(
                        "room {room} layer {layer} {} stream 0x{offset:X}+0x{size:X} \
                         exceeds the MAP",
                        kind.name()
                    )));
                }
                match groups.get_mut(&offset) {
                    Some(group) => {
                        if group.kind != kind {
                            return Err(Error::Format(format!(
                                "the stream at 0x{offset:X} is read as {} by one room and \
                                 as {} by room {room} layer {layer}",
                                group.kind.name(),
                                kind.name()
                            )));
                        }
                        if size > group.extent {
                            group.extent = size;
                            group.data = lzss::decompress(&map[offset..offset + size]);
                        }
                        group.references.push(Reference {
                            room,
                            layer,
                            compressed_size: Some(size),
                        });
                    }
                    None => {
                        order.push(offset);
                        groups.insert(
                            offset,
                            Decoded {
                                kind,
                                offset,
                                extent: size,
                                references: vec![Reference {
                                    room,
                                    layer,
                                    compressed_size: Some(size),
                                }],
                                data: lzss::decompress(&map[offset..offset + size]),
                            },
                        );
                    }
                }
            }
        }
    }

    let mut decoded: Vec<Decoded> = order
        .into_iter()
        .map(|offset| groups.remove(&offset).expect("group was inserted"))
        .collect();
    for group in &mut decoded {
        for reference in &mut group.references {
            if reference.compressed_size == Some(group.extent) {
                reference.compressed_size = None;
            }
        }
    }

    let mut spans: Vec<(usize, usize)> = decoded.iter().map(|g| (g.offset, g.extent)).collect();
    spans.sort_unstable();
    for pair in spans.windows(2) {
        let (offset, size) = pair[0];
        if offset + size > pair[1].0 {
            return Err(Error::Format(format!(
                "the stream at 0x{offset:X}+0x{size:X} overlaps the one at 0x{:X}",
                pair[1].0
            )));
        }
    }
    Ok((tables, decoded))
}

pub fn overlay_for(prg_path: &Path, map_path: &Path) -> PathBuf {
    if !prg_path.is_dir() {
        return prg_path.to_path_buf();
    }
    let stem = file_stem(map_path);
    let (stage, _) = stage_of(&stem);
    prg_path.join(format!("{stage}.PRG"))
}

pub fn extract(prg_path: &Path, map_path: &Path, output_dir: &Path) -> Result<Manifest> {
    let prg_path = overlay_for(prg_path, map_path);
    let prg = std::fs::read(&prg_path)?;
    let map = std::fs::read(map_path)?;
    let stem = file_stem(map_path);
    let (_, substage) = stage_of(&stem);
    let (tables, decoded) = decode(&prg, &map, substage)?;

    let mut palettes: std::collections::HashMap<usize, Vec<u8>> = std::collections::HashMap::new();
    for group in &decoded {
        if group.kind != Kind::Palette {
            continue;
        }
        for reference in &group.references {
            if reference.layer == 0 {
                if let Some(colours) = display_from_palette(&group.data) {
                    palettes.insert(reference.room, colours);
                }
            }
        }
    }

    std::fs::create_dir_all(output_dir)?;
    let mut streams = Vec::with_capacity(decoded.len());
    for group in &decoded {
        let data = &group.data;
        let kind = &group.kind;
        let owner = group
            .references
            .iter()
            .min_by_key(|r| (r.room, r.layer))
            .expect("a group has at least one reference");
        let (room, layer) = (owner.room, owner.layer);
        let mut stream = Stream {
            kind: group.kind,
            offset: group.offset,
            compressed_size: group.extent,
            decompressed_size: data.len(),
            sha256: sha256_hex(data),
            references: group.references.clone(),
            file: None,
            words: Vec::new(),
            header: Vec::new(),
        };
        match kind {
            Kind::Characters => {
                let file = format!("{ROOMS_DIR}/room-{room:02}/layer-{layer}/characters.png");
                image::write_indexed_palette(
                    &safe_join(output_dir, &file)?,
                    &to_atlas(data),
                    palettes.get(&room).map(Vec::as_slice),
                )?;
                let tiles = data.len() / TILE_BYTES * TILE_BYTES;
                stream.header = hex_bytes(&data[tiles..]);
                stream.file = Some(file);
            }
            Kind::Palette => {
                let even = data.len() & !1;
                stream.words = hex_words(&data[..even]);
                stream.header = hex_bytes(&data[even..]);
            }
            Kind::Tilemap => {
                let split = TILEMAP_HEADER.min(data.len());
                stream.header = hex_bytes(&data[..split]);
                stream.words = hex_words(&data[split..]);
                let covered = split + stream.words.len() * 2;
                stream.header.extend(hex_bytes(&data[covered..]));
            }
        }
        streams.push(stream);
    }

    let manifest = Manifest {
        format: FORMAT.to_string(),
        version: VERSION,
        stage: stem,
        source: Source {
            map: file_name(map_path),
            map_size: map.len(),
            map_sha256: sha256_hex(&map),
            prg: file_name(&prg_path),
            prg_size: prg.len(),
            prg_sha256: sha256_hex(&prg),
        },
        tables,
        streams,
    };
    let mut json = serde_json::to_string_pretty(&manifest)?;
    json.push('\n');
    std::fs::write(output_dir.join(MANIFEST_NAME), json)?;
    if manifest.stage != "STAGE_07" {
        let preview = crate::map_render::render_composite(&prg_path, map_path)?;
        image::write_rgba(
            &output_dir.join(crate::map_render::COMPOSITE_NAME),
            &preview,
        )?;
    }
    Ok(manifest)
}

impl Stream {
    pub fn label(&self) -> String {
        let owner = self.references.iter().min_by_key(|r| (r.room, r.layer));
        let (room, layer) = owner.map(|r| (r.room, r.layer)).unwrap_or((0, 0));
        let kind = self.kind.name();
        match self.references.len() {
            0 | 1 => format!("room {room} layer {layer} {kind}"),
            n => format!(
                "room {room} layer {layer} {kind} (shared with {} more)",
                n - 1
            ),
        }
    }

    fn editable(&self) -> Result<()> {
        if let Some(reference) = self
            .references
            .iter()
            .find(|r| r.compressed_size.is_some_and(|s| s != self.compressed_size))
        {
            return Err(Error::Format(format!(
                "{}: room {} layer {} reads only {} of its {} bytes, so the stream \
                 cannot be recompressed without changing what that room draws. \
                 Edit the rooms that share it together, or leave it alone.",
                self.label(),
                reference.room,
                reference.layer,
                reference.compressed_size.unwrap_or(0),
                self.compressed_size
            )));
        }
        Ok(())
    }
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
    Ok(manifest)
}

fn stream_bytes(root: &Path, stream: &Stream) -> Result<Vec<u8>> {
    let mut out = match stream.kind {
        Kind::Characters => {
            let file = stream
                .file
                .as_deref()
                .ok_or_else(|| Error::Format("character stream has no PNG".to_string()))?;
            let atlas = image::read_indexed(&safe_join(root, file)?)?;
            let tiles = stream.decompressed_size / TILE_BYTES * TILE_BYTES;
            from_atlas(&atlas, tiles)?
        }
        Kind::Palette => {
            let mut out = parse_words(&stream.words)?;
            out.extend(parse_bytes(&stream.header)?);
            out
        }
        Kind::Tilemap => {
            let split = TILEMAP_HEADER.min(stream.decompressed_size);
            let header = parse_bytes(&stream.header)?;
            let mut out = header[..split.min(header.len())].to_vec();
            out.extend(parse_words(&stream.words)?);
            out.extend(&header[split.min(header.len())..]);
            out
        }
    };
    if stream.kind == Kind::Characters {
        out.extend(parse_bytes(&stream.header)?);
    }
    if out.len() != stream.decompressed_size {
        return Err(Error::Format(format!(
            "{}: rebuilt to {} bytes, expected {}",
            stream.label(),
            out.len(),
            stream.decompressed_size
        )));
    }
    Ok(out)
}

pub fn rebuild_bytes(manifest_path: &Path, map_path: &Path) -> Result<(Vec<u8>, usize)> {
    let manifest = load_manifest(manifest_path)?;
    let root = manifest_path.parent().unwrap_or_else(|| Path::new("."));
    let retail = std::fs::read(map_path)?;
    if retail.len() != manifest.source.map_size {
        return Err(Error::Format(format!(
            "{} is {} bytes, the manifest describes {}",
            map_path.display(),
            retail.len(),
            manifest.source.map_size
        )));
    }
    let mut out = retail.clone();
    let mut changed = 0;
    for stream in &manifest.streams {
        let bytes = stream_bytes(root, stream)?;
        if sha256_hex(&bytes) == stream.sha256 {
            continue;
        }
        stream.editable()?;
        let compressed = lzss::compress(&bytes);
        if compressed.len() != stream.compressed_size {
            return Err(Error::Format(format!(
                "{}: the edit recompresses to {} bytes but its slot is {}. Moving \
                 streams needs the MAP relocated and the PRG offset tables \
                 regenerated -- use repack",
                stream.label(),
                compressed.len(),
                stream.compressed_size
            )));
        }
        out[stream.offset..stream.offset + compressed.len()].copy_from_slice(&compressed);
        changed += 1;
    }
    Ok((out, changed))
}

pub fn rebuild(
    manifest_path: &Path,
    map_path: &Path,
    output_path: &Path,
) -> Result<(Vec<u8>, usize)> {
    let (data, changed) = rebuild_bytes(manifest_path, map_path)?;
    if let Some(parent) = output_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(output_path, &data)?;
    Ok((data, changed))
}

pub fn verify(manifest_path: &Path, map_path: &Path) -> Result<()> {
    let (rebuilt, _) = rebuild_bytes(manifest_path, map_path)?;
    let retail = std::fs::read(map_path)?;
    if rebuilt == retail {
        return Ok(());
    }
    let at = rebuilt
        .iter()
        .zip(&retail)
        .position(|(a, b)| a != b)
        .unwrap_or(0);
    Err(Error::Mismatch(format!(
        "rebuilt MAP does not match {} (first difference at offset 0x{at:X})",
        map_path.display()
    )))
}

fn relocate(regions: &[Region], old: usize, map_size: usize, new_size: usize) -> Result<usize> {
    if old == map_size {
        return Ok(new_size);
    }
    regions
        .iter()
        .find(|region| {
            old >= region.original_offset && old < region.original_offset + region.original_size
        })
        .map(|region| region.offset + (old - region.original_offset))
        .ok_or_else(|| Error::Format(format!("0x{old:X} is outside the MAP")))
}

pub fn repack(
    manifest_path: &Path,
    map_path: &Path,
    output_path: &Path,
    layout_path: &Path,
) -> Result<Layout> {
    let manifest = load_manifest(manifest_path)?;
    let root = manifest_path.parent().unwrap_or_else(|| Path::new("."));
    let retail = std::fs::read(map_path)?;
    if retail.len() != manifest.source.map_size {
        return Err(Error::Format(format!(
            "{} is {} bytes, the manifest describes {}",
            map_path.display(),
            retail.len(),
            manifest.source.map_size
        )));
    }

    let mut order: Vec<&Stream> = manifest.streams.iter().collect();
    order.sort_by_key(|stream| stream.offset);

    let mut out: Vec<u8> = Vec::with_capacity(retail.len());
    let mut regions: Vec<Region> = Vec::with_capacity(order.len() * 2 + 1);
    let mut entries = Vec::with_capacity(order.len());
    let mut changed = 0;
    let mut cursor = 0usize;
    for stream in &order {
        if stream.offset < cursor {
            return Err(Error::Format(format!(
                "{} overlaps the stream before it",
                stream.label()
            )));
        }
        if stream.offset > cursor {
            regions.push(Region {
                original_offset: cursor,
                original_size: stream.offset - cursor,
                offset: out.len(),
            });
            out.extend_from_slice(&retail[cursor..stream.offset]);
        }
        let bytes = stream_bytes(root, stream)?;
        let compressed = if sha256_hex(&bytes) == stream.sha256 {
            retail[stream.offset..stream.offset + stream.compressed_size].to_vec()
        } else {
            stream.editable()?;
            changed += 1;
            lzss::compress(&bytes)
        };
        let offset = out.len();
        regions.push(Region {
            original_offset: stream.offset,
            original_size: stream.compressed_size,
            offset,
        });
        entries.push(LayoutEntry {
            kind: stream.kind,
            original_offset: stream.offset,
            offset,
            compressed_size: compressed.len(),
            moved: offset != stream.offset || compressed.len() != stream.compressed_size,
            references: stream.references.clone(),
        });
        out.extend_from_slice(&compressed);
        cursor = stream.offset + stream.compressed_size;
    }
    if cursor < retail.len() {
        regions.push(Region {
            original_offset: cursor,
            original_size: retail.len() - cursor,
            offset: out.len(),
        });
        out.extend_from_slice(&retail[cursor..]);
    }

    let mut map_offsets = manifest.tables.map_offsets.clone();
    let mut compressed_sizes = manifest.tables.compressed_sizes.clone();
    for entry in map_offsets.iter_mut() {
        *entry = relocate(&regions, *entry as usize, retail.len(), out.len())? as u32;
    }
    for entry in &entries {
        for reference in &entry.references {
            let index = Tables::entry(reference.room, reference.layer, entry.kind);
            map_offsets[index] = entry.offset as u32;
            compressed_sizes[index] = match reference.compressed_size {
                Some(size) => size as u32,
                None => entry.compressed_size as u32,
            };
        }
    }

    let mut room_graphics = Vec::with_capacity(manifest.tables.room_graphics.len());
    for (room, graphics) in manifest.tables.room_graphics.iter().enumerate() {
        let start = graphics.offset as usize;
        let end = start + graphics.size as usize;
        let offset = relocate(&regions, start, retail.len(), out.len())?;
        let last = relocate(&regions, end.max(start + 1) - 1, retail.len(), out.len())?;
        if last + 1 != offset + graphics.size.max(1) as usize {
            return Err(Error::Format(format!(
                "room {room}'s collision data at 0x{start:X}+0x{:X} does not move as one \
                 piece",
                graphics.size
            )));
        }
        room_graphics.push(RoomGraphics {
            offset: offset as u32,
            size: graphics.size,
        });
    }

    let layout = Layout {
        format: FORMAT.to_string(),
        stage: manifest.stage.clone(),
        substage: manifest.tables.substage,
        rooms: manifest.tables.rooms,
        streams: entries,
        map_offsets,
        compressed_sizes,
        room_graphics,
        changed,
        map_size: out.len(),
    };
    if let Some(parent) = output_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(output_path, &out)?;
    let mut json = serde_json::to_string_pretty(&layout)?;
    json.push('\n');
    if let Some(parent) = layout_path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    std::fs::write(layout_path, json)?;
    Ok(layout)
}

pub fn load_layout(layout_path: &Path) -> Result<Layout> {
    let text = std::fs::read_to_string(layout_path)?;
    let layout: Layout = serde_json::from_str(&text)?;
    if layout.format != FORMAT {
        return Err(Error::Format(format!(
            "{} is not a {FORMAT} layout",
            layout_path.display()
        )));
    }
    let entries = layout.rooms * LAYERS * Kind::ALL.len();
    if layout.map_offsets.len() != entries
        || layout.compressed_sizes.len() != entries
        || layout.room_graphics.len() != layout.rooms
    {
        return Err(Error::Format(format!(
            "{} describes {} rooms but its tables do not match",
            layout_path.display(),
            layout.rooms
        )));
    }
    Ok(layout)
}

pub fn layer_header(layout: &Layout, prefix: &str) -> Result<String> {
    check_prefix(prefix)?;
    let mut out = String::new();
    out.push_str(&generated_banner());
    out.push_str(&table(
        &format!("SaturnLayerMapOffsets {prefix}LayerMapOffsets"),
        layout.rooms,
        &layout.map_offsets,
    ));
    out.push('\n');
    out.push_str(&table(
        &format!("SaturnLayerCompressedSizes {prefix}LayerCompressedSizes"),
        layout.rooms,
        &layout.compressed_sizes,
    ));
    Ok(out)
}

pub fn room_graphics_header(layout: &Layout, prefix: &str) -> Result<String> {
    check_prefix(prefix)?;
    let mut out = generated_banner();
    out.push_str(&format!(
        "SaturnRoomGraphics {prefix}RoomGraphics[{}] = {{\n",
        layout.rooms
    ));
    for entry in &layout.room_graphics {
        out.push_str(&format!(
            "    {{0x{:05X}, 0x{:02X}}},\n",
            entry.offset, entry.size
        ));
    }
    out.push_str("};\n");
    Ok(out)
}

fn generated_banner() -> String {
    "// SPDX-License-Identifier: AGPL-3.0-or-later\n\
     // Generated by tools/saturn/assets: map generate-headers.\n\
     // Edit the MAP assets and regenerate this file; do not hand-edit it.\n\n"
        .to_string()
}

fn check_prefix(prefix: &str) -> Result<()> {
    let valid = !prefix.is_empty()
        && prefix
            .chars()
            .all(|c| c.is_ascii_alphanumeric() || c == '_')
        && !prefix.starts_with(|c: char| c.is_ascii_digit());
    if valid {
        Ok(())
    } else {
        Err(Error::Format(format!(
            "{prefix:?} is not a C identifier prefix"
        )))
    }
}

fn table(declaration: &str, rooms: usize, values: &[u32]) -> String {
    let mut out = format!("{declaration}[{rooms}] = {{\n");
    for room in 0..rooms {
        let layers: Vec<String> = (0..LAYERS)
            .map(|layer| {
                let entries: Vec<String> = Kind::ALL
                    .into_iter()
                    .map(|kind| match values[Tables::entry(room, layer, kind)] {
                        0 => "0".to_string(),
                        value => format!("0x{value:05X}"),
                    })
                    .collect();
                format!("{{{}}}", entries.join(", "))
            })
            .collect();
        out.push_str(&format!("    {{{{{}}}}},\n", layers.join(", ")));
    }
    out.push_str("};\n");
    out
}

pub fn generate_headers(
    layout_path: &Path,
    prefix: &str,
    layer_path: &Path,
    graphics_path: &Path,
) -> Result<()> {
    let layout = load_layout(layout_path)?;
    for (path, text) in [
        (layer_path, layer_header(&layout, prefix)?),
        (graphics_path, room_graphics_header(&layout, prefix)?),
    ] {
        if let Some(parent) = path.parent() {
            std::fs::create_dir_all(parent)?;
        }
        std::fs::write(path, text)?;
    }
    Ok(())
}

pub fn verify_headers(
    layout_path: &Path,
    prefix: &str,
    layer_path: &Path,
    graphics_path: &Path,
) -> Result<()> {
    let layout = load_layout(layout_path)?;
    for (path, expected) in [
        (layer_path, layer_header(&layout, prefix)?),
        (graphics_path, room_graphics_header(&layout, prefix)?),
    ] {
        let actual = std::fs::read_to_string(path)?;
        if actual != expected {
            let line = actual
                .lines()
                .zip(expected.lines())
                .position(|(a, b)| a != b)
                .map(|index| index + 1)
                .unwrap_or_else(|| actual.lines().count().min(expected.lines().count()) + 1);
            return Err(Error::Mismatch(format!(
                "{} is not what the MAP describes (first difference at line {line})",
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
    fn substages_map_to_their_shared_overlay() {
        assert_eq!(stage_of("STAGE_7B"), ("STAGE_07", 1));
        assert_eq!(stage_of("STAGE_9C"), ("STAGE_09", 2));
        assert_eq!(stage_of("RSTAGE9C"), ("RSTAGE09", 2));
        assert_eq!(stage_of("RSTAG13B"), ("RSTAGE13", 1));
        assert_eq!(stage_of("STAGE_02"), ("STAGE_02", 0));
    }

    #[test]
    fn a_substage_index_shifts_the_export_pointers() {
        let mut prg = vec![0u8; 0x100];
        for set in 0..3usize {
            let at = 0x14 + set * SUBSTAGE_STRIDE;
            prg[at..at + 4]
                .copy_from_slice(&(STAGE_LOAD_ADDRESS + 0x40 + set as u32).to_be_bytes());
        }
        for set in 0..3usize {
            assert_eq!(table_offset(&prg, set, 0x14).unwrap(), 0x40 + set);
        }
    }

    #[test]
    fn characters_round_trip_through_the_atlas() {
        let data: Vec<u8> = (0..TILE_BYTES * 70).map(|i| (i * 37 + 11) as u8).collect();
        let atlas = to_atlas(&data);
        assert_eq!(from_atlas(&atlas, data.len()).unwrap(), data);
    }

    #[test]
    fn a_resized_atlas_is_refused() {
        let atlas = Indexed::new(ATLAS_COLUMNS * 8, 8);
        assert!(from_atlas(&atlas, TILE_BYTES * 100).is_err());
    }

    #[test]
    fn hex_words_round_trip() {
        let data: Vec<u8> = (0..64).collect();
        assert_eq!(parse_words(&hex_words(&data)).unwrap(), data);
        assert_eq!(parse_bytes(&hex_bytes(&data)).unwrap(), data);
    }

    #[test]
    fn a_room_count_that_is_not_whole_rooms_is_refused() {
        let mut prg = vec![0u8; 0x100];
        let put = |prg: &mut Vec<u8>, field: usize, offset: u32| {
            prg[field..field + 4].copy_from_slice(&(STAGE_LOAD_ADDRESS + offset).to_be_bytes());
        };
        put(&mut prg, 0x14, 0x40);
        put(&mut prg, 0x18, 0x50);
        put(&mut prg, 0x20, 0x4A);
        assert!(tables(&prg, 0).is_err());
    }
}
