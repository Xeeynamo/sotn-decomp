// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rchi/rchi.h"

#include "../e_falling_pebble.h"

extern void (*g_api_RevealSecretPassageAtPlayerPositionOnMap)(s32);
#include "../rchi/e_rchi_demon_switch.h"

INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_demon_switch_wall", EntityDemonSwitchWall);
