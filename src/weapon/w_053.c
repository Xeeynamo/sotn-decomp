// Weapon ID #53. Used by weapons:
// Katana, Osafune katana, Masamune, Yasutsuna, Unknown#189, Unknown#192,
// Unknown#193, Unknown#194
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_053_1.h"
#include "w_053_2.h"
#define g_Animset w_053_1
#define g_Animset2 w_053_2

INCLUDE_ASM("weapon/nonmatchings/w_053", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_053", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_053", func_ptr_80170008);

INCLUDE_ASM("weapon/nonmatchings/w_053", func_ptr_8017000C);

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 53; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
