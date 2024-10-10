// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "../e_merman2.h"

s32 func_801D2D40(s16 yVector) {
    s16 newY = yVector + g_CurrentEntity->posY.i.hi;
    s32 expectedResult = 0;
    Collider collider;
    Entity* newEntity;
    s32 res;

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi, newY, &collider, 0);
    res = expectedResult == (collider.effects & EFFECT_SOLID);

    if (collider.effects & EFFECT_WATER) {
        if (!g_CurrentEntity->ext.merman.isUnderwater) {
            newEntity = AllocEntity(g_Entities + 232, g_Entities + 256);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_MERMAN_JUMP_WATER, g_CurrentEntity, newEntity);
                newEntity->posY.i.hi += yVector;
                newEntity->zPriority = g_CurrentEntity->zPriority;
            }
            g_api.PlaySfx(SE_WATER_SPLASH);
            g_CurrentEntity->ext.merman.isUnderwater = true;
        }
    }
    return res;
}

extern u16 D_80180B48[];
extern s16 g_WaterXTbl[];     // pos TBL
extern Point32 D_80183914[]; // accel_x TBL
extern s32 D_80183938;       // Collision data
extern u8 D_80183984[];      // Animation
extern u8 D_8018398C[];      // Animation
extern u8 D_80183934[];      // timers
extern s32 D_80183948;       // Collision data
extern u16 D_80183958;       // Collision data
extern u8 D_80183960[];      // Animation
extern u8 D_8018396C[];      // Animation

