// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

// Same function in DRA is func_8010D59C (InitPlayerAfterImage)
static u8 mar_801545B0[] = {
    10, 8, 8, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -1, -1, 0, 0};
void InitMariaAfterImage(void) {
    byte stackpad[40];
    Primitive* prim;
    s32 i;

    if (g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag) {
        return;
    }
    if ((g_Player.padTapped & GAMEBUTTONS) ||
        ((g_Player.padHeld ^ g_Player.padPressed) & g_Player.padHeld &
         GAMEBUTTONS) ||
        (PLAYER.velocityY > FIX(0.5))) {
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.index = 0;
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.timer = 0;
    } else {
        if (g_Entities[E_AFTERIMAGE_1].ext.afterImage.index >= 10) {
            return;
        }
        if (g_Entities[E_AFTERIMAGE_1].ext.afterImage.timer == 0) {
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.timer =
                mar_801545B0[g_Entities[E_AFTERIMAGE_1].ext.afterImage.index];
        }
        if (--g_Entities[E_AFTERIMAGE_1].ext.afterImage.timer == 0) {
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.index++;
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.timer =
                mar_801545B0[g_Entities[E_AFTERIMAGE_1].ext.afterImage.index];
        }
    }
    if (g_Entities[E_AFTERIMAGE_1].pose) {
        g_Entities[E_AFTERIMAGE_1].pose--;
        return;
    }
    for (prim = &g_PrimBuf[g_Entities[E_AFTERIMAGE_1].primIndex], i = 0;
         prim != NULL; i++, prim = prim->next) {
        if (i == g_Entities[E_AFTERIMAGE_1].entityId) {
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            prim->x0 = PLAYER.posX.i.hi;
            prim->y0 = PLAYER.posY.i.hi;
            prim->x1 = PLAYER.animCurFrame;
            prim->y1 = 0;
            prim->x2 = PLAYER.facingLeft;
            prim->y2 = PLAYER.palette;
        }
    }
    g_Entities[E_AFTERIMAGE_1].pose = 2;
    g_Entities[E_AFTERIMAGE_1].entityId++;
    if (g_Entities[E_AFTERIMAGE_1].entityId >= 6) {
        g_Entities[E_AFTERIMAGE_1].entityId = 0;
    }
}

// Extremely similar to func_8010D800 (DrawPlayerAfterImage)
static u8 mar_801545C4[] = {
    4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 16, 16, 16, 16, 16, 16};
static u8 mar_801545D4[] = {
    8, 12, 16, 20, 24, 28, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};
void DrawMariaAfterImage(void) {
    byte pad[0x28];
    Primitive* prim;
    PlayerDraw* draw;
    s32 i;
    u8 var_s3;
    u8 var_s5;
    u8 resetAnim;

    resetAnim = g_Entities[E_AFTERIMAGE_1].ext.afterImage.resetFlag;
    prim = &g_PrimBuf[g_Entities[E_AFTERIMAGE_1].primIndex];
    i = 0;
    draw = &g_PlayerDraw[1];
    var_s5 = mar_801545C4[g_Entities[E_AFTERIMAGE_1].ext.afterImage.index];
    var_s3 = mar_801545D4[g_Entities[E_AFTERIMAGE_1].ext.afterImage.index];
    while (prim != NULL) {
        if (prim->r0 > var_s3) {
            prim->r0 -= var_s5;
        }
        if (prim->r0 < 112 && prim->b0 < 240) {
            prim->b0 += 6;
        }
        if (prim->r0 < 88) {
            prim->y1 = 16;
        } else {
            prim->y1 = 0;
        }
        if (prim->r0 <= var_s3) {
            prim->x1 = 0;
        }
        if ((i ^ g_Timer) & 1) {
            g_Entities[i / 2 + E_AFTERIMAGE_1].posX.i.hi = prim->x0;
            g_Entities[i / 2 + E_AFTERIMAGE_1].posY.i.hi = prim->y0;
            g_Entities[i / 2 + E_AFTERIMAGE_1].animCurFrame = prim->x1;
            g_Entities[i / 2 + E_AFTERIMAGE_1].drawMode = prim->y1;
            g_Entities[i / 2 + E_AFTERIMAGE_1].facingLeft = prim->x2;
            g_Entities[i / 2 + E_AFTERIMAGE_1].palette = prim->y2;
            g_Entities[i / 2 + E_AFTERIMAGE_1].zPriority = PLAYER.zPriority - 2;
            if (resetAnim) {
                g_Entities[i / 2 + E_AFTERIMAGE_1].animCurFrame = 0;
                prim->x1 = 0;
            }

            draw->r0 = draw->r1 = draw->r2 = draw->r3 = draw->g0 = draw->g1 =
                draw->g2 = draw->g3 = prim->r0;
            draw->b0 = draw->b1 = draw->b2 = draw->b3 = prim->b0;
            draw->enableColorBlend = true;
            draw++;
        }
        i++;
        prim = prim->next;
    }
}

void MarSetStep(s16 step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}

void MarSetAnimation(AnimationFrame* anim) {
    g_CurrentEntity->anim = anim;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
}

void MarDecelerateX(s32 speed) {
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

static void DecelerateY(s32 speed) {
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

s32 MarCheckFacing(void) {
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

void MarSetSpeedX(s32 speed) {
    if (g_CurrentEntity->facingLeft == 1)
        speed = -speed;
    g_CurrentEntity->velocityX = speed;
}

// different the RIC counterpart
int func_maria_8015CAAC(s32 speed) {
    if (PLAYER.entityRoomIndex == 1)
        speed = -speed;
    PLAYER.velocityX = speed;
    return 0;
}

void MarSetInvincibilityFrames(s32 kind, s16 invincibilityFrames) {
    if (!kind) {
        if (g_Player.timers[PL_T_INVINCIBLE_SCENE] <= invincibilityFrames) {
            g_Player.timers[PL_T_INVINCIBLE_SCENE] = invincibilityFrames;
        }
    } else if (g_Player.timers[PL_T_INVINCIBLE] <= invincibilityFrames) {
        g_Player.timers[PL_T_INVINCIBLE] = invincibilityFrames;
    }
}

void MarDisableAfterImage(s32 resetAnims, s32 arg1) {
    Primitive* prim;

#if defined(VERSION_US)
    FntPrint("op disable\n");
#endif
    if (resetAnims) {
        g_Entities[E_AFTERIMAGE_1].ext.disableAfterImage.unk7D = 1;
        g_Entities[E_AFTERIMAGE_1].animCurFrame =
            g_Entities[E_AFTERIMAGE_2].animCurFrame =
                g_Entities[E_AFTERIMAGE_3].animCurFrame = 0;
        prim = &g_PrimBuf[g_Entities[E_AFTERIMAGE_1].primIndex];
        while (prim) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }
    g_Entities[E_AFTERIMAGE_1].ext.disableAfterImage.unk7C = 1;
    g_Entities[E_AFTERIMAGE_1].ext.disableAfterImage.unk7E = 0xA;
    if (arg1) {
        g_Player.timers[PL_T_AFTERIMAGE_DISABLE] = 4;
    }
}

void func_maria_8015CC28(void) {
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag =
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.resetFlag =
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.index =
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.timer = 0;
}
