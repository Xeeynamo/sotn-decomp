// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

/*
 * EntityDemonSwitchWall differs from the CHI original in branch layout,
 * constants and wall control flow, so it cannot share the CHI source.
 */
#include "../e_falling_pebble.h"

extern void (*g_api_RevealSecretPassageAtPlayerPositionOnMap)(s32);
#include "e_rchi_demon_switch.h"

INCLUDE_ASM("st/rchi/nonmatchings/e_demon_switch_wall", EntityDemonSwitchWall);