void EntityMerman2(Entity* self) {
    s32 primIndex;
    Collider collider;
    Entity* newEntity;
    Entity* newEntity2;
    Primitive* prim;
    s16 posX, posY;
    s32 colRes;
    s32 offset;
    u32 colorOffset;
    s16* pos;
    s16 camY;
    s32 rnd;
    s32 i;

    if (self->ext.merman2.ignoreCol && (self->step < MERMAN2_7)) {
        SetStep(MERMAN2_7);
    }

    if ((self->flags & FLAG_DEAD) && (self->step < MERMAN2_DYING)) {
        PlaySfxPositional(0x71D);
        self->drawFlags = FLAG_DRAW_DEFAULT;
        if (self->flags & FLAG_HAS_PRIMS) {
            g_api.FreePrimitives(self->primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }
        self->hitboxState = 0;
        self->flags &= ~FLAG_UNK_20000000;
        SetStep(MERMAN2_DYING);
    }

    switch (self->step) {
    case MERMAN2_INIT:
        InitializeEntity(D_80180B48);
        self->hitboxOffY = 8;
        self->zPriority = 0xA9;
        if (self->params != 0) {
            self->palette++;
        }
        self->velocityY = FIX(-1);
        break;

    case MERMAN2_SWIMMING_UP:
        AnimateEntity(D_8018398C, self);
        MoveEntity();
        posY = self->posY.i.hi - 24;
        g_api.CheckCollision(self->posX.i.hi, posY, &collider, 0);
        if (!(collider.effects & EFFECT_WATER)) {
            SetStep(MERMAN2_SWIMMING);
        }
        break;

    case MERMAN2_SWIMMING:
        if (self->step_s == 0) {
            rnd = Random() & 3;
            self->velocityX = D_80183914[rnd].x;
            self->velocityY = D_80183914[rnd].y;
            self->step_s++;
        }
        if (AnimateEntity(D_8018398C, self) == 0) {
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
        pos = g_WaterXTbl;
        pos += (self->params >> 8) & 1;
        posY += g_Tilemap.scrollY.i.hi;
        if (pos[4] < posY) {
            self->posY.i.hi = pos[4] - g_Tilemap.scrollY.i.hi - 24;
        }

        if ((u8)self->ext.merman2.timer++ > 32) {
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
                u32 v0;
                prim = &g_PrimBuf[primIndex];
                self->animCurFrame = 0;
                self->primIndex = primIndex;
                self->ext.merman2.prim = prim;
                self->flags |= FLAG_HAS_PRIMS;
                prim->tpage = 0x12;
                prim->clut = 0x28C;
                if (self->params & 1) {
                    prim->clut = 0x28D;
                }
                prim->u0 = 0;
                prim->u1 = 0x20;
                prim->v1 = prim->v0 = 0x38;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                v0 = prim->v0 + 0x38;
                prim->v2 = v0;
                prim->v3 = v0;

                if (self->facingLeft != 0) {
                    s16 posX = self->posX.i.hi;
                    prim->x0 = posX + 15;
                    prim->x1 = posX - 17;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                } else {
                    s16 posX = self->posX.i.hi;
                    prim->x0 = posX - 15;
                    prim->x1 = posX + 17;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                }
                prim->y0 = prim->y1 = self->posY.i.hi - 17;

                setRGB0(prim, 64, 64, 160);

                *(s32*)&prim->r1 = *(s32*)&prim->r0;
                *(s32*)&prim->r2 = *(s32*)&prim->r0;
                *(s32*)&prim->r3 = *(s32*)&prim->r0;

                prim->y3 = prim->y2 = prim->y0 + 0x38;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            } else {
                self->animCurFrame = 17;
                DestroyEntity(self);
            }
            break;

        case MERMAN2_JUMPING_UNDERWATER:
            MoveEntity();
            pos = g_WaterXTbl;
            pos += (self->params >> 8) & 1;
            posY = self->posY.i.hi;
            posY -= 24;
            camY = g_Tilemap.scrollY.i.hi + posY;
            if (camY < pos[3]) {
                g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_MERMAN_JUMP_WATER, self, newEntity);
                    newEntity->posY.i.hi -= 24;
                    newEntity->zPriority = self->zPriority;
                }
                self->rotZ = 0;
                self->drawFlags |= FLAG_DRAW_ROTZ;
                self->step_s++;
            }
            break;

        case MERMAN2_JUMPING_IN_AIR:
            prim = self->ext.merman2.prim;
            if (self->velocityY > ~0xBFFF) {
                prim->drawMode = DRAW_HIDE;
                self->animCurFrame = 18;
                self->hitboxHeight = 8;
                self->rotZ -= 0x80;
            } else {
                if (self->facingLeft != 0) {
                    s16 posX = self->posX.i.hi;
                    prim->x0 = posX + 15;
                    prim->x1 = posX - 17;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                    prim->y1 = prim->y0 = self->posY.i.hi - 17;
                    prim->y3 = prim->y2 = prim->y0 + 0x38;
                } else {
                    s16 posX = self->posX.i.hi;
                    prim->x0 = posX - 15;
                    prim->x1 = posX + 17;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                    prim->y1 = prim->y0 = self->posY.i.hi - 17;
                    prim->y3 = prim->y2 = prim->y0 + 0x38;
                }

                colorOffset =
                    (u32)(((__builtin_abs(self->velocityY) >> 0xC) - 10) &
                          0xFF) >>
                    1;

                setRGB0(prim, 128 - colorOffset, 128 - colorOffset,
                        colorOffset + 192);

                *(s32*)&prim->r1 = *(s32*)&prim->r0;
                *(s32*)&prim->r2 = *(s32*)&prim->r0;
                *(s32*)&prim->r3 = *(s32*)&prim->r0;
            }
            if (self->velocityY < 0) {
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN2_JUMP_AIR, self, newEntity);
                    newEntity->posX.i.hi -= 6 - ((Random() & 3) * 4);
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
            if (self->velocityY > 0) {
                func_801D2D40(0x1B);
            }
            if (self->ext.merman2.isUnderwater == 0) {
                if (UnkCollisionFunc3(&D_80183938) & 1) {
                    g_api.FreePrimitives(self->primIndex);
                    self->hitboxHeight = 21;
                    self->flags &= ~FLAG_HAS_PRIMS;
                    self->drawFlags &=
                        FLAG_DRAW_UNK80 | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                        FLAG_DRAW_UNK10 | FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY |
                        FLAG_DRAW_ROTX;
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
            if (AnimateEntity(D_80183984, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;

        case MERMAN2_WALKING_TO_PLAYER_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.merman2.timer = D_80183934[Random() & 3];
            self->step_s++;
            break;

        case MERMAN2_WALKING_TO_PLAYER_WALKING:
            AnimateEntity(D_80183960, self);
            colRes = UnkCollisionFunc2(&D_80183958);
            if (colRes == 0xFF) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.375);
            } else {
                self->velocityX = FIX(0.375);
            }

            if (colRes & 0x80) {
                self->posX.val += self->velocityX;
            }

            if (!(self->params & 1) ||
                (self->velocityX *= 2, !(self->params & 1))) {
                if (!(self->posX.i.hi & 0xFF00)) {
                    self->ext.merman2.timer--;
                    if ((self->ext.merman2.timer & 0xFF) == 0) {
                        if (Random() % 2) {
                            SetStep(MERMAN2_SPIT_FIRE);
                        } else {
                            self->step_s--;
                        }
                    }
                    if (func_801D2D40(0x1B)) {
                        self->ext.merman2.ignoreCol = 1;
                    }
                }
            } else {
                if (func_801D2D40(0x1B)) {
                    self->ext.merman2.ignoreCol = 1;
                }
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
            if (AnimateEntity(D_8018396C, self) == 0) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                i = 0;
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN2_UNK1, self, newEntity);
                    newEntity->posY.i.hi -= 12;
                    newEntity->facingLeft = self->facingLeft;
                }
                newEntity2 = g_Entities + 224;
                for (offset = 0; i < 3; i++, offset += 8) {
                    newEntity = AllocEntity(newEntity2, newEntity2 + 32);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(
                            E_MERMAN2_SPIT_FIRE, self, newEntity);
                        if (self->facingLeft != 0) {
                            newEntity->posX.i.hi += 8 + offset;
                        } else {
                            newEntity->posX.i.hi += -8 - offset;
                        }
                        newEntity->posY.i.hi -= 12;
                        newEntity->facingLeft = self->facingLeft;
                        if (i == 0) {
                            newEntity->params = 1;
                        }
                    }
                }
                self->ext.merman2.rotation = 1;
                self->rotZ = 0;
                self->drawFlags |= FLAG_DRAW_ROTZ;
                if (self->facingLeft != 0) {
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
            if ((self->ext.merman2.rotation < 0x100) && (g_Timer & 1)) {
                self->ext.merman2.rotation *= 2;
            }
            if (self->velocityX != 0) {
                if (self->facingLeft != 0) {
                    self->velocityX += FIX(0.1875);
                } else {
                    self->velocityX -= FIX(0.1875);
                }
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            if (self->facingLeft != 0) {
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

            if (UnkCollisionFunc3(&D_80183938) & 1) {
                if (self->facingLeft == 0) {
                    self->velocityX = FIX(2.5);
                } else {
                    self->velocityX = FIX(-5.0 / 2.0);
                }
                self->ext.merman2.rotation = 4;
                self->posY.i.hi += 10;
                self->step_s++;
            }
            func_801D2D40(0x1B);
            if (self->ext.merman2.isUnderwater) {
                self->ext.merman2.ignoreCol = 1;
            }
            break;

        case 3:
            posY = self->posY.i.hi + 8;
            posX = self->posX.i.hi;
            if (self->facingLeft != 0) {
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
                    FLAG_DRAW_UNK80 | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                    FLAG_DRAW_UNK10 | FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY |
                    FLAG_DRAW_ROTX;
                SetStep(MERMAN2_WALKING_TO_PLAYER);
            }
            if (func_801D2D40(0x1B)) {
                self->ext.merman2.ignoreCol = 1;
            }
        }
        break;

    case MERMAN2_7:
        if (self->step_s == 0) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += FIX(0.25);
        if (!(func_801D2D40(0x1B)) && !(self->ext.merman2.isUnderwater)) {
            self->ext.merman2.ignoreCol = 0;
            SetStep(MERMAN2_WALKING_TO_PLAYER);
        }
        break;

    case MERMAN2_DYING:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 14;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
            if (!(GetSideToPlayer() & 1)) {
                self->velocityX = FIX(-2);
            } else {
                self->velocityX = FIX(2);
            }
            self->velocityY = FIX(-1);
            self->step_s++;
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                u32 v0;
                prim = &g_PrimBuf[primIndex];
                self->primIndex = primIndex;
                self->ext.merman2.prim = prim;
                self->flags |= FLAG_HAS_PRIMS;
                UnkPolyFunc2(prim);
                prim->tpage = 0x12;
                prim->clut = 0x292;
                if (self->params & 1) {
                    prim->clut = 0x293;
                }
                if (self->facingLeft != 0) {
                    u32 u1 = 0x1C8;
                    prim->u0 = 0xF0;
                    prim->u1 = u1;
                } else {
                    prim->u0 = 0xC8;
                    prim->u1 = 0xF0;
                }

                prim->v0 = prim->v1 = 0;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                v0 = prim->v0 + 0x30;
                prim->v2 = v0;
                prim->v3 = v0;

                prim->priority = self->zPriority + 1;
                prim->drawMode = DRAW_UNK02;
                *(s16*)&prim->next->r2 = 0x28;
                *(s16*)&prim->next->b2 = 0x30;
                prim->next->b3 = 0x80;
                if (self->facingLeft != 0) {
                    prim->next->x1 = self->posX.i.hi - 3;
                } else {
                    prim->next->x1 = self->posX.i.hi + 3;
                }
                prim->next->y0 = self->posY.i.hi + 2;
            }
            UnkPrimHelper(prim);
            break;

        case 1:
            UnkCollisionFunc3(&D_80183948);
            prim = self->ext.merman2.prim;
            self->velocityY -= FIX(0.1875);
            if (self->facingLeft != 0) {
                prim->next->x1 = self->posX.i.hi - 3;
            } else {
                prim->next->x1 = self->posX.i.hi + 3;
            }
            prim->next->y0 = self->posY.i.hi + 2;
            UnkPrimHelper(prim);
            if (!(g_Timer % 10)) {
                prim->clut += 2;
                if (prim->clut >= 0x2A0) {
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
            func_801D2D40(0x1B);
            break;

        case 2:
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            func_801C13F8();
            DestroyEntity(self);
        }
        break;
    }
}

// some sort of explosion
void EntityExplosion2(Entity* self) {
    Primitive* prim;
    s16 primIndex;

    if (self->step == 0) {
        InitializeEntity(D_80180B48);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->zPriority += 4;
        if (self->params != 0) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.entityExplosion2.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
            UnkPolyFunc2(prim);
            prim->u0 = 0;
            prim->u1 = 0x20;
            prim->tpage = 0x1A;
            prim->clut = 0x1FF;
            prim->v3 = prim->v2 = 0x20;
            prim->v1 = prim->v0 = 0;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            LOH(prim->next->r2) = 0x40;
            LOH(prim->next->b2) = 0x40;
            LOH(prim->next->u1) = 0;
            prim->next->b3 = 0x60;
            prim->next->x1 = (u16)self->posX.i.hi;
            prim->next->y0 = (u16)self->posY.i.hi;
            prim->priority = self->zPriority - 4;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        }
    }

    if (self->params != 0) {
        prim = self->ext.entityExplosion2.prim;
        UnkPrimHelper(prim);
        prim->next->b3 += 252;
        LOH(prim->next->u1) -= 128;
        if (prim->next->b3 < 16) {
            prim->drawMode = DRAW_HIDE;
        }
    }

    self->ext.entityExplosion2.unk84++;
    if (!(self->ext.entityExplosion2.unk84 % 4)) {
        self->posY.i.hi++;
    }

    if (AnimateEntity(D_801839A0, self) == 0) {
        DestroyEntity(self);
    }
}

// medium sized water splash used with merman
void EntityMediumWaterSplash(Entity* entity) {
    Entity* newEntity;

    if (entity->step == 0) {
        InitializeEntity(D_80180B54);
        entity->animCurFrame = 0;
        if (entity->facingLeft != 0) {
            entity->velocityX = FIX(2);
            return;
        }
        entity->velocityX = FIX(-2);
        return;
    }
    AnimateEntity(D_80183994, entity);
    MoveEntity();
    if (entity->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
            newEntity->params = 0;
        }
        DestroyEntity(entity);
    }
}

