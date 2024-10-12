// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

static u8 anim_1[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 anim_2[] = {4, 4, 4, 5, 4, 6, 4, 5, 0, 0, 0, 0};
static u8 anim_3[] = {4, 14, 4, 15, 4, 16, 4, 17, 0, 0, 0, 0};
static u8* g_eBreakableAnimations[] = {
    anim_1, anim_2, anim_3, NULL, NULL, NULL, NULL, NULL};
static u8 g_eBreakableHitboxes[] = {8, 8, 8, 0, 0, 0, 0, 0};
static u8 g_eBreakableExplosionTypes[] = {0, 0, 0, 0, 0, 0, 0, 0};
static u16 g_eBreakableanimSets[] = {
    ANIMSET_DRA(3), ANIMSET_OVL(1), ANIMSET_OVL(8), 0, 0, 0, 0, 0};
static u8 g_eBreakableDrawModes[] = {
    DRAW_TPAGE | DRAW_TPAGE2 | DRAW_UNK_40,
    DRAW_TPAGE | DRAW_TPAGE2 | DRAW_UNK_40,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT};

#ifndef VERSION_PSP
// on PSP this might be either optimised out to BSS or completely removed
static u8 unused[] = {0, 0, 0, 0, 0, 0, 0, 0};
#endif

extern u16 g_EInitBreakable[];

void EntityBreakableNZ0(Entity* self) {
    u16 breakableType = self->params >> 12;
    s16 top, bottom, left, right;
    Entity* entityDropItem;
    Primitive* prim;

    if (self->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], self);
        if (breakableType == 2) {
            prim = &g_PrimBuf[self->primIndex];
            if (g_Timer & 2) {
                prim->clut = 0x21B;
            } else {
                prim->clut = 0x21C;
            }
        }

        if (self->hitParams) { // If destroyed
            if (breakableType == 2) {
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
            }
            g_api.PlaySfx(SFX_CANDLE_HIT);
            entityDropItem = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entityDropItem);
                entityDropItem->params =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(self);
        }
    } else {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        self->drawMode = g_eBreakableDrawModes[breakableType];
        self->hitboxHeight = g_eBreakableHitboxes[breakableType];
        self->animSet = g_eBreakableanimSets[breakableType];
        if (breakableType == 2) {
            self->unk5A = 0x4B;
            self->palette = 0x219;
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[self->primIndex];
            prim->tpage = 0x12;
            prim->u0 = prim->u2 = 0xC8;
            prim->u1 = prim->u3 = 0xF8;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xA0;
            left = self->posX.i.hi - 23;
            right = self->posX.i.hi + 25;
            prim->x0 = prim->x2 = left;
            prim->x1 = prim->x3 = right;
            top = self->posY.i.hi - 23;
            bottom = self->posY.i.hi + 9;
            prim->y0 = prim->y1 = top;
            prim->y2 = prim->y3 = bottom;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        }
    }
}
