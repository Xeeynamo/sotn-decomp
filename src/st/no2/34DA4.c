// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

void func_us_801B4DA4(Entity* self) {
    DRAWENV draw;
    DR_ENV* dr_env;
    Primitive* prim;
    s32 i;
    s32 primIndex;
    u8 flag;

    RECT rect = {.x = 0, .y = 256, .w = 80, .h = 192};

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
            return;
        }
        DestroyEntity(self);
        return;
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
        prim->clut = 0x15F;
        prim->u0 = prim->u2 = 0x10;
        prim->u1 = prim->u3 = 0x20;
        prim->v0 = prim->v1 = 0xD0;
        prim->v2 = prim->v3 = 0xE0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x28;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x28;
        prim->r0 = 0x40;
        prim->g0 = 0x38;
        prim->b0 = 0x38;
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
        prim->tpage = flag ? 0x104 : 0x100;
#endif
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
        prim->x0 = prim->x2 = 0x7B;
        prim->x1 = prim->x3 = 0xC3;
        prim->y0 = prim->y1 = 0x27;
        prim->y2 = prim->y3 = 0x6F;
#ifdef VERSION_PSP
        prim->r0 = 0x20;
        prim->g0 = 0x10;
        prim->b0 = 0x20;
#else
        prim->r0 = 0x10;
        prim->g0 = 0x8;
        prim->b0 = 0x10;
#endif
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x142;
        prim->drawMode =
            DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        return;
    }
}
