// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A9C2C, func_060A9C2C);

// DrawRicAfterImage
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A9DEC, func_060A9DEC);

void RicSetStep(s16 step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}

void RicSetAnimation(AnimationFrame* anim) {
    g_CurrentEntity->anim = anim;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
}

#include "update_entity_sprite.h"

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AA194, func_060AA194);

void RicDecelerateX(s32 speed) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += speed;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= speed;
        if (g_CurrentEntity->velocityX < 0)
            g_CurrentEntity->velocityX = 0;
    }
}

void RicDecelerateY(s32 speed) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += speed;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= speed;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}

s32 RicCheckFacing(void) {
    if (g_Player.unk44 & 2) {
        return 0;
    }

    if (PLAYER.facingLeft == 1) {
        if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.facingLeft = 0;
            g_Player.unk4C = 1;
            return -1;
        } else if (g_Player.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Player.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.facingLeft = 1;
            g_Player.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

int func_8015CAAC(s32 speed) {
    if (PLAYER.entityRoomIndex == 1)
        speed = -speed;
    PLAYER.velocityX = speed;
    return speed;
}

void RicSetInvincibilityFrames(s32 kind, s16 invincibilityFrames) {
    if (!kind) {
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x15), 0);
        if (g_Player.timers[PL_T_INVINCIBLE_SCENE] <= invincibilityFrames) {
            g_Player.timers[PL_T_INVINCIBLE_SCENE] = invincibilityFrames;
        }
    } else if (g_Player.timers[PL_T_INVINCIBLE] <= invincibilityFrames) {
        g_Player.timers[PL_T_INVINCIBLE] = invincibilityFrames;
    }
}

void DisableAfterImage(s32 resetAnims, s32 arg1) {
    Primitive* prim;
    Entity* entity;
    s32 i;

    if (resetAnims) {
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.resetFlag = 1;
        entity = &g_Entities[E_AFTERIMAGE_1];
        for (i = 0; i < 3; i++, entity++) {
            entity->animCurFrame = 0;
            entity->unk0->flags = 0;
        }
        prim = &g_PrimBuf[g_Entities[E_AFTERIMAGE_1].primIndex];
        while (prim) {
            prim->x1 = 0;
            prim = *(Primitive**)((u8*)prim + 0x20);
        }
    }
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.index = 10;
    if (arg1) {
        g_Player.timers[PL_T_AFTERIMAGE_DISABLE] = 4;
    }
}

void func_8015CC28(void) {
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag =
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.resetFlag =
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.index =
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.timer = 0;
}

void func_060AA4F4(s32 spawnParticles) {
    Entity* source;
    Entity* factory;

    if (spawnParticles == 1) {
        source = &PLAYER;
        factory = RicCreateEntFactoryFromEntity(
            source, FACTORY(BP_CRASH_DAGGER, 0x47), 0);
        if (factory != NULL) {
            factory->flags |= FLAG_UNK_10000;
        }
        factory = RicCreateEntFactoryFromEntity(
            source, FACTORY(BP_CRASH_DAGGER, 0x40), 0);
        if (factory != NULL) {
            factory->flags |= FLAG_UNK_10000;
        }
    }

    DisableAfterImage(1, 1);
}
