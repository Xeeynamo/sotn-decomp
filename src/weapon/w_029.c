#include "weapon_private.h"

// Variant of DestroyEntity
INCLUDE_ASM("weapon/nonmatchings/w_029", func_CF000_8017ADD8);

INCLUDE_ASM("weapon/nonmatchings/w_029", LoadWeaponPalette);

INCLUDE_ASM("weapon/nonmatchings/w_029", SetSpriteBank1);

INCLUDE_ASM("weapon/nonmatchings/w_029", SetSpriteBank2);

INCLUDE_ASM("weapon/nonmatchings/w_029", DecelerateX);

INCLUDE_ASM("weapon/nonmatchings/w_029", DecelerateY);

INCLUDE_ASM("weapon/nonmatchings/w_029", func_CF000_8017AFC8);

INCLUDE_ASM("weapon/nonmatchings/w_029", func_CF000_8017AFF8);

INCLUDE_ASM("weapon/nonmatchings/w_029", func_CF000_8017B06C);

INCLUDE_ASM("weapon/nonmatchings/w_029", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_029", func_ptr_80170004);

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 29; }

INCLUDE_ASM("weapon/nonmatchings/w_029", func_ptr_80170020);

INCLUDE_ASM("weapon/nonmatchings/w_029", func_ptr_80170024);

INCLUDE_ASM("weapon/nonmatchings/w_029", func_ptr_80170028);

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
