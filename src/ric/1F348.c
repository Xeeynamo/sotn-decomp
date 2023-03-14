#include "ric.h"

void func_8015B348(void) {
    switch (PLAYER.unk2E) {
    case 0:
        g_CurrentEntity->flags |= FLAG_UNK_10000;
        D_80097420[0] = 4;
        func_8015C93C(0x2000);

        if (PLAYER.accelerationX == 0) {
            func_8015C920(&D_80155748);
            *D_80072F1A = 4;
            func_801606BC(g_CurrentEntity, 0x1D, 0);
            func_801606BC(g_CurrentEntity, 0x90021, 0);
            D_801545AC = 0;
            PLAYER.unk2E++;
        }
        break;

    case 1:
        PLAYER.unk19 = 2;
        D_801545AA += 64;
        PLAYER.unk1C = (rsin(D_801545AA) >> 0xA) + 256;

        if (D_801545AC != 0) {
            D_801545AC--;
            if ((D_801545AC) == 0) {
                PLAYER.unk19 = 0;
                PLAYER.unk1C = 0x100;
                func_801606BC(g_CurrentEntity, 0x17, 0);
                D_801545A8 = 0x90;
                PLAYER.unk2E++;
            }
        }
        break;

    case 2:
        D_801545A8--;
        if ((D_801545A8) == 0) {
            func_8015C920(&D_801558B4);
            PLAYER.palette = 0x814E;
            g_CurrentEntity->accelerationY = -0x10000;
            func_801606BC(g_CurrentEntity, 0x16, 0);
            D_801545A8 = 0x30;
            g_api.PlaySfx(0x6E2);
            D_80174F78 = 0xA0;
            PLAYER.unk2E++;
        }
        break;

    case 3:
        D_801545A8--;
        if ((D_801545A8) == 0) {
            PLAYER.accelerationY = 0;
            D_801545A8 = 0xC0;
            func_801606BC(g_CurrentEntity, 0x24, 0);
            func_801606BC(g_CurrentEntity, 0x20025, 0);
            func_801606BC(g_CurrentEntity, 0x30026, 0);
            func_801606BC(g_CurrentEntity, 0x40027, 0);
            PLAYER.palette = 0x813D;
            *D_80072F1A = 0;
            PLAYER.unk2E++;
        }

        if (D_80097BA0.hp < D_80097BA0.hpMax) {
            D_80097BA0.hp++;
        }

        D_80174F78--;
        if ((D_80174F78 >= 0) && (D_80174F78 == (((D_80174F78) / 20) * 0x14))) {
            g_api.PlaySfx(NA_SE_PL_RIC_UNK_6E2);
        }
        break;

    case 4:
        D_801545A8--;
        if ((D_801545A8 << 0x10) == 0) {
            D_801545A8 = 0x10;
            PLAYER.unk2E++;
        }

        if (D_80097BA0.hp < D_80097BA0.hpMax) {
            D_80097BA0.hp++;
        }

        D_80174F78--;
        if ((D_80174F78 >= 0) && (D_80174F78 == (((D_80174F78) / 20) * 0x14))) {
            g_api.PlaySfx(NA_SE_PL_RIC_UNK_6E2);
        }
        break;

    case 5:
        if (D_801545A8 == 5) {
            PLAYER.animFrameIdx = 6;
            PLAYER.palette = 0x8120;
            func_801606BC(g_CurrentEntity, 0x1C, 0);
        }
        D_801545A8--;
        if (D_801545A8 == 0) {
            func_8015C920(&D_801558D4);
            g_api.PlaySfx(NA_SE_UNK_62F);
            func_801606BC(g_CurrentEntity, 0x1B, 0);
            PLAYER.unk2E++;
            break;
        }

        if (D_80097BA0.hp < D_80097BA0.hpMax) {
            D_80097BA0.hp++;
        }
        break;

    case 6:
        if (PLAYER.animFrameDuration < 0) {
            func_8015C920(&D_801558DC);
            PLAYER.unk2E++;
        }
        break;

    case 7:
        if (PLAYER.animFrameDuration < 0) {
            g_CurrentEntity->flags &= ~FLAG_UNK_10000;
            D_80097420[0] = 0;
            func_8015CF08();
            func_8015C920(&D_801558DC);
            *D_80072F1A = 4;
            func_801606BC(g_CurrentEntity, 0x90021, 0);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/1F348", func_8015B898);

// same as DRA/func_80115C50
void func_8015BB80(void) {
    s32 dist;

    if (g_StageId == STAGE_TOP) {
        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8000 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8000 < 0) {
            PLAYER.posX.i.hi++;
        }
    }

    if (g_StageId == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {
        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8384 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8384 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}
