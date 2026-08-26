// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rchi/rchi.h"

/* No other PSP overlay contains this reverse-stage switch/wall family. */
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_demon_switch_wall", UpdateFallingPebble);

extern void (*g_api_RevealSecretPassageAtPlayerPositionOnMap)(s32);
#include "../e_rchi_demon_switch.h"

INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_demon_switch_wall", EntityDemonSwitchWall);
