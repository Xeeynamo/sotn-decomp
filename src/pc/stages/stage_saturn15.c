// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef STAGE15_ROOM_TEST
#include <psyz/cd.h>
#include "music/xa_config.h"
#endif
#include "overlay.h"

#ifndef STAGE15_ASSET_DIR
#define STAGE15_ASSET_DIR "stage15_assets"
#endif

#include "stage15_data.h"

static SpriteParts* s_SpriteBanks[] = {NULL};
static u_long s_EmptyClut[] = {(u_long)-1};
static u_long* s_Cluts[] = {s_EmptyClut};
static GfxBank s_EmptyGfxBank = {.kind = GFX_BANK_NONE};
static GfxBank* s_GfxBanks[] = {&s_EmptyGfxBank};
static RoomDef* s_TileLayers;
static LayoutEntity* s_CurrentLayout;
static size_t s_CurrentLayoutCount;
static const u8 s_Stage15RoomBounds[7][4] = {
    {4, 44, 12, 45}, {13, 44, 16, 44}, {21, 44, 21, 44}, {17, 44, 20, 44},
    {3, 44, 3, 44},  {3, 45, 3, 45},   {13, 45, 13, 45},
};

static void Noop(void) {}

#ifndef STAGE15_ROOM_TEST
#define STAGE15_BACKDROP_ENTITY (TOTAL_ENTITY_COUNT - 1)
#define STAGE15_MASONRY_CLUT_SLOT 0x1FF
static void EntityStage15Backdrop(Entity* self);
static void EntityStage15Masonry(Entity* self);

#define STAGE15_MASONRY_PIXEL_BYTES (24 * 16 / 2)
#define STAGE15_MASONRY_PALETTE_WORDS 16
static u8 s_Stage15MasonryPixels[STAGE15_MASONRY_PIXEL_BYTES]
    __attribute__((aligned(4)));
static u16 s_Stage15MasonryPalette[STAGE15_MASONRY_PALETTE_WORDS];
static u16 s_Stage15MasonryTpage;
static bool s_Stage15MasonryReady;

static bool Stage15LoadMasonry(void) {
    s32 length;

    length = FileReadToBuf(
        STAGE15_ASSET_DIR "/stage15_masonry.chars.bin", s_Stage15MasonryPixels,
        0, sizeof(s_Stage15MasonryPixels));
    if (length != sizeof(s_Stage15MasonryPixels)) {
        return false;
    }
    length = FileReadToBuf(
        STAGE15_ASSET_DIR "/stage15_masonry.pal.bin", s_Stage15MasonryPalette,
        0, sizeof(s_Stage15MasonryPalette));
    return length == sizeof(s_Stage15MasonryPalette);
}

#ifndef STAGE15_ROOM_TEST
extern s32 g_CurCdPos;
extern XaMusicConfig g_XaMusicConfigs[];

static void Stage15ConfigureMusic(void) {
    XaMusicConfig* start = &g_XaMusicConfigs[MU_STAGE15 - 0x300];
    XaMusicConfig* loop = &g_XaMusicConfigs[MU_STAGE15_LOOP_POINT - 0x300];
    u32 base = 0U - (u32)g_CurCdPos;

    Psyz_CdSetDiskPath(STAGE15_ASSET_DIR "/music/audio.cue");
    *start = (XaMusicConfig){
        base,
        SATURN_XA_INTRO_VSYNC,
        SATURN_XA_FILE_NUMBER,
        SATURN_XA_CHANNEL,
        80,
        0,
        1};
    *loop = (XaMusicConfig){
        base + SATURN_XA_LOOP_SECTOR,
        SATURN_XA_LOOP_VSYNC,
        SATURN_XA_FILE_NUMBER,
        SATURN_XA_CHANNEL,
        80,
        0,
        0};
}
#endif

