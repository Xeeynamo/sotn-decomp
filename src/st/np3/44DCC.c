/*
 * Overlay: NP3
 * Description: Merman Room
 */

#include "np3.h"

typedef enum {
    MERMAN_INIT,
    MERMAN_SWIMMING_UP,
    MERMAN_SWIMMING = 3,
    MERMAN_JUMPING,
    MERMAN_WALKING_TOWARDS_PLAYER,
    MERMAN_SPIT_FIRE,
    MERMAN_LUNGE,
    MERMAN_FALLING,
    MERMAN_DYING,
} MermanSteps;

typedef enum {
    MERMAN_JUMPING_SETUP,
    MERMAN_JUMPING_UNDERWATER,
    MERMAN_JUMPING_IN_AIR,
    MERMAN_JUMPING_LANDING,
} MermanJumpingSubSteps;

typedef enum {
    MERMAN_WALKING_TOWARDS_START,
    MERMAN_WALKING_TOWARDS_PLAYER_WALKING,
} MermanWalkingTowardsPlayerSubSteps;

typedef enum {
    MERMAN_SPIT_FIRE_FACE_PLAYER,
    MERMAN_SPIT_FIRE_ATTACK,
} MermanSpitFireSubSteps;

typedef enum {
    MERMAN_LUNGE_START,
    MERMAN_LUNGE_SETUP,
    MERMAN_LUNGE_TOWARDS_PLAYER,
    MERMAN_LUNGE_STANDING,
} MermanLungeSubSteps;

typedef enum {
    MERMAN_DYING_SETUP,
    MERMAN_DYING_KNOCKEDBACK,
    MERMAN_DYING_END,
} MermanDyingSubSteps;

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

s32 func_801C6458(s16 yVector) {
    s16 newY = yVector + g_CurrentEntity->posY.i.hi;
    s32 expectedResult = 0;
    Collider collider;
    Entity* newEntity;
    s32 res;

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi, newY, &collider, 0);

    if (expectedResult == (collider.unk0 & 1)) {
        res = true;
    } else {
        res = false;
    }

    if (collider.unk0 & 8) {
        if (*(u8*)&g_CurrentEntity->ext.generic.unkA0 == 0) {
            newEntity = AllocEntity(&D_8007DE38, &D_8007DE38[24]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x33, g_CurrentEntity, newEntity);
                newEntity->posY.i.hi += yVector;
                newEntity->zPriority = g_CurrentEntity->zPriority;
            }
            g_api.PlaySfx(0x7C2);
            *(u8*)&g_CurrentEntity->ext.generic.unkA0 = 1;
        }
    }
    return res;
}

