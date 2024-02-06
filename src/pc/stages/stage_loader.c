#include <game.h>
#include <string.h>
#include <cJSON/cJSON.h>
#include "stage_loader.h"

typedef struct {
    const char* assetPath;
} RoomLoadDesc;

#define JITEM(x) cJSON_GetObjectItemCaseSensitive(jitem, x)
static TileDefinition* g_TileDefToLoad = NULL;
static bool LoadRoomTileDef(FileStringified* file) {
    INFOF("load");
    RoomLoadDesc* desc = (RoomLoadDesc*)file->param;
    cJSON* jitem = cJSON_Parse(file->content);
    if (!jitem) {
        ERRORF("failed to parse: %s", cJSON_GetErrorPtr());
        return false;
    }

    FILE* f;
    char buf[0x100];
    snprintf(buf, sizeof(buf), "%s/%s.bin", desc->assetPath,
             JITEM("gfxPage")->valuestring);
    f = fopen(buf, "rb");
    if (f) {
        fread(g_TileDefToLoad->gfxPage, 0x1000, 1, f);
        fclose(f);
    } else {
        ERRORF("unable to load '%s'", buf);
        return false;
    }
    snprintf(buf, sizeof(buf), "%s/%s.bin", desc->assetPath,
             JITEM("gfxIndex")->valuestring);
    f = fopen(buf, "rb");
    if (f) {
        fread(g_TileDefToLoad->gfxIndex, 0x1000, 1, f);
        fclose(f);
    } else {
        ERRORF("unable to load '%s'", buf);
        return false;
    }
    snprintf(buf, sizeof(buf), "%s/%s.bin", desc->assetPath,
             JITEM("clut")->valuestring);
    f = fopen(buf, "rb");
    if (f) {
        fread(g_TileDefToLoad->clut, 0x1000, 1, f);
        fclose(f);
    } else {
        ERRORF("unable to load '%s'", buf);
        return false;
    }
    snprintf(buf, sizeof(buf), "%s/%s.bin", desc->assetPath,
             JITEM("collision")->valuestring);
    f = fopen(buf, "rb");
    if (f) {
        fread(g_TileDefToLoad->collision, 0x1000, 1, f);
        fclose(f);
    } else {
        ERRORF("unable to load '%s'", buf);
        return false;
    }

    cJSON_Delete(jitem);
    return true;
}

static int g_TileDefIndex = 0;
static TileDefinition g_TileDefPool[0x40];
static TileDefinition g_TileDefDataPool[0x40][4][0x1000];
static int g_LayoutIndex = 0;
static u16 g_LayoutPool[0x10000];
static bool LoadRoomLayerDef(LayerDef* l, cJSON* jitem, RoomLoadDesc* desc) {
    l->rect.left = JITEM("left")->valueint;
    l->rect.top = JITEM("top")->valueint;
    l->rect.right = JITEM("right")->valueint;
    l->rect.bottom = JITEM("bottom")->valueint;
    l->zPriority = JITEM("zPriority")->valueint;
    l->flags = 0;

    char buf[0x100];
    FILE* f;
    snprintf(buf, sizeof(buf), "%s/%s.tilelayout.bin", desc->assetPath,
             JITEM("data")->valuestring);
    f = fopen(buf, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        size_t len = ftell(f);
        fseek(f, 0, SEEK_SET);
        if (g_LayoutIndex + len > LEN(g_LayoutPool)) {
            ERRORF("%s out of memory", NAMEOF(g_LayoutPool));
            return false;
        }
        l->layout = g_LayoutPool + g_LayoutIndex;
        g_LayoutIndex += len;
        fread(l->layout, len, 1, f);
        fclose(f);
    } else {
        ERRORF("unable to load '%s'", buf);
        return false;
    }

    if (g_TileDefIndex >= LEN(g_TileDefPool)) {
        ERRORF("%s out of memory", NAMEOF(g_TileDefPool));
        return false;
    }
    l->tileDef = g_TileDefPool + g_TileDefIndex;
    l->tileDef->gfxPage = g_TileDefDataPool[g_TileDefIndex][0];
    l->tileDef->gfxIndex = g_TileDefDataPool[g_TileDefIndex][1];
    l->tileDef->clut = g_TileDefDataPool[g_TileDefIndex][2];
    l->tileDef->collision = g_TileDefDataPool[g_TileDefIndex][3];
    g_TileDefIndex++;
    snprintf(buf, sizeof(buf), "%s/%s.tiledef.json", desc->assetPath,
             JITEM("tiledef")->valuestring);
    g_TileDefToLoad = l->tileDef;

    return FileStringify(LoadRoomTileDef, buf, desc);
}

static int g_LayerDefIndex = 0;
static LayerDef g_LayerDefPool[0x40];
static RoomDef g_TileLayers[0x100];
static bool LoadTileLayers(FileStringified* file) {
    INFOF("load");
    RoomLoadDesc* desc = (RoomLoadDesc*)file->param;
    cJSON* json = cJSON_Parse(file->content);
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
            if (!LoadRoomLayerDef(item->bg, jbg, desc)) {
                return false;
            }
        } else {
            memset(item->bg, 0, sizeof(LayerDef));
        }

        cJSON* jfg = JITEM("fg");
        item->fg = g_LayerDefPool + g_LayerDefIndex++;
        if (g_LayerDefIndex >= LEN(g_LayerDefPool)) {
            ERRORF("%s out of memory", NAMEOF(g_LayerDefPool));
            return false;
        }
        if (jfg) {
            if (!LoadRoomLayerDef(item->fg, jfg, desc)) {
                return false;
            }
        } else {
            memset(item->fg, 0, sizeof(LayerDef));
        }
    }
    cJSON_Delete(json);

    for (int i = len; i < LEN(g_TileLayers); i++) {
        g_TileLayers[i].fg = NULL;
        g_TileLayers[i].bg = NULL;
    }
    return true;
}

RoomDef* LoadRooms(const char* filePath) {
    char assetPath[0x100];

    const char* strTerminator = strrchr(filePath, '/');
    size_t len = (size_t)(strTerminator - filePath);
    len = MIN(len, LEN(assetPath) - 1);
    memcpy(assetPath, filePath, len);
    assetPath[len] = '\0';

    g_LayerDefIndex = 0;
    g_LayoutIndex = 0;
    g_TileDefIndex = 0;

    RoomLoadDesc desc;
    desc.assetPath = assetPath;
    if (!FileStringify(LoadTileLayers, filePath, &desc)) {
        ERRORF("failed to load '%s'", filePath);
        return NULL;
    }

    return g_TileLayers;
}
