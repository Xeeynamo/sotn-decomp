/*
 * Overlay: NP3
 * Description: Merman Room
 */

#include "np3.h"

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
    MERMAN2_JUMPING_SETUP,
    MERMAN2_JUMPING_UNDERWATER,
    MERMAN2_JUMPING_IN_AIR,
} Merman2JumpingSubSteps;

typedef enum {
    MERMAN2_WALKING_TO_PLAYER_SETUP,
    MERMAN2_WALKING_TO_PLAYER_FACE_PLAYER,
    MERMAN2_WALKING_TO_PLAYER_WALKING,
} Merman2WalkingToPlayerSubSteps;

typedef enum {
    MERMAN2_SPIT_FIRE_FACE_PLAYER,
    MERMAN2_SPIT_FIRE_ATTACK,
} Merman2SpitFireSubSteps;

// EntitySplashWater ID 0x2D
INCLUDE_ASM("asm/us/st/np3/nonmatchings/44DCC", func_801C4DCC);

// EntitySurfacingWater ID 0x2E
INCLUDE_ASM("asm/us/st/np3/nonmatchings/44DCC", func_801C56D8);

// EntitySideWaterSplash ID 0x2F
INCLUDE_ASM("asm/us/st/np3/nonmatchings/44DCC", func_801C5BC4);

// EntitySmallWaterDrop ID 0x30
INCLUDE_ASM("asm/us/st/np3/nonmatchings/44DCC", func_801C5F58);

// EntityWaterDrop ID 0x31
INCLUDE_ASM("asm/us/st/np3/nonmatchings/44DCC", func_801C61B4);

