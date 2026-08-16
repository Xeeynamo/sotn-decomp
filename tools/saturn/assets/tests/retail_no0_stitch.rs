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
fn no0_room_0_has_at_least_99_percent_colour_ssim_with_converted_saturn_room_6() {
    let root = repo_root();
    let prg = root.join("disks/saturn/STAGE_03.PRG");
    let map = root.join("disks/saturn/STAGE_03.MAP");
    let tileset = root.join("disks/us/ST/NO0/F_NO0.BIN");
    if !prg.exists() || !map.exists() || !tileset.exists() {
        return;
    }
    let output = std::env::temp_dir()
        .join("sotn-no0-visual-stitch-test")
        .join("no0_stitch.h");
    stitch::stitch_no0(&prg, &map, &root.join("assets/st/no0"), &tileset, &output)
        .expect("Saturn STAGE03 room 6 / PC NO0 room 0 must retain at least 99% colour SSIM");
    stitch_preservation::assert_existing_connections_preserved(
        &root.join("assets/st/no0"),
        &output.parent().unwrap().join("assets/no0"),
        "",
        &[],
    );
    assert!(output.with_file_name("no0-stitch-saturn.png").exists());
    assert!(output.with_file_name("no0-stitch-pc.png").exists());
    assert!(output.with_file_name("no0-stitch-diff.png").exists());
}
