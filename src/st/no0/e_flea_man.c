// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

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

INCLUDE_ASM("st/no0/nonmatchings/e_flea_man", func_us_801DC788);