#ifdef STAGE15_ENTITY_LABELS
static void Stage15DrawEntityLabels(void) {
    LayoutEntity* layout;
    DR_MODE* drawMode;
    SPRT* sprite;
    TILE* tile;
    char label[24];
    const char* character;
    s32 characterIndex;
    s32 labelLength;
    s32 layoutIndex;
    s32 screenX;
    s32 screenY;
    s32 tpage;

    if (s_CurrentLayout == NULL || g_GpuUsage.drawModes >= MAX_DRAW_MODES) {
        return;
    }

    tpage = getTPage(0, 0, 0x380, 0x100);
    drawMode = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];
    SetDrawMode(drawMode, 0, 0, tpage, NULL);

    for (layoutIndex = 0; layoutIndex < s_CurrentLayoutCount; layoutIndex++) {
        layout = &s_CurrentLayout[layoutIndex];
        screenX = layout->posX - g_Tilemap.scrollX.i.hi;
        screenY = layout->posY - g_Tilemap.scrollY.i.hi;
        if (screenX < -32 || screenX >= DISP_STAGE_W + 32 || screenY < -16 ||
            screenY >= DISP_STAGE_H + 16) {
            continue;
        }

        labelLength = snprintf(label, sizeof(label), "%d:%d",
                               layout->entityId & 0x3FF, layout->params);
        if (labelLength <= 0) {
            continue;
        }

        if (g_GpuUsage.tile + 3 <= MAX_TILE_COUNT) {
            tile = &g_CurrentBuffer->tiles[g_GpuUsage.tile++];
            SetTile(tile);
            SetSemiTrans(tile, false);
            setRGB0(tile, 0, 0, 0);
            setXY0(
                tile, screenX + g_backbufferX + 3, screenY + g_backbufferY - 5);
            setWH(tile, labelLength * 8 + 2, 10);
            AddPrim(&g_CurrentBuffer->ot[0x1EF], tile);

            tile = &g_CurrentBuffer->tiles[g_GpuUsage.tile++];
            SetTile(tile);
            SetSemiTrans(tile, false);
            setRGB0(tile, 255, 64, 64);
            setXY0(tile, screenX + g_backbufferX - 3, screenY + g_backbufferY);
            setWH(tile, 7, 1);
            AddPrim(&g_CurrentBuffer->ot[0x1F0], tile);

            tile = &g_CurrentBuffer->tiles[g_GpuUsage.tile++];
            SetTile(tile);
            SetSemiTrans(tile, false);
            setRGB0(tile, 255, 64, 64);
            setXY0(tile, screenX + g_backbufferX, screenY + g_backbufferY - 3);
            setWH(tile, 1, 7);
            AddPrim(&g_CurrentBuffer->ot[0x1F0], tile);
        }

        for (character = label; *character != '\0'; character++) {
            if (g_GpuUsage.sp >= MAX_SPRT_COUNT) {
                break;
            }
            characterIndex = (u8)*character - 0x20;
            sprite = &g_CurrentBuffer->sprite[g_GpuUsage.sp++];
            SetSprt8(sprite);
            SetSemiTrans(sprite, false);
            SetShadeTex(sprite, true);
            setRGB0(sprite, 128, 128, 128);
            sprite->x0 = screenX + 4 + (character - label) * 8 + g_backbufferX;
            sprite->y0 = screenY - 4 + g_backbufferY;
            sprite->u0 = (characterIndex & 0xF) * 8;
            sprite->v0 = (characterIndex >> 4) * 8;
            sprite->clut = getClut(0x380, 0x180);
            AddPrim(&g_CurrentBuffer->ot[0x1F0], sprite);
        }
    }

    AddPrim(&g_CurrentBuffer->ot[0x1F0], drawMode);
    g_GpuUsage.drawModes++;
}
#endif

static s32 Stage15CurrentRoom(void) {
    s32 room;

    for (room = 0; room < LEN(s_Stage15RoomBounds); room++) {
        if (g_Tilemap.left == s_Stage15RoomBounds[room][0] &&
            g_Tilemap.top == s_Stage15RoomBounds[room][1] &&
            g_Tilemap.right == s_Stage15RoomBounds[room][2] &&
            g_Tilemap.bottom == s_Stage15RoomBounds[room][3]) {
            return room;
        }
    }
    return -1;
}

EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 3};
u16 g_RedDoorTiles[2][8];
static u16 s_Stage15RedDoorTiles[32];
static Tilemap s_Stage15RedDoorTilemap = {
    .fg = &s_Stage15RedDoorTiles[4],
    .hSize = 0,
};

static u8 Stage15DoorSideToPlayer(Entity* self) {
    u8 side = 0;
    if (self->posX.i.hi > PLAYER.posX.i.hi) {
        side |= 1;
    }
    if (self->posY.i.hi > PLAYER.posY.i.hi) {
        side |= 2;
    }
    return side;
}

