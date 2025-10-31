// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "sfx.h"

// Forward declaration. EntityAlucard needs to not know these args are s16.
// But 80113D7C (in this file, but before PlayerStepKill) needs to know
// the proper s16 args. So we put it to the top of this file.
void PlayerStepKill(DamageParam* damage, s16 arg_PlayerStep, s16 arg2);

void func_80111928(void) { D_801396EA = 0; }

void func_80111938(void) {
    D_801396EA = 1;
    D_801396E4 = PLAYER.animCurFrame;
    D_801396E6 = PLAYER.drawFlags;
    D_801396E8 = PLAYER.palette;
}

void func_8011197C(void) {
    D_801396EA = 0;
    PLAYER.animCurFrame = D_801396E4;
    PLAYER.drawFlags = D_801396E6;
    PLAYER.palette = D_801396E8;
    PLAYER.hitParams = 0;
}

#ifndef VERSION_HD
extern s32 D_80137FDC;
#endif
bool func_801119C4(void) {
    if (!D_801396EA) {
        if (g_Player.padTapped & PAD_L2) {
            if (g_Player.demo_timer == 0) {
                func_80111938();
                return true;
            }
        }

        return false;
    }

    if (g_Player.demo_timer != 0) {
        func_8011197C();
        return false;
    }

    if (g_Player.padTapped & PAD_L2) {
        func_8011197C();
        return false;
    }

    if (g_Player.padPressed & PAD_CROSS) {
        if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.posX.val += FIX(16.0f);
        }
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.posX.val -= FIX(16.0f);
        }
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0f);
        }
        if (g_Player.padPressed & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0f);
        }

    } else {
        if (g_Player.padTapped & PAD_RIGHT) {
            PLAYER.posX.val += FIX(16.0f);
        }
        if (g_Player.padTapped & PAD_LEFT) {
            PLAYER.posX.val -= FIX(16.0f);
        }
        if (g_Player.padTapped & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0f);
        }
        if (g_Player.padTapped & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0f);
        }
    }
#ifndef VERSION_HD
    if (g_Player.padTapped & PAD_TRIANGLE) {
        if (D_80137FDC & 1) {
            PLAYER.palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
        } else {
            PLAYER.palette = PAL_FLAG(PAL_ALUCARD);
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
    if (!(PLAYER.animCurFrame <= 0xE0)) {
        PLAYER.animCurFrame = 0xE0;
    }
    FntPrint("charal:%02x\n", PLAYER.animCurFrame);
    return true;
}

void func_80111CC0(void) {
    if (g_Player.timers[1]) {
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x17), 0);
    }
    if (g_Player.timers[0]) {
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x16), 0);
    }
}

bool func_80111D24(void) {
    Collider collider;
    s32 hitboxRightMargin = 0;
    s32 hitboxLeftMargin = 0;
    s32 speed = FIX(0.75);
    s32 posX = PLAYER.posX.i.hi;
    s32 posY = PLAYER.posY.i.hi;

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
    s32 floorY;
    s32 xPos;
    s32 yPos;
    s32 filtered_effects;

    floorY = g_SensorsFloor[1].y - 1;
    xPos = PLAYER.posX.i.hi + 9;
    yPos = PLAYER.posY.i.hi + floorY - 1;
    CheckCollision(xPos, yPos, &collider1, 0);
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
        // This "plus 16, minus 8" is a random guess. The effect is just +8.
        // We can use any pair that comes out to 8, but the compiler comes
        // out wrong if we don't split it into two. So "+10-2" works equally
        // well for example. The real numbers are likely unknowable.
        xPos = (PLAYER.posX.i.hi + 16) + collider1.unk4 - 8;
        yPos = PLAYER.posY.i.hi + floorY - 1;
        CheckCollision(xPos, yPos, &collider2, 0);
        if (mistReset && (collider2.effects & EFFECT_MIST_ONLY)) {
            collider1.effects = EFFECT_NONE;
        }
        if (!(collider2.effects & EFFECT_SOLID)) {
            PLAYER.posX.i.hi += collider1.unk4;
            return 1;
        }
    }
    xPos = PLAYER.posX.i.hi - 9;
    yPos = PLAYER.posY.i.hi + floorY - 1;
    CheckCollision(xPos, yPos, &collider1, 0);

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
        // See above comment regarding values combining to 8.
        xPos = (PLAYER.posX.i.hi - 9) + collider1.unkC + 1;
        yPos = PLAYER.posY.i.hi + floorY - 1;
        CheckCollision(xPos, yPos, &collider2, 0);

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
    Entity* ent;
    bool collision = func_80111D24();

    if (g_Entities[E_WEAPON].step == 5) {
        if (collision) {
            return false;
        } else {
            ent = &g_Entities[E_WEAPON];
            DestroyEntity(ent);
            return true;
        }
    } else if (g_Entities[E_WEAPON].step <= 2) {
        if (g_Entities[E_WEAPON].step) {
            g_Player.unk46 = 0;
            g_Entities[E_WEAPON].step = 3;
        }
    }
    return false;
}

static s32 D_800ACF74 = 0;
static s32 g_AlucardChairSleepTimer = 0;

