// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON/cJSON.h>
#include "stage_loader.h"

// this is shared across all the overlays
u8 stage_placeholder[1444];
u8 stage_title_jp[836];

// Use a pre-allocated pool of bytes instead of relying on malloc. This is done
// because the JSON size is unknown and because it is easier to not take track
// of previously allocated memory.
// Don't try this at work!

#define JITEM(x) cJSON_GetObjectItemCaseSensitive(jitem, x)

typedef struct {
    const char* assetPath;
} RoomLoadDesc;
static TileDefinition* g_TileDefToLoad = NULL;
static bool LoadRoomTileDef(struct FileAsString* file) {
    INFOF("load");
    RoomLoadDesc* desc = (RoomLoadDesc*)file->param;
    cJSON* jitem = cJSON_Parse(file->content);
    if (!jitem) {
        ERRORF("failed to parse: %s", cJSON_GetErrorPtr());
        return false;
    }

    FILE* f;
    char buf[0x100];
    snprintf(buf, sizeof(buf), "%s/%s", desc->assetPath,
             JITEM("gfxPage")->valuestring);
    if (FileReadToBuf(buf, g_TileDefToLoad->gfxPage, 0, 0x1000) < 0) {
        cJSON_Delete(jitem);
        return false;
    }

    snprintf(buf, sizeof(buf), "%s/%s", desc->assetPath,
             JITEM("gfxIndex")->valuestring);
    if (FileReadToBuf(buf, g_TileDefToLoad->gfxIndex, 0, 0x1000) < 0) {
        cJSON_Delete(jitem);
        return false;
    }

    snprintf(
        buf, sizeof(buf), "%s/%s", desc->assetPath, JITEM("clut")->valuestring);
    if (FileReadToBuf(buf, g_TileDefToLoad->clut, 0, 0x1000) < 0) {
        cJSON_Delete(jitem);
        return false;
    }

    snprintf(buf, sizeof(buf), "%s/%s", desc->assetPath,
             JITEM("collision")->valuestring);
    if (FileReadToBuf(buf, g_TileDefToLoad->collision, 0, 0x1000) < 0) {
        cJSON_Delete(jitem);
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

    // hack to load t_8018xxxx.tiledef instead of D_8018xxxx.tiledef
    snprintf(buf, sizeof(buf), "%s/t_%s.tiledef.json", desc->assetPath,
             JITEM("tiledef")->valuestring + 2);

    g_TileDefToLoad = l->tileDef;

    return FileAsString(LoadRoomTileDef, buf, desc);
}

static int g_LayerDefIndex = 0;
static LayerDef g_LayerDefPool[0x40];
static RoomDef g_TileLayers[0x100];
static bool LoadTileLayers(struct FileAsString* file) {
    int i;
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
    for (i = 0; i < len; i++) {
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

    for (i = len; i < LEN(g_TileLayers); i++) {
        g_TileLayers[i].fg = NULL;
        g_TileLayers[i].bg = NULL;
    }
    return true;
}

RoomDef* LoadRoomsLayers(const char* filePath) {
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
    if (!FileAsString(LoadTileLayers, filePath, &desc)) {
        ERRORF("failed to load '%s'", filePath);
        return NULL;
    }

    return g_TileLayers;
}

static int g_LayoutEntityIndex = 0;
static LayoutEntity g_LayoutEntityPool[0x200];
static bool _LoadObjLayout(const struct FileAsString* file) {
    int i;
    cJSON* json = cJSON_Parse(file->content);
    if (!json) {
        ERRORF("failed to parse: %s", cJSON_GetErrorPtr());
        return false;
    }

    // from here, assume the JSON is valid and well structured
    LayoutEntity* e;
    int len = cJSON_GetArraySize(json);
    for (i = 0; i < len; i++) {
        cJSON* jitem = cJSON_GetArrayItem(json, i);
        e = g_LayoutEntityPool + g_LayoutEntityIndex++;
        e->posX = JITEM("x")->valueint;
        e->posY = JITEM("y")->valueint;
        e->entityId = JITEM("entityId")->valueint;
        e->entityRoomIndex = JITEM("entityRoomIndex")->valueint;
        e->params = JITEM("subId")->valueint;
    }

    e = g_LayoutEntityPool + g_LayoutEntityIndex++;
    e->posX = -1;
    e->posY = -1;
    e->entityId = 0;
    e->entityRoomIndex = 0;
    e->params = 0;
    return true;
}
LayoutEntity* LoadObjLayout(const char* filePath) {
    int start = g_LayoutEntityIndex;
    if (!FileAsString(_LoadObjLayout, filePath, NULL)) {
        // if the load fails, resets the pool as it was before
        g_LayoutEntityIndex = start;
        return NULL;
    }

    return g_LayoutEntityPool + start;
}

RoomHeader room_headers[0x100];
static bool _LoadRoomDefArray(const struct FileAsString* file) {
    int i;
    cJSON* json = cJSON_Parse(file->content);
    if (!json) {
        ERRORF("failed to parse: %s", cJSON_GetErrorPtr());
        return false;
    }

    // from here, assume the JSON is valid and well structured
    const int max = LEN(room_headers);
    int len = cJSON_GetArraySize(json);
    if (len > max) {
        WARNF("room def has %i elements, but only %i will be read", len, max);
        len = max;
    }

    for (i = 0; i < len; i++) {
        cJSON* jitem = cJSON_GetArrayItem(json, i);
        RoomHeader* room = &room_headers[i];
        room->left = JITEM("left")->valueint;
        room->top = JITEM("top")->valueint;
        room->right = JITEM("right")->valueint;
        room->bottom = JITEM("bottom")->valueint;
        room->load.tileLayoutId = JITEM("tileLayoutId")->valueint;
        room->load.tilesetId = JITEM("tilesetId")->valueint;
        room->load.objGfxId = JITEM("objGfxId")->valueint;
        room->load.objLayoutId = JITEM("objLayoutId")->valueint;
    }
    return true;
}
RoomHeader* LoadRoomDefs(const char* filePath) {
    if (!FileAsString(_LoadRoomDefArray, filePath, NULL)) {
        return NULL;
    }
    return room_headers;
}

static int g_SpritePartPtrIndex = 0;
static SpriteParts* g_SpritePartPtrPool[0x100];
static int g_SpritePartIndex = 0;
static u16 g_SpritePartPool[0x200 * sizeof(SpritePart)];
static bool _LoadSpriteParts(struct FileAsString* file) {
    int i, j;
    cJSON* json = cJSON_Parse(file->content);
    if (!json) {
        ERRORF("failed to parse: %s", cJSON_GetErrorPtr());
        return false;
    }

    // from here, assume the JSON is valid and well structured
    int len = cJSON_GetArraySize(json);
    if (g_SpritePartPtrIndex + len > LEN(g_SpritePartPtrPool)) {
        WARNF("sprite pointer pool out of memory");
        return false;
    }

    for (i = 0; i < len; i++) {
        SpriteParts* s = NULL;
        const cJSON* jpart = cJSON_GetArrayItem(json, i);
        if (!cJSON_IsNull(jpart))
            jpart = cJSON_GetArrayItem(json, i);
        u16 spriteCount = (u16)cJSON_GetArraySize(jpart);
        u32 dataNeeded = 1 + spriteCount * sizeof(SpritePart) / sizeof(u16);
        if (g_SpritePartIndex + dataNeeded > LEN(g_SpritePartPool)) {
            WARNF("sprite pool out of memory");
            return false;
        }

        s = (SpriteParts*)&g_SpritePartPool[g_SpritePartIndex];
        g_SpritePartIndex += dataNeeded;
        s->count = spriteCount;
        for (j = 0; j < spriteCount; j++) {
            SpritePart* p = &s->parts[j];
            const cJSON* jitem = cJSON_GetArrayItem(jpart, j);
            p->flags = JITEM("flags")->valueint;
            p->offsetx = JITEM("offsetx")->valueint;
            p->offsety = JITEM("offsety")->valueint;
            p->width = JITEM("width")->valueint;
            p->height = JITEM("height")->valueint;
            p->clut = JITEM("clut")->valueint;
            p->tileset = JITEM("tileset")->valueint;
            p->left = JITEM("left")->valueint;
            p->top = JITEM("top")->valueint;
            p->right = JITEM("right")->valueint;
            p->bottom = JITEM("bottom")->valueint;
        }
        g_SpritePartPtrPool[g_SpritePartPtrIndex++] = s;
    }

    return true;
}
SpritePart* LoadSpriteParts(const char* filePath) {
    int start = g_SpritePartPtrIndex;
    int spriteStart = g_SpritePartIndex;
    if (!FileAsString(_LoadSpriteParts, filePath, NULL)) {
        // if the load fails, resets the pool as it was before
        g_SpritePartPtrIndex = start;
        g_SpritePartIndex = spriteStart;
        return NULL;
    }

    return g_SpritePartPtrPool + start;
}

void LoadReset() {
    g_LayoutEntityIndex = 0;
    g_SpritePartPtrIndex = 0;
    g_SpritePartIndex = 0;
}
