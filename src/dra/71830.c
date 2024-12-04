// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "objects.h"

// BSS
#if defined(VERSION_US)
extern s32 D_80137FDC;
#endif

void func_80111928(void) { D_801396EA = 0; }

void func_80111938(void) {
    D_801396EA = 1;
    D_801396E4 = PLAYER.animCurFrame;
    D_801396E6 = PLAYER.drawFlags;
    D_801396E8 = PLAYER.palette;
}

void func_8011197C(void) {
    D_801396EA = 0;
    PLAYER.hitParams = 0;
    PLAYER.animCurFrame = D_801396E4;
    PLAYER.drawFlags = D_801396E6;
    PLAYER.palette = D_801396E8;
}

bool func_801119C4(void) {
    if (D_801396EA == 0) {
        if (g_Player.padTapped & PAD_L2) {
            if (g_Player.D_80072EFC == 0) {
                func_80111938();
                return true;
            }
        }

        return false;
    }
    if ((g_Player.D_80072EFC != 0) || (g_Player.padTapped & PAD_L2)) {
        func_8011197C();
        return false;
    }
    if (g_Player.padPressed & PAD_CROSS) {
        if (g_Player.padPressed & PAD_RIGHT) {
            g_Entities->posX.val += FIX(16.0f);
        }
        if (g_Player.padPressed & PAD_LEFT) {
            g_Entities->posX.val -= FIX(16.0f);
        }
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0f);
        }
        if (g_Player.padPressed & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0f);
        }

    } else {
        if (g_Player.padTapped & PAD_RIGHT) {
            g_Entities->posX.val += FIX(16.0f);
        }
        if (g_Player.padTapped & PAD_LEFT) {
            g_Entities->posX.val -= FIX(16.0f);
        }
        if (g_Player.padTapped & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0f);
        }
        if (g_Player.padTapped & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0f);
        }
    }
#ifdef VERSION_US
    if (g_Player.padTapped & PAD_TRIANGLE) {
        if (!(D_80137FDC & 1)) {
            PLAYER.palette = 0x8100;
        } else {
            PLAYER.palette = 0x810D;
        }
        D_80137FDC++;
    }
#endif
    if (g_Player.padTapped & PAD_CIRCLE) {
        PLAYER.animCurFrame--;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        PLAYER.animCurFrame++;
    }
    if (PLAYER.animCurFrame <= 0) {
        PLAYER.animCurFrame = 1;
    }
    if (!(PLAYER.animCurFrame < 0xE1)) {
        PLAYER.animCurFrame = 0xE0;
    }
    FntPrint("charal:%02x\n", PLAYER.animCurFrame);
    return true;
}

void func_80111CC0(void) {
    if (g_Player.timers[1]) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x17), 0);
    }
    if (g_Player.timers[0]) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x16), 0);
    }
}

bool func_80111D24(void) {
    Collider collider;
    s32 speed = 0xC000;
    s16 posX = PLAYER.posX.i.hi;
    s16 posY = PLAYER.posY.i.hi;
    s32 hitboxLeftMargin;
    s32 hitboxRightMargin;

    CheckCollision(posX - 7, posY, &collider, 0);
    hitboxLeftMargin = collider.effects & EFFECT_MIST_ONLY;
    CheckCollision(posX + 7, posY, &collider, 0);
    hitboxRightMargin = collider.effects & EFFECT_MIST_ONLY;

    if (hitboxRightMargin & hitboxLeftMargin) {
        SetSpeedX(speed);
        return true;
    } else if (hitboxRightMargin != 0) {
        PLAYER.velocityX = -speed;
        return true;
    } else if (hitboxLeftMargin != 0) {
        PLAYER.velocityX = speed;
        return true;
    }
    return false;
}

