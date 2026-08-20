use serde_json::Value;
use std::collections::BTreeMap;
use std::path::{Path, PathBuf};

fn json(path: &Path) -> Value {
    serde_json::from_slice(&std::fs::read(path).unwrap()).unwrap()
}

fn entity_layouts(root: &Path) -> PathBuf {
    for relative in ["entity_layouts.json", "us/entity_layouts.json"] {
        let path = root.join(relative);
        if path.exists() {
            return path;
        }
    }
    panic!("{} has no entity layouts", root.display());
}

fn loading_room_indices(rooms: &[Value], layers: &[Value]) -> Vec<usize> {
    rooms
        .iter()
        .enumerate()
        .filter_map(|(index, room)| {
            let layer = layers.get(room["layerId"].as_u64().unwrap() as usize)?;
            ["fg", "bg"]
                .iter()
                .any(|side| layer[*side]["isLoadingRoom"].as_bool() == Some(true))
                .then_some(index)
        })
        .collect()
}

fn existing_door_positions(root: &Path, data_dir: &str) -> BTreeMap<usize, Vec<(i64, i64, Value)>> {
    let rooms = json(&root.join(data_dir).join("rooms.json"));
    let layouts = json(&entity_layouts(root));
    let rooms = rooms.as_array().unwrap();
    let indices = layouts["indices"].as_array().unwrap();
    let entities = layouts["entities"].as_array().unwrap();
    rooms
        .iter()
        .enumerate()
        .filter_map(|(room_index, room)| {
            let layout = room["entityLayoutId"].as_u64().unwrap() as usize;
            let bank = indices.get(layout)?.as_u64().unwrap() as usize;
            let doors = entities[bank]
                .as_array()
                .unwrap()
                .iter()
                .filter(|entity| entity["id"] == "E_RED_DOOR")
                .map(|entity| {
                    let mut identity = entity.clone();
                    identity.as_object_mut().unwrap().remove("x");
                    identity.as_object_mut().unwrap().remove("y");
                    (
                        room["left"].as_i64().unwrap() * 256 + entity["x"].as_i64().unwrap(),
                        room["top"].as_i64().unwrap() * 256 + entity["y"].as_i64().unwrap(),
                        identity,
                    )
                })
                .collect::<Vec<_>>();
            (!doors.is_empty()).then_some((room_index, doors))
        })
        .collect()
}

pub fn assert_existing_connections_preserved(
    source: &Path,
    output: &Path,
    data_dir: &str,
    resized_rooms: &[usize],
) {
    let source_rooms = json(&source.join(data_dir).join("rooms.json"));
    let source_layers = json(&source.join(data_dir).join("layers.json"));
    let output_rooms = json(&output.join(data_dir).join("rooms.json"));
    let output_layers = json(&output.join(data_dir).join("layers.json"));
    let source_rooms = source_rooms.as_array().unwrap();
    let source_layers = source_layers.as_array().unwrap();
    let output_rooms = output_rooms.as_array().unwrap();
    let output_layers = output_layers.as_array().unwrap();

    for (room_index, source_room) in source_rooms.iter().enumerate() {
        if !resized_rooms.contains(&room_index) {
            assert_eq!(
                output_rooms[room_index], *source_room,
                "existing room {room_index} changed"
            );
        }
    }

    for room_index in loading_room_indices(source_rooms, source_layers) {
        assert_eq!(
            output_rooms[room_index], source_rooms[room_index],
            "existing CD/loading room {room_index} moved"
        );
        let layer = source_rooms[room_index]["layerId"].as_u64().unwrap() as usize;
        assert_eq!(
            output_layers[layer], source_layers[layer],
            "existing CD/loading room {room_index}'s layer changed"
        );
    }

    let before = existing_door_positions(source, data_dir);
    let after = existing_door_positions(output, data_dir);
    for (room, doors) in before {
        let output_doors = after
            .get(&room)
            .unwrap_or_else(|| panic!("room {room} lost all of its existing red doors"));
        for door in doors {
            assert!(
                output_doors.contains(&door),
                "existing red door in room {room} moved or changed"
            );
        }
    }
}
