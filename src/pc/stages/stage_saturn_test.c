// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <game.h>

void Psyz_ModuleStart(void* param);

enum TransitionEdge {
    EDGE_LEFT,
    EDGE_RIGHT,
};

typedef struct {
    u8 from;
    u8 to;
    u8 edge;
    u8 worldY;
} Transition;

typedef struct {
    u8 room;
    u8 params;
    u8 triggerX;
    u8 triggerY;
    u8 teleport;
} Exit;

#if defined(TEST_STAGE15)
enum { LARGE, GARDEN, BOSS, GARDEN_2, CD_TOP, CD_BOTTOM, SAVE, ROOM_COUNT };
static const Transition s_Transitions[] = {
    {LARGE, CD_TOP, EDGE_LEFT, 44},     {LARGE, CD_BOTTOM, EDGE_LEFT, 45},
    {LARGE, SAVE, EDGE_RIGHT, 45},      {LARGE, GARDEN, EDGE_RIGHT, 44},
    {GARDEN, LARGE, EDGE_LEFT, 44},     {GARDEN, GARDEN_2, EDGE_RIGHT, 44},
    {GARDEN_2, GARDEN, EDGE_LEFT, 44},  {GARDEN_2, BOSS, EDGE_RIGHT, 44},
    {BOSS, GARDEN_2, EDGE_LEFT, 44},    {CD_TOP, LARGE, EDGE_RIGHT, 44},
    {CD_BOTTOM, LARGE, EDGE_RIGHT, 45}, {SAVE, LARGE, EDGE_LEFT, 45},
};
static const Exit s_Exits[] = {{CD_TOP, 0x40, 2, 44, 137}};
static const u8 s_InertCdRoom = CD_BOTTOM;
#define SAVE_PARAMS 0x22
#elif defined(TEST_STAGE16)
enum { LARGE, CORRIDOR, CD_NO0, CD_NO4, SAVE, ROOM_COUNT };
static const Transition s_Transitions[] = {
    {LARGE, CORRIDOR, EDGE_LEFT, 36},  {CORRIDOR, LARGE, EDGE_RIGHT, 36},
    {CORRIDOR, CD_NO0, EDGE_LEFT, 36}, {CD_NO0, CORRIDOR, EDGE_RIGHT, 36},
    {LARGE, CD_NO4, EDGE_RIGHT, 34},   {CD_NO4, LARGE, EDGE_LEFT, 34},
    {LARGE, SAVE, EDGE_LEFT, 34},      {SAVE, LARGE, EDGE_RIGHT, 34},
};
static const Exit s_Exits[] = {
    {CD_NO0, 0x40, 26, 36, 138},
    {CD_NO4, 0x41, 37, 34, 139},
};
#define SAVE_PARAMS 0x20
#elif defined(TEST_RSTAGE15)
enum { LARGE, GARDEN, BOSS, GARDEN_2, CD_TOP, CD_BOTTOM, SAVE, ROOM_COUNT };
static const Transition s_Transitions[] = {
    {LARGE, CD_TOP, EDGE_RIGHT, 18},    {LARGE, CD_BOTTOM, EDGE_RIGHT, 19},
    {LARGE, SAVE, EDGE_LEFT, 18},       {LARGE, GARDEN, EDGE_LEFT, 19},
    {GARDEN, LARGE, EDGE_RIGHT, 19},    {GARDEN, GARDEN_2, EDGE_LEFT, 19},
    {GARDEN_2, GARDEN, EDGE_RIGHT, 19}, {GARDEN_2, BOSS, EDGE_LEFT, 19},
    {BOSS, GARDEN_2, EDGE_RIGHT, 19},   {CD_TOP, LARGE, EDGE_LEFT, 18},
    {CD_BOTTOM, LARGE, EDGE_LEFT, 19},  {SAVE, LARGE, EDGE_RIGHT, 18},
};
static const Exit s_Exits[] = {{CD_BOTTOM, 0x41, 61, 19, 137}};
static const u8 s_InertCdRoom = CD_TOP;
#define SAVE_PARAMS 0x22
#define REVERSE_SAVE_ROOM
#elif defined(TEST_RSTAGE16)
enum { LARGE, CORRIDOR, CD_NO4, CD_NO0, SAVE, ROOM_COUNT };
static const Transition s_Transitions[] = {
    {LARGE, CORRIDOR, EDGE_RIGHT, 27},  {CORRIDOR, LARGE, EDGE_LEFT, 27},
    {CORRIDOR, CD_NO0, EDGE_RIGHT, 27}, {CD_NO0, CORRIDOR, EDGE_LEFT, 27},
    {LARGE, CD_NO4, EDGE_LEFT, 29},     {CD_NO4, LARGE, EDGE_RIGHT, 29},
    {LARGE, SAVE, EDGE_RIGHT, 29},      {SAVE, LARGE, EDGE_LEFT, 29},
};
static const Exit s_Exits[] = {
    {CD_NO4, 0x40, 26, 29, 139},
    {CD_NO0, 0x41, 37, 27, 138},
};
#define SAVE_PARAMS 0x20
#define REVERSE_SAVE_ROOM
#else
#error "select a stage with TEST_STAGE15, TEST_STAGE16, ..."
#endif

static int FindRoom(const RoomHeader* rooms, u8 x, u8 y) {
    for (int room = 0; rooms[room].left != 0x40; room++) {
        const RoomHeader* current = &rooms[room];
        if (x >= current->left && x <= current->right && y >= current->top &&
            y <= current->bottom) {
            return room;
        }
    }
    return -1;
}

static int RoomTileWidth(const RoomHeader* room) {
    return (room->right - room->left + 1) * 16;
}

