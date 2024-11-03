// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

extern u8 D_us_80182640[];
extern u16 D_us_8018264C[];
extern s16 D_us_8018265C[];
extern s16 D_us_80182668[];

extern s32 D_us_80182618[]; // velocityX
extern s32 D_us_8018262C[]; // velocityY

// Checks for collisions while the entity is moving downward, updating position
// if collision occurs. This is similar to other function CheckFieldCollision
void CheckFieldCollisionY(s16 hitSensors[], s16 sensorCount) {
    Collider collider;
    s32 velocityY;
    s16 currentPosX;
    s16 currentPosY;
    s16 i;

    velocityY = g_CurrentEntity->velocityY;
    if (velocityY >= 0) {
        return;
    }

    currentPosX = g_CurrentEntity->posX.i.hi;
    currentPosY = g_CurrentEntity->posY.i.hi;

    for (i = 0; i < sensorCount; i++) {
        currentPosX += *hitSensors++;
        currentPosY += *hitSensors++;

        g_api.CheckCollision(currentPosX, currentPosY, &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->posY.i.hi += collider.unk20;
            break;
        }
    }
}

void SetFacingLeft(void) {
    g_CurrentEntity->facingLeft = (GetSideToPlayer() & 1) ^ 1;
}

// Flea Man
void EntityFleaMan(Entity* self) {
    u32 distanceX;
    u8 rand;
    u8 index;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
        EntityExplosionSpawn(1, 0);
        return;
    }

    if (self->ext.fleaMan.unk7C) {
        self->ext.fleaMan.unk7C--;
        self->hitboxState = 0;
    } else {
        self->hitboxState = 19;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFleaMan);
        self->animCurFrame = 16;
        if (self->params & 1) {
            self->facingLeft = 1;
            self->velocityX = 0x140;
            self->velocityY = 0xA0;
            self->step = 2;
        } else {
            self->step = 1;
        }

#ifndef VERSION_PSP
        if (self->ext.fleaMan.unk7C) {
            self->step = 3;
        }
#endif
        break;

    case 1:
        AnimateEntity(D_us_80182640, self);
        SetFacingLeft();
        if (GetDistanceToPlayerX() < 0x60 && GetDistanceToPlayerY() < 0x40) {
            self->step = 3;
        }
        break;

    case 2:
        self->zPriority = 0;
        MoveEntity();
        break;

    case 3:
        SetFacingLeft();
        if (self->hitParams && self->hitParams < 4) {
            index = 2;
        } else {
            rand = Random() & 7;
            distanceX = GetDistanceToPlayerX();

            if (distanceX < 0x50) {
                switch (rand) {
                case 0:
                case 1:
                    index = 3;
                    break;
                case 2:
                    index = 2;
                    break;
                case 3:
                    index = 1;
                    break;
                default:
                    index = 0;
                    break;
                }
            } else if (distanceX <= 0x7F) {
                switch (rand) {
                case 0:
                    index = 3;
                    break;
                case 1:
                    index = 2;
                    break;
                case 2:
                    index = 0;
                    break;
                default:
                    if (self->facingLeft ^ PLAYER.facingLeft) {
                        index = 0;
                    } else {
                        index = 1;
                    }
                    break;
                }
            } else {
                index = 4;
            }
        }

        distanceX = D_us_80182618[index];
        if (self->facingLeft) {
            self->velocityX = -distanceX;
        } else {
            self->velocityX = distanceX;
        }

        self->velocityY = D_us_8018262C[index];
        if (index == 1) {
            PlaySfxPositional(SFX_BLIPS_C);
        } else if (index == 0 || index == 2) {
            PlaySfxPositional(SFX_BLIPS_D);
        }

        self->step++;
        break;

    case 4:
        if (self->velocityY > FIX(-0.25) && self->velocityY < FIX(0.25)) {
            index = 19;
        } else if (self->velocityY < 0) {
            index = 20;
        } else {
            index = 18;
        }
        self->animCurFrame = index;
        if (UnkCollisionFunc3(D_us_8018264C) & 1) {
            self->step = 3;
        }
        CheckFieldCollisionY(D_us_8018265C, 3);
        CheckFieldCollision(D_us_80182668, 2);
        break;
    }
}
