// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"
#include "sfx.h"

void EntityFadeToWhite1(Entity* self) {
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            InitializeEntity(D_8018047C);
            prim = &g_PrimBuf[primIndex];
            self->animSet = ANIMSET_DRA(0);
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            prim->x1 = prim->x3 = 0x100;
            prim->y2 = prim->y3 = 0xE0;
            prim->priority = 192;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = prim->y0 = prim->y1 = prim->x0 = prim->x2 = 0;
            prim->drawMode = DRAW_HIDE;
        }
        break;

    case 1:
        if (D_801A3F84 & 0x10) {
            g_PrimBuf[self->primIndex].drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            g_api.PlaySfx(SFX_FM_EXPLODE_A); // Fade to white
            self->step++;
        }
        break;

    case 2:
        prim = &g_PrimBuf[self->primIndex];
        prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 = prim->g2 =
            prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->r0 =
                prim->b3 + 4;
        if (prim->r0 > 240) {
            self->ext.fadeToWhite.unk7C = 1;
            self->ext.fadeToWhite.unk7E = 0x200;
            self->ext.fadeToWhite.unk80 = 0;
            D_801A3F84 |= 0x20;
            g_api.PlaySfx(SFX_SUC_APPEAR);
            self->step++;
        }
        break;

    case 3:
        prim = &g_PrimBuf[self->primIndex];
        prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 = prim->g2 =
            prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->r0 =
                prim->b3 - 2;
        if (prim->r0 < 4) {
            prim->drawMode = DRAW_HIDE;
            self->step++;
        }
        break;

    case 4:
        if (D_801A3F84 & 0x200) {
            self->ext.fadeToWhite.unk7C = 0;
            g_api.PlaySfx(0xA1);
            DestroyEntity(self);
        }
        break;
    }

    if (self->ext.fadeToWhite.unk7C != 0) {
        if (--self->ext.fadeToWhite.unk7E == 0) {
            g_api.PlaySfx(SFX_SUC_APPEAR);
        }
    }
}

// ID 24
void EntityFadeToWhite2(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 i;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 2);
        if (primIndex != -1) {
            InitializeEntity(D_8018047C);
            prim = &g_PrimBuf[primIndex];
            self->animSet = ANIMSET_DRA(0);
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            for (i = 0; prim != NULL; i++) {
                prim->x0 = prim->x2 = 0;
                prim->x1 = prim->x3 = 256;
                prim->y0 = prim->y1 = 0;
                prim->y2 = prim->y3 = 224;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 0;
                prim->priority = i + 192;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        }
        break;

    case 1:
        if (D_801A3F84 & 0x10) {
            g_PrimBuf[self->primIndex].drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            self->step++;
        }
        break;

    case 2:
        prim = &g_PrimBuf[self->primIndex];
        prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 = prim->g2 =
            prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->r0 =
                prim->b3 + 2;
        if (prim->r0 > 252) {
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            self->step++;
        }
        break;

    case 3:
        prim = g_PrimBuf[self->primIndex].next;
        prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 = prim->g2 =
            prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->r0 =
                prim->b3 + 8;
        if (prim->r0 > 240) {
            D_801A3F84 |= 0x40;
            self->step++;
        }
        break;

    case 4:
        break;
    }
}
