use crate::map;
use crate::psx_stage::{
    read_entity_layout, read_layout_table, read_rooms, render_layer_raster_phase, EntityRecord,
    Raster, RoomKind,
};
use crate::{Error, Result};
use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::path::{Path, PathBuf};

pub const SATURN_SHAFT_ROOM: usize = 17;
pub const PSX_SHAFT_ROOM: usize = 1;

pub const STITCH_ROW: usize = 21;

const CHAMBER_SHIFT: usize = 32;
const CHAMBER_ROWS: std::ops::Range<usize> = 22..32;

const TILES: usize = 16;
const PSX_CELLS: usize = 2;
const SATURN_CELLS: usize = 4;

pub const PSX_ROWS: usize = TILES * PSX_CELLS;
pub const SATURN_ROWS: usize = TILES * SATURN_CELLS;
const REVERSE_PSX_START: usize = SATURN_ROWS - PSX_ROWS;

pub const NP3_TILEDEF_ENTRIES: usize = 4096;

pub struct TileDefs {
    pub page: Vec<u8>,
    pub index: Vec<u8>,
    pub clut: Vec<u8>,
    pub collision: Vec<u8>,
}

pub struct Np3Art {
    tiles: HashMap<Block, Vec<u16>>,
    arrangements: HashMap<Block, Vec<(u8, u8, u8)>>,
    indexed_arrangements: HashMap<Vec<u8>, Vec<(u8, u8, u8)>>,
    palettes: Vec<[u16; 16]>,
    free_graphics: Vec<(u8, u8)>,
    free_palettes: Vec<u8>,
}

impl Np3Art {
    pub fn load(path: &Path, defs: &TileDefs) -> Result<Self> {
        Self::load_reserving(path, defs, &[])
    }

    fn load_reserving(path: &Path, defs: &TileDefs, reserved_defs: &[&TileDefs]) -> Result<Self> {
        let source = std::fs::read(path)?;
        if source.len() != 0x40000 {
            return Err(Error::Format(format!(
                "{} is {} bytes, expected a 0x40000-byte PSX stage tileset",
                path.display(),
                source.len()
            )));
        }

        let mut vram = vec![0u16; 1024 * 256];
        const X: [usize; 32] = [
            0x200, 0x220, 0x200, 0x220, 0x240, 0x260, 0x240, 0x260, 0x280, 0x2A0, 0x280, 0x2A0,
            0x2C0, 0x2E0, 0x2C0, 0x2E0, 0x300, 0x320, 0x300, 0x320, 0x340, 0x360, 0x340, 0x360,
            0x380, 0x3A0, 0x380, 0x3A0, 0x3C0, 0x3E0, 0x3C0, 0x3E0,
        ];
        for (i, &x) in X.iter().enumerate() {
            let y = if i & 2 != 0 { 0x80 } else { 0 };
            let chunk = &source[i * 0x2000..(i + 1) * 0x2000];
            for row in 0..0x80 {
                for column in 0..0x20 {
                    let at = (row * 0x20 + column) * 2;
                    vram[(y + row) * 1024 + x + column] =
                        u16::from_le_bytes([chunk[at], chunk[at + 1]]);
                }
            }
        }

        let mut palettes = Vec::with_capacity(256);
        for clut in 0..256 {
            let palette_x = 0x200 + (clut & 0x0F) * 16;
            let palette_y = 0xF0 + (clut >> 4);
            let mut palette = [0u16; 16];
            palette.copy_from_slice(
                &vram[palette_y * 1024 + palette_x..palette_y * 1024 + palette_x + 16],
            );
            for colour in &mut palette {
                *colour &= 0x7FFF;
            }
            palettes.push(palette);
        }

        let mut referenced = HashMap::new();
        let mut referenced_cluts = HashMap::new();
        for reserved in std::iter::once(defs).chain(reserved_defs.iter().copied()) {
            for id in 1..reserved.page.len().min(NP3_TILEDEF_ENTRIES) {
                referenced_cluts.insert(reserved.clut[id], ());
                let page = reserved.page[id] as usize;
                if page >= 8 {
                    continue;
                }
                referenced.insert((page as u8, reserved.index[id]), ());
            }
        }

        let render = |definition: &TileDefs, id: usize| -> Option<Block> {
            let page = definition.page[id] as usize;
            if page >= 8 {
                return None;
            }
            let index = definition.index[id] as usize;
            let u = (index & 0x0F) * 16;
            let v = (index >> 4) * 16;
            let clut = definition.clut[id] as usize;
            let palette_x = 0x200 + (clut & 0x0F) * 16;
            let palette_y = 0xF0 + (clut >> 4);
            let mut pixels = Vec::with_capacity(256);
            for y in 0..16 {
                for x in 0..16 {
                    let pixel_x = u + x;
                    let word = vram[(v + y) * 1024 + 0x200 + page * 0x40 + pixel_x / 4];
                    let colour_index = ((word >> ((pixel_x & 3) * 4)) & 0xF) as usize;
                    pixels.push(if colour_index == 0 {
                        None
                    } else {
                        Some(vram[palette_y * 1024 + palette_x + colour_index] & 0x7FFF)
                    });
                }
            }
            Some(pixels)
        };
        let render_indices = |definition: &TileDefs, id: usize| -> Option<Vec<u8>> {
            let page = definition.page[id] as usize;
            if page >= 8 {
                return None;
            }
            let index = definition.index[id] as usize;
            let u = (index & 0x0F) * 16;
            let v = (index >> 4) * 16;
            let mut pixels = Vec::with_capacity(256);
            for y in 0..16 {
                for x in 0..16 {
                    let pixel_x = u + x;
                    let word = vram[(v + y) * 1024 + 0x200 + page * 0x40 + pixel_x / 4];
                    pixels.push(((word >> ((pixel_x & 3) * 4)) & 0xF) as u8);
                }
            }
            Some(pixels)
        };

        let mut tiles: HashMap<Block, Vec<u16>> = HashMap::new();
        for id in 1..defs.page.len().min(NP3_TILEDEF_ENTRIES) {
            let Some(pixels) = render(defs, id) else {
                continue;
            };
            let ids = tiles.entry(pixels).or_default();
            ids.push(id as u16);
        }
        let mut arrangements: HashMap<Block, Vec<(u8, u8, u8)>> = HashMap::new();
        let mut indexed_arrangements: HashMap<Vec<u8>, Vec<(u8, u8, u8)>> = HashMap::new();
        for definition in std::iter::once(defs).chain(reserved_defs.iter().copied()) {
            for id in 1..definition.page.len().min(NP3_TILEDEF_ENTRIES) {
                let Some(pixels) = render(definition, id) else {
                    continue;
                };
                let art = definition.art(id as u16);
                let candidates = arrangements.entry(pixels).or_default();
                if !candidates.contains(&art) {
                    candidates.push(art);
                }
                let indices = render_indices(definition, id).unwrap();
                let candidates = indexed_arrangements.entry(indices).or_default();
                if !candidates.contains(&art) {
                    candidates.push(art);
                }
            }
        }
        for candidates in arrangements.values_mut() {
            candidates.sort_unstable();
            candidates.dedup();
        }
        for candidates in indexed_arrangements.values_mut() {
            candidates.sort_unstable();
            candidates.dedup();
        }

        let mut free_graphics = Vec::new();
        for page in 0..8usize {
            for index in 0..256usize {
                if page < 4 && index >> 4 == 0xF {
                    continue;
                }
                if referenced.contains_key(&(page as u8, index as u8)) {
                    continue;
                }
                let u = (index & 0x0F) * 16;
                let v = (index >> 4) * 16;
                let blank = (0..16).all(|y| {
                    (0..4)
                        .all(|word| vram[(v + y) * 1024 + 0x200 + page * 0x40 + u / 4 + word] == 0)
                });
                if blank {
                    free_graphics.push((page as u8, index as u8));
                }
            }
        }
        let free_palettes = palettes
            .iter()
            .enumerate()
            .filter(|(clut, _)| !referenced_cluts.contains_key(&(*clut as u8)))
            .map(|(clut, _)| clut as u8)
            .collect();
        Ok(Self {
            tiles,
            arrangements,
            indexed_arrangements,
            palettes,
            free_graphics,
            free_palettes,
        })
    }
}

impl TileDefs {
    pub fn load(dir: &Path, tiledef: usize) -> Result<Self> {
        Self::load_named(dir, "np3", tiledef)
    }

    fn load_named(dir: &Path, stage: &str, tiledef: usize) -> Result<Self> {
        let read = |what: &str| -> Result<Vec<u8>> {
            Ok(std::fs::read(
                dir.join(format!("{stage}_tiledef_{tiledef}_{what}.bin")),
            )?)
        };
        Ok(Self {
            page: read("tiles")?,
            index: read("pages")?,
            clut: read("cluts")?,
            collision: read("cols")?,
        })
    }

    fn art(&self, id: u16) -> (u8, u8, u8) {
        let at = id as usize;
        (
            self.page.get(at).copied().unwrap_or(0),
            self.index.get(at).copied().unwrap_or(0),
            self.clut.get(at).copied().unwrap_or(0),
        )
    }

    fn hit(&self, id: u16) -> u8 {
        self.collision.get(id as usize).copied().unwrap_or(0)
    }
}

#[derive(Clone, Copy, Debug)]
pub struct MintedTile {
    pub id: u16,
    pub page: u8,
    pub index: u8,
    pub clut: u8,
    pub collision: u8,
    pub from: u16,
}

pub struct Stitch {
    pub fg: Vec<u16>,
    pub bg: Vec<u16>,
    pub collision: Vec<u8>,
    pub minted: Vec<MintedTile>,
    pub graphics: Vec<GeneratedGraphic>,
    pub palettes: Vec<GeneratedPalette>,
    pub exact: usize,
    pub approximate: usize,
}

#[derive(Clone, Debug)]
pub struct GeneratedGraphic {
    pub page: u8,
    pub index: u8,
    pub pixels: Vec<u8>,
}

#[derive(Clone, Debug)]
pub struct GeneratedPalette {
    pub clut: u8,
    pub colours: [u16; 16],
}

type Block = Vec<Option<u16>>;

fn block(raster: &Raster, tx: usize, ty: usize) -> Block {
    let mut out = Vec::with_capacity(256);
    for y in 0..16 {
        let at = (ty * 16 + y) * raster.width + tx * 16;
        out.extend_from_slice(&raster.pixels[at..at + 16]);
    }
    out
}

fn block_variants(rasters: &[&Raster], tx: usize, ty: usize) -> Vec<Block> {
    let mut out = Vec::with_capacity(625);
    let choices = [624usize, 0, 156, 312, 468]
        .into_iter()
        .chain((0..625).filter(|choice| ![624, 0, 156, 312, 468].contains(choice)));
    for choice in choices {
        let mut phases = [0usize; 4];
        let mut remaining = choice;
        for phase in &mut phases {
            *phase = remaining % 5;
            remaining /= 5;
        }
        let mut pixels = Vec::with_capacity(256);
        for y in 0..16 {
            for (group, &phase) in phases.iter().enumerate() {
                let raster = rasters[phase];
                let at = (ty * 16 + y) * raster.width + tx * 16 + group * 4;
                pixels.extend_from_slice(&raster.pixels[at..at + 4]);
            }
        }
        out.push(pixels);
    }
    out
}

fn indexed_block_variants(rasters: &[&Raster], tx: usize, ty: usize) -> Vec<Vec<u8>> {
    let mut out = Vec::with_capacity(625);
    let choices = [624usize, 0, 156, 312, 468]
        .into_iter()
        .chain((0..625).filter(|choice| ![624, 0, 156, 312, 468].contains(choice)));
    for choice in choices {
        let mut phases = [0usize; 4];
        let mut remaining = choice;
        for phase in &mut phases {
            *phase = remaining % 5;
            remaining /= 5;
        }
        let mut pixels = Vec::with_capacity(256);
        for y in 0..16 {
            for (group, &phase) in phases.iter().enumerate() {
                let raster = rasters[phase];
                let at = (ty * 16 + y) * raster.width + tx * 16 + group * 4;
                pixels.extend_from_slice(&raster.indices[at..at + 4]);
            }
        }
        out.push(pixels);
    }
    out
}

fn is_empty(block: &Block) -> bool {
    block.iter().all(|pixel| pixel.is_none())
}

fn colour_pattern(block: &Block) -> Vec<u8> {
    let mut colours = Vec::new();
    block
        .iter()
        .map(|pixel| match pixel {
            None => 0,
            Some(colour) => {
                let index = colours
                    .iter()
                    .position(|entry| entry == colour)
                    .unwrap_or_else(|| {
                        colours.push(*colour);
                        colours.len() - 1
                    });
                (index + 1) as u8
            }
        })
        .collect()
}

fn block_distance(left: &Block, right: &Block) -> u64 {
    left.iter()
        .zip(right)
        .map(|(a, b)| match (a, b) {
            (None, None) => 0,
            (Some(a), Some(b)) => {
                let channel =
                    |shift: u32| ((*a >> shift) & 31) as i32 - ((*b >> shift) & 31) as i32;
                [channel(0), channel(5), channel(10)]
                    .into_iter()
                    .map(|delta| (delta * delta) as u64)
                    .sum()
            }
            _ => 100_000,
        })
        .sum()
}

fn block_pattern_distance(left: &Block, right: &Block) -> usize {
    colour_pattern(left)
        .iter()
        .zip(colour_pattern(right))
        .map(|(a, b)| match (*a == 0, b == 0) {
            (true, true) => 0,
            (true, false) | (false, true) => 256,
            (false, false) => usize::from(*a != b),
        })
        .sum()
}

#[derive(Clone, Copy)]
struct TileRegion {
    left: usize,
    top: usize,
    width: usize,
    height: usize,
}

#[derive(Clone, Copy)]
struct SaturnRoomSource {
    room: usize,
    bounds: (u8, u8, u8, u8),
    room_width: usize,
    room_height: usize,
    region: TileRegion,
    name: &'static str,
}

