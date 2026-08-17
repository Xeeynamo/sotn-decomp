use saturn_assets::psx_stage::{read_layout_table, read_rooms, RoomKind};
use std::path::{Path, PathBuf};

fn repo_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR"))
        .ancestors()
        .nth(3)
        .expect("crate is three levels below the repo root")
        .to_path_buf()
}

fn prg(name: &str) -> Option<Vec<u8>> {
    std::fs::read(repo_root().join("disks/saturn").join(name)).ok()
}

fn stage15_layout_ids(rooms: &[saturn_assets::psx_stage::RoomRecord]) -> Vec<usize> {
    let mut ids: Vec<usize> = rooms
        .iter()
        .filter_map(|room| match room.kind {
            RoomKind::Ordinary { layout, .. } => Some(layout as usize),
            _ => None,
        })
        .collect();
    ids.extend([48, 49, 50]);
    ids.dedup();
    ids
}

#[test]
fn stage15_layout_addresses_match_the_former_hardcoded_table() {
    let Some(prg) = prg("STAGE_15.PRG") else {
        return;
    };
    let table = read_layout_table(&prg).expect("layout table");
    let ids = stage15_layout_ids(&read_rooms(&prg).expect("rooms"));

    assert_eq!(ids, [1, 2, 3, 4, 48, 49, 50]);
    let addresses: Vec<u32> = ids.iter().map(|&id| table[id]).collect();
    assert_eq!(
        addresses,
        [
            0x060F_10F8,
            0x060F_1328,
            0x060F_1418,
            0x060F_1468,
            0x060F_0F0E,
            0x060F_0EC8,
            0x060F_0F54,
        ]
    );
}

#[test]
fn saturn_stages_share_one_room_record_format() {
    for name in [
        "STAGE_01.PRG",
        "STAGE_02.PRG",
        "STAGE_15.PRG",
        "STAGE_16.PRG",
    ] {
        let Some(prg) = prg(name) else {
            continue;
        };
        let table = read_layout_table(&prg).expect("layout table");
        assert_eq!(table.len(), 53, "{name} layout table width");

        let rooms = read_rooms(&prg).expect("rooms");
        assert!(!rooms.is_empty(), "{name} has no rooms");
        for room in &rooms {
            if let RoomKind::Ordinary { layout, .. } = room.kind {
                assert!(
                    (layout as usize) < table.len(),
                    "{name} layout id {layout} is past the pointer table"
                );
            }
        }
    }
}

#[test]
fn stage01_carries_the_saturn_only_entrance_rooms() {
    let Some(prg) = prg("STAGE_01.PRG") else {
        return;
    };
    let rooms = read_rooms(&prg).expect("rooms");
    assert_eq!(rooms.len(), 32);

    let bounds: Vec<(u8, u8, u8, u8)> = rooms
        .iter()
        .map(|r| (r.bounds.left, r.bounds.top, r.bounds.right, r.bounds.bottom))
        .collect();
    assert_eq!(bounds[17], (2, 41, 2, 44));
    assert_eq!(bounds[24], (3, 44, 3, 44));
    assert!(matches!(rooms[24].kind, RoomKind::Special { .. }));

    let loading: Vec<_> = rooms
        .iter()
        .filter(|r| matches!(r.kind, RoomKind::Loading { .. }))
        .map(|r| (r.bounds.left, r.bounds.top))
        .collect();
    assert_eq!(loading, [(15, 38), (16, 36), (21, 36), (16, 41), (4, 44)]);
}
