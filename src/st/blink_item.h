#include "game.h"

void BlinkItem(Entity* self, s32 renderFlags) {
    Primitive* prim = &g_PrimBuf[self->primIndex];
    s16 right, left, bottom, top;

    left = self->posX.i.hi - 7;
    right = self->posX.i.hi + 7;

    prim->x0 = prim->x2 = left;
    prim->x1 = prim->x3 = right;

    top = self->posY.i.hi - 7;
    bottom = self->posY.i.hi + 7;

    prim->y0 = prim->y1 = top;
    prim->y2 = prim->y3 = bottom;

    if (renderFlags & RENDERFLAGS_NOSHADOW) {
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 =
                255;
    } else {
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 =
                128;
    }
}
