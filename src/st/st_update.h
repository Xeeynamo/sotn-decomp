// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

// palette
u16 UNK_Invincibility0[] = {
    PAL_OVL(0x163), PAL_OVL(0x164), PAL_OVL(0x166), PAL_OVL(0x164),
    PAL_OVL(0x160), PAL_OVL(0x166), PAL_OVL(0x162), PAL_OVL(0x164),
    PAL_OVL(0x167), PAL_OVL(0x164), PAL_OVL(0x167), PAL_OVL(0x168),
    PAL_OVL(0x168), PAL_OVL(0x164), PAL_OVL(0x161), PAL_OVL(0x164),
    PAL_OVL(0x165), PAL_OVL(0x165), PAL_OVL(0x163), PAL_OVL(0x163),
#if !(defined VERSION_BETA)
    PAL_OVL(0x165), PAL_OVL(0x165),
#endif
};
#include "random.h"
#include "update.h"
#include "update_stage_entities.h"
