
use crate::image::Rgba;
use crate::lzss;
use crate::map::{self, stage_of, LAYERS, ROOM_STRIDE, STAGE_LOAD_ADDRESS, SUBSTAGE_STRIDE};
use crate::sprite::rgb555;
use crate::{Error, Result};
use std::path::{Path, PathBuf};

const SCREEN_WIDTH: usize = 320;
const SCREEN_HEIGHT: usize = 256;
const TILE_BYTES: usize = 32;
pub const COMPOSITE_NAME: &str = "composite.png";

#[derive(Clone, Copy)]
struct Extent {
    min_x: u8,
    min_y: u8,
    max_x: u8,
    max_y: u8,
}

struct StageImage {
    image: Rgba,
    rooms: usize,
    extent: Extent,
}

struct RoomImage {
    left: u8,
    top: u8,
    right: u8,
    bottom: u8,
    image: Rgba,
}

fn read_u32(data: &[u8], at: usize) -> Result<u32> {
    data.get(at..at + 4)
        .map(|bytes| u32::from_be_bytes([bytes[0], bytes[1], bytes[2], bytes[3]]))
        .ok_or_else(|| Error::Format(format!("u32 at 0x{at:X} lies outside the overlay")))
}

fn export_offset(prg: &[u8], substage: usize, field: usize) -> Result<usize> {
    let at = field
        .checked_add(substage.saturating_mul(SUBSTAGE_STRIDE))
        .ok_or_else(|| Error::Format("stage export offset overflowed".to_string()))?;
    let address = read_u32(prg, at)?;
    address
        .checked_sub(STAGE_LOAD_ADDRESS)
        .map(|offset| offset as usize)
        .filter(|&offset| offset < prg.len())
        .ok_or_else(|| {
            Error::Format(format!(
                "export pointer 0x{address:08X} at +0x{at:X} is outside the stage PRG"
            ))
        })
}

fn room_count(prg: &[u8], substage: usize) -> Result<usize> {
    let counts = export_offset(prg, substage, 0x14)?;
    let next = export_offset(prg, substage, 0x20)?;
    let span = next as isize - counts as isize;
    if span <= 0 || span as usize % ROOM_STRIDE != 0 {
        return Err(Error::Format(
            "cannot derive room count from the stage export tables".to_string(),
        ));
    }
    Ok(span as usize / ROOM_STRIDE)
}

fn stage_streams(
    prg: &[u8],
    map_data: &[u8],
    room: usize,
    layer: usize,
    substage: usize,
) -> Result<Option<[Vec<u8>; 3]>> {
    if layer >= LAYERS {
        return Err(Error::Format(format!(
            "layer {layer} is outside 0..{}",
            LAYERS - 1
        )));
    }
    let counts = export_offset(prg, substage, 0x14)?;
    let offsets = export_offset(prg, substage, 0x18)?;
    let descriptor = room
        .checked_mul(ROOM_STRIDE)
        .and_then(|value| value.checked_add(layer * 12))
        .ok_or_else(|| Error::Format("room descriptor offset overflowed".to_string()))?;
    if counts + descriptor + 12 > prg.len() || offsets + descriptor + 12 > prg.len() {
        return Err(Error::Format(
            "room descriptor lies outside the stage PRG".to_string(),
        ));
    }

    let mut streams: [Vec<u8>; 3] = std::array::from_fn(|_| Vec::new());
    for (index, stream) in streams.iter_mut().enumerate() {
        let offset = read_u32(prg, offsets + descriptor + index * 4)? as usize;
        let size = read_u32(prg, counts + descriptor + index * 4)? as usize;
        if size == 0 {
            return Ok(None);
        }
        let end = offset.checked_add(size).ok_or_else(|| {
            Error::Format(format!(
                "room {room} layer {layer} stream {index} range overflowed"
            ))
        })?;
        let compressed = map_data.get(offset..end).ok_or_else(|| {
            Error::Format(format!(
                "room {room} layer {layer} stream {index} range 0x{offset:X}+0x{size:X} exceeds the MAP"
            ))
        })?;
        *stream = lzss::decompress(compressed);
    }
    Ok(Some(streams))
}

