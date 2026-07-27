//! png reader/write for fonts
//!
//! orignals are 1 bit fonts but write 8-bit for compatiblity

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

pub fn write(path: &Path, atlas: &Bilevel) -> Result<()> {
    if let Some(parent) = path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    let file = File::create(path)?;
    let mut encoder = png::Encoder::new(BufWriter::new(file), atlas.width, atlas.height);
    encoder.set_color(png::ColorType::Grayscale);
    encoder.set_depth(png::BitDepth::Eight);
    let mut writer = encoder
        .write_header()
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;
    let luminance: Vec<u8> = atlas
        .pixels
        .iter()
        .map(|&b| if b != 0 { 255 } else { 0 })
        .collect();
    writer
        .write_image_data(&luminance)
        .map_err(|e| Error::Png(format!("{}: {e}", path.display())))?;
    Ok(())
}

pub fn read(path: &Path) -> Result<Bilevel> {
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
        pixels.push(u8::from(opaque && colour.iter().any(|&c| c != 0)));
    }

    Ok(Bilevel {
        width: info.width,
        height: info.height,
        pixels,
    })
}
