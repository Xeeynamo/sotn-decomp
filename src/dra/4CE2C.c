// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

void HideAllBackgroundLayers(void) {
    s32 i;

    g_Tilemap.flags = 0;
    for (i = 0; i < MAX_BG_LAYER_COUNT; i++) {
        g_BgLayers[i].flags = 0;
    }
}

// internal structure that holds all the information to render room layers
typedef struct {
    /* 0x00 */ u16 x;
    /* 0x02 */ u16 y;
    /* 0x04 */ u16 flags;
    /* 0x06 */ u16 clutAlt;
    /* 0x08 */ u16 order;
    /* 0x0A */ u16 isSemiTrans;
    /* 0x0C */ u16 tpage;
    /* 0x0E */ u16 roomTileWidth;
    /* 0x10 */ u16 roomTileHeight;
    /* 0x12 */ u16 pad12;
    /* 0x14 */ u16* tiles;
    /* 0x18 */ u8* page;
    /* 0x1C */ u8* gfx;
    /* 0x20 */ u8* clut;
    /* 0x24 */ OT_TYPE* ot;
    /* 0x28 */ SPRT_16* sp16;
    /* 0x2C */ DR_MODE* dr;
    /* 0x30 */ RECT rect;
} TilemapRenderer;

void RenderTilemap(void) {
#ifdef VERSION_PC
    SPRT_16 _sp16;
    TilemapRenderer _r;
    SPRT_16* sp16 = &_sp16;
    TilemapRenderer* r = &_r;
#else
    SPRT_16* sp16 = (SPRT_16*)0x1F800000;
    TilemapRenderer* r = (TilemapRenderer*)0x1F800010;
#endif

    Tilemap* t = &g_Tilemap;
    BgLayer* bg;
    s32 subX;
    s32 subY;
    s32 row;
    s32 tx;
    s32 ty;
    u16 tpage;
    s32 startTx;
    s32 startTy;
    s32 i;
    s32 j;
    s32 l;
    u16 tile;
    u16 gfx;
    u16 page;
    u16 clut;
    s32 x0;
    s32 y0;
    u8 u;
    u8 v;

    r->rect.x = 0;
    r->rect.y = 0;
    r->rect.w = 255;
    r->rect.h = 255;
    setSprt16(sp16);
    r->ot = g_CurrentBuffer->ot;
    r->sp16 = &g_CurrentBuffer->sprite16[g_GpuUsage.sp16];
    r->dr = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];
    r->x = g_backbufferX;
    r->y = g_backbufferY;
    if (t->hideTimer > 0) {
        t->hideTimer--;
    } else {
        r->flags = t->flags;
        if (r->flags & LAYER_SHOW) {
            r->clutAlt = r->flags & LAYER_CLUT_ALT;
            r->page = t->tileDef->gfxPage;
            r->gfx = t->tileDef->gfxIndex;
            r->clut = t->tileDef->clut;
            r->order = t->order;
            r->roomTileWidth = t->hSize * 16;
            r->roomTileHeight = t->vSize * 16;
            subX = t->scrollX.i.hi & 0xF;
            startTx = t->scrollX.i.hi >> 4;
            subY = t->scrollY.i.hi & 0xF;
            startTy = t->scrollY.i.hi >> 4;
            r->tpage = 0;
            r->isSemiTrans = false;
            if (r->flags & LAYER_SEMI_TRANS) {
                r->isSemiTrans = true;
                r->tpage = r->flags & LAYER_TPAGE_ID;
            }
            y0 = r->y - subY;
            for (i = 0; i < N_VERTI_TILES; i++, y0 += TILE_SIZE) {
                x0 = r->x - subX;
                ty = startTy + i;
                if (ty < 0) {
                    continue;
                }
                if (ty >= r->roomTileHeight) {
                    break;
                }
                row = ty * r->roomTileWidth;
                r->tiles = &t->fg[startTx + ty * r->roomTileWidth];
                j = 0;
                tx = startTx;
                for (; j < N_HORIZ_TILES; j++, x0 += TILE_SIZE, tx++) {
                    if (tx < 0) {
                        continue;
                    }
                    if (tx >= r->roomTileWidth) {
                        break;
                    }

                    tile = *r->tiles++;
                    if (tile == 0) {
                        continue;
                    }
                    page = r->page[tile];
                    gfx = r->gfx[tile];
                    u = gfx * 0x10;
                    v = gfx & 0xF0;
                    clut = g_ClutIds[r->clut[tile]];
                    if (r->clutAlt) {
                        clut = g_ClutIds[0x100 + r->clut[tile]];
                    }
                    if (g_GpuUsage.sp16 >= MAXSPRT16) {
                        continue;
                    }
                    sp16->clut = clut;
                    sp16->x0 = x0;
                    sp16->y0 = y0;
                    sp16->u0 = u;
                    sp16->v0 = v;
                    setSemiTrans(sp16, r->isSemiTrans);
                    setShadeTex(sp16, true);
                    __builtin_memcpy(r->sp16, sp16, sizeof(SPRT_16));
                    addPrim(r->order + page + r->ot, r->sp16);
                    r->sp16++;
                    g_GpuUsage.sp16++;
                }
            }

            for (i = 0; i < 24; i++) {
                if (g_GpuUsage.drawModes >= MAX_DRAW_MODES) {
                    break;
                }
                tpage = i + 8 + r->tpage;
                if (r->flags & LAYER_TPAGE_ALT) {
                    tpage += 0x80;
                }
                SetDrawMode(r->dr, 0, 0, tpage, &r->rect);
                AddPrim(i + r->order + r->ot, r->dr);
                r->dr++;
                g_GpuUsage.drawModes++;
            }
        }
    }

    l = 0;
    bg = g_BgLayers;
    for (; l < MAX_BG_LAYER_COUNT; l++, bg++) {
        if (bg->hideTimer > 0) {
            bg->hideTimer--;
            continue;
        }
        r->flags = bg->flags;
        if (!(r->flags & LAYER_SHOW)) {
            continue;
        }
        r->clutAlt = r->flags & LAYER_CLUT_ALT;
        r->page = bg->tileDef->gfxPage;
        r->gfx = bg->tileDef->gfxIndex;
        r->clut = bg->tileDef->clut;
        r->order = bg->order;
        r->roomTileWidth = bg->w * 16;
        r->roomTileHeight = bg->h * 16;
        subX = bg->scrollX.i.hi & 0xF;
        startTx = bg->scrollX.i.hi >> 4;
        subY = bg->scrollY.i.hi & 0xF;
        startTy = bg->scrollY.i.hi >> 4;
        if (r->flags & LAYER_WRAP_BG) {
            startTx &= TILE_SIZE - 1;
            startTy &= TILE_SIZE - 1;
        }
        r->tpage = 0;
        r->isSemiTrans = false;
        if (r->flags & LAYER_SEMI_TRANS) {
            r->isSemiTrans = true;
            r->tpage = r->flags & LAYER_TPAGE_ID;
        }
        y0 = r->y - subY;
        for (i = 0; i < N_VERTI_TILES; i++, y0 += TILE_SIZE) {
            x0 = r->x - subX;
            ty = startTy + i;
            if (r->flags & LAYER_WRAP_BG) {
                ty &= TILE_SIZE - 1;
            }
            if (ty < 0) {
                continue;
            }
            if (ty >= r->roomTileHeight) {
                break;
            }
            row = ty * r->roomTileWidth;
            r->tiles = &bg->layout[startTx + row];
            j = 0;
            tx = startTx;
            for (; j < N_HORIZ_TILES; j++, x0 += TILE_SIZE, tx++) {
                if (r->flags & LAYER_WRAP_BG) {
                    tx &= 0xF;
                    r->tiles = &bg->layout[tx + row];
                }
                if (tx < 0) {
                    continue;
                }
                if (tx >= r->roomTileWidth) {
                    break;
                }

                tile = *r->tiles++;
                if (tile == 0) {
                    continue;
                }
                page = r->page[tile];
                gfx = r->gfx[tile];
                u = gfx * 0x10;
                v = gfx & 0xF0;
                clut = g_ClutIds[r->clut[tile]];
                if (r->clutAlt) {
                    clut = g_ClutIds[0x100 + r->clut[tile]];
                }
                if (g_GpuUsage.sp16 >= MAXSPRT16) {
                    continue;
                }
                sp16->clut = clut;
                sp16->x0 = x0;
                sp16->y0 = y0;
                sp16->u0 = u;
                sp16->v0 = v;
                setSemiTrans(sp16, r->isSemiTrans);
                setShadeTex(sp16, true);
                __builtin_memcpy(r->sp16, sp16, sizeof(SPRT_16));
                addPrim(r->order + page + r->ot, r->sp16);
                r->sp16++;
                g_GpuUsage.sp16++;
            }
        }
        for (i = 0; i < 24; i++) {
            if (g_GpuUsage.drawModes >= MAX_DRAW_MODES) {
                break;
            }
            tpage = i + 8 + r->tpage;
            if (r->flags & LAYER_TPAGE_ALT) {
                tpage += 0x80;
            }
            SetDrawMode(r->dr, 0, 0, tpage, &r->rect);
            AddPrim(i + r->order + r->ot, r->dr);
            r->dr++;
            g_GpuUsage.drawModes++;
        }
    }
}

