// Weapon ID #55. Used by weapons:
// Holy sword, Unknown#196
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_055_1.h"
#include "w_055_2.h"
#define g_Animset w_055_1
#define g_Animset2 w_055_2

INCLUDE_ASM("weapon/nonmatchings/w_055", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_055", func_ptr_80170004);

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 55; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