fn region<T: Copy>(
    data: &[T],
    source_width: usize,
    source_height: usize,
    area: TileRegion,
    name: &str,
) -> Result<Vec<T>> {
    if data.len() < source_width * source_height
        || area.left + area.width > source_width
        || area.top + area.height > source_height
    {
        return Err(Error::Format(format!("invalid {name} region")));
    }
    let mut result = Vec::with_capacity(area.width * area.height);
    for row in area.top..area.top + area.height {
        let start = row * source_width + area.left;
        result.extend_from_slice(&data[start..start + area.width]);
    }
    Ok(result)
}

fn load_saturn_room_source(
    prg_path: &Path,
    map_path: &Path,
    scratch: &Path,
    source: SaturnRoomSource,
) -> Result<(Vec<u8>, Vec<(Raster, Raster)>)> {
    let manifest = map::extract(prg_path, map_path, scratch)?;
    let overlay = std::fs::read(map::overlay_for(prg_path, map_path))?;
    let map_data = std::fs::read(map_path)?;
    let room = read_rooms(&overlay)?
        .get(source.room)
        .copied()
        .ok_or_else(|| Error::Format(format!("{} does not exist", source.name)))?;
    let bounds = room.bounds;
    let actual = (bounds.left, bounds.top, bounds.right, bounds.bottom);
    if !matches!(room.kind, RoomKind::Ordinary { .. }) || actual != source.bounds {
        return Err(Error::Format(format!(
            "{} is ({},{})-({},{}), expected ({},{})-({},{})",
            source.name,
            actual.0,
            actual.1,
            actual.2,
            actual.3,
            source.bounds.0,
            source.bounds.1,
            source.bounds.2,
            source.bounds.3,
        )));
    }

    let stream = manifest.tables.room_graphics[source.room];
    let at = stream.offset as usize;
    let bytes = map_data
        .get(at..at + stream.size as usize)
        .ok_or_else(|| Error::Format(format!("{} collision lies outside the MAP", source.name)))?;
    let collision = crate::lzss::decompress(bytes);
    let collision = region(
        &collision,
        source.room_width,
        source.room_height,
        source.region,
        &format!("{} collision", source.name),
    )?;

    let full_width = source.room_width * 16;
    let full_height = source.room_height * 16;
    let pixel_region = TileRegion {
        left: source.region.left * 16,
        top: source.region.top * 16,
        width: source.region.width * 16,
        height: source.region.height * 16,
    };
    let mut phases = Vec::with_capacity(5);
    for discarded_column in 0..5 {
        let fg = render_layer_raster_phase(&manifest, &map_data, source.room, 0, discarded_column)?;
        let bg = render_layer_raster_phase(&manifest, &map_data, source.room, 2, discarded_column)?;
        for raster in [&fg, &bg] {
            if raster.width != full_width || raster.height != full_height {
                return Err(Error::Format(format!(
                    "squished {} is {}x{}, expected {}x{}",
                    source.name, raster.width, raster.height, full_width, full_height,
                )));
            }
        }
        let crop = |raster: &Raster, layer: &str| -> Result<Raster> {
            Ok(Raster {
                width: pixel_region.width,
                height: pixel_region.height,
                pixels: region(
                    &raster.pixels,
                    full_width,
                    full_height,
                    pixel_region,
                    &format!("{} {layer}", source.name),
                )?,
                indices: region(
                    &raster.indices,
                    full_width,
                    full_height,
                    pixel_region,
                    &format!("{} {layer} indices", source.name),
                )?,
            })
        };
        phases.push((crop(&fg, "foreground")?, crop(&bg, "background")?));
    }
    Ok((collision, phases))
}

const SATURN_SHAFT_SOURCE: SaturnRoomSource = SaturnRoomSource {
    room: SATURN_SHAFT_ROOM,
    bounds: (2, 41, 2, 44),
    room_width: TILES,
    room_height: SATURN_ROWS,
    region: TileRegion {
        left: 0,
        top: 0,
        width: TILES,
        height: SATURN_ROWS,
    },
    name: "STAGE_01 room 17",
};

const SATURN_REVERSE_SHAFT_SOURCE: SaturnRoomSource = SaturnRoomSource {
    bounds: (61, 19, 61, 22),
    name: "RSTAGE01 room 17",
    ..SATURN_SHAFT_SOURCE
};

pub fn saturn_shaft_collision(prg_path: &Path, map_path: &Path, scratch: &Path) -> Result<Vec<u8>> {
    load_saturn_room_source(prg_path, map_path, scratch, SATURN_SHAFT_SOURCE).map(|source| source.0)
}

pub fn saturn_shaft_art(
    prg_path: &Path,
    map_path: &Path,
    scratch: &Path,
) -> Result<Vec<(Raster, Raster)>> {
    load_saturn_room_source(prg_path, map_path, scratch, SATURN_SHAFT_SOURCE).map(|source| source.1)
}

fn learn(saturn: &[&Raster], psx: &[u16]) -> HashMap<Block, Vec<u16>> {
    let mut dict: HashMap<Block, Vec<u16>> = HashMap::new();
    let pair = |saturn_row: usize, psx_row: usize, dict: &mut HashMap<Block, Vec<u16>>| {
        for tx in 0..TILES {
            for raster in saturn {
                let id = psx[psx_row * TILES + tx];
                let ids = dict.entry(block(raster, tx, saturn_row)).or_default();
                if !ids.contains(&id) {
                    ids.push(id);
                }
            }
        }
    };
    for row in 0..STITCH_ROW {
        pair(row, row, &mut dict);
    }
    for psx_row in CHAMBER_ROWS {
        pair(psx_row + CHAMBER_SHIFT, psx_row, &mut dict);
    }
    dict
}

struct Minter<'a> {
    defs: &'a TileDefs,
    next: u16,
    minted: Vec<MintedTile>,
    seen: HashMap<(u16, u8), u16>,
    seen_art: HashMap<(u8, u8, u8, u8), u16>,
}

impl<'a> Minter<'a> {
    fn resolve(&mut self, source: u16, collision: u8) -> Result<u16> {
        if self.defs.hit(source) == collision {
            return Ok(source);
        }
        if let Some(&id) = self.seen.get(&(source, collision)) {
            return Ok(id);
        }
        let (page, index, clut) = self.defs.art(source);
        for id in 0..self.next {
            if self.defs.art(id) == (page, index, clut) && self.defs.hit(id) == collision {
                self.seen.insert((source, collision), id);
                return Ok(id);
            }
        }
        if self.next as usize >= NP3_TILEDEF_ENTRIES {
            return Err(Error::Format(
                "ran out of NP3 tile definitions to mint into".to_string(),
            ));
        }
        let id = self.next;
        self.next += 1;
        self.minted.push(MintedTile {
            id,
            page,
            index,
            clut,
            collision,
            from: source,
        });
        self.seen.insert((source, collision), id);
        Ok(id)
    }

    fn resolve_art(&mut self, page: u8, index: u8, clut: u8, collision: u8) -> Result<u16> {
        let key = (page, index, clut, collision);
        if let Some(&id) = self.seen_art.get(&key) {
            return Ok(id);
        }
        for id in 1..self.next {
            if self.defs.art(id) == (page, index, clut) && self.defs.hit(id) == collision {
                self.seen_art.insert(key, id);
                return Ok(id);
            }
        }
        if self.next as usize >= NP3_TILEDEF_ENTRIES {
            return Err(Error::Format(
                "ran out of NP3 tile definitions to mint into".to_string(),
            ));
        }
        let id = self.next;
        self.next += 1;
        self.minted.push(MintedTile {
            id,
            page,
            index,
            clut,
            collision,
            from: 0xFFFF,
        });
        self.seen_art.insert(key, id);
        Ok(id)
    }
}

struct GraphicMinter<'a> {
    art: &'a Np3Art,
    next: usize,
    graphics: Vec<GeneratedGraphic>,
    palettes: Vec<GeneratedPalette>,
    seen: HashMap<Block, (u8, u8, u8)>,
    seen_indexed: HashMap<(Vec<u8>, u8), (u8, u8, u8)>,
}

fn dominant_layout_clut(defs: &TileDefs, fg: &[u16], bg: &[u16]) -> u8 {
    let mut counts: HashMap<u8, usize> = HashMap::new();
    for &id in fg.iter().chain(bg).filter(|&&id| id != 0) {
        *counts.entry(defs.art(id).2).or_default() += 1;
    }
    counts
        .into_iter()
        .max_by_key(|&(clut, count)| (count, std::cmp::Reverse(clut)))
        .map(|(clut, _)| clut)
        .unwrap_or(0)
}

impl<'a> GraphicMinter<'a> {
    fn encode_mirrored_palette(
        &mut self,
        variants: &[Block],
        indexed_variants: &[Vec<u8>],
    ) -> Result<(u8, u8, u8)> {
        for (pixels, indices) in variants.iter().zip(indexed_variants) {
            let mut palette = [0u16; 16];
            let mut compatible = true;
            for (&colour, &index) in pixels.iter().zip(indices) {
                let Some(colour) = colour else { continue };
                let slot = &mut palette[index as usize];
                if *slot != 0 && *slot != colour {
                    compatible = false;
                    break;
                }
                *slot = colour;
            }
            let encoded_indices = if compatible {
                indices.clone()
            } else {
                let mut colours = Vec::new();
                for colour in pixels.iter().flatten() {
                    if !colours.contains(colour) {
                        colours.push(*colour);
                    }
                }
                if colours.len() > 15 {
                    continue;
                }
                palette = [0u16; 16];
                palette[1..1 + colours.len()].copy_from_slice(&colours);
                pixels
                    .iter()
                    .map(|pixel| match pixel {
                        None => 0,
                        Some(colour) => {
                            colours.iter().position(|entry| entry == colour).unwrap() as u8 + 1
                        }
                    })
                    .collect()
            };
            let existing = self.palettes.iter().position(|generated| {
                generated
                    .colours
                    .iter()
                    .zip(&palette)
                    .all(|(&a, &b)| a == 0 || b == 0 || a == b)
            });
            let clut = if let Some(at) = existing {
                for (target, &source) in self.palettes[at].colours.iter_mut().zip(&palette) {
                    if *target == 0 {
                        *target = source;
                    }
                }
                self.palettes[at].clut
            } else {
                let clut = *self
                    .art
                    .free_palettes
                    .get(self.palettes.len())
                    .ok_or_else(|| {
                        Error::Format("ran out of blank RNO3 CLUTs for Saturn palettes".to_string())
                    })?;
                self.palettes.push(GeneratedPalette {
                    clut,
                    colours: palette,
                });
                clut
            };
            if compatible {
                if let Some(candidates) = self.art.indexed_arrangements.get(indices) {
                    let (page, index, _) = candidates[0];
                    return Ok((page, index, clut));
                }
            }
            if let Some(&encoded) = self.seen_indexed.get(&(encoded_indices.clone(), clut)) {
                return Ok(encoded);
            }
            let (page, index) = *self.art.free_graphics.get(self.next).ok_or_else(|| {
                Error::Format("ran out of blank RNO3 graphics for Saturn arrangements".to_string())
            })?;
            self.next += 1;
            let packed = encoded_indices
                .chunks_exact(2)
                .map(|pair| pair[0] | (pair[1] << 4))
                .collect();
            self.graphics.push(GeneratedGraphic {
                page,
                index,
                pixels: packed,
            });
            let encoded = (page, index, clut);
            self.seen_indexed.insert((encoded_indices, clut), encoded);
            return Ok(encoded);
        }
        Err(Error::Format(
            "Saturn block mixes palette banks inside one PSX tile".to_string(),
        ))
    }

    fn encode_fixed_clut(&mut self, variants: &[Block], clut: u8) -> Result<(u8, u8, u8)> {
        let palette = &self.art.palettes[clut as usize];
        let distance = |a: u16, b: u16| -> u32 {
            [0, 5, 10]
                .into_iter()
                .map(|shift| {
                    let delta = ((a >> shift) & 31) as i32 - ((b >> shift) & 31) as i32;
                    (delta * delta) as u32
                })
                .sum()
        };
        let (indices, _) = variants
            .iter()
            .map(|pixels| {
                let mut score = 0u32;
                let indices: Vec<u8> = pixels
                    .iter()
                    .map(|pixel| match pixel {
                        None => 0,
                        Some(colour) => {
                            let (index, cost) = (1..16)
                                .map(|index| (index as u8, distance(*colour, palette[index])))
                                .min_by_key(|&(index, cost)| (cost, index))
                                .unwrap();
                            score += cost;
                            index
                        }
                    })
                    .collect();
                (indices, score)
            })
            .min_by_key(|(_, score)| *score)
            .ok_or_else(|| Error::Format("RNO3 has no indexed Saturn variant".to_string()))?;
        if let Some(&encoded) = self.seen_indexed.get(&(indices.clone(), clut)) {
            return Ok(encoded);
        }
        let (page, index) = *self.art.free_graphics.get(self.next).ok_or_else(|| {
            Error::Format(
                "ran out of blank RNO3 graphics for fixed-palette arrangements".to_string(),
            )
        })?;
        self.next += 1;
        let packed = indices
            .chunks_exact(2)
            .map(|pair| pair[0] | (pair[1] << 4))
            .collect();
        self.graphics.push(GeneratedGraphic {
            page,
            index,
            pixels: packed,
        });
        let encoded = (page, index, clut);
        self.seen_indexed.insert((indices, clut), encoded);
        Ok(encoded)
    }

