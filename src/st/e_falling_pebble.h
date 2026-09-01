// SPDX-License-Identifier: AGPL-3.0-or-later

// func_8019BD0C
static void UpdateFallingPebble(Primitive* prim) {
    const int FallSpeed = 2;
    const int MaxScrolledY = 160;

    s32 newYScrolled;
    u32 rand;

    switch (prim->p3) {
    case 1: // Init (and fallthru to Idle)
        rand = (Random() & 1);
        prim->u0 = rand + 1;
        prim->v0 = rand + 1;
        prim->r0 = 0x60;
        prim->g0 = 0x80;
        prim->b0 = 0x30;
        prim->priority = 0xA0;
        prim->drawMode = DRAW_UNK02;
        prim->p2 = (Random() & 0x1F) + 0x10;
        prim->p3 = 2;
        // fallthrough
    case 2: // Idle
        prim->y0 += FallSpeed;
        newYScrolled = g_Tilemap.scrollY.i.hi + prim->y0;
        if (!--prim->p2 || newYScrolled > MaxScrolledY) {
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0; // Inactive
        }
        return;
    }
}
