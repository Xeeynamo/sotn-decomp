// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

// Adds a subtle glow to the bottom of the screen in screens where the
// lava appears to cast shadow on the player and enemies (eg. Lossoth rooms)
//
// This is purely a cosmetic effect and the shadows themselves are handled
// elsewhere.
//
// Notably this is not used in the interim room with Discus Lord despite it
// having lava, though this room also does not cast shadow.
void EntityLavaGlow(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->animCurFrame = 0;
        break;
    case 1:
        primIndex = g_api.func_800EDB58(PRIM_G4, 1);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->x0 = 0;
                prim->y0 = 0x90;
                prim->x1 = 0x100;
                prim->y1 = 0x90;
                prim->x2 = 0;
                prim->y2 = 0x100;
                prim->x3 = 0x100;
                prim->y3 = 0x100;
                prim->r0 = 0;
                prim->b0 = 0;
                prim->g0 = 0;
                LOW(prim->r1) = LOW(prim->r0);
                prim->r2 = 0xE0;
                prim->b2 = 0x30;
                prim->g2 = 0x50;
                LOW(prim->r3) = LOW(prim->r2);
                prim->priority = 0xD0;
                prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_COLORS | DRAW_TRANSP;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        self->step++;
        // Fallthrough
    case 3:
        break;
    }
}
