// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

// n.b.! this file is the same as rbo5/unk_44954.c

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5354);

void func_8010E0A8(void) {
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk2 = 0;
}

void func_8010E0B8(void) {
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk1 = 0;
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk0 = 0;
}

extern s16 D_us_801D4D6C[];

void func_us_801C5430(s16 a0, s16 a1) {
    if (D_us_801D4D6C[0] <= a1) {
        D_us_801D4D6C[0] = a1;
    }
}

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

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C55A8);

#include "../../set_speed_x.h"

void func_8010E3B8(s32 velocityX) {
    if (DOPPLEGANGER.entityRoomIndex == 1) {
        velocityX = -velocityX;
    }
    DOPPLEGANGER.velocityX = velocityX;
}

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_8010E470);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_8010E570);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_8010E6AC);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C58E4);

void SetPlayerAnim(u8 anim);                                 /* extern */
extern s16 DOPPLEGANGER_step_s;
extern s32 DOPPLEGANGER_velocityY;
extern s16 g_Dop_unk44[];

void func_us_801C5990(void) {
    DOPPLEGANGER_velocityY = 0xFFFBC000;
    *g_Dop_unk44 |= 0x21;
    SetPlayerAnim(0x20);
    DOPPLEGANGER_step_s = 0;
}

extern s32 D_800762E0;
extern s16 D_us_801D4D5A;
extern s16 D_us_801D4D5C;
extern u16 D_us_801D4DC0;

void func_us_801C59DC(void) {
    SetPlayerStep(4);
    if (D_us_801D4DC0 != 2) {
        SetPlayerAnim(0x1C);
    }
    DOPPLEGANGER_velocityY = 0x20000;
    D_us_801D4D5A = 8;
    D_us_801D4D5C = 8;
    D_800762E0 = 0;
    *g_Dop_unk44 = 0x10;
}


INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5A4C);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_8010EA54);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5B68);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_8010ED54);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5CF8);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_8010FAF4);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5FDC);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C6040);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_80111CC0);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C6654);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", PlayerStepWalk);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C68D0);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C6BA0);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C6BE8);
