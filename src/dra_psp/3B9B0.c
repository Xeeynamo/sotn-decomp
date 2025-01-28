// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void GetPlayerSensor(Collider* col) {
    void (*theFunc)(Collider* col);
    u32 mod = 0;
    if (g_PlayableCharacter == PLAYER_ALUCARD) {
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            mod += 2;
        }
        col->unk14 = g_SensorsWall[0].x - mod;
        col->unk1C = g_SensorsWall[0].y + mod;
        col->unk18 = g_SensorsFloor[1].y - 1;
        col->unk20 = g_SensorsCeiling[1].y + 1;
    } else {
        theFunc = g_PlOvl.GetPlayerSensor;
        theFunc(col);
    }
}

void func_8010BFFC(void) {
    s16 x;
    s16 y;
    s32 i;
    bool collided = false;
    s16 original_Y = PLAYER.posY.i.hi;

    if ((g_Player.pl_vram_flag & 1) || D_801396EA) {
        return;
    }
    if (g_Player.status & PLAYER_STATUS_TRANSFORM)
        return;
    if (g_Player.unk78 == 1) {
        return;
    }

    if (PLAYER.posY.i.hi < 48) {
        PLAYER.posY.i.hi -= 16;
        while (true) {
            for (i = 0; i < 4; i++) {
                x = PLAYER.posX.i.hi + g_SensorsFloor[i].x;
                y = PLAYER.posY.i.hi + g_SensorsFloor[i].y;
                CheckCollision(x, y, &g_Player.colFloor[i], 0);
            }
            if ((g_Player.colFloor[1].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colFloor[2].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colFloor[3].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID) {
                PLAYER.velocityY = 0;
                PLAYER.posY.i.hi--;
                collided = true;
                continue;
            }
            if (collided) {
                return;
            }
            PLAYER.posY.i.hi += 8;
            if (PLAYER.posY.i.hi >= 48) {
                PLAYER.posY.i.hi = original_Y;
                return;
            }
        }
    } else if (PLAYER.posY.i.hi > 176) {
        PLAYER.posY.i.hi += 32;
        while (true) {
            for (i = 0; i < 4; i++) {
                x = PLAYER.posX.i.hi + g_SensorsCeiling[i].x;
                y = PLAYER.posY.i.hi + g_SensorsCeiling[i].y;
                CheckCollision(x, y, &g_Player.colFloor[i] + 4, 0);
            }
            if ((g_Player.colCeiling[1].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colCeiling[2].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colCeiling[3].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID) {
                PLAYER.velocityY = 0;
                PLAYER.posY.i.hi++;
                collided = true;
                continue;
            }
            if (collided) {
                PLAYER.posY.i.hi--;
                return;
            }
            PLAYER.posY.i.hi -= 8;
            if (PLAYER.posY.i.hi <= 176) {
                PLAYER.posY.i.hi = original_Y;
                return;
            }
        }
    }
}

// CheckFloor
INCLUDE_ASM("dra_psp/psp/dra_psp/3B9B0", func_psp_091187D8);
// CheckCeiling
INCLUDE_ASM("dra_psp/psp/dra_psp/3B9B0", func_psp_091190E0);
// CheckWallRight
INCLUDE_ASM("dra_psp/psp/dra_psp/3B9B0", func_psp_09119950);
// CheckWallLeft
INCLUDE_ASM("dra_psp/psp/dra_psp/3B9B0", func_psp_09119D00);
