// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno2/rno2.h"

extern RECT g_Rno2DrawEnvClip;

void func_us_801B4DA4_from_bo0(Entity* self) {
    DRAWENV draw;
    DR_ENV* dr_env;
    Primitive* prim;
    s32 i;
    s32 primIndex;
    u8 flag;

    RECT rect = g_Rno2DrawEnvClip;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        primIndex = g_api.func_800EDB58(PRIM_GT4, 8);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            prim->priority = 0x13F;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            prim->priority = 0x141;
            prim->drawMode = DRAW_UNK_800;
            prim = prim->next;
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 1:
        prim = &g_PrimBuf[self->primIndex];
        draw = g_CurrentBuffer->draw;
        if (draw.ofs[0] == 0) {
            flag = 0;
        } else {
            flag = 1;
        }
        draw.isbg = 1;
        draw.r0 = 0;
        draw.g0 = 0;
        draw.b0 = 0;
        draw.dtd = 1;
        draw.clip = rect;
        draw.ofs[0] = 0;
        draw.ofs[1] = 0x100;
        dr_env = *(DR_ENV**)&prim->r1;
        SetDrawEnv(dr_env, &draw);
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim = self->ext.prim;

        for (i = 2; i >= 0; i--) {
            prim->type = PRIM_GT4;
#ifdef VERSION_PSP
            prim->tpage = 0x1110;
#else
            prim->tpage = 0x110;
#endif
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = prim->u0 + 0x28;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = prim->v0 + 0x28;
            prim->x0 = prim->x2 = i * 0xA;
            prim->x1 = prim->x3 = prim->x0 + (0x50 - (i * 0x14));
            prim->y0 = prim->y1 = (i * 0xA) + 0x40;
            prim->y2 = prim->y3 = prim->y0 + (0x50 - (i * 0x14));
            prim->r0 = prim->g0 = prim->b0 = 0xFF;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0x140;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            if (i == 0) {
                prim->drawMode = DRAW_DEFAULT;
            }
            prim->drawMode |= DRAW_COLORS;
            prim = prim->next;
        }

        prim->type = PRIM_GT4;
#ifdef VERSION_PSP
        prim->tpage = 0x101A;
#else
        prim->tpage = 0x1A;
#endif
        prim->clut = PAL_FILL_WHITE;
        prim->u0 = prim->u2 = 0x10;
        prim->u1 = prim->u3 = 0x20;
        prim->v0 = prim->v1 = 0xD0;
        prim->v2 = prim->v3 = 0xE0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x28;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x28;
        prim->r0 = 0x48;
        prim->g0 = 0x30;
        prim->b0 = 0x48;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x140;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;

        prim = prim->next;
        prim->type = PRIM_GT4;
#ifdef VERSION_PSP
        prim->tpage = 0x104;
#else
        if (flag) {
            prim->tpage = 0x104;
        } else {
            prim->tpage = 0x100;
        }
#endif
        prim->u0 = prim->u2 = 0x49;
        prim->u1 = prim->u3 = 0x71;
        prim->v0 = prim->v1 = 0x97;
        prim->v2 = prim->v3 = 0xBF;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x28;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x28;
        prim->priority = 0x140;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        prim->type = PRIM_GT4;
#ifdef VERSION_PSP
        prim->tpage = 0x1110;
#else
        prim->tpage = 0x110;
#endif
        prim->u0 = prim->u2 = 4;
        prim->u1 = prim->u3 = 0x4C;
        prim->v0 = prim->v1 = 0x44;
        prim->v2 = prim->v3 = 0x8C;
        prim->x0 = prim->x2 = 0x39;
        prim->x1 = prim->x3 = 0x81;
        prim->y0 = prim->y1 = 0x87;
        prim->y2 = prim->y3 = 0xCF;
#ifdef VERSION_PSP
        prim->r0 = 0x20;
        prim->g0 = 0x10;
        prim->b0 = 0x20;
#else
        prim->r0 = 0x10;
        prim->g0 = 8;
        prim->b0 = 0x10;
#endif
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x142;
        prim->drawMode = DRAW_DITHERING | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_COLORS | DRAW_TRANSP;
        break;
    }
}

