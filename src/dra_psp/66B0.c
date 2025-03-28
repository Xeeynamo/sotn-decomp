// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

#define CAPE_PAL_TERMINATOR -1
s32 g_CapePaletteDefs[] = {
    ITEM_NO_CAPE,        0x409, ITEM_CLOTH_CAPE,     0x412,
    ITEM_REVERSE_CLOAK,  0x40B, ITEM_ELVEN_CLOAK,    0x40E,
    ITEM_CRYSTAL_CLOAK,  0x410, ITEM_ROYAL_CLOAK,    0x40D,
    ITEM_BLOOD_CLOAK,    0x40F, ITEM_JOSEPHS_CLOAK,  0x411,
    ITEM_TWILIGHT_CLOAK, 0x40A, CAPE_PAL_TERMINATOR, 0x409,
};

void UpdateCapePalette(void) {
    s32 clut;
    s32 i;

    func_800EA538(6);

    i = 0;
    while (1) {
        if (g_Status.equipment[CAPE_SLOT] == g_CapePaletteDefs[i]) {
            break;
        }

        if (g_CapePaletteDefs[i] == CAPE_PAL_TERMINATOR) {
            break;
        }
        i += 2;
    }

    clut = g_CapePaletteDefs[i + 1];
    if (g_Status.equipment[CAPE_SLOT] == ITEM_REVERSE_CLOAK &&
        g_Settings.isCloakLiningReversed) {
        clut++;
    }

    func_800EA5E4(clut);
    if (g_Status.equipment[CAPE_SLOT] == ITEM_TWILIGHT_CLOAK) {
        func_800EA5E4(0x415);
    }
}

void RefreshCapePalette(void) {
    if (g_StageId != STAGE_ST0 && g_PlayableCharacter == PLAYER_ALUCARD) {
        UpdateCapePalette();
    }
}

void func_800FF708(s32 equipType, s32 arg1) {
    s32 rnd;

    do {
    loop_1:
        rnd = rand() % 90;
        while (rnd == 0x19) {
            goto loop_1;
        }
    } while (g_AccessoryDefs[rnd].equipType != equipType);
    (g_Status.equipment + 2)[arg1] = rnd;
}
