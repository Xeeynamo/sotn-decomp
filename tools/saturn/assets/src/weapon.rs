use crate::image::{self, Indexed};
use crate::sheet;
use crate::sprite::{
    display_palette, pack, parse_image_table, read_palette_banks, to_linear, unpack, RawRecord,
    RESOURCE_STRIDE,
};
use crate::{sha256_hex, Error, Result};
use serde::{Deserialize, Serialize};
use std::path::{Path, PathBuf};

pub const FORMAT: &str = "sotn-saturn-weapon-chr";
pub const VERSION: u32 = 1;
pub const MANIFEST_NAME: &str = "manifest.json";
pub const LINEAR_NAME: &str = "linear.png";
pub const CONTACT_NAME: &str = "contact.png";
pub const SPRITES_DIR: &str = "sprites";
pub const ENCODING: &str = "indexed4-linear-high-nibble-first";

pub const VDP1_BASE: u32 = 0x25C0_0000;
pub const DESTINATION_OFFSET_GLOBAL: u32 = 0x0605_BEC4;

#[derive(Clone, Copy)]
pub struct Profile {
    pub name: &'static str,
    pub file: &'static str,
    pub prg: &'static str,
    pub load_address: u32,
    pub resource_array_offset: usize,
    pub resource_count: usize,
    pub vdp1_offset: u32,
}

pub const PROFILES: &[Profile] = &[
    Profile {
        name: "maria",
        file: "MAR_W.CHR",
        prg: "MARIA.PRG",
        load_address: 0x060A_5000,
        resource_array_offset: 0x21D68,
        resource_count: 13,
        vdp1_offset: 0x1D980,
    },
    Profile {
        name: "richter",
        file: "RIC_W.CHR",
        prg: "RICHTER.PRG",
        load_address: 0x060A_5000,
        resource_array_offset: 0x1DF2C,
        resource_count: 10,
        vdp1_offset: 0x1D980,
    },
    Profile {
        name: "alucard",
        file: "ALC_W.CHR",
        prg: "ALUCARD.PRG",
        load_address: 0x060A_5000,
        resource_array_offset: 0x26DF8,
        resource_count: 13,
        vdp1_offset: 0x2A980,
    },
];

