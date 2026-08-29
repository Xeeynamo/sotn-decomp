// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

/*
 * RCHI differs throughout these CHI-derived functions (branch layout,
 * constants, and wall control flow), so the CHI source is not byte-identical.
 */
INCLUDE_ASM("st/rchi/nonmatchings/e_demon_switch_wall", UpdateFallingPebble);

extern void (*g_api_RevealSecretPassageAtPlayerPositionOnMap)(s32);
#include "e_rchi_demon_switch.h"

INCLUDE_ASM("st/rchi/nonmatchings/e_demon_switch_wall", EntityDemonSwitchWall);