fn decode_palette(data: &[u8]) -> Result<Vec<[u8; 3]>> {
    if data.len() < 32 || data.len() % 32 != 0 {
        return Err(Error::Format(format!(
            "palette stream size {} is not a whole number of 16-colour banks",
            data.len()
        )));
    }
    Ok(data
        .chunks_exact(2)
        .map(|word| rgb555(u16::from_be_bytes([word[0], word[1]])))
        .collect())
}

fn render_layer_bytes(
    characters: &[u8],
    palette_data: &[u8],
    map_data: &[u8],
    transparent_zero: bool,
    retained_palette_data: &[Vec<u8>],
) -> Result<(Rgba, usize)> {
    if map_data.len() < 4 {
        return Err(Error::Format(
            "map stream has no width/height header".to_string(),
        ));
    }
    let mut width = u16::from_be_bytes([map_data[0], map_data[1]]) as usize;
    let height = u16::from_be_bytes([map_data[2], map_data[3]]) as usize;
    if width == 0 || height == 0 {
        return Err(Error::Format(format!(
            "map dimensions are {width}x{height}"
        )));
    }
    let mut expected = 4usize
        .checked_add(width.saturating_mul(height).saturating_mul(2))
        .ok_or_else(|| Error::Format("map dimensions overflowed".to_string()))?;
    if map_data.len() > expected && (map_data.len() - 4) % (height * 2) == 0 {
        let payload_width = (map_data.len() - 4) / (height * 2);
        if payload_width == 0x500 && width == 720 {
            width = payload_width;
            expected = map_data.len();
        }
    }

    let entries_bytes = if map_data.len() < expected {
        let missing = expected - map_data.len();
        if missing > 32 {
            return Err(Error::Format(format!(
                "map is {width}x{height}, needs {expected} bytes, got {}",
                map_data.len()
            )));
        }
        let mut padded = map_data.to_vec();
        padded.resize(expected, 0);
        padded
    } else {
        map_data[..expected].to_vec()
    };
    if characters.len() % TILE_BYTES != 0 {
        return Err(Error::Format(format!(
            "4bpp character stream size {} is not divisible by {TILE_BYTES}",
            characters.len()
        )));
    }

    let palette = decode_palette(palette_data)?;
    let retained: Vec<Vec<[u8; 3]>> = retained_palette_data
        .iter()
        .map(|data| decode_palette(data))
        .collect::<Result<_>>()?;
    let tile_count = characters.len() / TILE_BYTES;
    let pixel_width = width
        .checked_mul(8)
        .ok_or_else(|| Error::Format("render width overflowed".to_string()))?;
    let pixel_height = height
        .checked_mul(8)
        .ok_or_else(|| Error::Format("render height overflowed".to_string()))?;
    let mut image = Rgba::new(pixel_width as u32, pixel_height as u32, [0, 0, 0, 0]);

    for map_y in 0..height {
        for map_x in 0..width {
            let at = 4 + (map_y * width + map_x) * 2;
            let entry = u16::from_be_bytes([entries_bytes[at], entries_bytes[at + 1]]);
            let tile = (entry & 0x03FF) as usize;
            let palette_bank = (entry >> 12) as usize;
            if tile >= tile_count {
                return Err(Error::Format(format!(
                    "tile {tile} at ({map_x}, {map_y}) exceeds {tile_count} characters"
                )));
            }
            let flip_x = entry & 0x0400 != 0;
            let flip_y = entry & 0x0800 != 0;
            let tile_data = &characters[tile * TILE_BYTES..(tile + 1) * TILE_BYTES];
            for y in 0..8 {
                let source_y = if flip_y { 7 - y } else { y };
                for x in 0..8 {
                    let source_x = if flip_x { 7 - x } else { x };
                    let packed = tile_data[source_y * 4 + source_x / 2];
                    let colour_index = if source_x % 2 == 0 {
                        packed >> 4
                    } else {
                        packed & 0xF
                    };
                    let palette_index = palette_bank * 16 + colour_index as usize;
                    let colour = palette
                        .get(palette_index)
                        .or_else(|| retained.iter().find_map(|bank| bank.get(palette_index)))
                        .ok_or_else(|| {
                            Error::Format(format!(
                                "palette bank {palette_bank} at ({map_x}, {map_y}) exceeds {} decoded banks",
                                palette.len() / 16
                            ))
                        })?;
                    let alpha = if transparent_zero && colour_index == 0 {
                        0
                    } else {
                        255
                    };
                    image.set(
                        (map_x * 8 + x) as u32,
                        (map_y * 8 + y) as u32,
                        [colour[0], colour[1], colour[2], alpha],
                    );
                }
            }
        }
    }
    Ok((image, tile_count))
}