static void Stage15InitializeDoor(Entity* self) {
    u16* init = g_EInitCommon;
    EnemyDef* enemy;

    self->animSet = *init++;
    self->animCurFrame = *init++;
    self->unk5A = *init++;
    self->palette = *init++;
    self->enemyId = *init++;
    enemy = &g_api.enemyDefs[self->enemyId];
    self->hitPoints = enemy->hitPoints;
    self->attack = enemy->attack;
    self->attackElement = enemy->attackElement;
    self->hitboxState = enemy->hitboxState;
    self->hitboxWidth = enemy->hitboxWidth;
    self->hitboxHeight = enemy->hitboxHeight;
    self->flags = enemy->flags;
    self->hitboxOffX = 0;
    self->hitboxOffY = 0;
    self->step++;
    self->step_s = 0;
    if (!self->zPriority) {
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0xC;
    }
}

#define InitializeEntity(init) Stage15InitializeDoor(self)
#define GetSideToPlayer() Stage15DoorSideToPlayer(self)
#define g_Tilemap s_Stage15RedDoorTilemap
#include "../../st/e_red_door.h"
#undef g_Tilemap
#undef GetSideToPlayer
#undef InitializeEntity

static bool Stage15BackdropIsActive(void) {
    return g_Entities[STAGE15_BACKDROP_ENTITY].pfnUpdate ==
           EntityStage15Backdrop;
}
#endif

#ifdef STAGE15_NATIVE_8X8
#define STAGE15_NATIVE_LAYERS 3
#define STAGE15_NATIVE_CHARS_SIZE (256 * 256 / 2)
#define STAGE15_NATIVE_MAP_WORDS (360 * 64 + 2)
#define STAGE15_NATIVE_PAL_WORDS (16 * 16)

typedef struct {
    u_long chars[STAGE15_NATIVE_CHARS_SIZE / sizeof(u_long)];
    u16 map[STAGE15_NATIVE_MAP_WORDS];
    u16 palettes[STAGE15_NATIVE_PAL_WORDS];
    u16 cluts[16];
    u16 tpage;
    u8 characterVisible[1024];
    s32 paletteCount;
    u16 width;
    u16 height;
} Stage15NativeLayer;

static Stage15NativeLayer s_NativeLayers[STAGE15_NATIVE_LAYERS];
static s32 s_NativeRoom = -1;
static bool s_NativeReady;

static bool Stage15LoadNativeLayer(s32 room, s32 layer) {
    Stage15NativeLayer* native = &s_NativeLayers[layer];
    char path[256];
    s32 length;
    s32 entryCount;

    snprintf(path, sizeof(path),
             STAGE15_ASSET_DIR "/native_room%d_layer%d.chars.bin", room, layer);
    length = FileReadToBuf(path, native->chars, 0, sizeof(native->chars));
    if (length != sizeof(native->chars)) {
        return false;
    }

    snprintf(path, sizeof(path),
             STAGE15_ASSET_DIR "/native_room%d_layer%d.pal.bin", room, layer);
    length = FileReadToBuf(path, native->palettes, 0, sizeof(native->palettes));
    if (length <= 0 || (length & 0x1)) {
        return false;
    }
    native->paletteCount = length / (16 * sizeof(u16));
    if (native->paletteCount > 16) {
        native->paletteCount = 16;
    }
    {
        const u8* pixels = (const u8*)native->chars;
        s32 character;
        s32 row;
        s32 byte;
        for (character = 0; character < LEN(native->characterVisible);
             character++) {
            native->characterVisible[character] = 0;
            for (row = 0; row < 8 && !native->characterVisible[character];
                 row++) {
                s32 offset =
                    ((character >> 5) * 8 + row) * 128 + (character & 0x1F) * 4;
                for (byte = 0; byte < 4; byte++) {
                    if (pixels[offset + byte] != 0) {
                        native->characterVisible[character] = 1;
                        break;
                    }
                }
            }
        }
    }
    snprintf(path, sizeof(path),
             STAGE15_ASSET_DIR "/native_room%d_layer%d.map.bin", room, layer);
    length = FileReadToBuf(path, native->map, 0, sizeof(native->map));
    if (length < 4 || (length & 0x1)) {
        return false;
    }
    native->width = native->map[0];
    native->height = native->map[1];
    entryCount = native->width * native->height;
    if (native->width == 0 || native->height == 0 ||
        entryCount > STAGE15_NATIVE_MAP_WORDS - 2 ||
        length < (entryCount + 2) * sizeof(u16)) {
        return false;
    }
    return true;
}

