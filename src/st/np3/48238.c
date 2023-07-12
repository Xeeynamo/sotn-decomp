/*
 * Overlay: NP3
 * Description: Merman Room (2)
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

void EntityMerman(Entity* self) {
    Entity* newEntity;
    Collider collider;
    s16 posX, posY;
    s32 colRet;
    s16* pos;
    s16 camY;
    s32 rnd;

    if (self->ext.merman.isUnderwater) {
        self->palette = self->ext.merman.palette;
    }
    if (self->ext.merman.ignoreCol && (self->step < MERMAN_FALLING)) {
        SetStep(MERMAN_FALLING);
    }

    if ((self->flags & 0x100) && (self->step < MERMAN_DYING)) {
        func_801C2598(0x71D);
        self->hitboxState = 0;
        if (self->step == MERMAN_LUNGE) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 2;
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
        if (!(collider.effects & EFFECT_WATER)) {
            SetStep(MERMAN_SWIMMING);
        }
        return;

    case MERMAN_SWIMMING:
        if (self->step_s == 0) {
            self->hitboxWidth = 5;
            self->hitboxHeight = 17;
            rnd = Random() & 3;
            self->accelerationX = D_80182338[rnd].x;
            self->accelerationY = D_80182338[rnd].y;
            self->step_s++;
        }
        if (AnimateEntity(D_801823D0, self) == 0) {
            self->facing = (GetSideToPlayer() & 1) ^ 1;
        }
        MoveEntity();
        camY = g_Camera.posY.i.hi;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;

        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.effects & EFFECT_WATER)) {
            self->accelerationY = 0x8000;
        }

        pos = D_80181230;
        pos += (self->params >> 8) & 1;
        posY += g_Camera.posY.i.hi;
        if (pos[4] < posY) {
            self->posY.i.hi = pos[4] - g_Camera.posY.i.hi - 24;
        }
        if ((u8)self->ext.merman.timer2++ > 32) {
            self->ext.merman.timer2 = 0;
            self->step_s = 0;
            if ((GetDistanceToPlayerX() >= 48) && !(Random() & 1)) {
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
            pos = D_80181230;
            pos += (self->params >> 8) & 1;
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
            if (!self->ext.merman.isUnderwater) {
                if (func_801BC8E4(&D_8018235C) & 1) {
                    self->animFrameDuration = 0;
                    self->animFrameIdx = 0;
                    self->step_s++;
                }
            } else {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                               FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
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
            self->facing = (GetSideToPlayer() & 1) ^ 1;
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
            if (func_801C6458(0x15)) {
                self->ext.merman.ignoreCol = 1;
            }
        }
        break;

    case MERMAN_SPIT_FIRE:
        switch (self->step_s) {
        case MERMAN_SPIT_FIRE_FACE_PLAYER:
            self->facing = (GetSideToPlayer() & 1) ^ 1;
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
            if (collider.effects & EFFECT_SOLID) {
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
            if (self->ext.merman.isUnderwater) {
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
            if (self->ext.merman.isUnderwater) {
                self->ext.merman.ignoreCol = 1;
            }
        }
        break;

    case MERMAN_FALLING:
        if (self->step_s == 0) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
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
                if (!(GetSideToPlayer() & 1)) {
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
                        newEntity->params = 2;
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
                entity->params = 0;
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
        self->hitboxState = 0;
        self->zPriority += 4;
        self->flags |= FLAG_UNK_2000;
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
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = D_80182454[self->params];
        self->accelerationY = D_80182440[self->params];
        self->step++;
        return;
    } else {
        self->animFrameDuration++;
        self->posY.val += self->accelerationY;
    }

    if (!(self->animFrameDuration & 1)) {
        self->animCurFrame++;
    }

    if (D_80182458[self->params] < self->animFrameDuration) {
        DestroyEntity(self);
    }
}