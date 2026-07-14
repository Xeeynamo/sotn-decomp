// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

// Same function in DRA is func_8010D59C (InitPlayerAfterImage)
static u8 mar_801545B0[] = {
    10, 8, 8, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -1, -1, 0, 0};
void InitMariaAfterImage(void) {
    Primitive* prim;
    s32 i;

    if (MARIA_AFTERIMAGE_1.ext.afterImage.disableFlag) {
        return;
    }
    if (g_Maria.padTapped & GAMEBUTTONS ||
        (g_Maria.padHeld & (g_Maria.padHeld ^ g_Maria.padPressed) &
         GAMEBUTTONS) ||
        MARIA.velocityY > FIX(0.5)) {
        MARIA_AFTERIMAGE_1.ext.afterImage.index = 0;
        MARIA_AFTERIMAGE_1.ext.afterImage.timer = 0;
    } else if (MARIA_AFTERIMAGE_1.ext.afterImage.index >= MaxAfterImageIndex) {
        return;
    } else {
        if (MARIA_AFTERIMAGE_1.ext.afterImage.timer == 0) {
            MARIA_AFTERIMAGE_1.ext.afterImage.timer =
                mar_801545B0[MARIA_AFTERIMAGE_1.ext.afterImage.index];
        }

        if (--MARIA_AFTERIMAGE_1.ext.afterImage.timer == 0) {
            MARIA_AFTERIMAGE_1.ext.afterImage.index++;
            MARIA_AFTERIMAGE_1.ext.afterImage.timer =
                mar_801545B0[MARIA_AFTERIMAGE_1.ext.afterImage.index];
        }
    }

    if (MARIA_AFTERIMAGE_1.pose) {
        MARIA_AFTERIMAGE_1.pose--;
        return;
    }

    for (prim = &g_PrimBuf[MARIA_AFTERIMAGE_1.primIndex], i = 0; prim != NULL;
         i++, prim = prim->next) {
        if (i == MARIA_AFTERIMAGE_1.entityId) {
            PGREY(prim, 0) = 0x80;
            prim->x0 = MARIA.posX.i.hi;
            prim->y0 = MARIA.posY.i.hi;
            prim->x1 = MARIA.animCurFrame;
            prim->y1 = 0;
            prim->x2 = MARIA.facingLeft;
            prim->y2 = MARIA.palette;
        }
    }

    MARIA_AFTERIMAGE_1.pose = 2;
    MARIA_AFTERIMAGE_1.entityId++;
    if (MARIA_AFTERIMAGE_1.entityId >= MaxAfterImages) {
        MARIA_AFTERIMAGE_1.entityId = 0;
    }
}

// Extremely similar to func_8010D800 (DrawPlayerAfterImage)
static u8 mar_801545C4[] = {
    4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 16, 16, 16, 16, 16, 16};
static u8 mar_801545D4[] = {
    8, 12, 16, 20, 24, 28, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};
void DrawMariaAfterImage(void) {
    PlayerDraw* draw;
    Primitive* prim;
    s32 i;
    u8 var_s5;
    u8 resetAnim;
    u8 var_s3;

    resetAnim = MARIA_AFTERIMAGE_1.ext.afterImage.resetFlag;
    prim = &g_PrimBuf[MARIA_AFTERIMAGE_1.primIndex];
    i = 0;
    draw = &g_PlayerDraw[6];
    var_s5 = mar_801545C4[MARIA_AFTERIMAGE_1.ext.afterImage.index];
    var_s3 = mar_801545D4[MARIA_AFTERIMAGE_1.ext.afterImage.index];

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
            g_Entities[(i / 2) + 65].posX.i.hi = prim->x0;
            g_Entities[(i / 2) + 65].posY.i.hi = prim->y0;
            g_Entities[(i / 2) + 65].animCurFrame = prim->x1;
            g_Entities[(i / 2) + 65].blendMode = prim->y1;
            g_Entities[(i / 2) + 65].facingLeft = prim->x2;
            g_Entities[(i / 2) + 65].palette = prim->y2;
            g_Entities[(i / 2) + 65].zPriority = MARIA.zPriority - 2;
            if (resetAnim) {
                g_Entities[(i / 2) + 65].animCurFrame = 0;
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
    MARIA.step = step;
    MARIA.step_s = 0;
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
        if (g_CurrentEntity->velocityX < 0) {
            g_CurrentEntity->velocityX = 0;
        }
    }
}

// nb. no DecelerateY

s32 MarCheckFacing(void) {
    if (g_Maria.unk44 & 2) {
        return 0;
    }

    if (MARIA.facingLeft == 1) {
        if (g_Maria.padPressed & PAD_RIGHT) {
            MARIA.facingLeft = 0;
            g_Maria.unk4C = 1;
            return -1;
        } else if (g_Maria.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Maria.padPressed & PAD_RIGHT) {
            return 1;
        }

        if (g_Maria.padPressed & PAD_LEFT) {
            MARIA.facingLeft = 1;
            g_Maria.unk4C = 1;
            return -1;
        }
    }

    return 0;
}

void MarSetSpeedX(s32 speed) {
    if (g_CurrentEntity->facingLeft == 1) {
        speed = -speed;
    }
    g_CurrentEntity->velocityX = speed;
}

// different the RIC counterpart
s32 func_maria_8015CAAC(s32 speed) {
    if (MARIA.entityRoomIndex == 1) {
        speed = -speed;
    }
    MARIA.velocityX = speed;
    return 0;
}

void MarSetInvincibilityFrames(s32 kind, s16 invincibilityFrames) {
    if (!kind) {
        if (g_Maria.timers[PL_T_INVINCIBLE_SCENE] <= invincibilityFrames) {
            g_Maria.timers[PL_T_INVINCIBLE_SCENE] = invincibilityFrames;
        }
    } else if (g_Maria.timers[PL_T_INVINCIBLE] <= invincibilityFrames) {
        g_Maria.timers[PL_T_INVINCIBLE] = invincibilityFrames;
    }
}

void MarDisableAfterImage(s32 resetAnims, s32 arg1) {
    Primitive* prim;

    if (resetAnims) {
        MARIA_AFTERIMAGE_1.ext.disableAfterImage.resetFlag = 1;
        MARIA_AFTERIMAGE_1.animCurFrame = MARIA_AFTERIMAGE_2.animCurFrame =
            MARIA_AFTERIMAGE_3.animCurFrame = 0;
        prim = &g_PrimBuf[MARIA_AFTERIMAGE_1.primIndex];

        while (prim != NULL) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }
    MARIA_AFTERIMAGE_1.ext.disableAfterImage.disableFlag = 1;
    MARIA_AFTERIMAGE_1.ext.disableAfterImage.index = MaxAfterImageIndex;
    if (arg1) {
        g_Maria.timers[PL_T_AFTERIMAGE_DISABLE] = 4;
    }
}

void func_maria_8015CC28(void) {
    MARIA_AFTERIMAGE_1.ext.afterImage.disableFlag =
        MARIA_AFTERIMAGE_1.ext.afterImage.resetFlag =
            MARIA_AFTERIMAGE_1.ext.afterImage.index =
                MARIA_AFTERIMAGE_1.ext.afterImage.timer = 0;
}
