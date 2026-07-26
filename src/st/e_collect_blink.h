// SPDX-License-Identifier: AGPL-3.0-or-later

static void BlinkItem(Entity* self, u16 timer) {
    Primitive* prim;
    s32 temp;
    prim = &g_PrimBuf[self->primIndex];

    prim->x0 = prim->x2 = self->posX.i.hi - 7;
    prim->x1 = prim->x3 = prim->x0 + 14;

    prim->y0 = prim->y1 = self->posY.i.hi - 7;
    prim->y2 = prim->y3 = prim->y0 + 14;

    if (timer & 2) {
        PCOL(prim) = 0xFF;
    } else {
        PCOL(prim) = 0x80;
    }
}
