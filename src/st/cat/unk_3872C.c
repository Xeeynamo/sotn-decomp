// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801B872C);

void func_us_801B87E8(Entity* self) {
    Primitive* prim;
    s16 base_x;
    s32 cntr;
    u8 castleFlag;

    for (base_x = -g_Tilemap.scrollX.i.hi; base_x < (-0x3E); base_x += 0x3E)
        ;

    if (!self->step) {
        self->step++;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);

        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        cntr = 0;
        while (prim) {
            prim->x0 = prim->x2 = base_x + ((cntr & 0x7) * 0x3E);
            prim->x1 = prim->x3 = prim->x0 + 0x3E;
            prim->y1 = prim->y0 = ((cntr >> 3) * 0x5F) + 0x1C;
            prim->tpage = 0xF;
            prim->clut = 0x8F;
            prim->priority = 0x20;
            prim->u0 = 1;
            prim->v0 = 0x81;
            prim->u1 = 0x3F;
            prim->v1 = 0x81;
            prim->u2 = 1;
            prim->v2 = 0xDE;
            prim->u3 = 0x3F;
            prim->v3 = 0xDE;
            prim->drawMode = DRAW_UNK02;
            prim->y3 = prim->y2 = prim->y0 + 0x5F;
            if (g_CastleFlags[CAT_SPIKE_ROOM_LIT] == 0) {
                prim->drawMode = DRAW_HIDE | DRAW_COLORS | DRAW_UNK02;
            }
            prim = prim->next;
            cntr++;
        }

    } else {
        cntr = 0;
        if (self->ext.et_801B87E8.unk80 != g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
            self->ext.et_801B87E8.unk81 = 1;
        }
        prim = &g_PrimBuf[self->primIndex];
        while (prim != 0) {
            if (g_CastleFlags[CAT_SPIKE_ROOM_LIT] != 0) {
                prim->drawMode &= ~DRAW_HIDE;
            }
            if (self->ext.et_801B87E8.unk81 != 0) {
                if (prim->r0 > 0x7f) {
                    self->ext.et_801B87E8.unk81 = 0;
                } else {
                    prim->r0 = prim->r0 + 2;
                    prim->g0 = (prim->b0 = prim->r0);
                    LOWU(prim->r1) = LOWU(prim->r0);
                    LOWU(prim->r2) = LOWU(prim->r0);
                    LOWU(prim->r3) = LOWU(prim->r0);
                }
            }
            prim->x0 = prim->x2 = base_x + (2 * ((cntr & 7) * 31));
            prim->x1 = prim->x3 = prim->x0 + 0x3E;
            prim = prim->next;
            cntr++;
        }
    }

    castleFlag = g_CastleFlags[CAT_SPIKE_ROOM_LIT];
    do {
        self->ext.et_801B87E8.unk80 = castleFlag;
        FntPrint("base_x:%04x\n", base_x);
    } while (0);
}

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801B8AD0);
