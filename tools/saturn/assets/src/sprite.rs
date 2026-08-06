use crate::image::{self, Indexed};
use crate::{Error, Result};
use serde::{Deserialize, Serialize};

pub const RESOURCE_STRIDE: usize = 12;
pub const OFFSET_UNIT: usize = 8;
pub const MAX_IMAGES: usize = 512;
pub const PALETTE_BANK_SIZE: usize = 16;
pub const RESOURCE_ALLOCATION: u16 = 0xFFFF;
pub const RESOURCE_FLAGS: u16 = 0xFFFF;

pub fn unpack(data: &[u8]) -> Vec<u8> {
    let mut pixels = Vec::with_capacity(data.len() * 2);
    for &byte in data {
        pixels.push(byte >> 4);
        pixels.push(byte & 0xF);
    }
    pixels
}

pub fn pack(pixels: &[u8]) -> Result<Vec<u8>> {
    if pixels.len() % 2 != 0 {
        return Err(Error::Format(format!(
            "packed 4bpp needs an even pixel count, got {}",
            pixels.len()
        )));
    }
    if let Some(bad) = pixels.iter().find(|&&p| p > image::MAX_INDEX) {
        return Err(Error::Format(format!(
            "4bpp image contains index {bad}, above {}",
            image::MAX_INDEX
        )));
    }
    Ok(pixels
        .chunks_exact(2)
        .map(|pair| (pair[0] << 4) | pair[1])
        .collect())
}

pub const LINEAR_WIDTH: u32 = 320;

pub fn to_linear(data: &[u8]) -> Indexed {
    let pixels = unpack(data);
    let height = (pixels.len() as u32).div_ceil(LINEAR_WIDTH).max(1);
    let mut linear = Indexed::new(LINEAR_WIDTH, height);
    linear.pixels[..pixels.len()].copy_from_slice(&pixels);
    linear
}

#[derive(Debug, Clone, Copy, Serialize, Deserialize)]
pub struct Resource {
    pub images_address: u32,
    pub palette_address: u32,
    pub allocation: u16,
    pub flags: u16,
}

impl Resource {
    pub fn read(data: &[u8], offset: usize) -> Option<Resource> {
        let bytes = data.get(offset..offset + RESOURCE_STRIDE)?;
        Some(Resource {
            images_address: u32::from_be_bytes(bytes[0..4].try_into().unwrap()),
            palette_address: u32::from_be_bytes(bytes[4..8].try_into().unwrap()),
            allocation: u16::from_be_bytes(bytes[8..10].try_into().unwrap()),
            flags: u16::from_be_bytes(bytes[10..12].try_into().unwrap()),
        })
    }

    pub fn is_canonical(&self) -> bool {
        self.allocation == RESOURCE_ALLOCATION && self.flags == RESOURCE_FLAGS
    }
}

#[derive(Debug, Clone, Copy)]
pub struct RawRecord {
    pub index: usize,
    pub stored_width: u8,
    pub stored_height: u8,
    pub offset: usize,
    pub byte_count: usize,
    pub allocation_size: usize,
}

impl RawRecord {
    pub fn pixel_width(&self) -> u32 {
        self.stored_width as u32 * 2
    }

    pub fn pixel_height(&self) -> u32 {
        self.stored_height as u32 * 2
    }
}

pub fn parse_image_table(data: &[u8], table_offset: usize) -> Result<(Vec<RawRecord>, usize)> {
    let mut records: Vec<RawRecord> = Vec::new();
    let mut cursor = table_offset;
    let total = loop {
        if records.len() >= MAX_IMAGES {
            return Err(Error::Format(format!(
                "image table at 0x{table_offset:X} has no terminator in {MAX_IMAGES} entries"
            )));
        }
        if cursor + 4 > data.len() {
            return Err(Error::Format(format!(
                "image table at 0x{table_offset:X} runs past the end of the overlay"
            )));
        }
        let stored_width = data[cursor];
        let stored_height = data[cursor + 1];
        let units = u16::from_be_bytes([data[cursor + 2], data[cursor + 3]]) as usize;
        if stored_width == 0 && stored_height == 0 {
            if records.is_empty() {
                return Err(Error::Format(format!(
                    "image table at 0x{table_offset:X} is empty"
                )));
            }
            break units * OFFSET_UNIT;
        }
        if stored_width == 0 || stored_height == 0 {
            return Err(Error::Format(format!(
                "image {} at 0x{table_offset:X} has a zero dimension",
                records.len()
            )));
        }
        let offset = units * OFFSET_UNIT;
        let byte_count = stored_width as usize * stored_height as usize * 2;
        if let Some(previous) = records.last() {
            if offset < previous.offset + previous.byte_count {
                return Err(Error::Format(format!(
                    "image {} at 0x{table_offset:X} overlaps image {}",
                    records.len(),
                    previous.index
                )));
            }
        }
        records.push(RawRecord {
            index: records.len(),
            stored_width,
            stored_height,
            offset,
            byte_count,
            allocation_size: 0,
        });
        cursor += 4;
    };

    let last = records.last().expect("checked non-empty above");
    if last.offset + last.byte_count > total {
        return Err(Error::Format(format!(
            "image {} at 0x{table_offset:X} ends past its {total}-byte region",
            last.index
        )));
    }
    for index in 0..records.len() {
        let next = records
            .get(index + 1)
            .map(|record| record.offset)
            .unwrap_or(total);
        records[index].allocation_size = next - records[index].offset;
    }
    Ok((records, total))
}

