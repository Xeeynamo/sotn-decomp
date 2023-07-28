#define INCLUDE_ASM_NEW

#include "dra.h"
#include "sfx.h"

void func_80112BB0(void) {
    char pad[12];
    s32 temp_v0;
    s32 temp_v1;
    s32 var_s2;

    if (PLAYER.step_s != 0x58) {
        func_8010E1EC(0x1000);
        if (PLAYER.velocityY < -0x10000) {
            if (!(g_Player.unk44 & 0x40) &&
                !(g_Player.padPressed & PAD_CROSS)) {
                PLAYER.velocityY = -0x10000;
            }
            if (g_Player.pl_vram_flag & 2) {
                PLAYER.velocityY = -0x4000;
                g_Player.unk44 |= 0x20;
            }
        }
        if (func_8010FDF8(0x11029) != 0) {
            return;
        }
    }
    switch (PLAYER.step_s) {
    case 0x0:
        var_s2 = func_8010E27C();
        if (var_s2 != 0) {
            if ((PLAYER.ext.generic.unkAC == 0x16) ||
                (PLAYER.ext.generic.unkAC == 0x19)) {
                func_8010DA48(0x18U);
            }
            SetSpeedX(0x18000);
        } else if ((PLAYER.ext.generic.unkAC == 0x1A) ||
                   (PLAYER.ext.generic.unkAC == 0x18)) {
            func_8010DA48(0x19U);
        }
        if (var_s2 <= 0) {
            g_Player.unk44 &= 0xFFEF;
        }
        if (PLAYER.velocityY > 0) {
            if (PLAYER.ext.generic.unkAC != 0x1B) {
                func_8010DA48(0x1BU);
            }
            PLAYER.step_s = 1;
        }
        break;
    case 0x1:
        var_s2 = func_8010E27C();
        if ((var_s2 == 0) || (SetSpeedX(0x18000), (var_s2 <= 0))) {
            g_Player.unk44 &= 0xFFEF;
        }
        break;
    case 0x58:
        func_8010DFF0(1, 1);
        if (D_80139824 > 0) {
            D_80139824--;
        }
        if ((PLAYER.animFrameIdx == 3) && (PLAYER.animFrameDuration == 1) &&
            (D_80139824 != 0)) {
            PLAYER.animFrameIdx = 1;
        }
        if ((PLAYER.animFrameIdx == 4) ||
            (g_Player.padTapped & (PAD_DOWN | PAD_UP))) {
            PLAYER.step_s = 0x40;
        }
        break;
    case 0x57:
    case 0x5B:
        func_8010DFF0(1, 1);
        func_8010E1EC(0x1000);
        if (PLAYER.ext.generic.unkAC == 0x6C) {
            if (PLAYER.animFrameDuration < 0) {
                temp_v0 = (PLAYER.velocityY > 0x10000) ^ 1;
                PLAYER.step_s = D_800ACF7C[temp_v0].unk0;
                func_8010DA48(D_800ACF7C[temp_v0].unk2);
                func_8010FAF4();
                g_Player.unk44 = 1;
                D_80138FC8 = 0xFE;
                D_80138FCA = 0x10;
            }
        } else if (
            (PLAYER.animFrameIdx == 4) && (PLAYER.animFrameDuration == 1)) {
            PLAYER.animFrameIdx = 5;
            PLAYER.ext.generic.unkAC = 0x6C;
        }
        break;
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
    case 0x50:
    case 0x51:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x5A:
    case 0x5C:
    case 0x5D:
        func_8010DFF0(1, 1);
    case 0x40:
    case 0x59:
        func_8010DFF0(1, 1);
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.velocityX = -0x18000;
        }
        if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.velocityX = 0x18000;
        }
        if (PLAYER.animFrameDuration < 0) {
            temp_v1 = (PLAYER.velocityY > 0x10000) ^ 1;
            PLAYER.step_s = D_800ACF7C[temp_v1].unk0;
            func_8010DA48(D_800ACF7C[temp_v1].unk2);
            func_8010FAF4();
        }
        break;
    case 0x70:
        if (g_Player.unk44 & 0x80) {
            func_8010E83C(1);
            if (!(g_Player.padPressed & PAD_CROSS)) {
                PLAYER.velocityY = -0x44000;
            }
            g_Player.unk44 |= 0x40;
        }
        break;
    }

    if (PLAYER.step_s < 2) {
        if (g_Player.unk44 & 1) {
            if ((g_Player.padPressed & PAD_DOWN) &&
                (g_Player.padTapped & PAD_CROSS)) {
                func_8010DA48(0x22U);
                PLAYER.step_s = 0x70;
                func_8011AAFC(g_CurrentEntity, 5U, 0);
                PLAYER.velocityY = 0x60000;
                g_Player.unk44 &= 0xFF7F;
                if (var_s2 != 0) {
                    SetSpeedX(0x48000);
                }
                PlaySfx(0x6F0);
            }
            if (g_Player.unk44 & 0x100) {
                PLAYER.velocityX = 0;
            }
        }
    } else {
        if (g_Player.unk44 & 0x100) {
            PLAYER.velocityX = 0;
        }
    }
}

const u32 rodataPadding = 0;

void func_80113148(void) {
    if (g_Player.D_80072F0A != 0 && g_Player.padTapped & PAD_CROSS) {
        func_8010E83C(1);
    } else if (func_8010FDF8(0x9029) == 0) {
        func_8010E1EC(0x1000);
        if (func_8010E27C() != 0) {
            SetSpeedX(0xC000);
        }
    }
}

INCLUDE_ASM("dra/nonmatchings/72BB0", func_801131C4);

void func_801139CC(s32 arg0) {
    s32 move = PLAYER.facing != 0 ? -3 : 3;

    PLAYER.posY.i.hi -= 22;
    PLAYER.posX.i.hi = move + PLAYER.posX.i.hi;
    func_8011AAFC(g_CurrentEntity, 0x10004, 0);
    PLAYER.posY.i.hi = PLAYER.posY.i.hi + 22;
    PLAYER.posX.i.hi = PLAYER.posX.i.hi - move;

    if (arg0 & 1) {
        func_80102CD8(3);
        PlaySfx(NA_SE_SECRET_STAIRS);
    }
    if (arg0 & 2) {
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
    }
}