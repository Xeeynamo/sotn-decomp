// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

extern u16* g_AlucardEffectAnimTable[];
extern s8 D_060B24B0[];

typedef struct {
    u16** frames;
    s8* frameProps;
    u16 palette;
    u16 soundId;
    u8 frameStart;
    u8 soundFrame;
    s16 unused;
} AlucardWeaponAnimation;

AlucardWeaponAnimation g_AlucardEffectWeaponAnimation[] = {
    {
        g_AlucardEffectAnimTable,
        D_060B24B0,
        0,
        0x060C,
        0x1B,
        1,
        0,
    },
};
