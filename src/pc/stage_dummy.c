#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON/cJSON.h>
#include "pc.h"
#include "sfx.h"

static void Update(void);
static void HitDetection(void);
static void func_8018A7AC(void);
static void InitRoomEntities(s32 objLayoutId);

static RoomHeader g_Rooms[1];
static s16** g_SpriteBanks[1];
static u16* g_Cluts[1];
static RoomDef g_TileLayers[0x100];
void* g_EntityGfxs[17];
static void UpdateStageEntities(void);

static Overlay g_StageDummy = {
    Update,
    HitDetection,
    func_8018A7AC,
    InitRoomEntities,
    g_Rooms,
    g_SpriteBanks,
    g_Cluts,
    NULL,
    g_TileLayers,
    g_EntityGfxs,
    UpdateStageEntities,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

static RoomHeader g_Rooms[1] = {0};
static s16** g_SpriteBanks[1] = {0};
static RoomDef g_TileLayers[0x100] = {0};

static u32* D_801801B8[] = {
    (u32*)0x00000000, (u32*)0x00000000, (u32*)0x00000000,
    (u32*)0x00000000, (u32*)0xFFFFFFFF,
};
void* g_EntityGfxs[] = {
    D_801801B8, D_801801B8, D_801801B8, D_801801B8, D_801801B8, D_801801B8,
    D_801801B8, D_801801B8, D_801801B8, D_801801B8, D_801801B8, D_801801B8,
    D_801801B8, D_801801B8, D_801801B8, D_801801B8, NULL,
};

static u8 D_80181D08[0x2000];
static u32* D_801800A0[] = {
    (u32*)0x00000005, (u32*)0x00002000, (u32*)0x00000010,
    (u32*)D_80181D08, (u32*)0xFFFFFFFF,
};
static u16* g_Cluts[] = {
    D_801800A0,
};

#define JITEM(x) cJSON_GetObjectItemCaseSensitive(jitem, x)
static TileDefinition* g_TileDefToLoad = NULL;
bool LoadRoomTileDef(const char* content) {
    INFOF("load");
    cJSON* jitem = cJSON_Parse(content);
    if (!jitem) {
        ERRORF("failed to parse: %s", cJSON_GetErrorPtr());
        return false;
    }

    FILE* f;
    char buf[0x100];
    snprintf(buf, sizeof(buf), "assets/st/wrp/%s.bin",
             JITEM("gfxPage")->valuestring);
    f = fopen(buf, "rb");
    if (f) {
        fread(g_TileDefToLoad->gfxPage, 0x1000, 1, f);
        fclose(f);
    } else {
        WARNF("unable to load '%s'", buf);
    }
    snprintf(buf, sizeof(buf), "assets/st/wrp/%s.bin",
             JITEM("gfxIndex")->valuestring);
    f = fopen(buf, "rb");
    if (f) {
        fread(g_TileDefToLoad->gfxIndex, 0x1000, 1, f);
        fclose(f);
    } else {
        WARNF("unable to load '%s'", buf);
    }
    snprintf(
        buf, sizeof(buf), "assets/st/wrp/%s.bin", JITEM("clut")->valuestring);
    f = fopen(buf, "rb");
    if (f) {
        fread(g_TileDefToLoad->clut, 0x1000, 1, f);
        fclose(f);
    } else {
        WARNF("unable to load '%s'", buf);
    }
    snprintf(buf, sizeof(buf), "assets/st/wrp/%s.bin",
             JITEM("collision")->valuestring);
    f = fopen(buf, "rb");
    if (f) {
        fread(g_TileDefToLoad->collision, 0x1000, 1, f);
        fclose(f);
    } else {
        WARNF("unable to load '%s'", buf);
    }

    cJSON_Delete(jitem);
    return true;
}

static int g_TileDefIndex = 0;
static TileDefinition g_TileDefPool[0x40];
static TileDefinition g_TileDefDataPool[0x40][4][0x1000];
static int g_LayoutIndex = 0;
static u16 g_LayoutPool[0x10000];
void LoadRoomLayerDef(LayerDef* l, cJSON* jitem) {
    l->rect.left = JITEM("left")->valueint;
    l->rect.top = JITEM("top")->valueint;
    l->rect.right = JITEM("right")->valueint;
    l->rect.bottom = JITEM("bottom")->valueint;
    l->zPriority = JITEM("zPriority")->valueint;
    l->flags = 0;

    char buf[0x100];
    FILE* f;
    snprintf(buf, sizeof(buf), "assets/st/wrp/%s.tilelayout.bin",
             JITEM("data")->valuestring);
    f = fopen(buf, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        size_t len = ftell(f);
        fseek(f, 0, SEEK_SET);
        if (g_LayoutIndex + len > LEN(g_LayoutPool)) {
            ERRORF("out of memory");
            exit(1);
        }
        l->layout = g_LayoutPool + g_LayoutIndex;
        g_LayoutIndex += len;
        fread(l->layout, len, 1, f);
        fclose(f);
    } else {
        WARNF("unable to load '%s'", buf);
    }

    if (g_TileDefIndex >= LEN(g_TileDefPool)) {
        ERRORF("out of memory");
        exit(1);
    }
    l->tileDef = g_TileDefPool + g_TileDefIndex;
    l->tileDef->gfxPage = g_TileDefDataPool[g_TileDefIndex][0];
    l->tileDef->gfxIndex = g_TileDefDataPool[g_TileDefIndex][1];
    l->tileDef->clut = g_TileDefDataPool[g_TileDefIndex][2];
    l->tileDef->collision = g_TileDefDataPool[g_TileDefIndex][3];
    g_TileDefIndex++;
    snprintf(buf, sizeof(buf), "assets/st/wrp/%s.tiledef.json",
             JITEM("tiledef")->valuestring);
    g_TileDefToLoad = l->tileDef;
    FileStringify(LoadRoomTileDef, buf);
}

static int g_LayerDefIndex = 0;
static LayerDef g_LayerDefPool[0x40];
bool LoadTileLayers(const char* content) {
    INFOF("load");
    cJSON* json = cJSON_Parse(content);
    if (!json) {
        ERRORF("failed to parse: %s", cJSON_GetErrorPtr());
        return false;
    }

    // from here, assume the JSON is valid and well structured
    int len = cJSON_GetArraySize(json);
    if (len > LEN(g_TileLayers)) {
        WARNF("data too big, will truncate (cur: %d, max: %d)", len,
              LEN(g_TileLayers));
        len = LEN(g_TileLayers);
    }
    for (int i = 0; i < len; i++) {
        RoomDef* item = &g_TileLayers[i];
        cJSON* jitem = cJSON_GetArrayItem(json, i);

        cJSON* jbg = JITEM("bg");
        item->bg = g_LayerDefPool + g_LayerDefIndex++;
        if (g_LayerDefIndex >= LEN(g_LayerDefPool)) {
            ERRORF("out of memory");
            exit(1);
        }
        if (jbg) {
            LoadRoomLayerDef(item->bg, jbg);
        } else {
            memset(item->bg, 0, sizeof(LayerDef));
        }

        cJSON* jfg = JITEM("fg");
        item->fg = g_LayerDefPool + g_LayerDefIndex++;
        if (g_LayerDefIndex >= LEN(g_LayerDefPool)) {
            ERRORF("out of memory");
            exit(1);
        }
        if (jfg) {
            LoadRoomLayerDef(item->fg, jfg);
        } else {
            memset(item->fg, 0, sizeof(LayerDef));
        }
    }
    cJSON_Delete(json);
    return true;
}
void InitStageDummy(Overlay* o) {
    FILE* f;

    f = fopen("assets/st/wrp/D_80181D08.dec", "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        size_t len = ftell(f);
        fseek(f, 0, SEEK_SET);
        fread(D_80181D08, len, 1, f);
        fclose(f);
    }

    g_TileDefIndex = 0;
    g_LayerDefIndex = 0;
    g_LayoutIndex = 0;
    FileStringify(LoadTileLayers, "assets/st/wrp/rooms.layers.json");

    memcpy(o, &g_StageDummy, sizeof(Overlay));
}

static void Update(void) { NOT_IMPLEMENTED; }

static void HitDetection(void) { NOT_IMPLEMENTED; }

static void func_8018A7AC(void) { NOT_IMPLEMENTED; }

void SetGameState(GameState gameState);
void PlaySfx(s32 sfxId);
static void InitRoomEntities(s32 objLayoutId) {
    if (g_StageId == STAGE_SEL) {
        SetGameState(Game_NowLoading);
        g_GameStep = NowLoading_2;
        g_StageId = STAGE_WRP;
        return;
    }

    INFOF("Stage ID: %02X", g_StageId);
    PlaySfx(MU_REQUIEM_FOR_THE_GODS);
}

static void UpdateStageEntities(void) { NOT_IMPLEMENTED; }
