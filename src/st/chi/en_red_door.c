// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: en_red_door.c
 * Overlay: CHI
 * Description: ENTITY - Red door that connects stages
 */

#include "chi.h"

// D_80180768
u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    {0x039C, 0x039B, 0x039C, 0x039B, 0x010D, 0x010B, 0x010D, 0x010B},
    {0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x02F4, 0x0309, 0x0305, 0x0307},
    {0x03A3, 0x03A7, 0x03A8, 0x03A3, 0x02F4, 0x030F, 0x0310, 0x02F4},
};

// D_80180E0C: g_eRedDoorUV
// func_801A05DC: EntityIsNearPlayer
// func_801A0654: [E_RED_DOOR] EntityRedDoor
#include "../e_red_door.h"
