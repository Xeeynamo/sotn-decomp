use saturn_assets::psx_stage::Raster;
use saturn_assets::stitch::{self, Np3Art, TileDefs, PSX_ROWS, SATURN_ROWS, STITCH_ROW};
use std::collections::HashMap;
use std::path::{Path, PathBuf};

#[path = "support/stitch_preservation.rs"]
mod stitch_preservation;

fn repo_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR"))
        .ancestors()
        .nth(3)
        .expect("crate is three levels below the repo root")
        .to_path_buf()
}

fn u16le(path: &Path) -> Option<Vec<u16>> {
    Some(
        std::fs::read(path)
            .ok()?
            .chunks_exact(2)
            .map(|b| u16::from_le_bytes([b[0], b[1]]))
            .collect(),
    )
}

struct Inputs {
    fg: Vec<u16>,
    bg: Vec<u16>,
    defs: TileDefs,
    np3_art: Np3Art,
    saturn: Vec<u8>,
    art: Vec<(Raster, Raster)>,
}

fn inputs() -> Option<Inputs> {
    let root = repo_root();
    let np3 = root.join("assets/st/np3");
    let disc = root.join("disks/saturn");
    let prg = disc.join("STAGE_01.PRG");
    let map = disc.join("STAGE_01.MAP");
    if !prg.exists() {
        return None;
    }
    let scratch = std::env::temp_dir().join("np3-stitch-test");
    let defs = TileDefs::load(&np3, 2).ok()?;
    let np3_art = Np3Art::load(&root.join("disks/us/ST/NP3/F_NP3.BIN"), &defs).ok()?;
    Some(Inputs {
        fg: u16le(&np3.join("np3_tilemap_2.bin"))?,
        bg: u16le(&np3.join("np3_tilemap_3.bin"))?,
        defs,
        np3_art,
        saturn: stitch::saturn_shaft_collision(&prg, &map, &scratch).ok()?,
        art: stitch::saturn_shaft_art(&prg, &map, &scratch).ok()?,
    })
}

fn build(i: &Inputs) -> stitch::Stitch {
    stitch::build(&i.art, &i.fg, &i.bg, &i.defs, &i.np3_art, &i.saturn, 0x0713).expect("build")
}

#[test]
fn the_versions_share_exactly_the_rows_above_the_stitch_line() {
    let Some(i) = inputs() else { return };
    let hit = |t: u16| i.defs.collision[t as usize];

    let shared = (0..PSX_ROWS)
        .take_while(|&row| (0..16).all(|c| hit(i.fg[row * 16 + c]) == i.saturn[row * 16 + c]))
        .count();
    assert_eq!(shared, STITCH_ROW, "shared prefix moved");
    let row = STITCH_ROW;
    assert!(
        (0..16).any(|c| hit(i.fg[row * 16 + c]) != i.saturn[row * 16 + c]),
        "row {row} still matches; the stitch line could sit lower"
    );
}

#[test]
fn saturn_art_is_almost_entirely_tiles_np3_already_has() {
    let Some(i) = inputs() else { return };
    let built = build(&i);

    let total = built.exact + built.approximate;
    assert!(total > 600, "only {total} tiles below the line");
    let coverage = built.exact as f64 / total as f64;
    assert!(
        coverage > 0.90,
        "only {:.1}% of the new section matched NP3 art exactly",
        coverage * 100.0
    );
    assert_eq!(built.approximate, 0, "the stitch must never guess at art");
    assert!(
        !built.graphics.is_empty(),
        "expected new Saturn arrangements"
    );
    assert!(built
        .graphics
        .iter()
        .all(|graphic| graphic.pixels.len() == 128));
    for tile in &built.minted {
        if tile.from == 0xFFFF {
            assert!(built
                .graphics
                .iter()
                .any(|graphic| { graphic.page == tile.page && graphic.index == tile.index }));
            continue;
        }
        let from = tile.from as usize;
        assert_eq!(tile.page, i.defs.page[from]);
        assert_eq!(tile.index, i.defs.index[from]);
        assert_eq!(tile.clut, i.defs.clut[from]);
        assert_ne!(
            tile.collision, i.defs.collision[from],
            "minted a tile that duplicates one NP3 already has"
        );
    }
}

#[test]
fn the_stitched_shaft_reproduces_saturn_collision() {
    let Some(i) = inputs() else { return };
    let built = build(&i);

    assert_eq!(built.fg.len(), 16 * SATURN_ROWS);
    assert_eq!(built.bg.len(), 16 * SATURN_ROWS);
    stitch::verify(&built, &i.fg, &i.defs, &i.saturn).expect("verify");

    assert_eq!(&built.fg[..16 * STITCH_ROW], &i.fg[..16 * STITCH_ROW]);
    assert_eq!(&built.bg[..16 * STITCH_ROW], &i.bg[..16 * STITCH_ROW]);
}

#[test]
fn every_emitted_tile_is_drawable() {
    let Some(i) = inputs() else { return };
    let built = build(&i);
    let minted: HashMap<u16, ()> = built.minted.iter().map(|t| (t.id, ())).collect();

    for (index, &tile) in built.fg.iter().chain(built.bg.iter()).enumerate() {
        assert!(
            (tile as usize) < stitch::NP3_TILEDEF_ENTRIES,
            "tile {tile} at {index} is past NP3's tile definitions"
        );
        if !minted.contains_key(&tile) {
            assert!((tile as usize) < i.defs.collision.len());
        }
    }
}

#[test]
fn np3_shaft_has_at_least_99_percent_colour_ssim_with_converted_saturn_room_17() {
    let root = repo_root();
    let prg = root.join("disks/saturn/STAGE_01.PRG");
    let map = root.join("disks/saturn/STAGE_01.MAP");
    let tileset = root.join("disks/us/ST/NP3/F_NP3.BIN");
    if !prg.exists() || !map.exists() || !tileset.exists() {
        return;
    }
    let output = std::env::temp_dir()
        .join("sotn-np3-visual-stitch-test")
        .join("np3_stitch.h");
    stitch::stitch_np3(&prg, &map, &root.join("assets/st/np3"), &tileset, &output)
        .expect("Saturn STAGE01 room 17 / PC NP3 shaft must retain at least 99% colour SSIM");
    stitch_preservation::assert_existing_connections_preserved(
        &root.join("assets/st/np3"),
        &output.parent().unwrap().join("assets/np3"),
        "",
        &[1],
    );
    assert!(output.with_file_name("np3-stitch-saturn.png").exists());
    assert!(output.with_file_name("np3-stitch-pc.png").exists());
    assert!(output.with_file_name("np3-stitch-diff.png").exists());
}
