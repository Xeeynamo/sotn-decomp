
use crate::image::{self, Rgba};
use crate::map::{self, Kind, Manifest, Stream, STAGE_LOAD_ADDRESS};
use crate::{sprite, stage};
use crate::{Error, Result};
use serde::Serialize;
use serde_json::json;
use std::collections::{BTreeMap, HashMap};
use std::path::Path;

const PSX_TEXTURE_SIZE: usize = 0x40000;
const MAX_TILEDEFS: usize = 0x1000;
const MAX_PALETTES: usize = 256;
const GAME_LOAD_ADDRESS: u32 = 0x0606_6000;
const COMMON_LOAD_TABLE: u32 = 0x0608_46D4;
const COMMON_SAVE_TABLE: u32 = 0x0608_4734;
const COMMON_LOAD_COLLISION_OFFSET: usize = 0x2999;
const COMMON_LOAD_COLLISION_SIZE: usize = 20;
const COMMON_SAVE_COLLISION_OFFSET: usize = 0x565B;
const COMMON_SAVE_COLLISION_SIZE: usize = 52;
const MASONRY_SPRITE_BANK: usize = 8;
const MASONRY_IMAGE: usize = 0;
const MASONRY_PALETTE_BANK: usize = 0;
const CLUT_OFFSETS: [usize; 16] = [
    0x5C00, 0x5C20, 0x7C00, 0x7C20, 0xDC00, 0xDC20, 0xFC00, 0xFC20, 0x15C00,
    0x15C20, 0x17C00, 0x17C20, 0x1DC00, 0x1DC20, 0x1FC00, 0x1FC20,
];

#[derive(Clone, Copy, Debug)]
pub enum ScaleModel {
    Raster,
    TileGroups,
}

#[derive(Clone, Copy, Debug, Serialize)]
struct Bounds {
    left: u8,
    top: u8,
    right: u8,
    bottom: u8,
}

#[derive(Debug, Serialize)]
struct LayerReport {
    room: usize,
    layer: usize,
    source_width: usize,
    source_height: usize,
    output_width: usize,
    output_height: usize,
    lossy_tiles: usize,
}

#[derive(Debug, PartialEq, Eq, Serialize)]
struct TransitionReport {
    from: usize,
    to: usize,
    edge: &'static str,
}

#[derive(Debug, Serialize)]
struct Report {
    source: String,
    scale: String,
    rooms: Vec<Bounds>,
    layers: Vec<LayerReport>,
    graphics: usize,
    palettes: usize,
    tile_definitions: usize,
    collision_types: BTreeMap<u8, usize>,
    internal_transitions: Vec<TransitionReport>,
    cross_stage_records_omitted: bool,
}

#[derive(Clone)]
struct Raster {
    width: usize,
    height: usize,
    pixels: Vec<Option<u16>>,
}

#[derive(Clone)]
struct DecodedLayer {
    characters: Vec<u8>,
    palette: Vec<u8>,
    tilemap: Vec<u8>,
}

#[derive(Default)]
struct PackedStage {
    graphics: Vec<Vec<u8>>,
    graphic_ids: BTreeMap<Vec<u8>, u16>,
    palettes: Vec<Vec<u16>>,
    palette_ids: BTreeMap<Vec<u16>, u8>,
    tiledefs: Vec<(u8, u8, u8, u8)>,
    tiledef_ids: BTreeMap<(u8, u8, u8, u8), u16>,
    approximate_tile_ids: BTreeMap<(Vec<u8>, Vec<u16>), u16>,
}

fn be_u16(data: &[u8], at: usize, what: &str) -> Result<u16> {
    let b = data
        .get(at..at + 2)
        .ok_or_else(|| Error::Format(format!("{what} is truncated at 0x{at:X}")))?;
    Ok(u16::from_be_bytes([b[0], b[1]]))
}

fn be_u32(data: &[u8], at: usize, what: &str) -> Result<u32> {
    let b = data
        .get(at..at + 4)
        .ok_or_else(|| Error::Format(format!("{what} is truncated at 0x{at:X}")))?;
    Ok(u32::from_be_bytes([b[0], b[1], b[2], b[3]]))
}

fn stream<'a>(
    manifest: &'a Manifest,
    room: usize,
    layer: usize,
    kind: Kind,
) -> Result<&'a Stream> {
    manifest
        .streams
        .iter()
        .find(|stream| {
            stream.kind == kind
                && stream
                    .references
                    .iter()
                    .any(|r| r.room == room && r.layer == layer)
        })
        .ok_or_else(|| {
            Error::Format(format!(
                "room {room} layer {layer} has no {} stream",
                kind.name()
            ))
        })
}

fn decode_stream(map_data: &[u8], stream: &Stream) -> Result<Vec<u8>> {
    let bytes = map_data
        .get(stream.offset..stream.offset + stream.compressed_size)
        .ok_or_else(|| Error::Format(format!("{} lies outside the MAP", stream.label())))?;
    let mut decoded = crate::lzss::decompress(bytes);
    decoded.truncate(stream.decompressed_size);
    Ok(decoded)
}

fn read_bounds(prg: &[u8], count: usize) -> Result<Vec<Bounds>> {
    let address = be_u32(prg, 0x10, "room-header pointer")?;
    let start = address
        .checked_sub(STAGE_LOAD_ADDRESS)
        .ok_or_else(|| Error::Format("room-header pointer precedes the overlay".to_string()))?
        as usize;
    (0..count)
        .map(|room| {
            let at = start + room * 6;
            let b = prg
                .get(at..at + 4)
                .ok_or_else(|| Error::Format("room-header table is truncated".to_string()))?;
            Ok(Bounds {
                left: b[0],
                top: b[1],
                right: b[2],
                bottom: b[3],
            })
        })
        .collect()
}

fn write_entity_layout(
    prg: &[u8],
    output: &Path,
    layout_id: usize,
    address: u32,
) -> Result<Vec<serde_json::Value>> {
    let mut at = address
        .checked_sub(STAGE_LOAD_ADDRESS)
        .ok_or_else(|| Error::Format("entity layout precedes the overlay".to_string()))?
        as usize;
    let mut entities = Vec::new();
    loop {
        let x = be_u16(prg, at, "entity x")?;
        let y = be_u16(prg, at + 2, "entity y")?;
        let entity_id = be_u16(prg, at + 4, "entity id")?;
        let room_index = be_u16(prg, at + 6, "entity room index")?;
        let params = be_u16(prg, at + 8, "entity params")?;
        at += 10;
        if x == 0xFFFF && y == 0xFFFF {
            break;
        }
        if x == 0xFFFE && y == 0xFFFE {
            continue;
        }
        entities.push(json!({
            "x": (x as usize * 4 / 5),
            "y": y,
            "entityId": entity_id,
            "entityRoomIndex": room_index,
            "subId": params
        }));
    }
    write_json(
        &output.join(format!("layout{layout_id}.layoutobj.json")),
        &entities,
    )?;
    Ok(entities)
}

fn render_layer(
    manifest: &Manifest,
    map_data: &[u8],
    room: usize,
    layer: usize,
    scale_model: ScaleModel,
) -> Result<Raster> {
    let chars = decode_stream(
        map_data,
        stream(manifest, room, layer, Kind::Characters)?,
    )?;
    let palette = decode_stream(map_data, stream(manifest, room, layer, Kind::Palette)?)?;
    let tilemap = decode_stream(map_data, stream(manifest, room, layer, Kind::Tilemap)?)?;
    render_decoded_layer(&chars, &palette, &tilemap, scale_model, &format!(
        "room {room} layer {layer}"
    ))
}

