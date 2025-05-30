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

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityMerman2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityMermanFireSpit);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/working_on", EntityMediumWaterSplash);

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
