// Weapon ID #5. Used by weapons:
// Star flail, Unknown#171
#include "weapon_private.h"
#include "shared.h"
#include "w_005_1.h"
#include "w_005_2.h"
#define g_Animset w_005_1
#define g_Animset2 w_005_2

INCLUDE_ASM("weapon/nonmatchings/w_005", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 5; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