fn render_decoded_layer(
    chars: &[u8],
    palette: &[u8],
    tilemap: &[u8],
    scale_model: ScaleModel,
    label: &str,
) -> Result<Raster> {
    let width = be_u16(&tilemap, 0, "tilemap width")? as usize;
    let height = be_u16(&tilemap, 2, "tilemap height")? as usize;
    let mut source = Raster {
        width: width * 8,
        height: height * 8,
        pixels: vec![None; width * height * 64],
    };

    for cell_y in 0..height {
        for cell_x in 0..width {
            let pnd = be_u16(
                &tilemap,
                4 + (cell_y * width + cell_x) * 2,
                "pattern-name table",
            )?;
            let character = (pnd & 0x03FF) as usize;
            let hflip = pnd & 0x0400 != 0;
            let vflip = pnd & 0x0800 != 0;
            let bank = (pnd >> 12) as usize;
            for y in 0..8 {
                for x in 0..8 {
                    let sx = if hflip { 7 - x } else { x };
                    let sy = if vflip { 7 - y } else { y };
                    let packed = *chars
                        .get(character * 32 + sy * 4 + sx / 2)
                        .ok_or_else(|| {
                            Error::Format(format!(
                                "{label} references missing character {character}"
                            ))
                        })?;
                    let index = if sx & 1 == 0 { packed >> 4 } else { packed & 0xF };
                    if index == 0 {
                        continue;
                    }
                    let colour = be_u16(
                        &palette,
                        (bank * 16 + index as usize) * 2,
                        "palette",
                    )? & 0x7FFF;
                    let at = (cell_y * 8 + y) * source.width + cell_x * 8 + x;
                    source.pixels[at] = Some(colour);
                }
            }
        }
    }

    let output_width = source.width * 4 / 5;
    let mut output = Raster {
        width: output_width,
        height: source.height,
        pixels: vec![None; output_width * source.height],
    };
    for y in 0..output.height {
        match scale_model {
            ScaleModel::Raster => {
                for x in 0..output.width {
                    output.pixels[y * output.width + x] =
                        source.pixels[y * source.width + x * 5 / 4];
                }
            }
            ScaleModel::TileGroups => {
                const WIDTHS: [usize; 5] = [7, 6, 7, 6, 6];
                for group in 0..source.width / 40 {
                    let mut output_x = group * 32;
                    for (character, width) in WIDTHS.iter().copied().enumerate() {
                        let source_x = group * 40 + character * 8;
                        for x in 0..width {
                            output.pixels[y * output.width + output_x + x] =
                                source.pixels
                                    [y * source.width + source_x + x * 8 / width];
                        }
                        output_x += width;
                    }
                }
            }
        }
    }
    Ok(output)
}

fn common_layers(game: &[u8], load_map: &[u8], table_address: u32) -> Result<Vec<DecodedLayer>> {
    let table = table_address
        .checked_sub(GAME_LOAD_ADDRESS)
        .ok_or_else(|| Error::Format("common-room table precedes GAME.PRG".to_string()))?
        as usize;
    let mut layers = Vec::with_capacity(2);
    for layer in 0..2 {
        let record = table + layer * 24;
        let mut decoded = Vec::with_capacity(3);
        for stream in 0..3 {
            let descriptor = record + stream * 8;
            let offset = be_u32(game, descriptor, "common-room stream offset")? as usize;
            let size = be_u32(game, descriptor + 4, "common-room compressed size")? as usize;
            let source = load_map.get(offset..offset + size).ok_or_else(|| {
                Error::Format(format!(
                    "common-room stream 0x{offset:X}+0x{size:X} lies outside LOAD.MAP"
                ))
            })?;
            decoded.push(crate::lzss::decompress(source));
        }
        let tilemap_size = {
            let width = be_u16(&decoded[2], 0, "common-room tilemap width")? as usize;
            let height = be_u16(&decoded[2], 2, "common-room tilemap height")? as usize;
            4 + width * height * 2
        };
        decoded[2].truncate(tilemap_size);
        layers.push(DecodedLayer {
            characters: decoded.remove(0),
            palette: decoded.remove(0),
            tilemap: decoded.remove(0),
        });
    }
    Ok(layers)
}

fn common_collision(load_map: &[u8], offset: usize, size: usize, name: &str) -> Result<Vec<u8>> {
    let source = load_map.get(offset..offset + size).ok_or_else(|| {
        Error::Format(format!(
            "{name} collision stream 0x{offset:X}+0x{size:X} lies outside LOAD.MAP"
        ))
    })?;
    let mut collision = crate::lzss::decompress(source);
    if collision.len() < 16 * 16 {
        return Err(Error::Format(format!(
            "{name} collision decoded to {} bytes, expected 256",
            collision.len()
        )));
    }
    collision.truncate(16 * 16);
    Ok(collision)
}

fn rgb(colour: u16) -> [u8; 3] {
    let r = (colour & 0x1F) as u32;
    let g = ((colour >> 5) & 0x1F) as u32;
    let b = ((colour >> 10) & 0x1F) as u32;
    [(r * 255 / 31) as u8, (g * 255 / 31) as u8, (b * 255 / 31) as u8]
}

fn colour_distance(a: u16, b: u16) -> u32 {
    let a = rgb(a);
    let b = rgb(b);
    a.iter()
        .zip(b.iter())
        .map(|(&x, &y)| {
            let d = x as i32 - y as i32;
            (d * d) as u32
        })
        .sum()
}

fn quantize_tile(colours: &[Option<u16>]) -> (Vec<u8>, Vec<u16>, bool) {
    let mut frequencies: HashMap<u16, usize> = HashMap::new();
    for colour in colours.iter().flatten() {
        *frequencies.entry(*colour).or_default() += 1;
    }
    let distinct = frequencies.len();
    let mut ranked: Vec<(u16, usize)> = frequencies.into_iter().collect();
    ranked.sort_by_key(|&(colour, frequency)| (std::cmp::Reverse(frequency), colour));
    let mut palette = vec![0];
    palette.extend(
        ranked
            .iter()
            .take(15)
            .map(|&(colour, _)| if colour == 0 { 0x8000 } else { colour }),
    );
    while palette.len() < 16 {
        palette.push(0);
    }
    let pixels = colours
        .iter()
        .map(|colour| match colour {
            None => 0,
            Some(colour) => palette[1..]
                .iter()
                .enumerate()
                .min_by_key(|&(_, candidate)| colour_distance(*colour, *candidate))
                .map(|(index, _)| index as u8 + 1)
                .unwrap_or(0),
        })
        .collect();
    (pixels, palette, distinct > 15)
}

impl PackedStage {
    fn intern_graphic(&mut self, pixels: Vec<u8>) -> Result<u16> {
        if let Some(id) = self.graphic_ids.get(&pixels) {
            return Ok(*id);
        }
        let id = self.graphics.len() as u16;
        if id as usize >= 1984 {
            return Err(Error::Format(format!(
                "converted stage exceeds the PSX stage texture capacity at {} graphics",
                self.graphics.len()
            )));
        }
        self.graphics.push(pixels.clone());
        self.graphic_ids.insert(pixels, id);
        Ok(id)
    }

    fn intern_palette(&mut self, colours: Vec<u16>) -> Result<u8> {
        if let Some(id) = self.palette_ids.get(&colours) {
            return Ok(*id);
        }
        let id = self.palettes.len() as u8;
        self.palettes.push(colours.clone());
        self.palette_ids.insert(colours, id);
        Ok(id)
    }