fn retained_palettes(
    prg: &[u8],
    map_data: &[u8],
    room: usize,
    layer: usize,
    substage: usize,
) -> Result<Vec<Vec<u8>>> {
    let mut retained = Vec::new();
    for previous in (0..layer).rev() {
        if let Some(streams) = stage_streams(prg, map_data, room, previous, substage)? {
            retained.push(streams[1].clone());
        }
    }
    Ok(retained)
}

fn resize_room(image: &Rgba, width: usize, height: usize, wrap_x: bool, wrap_y: bool) -> Rgba {
    let mut resized = Rgba::new(width as u32, height as u32, [0, 0, 0, 0]);
    let source_width = image.width as usize;
    let source_height = image.height as usize;
    for y in 0..height {
        let source_y = if wrap_y { y % source_height } else { y };
        for x in 0..width {
            let source_x = if wrap_x { x % source_width } else { x };
            if source_x >= source_width || source_y >= source_height {
                continue;
            }
            let source = (source_y * source_width + source_x) * 4;
            let output = (y * width + x) * 4;
            resized.pixels[output..output + 4].copy_from_slice(&image.pixels[source..source + 4]);
        }
    }
    resized
}

fn render_stage_bytes(
    prg: &[u8],
    map_data: &[u8],
    layer: usize,
    extent: Option<Extent>,
    transparent_zero: bool,
    substage: usize,
) -> Result<Option<StageImage>> {
    let bounds_offset = export_offset(prg, 0, 0x10)?;
    let setup_offset = export_offset(prg, substage, 0x1C)?;
    let rooms_total = room_count(prg, substage)?;
    let mut rooms = Vec::new();

    for room in 0..rooms_total {
        let record = bounds_offset + room * 6;
        let bounds = prg.get(record..record + 4).ok_or_else(|| {
            Error::Format("room bounds table lies outside the stage PRG".to_string())
        })?;
        let (left, top, right, bottom) = (bounds[0], bounds[1], bounds[2], bounds[3]);
        if left == 0xFF || right < left || bottom < top {
            continue;
        }
        let Some(streams) = stage_streams(prg, map_data, room, layer, substage)? else {
            continue;
        };
        let retained = retained_palettes(prg, map_data, room, layer, substage)?;
        let (mut image, _) = render_layer_bytes(
            &streams[0],
            &streams[1],
            &streams[2],
            transparent_zero,
            &retained,
        )?;
        let expected_width = (right - left + 1) as usize * SCREEN_WIDTH;
        let expected_height = (bottom - top + 1) as usize * SCREEN_HEIGHT;
        if image.width as usize != expected_width || image.height as usize != expected_height {
            let setup = setup_offset + room * 9 + layer * 3;
            let values = prg.get(setup..setup + 3).ok_or_else(|| {
                Error::Format("room setup table lies outside the stage PRG".to_string())
            })?;
            let wrap_x = values[2] & 1 != 0 || values[0] == 0;
            let wrap_y = values[2] & 2 != 0 || values[1] == 0;
            image = resize_room(&image, expected_width, expected_height, wrap_x, wrap_y);
        }
        rooms.push(RoomImage {
            left,
            top,
            right,
            bottom,
            image,
        });
    }
    if rooms.is_empty() {
        return Ok(None);
    }

    let extent = extent.unwrap_or_else(|| Extent {
        min_x: rooms.iter().map(|room| room.left).min().unwrap_or(0),
        min_y: rooms.iter().map(|room| room.top).min().unwrap_or(0),
        max_x: rooms.iter().map(|room| room.right).max().unwrap_or(0),
        max_y: rooms.iter().map(|room| room.bottom).max().unwrap_or(0),
    });
    let width = (extent.max_x - extent.min_x + 1) as usize * SCREEN_WIDTH;
    let height = (extent.max_y - extent.min_y + 1) as usize * SCREEN_HEIGHT;
    let fill_alpha = if transparent_zero { 0 } else { 255 };
    let mut image = Rgba::new(width as u32, height as u32, [0, 0, 0, fill_alpha]);
    for room in &rooms {
        if room.left < extent.min_x
            || room.top < extent.min_y
            || room.right > extent.max_x
            || room.bottom > extent.max_y
        {
            continue;
        }
        let x = (room.left - extent.min_x) as usize * SCREEN_WIDTH;
        let y = (room.top - extent.min_y) as usize * SCREEN_HEIGHT;
        let room_width = room.image.width as usize;
        for row in 0..room.image.height as usize {
            let source = row * room_width * 4;
            let destination = ((y + row) * width + x) * 4;
            image.pixels[destination..destination + room_width * 4]
                .copy_from_slice(&room.image.pixels[source..source + room_width * 4]);
        }
    }
    Ok(Some(StageImage {
        image,
        rooms: rooms.len(),
        extent,
    }))
}

