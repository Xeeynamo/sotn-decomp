// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../bo3/bo3.h"

extern u8 D_pspeu_09266788[];

static u8 D_pspeu_09252840[8] = {0x04, 0x01, 0x04, 0x02, 0x00};
static u8 D_pspeu_09252848[8] = {0x04, 0x00, 0x04, 0x00, 0x00};
static u8 D_pspeu_09252850[16] = {
    0x05, 0x01, 0x05, 0x02, 0x05, 0x03, 0x05, 0x04, 0x00};
static u8 D_pspeu_09252860[16] = {
    0x05, 0x05, 0x05, 0x06, 0x05, 0x07, 0x05, 0x08, 0x00};
static u8 D_pspeu_09252870[16] = {
    0x05, 0x0D, 0x05, 0x0E, 0x05, 0x0F, 0x05, 0x10, 0x00};
static u8 D_pspeu_09252880[8] = {0x05, 0x11, 0x05, 0x12, 0x05, 0x13, 0x00};
static u8 D_pspeu_09252888[8] = {0x05, 0x17, 0x00, 0x00};
static u8 D_pspeu_09252890[8] = {0x05, 0x16, 0x00, 0x00};
static u8 D_pspeu_09252898[16] = {
    0x05, 0x14, 0xFF, 0xFF, 0x05, 0x15, 0x05, 0x15, 0xFF, 0x00, 0x00, 0x00};
static u8* anims[] = {
    D_pspeu_09252840, D_pspeu_09252848, D_pspeu_09252850, D_pspeu_09252860,
    D_pspeu_09266788, D_pspeu_09252870, D_pspeu_09252880, D_pspeu_09252888,
    D_pspeu_09252890, D_pspeu_09252898};

static u8 hitbox_heights[16] = {
    0x08, 0x08, 0x28, 0x18, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00};
static u8 params_arr[16] = {
    0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00};
static u16 palettes[12] = {
    PAL_NULL, PAL_NULL, 0x228, 0x228, 0x228, 0x228, 0x228, 0x228, 0x228, 0x228};
static u16 anim_sets[12] = {
    ANIMSET_DRA(0x3), ANIMSET_DRA(0x3), ANIMSET_OVL(0xB), ANIMSET_OVL(0xB),
    ANIMSET_OVL(0xB), ANIMSET_OVL(0xB), ANIMSET_OVL(0xB), ANIMSET_OVL(0xB),
    ANIMSET_OVL(0xB), ANIMSET_OVL(0xB)};
static u16 unk5a_arr[12] = {0x0000, 0x007C, 0x005B, 0x005B, 0x005B,
                            0x005B, 0x005B, 0x005B, 0x005B, 0x005B};
static u8 blend_modes[16] = {
    DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE};
static u16 hitbox_y_offsets[12] = {0x0000, 0x0000, 0xFFE8, 0xFFF0, 0x0000,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

extern s32 E_ID(UNK_43);
#define E_BREAKABLE_RELIC E_ID(UNK_43)

#include "../../st/e_breakable_no4.h"

INCLUDE_ASM("boss/bo3_psp/nonmatchings/bo3_psp/unk_EB90", func_us_801C123C_from_no4);

INCLUDE_ASM("boss/bo3_psp/nonmatchings/bo3_psp/unk_EB90", func_pspeu_09246618);

INCLUDE_ASM("boss/bo3_psp/nonmatchings/bo3_psp/unk_EB90", func_us_801A07CC);

INCLUDE_ASM("boss/bo3_psp/nonmatchings/bo3_psp/unk_EB90", func_pspeu_09246A00);

INCLUDE_ASM("boss/bo3_psp/nonmatchings/bo3_psp/unk_EB90", func_us_801A0A80);

INCLUDE_ASM("boss/bo3_psp/nonmatchings/bo3_psp/unk_EB90", func_us_801A1120);

INCLUDE_ASM("boss/bo3_psp/nonmatchings/bo3_psp/unk_EB90", func_us_801A16E4);

INCLUDE_ASM("boss/bo3_psp/nonmatchings/bo3_psp/unk_EB90", func_pspeu_092481F0);

INCLUDE_ASM("boss/bo3_psp/nonmatchings/bo3_psp/unk_EB90", func_us_801A1BE8);

INCLUDE_ASM("boss/bo3_psp/nonmatchings/bo3_psp/unk_EB90", EntitySplashWater);

#include "../../st/entity_water_drop.h"

INCLUDE_ASM("boss/bo3_psp/nonmatchings/bo3_psp/unk_EB90", EntityBackgroundBlock);