s32 func_801C6458(s16 yOffset) {
    s16 newY = yOffset + g_CurrentEntity->posY.i.hi;
    s32 expectedResult = 0;
    Collider collider;
    Entity* newEntity;
    s32 res;

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi, newY, &collider, 0);

    if (expectedResult == (collider.effects & EFFECT_SOLID)) {
        res = true;
    } else {
        res = false;
    }

    if (collider.effects & EFFECT_WATER) {
        if (!g_CurrentEntity->ext.merman.isUnderwater) {
            newEntity = AllocEntity(&D_8007DE38, &D_8007DE38[24]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x33, g_CurrentEntity, newEntity);
                newEntity->posY.i.hi += yOffset;
                newEntity->zPriority = g_CurrentEntity->zPriority;
            }
            g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
            g_CurrentEntity->ext.merman.isUnderwater = true;
        }
    }
    return res;
}

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

    if ((self->flags & 0x100) && (self->step < MERMAN2_DYING)) {
        func_801C2598(0x71D);
        self->unk19 = 0;
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
        InitializeEntity(D_80180AB4);
        self->hitboxOffY = 8;
        self->zPriority = 0xA9;
        if (self->params != 0) {
            self->palette++;
        }
        self->velocityY = FIX(-1);
        break;

    case MERMAN2_SWIMMING_UP:
        AnimateEntity(D_8018229C, self);
        MoveEntity();
        posY = self->posY.i.hi - 24;
        g_api.CheckCollision(self->posX.i.hi, posY, &collider, 0);
        if (!(collider.effects & EFFECT_WATER)) {
            SetStep(MERMAN2_SWIMMING);
        }
        return;

    case MERMAN2_SWIMMING:
        if (self->step_s == 0) {
            rnd = Random() & 3;
            self->velocityX = D_80182224[rnd].x;
            self->velocityY = D_80182224[rnd].y;
            self->step_s++;
        }
        if (AnimateEntity(D_8018229C, self) == 0) {
            self->facing = (GetSideToPlayer() & 1) ^ 1;
        }
        MoveEntity();
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.effects & EFFECT_WATER)) {
            self->velocityY = FIX(0.5);
        }
        pos = D_80181230;
        pos += (self->params >> 8) & 1;
        posY += g_Camera.posY.i.hi;
        if (pos[4] < posY) {
            self->posY.i.hi = pos[4] - g_Camera.posY.i.hi - 24;
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

                if (self->facing != 0) {
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
                prim->blendMode = 6;
                return;
            }
            self->animCurFrame = 17;
            DestroyEntity(self);
            break;

        case MERMAN2_JUMPING_UNDERWATER:
            MoveEntity();
            pos = D_80181230;
            pos += (self->params >> 8) & 1;
            posY = self->posY.i.hi;
            posY -= 24;
            camY = g_Camera.posY.i.hi + posY;
            if (camY < pos[3]) {
                g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
                newEntity = AllocEntity(D_8007DE38, &D_8007DE38[24]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x33, self, newEntity);
                    newEntity->posY.i.hi -= 24;
                    newEntity->zPriority = self->zPriority;
                }
                self->rotAngle = 0;
                self->unk19 |= 4;
                self->step_s++;
            }
            break;

        case MERMAN2_JUMPING_IN_AIR:
            prim = self->ext.merman2.prim;
            if (self->velocityY > ~0xBFFF) {
                prim->blendMode = BLEND_VISIBLE;
                self->animCurFrame = 18;
                self->hitboxHeight = 8;
                self->rotAngle -= 0x80;
            } else {
                if (self->facing != 0) {
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
                    (u32)(((ABS(self->velocityY) >> 0xC) - 10) & 0xFF) >> 1;

                setRGB0(prim, 128 - colorOffset, 128 - colorOffset,
                        colorOffset + 192);

                *(s32*)&prim->r1 = *(s32*)&prim->r0;
                *(s32*)&prim->r2 = *(s32*)&prim->r0;
                *(s32*)&prim->r3 = *(s32*)&prim->r0;
            }
            if (self->velocityY < 0) {
                newEntity = AllocEntity(D_8007DE38, &D_8007DE38[24]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x38, self, newEntity);
                    newEntity->posX.i.hi -= 6 - ((Random() & 3) * 4);
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
            if (self->velocityY > 0) {
                func_801C6458(0x1B);
            }
            if (self->ext.merman2.isUnderwater == 0) {
                if (func_801BC8E4(&D_80182248) & 1) {
                    g_api.FreePrimitives(self->primIndex);
                    self->hitboxHeight = 21;
                    self->flags &= ~FLAG_HAS_PRIMS;
                    self->unk19 &= 0xFB;
                    SetStep(MERMAN2_WALKING_TO_PLAYER);
                    return;
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
            if (AnimateEntity(D_80182294, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;

        case MERMAN2_WALKING_TO_PLAYER_FACE_PLAYER:
            self->facing = (GetSideToPlayer() & 1) ^ 1;
            self->ext.merman2.timer = D_80182244[Random() & 3];
            self->step_s++;
            break;

        case MERMAN2_WALKING_TO_PLAYER_WALKING:
            AnimateEntity(D_80182270, self);
            colRes = func_801BCB5C(&D_80182268);
            if (colRes == 0xFF) {
                self->facing ^= 1;
            }
            if (self->facing == 0) {
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
                    if (func_801C6458(0x1B)) {
                        self->ext.merman2.ignoreCol = 1;
                    }
                }
            } else {
                if (func_801C6458(0x1B)) {
                    self->ext.merman2.ignoreCol = 1;
                }
            }
        }
        break;

    case MERMAN2_SPIT_FIRE:
        switch (self->step_s) {
        case MERMAN2_SPIT_FIRE_FACE_PLAYER:
            self->facing = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            return;

        case MERMAN2_SPIT_FIRE_ATTACK:
            if (AnimateEntity(D_8018227C, self) == 0) {
                func_801C2598(0x662);
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                i = 0;
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x34, self, newEntity);
                    newEntity->posY.i.hi -= 12;
                    newEntity->facing = self->facing;
                }
                newEntity2 = &D_8007A958[64];
                for (offset = 0; i < 3; i++, offset += 8) {
                    newEntity = AllocEntity(newEntity2, &newEntity2[32]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(0x36, self, newEntity);
                        if (self->facing != 0) {
                            newEntity->posX.i.hi += 8 + offset;
                        } else {
                            newEntity->posX.i.hi += -8 - offset;
                        }
                        newEntity->posY.i.hi -= 12;
                        newEntity->facing = self->facing;
                        if (i == 0) {
                            newEntity->params = 1;
                        }
                    }
                }
                self->ext.merman2.rotation = 1;
                self->rotAngle = 0;
                self->unk19 |= 4;
                if (self->facing != 0) {
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
            if ((self->ext.merman2.rotation < 0x100) && (g_blinkTimer & 1)) {
                self->ext.merman2.rotation *= 2;
            }
            if (self->velocityX != 0) {
                if (self->facing != 0) {
                    self->velocityX += FIX(0.1875);
                } else {
                    self->velocityX -= FIX(0.1875);
                }
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            if (self->facing != 0) {
                posX -= 20;
            } else {
                posX += 20;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
            }
            self->rotAngle += self->ext.merman2.rotation;
            self->velocityY -= FIX(0.125);

            if (func_801BC8E4(&D_80182248) & 1) {
                if (self->facing == 0) {
                    self->velocityX = FIX(2.5);
                } else {
                    self->velocityX = ~0x27FFF;
                }
                self->ext.merman2.rotation = 4;
                self->posY.i.hi += 10;
                self->step_s++;
            }
            func_801C6458(0x1B);
            if (self->ext.merman2.isUnderwater) {
                self->ext.merman2.ignoreCol = 1;
            }
            break;

        case 3:
            posY = self->posY.i.hi + 8;
            posX = self->posX.i.hi;
            if (self->facing != 0) {
                posX -= 20;
            } else {
                posX += 20;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
            }
            MoveEntity();
            self->rotAngle += 0xC0;
            if (self->rotAngle > 0x1000) {
                self->posY.i.hi -= 10;
                self->unk19 &= 0xFB;
                SetStep(MERMAN2_WALKING_TO_PLAYER);
            }
            if (func_801C6458(0x1B)) {
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
        if (!(func_801C6458(0x1B)) && !(self->ext.merman2.isUnderwater)) {
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
                self->flags |= 0x800000;
                func_801D2684(prim, primIndex);
                prim->tpage = 0x12;
                prim->clut = 0x292;
                if (self->params & 1) {
                    prim->clut = 0x293;
                }
                if (self->facing != 0) {
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
                prim->blendMode = 2;
                *(s16*)&prim->next->r2 = 0x28;
                *(s16*)&prim->next->b2 = 0x30;
                prim->next->b3 = 0x80;
                if (self->facing != 0) {
                    prim->next->x1 = self->posX.i.hi - 3;
                } else {
                    prim->next->x1 = self->posX.i.hi + 3;
                }
                prim->next->y0 = self->posY.i.hi + 2;
            }
            func_801D1F38(prim);
            break;

        case 1:
            func_801BC8E4(&D_80182258);
            prim = self->ext.merman2.prim;
            self->velocityY -= FIX(0.1875);
            if (self->facing != 0) {
                prim->next->x1 = self->posX.i.hi - 3;
            } else {
                prim->next->x1 = self->posX.i.hi + 3;
            }
            prim->next->y0 = self->posY.i.hi + 2;
            func_801D1F38(prim);
            if (!(g_blinkTimer % 10)) {
                prim->clut += 2;
                if (prim->clut >= 0x2A0) {
                    prim->blendMode = BLEND_VISIBLE;
                    self->step_s++;
                } else {
                    newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(0x37, self, newEntity);
                        newEntity->facing = self->facing;
                        newEntity->params = prim->clut;
                        newEntity->zPriority = self->zPriority;
                    }
                }
            }
            func_801C6458(0x1B);
            break;

        case 2:
            func_801C2598(0x65B);
            func_801B653C();
            DestroyEntity(self);
        }
        break;
    }
}

// some sort of explosion: ID 0x36
void EntityExplosion2(Entity* entity, s32 arg1) {
    Primitive* poly;
    s16 primIndex;

    if (entity->step == 0) {
        InitializeEntity(D_80180AB4);
        entity->animCurFrame = 0;
        entity->hitboxState = 0;
        entity->zPriority += 4;
        if (entity->params != 0) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex == -1) {
                DestroyEntity(entity);
                return;
            }
            poly = &g_PrimBuf[primIndex];
            entity->primIndex = primIndex;
            *(s32*)&entity->ext.generic.unk7C.s = poly;
            entity->flags |= FLAG_HAS_PRIMS;
            func_801D2684(poly, primIndex);
            poly->u0 = 0;
            poly->u1 = 0x20;
            poly->tpage = 0x1A;
            poly->clut = 0x1FF;
            poly->v3 = poly->v2 = 0x20;
            poly->v1 = poly->v0 = 0;
            poly->u2 = poly->u0;
            poly->u3 = poly->u1;
            LOH(poly->next->r2) = 0x40;
            LOH(poly->next->b2) = 0x40;
            LOH(poly->next->u1) = 0;
            poly->next->b3 = 0x60;
            poly->next->x1 = entity->posX.i.hi;
            poly->next->y0 = entity->posY.i.hi;
            poly->priority = entity->zPriority - 4;
            poly->blendMode = 6;
        }
    }

    if (entity->params != 0) {
        poly = *(s32*)&entity->ext.generic.unk7C.s;
        func_801D1F38(poly);
        ((POLY_GT4*)poly->next)->b3 += 252;
        LOH(poly->next->u1) -= 128;
        if (poly->next->b3 < 16) {
            poly->blendMode = BLEND_VISIBLE;
        }
    }

    entity->ext.generic.unk84.U8.unk0++;
    if (!(entity->ext.generic.unk84.U8.unk0 % 4)) {
        entity->posY.i.hi++;
    }

    if (AnimateEntity(D_801822B0, entity) == 0) {
        DestroyEntity(entity);
    }
}

void EntityMediumWaterSplash(Entity* entity) {
    Entity* newEntity;

    if (entity->step == 0) {
        InitializeEntity(D_80180AC0);
        entity->animCurFrame = 0;
        if (entity->facing != 0) {
            entity->velocityX = FIX(2);
            return;
        }
        entity->velocityX = FIX(-2);
        return;
    }
    AnimateEntity(D_801822A4, entity);
    MoveEntity();
    if (entity->flags & 0x100) {
        newEntity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
            newEntity->params = 0;
        }
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/44DCC", func_801C7954);

void func_801C7D80(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180AB4);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->flags |= FLAG_UNK_2000;
        self->zPriority += 4;
    }
    MoveEntity();
    self->velocityY += FIX(0.15625);
    if (AnimateEntity(D_801822B8, self) == 0) {
        DestroyEntity(self);
    }
}

// ID 0x35
void func_801C7E18(Entity* self) {
    s8 temp; // probably !FAKE

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
        self->animSet = ANIMSET_DRA(2);
        self->velocityY = FIX(-5);
        self->palette = 0x8162;
        self->blendMode = 0x10;
        self->palette = 0x8018;
        self->blendMode = 0x30;
        self->unk6C = 0xA0;
        self->unk1A = 0x100;
        self->unk1C = 0x1A0;
        self->unk19 |= 3;
        self->ext.generic.unk84.S8.unk1 = 0x11;
        self->ext.generic.unk84.S8.unk0 = self->params;
        self->unk19 |= 8;
        break;

    case 1:
        temp = self->ext.generic.unk84.S8.unk0 - 1;
        self->ext.generic.unk84.S8.unk0--;
        self->ext.generic.unk84.S8.unk1--;
        if (!(temp & 0xFF)) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_801822C0, self);
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->unk1A += 6;
        self->unk1C -= 4;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        if (!--self->ext.generic.unk84.U8.unk1) {
            self->velocityY = 0;
            self->step++;
        }
        break;

    case 3:
        if (AnimateEntity(D_801822C0, self) == 0) {
            MoveEntity();
            self->velocityY += FIX(0.25);
            self->unk1A += 6;
            self->unk1C -= 4;
        }
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityLargeFallingObject(Entity* self) {
    u8 temp_v0;

    if (self->step == 0) {
        InitializeEntity(D_80180AB4);
        self->animCurFrame = 13;
        self->ext.generic.unk84.S8.unk0 = 0x20;
        self->hitboxState = 0;
        self->velocityY = FIX(0.0625);
        self->palette = self->params + 0xE;
        self->unk6C = 0x80;
        self->unk19 |= 8;
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
        InitializeEntity(D_80180A60);
        self->flags |= FLAG_UNK_2000;
    }

    if (!(g_blinkTimer & 0x3F)) {
        Entity* player = &PLAYER;
        temp = g_Camera.posY.i.hi + player->posY.i.hi;
        if (temp >= 256) {
            temp_s0 = g_Camera.posX.i.hi + player->posX.i.hi;
            temp_s0_2 = 128;
            temp_s0_2 = temp_s0 - temp_s0_2 + Random();
            temp_s0 = temp_s0_2 - 64;
            if (temp_s0 <= 0x280) {
                temp2 = 496;
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[170]);
                if (newEntity != 0) {
                    if (Random() & 1) {
                        CreateEntityFromCurrentEntity(0x32, newEntity);
                        newEntity->params = Random() & 1;
                    } else {
                        CreateEntityFromCurrentEntity(0x39, newEntity);
                    }
                    newEntity->posX.i.hi = temp_s0_2 - g_Camera.posX.i.hi;
                    newEntity->posY.i.hi = temp2 - g_Camera.posY.i.hi;
                }
            }
        }
    }
}
