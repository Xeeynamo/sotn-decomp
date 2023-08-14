#ifndef WEAPON_PRIVATE_H
#define WEAPON_PRIVATE_H

#define INCLUDE_ASM_NEW
#include <weapon.h>

// exported
void EntityWeaponAttack(Entity* self);
void LoadWeaponPalette(s32 clutIndex);
void func_ptr_80170004(Entity* self);

// internals
void DestroyEntity(Entity* entity);

#endif