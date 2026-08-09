use crate::{Error, Result};
use std::fs::File;
use std::io::BufWriter;
use std::path::Path;

pub struct Bilevel {
    pub width: u32,
    pub height: u32,
    pub pixels: Vec<u8>,
}

impl Bilevel {
    pub fn new(width: u32, height: u32) -> Self {
        Bilevel {
            width,
            height,
            pixels: vec![0; (width as usize) * (height as usize)],
        }
    }

    pub fn get(&self, x: u32, y: u32) -> u8 {
        self.pixels[(y as usize) * (self.width as usize) + (x as usize)]
    }

    pub fn set(&mut self, x: u32, y: u32, value: u8) {
        let width = self.width as usize;
        self.pixels[(y as usize) * width + (x as usize)] = value;
    }
}

pub struct Indexed {
    pub width: u32,
    pub height: u32,
    pub pixels: Vec<u8>,
}

pub const MAX_INDEX: u8 = 15;

impl Indexed {
    pub fn new(width: u32, height: u32) -> Self {
        Indexed {
            width,
            height,
            pixels: vec![0; (width as usize) * (height as usize)],
        }
    }

    pub fn get(&self, x: u32, y: u32) -> u8 {
        self.pixels[(y as usize) * (self.width as usize) + (x as usize)]
    }

    pub fn set(&mut self, x: u32, y: u32, value: u8) {
        let width = self.width as usize;
        self.pixels[(y as usize) * width + (x as usize)] = value;
    }
}

fn display_ramp(pixels: &[u8]) -> Vec<u8> {
    let highest = pixels.iter().copied().max().unwrap_or(0).max(1);
    (0..=MAX_INDEX)
        .flat_map(|index| {
            if index <= highest {
                let level = (index as u32 * 255 / highest as u32) as u8;
                [level, level, level]
            } else {
                let spare = index - highest;
                let level = 96 + (spare as u32 * 159 / (MAX_INDEX - highest).max(1) as u32) as u8;
                [level, 0, 0]
            }
        })
        .collect()
}

pub fn write_indexed(path: &Path, image: &Indexed) -> Result<()> {
    write_indexed_palette(path, image, None)
}

pub fn write_indexed_palette(path: &Path, image: &Indexed, palette: Option<&[u8]>) -> Result<()> {
    if let Some(bad) = image.pixels.iter().find(|&&p| p > MAX_INDEX) {
        return Err(Error::Format(format!(
            "{}: 4bpp image contains index {bad}, above {MAX_INDEX}",
            path.display()
        )));
    }
    if let Some(colours) = palette {
        let entries = (MAX_INDEX as usize + 1) * 3;
        if colours.len() != entries {
            return Err(Error::Format(format!(
                "{}: display palette is {} bytes, expected {entries} (RGB per index)",
                path.display(),
                colours.len()
            )));
        }
    }
    if let Some(parent) = path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    let file = File::create(path)?;
    let mut encoder = png::Encoder::new(BufWriter::new(file), image.width, image.height);
    encoder.set_color(png::ColorType::Indexed);
    encoder.set_depth(png::BitDepth::Eight);
    match palette {
        Some(colours) => {
            encoder.set_palette(colours.to_vec());
            encoder.set_trns(vec![0u8]);
        }
        None => encoder.set_palette(display_ramp(&image.pixels)),
    }
    let mut writer = encoder
        .write_header()
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;
    writer
        .write_image_data(&image.pixels)
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;
    Ok(())
}

pub struct Rgba {
    pub width: u32,
    pub height: u32,
    pub pixels: Vec<u8>,
}

impl Rgba {
    pub fn new(width: u32, height: u32, fill: [u8; 4]) -> Self {
        Rgba {
            width,
            height,
            pixels: fill
                .iter()
                .copied()
                .cycle()
                .take((width as usize) * (height as usize) * 4)
                .collect(),
        }
    }

    pub fn set(&mut self, x: u32, y: u32, colour: [u8; 4]) {
        if x >= self.width || y >= self.height {
            return;
        }
        let at = ((y as usize) * (self.width as usize) + (x as usize)) * 4;
        self.pixels[at..at + 4].copy_from_slice(&colour);
    }

    pub fn fill_rect(&mut self, x: u32, y: u32, width: u32, height: u32, colour: [u8; 4]) {
        for row in y..y + height {
            for column in x..x + width {
                self.set(column, row, colour);
            }
        }
    }
}

