// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #17. Used by weapons:
// Pentagram, Bat Pentagram
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_017_1.h"
#include "w_017_2.h"
#define g_Animset w_017_1
#define g_Animset2 w_017_2

INCLUDE_ASM("weapon/nonmatchings/w_017", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 17; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
