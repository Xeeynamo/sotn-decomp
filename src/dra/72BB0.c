
#include "dra.h"
#include "sfx.h"

void func_80112BB0(void) {
    char pad[12];
    s32 temp_v0;
    s32 temp_v1;
    s32 var_s2;

    if (PLAYER.step_s != 0x58) {
        DecelerateX(0x1000);
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
        DecelerateX(0x1000);
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
                CreateEntFactoryFromEntity(g_CurrentEntity, 0x5, 0);
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
        DecelerateX(0x1000);
        if (func_8010E27C() != 0) {
            SetSpeedX(0xC000);
        }
    }
}

void func_801131C4(void) {
    s32 i;
    s32 x_offset;
    u16 local_flags;
    bool condition = false;

    local_flags = 0;
    condition = ((g_Player.pl_vram_flag & 0x20) != condition);

    if ((g_Player.padTapped & PAD_CROSS) && !(g_Player.unk46 & PAD_LEFT)) {
        if (g_Player.padPressed & PAD_DOWN) {
            for (i = 0; i < 4; i++) {
                if ((g_Player.colliders[i].effects & EFFECT_SOLID_FROM_ABOVE)) {
                    g_Player.D_80072F0E = 8;
                    return;
                }
            }
        }
        if (g_Player.unk72 == 0) {
            func_8010E83C(1);
            return;
        }
    }
    if (func_8010FDF8(0x100C) != 0) {
        return;
    }
    DecelerateX(0x2000);
    if (g_Player.unk48 != 0) {
        if (PLAYER.ext.player.unkAC == 0x11) {
            PLAYER.ext.player.unkAC = 0x65;
            PLAYER.animFrameDuration = 2;
            PLAYER.animFrameIdx = 3;
        }
    } else if (PLAYER.ext.player.unkAC == 0x65) {
        func_8010DA48(0x11);
    }
    switch (PLAYER.step_s) {
    case 0x0:
        if (D_800ACF74 != 0) {
            D_800ACF74--;
        } else if (D_80097448[0] >= 0x19) {
            if (g_Player.unk48 == 0) {
                x_offset = 0xC;
                if (PLAYER.facingLeft) {
                    x_offset = -0xC;
                }
                PLAYER.posX.i.hi = x_offset + PLAYER.posX.i.hi;
                PLAYER.posY.i.hi += 2;
                CreateEntFactoryFromEntity(g_CurrentEntity, 0xD0004, 0);
                D_800ACF74 = 0x60;
                PLAYER.posY.i.hi -= 2;
                PLAYER.posX.i.hi -= x_offset;
            }
        }
        local_flags = 6;
        break;
    case 0x1:
        if (!(g_Player.padPressed & PAD_DOWN)) {
            local_flags = 1;
            if ((PLAYER.animFrameIdx >= 4) || PLAYER.ext.player.unkAC == 0x65) {
                func_8010DA48(0x13);
                PLAYER.step_s = 2;
                PLAYER.animFrameIdx = 2;
                if (g_Player.unk72 == 1) {
                    PLAYER.animFrameIdx = 0;
                }
                if (g_Player.unk72 == 2) {
                    PLAYER.animFrameIdx = 1;
                }
                return;
            }
        } else if (PLAYER.ext.player.unkAC == 0x65) {
            PLAYER.step_s = 0;
        } else {
            if (PLAYER.animFrameDuration < 0) {
                local_flags = 0x20;
            }
        }
        break;
    case 0x5:
        func_8010DFF0(1, 1);
        if (g_Player.unk72 == PLAYER.animFrameIdx ||
            PLAYER.animFrameDuration < 0) {
            local_flags = 0x20;
        }
        break;
    case 0x3:
    case 0x4:
        func_8010DFF0(1, 1);
        if (PLAYER.animFrameDuration < 0) {
            local_flags = 0x20;
        }
        break;
    case 0x2:
        local_flags = 1;
        if (g_Player.padPressed & PAD_DOWN) {
            func_8010E470(0, PLAYER.velocityX);
            break;
        }
        if (g_Player.unk72 != 0) {
            func_8010DFF0(1, 1);
            if (g_Player.unk72 == 1) {
                PLAYER.animFrameIdx = 0;
                PLAYER.animFrameDuration = 3;
                break;
            } else if (g_Player.unk72 == 2) {
                if (PLAYER.animFrameIdx != 0) {
                    PLAYER.animFrameIdx = 1;
                    PLAYER.animFrameDuration = 3;
                }
                break;
            } else if (g_Player.unk72 == 3) {
                if (PLAYER.animFrameIdx >= 2) {
                    PLAYER.animFrameIdx = 2;
                    PLAYER.animFrameDuration = 3;
                }
                break;
            } else if (g_Player.unk72 == 4) {
                if (PLAYER.animFrameIdx >= 3) {
                    PLAYER.animFrameIdx = 3;
                    PLAYER.animFrameDuration = 3;
                }
                break;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }

        break;
    case 0x40:
    case 0x59:
        func_8010DFF0(1, 1);
        if (PLAYER.animFrameIdx < g_Player.unk54) {
            if (PLAYER.animFrameIdx < 2) {
                func_8010E27C();
                if (!(g_Player.padPressed & PAD_DOWN)) {
                    if (g_Player.unk72 == 0) {
                        PLAYER.step = 0;
                        PLAYER.ext.player.unkAC = 0x24;
                    }
                }
            }
        } else {
            g_Player.unk46 &= 0x7FFF;
            local_flags = 0xE;
            if (PLAYER.animFrameIdx == 7) {
                if (g_Player.padPressed & g_Player.D_80072EF8) {
                    PLAYER.animFrameDuration = 2;
                    local_flags = 0xE;
                } else {
                    local_flags = 0x2E;
                }
            }
        }
        break;
    case 0x47:
    case 0x49:
        if ((PLAYER.animFrameIdx == 6) &&
            (g_Player.padPressed & g_Player.D_80072EF8)) {
            PLAYER.animFrameDuration = 2;
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x48:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4E:
        case 0x4F:
        case 0x50:
        case 0x53:
        case 0x54:
        case 0x55:
        case 0x56:
        case 0x57:
        case 0x58:
        case 0x5A:
        case 0x5B:
        case 0x5C:
        case 0x5D:
        }
        func_8010DFF0(1, 1);
        if (PLAYER.animFrameIdx < g_Player.unk54) {
            if (PLAYER.animFrameIdx < 3) {
                func_8010E27C();
                if (!(g_Player.padPressed & PAD_DOWN)) {
                    if (g_Player.unk72 == 0) {
                        PLAYER.ext.player.unkAC =
                            D_800B0608[PLAYER.step_s - 0x41] + condition;
                        PLAYER.step = 0;
                    }
                }
            }
        } else {
            g_Player.unk46 &= 0x7FFF;
            local_flags = 0xE;
            if (PLAYER.animFrameDuration < 0) {
                local_flags = 0x2E;
            }
        }
        break;
    case 0x51:
        func_8010DFF0(1, 1);
        if (PLAYER.animFrameDuration < 0) {
            local_flags = 0x2E;
        }
        break;
    }

    if (local_flags & 0x20) {
        func_8010E470(0, 0);
        local_flags |= 0x8000;
    }
    if (local_flags & 2) {
        if (g_Player.unk4C != 0) {
            func_8010DA48(0x14);
            PLAYER.step_s = 0;
            local_flags |= 0x8000;
        }
    }
    if (local_flags & 4) {
        if (!(g_Player.padPressed & PAD_DOWN)) {
            func_8010DA48(0x13);
            PLAYER.step_s = 2;
            local_flags |= 0x8000;
        }
    }
    if (local_flags & 1) {
        if (func_8010E27C()) {
            switch ((u8)g_Player.unk72) {
            case 0:
            case 3:
            case 4:
                func_8010E6AC(0);
                local_flags |= 0x8000;
                break;
            case 1:
            case 2:
                if (g_Player.padTapped & (PAD_RIGHT | PAD_LEFT)) {
                    PLAYER.step_s = 5;
                    func_8010DA48(0xF6);
                    SetSpeedX(FIX(0.75));
                    local_flags |= 0x8000;
                }
                break;
            }
        }
    }
    if ((local_flags & 0x8000) && (local_flags & 8)) {
        func_8010FAF4();
    }
}

void func_801139CC(s32 arg0) {
    s32 move = PLAYER.facingLeft != 0 ? -3 : 3;

    PLAYER.posY.i.hi -= 22;
    PLAYER.posX.i.hi = move + PLAYER.posX.i.hi;
    CreateEntFactoryFromEntity(g_CurrentEntity, 0x10004, 0);
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
const u32 rodataPadding_418DC = 0;