static bool Stage15LoadNativeRoom(s32 room) {
    RECT paletteRect;
    Stage15NativeLayer* native;
    s32 layer;
    s32 palette;
    s32 paletteSlot;

    s_NativeReady = false;
    s_NativeRoom = room;
    for (layer = 0; layer < STAGE15_NATIVE_LAYERS; layer++) {
        if (!Stage15LoadNativeLayer(room, layer)) {
            return false;
        }
    }

    for (layer = 0; layer < STAGE15_NATIVE_LAYERS; layer++) {
        native = &s_NativeLayers[layer];
        native->tpage = LoadTPage(
            native->chars, 0, 0, 0x200 + layer * 0x40, 0, 0x100, 0x100);
    }
    for (layer = 0; layer < STAGE15_NATIVE_LAYERS; layer++) {
        native = &s_NativeLayers[layer];
        for (palette = 0; palette < native->paletteCount; palette++) {
            paletteSlot = layer * 16 + palette;
            paletteRect.x = 0x300 + (paletteSlot & 0xF) * 16;
            paletteRect.y = 0xF0 + (paletteSlot >> 4);
            paletteRect.w = 16;
            paletteRect.h = 1;
            native->cluts[palette] =
                LoadClut2((u_long*)&native->palettes[palette * 16],
                          paletteRect.x, paletteRect.y);
        }
    }
    s_NativeReady = true;
    return true;
}

static void Stage15DrawNativeBlock(
    Stage15NativeLayer* native, s32 order, s32 mapX, s32 mapY, s32 blockWidth,
    s32 blockHeight, s32 x0, s32 y0, s32 x1) {
    POLY_GT4* poly;
    u16 pnd;
    u16 character;
    u16 palette;
    u8 u0;
    u8 u1;
    u8 v0;
    u8 v1;
    bool blockVisible = false;
    s32 dx;
    s32 dy;

    if (x1 <= 0 || x0 >= DISP_STAGE_W || y0 <= -blockHeight * 8 ||
        y0 >= DISP_STAGE_H || g_GpuUsage.gt4 >= MAX_POLY_GT4_COUNT) {
        return;
    }
    pnd = native->map[2 + mapY * native->width + mapX];
    character = pnd & 0x3FF;
    palette = pnd >> 12;
    if (palette >= native->paletteCount) {
        return;
    }
    for (dy = 0; dy < blockHeight && !blockVisible; dy++) {
        for (dx = 0; dx < blockWidth; dx++) {
            u16 member =
                native->map[2 + (mapY + dy) * native->width + mapX + dx];
            if (native->characterVisible[member & 0x3FF]) {
                blockVisible = true;
                break;
            }
        }
    }
    if (!blockVisible) {
        return;
    }

    u0 = (character & 0x1F) * 8;
    v0 = (character >> 5) * 8;
    u1 = u0 + blockWidth * 8 - 1;
    v1 = v0 + blockHeight * 8 - 1;
    if (pnd & 0x0400) {
        u0 += 7;
        u1 = u0 - (blockWidth * 8 - 1);
    }
    if (pnd & 0x0800) {
        v0 += 7;
        v1 = v0 - (blockHeight * 8 - 1);
    }

    poly = &g_CurrentBuffer->polyGT4[g_GpuUsage.gt4++];
    setPolyGT4(poly);
    setShadeTex(poly, true);
    setSemiTrans(poly, false);
    setRGB0(poly, 0x80, 0x80, 0x80);
    setRGB1(poly, 0x80, 0x80, 0x80);
    setRGB2(poly, 0x80, 0x80, 0x80);
    setRGB3(poly, 0x80, 0x80, 0x80);
    poly->x0 = poly->x2 = x0 + g_backbufferX;
    poly->x1 = poly->x3 = x1 + g_backbufferX;
    poly->y0 = poly->y1 = y0 + g_backbufferY;
    poly->y2 = poly->y3 = y0 + blockHeight * 8 + g_backbufferY;
    poly->u0 = poly->u2 = u0;
    poly->u1 = poly->u3 = u1;
    poly->v0 = poly->v1 = v0;
    poly->v2 = poly->v3 = v1;
    poly->tpage = native->tpage;
    poly->clut = native->cluts[palette];
    AddPrim(&g_CurrentBuffer->ot[order], poly);
}

