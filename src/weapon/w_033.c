// Weapon ID #33. Used by weapons:
// Nunchaku
#include "weapon_private.h"
#include "shared.h"
#include "w_033_1.h"
#include "w_033_2.h"
#define g_Animset w_033_1
#define g_Animset2 w_033_2

INCLUDE_ASM("weapon/nonmatchings/w_033", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 33; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
