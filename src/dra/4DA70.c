// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

static void DestroyPrimitive(Primitive* prim) {
    s32 i;
    s32 n;
    u32* primData = (u32*)prim;

    for (n = sizeof(Primitive) / sizeof(*primData), i = 0; i < n; i++) {
        *primData++ = 0;
    }
}

void DestroyAllPrimitives(void) {
    s32 i;
    Primitive* prim;

    for (i = 0, prim = g_PrimBuf; i < MAX_PRIM_COUNT; i++) {
        DestroyPrimitive(prim);
        prim->type = PRIM_NONE;
        prim++;
    }
}

s32 func_800EDAE4(void) {
    s32 i;
    DR_ENV* ptr = &D_800974AC[0];

    for (i = 0; i < 16; i++, ptr++) {
        ptr->tag = 0;
    }
#ifdef VERSION_PSP
    return 0;
#endif
}

DR_ENV* func_800EDB08(Primitive* prim) {
    s32 i;
    DR_ENV* dr = &D_800974AC[0];

    for (i = 0; i < LEN(D_800974AC); i++, dr++) {
        if (dr->tag == 0) {
#ifdef VERSION_PSP
            SetDrawEnv(dr, 0);
#endif
            dr->tag = 1;
            setcode(prim, 7);
            *(DR_ENV**)&prim->r1 = dr;
            return dr;
        }
    }

    return NULL;
}

s32 D_800A2438 = 0;

// This function casts its return value as an s16, but at least one caller
// (EntityGravityBootBeam) needs to receive a returned s32 so we use that here.
s32 func_800EDB58(u8 primType, s32 count) {
    s32 primStartIdx;
    s32 i;
    s32 var_v1;
    Primitive* prim;

    var_v1 = count;
    primStartIdx = 0;
    for (i = 0, prim = g_PrimBuf; i < MAX_PRIM_ALLOC_COUNT; prim++, i++) {
        if (prim->type != PRIM_NONE) {
            primStartIdx = i + 1;
            var_v1 = count;
        } else if (--var_v1 == 0) {
            break;
        }
    }
    if (var_v1 != 0) {
        return -1;
    }

    for (i = 0, prim = &g_PrimBuf[primStartIdx]; i < count; i++, prim++) {
        DestroyPrimitive(prim);
        prim->type = primType;
        prim->next = &g_PrimBuf[primStartIdx] + i + 1;
    }
    prim[-1].type &= 0xEF;
    prim[-1].next = NULL;
    // Casted return value as mentioned above
    return (s16)primStartIdx;
}

s16 AllocPrimitives(u8 primType, s32 count) {
    s32 i;
    Primitive* prim;
    s16 index;

    for (i = 0, prim = &g_PrimBuf[0]; i < MAX_PRIM_ALLOC_COUNT; i++, prim++) {
        if (prim->type == PRIM_NONE) {
            DestroyPrimitive(prim);
            if (count == 1) {
                prim->type = primType;
                prim->next = NULL;
                if (D_800A2438 < i) {
                    D_800A2438 = i;
                }
            } else {
                prim->type = primType;
                index = AllocPrimitives(primType, count - 1);
                if (index == -1) {
                    prim->type = PRIM_NONE;
                    return -1;
                }
                prim->next = &g_PrimBuf[index];
            }
            return i;
        }
    }
    return -1;
}

s16 AllocPrimitivesReverse(u8 type, s32 count) {
    s32 i;
    Primitive* prim;
    s16 index;

    for (prim = &g_PrimBuf[LEN(g_PrimBuf) - 1], i = LEN(g_PrimBuf) - 1; i >= 0;
         i--, prim--) {
        if (prim->type == PRIM_NONE) {
            DestroyPrimitive(prim);
            if (count == 1) {
                prim->type = type;
                prim->next = NULL;
            } else {
                prim->type = type;
                index = AllocPrimitivesReverse(type, count - 1);
                prim->next = &g_PrimBuf[index];
            }
            return i;
        }
    }
#if defined(VERSION_PSP)
    return 0;
#endif
}

void FreePrimitives(s32 primitiveIndex) {
    Primitive* prim;

    for (prim = &g_PrimBuf[primitiveIndex]; prim != NULL; prim = prim->next) {
        if (prim->type == PRIM_ENV) {
            **(DR_ENV***)&prim->r1 = NULL;
            prim->type = PRIM_NONE;
        } else {
            prim->type = PRIM_NONE;
        }
    }
}