fn composite_bytes(prg: &[u8], map_data: &[u8], substage: usize) -> Result<Rgba> {
    let base = render_stage_bytes(prg, map_data, 0, None, true, substage)?
        .ok_or_else(|| Error::Format("stage has no populated rooms on layer 0".to_string()))?;
    let width = base.image.width as usize;
    let height = base.image.height as usize;
    let mut layers = vec![base.image];
    for layer in 1..LAYERS {
        let image = render_stage_bytes(prg, map_data, layer, Some(base.extent), true, substage)?
            .map(|rendered| rendered.image)
            .unwrap_or_else(|| Rgba::new(width as u32, height as u32, [0, 0, 0, 0]));
        if image.width as usize != width || image.height as usize != height {
            return Err(Error::Format(
                "composite layers have inconsistent dimensions".to_string(),
            ));
        }
        layers.push(image);
    }

    let bounds_offset = export_offset(prg, 0, 0x10)?;
    let priority_offset = export_offset(prg, substage, 0x24)?;
    let rooms = room_count(prg, substage)?;
    let extent = base.extent;
    let mut output = Rgba::new(width as u32, height as u32, [0, 0, 0, 0]);
    for room in 0..rooms {
        let record = bounds_offset + room * 6;
        let bounds = prg.get(record..record + 4).ok_or_else(|| {
            Error::Format("room bounds table lies outside the stage PRG".to_string())
        })?;
        let (left, top, right, bottom) = (bounds[0], bounds[1], bounds[2], bounds[3]);
        if left == 0xFF
            || right < left
            || bottom < top
            || left < extent.min_x
            || top < extent.min_y
            || right > extent.max_x
            || bottom > extent.max_y
        {
            continue;
        }
        let priorities = prg
            .get(priority_offset + room * 12..priority_offset + room * 12 + 12)
            .ok_or_else(|| {
                Error::Format("room priority table lies outside the stage PRG".to_string())
            })?;
        let mut order = [0usize, 1, 2];
        order.sort_by_key(|&layer| (priorities[layer + 1], layer));
        let start_x = (left - extent.min_x) as usize * SCREEN_WIDTH;
        let start_y = (top - extent.min_y) as usize * SCREEN_HEIGHT;
        let room_width = (right - left + 1) as usize * SCREEN_WIDTH;
        let room_height = (bottom - top + 1) as usize * SCREEN_HEIGHT;
        for layer in order {
            for y in start_y..start_y + room_height {
                let start = (y * width + start_x) * 4;
                let end = start + room_width * 4;
                for at in (start..end).step_by(4) {
                    if layers[layer].pixels[at + 3] != 0 {
                        output.pixels[at..at + 4]
                            .copy_from_slice(&layers[layer].pixels[at..at + 4]);
                    }
                }
            }
        }
    }
    Ok(output)
}

fn read_inputs(prg_path: &Path, map_path: &Path) -> Result<(Vec<u8>, Vec<u8>, usize)> {
    let resolved = map::overlay_for(prg_path, map_path);
    let stem = map_path
        .file_stem()
        .and_then(|stem| stem.to_str())
        .unwrap_or_default();
    let (_, substage) = stage_of(stem);
    Ok((std::fs::read(resolved)?, std::fs::read(map_path)?, substage))
}