pub fn write_rgba(path: &Path, image: &Rgba) -> Result<()> {
    if let Some(parent) = path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    let file = File::create(path)?;
    let mut encoder = png::Encoder::new(BufWriter::new(file), image.width, image.height);
    encoder.set_color(png::ColorType::Rgba);
    encoder.set_depth(png::BitDepth::Eight);
    let mut writer = encoder
        .write_header()
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;
    writer
        .write_image_data(&image.pixels)
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;
    Ok(())
}

pub fn read_indexed(path: &Path) -> Result<Indexed> {
    if let Some(indexed) = read_palette_indices(path)? {
        return Ok(indexed);
    }
    let (width, height, luminance) = read_luminance(path)?;
    let highest = luminance.iter().copied().max().unwrap_or(0).max(1) as u16;
    Ok(Indexed {
        width,
        height,
        pixels: luminance
            .iter()
            .map(|&value| {
                ((value as u16 * MAX_INDEX as u16 + highest / 2) / highest).min(MAX_INDEX as u16)
                    as u8
            })
            .collect(),
    })
}

fn read_palette_indices(path: &Path) -> Result<Option<Indexed>> {
    let file = File::open(path)?;
    let mut decoder = png::Decoder::new(file);
    decoder.set_transformations(png::Transformations::IDENTITY);
    let mut reader = decoder
        .read_info()
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;
    if reader.info().color_type != png::ColorType::Indexed {
        return Ok(None);
    }
    let mut buffer = vec![0; reader.output_buffer_size()];
    let info = reader
        .next_frame(&mut buffer)
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;

    let depth = info.bit_depth as u8 as u32;
    let width = info.width as usize;
    let row_bytes = (width * depth as usize).div_ceil(8);
    let mut pixels = Vec::with_capacity(width * info.height as usize);
    for row in buffer.chunks(row_bytes).take(info.height as usize) {
        for x in 0..width {
            let bit = x * depth as usize;
            let byte = row[bit / 8];
            let value = match depth {
                8 => byte,
                _ => (byte >> (8 - depth as usize - (bit % 8))) & ((1 << depth) - 1) as u8,
            };
            pixels.push(value);
        }
    }
    Ok(Some(Indexed {
        width: info.width,
        height: info.height,
        pixels,
    }))
}

fn write_luminance(path: &Path, image: &Bilevel) -> Result<()> {
    if let Some(parent) = path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    let file = File::create(path)?;
    let mut encoder = png::Encoder::new(BufWriter::new(file), image.width, image.height);
    encoder.set_color(png::ColorType::Grayscale);
    encoder.set_depth(png::BitDepth::Eight);
    let mut writer = encoder
        .write_header()
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;
    writer
        .write_image_data(&image.pixels)
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;
    Ok(())
}

pub fn write(path: &Path, atlas: &Bilevel) -> Result<()> {
    write_luminance(
        path,
        &Bilevel {
            width: atlas.width,
            height: atlas.height,
            pixels: atlas
                .pixels
                .iter()
                .map(|&b| if b != 0 { 255 } else { 0 })
                .collect(),
        },
    )
}

fn read_luminance(path: &Path) -> Result<(u32, u32, Vec<u8>)> {
    let file = File::open(path)?;
    let mut decoder = png::Decoder::new(file);
    decoder.set_transformations(png::Transformations::normalize_to_color8());
    let mut reader = decoder
        .read_info()
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;
    let mut buffer = vec![0; reader.output_buffer_size()];
    let info = reader
        .next_frame(&mut buffer)
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;
    if info.bit_depth != png::BitDepth::Eight {
        return Err(Error::Png(format!(
            "{}: expected 8 bits per sample after normalization, got {:?}",
            path.display(),
            info.bit_depth
        )));
    }

    let channels = info.color_type.samples();
    let has_alpha = matches!(
        info.color_type,
        png::ColorType::GrayscaleAlpha | png::ColorType::Rgba
    );
    let mut pixels = Vec::with_capacity((info.width as usize) * (info.height as usize));
    for sample in buffer[..info.buffer_size()].chunks_exact(channels) {
        let opaque = !has_alpha || sample[channels - 1] != 0;
        let colour = if has_alpha {
            &sample[..channels - 1]
        } else {
            sample
        };
        pixels.push(if opaque {
            colour.iter().copied().max().unwrap_or(0)
        } else {
            0
        });
    }
    Ok((info.width, info.height, pixels))
}

pub fn read(path: &Path) -> Result<Bilevel> {
    let (width, height, luminance) = read_luminance(path)?;
    Ok(Bilevel {
        width,
        height,
        pixels: luminance.iter().map(|&v| u8::from(v != 0)).collect(),
    })
}
