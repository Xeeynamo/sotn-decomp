// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: en_breakable.h
 * Overlay: CHI
 * Description: ENTITY - Breakable with debris
 */

#include "chi.h"

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

    u16* ptr;
    s32 i;
    u16 breakableType = self->params >> 12;
    Entity* entity;

    if (!self->step) {
        InitializeEntity(&OVL_EXPORT(EInitBreakable));
        self->zPriority = 0x70;
        self->drawMode = g_eBreakableDrawModes[breakableType];
        self->hitboxHeight = g_eBreakableHitboxes[breakableType];
        self->animSet = g_eBreakableAnimSets[breakableType];

        entity = self + 1;
        DestroyEntity(entity);
        CreateEntityFromEntity(E_BACKGROUND_BLOCK, self, entity);
        if (breakableType) {
            (self + 1)->posY.i.hi += BackgroundBlockTallOffsetY;
        } else {
            (self + 1)->posY.i.hi += BackgroundBlockOffsetY;
        }
        entity->params = 1;
    }

    AnimateEntity(g_eBreakableAnimations[breakableType], self);

    if (self->hitParams) {
        g_api_PlaySfx(SFX_FIRE_SHOT);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = g_eBreakableExplosionTypes[breakableType] | 0x10;
        }

        for (ptr = &g_eBreakableDebrisOffsets, i = 0; i < DebrisBaseCount;
             i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_BREAKABLE_DEBRIS, self, entity);
                entity->posX.i.hi += *ptr++;
                entity->posY.i.hi += *ptr++;
                if (breakableType != 0) {
                    entity->posY.i.hi += DebrisTallOffsetY;
                }
                entity->params = i;
            }
        }

        if (breakableType) {
            for (i = 0; i < DebrisTallExtraCount; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_BREAKABLE_DEBRIS, self, entity);
                    entity->posX.i.hi += *ptr++;
                    entity->posY.i.hi += *ptr++;
                    entity->params = i + DebrisBaseCount;
                }
            }
        }
        DestroyEntity(self + 1);
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
    s16 primIndex;
    s32 facing;
    s32 temp_v0_2;
    u16 angle;
    u16 temp_v0_5;
    Entity* newEntity;
    s32 temp;

    switch (self->step) {
    case INIT:
        InitializeEntity(&OVL_EXPORT(EInitBreakable));
        self->zPriority = 0x70;
        self->hitboxState = 0;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->animCurFrame = self->params + 28;
        facing = GetSideToPlayer() & 1;

        angle = (Random() & 0x1E) + 8;
        self->ext.breakableDebris.angle = angle;
        if (self->facingLeft) {
            self->ext.breakableDebris.angle = -angle;
        }

        // Check for upper "tall" debris
        if (self->params >= 4) {
            self->ext.breakableDebris.angle = -self->ext.breakableDebris.angle;
        }

        if (facing == 0) {
            self->velocityX = FIX(-1);
        } else {
            self->velocityX = FIX(1);
        }

        temp = 0x8000;
        temp_v0_2 = Random() << 8;
        self->velocityX = self->velocityX + temp - temp_v0_2;
        self->velocityY = FIX(-3);
        self->velocityY = (self->params >> 1) * 0x6000 - 0x30000;

        // "Last standing" debris just sits there (tall breakables only)
        if (self->params == 6) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step = 2;
        }

        self->primIndex = 0;
        if (self->params == 0) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                prim = &g_PrimBuf[primIndex];
                self->primIndex = primIndex;
                self->flags |= FLAG_HAS_PRIMS;

                UnkPolyFunc2(prim, primIndex);

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
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 6, &collider, 0);
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
                prim->next->b3 += 252;
                if (prim->next->b3 == 0) {
                    g_api.FreePrimitives(self->primIndex);
                    self->primIndex = 0;
                    self->flags &= ~FLAG_HAS_PRIMS;
                }
            }
        }
        break;
    }
}