    fn encode(&mut self, variants: &[Block]) -> Result<(u8, u8, u8)> {
        for pixels in variants {
            if let Some(&art) = self.seen.get(pixels) {
                return Ok(art);
            }
            for (clut, palette) in self.art.palettes.iter().enumerate() {
                let mut indices = Vec::with_capacity(256);
                let mut representable = true;
                for pixel in pixels {
                    let index = match pixel {
                        None => 0,
                        Some(colour) => match palette[1..].iter().position(|entry| entry == colour)
                        {
                            Some(index) => index + 1,
                            None => {
                                representable = false;
                                break;
                            }
                        },
                    };
                    indices.push(index as u8);
                }
                if !representable {
                    continue;
                }
                let (page, index) = *self.art.free_graphics.get(self.next).ok_or_else(|| {
                    Error::Format(
                        "ran out of blank NP3 graphics for Saturn arrangements".to_string(),
                    )
                })?;
                self.next += 1;
                let packed = indices
                    .chunks_exact(2)
                    .map(|pair| pair[0] | (pair[1] << 4))
                    .collect();
                self.graphics.push(GeneratedGraphic {
                    page,
                    index,
                    pixels: packed,
                });
                let encoded = (page, index, clut as u8);
                self.seen.insert(pixels.clone(), encoded);
                return Ok(encoded);
            }

            let mut colours = Vec::new();
            for &pixel in pixels.iter().flatten() {
                if !colours.contains(&pixel) {
                    colours.push(pixel);
                }
            }
            if colours.len() <= 15 {
                let distance = |a: u16, b: u16| -> u32 {
                    let channel = |value: u16, shift: u32| ((value >> shift) & 0x1Fu16) as i32;
                    let dr = channel(a, 0) - channel(b, 0);
                    let dg = channel(a, 5) - channel(b, 5);
                    let db = channel(a, 10) - channel(b, 10);
                    (dr * dr + dg * dg + db * db) as u32
                };
                let mut best: Option<(u32, usize, Vec<u8>)> = None;
                for (clut, palette) in self.art.palettes.iter().enumerate() {
                    let mut used = [false; 16];
                    let mut mapping = Vec::with_capacity(colours.len());
                    let mut score = 0;
                    for &colour in &colours {
                        let Some((index, cost)) = (1..16)
                            .filter(|&index| !used[index])
                            .map(|index| (index, distance(colour, palette[index])))
                            .min_by_key(|&(_, cost)| cost)
                        else {
                            continue;
                        };
                        used[index] = true;
                        mapping.push(index as u8);
                        score += cost;
                    }
                    if best.as_ref().map_or(true, |(old, _, _)| score < *old) {
                        best = Some((score, clut, mapping));
                    }
                }
                if let Some((_, clut, mapping)) = best {
                    let (page, index) =
                        *self.art.free_graphics.get(self.next).ok_or_else(|| {
                            Error::Format(
                                "ran out of blank NP3 graphics for Saturn arrangements".to_string(),
                            )
                        })?;
                    self.next += 1;
                    let indices: Vec<u8> = pixels
                        .iter()
                        .map(|pixel| match pixel {
                            None => 0,
                            Some(colour) => {
                                mapping[colours.iter().position(|entry| entry == colour).unwrap()]
                            }
                        })
                        .collect();
                    let packed = indices
                        .chunks_exact(2)
                        .map(|pair| pair[0] | (pair[1] << 4))
                        .collect();
                    self.graphics.push(GeneratedGraphic {
                        page,
                        index,
                        pixels: packed,
                    });
                    let encoded = (page, index, clut as u8);
                    self.seen.insert(pixels.clone(), encoded);
                    return Ok(encoded);
                }
            }
            if colours.len() <= 15 {
                let clut = *self
                    .art
                    .free_palettes
                    .get(self.palettes.len())
                    .ok_or_else(|| {
                        Error::Format(
                            "ran out of blank NP3 palettes for Saturn arrangements".to_string(),
                        )
                    })?;
                let (page, index) = *self.art.free_graphics.get(self.next).ok_or_else(|| {
                    Error::Format(
                        "ran out of blank NP3 graphics for Saturn arrangements".to_string(),
                    )
                })?;
                self.next += 1;
                let mut palette = [0u16; 16];
                palette[1..1 + colours.len()].copy_from_slice(&colours);
                let indices: Vec<u8> = pixels
                    .iter()
                    .map(|pixel| match pixel {
                        None => 0,
                        Some(colour) => {
                            colours.iter().position(|entry| entry == colour).unwrap() as u8 + 1
                        }
                    })
                    .collect();
                let packed = indices
                    .chunks_exact(2)
                    .map(|pair| pair[0] | (pair[1] << 4))
                    .collect();
                self.graphics.push(GeneratedGraphic {
                    page,
                    index,
                    pixels: packed,
                });
                self.palettes.push(GeneratedPalette {
                    clut,
                    colours: palette,
                });
                let encoded = (page, index, clut);
                self.seen.insert(pixels.clone(), encoded);
                return Ok(encoded);
            }
        }
        Err(Error::Format(
            "no NP3 palette can represent an unmatched Saturn block exactly".to_string(),
        ))
    }
}

pub fn build(
    saturn_art: &[(Raster, Raster)],
    psx_fg: &[u16],
    psx_bg: &[u16],
    defs: &TileDefs,
    np3_art: &Np3Art,
    saturn_collision: &[u8],
    first_free_tile: u16,
) -> Result<Stitch> {
    if psx_fg.len() != TILES * PSX_ROWS || psx_bg.len() != TILES * PSX_ROWS {
        return Err(Error::Format(format!(
            "PSX shaft tilemaps must be {} tiles",
            TILES * PSX_ROWS
        )));
    }
    if saturn_collision.len() != TILES * SATURN_ROWS {
        return Err(Error::Format(format!(
            "Saturn shaft collision must be {} tiles",
            TILES * SATURN_ROWS
        )));
    }

    if saturn_art.len() != 5 {
        return Err(Error::Format(format!(
            "expected all 5 Saturn raster phases, got {}",
            saturn_art.len()
        )));
    }
    let saturn_fg: Vec<&Raster> = saturn_art.iter().map(|phase| &phase.0).collect();
    let saturn_bg: Vec<&Raster> = saturn_art.iter().map(|phase| &phase.1).collect();
    let mut fg_dict = learn(&saturn_fg, psx_fg);
    let mut bg_dict = learn(&saturn_bg, psx_bg);
    for (pixels, ids) in &np3_art.tiles {
        for dict in [&mut fg_dict, &mut bg_dict] {
            let entry = dict.entry(pixels.clone()).or_default();
            for &id in ids {
                if !entry.contains(&id) {
                    entry.push(id);
                }
            }
        }
    }
    let mut minter = Minter {
        defs,
        next: first_free_tile,
        minted: Vec::new(),
        seen: HashMap::new(),
        seen_art: HashMap::new(),
    };
    let mut graphic_minter = GraphicMinter {
        art: np3_art,
        next: 0,
        graphics: Vec::new(),
        palettes: Vec::new(),
        seen: HashMap::new(),
        seen_indexed: HashMap::new(),
    };
    let mut fg = vec![0u16; TILES * SATURN_ROWS];
    let mut bg = vec![0u16; TILES * SATURN_ROWS];
    let mut exact = 0;
    let approximate = 0;

    fg[..TILES * STITCH_ROW].copy_from_slice(&psx_fg[..TILES * STITCH_ROW]);
    bg[..TILES * STITCH_ROW].copy_from_slice(&psx_bg[..TILES * STITCH_ROW]);

    for row in STITCH_ROW..SATURN_ROWS {
        for column in 0..TILES {
            let at = row * TILES + column;

            let want = saturn_collision[at];
            let keys = block_variants(&saturn_fg, column, row);
            if keys.iter().any(is_empty) && want == 0 {
                fg[at] = 0;
                exact += 1;
            } else {
                let candidates = keys.iter().find_map(|key| fg_dict.get(key)).cloned();
                exact += 1;
                fg[at] = if let Some(candidates) = candidates {
                    let source = candidates
                        .iter()
                        .copied()
                        .find(|&id| defs.hit(id) == want)
                        .unwrap_or(candidates[0]);
                    minter.resolve(source, want)?
                } else {
                    let (page, index, clut) = graphic_minter.encode(&keys).map_err(|error| {
                        Error::Format(format!("foreground row {row} column {column}: {error}"))
                    })?;
                    minter.resolve_art(page, index, clut, want)?
                };
            }

            let keys = block_variants(&saturn_bg, column, row);
            bg[at] = if keys.iter().any(is_empty) {
                0
            } else {
                if let Some(ids) = keys.iter().find_map(|key| bg_dict.get(key)) {
                    ids[0]
                } else {
                    let (page, index, clut) = graphic_minter.encode(&keys).map_err(|error| {
                        Error::Format(format!("backdrop row {row} column {column}: {error}"))
                    })?;
                    minter.resolve_art(page, index, clut, 0)?
                }
            };
        }
    }

    Ok(Stitch {
        fg,
        bg,
        collision: saturn_collision.to_vec(),
        minted: minter.minted,
        graphics: graphic_minter.graphics,
        palettes: graphic_minter.palettes,
        exact,
        approximate,
    })
}

pub fn verify(
    stitch: &Stitch,
    psx_fg: &[u16],
    defs: &TileDefs,
    saturn_collision: &[u8],
) -> Result<()> {
    let shared = (0..PSX_ROWS)
        .take_while(|&row| {
            (0..TILES).all(|column| {
                defs.hit(psx_fg[row * TILES + column]) == saturn_collision[row * TILES + column]
            })
        })
        .count();
    if shared != STITCH_ROW {
        return Err(Error::Format(format!(
            "the versions share {shared} tile rows but STITCH_ROW is {STITCH_ROW}"
        )));
    }

    verify_collision(stitch, defs, saturn_collision, TILES, "NP3 shaft")
}

fn verify_collision(
    stitch: &Stitch,
    defs: &TileDefs,
    wanted: &[u8],
    width: usize,
    name: &str,
) -> Result<()> {
    let minted: HashMap<u16, u8> = stitch
        .minted
        .iter()
        .map(|tile| (tile.id, tile.collision))
        .collect();
    for (at, (&tile, &want)) in stitch.fg.iter().zip(wanted).enumerate() {
        let got = if tile == 0 {
            0
        } else {
            minted.get(&tile).copied().unwrap_or_else(|| defs.hit(tile))
        };
        if got != want {
            return Err(Error::Format(format!(
                "{name} collision mismatch at row {} column {}: \
                 0x{got:02X} != 0x{want:02X}",
                at / width,
                at % width
            )));
        }
    }
    Ok(())
}

fn read_tilemap(path: &Path) -> Result<Vec<u16>> {
    Ok(std::fs::read(path)?
        .chunks_exact(2)
        .map(|b| u16::from_le_bytes([b[0], b[1]]))
        .collect())
}

fn first_free_tile_named(assets: &Path, stage: &str) -> Result<u16> {
    let mut highest = 0u16;
    for entry in std::fs::read_dir(assets)? {
        let path = entry?.path();
        let name = path.file_name().and_then(|n| n.to_str()).unwrap_or("");
        if name.starts_with(&format!("{stage}_tilemap_")) && name.ends_with(".bin") {
            highest = highest.max(read_tilemap(&path)?.into_iter().max().unwrap_or(0));
        }
    }
    Ok(highest + 1)
}

const NO4_SATURN_ROOM: usize = 4;
const NO4_TILES: usize = 16;
const NO4_ROWS: usize = 32;

const NO4_SOURCE: SaturnRoomSource = SaturnRoomSource {
    room: NO4_SATURN_ROOM,
    bounds: (23, 37, 24, 42),
    room_width: NO4_TILES,
    room_height: NO4_ROWS,
    region: TileRegion {
        left: 0,
        top: 0,
        width: NO4_TILES,
        height: NO4_ROWS,
    },
    name: "STAGE_9B room 4",
};

#[derive(Clone, Copy, PartialEq, Eq)]
enum ArtPolicy {
    Exact,
    ReuseNearest,
    FixedPalette,
    MirroredPalette,
}

impl ArtPolicy {
    fn samples_all_phases(self) -> bool {
        self != Self::Exact
    }

    fn preserves_matching_rows(self) -> bool {
        matches!(self, Self::ReuseNearest | Self::FixedPalette)
    }
}

struct BuildConfig {
    rows: usize,
    art: ArtPolicy,
    source_name: &'static str,
}