void PlayerStepStand(void) {
    s16 x_offset;
    u16 local_flags = 3;
    s32 atLedge;

    atLedge = 0;
    if (g_Player.vram_flag & IN_AIR_OR_EDGE) {
        atLedge = 1;
    }

    if (((PLAYER.step_s == 0x57) || (PLAYER.step_s == 0x5B)) &&
        PLAYER.pose < 5) {
        if (func_8010FDF8(0x43018) != 0) {
            return;
        }
        DecelerateX(FIX(0.0625));
    } else {
        if (func_8010FDF8(0x4301C) != 0) {
            return;
        }
        DecelerateX(FIX(0.125));
    }

    if ((PLAYER.step < 0x40) && (!g_Player.unk48)) {
        if (D_800ACF74 != 0) {
            D_800ACF74--;
        } else if (D_80097448[0] > 0x30) {
            x_offset = 4;
            if (PLAYER.facingLeft) {
                x_offset = -x_offset;
            }
            PLAYER.posX.i.hi += x_offset;
            PLAYER.posY.i.hi -= 0x10;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_4, 13), 0);
            PLAYER.posY.i.hi += 0x10;
            PLAYER.posX.i.hi -= x_offset;
            D_800ACF74 = 0x60;
        }
    }
    switch (PLAYER.step_s) {
    case Player_Stand_0:
        break;
    case Player_Stand_PressUp:
        local_flags = 1;
        if (g_Player.unk14 != 0) {
            switch (g_Player.unk14) {
            case 1:
                SetPlayerAnim(0xF2);
                PLAYER.facingLeft = 0;
                break;
            case 2:
                SetPlayerAnim(0xF2);
                PLAYER.facingLeft = 1;
                break;
            case 3:
                SetPlayerAnim(0xF3);
                PLAYER.facingLeft = 0;
                break;
            case 4:
            default:
                SetPlayerAnim(0xF3);
                PLAYER.facingLeft = 1;
                break;
            }
            PLAYER.step_s = Player_Stand_ChairSit;
            local_flags |= 0x8000;
            g_AlucardChairSleepTimer = 0x1800;
        } else if (!(g_Player.padPressed & PAD_UP)) {
            local_flags = 5;
        }
        break;
    case Player_Stand_2:
        switch (PLAYER.ext.player.anim) {
        case 11:
        case 10:
        case 15:
        case 14:
            break;
        default:
            SetPlayerAnim(0x63);
        case 0x63:
            if (g_Player.unk48 == 0) {
                local_flags = 5;
            }
        }
        break;
    case Player_Stand_3:
        local_flags = 0;
        if ((PLAYER.pose >= 4) || (PLAYER.ext.player.anim == 0xE)) {
            local_flags = 1;
        }
        if ((PLAYER.pose >= 7) || (PLAYER.poseTimer < 0)) {
            local_flags = 7;
        }
        break;
    case Player_Stand_ChairSit:
        if (PLAYER.ext.player.anim == 0xF2 && --g_AlucardChairSleepTimer == 0) {
            if (g_StageId == STAGE_NO1) {
                PlaySfx(SFX_ALU_ZZZ_SNORE);
            }
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_SLEEP_ZZZ, 0), 0);
            g_AlucardChairSleepTimer = 0x200;
        }
        local_flags = 1;
        break;
    case 0x40:
    case 0x59:
        func_8010DFF0(1, 1);
        if (PLAYER.pose < g_Player.unk54) {
            if (PLAYER.pose < 2) {
                CheckMoveDirection();
                if (g_Player.padPressed & PAD_DOWN) {
                    PLAYER.step = 2;
                    PLAYER.ext.player.anim = 0x26;
                }
            }
            local_flags = 0;
        } else {
            g_Player.unk46 &= 0x7FFF;
            local_flags = 0xB;
            if (PLAYER.pose == 7) {
                if (g_Player.padPressed & g_Player.D_80072EF8) {
                    PLAYER.poseTimer = 2;
                } else {
                    local_flags = 0xF;
                }
            }
        }
        break;
    case 0x47:
    case 0x49:
        if ((PLAYER.pose == 6) && (g_Player.padPressed & g_Player.D_80072EF8)) {
            PLAYER.poseTimer = 2;
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
    case 0x5D:
    case 0x4E:
    case 0x4F:
    case 0x50:
        func_8010DFF0(1, 1);
        if (PLAYER.pose < g_Player.unk54) {
            if (PLAYER.pose < 3) {
                CheckMoveDirection();
                if (g_Player.padPressed & PAD_DOWN) {
                    // Note that to reach this point, our minimum case is 0x41
                    PLAYER.ext.player.anim =
                        D_800B0608[PLAYER.step_s - 0x41] + 2;
                    PLAYER.step = 2;
                }
            }
            local_flags = 0;
        } else {
            g_Player.unk46 &= 0x7FFF;
            local_flags = 0x1B;
            if (PLAYER.poseTimer < 0) {
                local_flags = 0xF;
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
        if (PLAYER.pose == 0) {
            if (--D_80139824 == 0) {
                PLAYER.poseTimer = 1;
            } else {
                PLAYER.poseTimer = 2;
            }
        }
        if (PLAYER.pose >= g_Player.unk54) {
            g_Player.unk46 &= 0x7FFF;
            local_flags = 0x1B;
        }
        if (PLAYER.poseTimer < 0) {
            local_flags = 0xF;
            break;
        }
        break;
    case 0x57:
    case 0x5B:
        func_8010DFF0(1, 1);
        local_flags = 0;
        if ((PLAYER.pose < (g_Player.unk54 - 6)) &&
            (g_Player.vram_flag & TOUCHING_GROUND) && (g_GameTimer & 1)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_69, 1), 0);
        }
        if (PLAYER.pose >= g_Player.unk54) {
            g_Player.unk46 &= 0x7FFF;
            local_flags = 0x19;
        }
        if (PLAYER.poseTimer < 0) {
            local_flags = 0xF;
        }
        if (PLAYER.pose == 4 && PLAYER.poseTimer == 1 &&
            !(g_Player.vram_flag & TOUCHING_GROUND)) {
            PLAYER.pose = 5;
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
        if (PLAYER.pose == 4 && PLAYER.poseTimer == 1 && D_80139824) {
            PLAYER.pose = 2;
        }
        if (PLAYER.pose == 6) {
            PLAYER.step_s = 0x40;
        }
        if (g_Player.padTapped & PAD_DOWN) {
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
        if (PLAYER.pose == 6 && PLAYER.poseTimer == 1 && D_80139824) {
            PLAYER.poseTimer = 2;
        }
        if (PLAYER.pose == 0xA) {
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
        local_flags = 0;
        if (PLAYER.poseTimer < 0) {
            local_flags = 0xF;
        }
        break;
    }

    if (local_flags & 4) {
        func_8010E570(0);
        local_flags |= 0x8000;
    }
    if ((local_flags & 2) && (g_Player.padPressed & PAD_UP) &&
        !g_Player.unk48) {
        SetPlayerAnim(atLedge);
        PLAYER.step_s = Player_Stand_PressUp;
        local_flags |= 0x8000;
        if (g_Player.unk14 != 0) {
            switch (g_Player.unk14) {
            case 1:
                SetPlayerAnim(0xF2);
                PLAYER.facingLeft = 0;
                break;
            case 2:
                SetPlayerAnim(0xF2);
                PLAYER.facingLeft = 1;
                break;
            case 3:
                SetPlayerAnim(0xF3);
                PLAYER.facingLeft = 0;
                break;
            case 4:
            default:
                SetPlayerAnim(0xF3);
                PLAYER.facingLeft = 1;
                break;
            }
            PLAYER.step_s = Player_Stand_ChairSit;
            local_flags |= 0x8000;
            g_AlucardChairSleepTimer = 0x1800;
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

void PlayerStepWalk(void) {
    if (func_8010FDF8(0x4301C) == 0) {
        SetSpeedX(FIX(1.5));
        if (CheckMoveDirection() == 0) {
            func_8010E570(0);
        }
    }
}

s16 D_800ACF7C[] = {
    1,
    31,
    0,
    27,
};

s16 g_SfxPainGrunts[] = {
    SFX_VO_ALU_YELL,   SFX_VO_ALU_SILENCE, SFX_VO_ALU_PAIN_E, SFX_VO_ALU_PAIN_D,
    SFX_VO_ALU_PAIN_C, SFX_VO_ALU_PAIN_B,  SFX_VO_ALU_PAIN_A,
};

void PlayerStepJump(void) {
    s32 walkResult;
    s16 stepSlot;

    if (PLAYER.step_s != 0x58) {
        DecelerateX(FIX(1.0 / 16));
        if (PLAYER.velocityY < FIX(-1)) {
            if (!(g_Player.unk44 & 0x40) &&
                !(g_Player.padPressed & PAD_CROSS)) {
                PLAYER.velocityY = FIX(-1);
            }
            if (g_Player.vram_flag & TOUCHING_CEILING) {
                PLAYER.velocityY = FIX(-0.25);
                g_Player.unk44 |= 0x20;
            }
        }
        if (func_8010FDF8(0x11029)) {
            return;
        }
    }
    switch (PLAYER.step_s) {
    case 0x0:
        walkResult = CheckMoveDirection();
        if (walkResult != 0) {
            if ((PLAYER.ext.player.anim == 0x16) ||
                (PLAYER.ext.player.anim == 0x19)) {
                SetPlayerAnim(0x18);
            }
            SetSpeedX(FIX(1.5));
        } else if ((PLAYER.ext.player.anim == 0x1A) ||
                   (PLAYER.ext.player.anim == 0x18)) {
            SetPlayerAnim(0x19);
        }
        if (walkResult <= 0) {
            g_Player.unk44 &= ~0x10;
        }
        if (PLAYER.velocityY > 0) {
            if (PLAYER.ext.player.anim != 0x1B) {
                SetPlayerAnim(0x1B);
            }
            PLAYER.step_s = 1;
        }
        break;
    case 0x1:
        walkResult = CheckMoveDirection();
        if (walkResult != 0) {
            SetSpeedX(FIX(1.5));
        }
        if (walkResult <= 0) {
            g_Player.unk44 &= ~0x10;
        }
        break;
    case 0x58:
        func_8010DFF0(1, 1);
        if (D_80139824 > 0) {
            D_80139824--;
        }
        if ((PLAYER.pose == 3) && (PLAYER.poseTimer == 1) &&
            (D_80139824 != 0)) {
            PLAYER.pose = 1;
        }
        if ((PLAYER.pose == 4) || (g_Player.padTapped & (PAD_DOWN | PAD_UP))) {
            PLAYER.step_s = 0x40;
        }
        break;
    case 0x57:
    case 0x5B:
        func_8010DFF0(1, 1);
        DecelerateX(FIX(1.0 / 16));
        if (PLAYER.ext.player.anim == 0x6C) {
            if (PLAYER.poseTimer < 0) {
                if (PLAYER.velocityY > FIX(1)) {
                    stepSlot = 0;
                } else {
                    stepSlot = 2;
                }
                PLAYER.step_s = D_800ACF7C[stepSlot];
                SetPlayerAnim((u8)D_800ACF7C[stepSlot + 1]);
                func_8010FAF4();
                g_Player.unk44 = 1;
                g_ButtonCombo[COMBO_BF].buttonsCorrect = 0xFE;
                g_ButtonCombo[COMBO_BF].timer = 0x10;
            }
        } else if ((PLAYER.pose == 4) && (PLAYER.poseTimer == 1)) {
            PLAYER.pose = 5;
            PLAYER.ext.player.anim = 0x6C;
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
    case 0x4A:
    case 0x49:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x5D:
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
        func_8010DFF0(1, 1);
    case 0x59:
    case 0x40:
        func_8010DFF0(1, 1);
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.velocityX = FIX(-1.5);
        }
        if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.velocityX = FIX(1.5);
        }
        if (PLAYER.poseTimer < 0) {
            if (PLAYER.velocityY > FIX(1)) {
                stepSlot = 0;
            } else {
                stepSlot = 2;
            }
            PLAYER.step_s = D_800ACF7C[stepSlot];
            SetPlayerAnim((u8)D_800ACF7C[stepSlot + 1]);
            func_8010FAF4();
        }
        break;
    // This case is when we're dive-kicking
    case 0x70:
        // This flag is set in EntityDiveKickAttack if it detects a hit
        if (g_Player.unk44 & 0x80) {
            func_8010E83C(1);
            // If cross is not pressed, we bounce up from the hit.
            // But note that the above function call includes the line:
            // PLAYER.velocityY = FIX(-4.875);
            // So we will always bounce up, but this makes us bounce up less,
            // if not pressing cross.
            if (!(g_Player.padPressed & PAD_CROSS)) {
                PLAYER.velocityY = FIX(-4.25);
            }
            g_Player.unk44 |= 0x40;
        }
        break;
    }
    // This block initiates a dive-kick
    if (PLAYER.step_s == 0 || PLAYER.step_s == 1) {
        if (!(g_Player.unk44 & 1)) {
            return;
        }
        if ((g_Player.padPressed & PAD_DOWN) &&
            (g_Player.padTapped & PAD_CROSS)) {
            SetPlayerAnim(0x22);
            PLAYER.step_s = 0x70;
            // blueprint 5 has child ID 6, which is EntityDiveKickAttack
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_5, 0);
            g_Player.unk44 &= ~0x80;
            PLAYER.velocityY = FIX(6);
            if (walkResult != 0) {
                SetSpeedX(FIX(4.5));
            }
            PlaySfx(SFX_VO_ALU_ATTACK_C);
        }
    }
    if (g_Player.unk44 & 0x100) {
        PLAYER.velocityX = 0;
    }
}

void PlayerStepFall(void) {
    if (g_Player.timers[5] && g_Player.padTapped & PAD_CROSS) {
        func_8010E83C(1);
    } else if (func_8010FDF8(0x9029) == 0) {
        DecelerateX(FIX(1.0 / 16));
        if (CheckMoveDirection()) {
            SetSpeedX(FIX(0.75));
        }
    }
}

void PlayerStepCrouch(void) {
    s32 i;
    s16 x_offset;
    s16 local_flags;
    bool atLedge;

    local_flags = 0;

    atLedge = 0;
    if (g_Player.vram_flag & IN_AIR_OR_EDGE) {
        atLedge = 1;
    }

    if ((g_Player.padTapped & PAD_CROSS) && !(g_Player.unk46 & 0x8000)) {
        if (g_Player.padPressed & PAD_DOWN) {
            for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
                if (g_Player.colFloor[i].effects & EFFECT_SOLID_FROM_ABOVE) {
                    g_Player.timers[7] = 8;
                    return;
                }
            }
        }
        if (!g_Player.unk72) {
            func_8010E83C(1);
            return;
        }
    }
    if (func_8010FDF8(0x100C) != 0) {
        return;
    }
    DecelerateX(FIX(1.0 / 8));
    if (g_Player.unk48) {
        if (PLAYER.ext.player.anim == 0x11) {
            PLAYER.ext.player.anim = 0x65;
            PLAYER.poseTimer = 2;
            PLAYER.pose = 3;
        }
    } else if (PLAYER.ext.player.anim == 0x65) {
        SetPlayerAnim(0x11);
    }
    switch (PLAYER.step_s) {
    case 0x0:
        if (D_800ACF74 != 0) {
            D_800ACF74--;
        } else if (D_80097448[0] > 0x18) {
            if (!g_Player.unk48) {
                x_offset = 12;
                if (PLAYER.facingLeft) {
                    x_offset = -x_offset;
                }
                PLAYER.posX.i.hi += x_offset;
                PLAYER.posY.i.hi += 2;
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_4, 13), 0);
                PLAYER.posY.i.hi -= 2;
                PLAYER.posX.i.hi -= x_offset;
                D_800ACF74 = 0x60;
            }
        }
        local_flags = 6;
        break;
    case 0x1:
        if (!(g_Player.padPressed & PAD_DOWN)) {
            local_flags = 1;
            if ((PLAYER.pose >= 4) || PLAYER.ext.player.anim == 0x65) {
                SetPlayerAnim(0x13);
                PLAYER.step_s = 2;
                PLAYER.pose = 2;
                if (g_Player.unk72 == 1) {
                    PLAYER.pose = 0;
                }
                if (g_Player.unk72 == 2) {
                    PLAYER.pose = 1;
                }
                return;
            }
        } else if (PLAYER.ext.player.anim == 0x65) {
            PLAYER.step_s = 0;
        } else {
            if (PLAYER.poseTimer < 0) {
                local_flags = 0x20;
            }
        }
        break;
    case 0x5:
        func_8010DFF0(1, 1);
        if (g_Player.unk72 == PLAYER.pose || PLAYER.poseTimer < 0) {
            local_flags = 0x20;
        }
        break;
    case 0x4:
    case 0x3:
        func_8010DFF0(1, 1);
        if (PLAYER.poseTimer < 0) {
            local_flags = 0x20;
        }
        break;
    case 0x2:
        local_flags = 1;
        if (g_Player.padPressed & PAD_DOWN) {
            func_8010E470(0, PLAYER.velocityX);
            break;
        }
        if (g_Player.unk72) {
            func_8010DFF0(1, 1);
            if (g_Player.unk72 == 1) {
                PLAYER.pose = 0;
                PLAYER.poseTimer = 3;
                break;
            } else if (g_Player.unk72 == 2) {
                if (PLAYER.pose > 0) {
                    PLAYER.pose = 1;
                    PLAYER.poseTimer = 3;
                }
                break;
            } else if (g_Player.unk72 == 3) {
                if (PLAYER.pose >= 2) {
                    PLAYER.pose = 2;
                    PLAYER.poseTimer = 3;
                }
                break;
            } else if (g_Player.unk72 == 4) {
                if (PLAYER.pose >= 3) {
                    PLAYER.pose = 3;
                    PLAYER.poseTimer = 3;
                }
                break;
            }
        }
        if (PLAYER.poseTimer < 0) {
            func_8010E570(0);
        }

        break;
    case 0x40:
    case 0x59:
        func_8010DFF0(1, 1);
        if (PLAYER.pose < g_Player.unk54) {
            if (PLAYER.pose < 2) {
                CheckMoveDirection();
                if (!(g_Player.padPressed & PAD_DOWN)) {
                    if (!g_Player.unk72) {
                        PLAYER.step = 0;
                        PLAYER.ext.player.anim = 0x24;
                    }
                }
            }
        } else {
            g_Player.unk46 &= 0x7FFF;
            local_flags = 0xE;
            if (PLAYER.pose == 7) {
                if (g_Player.padPressed & g_Player.D_80072EF8) {
                    PLAYER.poseTimer = 2;
                } else {
                    local_flags = 0x2E;
                }
            }
        }
        break;
    case 0x47:
    case 0x49:
        if ((PLAYER.pose == 6) && (g_Player.padPressed & g_Player.D_80072EF8)) {
            PLAYER.poseTimer = 2;
        }
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
    case 0x5D:
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
        func_8010DFF0(1, 1);
        if (PLAYER.pose < g_Player.unk54) {
            if (PLAYER.pose < 3) {
                CheckMoveDirection();
                if (!(g_Player.padPressed & PAD_DOWN)) {
                    if (!g_Player.unk72) {
                        PLAYER.ext.player.anim =
                            D_800B0608[PLAYER.step_s - 0x41] + atLedge;
                        PLAYER.step = 0;
                    }
                }
            }
        } else {
            g_Player.unk46 &= 0x7FFF;
            local_flags = 0xE;
            if (PLAYER.poseTimer < 0) {
                local_flags = 0x2E;
            }
        }
        break;
    case 0x51:
        func_8010DFF0(1, 1);
        if (PLAYER.poseTimer < 0) {
            local_flags = 0x2E;
        }
        break;
    }

    if (local_flags & 0x20) {
        func_8010E470(0, 0);
        local_flags |= 0x8000;
    }
    if (local_flags & 2) {
        if (g_Player.unk4C) {
            SetPlayerAnim(0x14);
            PLAYER.step_s = 0;
            local_flags |= 0x8000;
        }
    }
    if (local_flags & 4) {
        if (!(g_Player.padPressed & PAD_DOWN)) {
            SetPlayerAnim(0x13);
            PLAYER.step_s = 2;
            local_flags |= 0x8000;
        }
    }
    if (local_flags & 1) {
        if (CheckMoveDirection()) {
            switch (g_Player.unk72 & 0xFF) {
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
                    SetPlayerAnim(0xF6);
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

void func_801139CC(u16 arg0) {
    s16 move = 3;
    if (PLAYER.facingLeft) {
        move = -move;
    }

    PLAYER.posY.i.hi -= 22;
    PLAYER.posX.i.hi += move;
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_4, 1), 0);
    PLAYER.posY.i.hi += 22;
    PLAYER.posX.i.hi -= move;

    if (arg0 & 1) {
        func_80102CD8(3);
        PlaySfx(SFX_WALL_DEBRIS_B);
    }
    if (arg0 & 2) {
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
    }
}

void PlayerStepHighJump(void) {
    s16 var_s1 = 0;

    g_Player.unk4A++;
    if (func_8010FDF8(2) != 0) {
        return;
    }

    switch (PLAYER.step_s) {
    case 0:
        if (g_Player.vram_flag & TOUCHING_CEILING) {
            func_801139CC(3);
            if (g_Player.unk4A > 4) {
                PLAYER.step_s = 2;
                PLAYER.drawFlags |= FLAG_DRAW_ROTATE;
                PLAYER.rotate = 0x800;
                PLAYER.rotPivotX = 0;
                PLAYER.rotPivotY = 2;
                PLAYER.facingLeft += 1;
                PLAYER.facingLeft &= 1;
                SetPlayerAnim(0x2B);
            } else {
                PLAYER.step_s = 3;
            }
        } else if (g_Player.unk4A > 28) {
            PLAYER.step_s = 1;
            PLAYER.velocityY = FIX(-6);
            SetPlayerAnim(0x1B);
        }
        break;

    case 1:
        if (g_Player.vram_flag & TOUCHING_CEILING) {
            PLAYER.step_s = 2;
            func_801139CC(3);
        } else {
            PLAYER.velocityY += FIX(3.0 / 8);
            if (PLAYER.velocityY > FIX(0.5)) {
                var_s1 = 1;
            }
        }
        break;

    case 2:
        PLAYER.drawFlags |= FLAG_DRAW_ROTATE;
        PLAYER.rotPivotX = 0;
        PLAYER.rotPivotY = 2;
        if (g_Player.unk4A > 0x38) {
            SetPlayerAnim(0x2D);
            PLAYER.drawFlags &=
                (FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40 |
                 FLAG_BLINK | FLAG_DRAW_OPACITY | FLAG_DRAW_SCALEY |
                 FLAG_DRAW_SCALEX);
            PLAYER.rotate = 0;
            PLAYER.facingLeft += 1;
            PLAYER.facingLeft &= 1;
            PLAYER.step_s = 4;
        }
        break;

    case 3:
        if (g_Player.unk4A > 20) {
            var_s1 = 1;
        }
        break;

    case 4:
        PLAYER.velocityY += FIX(1.0 / 16);
        if (PLAYER.poseTimer < 0) {
            var_s1 = 2;
        }
        break;
    }

    if (var_s1) {
        if (--var_s1) {
            SetPlayerAnim(0x1C);
        }
        PLAYER.palette = PAL_FLAG(PAL_ALUCARD);
        PLAYER.step_s = 1;
        PLAYER.step = Player_Jump;
    }
}

s32 func_80113D7C(s16 damageAmount) {
    DamageParam damage;
    s32 handleDamageResult;
    s16 step;
    s16 step_s;

    damageAmount = damageAmount / 2;

    handleDamageResult = HandleDamage(&damage, DAMAGEKIND_2, damageAmount, 1);
    CreateHPNumMove(damage.damageTaken, 0);
    func_800FE8F0();
    if (handleDamageResult == 4) {
        // Cache these values because we're going to set Player_Kill.
        step = PLAYER.step;
        step_s = PLAYER.step_s;
        damage.effects = EFFECT_NONE;
        damage.damageKind = DAMAGEKIND_0;
        SetPlayerStep(Player_Kill);
        PlayerStepKill(&damage, step, step_s);
        return -1;
    }
    g_Player.timers[2] = 4;
    g_Player.unk40 = 0x8166;
    PlaySfx(g_SfxPainGrunts[(rand() & 1) + 3]);
    return 0;
}

s32 func_80113E68(void) {
    s16 rnd = rand() & PSP_RANDMASK;
    PLAYER.ext.player.anim = 0x2E + (rnd % 3);
    return rnd % 16;
}

void func_80113EE0(void) {
    PLAYER.pose = PLAYER.poseTimer = 0;
    PLAYER.animSet = ANIMSET_DRA(1);
    PLAYER.entityId = 0;
    PLAYER.drawMode = DRAW_DEFAULT;
    g_Player.unk44 = 0;
    g_Player.unk46 = 0;
    PLAYER.drawFlags &= (FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40 |
                         FLAG_BLINK | FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX);
    PLAYER.rotate = 0;
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
    if (g_Entities[E_WEAPON].entityId == E_MIST) {
        func_8010FAF4();
    }
}

void func_80113F7C(void) {
    Entity* other = PLAYER.unkB8;
    s16 otherHitboxOffX;
    s16 playerHitboxOffX;
    s16 posX;

#if defined(VERSION_PSP)
    if (other == NULL) {
        return;
    }
#endif

    if (other->facingLeft) {
        otherHitboxOffX = -other->hitboxOffX;
    } else {
        otherHitboxOffX = other->hitboxOffX;
    }

    if (PLAYER.facingLeft) {
        playerHitboxOffX = -PLAYER.hitboxOffX;
    } else {
        playerHitboxOffX = PLAYER.hitboxOffX;
    }

    posX = PLAYER.posX.i.hi + playerHitboxOffX - other->posX.i.hi -
           otherHitboxOffX;

    if (abs(posX) < 16 && other->velocityX != 0) {
        if (other->velocityX < 0) {
            PLAYER.entityRoomIndex = 0;
        } else {
            PLAYER.entityRoomIndex = 1;
        }
    } else {
        if (posX < 0) {
            PLAYER.entityRoomIndex = 0;
        } else {
            PLAYER.entityRoomIndex = 1;
        }
    }
}

void AlucardHandleDamage(DamageParam* damage, s16 arg1, s16 arg2) {
    void (*weapon_func)(void);
    bool step_sIsZero = false;
    s16 randbit;
    s16 var_s2;
    s16 sfxIndex;
    s32 i;

    switch (PLAYER.step_s) {
    case 0:
        step_sIsZero = true;
        func_80113EE0();
        if (damage->damageKind < DAMAGEKIND_16) {
            func_80113F7C();
        } else {
            if (damage->damageKind == DAMAGEKIND_16) {
                func_80113F7C();
            }
            if (damage->damageKind == DAMAGEKIND_17) {
                PLAYER.entityRoomIndex = 1;
            }
            if (damage->damageKind == DAMAGEKIND_18) {
                PLAYER.entityRoomIndex = 0;
            }
        }
        if (g_Player.status & PLAYER_STATUS_AXEARMOR) {
            PLAYER.velocityY = FIX(-3);
            func_8010E3B8(FIX(-1.25));
            PLAYER.step = Player_AxearmorHit;
            PLAYER.step_s = 0;
            PLAYER.ext.player.anim = 0xD1;
            PlaySfx(SFX_VO_ALU_YELL);
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_85, 0);
            weapon_func = D_8017A000.func_ptr_80170010;
            weapon_func();
            if (g_Player.unk72) {
                PLAYER.velocityY = 0;
            }
            return;
        }
        func_80111CC0();
        i = 0;
        sfxIndex = 0;
        switch (damage->damageKind) {
        case DAMAGEKIND_5:
            i = 13;
            g_Player.damageTaken = damage->damageTaken;
        case DAMAGEKIND_4:
            PLAYER.posY.val -= 1;
            PLAYER.velocityY = FIX(-0.5);
            func_8010E3B8(FIX(-8));
            PLAYER.step_s = i + 2;
            PLAYER.ext.player.anim = 0x2E;
            g_Player.timers[2] = 0x200;
            PLAYER.facingLeft = PLAYER.entityRoomIndex;
            if (damage->damageKind == DAMAGEKIND_4) {
                sfxIndex = (rand() & 1) + 1;
            }
            break;
        case DAMAGEKIND_16:
        case DAMAGEKIND_18:
        case DAMAGEKIND_17:
            sfxIndex = (rand() & 1) + 3;
            switch (arg1) {
            case 4:
            case 3:
                i = FIX(1);
            case 0:
            case 1:
                break;
            }
            PLAYER.velocityY = i + FIX(-4);
            func_8010E3B8(FIX(-5.0 / 3));
            PLAYER.step_s = 1;
            if (func_80113E68() == 0) {
                PLAYER.ext.player.anim = 0x40;
            }
            break;
        case DAMAGEKIND_3:
        case DAMAGEKIND_7:
            sfxIndex = (rand() & 1) + 3;
            switch (arg1) {
            case 3:
            case 4:
                i = FIX(1);
            case 0:
            case 1:
            case 5:
            default:
                PLAYER.velocityY = i + FIX(-4);
                func_8010E3B8(FIX(-5.0 / 3));
                PLAYER.step_s = 1;
                if (func_80113E68() == 0) {
                    PLAYER.ext.player.anim = 0x40;
                }
                break;
            case 2:
            case 6:
                PLAYER.velocityY = 0;
                func_8010E3B8(FIX(-5.0 / 2));
                PLAYER.step_s = 7;
                PLAYER.ext.player.anim = 0x23;
                CreateEntFactoryFromEntity(g_CurrentEntity, BP_0, 0);
            }
            break;
        case DAMAGEKIND_2:
            sfxIndex = (rand() & 1) + 5;
            switch (arg1) {
            case 0:
            case 1:
                PLAYER.velocityY = 0;
                func_8010E3B8(FIX(-2.5));
                PLAYER.step_s = 6;
                randbit = (rand() & 1);
                // Weird test, I  think PLAYER.entityRoomIndex is a wrong name.
                // But if they don't match, we add 2 to the offset.
                if (PLAYER.entityRoomIndex != PLAYER.facingLeft) {
                    randbit += 2;
                }
                PLAYER.ext.player.anim = randbit + 0x31;
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_0, 6), 0);
                break;
            case 2:
            case 6:
                PLAYER.velocityY = 0;
                func_8010E3B8(FIX(-2.5));
                PLAYER.step_s = 7;
                PLAYER.ext.player.anim = 0x23;
                CreateEntFactoryFromEntity(g_CurrentEntity, BP_0, 0);
                break;
            case 3:
            case 4:
            case 5:
            default:
                PLAYER.velocityY = FIX(-2);
                func_8010E3B8(FIX(-1.25));
                PLAYER.step_s = 1;
                func_80113E68();
                break;
            }
            break;
        default:
            FntPrint("dam_kind:%04x\n", damage->damageKind);
            break;
        }
        g_Player.unk40 = 0x8166;
        g_Player.timers[2] = 6;
        PlaySfx(g_SfxPainGrunts[sfxIndex]);
        if (damage->effects & ELEMENT_CURSE) {
            g_Player.timers[1] =
                GetStatusAilmentTimer(STATUS_AILMENT_CURSE, 0x400);
            g_Player.unk40 = 0x8165;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_47, 2), 0);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x17), 0);
            PlaySfx(SFX_VO_ALU_WHAT);
        } else if (damage->effects & ELEMENT_POISON) {
            g_Player.timers[0] =
                GetStatusAilmentTimer(STATUS_AILMENT_POISON, 0xFFF);
            g_Player.unk40 = 0x8164;
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x16), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_47, 1), 0);
            PlaySfx(SFX_VO_ALU_WHAT);
        } else if (damage->effects & ELEMENT_FIRE) {
            PlaySfx(SFX_FM_EXPLODE_SWISHES);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x45), 0);
            g_Player.unk40 = 0x8160;
            if (damage->effects & ELEMENT_UNK_10000) {
                CreateEntFactoryFromEntity(g_CurrentEntity, BP_19, 0);
                g_Player.timers[2] = 10;
            } else {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_17, 1), 0);
                CreateEntFactoryFromEntity(g_CurrentEntity, BP_18, 0);
                g_Player.timers[2] = 16;
            }
        } else if (damage->effects & ELEMENT_THUNDER) {
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_45, 0);
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x46), 0);
            g_Player.timers[2] = 24;
            g_Player.unk40 = 0x8102;
        } else if (damage->effects & ELEMENT_ICE) {
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_HIT_BY_ICE, 0);
            g_Player.timers[2] = 12;
            g_Player.unk40 = 0x8169;
            PLAYER.ext.player.anim = 0x2E;
        } else {
            if (damage->effects & ELEMENT_HOLY) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_119, 0), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x68), 0);
                g_Player.timers[2] = 8;
                g_Player.unk40 = 0x8168;
            }
            if (damage->effects & ELEMENT_DARK) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_113, 0), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x62), 0);
                g_Player.timers[2] = 16;
                g_Player.unk40 = 0x8164;
            }
            if (damage->effects & ELEMENT_CUT) {
                PlaySfx(SFX_WEAPON_STAB_B);
                g_Player.unk40 = 0x8166;
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x42), 0);
                if (damage->effects & ELEMENT_UNK_10000) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_21, 5), 0);
                    g_Player.timers[2] = 10;
                } else {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_20, 5), 0);
                    g_Player.timers[2] = 16;
                }
            } else {
                i = damage->effects & ELEMENT_WATER;
                if (!(damage->effects &
                      (ELEMENT_FIRE | ELEMENT_THUNDER | ELEMENT_ICE |
                       ELEMENT_HOLY | ELEMENT_DARK | ELEMENT_STONE |
                       ELEMENT_CUT | ELEMENT_POISON))) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x58), 0);
                }
            }
        }

        break;
    case 1:
        if (func_8010FDF8(0x20280) != 0) {
            return;
        }
        if (PLAYER.poseTimer < 0) {
            SetPlayerAnim(0x1C);
            PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
        }
        break;
    case 15:
    case 2:
        if ((g_Player.unk04 & 0x8000) &&
            !(g_Player.vram_flag & TOUCHING_ANY_SLOPE)) {
            goto deepcond;
        }
        if ((g_Player.vram_flag & TOUCHING_ANY_SLOPE) && !(g_GameTimer & 1)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_69, 10), 0);
        }
        if (!(g_Player.vram_flag &
              (TOUCHING_L_WALL | TOUCHING_R_WALL | TOUCHING_CEILING))) {
            break;
        }
        if (g_Player.vram_flag & TOUCHING_CEILING) {
            func_801139CC(1);
            PLAYER.velocityX /= 2;
            PLAYER.velocityY = 0;
            g_Player.timers[8] = 24;
            PLAYER.step_s = 5;
            if (g_Player.prev_step_s == 0xF &&
                (func_80113D7C(g_Player.damageTaken) != 0)) {
                return;
            }
            break;
        }
        if ((g_StageId != STAGE_BO6) && (g_StageId != STAGE_RBO6) &&
            (g_StageId != STAGE_DRE)) {
            for (i = 2; i < NUM_VERTICAL_SENSORS; i++) {
                if (g_Player.colWall[i].effects & EFFECT_UNK_0002) {
                    break;
                }
            }
            if (i == NUM_VERTICAL_SENSORS) {
                for (i = NUM_VERTICAL_SENSORS + 2; i < NUM_VERTICAL_SENSORS * 2;
                     i++) {
                    if (g_Player.colWall[i].effects & EFFECT_UNK_0002) {
                        break;
                    }
                }
            }
            if (i == 14) {
            // Not a very good label name, but it's deep in a bunch of
            // conditionals.
            deepcond:
                PLAYER.velocityY = FIX(-4);
                func_8010E3B8(FIX(-1.25));
                PLAYER.ext.player.anim = 0x2F;
                var_s2 = -3;
                if (PLAYER.velocityX != 0) {
                    var_s2 = -var_s2;
                }
                PLAYER.posY.i.hi += 0x15;
                PLAYER.posX.i.hi += var_s2;
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_4, 9), 0);
                PLAYER.posY.i.hi -= 0x15;
                PLAYER.posX.i.hi -= var_s2;
                PlaySfx(SFX_WALL_DEBRIS_B);
                func_80102CD8(2);
                PLAYER.step_s = 1;
                if (g_Player.prev_step_s == 0xF &&
                    (func_80113D7C(g_Player.damageTaken) != 0)) {
                    return;
                }
                break;
            }
        }

        if (PLAYER.step_s == 0xF) {
            g_Player.timers[8] = 8;
            SetPlayerAnim(0x3F);
            PlaySfx(SFX_WALL_DEBRIS_B);
            PLAYER.velocityY = FIX(-2.5);
            func_80102CD8(2);
            PLAYER.step_s = 3;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_31, 8), 0);
            if (func_80113D7C(g_Player.damageTaken) != 0) {
                return;
            }
            break;
        }

        PLAYER.velocityX /= 2;
        PLAYER.velocityY = 0;
        g_Player.timers[8] = 48;
        PlaySfx(SFX_STOMP_HARD_B);
        PLAYER.drawFlags |= FLAG_DRAW_ROTATE;
        PLAYER.rotate = 0x400;
        PLAYER.rotPivotX = 0x10;
        PLAYER.rotPivotY = 4;
        SetPlayerAnim(0x2C);
        PLAYER.step_s = 0xE;
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_31, 8), 0);
        break;
    case 3:
        if (!g_Player.timers[8]) {
            SetSpeedX(FIX(0.75));
            if (func_8010FDF8(0x20280) != 0) {
                return;
            }
        }
        break;
    case 4:
        break;
    case 5:
        DecelerateX(FIX(1.0 / 8));
        if (g_Player.timers[8]) {
            if ((g_Player.vram_flag & TOUCHING_CEILING) && !(g_GameTimer & 3)) {
                func_801139CC(0);
            }
            break;
        } else if (g_Player.vram_flag & (TOUCHING_L_WALL | TOUCHING_R_WALL)) {
            if (!(g_Player.vram_flag &
                  (TOUCHING_ANY_SLOPE | TOUCHING_RAISING_SLOPE |
                   VRAM_FLAG_UNK2000 | TOUCHING_SLIGHT_SLOPE |
                   TOUCHING_CEILING_SLOPE | VRAM_FLAG_UNK400 |
                   VRAM_FLAG_UNK200 | VRAM_FLAG_UNK100 | TOUCHING_CEILING |
                   TOUCHING_GROUND))) {
                PLAYER.velocityY += FIX(12.0 / 128);
                if (PLAYER.velocityY > FIX(7)) {
                    PLAYER.velocityY = FIX(7);
                }
                if (!(g_GameTimer & 3)) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_12, 4), 0);
                }
                break;
            }
        }
        PLAYER.step_s = 1;
        func_80113E68();
        PLAYER.poseTimer = PLAYER.pose = 0;
        break;
    case 14:
        PLAYER.drawFlags |= FLAG_DRAW_ROTATE;
        if (g_Player.timers[8] <= 0) {
            PLAYER.drawFlags &= ~FLAG_DRAW_ROTATE;
            PLAYER.rotate = 0x800;
            PLAYER.velocityX = -(PLAYER.velocityX / 2);
            PLAYER.velocityY = 0;
            SetPlayerAnim(0x1C);
            PLAYER.step_s = 1;
            PLAYER.step = 4;
            g_Player.unk44 = 0;
        }
        break;
    case 6:
    case 7:
        DecelerateX(FIX(1.0 / 8));
        if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
            func_8010E7AC();
        }
        if (PLAYER.poseTimer < 0) {
            if (PLAYER.step_s == 6) {
                func_8010E570(0);
            } else {
                func_8010E470(0, PLAYER.velocityX);
            }
        }
        break;
    }
    if (step_sIsZero && (g_Player.unk72)) {
        PLAYER.velocityY = 0;
    }
}

