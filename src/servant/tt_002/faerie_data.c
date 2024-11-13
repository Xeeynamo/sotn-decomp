// SPDX-License-Identifier: AGPL-3.0-or-later
#include "faerie.h"
#include "sfx.h"

// SFX map
s32 D_us_80172BCC[] = {
    SFX_TT002_UNK_885, SFX_TT002_UNK_886, SFX_TT002_UNK_887,
    SFX_TT002_UNK_888, SFX_TT002_UNK_891, SFX_TT002_UNK_892,
};

// ranked lookup tables for sfx
s32 D_us_80172BE4[] = {0x3F, SFX_TT002_UNK_889, 0x7F, SFX_TT002_UNK_88A,
                       0xBF, SFX_TT002_UNK_88B, 0xFF, SFX_TT002_UNK_88C};

s32 D_us_80172C04[] = {0x3F, SFX_TT002_UNK_88D, 0x7F, SFX_TT002_UNK_88E,
                       0xBF, SFX_TT002_UNK_88F, 0xFF, SFX_TT002_UNK_890};

s16 D_us_80172C24[] = {0x0000, 0x0022, 0x0472, 0xFFFF, 0x000E, 0x0000};

s16 D_us_80172C30[] = {0x0000, 0x0022, 0x0473, 0xFFFF, 0x000E, 0x0000};

// This is a ranked lookup table.  First column is selected from a rand() %
// 0x100 to select the data at the pointer in column 2
s32 D_us_80172C3C[] = {0x0000007F, D_us_80172C24, 0x000000FF, D_us_80172C30};

s16 D_us_80172C4C[] = {0x0000, 0x0026, 0x0476, 0xFFFF, 0x000E, 0x0000};

s16 D_us_80172C58[] = {0x0000, 0x0026, 0x0479, 0xFFFF, 0x000E, 0x0000};

// This is a ranked lookup table.  First column is selected from a rand() %
// 0x100 to select the data at the pointer in column 2
s32 D_us_80172C64[] = {0x0000007F, D_us_80172C4C, 0x000000FF, D_us_80172C58};

// position data with a flag field
// clang-format off
FaerieUnkA4 D_us_80172C74[2] = { { 0, 14, 0x0492,} , { -1, 14, 0 } };
FaerieUnkA4 D_us_80172C80[2] = { { 0, 14, 0x048E,} , { -1, 14, 0 } };
FaerieUnkA4 D_us_80172C8C[2] = { { 0, 37, 0x047A,} , { -1, 14, 0 } };
FaerieUnkA4 D_us_80172C98[2] = { { 0, 36, 0x048A,} , { -1, 14, 0 } };
FaerieUnkA4 D_us_80172CA4[2] = { { 0, 36, 0x047A,} , { -1, 14, 0 } };

Unk2CB0 D_us_80172CB0[] = {
    { .left = -1,  .top = -1,  .unk8 = D_us_80172C74 },
    { .left = -1,  .top = -1,  .unk8 = D_us_80172C80 },
    { .left = 88,  .top = 184, .unk8 = D_us_80172C8C },
    { .left = 32,  .top = 128, .unk8 = D_us_80172C98 },
    { .left = 56,  .top = 128, .unk8 = D_us_80172CA4 },
    { .left = 128, .top = 208, .unk8 = D_us_80172C8C },
    { .left = 208, .top = 112, .unk8 = D_us_80172CA4 },
    { .left = 160, .top = 128, .unk8 = D_us_80172C98 },
    { .left = 208, .top = 120, .unk8 = D_us_80172CA4 },
    { .left = 48,  .top = 128, .unk8 = D_us_80172C98 },
};
// clang-format on

s16 g_FaerieFrameCount1 = 0x1518;
s16 g_FaerieFrameCount2 = 0x0960;