fn build_room(
    saturn_art: &[(Raster, Raster)],
    psx_fg_layout: &[u16],
    psx_bg_layout: &[u16],
    defs: &TileDefs,
    art: &Np3Art,
    collision: &[u8],
    first_free: u16,
    config: BuildConfig,
) -> Result<Stitch> {
    let rows = config.rows;
    let source_name = config.source_name;
    if saturn_art.is_empty()
        || collision.len() != NO4_TILES * rows
        || psx_fg_layout.len() != NO4_TILES * rows
        || psx_bg_layout.len() != NO4_TILES * rows
    {
        return Err(Error::Format(
            "incomplete STAGE_9B room 4 source".to_string(),
        ));
    }
    let mut pattern_dict: HashMap<Vec<u8>, Vec<(u8, u8, u8)>> = HashMap::new();
    for (pixels, arrangements) in &art.arrangements {
        let entry = pattern_dict.entry(colour_pattern(pixels)).or_default();
        for &arrangement in arrangements {
            if !entry.contains(&arrangement) {
                entry.push(arrangement);
            }
        }
    }
    for arrangements in pattern_dict.values_mut() {
        arrangements.sort_unstable();
        arrangements.dedup();
    }
    let mut selected_patterns: HashMap<Vec<u8>, Vec<u16>> = HashMap::new();
    for (pixels, ids) in &art.tiles {
        let entry = selected_patterns.entry(colour_pattern(pixels)).or_default();
        entry.extend(ids.iter().copied());
    }
    for ids in selected_patterns.values_mut() {
        ids.sort_unstable();
        ids.dedup();
    }
    let mut minter = Minter {
        defs,
        next: first_free,
        minted: Vec::new(),
        seen: HashMap::new(),
        seen_art: HashMap::new(),
    };
    let mut graphic_minter = GraphicMinter {
        art,
        next: 0,
        graphics: Vec::new(),
        palettes: Vec::new(),
        seen: HashMap::new(),
        seen_indexed: HashMap::new(),
    };
    let saturn_fg: Vec<&Raster> = saturn_art.iter().map(|phase| &phase.0).collect();
    let saturn_bg: Vec<&Raster> = saturn_art.iter().map(|phase| &phase.1).collect();
    let mut fg = vec![0u16; NO4_TILES * rows];
    let mut bg = vec![0u16; NO4_TILES * rows];
    let mut psx_fg = 0usize;
    let mut psx_bg = 0usize;
    let mut generated_fg = 0usize;
    let mut generated_bg = 0usize;
    let mut nearest_fg = 0usize;
    let mut nearest_bg = 0usize;
    let mut preserved_rows = 0usize;
    let generated_fg_clut = dominant_layout_clut(defs, psx_fg_layout, &[]);
    let generated_bg_clut = dominant_layout_clut(defs, &[], psx_bg_layout);
    for row in 0..rows {
        let row_matches = config.art.preserves_matching_rows()
            && (0..NO4_TILES).all(|column| {
                let at = row * NO4_TILES + column;
                if defs.hit(psx_fg_layout[at]) != collision[at] {
                    return false;
                }
                let matches = |id: u16, rasters: &[&Raster]| {
                    if id == 0 {
                        return block_variants(rasters, column, row).iter().any(is_empty);
                    }
                    let Some((pixels, _)) = art.tiles.iter().find(|(_, ids)| ids.contains(&id))
                    else {
                        return false;
                    };
                    let pattern = colour_pattern(pixels);
                    block_variants(rasters, column, row)
                        .iter()
                        .any(|candidate| colour_pattern(candidate) == pattern)
                };
                matches(psx_fg_layout[at], &saturn_fg) && matches(psx_bg_layout[at], &saturn_bg)
            });
        if row_matches {
            let start = row * NO4_TILES;
            fg[start..start + NO4_TILES].copy_from_slice(&psx_fg_layout[start..start + NO4_TILES]);
            bg[start..start + NO4_TILES].copy_from_slice(&psx_bg_layout[start..start + NO4_TILES]);
            psx_fg += NO4_TILES;
            psx_bg += NO4_TILES;
            preserved_rows += 1;
            continue;
        }
        for column in 0..NO4_TILES {
            let at = row * NO4_TILES + column;
            let want = collision[at];
            let variants = if config.art.samples_all_phases() {
                block_variants(&saturn_fg, column, row)
            } else {
                vec![block(saturn_fg[0], column, row)]
            };
            let indexed_variants = (config.art == ArtPolicy::MirroredPalette)
                .then(|| indexed_block_variants(&saturn_fg, column, row));
            let all_candidate = if config.art == ArtPolicy::ReuseNearest {
                variants
                    .iter()
                    .filter(|key| !is_empty(key))
                    .find_map(|key| {
                        art.arrangements
                            .get(key)
                            .or_else(|| pattern_dict.get(&colour_pattern(key)))
                    })
            } else {
                None
            };
            let selected_candidate = if config.art == ArtPolicy::MirroredPalette {
                None
            } else {
                variants
                    .iter()
                    .filter(|key| !is_empty(key))
                    .find_map(|key| {
                        art.tiles
                            .get(key)
                            .or_else(|| selected_patterns.get(&colour_pattern(key)))
                    })
            };
            if want == 0 && variants.iter().all(is_empty) {
                fg[at] = 0;
            } else if let Some(ids) = selected_candidate {
                let source = ids
                    .iter()
                    .copied()
                    .find(|&id| defs.hit(id) == want)
                    .unwrap_or(ids[0]);
                fg[at] = minter.resolve(source, want)?;
                psx_fg += 1;
            } else if let Some(candidates) = all_candidate {
                let (page, index, clut) = candidates[0];
                fg[at] = minter.resolve_art(page, index, clut, want)?;
                psx_fg += 1;
            } else {
                let wanted = variants
                    .iter()
                    .find(|key| !is_empty(key))
                    .unwrap_or(&variants[0]);
                if config.art == ArtPolicy::ReuseNearest {
                    let (_, candidates) = art
                        .arrangements
                        .iter()
                        .filter(|(pixels, _)| !is_empty(pixels))
                        .min_by(|a, b| {
                            block_pattern_distance(wanted, a.0)
                                .cmp(&block_pattern_distance(wanted, b.0))
                                .then_with(|| a.0.cmp(b.0))
                        })
                        .ok_or_else(|| Error::Format("RNO4 has no PSX arrangements".to_string()))?;
                    let (page, index, clut) = candidates[0];
                    fg[at] = minter.resolve_art(page, index, clut, want)?;
                    nearest_fg += 1;
                } else {
                    let encoded = match config.art {
                        ArtPolicy::FixedPalette => {
                            graphic_minter.encode_fixed_clut(&variants, generated_fg_clut)
                        }
                        ArtPolicy::MirroredPalette => graphic_minter
                            .encode_mirrored_palette(&variants, indexed_variants.as_ref().unwrap()),
                        ArtPolicy::Exact => graphic_minter.encode(&variants),
                        ArtPolicy::ReuseNearest => unreachable!(),
                    }
                    .map_err(|error| {
                        Error::Format(format!(
                            "{source_name} foreground row {row} column {column}: {error}"
                        ))
                    })?;
                    let (page, index, clut) = encoded;
                    fg[at] = minter.resolve_art(page, index, clut, want)?;
                    generated_fg += 1;
                }
            }

            let variants = if config.art.samples_all_phases() {
                block_variants(&saturn_bg, column, row)
            } else {
                vec![block(saturn_bg[0], column, row)]
            };
            let indexed_variants = (config.art == ArtPolicy::MirroredPalette)
                .then(|| indexed_block_variants(&saturn_bg, column, row));
            let all_candidate = if config.art == ArtPolicy::ReuseNearest {
                variants
                    .iter()
                    .filter(|key| !is_empty(key))
                    .find_map(|key| {
                        art.arrangements
                            .get(key)
                            .or_else(|| pattern_dict.get(&colour_pattern(key)))
                    })
            } else {
                None
            };
            let selected_candidate = if config.art == ArtPolicy::MirroredPalette {
                None
            } else {
                variants
                    .iter()
                    .filter(|key| !is_empty(key))
                    .find_map(|key| {
                        art.tiles
                            .get(key)
                            .or_else(|| selected_patterns.get(&colour_pattern(key)))
                    })
            };
            bg[at] = if variants.iter().all(is_empty) {
                0
            } else if let Some(ids) = selected_candidate {
                psx_bg += 1;
                ids[0]
            } else if let Some(candidates) = all_candidate {
                psx_bg += 1;
                let (page, index, clut) = candidates[0];
                minter.resolve_art(page, index, clut, 0)?
            } else {
                let wanted = variants
                    .iter()
                    .find(|key| !is_empty(key))
                    .unwrap_or(&variants[0]);
                if config.art == ArtPolicy::ReuseNearest {
                    let (_, candidates) = art
                        .arrangements
                        .iter()
                        .filter(|(pixels, _)| !is_empty(pixels))
                        .min_by(|a, b| {
                            block_pattern_distance(wanted, a.0)
                                .cmp(&block_pattern_distance(wanted, b.0))
                                .then_with(|| a.0.cmp(b.0))
                        })
                        .ok_or_else(|| Error::Format("RNO4 has no PSX arrangements".to_string()))?;
                    let (page, index, clut) = candidates[0];
                    nearest_bg += 1;
                    minter.resolve_art(page, index, clut, 0)?
                } else {
                    let encoded = match config.art {
                        ArtPolicy::FixedPalette => {
                            graphic_minter.encode_fixed_clut(&variants, generated_bg_clut)
                        }
                        ArtPolicy::MirroredPalette => graphic_minter
                            .encode_mirrored_palette(&variants, indexed_variants.as_ref().unwrap()),
                        ArtPolicy::Exact => graphic_minter.encode(&variants),
                        ArtPolicy::ReuseNearest => unreachable!(),
                    }
                    .map_err(|error| {
                        Error::Format(format!(
                            "{source_name} background row {row} column {column}: {error}"
                        ))
                    })?;
                    let (page, index, clut) = encoded;
                    generated_bg += 1;
                    minter.resolve_art(page, index, clut, 0)?
                }
            };
        }
    }
    println!(
        "{source_name} tile selection: preserved {preserved_rows}/{rows} PSX rows; exact PSX fg={psx_fg}, bg={psx_bg}; nearest PSX fg={nearest_fg}, bg={nearest_bg}; generated Saturn-derived fg={generated_fg}, bg={generated_bg} ({} unique graphics)", graphic_minter.graphics.len());
    Ok(Stitch {
        fg,
        bg,
        collision: collision.to_vec(),
        minted: minter.minted,
        graphics: graphic_minter.graphics,
        palettes: graphic_minter.palettes,
        exact: NO4_TILES * rows,
        approximate: 0,
    })
}

fn no4_tile_block(id: u16, stitch: &Stitch, defs: &TileDefs, art: &Np3Art) -> Result<Block> {
    if id == 0 {
        return Ok(vec![None; 256]);
    }
    let minted = stitch.minted.iter().find(|tile| tile.id == id);
    let (page, index, clut) = minted
        .map(|tile| (tile.page, tile.index, tile.clut))
        .unwrap_or_else(|| defs.art(id));
    if let Some(graphic) = stitch
        .graphics
        .iter()
        .find(|graphic| graphic.page == page && graphic.index == index)
    {
        let generated_palette = stitch
            .palettes
            .iter()
            .find(|palette| palette.clut == clut)
            .map(|palette| &palette.colours);
        let palette = generated_palette
            .or_else(|| art.palettes.get(clut as usize))
            .ok_or_else(|| Error::Format(format!("generated NO4 tile uses missing CLUT {clut}")))?;
        let mut pixels = Vec::with_capacity(256);
        for &packed in &graphic.pixels {
            for colour_index in [packed & 0xF, packed >> 4] {
                pixels.push(if colour_index == 0 {
                    None
                } else {
                    Some(palette[colour_index as usize])
                });
            }
        }
        return Ok(pixels);
    }
    if let Some(palette) = stitch
        .palettes
        .iter()
        .find(|palette| palette.clut == clut)
        .map(|palette| &palette.colours)
    {
        if let Some((indices, _)) = art.indexed_arrangements.iter().find(|(_, arrangements)| {
            arrangements
                .iter()
                .any(|&(candidate_page, candidate_index, _)| {
                    candidate_page == page && candidate_index == index
                })
        }) {
            return Ok(indices
                .iter()
                .map(|&index| {
                    if index == 0 {
                        None
                    } else {
                        Some(palette[index as usize])
                    }
                })
                .collect());
        }
    }
    for (pixels, ids) in &art.tiles {
        if ids.iter().any(|&candidate| {
            (minted.is_none() && candidate == id) || defs.art(candidate) == (page, index, clut)
        }) {
            return Ok(pixels.clone());
        }
    }
    for (pixels, arrangements) in &art.arrangements {
        if arrangements.contains(&(page, index, clut)) {
            return Ok(pixels.clone());
        }
    }
    Err(Error::Format(format!(
        "cannot render stitched NO4 tile 0x{id:04X}"
    )))
}

fn composite(fg: &Block, bg: &Block) -> Block {
    fg.iter()
        .zip(bg)
        .map(|(front, back)| front.or(*back))
        .collect()
}

fn rgb15(colour: u16) -> [u8; 4] {
    let expand = |value: u16| ((value * 255 + 15) / 31) as u8;
    [
        expand(colour & 31),
        expand((colour >> 5) & 31),
        expand((colour >> 10) & 31),
        255,
    ]
}