// rotation angles
s16 D_800ACF94[] = {
    0x0000, 0x0000, 0x0100, 0x0000, 0xFF00, 0x0000, 0x0100, 0x0000,
    0xFF00, 0xFE00, 0xFF00, 0x0000, 0x0100, 0x0200, 0x0100, 0x0000,
};

void PlayerStepStoned(s32 arg0) {
    s16 animVariant;
    bool newlyPetrified = false;
    s32 yShift = 0;

    switch (PLAYER.step_s) {
    case 0:
        newlyPetrified = true;
        func_80113EE0();
        func_80113F7C();
        PLAYER.velocityY = FIX(-4);
        if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
            PLAYER.velocityY = FIX(-2);
        }
        func_8010E3B8(FIX(-1.25));
        func_80113E68();
        PLAYER.palette = PAL_FLAG(PAL_CC_STONE_EFFECT);
        PlaySfx(SFX_VO_ALU_SILENCE);
        g_Player.timers[2] = 0;
        g_Player.timers[0] = 0;
        g_Player.timers[1] = 0;
        g_Player.unk5E = GetStatusAilmentTimer(STATUS_AILMENT_PETRIFIED, 8);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_47, 3), 0);
        func_8010E168(1, 4);
        PLAYER.step_s = 1;
        break;
    case 1:
        func_8010E168(1, 4);
        PLAYER.palette = PAL_FLAG(PAL_CC_STONE_EFFECT);
        if (func_8010FDF8(0x20280) != 0) {
            PLAYER.step = Player_StatusStone;
            PLAYER.velocityX = PLAYER.velocityY = 0;
            func_80102CD8(1);
            PlaySfx(SFX_WALL_DEBRIS_B);
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_39, 0);

            animVariant = rand() % 64;

            if (g_Status.hp == 0) {
                D_80137FE0 = 0x20;
                animVariant = 2;
            }
            if (animVariant) {
                animVariant &= 1;
                PLAYER.palette = PAL_FLAG(PAL_UNK_19E) + animVariant;
                SetPlayerAnim(0x38 + animVariant);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_16, 3), 0);
            } else {
                PLAYER.palette = PAL_FLAG(PAL_UNK_19E);
                SetPlayerAnim(0x3A);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_29, 7), 0);
            }
            PLAYER.step_s = 2;
        }
        break;
    case 2:
        yShift = FIX(44.0 / 256);
        if (D_80097448[0] > 0x28) {
            yShift = yShift / 4;
        }

        if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
            PLAYER.velocityY += yShift;
            if (PLAYER.velocityY > FIX(7)) {
                PLAYER.velocityY = FIX(7);
            }
            func_8010E168(1, 4);
            break;
        }

        if (!(g_Player.unk04 & 1)) {
            func_80102CD8(1);
            PlaySfx(SFX_WALL_DEBRIS_B);
        }

        PLAYER.velocityY = 0;
        if (g_Status.hp == 0) {
            if (--D_80137FE0 == 0) {
                PLAYER.step = Player_Kill;
                PlaySfx(SFX_VO_ALU_DEATH);
                PLAYER.step_s = 16;
            }
            func_8010E168(1, 4);
            break;
        }
        // Handles wiggling out of being petrified.
        if (g_Player.padTapped & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT) ||
            arg0 != 0 || D_800ACE44 != 0) {
            g_Player.padTapped |= (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
            // Counter for how many wiggles left until we're out
            g_Player.unk5E--;
            PLAYER.poseTimer = 0x10;
            PlaySfx(SFX_STONE_MOVE_B);
            if (g_Player.unk5E <= 0) {
                SetPlayerAnim(0x3B);
                if (PLAYER.ext.player.anim != 0x3A) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_16, 3), 0);
                } else {
                    CreateEntFactoryFromEntity(g_CurrentEntity, BP_32, 0);
                }
                PlaySfx(SFX_VO_ALU_PAIN_A);
                PLAYER.step = Player_Hit;
                PLAYER.step_s = 6;
                PLAYER.palette = PAL_FLAG(PAL_ALUCARD);
                break;
            }
            func_8010E168(1, 0x1C);
            PLAYER.step_s = 3;
            if (PLAYER.ext.player.anim != 0x3A) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_13, 3), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_31, 3), 0);
            } else {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_13, 8), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_30, 7), 0);
            }
        }
        PLAYER.palette = ((PLAYER.ext.player.anim - 0x38) & 1) + 0x7FFF + 0x19F;
        break;
    case 3:
        if (PLAYER.poseTimer < 0) {
            PLAYER.step_s = 2;
            PLAYER.drawFlags &=
                (FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40 |
                 FLAG_BLINK | FLAG_DRAW_OPACITY | FLAG_DRAW_SCALEY |
                 FLAG_DRAW_SCALEX);
        } else {
            PLAYER.rotPivotX = 0;
            PLAYER.drawFlags |= FLAG_DRAW_ROTATE;
            PLAYER.rotate = D_800ACF94[PLAYER.poseTimer] >> 4;
            if (PLAYER.rotate) {
                PLAYER.rotPivotY = 0x14;
            } else {
                PLAYER.rotPivotY = 0x18;
            }
        }
        break;
    }
    if (PLAYER.ext.player.anim == 0x3A) {
        func_8010E168(1, 4);
    }
    if (newlyPetrified && g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

// Somewhat weird args, worth more study. arg2 is unused.
void PlayerStepKill(DamageParam* damage, s16 arg_PlayerStep, s16 arg2) {
    s32 i;
    s32 j;
    Entity* ent;

    u8* s2;
    u8* data;
    bool nullifyVelY;
    PlayerDraw* plDraw;

    nullifyVelY = false;
    PLAYER.drawFlags = DRAW_COLORS;
    plDraw = &g_PlayerDraw[0];
    if ((g_unkGraphicsStruct.unk20 == 0xFFF) && (PLAYER.step_s)) {
        SetPlayerStep(Player_Unk17);
        PLAYER.velocityX = PLAYER.velocityY = 0;
        return;
    }
    switch (PLAYER.step_s) {
    case 0:
        nullifyVelY = true;
        PLAYER.velocityX = PLAYER.velocityY = 0;
        if (arg_PlayerStep == Player_StatusStone) {
            ent = &g_Entities[16];
            for (j = 16; j < 64; j++, ent++) {
                // Entity 32 appears to be EntityPlayerDissolves
                if (ent->entityId == 32) {
                    PlaySfx(SFX_VO_ALU_DEATH);
                    PLAYER.step_s = 16;
                    return;
                }
            }
        }
        PlaySfx(SFX_VO_ALU_DEATH);
        func_80113EE0();
        func_80113F7C();
        PLAYER.velocityY = FIX(-3.25);
        func_8010E3B8(FIX(-1.25));
        PLAYER.ext.player.anim = 0xC0;
        PLAYER.rotate = 0;
        PLAYER.rotPivotY = 0;
        PLAYER.rotPivotX = 0;
        if (damage->effects & ELEMENT_FIRE) {
            func_80118C28(3);
            // Blueprint 44 has child 11, EntityPlayerBlinkWhite
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x4F),
                0); // Blueprint 51 has child 16, func_8011EDA8
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_51, 2), 0);
            D_80137FEC = 1;
        } else if (damage->effects & ELEMENT_THUNDER) {
            func_80118C28(9);
            // Blueprint 44 has child 11, EntityPlayerBlinkWhite
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x59), 0);
            // Blueprint 45 has child 30, EntityHitByLightning
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_45, 1), 0);
            D_80137FEC = 2;
        } else if (damage->effects & ELEMENT_ICE) {
            func_80118C28(10);
            // Blueprint 44 has child 11, EntityPlayerBlinkWhite
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x5A), 0);
            // Blueprint 46 has child 33, EntityHitByIce
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_HIT_BY_ICE, 0);
            D_80137FEC = 3;
            PLAYER.drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        } else {
            func_80118C28(1);
            // Blueprint 44 has child 11, EntityPlayerBlinkWhite
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x53), 0);
            // Blueprint 49 has child 5, func_8011E4BC
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_49, 5), 0);
            D_80137FEC = 0;
        }
        plDraw->r0 = plDraw->g0 = plDraw->b0 = plDraw->r1 = plDraw->g1 =
            plDraw->b1 = plDraw->r2 = plDraw->g2 = plDraw->b2 = plDraw->r3 =
                plDraw->g3 = plDraw->b3 = 0x80;
        plDraw->enableColorBlend = 1;
        PLAYER.step_s++;
        break;
    case 1:
        if (D_80137FEC == 0) {
            if (plDraw->r0 < 0xF8) {
                plDraw->r0++;
            }
            if (plDraw->b0 > 8) {
                plDraw->b0--;
            }

            plDraw->r3 = plDraw->r2 = plDraw->r1 = plDraw->r0;
            plDraw->g0 = plDraw->g1 = plDraw->b1 = plDraw->g2 = plDraw->b2 =
                plDraw->g3 = plDraw->b3 = plDraw->b0;
        }
        if (D_80137FEC == 1 || D_80137FEC == 2) {
            if (plDraw->b0 > 8) {
                plDraw->b0--;
            }
            plDraw->r3 = plDraw->r2 = plDraw->r1 = plDraw->r0 = plDraw->g0 =
                plDraw->g1 = plDraw->b1 = plDraw->g2 = plDraw->b2 = plDraw->g3 =
                    plDraw->b3 = plDraw->b0;
        }
        if (D_80137FEC == 3) {
            if (plDraw->r0 < 0xF8) {
                plDraw->r0--;
            }
            plDraw->r3 = plDraw->r2 = plDraw->r1 = plDraw->g3 = plDraw->g2 =
                plDraw->g1 = plDraw->g0 = plDraw->r0;
            if (plDraw->b0 < 0xF8) {
                plDraw->b0++;
            }
            plDraw->b3 = plDraw->b2 = plDraw->b1 = plDraw->b0;
        }
        PLAYER.velocityY += FIX(11.0 / 128);
        if (PLAYER.velocityY > FIX(1.0 / 4)) {
            PLAYER.velocityY = FIX(1.0 / 16);
        }
        if (PLAYER.poseTimer < 0) {
            StoreImage(&D_800AE130, (u_long*)&D_80139A7C);
            D_80137FE4 = 0;
            D_80137FE8 = 0x40;
            PLAYER.step_s++;
        }
        break;
    case 2:
        for (i = 0; i < 4; i++) {
            s2 = data = (u8*)&D_80139A7C[0];
            s2 += ((D_80137FE4 >> 1) & 7);
            s2 += ((D_80137FE4 & 0xFF) >> 4) << 6;
            for (j = 0; j < 0x28; j++) {
                if (D_80137FE4 & 1) {
                    *(s2 + ((j & 7) * 8) + ((j >> 3) * 0x400)) &= 0xF0;
                } else {
                    *(s2 + ((j & 7) * 8) + ((j >> 3) * 0x400)) &= 0x0F;
                }
            }
            D_80137FE4 += 0x23;
            D_80137FE4 &= 0xFF;
        }
        LoadImage(&D_800AE130, (u_long*)data);
        if (--D_80137FE8 == 0) {
            PLAYER.velocityY = 0;
            plDraw->enableColorBlend = 0;
            PLAYER.step_s = 0x80;
        }
        break;
    case 16:
        D_80137FF0 = 0x50;
        PLAYER.step_s++;
        break;
    case 17:
        g_Player.unk5E = 5;
        if (D_80137FF0 % 16 == 7) {
            g_Player.padTapped = PAD_UP;
            PlaySfx(SFX_STONE_MOVE_B);
        }
        if (--D_80137FF0 == 0) {
            D_800AFC50[0].pose |= PLAYER.animCurFrame;
            PLAYER.palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
            SetPlayerAnim(0x3E);
            // Blueprint 16 has child 2, EntitySmokePuff
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_16, 3), 0);
            PLAYER.step_s++;
        }
        break;
    case 18:
        if (PLAYER.poseTimer < 0) {
            plDraw->enableColorBlend = 0;
            g_CurrentEntity->step_s = 0x80;
        }
        break;
    case 0x80:
        break;
    }
    DecelerateX(FIX(1.0 / 64));
    if (PLAYER.pose >= 15) {
        if ((PLAYER.pose == 22) && (PLAYER.poseTimer == 1)) {
            PLAYER.rotate -= 0x100;
        }
        PLAYER.rotate -= 6;
        if (PLAYER.rotate < -0x280) {
            PLAYER.rotate = -0x280;
        }
    }
    if (nullifyVelY && (g_Player.unk72)) {
        PLAYER.velocityY = 0;
    }
}

