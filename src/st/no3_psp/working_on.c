// SPDX-License-Identifier: AGPL-3.0-or-later
// This file is most actively being worked on. Functions are being
// decompiled, pulled into their own files, and code-shared in sequence.

#include "../no3/no3.h"

// Detects if the merman is splashing into water.
// If so, creates a splash effect, and sets merman underwater to true.

// CheckMermanEnteringWater
bool func_pspeu_0924D9C0(s16 yOffset) {
    Collider collider;
    Entity* newEntity;
    s32 res = false;

    s16 x = g_CurrentEntity->posX.i.hi;
    s16 y = g_CurrentEntity->posY.i.hi + yOffset;
    g_api.CheckCollision(x, y, &collider, 0);

    if (!(collider.effects & EFFECT_SOLID)) {
        res = true;
    }

    if (collider.effects & EFFECT_WATER) {
        if (!g_CurrentEntity->ext.merman.isUnderwater) {
            newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_MERMAN_WATER_SPLASH, g_CurrentEntity, newEntity);
                newEntity->posY.i.hi += yOffset;
                newEntity->zPriority = g_CurrentEntity->zPriority;
            }
            g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
            g_CurrentEntity->ext.merman.isUnderwater = true;
        }
    }
    return res;
}

typedef enum {
    MERMAN2_INIT,
    MERMAN2_SWIMMING_UP,
    MERMAN2_SWIMMING = 3,
    MERMAN2_JUMPING,
    MERMAN2_WALKING_TO_PLAYER,
    MERMAN2_SPIT_FIRE,
    MERMAN2_7,
    MERMAN2_DYING,
} Merman2Steps;

typedef enum {
    MERMAN2_WALKING_TO_PLAYER_SETUP,
    MERMAN2_WALKING_TO_PLAYER_FACE_PLAYER,
    MERMAN2_WALKING_TO_PLAYER_WALKING,
} Merman2WalkingToPlayerSubSteps;

typedef enum {
    MERMAN2_JUMPING_SETUP,
    MERMAN2_JUMPING_UNDERWATER,
    MERMAN2_JUMPING_IN_AIR,
} Merman2JumpingSubSteps;

typedef enum {
    MERMAN2_SPIT_FIRE_FACE_PLAYER,
    MERMAN2_SPIT_FIRE_ATTACK,
} Merman2SpitFireSubSteps;

#define XY(x, y) x, y
static Point32 g_merman2Swimvels[] = {XY(FIX(0.5), FIX(-0.5)), XY(FIX(-0.5), FIX(-0.5)), XY(FIX(0.5), FIX(0.5)), XY(FIX(-0.5), FIX(0.5))};
static u8 g_merman2_walktimers[] = {0x40, 0x30, 0x50, 0x40};
static s16 g_merman_coll1[] = {XY(0, 27), XY(0, 4), XY(4, -4), XY(-8, 0)};
static s16 g_merman2_coll3[] = {XY(0, 22), XY(0, 4), XY(8, -4), XY(-16, 0)};
static s16 g_merman_coll2[] = {XY(0, 27), XY(8, 0)};
static u8 g_merman2_walkanim[] = {9, 1, 9, 2, 9, 3, 9, 4, 0};
static u8 g_merman2_spitfire[] = {24, 5, 2, 8, 2, 9, 5, 10, 11, 11, 5, 10, 2, 9, 2, 8, 8, 12, 1, 13, 255, 0};
static u8 g_merman_walkanim_init[] = {24, 7, 7, 6, 16, 5, 255, 0};
static u8 g_merman2_swim_anim[] = {11, 15, 11, 16, 0};
static u8 g_MediumWaterSplashAnim[] = {2, 19, 2, 20, 2, 21, 2, 22, 0};
static u8 g_explosion2anim[] = {7, 23, 7, 24, 7, 25, 255, 0};

extern s16 D_pspeu_09295DC8[];
extern u16 g_EInitWaterObject[];
extern u8 g_HighWaterSplashAnim[];

