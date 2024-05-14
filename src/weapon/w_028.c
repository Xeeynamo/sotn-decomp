// Weapon ID #28. Used by weapons:
// Skull shield, Unknown#212
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_028", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 28; }

INCLUDE_ASM("weapon/nonmatchings/w_028", func_C8000_8017B3D4);

INCLUDE_ASM("weapon/nonmatchings/w_028", EntityWeaponShieldSpell);

INCLUDE_ASM("weapon/nonmatchings/w_028", func_ptr_80170024);

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