void PlayerStepUnk17(void) {
    PLAYER.drawFlags = FLAG_DRAW_ROTATE;
    PLAYER.velocityX = PLAYER.velocityY = 0;
    PLAYER.poseTimer = 4;

    if (g_unkGraphicsStruct.unk20 == 0) {
        if (g_Player.vram_flag & TOUCHING_GROUND) {
            func_8010E570(0);
        } else {
            func_8010E7AC();
        }
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x4a), 0);
        g_PlayerDraw->enableColorBlend = 0;
    }
}

// same as RIC/func_8015BB80
static void func_80115C50(void) {
    if (g_StageId == STAGE_TOP) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX) - 8000 > 0) {
            PLAYER.posX.i.hi--;
        }

        if (abs((g_Tilemap.left << 8) + g_PlayerX) - 8000 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
    if (g_StageId == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX) - 8384 > 0) {
            PLAYER.posX.i.hi--;
        }

        if (abs((g_Tilemap.left << 8) + g_PlayerX) - 8384 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}

// Corresponding RIC function is RicStepTeleport
void PlayerStepTeleport(void) {
    Entity* newEnt;

    PLAYER.velocityX = PLAYER.velocityY = 0;
    g_Player.padSim = 0;
#if defined(VERSION_PSP)
    g_pads[0].pressed = g_pads[0].tapped = 0;
#endif
    g_Player.demo_timer = 4;

    switch (PLAYER.step_s) {
    case 0:
        if (PLAYER.pose == 8 && PLAYER.poseTimer == 1) {
            newEnt = CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 0), 0);
            if (newEnt == NULL) {
                PLAYER.poseTimer = 2;
            }
        }
