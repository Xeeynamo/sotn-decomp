#ifndef WEAPON_PRIVATE_H
#define WEAPON_PRIVATE_H

#define INCLUDE_ASM_NEW
#include <weapon.h>

// exported
void EntityWeaponAttack(Entity* self);
void LoadWeaponPalette(s32 clutIndex);
void func_ptr_80170004(Entity* self);
void func_ptr_80170008(Entity* self);
void func_ptr_8017000C(Entity* self);
void func_ptr_80170010(Entity* self);
void func_ptr_80170014(Entity* self);
int GetWeaponId(void);
void func_ptr_80170020(Entity* self);
void func_ptr_80170024(Entity* self);
void func_ptr_80170028(Entity* self);
void WeaponUnused2C(void);
void WeaponUnused30(void);
void WeaponUnused34(void);
void WeaponUnused38(void);
void WeaponUnused3C(void);

// internals
void DestroyEntity(Entity* entity);

#endif