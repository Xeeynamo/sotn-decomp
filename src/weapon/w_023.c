// Weapon ID #23. Used by weapons:
// Herald shield, Unknown#207
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_023", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 23; }

INCLUDE_ASM("weapon/nonmatchings/w_023", EntityWeaponShieldSpell);

INCLUDE_ASM("weapon/nonmatchings/w_023", func_ptr_80170024);

INCLUDE_ASM("weapon/nonmatchings/w_023", func_ptr_80170028);

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