static u8 CollisionAt(const RoomDef* layers, const RoomHeader* rooms, int room,
                      int tileX, int tileY) {
    const LayerDef* fg = layers[room].fg;
    u16 tile = fg->layout[tileY * RoomTileWidth(&rooms[room]) + tileX];
    return fg->tileDef->collision[tile];
}

static void ExpectTransition(
    const RoomHeader* rooms, const RoomDef* layers, const Transition* t) {
    const RoomHeader* source = &rooms[t->from];
    const RoomHeader* target = &rooms[t->to];
    int sourceColumn;
    int targetColumn;
    u8 queryX;

    assert(t->from != t->to);
    assert(t->worldY >= source->top && t->worldY <= source->bottom);
    if (t->edge == EDGE_RIGHT) {
        queryX = source->right + 1;
        sourceColumn = RoomTileWidth(source) - 1;
        targetColumn = 0;
    } else {
        queryX = source->left - 1;
        sourceColumn = 0;
        targetColumn = RoomTileWidth(target) - 1;
    }
    assert(FindRoom(rooms, queryX, t->worldY) == t->to);

    int sourceRow = (t->worldY - source->top) * 16;
    int targetRow = (t->worldY - target->top) * 16;
    for (int row = 6; row <= 9; row++) {
        assert(!(
            CollisionAt(layers, rooms, t->from, sourceColumn, sourceRow + row) &
            EFFECT_SOLID));
        assert(
            !(CollisionAt(layers, rooms, t->to, targetColumn, targetRow + row) &
              EFFECT_SOLID));
    }
}

int main(void) {
    Overlay overlay;
    Psyz_ModuleStart(&overlay);
    RoomHeader* rooms = overlay.rooms;
    RoomDef* layers = overlay.tileLayers;
    assert(rooms != NULL);
    assert(layers != NULL);
    assert(overlay.Update != NULL);
    assert(overlay.InitRoomEntities != NULL);
    assert(overlay.UpdateStageEntities != NULL);

    for (int room = 0; room < ROOM_COUNT; room++) {
        assert(layers[room].fg != NULL);
        assert(layers[room].fg->layout != NULL);
        assert(layers[room].fg->tileDef != NULL);
        assert(layers[room].fg->flags & LAYER_SHOW);
        assert(layers[room].bg != NULL);
        assert(layers[room].bg->layout != NULL);
    }

    for (int i = 0; i < LEN(s_Transitions); i++) {
        ExpectTransition(rooms, layers, &s_Transitions[i]);
    }

    for (int i = 0; i < LEN(s_Exits); i++) {
        const Exit* exit = &s_Exits[i];
        int trigger = FindRoom(rooms, exit->triggerX, exit->triggerY);
        assert(trigger >= 0);
        assert(rooms[trigger].load.tilesetId == 0xFF);
        assert(rooms[trigger].load.tileLayoutId == exit->teleport);
        assert(layers[exit->room].fg->rect.params == exit->params);
        assert(layers[exit->room].fg->zPriority == exit->teleport);
        assert(FindRoom(rooms, exit->triggerX + (exit->params & 1 ? -1 : 1),
                        exit->triggerY) == exit->room);
    }
#ifdef TEST_STAGE15
    assert(layers[s_InertCdRoom].fg->rect.params == 0x10);
    assert(FindRoom(rooms, 2, 45) == -1);
#endif
#ifdef TEST_RSTAGE15
    assert(layers[s_InertCdRoom].fg->rect.params == 0x10);
    assert(FindRoom(rooms, 61, 18) == -1);
#endif

    assert(layers[SAVE].fg->rect.params == SAVE_PARAMS);
    assert(layers[SAVE].fg->zPriority == 0xA0);
    for (int tileY = 0; tileY < 16; tileY++) {
        for (int tileX = 0; tileX < 16; tileX++) {
            u16 tile = layers[SAVE].fg->layout[tileY * 16 + tileX];
            u8 hit = layers[SAVE].fg->tileDef->collision[tile];
#ifdef REVERSE_SAVE_ROOM
            if (tileY <= 3 || tileY >= 14) {
                assert(hit == 3);
            } else if (tileY >= 6 && tileY <= 9) {
                assert(hit == 0);
            } else if (tileY == 4 || tileY == 5 || tileY == 10) {
                assert(hit == ((tileX < 3 || tileX >= 13) ? 3 : 0));
            }
#else
            if (tileY <= 1 || tileY >= 12) {
                assert(hit == 3);
            } else if (tileY >= 6 && tileY <= 9) {
                assert(hit == 0);
            } else if (tileY == 10 || tileY == 11) {
                assert(hit == ((tileX < 3 || tileX >= 13) ? 3 : 0));
            }
#endif
        }
    }

    for (int room = 0; room < ROOM_COUNT; room++) {
        int width = RoomTileWidth(&rooms[room]);
        int height = (rooms[room].bottom - rooms[room].top + 1) * 16;
        int visible = 0;
        for (int tile = 0; tile < width * height; tile++) {
            visible |= layers[room].fg->layout[tile] != 0;
            visible |= layers[room].bg->layout[tile] != 0;
        }
        assert(visible);
    }

    assert(rooms[10].left == rooms[0].left);
    assert(rooms[10].top == rooms[0].top);
    assert(rooms[10].load.tileLayoutId == rooms[0].load.tileLayoutId);
    assert(rooms[10].load.objLayoutId == rooms[0].load.objLayoutId);
    assert(rooms[20].left == rooms[0].left);
    assert(rooms[20].top == rooms[0].top);
    return 0;
}