// spawns EntityMediumWaterSplash, part of merman splash
void EntityMermanWaterSplash(Entity* self) {
    Unkstruct_801C7954 sp;
    Entity* newEntity;
    Primitive* prim;
    s16 primIndex;
    s16* posPtr;
    s32* velPtr;
    u8 temp;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        break;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.mermanWaterSplash.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;

        for (i = 0; prim != NULL; i++) {
            prim->g0 = prim->r0 = 64;
            prim->b0 = 160;
            prim->v0 = prim->u0 = 2;
            prim->x0 = self->posX.i.hi + D_801839E8[i];
            prim->y0 = self->posY.i.hi - 12;
            LOW(sp.y3) = D_801839C0[i].x;
            prim->y1 = sp.y1;
            prim->y3 = sp.y3;
            LOW(sp.x3) = D_801839C0[i].y;
            prim->x2 = sp.x2;
            prim->x3 = sp.x3;
            prim->p1 = 0;
            prim->p3 = 1;
            prim->p2 = i % 2;
            prim->priority = self->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }

        posPtr = &D_801839FC;
        velPtr = &D_80183A0C;

        for (i = 0; i < 7; i++) {
            newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_HIGH_WATER_SPLASH, self, newEntity);
                newEntity->params = D_801839F4[i];
                newEntity->posX.i.hi = newEntity->posX.i.hi + posPtr[i];
                newEntity->velocityX = velPtr[i];
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        self->ext.mermanWaterSplash.unk84 = 0;
        self->ext.mermanWaterSplash.unk86 = 0;
        self->step++;
        break;

    case 2:
        prim = self->ext.mermanWaterSplash.prim;
        temp = false;
        while (prim != NULL) {
            if (prim->p1 == 0) {
                sp.x0 = prim->x0;
                sp.x1 = prim->x1;
                sp.y0 = prim->y0;
                sp.y2 = prim->y2;
                sp.y1 = prim->y1;
                sp.y3 = prim->y3;
                sp.x2 = prim->x2;
                sp.x3 = prim->x3;
                temp |= true;
                LOW(sp.x1) += LOW(sp.y3);
                LOW(sp.y2) += LOW(sp.x3);
                LOW(sp.x3) += 0x2000;
                if ((LOW(sp.x3) > 0) && (prim->p2 != 0) && (prim->p3 != 0)) {
                    if (LOH(sp.x0) > self->posX.i.hi) {
                        LOW(sp.y3) += 0x4000;
                    } else {
                        LOW(sp.y3) -= 0x4000;
                    }
                    prim->p3 = 0;
                }
                if (prim->y0 & 0xFF00) {
                    prim->p1 = 1;
                    prim->drawMode |= DRAW_HIDE;
                }
                prim->x0 = sp.x0;
                prim->x1 = sp.x1;
                prim->y0 = sp.y0;
                prim->y2 = sp.y2;
                prim->x2 = sp.x2;
                prim->x3 = sp.x3;
                prim->y1 = sp.y1;
                prim->y3 = sp.y3;
            }
            prim = prim->next;
        }
        if (!temp) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

// some kind of falling object
void EntityFallingObject2(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180B48);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->flags |= FLAG_UNK_2000;
        self->zPriority += 4;
    }
    MoveEntity();
    self->velocityY += FIX(0.15625);
    if (AnimateEntity(D_801839A8, self) == 0) {
        DestroyEntity(self);
    }
}

