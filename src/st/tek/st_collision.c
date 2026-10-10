// SPDX-License-Identifier: AGPL-3.0-or-later
#include "tek.h"

INCLUDE_ASM("st/tek/nonmatchings/st_collision", HitDetection);

static u16 g_eDamageDisplayClut[] = {
    PAL_UNK_1B2, PAL_UNK_1B3, PAL_UNK_1B6, PAL_UNK_1B7,
    PAL_UNK_1B4, PAL_UNK_1B5, PAL_UNK_1B0, PAL_UNK_1B1,
};

#include "../entity_damage_display.h"