// Matching, assembler skips a NOP
// https://decomp.me/scratch/8wa56
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/np3/nonmatchings/44DCC", EntityMerman2);
#else
void EntityMerman2(Entity* self) {
    s32 firstPrimIndex;
    Collider collider;
    Entity* newEntity;
    Entity* newEntity2;
    Primitive* prim;
    s16 posX, posY;
    s32 colRes;
    s32 offset;
    s32 index;
    u32 accel;
    s16* pos;
    s16 camY;
    s32 rnd;
    s32 res;
    s32 i;

    if (self->ext.merman2.ignoreCol && (self->step < MERMAN2_7)) {
        SetStep(MERMAN2_7);
    }

    if ((self->flags & 0x100) && (self->step < MERMAN2_DYING)) {
        func_801C2598(0x71D);
        self->unk19 = 0;
        if (self->flags & FLAG_FREE_POLYGONS) {
            g_api.FreePrimitives(self->firstPolygonIndex);
            self->flags &= ~FLAG_FREE_POLYGONS;
        }
        self->unk3C = 0;
        self->flags &= ~FLAG_UNK_20000000;
        SetStep(MERMAN2_DYING);
    }

    switch (self->step) {
    case MERMAN2_INIT:
        InitializeEntity(D_80180AB4);
        self->unk12 = 8;
        self->zPriority = 0xA9;
        if (self->subId != 0) {
            self->palette++;
        }
        self->accelerationY = -0x10000;
        break;

    case MERMAN2_SWIMMING_UP:
        AnimateEntity(D_8018229C, self);
        MoveEntity();
        posY = self->posY.i.hi - 24;
        g_api.CheckCollision(self->posX.i.hi, posY, &collider, 0);
        if (!(collider.unk0 & 8)) {
            SetStep(MERMAN2_SWIMMING);
            break;
        }

    case MERMAN2_SWIMMING:
        if (self->step_s == 0) {
            rnd = (Random() & 3) * 2;
            self->accelerationX = D_80182224[rnd];
            self->accelerationY = D_80182228[rnd];
            self->step_s++;
        }
        if (AnimateEntity(D_8018229C, self) == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
        }
        MoveEntity();
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.unk0 & 8)) {
            self->accelerationY = 0x8000;
        }
        index = (self->subId >> 8) & 1;
        pos = &D_80181230;
        pos += index;
        posY += g_Camera.posY.i.hi;
        if (pos[4] < posY) {
            self->posY.i.hi = pos[4] - g_Camera.posY.i.hi - 24;
        }

        if ((u8)self->ext.merman2.timer++ > 32) {
            self->ext.merman2.timer = 0;
            self->step_s = 0;
            if ((GetPlayerDistanceX() >= 48) && !(Random() & 1)) {
                SetStep(MERMAN2_JUMPING);
            }
        }
        break;

    case MERMAN2_JUMPING:
        switch (self->step_s) {
        case MERMAN2_JUMPING_SETUP:
            self->accelerationX = 0;
            self->accelerationY = -0x88000;
            self->step_s++;
            firstPrimIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (firstPrimIndex != -1) {
                u32 v0;
                prim = &g_PrimBuf[firstPrimIndex];
                self->animCurFrame = 0;
                self->firstPolygonIndex = firstPrimIndex;
                self->ext.merman2.prim = prim;
                self->flags |= FLAG_FREE_POLYGONS;
                prim->tpage = 0x12;
                prim->clut = 0x28C;
                if (self->subId & 1) {
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
            index = (self->subId >> 8) & 1;
            pos = &D_80181230;
            pos += index;
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
                self->unk1E = 0;
                self->unk19 |= 4;
                self->step_s++;
            }
            break;

        case MERMAN2_JUMPING_IN_AIR:
            prim = self->ext.merman2.prim;
            if (self->accelerationY > ~0xBFFF) {
                prim->blendMode = 8;
                self->animCurFrame = 18;
                self->hitboxHeight = 8;
                self->unk1E -= 0x80;
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

                accel =
                    (u32)(((ABS(self->accelerationY) >> 0xC) - 10) & 0xFF) >> 1;

                setRGB0(prim, 128 - accel, 128 - accel, accel + 192);

                *(s32*)&prim->r1 = *(s32*)&prim->r0;
                *(s32*)&prim->r2 = *(s32*)&prim->r0;
                *(s32*)&prim->r3 = *(s32*)&prim->r0;
            }
            if (self->accelerationY < 0) {
                newEntity = AllocEntity(D_8007DE38, &D_8007DE38[24]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x38, self, newEntity);
                    newEntity->posX.i.hi -= 6 - ((Random() & 3) * 4);
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
            if (self->accelerationY > 0) {
                func_801C6458(0x1B);
            }
            if (self->ext.merman2.isUnderwater == 0) {
                if (func_801BC8E4(&D_80182248) & 1) {
                    g_api.FreePrimitives(self->firstPolygonIndex);
                    self->hitboxHeight = 21;
                    self->flags &= ~FLAG_FREE_POLYGONS;
                    self->unk19 &= 0xFB;
                    SetStep(MERMAN2_WALKING_TO_PLAYER);
                    return;
                }
            } else {
                self->flags |= 0xC0000000;
                MoveEntity();
                self->accelerationY += 0x4000;
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
            self->facing = (GetPlayerSide() & 1) ^ 1;
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
                self->accelerationX = -0x6000;
            } else {
                self->accelerationX = 0x6000;
            }

            if (colRes & 0x80) {
                self->posX.val += self->accelerationX;
            }

            if (!(self->subId & 1) ||
                (self->accelerationX *= 2, !(self->subId & 1))) {
                if (!(self->posX.i.hi & 0xFF00)) {
                    self->ext.merman2.timer--;
                    if ((self->ext.merman2.timer & 0xFF) == 0) {
                        if (Random() % 2) {
                            SetStep(MERMAN2_SPIT_FIRE);
                        } else {
                            self->step_s--;
                        }
                    }
                    res = func_801C6458(0x1B);
                    if (res != 0) {
                        self->ext.merman2.ignoreCol = 1;
                    }
                }
            } else {
                res = func_801C6458(0x1B);
                if (res != 0) {
                    self->ext.merman2.ignoreCol = 1;
                }
            }
        }
        break;

    case MERMAN2_SPIT_FIRE:
        switch (self->step_s) {
        case MERMAN2_SPIT_FIRE_FACE_PLAYER:
            self->facing = (GetPlayerSide() & 1) ^ 1;
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
                            newEntity->subId = 1;
                        }
                    }
                }
                self->ext.merman2.rotation = 1;
                self->unk1E = 0;
                self->unk19 |= 4;
                if (self->facing != 0) {
                    self->accelerationX = -0x60000;
                } else {
                    self->accelerationX = 0x60000;
                }
                self->accelerationY = -0x1000;
                self->posY.i.hi -= 1;
                self->step_s++;
            }
            break;

        case 2:
            if ((self->ext.merman2.rotation < 0x100) && (g_blinkTimer & 1)) {
                self->ext.merman2.rotation *= 2;
            }
            if (self->accelerationX != 0) {
                if (self->facing != 0) {
                    self->accelerationX += 0x3000;
                } else {
                    self->accelerationX -= 0x3000;
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
            if (collider.unk0 & 1) {
                self->accelerationX = 0;
            }
            self->unk1E += self->ext.merman2.rotation;
            self->accelerationY -= 0x2000;

            if (func_801BC8E4(&D_80182248) & 1) {
                if (self->facing == 0) {
                    self->accelerationX = 0x28000;
                } else {
                    self->accelerationX = ~0x27FFF;
                }
                self->ext.merman2.rotation = 4;
                self->posY.i.hi += 10;
                self->step_s++;
            }
            func_801C6458(0x1B);
            res = self->ext.merman2.isUnderwater;
            if (res != 0) {
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
            if (collider.unk0 & 1) {
                self->accelerationX = 0;
            }
            MoveEntity();
            self->unk1E += 0xC0;
            if (self->unk1E > 0x1000) {
                self->posY.i.hi -= 10;
                self->unk19 &= 0xFB;
                SetStep(MERMAN2_WALKING_TO_PLAYER);
            }
            res = func_801C6458(0x1B);
            if (res != 0) {
                self->ext.merman2.ignoreCol = 1;
            }
        }
        break;

    case MERMAN2_7:
        if (self->step_s == 0) {
            self->flags |= 0xC0000000;
            self->step_s++;
        }
        MoveEntity();
        self->accelerationY += 0x4000;
        if (!(func_801C6458(0x1B)) && !(self->ext.merman2.isUnderwater)) {
            self->ext.merman2.ignoreCol = 0;
            SetStep(MERMAN2_WALKING_TO_PLAYER);
        }
        break;

    case MERMAN2_DYING:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 14;
            self->flags |= 0xC0000000;
            if (!(GetPlayerSide() & 1)) {
                self->accelerationX = -0x20000;
            } else {
                self->accelerationX = 0x20000;
            }
            self->accelerationY = -0x10000;
            self->step_s++;
            firstPrimIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (firstPrimIndex != -1) {
                u32 v0;
                prim = &g_PrimBuf[firstPrimIndex];
                self->firstPolygonIndex = firstPrimIndex;
                self->ext.merman2.prim = prim;
                self->flags |= 0x800000;
                func_801D2684(prim, firstPrimIndex);
                prim->tpage = 0x12;
                prim->clut = 0x292;
                if (self->subId & 1) {
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
            self->accelerationY -= 0x3000;
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
                    prim->blendMode = 8;
                    self->step_s++;
                } else {
                    newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(0x37, self, newEntity);
                        newEntity->facing = self->facing;
                        newEntity->subId = prim->clut;
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
#endif

// some sort of explosion: ID 0x36
void EntityExplosion2(Entity* entity, s32 arg1) {
    Primitive* poly;
    s16 firstPolygonIndex;

    if (entity->step == 0) {
        InitializeEntity(D_80180AB4);
        entity->animCurFrame = 0;
        entity->unk3C = 0;
        entity->zPriority += 4;
        if (entity->subId != 0) {
            firstPolygonIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (firstPolygonIndex == -1) {
                DestroyEntity(entity);
                return;
            }
            poly = &g_PrimBuf[firstPolygonIndex];
            entity->firstPolygonIndex = firstPolygonIndex;
            *(s32*)&entity->ext.generic.unk7C.s = poly;
            entity->flags |= FLAG_FREE_POLYGONS;
            func_801D2684(poly, firstPolygonIndex);
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

    if (entity->subId != 0) {
        poly = *(s32*)&entity->ext.generic.unk7C.s;
        func_801D1F38(poly);
        ((POLY_GT4*)poly->next)->b3 += 252;
        LOH(poly->next->u1) -= 128;
        if (poly->next->b3 < 16) {
            poly->blendMode = 8;
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
            entity->accelerationX = 0x20000;
            return;
        }
        entity->accelerationX = -0x20000;
        return;
    }
    AnimateEntity(D_801822A4, entity);
    MoveEntity();
    if (entity->flags & 0x100) {
        newEntity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
            newEntity->subId = 0;
        }
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/44DCC", func_801C7954);

void func_801C7D80(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180AB4);
        self->animCurFrame = 0;
        self->unk3C = 0;
        self->flags |= 0x2000;
        self->zPriority += 4;
    }
    MoveEntity();
    self->accelerationY += 0x2800;
    if (AnimateEntity(D_801822B8, self) == 0) {
        DestroyEntity(self);
    }
}

// ID 0x35
void func_801C7E18(Entity* self) {
    s8 temp; // probably !FAKE

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A54);
        self->animSet = 2;
        self->accelerationY = -0x50000;
        self->palette = 0x8162;
        self->blendMode = 0x10;
        self->palette = 0x8018;
        self->blendMode = 0x30;
        self->unk6C = 0xA0;
        self->unk1A = 0x100;
        self->unk1C = 0x1A0;
        self->unk19 |= 3;
        self->ext.generic.unk84.S8.unk1 = 0x11;
        self->ext.generic.unk84.S8.unk0 = self->subId;
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
        self->accelerationY += 0x4000;
        self->unk1A += 6;
        self->unk1C -= 4;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        if (!--self->ext.generic.unk84.U8.unk1) {
            self->accelerationY = 0;
            self->step++;
        }
        break;

    case 3:
        if (AnimateEntity(D_801822C0, self) == 0) {
            MoveEntity();
            self->accelerationY += 0x4000;
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
        self->unk3C = 0;
        self->accelerationY = 0x1000;
        self->palette = self->subId + 0xE;
        self->unk6C = 0x80;
        self->unk19 |= 8;
        self->flags |= 0x2000;
        return;
    }
    MoveEntity();
    temp_v0 = self->ext.generic.unk84.U8.unk0 - 1;
    self->ext.generic.unk84.U8.unk0--;
    self->accelerationY += 0x1000;
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
        self->flags |= 0x2000;
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
                        newEntity->subId = Random() & 1;
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

// Matching, assembler skips a NOP
// https://decomp.me/scratch/pjVr0
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/np3/nonmatchings/44DCC", EntityMerman);
#else
void EntityMerman(Entity* self) {
    Entity* newEntity;
    Collider collider;
    s16 posX, posY;
    s32 colRet;
    s16* pos;
    s16 camY;
    s32 rnd;
    s32 res;
    s32 index;

    if (self->ext.merman.isUnderwater) {
        self->palette = self->ext.merman.palette;
    }
    if (self->ext.merman.ignoreCol && (self->step < MERMAN_FALLING)) {
        SetStep(MERMAN_FALLING);
    }

    if ((self->flags & 0x100) && (self->step < MERMAN_DYING)) {
        func_801C2598(0x71D);
        self->unk3C = 0;
        if (self->step == MERMAN_LUNGE) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->subId = 2;
            }
            DestroyEntity(self);
            return;
        }
        SetStep(MERMAN_DYING);
    }

    switch (self->step) {
    case MERMAN_INIT:
        InitializeEntity(D_80180ACC);
        self->ext.merman.palette = 0x2B9;
        self->zPriority = 0xA9;
        self->accelerationY = -0x10000;
        self->hitboxWidth = 5;
        self->hitboxHeight = 17;
        self->palette = self->ext.merman.palette;
        break;

    case MERMAN_SWIMMING_UP:
        if (self->step_s == 0) {
            self->hitboxWidth = 18;
            self->hitboxHeight = 4;
            self->step_s++;
        }
        AnimateEntity(D_801823D0, self);
        MoveEntity();

        posX = self->posX.i.hi;
        posY = self->posY.i.hi - 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.unk0 & 8)) {
            SetStep(MERMAN_SWIMMING);
            break;
        }

    case MERMAN_SWIMMING:
        if (self->step_s == 0) {
            self->hitboxWidth = 5;
            self->hitboxHeight = 17;
            rnd = (Random() & 3) * 2;
            self->accelerationX = D_80182338[rnd];
            self->accelerationY = D_8018233C[rnd];
            self->step_s++;
        }
        if (AnimateEntity(D_801823D0, self) == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
        }
        MoveEntity();
        camY = g_Camera.posY.i.hi;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;

        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.unk0 & 8)) {
            self->accelerationY = 0x8000;
        }

        index = (self->subId >> 8) & 1;
        pos = &D_80181230;
        pos += index;
        posY += g_Camera.posY.i.hi;
        if (pos[4] < posY) {
            self->posY.i.hi = pos[4] - g_Camera.posY.i.hi - 24;
        }
        if ((u8)self->ext.merman.timer2++ > 32) {
            self->ext.merman.timer2 = 0;
            self->step_s = 0;
            if ((GetPlayerDistanceX() >= 48) && !(Random() & 1)) {
                SetStep(MERMAN_JUMPING);
            }
        }
        break;

    case MERMAN_JUMPING:
        switch (self->step_s) {
        case MERMAN_JUMPING_SETUP:
            self->accelerationX = 0;
            self->accelerationY = -0x88000;
            self->step_s++;
            break;

        case MERMAN_JUMPING_UNDERWATER:
            MoveEntity();
            index = (self->subId >> 8) & 1;
            pos = &D_80181230;
            pos += index;
            camY = g_Camera.posY.i.hi;
            posY = self->posY.i.hi;
            posY -= 20;
            posY += camY;
            if (posY < pos[3]) {
                g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
                newEntity = AllocEntity(D_8007DE38, &D_8007DE38[24]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x33, self, newEntity);
                    newEntity->posY.i.hi -= 20;
                    newEntity->zPriority = self->zPriority;
                }
                self->step_s++;
            }
            break;

        case MERMAN_JUMPING_IN_AIR:
            AnimateEntity(D_801823BC, self);
            if (self->ext.merman.isUnderwater == 0) {
                if (func_801BC8E4(&D_8018235C) & 1) {
                    self->animFrameDuration = 0;
                    self->animFrameIdx = 0;
                    self->step_s++;
                }
            } else {
                self->flags |= 0xC0000000;
                MoveEntity();
                self->accelerationY += 0x4000;
            }

            self->ext.merman.timer++;
            if (self->accelerationY < 0) {
                if ((self->ext.merman.palette >= 0x2B3) &&
                    !(self->ext.merman.timer % 4)) {
                    self->ext.merman.palette--;
                }
                self->palette = self->ext.merman.palette;
                newEntity = AllocEntity(D_8007DE38, &D_8007DE38[24]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x3B, self, newEntity);
                    newEntity->posX.i.hi -= 6 - ((Random() & 3) * 4);
                    newEntity->accelerationX = D_80182418[self->animFrameIdx];
                }
            } else {
                self->palette = 0x2B2;
                if (self->accelerationY > 0) {
                    func_801C6458(0x15);
                }
            }
            break;

        case MERMAN_JUMPING_LANDING:
            if (AnimateEntity(D_801823DC, self) != 0) {
                break;
            }
            SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
        }
        break;

    case MERMAN_WALKING_TOWARDS_PLAYER:
        switch (self->step_s) {
        case MERMAN_WALKING_TOWARDS_START:
            self->facing = (GetPlayerSide() & 1) ^ 1;
            if (self->facing == 0) {
                self->accelerationX = -0x6000;
            } else {
                self->accelerationX = 0x6000;
            }
            self->ext.merman.timer2 = D_80182358[Random() & 3];
            self->step_s++;
            break;

        case MERMAN_WALKING_TOWARDS_PLAYER_WALKING:
            AnimateEntity(D_80182394, self);
            colRet = func_801BCB5C(&D_8018238C);
            if (colRet == 0xFF) {
                self->facing ^= 1;
            }
            if (self->facing == 0) {
                self->accelerationX = -0x6000;
            } else {
                self->accelerationX = 0x6000;
            }
            if (colRet & 0x80) {
                self->posX.val += self->accelerationX;
            }
            self->ext.merman.timer2--;
            if (!(self->ext.merman.timer2 & 0xFF)) {
                if (Random() % 2) {
                    SetStep(MERMAN_SPIT_FIRE);
                } else {
                    SetStep(MERMAN_LUNGE);
                }
            }
            res = func_801C6458(0x15);
            if (res != 0) {
                self->ext.merman.ignoreCol = 1;
            }
        }
        break;

    case MERMAN_SPIT_FIRE:
        switch (self->step_s) {
        case MERMAN_SPIT_FIRE_FACE_PLAYER:
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->step_s++;
            break;

        case MERMAN_SPIT_FIRE_ATTACK:
            if (AnimateEntity(D_801823AC, self) == 0) {
                SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
            }
            if (*(s32*)&self->animFrameIdx == 4) {
                func_801C2598(0x662);
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x3A, self, newEntity);
                    if (self->facing != 0) {
                        newEntity->posX.i.hi += 12;
                    } else {
                        newEntity->posX.i.hi -= 12;
                    }
                    newEntity->posY.i.hi -= 10;
                    newEntity->facing = self->facing;
                }
            }
        }
        break;

    case MERMAN_LUNGE:
        switch (self->step_s) {
        case MERMAN_LUNGE_START:
            if (AnimateEntity(D_801823DC, self) == 0) {
                self->step_s++;
            }
            break;

        case MERMAN_LUNGE_SETUP:
            if (self->facing == 0) {
                self->accelerationX = ~0x27FFF;
            } else {
                self->accelerationX = 0x28000;
            }

            self->accelerationY = -0x20000;
            self->ext.merman.timer2 = 64;
            self->animCurFrame = 12;
            self->hitboxWidth = 18;
            self->hitboxHeight = 4;
            self->step_s++;
            break;

        case MERMAN_LUNGE_TOWARDS_PLAYER:
            posY = self->posY.i.hi + 8;
            posX = self->posX.i.hi;
            if (self->facing != 0) {
                posX += 24;
            } else {
                posX -= 24;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.unk0 & 1) {
                self->accelerationX = 0;
            }
            func_801C0B20(&D_8018236C);
            if (self->facing != 0) {
                self->accelerationX -= 0x800;
            } else {
                self->accelerationX += 0x800;
            }
            self->ext.merman.timer2--;
            if ((self->ext.merman.timer2 & 0xFF) == 0) {
                self->accelerationX = 0;
                self->accelerationY = 0x20000;
                self->posY.i.hi -= 9;
                func_801BC8E4(&D_8018235C);
                self->animFrameIdx = 2;
                self->hitboxWidth = 5;
                self->animFrameDuration = 0;
                self->hitboxHeight = 17;
                self->step_s++;
            }
            func_801C6458(11);
            res = self->ext.merman.isUnderwater;
            if (res != 0) {
                self->ext.merman.ignoreCol = 1;
            }
            break;

        case MERMAN_LUNGE_STANDING:
            func_801BC8E4(&D_8018235C);
            if (AnimateEntity(D_801823DC, self) == 0) {
                self->accelerationY = 0;
                SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
            }
            func_801C6458(11);
            res = self->ext.merman.isUnderwater;
            if (res != 0) {
                self->ext.merman.ignoreCol = 1;
            }
        }
        break;

    case MERMAN_FALLING:
        if (self->step_s == 0) {
            self->flags |= 0xC0000000;
            self->step_s++;
        }
        MoveEntity();
        self->accelerationY += 0x4000;
        if (!(func_801C6458(21)) && !(self->ext.merman.isUnderwater)) {
            self->ext.merman.ignoreCol = 0;
            SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
        }
        break;

    case MERMAN_DYING:
        switch (self->step_s) {
        case MERMAN_DYING_SETUP:
            self->ext.merman.palette = 0x2BC;
            self->accelerationY = 0;
            self->step_s++;

        case MERMAN_DYING_KNOCKEDBACK:
            if (func_801BC8E4(&D_8018237C) & 1) {
                if (!(GetPlayerSide() & 1)) {
                    self->accelerationX = -0x8000;
                } else {
                    self->accelerationX = 0x8000;
                }
                self->step_s++;
            }

        case MERMAN_DYING_END:
            AnimateEntity(D_801823EC, self); // spinning
            MoveEntity();
            self->palette = self->ext.merman.palette;
            if (!(g_blinkTimer % 8)) {
                self->ext.merman.palette++;
                if (self->ext.merman.palette == 0x2C0) {
                    func_801C2598(0x65B);
                    newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(0x3C, self, newEntity);
                        newEntity->subId = 2;
                    }
                }
            }
            if (self->ext.merman.palette >= 0x2C5) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}
