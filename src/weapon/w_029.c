// Weapon ID #29. Used by weapons:
// Fire shield, Unknown#213
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_029", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_029", func_ptr_80170004);

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 29; }

INCLUDE_ASM("weapon/nonmatchings/w_029", EntityWeaponShieldSpell);

INCLUDE_ASM("weapon/nonmatchings/w_029", func_ptr_80170024);

INCLUDE_ASM("weapon/nonmatchings/w_029", func_ptr_80170028);

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