    fn intern_tile(
        &mut self,
        mut pixels: Vec<u8>,
        mut palette: Vec<u16>,
        collision: u8,
        exact_graphic_limit: usize,
        preserve_exact: bool,
    ) -> Result<u16> {
        if !self.palette_ids.contains_key(&palette) {
            if let Some((_, target)) = self.palettes.iter().enumerate().find(|(_, target)| {
                palette[1..]
                    .iter()
                    .filter(|&&colour| colour != 0)
                    .all(|colour| target[1..].contains(colour))
            }) {
                for pixel in &mut pixels {
                    if *pixel == 0 {
                        continue;
                    }
                    let colour = palette[*pixel as usize];
                    *pixel = target[1..]
                        .iter()
                        .position(|candidate| *candidate == colour)
                        .map(|index| index as u8 + 1)
                        .unwrap_or(0);
                }
                palette = target.clone();
            }
        }
        if !self.palette_ids.contains_key(&palette) && self.palettes.len() >= MAX_PALETTES {
            let replacement = self
                .palettes
                .iter()
                .enumerate()
                .skip(1)
                .min_by_key(|(_, candidate)| {
                    palette[1..]
                        .iter()
                        .filter(|&&colour| colour != 0)
                        .map(|colour| {
                            candidate[1..]
                                .iter()
                                .map(|other| colour_distance(*colour, *other))
                                .min()
                                .unwrap_or(u32::MAX)
                        })
                        .sum::<u32>()
                })
                .map(|(id, _)| id)
                .unwrap_or(0);
            let target = &self.palettes[replacement];
            for pixel in &mut pixels {
                if *pixel == 0 {
                    continue;
                }
                let colour = palette[*pixel as usize];
                *pixel = target[1..]
                    .iter()
                    .enumerate()
                    .min_by_key(|&(_, candidate)| colour_distance(colour, *candidate))
                    .map(|(index, _)| index as u8 + 1)
                    .unwrap_or(0);
            }
            palette = target.clone();
        }
        if !self.graphic_ids.contains_key(&pixels)
            && self.graphics.len()
                >= exact_graphic_limit + if preserve_exact { 100 } else { 0 }
        {
            let approximate_key = (pixels.clone(), palette.clone());
            if let Some(id) = self.approximate_tile_ids.get(&approximate_key) {
                return Ok(*id);
            }
            let id = self
                .tiledefs
                .iter()
                .enumerate()
                .filter(|(_, (_, _, _, hit))| *hit == 0)
                .min_by_key(|(_, (index, page, clut, _))| {
                    let candidate = &self.graphics
                        [slot_for_page_index(*page as usize, *index)];
                    let candidate_palette = &self.palettes[*clut as usize];
                    pixels
                        .iter()
                        .step_by(4)
                        .zip(candidate.iter().step_by(4))
                        .map(|(&a, &b)| match (a, b) {
                            (0, 0) => 0,
                            (0, _) | (_, 0) => 0x100000,
                            _ => colour_distance(
                                palette[a as usize],
                                candidate_palette[b as usize],
                            ),
                        })
                        .sum::<u32>()
                })
                .map(|(id, _)| id as u16)
                .unwrap_or(0);
            self.approximate_tile_ids.insert(approximate_key, id);
            return Ok(id);
        }
        let slot = self.intern_graphic(pixels)?;
        let clut = self.intern_palette(palette)?;
        let page = page_for_slot(slot as usize) as u8;
        let gfx_index = index_for_slot(slot as usize);
        let key = (gfx_index, page, clut, collision);
        if let Some(id) = self.tiledef_ids.get(&key) {
            return Ok(*id);
        }
        if self.tiledefs.len() >= MAX_TILEDEFS {
            return Err(Error::Format(
                "converted stage exceeds 4096 tile definitions".to_string(),
            ));
        }
        let id = self.tiledefs.len() as u16;
        self.tiledefs.push(key);
        self.tiledef_ids.insert(key, id);
        Ok(id)
    }

    fn with_collision(&mut self, id: u16, collision: u8) -> Result<u16> {
        let &(index, page, clut, _) = self
            .tiledefs
            .get(id as usize)
            .ok_or_else(|| Error::Format(format!("missing tile definition {id}")))?;
        let key = (index, page, clut, collision);
        if let Some(id) = self.tiledef_ids.get(&key) {
            return Ok(*id);
        }
        if self.tiledefs.len() >= MAX_TILEDEFS {
            return Err(Error::Format(
                "converted stage exceeds 4096 tile definitions".to_string(),
            ));
        }
        let id = self.tiledefs.len() as u16;
        self.tiledefs.push(key);
        self.tiledef_ids.insert(key, id);
        Ok(id)
    }
}

fn page_for_slot(mut slot: usize) -> usize {
    for page in 0..8 {
        let rows = if page < 4 { 15 } else { 16 };
        let capacity = rows * 16;
        if slot < capacity {
            return page;
        }
        slot -= capacity;
    }
    unreachable!()
}

fn position_for_slot(mut slot: usize) -> (usize, usize, usize) {
    for page in 0..8 {
        let rows = if page < 4 { 15 } else { 16 };
        let capacity = rows * 16;
        if slot < capacity {
            return (page, slot % 16, slot / 16);
        }
        slot -= capacity;
    }
    unreachable!()
}

fn index_for_slot(slot: usize) -> u8 {
    let (_, x, y) = position_for_slot(slot);
    (x | (y << 4)) as u8
}

fn write_preview(path: &Path, raster: &Raster) -> Result<()> {
    let mut preview = Rgba::new(raster.width as u32, raster.height as u32, [0, 0, 0, 0]);
    for y in 0..raster.height {
        for x in 0..raster.width {
            if let Some(colour) = raster.pixels[y * raster.width + x] {
                let [r, g, b] = rgb(colour);
                preview.set(x as u32, y as u32, [r, g, b, 255]);
            }
        }
    }
    image::write_rgba(path, &preview)
}

fn slot_for_page_index(page: usize, index: u8) -> usize {
    let prior: usize = (0..page)
        .map(|p| if p < 4 { 15 * 16 } else { 16 * 16 })
        .sum();
    prior + ((index as usize >> 4) * 16) + (index as usize & 0xF)
}

fn write_packed_preview(
    path: &Path,
    width: usize,
    height: usize,
    layout: &[u8],
    packed: &PackedStage,
) -> Result<()> {
    let mut preview = Rgba::new(width as u32, height as u32, [0, 0, 0, 0]);
    let tile_width = width / 16;
    for (cell, tile) in layout.chunks_exact(2).enumerate() {
        let tile_id = u16::from_le_bytes([tile[0], tile[1]]) as usize;
        let &(index, page, clut, _) = packed.tiledefs.get(tile_id).ok_or_else(|| {
            Error::Format(format!("preview references missing tile definition {tile_id}"))
        })?;
        let pixels = &packed.graphics[slot_for_page_index(page as usize, index)];
        let palette = &packed.palettes[clut as usize];
        let tile_x = (cell % tile_width) * 16;
        let tile_y = (cell / tile_width) * 16;
        for y in 0..16 {
            for x in 0..16 {
                let pixel = pixels[y * 16 + x] as usize;
                if pixel == 0 {
                    continue;
                }
                let [r, g, b] = rgb(palette[pixel]);
                preview.set(
                    (tile_x + x) as u32,
                    (tile_y + y) as u32,
                    [r, g, b, 255],
                );
            }
        }
    }
    image::write_rgba(path, &preview)
}

