// Weapon ID #53. Used by weapons:
// Katana, Osafune katana, Masamune, Yasutsuna, Unknown#189, Unknown#192,
// Unknown#193, Unknown#194
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_053", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_053", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_053", func_ptr_80170008);

INCLUDE_ASM("weapon/nonmatchings/w_053", func_ptr_8017000C);

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 53; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
