// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

static s16 g_sensors[] = {0, 20, 0, 4, 4, -4, -8, 0};
static s16 g_sensors2[] = {0, 20, 4, 0};
// Possibly movement distance
static s16 D_us_80181BA4[] = {-16, 38, 16, 6};
// Possibly attack distance
static s16 D_us_80181BAC[] = {32, 48, 64, 16};
static u8 g_anim1[] = {5, 1, 5, 2, 5, 3, 5, 2, 0, 0, 0, 0};
static u8 g_anim2[] = {
    33, 1, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 33, 8, -1, 0, 0, 0};
static u8 g_anim3[] = {1, 1,  1,  2,  1, 3, 1, 10, 1,  11, 1,  12,
                       1, 13, 33, 12, 4, 3, 4, 2,  20, 1,  -1, 0};
static u8 g_anim4[] = {9, 1, 9, 14, 9, 1, 9, 14, 9, 1, 9, 14, 0, 0, 0, 0};
static u8 g_anim5[] = {5, 24, 5, 25, 5, 26, 5, 25, 0, 0, 0, 0};
static u8 g_anim6[] = {
    1, 14, 1, 15, 1, 16, 1,  17, 1, 18, 1, 19, 8,  18, 1,  20,
    1, 21, 1, 22, 1, 23, 33, 22, 3, 21, 3, 15, 32, 14, -1, 0};
static s8 g_hitbox[][4] = {
    {0, 0, 0, 0}, {-63, -55, 0, 0}, {-33, 30, 8, 8}, {21, -23, 9, 9}};
static u8 g_hitboxIdx[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2,
                           1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 0};
extern s16* sprites_dai_3[];

// Corner Guard movement?
static bool func_us_801D1010(s16* arg0) {
    Collider collider;
    s32 posX, posY;

    if (g_CurrentEntity->velocityX > 0) {
        arg0 += 2;
    }
    posX = g_CurrentEntity->posX.i.hi + arg0[0];
    posY = g_CurrentEntity->posY.i.hi + arg0[1];
    g_api.CheckCollision(posX, posY, &collider, 0);
    if (collider.effects & EFFECT_UNK_8000) {
        return true;
    }
    return false;
}

static void func_us_801D1084(EntranceCascadePrim* prim) {
    Entity* entity;
    s32 psxSpPad[9];

    UnkPrimHelper(prim);
    switch (prim->next->step) {
    case 0:
        prim->next->unk10 = ((Random() & 0x1F) << 12) - FIX(1);
        prim->next->unk14 = -(Random() & 0x1F) * FLT(1);
        prim->next->step = 1;
        prim->next->velocityX.i.lo = (Random() & 0xF) + 8;
        // fallthrough
    case 1:
        if (prim->next->unk10 > 0) {
            prim->next->unk1E -= 32;
        } else {
            prim->next->unk1E += 32;
        }
        prim->next->unk14 += FLT(1.5);
        prim->next->velocityX.i.lo--;
        if (!prim->next->velocityX.i.lo) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
                entity->posX.i.hi = prim->next->x1;
                entity->posY.i.hi = prim->next->y0;
                entity->params = 0;
            }
            UnkPolyFunc0(prim);
        }
        return;
    }
}

