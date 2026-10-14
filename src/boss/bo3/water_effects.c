// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

extern EInit g_EInitInteractable;
extern EInit g_EInitCommon;
extern s16 water_surface_lines[];
extern s16 water_tile_rects[];

s16 D_us_80180C64 = 0;
u16 D_us_80180C66 = 0;
s16 D_us_80180C68[] = {0x0000, 0x04D0, 0x00D8, 0x00E8, 0x0068, 0x00B0,
                       0x00F0, 0x00F0, 0x0340, 0x0074, 0x00F0, 0x00F0};

#ifdef VERSION_PSP
char D_pspeu_09265D48[] = "mizu %x\n";
#endif

s32 g_SplashYMovement[] = {FIX(-6.5), FIX(9.0 / 32), FIX(-5.5), FIX(17.0 / 64),
                           FIX(-4.5), FIX(0.25),     FIX(-3.5), FIX(15.0 / 64)};
s16 g_SurfacingYTbl[] = {0, 2, 4, 6, 8, 10};
static s16 water_slow_zones[] = {
    0x260, 0x020, 0x0D0, 0x080, 0x470, 0x020,
    0x0D0, 0x080, 0x0C0, 0x02C, 0x0E0, 0x500,
};
s16 D_us_80180CC4[] = {0x01E0, 0x0060, 0x0061, 0x006E, 0x01FF, 0x01E0};
u8 D_us_80180CD0[] = {0, 0, 0, 1, 1, 0, 0, 0};
u16 D_us_80180CD8[] = {
    0x0373, 0x0000, 0x0000, 0x0000, 0x075E, 0x0001, 0x0001, 0x0001,
    0x0375, 0x0000, 0x0000, 0x0000, 0x0765, 0x0001, 0x0001, 0x0001,
    0x03F2, 0x0000, 0x0000, 0x0000, 0x075C, 0x0001, 0x0001, 0x0001,
    0x072D, 0x0000, 0x0000, 0x0000, 0x075D, 0x0001, 0x0001, 0x0001,
    0x0375, 0x0000, 0x0000, 0x0969, 0x0762, 0x0001, 0x0001, 0x0764,
    0x0933, 0x0000, 0x0000, 0x0951, 0x0761, 0x0001, 0x0001, 0x0763};
static s16 g_splashAspects[] = {0, 1, 2, 4, -1, -2, -4, 0};

s16 D_us_801B2870[2];
s32 D_us_801B2874;

void func_us_801A071C(void) {
    s16* data;
    s16* tileRects;
    s16* surfaceLines;
    s16 value;

    data = D_us_80180C68;
    tileRects = water_tile_rects;
    surfaceLines = water_surface_lines;
    data += 2;
    tileRects += 0x6E;
    surfaceLines += 0x70;

    value = 0xD8 - D_us_80180C64;
    if (value < 0x18) {
        value = 0;
    }
    *data = value;
    *tileRects = value;
    *surfaceLines = value;
    data += 4;
    tileRects += 4;
    surfaceLines += 5;

    if (D_us_80180C64 < 0xC0) {
        value = 0xF0;
    } else {
        value = 0x1A8 - D_us_80180C64;
    }
    *data = value;
    data += 4;
    *data = value;
    if (value > 0xE8) {
        value = 0xE8;
    }
    *surfaceLines = value;
    surfaceLines += 5;
    *surfaceLines = value;
    value++;
    *tileRects = value;
    tileRects += 4;
    *tileRects = value;
}

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A07CC);

u16 func_us_801A09DC(s16 index, s16 x, s16 y, s16* out) {
    s16* data;
    s16 value;

    data = &D_us_80180C68[index * 4];
    x -= *data++;
    if (x < 0) {
        return 0;
    }
    *out++ = x;
    value = *data++ - x;
    if (value <= 0) {
        return 0;
    }
    *out = value;
    value = *data++;
    if (value > y) {
        return 0;
    }
    if (y >= *data++) {
        return 0;
    }
    return y + 0x8000 - value;
}

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A0A80);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A1120);

void func_us_801A16E4(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Primitive* prim;
    u16 params;
    s16 aspect;
    s32 primIndex;
    s16 x, y;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        aspect = (self->posX.i.hi - 120) >> 4;
        if (aspect < -8) {
            aspect = -8;
        }
        if (aspect > 8) {
            aspect = 8;
        }
        params = self->params;
        if (!(params & 0x8000)) {
            g_api.PlaySfxVolPan(SFX_WATER_SPLASH_MOVE, 0x7F, aspect);
        }
        params = (params >> 8) & 0x7F;
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        self->ext.waterEffects.unk82 = y + tilemap->scrollY.i.hi;
        prim = &g_PrimBuf[primIndex];
        for (i = 0; i < 2; i++) {
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x1E;
            prim->v0 = prim->v1 = 0x60;
            prim->v2 = prim->v3 = 0x7C;
            prim->y2 = prim->y3 = y;
            prim->x2 = prim->x0 = x - 9;
            prim->x3 = prim->x1 = x + 9;
            PGREY(prim, 0) = PGREY(prim, 1) = 255;
            PGREY(prim, 2) = PGREY(prim, 3) = 128;
            prim->clut = PAL_CC_MAGIC_HUD_EFFECT;
            prim->tpage = 0x1A;
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            if (i != 0) {
                prim->clut = PAL_CC_STONE_EFFECT;
                prim->priority = self->zPriority + 4;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }
        self->ext.waterEffects.topY.i.hi =
            g_SurfacingYTbl[self->params & 0xFF] + 12 + (rand() & 1);
        break;

    case 1:
        self->ext.waterEffects.topY.val -= FIX(0.25);
        break;
    }

    self->posY.i.hi += D_us_801B2870[0];
    x = self->posX.i.hi;
    y = self->ext.waterEffects.unk82 - self->posY.i.hi - tilemap->scrollY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 2; i++) {
        prim->y2 -= y;
        prim->y3 -= y;
        prim->y0 = prim->y2 - self->ext.waterEffects.topY.i.hi;
        prim->y1 = prim->y3 - self->ext.waterEffects.topY.i.hi;
        prim->x2 = prim->x0 = x - 9;
        prim->x3 = prim->x1 = x + 9;
        prim->b1 -= 8;
        PGREY(prim, 0) = PGREY(prim, 1);
        prim->b3 -= 4;
        PGREY(prim, 2) = PGREY(prim, 3);
        if (prim->r0 < 9) {
            DestroyEntity(self);
            return;
        }
        prim = prim->next;
    }
    self->ext.waterEffects.unk82 = self->posY.i.hi + tilemap->scrollY.i.hi;
}

#include "../../st/water_slow_zone.h"

void func_us_801B5004(Tilemap* map, s32 arg1) {
    Tilemap* tmap;
    s16 tilePos;
    u16* tileData;
    s32 i;

    tmap = &g_Tilemap;
    tilePos = D_us_80180CC4[arg1 >> 1];
    tileData = &D_us_80180CD8[arg1 << 2];

    for (i = 0; i < 4; i++) {
        tmap->fg[tilePos] = *tileData++;
        tilePos += tmap->hSize << 4;
    }
}

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A1BE8);

#include "../../st/entity_splash_water.h"

#include "../../st/entity_water_drop.h"
