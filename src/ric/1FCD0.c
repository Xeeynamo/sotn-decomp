#include "ric.h"

void func_8015BCD0(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    D_80072EF4 = 0;
    D_80072EFC = 4;
    switch (PLAYER.unk2E) {
    case 0:
        if ((*(s32*)&PLAYER.animFrameIdx == 0x10005) &&
            (func_801606BC(g_CurrentEntity, 0x4D, 0) == NULL)) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8015CD98(0);
        }
        break;

    case 2:
        func_8015BB80();
        if ((*(s32*)&PLAYER.animFrameIdx == 0x10005) &&
            (func_801606BC(g_CurrentEntity, 0x2004D, 0) == NULL)) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8015CD98(0);
        }
        break;

    case 4:
        func_8015BB80();
        if ((*(s32*)&PLAYER.animFrameIdx == 0x10005) &&
            (func_801606BC(g_CurrentEntity, 0x4004D, 0) == NULL)) {
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
        if (D_80072F3C != 0) {
            func_8015CD98(0);
        }
    }
}

void func_8015BE84(void) {
    if ((D_80072EE8 & 0x80) && (D_80072F64 & 0x80)) {
        PLAYER.step = 4;
        func_8015C920(&D_8015555C);
        func_8015CA84(-0x18000);
        PLAYER.accelerationY = 0;
        if (D_80072F92 == 0) {
            PLAYER.accelerationY = -0x48000;
        }
        PLAYER.unk2E = 2;
        D_80072F64 = (D_80072F64 | 0xA) & 0xFFFB;
        return;
    }
    func_8015C93C(0x1000);
    PLAYER.accelerationY += 0x1000;

    if (D_80072F20.pl_vram_flag & 1) {
        g_CurrentEntity->accelerationX /= 2;
        func_801606BC(g_CurrentEntity, 0, 0);
        PLAYER.facing = (PLAYER.facing + 1) & 1;
        func_8015CCC8(3, PLAYER.accelerationX);
        g_api.PlaySfx(0x64B);
        return;
    } else if (D_80072F20.pl_vram_flag & 0xC) {
        PLAYER.accelerationX = 0;
    }

    if (PLAYER.accelerationX < 0) {
        if (D_80072EE8 & 0x2000) {
            func_8015C93C(0x2000);
        }
        if ((PLAYER.accelerationX > (s32)0xFFFD0000) || (D_80072F20.pl_vram_flag & 8)) {
            PLAYER.accelerationX /= 2;
            PLAYER.facing = (PLAYER.facing + 1) & 1;
            func_8015C920(&D_80155788);
            D_80072F64 = 0xA;
            PLAYER.unk2E = 2;
            PLAYER.step = 4;
        }
    }
    if (PLAYER.accelerationX > 0) {
        if (D_80072EE8 & 0x8000) {
            func_8015C93C(0x2000);
        }
        if ((PLAYER.accelerationX <= 0x2FFFF) || (D_80072F20.pl_vram_flag & 4)) {
            PLAYER.accelerationX /= 2;
            PLAYER.facing = (PLAYER.facing + 1) & 1;
            func_8015C920(&D_80155788);
            D_80072F64 = 0xA;
            PLAYER.unk2E = 2;
            PLAYER.step = 4;
        }
    }
}

void func_8015C178(void) {
    func_8015C93C(0x1C00);

    if (D_8007342A < 0) {
        D_80072F66 = 0;
        func_8015CD98(0);
    } else if ((*(u16*)&PLAYER.animFrameIdx >= 0x12) && !(D_80072F20.pl_vram_flag & 1)) {
        D_80072F66 = 0;
        func_8015CF08();
    } else {
        if (!(D_8003C8C4 & 3) && (*(u16*)&PLAYER.animFrameIdx < 0x12) &&
            (D_80072F20.pl_vram_flag & 1)) {
            func_801606BC(g_CurrentEntity, 0x20018, 0);
        }

        if ((*(s32*)&PLAYER.animFrameIdx == 0x10012) && (D_80072F20.pl_vram_flag & 1)) {
            func_801606BC(g_CurrentEntity, 0, 0);
        }
    }
}

