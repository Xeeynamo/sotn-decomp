// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

extern PlayerState g_Dop;

// n.b.! this file is the same as bo4/unk_45354.c

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C4954);

void func_8010E0A8(void) {
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk2 = 0;
}

void func_8010E0B8(void) {
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk1 = 0;
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk0 = 0;
}

void func_us_801C4A30(s16 a0, s16 a1) {
    if (g_Dop.timers[ALU_T_INVINCIBLE_CONSUMABLES] <= a1) {
        g_Dop.timers[ALU_T_INVINCIBLE_CONSUMABLES] = a1;
    }
}

#include "../../decelerate.h"

s32 CheckMoveDirection(void) {
    if (g_Dop.unk44 & 2) {
        return 0;
    }
    if (DOPPLEGANGER.facingLeft == 1) {
        if (g_Dop.padPressed & PAD_RIGHT) {
            DOPPLEGANGER.facingLeft = 0;
            g_Dop.unk4C = 1;
            return -1;
        } else if (g_Dop.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Dop.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Dop.padPressed & PAD_LEFT) {
            DOPPLEGANGER.facingLeft = 1;
            g_Dop.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C4BA8);

#include "../../set_speed_x.h"

void func_8010E3B8(s32 velocityX) {
    if (DOPPLEGANGER.entityRoomIndex == 1) {
        velocityX = -velocityX;
    }
    DOPPLEGANGER.velocityX = velocityX;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_8010E470);

extern u8 D_us_801813AC[];

void func_8010E570(s32 arg0) {
    s32 anim = 0;
    bool atLedge = false;

    if (g_Dop.vram_flag & 0x20) {
        atLedge = true;
    }

    DOPPLEGANGER.velocityX = arg0;
    DOPPLEGANGER.velocityY = 0;
    SetPlayerStep(Dop_Stand);
    if (g_Dop.unk48) {
        DOPPLEGANGER.step_s = 2;
        atLedge = false;
    }

    switch (g_Dop.prev_step) {
    case Dop_UnmorphBat:
        anim = 4;
        break;
    case Dop_Walk:
        anim = 4;
        if (DOPPLEGANGER.ext.player.anim == 9) {
            DOPPLEGANGER.ext.player.anim = D_us_801813AC[2 + atLedge];
            return;
        }
        if (DOPPLEGANGER.ext.player.anim == 7) {
            anim = 0;
        }
        break;
    case Dop_Jump:
    case Dop_Fall:
        anim = 6;
        if (abs(DOPPLEGANGER.velocityX) > FIX(2.5)) {
            anim = 4;
        }
        break;
    default:
        anim = 8;
        break;
    }
    anim += atLedge;
    SetPlayerAnim(D_us_801813AC[anim]);
}

void func_8010E6AC(bool forceAnim13) {
    bool atLedge;

    atLedge = 0;
    if (g_Dop.vram_flag & 0x20) {
        atLedge = 1;
    }

    SetSpeedX(FIX(1.5));
    DOPPLEGANGER.velocityY = 0;
    SetPlayerStep(Dop_Walk);

    if (forceAnim13) {
        if (DOPPLEGANGER.ext.player.anim != 13) {
            SetPlayerAnim(13);
        }
    } else {
        SetPlayerAnim(7);
        // Factory blueprint 1 has child 2, which is func_8011B5A4
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(1, 5), 0);
    }

    if (g_Dop.unk4C) {
        DOPPLEGANGER.ext.player.anim = 9;
    }

    if ((DOPPLEGANGER.ext.player.anim == 7) && atLedge) {
        DOPPLEGANGER.pose = 1;
    }

    if (g_Dop.prev_step == Dop_Crouch) {
        DOPPLEGANGER.pose = 4;
    }
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C4EE4);

void func_us_801C4F90(void) {
    DOPPLEGANGER.velocityY = FIX(-4.25);
    g_Dop.unk44 |= 0x21;
    SetPlayerAnim(0x20);
    DOPPLEGANGER.step_s = 0;
}

void func_us_801C4FDC(void) {
    SetPlayerStep(4);
    if (g_Dop.prev_step != 2) {
        SetPlayerAnim(0x1C);
    }
    DOPPLEGANGER.velocityY = FIX(2.0);
    g_Dop.timers[ALU_T_5] = 8;
    g_Dop.timers[ALU_T_6] = 8;
    DOPPLEGANGER.velocityX = 0;
    g_Dop.unk44 = 0x10;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C504C);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_8010EA54);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C5168);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_8010ED54);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C52F8);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_8010FAF4);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C55EC);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C5650);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_80111CC0);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C5C64);

void PlayerStepWalk(void) {
    if (func_us_801C5650(0x4301C) == 0) {
        SetSpeedX(0x18000);
        if (CheckMoveDirection() == 0) {
            func_8010E570(0);
        }
    }
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C5EE0);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C61B0);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C61F8);
