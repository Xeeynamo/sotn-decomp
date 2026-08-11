
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::path::{Path, PathBuf};

pub const FORMAT: &str = "sotn-saturn-sound-package";
pub const VERSION: u32 = 1;
pub const MANIFEST_NAME: &str = "manifest.json";
pub const AREAS_DIR: &str = "areas";

pub const AREA_MAP_OFFSET: usize = 0x369C0;
pub const AREA_MAP_SIZE: usize = 58;
pub const DRIVER_OFFSET: usize = 0x369FC;
pub const SOUND_FILE_TABLE_OFFSET: usize = 0x3D20C;
pub const SOUND_FILE_COUNT: usize = 57;
pub const SOUND_FILE_RECORD: usize = 17;

const DRIVER_SYSTEM_TABLE: usize = 0x400;
const DRIVER_SIGNATURE: [u8; 4] = [0x00, 0x00, 0x04, 0x40];

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
pub struct Area {
    pub id: u8,
    pub address: u32,
    pub size: u32,
    pub loadable: bool,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
#[serde(rename_all = "lowercase")]
pub enum Contents {
    Sequence,
    Other,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Song {
    pub index: usize,
    pub offset: u32,
    pub resolution: u16,
    pub track_offset: u16,
    pub tempo_offset: u16,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct AreaFile {
    pub id: u8,
    pub address: u32,
    pub offset: usize,
    pub size: usize,
    pub loadable: bool,
    pub contents: Contents,
    pub sha256: String,
    pub file: String,
    #[serde(skip_serializing_if = "Vec::is_empty", default)]
    pub songs: Vec<Song>,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Source {
    pub crt: String,
    pub crt_size: usize,
    pub crt_sha256: String,
    pub game: String,
    pub game_size: usize,
    pub game_sha256: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Manifest {
    pub format: String,
    pub version: u32,
    pub package: String,
    pub base_area: u8,
    pub base_address: u32,
    pub source: Source,
    pub areas: Vec<AreaFile>,
}

fn file_name(path: &Path) -> String {
    path.file_name()
        .map(|n| n.to_string_lossy().into_owned())
        .unwrap_or_else(|| path.display().to_string())
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

fn read_u16(data: &[u8], at: usize) -> Option<u16> {
    data.get(at..at + 2)
        .map(|b| u16::from_be_bytes([b[0], b[1]]))
}

fn read_u32(data: &[u8], at: usize) -> Option<u32> {
    data.get(at..at + 4)
        .map(|b| u32::from_be_bytes([b[0], b[1], b[2], b[3]]))
}

fn boot(game: &[u8]) -> Result<()> {
    let signature = game
        .get(DRIVER_OFFSET + DRIVER_SYSTEM_TABLE..DRIVER_OFFSET + DRIVER_SYSTEM_TABLE + 4)
        .ok_or_else(|| Error::Format("0.BIN is too small to hold the sound driver".to_string()))?;
    if signature != DRIVER_SIGNATURE {
        return Err(Error::Format(
            "0.BIN does not carry the v2.10-L sound driver these offsets describe".to_string(),
        ));
    }
    Ok(())
}

pub fn area_map(game: &[u8]) -> Result<Vec<Area>> {
    boot(game)?;
    let map = game
        .get(AREA_MAP_OFFSET..AREA_MAP_OFFSET + AREA_MAP_SIZE)
        .ok_or_else(|| Error::Format("0.BIN does not reach the sound area map".to_string()))?;
    let mut areas = Vec::new();
    for at in (0..map.len()).step_by(8) {
        if map[at] == 0xFF {
            return Ok(areas);
        }
        let Some(record) = map.get(at..at + 8) else {
            break;
        };
        let size_and_flags = u32::from_be_bytes([record[4], record[5], record[6], record[7]]);
        areas.push(Area {
            id: record[0],
            address: u32::from_be_bytes([0, record[1], record[2], record[3]]),
            size: size_and_flags & 0x000F_FFFF,
            loadable: size_and_flags & 0x8000_0000 != 0,
        });
    }
    Err(Error::Format(
        "the sound area map has no terminator".to_string(),
    ))
}

pub fn sound_files(game: &[u8]) -> Result<Vec<(String, u8)>> {
    boot(game)?;
    let mut files = Vec::with_capacity(SOUND_FILE_COUNT);
    for index in 0..SOUND_FILE_COUNT {
        let at = SOUND_FILE_TABLE_OFFSET + index * SOUND_FILE_RECORD;
        let record = game.get(at..at + SOUND_FILE_RECORD).ok_or_else(|| {
            Error::Format("0.BIN does not reach the whole sound-file table".to_string())
        })?;
        let end = record[..16].iter().position(|&b| b == 0).unwrap_or(16);
        let name = String::from_utf8_lossy(&record[..end]).into_owned();
        if name.is_empty() {
            return Err(Error::Format(format!(
                "sound-file record {index} has no name"
            )));
        }
        files.push((name.to_uppercase(), record[16]));
    }
    Ok(files)
}

pub fn base_area(game: &[u8], crt_name: &str) -> Result<u8> {
    let wanted = crt_name.to_uppercase();
    sound_files(game)?
        .into_iter()
        .find(|(name, _)| *name == wanted)
        .map(|(_, area)| area)
        .ok_or_else(|| {
            Error::Format(format!(
                "{crt_name} is not in 0.BIN's sound-file table, so nothing says where it loads"
            ))
        })
}

fn songs(data: &[u8]) -> Option<Vec<Song>> {
    let count = read_u16(data, 0)? as usize;
    if count == 0 || count > 128 {
        return None;
    }
    let mut songs = Vec::with_capacity(count);
    for index in 0..count {
        let offset = read_u32(data, 2 + index * 4)?;
        let song = data.get(offset as usize..)?;
        let resolution = read_u16(song, 0)?;
        let track_offset = read_u16(song, 4)?;
        let tempo_offset = read_u16(song, 6)?;
        if !(24..=960).contains(&resolution)
            || song.len() <= track_offset as usize
            || song.len() < tempo_offset as usize + 8
        {
            return None;
        }
        songs.push(Song {
            index,
            offset,
            resolution,
            track_offset,
            tempo_offset,
        });
    }
    Some(songs)
}

pub fn areas_of(game: &[u8], crt_name: &str, size: usize) -> Result<(u8, u32, Vec<Area>)> {
    let base = base_area(game, crt_name)?;
    let map = area_map(game)?;
    let start = map
        .iter()
        .find(|area| area.id == base)
        .ok_or_else(|| Error::Format(format!("area 0x{base:02X} is not in the area map")))?
        .address;
    let end = start + size as u32;
    let mut contained: Vec<Area> = map
        .into_iter()
        .filter(|area| area.address >= start && area.address < end)
        .collect();
    contained.sort_by_key(|area| area.address);
    if contained.first().map(|area| area.address) != Some(start) {
        return Err(Error::Format(format!(
            "{crt_name} does not begin on its base area"
        )));
    }
    Ok((base, start, contained))
}

pub fn extract(game_path: &Path, crt_path: &Path, output_dir: &Path) -> Result<Manifest> {
    let game = std::fs::read(game_path)?;
    let data = std::fs::read(crt_path)?;
    let name = file_name(crt_path);
    let (base, base_address, areas) = areas_of(&game, &name, data.len())?;

    std::fs::create_dir_all(output_dir.join(AREAS_DIR))?;
    let mut files = Vec::with_capacity(areas.len());
    for (index, area) in areas.iter().enumerate() {
        let offset = (area.address - base_address) as usize;
        let end = areas
            .get(index + 1)
            .map(|next| (next.address - base_address) as usize)
            .unwrap_or(data.len());
        if end < offset || end > data.len() {
            return Err(Error::Format(format!(
                "area 0x{:02X} lies outside {name}",
                area.id
            )));
        }
        let bytes = &data[offset..end];
        let songs = songs(bytes);
        let file = format!("{AREAS_DIR}/{:02X}.bin", area.id);
        std::fs::write(safe_join(output_dir, &file)?, bytes)?;
        files.push(AreaFile {
            id: area.id,
            address: area.address,
            offset,
            size: bytes.len(),
            loadable: area.loadable,
            contents: if songs.is_some() {
                Contents::Sequence
            } else {
                Contents::Other
            },
            sha256: sha256_hex(bytes),
            file,
            songs: songs.unwrap_or_default(),
        });
    }

    let manifest = Manifest {
        format: FORMAT.to_string(),
        version: VERSION,
        package: name.clone(),
        base_area: base,
        base_address,
        source: Source {
            crt: name,
            crt_size: data.len(),
            crt_sha256: sha256_hex(&data),
            game: file_name(game_path),
            game_size: game.len(),
            game_sha256: sha256_hex(&game),
        },
        areas: files,
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
    Ok(manifest)
}

pub fn rebuild_bytes(manifest_path: &Path) -> Result<Vec<u8>> {
    let manifest = load_manifest(manifest_path)?;
    let root = manifest_path.parent().unwrap_or_else(|| Path::new("."));
    let mut out = Vec::with_capacity(manifest.source.crt_size);
    for area in &manifest.areas {
        if area.offset != out.len() {
            return Err(Error::Format(format!(
                "area 0x{:02X} starts at 0x{:X}, but the areas before it fill 0x{:X}",
                area.id,
                area.offset,
                out.len()
            )));
        }
        let bytes = std::fs::read(safe_join(root, &area.file)?)?;
        if bytes.len() != area.size {
            return Err(Error::Format(format!(
                "{} is {} bytes, expected {} -- a sound area cannot change size \
                 without rewriting 0.BIN's area map",
                area.file,
                bytes.len(),
                area.size
            )));
        }
        out.extend_from_slice(&bytes);
    }
    if out.len() != manifest.source.crt_size {
        return Err(Error::Format(format!(
            "rebuilt {} bytes, retail is {}",
            out.len(),
            manifest.source.crt_size
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

pub fn verify(manifest_path: &Path, crt_path: &Path) -> Result<()> {
    let rebuilt = rebuild_bytes(manifest_path)?;
    let retail = std::fs::read(crt_path)?;
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
        "rebuilt package does not match {} ({detail})",
        crt_path.display()
    )))
}

#[cfg(test)]
mod tests {
    use super::*;

    fn game_with(map: &[u8]) -> Vec<u8> {
        let mut game = vec![0u8; SOUND_FILE_TABLE_OFFSET + SOUND_FILE_COUNT * SOUND_FILE_RECORD];
        game[DRIVER_OFFSET + DRIVER_SYSTEM_TABLE..DRIVER_OFFSET + DRIVER_SYSTEM_TABLE + 4]
            .copy_from_slice(&DRIVER_SIGNATURE);
        game[AREA_MAP_OFFSET..AREA_MAP_OFFSET + map.len()].copy_from_slice(map);
        game
    }

    fn record(id: u8, address: u32, size: u32) -> [u8; 8] {
        let mut out = [0u8; 8];
        out[0] = id;
        out[1..4].copy_from_slice(&address.to_be_bytes()[1..]);
        out[4..8].copy_from_slice(&(size | 0x8000_0000).to_be_bytes());
        out
    }

    #[test]
    fn a_0bin_without_the_expected_driver_is_refused() {
        let game = vec![0u8; SOUND_FILE_TABLE_OFFSET + SOUND_FILE_COUNT * SOUND_FILE_RECORD];
        assert!(area_map(&game).is_err());
    }

    #[test]
    fn the_area_map_ends_at_its_terminator() {
        let mut map = Vec::new();
        map.extend_from_slice(&record(0x10, 0xB000, 0x57BC));
        map.extend_from_slice(&record(0x00, 0x107BC, 0x32B64));
        map.extend_from_slice(&[0xFF; 8]);
        let areas = area_map(&game_with(&map)).expect("area map");
        assert_eq!(areas.len(), 2);
        assert_eq!(areas[0].id, 0x10);
        assert_eq!(areas[1].address, 0x107BC);
        assert!(areas[0].loadable);
    }

    #[test]
    fn a_map_without_a_terminator_is_refused() {
        let map: Vec<u8> = (0..AREA_MAP_SIZE / 8)
            .flat_map(|index| record(index as u8, 0x1000 * index as u32 + 1, 8))
            .collect();
        assert!(area_map(&game_with(&map)).is_err());
    }

    #[test]
    fn a_package_covers_the_areas_its_size_reaches() {
        let mut map = Vec::new();
        map.extend_from_slice(&record(0x11, 0x43320, 0x878));
        map.extend_from_slice(&record(0x01, 0x43B98, 0xA790));
        map.extend_from_slice(&record(0x12, 0x4E328, 0x800));
        map.extend_from_slice(&[0xFF; 8]);
        let mut game = game_with(&map);
        for index in 0..SOUND_FILE_COUNT {
            let at = SOUND_FILE_TABLE_OFFSET + index * SOUND_FILE_RECORD;
            let name = format!("SD_{index:02}.CRT");
            game[at..at + name.len()].copy_from_slice(name.as_bytes());
            game[at + 16] = 0x12;
        }
        let name = b"SD_ALK.CRT";
        game[SOUND_FILE_TABLE_OFFSET..SOUND_FILE_TABLE_OFFSET + name.len()]
            .copy_from_slice(name);
        game[SOUND_FILE_TABLE_OFFSET + 10] = 0;
        game[SOUND_FILE_TABLE_OFFSET + 16] = 0x11;

        let (base, address, areas) = areas_of(&game, "SD_ALK.CRT", 0x878 + 0xA790).expect("areas");
        assert_eq!((base, address), (0x11, 0x43320));
        assert_eq!(
            areas.iter().map(|area| area.id).collect::<Vec<_>>(),
            vec![0x11, 0x01]
        );
    }

    #[test]
    fn a_file_the_table_does_not_name_has_nowhere_to_load() {
        let mut map = Vec::new();
        map.extend_from_slice(&record(0x11, 0x43320, 0x878));
        map.extend_from_slice(&[0xFF; 8]);
        let mut game = game_with(&map);
        for index in 0..SOUND_FILE_COUNT {
            let at = SOUND_FILE_TABLE_OFFSET + index * SOUND_FILE_RECORD;
            let name = format!("SD_{index:02}.CRT");
            game[at..at + name.len()].copy_from_slice(name.as_bytes());
            game[at + 16] = 0x11;
        }
        assert!(base_area(&game, "SD_NOPE.CRT").is_err());
    }
}
