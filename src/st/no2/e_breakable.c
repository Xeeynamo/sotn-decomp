// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

#ifdef VERSION_PSP
extern s32 E_ID(BREAKABLE_DEBRIS);
#endif

static u8 anim_1[] = {4, 1, 4, 2, 0, 0};
static u8 anim_2[] = {4, 0, 4, 0, 0};
static u8 anim_3[] = {5, 1, 5, 2, 5, 3, 5, 4, 0, 0};
static u8 anim_4[] = {5, 5, 5, 6, 5, 7, 5, 8, 0, 0};
static u8 anim_5[] = {5, 9, 5, 10, 5, 11, 5, 12, 0, 0};
static u8 anim_6[] = {5, 13, 5, 14, 5, 15, 5, 16, 0, 0};
static u8 anim_7[] = {5, 17, 5, 18, 5, 19, 0, 0};
static u8 anim_8[] = {5, 23, 0, 0};
static u8 anim_9[] = {5, 22, 0, 0};
static u8 anim_10[] = {5, 20, -1, -1, 5, 21, 5, 21, -1, 0};
static u8* g_eBreakableAnimations[] = {anim_1, anim_2, anim_3, anim_4, anim_5,
                                       anim_6, anim_7, anim_8, anim_9, anim_10};
static u8 g_eBreakableHitboxes[] = {8, 8, 40, 24, 16, 16, 8, 8, 8, 8, 8, 0};
static u8 g_eBreakableExplosionTypes[] = {0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0};
static u16 g_eBreakablePalettes[] = {
    PAL_NONE,      PAL_NONE,      PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE,
    PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE};
static u16 g_eBreakableAnimSets[] = {
    ANIMSET_DRA(3), ANIMSET_DRA(3), ANIMSET_OVL(7), ANIMSET_OVL(7),
    ANIMSET_OVL(7), ANIMSET_OVL(7), ANIMSET_OVL(7), ANIMSET_OVL(7),
    ANIMSET_OVL(7), ANIMSET_OVL(7)};
static u16 g_eBreakableUnk5A[] = {0, 0, 91, 91, 91, 91, 91, 91, 91, 91};
static u8 g_eBreakableDrawModes[] = {
    DRAW_TPAGE | DRAW_TPAGE2 | DRAW_UNK_40,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_DEFAULT,
    DRAW_DEFAULT};
static u16 g_eBreakableHitboxOffsets[] = {
    0, 0, -24, -16, 0, 0, 0, 0, 0, 0, 0, 0};
static s16 g_eBreakableDebrisOffsets[] = {0, 1, 2, 2, 3, 0, 1, 2, 3, 0};

void EntityBreakable(Entity* self) {
    s16* ptr;
    Entity* entity;
    u16 breakableType;
    s32 i;
    s32 debrisCount;
    s16 posY;

    breakableType = self->params >> 12;
    if (!self->step) {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        self->drawMode = g_eBreakableDrawModes[breakableType];
        self->hitboxHeight = g_eBreakableHitboxes[breakableType];
        self->animSet = g_eBreakableAnimSets[breakableType];
        self->unk5A = g_eBreakableUnk5A[breakableType];
        self->palette = g_eBreakablePalettes[breakableType];
        self->hitboxOffY = g_eBreakableHitboxOffsets[breakableType];
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
            posY = self->posY.i.hi - 40;
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
                posY += 16;
            }
            g_api.PlaySfx(SFX_CANDLE_HIT_WHOOSH_B);
            break;
        case 9:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_ID(BREAKABLE_DEBRIS), entity);
                entity->params = 256;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
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

void EntityBreakableDebris(Entity* self) {
    Collider collider;
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s16 posX, posY;

    switch (self->step) {
    case 0:
        if (self->params & 0x100) {
            InitializeEntity(g_EInitInteractable);
            self->animSet = ANIMSET_OVL(7);
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
        prim->v0 = prim->v1 = posY;
        prim->v2 = prim->v3 = posY + 15;
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
        }
        break;
    }
}