#endif

void func_801C8DF0(Entity* self) {
    Entity* entity;

    if (self->step == 0) {
        InitializeEntity(D_80180AD8);
        self->hitboxWidth = 6;
        self->animCurFrame = 0;
        self->hitboxHeight = 3;

        if (self->facing != 0) {
            self->accelerationX = 0x18000;
        } else {
            self->accelerationX = ~0x17FFF;
        }

        self->unk19 = 3;
        self->unk1C = self->unk1A = 0x80;

        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_UNK_15, self, entity);
            entity->ext.generic.unk94 = 4;
            entity->unk19 = 3;
            entity->zPriority = self->zPriority + 8;
            entity->unk1C = entity->unk1A = 192;
        }
    } else {
        AnimateEntity(D_80182400, self);
        MoveEntity();

        if (self->unk1A < 0x100) {
            self->unk1C = self->unk1A += 8;
        }

        if (self->flags & 0x100) {
            entity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->subId = 0;
            }
            DestroyEntity(self);
        }
    }
}

// some kind of falling object
void func_801C8F54(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180ACC);
        self->animCurFrame = 0;
        self->unk3C = 0;
        self->zPriority += 4;
        self->flags |= 0x2000;
    }
    MoveEntity();
    self->accelerationY += 0x2800;
    if (AnimateEntity(D_80182414, self) == 0) {
        DestroyEntity(self);
    }
}

void EntityMermanExplosion(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180A54);
        self->palette = 0x82BB;
        self->animSet = 2;
        self->animCurFrame = D_80182454[self->subId];
        self->accelerationY = D_80182440[self->subId];
        self->step++;
        return;
    } else {
        self->animFrameDuration++;
        self->posY.val += self->accelerationY;
    }

    if (!(self->animFrameDuration & 1)) {
        self->animCurFrame++;
    }

    if (D_80182458[self->subId] < self->animFrameDuration) {
        DestroyEntity(self);
    }
}