void EntityMerman2(Entity* self) {
    u8 colorOffset; //s8
    u8 rnd; //s7
    s16* pos; //s6
    s32 primIndex; //s5
    s32 colRes; //sp5c
    Collider collider;
    Entity* newEntity; //s1
    Primitive* prim;
    s16 posX, posY; //s4, s3
    s32 i; //s2

    if (self->ext.merman2.ignoreCol && (self->step < MERMAN2_7)) {
        SetStep(MERMAN2_7);
    }

    if ((self->flags & FLAG_DEAD) && (self->step < MERMAN2_DYING)) {
        PlaySfxPositional(0x71D);
        self->drawFlags = FLAG_DRAW_DEFAULT;
        if (self->flags & FLAG_HAS_PRIMS) {
            primIndex = self->primIndex;
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }
        self->flags &= ~FLAG_UNK_20000000;
        self->hitboxState = 0;
        SetStep(MERMAN2_DYING);
    }

    switch (self->step) {
    case MERMAN2_INIT:
        InitializeEntity(g_EInitWaterObject);
        self->hitboxOffY = 8;
        self->zPriority = 0xA9;
        if (self->params) {
            self->palette++;
        }
        self->velocityY = FIX(-1);
        break;

    case MERMAN2_SWIMMING_UP:
        AnimateEntity(g_merman2_swim_anim, self);
        MoveEntity();
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.effects & EFFECT_WATER)) {
            SetStep(MERMAN2_SWIMMING);
        }
        break;

    case MERMAN2_SWIMMING:
        if (!self->step_s) {
            rnd = Random() & 3;
            self->velocityX = g_merman2Swimvels[rnd].x;
            self->velocityY = g_merman2Swimvels[rnd].y;
            self->step_s++;
        }
        if (AnimateEntity(g_merman2_swim_anim, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        MoveEntity();
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.effects & EFFECT_WATER)) {
            self->velocityY = FIX(0.5);
        }
        posY += g_Tilemap.scrollY.i.hi;
        pos = D_pspeu_09295DC8;
        pos += (self->params & 0x100) >> 8;
        if (posY > pos[4]) {
            self->posY.i.hi = pos[4] - g_Tilemap.scrollY.i.hi - 24;
        }

        if (self->ext.merman2.timer++ > 32) {
            self->ext.merman2.timer = 0;
            self->step_s = 0;
            if ((GetDistanceToPlayerX() >= 48) && !(Random() & 1)) {
                SetStep(MERMAN2_JUMPING);
            }
        }
        break;

    case MERMAN2_JUMPING:
        switch (self->step_s) {
        case MERMAN2_JUMPING_SETUP:
            self->velocityX = 0;
            self->velocityY = FIX(-8.5);
            self->step_s++;
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                self->animCurFrame = 0;
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.merman2.prim = prim;
                prim->tpage = 0x12;
                prim->clut = 0x28C;
                if (self->params & 1) {
                    prim->clut++;
                }
                prim->u0 = 0;
                prim->u1 = prim->u0 + 0x20;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0x38;
                prim->v1 = prim->v0;
                prim->v2 = prim->v0 + 0x38;
                prim->v3 = prim->v2;

                // These should probably be written some other way
                if (self->facingLeft) {
                    prim->x0 = (self->posX.i.hi - 0x8000) - 0x7FF1;
                    prim->x1 = prim->x0 - 0x20;
                } else {
                    prim->x0 = (self->posX.i.hi + 0x7FFF) + 0x7FF2;
                    prim->x1 = prim->x0 + 0x20;
                }
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
                prim->y0 = (self->posY.i.hi + 0x7FFF) + 0x7FF0;
                prim->y1 = prim->y0;
                prim->y2 = prim->y0 + 0x38;
                prim->y3 = prim->y2;
                setRGB0(prim, 64, 64, 160);
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);

                prim->priority = self->zPriority;
                prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            } else {
                self->animCurFrame = 17;
                DestroyEntity(self);
            }
            break;

        case MERMAN2_JUMPING_UNDERWATER:
            MoveEntity();
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            posY -= 24;
            posY += g_Tilemap.scrollY.i.hi;
            pos = D_pspeu_09295DC8;
            pos += (self->params & 0x100) >> 8;
            
            if (posY < pos[3]) {
                g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_MERMAN_WATER_SPLASH, self, newEntity);
                    newEntity->posY.i.hi -= 24;
                    newEntity->zPriority = self->zPriority;
                }
                self->drawFlags |= FLAG_DRAW_ROTZ;
                self->rotZ = 0;
                self->step_s++;
            }
            break;

        case MERMAN2_JUMPING_IN_AIR:
            prim = self->ext.merman2.prim;
            if (self->velocityY > ~0xBFFF) {
                prim->drawMode = DRAW_HIDE;
                self->animCurFrame = 18;
                self->rotZ -= 0x80;
                self->hitboxHeight = 8;
            } else {
                // These should probably be written some other way
                if (self->facingLeft) {
                    prim->x0 = (self->posX.i.hi - 0x8000) - 0x7FF1;
                    prim->x1 = prim->x0 - 0x20;
                } else {
                    prim->x0 = (self->posX.i.hi + 0x7FFF) + 0x7FF2;
                    prim->x1 = prim->x0 + 0x20;
                }
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
                prim->y0 = (self->posY.i.hi + 0x7FFF) + 0x7FF0;
                prim->y1 = prim->y0;
                prim->y2 = prim->y0 + 0x38;
                prim->y3 = prim->y2;

                colorOffset = (abs(self->velocityY) >> 0xC) - 10;

                setRGB0(prim, 128 - colorOffset / 2, 128 - colorOffset / 2, colorOffset /2 + 192);

                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
            }
            if (self->velocityY < 0) {
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN2_JUMP_AIR, self, newEntity);
                    newEntity->posX.i.hi += ((Random() & 3) * 4) - 6;
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
            if (self->velocityY > 0) {
                func_pspeu_0924D9C0(0x1B);
            }
            if (!self->ext.merman2.isUnderwater) {
                if (UnkCollisionFunc3(&g_merman_coll1) & 1) {
                    primIndex = self->primIndex;
                    g_api.FreePrimitives(primIndex);
                    self->flags &= ~FLAG_HAS_PRIMS;
                    self->drawFlags &=
                        FLAG_BLINK | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                        FLAG_DRAW_UNK10 | FLAG_DRAW_OPACITY | FLAG_DRAW_ROTY |
                        FLAG_DRAW_ROTX;
                    self->hitboxHeight = 21;
                    SetStep(MERMAN2_WALKING_TO_PLAYER);
                }
            } else {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                               FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
                MoveEntity();
                self->velocityY += FIX(0.25);
            }
        }
        break;

    case MERMAN2_WALKING_TO_PLAYER:
        switch (self->step_s) {
        case MERMAN2_WALKING_TO_PLAYER_SETUP:
            if (AnimateEntity(g_merman_walkanim_init, self) == 0) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;

        case MERMAN2_WALKING_TO_PLAYER_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            rnd = Random() & 3;
            self->ext.merman2.timer = g_merman2_walktimers[rnd];
            self->step_s++;
            break;

        case MERMAN2_WALKING_TO_PLAYER_WALKING:
            AnimateEntity(g_merman2_walkanim, self);
            colRes = UnkCollisionFunc2(&g_merman_coll2);
            if (colRes == 0xFF) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft) {
                self->velocityX = FIX(0.375);
            } else {
                self->velocityX = FIX(-0.375);
            }

            if (colRes & 0x80) {
                self->posX.val += self->velocityX;
            }

            if ((self->params & 1)){
                self->velocityX *= 2;
            }
            if(!(self->params & 1)) {
                if ((self->posX.i.hi & 0xFF00)) {
                    break;
                }
                if (!--self->ext.merman2.timer) {
                    if (Random() & 1) {
                        SetStep(MERMAN2_SPIT_FIRE);
                    } else {
                        self->step_s--;
                    }
                }
                
            }
            if (func_pspeu_0924D9C0(0x1B)) {
                self->ext.merman2.ignoreCol = 1;
            }
            
        }
        break;

    case MERMAN2_SPIT_FIRE:
        switch (self->step_s) {
        case MERMAN2_SPIT_FIRE_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            break;

        case MERMAN2_SPIT_FIRE_ATTACK:
            if (AnimateEntity(g_merman2_spitfire, self) == 0) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_MEDIUM_WATER_SPLASH, self, newEntity);
                    newEntity->posY.i.hi -= 12;
                    newEntity->facingLeft = self->facingLeft;
                }
                for (i = 0; i < 3; i++) {
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(
                            E_MERMAN2_SPIT_FIRE, self, newEntity);
                        if (self->facingLeft) {
                            newEntity->posX.i.hi += (8 + i * 8);
                        } else {
                            newEntity->posX.i.hi -= (8 + i * 8);
                        }
                        newEntity->posY.i.hi -= 12;
                        newEntity->facingLeft = self->facingLeft;
                        if (i == 0) {
                            newEntity->params = 1;
                        }
                    }
                }
                self->drawFlags |= FLAG_DRAW_ROTZ;
                self->rotZ = 0;
                self->ext.merman2.rotation = 1;
                if (self->facingLeft) {
                    self->velocityX = FIX(-6);
                } else {
                    self->velocityX = FIX(6);
                }
                self->velocityY = FIX(-0.0625);
                self->posY.i.hi -= 1;
                self->step_s++;
            }
            break;

        case 2:
            if ((self->ext.merman2.rotation < 0x100) && (g_Timer % 2)) {
                self->ext.merman2.rotation *= 2;
            }
            if (self->velocityX != 0) {
                if (self->facingLeft) {
                    self->velocityX += FIX(0.1875);
                } else {
                    self->velocityX -= FIX(0.1875);
                }
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            if (self->facingLeft) {
                posX -= 20;
            } else {
                posX += 20;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
            }
            self->rotZ += self->ext.merman2.rotation;
            self->velocityY -= FIX(0.125);

            if (UnkCollisionFunc3(&g_merman_coll1) & 1) {
                if (self->facingLeft) {
                    self->velocityX = FIX(-2.5);
                } else {
                    self->velocityX = FIX(2.5);
                }
                self->ext.merman2.rotation = 4;
                self->posY.i.hi += 10;
                self->step_s++;
            }
            func_pspeu_0924D9C0(0x1B);
            if (self->ext.merman2.isUnderwater) {
                self->ext.merman2.ignoreCol = 1;
            }
            break;

        case 3:
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            if (self->facingLeft) {
                posX -= 20;
            } else {
                posX += 20;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
            }
            MoveEntity();
            self->rotZ += 0xC0;
            if (self->rotZ > 0x1000) {
                self->posY.i.hi -= 10;
                self->drawFlags &=
                    FLAG_BLINK | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                    FLAG_DRAW_UNK10 | FLAG_DRAW_OPACITY | FLAG_DRAW_ROTY |
                    FLAG_DRAW_ROTX;
                SetStep(MERMAN2_WALKING_TO_PLAYER);
            }
            if (func_pspeu_0924D9C0(0x1B)) {
                self->ext.merman2.ignoreCol = 1;
            }
        }
        break;

    case MERMAN2_7:
        if (!self->step_s) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += FIX(0.25);
        if (!(func_pspeu_0924D9C0(0x1B)) &&
            !(self->ext.merman2.isUnderwater)) {
            self->ext.merman2.ignoreCol = 0;
            SetStep(MERMAN2_WALKING_TO_PLAYER);
        }
        break;

    case MERMAN2_DYING:
        switch (self->step_s) {
        case 0:
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
            self->animCurFrame = 14;
            if ((GetSideToPlayer() & 1)) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = FIX(-1);
            self->step_s++;
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.merman2.prim = prim;
                UnkPolyFunc2(prim);
                prim->tpage = 0x12;
                prim->clut = 0x292;
                if (self->params & 1) {
                    prim->clut++;
                }
                if (self->facingLeft) {
                    prim->u0 = 0xF0;
                    prim->u1 = prim->u0 - 0x28;
                } else {
                    prim->u0 = 0xC8;
                    prim->u1 = prim->u0 + 0x28;
                }
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0;
                prim->v1 = prim->v0;
                prim->v2 = prim->v0 + 0x30;
                prim->v3 = prim->v2;

                prim->priority = self->zPriority + 1;
                prim->drawMode = DRAW_UNK02;
                *(s16*)&prim->next->r2 = 0x28;
                *(s16*)&prim->next->b2 = 0x30;
                prim->next->b3 = 0x80;
                if (self->facingLeft) {
                    prim->next->x1 = self->posX.i.hi - 3;
                } else {
                    prim->next->x1 = self->posX.i.hi + 3;
                }
                prim->next->y0 = self->posY.i.hi + 2;
            }
            UnkPrimHelper(prim);
            break;

        case 1:
            UnkCollisionFunc3(&g_merman2_coll3);
            self->velocityY -= FIX(0.1875);
            prim = self->ext.merman2.prim;
            if (self->facingLeft) {
                prim->next->x1 = self->posX.i.hi - 3;
            } else {
                prim->next->x1 = self->posX.i.hi + 3;
            }
            prim->next->y0 = self->posY.i.hi + 2;
            UnkPrimHelper(prim);
            if (!(g_Timer % 10)) {
                prim->clut += 2;
                if (prim->clut > 0x29F) {
                    prim->drawMode = DRAW_HIDE;
                    self->step_s++;
                } else {
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(
                            E_MERMAN2_DYING, self, newEntity);
                        newEntity->facingLeft = self->facingLeft;
                        newEntity->params = prim->clut;
                        newEntity->zPriority = self->zPriority;
                    }
                }
            }
            func_pspeu_0924D9C0(0x1B);
            break;

        case 2:
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            CreateExplosionPuff();
            DestroyEntity(self);
        }
        break;
    }
}