void EntityHighWaterSplash(Entity* self) {
    s8 temp; // probably !FAKE

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = ANIMSET_DRA(2);
        self->velocityY = FIX(-5);
        self->palette = 0x8162;
        self->drawMode = DRAW_TPAGE;
        self->palette = 0x8018;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->unk6C = 0xA0;
        self->rotX = 0x100;
        self->rotY = 0x1A0;
        self->drawFlags |= FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        self->ext.mermanWaterSplash.unk85 = 0x11;
        self->ext.mermanWaterSplash.unk84 = self->params;
        self->drawFlags |= FLAG_DRAW_UNK8;
        break;

    case 1:
        temp = self->ext.mermanWaterSplash.unk84 - 1;
        self->ext.mermanWaterSplash.unk84--;
        self->ext.mermanWaterSplash.unk85--;
        if (!(temp & 0xFF)) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_801839B0, self);
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotX += 6;
        self->rotY -= 4;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        if (!--self->ext.mermanWaterSplash.unk85) {
            self->velocityY = 0;
            self->step++;
        }
        break;

    case 3:
        if (AnimateEntity(D_801839B0, self) == 0) {
            MoveEntity();
            self->velocityY += FIX(0.25);
            self->rotX += 6;
            self->rotY -= 4;
        }
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        break;
    }
}