fn write_stitch_visual_test(
    stitch: &Stitch,
    saturn_art: &[(Raster, Raster)],
    defs: &TileDefs,
    art: &Np3Art,
    output: &Path,
    rows: usize,
    file_prefix: &str,
    source_name: &str,
    legal_tile_phases: bool,
) -> Result<()> {
    let height = rows * 16;
    let mut saturn_png = crate::image::Rgba::new(256, height as u32, [0, 0, 0, 0]);
    let mut pc_png = crate::image::Rgba::new(256, height as u32, [0, 0, 0, 0]);
    let mut diff_png = crate::image::Rgba::new(256, height as u32, [0, 0, 0, 255]);
    let mut saturn_pixels = vec![None; 256 * height];
    let mut pc_pixels = vec![None; 256 * height];
    let mut missing_tiles = Vec::new();
    for row in 0..rows {
        for column in 0..16 {
            let at = row * 16 + column;
            let pc_fg = no4_tile_block(stitch.fg[at], stitch, defs, art)?;
            let pc_bg = no4_tile_block(stitch.bg[at], stitch, defs, art)?;
            let pc = composite(&pc_fg, &pc_bg);
            let fg_phases: Vec<&Raster> = saturn_art.iter().map(|phase| &phase.0).collect();
            let bg_phases: Vec<&Raster> = saturn_art.iter().map(|phase| &phase.1).collect();
            let fg_variants = block_variants(&fg_phases, column, row);
            let bg_variants = block_variants(&bg_phases, column, row);
            let fixed_saturn = if legal_tile_phases {
                fg_variants
                    .iter()
                    .zip(&bg_variants)
                    .map(|(fg, bg)| composite(fg, bg))
                    .min_by_key(|candidate| block_distance(candidate, &pc))
                    .unwrap()
            } else {
                composite(
                    &block(&saturn_art[0].0, column, row),
                    &block(&saturn_art[0].1, column, row),
                )
            };
            if fixed_saturn.iter().any(Option::is_some) && pc.iter().all(Option::is_none) {
                missing_tiles.push((column, row, stitch.fg[at], stitch.bg[at]));
            }
            for y in 0..16 {
                for x in 0..16 {
                    let pixel = y * 16 + x;
                    let image_at = (row * 16 + y) * 256 + column * 16 + x;
                    saturn_pixels[image_at] = fixed_saturn[pixel];
                    pc_pixels[image_at] = pc[pixel];
                    if let Some(colour) = fixed_saturn[pixel] {
                        saturn_png.set(
                            (column * 16 + x) as u32,
                            (row * 16 + y) as u32,
                            rgb15(colour),
                        );
                    }
                    if let Some(colour) = pc[pixel] {
                        pc_png.set(
                            (column * 16 + x) as u32,
                            (row * 16 + y) as u32,
                            rgb15(colour),
                        );
                    }
                }
            }
        }
    }

    let mut saturn_colours = Vec::new();
    let mut pc_colours = Vec::new();
    for colour in saturn_pixels.iter().flatten() {
        if !saturn_colours.contains(colour) {
            saturn_colours.push(*colour);
        }
    }
    for colour in pc_pixels.iter().flatten() {
        if !pc_colours.contains(colour) {
            pc_colours.push(*colour);
        }
    }
    let distance = |a: u16, b: u16| -> u32 {
        let channel = |value: u16, shift: u32| ((value >> shift) & 31) as i32;
        let dr = channel(a, 0) - channel(b, 0);
        let dg = channel(a, 5) - channel(b, 5);
        let db = channel(a, 10) - channel(b, 10);
        (dr * dr + dg * dg + db * db) as u32
    };
    let colour_map: HashMap<u16, u16> = saturn_colours
        .iter()
        .map(|&source| {
            let target = pc_colours
                .iter()
                .copied()
                .min_by_key(|&candidate| distance(source, candidate))
                .unwrap_or(source);
            (source, target)
        })
        .collect();
    let mut equal = 0usize;
    for (at, (saturn, pc)) in saturn_pixels.iter().zip(&pc_pixels).enumerate() {
        let matches = match (saturn, pc) {
            (None, None) => true,
            (Some(source), Some(target)) => colour_map[source] == *target,
            _ => false,
        };
        if matches {
            equal += 1;
            let level = pc
                .map(|colour| {
                    let rgba = rgb15(colour);
                    ((u16::from(rgba[0]) + u16::from(rgba[1]) + u16::from(rgba[2])) / 3) as u8
                })
                .unwrap_or(0);
            diff_png.set(
                (at % 256) as u32,
                (at / 256) as u32,
                [level, level, level, 255],
            );
        } else {
            diff_png.set((at % 256) as u32, (at / 256) as u32, [255, 0, 0, 255]);
        }
    }
    let exact_similarity = equal as f64 / (256.0 * height as f64);
    let silhouette_equal = saturn_pixels
        .iter()
        .zip(&pc_pixels)
        .filter(|(saturn, pc)| saturn.is_some() == pc.is_some())
        .count();
    let silhouette_similarity = silhouette_equal as f64 / (256.0 * height as f64);
    let luminance = |colour: Option<u16>| -> f64 {
        colour
            .map(|value| {
                let rgba = rgb15(value);
                0.2126 * f64::from(rgba[0])
                    + 0.7152 * f64::from(rgba[1])
                    + 0.0722 * f64::from(rgba[2])
            })
            .unwrap_or(0.0)
    };
    let c1 = (0.01_f64 * 255.0).powi(2);
    let c2 = (0.03_f64 * 255.0).powi(2);
    let mut structural_similarity = 0.0;
    let mut windows = 0usize;
    for window_y in (0..height).step_by(8) {
        for window_x in (0..256).step_by(8) {
            let mut source = [0.0; 64];
            let mut target = [0.0; 64];
            for y in 0..8 {
                for x in 0..8 {
                    let index = (window_y + y) * 256 + window_x + x;
                    source[y * 8 + x] =
                        luminance(saturn_pixels[index].map(|colour| colour_map[&colour]));
                    target[y * 8 + x] = luminance(pc_pixels[index]);
                }
            }
            let mean_source = source.iter().sum::<f64>() / 64.0;
            let mean_target = target.iter().sum::<f64>() / 64.0;
            let mut variance_source = 0.0;
            let mut variance_target = 0.0;
            let mut covariance = 0.0;
            for (&a, &b) in source.iter().zip(&target) {
                variance_source += (a - mean_source).powi(2);
                variance_target += (b - mean_target).powi(2);
                covariance += (a - mean_source) * (b - mean_target);
            }
            variance_source /= 63.0;
            variance_target /= 63.0;
            covariance /= 63.0;
            structural_similarity += ((2.0 * mean_source * mean_target + c1)
                * (2.0 * covariance + c2))
                / ((mean_source.powi(2) + mean_target.powi(2) + c1)
                    * (variance_source + variance_target + c2));
            windows += 1;
        }
    }
    structural_similarity /= windows as f64;
    if !missing_tiles.is_empty() {
        println!(
            "visual comparison found {} wholly missing tiles; first: {:?}",
            missing_tiles.len(),
            &missing_tiles[..missing_tiles.len().min(12)]
        );
    }
    let parent = output.parent().unwrap_or(Path::new("."));
    crate::image::write_rgba(
        &parent.join(format!("{file_prefix}-saturn.png")),
        &saturn_png,
    )?;
    crate::image::write_rgba(&parent.join(format!("{file_prefix}-pc.png")), &pc_png)?;
    crate::image::write_rgba(&parent.join(format!("{file_prefix}-diff.png")), &diff_png)?;
    if !missing_tiles.is_empty() {
        return Err(Error::Format(format!(
            "visual stitch leaves {} Saturn tiles wholly missing against {source_name}",
            missing_tiles.len(),
        )));
    }
    if silhouette_similarity < 0.95 {
        return Err(Error::Format(format!(
            "visual stitch silhouette similarity is only {:.2}% against {source_name}; expected at least 95%",
            silhouette_similarity * 100.0,
        )));
    }
    if structural_similarity < 0.99 {
        return Err(Error::Format(format!(
            "visual stitch colour SSIM is only {:.2}% against {source_name}; expected at least 99%",
            structural_similarity * 100.0,
        )));
    }
    println!(
        "{source_name}/PC room similarity: {:.2}% palette-independent silhouette, {:.2}% colour SSIM ({:.2}% palette-normalized exact pixels)",
        silhouette_similarity * 100.0, structural_similarity * 100.0,
        exact_similarity * 100.0);
    Ok(())
}

struct StitchAssets {
    fg: Vec<u16>,
    bg: Vec<u16>,
    defs: TileDefs,
    art: Np3Art,
    first_free: u16,
}

fn load_stitch_assets(
    assets: &Path,
    tileset: &Path,
    stage: &str,
    tilemaps: (usize, usize),
    tiledef: usize,
    reserved_tiledefs: &[usize],
) -> Result<StitchAssets> {
    let fg = read_tilemap(&assets.join(format!("{stage}_tilemap_{}.bin", tilemaps.0)))?;
    let bg = read_tilemap(&assets.join(format!("{stage}_tilemap_{}.bin", tilemaps.1)))?;
    let defs = TileDefs::load_named(assets, stage, tiledef)?;
    let reserved = reserved_tiledefs
        .iter()
        .map(|&index| TileDefs::load_named(assets, stage, index))
        .collect::<Result<Vec<_>>>()?;
    let reserved_refs = reserved.iter().collect::<Vec<_>>();
    let art = Np3Art::load_reserving(tileset, &defs, &reserved_refs)?;
    Ok(StitchAssets {
        fg,
        bg,
        defs,
        art,
        first_free: first_free_tile_named(assets, stage)?,
    })
}

#[derive(Clone, Copy)]
struct RoomStitchConfig {
    reserved_tiledefs: &'static [usize],
    saturn: SaturnRoomSource,
    art: ArtPolicy,
    visual_name: &'static str,
    visual_source: &'static str,
    verify_name: &'static str,
    reverse: bool,
    door_layout: usize,
    door_slot: u16,
    psx_entity_layout: usize,
    psx_entity_y_offset: i16,
    description: &'static str,
    graft: AssetGraft,
}

#[derive(Clone, Copy)]
struct ShaftStitchConfig {
    reserved_tiledefs: &'static [usize],
    saturn: SaturnRoomSource,
    art: ArtPolicy,
    visual_name: &'static str,
    visual_source: &'static str,
    verify_name: &'static str,
    reverse: bool,
    door_layout: usize,
    door_slot: u16,
    psx_entity_layout: usize,
    psx_entity_y_offset: i16,
    graft: AssetGraft,
}

#[derive(Clone, Deserialize, Serialize)]
struct PsxEntity {
    x: i16,
    y: i16,
    id: String,
    flags: u8,
    slot: u8,
    #[serde(rename = "spawnId")]
    spawn_id: u8,
    params: u16,
    #[serde(rename = "yOrder")]
    y_order: Option<usize>,
}

#[derive(Deserialize, Serialize)]
struct PsxEntityLayouts {
    entities: Vec<Vec<PsxEntity>>,
    indices: Vec<usize>,
}

#[derive(Clone, Deserialize, Serialize)]
struct PsxRoom {
    left: i16,
    top: i16,
    right: i16,
    bottom: i16,
    #[serde(rename = "layerId")]
    layer_id: i16,
    #[serde(rename = "tileDefId")]
    tiledef_id: i16,
    #[serde(rename = "entityGfxId")]
    entity_gfx_id: i16,
    #[serde(rename = "entityLayoutId")]
    entity_layout_id: i16,
}

#[derive(Clone, Deserialize, Serialize)]
struct PsxLayerDef {
    data: String,
    tiledef: String,
    left: i16,
    top: i16,
    right: i16,
    bottom: i16,
    #[serde(rename = "scrollMode")]
    scroll_mode: u8,
    #[serde(rename = "hideOnMap")]
    hide_on_map: bool,
    #[serde(rename = "isSaveRoom")]
    is_save_room: bool,
    #[serde(rename = "isLoadingRoom")]
    is_loading_room: bool,
    #[serde(rename = "unusedFlag")]
    unused_flag: bool,
    #[serde(rename = "zPriority")]
    z_priority: u16,
    flags: u16,
}

#[derive(Clone, Deserialize, Serialize)]
struct PsxLayers {
    #[serde(skip_serializing_if = "Option::is_none")]
    fg: Option<PsxLayerDef>,
    #[serde(skip_serializing_if = "Option::is_none")]
    bg: Option<PsxLayerDef>,
}

#[derive(Clone, Copy)]
struct AssetGraft {
    stage: &'static str,
    data_dir: &'static str,
    rooms: &'static str,
    layers: &'static str,
    room: usize,
    tilemaps: (usize, usize),
    tiledef: usize,
    psx_width: usize,
    psx_height: usize,
    region: TileRegion,
    shaft_top: Option<i16>,
    shaft_bottom: Option<i16>,
    cd: Option<(i16, i16)>,
    trigger: (i16, i16, i16),
}

fn load_saturn_door(
    prg_path: &Path,
    map_path: &Path,
    layout: usize,
    slot: u16,
) -> Result<EntityRecord> {
    let overlay = std::fs::read(map::overlay_for(prg_path, map_path))?;
    let layouts = read_layout_table(&overlay)?;
    let address = *layouts
        .get(layout)
        .ok_or_else(|| Error::Format(format!("Saturn entity layout {layout} does not exist")))?;
    let doors = read_entity_layout(&overlay, address)?
        .into_iter()
        .filter(|entity| entity.entity_id & 0x3FF == 5 && entity.room_index == slot)
        .collect::<Vec<_>>();
    if doors.len() != 1 {
        return Err(Error::Format(format!(
            "Saturn entity layout {layout} contains {} red doors in slot 0x{slot:02X}, expected one",
            doors.len(),
        )));
    }
    let mut door = doors[0];
    door.x = ((u32::from(door.x) * 4) / 5) as u16;
    door.params &= 0x100;
    Ok(door)
}

fn write_stitched_entity_layout(
    assets: &Path,
    layout: usize,
    y_offset: i16,
    door: &EntityRecord,
) -> Result<()> {
    let direct = assets.join("entity_layouts.json");
    let path = if direct.exists() {
        direct
    } else if assets.join("us/entity_layouts.json").exists() {
        assets.join("us/entity_layouts.json")
    } else {
        assets
            .parent()
            .unwrap_or(assets)
            .join("entity_layouts.json")
    };
    let mut layouts: PsxEntityLayouts = serde_json::from_slice(&std::fs::read(&path)?)?;
    let bank = *layouts
        .indices
        .get(layout)
        .ok_or_else(|| Error::Format(format!("PSX entity layout index {layout} does not exist")))?;
    let mut entities = layouts.entities.get(bank).cloned().ok_or_else(|| {
        Error::Format(format!(
            "PSX entity layout index {layout} refers to missing bank {bank}"
        ))
    })?;
    if entities.len() < 2 || entities[0].x != -2 || entities.last().unwrap().x != -1 {
        return Err(Error::Format(
            "PSX entity layout is missing its sentinels".to_string(),
        ));
    }
    let end = entities.len() - 1;
    for entity in &mut entities[1..end] {
        entity.y = entity.y.checked_add(y_offset).ok_or_else(|| {
            Error::Format("shifted PSX entity position is outside i16".to_string())
        })?;
    }
    let requested_slot = door.room_index as u8;
    let spawn_id = (door.room_index >> 8) as u8;
    if !entities.iter().any(|entity| {
        entity.x == door.x as i16
            && entity.y == door.y as i16
            && entity.id == "E_RED_DOOR"
            && entity.slot == requested_slot
            && entity.spawn_id == spawn_id
            && entity.params == door.params
    }) {
        let mut slot = requested_slot;
        while entities[1..end].iter().any(|entity| entity.slot == slot) {
            slot = slot.checked_add(1).ok_or_else(|| {
                Error::Format("PSX entity layout has no free slot for Saturn door".to_string())
            })?;
        }
        entities.insert(
            entities.len() - 1,
            PsxEntity {
                x: door.x as i16,
                y: door.y as i16,
                id: "E_RED_DOOR".to_string(),
                flags: 0,
                slot,
                spawn_id,
                params: door.params,
                y_order: None,
            },
        );
    }
    layouts.entities.push(entities);
    layouts.indices[layout] = layouts.entities.len() - 1;
    std::fs::write(path, serde_json::to_string_pretty(&layouts)? + "\n")?;
    Ok(())
}

