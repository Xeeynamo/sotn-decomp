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
fn rno0_room_0_has_at_least_99_percent_colour_ssim_with_converted_saturn_room_6() {
    let root = repo_root();
    let prg = root.join("disks/saturn/RSTAGE03.PRG");
    let map = root.join("disks/saturn/RSTAGE03.MAP");
    let tileset = root.join("disks/us/ST/RNO0/F_RNO0.BIN");
    if !prg.exists() || !map.exists() || !tileset.exists() {
        return;
    }
    let output = std::env::temp_dir()
        .join("sotn-rno0-visual-stitch-test")
        .join("rno0_stitch.h");
    stitch::stitch_rno0(&prg, &map, &root.join("assets/st/rno0"), &tileset, &output)
        .expect("Saturn RSTAGE03 room 6 / PC RNO0 room 0 must retain at least 99% colour SSIM");
    stitch_preservation::assert_existing_connections_preserved(
        &root.join("assets/st/rno0"),
        &output.parent().unwrap().join("assets/rno0"),
        "",
        &[],
    );
    assert!(output.with_file_name("rno0-stitch-saturn.png").exists());
    assert!(output.with_file_name("rno0-stitch-pc.png").exists());
    assert!(output.with_file_name("rno0-stitch-diff.png").exists());
}
