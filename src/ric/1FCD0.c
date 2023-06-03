#include "ric.h"

void func_8015BCD0(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    g_Player.D_80072EF4 = 0;
    g_Player.D_80072EFC = 4;
    switch (PLAYER.step_s) {
    case 0:
        if (LOW(PLAYER.animFrameIdx) == 0x10005 &&
            func_801606BC(g_CurrentEntity, 0x4D, 0) == NULL) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8015CD98(0);
        }
        break;

    case 2:
        func_8015BB80();
        if (LOW(PLAYER.animFrameIdx) == 0x10005 &&
            func_801606BC(g_CurrentEntity, 0x2004D, 0) == NULL) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8015CD98(0);
        }
        break;

    case 4:
        func_8015BB80();
        if (LOW(PLAYER.animFrameIdx) == 0x10005 &&
            func_801606BC(g_CurrentEntity, 0x4004D, 0) == NULL) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8015CD98(0);
        }
        break;

    case 1:
    case 3:
    case 5:
        if (PLAYER.animFrameDuration < 0) {
            func_8015CD98(0);
        }
        if (g_Player.unk1C != 0) {
            func_8015CD98(0);
        }
    }
}

void func_8015BE84(void) {
    if (g_Player.padPressed & PAD_SQUARE && g_Player.unk44 & 0x80) {
        PLAYER.step = 4;
        func_8015C920(&D_8015555C);
        func_8015CA84(-0x18000);
        PLAYER.accelerationY = 0;
        if (g_Player.unk72 == 0) {
            PLAYER.accelerationY = -0x48000;
        }
        PLAYER.step_s = 2;
        g_Player.unk44 = (g_Player.unk44 | 0xA) & 0xFFFB;
        return;
    }
    func_8015C93C(0x1000);
    PLAYER.accelerationY += 0x1000;

    if (g_Player.pl_vram_flag & 1) {
        g_CurrentEntity->accelerationX /= 2;
        func_801606BC(g_CurrentEntity, 0, 0);
        PLAYER.facing = (PLAYER.facing + 1) & 1;
        func_8015CCC8(3, PLAYER.accelerationX);
        g_api.PlaySfx(0x64B);
        return;
    }

    if (g_Player.pl_vram_flag & 0xC) {
        PLAYER.accelerationX = 0;
    }

    if (PLAYER.accelerationX < 0) {
        if (g_Player.padPressed & PAD_RIGHT) {
            func_8015C93C(0x2000);
        }
        if ((PLAYER.accelerationX > (s32)0xFFFD0000) ||
            (g_Player.pl_vram_flag & 8)) {
            PLAYER.accelerationX /= 2;
            PLAYER.facing = (PLAYER.facing + 1) & 1;
            func_8015C920(&D_80155788);
            g_Player.unk44 = 0xA;
            PLAYER.step_s = 2;
            PLAYER.step = 4;
        }
    }

    if (PLAYER.accelerationX > 0) {
        if (g_Player.padPressed & PAD_LEFT) {
            func_8015C93C(0x2000);
        }
        if ((PLAYER.accelerationX <= 0x2FFFF) || (g_Player.pl_vram_flag & 4)) {
            PLAYER.accelerationX /= 2;
            PLAYER.facing = (PLAYER.facing + 1) & 1;
            func_8015C920(&D_80155788);
            g_Player.unk44 = 0xA;
            PLAYER.step_s = 2;
            PLAYER.step = 4;
        }
    }
}

void func_8015C178(void) {
    func_8015C93C(0x1C00);

    if (PLAYER.animFrameDuration < 0) {
        g_Player.unk46 = 0;
        func_8015CD98(0);
    } else if (PLAYER.animFrameIdx >= 0x12 && !(g_Player.pl_vram_flag & 1)) {
        g_Player.unk46 = 0;
        func_8015CF08();
    } else {
        if (!(D_8003C8C4 & 3) && PLAYER.animFrameIdx < 0x12 &&
            g_Player.pl_vram_flag & 1) {
            func_801606BC(g_CurrentEntity, 0x20018, 0);
        }

        if ((LOW(PLAYER.animFrameIdx) == 0x10012) &&
            (g_Player.pl_vram_flag & 1)) {
            func_801606BC(g_CurrentEntity, 0, 0);
        }
    }
}