fn write_json(path: &Path, value: &impl Serialize) -> Result<()> {
    let mut data = serde_json::to_string_pretty(value)?;
    data.push('\n');
    std::fs::write(path, data)?;
    Ok(())
}

fn write_native_layer(
    manifest: &Manifest,
    map_data: &[u8],
    output: &Path,
    room: usize,
    layer: usize,
) -> Result<()> {
    let characters = decode_stream(
        map_data,
        stream(manifest, room, layer, Kind::Characters)?,
    )?;
    let palettes = decode_stream(
        map_data,
        stream(manifest, room, layer, Kind::Palette)?,
    )?;
    let tilemap = decode_stream(
        map_data,
        stream(manifest, room, layer, Kind::Tilemap)?,
    )?;
    write_native_decoded_layer(
        output,
        room,
        layer,
        &DecodedLayer {
            characters,
            palette: palettes,
            tilemap,
        },
    )
}

fn write_native_decoded_layer(
    output: &Path,
    room: usize,
    layer: usize,
    decoded: &DecodedLayer,
) -> Result<()> {
    let characters = &decoded.characters;
    let palettes = &decoded.palette;
    let tilemap = &decoded.tilemap;
    if characters.len() > 1024 * 32 {
        return Err(Error::Format(format!(
            "room {room} layer {layer} has more than 1024 Saturn characters"
        )));
    }

    let mut atlas = vec![0u8; 256 * 256 / 2];
    for character in 0..characters.len() / 32 {
        let atlas_x = (character % 32) * 8;
        let atlas_y = (character / 32) * 8;
        for y in 0..8 {
            for pair in 0..4 {
                let source = characters[character * 32 + y * 4 + pair];
                let destination =
                    (atlas_y + y) * 128 + atlas_x / 2 + pair;
                atlas[destination] = (source >> 4) | (source << 4);
            }
        }
    }

    let psx_palettes = native_psx_palettes(palettes);

    let width = be_u16(&tilemap, 0, "native tilemap width")?;
    let height = be_u16(&tilemap, 2, "native tilemap height")?;
    let mut psx_tilemap = Vec::with_capacity(tilemap.len());
    psx_tilemap.extend_from_slice(&width.to_le_bytes());
    psx_tilemap.extend_from_slice(&height.to_le_bytes());
    for entry in tilemap[4..].chunks_exact(2) {
        let entry = u16::from_be_bytes([entry[0], entry[1]]);
        psx_tilemap.extend_from_slice(&entry.to_le_bytes());
    }

    let stem = format!("native_room{room}_layer{layer}");
    std::fs::write(output.join(format!("{stem}.chars.bin")), &atlas)?;
    std::fs::write(
        output.join(format!("{stem}.pal.bin")),
        &psx_palettes,
    )?;
    std::fs::write(
        output.join(format!("{stem}.map.bin")),
        &psx_tilemap,
    )?;

    let mut preview = Rgba::new(
        (width as u32 * 32) / 5,
        height as u32 * 8,
        [0, 0, 0, 0],
    );
    for cell_y in 0..height as usize {
        for cell_x in 0..width as usize {
            let at = 4 + (cell_y * width as usize + cell_x) * 2;
            let pnd = u16::from_le_bytes([
                psx_tilemap[at],
                psx_tilemap[at + 1],
            ]);
            let character = (pnd & 0x03FF) as usize;
            let bank = (pnd >> 12) as usize;
            let hflip = pnd & 0x0400 != 0;
            let vflip = pnd & 0x0800 != 0;
            let x0 = cell_x * 32 / 5;
            let x1 = (cell_x + 1) * 32 / 5;
            for destination_y in 0..8 {
                let source_y =
                    if vflip { 7 - destination_y } else { destination_y };
                for destination_x in x0..x1 {
                    let mut source_x =
                        (destination_x - x0) * 8 / (x1 - x0);
                    if hflip {
                        source_x = 7 - source_x;
                    }
                    let atlas_x = (character % 32) * 8 + source_x;
                    let atlas_y = (character / 32) * 8 + source_y;
                    let packed = atlas[atlas_y * 128 + atlas_x / 2];
                    let pixel = if atlas_x & 1 == 0 {
                        packed & 0xF
                    } else {
                        packed >> 4
                    } as usize;
                    if pixel == 0 {
                        continue;
                    }
                    let palette_at = (bank * 16 + pixel) * 2;
                    if palette_at + 1 >= psx_palettes.len() {
                        continue;
                    }
                    let colour = u16::from_le_bytes([
                        psx_palettes[palette_at],
                        psx_palettes[palette_at + 1],
                    ]);
                    let [r, g, b] = rgb(colour);
                    preview.set(
                        destination_x as u32,
                        (cell_y * 8 + destination_y) as u32,
                        [r, g, b, 255],
                    );
                }
            }
        }
    }
    image::write_rgba(
        &output.join(format!("{stem}.preview.png")),
        &preview,
    )?;
    Ok(())
}

fn psx_palettes(palettes: &[u8], clear_high_bit: bool) -> Vec<u8> {
    let mut psx_palettes = Vec::with_capacity(palettes.len());
    for (index, colour) in palettes.chunks_exact(2).enumerate() {
        let mut colour = if index % 16 == 0 {
            0
        } else {
            u16::from_be_bytes([colour[0], colour[1]])
        };
        if clear_high_bit {
            colour &= 0x7FFF;
        }
        psx_palettes.extend_from_slice(&colour.to_le_bytes());
    }
    psx_palettes
}

fn native_psx_palettes(palettes: &[u8]) -> Vec<u8> {
    psx_palettes(palettes, true)
}

fn write_masonry_sprite(prg: &[u8], disc_dir: &Path, output: &Path) -> Result<()> {
    let chr = std::fs::read(disc_dir.join("STAGE_15.CHR"))?;
    let zero = std::fs::read(disc_dir.join("0.BIN"))?;
    let overlay = stage::Overlay::new(prg, Some(&zero));
    let (resources, images) = stage::resources(&overlay, chr.len())?;
    let (resource_index, resource) = resources
        .iter()
        .enumerate()
        .find(|(_, resource)| resource.banks.contains(&MASONRY_SPRITE_BANK))
        .ok_or_else(|| Error::Format("Stage 15 has no shared sprite bank 8".to_string()))?;
    let image = images
        .iter()
        .find(|image| image.resource == resource_index && image.index == MASONRY_IMAGE)
        .ok_or_else(|| Error::Format("Stage 15 shared sprite bank 8 has no image 0".to_string()))?;
    if (image.pixel_width, image.pixel_height, image.byte_count) != (24, 16, 192) {
        return Err(Error::Format(format!(
            "Stage 15 masonry image changed from 24x16/192 bytes to {}x{}/{} bytes",
            image.pixel_width, image.pixel_height, image.byte_count
        )));
    }
    let saturn_pixels = chr
        .get(image.file_offset..image.file_offset + image.byte_count)
        .ok_or_else(|| Error::Format("Stage 15 masonry image lies outside its CHR".to_string()))?;
    let psx_pixels: Vec<u8> = saturn_pixels
        .iter()
        .map(|byte| byte.rotate_left(4))
        .collect();

    let (_, palette_data, palette_offset) = overlay
        .resolve(resource.palette_address)
        .ok_or_else(|| Error::Format("Stage 15 masonry palette is unresolved".to_string()))?;
    let saturn_palette =
        sprite::palette_bank(palette_data, palette_offset, MASONRY_PALETTE_BANK)
            .ok_or_else(|| Error::Format("Stage 15 masonry palette bank is missing".to_string()))?;
    let psx_palette = psx_palettes(saturn_palette, false);

    std::fs::write(output.join("stage15_masonry.chars.bin"), psx_pixels)?;
    std::fs::write(output.join("stage15_masonry.pal.bin"), psx_palette)?;
    Ok(())
}

