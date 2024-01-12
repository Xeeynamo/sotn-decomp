#include "ric.h"

// Runs when Richter's step is 22. This happens when he dies in prologue
// and gets saved by Maria.
void func_8015B348(void) {
    switch (PLAYER.step_s) {
    case 0:
        g_CurrentEntity->flags |= FLAG_UNK_10000;
        D_80097420[0] = 4;
        func_8015C93C(0x2000);

        if (PLAYER.velocityX == 0) {
            func_8015C920(&D_80155748);
            g_Player.D_80072F00[13] = 4;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 29), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x900, 33), 0);
            D_801545AC = 0;
            PLAYER.step_s++;
        }
        break;

    case 1:
        PLAYER.drawFlags = FLAG_DRAW_ROTY;
        D_801545AA += 64;
        PLAYER.rotY = (rsin(D_801545AA) >> 0xA) + 256;

        if (D_801545AC != 0) {
            D_801545AC--;
            if ((D_801545AC) == 0) {
                PLAYER.drawFlags = 0;
                PLAYER.rotY = 0x100;
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 23), 0);
                D_801545A8 = 0x90;
                PLAYER.step_s++;
            }
        }
        break;

    case 2:
        // In this step, Richter rises into the air, similar to when he uses the
        // Cross subweapon crash.
        D_801545A8--;
        if ((D_801545A8) == 0) {
            func_8015C920(&D_801558B4);
            PLAYER.palette = 0x814E;
            g_CurrentEntity->velocityY = FIX(-1);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 22), 0);
            D_801545A8 = 0x30;
            g_api.PlaySfx(0x6E2);
            D_80174F78 = 0xA0;
            PLAYER.step_s++;
        }
        break;

    case 3:
        D_801545A8--;
        if ((D_801545A8) == 0) {
            PLAYER.velocityY = 0;
            D_801545A8 = 0xC0;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 36), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x200, 37), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x300, 38), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x400, 39), 0);
            PLAYER.palette = 0x813D;
            g_Player.D_80072F00[13] = 0;
            PLAYER.step_s++;
        }

        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }

        D_80174F78--;
        if ((D_80174F78 >= 0) && (D_80174F78 % 20 == 0)) {
            g_api.PlaySfx(NA_SE_PL_RIC_UNK_6E2);
        }
        break;

    case 4:
        D_801545A8--;
        if ((D_801545A8 << 0x10) == 0) {
            D_801545A8 = 0x10;
            PLAYER.step_s++;
        }

        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }

        D_80174F78--;
        if ((D_80174F78 >= 0) && (D_80174F78 % 20 == 0)) {
            g_api.PlaySfx(NA_SE_PL_RIC_UNK_6E2);
        }
        break;

    case 5:
        if (D_801545A8 == 5) {
            PLAYER.animFrameIdx = 6;
            PLAYER.palette = 0x8120;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 28), 0);
        }
        D_801545A8--;
        if (D_801545A8 == 0) {
            func_8015C920(&D_801558D4);
            g_api.PlaySfx(NA_SE_UNK_62F);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 27), 0);
            PLAYER.step_s++;
            break;
        }

        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }
        break;

    case 6:
        if (PLAYER.animFrameDuration < 0) {
            func_8015C920(&D_801558DC);
            PLAYER.step_s++;
        }
        break;

    case 7:
        if (PLAYER.animFrameDuration < 0) {
            g_CurrentEntity->flags &= ~FLAG_UNK_10000;
            D_80097420[0] = 0;
            func_8015CF08();
            func_8015C920(&D_801558DC);
            g_Player.D_80072F00[13] = 4;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x900, 33), 0);
        }
        break;
    }
}

void func_8015B898(void) {
    s32 condition = 0;

    if (!PLAYER.facingLeft) {
        condition = (g_Player.pl_vram_flag & 4) != condition;
    } else if (g_Player.pl_vram_flag & 8) {
        condition = 1;
    }
    if ((PLAYER.posX.i.hi > (u8)-5) && (!PLAYER.facingLeft)) {
        condition = 1;
    }
    if (PLAYER.posX.i.hi < 5 && (PLAYER.facingLeft)) {
        condition = 1;
    }
    if ((!PLAYER.facingLeft &&
         (g_Player.colliders[2].effects & EFFECT_UNK_8000)) ||
        (PLAYER.facingLeft &&
         (g_Player.colliders[3].effects & EFFECT_UNK_8000))) {
        condition = 1;
    }
    if (condition && (PLAYER.animFrameIdx < 6)) {
        PLAYER.animFrameIdx = 6;
        if (PLAYER.velocityX > FIX(1)) {
            PLAYER.velocityX = FIX(2);
        }
        if (PLAYER.velocityX < FIX(-1)) {
            PLAYER.velocityX = FIX(-2);
        }
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
    }
    if (PLAYER.animFrameIdx < 5) {
        if (func_8015DBB0(0x44)) {
            return;
        }
        if ((g_Player.unk72 == 0) && (g_Player.padTapped & PAD_CROSS)) {
            PLAYER.posY.i.hi -= 4;
            func_8015DA60();
            return;
        }
    } else if (PLAYER.animFrameIdx < 7) {
        if (func_8015DBB0(0x40044)) {
            return;
        }
    } else if (func_8015DBB0(0x4004C)) {
        return;
    }

    func_8015C93C(0x2000);
    if (PLAYER.step_s == 0) {
        if (!(g_GameTimer & 3) && (2 < PLAYER.animFrameIdx) &&
            (PLAYER.animFrameIdx < 6)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x200, 24), 0);
        }
        if (PLAYER.animFrameIdx == 6 && PLAYER.animFrameDuration == 1) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8015CCC8(0, PLAYER.velocityX);
        }
    }
}

// same as DRA/func_80115C50
void func_8015BB80(void) {
    s32 dist;

    if (g_StageId == STAGE_TOP) {
        dist = g_Tilemap.left * 256 + playerX;
        dist = ABS(dist);

        if (dist - 8000 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = g_Tilemap.left * 256 + playerX;
        dist = ABS(dist);

        if (dist - 8000 < 0) {
            PLAYER.posX.i.hi++;
        }
    }

    if (g_StageId == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {
        dist = g_Tilemap.left * 256 + playerX;
        dist = ABS(dist);

        if (dist - 8384 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = g_Tilemap.left * 256 + playerX;
        dist = ABS(dist);

        if (dist - 8384 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}