typedef union {
    TILE tile;
    LINE_G2 g2;
    POLY_G4 g4;
    POLY_GT4 gt4;
    POLY_GT3 gt3;
    SPRT sprt;
} PrimBuf;

typedef struct {
    OT_TYPE* ot;
    POLY_GT4* gt4;
    POLY_G4* g4;
    POLY_GT3* gt3;
    LINE_G2* g2;
    TILE* tile;
    DR_MODE* dr;
    SPRT* sprt;
    DR_ENV* env;
} PrimitivesRenderer;

void RenderPrimitives(void) {
#ifdef VERSION_PSP
#define RECT_LOC 0x12C
#else
#define RECT_LOC 0x128
#endif

#ifdef VERSION_PC
    RECT _rect;
    RECT* rect = &_rect;
    PrimitivesRenderer _r;
    PrimitivesRenderer* r = &_r;
    PrimBuf _primbuf;
    PrimBuf* primbuf = &_primbuf;
#else
    RECT* rect = (RECT*)SP(RECT_LOC);
    PrimitivesRenderer* r = (PrimitivesRenderer*)SP(0x000);
    PrimBuf* primbuf = (PrimBuf*)SP(sizeof(PrimitivesRenderer));
#endif

    s32 i;
    Primitive* prim;
    u8 primType;
    s32 useShadeTex;
    s32 dtd;
    s32 unkBool;

    DRAWENV drawEnv;
    s16 drawOfs;
    DR_ENV* env;

    r->ot = &g_CurrentBuffer->ot[0];
    r->gt4 = &g_CurrentBuffer->polyGT4[g_GpuUsage.gt4];
    r->g4 = &g_CurrentBuffer->polyG4[g_GpuUsage.g4];
    r->gt3 = &g_CurrentBuffer->polyGT3[g_GpuUsage.gt3];
    r->g2 = &g_CurrentBuffer->lineG2[g_GpuUsage.line];
    r->tile = &g_CurrentBuffer->tiles[g_GpuUsage.tile];
    r->dr = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];
    r->sprt = &g_CurrentBuffer->sprite[g_GpuUsage.sp];
    r->env = &g_CurrentBuffer->env[g_GpuUsage.env];
    rect->x = 0;
    rect->y = 0;
    rect->w = 255;
    rect->h = 255;
    if (D_8003C0EC[3]) {
        if (g_GpuUsage.tile < MAX_TILE_COUNT) {
            setSemiTrans(r->tile, false);
            r->tile->r0 = D_8003C0EC[0];
            r->tile->g0 = D_8003C0EC[1];
            r->tile->b0 = D_8003C0EC[2];
            r->tile->x0 = 0;
            r->tile->y0 = 0;
            r->tile->w = DISP_STAGE_W;
            r->tile->h = DISP_STAGE_H;
            addPrim(&r->ot[0], r->tile);
            g_GpuUsage.tile++;
            D_8003C0EC[3]--;
        }
    } else {
        unkBool = 0;
        for (i = 0, prim = &g_PrimBuf[0]; i < MAX_PRIM_COUNT; prim++, i++) {
            primType = prim->type;
            if (!primType) {
                continue;
            }
            if (prim->drawMode & DRAW_HIDE) {
                continue;
            }
            if (prim->drawMode & DRAW_COLORS) {
                useShadeTex = false;
            } else {
                useShadeTex = true;
            }
            if (D_800973EC != 0 && !(prim->drawMode & DRAW_MENU)) {
                continue;
            }
            if (prim->x0 < -512 || prim->x0 > 512) {
                continue;
            }
            if (prim->y0 < -512 || prim->y0 > 512) {
                continue;
            }
            if (prim->drawMode & DRAW_UNK_400) {
                dtd = true;
                if (!unkBool) {
                    SetDrawMode(r->dr, 0, 0, 0, rect);
#ifdef VERSION_PSP
                    if (prim->priority < 0 || prim->priority >= 0x200) {
                        prim->priority = 0x1FF;
                    }
#endif
                    addPrim(&r->ot[prim->priority], r->dr);
                    r->dr++;
                    g_GpuUsage.drawModes++;
                }
            } else {
                dtd = false;
            }
            switch (primType) {
            case PRIM_TILE:
            case PRIM_TILE_ALT:
                setTile(&primbuf->tile);
                if (g_GpuUsage.tile < MAX_TILE_COUNT) {
                    setSemiTrans(&primbuf->tile, prim->drawMode & DRAW_TRANSP);
                    primbuf->tile.r0 = prim->r0;
                    primbuf->tile.g0 = prim->g0;
                    primbuf->tile.b0 = prim->b0;
                    if (prim->drawMode & (DRAW_ABSPOS | DRAW_MENU)) {
                        primbuf->tile.x0 = prim->x0;
                        primbuf->tile.y0 = prim->y0;
                    } else {
                        primbuf->tile.x0 = prim->x0 + g_backbufferX;
                        primbuf->tile.y0 = prim->y0 + g_backbufferY;
                    }
                    primbuf->tile.w = prim->u0;
                    primbuf->tile.h = prim->v0;
                    *r->tile = primbuf->tile;
#ifdef VERSION_PSP
                    if (prim->priority < 0 || prim->priority >= 0x200) {
                        prim->priority = 0x1FF;
                    }
#endif
                    addPrim(&r->ot[prim->priority], r->tile);
                    r->tile++;
                    g_GpuUsage.tile++;
                    if (!(primType & 0x10) &&
                        g_GpuUsage.drawModes < MAX_DRAW_MODES) {
                        SetDrawMode(
                            r->dr, 0, dtd,
                            prim->drawMode & (DRAW_UNK_40 | DRAW_TPAGE2), rect);
#ifdef VERSION_PSP
                        if (prim->priority < 0 || prim->priority >= 0x200) {
                            prim->priority = 0x1FF;
                        }
#endif
                        addPrim(&r->ot[prim->priority], r->dr);
                        r->dr++;
                        g_GpuUsage.drawModes++;
                    }
                }
                break;
            case 2:
            case 18:
                setLineG2(&primbuf->g2);
                if (g_GpuUsage.line < MAX_LINE_G2_COUNT) {
                    setSemiTrans(&primbuf->g2, prim->drawMode & DRAW_TRANSP);
                    setShadeTex(&primbuf->g2, useShadeTex);
                    primbuf->g2.r0 = prim->r0;
                    primbuf->g2.g0 = prim->g0;
                    primbuf->g2.b0 = prim->b0;
                    primbuf->g2.r1 = prim->r1;
                    primbuf->g2.g1 = prim->g1;
                    primbuf->g2.b1 = prim->b1;
                    if (prim->drawMode & (DRAW_ABSPOS | DRAW_MENU)) {
                        primbuf->g2.x0 = prim->x0;
                        primbuf->g2.y0 = prim->y0;
                        primbuf->g2.x1 = prim->x1;
                        primbuf->g2.y1 = prim->y1;
                    } else {
                        primbuf->g2.x0 = prim->x0 + g_backbufferX;
                        primbuf->g2.y0 = prim->y0 + g_backbufferY;
                        primbuf->g2.x1 = prim->x1 + g_backbufferX;
                        primbuf->g2.y1 = prim->y1 + g_backbufferY;
                    }
                    *r->g2 = primbuf->g2;
#ifdef VERSION_PSP
                    if (prim->priority < 0 || prim->priority >= 0x200) {
                        prim->priority = 0x1FF;
                    }
#endif
                    addPrim(&r->ot[prim->priority], r->g2);
                    r->g2++;
                    g_GpuUsage.line++;
                    if ((primType & 0x10) == 0 &&
                        g_GpuUsage.drawModes < MAX_DRAW_MODES) {
                        SetDrawMode(
                            r->dr, 0, dtd,
                            prim->drawMode & (DRAW_UNK_40 | DRAW_TPAGE2), rect);
#ifdef VERSION_PSP
                        if (prim->priority < 0 || prim->priority >= 0x200) {
                            prim->priority = 0x1FF;
                        }
#endif
                        addPrim(&r->ot[prim->priority], r->dr);
                        r->dr++;
                        g_GpuUsage.drawModes++;
                    }
                }
                break;
            case PRIM_G4:
            case 19:
                setPolyG4(&primbuf->g4);
                if (g_GpuUsage.g4 < MAX_POLY_G4_COUNT) {
                    setSemiTrans(&primbuf->g4, prim->drawMode & DRAW_TRANSP);
                    setShadeTex(&primbuf->g4, useShadeTex);
                    primbuf->g4.r0 = prim->r0;
                    primbuf->g4.g0 = prim->g0;
                    primbuf->g4.b0 = prim->b0;
                    primbuf->g4.r1 = prim->r1;
                    primbuf->g4.g1 = prim->g1;
                    primbuf->g4.b1 = prim->b1;
                    primbuf->g4.r2 = prim->r2;
                    primbuf->g4.g2 = prim->g2;
                    primbuf->g4.b2 = prim->b2;
                    primbuf->g4.r3 = prim->r3;
                    primbuf->g4.g3 = prim->g3;
                    primbuf->g4.b3 = prim->b3;
                    if (prim->drawMode & (DRAW_ABSPOS | DRAW_MENU)) {
                        primbuf->g4.x0 = prim->x0;
                        primbuf->g4.y0 = prim->y0;
                        primbuf->g4.x1 = prim->x1;
                        primbuf->g4.y1 = prim->y1;
                        primbuf->g4.x2 = prim->x2;
                        primbuf->g4.y2 = prim->y2;
                        primbuf->g4.x3 = prim->x3;
                        primbuf->g4.y3 = prim->y3;
                    } else {
                        primbuf->g4.x0 = prim->x0 + g_backbufferX;
                        primbuf->g4.y0 = prim->y0 + g_backbufferY;
                        primbuf->g4.x1 = prim->x1 + g_backbufferX;
                        primbuf->g4.y1 = prim->y1 + g_backbufferY;
                        primbuf->g4.x2 = prim->x2 + g_backbufferX;
                        primbuf->g4.y2 = prim->y2 + g_backbufferY;
                        primbuf->g4.x3 = prim->x3 + g_backbufferX;
                        primbuf->g4.y3 = prim->y3 + g_backbufferY;
                    }
                    *r->g4 = primbuf->g4;
#ifdef VERSION_PSP
                    if (prim->priority < 0 || prim->priority >= 0x200) {
                        prim->priority = 0x1FF;
                    }
#endif
                    addPrim(&r->ot[prim->priority], r->g4);
                    r->g4++;
                    g_GpuUsage.g4++;
                    if ((primType & 0x10) == 0 &&
                        g_GpuUsage.drawModes < MAX_DRAW_MODES) {
                        SetDrawMode(
                            r->dr, 0, dtd,
                            prim->drawMode & (DRAW_UNK_40 | DRAW_TPAGE2), rect);
#ifdef VERSION_PSP
                        if (prim->priority < 0 || prim->priority >= 0x200) {
                            prim->priority = 0x1FF;
                        }
#endif
                        addPrim(&r->ot[prim->priority], r->dr);
                        r->dr++;
                        g_GpuUsage.drawModes++;
                    }
                }
                break;
            case PRIM_GT4:
                setPolyGT4(&primbuf->gt4);
                if (g_GpuUsage.gt4 < MAX_POLY_GT4_COUNT) {
                    setSemiTrans(&primbuf->gt4, prim->drawMode & DRAW_TRANSP);
                    setShadeTex(&primbuf->gt4, useShadeTex);
                    primbuf->gt4.r0 = prim->r0;
                    primbuf->gt4.g0 = prim->g0;
                    primbuf->gt4.b0 = prim->b0;
                    primbuf->gt4.r1 = prim->r1;
                    primbuf->gt4.g1 = prim->g1;
                    primbuf->gt4.b1 = prim->b1;
                    primbuf->gt4.r2 = prim->r2;
                    primbuf->gt4.g2 = prim->g2;
                    primbuf->gt4.b2 = prim->b2;
                    primbuf->gt4.r3 = prim->r3;
                    primbuf->gt4.g3 = prim->g3;
                    primbuf->gt4.b3 = prim->b3;
                    if (prim->drawMode & (DRAW_ABSPOS | DRAW_MENU)) {
                        primbuf->gt4.x0 = prim->x0;
                        primbuf->gt4.y0 = prim->y0;
                        primbuf->gt4.x1 = prim->x1;
                        primbuf->gt4.y1 = prim->y1;
                        primbuf->gt4.x2 = prim->x2;
                        primbuf->gt4.y2 = prim->y2;
                        primbuf->gt4.x3 = prim->x3;
                        primbuf->gt4.y3 = prim->y3;
                    } else {
                        primbuf->gt4.x0 = prim->x0 + g_backbufferX;
                        primbuf->gt4.y0 = prim->y0 + g_backbufferY;
                        primbuf->gt4.x1 = prim->x1 + g_backbufferX;
                        primbuf->gt4.y1 = prim->y1 + g_backbufferY;
                        primbuf->gt4.x2 = prim->x2 + g_backbufferX;
                        primbuf->gt4.y2 = prim->y2 + g_backbufferY;
                        primbuf->gt4.x3 = prim->x3 + g_backbufferX;
                        primbuf->gt4.y3 = prim->y3 + g_backbufferY;
                    }
                    primbuf->gt4.u0 = prim->u0;
                    primbuf->gt4.v0 = prim->v0;
                    primbuf->gt4.u1 = prim->u1;
                    primbuf->gt4.v1 = prim->v1;
                    primbuf->gt4.u2 = prim->u2;
                    primbuf->gt4.v2 = prim->v2;
                    primbuf->gt4.u3 = prim->u3;
                    primbuf->gt4.v3 = prim->v3;
                    primbuf->gt4.tpage =
                        prim->tpage +
                        (prim->drawMode & (DRAW_UNK_40 | DRAW_TPAGE2));
                    primbuf->gt4.clut = g_ClutIds[prim->clut];
                    *r->gt4 = primbuf->gt4;
#ifdef VERSION_PSP
                    if (prim->priority < 0 || prim->priority >= 0x200) {
                        prim->priority = 0x1FF;
                    }
#endif
                    addPrim(&r->ot[prim->priority], r->gt4);
                    r->gt4++;
                    g_GpuUsage.gt4++;
                    if (dtd && g_GpuUsage.drawModes < MAX_DRAW_MODES) {
                        SetDrawMode(r->dr, 0, dtd, 0, rect);
#ifdef VERSION_PSP
                        if (prim->priority < 0 || prim->priority >= 0x200) {
                            prim->priority = 0x1FF;
                        }
#endif
                        addPrim(&r->ot[prim->priority], r->dr);
                        r->dr++;
                        g_GpuUsage.drawModes++;
                    }
                }
                break;
            case PRIM_GT3:
                setPolyGT3(&primbuf->gt3);
                if (g_GpuUsage.gt3 < MAX_POLY_GT3_COUNT) {
                    setSemiTrans(&primbuf->gt3, prim->drawMode & DRAW_TRANSP);
                    setShadeTex(&primbuf->gt3, useShadeTex);
                    primbuf->gt3.r0 = prim->r0;
                    primbuf->gt3.g0 = prim->g0;
                    primbuf->gt3.b0 = prim->b0;
                    primbuf->gt3.r1 = prim->r1;
                    primbuf->gt3.g1 = prim->g1;
                    primbuf->gt3.b1 = prim->b1;
                    primbuf->gt3.r2 = prim->r2;
                    primbuf->gt3.g2 = prim->g2;
                    primbuf->gt3.b2 = prim->b2;
                    if (prim->drawMode & (DRAW_ABSPOS | DRAW_MENU)) {
                        primbuf->gt3.x0 = prim->x0;
                        primbuf->gt3.y0 = prim->y0;
                        primbuf->gt3.x1 = prim->x1;
                        primbuf->gt3.y1 = prim->y1;
                        primbuf->gt3.x2 = prim->x2;
                        primbuf->gt3.y2 = prim->y2;
                    } else {
                        primbuf->gt3.x0 = prim->x0 + g_backbufferX;
                        primbuf->gt3.y0 = prim->y0 + g_backbufferY;
                        primbuf->gt3.x1 = prim->x1 + g_backbufferX;
                        primbuf->gt3.y1 = prim->y1 + g_backbufferY;
                        primbuf->gt3.x2 = prim->x2 + g_backbufferX;
                        primbuf->gt3.y2 = prim->y2 + g_backbufferY;
                    }
                    primbuf->gt3.u0 = prim->u0;
                    primbuf->gt3.v0 = prim->v0;
                    primbuf->gt3.u1 = prim->u1;
                    primbuf->gt3.v1 = prim->v1;
                    primbuf->gt3.u2 = prim->u2;
                    primbuf->gt3.v2 = prim->v2;
                    primbuf->gt3.tpage =
                        prim->tpage +
                        (prim->drawMode & (DRAW_UNK_40 | DRAW_TPAGE2));
                    primbuf->gt3.clut = g_ClutIds[prim->clut];

                    *r->gt3 = primbuf->gt3;
#ifdef VERSION_PSP
                    if (prim->priority < 0 || prim->priority >= 0x200) {
                        prim->priority = 0x1FF;
                    }
#endif
                    addPrim(&r->ot[prim->priority], r->gt3);
                    r->gt3++;
                    g_GpuUsage.gt3++;
                    if (dtd && g_GpuUsage.drawModes < MAX_DRAW_MODES) {
                        SetDrawMode(r->dr, 0, dtd, 0, rect);
#ifdef VERSION_PSP
                        if (prim->priority < 0 || prim->priority >= 0x200) {
                            prim->priority = 0x1FF;
                        }
#endif
                        addPrim(&r->ot[prim->priority], r->dr);
                        r->dr++;
                        g_GpuUsage.drawModes++;
                    }
                }
                break;
            case PRIM_SPRT:
            case 22:
                setSprt(&primbuf->sprt);
                if (g_GpuUsage.sp < MAX_SPRT_COUNT) {
                    setSemiTrans(&primbuf->sprt, prim->drawMode & DRAW_TRANSP);
                    setShadeTex(&primbuf->sprt, useShadeTex);
                    primbuf->sprt.r0 = prim->r0;
                    primbuf->sprt.g0 = prim->g0;
                    primbuf->sprt.b0 = prim->b0;
                    if (prim->drawMode & (DRAW_ABSPOS | DRAW_MENU)) {
                        primbuf->sprt.x0 = prim->x0;
                        primbuf->sprt.y0 = prim->y0;
                    } else {
                        primbuf->sprt.x0 = prim->x0 + g_backbufferX;
                        primbuf->sprt.y0 = prim->y0 + g_backbufferY;
                    }
                    primbuf->sprt.u0 = prim->u0;
                    primbuf->sprt.v0 = prim->v0;
                    primbuf->sprt.w = prim->u1;
                    primbuf->sprt.h = prim->v1;
                    primbuf->sprt.clut = g_ClutIds[prim->clut];
                    *r->sprt = primbuf->sprt;
#ifdef VERSION_PSP
                    if (prim->priority < 0 || prim->priority >= 0x200) {
                        prim->priority = 0x1FF;
                    }
#endif
                    addPrim(&r->ot[prim->priority], r->sprt);
                    r->sprt++;
                    g_GpuUsage.sp++;
                    if ((primType & 0x10) == 0 &&
                        g_GpuUsage.drawModes < MAX_DRAW_MODES) {
                        SetDrawMode(r->dr, 0, dtd,
                                    prim->tpage + (prim->drawMode &
                                                   (DRAW_UNK_40 | DRAW_TPAGE2)),
                                    rect);
#ifdef VERSION_PSP
                        if (prim->priority < 0 || prim->priority >= 0x200) {
                            prim->priority = 0x1FF;
                        }
#endif
                        addPrim(&r->ot[prim->priority], r->dr);
                        r->dr++;
                        g_GpuUsage.drawModes++;
                    }
                }
                break;
            case PRIM_ENV:
                if (g_GpuUsage.env < MAX_ENV_COUNT) {
                    env = *(DR_ENV**)&prim->r1;
                    if (prim->drawMode & DRAW_UNK_1000) {
                        drawOfs = g_CurrentBuffer->draw.ofs[0];
#ifndef VERSION_PSP
                        *(s16*)&env->code[2] = drawOfs;
                        *(s16*)&env->code[7] = drawOfs;
#endif
#ifdef VERSION_PSP
                        env->ofs[0] = drawOfs;
                        env->clip.x = drawOfs;
#endif
                    }
                    if (prim->drawMode & DRAW_UNK_800) {
                        drawEnv = g_CurrentBuffer->draw;
                        drawEnv.isbg = 0;
                        SetDrawEnv(env, &drawEnv);
                    }
                    *r->env = *env;
#ifndef VERSION_PSP
                    if (prim->drawMode & DRAW_UNK_1000) {
                        env = r->env;
                        *(s16*)&env->code[0] += drawOfs;
                        *(s16*)&env->code[1] += drawOfs;
                    }
#endif
#ifdef VERSION_PSP
                    if (prim->priority < 0 || prim->priority >= 0x200) {
                        prim->priority = 0x1FF;
                    }
#endif
                    addPrim(&r->ot[prim->priority], r->env);
                    r->env++;
                    g_GpuUsage.env++;
                }
                break;
            }
            if (primType & 0x10) {
                unkBool = true;
            } else {
                unkBool = false;
            }
        }
    }
}
