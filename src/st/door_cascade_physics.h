// SPDX-License-Identifier: AGPL-3.0-or-later

// When cavern door or heart door are opened, a cascade
// of single blue pixels flies out of the door as it slides down.
// This function manages the physics for those pixel-prims.
void DoorCascadePhysics(EntranceCascadePrim* prim) {
    s32 xVar;
    s32 yVar;

    switch (prim->p3) {
    case 1:
        xVar = (Random() & 0xF) - 8;
        prim->x0 = g_CurrentEntity->posX.i.hi + xVar;
        prim->y0 = 0x9C;
        prim->x1 = 0;
        prim->y1 = 0;
        if (xVar > 0) {
            prim->velocityX.val = Random() * 0x40;
        } else {
            prim->velocityX.val = -Random() * 0x40;
        }
        prim->velocityY.val = (Random() << 8) + FIX(-4);
        prim->drawMode = DRAW_UNK02;
        prim->p3++;
        /* fallthrough */
    case 2:
        xVar = (prim->x0 << 0x10) + (u16)prim->x1;
        yVar = (prim->y0 << 0x10) + (u16)prim->y1;
        xVar += prim->velocityX.val;
        yVar += prim->velocityY.val;
        prim->x0 = (xVar >> 0x10);
        prim->x1 = xVar & 0xFFFF;
        prim->y0 = (yVar >> 0x10);
        prim->y1 = yVar & 0xFFFF;

        prim->velocityY.val += FIX(1.0 / 4.0);
        if (prim->velocityY.val <= FIX(6)) {
            return;
        }
        prim->p3++;
        break;
    case 3:
        prim->drawMode = DRAW_HIDE;
        prim->p3 = 0;
        break;
    }
}
