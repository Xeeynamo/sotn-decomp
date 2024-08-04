// Weapon ID #56. Used by weapons:
// Muramasa
#include "weapon_private.h"
#include "shared.h"
#include "w_056_1.h"
#include "w_056_2.h"
#define g_Animset w_056_1
#define g_Animset2 w_056_2

INCLUDE_ASM("weapon/nonmatchings/w_056", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_056", func_ptr_80170004);

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 56; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