pub fn render_room(
    prg_path: &Path,
    map_path: &Path,
    room: usize,
    layer: usize,
) -> Result<(Rgba, usize)> {
    let (prg, map_data, substage) = read_inputs(prg_path, map_path)?;
    let streams = stage_streams(&prg, &map_data, room, layer, substage)?
        .ok_or_else(|| Error::Format(format!("room {room} layer {layer} is empty")))?;
    let retained = retained_palettes(&prg, &map_data, room, layer, substage)?;
    render_layer_bytes(&streams[0], &streams[1], &streams[2], layer != 0, &retained)
}

pub fn render_stage_layer(prg_path: &Path, map_path: &Path, layer: usize) -> Result<(Rgba, usize)> {
    let (prg, map_data, substage) = read_inputs(prg_path, map_path)?;
    let rendered = render_stage_bytes(&prg, &map_data, layer, None, layer != 0, substage)?
        .ok_or_else(|| Error::Format(format!("stage has no populated rooms on layer {layer}")))?;
    Ok((rendered.image, rendered.rooms))
}

pub fn render_composite(prg_path: &Path, map_path: &Path) -> Result<Rgba> {
    let (prg, map_data, substage) = read_inputs(prg_path, map_path)?;
    composite_bytes(&prg, &map_data, substage)
}

#[derive(Debug)]
pub struct BatchJob {
    pub name: String,
    pub prg: PathBuf,
    pub map: PathBuf,
}

pub fn discover(input_dir: &Path) -> Result<Vec<BatchJob>> {
    let mut maps: Vec<PathBuf> = std::fs::read_dir(input_dir)?
        .filter_map(|entry| entry.ok().map(|entry| entry.path()))
        .filter(|path| path.extension().and_then(|ext| ext.to_str()) == Some("MAP"))
        .collect();
    maps.sort();
    let mut jobs = Vec::new();
    for map_path in maps {
        let name = map_path
            .file_stem()
            .and_then(|stem| stem.to_str())
            .unwrap_or_default()
            .to_string();
        if matches!(name.as_str(), "TITLE" | "BOSS_R14" | "STAGE_07") {
            continue;
        }
        let prg = map::overlay_for(input_dir, &map_path);
        if prg.is_file() {
            jobs.push(BatchJob {
                name,
                prg,
                map: map_path,
            });
        }
    }
    let boss_prg = input_dir.join("BOSS_R14.PRG");
    let boss_map = input_dir.join("RSTAGE14.MAP");
    if boss_prg.is_file() && boss_map.is_file() {
        jobs.push(BatchJob {
            name: "BOSS_R14".to_string(),
            prg: boss_prg,
            map: boss_map,
        });
    }
    jobs.sort_by(|left, right| left.name.cmp(&right.name));
    Ok(jobs)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn a_flipped_tile_uses_its_selected_palette_bank() {
        let mut characters = vec![0u8; TILE_BYTES];
        characters[3] = 0x01;
        let mut palette = vec![0u8; 64];
        palette[34..36].copy_from_slice(&0x001Fu16.to_be_bytes());
        let tilemap = [0, 1, 0, 1, 0x14, 0x00];
        let (image, tiles) =
            render_layer_bytes(&characters, &palette, &tilemap, true, &[]).unwrap();
        assert_eq!(tiles, 1);
        assert_eq!(&image.pixels[..4], &[255, 0, 0, 255]);
        assert_eq!(&image.pixels[4..8], &[0, 0, 0, 0]);
    }

    #[test]
    fn a_short_tilemap_is_zero_filled_like_the_runtime_scratch_buffer() {
        let characters = vec![0u8; TILE_BYTES];
        let palette = vec![0u8; 32];
        let tilemap = [0, 2, 0, 1, 0, 0];
        let (image, _) = render_layer_bytes(&characters, &palette, &tilemap, false, &[]).unwrap();
        assert_eq!((image.width, image.height), (16, 8));
        assert!(image.pixels.chunks_exact(4).all(|pixel| pixel[3] == 255));
    }
}
