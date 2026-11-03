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

extern char DAT_06006F80[];
extern char DAT_06006F84[];
extern char DAT_06006F90[];
extern char DAT_06006F9C[];

FileLoadEntry DAT_06038A4C = {{DAT_06006F80, &g_PlayerOvl, 0xFFFFFFFF,
                               0x00000000, 0xFFFFFFFF, 0x00000000},
                              0x00000000,
                              0x00000000};

FileLoadEntry DAT_06038A6C = {{DAT_06006F80, DAT_00232000, 0xFFFFFFFF,
                               0x00000000, 0xFFFFFFFF, 0x00000000},
                              0x00000000,
                              0x00000000};

FileLoadEntry DAT_06038A8C = {{DAT_06006F80, g_FileLoadBuffer, 0xFFFFFFFF,
                               0x00000000, 0x00000002, 0x00000001},
                              0x00000001,
                              0x00000000};

FileLoadEntry DAT_06038AAC = {{DAT_06006F84, g_Weapon0OvlArea, 0x00003000,
                               0x00000000, 0xFFFFFFFF, 0x00000000},
                              0x00000000,
                              0x00000000};

FileLoadEntry DAT_06038ACC = {{DAT_06006F90, g_FileLoadBuffer, 0x00004000,
                               0x00000000, 0x00000002, 0x00000001},
                              0x00000001,
                              0x00000000};

FileLoadEntry DAT_06038AEC = {{DAT_06006F90, g_FileLoadBuffer, 0x00004000,
                               0x00000000, 0xFFFFFFFF, 0x00000000},
                              0x00000000,
                              0x00000000};

FileLoadEntry DAT_06038B0C = {{DAT_06006F9C, &g_StageOverlayData, 0xFFFFFFFF,
                               0x00000000, 0xFFFFFFFF, 0x00000000},
                              0x00000000,
                              0x00000000};

FileLoadEntry DAT_06038B2C = {{DAT_06006F9C, g_FileLoadBuffer, 0xFFFFFFFF,
                               0x00000000, 0x00000002, 0x00000001},
                              0x00000001,
                              0x00000000};

FileLoadEntry DAT_06038B4C = {{DAT_06006F9C, &DAT_00252000, 0xFFFFFFFF,
                               0x00000000, 0xFFFFFFFF, 0x00000000},
                              0x00000000,
                              0x00000000};

FileLoadEntry DAT_06038B6C = {
    {NULL, &g_BatServantDesc, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000},
    0x00000000,
    0x00000000};

FileLoadEntry DAT_06038B8C = {
    {NULL, g_FileLoadBuffer, 0xFFFFFFFF, 0x00000000, 0x00000002, 0x00000001},
    0x00000001,
    0x00000000};

FileLoadEntry DAT_06038BAC = {
    {NULL, g_FileLoadBuffer, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000},
    0x00000000,
    0x00000000};

FileLoadEntry* DAT_06038BCC[] = {
    &DAT_06038A4C, &DAT_06038A6C, &DAT_06038A8C, &DAT_06038AAC, &DAT_06038ACC,
    &DAT_06038B0C, &DAT_06038B2C, &DAT_06038B4C, &DAT_06038B6C, &DAT_06038B8C,
};

extern char DAT_06007060[];
extern char DAT_0600706C[];
extern char DAT_0600707C[];
extern char DAT_0600708C[];
extern char DAT_06007098[];
extern char DAT_060070A4[];
extern char DAT_060070B0[];
extern char DAT_060070BC[];
extern char DAT_060070C8[];
extern char DAT_060070D4[];
extern char DAT_060070E0[];
extern char DAT_060070EC[];
extern char DAT_060070F8[];
extern char DAT_06007108[];
extern char DAT_06007118[];
extern char DAT_06007128[];
extern char DAT_06007138[];
extern char DAT_06007144[];
extern char DAT_06007150[];
extern char DAT_0600715C[];
extern char DAT_06007168[];
extern char DAT_06007174[];
extern char DAT_06007180[];
extern char DAT_0600718C[];
extern char DAT_06007198[];
extern char DAT_060071A4[];
extern char DAT_060071B0[];
extern char DAT_060071BC[];

char* DAT_06038BF4[][3] = {
    {DAT_060070EC, DAT_060070E0, DAT_060070D4},
    {DAT_060070C8, DAT_060070BC, DAT_060070B0},
    {DAT_060070A4, DAT_06007098, DAT_0600708C},
    {DAT_0600707C, DAT_0600706C, DAT_06007060},
};

char* DAT_06038C24[][2] = {
    {DAT_060071A4, DAT_06007198}, {DAT_0600718C, DAT_06007180},
    {DAT_06007174, DAT_06007168}, {DAT_0600715C, DAT_06007150},
    {DAT_06007144, DAT_06007138}, {DAT_06007128, DAT_06007118},
    {DAT_06007108, DAT_060070F8},
};
