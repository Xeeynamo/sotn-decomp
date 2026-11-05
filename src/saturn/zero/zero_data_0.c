// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "inc_asm.h"
#include "zero.h"
#include "zero/overlay.h"

u16 DAT_060389CC[] = {
    /* 0x060389CC */ 0x0000,
    /* 0x060389CE */ 0x0000,
    /* 0x060389D0 */ 0x0000,
    /* 0x060389D2 */ 0x0000,
    /* 0x060389D4 */ 0x0000,
    /* 0x060389D6 */ 0x0000,
    /* 0x060389D8 */ 0x0000,
    /* 0x060389DA */ 0x0000,
    /* 0x060389DC */ 0x0000,
    /* 0x060389DE */ 0x0000,
};

s32 DAT_060389E0[][2] = {
    {0x00000B01, 0xF000080D},
    {0x00000B02, 0xF000080E},
    {0x00000B33, 0xF0000811},
};

s32 DAT_060389F8[] = {
    0xFF000000, 0xFF000000, 0xF000080C, 0xF0000808,
    0xF000080B, 0xF0000809, 0xF000080A,
};

extern char DAT_0600597C[];
extern char DAT_06005988[];
extern char DAT_06005994[];
extern char DAT_060059A0[];
extern char DAT_060059AC[];
extern char DAT_060059B8[];
extern char DAT_060059C4[];
extern char DAT_060059D0[];

char* DAT_06038A14[][2] = {
    {DAT_060059D0, DAT_060059C4}, {DAT_060059B8, DAT_060059AC},
    {DAT_060059A0, DAT_06005994}, {DAT_060059D0, DAT_060059C4},
    {DAT_06005988, DAT_0600597C}, {DAT_060059D0, DAT_060059C4},
};

s32 DAT_06038A44 = 0;

s32 DAT_06038A48 = 0;
