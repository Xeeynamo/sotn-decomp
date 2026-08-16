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
fn rno4_room_5_is_at_least_99_percent_similar_to_saturn_room_4() {
    let root = repo_root();
    let prg = root.join("disks/saturn/RSTAGE09.PRG");
    let map = root.join("disks/saturn/RSTAGE9B.MAP");
    let tileset = root.join("disks/us/ST/RNO4/F_RNO4.BIN");
    if !prg.exists() || !map.exists() || !tileset.exists() {
        return;
    }
    let output = std::env::temp_dir()
        .join("sotn-rno4-visual-stitch-test")
        .join("rno4_stitch.h");
    stitch::stitch_rno4(&prg, &map, &root.join("assets/st/rno4"), &tileset, &output)
        .expect("Saturn RSTAGE9B room 4 / PC RNO4 room 5 must remain at least 99% similar");
    stitch_preservation::assert_existing_connections_preserved(
        &root.join("assets/st/rno4"),
        &output.parent().unwrap().join("assets/rno4"),
        "",
        &[],
    );
    assert!(output.with_file_name("rno4-stitch-saturn.png").exists());
    assert!(output.with_file_name("rno4-stitch-pc.png").exists());
    assert!(output.with_file_name("rno4-stitch-diff.png").exists());
}
