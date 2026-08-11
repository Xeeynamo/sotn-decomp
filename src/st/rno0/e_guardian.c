// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

#define GUARDIAN

// These defines allow us to use single names in
// the .h file but call it Guardian in the overlay entities
#define E_ARMOR_LORD E_GUARDIAN
#define E_ARMOR_LORD_SWORD_SHADOW E_GUARDIAN_SWORD_SHADOW
#define E_ARMOR_LORD_FIRE_WAVE E_GUARDIAN_FIRE_WAVE
#define E_ARMOR_LORD_UNK2 E_GUARDIAN_UNK2
#define E_ARMOR_LORD_UNUSED E_GUARDIAN_UNUSED

#define PAL_ARMOR_LORD_UNK PAL_GUARDIAN_UNK

#define EntityArmorLord EntityGuardian
#define EntityArmorLordSwordShadow EntityGuardianSwordShadow 
#define EntityArmorLordFireWave EntityGuardianFireWave 
#define EntityArmorLordUnk2 EntityGuardianUnk2
#define EntityArmorLordUnused EntityGuardianUnused

#define g_EInitArmorLord g_EInitGuardian
#define g_EInitArmorLordSwordShadow g_EInitGuardianSwordShadow
#define g_EInitArmorLordTemp g_EInitGuardianTemp

#include "../e_armor_lord.h"