bool func_80111DE8(bool mistReset) {
    Collider collider1;
    Collider collider2;
    s32 yOffset;
    s32 filtered_effects;
    s32 colliderXOffset;
    s32 playerX;

    yOffset = g_SensorsFloor[1].y - 1;

    CheckCollision(
        PLAYER.posX.i.hi + 9, PLAYER.posY.i.hi + yOffset - 1, &collider1, 0);
    if (mistReset && (collider1.effects & EFFECT_MIST_ONLY)) {
        collider1.effects = EFFECT_NONE;
    }
    filtered_effects =
        collider1.effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                             EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if (filtered_effects == EFFECT_UNK_8000 + EFFECT_UNK_4000 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                EFFECT_UNK_0002 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_4000 + EFFECT_UNK_0800 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_4000 + EFFECT_UNK_0800 +
                                EFFECT_UNK_0002 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_8000 + EFFECT_UNK_0002 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_0800 + EFFECT_UNK_0002 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_0002 + EFFECT_SOLID) {
        // silly arrangement needed to make registers match
        playerX = PLAYER.posX.i.hi;
        colliderXOffset = collider1.unk4;
        CheckCollision(colliderXOffset + playerX + 8,
                       PLAYER.posY.i.hi + yOffset - 1, &collider2, 0);
        if (mistReset && (collider2.effects & EFFECT_MIST_ONLY)) {
            collider1.effects = EFFECT_NONE;
        }
        if (!(collider2.effects & EFFECT_SOLID)) {
            PLAYER.posX.i.hi += collider1.unk4;
            return 1;
        }
    }

    CheckCollision(
        PLAYER.posX.i.hi - 9, PLAYER.posY.i.hi + yOffset - 1, &collider1, 0);
    if (mistReset && (collider1.effects & EFFECT_MIST_ONLY)) {
        collider1.effects = EFFECT_NONE;
    }
    filtered_effects =
        collider1.effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                             EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if (filtered_effects == EFFECT_UNK_8000 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_8000 + EFFECT_UNK_0002 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_0800 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_0800 + EFFECT_UNK_0002 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                EFFECT_UNK_0002 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_4000 + EFFECT_UNK_0800 +
                                EFFECT_UNK_0002 + EFFECT_SOLID ||
        filtered_effects == EFFECT_UNK_0002 + EFFECT_SOLID) {
        // silly arrangement needed to make registers match
        playerX = PLAYER.posX.i.hi;
        colliderXOffset = collider1.unkC;
        CheckCollision(colliderXOffset + playerX - 8,
                       PLAYER.posY.i.hi + yOffset - 1, &collider2, 0);
        if (mistReset && (collider2.effects & EFFECT_MIST_ONLY)) {
            collider1.effects = EFFECT_NONE;
        }
        if (!(collider2.effects & EFFECT_SOLID)) {
            PLAYER.posX.i.hi += collider1.unkC;
            return 1;
        }
    }
    return 0;
}

bool func_8011203C(void) {
    s32 collision = func_80111D24();

    if (g_Entities[E_WEAPON].step == 5) {
        if (collision == false) {
            DestroyEntity(&g_Entities[E_WEAPON]);
            return true;
        }
        return false;
    } else if (g_Entities[E_WEAPON].step <= 2) {
        if (g_Entities[E_WEAPON].step != 0) {
            g_Player.unk46 = 0;
            g_Entities[E_WEAPON].step = 3;
        }
    }
    return false;
}

