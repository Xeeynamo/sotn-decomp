// SPDX-License-Identifier: AGPL-3.0-or-later
#include "tek.h"

u16 g_ESoulStealOrbAngles[] = {
    0x820, 0x840, 0x860, 0x880, 0x8C0, 0x900, 0x940, 0xA00,
};

s16 g_ESoulStealOrbSprt[] = {
    // clang-format off
    -3,  -3,  8,  8,  80,  104, 88,  112,
    -3,  -3,  8,  8,  72,  104, 80,  112,
    -7,  -7,  16, 15, 72,  112, 88,  127,
    -11, -11, 24, 23, 0,   104, 24,  127,
    -11, -11, 24, 23, 24,  104, 48,  127,
    -11, -11, 24, 23, 48,  104, 72,  127,
    // clang-format on
};

u8 g_ESoulStealOrbAnim[] = {
    5, 1, 4, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 3, 5, 2, 7, 1, 0, 0};

INCLUDE_ASM("st/tek/nonmatchings/e_particles", EntitySoulStealOrb);

INCLUDE_ASM("st/tek/nonmatchings/e_particles", EntityEnemyBlood);