static void Stage15DrawNativeLayer(s32 layer, s32 order, bool wrap) {
    Stage15NativeLayer* native = &s_NativeLayers[layer];
    s32 scrollX = g_Tilemap.scrollX.i.hi;
    s32 scrollY = g_Tilemap.scrollY.i.hi;
    s32 startX;
    s32 startY;
    s32 endX;
    s32 endY;
    s32 logicalX;
    s32 logicalY;
    s32 mapX;
    s32 mapY;
    s32 x0;
    s32 x1;
    s32 y0;

    if (layer == 1) {
        scrollX = 0;
        scrollY = 10;
    }
    if (wrap) {
        scrollX %= (native->width * 32) / 5;
        scrollY %= native->height * 8;
        if (scrollX < 0) {
            scrollX += (native->width * 32) / 5;
        }
        if (scrollY < 0) {
            scrollY += native->height * 8;
        }
    }
    startX = (scrollX * 5) / 32;
    startY = scrollY / 8;
    endX = startX + 41;
    endY = startY + 30;
    for (logicalY = startY; logicalY <= endY; logicalY++) {
        mapY = wrap ? logicalY % native->height : logicalY;
        if (mapY < 0 || mapY >= native->height) {
            continue;
        }
        y0 = logicalY * 8 - scrollY;
        for (logicalX = startX; logicalX <= endX; logicalX++) {
            mapX = wrap ? logicalX % native->width : logicalX;
            if (mapX < 0 || mapX >= native->width) {
                continue;
            }
            {
                const s32 blockWidth = 1;
                const s32 blockHeight = 1;
                x0 = (logicalX * 32) / 5 - scrollX;
                x1 = ((logicalX + blockWidth) * 32) / 5 - scrollX;
                Stage15DrawNativeBlock(native, order, mapX, mapY, blockWidth,
                                       blockHeight, x0, y0, x1);
            }
        }
    }
}

static void Stage15DrawBackScreen(void) {
    POLY_G4* poly;

    if (g_GpuUsage.g4 >= MAX_POLY_G4_COUNT) {
        return;
    }
    poly = &g_CurrentBuffer->polyG4[g_GpuUsage.g4++];
    setPolyG4(poly);
    setSemiTrans(poly, false);
    setRGB0(poly, 0x31, 0x00, 0x29);
    setRGB1(poly, 0x31, 0x00, 0x29);
    setRGB2(poly, 0x31, 0x00, 0x29);
    setRGB3(poly, 0x31, 0x00, 0x29);
    poly->x0 = poly->x2 = g_backbufferX;
    poly->x1 = poly->x3 = DISP_STAGE_W + g_backbufferX;
    poly->y0 = poly->y1 = g_backbufferY;
    poly->y2 = poly->y3 = DISP_STAGE_H + g_backbufferY;
    AddPrim(&g_CurrentBuffer->ot[0x10], poly);
}

static bool Stage15RenderNativeLayers(void) {
    s32 room = Stage15CurrentRoom();

    if (room < 0) {
        return false;
    }
    if (room != s_NativeRoom && !Stage15LoadNativeRoom(room)) {
        return false;
    }
    if (!s_NativeReady) {
        return false;
    }
    if (g_Tilemap.hideTimer > 0) {
        g_Tilemap.hideTimer--;
        return true;
    }

    if (room < 4 && Stage15BackdropIsActive()) {
        Stage15DrawBackScreen();
        Stage15DrawNativeLayer(1, 0x20, true);
    }
    Stage15DrawNativeLayer(2, 0x40, false);
    Stage15DrawNativeLayer(0, room >= 4 ? 0xA0 : 0x60, false);
#ifdef STAGE15_ENTITY_LABELS
    Stage15DrawEntityLabels();
#endif
    return true;
}
#endif

