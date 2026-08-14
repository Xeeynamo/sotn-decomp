#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <game.h>

#ifndef STAGE15_ASSET_DIR
#error "STAGE15_ASSET_DIR must name the converted asset directory"
#endif

void InitStage(Overlay* overlay);

enum TransitionEdge {
    EDGE_LEFT,
    EDGE_RIGHT,
};

enum Stage15Room {
    ROOM_LARGE,
    ROOM_GARDEN,
    ROOM_BOSS,
    ROOM_GARDEN_2,
    ROOM_CD_TOP,
    ROOM_CD_BOTTOM,
    ROOM_SAVE,
};

static int FindRoom(const RoomHeader* rooms, u8 x, u8 y) {
    for (int room = 0; rooms[room].left != 0x40; room++) {
        const RoomHeader* current = &rooms[room];
        if (x >= current->left && x <= current->right &&
            y >= current->top && y <= current->bottom) {
            return room;
        }
    }
    return -1;
}

static int RoomTileWidth(const RoomHeader* room) {
    return (room->right - room->left + 1) * 16;
}

static u8 CollisionAt(const RoomDef* layers, const RoomHeader* rooms,
                      int room, int tileX, int tileY) {
    const LayerDef* fg = layers[room].fg;
    int width = RoomTileWidth(&rooms[room]);
    u16 tile = fg->layout[tileY * width + tileX];
    return fg->tileDef->collision[tile];
}

static void ExpectTransition(const RoomHeader* rooms, const RoomDef* layers,
                             int from, int to, enum TransitionEdge edge,
                             u8 worldY) {
    const RoomHeader* source = &rooms[from];
    const RoomHeader* target = &rooms[to];
    int sourceColumn;
    int sourceRow;
    int targetColumn;
    int targetRow;
    u8 queryX;

    assert(from != to);
    assert(worldY >= source->top && worldY <= source->bottom);
    if (edge == EDGE_RIGHT) {
        queryX = source->right + 1;
        sourceColumn = RoomTileWidth(source) - 1;
        targetColumn = 0;
    } else {
        queryX = source->left - 1;
        sourceColumn = 0;
        targetColumn = RoomTileWidth(target) - 1;
    }
    assert(FindRoom(rooms, queryX, worldY) == to);

    sourceRow = (worldY - source->top) * 16;
    targetRow = (worldY - target->top) * 16;
    for (int row = 6; row <= 9; row++) {
        assert(!(CollisionAt(layers, rooms, from, sourceColumn,
                             sourceRow + row) & EFFECT_SOLID));
        assert(!(CollisionAt(layers, rooms, to, targetColumn,
                             targetRow + row) & EFFECT_SOLID));
    }

}

