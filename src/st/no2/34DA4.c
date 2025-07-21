// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

// already in e_init.c
extern EInit D_us_80180844[];
// st/no2/data/34DA4.rodata.s
extern RECT D_us_801B2E20;

void func_us_801B4DA4(Entity* self) {
    DRAWENV draw;
    RECT rect;
    DR_ENV* dr_env;
    Prim_801B4DA4* prim;
    s32 i;
    s32 primIndex;
    u8 flag;

    rect = D_us_801B2E20;
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180844);
        primIndex = g_api.func_800EDB58(4, 8);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = (Prim_801B4DA4*)&g_PrimBuf[primIndex];
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->union0.rgb.type = 7;
            prim->priority = 0x13F;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->union0.rgb.type = 7;
            prim->priority = 0x141;
            prim->drawMode = DRAW_UNK_800;
            prim = prim->next;
            self->ext.prim = (Primitive*)prim;
            for (; prim != NULL; prim = prim->next) {
                prim->drawMode = DRAW_HIDE;
            }
            return;
        }
        DestroyEntity(self);
        return;
    case 1:
        prim = (Prim_801B4DA4*)&g_PrimBuf[self->primIndex];
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
        dr_env = prim->union1.drenv1;
        SetDrawEnv(dr_env, &draw);
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim = self->ext.et_801B4DA4.prim;
        for (i = 2; i >= 0; i--) {
            prim->union0.rgb.type = 4;
            prim->tpage = 0x110;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = prim->u0 + 0x28;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = prim->v0 + 0x28;
            prim->x0 = prim->x2 = i * 0xA;
            prim->x1 = prim->x3 = prim->x0 + (0x50 - (i * 0x14));
            prim->y0 = prim->y1 = (i * 0xA) + 0x40;
            prim->y2 = prim->y3 = prim->y0 + (0x50 - (i * 0x14));
            prim->union0.rgb.r0 = prim->union0.rgb.g0 = prim->union0.rgb.b0 =
                0xFF;
            prim->union1.drenv1 = prim->union0.drenv0;
            prim->union2.drenv2 = prim->union0.drenv0;
            prim->union3.drenv3 = prim->union0.drenv0;
            prim->priority = 0x140;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            if (i == 0) {
                prim->drawMode = DRAW_DEFAULT;
            }
            prim->drawMode |= DRAW_COLORS;
            prim = prim->next;
        }
        prim->union0.rgb.type = 4;
        prim->tpage = 0x1A;
        prim->clut = 0x15F;
        prim->u0 = prim->u2 = 0x10;
        prim->u1 = prim->u3 = 0x20;
        prim->v0 = prim->v1 = 0xD0;
        prim->v2 = prim->v3 = 0xE0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x28;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x28;
        prim->union0.rgb.r0 = 0x40;
        prim->union0.rgb.g0 = 0x38;
        prim->union0.rgb.b0 = 0x38;
        prim->union1.drenv1 = prim->union0.drenv0;
        prim->union2.drenv2 = prim->union0.drenv0;
        prim->union3.drenv3 = prim->union0.drenv0;
        prim->priority = 0x140;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim = prim->next;
        prim->union0.rgb.type = 4;
        prim->tpage = (flag) ? 0x104 : 0x100;
        prim->u0 = prim->u2 = 0x8B;
        prim->u1 = prim->u3 = 0xB3;
        prim->v0 = prim->v1 = 0x37;
        prim->v2 = prim->v3 = 0x5F;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x28;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x28;
        prim->priority = 0x140;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->union0.rgb.type = 4;
        prim->tpage = 0x110;
        prim->u0 = prim->u2 = 4;
        prim->u1 = prim->u3 = 0x4C;
        prim->v0 = prim->v1 = 0x44;
        prim->v2 = prim->v3 = 0x8C;
        prim->x0 = prim->x2 = 0x7B;
        prim->x1 = prim->x3 = 0xC3;
        prim->y0 = prim->y1 = 0x27;
        prim->y2 = prim->y3 = 0x6F;
        prim->union0.rgb.r0 = 0x10;
        prim->union0.rgb.g0 = 0x8;
        prim->union0.rgb.b0 = 0x10;
        prim->union1.drenv1 = prim->union0.drenv0;
        prim->union2.drenv2 = prim->union0.drenv0;
        prim->union3.drenv3 = prim->union0.drenv0;
        prim->priority = 0x142;
        prim->drawMode =
            DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        return;
    }
}

INCLUDE_ASM("st/no2/nonmatchings/34DA4", func_us_801B52B4);

INCLUDE_ASM("st/no2/nonmatchings/34DA4", func_us_801B5368);

INCLUDE_ASM("st/no2/nonmatchings/34DA4", func_us_801B5578);

INCLUDE_ASM("st/no2/nonmatchings/34DA4", func_us_801B56A4);

INCLUDE_ASM("st/no2/nonmatchings/34DA4", func_us_801B5750);

INCLUDE_ASM("st/no2/nonmatchings/34DA4", func_us_801B5948);

INCLUDE_RODATA("st/no2/nonmatchings/34DA4", D_us_801B2E20);
