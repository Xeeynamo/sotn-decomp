// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: en_breakable.c
 * Overlay: CHI
 * Description: ENTITY - Breakable Object breaks into debris when struck
 */

#include "chi.h"

// D_80180818
static u8 anim_1[] = {3, 14, 4, 15, 4, 16, 4, 17, 4, 18, 4, 19, 3, 20, 0, 0};

// D_80180828
static u8 anim_2[] = {3, 21, 4, 22, 4, 23, 4, 24, 4, 25, 4, 26, 3, 27, 0, 0};

// D_80180838
static u8* g_eBreakableAnimations[] = {
    anim_1, anim_2, NULL, NULL, NULL, NULL, NULL, NULL};

// D_80180858
static u8 g_eBreakableHitboxes[] = {12, 20, 0, 0, 0, 0, 0, 0};

// D_80180860
static u8 g_eBreakableExplosionTypes[] = {3, 3, 0, 0, 0, 0, 0, 0};

// D_80180868
static u16 g_eBreakableAnimSets[] = {
    ANIMSET_OVL(1), ANIMSET_OVL(1), 0, 0, 0, 0, 0, 0};

// D_80180878
static u8 g_eBreakableDrawModes[] = {
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT};

// D_80180880
static s16 g_eBreakableDebrisOffsets[] = {
    -4, -4, 3, -6, 2, 9, -4, 12, 0, 2, 0, 15, 0, 31};

// func_8019B698: [E_BREAKABLE] EntityBreakableWithDebris
// func_8019B914: [E_BREAKABLE_DEBRIS] EntityBreakableDebris
#ifdef VERSION_PSP
extern s32 E_ID(BACKGROUND_BLOCK);
extern s32 E_ID(BREAKABLE_DEBRIS);
#endif

// params: (>> 12) represents the breakable type.
//                 Any non-zero value is considered a "tall" breakable,
//                 meaning it breaks into more debris,
//                 some of which spawns higher up
void EntityBreakableWithDebris(Entity* self) {
    const int DebrisBaseCount = 4;
    const int DebrisTallExtraCount = 3;
    const int BackgroundBlockOffsetY = -16;
    const int BackgroundBlockTallOffsetY = -32;
    const int DebrisTallOffsetY = -20;

    s16* ptr;
    s32 i;
    u16 breakableType = self->params >> 12;
    Entity* entity;

    if (!self->step) {
        InitializeEntity(OVL_EXPORT(EInitBreakable));
        self->zPriority = 0x70;
        self->drawMode = g_eBreakableDrawModes[breakableType];
        self->hitboxHeight = g_eBreakableHitboxes[breakableType];
        self->animSet = g_eBreakableAnimSets[breakableType];

        entity = self + 1;
        DestroyEntity(entity);
        CreateEntityFromEntity(E_ID(BACKGROUND_BLOCK), self, entity);
        if (breakableType) {
            entity->posY.i.hi += BackgroundBlockTallOffsetY;
        } else {
            entity->posY.i.hi += BackgroundBlockOffsetY;
        }
        entity->params = 1;
    }

    AnimateEntity(g_eBreakableAnimations[breakableType], self);

    if (self->hitParams) {
        g_api.PlaySfx(SFX_FIRE_SHOT);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = g_eBreakableExplosionTypes[breakableType];
            entity->params |= 0x10;
        }

        for (ptr = g_eBreakableDebrisOffsets, i = 0; i < DebrisBaseCount; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(BREAKABLE_DEBRIS), self, entity);
                entity->posX.i.hi += *ptr++;
                entity->posY.i.hi += *ptr++;
                if (breakableType) {
                    entity->posY.i.hi += DebrisTallOffsetY;
                }
                entity->params = i;
            }
        }

        if (breakableType) {
            for (i = 0; i < DebrisTallExtraCount; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BREAKABLE_DEBRIS), self, entity);
                    entity->posX.i.hi += *ptr++;
                    entity->posY.i.hi += *ptr++;
                    entity->params = i + DebrisBaseCount;
                }
            }
        }
        entity = self + 1;
        DestroyEntity(entity);
        ReplaceBreakableWithItemDrop(self);
    }
}

// params: Index of breakable debris to use
//         (>= 4) Considered a "tall" breakable debris
//         (== 6) The "last standing" debris, that doesn't move
void EntityBreakableDebris(Entity* self) {
    typedef enum Step {
        INIT = 0,
        UPDATE = 1,
    };

    Collider collider;
    Primitive* prim;
    u32 primIndex;
    s32 facing;
    u32 posX;
    u32 posY;
    Entity* newEntity;

    switch (self->step) {
    case INIT:
        InitializeEntity(OVL_EXPORT(EInitBreakable));
        self->hitboxState = 0;
        self->zPriority = 0x70;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->animCurFrame = self->params + 28;
        facing = GetSideToPlayer() & 1;

        self->ext.breakableDebris.angle = (Random() & 0x1E) + 8;
        if (self->facingLeft) {
            self->ext.breakableDebris.angle = -self->ext.breakableDebris.angle;
        }

        // Check for upper "tall" debris
        if (self->params > 3) {
            self->ext.breakableDebris.angle = -self->ext.breakableDebris.angle;
        }

        if (facing) {
            self->velocityX = FIX(1);
        } else {
            self->velocityX = FIX(-1);
        }

        self->velocityX += FIX(0.5) - (Random() << 8);
        self->velocityY = FIX(-3);
        self->velocityY += (self->params >> 1) * FIX(0.375);

        // "Last standing" debris just sits there (tall breakables only)
        if (self->params == 6) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step = 2;
        }

        self->primIndex = 0;
        if (!self->params) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];

                UnkPolyFunc2(prim);

                prim->tpage = 0x1A;
                prim->clut = 0x159;
                prim->u0 = prim->u2 = 0x40;
                prim->u1 = prim->u3 = 0x60;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x20;

                prim->next->x1 = self->posX.i.hi + 4;
                prim->next->y0 = self->posY.i.hi - 8;
                LOH(prim->next->r2) = 0x20;
                LOH(prim->next->b2) = 0x20;
                prim->next->b3 = 0x10;

                prim->priority = 0x72;
                prim->drawMode = DRAW_TRANSP | DRAW_UNK02 | DRAW_COLORS |
                                 DRAW_TPAGE | DRAW_TPAGE2;
            }
        }
        break;

    case 1:
        MoveEntity();
        self->rotZ += self->ext.breakableDebris.angle;
        self->velocityY += FIX(0.25);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 6;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY / 2;
            self->velocityX -= self->velocityX / 3;
            if (self->velocityY > FIX(-0.625)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->params = 16;
                }
                DestroyEntity(self);
                break;
            }
        }

        if (self->primIndex != 0) {
            prim = &g_PrimBuf[self->primIndex];
            UnkPrimHelper(prim);
            LOH(prim->next->r2) = LOH(prim->next->b2) += 4;
            if (LOH(prim->next->r2) > 64) {
                prim->next->b3 -= 4;
                if (!prim->next->b3) {
                    g_api.FreePrimitives(self->primIndex);
                    self->flags &= ~FLAG_HAS_PRIMS;
                    self->primIndex = 0;
                }
            }
        }
        break;
    }
}
