// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

enum CornerGuardSteps {
    CORNER_GUARD_INIT,
    CORNER_GUARD_HEAD_INIT,
    CORNER_GUARD_MOVE,
    CORNER_GUARD_SHAKE_HEAD,
    CORNER_GUARD_MOVE_RIGHT,
    CORNER_GUARD_MOVE_LEFT,
    CORNER_GUARD_SLASH,
    CORNER_GUARD_LUNGE,
    CORNER_GUARD_DEATH,
};

enum CornerGuardSubsteps {
    CORNER_GUARD_LUNGE_INIT,
    CORNER_GUARD_LUNGE_START,
    CORNER_GUARD_LUNGE_MOVE,
    CORNER_GUARD_LUNGE_CONCLUDE,
    CORNER_GUARD_LUNGE_LOOK,
};

enum CornerGuardDeathSteps {
    CORNER_GUARD_DEATH_INIT,
    CORNER_GUARD_DEATH_CONCLUDE,
};

extern EInit g_EInitCornerGuard;
extern EInit g_EInitCornerGuardAttack;

static s16 sensors_head[] = {0, 20, 0, 4, 4, -4, -8, 0};
static s16 sensors_body[] = {0, 20, 4, 0};
static Point16 pos_offsets[] = {{-16, 38}, {16, 6}};
static s16 attack_intervals[] = {32, 48, 64, 16};
static AnimateEntityFrame anim_move_left[] = {
    {5, 1}, {5, 2}, {5, 3}, {5, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim_wind_up[] = {
    {33, 1}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {1, 9}, {33, 8}, POSE_END};
static AnimateEntityFrame anim_lunge[] = {
    {1, 1},  {1, 2},   {1, 3}, {1, 10}, {1, 11}, {1, 12},
    {1, 13}, {33, 12}, {4, 3}, {4, 2},  {20, 1}, POSE_END};
static AnimateEntityFrame anim_shake_head[] = {
    {9, 1}, {9, 14}, {9, 1}, {9, 14}, {9, 1}, {9, 14}, POSE_LOOP(0)};
static AnimateEntityFrame anim_move_right[] = {
    {5, 24}, {5, 25}, {5, 26}, {5, 25}, POSE_LOOP(0)};
static AnimateEntityFrame anim_slash[] = {
    {1, 14}, {1, 15}, {1, 16}, {1, 17},  {1, 18}, {1, 19}, {8, 18},  {1, 20},
    {1, 21}, {1, 22}, {1, 23}, {33, 22}, {3, 21}, {3, 15}, {32, 14}, POSE_END};
static FrameProperty hitboxes[] = {
    {0, 0, 0, 0}, {-63, -55, 0, 0}, {-33, 30, 8, 8}, {21, -23, 9, 9}};
static u8 hitboxIdx[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2,
                         1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 0};
extern s16* sprites_dai_3[];

// Checks if Corner Guard has more stairs to move forward to
static bool CornerGuardCheckMovement(Point16* points) {
    Collider collider;
    s32 posX, posY;

    if (g_CurrentEntity->velocityX > 0) {
        points++;
    }
    posX = g_CurrentEntity->posX.i.hi + points->x;
    posY = g_CurrentEntity->posY.i.hi + points->y;
    g_api.CheckCollision(posX, posY, &collider, 0);
    // Checks if the Corner Guard would land on stairs
    if (collider.effects & EFFECT_UNK_8000) {
        return true;
    }
    return false;
}

static void CornerGuardDeath(EntranceCascadePrim* prim) {
    Entity* explosion;
    s32 psxSpPad[9];

    UnkPrimHelper(prim);
    switch (prim->next->step) {
    case CORNER_GUARD_DEATH_INIT:
        prim->next->unk10 = ((Random() & 0x1F) << 12) - FIX(1);
        prim->next->unk14 = -(Random() & 0x1F) * FLT(1);
        prim->next->step = CORNER_GUARD_DEATH_CONCLUDE;
        prim->next->velocityX.i.lo = (Random() & 0xF) + 8;
        // fallthrough
    case CORNER_GUARD_DEATH_CONCLUDE:
        if (prim->next->unk10 > 0) {
            prim->next->unk1E -= 32;
        } else {
            prim->next->unk1E += 32;
        }
        prim->next->unk14 += FLT(1.5);
        prim->next->velocityX.i.lo--;
        if (!prim->next->velocityX.i.lo) {
            explosion = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (explosion != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, explosion);
                explosion->posX.i.hi = prim->next->x1;
                explosion->posY.i.hi = prim->next->y0;
                explosion->params = EXPLOSION_SMALL;
            }
            UnkPolyFunc0(prim);
        }
        return;
    }
}

void EntityCornerGuard(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s32 uCoord, vCoord;
    s32 distance;
    bool playerOnLeft;
    s16* dataPtr;
    s16 palette;

    if ((self->flags & FLAG_DEAD) && ((self->step) < CORNER_GUARD_DEATH)) {
        SetStep(CORNER_GUARD_DEATH);
    }
    switch (self->step) {
    case CORNER_GUARD_INIT:
        InitializeEntity(g_EInitCornerGuard);
        self->animCurFrame = 1;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_CORNER_GUARD_ATTACK, entity);
        // fallthrough
    case CORNER_GUARD_HEAD_INIT:
        if (UnkCollisionFunc3(sensors_head) & 1) {
            self->ext.cornerGuard.prevPlayerOnLeft = Random() & 1;
            self->ext.cornerGuard.facingLeft =
                self->ext.cornerGuard.prevPlayerOnLeft;
            SetStep(CORNER_GUARD_MOVE);
        }
        break;
    case CORNER_GUARD_MOVE:
        self->animCurFrame = 1;
        distance = GetDistanceToPlayerX();
        if (distance < 96) {
            playerOnLeft = GetSideToPlayer() & 1;
            // Player has switched sides since last frame
            if (playerOnLeft != self->ext.cornerGuard.prevPlayerOnLeft) {
                SetStep(CORNER_GUARD_SHAKE_HEAD);
                // Player is on the left or above
            } else if (self->ext.cornerGuard.prevPlayerOnLeft) {
                SetStep(CORNER_GUARD_MOVE_LEFT);
            } else {
                SetStep(CORNER_GUARD_MOVE_RIGHT);
            }
        }
        break;
    case CORNER_GUARD_SHAKE_HEAD:
        if (!AnimateEntity(anim_shake_head, self)) {
            self->ext.cornerGuard.prevPlayerOnLeft = GetSideToPlayer() & 1;
            self->ext.cornerGuard.facingLeft =
                self->ext.cornerGuard.prevPlayerOnLeft;
            if (self->ext.cornerGuard.prevPlayerOnLeft) {
                SetStep(CORNER_GUARD_MOVE_LEFT);
            } else {
                SetStep(CORNER_GUARD_MOVE_RIGHT);
            }
        }
        break;
    case CORNER_GUARD_MOVE_RIGHT:
        if (!self->step_s) {
            self->velocityX = FIX(0.5);
            if ((self->ext.cornerGuard.prevPlayerOnLeft) ^
                (self->ext.cornerGuard.facingLeft)) {
                self->velocityX = FIX(-0.75);
            }
            self->ext.cornerGuard.attackInterval =
                attack_intervals[Random() & 3];
            self->step_s++;
        }
        AnimateEntity(anim_move_right, self);
        UnkCollisionFunc2(sensors_body);
        if (!CornerGuardCheckMovement(pos_offsets)) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        if ((self->ext.cornerGuard.prevPlayerOnLeft ^
             self->ext.cornerGuard.facingLeft) &&
            (GetDistanceToPlayerX() > 96)) {
            self->ext.cornerGuard.facingLeft =
                self->ext.cornerGuard.prevPlayerOnLeft;
            self->velocityX = FIX(0.5);
        }
        if (!self->ext.cornerGuard.attackInterval) {
            if (GetDistanceToPlayerX() < 48) {
                SetStep(CORNER_GUARD_SLASH);
            }
            playerOnLeft = GetSideToPlayer() & 1;
            if (playerOnLeft != self->ext.cornerGuard.prevPlayerOnLeft) {
                SetStep(CORNER_GUARD_SHAKE_HEAD);
            }
        } else {
            self->ext.cornerGuard.attackInterval--;
        }
        break;
    case CORNER_GUARD_SLASH:
        if (!self->step_s) {
            PlaySfxPositional(SFX_BONE_SWORD_SWISH_B);
            self->step_s++;
        }
        if (!AnimateEntity(anim_slash, self)) {
            playerOnLeft = GetSideToPlayer() & 1;
            if (playerOnLeft != self->ext.cornerGuard.prevPlayerOnLeft) {
                SetStep(CORNER_GUARD_SHAKE_HEAD);
            } else {
                SetStep(CORNER_GUARD_MOVE_RIGHT);
            }
        }
        break;
    case CORNER_GUARD_MOVE_LEFT:
        if (!self->step_s) {
            self->velocityX = FIX(-0.75);
            if (self->ext.cornerGuard.prevPlayerOnLeft ^
                (self->ext.cornerGuard.facingLeft)) {
                self->velocityX = FIX(0.5);
            }
            self->ext.cornerGuard.attackInterval =
                attack_intervals[Random() & 3];
            self->step_s++;
        }
        AnimateEntity(anim_move_left, self);
        UnkCollisionFunc2(sensors_body);
        if (!CornerGuardCheckMovement(pos_offsets)) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        if ((self->ext.cornerGuard.prevPlayerOnLeft ^
             (self->ext.cornerGuard.facingLeft)) &&
            (GetDistanceToPlayerX() > 96)) {
            self->ext.cornerGuard.facingLeft =
                self->ext.cornerGuard.prevPlayerOnLeft;
            self->velocityX = FIX(-0.75);
        }
        if (!self->ext.cornerGuard.attackInterval) {
            if (GetDistanceToPlayerX() < 96) {
                SetStep(CORNER_GUARD_LUNGE);
            }
            playerOnLeft = GetSideToPlayer() & 1;
            if (playerOnLeft != self->ext.cornerGuard.prevPlayerOnLeft) {
                SetStep(CORNER_GUARD_SHAKE_HEAD);
            }
        } else {
            self->ext.cornerGuard.attackInterval--;
        }
        break;
    case CORNER_GUARD_LUNGE:
        switch (self->step_s) {
        case CORNER_GUARD_LUNGE_INIT:
            if (!AnimateEntity(anim_wind_up, self)) {
                SetSubStep(CORNER_GUARD_LUNGE_START);
            }
            break;
        case CORNER_GUARD_LUNGE_START:
            self->velocityX = FIX(-3.0);
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            PlaySfxPositional(SFX_SCRAPE_B);
            self->step_s++;
            // fallthrough
        case CORNER_GUARD_LUNGE_MOVE:
            UnkCollisionFunc2(sensors_body);
            if (!CornerGuardCheckMovement(pos_offsets)) {
                self->posX.val -= self->velocityX;
                self->velocityX = 0;
            }
            self->velocityX -= self->velocityX / 16;
            // Generates dust if there is enough speed
            if (!(g_Timer & 7) && (abs(self->velocityX) > FIX(0.75))) {
                EntityExplosionVariantsSpawner(self, 1, 1, 12, 8, 5, 1);
            }
            if (!AnimateEntity(anim_lunge, self)) {
                self->step_s++;
            }
            break;
        case CORNER_GUARD_LUNGE_CONCLUDE:
            self->velocityX -= self->velocityX / 8;
            if (abs(self->velocityX) < FIX(0.25)) {
                self->step_s++;
            }
            break;
        case CORNER_GUARD_LUNGE_LOOK: // Looks back and forth after lunge if
                                      // the player jumped over it
            playerOnLeft = GetSideToPlayer() & 1;
            if (playerOnLeft != self->ext.cornerGuard.prevPlayerOnLeft) {
                SetStep(CORNER_GUARD_SHAKE_HEAD);
            } else {
                if (GetDistanceToPlayerX() < 64) {
                    self->ext.cornerGuard.facingLeft =
                        ((self->ext.cornerGuard.prevPlayerOnLeft) ^ 1);
                }
                SetStep(CORNER_GUARD_MOVE_LEFT);
            }
            break;
        }
        break;
    case CORNER_GUARD_DEATH:
        switch (self->step_s) {
        case CORNER_GUARD_DEATH_INIT:
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
                entity->params = EXPLOSION_SMALL_MULTIPLE;
            }
            self->animCurFrame = 0;
            PlaySfxPositional(SFX_CORNER_GUARD_DEATH);
            self->step_s++;
            break;
        case CORNER_GUARD_DEATH_CONCLUDE:
            // playerOnLeft reuse to represent whether the death sequence was
            // still occurring during this frame
            playerOnLeft = false;
            for (prim = self->ext.cornerGuard.prim; prim != NULL;
                 prim = prim->next, prim = prim->next) {
                if (prim->p3 & 8) {
                    CornerGuardDeath((EntranceCascadePrim*)prim);
                    playerOnLeft = true;
                }
            }
            if (!playerOnLeft) {
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

void EntityCornerGuardAttack(Entity* self) {
    s32 animCurFrame;
    s8* hitboxPtr;
    Entity* cornerGuard;

    if (!self->step) {
        InitializeEntity(g_EInitCornerGuardAttack);
    }
    cornerGuard = self - 1;
    if ((cornerGuard->entityId) != E_CORNER_GUARD) {
        DestroyEntity(self);
        return;
    }
    animCurFrame = cornerGuard->animCurFrame;
    self->facingLeft = cornerGuard->facingLeft;
    self->posX.val = cornerGuard->posX.val;
    self->posY.val = cornerGuard->posY.val;
    hitboxPtr = (s8*)(&hitboxes);
    hitboxPtr += hitboxIdx[animCurFrame] * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}