pub fn read_palette_banks(data: &[u8], offset: usize) -> Vec<Vec<[u8; 3]>> {
    let bank_bytes = PALETTE_BANK_SIZE * 2;
    if offset.saturating_add(2) > data.len() {
        return Vec::new();
    }
    let count = bank_count(data, offset);
    let mut banks = Vec::with_capacity(count);
    for bank in 0..count {
        let base = offset + 2 + bank * bank_bytes;
        if base.saturating_add(bank_bytes) > data.len() {
            break;
        }
        banks.push(
            (0..PALETTE_BANK_SIZE)
                .map(|index| {
                    rgb555(u16::from_be_bytes([
                        data[base + index * 2],
                        data[base + index * 2 + 1],
                    ]))
                })
                .collect(),
        );
    }
    banks
}

pub fn bank_count(data: &[u8], offset: usize) -> usize {
    match data.get(offset..offset + 2) {
        Some(bytes) => (u16::from_be_bytes([bytes[0], bytes[1]]) & 0x3FFF) as usize,
        None => 0,
    }
}

pub fn rgb555(word: u16) -> [u8; 3] {
    let channel = |shift: u32| (((word >> shift) & 0x1F) as u32 * 255 / 31) as u8;
    [channel(0), channel(5), channel(10)]
}

pub fn display_palette(banks: &[Vec<[u8; 3]>]) -> Option<Vec<u8>> {
    let bank = banks.first()?;
    if bank.len() != PALETTE_BANK_SIZE {
        return None;
    }
    Some(bank.iter().flatten().copied().collect())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn nibbles_round_trip_left_pixel_first() {
        let data: Vec<u8> = (0..=255u8).collect();
        let pixels = unpack(&data);
        assert_eq!(&pixels[..4], &[0x0, 0x0, 0x0, 0x1]);
        assert_eq!(pack(&pixels).unwrap(), data);
    }

    #[test]
    fn an_index_above_fifteen_is_refused() {
        let err = pack(&[0, 16]).unwrap_err();
        assert!(matches!(err, Error::Format(_)), "{err}");
    }

    #[test]
    fn the_linear_dump_round_trips_and_pads_the_last_row() {
        let data: Vec<u8> = (0..(LINEAR_WIDTH as usize / 2) * 3 - 1)
            .map(|i| (i * 31 + 7) as u8)
            .collect();
        let linear = to_linear(&data);
        assert_eq!((linear.width, linear.height), (LINEAR_WIDTH, 3));
        assert_eq!(pack(&linear.pixels[..data.len() * 2]).unwrap(), data);
        assert_eq!(&linear.pixels[data.len() * 2..], &[0, 0]);
    }

    #[test]
    fn an_image_table_decodes_offsets_dimensions_and_gaps() {
        let mut data = vec![0u8; 64];
        data[0..4].copy_from_slice(&[4, 4, 0, 0]);
        data[4..8].copy_from_slice(&[2, 3, 0, 8]);
        data[8..12].copy_from_slice(&[0, 0, 0, 16]);
        let (records, total) = parse_image_table(&data, 0).unwrap();
        assert_eq!(total, 128);
        assert_eq!(records.len(), 2);
        assert_eq!((records[0].offset, records[0].byte_count), (0, 32));
        assert_eq!(records[0].allocation_size, 64);
        assert_eq!(
            (records[0].pixel_width(), records[0].pixel_height()),
            (8, 8)
        );
        assert_eq!((records[1].offset, records[1].byte_count), (64, 12));
        assert_eq!(
            (records[1].pixel_width(), records[1].pixel_height()),
            (4, 6)
        );
    }

    #[test]
    fn overlapping_image_records_are_refused() {
        let mut data = vec![0u8; 32];
        data[0..4].copy_from_slice(&[4, 4, 0, 0]);
        data[4..8].copy_from_slice(&[2, 2, 0, 1]);
        data[8..12].copy_from_slice(&[0, 0, 0, 16]);
        let err = parse_image_table(&data, 0).unwrap_err();
        assert!(matches!(err, Error::Format(_)), "{err}");
    }

    #[test]
    fn an_unterminated_image_table_is_refused() {
        let data = vec![1u8; MAX_IMAGES * 8];
        let err = parse_image_table(&data, 0).unwrap_err();
        assert!(matches!(err, Error::Format(_)), "{err}");
    }

    #[test]
    fn rgb555_expands_to_full_range() {
        assert_eq!(rgb555(0xFC00), [0, 0, 255]);
        assert_eq!(rgb555(0x83E0), [0, 255, 0]);
        assert_eq!(rgb555(0x801F), [255, 0, 0]);
    }

    #[test]
    fn a_clut_reads_its_declared_banks() {
        let mut data = vec![0u8; 2 + PALETTE_BANK_SIZE * 2 * 2];
        data[0..2].copy_from_slice(&2u16.to_be_bytes());
        data[2..4].copy_from_slice(&0x801Fu16.to_be_bytes());
        let banks = read_palette_banks(&data, 0);
        assert_eq!(banks.len(), 2);
        assert_eq!(banks[0][0], [255, 0, 0]);
        assert_eq!(
            display_palette(&banks).unwrap().len(),
            PALETTE_BANK_SIZE * 3
        );
    }

    #[test]
    fn a_resource_is_canonical_only_with_the_measured_sentinel_fields() {
        let mut data = vec![0u8; RESOURCE_STRIDE];
        data[8..10].copy_from_slice(&0xFFFFu16.to_be_bytes());
        data[10..12].copy_from_slice(&0xFFFFu16.to_be_bytes());
        assert!(Resource::read(&data, 0).unwrap().is_canonical());
        data[10..12].copy_from_slice(&0xB344u16.to_be_bytes());
        assert!(!Resource::read(&data, 0).unwrap().is_canonical());
        assert!(Resource::read(&data, 4).is_none());
    }
}
