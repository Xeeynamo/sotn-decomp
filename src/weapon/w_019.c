// Weapon ID #19. Used by weapons:
// Neutron bomb
#include "weapon_private.h"
#include "shared.h"
#include "w_019_1.h"
#include "w_019_2.h"
#define g_Animset w_019_1
#define g_Animset2 w_019_2

INCLUDE_ASM("weapon/nonmatchings/w_019", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 19; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