fn write_tiledefs(output: &Path, packed: &PackedStage) -> Result<()> {
    let mut gfx_index = Vec::with_capacity(packed.tiledefs.len());
    let mut gfx_page = Vec::with_capacity(packed.tiledefs.len());
    let mut clut = Vec::with_capacity(packed.tiledefs.len());
    let mut collision = Vec::with_capacity(packed.tiledefs.len());
    for &(index, page, palette, hit) in &packed.tiledefs {
        gfx_index.push(index);
        gfx_page.push(page);
        clut.push(palette);
        collision.push(hit);
    }
    std::fs::write(output.join("tiledefs.gfx_index.bin"), gfx_index)?;
    std::fs::write(output.join("tiledefs.gfx_page.bin"), gfx_page)?;
    std::fs::write(output.join("tiledefs.clut.bin"), clut)?;
    std::fs::write(output.join("tiledefs.collision.bin"), collision)?;
    let definition = json!({
        "gfxIndex": "tiledefs.gfx_index.bin",
        "gfxPage": "tiledefs.gfx_page.bin",
        "clut": "tiledefs.clut.bin",
        "collision": "tiledefs.collision.bin"
    });
    write_json(&output.join("t_stage15.tiledef.json"), &definition)
}

fn write_c_tables(
    output: &Path,
    rooms: &[serde_json::Value],
    layers: &[serde_json::Value],
    entity_layouts: &[(usize, Vec<serde_json::Value>)],
    packed: &PackedStage,
) -> Result<()> {
    use std::fmt::Write as _;

    fn field(item: &serde_json::Value, key: &str) -> Result<i64> {
        item.get(key)
            .and_then(|v| v.as_i64())
            .ok_or_else(|| Error::Format(format!("generated table has no {key:?}")))
    }
    fn field_or(item: &serde_json::Value, key: &str, fallback: i64) -> i64 {
        item.get(key).and_then(|v| v.as_i64()).unwrap_or(fallback)
    }
    fn bytes(out: &mut String, name: &str, data: &[u8], pad_to: usize) {
        let _ = writeln!(out, "static u8 {name}[0x{pad_to:X}] = {{");
        for (i, b) in data.iter().enumerate() {
            let _ = write!(out, "{}0x{b:02X},", if i % 16 == 0 { "    " } else { " " });
            if i % 16 == 15 {
                let _ = writeln!(out);
            }
        }
        if data.len() % 16 != 0 {
            let _ = writeln!(out);
        }
        let _ = writeln!(out, "}};\n");
    }

    let mut out = String::new();
    out.push_str(
        "#ifndef STAGE15_DATA_H\n#define STAGE15_DATA_H\n\n\
         #include <game.h>\n#include <stage.h>\n\n",
    );

    let mut gfx_index = Vec::with_capacity(packed.tiledefs.len());
    let mut gfx_page = Vec::with_capacity(packed.tiledefs.len());
    let mut clut = Vec::with_capacity(packed.tiledefs.len());
    let mut collision = Vec::with_capacity(packed.tiledefs.len());
    for &(index, page, palette, hit) in &packed.tiledefs {
        gfx_index.push(index);
        gfx_page.push(page);
        clut.push(palette);
        collision.push(hit);
    }
    if gfx_index.len() > 0x1000 {
        return Err(Error::Format(format!(
            "{} tile definitions exceed the 0x1000 the overlay indexes",
            gfx_index.len()
        )));
    }
    bytes(&mut out, "s_Stage15TileDefGfxPage", &gfx_page, 0x1000);
    bytes(&mut out, "s_Stage15TileDefGfxIndex", &gfx_index, 0x1000);
    bytes(&mut out, "s_Stage15TileDefClut", &clut, 0x1000);
    bytes(&mut out, "s_Stage15TileDefCollision", &collision, 0x1000);
    out.push_str(
        "static TileDefinition s_Stage15TileDef = {\n    \
         s_Stage15TileDefGfxPage,\n    s_Stage15TileDefGfxIndex,\n    \
         s_Stage15TileDefClut,\n    s_Stage15TileDefCollision,\n};\n\n",
    );

    let mut stems: Vec<String> = Vec::new();
    for room in layers {
        for role in ["bg", "fg"] {
            let Some(layer) = room.get(role) else { continue };
            let stem = layer
                .get("data")
                .and_then(|v| v.as_str())
                .ok_or_else(|| Error::Format("layer has no data stem".to_string()))?;
            if !stems.iter().any(|s| s == stem) {
                stems.push(stem.to_string());
            }
        }
    }
    for stem in &stems {
        let path = output.join(format!("{stem}.tilelayout.bin"));
        let data = std::fs::read(&path)?;
        if data.len() % 2 != 0 {
            return Err(Error::Format(format!(
                "{} has an odd byte count",
                path.display()
            )));
        }
        writeln!(
            out,
            "static u16 s_Stage15Layout_{stem}[{}] = {{",
            data.len() / 2
        )
        .ok();
        for (i, word) in data.chunks_exact(2).enumerate() {
            let value = u16::from_le_bytes([word[0], word[1]]);
            let _ = write!(
                out,
                "{}0x{value:04X},",
                if i % 12 == 0 { "    " } else { " " }
            );
            if i % 12 == 11 {
                let _ = writeln!(out);
            }
        }
        if (data.len() / 2) % 12 != 0 {
            let _ = writeln!(out);
        }
        out.push_str("};\n\n");
    }

    let mut layer_defs = String::new();
    let mut room_defs = String::new();
    let mut layer_count = 0usize;
    for (index, room) in layers.iter().enumerate() {
        let mut slot = [String::from("NULL"), String::from("NULL")];
        for (which, role) in ["fg", "bg"].iter().enumerate() {
            let Some(layer) = room.get(role) else { continue };
            let stem = layer.get("data").and_then(|v| v.as_str()).unwrap();
            let name = format!("s_Stage15LayerDefs[{layer_count}]");
            writeln!(
                layer_defs,
                "    {{ s_Stage15Layout_{stem}, &s_Stage15TileDef,\n      \
                 {{ {}, {}, {}, {}, {} }}, 0x{:X}, 0x{:X} }},",
                field(layer, "left")?,
                field(layer, "top")?,
                field(layer, "right")?,
                field(layer, "bottom")?,
                field_or(layer, "params", 0),
                field(layer, "zPriority")?,
                field_or(layer, "flags", 1),
            )
            .ok();
            slot[which] = format!("&{name}");
            layer_count += 1;
        }
        writeln!(
            room_defs,
            "    [{index}] = {{ {}, {} }},",
            slot[0], slot[1]
        )
        .ok();
    }
    writeln!(out, "static LayerDef s_Stage15LayerDefs[] = {{\n{layer_defs}}};\n").ok();
    writeln!(
        out,
        "static RoomDef s_Stage15TileLayers[0x100] = {{\n{room_defs}}};\n"
    )
    .ok();

    out.push_str("static RoomHeader s_Stage15Rooms[] = {\n");
    for room in rooms {
        writeln!(
            out,
            "    {{ {}, {}, {}, {}, {{ {}, {}, {}, {} }} }},",
            field(room, "left")?,
            field(room, "top")?,
            field(room, "right")?,
            field(room, "bottom")?,
            field(room, "tileLayoutId")?,
            field(room, "tilesetId")?,
            field(room, "objGfxId")?,
            field(room, "objLayoutId")?,
        )
        .ok();
    }
    out.push_str("};\n\n");

    let mut highest = 0usize;
    for (id, entities) in entity_layouts {
        highest = highest.max(*id);
        writeln!(out, "static LayoutEntity s_Stage15Layout{id}[] = {{").ok();
        for entity in entities {
            writeln!(
                out,
                "    {{ {}, {}, {}, {}, {} }},",
                field(entity, "x")?,
                field(entity, "y")?,
                field(entity, "entityId")?,
                field(entity, "entityRoomIndex")?,
                field(entity, "subId")?,
            )
            .ok();
        }
        out.push_str("    { 0xFFFF, 0xFFFF, 0, 0, 0 },\n};\n\n");
    }
    writeln!(
        out,
        "static LayoutEntity* s_Stage15ObjLayouts[{}] = {{",
        highest + 1
    )
    .ok();
    for (id, _) in entity_layouts {
        writeln!(out, "    [{id}] = s_Stage15Layout{id},").ok();
    }
    out.push_str("};\n\n");
    writeln!(
        out,
        "static const size_t s_Stage15ObjLayoutCounts[{}] = {{",
        highest + 1
    )
    .ok();
    for (id, entities) in entity_layouts {
        writeln!(out, "    [{id}] = {},", entities.len()).ok();
    }
    out.push_str("};\n\n#endif\n");

    std::fs::write(output.join("stage15_data.h"), out)?;
    Ok(())
}

