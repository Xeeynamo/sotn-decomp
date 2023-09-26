// Weapon ID #51. Used by weapons:
// Estoc, Claymore, Flamberge, Zwei hander, Obsidian sword, Great Sword,
// Unknown#182, Unknown#183, Unknown#184, Unknown#185
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_051", func_169000_8017B1DC);

INCLUDE_ASM("weapon/nonmatchings/w_051", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_051", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_051", func_ptr_80170008);

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 51; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