void func_us_801B3D8C_from_bo0(Entity* self) {
    Primitive* prim;
    s16 xOffset;
    s16 yOffset;
    s32 i;

    if (self->params) {
        xOffset = 0;
        yOffset = -0x80;
    } else {
        xOffset = 0;
        yOffset = 0x30;
    }

    if (!self->step) {
        self->step += 1;
        if (self->params) {
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        } else {
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        }

        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            prim->u1 = 0x80;
            prim->v2 = 0;
            prim->u0 = 0xC8;
            prim->v3 = 0;
            prim->u3 = 0x80;
            prim->v0 = 0x68;
            prim->u2 = 0xC8;
            prim->v1 = 0x68;

            prim->x0 = prim->x2 = xOffset + ((i & 7) << 6);
            prim->x1 = prim->x3 = prim->x0 + 0x48;
            prim->y1 = prim->y0 = yOffset + ((i >> 3) * 0x64);
            prim->y3 = prim->y2 = prim->y0 + 0x6C;

            prim->tpage = 0xF;
            prim->clut = 0x36;
            prim->priority = 0x1E;
            prim->drawMode = DRAW_DEFAULT;
        }
    }
}

void func_us_801B3F30_from_bo0(Entity* self) {
    u8 colorLo;
    u16 color;
    s16 deltaPosXHi;
    s16 absDeltaPosXHi;
    u32 curPal;
    s32 i;
    s32 j;

    extern EInit g_EInitCommon;
    extern s32 g_Unk17ClutIds[];
    extern u16 g_Unk17PaletteAnim[];

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 3;
        self->ext.et_801B3F30.unk7C = 2;
        self->ext.et_801B3F30.unk80 = 0x10;
        self->zPriority = 0x80;
        self->blendMode = BLEND_TRANSP | BLEND_QUARTER;
        break;
    case 1:
        if (g_Tilemap.scrollY.i.hi >= 0x304) {
            deltaPosXHi = self->posX.i.hi - PLAYER.posX.i.hi;
            absDeltaPosXHi = abs(deltaPosXHi);
            if (absDeltaPosXHi < 0x80) {
                self->step++;
            }
        }
        break;
    case 2:
        if (--self->ext.et_801B3F30.unk80 == 0) {
            for (i = 0; i < 7; i++) {
                curPal = g_Unk17ClutIds[i];
                for (j = 1; j < 16; j++) {
                    color = g_Clut[0][0x400 + curPal * COLORS_PER_PAL + j];
                    colorLo = color & 0x1F;
                    colorLo++;
                    if (colorLo > 0x1F) {
                        colorLo = 0x1F;
                    }
                    g_Clut[0][0x400 + curPal * COLORS_PER_PAL + j] =
                        (color & ~0x1F) + colorLo;
                }
            }
            LoadClut((void*)&(g_Clut[0][0x400]), 0x200, 0xF4);
            self->ext.et_801B3F30.unk80 = 0x10;
        }
        break;
    }

    if (--self->ext.et_801B3F30.unk7C == 0) {
        self->ext.et_801B3F30.unk7E++;
        self->ext.et_801B3F30.unk7C = 2;
    }
    if (self->ext.et_801B3F30.unk7E > 6) {
        self->ext.et_801B3F30.unk7E = 0;
    }
    self->palette = g_Unk17PaletteAnim[self->ext.et_801B3F30.unk7E];
}

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1ED70", func_us_801B4148_from_bo0);

void func_us_801B41A4_from_bo0(Entity* self) {
    if (g_CurrentEntity->step == 0) {
        g_CurrentEntity->step++;
    }
    g_GpuBuffers[0].draw.r0 = 0x20;
    g_GpuBuffers[0].draw.g0 = 0x18;
    g_GpuBuffers[0].draw.b0 = 0x28;
    g_GpuBuffers[1].draw.r0 = 0x20;
    g_GpuBuffers[1].draw.g0 = 0x18;
    g_GpuBuffers[1].draw.b0 = 0x28;
}

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1ED70", func_us_801B4210_from_bo0);

void EntityBackgroundBlock(Entity* self) {
    extern ObjInit2 BackgroundBlockInit[];
    extern EInit g_EInitCommon;

    ObjInit2* objInit = &BackgroundBlockInit[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = LOHU(objInit->facingLeft);
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->blendMode = objInit->blendMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1ED70", EntityPrisoner);