#if !defined(VERSION_PSP)
        if (PLAYER.poseTimer < 0) {
            func_8010E570(0);
        }
#endif
        break;
    case 1:
        if (PLAYER.poseTimer < 0) {
            func_8010E570(0);
        }
        if (g_Player.warp_flag) {
            func_8010E570(0);
        }
        break;
    case 2:
        func_80115C50();
        if (PLAYER.pose == 8 && PLAYER.poseTimer == 1) {
            newEnt = CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 2), 0);
            if (newEnt == NULL) {
                PLAYER.poseTimer = 2;
            }
        }
#if !defined(VERSION_PSP)
        if (PLAYER.poseTimer < 0) {
            func_8010E570(0);
        }
#endif
        break;
    case 3:
        if (PLAYER.poseTimer < 0) {
            func_8010E570(0);
        }
        if (g_Player.warp_flag) {
            func_8010E570(0);
        }
        break;
    case 4:
        func_80115C50();
        if (PLAYER.pose == 8 && PLAYER.poseTimer == 1) {
            newEnt = CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 4), 0);
            if (newEnt == NULL) {
                PLAYER.poseTimer = 2;
            }
        }
#if !defined(VERSION_PSP)
        if (PLAYER.poseTimer < 0) {
            func_8010E570(0);
        }
#endif
        break;
    case 5:
        if (PLAYER.poseTimer < 0) {
            func_8010E570(0);
        }
        if (g_Player.warp_flag) {
            func_8010E570(0);
        }
        break;
    }
}