// EntityCornerGuard
void EntityCornerGuard(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s32 uCoord, vCoord;
    s32 distance;
    s32 facingLeft;
    s16* dataPtr;
    s16 palette;

    if ((self->flags & FLAG_DEAD) && ((self->step) < 8)) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCornerGuard);
        self->animCurFrame = 1;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_UNK_28, entity);
        // fallthrough
    case 1:
        if (UnkCollisionFunc3(g_sensors) & 1) {
            self->ext.cornerGuard.unk84 = Random() & 1;
            self->ext.cornerGuard.unk85 = self->ext.cornerGuard.unk84;
            SetStep(2);
        }
        break;
    case 2:
        self->animCurFrame = 1;
        distance = GetDistanceToPlayerX();
        if (distance < 96) {
            facingLeft = GetSideToPlayer() & 1;
            if (facingLeft != self->ext.cornerGuard.unk84) {
                SetStep(3);
            } else if (self->ext.cornerGuard.unk84) {
                SetStep(5);
            } else {
                SetStep(4);
            }
        }
        break;
    case 3:
        if (!AnimateEntity(g_anim4, self)) {
            self->ext.cornerGuard.unk84 = GetSideToPlayer() & 1;
            self->ext.cornerGuard.unk85 = self->ext.cornerGuard.unk84;
            if (self->ext.cornerGuard.unk84) {
                SetStep(5);
            } else {
                SetStep(4);
            }
        }
        break;
    case 4:
        if (!self->step_s) {
            self->velocityX = FIX(0.5);
            if ((self->ext.cornerGuard.unk84) ^ (self->ext.cornerGuard.unk85)) {
                self->velocityX = FIX(-0.75);
            }
            self->ext.cornerGuard.unk80 = D_us_80181BAC[Random() & 3];
            self->step_s++;
        }
        AnimateEntity(g_anim5, self);
        UnkCollisionFunc2(g_sensors2);
        if (!func_us_801D1010(D_us_80181BA4)) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        if ((self->ext.cornerGuard.unk84 ^ self->ext.cornerGuard.unk85) &&
            (GetDistanceToPlayerX() > 96)) {
            self->ext.cornerGuard.unk85 = self->ext.cornerGuard.unk84;
            self->velocityX = FIX(0.5);
        }
        if (!self->ext.cornerGuard.unk80) {
            if (GetDistanceToPlayerX() < 48) {
                SetStep(6);
            }
            facingLeft = GetSideToPlayer() & 1;
            if (facingLeft != self->ext.cornerGuard.unk84) {
                SetStep(3);
            }
        } else {
            self->ext.cornerGuard.unk80--;
        }
        break;
    case 6:
        if (!self->step_s) {
            PlaySfxPositional(SFX_BONE_SWORD_SWISH_B);
            self->step_s++;
        }
        if (!AnimateEntity(g_anim6, self)) {
            facingLeft = GetSideToPlayer() & 1;
            if (facingLeft != self->ext.cornerGuard.unk84) {
                SetStep(3);
            } else {
                SetStep(4);
            }
        }
        break;
    case 5:
        if (!self->step_s) {
            self->velocityX = FIX(-0.75);
            if (self->ext.cornerGuard.unk84 ^ (self->ext.cornerGuard.unk85)) {
                self->velocityX = FIX(0.5);
            }
            self->ext.cornerGuard.unk80 = D_us_80181BAC[Random() & 3];
            self->step_s++;
        }
        AnimateEntity(g_anim1, self);
        UnkCollisionFunc2(g_sensors2);
        if (!func_us_801D1010(D_us_80181BA4)) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        if ((self->ext.cornerGuard.unk84 ^ (self->ext.cornerGuard.unk85)) &&
            (GetDistanceToPlayerX() > 96)) {
            self->ext.cornerGuard.unk85 = self->ext.cornerGuard.unk84;
            self->velocityX = FIX(-0.75);
        }
        if (!self->ext.cornerGuard.unk80) {
            if (GetDistanceToPlayerX() < 96) {
                SetStep(7);
            }
            facingLeft = GetSideToPlayer() & 1;
            if (facingLeft != self->ext.cornerGuard.unk84) {
                SetStep(3);
            }
        } else {
            self->ext.cornerGuard.unk80--;
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(g_anim2, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            self->velocityX = FIX(-3.0);
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            PlaySfxPositional(SFX_SCRAPE_B);
            self->step_s++;
            // fallthrough
        case 2:
            UnkCollisionFunc2(g_sensors2);
            if (!func_us_801D1010(D_us_80181BA4)) {
                self->posX.val -= self->velocityX;
                self->velocityX = 0;
            }
            self->velocityX -= self->velocityX / 16;
            if (!(g_Timer & 7) && (abs(self->velocityX) > FIX(0.75))) {
                EntityExplosionVariantsSpawner(self, 1, 1, 12, 8, 5, 1);
            }
            if (!AnimateEntity(g_anim3, self)) {
                self->step_s++;
            }
            break;
        case 3:
            self->velocityX -= self->velocityX / 8;
            if (abs(self->velocityX) < FIX(0.25)) {
                self->step_s++;
            }
            break;
        case 4:
            facingLeft = GetSideToPlayer() & 1;
            if (facingLeft != self->ext.cornerGuard.unk84) {
                SetStep(3);
            } else {
                if (GetDistanceToPlayerX() < 64) {
                    self->ext.cornerGuard.unk85 =
                        ((self->ext.cornerGuard.unk84) ^ 1);
                }
                SetStep(5);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            dataPtr = (s16*)g_EInitCornerGuard;
            palette = dataPtr[3];
            dataPtr = sprites_dai_3[self->animCurFrame];
            primIndex = g_api.AllocPrimitives(PRIM_GT4, *dataPtr * 2);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.cornerGuard.prim = prim;
                dataPtr += 2;
                uCoord = (self->unk5A & 1);
                uCoord *= 127;
                vCoord = (self->unk5A & 2) >> 1;
                vCoord *= 127;
                for (; prim != NULL;
                     dataPtr++, prim = prim->next, prim = prim->next) {
                    UnkPolyFunc2(prim);
                    prim->next->x1 = self->posX.i.hi;
                    if (self->facingLeft) {
                        prim->next->x1 -= *dataPtr++;
                    } else {
                        prim->next->x1 += *dataPtr++;
                    }
                    prim->next->y0 = self->posY.i.hi + *dataPtr++;
                    ((EntranceCascadePrim*)prim->next)->x2 = *dataPtr++;
                    if (self->facingLeft) {
                        prim->next->x1 -=
                            ((EntranceCascadePrim*)prim->next)->x2 / 2;
                    } else {
                        prim->next->x1 +=
                            ((EntranceCascadePrim*)prim->next)->x2 / 2;
                    }
                    ((EntranceCascadePrim*)prim->next)->y2 = *dataPtr++;
                    prim->next->y0 +=
                        ((EntranceCascadePrim*)prim->next)->y2 / 2;
                    dataPtr += 2;
                    if (self->facingLeft) {
                        prim->u1 = prim->u3 = uCoord + *dataPtr++;
                        prim->v0 = prim->v1 = vCoord + *dataPtr++;
                        prim->u0 = prim->u2 = uCoord + *dataPtr++;
                        prim->v2 = prim->v3 = vCoord + *dataPtr++;
                    } else {
                        prim->u0 = prim->u2 = uCoord + *dataPtr++;
                        prim->v0 = prim->v1 = vCoord + *dataPtr++;
                        prim->u1 = prim->u3 = uCoord + *dataPtr++;
                        prim->v2 = prim->v3 = vCoord + *dataPtr++;
                    }
                    prim->tpage = 18;
                    prim->clut = palette;
                    prim->priority = self->zPriority + 2;
                    prim->drawMode = DRAW_UNK02;
                }
            } else {
                DestroyEntity(self);
                return;
            }
            entity = self + 1;
            DestroyEntity(entity);
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_UNK_00200000;
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 2;
            }
            self->animCurFrame = 0;
            PlaySfxPositional(SFX_SKEL_EXPLODE);
            self->step_s++;
            break;
        case 1:
            for (facingLeft = 0, prim = self->ext.cornerGuard.prim;
                 prim != NULL; prim = prim->next, prim = prim->next) {
                if (prim->p3 & 8) {
                    func_us_801D1084((EntranceCascadePrim*)prim);
                    facingLeft = 1;
                }
            }
            if (!facingLeft) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    }
    self->hitboxWidth = 7;
    self->hitboxHeight = 22;
    self->hitboxOffX = 0;
    self->hitboxOffY = 2;
    if (self->animCurFrame >= 10 && self->animCurFrame < 14) {
        self->hitboxWidth = 17;
        self->hitboxHeight = 9;
        self->hitboxOffX = -6;
        self->hitboxOffY = 12;
    }
}

// Corner Guard attack?
void func_us_801D1C24(Entity* self) {
    s32 animCurFrame;
    s8* hitboxPtr;
    Entity* entity;

    if (!self->step) {
        InitializeEntity(D_us_801809EC);
    }
    entity = self - 1;
    if ((entity->entityId) != E_CORNER_GUARD) {
        DestroyEntity(self);
        return;
    }
    animCurFrame = entity->animCurFrame;
    self->facingLeft = entity->facingLeft;
    self->posX.val = entity->posX.val;
    self->posY.val = entity->posY.val;
    // It doesn't seem like this is quite right
    hitboxPtr = *g_hitbox;
    hitboxPtr += g_hitboxIdx[animCurFrame] * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}