fn write_texture(output: &Path, packed: &PackedStage) -> Result<()> {
    let mut pages = vec![vec![0u8; 256 * 256]; 8];
    for (slot, pixels) in packed.graphics.iter().enumerate() {
        let (page, tile_x, tile_y) = position_for_slot(slot);
        for y in 0..16 {
            let dst = (tile_y * 16 + y) * 256 + tile_x * 16;
            pages[page][dst..dst + 16].copy_from_slice(&pixels[y * 16..y * 16 + 16]);
        }
    }
    let mut texture = vec![0u8; PSX_TEXTURE_SIZE];
    for (page, pixels) in pages.iter().enumerate() {
        for quadrant in 0..4 {
            let qx = (quadrant & 1) * 128;
            let qy = (quadrant >> 1) * 128;
            let chunk = (page * 4 + quadrant) * 0x2000;
            for y in 0..128 {
                for x in 0..64 {
                    let left = pixels[(qy + y) * 256 + qx + x * 2];
                    let right = pixels[(qy + y) * 256 + qx + x * 2 + 1];
                    texture[chunk + y * 64 + x] = left | (right << 4);
                }
            }
        }
    }
    for (id, palette) in packed.palettes.iter().enumerate() {
        let at = CLUT_OFFSETS[id % 16] + (id / 16) * 0x40;
        for (index, colour) in palette.iter().enumerate() {
            texture[at + index * 2..at + index * 2 + 2]
                .copy_from_slice(&colour.to_le_bytes());
        }
    }
    std::fs::write(output.join("F_STAGE15.BIN"), texture)?;
    Ok(())
}

fn internal_transitions(bounds: &[Bounds]) -> Vec<TransitionReport> {
    let mut transitions = Vec::new();
    for (from, a) in bounds.iter().enumerate() {
        for (to, b) in bounds.iter().enumerate() {
            if from == to {
                continue;
            }
            let vertical_overlap = a.top <= b.bottom && b.top <= a.bottom;
            let horizontal_overlap = a.left <= b.right && b.left <= a.right;
            if vertical_overlap && a.right.checked_add(1) == Some(b.left) {
                transitions.push(TransitionReport {
                    from,
                    to,
                    edge: "right",
                });
            }
            if vertical_overlap && b.right.checked_add(1) == Some(a.left) {
                transitions.push(TransitionReport {
                    from,
                    to,
                    edge: "left",
                });
            }
            if horizontal_overlap && a.bottom.checked_add(1) == Some(b.top) {
                transitions.push(TransitionReport {
                    from,
                    to,
                    edge: "bottom",
                });
            }
            if horizontal_overlap && b.bottom.checked_add(1) == Some(a.top) {
                transitions.push(TransitionReport {
                    from,
                    to,
                    edge: "top",
                });
            }
        }
    }
    transitions
}