void PlayerStepKillWater(void) {
    PlayerDraw* plDraw;
    bool var_s2;

    var_s2 = false;
    PLAYER.drawFlags = FLAG_DRAW_ROTATE;
    plDraw = g_PlayerDraw;
    if (g_unkGraphicsStruct.unk20 == 0xFFF && PLAYER.step_s) {
        SetPlayerStep(Player_Unk17);
        PLAYER.velocityX = PLAYER.velocityY = 0;
        return;
    }

    switch (PLAYER.step_s) {
    case 0:
        var_s2 = true;
        PLAYER.velocityX = PLAYER.velocityY = 0;
        PlaySfx(SFX_VO_ALU_DEATH);
        func_80113EE0();
        PLAYER.velocityY = FIX(-1.625);
        PLAYER.ext.player.anim = 0xC1;
        PLAYER.drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        PLAYER.rotate = 0x200;
        func_80118C28(1);
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x59), 0);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_49, 6), 0);
        // Sets as RBG, not RGB.
        plDraw->r0 = plDraw->g0 = plDraw->b0 = plDraw->r1 = plDraw->g1 =
            plDraw->b1 = plDraw->r2 = plDraw->g2 = plDraw->b2 = plDraw->r3 =
                plDraw->g3 = plDraw->b3 = 128;
        plDraw->enableColorBlend = true;
        PLAYER.step_s++;
        break;
    case 1:
        if (plDraw->b0 < 0xF8) {
            plDraw->b0++;
        }
        if (plDraw->r0 > 8) {
            plDraw->r0--;
        }
        plDraw->b3 = plDraw->b2 = plDraw->b1 = plDraw->b0;
        plDraw->g0 = plDraw->g1 = plDraw->r1 = plDraw->g2 = plDraw->r2 =
            plDraw->g3 = plDraw->r3 = plDraw->r0;
        PLAYER.velocityY += FIX(1.0 / 16);
        // Interesting, this isn't a normal capping function.
        // If we get going fast enough, it drops our speed, rather than holding
        if (PLAYER.velocityY > FIX(1.0 / 4)) {
            PLAYER.velocityY = FIX(1.0 / 16);
        }
        if (PLAYER.poseTimer < 0) {
            StoreImage(&D_800AE130, D_80139A7C);
            D_80137FE4 = 0;
            D_80137FE8 = 0x40;
            PLAYER.step = 0x10;
            g_CurrentEntity->step_s++;
        }
        break;
    }

    if (var_s2 && g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

void PlayerStepBossGrab(void) {
    DamageParam damage;
    s32 temp_s0;

    switch (g_CurrentEntity->step_s) {
    case 0:
        func_80113EE0();
        if (g_Player.unk62 == 0) {
            PLAYER.ext.player.anim = 0x37;
            g_Player.timers[2] = 8;
            g_Player.unk40 = 0x8166;
            PlaySfx(SFX_VO_ALU_PAIN_E);
        }
        PLAYER.velocityX = PLAYER.velocityY = 0;
        PLAYER.step_s = 1;
        g_Player.unk60 = 2;
        return;
    case 1:
        if (g_Player.unk60 == 3) {
            temp_s0 = HandleDamage(&damage, DAMAGEKIND_2, g_Player.unk64, 1);
            CreateHPNumMove(damage.damageTaken, 0);
            if (temp_s0 == 4) {
                SetPlayerStep(Player_Kill);
                PlayerStepKill(&damage, Player_BossGrab, 1);
                return;
            }
            if (g_Player.unk62 == 0) {
                g_Player.timers[2] = 4;
                g_Player.unk40 = 0x8166;
                PlaySfx(SFX_VO_ALU_PAIN_A);
            }
            if (g_Player.unk62 == 2) {
                g_Player.timers[2] = 4;
                g_Player.unk40 = 0x8161;
            }
            g_Player.unk60 = 2;
            return;
        }
        if (g_Player.unk60 == 4) {
            PLAYER.step = Player_Hit;
            PLAYER.step_s = 0xF;
            g_Player.unk60 = 0;
            SetPlayerAnim(0x2E);
            g_Player.damageTaken = g_Player.unk64;
            PlaySfx(SFX_VO_ALU_YELL);
            return;
        }
        if (g_Player.unk60 == 0) {
            PLAYER.step = Player_Hit;
            PLAYER.step_s = 1;
            return;
        }
    }
}

void PlayerStepHellfire(void) {
    // Whether we should run the last 3 function calls at the end
    s16 runFinishingBlock = 0;
    switch (PLAYER.step_s) {
    case 0:
        if (CreateEntFactoryFromEntity(g_CurrentEntity, BP_HELLFIRE, 0) ==
            NULL) {
            func_8010E570(0);
        }
        SetPlayerAnim(1);
        PLAYER.step_s++;
        break;
    case 1:
        if (g_Player.unk5C == 1) {
            PLAYER.step_s++;
        }
        break;
    case 2:
        PLAYER.velocityX = 0;
        if (CheckMoveDirection() != 0) {
            if (g_Player.padPressed & PAD_RIGHT) {
                if ((g_Player.colFloor[2].effects &
                     (EFFECT_UNK_8000 + EFFECT_SOLID)) ||
                    (g_Player.colFloor[1].effects & EFFECT_UNK_8000) ||
                    (PLAYER.posX.i.hi > 248)) {
                    SetSpeedX(FIX(3));
                }
            } else if ((g_Player.colFloor[3].effects &
                        (EFFECT_UNK_8000 + EFFECT_SOLID)) ||
                       (g_Player.colFloor[1].effects & EFFECT_UNK_8000) ||
                       (PLAYER.posX.i.hi < 8)) {
                SetSpeedX(FIX(3));
            }
        }
        if (g_Player.unk5C == 2) {
            PLAYER.velocityX = 0;
            SetPlayerAnim(0x3D);
            PLAYER.step_s++;
        }
        break;
    case 3:
        CheckMoveDirection();
        if (g_Player.unk5C == 3) {
            SetPlayerAnim(0x3C);
            PLAYER.step_s += 1;
            // In Hellfire, if you press down, it cancels the spell
            if (g_Player.padPressed & PAD_DOWN) {
                runFinishingBlock = 1;
            }
        }
        break;
    case 4:
        if (PLAYER.pose == 10 && PLAYER.poseTimer == 1) {
            g_Player.timers[12] = 4;
            // Make factory with blueprint 37. This creates entity with ID 28,
            // which is EntityExpandingCircle.
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_37, 0);
        }
        if (PLAYER.poseTimer < 0) {
            runFinishingBlock = 1;
        }
        break;
    }
    // Not sure why this cast to u16 is needed but it is
    if (((u16)runFinishingBlock) || (g_Player.unk5C == 0xFFFF)) {
        func_8010E570(0);
        SetPlayerAnim(0x3D);
        func_80111CC0();
    }
}

void PlayerStepUnk48(void) {
    switch (PLAYER.step_s) {
    case 0:
        func_80113EE0();
        g_Player.unk40 = 0x8166;
        g_Player.timers[2] = 6;
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
        PLAYER.ext.player.anim = 0x33;
        CreateEntFactoryFromEntity(g_CurrentEntity, BP_0, 0);
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x58), 0);
        PLAYER.step_s++;
        break;
    case 1:
        if (PLAYER.poseTimer < 0) {
            PlaySfx(SFX_VO_ALU_WHAT);
            func_8010E570(0);
        }
        break;
    }
}

void PlayerStepUnk49(void) {
    PLAYER.velocityX = PLAYER.velocityY = 0;
    if ((g_Player.padSim >> 16) != 2) {
        func_8010E570(0);
    }
}

void PlayerStepUnk50(void) {
    PLAYER.velocityX = PLAYER.velocityY = 0;
    if ((g_Player.padSim >> 16) != 2) {
        PLAYER.step = Player_AxearmorStand;
        PLAYER.step_s = 0;
        PLAYER.velocityX = PLAYER.velocityY = 0;
        PLAYER.ext.player.anim = 0xCF;
        PLAYER.poseTimer = PLAYER.pose = 0;
    }
}

bool BatFormFinished(void) {
    if (PLAYER.step_s == 0) {
        return false;
    }
    if (D_80097448[1] || g_Player.padTapped & PAD_R1 ||
        HandleTransformationMP(FORM_BAT, REDUCE) < 0) {
        SetPlayerStep(Player_UnmorphBat);
        SetPlayerAnim(0xCA);
        D_800AFDA4[0].pose = 6;
        PLAYER.palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
        g_Player.unk66 = 0;
        g_Player.unk68 = 0;
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x21), 0);
        PLAYER.velocityY >>= 1;
        return true;
    }
    return false;
}

static void func_8011690C(s16 arg0) {
    if (PLAYER.rotate < arg0) {
        PLAYER.rotate += 16;
        if (PLAYER.rotate > arg0) {
            PLAYER.rotate = arg0;
        }
    }
    if (PLAYER.rotate > arg0) {
        PLAYER.rotate -= 16;
        if (PLAYER.rotate < arg0) {
            PLAYER.rotate = arg0;
        }
    }
}

extern s32 g_WingSmashButtonCounter;
extern s32 g_WingSmashButtonTimer;
extern s32 g_WingSmashTimer;
extern s32 g_BatScreechDone;

s32 CheckWingSmashInput(void) {
    u32 directionsPressed;

    s32 down;
    s32 up;
    s32 forward;
    s32 backward;

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    up = PAD_UP;
    down = PAD_DOWN;
    if (PLAYER.facingLeft) {
        forward = PAD_LEFT;
        backward = PAD_RIGHT;
    } else {
        backward = PAD_LEFT;
        forward = PAD_RIGHT;
    }
    // Counter tells us how many correct buttons have been given in the
    // sequence. In each case, if we aren't pressing the right buttons, we
    // decrement the timer If the timer expires, progress gets wiped. Otherwise
    // we register the correct button by incrementing counter and resetting
    // timer to 20 frames.
    switch (g_WingSmashButtonCounter) {
    case 0:
        if (directionsPressed == up) {
            g_WingSmashButtonCounter++;
            g_WingSmashButtonTimer = 0x14;
            break;
        }
        if (--g_WingSmashButtonTimer == 0) {
            g_WingSmashButtonCounter = 0;
        }
        break;
    case 1:
        if (directionsPressed == (backward + up)) {
            g_WingSmashButtonCounter++;
            g_WingSmashButtonTimer = 0x14;
            break;
        }
        if (--g_WingSmashButtonTimer == 0) {
            g_WingSmashButtonCounter = 0;
        }
        break;
    case 2:
        if (directionsPressed == backward) {
            g_WingSmashButtonCounter++;
            g_WingSmashButtonTimer = 0x14;
            break;
        }
        if (--g_WingSmashButtonTimer == 0) {
            g_WingSmashButtonCounter = 0;
        }
        break;
    case 3:
        if (directionsPressed == (down + backward)) {
            g_WingSmashButtonCounter++;
            g_WingSmashButtonTimer = 0x14;
            break;
        }
        if (--g_WingSmashButtonTimer == 0) {
            g_WingSmashButtonCounter = 0;
        }
        break;
    case 4:
        if (directionsPressed == down) {
            g_WingSmashButtonCounter++;
            g_WingSmashButtonTimer = 0x14;
            break;
        }
        if (--g_WingSmashButtonTimer == 0) {
            g_WingSmashButtonCounter = 0;
        }
        break;
    case 5:
        if (directionsPressed == (down + forward)) {
            g_WingSmashButtonCounter++;
            g_WingSmashButtonTimer = 0x14;
            break;
        }
        if (--g_WingSmashButtonTimer == 0) {
            g_WingSmashButtonCounter = 0;
        }
        break;
    case 6:
        if (directionsPressed == forward) {
            g_WingSmashButtonCounter++;
            g_WingSmashButtonTimer = 0x14;
            break;
        }
        if (--g_WingSmashButtonTimer == 0) {
            g_WingSmashButtonCounter = 0;
        }
        break;
    case 7: // All buttons are in, nothing more to test for.
        if (--g_WingSmashButtonTimer == 0) {
            g_WingSmashButtonCounter = 0;
        }
    }
    // If we're not pressing cross (and we haven't put in all the buttons)
    // then all progress is lost.
    if (!(g_Player.padPressed & PAD_CROSS) && (g_WingSmashButtonCounter != 7)) {
        g_WingSmashButtonCounter = 0;
    }
    // And then we return whether or not we pulled off a wing smash.
    if (g_WingSmashButtonCounter == 7) {
        return true;
    }
    return false;
}