fn copy_asset_tree(source: &Path, output: &Path) -> Result<()> {
    std::fs::create_dir_all(output)?;
    fn copy_dir(source: &Path, output: &Path) -> Result<()> {
        for entry in std::fs::read_dir(source)? {
            let entry = entry?;
            let target = output.join(entry.file_name());
            if entry.file_type()?.is_dir() {
                std::fs::create_dir_all(&target)?;
                copy_dir(&entry.path(), &target)?;
            } else {
                std::fs::copy(entry.path(), target)?;
            }
        }
        Ok(())
    }
    copy_dir(source, output)
}

fn remove_path(path: &Path) -> Result<()> {
    let metadata = match std::fs::symlink_metadata(path) {
        Ok(metadata) => metadata,
        Err(error) if error.kind() == std::io::ErrorKind::NotFound => return Ok(()),
        Err(error) => return Err(error.into()),
    };
    if metadata.file_type().is_dir() {
        std::fs::remove_dir_all(path)?;
    } else {
        std::fs::remove_file(path)?;
    }
    Ok(())
}

fn publish_asset_tree<F>(source: &Path, output: &Path, generate: F) -> Result<()>
where
    F: FnOnce(&Path) -> Result<()>,
{
    let staging = output.with_extension("staging");
    let previous = output.with_extension("previous");
    remove_path(&staging)?;

    let generated = (|| {
        copy_asset_tree(source, &staging)?;
        generate(&staging)
    })();
    if let Err(error) = generated {
        remove_path(&staging).ok();
        return Err(error);
    }

    remove_path(&previous)?;
    let had_previous = std::fs::symlink_metadata(output).is_ok();
    if had_previous {
        std::fs::rename(output, &previous)?;
    }
    if let Err(error) = std::fs::rename(&staging, output) {
        if had_previous {
            std::fs::rename(&previous, output).map_err(|rollback| {
                Error::Format(format!(
                    "could not publish {} ({error}) or restore its previous contents ({rollback})",
                    output.display()
                ))
            })?;
        }
        return Err(error.into());
    }
    remove_path(&previous)?;
    Ok(())
}

fn write_tilemap(path: &Path, tiles: &[u16]) -> Result<()> {
    let bytes = tiles
        .iter()
        .flat_map(|tile| tile.to_le_bytes())
        .collect::<Vec<_>>();
    std::fs::write(path, bytes)?;
    Ok(())
}

fn patch_tilemap(source: &[u16], stitch: &[u16], width: usize, region: TileRegion) -> Vec<u16> {
    let mut output = source.to_vec();
    for row in 0..region.height {
        let destination = (region.top + row) * width + region.left;
        let source = row * region.width;
        output[destination..destination + region.width]
            .copy_from_slice(&stitch[source..source + region.width]);
    }
    output
}

fn write_stitched_tiledef(
    assets: &Path,
    stage: &str,
    tiledef: usize,
    source: &TileDefs,
    minted: &[MintedTile],
) -> Result<()> {
    let mut page = source.page.clone();
    let mut index = source.index.clone();
    let mut clut = source.clut.clone();
    let mut collision = source.collision.clone();
    for tile in minted {
        let id = tile.id as usize;
        if id >= page.len() {
            return Err(Error::Format(format!(
                "minted tile 0x{:04X} is outside {stage} tiledef {tiledef}",
                tile.id
            )));
        }
        page[id] = tile.page;
        index[id] = tile.index;
        clut[id] = tile.clut;
        collision[id] = tile.collision;
    }
    std::fs::write(
        assets.join(format!("{stage}_tiledef_{tiledef}_tiles.bin")),
        page,
    )?;
    std::fs::write(
        assets.join(format!("{stage}_tiledef_{tiledef}_pages.bin")),
        index,
    )?;
    std::fs::write(
        assets.join(format!("{stage}_tiledef_{tiledef}_cluts.bin")),
        clut,
    )?;
    std::fs::write(
        assets.join(format!("{stage}_tiledef_{tiledef}_cols.bin")),
        collision,
    )?;
    Ok(())
}

fn write_stitched_tileset(
    source: &Path,
    output_header: &Path,
    stage: &str,
    stitch: &Stitch,
) -> Result<()> {
    let mut data = std::fs::read(source)?;
    if data.len() != 0x40000 {
        return Err(Error::Format(format!(
            "{} is not a 0x40000-byte stage tileset",
            source.display()
        )));
    }
    for graphic in &stitch.graphics {
        let tile_x = (graphic.index & 0x0F) as usize;
        let tile_y = (graphic.index >> 4) as usize;
        let chunk = graphic.page as usize * 4 + (tile_y / 8) * 2 + tile_x / 8;
        for row in 0..16 {
            let destination = chunk * 0x2000 + ((tile_y % 8) * 16 + row) * 0x40 + (tile_x % 8) * 8;
            let source = row * 8;
            data[destination..destination + 8].copy_from_slice(&graphic.pixels[source..source + 8]);
        }
    }
    for palette in &stitch.palettes {
        let x = (palette.clut & 0x0F) as usize * 16;
        let y = 0x70 + (palette.clut >> 4) as usize;
        let page = x / 64;
        let half = (x % 64) / 32;
        let chunk = page * 4 + 2 + half;
        let destination = chunk * 0x2000 + y * 0x40 + (x % 32) * 2;
        for (index, colour) in palette.colours.iter().enumerate() {
            data[destination + index * 2..destination + index * 2 + 2]
                .copy_from_slice(&colour.to_le_bytes());
        }
    }
    let upper = stage.to_ascii_uppercase();
    let output = output_header
        .parent()
        .unwrap_or(Path::new("."))
        .join("disks/us/ST")
        .join(&upper)
        .join(format!("F_{upper}.BIN"));
    std::fs::create_dir_all(output.parent().unwrap())?;
    std::fs::write(output, data)?;
    Ok(())
}

fn json_path(root: &Path, stem: &str) -> PathBuf {
    root.join(format!("{stem}.json"))
}

fn write_stitched_rooms_and_layers(assets: &Path, config: AssetGraft) -> Result<()> {
    let rooms_path = json_path(assets, config.rooms);
    let layers_path = json_path(assets, config.layers);
    let mut rooms: Vec<PsxRoom> = serde_json::from_slice(&std::fs::read(&rooms_path)?)?;
    let mut layers: Vec<PsxLayers> = serde_json::from_slice(&std::fs::read(&layers_path)?)?;
    let room = rooms.get_mut(config.room).ok_or_else(|| {
        Error::Format(format!(
            "{} room {} does not exist",
            config.stage, config.room
        ))
    })?;
    let room_layer = room.layer_id as usize;
    if let Some(top) = config.shaft_top {
        room.top = top;
        let pair = &mut layers[room_layer];
        if let Some(layer) = &mut pair.fg {
            layer.top = top;
        }
        if let Some(layer) = &mut pair.bg {
            layer.top = top;
        }
    }
    if let Some(bottom) = config.shaft_bottom {
        room.bottom = bottom;
        let pair = &mut layers[room_layer];
        if let Some(layer) = &mut pair.fg {
            layer.bottom = bottom;
        }
        if let Some(layer) = &mut pair.bg {
            layer.bottom = bottom;
        }
    }
    if let Some((left, top)) = config.cd {
        let loading_layer = layers
            .iter()
            .position(|layer| layer.fg.as_ref().is_some_and(|fg| fg.is_loading_room))
            .ok_or_else(|| Error::Format(format!("{} has no PSX loading layer", config.stage)))?;
        let loading_room = rooms
            .iter()
            .position(|room| room.layer_id == loading_layer as i16)
            .ok_or_else(|| Error::Format(format!("{} loading layer has no room", config.stage)))?;
        let mut cd_layer = layers[loading_layer].clone();
        for layer in [&mut cd_layer.fg, &mut cd_layer.bg].into_iter().flatten() {
            layer.left = left;
            layer.right = left;
            layer.top = top;
            layer.bottom = top;
        }
        let layer_id = layers.len() as i16;
        layers.push(cd_layer);
        let mut cd_room = rooms[loading_room].clone();
        cd_room.left = left;
        cd_room.right = left;
        cd_room.top = top;
        cd_room.bottom = top;
        cd_room.layer_id = layer_id;
        rooms.push(cd_room);
    }
    rooms.push(PsxRoom {
        left: config.trigger.0,
        top: config.trigger.1,
        right: config.trigger.0,
        bottom: config.trigger.1,
        layer_id: config.trigger.2 as i8 as i16,
        tiledef_id: -1,
        entity_gfx_id: 0,
        entity_layout_id: 0,
    });
    std::fs::write(rooms_path, serde_json::to_string_pretty(&rooms)? + "\n")?;
    std::fs::write(layers_path, serde_json::to_string_pretty(&layers)? + "\n")?;
    Ok(())
}

fn emit_stitched_asset_tree(
    source_assets: &Path,
    source_tileset: &Path,
    output_header: &Path,
    loaded: &StitchAssets,
    stitch: &Stitch,
    config: AssetGraft,
    door: &EntityRecord,
    entity_layout: usize,
    entity_y_offset: i16,
) -> Result<PathBuf> {
    let output = output_header
        .parent()
        .unwrap_or(Path::new("."))
        .join("assets")
        .join(config.stage);
    let expected_room_tiles = config.psx_width * config.psx_height;
    let replace_whole_room = loaded.fg.len() != expected_room_tiles
        || config.region.left + config.region.width > config.psx_width
        || config.region.top + config.region.height > config.psx_height
        || (config.region.width == config.psx_width && config.region.height == config.psx_height);
    let fg = if replace_whole_room {
        stitch.fg.clone()
    } else {
        patch_tilemap(&loaded.fg, &stitch.fg, config.psx_width, config.region)
    };
    let bg = if replace_whole_room {
        stitch.bg.clone()
    } else {
        patch_tilemap(&loaded.bg, &stitch.bg, config.psx_width, config.region)
    };
    write_stitched_tileset(source_tileset, output_header, config.stage, stitch)?;
    publish_asset_tree(source_assets, &output, |staging| {
        let stage_assets = staging.join(config.data_dir);
        write_tilemap(
            &stage_assets.join(format!(
                "{}_tilemap_{}.bin",
                config.stage, config.tilemaps.0
            )),
            &fg,
        )?;
        write_tilemap(
            &stage_assets.join(format!(
                "{}_tilemap_{}.bin",
                config.stage, config.tilemaps.1
            )),
            &bg,
        )?;
        write_stitched_tiledef(
            &stage_assets,
            config.stage,
            config.tiledef,
            &loaded.defs,
            &stitch.minted,
        )?;
        write_stitched_entity_layout(staging, entity_layout, entity_y_offset, door)?;
        write_stitched_rooms_and_layers(staging, config)
    })?;
    Ok(output)
}

fn stitch_room(
    prg_path: &Path,
    map_path: &Path,
    assets: &Path,
    tileset: &Path,
    output: &Path,
    config: RoomStitchConfig,
) -> Result<()> {
    let graft = config.graft;
    let loaded = load_stitch_assets(
        assets,
        tileset,
        graft.stage,
        graft.tilemaps,
        graft.tiledef,
        config.reserved_tiledefs,
    )?;
    let crop_layer = |layout: &[u16], layer: &str| -> Result<Vec<u16>> {
        region(
            layout,
            graft.psx_width,
            graft.psx_height,
            graft.region,
            &format!("{} {layer}", config.verify_name),
        )
    };
    let psx_fg = crop_layer(&loaded.fg, "foreground")?;
    let psx_bg = crop_layer(&loaded.bg, "background")?;
    let scratch = output
        .parent()
        .unwrap_or(Path::new("."))
        .join(format!("{}-stitch-source", graft.stage));
    let (collision, saturn_art) =
        load_saturn_room_source(prg_path, map_path, &scratch, config.saturn)?;
    let rows = graft.region.height;
    let stitch = build_room(
        &saturn_art,
        &psx_fg,
        &psx_bg,
        &loaded.defs,
        &loaded.art,
        &collision,
        loaded.first_free,
        BuildConfig {
            rows,
            art: config.art,
            source_name: config.saturn.name,
        },
    )?;
    verify_collision(
        &stitch,
        &loaded.defs,
        &collision,
        graft.region.width,
        config.verify_name,
    )?;
    write_stitch_visual_test(
        &stitch,
        &saturn_art,
        &loaded.defs,
        &loaded.art,
        output,
        rows,
        config.visual_name,
        config.visual_source,
        config.reverse,
    )?;
    let door = load_saturn_door(prg_path, map_path, config.door_layout, config.door_slot)?;
    emit_stitched_asset_tree(
        assets,
        tileset,
        output,
        &loaded,
        &stitch,
        graft,
        &door,
        config.psx_entity_layout,
        config.psx_entity_y_offset,
    )?;
    std::fs::write(output, [])?;
    println!(
        "stitched {}: {} graphics, {} palettes, {} tile definitions -> {}",
        config.description,
        stitch.graphics.len(),
        stitch.palettes.len(),
        stitch.minted.len(),
        output.display(),
    );
    Ok(())
}

const NO4_CONFIG: RoomStitchConfig = RoomStitchConfig {
    reserved_tiledefs: &[0, 1],
    saturn: NO4_SOURCE,
    art: ArtPolicy::Exact,
    visual_name: "no4-stitch",
    visual_source: "Saturn STAGE_9B room 4",
    verify_name: "NO4",
    reverse: false,
    door_layout: 58,
    door_slot: 0x90,
    psx_entity_layout: 6,
    psx_entity_y_offset: 0,
    description: "Saturn STAGE_9B room 4 into NO4 room 5",
    graft: AssetGraft {
        stage: "no4",
        data_dir: "",
        rooms: "rooms",
        layers: "layers",
        room: 5,
        tilemaps: (9, 10),
        tiledef: 2,
        psx_width: 16,
        psx_height: 32,
        region: NO4_SOURCE.region,
        shaft_top: None,
        shaft_bottom: None,
        cd: None,
        trigger: (36, 34, 134),
    },
};