void EntityMermanFireSpit(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    if (!self->step) {
        InitializeEntity(g_EInitWaterObject);
        self->zPriority += 4;
        self->animCurFrame = 0;
        self->hitboxState = 0;
        if (self->params) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.EntityMermanFireSpit.prim = prim;
                UnkPolyFunc2(prim);
                prim->tpage = 0x1A;
                prim->clut = 0x1FF;
                prim->u0 = 0;
                prim->u1 = 0x20;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0;
                prim->v1 = prim->v0;
                prim->v2 = 0x20;
                prim->v3 = prim->v2;
                
                LOH(prim->next->r2) = 0x40;
                LOH(prim->next->b2) = 0x40;
                LOH(prim->next->u1) = 0;
                prim->next->b3 = 0x60;
                prim->next->x1 = self->posX.i.hi;
                prim->next->y0 = self->posY.i.hi;
                prim->priority = self->zPriority - 4;
                prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            } else {
                DestroyEntity(self);
                return;
            }
        }
    }

    if (self->params) {
        prim = self->ext.EntityMermanFireSpit.prim;
        UnkPrimHelper(prim);
        prim->next->b3 -= 4;
        LOH(prim->next->u1) -= 128;
        if (prim->next->b3 < 16) {
            prim->drawMode = DRAW_HIDE;
        }
    }

    self->ext.EntityMermanFireSpit.unk84++;
    if (!(self->ext.EntityMermanFireSpit.unk84 % 4)) {
        self->posY.i.hi++;
    }

    if (AnimateEntity(g_explosion2anim, self) == 0) {
        DestroyEntity(self);
    }
}

// medium sized water splash used with merman
void EntityMediumWaterSplash(Entity* self) {
    Entity* newEntity;

    if (!self->step) {
        InitializeEntity(g_EInitWaterSplash);
        self->animCurFrame = 0;
        if (self->facingLeft) {
            self->velocityX = FIX(2);
            return;
        }
        self->velocityX = FIX(-2);
        return;
    }
    AnimateEntity(g_MediumWaterSplashAnim, self);
    MoveEntity();
    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0;
        }
        DestroyEntity(self);
    }
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityMermanWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityMerman2JumpAir);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityHighWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityDeadMerman);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityMermanSpawner);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityMerman);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityMermanFireball);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityMermanJumpAir);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityMermanExplosion);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", func_pspeu_092516E8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", func_pspeu_09251C70);
