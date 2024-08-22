// SPDX-License-Identifier: AGPL-3.0-only
#include <types.h>

// A struct which describes variations of Weapon #53 and #56
typedef struct {
    /* 0x0 */ s16 uFlag;
    /* 0x2 */ s16 vFlag;
    /* 0x4 */ s16 clutFlag;
    /* 0x6 */ s16 lifetime;
    /* 0x8 */ s16 rotZ;
    /* 0xA */ u8 r;
    /* 0xB */ u8 g;
    /* 0xC */ u8 b;
    /* 0xD */ u8 : 8;
} W053_056Config; // size = 0xE