void SetRoomForegroundLayer(LayerDef* layerDef) {
    D_8003C708.flags = 0;
    g_canRevealMap = true; // Default to allowing revealing map
    g_Tilemap.tileDef = layerDef->tileDef;
    g_Tilemap.flags = 0;
    if (g_Tilemap.tileDef == 0) {
        return;
    }

    g_Tilemap.fg = layerDef->layout;
    g_Tilemap.order = layerDef->zPriority;
    if (layerDef->rect.params & LAYOUT_RECT_PARAMS_UNKNOWN_40) {
        g_Tilemap.order = 0x60;
        D_8003C708.flags = layerDef->rect.params;
        D_8003C708.unk2 = 0;
        D_8003C708.unk4 = 0;
        D_8003C708.zPriority = layerDef->zPriority;
    }
    if (layerDef->rect.params & LAYOUT_RECT_PARAMS_UNKNOWN_20) {
        g_Tilemap.order = 0x60;
        D_8003C708.flags = layerDef->rect.params;
    }
    // If this flag is set, disable revealing on map.
    // Used for hidden rooms including the "running through trees" at start,
    // and for the Nightmare stage.
    if (layerDef->rect.params & LAYOUT_RECT_PARAMS_HIDEONMAP) {
        g_Tilemap.order = 0x60;
        g_canRevealMap = 0;
    };
    g_Tilemap.flags = layerDef->flags;
    g_Tilemap.left = layerDef->rect.left;
    g_Tilemap.top = layerDef->rect.top;
    g_Tilemap.right = layerDef->rect.right;
    g_Tilemap.bottom = layerDef->rect.bottom;
    g_Tilemap.hSize = g_Tilemap.right - g_Tilemap.left + 1;
    g_Tilemap.vSize = g_Tilemap.bottom - g_Tilemap.top + 1;
    g_Tilemap.y = 0;
    g_Tilemap.x = 0;
    g_Tilemap.width = g_Tilemap.hSize << 8;
    g_Tilemap.height = g_Tilemap.vSize << 8;
    g_Tilemap.hideTimer = 1;
}

void SetRoomBackgroundLayer(s32 index, LayerDef* layerDef) {
    g_BgLayers[index].flags = 0;
    g_BgLayers[index].tileDef = layerDef->tileDef;
    g_BgLayers[index].layout = layerDef->layout;
    if (g_BgLayers[index].tileDef != 0) {
        g_BgLayers[index].order = layerDef->zPriority;
        g_BgLayers[index].flags = layerDef->flags;
        g_BgLayers[index].w = layerDef->rect.right - layerDef->rect.left + 1;
        g_BgLayers[index].h = layerDef->rect.bottom - layerDef->rect.top + 1;
        g_BgLayers[index].scrollKind = layerDef->rect.params;
        g_BgLayers[index].hideTimer = 1;
    }
}

void LoadRoomLayer(s32 layerIndex) {
    s32 i;

    SetRoomForegroundLayer(g_api.o.tileLayers[layerIndex].fg);
    SetRoomBackgroundLayer(0, g_api.o.tileLayers[layerIndex].bg);

    for (i = 1; i < MAX_BG_LAYER_COUNT; i++) {
        g_BgLayers[i].flags = 0;
    }
}