void func_801120B4(void) {
    s32 x_offset;
    u16 local_flags = 3;
    s32 atLedge;

    atLedge = 0;
    if (g_Player.pl_vram_flag & 0x20) {
        atLedge = 1;
    }

    if (((PLAYER.step_s == 0x57) || (PLAYER.step_s == 0x5B)) &&
        PLAYER.animFrameIdx < 5) {
        if (func_8010FDF8(0x43018) != 0) {
            return;
        }
        DecelerateX(0x1000);
    } else {
        if (func_8010FDF8(0x4301C) != 0) {
            return;
        }
        DecelerateX(0x2000);
    }

    if ((PLAYER.step < 0x40) && (g_Player.unk48 == 0)) {
        if (D_800ACF74 != 0) {
            D_800ACF74--;
        } else if (D_80097448[0] >= 0x31) {
            x_offset = 4;
            if (PLAYER.facingLeft != 0) {
                x_offset = -4;
            }
            PLAYER.posX.i.hi = x_offset + PLAYER.posX.i.hi;
            PLAYER.posY.i.hi -= 0x10;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(4, 13), 0);
            D_800ACF74 = 0x60;
            PLAYER.posY.i.hi += 0x10;
            PLAYER.posX.i.hi -= x_offset;
        }
    }
    switch (PLAYER.step_s) {
    case 0:
        break;
    case 1:
        local_flags = 1;
        if (g_Player.unk14 != 0) {
            switch (g_Player.unk14) {
            case 2:
                SetPlayerAnim(0xF2);
                PLAYER.facingLeft = 1;
                break;
            case 1:
                SetPlayerAnim(0xF2);
                PLAYER.facingLeft = 0;
                break;
            case 3:
                SetPlayerAnim(0xF3);
                PLAYER.facingLeft = 0;
                break;
            default:
                SetPlayerAnim(0xF3);
                PLAYER.facingLeft = 1;
                break;
            }
            PLAYER.step_s = 4;
            D_800ACF78 = 0x1800;
            local_flags |= 0x8000;
        } else if (!(g_Player.padPressed & PAD_UP)) {
            local_flags = 5;
        }
        break;
    case 2:
        switch (PLAYER.ext.player.anim) {
        case 10:
        case 11:
        case 14:
        case 15:
            break;
        default:
            SetPlayerAnim(0x63);
        case 0x63:
            if (g_Player.unk48 == 0) {
                local_flags = 5;
            }
        }
        break;
    case 0x3:
        local_flags = 0;
        if (((u16)PLAYER.animFrameIdx >= 4U) ||
            (PLAYER.ext.player.anim == 0xE)) {
            local_flags = 1;
        }
        if (((u16)PLAYER.animFrameIdx >= 7U) ||
            (PLAYER.animFrameDuration < 0)) {
            local_flags = 7;
        }
        break;
    case 0x4:
        if (PLAYER.ext.player.anim == 0xF2 && --D_800ACF78 == 0) {
            if (g_StageId == STAGE_NO1) {
                PlaySfx(0x7AD);
            }
            CreateEntFactoryFromEntity(g_CurrentEntity, 122, 0);
            D_800ACF78 = 0x200;
        }
        local_flags = 1;
        break;
    case 0x40:
    case 0x59:
        func_8010DFF0(1, 1);
        if ((u16)PLAYER.animFrameIdx < (u16)g_Player.unk54) {
            local_flags = 0;
            if (PLAYER.animFrameIdx < 2U) {
                CheckMoveDirection();
                if (g_Player.padPressed & PAD_DOWN) {
                    PLAYER.step = 2;
                    PLAYER.ext.player.anim = 0x26;
                }
            }
        } else {
            g_Player.unk46 &= 0x7FFF;
            local_flags = 0xB;
            if (PLAYER.animFrameIdx == 7) {
                if (g_Player.padPressed & g_Player.D_80072EF8) {
                    PLAYER.animFrameDuration = 2;
                } else {
                    local_flags = 0xF;
                }
            }
        }
        break;
    case 0x47:
    case 0x49:
        if ((PLAYER.animFrameIdx == 6) &&
            (g_Player.padPressed & g_Player.D_80072EF8)) {
            PLAYER.animFrameDuration = 2;
        }
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x46:
    case 0x48:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
    case 0x50:
    case 0x5D:
        func_8010DFF0(1, 1);
        if ((u16)PLAYER.animFrameIdx < (u16)g_Player.unk54) {
            local_flags = 0;
            if (PLAYER.animFrameIdx >= 3U) {
                break;
            }
            CheckMoveDirection();
            if (g_Player.padPressed & PAD_DOWN) {
                // Note that to reach this point, our minimum case is 0x41
                PLAYER.ext.player.anim = D_800B0608[PLAYER.step_s - 0x41] + 2;
                PLAYER.step = 2;
            }
        } else {
            g_Player.unk46 &= 0x7FFF;
            if (PLAYER.animFrameDuration < 0) {
                local_flags = 0xF;
            } else {
                local_flags = 0x1B;
            }
        }
        break;
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x5C:
        func_8010DFF0(1, 1);
        local_flags = 0;
        if (PLAYER.animFrameIdx == 0) {
            if (--D_80139824 == 0) {
                PLAYER.animFrameDuration = 1;
            } else {
                PLAYER.animFrameDuration = 2;
            }
        }
        if ((u16)PLAYER.animFrameIdx >= (u16)g_Player.unk54) {
            local_flags = 0x1B;
            g_Player.unk46 &= 0x7FFF;
        }
        if (PLAYER.animFrameDuration < 0) {
            local_flags = 0xF;
            break;
        }
        break;
    case 0x57:
    case 0x5B:
        func_8010DFF0(1, 1);
        local_flags = 0;
        if ((PLAYER.animFrameIdx < (g_Player.unk54 - 6)) &&
            (g_Player.pl_vram_flag & 1) && (g_GameTimer & 1)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(69, 1), 0);
        }
        if ((u16)PLAYER.animFrameIdx >= (u16)g_Player.unk54) {
            local_flags = 0x19;
            g_Player.unk46 &= 0x7FFF;
        }
        if (PLAYER.animFrameDuration < 0) {
            local_flags = 0xF;
        }
        if (PLAYER.animFrameIdx == 4 && PLAYER.animFrameDuration == 1 &&
            !(g_Player.pl_vram_flag & 1)) {
            PLAYER.animFrameIdx = 5;
            PLAYER.ext.player.anim = 0x6C;
            PLAYER.step = 4;
            g_Player.unk44 = 1;
        }
        break;
    case 0x58:
        func_8010DFF0(1, 1);
        if (D_80139824 > 0) {
            D_80139824--;
        }
        if (PLAYER.animFrameIdx == 4 && PLAYER.animFrameDuration == 1 &&
            D_80139824) {
            PLAYER.animFrameIdx = 2;
        }
        if (PLAYER.animFrameIdx == 6) {
            PLAYER.step_s = 0x40;
        }
        if (g_Player.padTapped & 0x4000) {
            PLAYER.step_s = 0x40;
        }
        if ((PLAYER.facingLeft && (g_Player.padPressed & PAD_RIGHT)) ||
            (!PLAYER.facingLeft && (g_Player.padPressed & PAD_LEFT))) {
            PLAYER.step_s = 0x40;
        }
        local_flags = 10;
        break;
    case 0x5A:
        func_8010DFF0(1, 1);
        if (D_80139824 > 0) {
            D_80139824--;
        }
        if (PLAYER.animFrameIdx == 6 && PLAYER.animFrameDuration == 1 &&
            D_80139824) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameIdx == 0xA) {
            PLAYER.step_s = 0x50;
        }
        if (g_Player.padTapped & (PAD_DOWN | PAD_UP)) {
            PLAYER.step_s = 0x50;
        }
        if ((PLAYER.facingLeft && (g_Player.padPressed & PAD_RIGHT)) ||
            (!PLAYER.facingLeft && (g_Player.padPressed & PAD_LEFT))) {
            PLAYER.step_s = 0x50;
        }
        local_flags = 0;
        break;
    case 0x45:
    case 0x51:
        func_8010DFF0(1, 1);
        // Probably some way to do this besides bit shifts but I couldn't get it
        local_flags = (((u16)PLAYER.animFrameDuration << 0x10) >> 0x1F) & 0xF;
        break;
    }

    if (local_flags & 4) {
        func_8010E570(0);
        local_flags |= 0x8000;
    }
    if ((local_flags & 2) && (g_Player.padPressed & PAD_UP) &&
        g_Player.unk48 == 0) {
        SetPlayerAnim(atLedge);
        PLAYER.step_s = 1;
        local_flags |= 0x8000;
        if (g_Player.unk14 != 0) {
            switch (g_Player.unk14) {
            case 2:
                SetPlayerAnim(0xF2);
                PLAYER.facingLeft = 1;
                break;
            case 1:
                SetPlayerAnim(0xF2);
                PLAYER.facingLeft = 0;
                break;
            case 3:
                SetPlayerAnim(0xF3);
                PLAYER.facingLeft = 0;
                break;
            default:
                SetPlayerAnim(0xF3);
                PLAYER.facingLeft = 1;
                break;
            }
            PLAYER.step_s = 4;
            D_800ACF78 = 0x1800;
            local_flags |= 0x8000;
        }
    }

    if ((local_flags & 1) && CheckMoveDirection()) {
        func_8010E6AC(0);
        local_flags |= 0x8000;
    }
    if ((local_flags & 0x8000) && (local_flags & 8)) {
        func_8010FAF4();
    }
}

void func_80112B64(void) {
    if (func_8010FDF8(0x4301C) == 0) {
        SetSpeedX(0x18000);
        if (CheckMoveDirection() == 0) {
            func_8010E570(0);
        }
    }
}