pub fn stitch_no4(
    prg_path: &Path,
    map_path: &Path,
    no4_assets: &Path,
    no4_tileset: &Path,
    output: &Path,
) -> Result<()> {
    stitch_room(
        prg_path,
        map_path,
        no4_assets,
        no4_tileset,
        output,
        NO4_CONFIG,
    )
}

const RNO4_SATURN_ROOM: usize = 4;
const RNO4_ROWS: usize = 32;

const RNO4_SOURCE: SaturnRoomSource = SaturnRoomSource {
    room: RNO4_SATURN_ROOM,
    bounds: (39, 21, 40, 26),
    room_width: NO4_TILES,
    room_height: RNO4_ROWS,
    region: TileRegion {
        left: 0,
        top: 0,
        width: NO4_TILES,
        height: RNO4_ROWS,
    },
    name: "RSTAGE9B room 4",
};

const RNO4_CONFIG: RoomStitchConfig = RoomStitchConfig {
    reserved_tiledefs: &[0, 1],
    saturn: RNO4_SOURCE,
    art: ArtPolicy::MirroredPalette,
    visual_name: "rno4-stitch",
    visual_source: "Saturn RSTAGE9B room 4",
    verify_name: "RNO4",
    reverse: true,
    door_layout: 58,
    door_slot: 0x90,
    psx_entity_layout: 6,
    psx_entity_y_offset: 0,
    description: "Saturn RSTAGE9B room 4 into RNO4 room 5",
    graft: AssetGraft {
        stage: "rno4",
        data_dir: "",
        rooms: "rooms",
        layers: "layers",
        room: 5,
        tilemaps: (9, 10),
        tiledef: 2,
        psx_width: 16,
        psx_height: 32,
        region: RNO4_SOURCE.region,
        shaft_top: None,
        shaft_bottom: None,
        cd: None,
        trigger: (27, 29, 136),
    },
};

pub fn stitch_rno4(
    prg_path: &Path,
    map_path: &Path,
    rno4_assets: &Path,
    rno4_tileset: &Path,
    output: &Path,
) -> Result<()> {
    stitch_room(
        prg_path,
        map_path,
        rno4_assets,
        rno4_tileset,
        output,
        RNO4_CONFIG,
    )
}

const RNO0_SATURN_ROOM: usize = 6;
const RNO0_ROOM_TILES_WIDE: usize = 96;
const RNO0_ROOM_TILES_HIGH: usize = 48;
const RNO0_CORNER_TILES: usize = 16;

const NO0_SATURN_ROOM: usize = 6;
const NO0_REGION_LEFT: usize = 80;
const NO0_REGION_TOP: usize = 32;

const NO0_SOURCE: SaturnRoomSource = SaturnRoomSource {
    room: NO0_SATURN_ROOM,
    bounds: (21, 34, 26, 36),
    room_width: RNO0_ROOM_TILES_WIDE,
    room_height: RNO0_ROOM_TILES_HIGH,
    region: TileRegion {
        left: NO0_REGION_LEFT,
        top: NO0_REGION_TOP,
        width: RNO0_CORNER_TILES,
        height: RNO0_CORNER_TILES,
    },
    name: "STAGE03 room 6",
};

const RNO0_SOURCE: SaturnRoomSource = SaturnRoomSource {
    room: RNO0_SATURN_ROOM,
    bounds: (37, 27, 42, 29),
    room_width: RNO0_ROOM_TILES_WIDE,
    room_height: RNO0_ROOM_TILES_HIGH,
    region: TileRegion {
        left: 0,
        top: 0,
        width: RNO0_CORNER_TILES,
        height: RNO0_CORNER_TILES,
    },
    name: "RSTAGE03 room 6",
};

const NO0_CONFIG: RoomStitchConfig = RoomStitchConfig {
    reserved_tiledefs: &[1, 2],
    saturn: NO0_SOURCE,
    art: ArtPolicy::FixedPalette,
    visual_name: "no0-stitch",
    visual_source: "Saturn STAGE03 room 6 bottom-right cell",
    verify_name: "NO0",
    reverse: true,
    door_layout: 7,
    door_slot: 0x93,
    psx_entity_layout: 1,
    psx_entity_y_offset: 0,
    description: "Saturn STAGE03 room 6 bottom-right into NO0 room 0",
    graft: AssetGraft {
        stage: "no0",
        data_dir: "",
        rooms: "rooms",
        layers: "layers",
        room: 0,
        tilemaps: (0, 1),
        tiledef: 0,
        psx_width: 96,
        psx_height: 48,
        region: NO0_SOURCE.region,
        shaft_top: None,
        shaft_bottom: None,
        cd: None,
        trigger: (27, 36, 133),
    },
};

pub fn stitch_no0(
    prg_path: &Path,
    map_path: &Path,
    no0_assets: &Path,
    no0_tileset: &Path,
    output: &Path,
) -> Result<()> {
    stitch_room(
        prg_path,
        map_path,
        no0_assets,
        no0_tileset,
        output,
        NO0_CONFIG,
    )
}

const RNO0_CONFIG: RoomStitchConfig = RoomStitchConfig {
    reserved_tiledefs: &[0, 2],
    saturn: RNO0_SOURCE,
    art: ArtPolicy::ReuseNearest,
    visual_name: "rno0-stitch",
    visual_source: "Saturn RSTAGE03 room 6 top-left cell",
    verify_name: "RNO0",
    reverse: true,
    door_layout: 7,
    door_slot: 0x90,
    psx_entity_layout: 1,
    psx_entity_y_offset: 0,
    description: "Saturn RSTAGE03 room 6 top-left into RNO0 room 0",
    graft: AssetGraft {
        stage: "rno0",
        data_dir: "",
        rooms: "rooms",
        layers: "layers",
        room: 0,
        tilemaps: (0, 1),
        tiledef: 1,
        psx_width: 96,
        psx_height: 48,
        region: RNO0_SOURCE.region,
        shaft_top: None,
        shaft_bottom: None,
        cd: None,
        trigger: (36, 27, 135),
    },
};

pub fn stitch_rno0(
    prg_path: &Path,
    map_path: &Path,
    rno0_assets: &Path,
    rno0_tileset: &Path,
    output: &Path,
) -> Result<()> {
    stitch_room(
        prg_path,
        map_path,
        rno0_assets,
        rno0_tileset,
        output,
        RNO0_CONFIG,
    )
}

fn psx_tile_block(art: &Np3Art, id: u16) -> Result<Block> {
    if id == 0 {
        return Ok(vec![None; 256]);
    }
    Ok(art
        .tiles
        .iter()
        .find_map(|(pixels, ids)| ids.contains(&id).then(|| pixels.clone()))
        .unwrap_or_else(|| vec![Some(0x7C1F); 256]))
}

fn render_psx_tilemap(
    tilemap: &[u16],
    width: usize,
    height: usize,
    art: &Np3Art,
) -> Result<crate::image::Rgba> {
    if tilemap.len() != width * height {
        return Err(Error::Format(format!(
            "PSX tilemap has {} entries, expected {width}x{height}",
            tilemap.len()
        )));
    }
    let mut image =
        crate::image::Rgba::new((width * 16) as u32, (height * 16) as u32, [0, 0, 0, 0]);
    for (at, &id) in tilemap.iter().enumerate() {
        let pixels = psx_tile_block(art, id)?;
        let tx = at % width;
        let ty = at / width;
        for y in 0..16 {
            for x in 0..16 {
                if let Some(colour) = pixels[y * 16 + x] {
                    image.set((tx * 16 + x) as u32, (ty * 16 + y) as u32, rgb15(colour));
                }
            }
        }
    }
    Ok(image)
}

fn composite_rgba(bg: &crate::image::Rgba, fg: &crate::image::Rgba) -> crate::image::Rgba {
    let width = fg.width.max(bg.width);
    let height = fg.height.max(bg.height);
    let mut out = crate::image::Rgba::new(width, height, [0, 0, 0, 0]);
    for y in 0..height as usize {
        for x in 0..width as usize {
            let target = (y * width as usize + x) * 4;
            let front_at = (x < fg.width as usize && y < fg.height as usize)
                .then(|| (y * fg.width as usize + x) * 4);
            let back_at = (x < bg.width as usize && y < bg.height as usize)
                .then(|| (y * bg.width as usize + x) * 4);
            let source = front_at
                .filter(|&at| fg.pixels[at + 3] != 0)
                .map(|at| {
                    [
                        fg.pixels[at],
                        fg.pixels[at + 1],
                        fg.pixels[at + 2],
                        fg.pixels[at + 3],
                    ]
                })
                .or_else(|| {
                    back_at.map(|at| {
                        [
                            bg.pixels[at],
                            bg.pixels[at + 1],
                            bg.pixels[at + 2],
                            bg.pixels[at + 3],
                        ]
                    })
                });
            if let Some(source) = source {
                out.pixels[target..target + 4].copy_from_slice(&source);
            }
        }
    }
    out
}

fn raster_rgba(raster: &Raster) -> crate::image::Rgba {
    let mut image =
        crate::image::Rgba::new(raster.width as u32, raster.height as u32, [0, 0, 0, 0]);
    for (at, &colour) in raster.pixels.iter().enumerate() {
        if let Some(colour) = colour {
            image.set(
                (at % raster.width) as u32,
                (at / raster.width) as u32,
                rgb15(colour),
            );
        }
    }
    image
}

pub fn dump_saturn_rooms(prg: &Path, map_path: &Path, output: &Path) -> Result<()> {
    let source = output.join("saturn-source");
    let manifest = map::extract(prg, map_path, &source)?;
    let overlay = std::fs::read(map::overlay_for(prg, map_path))?;
    let map_data = std::fs::read(map_path)?;
    let rooms = read_rooms(&overlay)?;
    std::fs::create_dir_all(output)?;
    let mut index = Vec::new();
    let mut rendered = 0usize;
    for (room_id, room) in rooms.iter().enumerate() {
        if !matches!(room.kind, RoomKind::Ordinary { .. }) {
            continue;
        }
        let fg = render_layer_raster_phase(&manifest, &map_data, room_id, 0, 4);
        let bg = render_layer_raster_phase(&manifest, &map_data, room_id, 2, 4);
        let (Ok(fg), Ok(bg)) = (fg, bg) else {
            continue;
        };
        let fg = raster_rgba(&fg);
        let bg = raster_rgba(&bg);
        let composite = composite_rgba(&bg, &fg);
        crate::image::write_rgba(&output.join(format!("room-{room_id}-fg.png")), &fg)?;
        crate::image::write_rgba(&output.join(format!("room-{room_id}-bg.png")), &bg)?;
        crate::image::write_rgba(
            &output.join(format!("room-{room_id}-composite.png")),
            &composite,
        )?;
        index.push(serde_json::json!({
            "room": room_id,
            "left": room.bounds.left,
            "top": room.bounds.top,
            "right": room.bounds.right,
            "bottom": room.bounds.bottom,
        }));
        rendered += 1;
    }
    std::fs::write(
        output.join("rooms.json"),
        serde_json::to_string_pretty(&index)? + "\n",
    )?;
    println!("dumped {rendered} Saturn rooms -> {}", output.display());
    Ok(())
}

fn dump_psx_rooms_named(assets: &Path, tileset: &Path, output: &Path, name: &str) -> Result<()> {
    let rooms: serde_json::Value =
        serde_json::from_slice(&std::fs::read(assets.join("rooms.json"))?)?;
    let layers: serde_json::Value =
        serde_json::from_slice(&std::fs::read(assets.join("layers.json"))?)?;
    let rooms = rooms
        .as_array()
        .ok_or_else(|| Error::Format(format!("{name} rooms.json is not an array")))?;
    let layers = layers
        .as_array()
        .ok_or_else(|| Error::Format(format!("{name} layers.json is not an array")))?;
    std::fs::create_dir_all(output)?;
    let mut art_by_def: HashMap<usize, Np3Art> = HashMap::new();
    let mut index = Vec::new();
    for (room_id, room) in rooms.iter().enumerate() {
        let layer_id = room["layerId"]
            .as_u64()
            .ok_or_else(|| Error::Format(format!("{name} room {room_id} has no layerId")))?
            as usize;
        let left = room["left"].as_u64().unwrap() as usize;
        let top = room["top"].as_u64().unwrap() as usize;
        let right = room["right"].as_u64().unwrap() as usize;
        let bottom = room["bottom"].as_u64().unwrap() as usize;
        let Some(layer) = layers.get(layer_id) else {
            continue;
        };
        let layer_left = layer["fg"]["left"].as_u64().unwrap() as usize;
        let layer_top = layer["fg"]["top"].as_u64().unwrap() as usize;
        let layer_right = layer["fg"]["right"].as_u64().unwrap() as usize;
        let layer_bottom = layer["fg"]["bottom"].as_u64().unwrap() as usize;
        let expected_width = (layer_right - layer_left + 1) * 16;
        let expected_height = (layer_bottom - layer_top + 1) * 16;
        let mut rendered = Vec::new();
        for role in ["fg", "bg"] {
            if layer[role].is_null() {
                rendered.push(crate::image::Rgba::new(
                    (expected_width * 16) as u32,
                    (expected_height * 16) as u32,
                    [0, 0, 0, 0],
                ));
                continue;
            }
            let definition = layer[role]["tiledef"].as_str().ok_or_else(|| {
                Error::Format(format!("{name} layer {layer_id} {role} has no tiledef"))
            })?;
            let tiledef = definition
                .strip_prefix(&format!("{name}_tiledef_"))
                .and_then(|value| value.strip_suffix(".json"))
                .and_then(|value| value.parse::<usize>().ok())
                .ok_or_else(|| Error::Format(format!("unknown {name} tiledef {definition}")))?;
            if !art_by_def.contains_key(&tiledef) {
                let defs = TileDefs::load_named(assets, name, tiledef)?;
                art_by_def.insert(tiledef, Np3Art::load(tileset, &defs)?);
            }
            let data = layer[role]["data"].as_str().ok_or_else(|| {
                Error::Format(format!("{name} layer {layer_id} {role} has no data"))
            })?;
            let tilemap = read_tilemap(&assets.join(data))?;
            let (width, height) = if tilemap.len() == expected_width * expected_height {
                (expected_width, expected_height)
            } else if tilemap.len() % expected_width == 0 {
                (expected_width, tilemap.len() / expected_width)
            } else {
                (16, tilemap.len() / 16)
            };
            let image = render_psx_tilemap(&tilemap, width, height, &art_by_def[&tiledef])?;
            crate::image::write_rgba(&output.join(format!("room-{room_id}-{role}.png")), &image)?;
            rendered.push(image);
        }
        let composite = composite_rgba(&rendered[1], &rendered[0]);
        crate::image::write_rgba(
            &output.join(format!("room-{room_id}-composite.png")),
            &composite,
        )?;
        index.push(serde_json::json!({
            "room": room_id, "left": left, "top": top,
            "right": right, "bottom": bottom, "layer": layer_id
        }));
    }
    std::fs::write(
        output.join("rooms.json"),
        serde_json::to_string_pretty(&index)? + "\n",
    )?;
    println!(
        "dumped {} PSX {} rooms -> {}",
        rooms.len(),
        name.to_uppercase(),
        output.display()
    );
    Ok(())
}