void ControlBatForm(void) {
    Entity* newEntity;
    s32 pressingCross;
    // When we initially move left/right, bat makes a screech sound.
    s32 screechDone;
    s16 x_offset;
    u32 directionsPressed;

    screechDone = 0;
    if (BatFormFinished()) {
        return;
    }

    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    pressingCross = g_Player.padPressed & PAD_CROSS;
    PLAYER.drawFlags = FLAG_DRAW_ROTATE;
    PLAYER.rotPivotY = 0;

#if defined(VERSION_HD)
    if (PLAYER.step_s != 3) {
#else
    // Just to make the curly brackets match at the end of this block
    if (1) {
#endif
        if (CheckWingSmashInput() && (!pressingCross) && (PLAYER.step_s) &&
            CastSpell(SPELL_WING_SMASH)) {
            LearnSpell(SPELL_WING_SMASH);
            SetPlayerAnim(0xC6);
            SetSpeedX(FIX(6));
            PLAYER.step_s = 3;
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x5c), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_67, 0);
            g_WingSmashTimer = 0x40;
#if !defined(VERSION_HD)
            g_WingSmashButtonCounter = 0;
#endif
        } else if ((g_Player.padTapped & PAD_TRIANGLE) &&
                   (PLAYER.step_s == 1 || PLAYER.step_s == 2) &&
                   (IsRelicActive(RELIC_ECHO_OF_BAT))) {
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_BAT_ECHO, 0);
        } else if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
                   (PLAYER.step_s == 1 || PLAYER.step_s == 2) &&
                   (IsRelicActive(RELIC_FIRE_OF_BAT)) && (CastSpell(9))) {
            SetPlayerAnim(0xC9);
            PLAYER.step_s = 4;
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 5), 0);
        }
    }

    switch (PLAYER.step_s) {
    case 0:
        g_WingSmashButtonCounter = 0;
        PLAYER.rotate = 0;
        g_Player.unk44 = g_Player.unk46 = g_Player.unk48 = 0;
        if (g_Entities[16].entityId == 0x22) {
            PLAYER.unk5A = 0;
            PLAYER.animSet = 13;
            D_800AFDA4[0].pose = 6;
            PLAYER.ext.player.anim = 0xCA;
            if (!func_8011203C()) {
                return;
            }
        } else {
            if (g_Player.unk66 == 0) {
                newEntity = CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x20), 0);
#if !defined(VERSION_HD)
                if (newEntity == NULL) {
                    return;
                }
#endif
                func_8010FAF4();
                g_Player.unk66++;
            }
            DecelerateX(0x480);
            DecelerateY(0x480);
            if (abs(PLAYER.velocityY) > FIX(1.25)) {
                if (PLAYER.velocityY > 0) {
                    PLAYER.velocityY = FIX(1.25);
                } else {
                    PLAYER.velocityY = FIX(-1.25);
                }
            }
            SetPlayerAnim(0xCA);
            D_800AFDA4[0].pose = PLAYER.animCurFrame;
            PLAYER.palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
            if (g_Player.unk66 == 1) {
                return;
            }
            if (g_Player.unk66 == 2) {
                PLAYER.unk5A = 0;
                PLAYER.animSet = 0xD;
                D_800AFDA4[0].pose = 6;
                return;
            }
        }
        SetPlayerAnim(0xC3);
        PLAYER.poseTimer = 1;
        PLAYER.pose = 2;
        PLAYER.palette = PAL_FLAG(PAL_ALUCARD);
        CheckMoveDirection();
        PLAYER.step_s++;
        break;
    case 1:
        if (directionsPressed && !pressingCross) {
            if (PLAYER.ext.player.anim == 0xC3) {
                PLAYER.pose /= 3;
            }
            PLAYER.step_s++;
        } else {
            func_8011690C(0);
            DecelerateX(0x1200);
            DecelerateY(0x1200);
            break;
        }
    case 2:
        // If you're pressing cross, you can't move and inputs are ignored.
        if (pressingCross) {
            directionsPressed = 0;
        }
        switch (directionsPressed) {
        case 0:
        default:
            SetPlayerAnim(0xC3);
            PLAYER.step_s = 1;
            break;
        case PAD_UP:
            PLAYER.ext.player.anim = 0xC2;
            if (PLAYER.velocityY < FIX(-1.25)) {
                DecelerateY(0x1200);
            } else {
                PLAYER.velocityY = FIX(-1.25);
            }
            func_8011690C(-0x80);
            DecelerateX(0x1200);
            break;
        case PAD_DOWN:
            if (g_Player.vram_flag & TOUCHING_GROUND) {
                PLAYER.ext.player.anim = 0xC4;
            } else {
                PLAYER.ext.player.anim = 0xC5;
            }
            if (PLAYER.velocityY > FIX(1.25)) {
                DecelerateY(0x1200);
            } else {
                PLAYER.velocityY = FIX(1.25);
            }
            func_8011690C(0);
            DecelerateX(0x1200);
            break;
        case PAD_RIGHT:
            PLAYER.ext.player.anim = 0xC2;
            PLAYER.facingLeft = 0;
            func_8011690C(0x180);
            if (PLAYER.velocityX > FIX(1.25)) {
                DecelerateX(0x1200);
            } else {
                PLAYER.velocityX = FIX(1.25);
            }
            DecelerateY(0x1200);
            if (!g_BatScreechDone) {
                PlaySfx(SFX_BAT_SCREECH);
            }
            screechDone = 1;
            break;
        case PAD_LEFT:
            PLAYER.ext.player.anim = 0xC2;
            PLAYER.facingLeft = 1;
            func_8011690C(0x180);
            if (PLAYER.velocityX < FIX(-1.25)) {
                DecelerateX(0x1200);
            } else {
                PLAYER.velocityX = FIX(-1.25);
            }
            DecelerateY(0x1200);
            if (!g_BatScreechDone) {
                PlaySfx(SFX_BAT_SCREECH);
            }
            screechDone = 1;
            break;
        case PAD_RIGHT | PAD_UP:
            PLAYER.ext.player.anim = 0xC2;
            PLAYER.facingLeft = 0;
            func_8011690C(0x80);
            if (PLAYER.velocityX > FIX(0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(0.875);
            }
            if (PLAYER.velocityY < FIX(-0.875)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(-0.875);
            }
            break;
        case PAD_LEFT | PAD_UP:
            PLAYER.ext.player.anim = 0xC2;
            PLAYER.facingLeft = 1;
            func_8011690C(0x80);
            if (PLAYER.velocityX < FIX(-0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(-0.875);
            }
            if (PLAYER.velocityY < FIX(-0.875)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(-0.875);
            }
            break;
        case PAD_RIGHT | PAD_DOWN:
            if (g_Player.vram_flag & TOUCHING_GROUND) {
                PLAYER.ext.player.anim = 0xC4;
            } else {
                PLAYER.ext.player.anim = 0xC5;
            }
            PLAYER.facingLeft = 0;
            func_8011690C(0);
            if (PLAYER.velocityX > FIX(0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(0.875);
            }
            if (PLAYER.velocityY > FIX(1.75)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(1.75);
            }
            break;
        case PAD_LEFT | PAD_DOWN:
            if (g_Player.vram_flag & TOUCHING_GROUND) {
                PLAYER.ext.player.anim = 0xC4;
            } else {
                PLAYER.ext.player.anim = 0xC5;
            }
            PLAYER.facingLeft = 1;
            func_8011690C(0);
            if (PLAYER.velocityX < FIX(-0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(-0.875);
            }
            if (PLAYER.velocityY > FIX(1.75)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(1.75);
            }
            break;
        }
        break;
    case 3:
        if (!PLAYER.facingLeft && (g_Player.vram_flag & TOUCHING_R_WALL) ||
            PLAYER.facingLeft && (g_Player.vram_flag & TOUCHING_L_WALL)) {
            g_Player.padTapped = PAD_R1;
            BatFormFinished();
            func_80102CD8(2);
            PlaySfx(SFX_WALL_DEBRIS_B);
            PLAYER.velocityX = 0;
            g_Player.demo_timer = 32;
            g_Player.padSim = 0;
            break;
        }
        // When wing smash ends, force an un-transform
        if (--g_WingSmashTimer == 0) {
            g_Player.padTapped = PAD_R1;
            BatFormFinished();
            g_Player.demo_timer = 32;
            g_Player.padSim = 0;
        } else {
            if (directionsPressed & PAD_UP) {
                PLAYER.velocityY -= FIX(0.125);
                func_8011690C(0x80);
            }
            if (directionsPressed & PAD_DOWN) {
                PLAYER.velocityY += FIX(0.125);
            }
            if (!(directionsPressed & PAD_UP)) {
                func_8011690C(0x180);
            }
            if (!(directionsPressed & (PAD_DOWN | PAD_UP))) {
                DecelerateY(FIX(0.125));
            }
            if (g_Player.vram_flag & TOUCHING_CEILING_SLOPE) {
                if (PLAYER.facingLeft &&
                        (g_Player.vram_flag & VRAM_FLAG_UNK400) ||
                    !PLAYER.facingLeft &&
                        !(g_Player.vram_flag & VRAM_FLAG_UNK400)) {
                    PLAYER.velocityY = FIX(6);
                }
            }
            if (g_Player.vram_flag & TOUCHING_ANY_SLOPE) {
                if (PLAYER.facingLeft &&
                        (g_Player.vram_flag & TOUCHING_RAISING_SLOPE) ||
                    !PLAYER.facingLeft &&
                        !(g_Player.vram_flag & TOUCHING_RAISING_SLOPE)) {
                    PLAYER.velocityY = FIX(-6);
                }
            }
            if (PLAYER.velocityY < FIX(-6)) {
                PLAYER.velocityY = FIX(-6);
            }
            if (PLAYER.velocityY > FIX(6)) {
                PLAYER.velocityY = FIX(6);
            }
            if (g_GameTimer % 3 == 0) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_WING_SMASH_TRAIL, 0);
                if (g_Player.vram_flag & TOUCHING_GROUND) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_69, 9), 0);
                }
                if (g_Player.vram_flag & TOUCHING_CEILING) {
                    x_offset = 3;
                    if (PLAYER.facingLeft) {
                        x_offset = -x_offset;
                    }
                    PLAYER.posY.i.hi -= 8;
                    PLAYER.posX.i.hi += x_offset;
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_4, 1), 0);
                    PLAYER.posY.i.hi += 8;
                    PLAYER.posX.i.hi -= x_offset;
                }
            }
        }
        break;
    // Happens when shooting fireball with Fire of Bat
    case 4:
        DecelerateX(FIX(12.0 / 128));
        DecelerateY(FIX(28.0 / 128));
        func_8011690C(0x180);
        if (PLAYER.poseTimer < 0) {
            // This actually creates the entity factory to produce the fireball
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_BAT_FIREBALL, 0);
            SetSpeedX(FIX(-1.5));
            func_8011690C(0);
            SetPlayerAnim(0xC3);
            PLAYER.step_s++;
        }
        break;
    // Finishing up on the fireball
    case 5:
        DecelerateX(FIX(12.0 / 128));
        DecelerateY(FIX(28.0 / 128));
        func_8011690C(0);
        if (PLAYER.ext.player.anim == 0xC4 && PLAYER.pose == 8) {
            PLAYER.step_s = 1;
        }
        break;
    }

    if (D_8013AECC != 0) {
        if (PLAYER.velocityX > 0) {
            PLAYER.velocityX = 0;
        }
    }
    if (D_8013AECC != 0) {
        if (D_8013AECC > 0) {
            D_8013AECC--;
            g_CurrentEntity->posY.i.hi++;
        } else {
            D_8013AECC++;
            g_CurrentEntity->posY.i.hi--;
        }
    }
    g_BatScreechDone = screechDone;
}

void PlayerStepUnmorphBat(void) {
    byte pad[0x28];
    s32 i;
    s32 else_cycles;

    PLAYER.drawFlags = FLAG_DRAW_ROTATE;
    DecelerateX(FIX(0.125));
    if (g_Player.vram_flag & (TOUCHING_CEILING | TOUCHING_GROUND)) {
        PLAYER.velocityY = 0;
    }
    DecelerateY(FIX(0.125));
    func_8011690C(0);
    else_cycles = 0;
    switch (PLAYER.step_s) {
    case 0:
        for (i = 0; i < 4; i++) {
            if (g_SensorsFloor[i].y < g_SensorsFloorDefault[i]) {
                g_SensorsFloor[i].y++;
            } else {
                else_cycles++;
            }
            if (g_SensorsCeiling[i].y > g_SensorsCeilingDefault[i]) {
                g_SensorsCeiling[i].y--;
            } else {
                else_cycles++;
            }
            // This means the lower parts only run once!
            if (i != 0) {
                continue;
            }
            if (g_Player.unk68) {
                if (D_8013AECC >= 12) {
                    continue;
                }
                D_8013AECC++;
            } else {
                if (g_Player.vram_flag & TOUCHING_ANY_SLOPE) {
                    PLAYER.posY.i.hi--;
                }
            }
        }

        if ((g_Player.vram_flag & (TOUCHING_CEILING | TOUCHING_GROUND)) ==
            (TOUCHING_CEILING | TOUCHING_GROUND)) {
            g_Player.unk68 = 1;
            PLAYER.velocityX = PLAYER.velocityY = 0;
        }
        if (else_cycles == 8) {
            PLAYER.animSet = 1;
            PLAYER.drawFlags = PLAYER.rotate = 0;
            g_Player.unk66 = 1;
            if (g_Player.unk68) {
                PLAYER.step_s = 2;
                D_800AFDA4[0].pose = 0xC7;
            } else {
                PLAYER.step_s = 1;
                D_800AFDA4[0].pose = 0x5F;
            }
        }
        break;
    case 1:
        if (g_Player.unk66 == 3) {
            func_8010E83C(0);
            PLAYER.posY.i.hi -= 3;
            if (!(g_Player.vram_flag & TOUCHING_ANY_SLOPE)) {
                PLAYER.velocityY = FIX(-1);
            }
            g_Player.unk44 |= 0x100;
            PLAYER.palette = PAL_FLAG(PAL_ALUCARD);
            TRANSFORM_LOCKOUT_TIMER = 0x18;
            func_80111CC0();
        }
        break;
    case 2:
        if (g_Player.unk66 == 3) {
            func_8010E4D0();
        }
        break;
    }
    if (func_80111DE8(0) != 0) {
        PLAYER.velocityX = 0;
    }
}

