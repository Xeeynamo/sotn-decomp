use saturn_assets::stitch;
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

#[test]
fn rno3_room_1_has_at_least_99_percent_colour_ssim_with_saturn_room_17() {
    let root = repo_root();
    let prg = root.join("disks/saturn/RSTAGE01.PRG");
    let map = root.join("disks/saturn/RSTAGE01.MAP");
    let tileset = root.join("disks/us/ST/RNO3/F_RNO3.BIN");
    if !prg.exists() || !map.exists() || !tileset.exists() {
        return;
    }
    let output = std::env::temp_dir()
        .join("sotn-rno3-visual-stitch-test")
        .join("rno3_stitch.h");
    stitch::stitch_rno3(&prg, &map, &root.join("assets/st/rno3"), &tileset, &output)
        .expect("Saturn RSTAGE01 room 17 / PC RNO3 room 1 must retain at least 99% colour SSIM");
    stitch_preservation::assert_existing_connections_preserved(
        &root.join("assets/st/rno3"),
        &output.parent().unwrap().join("assets/rno3"),
        "us",
        &[1],
    );
    assert!(output.with_file_name("rno3-stitch-saturn.png").exists());
    assert!(output.with_file_name("rno3-stitch-pc.png").exists());
    assert!(output.with_file_name("rno3-stitch-diff.png").exists());
}
