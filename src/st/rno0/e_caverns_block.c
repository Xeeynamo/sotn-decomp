// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

extern EInit g_EInitCommon;

// Defines the left, right, top, bottom UV coordinates for tile textures
#define UUVV(u1, u2, v1, v2) u1, u2, v1, v2
static u8 tileUVs[] = {
    UUVV(144, 216, 64, 88), UUVV(216, 255, 0, 40), UUVV(216, 255, 40, 80)
};
// Defines the left, right, top, and bottom offsets for each tile
#define LRTB(l, r, t, b) l, r, t, b
static s16 tileXYs[] = {
    LRTB(32, -36, 0, 24), LRTB(0, -35, -32, 8),   LRTB(38, -1, -32, 8),
    LRTB(-5, 67, 0, -24), LRTB(27, 66, 32, -8),   LRTB(-67, -28, 32, -8),
    LRTB(-33, 39, 0, 24), LRTB(-1, 38, -32, 8),   LRTB(-39, 0, -32, 8),
    LRTB(4, -68, 0, -24), LRTB(-28, -67, 32, -8), LRTB(66, 27, 32, -8)};

// Unused
void EntityCavernsBlockButton(Entity* self) {}

void EntityPinkCavernsBlock(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s16 i;
    u16 params;
    u8* var_a0;
    s16 posX, posY;
    s16 tilePos;
    s16* dataPtr;

    params = self->params;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animCurFrame = 0;
        self->zPriority = 0x9E;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);

        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        var_a0 = tileUVs;

        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x3E;
            prim->u0 = prim->u2 = *var_a0++;
            prim->u1 = prim->u3 = *var_a0++;
            prim->v0 = prim->v1 = *var_a0++;
            prim->v2 = prim->v3 = *var_a0++;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        self->step = 3;
        break;

    case 1:
        break;

    case 2:
        break;

    case 3:
        break;
    }

    if (self->step != 2) {
        dataPtr = &tileXYs[(params * 2 + 1) * 12];
        prim = &g_PrimBuf[self->primIndex];
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        while (prim != NULL) {
            prim->x0 = prim->x2 = posX + *dataPtr++;
            prim->x1 = prim->x3 = posX + *dataPtr++;
            prim->y0 = prim->y1 = posY + *dataPtr++;
            prim->y2 = prim->y3 = posY + *dataPtr++;
            prim = prim->next;
        }
    }
}