#ifndef STAGE15_ROOM_TEST
static void EntityStage15Backdrop(Entity* self) {
    LayerDef* def;
    BgLayer* bg = &g_BgLayers[1];

    (void)self;
    if (s_TileLayers == NULL) {
        return;
    }
    def = s_TileLayers[7].bg;
    if (def == NULL || def->tileDef == NULL) {
        bg->flags = 0;
        return;
    }
    bg->layout = def->layout;
    bg->tileDef = def->tileDef;
    bg->scrollX.i.hi = 0;
    bg->scrollY.i.hi = 10;
    bg->order = def->zPriority;
    bg->flags = def->flags;
    bg->w = def->rect.right - def->rect.left + 1;
    bg->h = def->rect.bottom - def->rect.top + 1;
    bg->scrollKind = def->rect.params;
    bg->hideTimer = 1;
}

static void EntityStage15Dummy(Entity* self) { (void)self; }

static void EntityStage15Masonry(Entity* self) {
    static const s8 offsetsX[3] = {-14, 2, 18};
    Primitive* prim;
    s32 column;
    s32 primIndex;
    s32 row;
    s32 rows;

    if (!s_Stage15MasonryReady) {
        return;
    }
    rows = (self->params & 2) ? 6 : 2;
    g_ClutIds[STAGE15_MASONRY_CLUT_SLOT] = getClut(0x3F0, 0xF3);
    if (self->step == 0) {
        primIndex = g_api.AllocPrimitives(PRIM_GT4, rows * 3);
        if (primIndex == -1) {
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        self->step = 1;
    }

    prim = &g_PrimBuf[self->primIndex];
    for (row = 0; row < rows; row++) {
        for (column = 0; column < 3; column++, prim = prim->next) {
            s32 centerX = self->posX.i.hi + offsetsX[column];
            s32 centerY = self->posY.i.hi - 8 - row * 16;

            prim->tpage = s_Stage15MasonryTpage;
            prim->clut = STAGE15_MASONRY_CLUT_SLOT;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 24;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 16;
            prim->x0 = prim->x2 = centerX - 10;
            prim->x1 = prim->x3 = centerX + 9;
            prim->y0 = prim->y1 = centerY - 8;
            prim->y2 = prim->y3 = centerY + 8;
            prim->priority = 0x80;
            prim->drawMode = DRAW_UNK02;
        }
    }
}

static void EntityStage15SpecialController(Entity* self) { self->step = 1; }

static void Stage15SyncRoomEntities(void) {
    LayoutEntity* layout;
    Entity* entity;
    size_t layoutIndex;
    s32 entityId;
    s32 index;
    s32 visible;

    if (s_CurrentLayout == NULL) {
        return;
    }
    for (layoutIndex = 0; layoutIndex < s_CurrentLayoutCount; layoutIndex++) {
        layout = &s_CurrentLayout[layoutIndex];
        index = STAGE_ENTITY_START + (layout->entityRoomIndex & 0xFF);
        if (index < STAGE_ENTITY_START || index >= TOTAL_ENTITY_COUNT) {
            continue;
        }
        entityId = layout->entityId & 0x3FF;
        visible = layout->posX >= g_Tilemap.scrollX.i.hi - 64 &&
                  layout->posX <= g_Tilemap.scrollX.i.hi + 320 &&
                  layout->posY >= g_Tilemap.scrollY.i.hi - 64 &&
                  layout->posY <= g_Tilemap.scrollY.i.hi + 288;
        entity = &g_Entities[index];
        if (!visible) {
            if (entity->pfnUpdate == EntityStage15Dummy ||
                entity->pfnUpdate == EntityStage15Masonry ||
                entity->pfnUpdate == EntityRedDoor ||
                entity->pfnUpdate == EntityStage15SpecialController) {
                DestroyEntity(entity);
            }
            continue;
        }
        if (entity->entityId != entityId ||
            (entity->pfnUpdate != EntityStage15Dummy &&
             entity->pfnUpdate != EntityStage15Masonry &&
             entity->pfnUpdate != EntityRedDoor &&
             entity->pfnUpdate != EntityStage15SpecialController)) {
            DestroyEntity(entity);
            entity->entityId = entityId;
            entity->params = layout->params;
            entity->entityRoomIndex = layout->entityRoomIndex >> 8;
            if (entityId == 5) {
                entity->pfnUpdate = EntityRedDoor;
            } else if (entityId == 15 && Stage15CurrentRoom() == 6) {
                entity->pfnUpdate = EntityStage15Masonry;
            } else if (entityId == 16) {
                entity->pfnUpdate = EntityStage15SpecialController;
            } else {
                entity->pfnUpdate = EntityStage15Dummy;
            }
        }
        entity->posX.i.hi =
            (s16)layout->posX - g_Tilemap.scrollX.i.hi +
            (entity->pfnUpdate == EntityRedDoor && entity->step != 0
                 ? entity->ext.redDoor.xOffset
                 : 0);
        entity->posY.i.hi =
            (s16)layout->posY - g_Tilemap.scrollY.i.hi +
            (entity->pfnUpdate == EntityRedDoor && entity->step != 0 ? 0x1F
                                                                     : 0);
    }
}

static void Stage15Update(void) {
    Entity* entity;

    Stage15SyncRoomEntities();
    for (entity = &g_Entities[STAGE_ENTITY_START];
         entity < &g_Entities[TOTAL_ENTITY_COUNT]; entity++) {
        if (entity->pfnUpdate == EntityStage15Dummy ||
            entity->pfnUpdate == EntityStage15Masonry ||
            entity->pfnUpdate == EntityRedDoor ||
            entity->pfnUpdate == EntityStage15SpecialController ||
            entity->pfnUpdate == EntityStage15Backdrop) {
            entity->pfnUpdate(entity);
        }
    }
}

static void Stage15InitRoomEntities(s32 layoutId) {
    Entity* entity;
    Entity* backdrop;

    for (entity = &g_Entities[STAGE_ENTITY_START];
         entity < &g_Entities[TOTAL_ENTITY_COUNT]; entity++) {
        if (entity->pfnUpdate == EntityStage15Dummy ||
            entity->pfnUpdate == EntityStage15Masonry ||
            entity->pfnUpdate == EntityRedDoor ||
            entity->pfnUpdate == EntityStage15SpecialController) {
            DestroyEntity(entity);
        }
    }
    s_CurrentLayout = layoutId >= 0 && layoutId < LEN(s_Stage15ObjLayouts)
                          ? s_Stage15ObjLayouts[layoutId]
                          : NULL;
    s_CurrentLayoutCount =
        layoutId >= 0 && layoutId < LEN(s_Stage15ObjLayoutCounts)
            ? s_Stage15ObjLayoutCounts[layoutId]
            : 0;
    backdrop = &g_Entities[STAGE15_BACKDROP_ENTITY];
    if (backdrop->pfnUpdate != EntityStage15Backdrop) {
        DestroyEntity(backdrop);
        backdrop->entityId = 1;
        backdrop->pfnUpdate = EntityStage15Backdrop;
    }
    Stage15SyncRoomEntities();
    EntityStage15Backdrop(backdrop);
}
#else
static void Stage15Update(void) {}
static void Stage15InitRoomEntities(s32 layoutId) { (void)layoutId; }
#endif

OVL_API void InitStage(Overlay* o) {
    memset(o, 0, sizeof(*o));
    s_CurrentLayout = NULL;
    s_CurrentLayoutCount = 0;
#ifndef STAGE15_ROOM_TEST
    g_PcStageLayerRenderer = NULL;
    g_PcGpuOtSubmitter = NULL;
    Stage15ConfigureMusic();
    s_Stage15MasonryReady = Stage15LoadMasonry();
    if (s_Stage15MasonryReady) {
        s_Stage15MasonryTpage =
            LoadTPage((u_long*)s_Stage15MasonryPixels, 0, 0, 0x2C0, 0, 24, 16);
        g_ClutIds[STAGE15_MASONRY_CLUT_SLOT] =
            LoadClut2((u_long*)s_Stage15MasonryPalette, 0x3F0, 0xF3);
    }
#endif

    o->Update = Stage15Update;
    o->HitDetection = Noop;
    o->UpdateRoomPosition = Noop;
    o->InitRoomEntities = Stage15InitRoomEntities;
    o->rooms = s_Stage15Rooms;
    o->spriteBanks = s_SpriteBanks;
    o->cluts = s_Cluts;
    o->objLayoutHorizontal = s_Stage15ObjLayouts;
    s_TileLayers = o->tileLayers = s_Stage15TileLayers;
    o->gfxBanks = s_GfxBanks;
    o->UpdateStageEntities = Noop;
#ifdef STAGE15_NATIVE_8X8
    s_NativeRoom = -1;
    s_NativeReady = false;
    g_PcStageLayerRenderer = Stage15RenderNativeLayers;
#endif
}