pub fn convert(
    prg_path: &Path,
    map_path: &Path,
    output: &Path,
    scale_model: ScaleModel,
) -> Result<()> {
    let source_dir = output.join("saturn-source");
    let manifest = map::extract(prg_path, map_path, &source_dir)?;
    if manifest.tables.rooms < 4 {
        return Err(Error::Format("Stage 15 needs at least four rooms".to_string()));
    }
    let prg_path = map::overlay_for(prg_path, map_path);
    let prg = std::fs::read(&prg_path)?;
    let map_data = std::fs::read(map_path)?;
    let disc_dir = map_path.parent().ok_or_else(|| {
        Error::Format("Stage 15 MAP has no parent directory".to_string())
    })?;
    let game = std::fs::read(disc_dir.join("GAME.PRG"))?;
    let load_map = std::fs::read(disc_dir.join("LOAD.MAP"))?;
    std::fs::create_dir_all(output)?;
    write_masonry_sprite(&prg, disc_dir, output)?;
    let loading_room = common_layers(&game, &load_map, COMMON_LOAD_TABLE)?;
    let save_room = common_layers(&game, &load_map, COMMON_SAVE_TABLE)?;
    let loading_collision = common_collision(
        &load_map,
        COMMON_LOAD_COLLISION_OFFSET,
        COMMON_LOAD_COLLISION_SIZE,
        "loading-room",
    )?;
    let save_collision = common_collision(
        &load_map,
        COMMON_SAVE_COLLISION_OFFSET,
        COMMON_SAVE_COLLISION_SIZE,
        "save-room",
    )?;
    let bounds = read_bounds(&prg, 4)?;
    let transitions = internal_transitions(&bounds);
    let expected = [
        (0, 1, "right"),
        (1, 0, "left"),
        (1, 3, "right"),
        (2, 3, "left"),
        (3, 1, "left"),
        (3, 2, "right"),
    ];
    if transitions
        .iter()
        .map(|transition| (transition.from, transition.to, transition.edge))
        .ne(expected)
    {
        return Err(Error::Format(format!(
            "Stage 15 ordinary-room adjacency changed: {transitions:?}"
        )));
    }
    let mut packed = PackedStage::default();
    let mut collision_types = BTreeMap::new();
    let decorative_graphic_limit = match scale_model {
        ScaleModel::Raster => 1300,
        ScaleModel::TileGroups => 1200,
    };

    packed.graphics.push(vec![0; 256]);
    packed.graphic_ids.insert(vec![0; 256], 0);
    packed.palettes.push(vec![0; 16]);
    packed.palette_ids.insert(vec![0; 16], 0);
    packed.tiledefs.push((0, 0, 0, 0));
    packed.tiledef_ids.insert((0, 0, 0, 0), 0);
    for room in 0..bounds.len() {
        for layer in 0..3 {
            write_native_layer(&manifest, &map_data, output, room, layer)?;
        }
    }
    let blank_native = DecodedLayer {
        characters: vec![0; 32],
        palette: vec![0; 32],
        tilemap: {
            let mut map = vec![0; 4 + 40 * 32 * 2];
            map[0..2].copy_from_slice(&40u16.to_be_bytes());
            map[2..4].copy_from_slice(&32u16.to_be_bytes());
            map
        },
    };
    for (room, source) in [
        (4usize, &loading_room),
        (5usize, &loading_room),
        (6usize, &save_room),
    ] {
        write_native_decoded_layer(output, room, 0, &source[0])?;
        write_native_decoded_layer(output, room, 1, &blank_native)?;
        write_native_decoded_layer(output, room, 2, &source[1])?;
    }
    let mut layer_json = Vec::new();
    let mut reports = Vec::new();
    for (room, room_bounds) in bounds.iter().enumerate() {
        let collision_stream = manifest.tables.room_graphics[room];
        let collision_bytes = map_data
            .get(
                collision_stream.offset as usize
                    ..collision_stream.offset as usize + collision_stream.size as usize,
            )
            .ok_or_else(|| Error::Format(format!("room {room} collision lies outside MAP")))?;
        let collision = crate::lzss::decompress(collision_bytes);
        let mut room_layers = Vec::new();
        for layer in [0usize, 2usize] {
            let raster = render_layer(&manifest, &map_data, room, layer, scale_model)?;
            if raster.width % 16 != 0 || raster.height % 16 != 0 {
                return Err(Error::Format(format!(
                    "room {room} layer {layer} does not land on 16px PSX tiles"
                )));
            }
            let tile_width = raster.width / 16;
            let tile_height = raster.height / 16;
            let expected_width = (room_bounds.right - room_bounds.left + 1) as usize * 16;
            let expected_height = (room_bounds.bottom - room_bounds.top + 1) as usize * 16;
            if (tile_width, tile_height) != (expected_width, expected_height) {
                return Err(Error::Format(format!(
                    "room {room} layer {layer}: converted grid {tile_width}x{tile_height}, \
                     room bounds require {expected_width}x{expected_height}"
                )));
            }
            let mut layout = Vec::with_capacity(tile_width * tile_height * 2);
            let mut lossy = 0;
            for tile_y in 0..tile_height {
                for tile_x in 0..tile_width {
                    let mut colours = Vec::with_capacity(256);
                    for y in 0..16 {
                        let at = (tile_y * 16 + y) * raster.width + tile_x * 16;
                        colours.extend_from_slice(&raster.pixels[at..at + 16]);
                    }
                    let (pixels, palette, tile_lossy) = quantize_tile(&colours);
                    lossy += usize::from(tile_lossy);
                    let hit = if layer == 0 {
                        *collision
                            .get(tile_y * tile_width + tile_x)
                            .ok_or_else(|| {
                                Error::Format(format!(
                                    "room {room} collision is shorter than {tile_width}x{tile_height}"
                                ))
                            })?
                    } else {
                        0
                    };
                    *collision_types.entry(hit).or_insert(0) += 1;
                    let exact_limit =
                        if layer == 0 { 1984 } else { decorative_graphic_limit };
                    let preserve_exact = room == 0
                        && layer == 2
                        && (8..=14).contains(&tile_x)
                        && (20..=28).contains(&tile_y);
                    let id = packed.intern_tile(
                        pixels,
                        palette,
                        hit,
                        exact_limit,
                        preserve_exact,
                    )?;
                    layout.extend_from_slice(&id.to_le_bytes());
                }
            }
            let role = if layer == 0 { "fg" } else { "bg" };
            let layout_stem = format!("room{room}_{role}");
            let layout_name = format!("{layout_stem}.tilelayout.bin");
            std::fs::create_dir_all(output)?;
            write_packed_preview(
                &output.join(format!("room{room}_{role}.packed.png")),
                raster.width,
                raster.height,
                &layout,
                &packed,
            )?;
            std::fs::write(output.join(&layout_name), layout)?;
            write_preview(
                &output.join(format!("room{room}_{role}.preview.png")),
                &raster,
            )?;
            room_layers.push(json!({
                "data": layout_stem,
                "tiledef": "D_stage15",
                "left": room_bounds.left,
                "top": room_bounds.top,
                "right": room_bounds.right,
                "bottom": room_bounds.bottom,
                "zPriority": if layer == 0 { 0x60 } else { 0x40 },
                "flags": 1
            }));
            reports.push(LayerReport {
                room,
                layer,
                source_width: raster.width * 5 / 4,
                source_height: raster.height,
                output_width: raster.width,
                output_height: raster.height,
                lossy_tiles: lossy,
            });
            eprintln!(
                "packed room {room} layer {layer}: {} graphics",
                packed.graphics.len()
            );
        }
        layer_json.push(json!({
            "fg": room_layers.remove(0),
            "bg": room_layers.remove(0)
        }));
    }

    for (id, left, top, params, source, saturn_collision) in [
        (
            4usize,
            3u8,
            44u8,
            0x10u8,
            &loading_room,
            &loading_collision,
        ),
        (
            5usize,
            3u8,
            45u8,
            0x10u8,
            &loading_room,
            &loading_collision,
        ),
        (
            6usize,
            13u8,
            45u8,
            0x22u8,
            &save_room,
            &save_collision,
        ),
    ] {
        let mut layer_defs = Vec::new();
        for (plane, decoded) in source.iter().enumerate() {
            let raster = render_decoded_layer(
                &decoded.characters,
                &decoded.palette,
                &decoded.tilemap,
                scale_model,
                &format!("special room {id} plane {plane}"),
            )?;
            if (raster.width, raster.height) != (256, 256) {
                return Err(Error::Format(format!(
                    "special room {id} plane {plane} is {}x{}, expected 256x256",
                    raster.width, raster.height
                )));
            }
            let mut layout = Vec::with_capacity(512);
            for tile_y in 0..16 {
                for tile_x in 0..16 {
                    let mut colours = Vec::with_capacity(256);
                    for y in 0..16 {
                        let at = (tile_y * 16 + y) * raster.width + tile_x * 16;
                        colours.extend_from_slice(&raster.pixels[at..at + 16]);
                    }
                    let (pixels, palette, _) = quantize_tile(&colours);
                    let hit = if plane != 0 {
                        0
                    } else {
                        saturn_collision[tile_y * 16 + tile_x]
                    };
                    *collision_types.entry(hit).or_insert(0) += 1;
                    let mut tile =
                        packed.intern_tile(pixels, palette, 0, 1984, false)?;
                    if hit != 0 {
                        tile = packed.with_collision(tile, hit)?;
                    }
                    layout.extend_from_slice(&tile.to_le_bytes());
                }
            }
            let role = if plane == 0 { "fg" } else { "bg" };
            let stem = format!("special_room{id}_{role}");
            std::fs::write(output.join(format!("{stem}.tilelayout.bin")), &layout)?;
            write_packed_preview(
                &output.join(format!("{stem}.packed.png")),
                raster.width,
                raster.height,
                &layout,
                &packed,
            )?;
            write_preview(
                &output.join(format!("{stem}.preview.png")),
                &raster,
            )?;
            layer_defs.push(json!({
                "data": stem,
                "tiledef": "D_stage15",
                "left": left,
                "top": top,
                "right": left,
                "bottom": top,
                "params": params,
                "zPriority": if plane == 0 { 0xA0 } else { 0x40 },
                "flags": 0x203
            }));
        }
        layer_json.push(json!({
            "fg": layer_defs.remove(0),
            "bg": layer_defs.remove(0)
        }));
    }

    let mut backdrop = render_layer(&manifest, &map_data, 0, 1, scale_model)?;
    const STAGE15_BACK_COLOR: u16 = 0x1406;
    for pixel in &mut backdrop.pixels {
        if pixel.is_none() {
            *pixel = Some(STAGE15_BACK_COLOR);
        }
    }
    if (backdrop.width, backdrop.height) != (256, 256) {
        return Err(Error::Format(format!(
            "Stage 15 shared backdrop is {}x{}, expected 256x256",
            backdrop.width, backdrop.height
        )));
    }
    let mut backdrop_layout = Vec::with_capacity(16 * 16 * 2);
    let mut backdrop_lossy = 0;
    for tile_y in 0..16 {
        for tile_x in 0..16 {
            let mut colours = Vec::with_capacity(256);
            for y in 0..16 {
                let at = (tile_y * 16 + y) * backdrop.width + tile_x * 16;
                colours.extend_from_slice(&backdrop.pixels[at..at + 16]);
            }
            let (pixels, palette, tile_lossy) = quantize_tile(&colours);
            backdrop_lossy += usize::from(tile_lossy);
            let id = packed.intern_tile(
                pixels,
                palette,
                0,
                decorative_graphic_limit,
                false,
            )?;
            backdrop_layout.extend_from_slice(&id.to_le_bytes());
        }
    }
    std::fs::write(
        output.join("shared_backdrop.tilelayout.bin"),
        &backdrop_layout,
    )?;
    write_packed_preview(
        &output.join("shared_backdrop.packed.png"),
        backdrop.width,
        backdrop.height,
        &backdrop_layout,
        &packed,
    )?;
    write_preview(
        &output.join("shared_backdrop.preview.png"),
        &backdrop,
    )?;
    layer_json.push(json!({
        "bg": {
            "data": "shared_backdrop",
            "tiledef": "D_stage15",
            "left": 0,
            "top": 0,
            "right": 0,
            "bottom": 0,
            "zPriority": 0x20,
            "flags": 0x1001
        }
    }));
    reports.push(LayerReport {
        room: 0,
        layer: 1,
        source_width: backdrop.width * 5 / 4,
        source_height: backdrop.height,
        output_width: backdrop.width,
        output_height: backdrop.height,
        lossy_tiles: backdrop_lossy,
    });

    write_json(&output.join("rooms.layers.json"), &layer_json)?;
    let mut room_json: Vec<_> = bounds
        .iter()
        .enumerate()
        .map(|(id, room)| {
            json!({
                "left": room.left, "top": room.top,
                "right": room.right, "bottom": room.bottom,
                "tileLayoutId": id, "tilesetId": 0,
                "objGfxId": 0, "objLayoutId": id + 1
            })
        })
        .collect();
    room_json.extend([
        json!({
            "left": 3, "top": 44, "right": 3, "bottom": 44,
            "tileLayoutId": 4, "tilesetId": 0,
            "objGfxId": 0, "objLayoutId": 48
        }),
        json!({
            "left": 3, "top": 45, "right": 3, "bottom": 45,
            "tileLayoutId": 5, "tilesetId": 0,
            "objGfxId": 0, "objLayoutId": 49
        }),
        json!({
            "left": 13, "top": 45, "right": 13, "bottom": 45,
            "tileLayoutId": 6, "tilesetId": 0,
            "objGfxId": 0, "objLayoutId": 50
        }),
    ]);
    while room_json.len() < 20 {
        room_json.push(json!({
            "left": 0x3F, "top": 0x3F, "right": 0, "bottom": 0,
            "tileLayoutId": 0, "tilesetId": 0,
            "objGfxId": 0, "objLayoutId": 0
        }));
    }
    let first = bounds[0];
    let room0_alias = json!({
        "left": first.left, "top": first.top,
        "right": first.right, "bottom": first.bottom,
        "tileLayoutId": 0, "tilesetId": 0,
        "objGfxId": 0, "objLayoutId": 1
    });
    room_json[10] = room0_alias.clone();
    room_json.push(room0_alias);
    room_json.push(json!({
        "left": 0x40, "top": 0, "right": 0, "bottom": 0,
        "tileLayoutId": 0, "tilesetId": 0, "objGfxId": 0, "objLayoutId": 0
    }));
    write_json(&output.join("rooms.roomdef.json"), &room_json)?;
    let mut entity_layouts = Vec::new();
    for (layout_id, address) in [
        (1, 0x060F10F8),
        (2, 0x060F1328),
        (3, 0x060F1418),
        (4, 0x060F1468),
        (48, 0x060F0F0E),
        (49, 0x060F0EC8),
        (50, 0x060F0F54),
    ] {
        let entities = write_entity_layout(&prg, output, layout_id, address)?;
        entity_layouts.push((layout_id, entities));
    }
    write_tiledefs(output, &packed)?;
    write_c_tables(output, &room_json, &layer_json, &entity_layouts, &packed)?;
    write_texture(output, &packed)?;
    let report = Report {
        source: map_path.display().to_string(),
        scale: match scale_model {
            ScaleModel::Raster => {
                "raster: nearest-neighbor x'=floor(x*4/5)".to_string()
            }
            ScaleModel::TileGroups => {
                "tile-groups: five 8px characters -> widths 7/6/7/6/6".to_string()
            }
        },
        rooms: bounds,
        layers: reports,
        graphics: packed.graphics.len(),
        palettes: packed.palettes.len(),
        tile_definitions: packed.tiledefs.len(),
        collision_types,
        internal_transitions: transitions,
        cross_stage_records_omitted: true,
    };
    write_json(&output.join("conversion-report.json"), &report)?;
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::{
        internal_transitions, native_psx_palettes, psx_palettes, Bounds,
        TransitionReport,
    };

    #[test]
    fn native_palette_zero_is_transparent_on_psx() {
        let mut saturn = vec![0xFF; 64];
        saturn[0..2].copy_from_slice(&0x8421u16.to_be_bytes());
        saturn[32..34].copy_from_slice(&0xFFFFu16.to_be_bytes());

        let psx = native_psx_palettes(&saturn);

        assert_eq!(u16::from_le_bytes([psx[0], psx[1]]), 0);
        assert_eq!(u16::from_le_bytes([psx[2], psx[3]]), 0x7FFF);
        assert_eq!(u16::from_le_bytes([psx[32], psx[33]]), 0);
        let preserved = psx_palettes(&saturn, false);
        assert_eq!(u16::from_le_bytes([preserved[2], preserved[3]]), 0xFFFF);
    }

    #[test]
    fn stage15_rooms_form_the_expected_chain() {
        let rooms = [
            Bounds {
                left: 4,
                top: 44,
                right: 12,
                bottom: 45,
            },
            Bounds {
                left: 13,
                top: 44,
                right: 16,
                bottom: 44,
            },
            Bounds {
                left: 21,
                top: 44,
                right: 21,
                bottom: 44,
            },
            Bounds {
                left: 17,
                top: 44,
                right: 20,
                bottom: 44,
            },
        ];
        assert_eq!(
            internal_transitions(&rooms),
            [
                TransitionReport {
                    from: 0,
                    to: 1,
                    edge: "right"
                },
                TransitionReport {
                    from: 1,
                    to: 0,
                    edge: "left"
                },
                TransitionReport {
                    from: 1,
                    to: 3,
                    edge: "right"
                },
                TransitionReport {
                    from: 2,
                    to: 3,
                    edge: "left"
                },
                TransitionReport {
                    from: 3,
                    to: 1,
                    edge: "left"
                },
                TransitionReport {
                    from: 3,
                    to: 2,
                    edge: "right"
                },
            ]
        );
    }
}
