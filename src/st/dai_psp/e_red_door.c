// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dai/dai.h"

u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    {0x04B3, 0x04B3, 0x04B3, 0x04B3, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x000D, 0x000E, 0x000F, 0x000E, 0x01F0, 0x01F6, 0x020E, 0x01F6},
    {0x000A, 0x000B, 0x000C, 0x000B, 0x0086, 0x0088, 0x00A1, 0x0088},
};

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/e_red_door", EntityIsNearPlayer);

INCLUDE_ASM("st/dai_psp/nonmatchings/dai_psp/e_red_door", DAI_EntityRedDoor);