void PlayerStepStuck(void) {
    Collider collider;
    s32 collisionCount = 0;

    CheckCollision(PLAYER.posX.i.hi, PLAYER.posY.i.hi + 0x19, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        collisionCount++;
    }
    CheckCollision(PLAYER.posX.i.hi + 4, PLAYER.posY.i.hi + 0x19, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        collisionCount++;
    }
    CheckCollision(PLAYER.posX.i.hi - 4, PLAYER.posY.i.hi + 0x19, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        collisionCount++;
    }
    if ((g_Player.vram_flag & (VRAM_FLAG_UNK40 | TOUCHING_GROUND)) ==
        (VRAM_FLAG_UNK40 | TOUCHING_GROUND)) {
        collisionCount++;
    }
    PLAYER.rotate = 0;
    CheckMoveDirection();
    if (collisionCount == 0) {
        func_8010E7AC();
        return;
    }

    switch (PLAYER.step_s) {
    case 0:
        if (PLAYER.poseTimer < 0) {
            SetPlayerAnim(0xF6);
            PLAYER.step_s++;
        }
        break;
    case 1:
        if (g_Player.padTapped & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT)) {
            SetPlayerAnim(0xC8);
            PlaySfx(SFX_VO_ALU_ATTACK_A);
            PLAYER.step_s = 0;
        } else if (g_Player.unk72 == 1) {
            PLAYER.pose = 0;
            PLAYER.poseTimer = 3;
        } else if (g_Player.unk72 == 2) {
            if (PLAYER.pose > 0) {
                PLAYER.pose = 1;
                PLAYER.poseTimer = 3;
            }
        } else if (g_Player.unk72 == 3) {
            if (PLAYER.pose >= 2) {
                PLAYER.pose = 2;
                PLAYER.poseTimer = 3;
                PLAYER.step = 2;
                PLAYER.step_s = 5;
            }
        } else if (g_Player.unk72 == 4) {
            if (PLAYER.pose >= 3) {
                PLAYER.pose = 3;
                PLAYER.poseTimer = 3;
                PLAYER.step = 2;
                PLAYER.step_s = 5;
            }
        }
        break;
    }
}

extern s32 g_MistTimer; // remaining time in mist transformation
extern s32 g_SecondaryMistTimer;
bool MistFormFinished(void) {
    if (PLAYER.step_s == 0) {
        return 0;
    }
#ifndef VERSION_PSP
    if (D_80097448[1] != 0 || g_Player.padTapped & BTN_MIST ||
#else
    if (g_SecondaryMistTimer != 0) {
        g_SecondaryMistTimer--;
    }
    if (D_80097448[1] != 0 ||
        g_SecondaryMistTimer == 0 &&
            ((g_Player.padPressed & BTN_MIST) != BTN_MIST) ||
#endif
        HandleTransformationMP(FORM_MIST, REDUCE) < 0) {
        CheckMoveDirection();
        SetPlayerStep(Player_UnmorphMist);
        return 1;
    }
    if (!IsRelicActive(RELIC_POWER_OF_MIST)) {
        if (g_MistTimer != 0) {
            g_MistTimer--;
        }
        if (g_MistTimer == 0) {
            CheckMoveDirection();
            SetPlayerStep(Player_UnmorphMist);
            return 1;
        }
    }
    return 0;
}

void ControlMistForm(void) {
    s32 xSpeedDiag;
    s32 ySpeedDiag;
    s32 xSpeedOrtho;
    s32 ySpeedOrtho;
    u32 directionsPressed;

    if (!IsRelicActive(RELIC_POWER_OF_MIST)) {
        // Ortho and Diag describe the speeds when moving orthogonally (in a
        // single direction) versus moving diagonally (in two directions at
        // once). Overall speed diagonally is 5/16 * sqrt(2) which is 0.442, so
        // a fair bit slower than orthogonal speed.
        xSpeedOrtho = FIX(0.5);
        ySpeedOrtho = FIX(0.5);
        xSpeedDiag = FIX(5.0 / 16);
        ySpeedDiag = FIX(5.0 / 16);
    } else {
        // With Power of Mist, we move at double speed.
        xSpeedOrtho = FIX(1);
        ySpeedOrtho = FIX(1);
        xSpeedDiag = FIX(10.0 / 16);
        ySpeedDiag = FIX(10.0 / 16);
    }
    if (MistFormFinished()) {
        return;
    }
    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    switch (PLAYER.step_s) {
    case 0:
        func_800EA5E4(0x1BU);
        CheckMoveDirection();
        g_Player.unk44 = g_Player.unk46 = g_Player.unk48 = 0;
        func_8010FAF4();
        CreateEntFactoryFromEntity(g_CurrentEntity, BP_73, 0);
        if (PLAYER.velocityX > 0) {
            PLAYER.velocityX = xSpeedOrtho;
        }
        if (PLAYER.velocityX < 0) {
            PLAYER.velocityX = -xSpeedOrtho;
        }
        if (PLAYER.velocityY > 0) {
            PLAYER.velocityY = ySpeedOrtho;
        }
        if (PLAYER.velocityY < 0) {
            PLAYER.velocityY = -ySpeedOrtho;
        }
        SetPlayerAnim(0xCA);
        D_800AFDA4[0].pose = PLAYER.animCurFrame;
        func_800EA538(8);
        if (!IsRelicActive(RELIC_GAS_CLOUD)) {
            func_800EA5E4(0x11CU);
        } else {
            func_800EA5E4(0x11FU);
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_83, 0);
        }
#if defined(VERSION_PSP)
        g_SecondaryMistTimer = 16;
#endif
        // Note that this means Power of Mist doesn't make mist infinite!
        // It just lasts 100,000 :)
        if (!IsRelicActive(RELIC_POWER_OF_MIST)) {
            g_MistTimer = 16;
        } else {
            g_MistTimer = 100000;
        }
        PLAYER.step_s += 1;
        break;
    case 1:
        switch (directionsPressed) {
        case 0:
        default:
            DecelerateX(FIX(3.0 / 256));
            DecelerateY(FIX(3.0 / 256));
            break;
        case PAD_UP:
            if (PLAYER.velocityY < -ySpeedOrtho) {
                DecelerateY(FIX(3.0 / 256));
            } else {
                PLAYER.velocityY = -ySpeedOrtho;
            }
            DecelerateX(FIX(3.0 / 256));
            break;
        case PAD_DOWN:
            if (ySpeedOrtho < PLAYER.velocityY) {
                DecelerateY(FIX(3.0 / 256));
            } else {
                PLAYER.velocityY = ySpeedOrtho;
            }
            DecelerateX(FIX(3.0 / 256));
            break;
        case PAD_RIGHT:
            PLAYER.facingLeft = 0;
            if (xSpeedOrtho < PLAYER.velocityX) {
                DecelerateX(FIX(3.0 / 256));
            } else {
                PLAYER.velocityX = xSpeedOrtho;
            }
            DecelerateY(FIX(3.0 / 256));
            break;
        case PAD_LEFT:
            PLAYER.facingLeft = 1;
            if (PLAYER.velocityX < -xSpeedOrtho) {
                DecelerateX(FIX(3.0 / 256));
            } else {
                PLAYER.velocityX = -xSpeedOrtho;
            }
            DecelerateY(FIX(3.0 / 256));
            break;
        case PAD_UP + PAD_RIGHT:
            PLAYER.facingLeft = 0;
            if (xSpeedDiag < PLAYER.velocityX) {
                DecelerateX(FIX(2.0 / 256));

            } else {
                PLAYER.velocityX = xSpeedDiag;
            }
            if (PLAYER.velocityY < -ySpeedDiag) {
                DecelerateY(FIX(2.0 / 256));
            } else {
                PLAYER.velocityY = -ySpeedDiag;
            }
            break;
        case PAD_UP + PAD_LEFT:
            PLAYER.facingLeft = 1;
            if (PLAYER.velocityX < -xSpeedDiag) {
                DecelerateX(FIX(2.0 / 256));
            } else {
                PLAYER.velocityX = -xSpeedDiag;
            }
            if (PLAYER.velocityY < -ySpeedDiag) {
                DecelerateY(FIX(2.0 / 256));
            } else {
                PLAYER.velocityY = -ySpeedDiag;
            }
            break;
        case PAD_DOWN + PAD_RIGHT:
            PLAYER.facingLeft = 0;
            if (xSpeedDiag < PLAYER.velocityX) {
                DecelerateX(FIX(2.0 / 256));
            } else {
                PLAYER.velocityX = xSpeedDiag;
            }
            if (ySpeedDiag < PLAYER.velocityY) {
                DecelerateY(FIX(2.0 / 256));
            } else {
                PLAYER.velocityY = ySpeedDiag;
            }
            break;
        case PAD_DOWN + PAD_LEFT:
            PLAYER.facingLeft = 1;
            if (PLAYER.velocityX < -xSpeedDiag) {
                DecelerateX(FIX(2.0 / 256));
            } else {
                PLAYER.velocityX = -xSpeedDiag;
            }
            if (ySpeedDiag < PLAYER.velocityY) {
                DecelerateY(FIX(2.0 / 256));
            } else {
                PLAYER.velocityY = ySpeedDiag;
            }
            break;
        }
        break;
    default:
        FntPrint("error step\n");
        break;
    }
    if (D_8013AECC != 0) {
        if (D_8013AECC > 0) {
            D_8013AECC -= 1;
            PLAYER.posY.i.hi++;
        } else {
            D_8013AECC += 1;
            PLAYER.posY.i.hi--;
        }
    }
}

void PlayerStepUnmorphMist(void) {
    byte pad[0x28];
    s32 i;
    s32 else_cycles;

    if ((g_Player.vram_flag & TOUCHING_GROUND) && (PLAYER.velocityY > 0)) {
        PLAYER.velocityY = 0;
    }
    if ((g_Player.vram_flag & TOUCHING_CEILING) && (PLAYER.velocityY < 0)) {
        PLAYER.velocityY = 0;
    }
    DecelerateX(0x200);
    DecelerateY(0x200);
    else_cycles = 0;
    for (i = 0; i < 4; i++) {
        if (g_SensorsFloor[i].y < g_SensorsFloorDefault[i]) {
            g_SensorsFloor[i].y++;
        } else {
            else_cycles++;
        }
        if (g_SensorsCeiling[i].y > g_SensorsCeilingDefault[i]) {
            g_SensorsCeiling[i].y--;
        } else {
            else_cycles++;
        }
        // This means the lower parts only run once!
        if (i != 0) {
            continue;
        }
        if (PLAYER.step_s) {
            if (D_8013AECC >= 12) {
                continue;
            }
            D_8013AECC++;
        } else {
            if (g_Player.vram_flag & TOUCHING_ANY_SLOPE) {
                PLAYER.posY.i.hi--;
            }
        }
    }
    if ((g_Player.vram_flag & (TOUCHING_CEILING | TOUCHING_GROUND)) ==
        (TOUCHING_CEILING | TOUCHING_GROUND)) {
        PLAYER.step_s = 1;
        PLAYER.velocityX = PLAYER.velocityY = 0;
    }
    if (else_cycles == 8) {
        if (func_80111D24()) {
            return;
        }
        PLAYER.animSet = 1;
        PLAYER.unk5A = 0;
        SetPlayerAnim(0xCB);
        if (PLAYER.step_s) {
            SetPlayerAnim(0xCC);
        }
        if (g_Entities[16].step < 3) {
            g_Entities[16].step = 3;
            return;
        }
        if (g_Entities[16].step == 5) {
            PLAYER.palette = PAL_FLAG(PAL_ALUCARD);
            func_8010FAF4();
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x5b), 0);
            if (PLAYER.step_s) {
                func_8010E4D0();
                return;
            }
            func_8010E83C(0);
            PLAYER.posY.i.hi -= 3;
            if (!(g_Player.vram_flag & TOUCHING_ANY_SLOPE)) {
                PLAYER.velocityY = FIX(-1);
            }
            g_Player.unk44 |= 0x100;
            TRANSFORM_LOCKOUT_TIMER = 0x18;
            func_80111CC0();
        }
    }
    if (func_80111DE8(1) != 0) {
        PLAYER.velocityX = 0;
    }
}

void PlayerStepDarkMetamorphosis(void) {
    if (PLAYER.poseTimer < 0) {
        func_8010E570(0);
    }
}

void PlayerStepSummonSpells(void) {
    if (PLAYER.poseTimer < 0) {
        func_8010E470(0, 0);
    }
}

void PlayerStepSoulSteal(void) {
    if (PLAYER.pose == 7 && PLAYER.poseTimer == 1) {
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIPPLE_OUTLINE, 22), 0);
        PlaySfx(SFX_UI_MP_FULL);
        CreateEntFactoryFromEntity(g_CurrentEntity, BP_112, 0);
    }
    if (PLAYER.poseTimer < 0) {
        func_8010E570(0);
    }
}

extern s32 D_80138008;
void PlayerStepSwordWarp(void) {
    if (PLAYER.step_s == 0) {
        if (g_Entities[E_WEAPON].entityId == E_NONE) {
            D_80138008 = 0x10;
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_61, 0x15), 0);
            PLAYER.step_s++;
        }
    } else if (--D_80138008 == 0) {
        PLAYER.palette = PAL_FLAG(PAL_ALUCARD);
        func_8010E570(0);
    }
}
