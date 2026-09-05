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
fn no4_room_dump_has_at_least_99_percent_colour_ssim_with_saturn() {
    let root = repo_root();
    let saturn = root.join("disks/saturn");
    let prg = saturn.join("STAGE_09.PRG");
    let map = saturn.join("STAGE_9B.MAP");
    let tileset = root.join("disks/us/ST/NO4/F_NO4.BIN");
    if !prg.exists() || !map.exists() || !tileset.exists() {
        return;
    }
    let output = std::env::temp_dir()
        .join("sotn-no4-visual-stitch-test")
        .join("no4_stitch.h");
    stitch::stitch_no4(&prg, &map, &root.join("assets/st/no4"), &tileset, &output)
        .expect("Saturn/PC NO4 visual stitch must retain at least 99% colour SSIM");
    stitch_preservation::assert_existing_connections_preserved(
        &root.join("assets/st/no4"),
        &output.parent().unwrap().join("assets/no4"),
        "",
        &[],
    );
    assert!(output.with_file_name("no4-stitch-saturn.png").exists());
    assert!(output.with_file_name("no4-stitch-pc.png").exists());
    assert!(output.with_file_name("no4-stitch-diff.png").exists());
}
