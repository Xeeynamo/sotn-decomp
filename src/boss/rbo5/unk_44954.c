// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

// n.b.! this file is the same as bo4/unk_45354.c

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C4954);

void func_8010E0A8(void) {
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk2 = 0;
}

void func_8010E0B8(void) {
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk1 = 0;
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk0 = 0;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C4A30);

#include "../../decelerate.h"

extern PlayerState g_Dop;

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

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_8010E570);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_8010E6AC);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C4EE4);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C4F90);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C4FDC);

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

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", PlayerStepWalk);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C5EE0);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C61B0);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_44954", func_us_801C61F8);
