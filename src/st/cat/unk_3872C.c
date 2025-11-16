// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

// This entity does not appear in the entity list and looks to be unused
// It is not present in the PSP version.
void func_us_801B872C(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        break;
    case 1:
        if (!(Random() & 7)) {
            newEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                    &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = (Random() & 3) - 0x4000;
            }
        }
        break;
    }
}

void func_us_801B87E8(Entity* self) {
    Primitive* prim;
    u32 primIndex;
    s16 base_x;
    s32 i;
    s16 _unused;

    for (base_x = -g_Tilemap.scrollX.i.hi; base_x < (-0x3E); base_x += 0x3E)
        ;

    _unused = 0x1c;
    if (!self->step) {
        self->step++;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;

        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
            prim = prim->next) {
            prim->x0 = prim->x2 = base_x + ((i & 0x7) * 0x3E);
            prim->x1 = prim->x3 = prim->x0 + 0x3E;
            prim->y1 = prim->y0 = ((i >> 3) * 0x5F) + 0x1C;
            prim->y3 = prim->y2 = prim->y0 + 0x5F;
            prim->u0 = 1;
            prim->v0 = 0x81;
            prim->u1 = 0x3F;
            prim->v1 = 0x81;
            prim->u2 = 1;
            prim->v2 = 0xDE;
            prim->u3 = 0x3F;
            prim->v3 = 0xDE;
            prim->tpage = 0xF;
            prim->clut = 0x8F;
            prim->priority = 0x20;
            prim->drawMode = DRAW_UNK02;
            if (!g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
                prim->drawMode |= DRAW_HIDE | DRAW_COLORS;
            }
        }

        self->ext.et_801B87E8.unk80 = g_CastleFlags[CAT_SPIKE_ROOM_LIT];
    } else {
        if (self->ext.et_801B87E8.unk80 ^ g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
            self->ext.et_801B87E8.unk81 = 1;
        }

        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
            prim = prim->next) {
            if (g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
                prim->drawMode &= ~DRAW_HIDE;
            }
            if (self->ext.et_801B87E8.unk81) {
                if (prim->r0 >= 0x80) {
                    self->ext.et_801B87E8.unk81 = 0;
                } else {
                    prim->r0 += 2;
                    prim->g0 = (prim->b0 = prim->r0);
                    LOWU(prim->r1) = LOWU(prim->r0);
                    LOWU(prim->r2) = LOWU(prim->r0);
                    LOWU(prim->r3) = LOWU(prim->r0);
                }
            }
            prim->x0 = prim->x2 = base_x + (2 * ((i & 7) * 31));
            prim->x1 = prim->x3 = prim->x0 + 0x3E;
        }

        self->ext.et_801B87E8.unk80 = g_CastleFlags[CAT_SPIKE_ROOM_LIT];
    }
    FntPrint("base_x:%04x\n", base_x);
}
