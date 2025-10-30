// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

extern u8* g_eBreakableAnimations[];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakablePalettes[];
extern u16 g_eBreakableAnimSets[];
extern u16 g_eBreakableUnk5A[];
extern u8 g_eBreakableDrawModes[];
extern u16 g_eBreakableHitboxOffsets[];
extern s16 g_eBreakableDebrisOffsets[];

extern EInit OVL_EXPORT(EInitBreakable);

void OVL_EXPORT(EntityBreakable)(Entity* self) {
    s16* ptr;
    Entity* entity;
    s32 i;
    s32 debrisCount;
    s16 posY;
    u16 breakableType;

    breakableType = self->params >> 12;
    if (!self->step) {
        InitializeEntity(OVL_EXPORT(EInitBreakable));
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        self->drawMode = g_eBreakableDrawModes[breakableType];
        self->hitboxHeight = g_eBreakableHitboxes[breakableType];
        self->animSet = g_eBreakableAnimSets[breakableType];
        self->unk5A = g_eBreakableUnk5A[breakableType];
        self->palette = g_eBreakablePalettes[breakableType];
        self->hitboxOffY = -g_eBreakableHitboxOffsets[breakableType];
    }

    AnimateEntity(g_eBreakableAnimations[breakableType], self);

    if (self->hitParams) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = g_eBreakableExplosionTypes[breakableType];
        }

        switch (breakableType) {
        case 2:
        case 3:
            self->facingLeft = GetSideToPlayer() & 1;

            posY = self->posY.i.hi + 40;
            if (breakableType == 2) {
                debrisCount = 4;
            } else {
                debrisCount = 3;
            }

            ptr = g_eBreakableDebrisOffsets;
            if (breakableType == 3) {
                ptr += 5;
            }

            for (i = 0; i < debrisCount; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BREAKABLE_DEBRIS), self, entity);
                    entity->posY.i.hi = posY;
                    entity->params = ptr[i];
                    entity->facingLeft = self->facingLeft;
                }
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->posY.i.hi = posY;
                    entity->params = 0;
                }
                posY -= 16;
            }
            g_api.PlaySfx(SFX_CANDLE_HIT_WHOOSH_B);
            ReplaceBreakableWithItemDrop(self);
            break;

        case 9:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_ID(BREAKABLE_DEBRIS), entity);
                entity->params = 256;
            }

            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            break;

        case 7:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            break;

        case 8:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            break;

        default:
            g_api.PlaySfx(SFX_CANDLE_HIT);
            ReplaceBreakableWithItemDrop(self);
            break;
        }
    }
}

#define PAL_BREAKABLE PAL_UNK_200
#define PAL_BREAKABLE_DEBRIS PAL_UNK_204

extern EInit g_EInitInteractable;
extern EInit g_EInitParticle;

void OVL_EXPORT(EntityBreakableDebris)(Entity* self) {
    Collider collider;
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s16 posX, posY;

    switch (self->step) {
    case 0:
        if (self->params & 0x100) {
            InitializeEntity(g_EInitInteractable);
            self->animSet = ANIMSET_OVL(4);
            self->unk5A = 91;
            self->palette = PAL_BREAKABLE;
            self->animCurFrame = 21;
            self->zPriority = 106;
            self->step = 256;
            return;
        }

        InitializeEntity(g_EInitParticle);

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 22;
        prim->clut = PAL_BREAKABLE_DEBRIS;
        prim->u0 = prim->u2 = 152;
        prim->u1 = prim->u3 = 167;
        posY = 132;
        posY += self->params * 16;
        prim->v0 = prim->v1 = posY + 15;
        prim->v2 = prim->v3 = posY;

        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        LOH(prim->next->r2) = 16;
        LOH(prim->next->b2) = 16;
        prim->next->b3 = 128;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        self->velocityX = ((Random() & 7) << 12) + FIX(0.5);
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        self->velocityY = ((Random() & 7) << 12) - FIX(0.5);
        // fallthrough

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        prim = self->ext.prim;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        if (self->facingLeft) {
            LOH(prim->next->tpage) += 16;
        } else {
            LOH(prim->next->tpage) -= 16;
        }
        UnkPrimHelper(prim);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 8;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_api.PlaySfx(SFX_SMALL_FLAME_IGNITE);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
                entity->params = 0;
            }
            DestroyEntity(self);
            break;
        }
        break;
    }
}