pub fn dump_psx_no4_rooms(assets: &Path, tileset: &Path, output: &Path) -> Result<()> {
    dump_psx_rooms_named(assets, tileset, output, "no4")
}

pub fn dump_psx_rno4_rooms(assets: &Path, tileset: &Path, output: &Path) -> Result<()> {
    dump_psx_rooms_named(assets, tileset, output, "rno4")
}

pub fn dump_psx_rno0_rooms(assets: &Path, tileset: &Path, output: &Path) -> Result<()> {
    dump_psx_rooms_named(assets, tileset, output, "rno0")
}

pub fn dump_psx_rno3_rooms(assets: &Path, tileset: &Path, output: &Path) -> Result<()> {
    dump_psx_rooms_named(assets, tileset, output, "rno3")
}

const NP3_CONFIG: ShaftStitchConfig = ShaftStitchConfig {
    reserved_tiledefs: &[],
    saturn: SATURN_SHAFT_SOURCE,
    art: ArtPolicy::Exact,
    visual_name: "np3-stitch",
    visual_source: "Saturn STAGE_01 room 17",
    verify_name: "NP3 shaft",
    reverse: true,
    door_layout: 18,
    door_slot: 0x90,
    psx_entity_layout: 2,
    psx_entity_y_offset: 0,
    graft: AssetGraft {
        stage: "np3",
        data_dir: "",
        rooms: "rooms",
        layers: "layers",
        room: 1,
        tilemaps: (2, 3),
        tiledef: 2,
        psx_width: 16,
        psx_height: 32,
        region: TileRegion {
            left: 0,
            top: 0,
            width: 16,
            height: 64,
        },
        shaft_top: None,
        shaft_bottom: Some(44),
        cd: Some((3, 44)),
        trigger: (4, 44, 131),
    },
};

const RNO3_CONFIG: ShaftStitchConfig = ShaftStitchConfig {
    reserved_tiledefs: &[0, 1],
    saturn: SATURN_REVERSE_SHAFT_SOURCE,
    art: ArtPolicy::MirroredPalette,
    visual_name: "rno3-stitch",
    visual_source: "Saturn RSTAGE01 room 17",
    verify_name: "RNO3 shaft",
    reverse: true,
    door_layout: 18,
    door_slot: 0x90,
    psx_entity_layout: 2,
    psx_entity_y_offset: (REVERSE_PSX_START * 16) as i16,
    graft: AssetGraft {
        stage: "rno3",
        data_dir: "us",
        rooms: "us/rooms",
        layers: "us/layers",
        room: 1,
        tilemaps: (2, 3),
        tiledef: 2,
        psx_width: 16,
        psx_height: 32,
        region: TileRegion {
            left: 0,
            top: 0,
            width: 16,
            height: 64,
        },
        shaft_top: Some(19),
        shaft_bottom: None,
        cd: Some((60, 19)),
        trigger: (59, 19, 132),
    },
};

pub fn stitch_np3(
    prg_path: &Path,
    map_path: &Path,
    np3_assets: &Path,
    np3_tileset: &Path,
    output: &Path,
) -> Result<()> {
    let config = NP3_CONFIG;
    let loaded = load_stitch_assets(
        np3_assets,
        np3_tileset,
        config.graft.stage,
        config.graft.tilemaps,
        config.graft.tiledef,
        config.reserved_tiledefs,
    )?;

    let scratch = output
        .parent()
        .unwrap_or(Path::new("."))
        .join(format!("{}-stitch-source", config.graft.stage));
    let (saturn_collision, saturn_art) =
        load_saturn_room_source(prg_path, map_path, &scratch, config.saturn)?;

    let stitch = build(
        &saturn_art,
        &loaded.fg,
        &loaded.bg,
        &loaded.defs,
        &loaded.art,
        &saturn_collision,
        loaded.first_free,
    )?;
    verify(&stitch, &loaded.fg, &loaded.defs, &saturn_collision)?;
    write_stitch_visual_test(
        &stitch,
        &saturn_art,
        &loaded.defs,
        &loaded.art,
        output,
        SATURN_ROWS,
        config.visual_name,
        config.visual_source,
        config.reverse,
    )?;
    let door = load_saturn_door(prg_path, map_path, config.door_layout, config.door_slot)?;
    emit_stitched_asset_tree(
        np3_assets,
        np3_tileset,
        output,
        &loaded,
        &stitch,
        config.graft,
        &door,
        config.psx_entity_layout,
        config.psx_entity_y_offset,
    )?;
    std::fs::write(output, [])?;
    let below = stitch.exact + stitch.approximate;
    println!(
        "stitched NP3 shaft at row {STITCH_ROW}: {} of {below} tiles matched exactly, \
         {} approximated, {} arrangements generated, {} tile ids minted \
        (from 0x{:04X}) -> {}",
        stitch.exact,
        stitch.approximate,
        stitch.graphics.len(),
        stitch.minted.len(),
        loaded.first_free,
        output.display()
    );
    Ok(())
}

pub fn stitch_rno3(
    prg_path: &Path,
    map_path: &Path,
    rno3_assets: &Path,
    rno3_tileset: &Path,
    output: &Path,
) -> Result<()> {
    let config = RNO3_CONFIG;
    let stage_assets = rno3_assets.join(config.graft.data_dir);
    let loaded = load_stitch_assets(
        &stage_assets,
        rno3_tileset,
        config.graft.stage,
        config.graft.tilemaps,
        config.graft.tiledef,
        config.reserved_tiledefs,
    )?;
    let scratch = output
        .parent()
        .unwrap_or(Path::new("."))
        .join(format!("{}-stitch-source", config.graft.stage));
    let (saturn_collision, saturn_art) =
        load_saturn_room_source(prg_path, map_path, &scratch, config.saturn)?;

    let row_matches = |psx_row: usize, saturn_row: usize| {
        (0..TILES).all(|column| {
            loaded.defs.hit(loaded.fg[psx_row * TILES + column])
                == saturn_collision[saturn_row * TILES + column]
        })
    };
    let shared_suffix = (0..PSX_ROWS)
        .rev()
        .take_while(|&row| row_matches(row, row + REVERSE_PSX_START))
        .count();
    let shared_top_chamber = (0..PSX_ROWS)
        .take_while(|&row| row_matches(row, row))
        .count();
    println!("RNO3 collision correspondences: shared suffix {shared_suffix}, top chamber {shared_top_chamber}");
    let mut aligned_fg = vec![0u16; TILES * SATURN_ROWS];
    let mut aligned_bg = vec![0u16; TILES * SATURN_ROWS];
    let aligned_start = TILES * REVERSE_PSX_START;
    aligned_fg[aligned_start..].copy_from_slice(&loaded.fg);
    aligned_bg[aligned_start..].copy_from_slice(&loaded.bg);
    let stitch = build_room(
        &saturn_art,
        &aligned_fg,
        &aligned_bg,
        &loaded.defs,
        &loaded.art,
        &saturn_collision,
        loaded.first_free,
        BuildConfig {
            rows: SATURN_ROWS,
            art: config.art,
            source_name: config.saturn.name,
        },
    )?;
    verify_collision(
        &stitch,
        &loaded.defs,
        &saturn_collision,
        TILES,
        config.verify_name,
    )?;
    write_stitch_visual_test(
        &stitch,
        &saturn_art,
        &loaded.defs,
        &loaded.art,
        output,
        SATURN_ROWS,
        config.visual_name,
        config.visual_source,
        config.reverse,
    )?;
    let door = load_saturn_door(prg_path, map_path, config.door_layout, config.door_slot)?;
    emit_stitched_asset_tree(
        rno3_assets,
        rno3_tileset,
        output,
        &loaded,
        &stitch,
        config.graft,
        &door,
        config.psx_entity_layout,
        config.psx_entity_y_offset,
    )?;
    std::fs::write(output, [])?;
    println!(
        "stitched RSTAGE01 room 17 above RNO3 room 1: {} arrangements generated, {} tile ids minted -> {}",
        stitch.graphics.len(), stitch.minted.len(), output.display()
    );
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::time::{SystemTime, UNIX_EPOCH};

    fn test_dir(name: &str) -> PathBuf {
        let nonce = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_nanos();
        std::env::temp_dir().join(format!(
            "saturn-assets-{name}-{}-{nonce}",
            std::process::id()
        ))
    }

    #[test]
    fn publishing_asset_tree_removes_stale_files() {
        let root = test_dir("publish");
        let source = root.join("source");
        let output = root.join("output");
        std::fs::create_dir_all(&source).unwrap();
        std::fs::write(source.join("current.bin"), b"first").unwrap();
        std::fs::write(source.join("removed.bin"), b"stale").unwrap();
        publish_asset_tree(&source, &output, |_| Ok(())).unwrap();

        std::fs::write(source.join("current.bin"), b"second").unwrap();
        std::fs::remove_file(source.join("removed.bin")).unwrap();
        publish_asset_tree(&source, &output, |_| Ok(())).unwrap();

        assert_eq!(
            std::fs::read(output.join("current.bin")).unwrap(),
            b"second"
        );
        assert!(!output.join("removed.bin").exists());
        std::fs::remove_dir_all(root).unwrap();
    }

    fn test_layer(left: i16, top: i16, is_loading_room: bool, is_save_room: bool) -> PsxLayerDef {
        PsxLayerDef {
            data: "tilemap.bin".to_string(),
            tiledef: "tiledef.json".to_string(),
            left,
            top,
            right: left,
            bottom: top,
            scroll_mode: 0,
            hide_on_map: false,
            is_save_room,
            is_loading_room,
            unused_flag: false,
            z_priority: 0,
            flags: 0,
        }
    }

    #[test]
    fn np3_graft_preserves_the_existing_save_room() {
        let root = test_dir("np3-save-room");
        std::fs::create_dir_all(&root).unwrap();
        let rooms = vec![
            PsxRoom {
                left: 20,
                top: 36,
                right: 20,
                bottom: 36,
                layer_id: 0,
                tiledef_id: 0,
                entity_gfx_id: 0,
                entity_layout_id: 52,
            },
            PsxRoom {
                left: 2,
                top: 41,
                right: 2,
                bottom: 42,
                layer_id: 1,
                tiledef_id: 0,
                entity_gfx_id: 0,
                entity_layout_id: 2,
            },
            PsxRoom {
                left: 3,
                top: 42,
                right: 3,
                bottom: 42,
                layer_id: 2,
                tiledef_id: 0,
                entity_gfx_id: 0,
                entity_layout_id: 48,
            },
        ];
        let layers = vec![
            PsxLayers {
                fg: Some(test_layer(20, 36, true, false)),
                bg: None,
            },
            PsxLayers {
                fg: Some(test_layer(2, 41, false, false)),
                bg: None,
            },
            PsxLayers {
                fg: Some(test_layer(3, 42, false, true)),
                bg: None,
            },
        ];
        std::fs::write(
            root.join("rooms.json"),
            serde_json::to_string(&rooms).unwrap(),
        )
        .unwrap();
        std::fs::write(
            root.join("layers.json"),
            serde_json::to_string(&layers).unwrap(),
        )
        .unwrap();

        write_stitched_rooms_and_layers(
            &root,
            AssetGraft {
                stage: "np3",
                data_dir: "",
                rooms: "rooms",
                layers: "layers",
                room: 1,
                tilemaps: (2, 3),
                tiledef: 2,
                psx_width: 16,
                psx_height: 32,
                region: TileRegion {
                    left: 0,
                    top: 0,
                    width: 16,
                    height: 64,
                },
                shaft_top: None,
                shaft_bottom: Some(44),
                cd: Some((3, 44)),
                trigger: (4, 44, 131),
            },
        )
        .unwrap();

        let rooms: Vec<PsxRoom> =
            serde_json::from_slice(&std::fs::read(root.join("rooms.json")).unwrap()).unwrap();
        let layers: Vec<PsxLayers> =
            serde_json::from_slice(&std::fs::read(root.join("layers.json")).unwrap()).unwrap();
        assert_eq!((rooms[2].left, rooms[2].top, rooms[2].layer_id), (3, 42, 2));
        assert!(layers[2].fg.as_ref().unwrap().is_save_room);
        assert_eq!((rooms[3].left, rooms[3].top), (3, 44));
        assert!(
            layers[rooms[3].layer_id as usize]
                .fg
                .as_ref()
                .unwrap()
                .is_loading_room
        );
        std::fs::remove_dir_all(root).unwrap();
    }
}
