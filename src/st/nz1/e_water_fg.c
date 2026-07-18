// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

extern EInit g_EInitInteractable;

static s16 D_us_80181094[][4] = {
    {0x010, 0x2C0, 0x50, 0x20}, {0x070, 0x2C0, 0x80, 0x20},
    {0x0B0, 0x2B0, 0x50, 0x20}, {0x010, 0x330, 0x50, 0x20},
    {0x010, 0x0C0, 0x30, 0x20}, {0x050, 0x0C0, 0x60, 0x20},
    {0x0C0, 0x0C0, 0x30, 0x20},
};

void EntityWaterForeground(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s16* ptr;
    s32 x, y;
    s32 params;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        prim->r0 = 0x48;
        prim->g0 = 0x40;
        prim->b0 = 0xC0;
        params = self->params;
        ptr = (s16*)D_us_80181094[params];
        x = ptr[0] - g_Tilemap.scrollX.i.hi;
        y = ptr[1] - g_Tilemap.scrollY.i.hi;
        prim->x0 = x;
        prim->y0 = y;
        prim->u0 = ptr[2];
        prim->v0 = ptr[3];
        prim->priority = 0x9A;
        prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        break;
    case 1:
        break;
    }
}