int main(void) {
    Overlay overlay;
    InitStage(&overlay);
    RoomHeader* rooms = overlay.rooms;
    RoomDef* layers = overlay.tileLayers;
    assert(rooms != NULL);
    assert(layers != NULL);
    assert(overlay.Update != NULL);
    assert(overlay.InitRoomEntities != NULL);
    assert(overlay.UpdateStageEntities != NULL);

    for (int room = 0; room < 4; room++) {
        assert(layers[room].fg != NULL);
        assert(layers[room].fg->layout != NULL);
        assert(layers[room].fg->tileDef != NULL);
        assert(layers[room].fg->flags & LAYER_SHOW);
        assert(layers[room].bg != NULL);
        assert(layers[room].bg->layout != NULL);
    }

    ExpectTransition(rooms, layers, ROOM_LARGE, ROOM_CD_TOP, EDGE_LEFT, 44);
    ExpectTransition(rooms, layers, ROOM_LARGE, ROOM_CD_BOTTOM, EDGE_LEFT,
                     45);
    ExpectTransition(rooms, layers, ROOM_LARGE, ROOM_SAVE, EDGE_RIGHT, 45);
    ExpectTransition(rooms, layers, ROOM_LARGE, ROOM_GARDEN, EDGE_RIGHT, 44);
    ExpectTransition(rooms, layers, ROOM_GARDEN, ROOM_LARGE, EDGE_LEFT, 44);
    ExpectTransition(rooms, layers, ROOM_GARDEN, ROOM_GARDEN_2, EDGE_RIGHT,
                     44);
    ExpectTransition(rooms, layers, ROOM_GARDEN_2, ROOM_GARDEN, EDGE_LEFT,
                     44);
    ExpectTransition(rooms, layers, ROOM_GARDEN_2, ROOM_BOSS, EDGE_RIGHT, 44);
    ExpectTransition(rooms, layers, ROOM_BOSS, ROOM_GARDEN_2, EDGE_LEFT, 44);

    ExpectTransition(rooms, layers, ROOM_CD_TOP, ROOM_LARGE, EDGE_RIGHT, 44);
    ExpectTransition(rooms, layers, ROOM_CD_BOTTOM, ROOM_LARGE, EDGE_RIGHT,
                     45);
    ExpectTransition(rooms, layers, ROOM_SAVE, ROOM_LARGE, EDGE_LEFT, 45);
    assert(layers[4].fg->rect.params == 0x10);
    assert(layers[5].fg->rect.params == 0x10);
    assert(layers[6].fg->rect.params == 0x22);
    {
        int leftVisible = 0;
        int rightVisible = 0;
        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 3; x++) {
                leftVisible += layers[6].fg->layout[y * 16 + x] != 0;
                rightVisible +=
                    layers[6].fg->layout[y * 16 + (15 - x)] != 0;
            }
        }
        assert(leftVisible >= 2 * 3);
        assert(rightVisible >= 6 * 3);
    }
    for (int room = 4; room <= 6; room++) {
        assert(layers[room].bg != NULL);
        assert(layers[room].bg->layout != NULL);
        int visible = 0;
        for (int tile = 0; tile < 16 * 16; tile++) {
            visible |= layers[room].fg->layout[tile] != 0;
            visible |= layers[room].bg->layout[tile] != 0;
        }
        assert(visible);
        assert(layers[room].fg->zPriority == 0xA0);
        for (int tileY = 0; tileY < 16; tileY++) {
            for (int tileX = 0; tileX < 16; tileX++) {
                u16 tile = layers[room].fg->layout[tileY * 16 + tileX];
                u8 hit = layers[room].fg->tileDef->collision[tile];
                if (room != 6) {
                    assert(hit ==
                           ((tileY <= 5 || tileY >= 10) ? 3 : 0));
                } else if (tileY <= 1 || tileY >= 12) {
                    assert(hit == 3);
                } else if (tileY >= 6 && tileY <= 9) {
                    assert(hit == 0);
                } else if (tileY == 10 || tileY == 11) {
                    assert(hit ==
                           ((tileX < 3 || tileX >= 13) ? 3 : 0));
                }
            }
        }
        {
            static const u8 slopeChecks[][3] = {
                {2, 5, 0x91}, {2, 10, 0x90}, {3, 3, 0x86},
                {3, 4, 0x92}, {3, 5, 0x93},  {3, 10, 0x8E},
                {3, 11, 0x8F}, {3, 12, 0x85}, {4, 3, 0x87},
                {4, 12, 0x84},
            };
            for (int i = 0; i < LEN(slopeChecks); i++) {
                int y = slopeChecks[i][0];
                int x = slopeChecks[i][1];
                u16 tile = layers[6].fg->layout[y * 16 + x];
                assert(layers[6].fg->tileDef->collision[tile] ==
                       slopeChecks[i][2]);
            }
        }
    }

    assert(FindRoom(rooms, 2, 44) == -1);
    assert(FindRoom(rooms, 2, 45) == -1);
    assert(FindRoom(rooms, 22, 44) == -1);
    assert(FindRoom(rooms, 4, 43) == -1);
    assert(FindRoom(rooms, 4, 46) == -1);

    assert(rooms[10].left == rooms[0].left);
    assert(rooms[10].top == rooms[0].top);
    assert(rooms[10].right == rooms[0].right);
    assert(rooms[10].bottom == rooms[0].bottom);
    assert(rooms[10].load.tileLayoutId == rooms[0].load.tileLayoutId);
    assert(rooms[10].load.objLayoutId == rooms[0].load.objLayoutId);
    assert(rooms[20].left == rooms[0].left);
    assert(rooms[20].top == rooms[0].top);

    for (int room = 0; rooms[room].left != 0x40; room++) {
        assert(rooms[room].load.tilesetId != 0xFF);
    }
    return 0;
}