pub fn profile(name: &str) -> Result<&'static Profile> {
    PROFILES.iter().find(|p| p.name == name).ok_or_else(|| {
        let known: Vec<&str> = PROFILES.iter().map(|p| p.name).collect();
        Error::Format(format!(
            "unknown weapon character {name:?}; known: {}",
            known.join(", ")
        ))
    })
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Source {
    pub name: String,
    pub size: usize,
    pub sha256: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct PrgSource {
    pub name: String,
    pub size: usize,
    pub sha256: String,
    pub resource_array_offset: usize,
    pub resource_count: usize,
    pub first_resource: usize,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Vdp1 {
    pub destination_base: u32,
    pub load_offset: u32,
    pub load_address: u32,
    pub destination_offset_global: u32,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct ImageRecord {
    pub index: usize,
    pub stored_width: u8,
    pub stored_height: u8,
    pub pixel_width: u32,
    pub pixel_height: u32,
    pub offset: usize,
    pub byte_count: usize,
    pub allocation_size: usize,
    pub file_offset: usize,
    pub sha256: String,
    pub file: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Package {
    pub resource_index: usize,
    pub image_table_address: u32,
    pub image_table_prg_offset: usize,
    pub palette_table_address: u32,
    pub palette_table_prg_offset: usize,
    pub palette_banks: usize,
    pub byte_count: usize,
    pub file_offset: usize,
    pub images: Vec<ImageRecord>,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Manifest {
    pub format: String,
    pub version: u32,
    pub character: String,
    pub encoding: String,
    pub linear: String,
    pub linear_width: u32,
    pub linear_height: u32,
    #[serde(skip_serializing_if = "Option::is_none", default)]
    pub contact: Option<String>,
    pub valid_pixels: usize,
    pub padding_pixels: usize,
    pub vdp1: Vdp1,
    pub source: Source,
    pub prg: Option<PrgSource>,
    #[serde(default)]
    pub packages: Vec<Package>,
}

impl Manifest {
    pub fn profile(&self) -> Result<&'static Profile> {
        profile(&self.character)
    }

    pub fn records(&self) -> impl Iterator<Item = (&Package, &ImageRecord)> {
        self.packages
            .iter()
            .flat_map(|package| package.images.iter().map(move |image| (package, image)))
    }
}

fn record_image(data: &[u8], record: &ImageRecord) -> Indexed {
    let bytes = &data[record.file_offset..record.file_offset + record.byte_count];
    Indexed {
        width: record.pixel_width,
        height: record.pixel_height,
        pixels: unpack(bytes),
    }
}

fn read_packages(prg: &[u8], profile: &Profile, chr_size: usize) -> Result<(usize, Vec<Package>)> {
    struct Parsed {
        image_table_address: u32,
        image_table_prg_offset: usize,
        palette_table_address: u32,
        palette_table_prg_offset: usize,
        byte_count: usize,
        records: Vec<RawRecord>,
    }

    let mut parsed = Vec::with_capacity(profile.resource_count);
    for index in 0..profile.resource_count {
        let entry = profile.resource_array_offset + index * RESOURCE_STRIDE;
        if entry + RESOURCE_STRIDE > prg.len() {
            return Err(Error::Format(format!(
                "resource array entry {index} runs past the end of the PRG"
            )));
        }
        let image_table_address = u32::from_be_bytes(prg[entry..entry + 4].try_into().unwrap());
        let palette_table_address =
            u32::from_be_bytes(prg[entry + 4..entry + 8].try_into().unwrap());
        let table_offset = image_table_address
            .checked_sub(profile.load_address)
            .map(|offset| offset as usize)
            .filter(|&offset| offset < prg.len())
            .ok_or_else(|| {
                Error::Format(format!(
                    "resource {index} image table 0x{image_table_address:08X} is outside the PRG"
                ))
            })?;
        let (records, byte_count) = parse_image_table(prg, table_offset)?;
        parsed.push(Parsed {
            image_table_address,
            image_table_prg_offset: table_offset,
            palette_table_address,
            palette_table_prg_offset: palette_table_address.wrapping_sub(profile.load_address)
                as usize,
            byte_count,
            records,
        });
    }

    let starts: Vec<usize> = (0..parsed.len())
        .filter(|&start| {
            parsed[start..]
                .iter()
                .map(|resource| resource.byte_count)
                .sum::<usize>()
                == chr_size
        })
        .collect();
    if starts.len() != 1 {
        return Err(Error::Format(format!(
            "{} does not uniquely partition {} ({} bytes): {} candidate splits",
            profile.prg,
            profile.file,
            chr_size,
            starts.len()
        )));
    }
    let first = starts[0];

    let mut packages = Vec::with_capacity(parsed.len() - first);
    let mut file_offset = 0usize;
    for (position, resource) in parsed.into_iter().enumerate().skip(first) {
        let banks = read_palette_banks(prg, resource.palette_table_prg_offset);
        let images = resource
            .records
            .iter()
            .map(|record| ImageRecord {
                index: record.index,
                stored_width: record.stored_width,
                stored_height: record.stored_height,
                pixel_width: record.stored_width as u32 * 2,
                pixel_height: record.stored_height as u32 * 2,
                offset: record.offset,
                byte_count: record.byte_count,
                allocation_size: record.allocation_size,
                file_offset: file_offset + record.offset,
                sha256: String::new(),
                file: format!(
                    "{SPRITES_DIR}/resource-{position:02}/image-{:03}.png",
                    record.index
                ),
            })
            .collect();
        packages.push(Package {
            resource_index: position,
            image_table_address: resource.image_table_address,
            image_table_prg_offset: resource.image_table_prg_offset,
            palette_table_address: resource.palette_table_address,
            palette_table_prg_offset: resource.palette_table_prg_offset,
            palette_banks: banks.len(),
            byte_count: resource.byte_count,
            file_offset,
            images,
        });
        file_offset += resource.byte_count;
    }
    if file_offset != chr_size {
        return Err(Error::Format(format!(
            "packages cover {file_offset} bytes of a {chr_size}-byte {}",
            profile.file
        )));
    }
    Ok((first, packages))
}

pub fn extract(
    character: &str,
    chr_path: &Path,
    prg_path: Option<&Path>,
    output_dir: &Path,
) -> Result<Manifest> {
    let profile = profile(character)?;
    let data = std::fs::read(chr_path)?;
    if data.is_empty() {
        return Err(Error::Format(format!("{} is empty", chr_path.display())));
    }

    let atlas = to_linear(&data);
    let valid_pixels = data.len() * 2;
    let total_pixels = (atlas.width * atlas.height) as usize;

    let prg = prg_path.map(std::fs::read).transpose()?;
    let (prg_source, mut packages) = match (prg_path, &prg) {
        (Some(path), Some(prg)) => {
            let (first, packages) = read_packages(prg, profile, data.len())?;
            (
                Some(PrgSource {
                    name: file_name(path),
                    size: prg.len(),
                    sha256: sha256_hex(prg),
                    resource_array_offset: profile.resource_array_offset,
                    resource_count: profile.resource_count,
                    first_resource: first,
                }),
                packages,
            )
        }
        _ => (None, Vec::new()),
    };

    std::fs::create_dir_all(output_dir)?;
    image::write_indexed(&output_dir.join(LINEAR_NAME), &atlas)?;

    for package in &mut packages {
        let banks = prg
            .as_deref()
            .map(|prg| read_palette_banks(prg, package.palette_table_prg_offset))
            .unwrap_or_default();
        let palette = display_palette(&banks);
        for record in &mut package.images {
            record.sha256 =
                sha256_hex(&data[record.file_offset..record.file_offset + record.byte_count]);
            image::write_indexed_palette(
                &safe_join(output_dir, &record.file)?,
                &record_image(&data, record),
                palette.as_deref(),
            )?;
        }
    }

    let manifest = Manifest {
        format: FORMAT.to_string(),
        version: VERSION,
        character: profile.name.to_string(),
        encoding: ENCODING.to_string(),
        linear: LINEAR_NAME.to_string(),
        linear_width: atlas.width,
        linear_height: atlas.height,
        contact: (!packages.is_empty()).then(|| CONTACT_NAME.to_string()),
        valid_pixels,
        padding_pixels: total_pixels - valid_pixels,
        vdp1: Vdp1 {
            destination_base: VDP1_BASE,
            load_offset: profile.vdp1_offset,
            load_address: VDP1_BASE + profile.vdp1_offset,
            destination_offset_global: DESTINATION_OFFSET_GLOBAL,
        },
        source: Source {
            name: file_name(chr_path),
            size: data.len(),
            sha256: sha256_hex(&data),
        },
        prg: prg_source,
        packages,
    };

    if let Some(name) = &manifest.contact {
        let groups: Vec<sheet::Group> = manifest
            .packages
            .iter()
            .map(|package| sheet::Group {
                label: Some(package.resource_index),
                palette: prg
                    .as_deref()
                    .map(|prg| read_palette_banks(prg, package.palette_table_prg_offset))
                    .as_deref()
                    .and_then(display_palette),
                records: package
                    .images
                    .iter()
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

fn file_name(path: &Path) -> String {
    path.file_name()
        .map(|name| name.to_string_lossy().into_owned())
        .unwrap_or_else(|| path.display().to_string())
}

fn safe_join(root: &Path, relative: &str) -> Result<PathBuf> {
    let path = Path::new(relative);
    if path.is_absolute()
        || path
            .components()
            .any(|component| matches!(component, std::path::Component::ParentDir))
    {
        return Err(Error::Format(format!(
            "manifest contains an unsafe path: {relative}"
        )));
    }
    Ok(root.join(path))
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
    let profile = manifest.profile()?;
    if manifest.encoding != ENCODING {
        return Err(Error::Format(format!(
            "{}: unsupported pixel encoding {:?}",
            manifest_path.display(),
            manifest.encoding
        )));
    }
    let vdp1 = &manifest.vdp1;
    if vdp1.destination_base != VDP1_BASE
        || vdp1.load_offset != profile.vdp1_offset
        || vdp1.load_address != VDP1_BASE + profile.vdp1_offset
        || vdp1.destination_offset_global != DESTINATION_OFFSET_GLOBAL
    {
        return Err(Error::Format(format!(
            "{}: VDP1 destination contract does not match the {} profile",
            manifest_path.display(),
            profile.name
        )));
    }
    if manifest.valid_pixels != manifest.source.size * 2 {
        return Err(Error::Format(format!(
            "{}: valid_pixels does not match the source size",
            manifest_path.display()
        )));
    }
    Ok(manifest)
}

fn check_packages(manifest: &Manifest) -> Result<()> {
    let mut expected = 0usize;
    for package in &manifest.packages {
        if package.file_offset != expected {
            return Err(Error::Format(format!(
                "resource {} starts at 0x{:X}, expected 0x{expected:X}",
                package.resource_index, package.file_offset
            )));
        }
        let end = expected + package.byte_count;
        if end > manifest.source.size {
            return Err(Error::Format(format!(
                "resource {} ends past the end of the CHR",
                package.resource_index
            )));
        }
        for (position, record) in package.images.iter().enumerate() {
            if record.index != position {
                return Err(Error::Format(format!(
                    "resource {} image indices are not sequential",
                    package.resource_index
                )));
            }
            if record.file_offset != package.file_offset + record.offset
                || record.file_offset + record.byte_count > end
                || record.allocation_size < record.byte_count
                || record.byte_count
                    != record.pixel_width as usize * record.pixel_height as usize / 2
            {
                return Err(Error::Format(format!(
                    "resource {} image {} is inconsistent with its package",
                    package.resource_index, record.index
                )));
            }
        }
        expected = end;
    }
    if !manifest.packages.is_empty() && expected != manifest.source.size {
        return Err(Error::Format(format!(
            "packages cover {expected} bytes of a {}-byte CHR",
            manifest.source.size
        )));
    }
    Ok(())
}

pub fn rebuild_bytes(manifest_path: &Path) -> Result<Vec<u8>> {
    let manifest = load_manifest(manifest_path)?;
    check_packages(&manifest)?;
    let root = manifest_path.parent().unwrap_or_else(|| Path::new("."));

    let atlas = image::read_indexed(&safe_join(root, &manifest.linear)?)?;
    if (atlas.width, atlas.height) != (manifest.linear_width, manifest.linear_height) {
        return Err(Error::Format(format!(
            "atlas is {}x{}, expected {}x{} (resizing is not supported)",
            atlas.width, atlas.height, manifest.linear_width, manifest.linear_height
        )));
    }
    if atlas.pixels.len() != manifest.valid_pixels + manifest.padding_pixels {
        return Err(Error::Format(format!(
            "atlas holds {} pixels, manifest describes {}",
            atlas.pixels.len(),
            manifest.valid_pixels + manifest.padding_pixels
        )));
    }
    if let Some(position) = atlas.pixels[manifest.valid_pixels..]
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

    let mut out = pack(&atlas.pixels[..manifest.valid_pixels])?;

    for (package, record) in manifest.records() {
        let start = record.file_offset;
        let end = start + record.byte_count;
        if sha256_hex(&out[start..end]) != record.sha256 {
            return Err(Error::Format(format!(
                "{} was edited at 0x{start:X}..0x{end:X}, which belongs to \
                 resource {} image {}; edit {} instead",
                manifest.linear, package.resource_index, record.index, record.file
            )));
        }
        let sprite = image::read_indexed(&safe_join(root, &record.file)?)?;
        if (sprite.width, sprite.height) != (record.pixel_width, record.pixel_height) {
            return Err(Error::Format(format!(
                "{} is {}x{}, expected {}x{} (resizing is not supported)",
                record.file, sprite.width, sprite.height, record.pixel_width, record.pixel_height
            )));
        }
        out[start..end].copy_from_slice(&pack(&sprite.pixels)?);
    }

    if out.len() != manifest.source.size {
        return Err(Error::Format(format!(
            "rebuilt {} bytes, retail is {}",
            out.len(),
            manifest.source.size
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
        "rebuilt weapon CHR does not match {} ({detail})",
        chr_path.display()
    )))
}
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn every_profile_names_a_distinct_character_and_file() {
        for profile in PROFILES {
            assert_eq!(super::profile(profile.name).unwrap().file, profile.file);
        }
        assert!(super::profile("dracula").is_err());
    }

    #[test]
    fn a_path_escaping_the_extract_is_refused() {
        let root = Path::new("/tmp/extract");
        assert!(safe_join(root, "sprites/resource-01/image-000.png").is_ok());
        assert!(safe_join(root, "../../etc/passwd").is_err());
        assert!(safe_join(root, "/etc/passwd").is_err());
    }
}
