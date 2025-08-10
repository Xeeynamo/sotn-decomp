// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

extern  u8* g_eBreakableAnimations[];
extern  u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakablePalettes[];
extern  u16 g_eBreakableAnimSets[];
extern  u16 g_eBreakableUnk5A[];
extern  u8 g_eBreakableDrawModes[];
extern  u16 g_eBreakableHitboxOffsets[];
extern  s16 g_eBreakableDebrisOffsets[];

extern EInit OVL_EXPORT(EInitBreakable);


void OVL_EXPORT(EntityBreakable)(Entity* self) {
    s16* ptr;
    Entity* entity;
    u16 breakableType;
    s32 i;
    s32 debrisCount;
    s16 posY;

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
            g_api.PlaySfx(0x67F);
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
            return;

        case 7:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;

        case 8:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;

        default:
            g_api.PlaySfx(SFX_CANDLE_HIT);
            break;
        }

        ReplaceBreakableWithItemDrop(self);
    }
}

extern EInit g_EInitInteractable;
extern EInit g_EInitParticle;

// Entity ID: 0x26
void OVL_EXPORT(EntityBreakableDebris)(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    Collider collider;
    s32 primIndex;
    s16 posX;
    s16 posY; // reused for prim->v0-3

    switch (self->step) {
    case 0:
        if (self->params & 0x100) {
            InitializeEntity(g_EInitInteractable);
            self->animSet = ANIMSET_OVL(4);
            self->unk5A = 0x5B;
            self->palette = PAL_DRA(0x200);
            self->animCurFrame = 0x15;
            self->zPriority = 0x6A;
            self->step = 256;
            break;
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
        prim->tpage = 0x16;
        prim->clut = 0x204;
        prim->u0 = prim->u2 = 0x98;
        prim->u1 = prim->u3 = 0xA7;
        posY = 0x84;
        posY += (self->params * 16);
        prim->v0 = prim->v1 = posY + 15;
        prim->v2 = prim->v3 = posY;

        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        LOH(prim->next->r2) = 0x10;
        LOH(prim->next->b2) = 0x10;
        prim->next->b3 = 0x80;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        self->velocityX = ((Random() & 7) << 0xC) + 0x8000;
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        self->velocityY = ((Random() & 7) << 0xC) - 0x8000;
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        prim = self->ext.prim;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;

        if (self->facingLeft) {
            LOH(prim->next->tpage) += 0x10;
        } else {
            LOH(prim->next->tpage) -= 0x10;
        }

        UnkPrimHelper(prim);

        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 8;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_api.PlaySfx(SFX_SMALL_FLAME_IGNITE);
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
                newEntity->params = 0;
            }
            DestroyEntity(self);
            break;
        }
    }
}