// falling object, larger
void EntityDeadMerman(Entity* self) {
    u8 temp_v0;

    if (self->step == 0) {
        InitializeEntity(D_80180B48);
        self->animCurFrame = 13;
        self->ext.generic.unk84.S8.unk0 = 0x20;
        self->hitboxState = 0;
        self->velocityY = FIX(0.0625);
        self->palette = self->params + 0xE;
        self->unk6C = 0x80;
        self->drawFlags |= FLAG_DRAW_UNK8;
        self->flags |= FLAG_UNK_2000;
        return;
    }
    MoveEntity();
    temp_v0 = self->ext.generic.unk84.U8.unk0 - 1;
    self->ext.generic.unk84.U8.unk0--;
    self->velocityY += FIX(0.0625);
    self->unk6C += 0xFE;
    if (temp_v0 == 0) {
        DestroyEntity(self);
    }
}

void EntityMermanSpawner(Entity* self) {
    Entity* newEntity;
    u16 temp_s0_2;
    u16 temp_s0;
    s32 temp2;
    s16 temp;

    if (self->step == 0) {
        InitializeEntity(D_80180AD0);
        self->flags |= FLAG_UNK_2000;
    }

    if (!(g_Timer & 0x3F)) {
        Entity* player = &PLAYER;
        temp = g_Tilemap.scrollY.i.hi + player->posY.i.hi;
        if (temp >= 256) {
            temp_s0 = g_Tilemap.scrollX.i.hi + player->posX.i.hi;
            temp_s0_2 = 128;
            temp_s0_2 = temp_s0 - temp_s0_2 + Random();
            temp_s0 = temp_s0_2 - 64;
            if (temp_s0 <= 0x280) {
                temp2 = 496;
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[170]);
                if (newEntity != 0) {
                    if (Random() & 1) {
                        CreateEntityFromCurrentEntity(
                            E_MERMAN_SPAWNER_3A, newEntity);
                        newEntity->params = Random() & 1;
                    } else {
                        CreateEntityFromCurrentEntity(
                            E_MERMAN_SPAWNER_41, newEntity);
                    }
                    newEntity->posX.i.hi = temp_s0_2 - g_Tilemap.scrollX.i.hi;
                    newEntity->posY.i.hi = temp2 - g_Tilemap.scrollY.i.hi;
                }
            }
        }
    }
}
