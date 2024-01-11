#ifndef WEAPON_PRIVATE_H
#define WEAPON_PRIVATE_H

#include <weapon.h>

#define WEAPON0 // forces WEAPON0 for the time being

#if defined(WEAPON0)
#define HAND_ID 0
#elif defined(WEAPON1)
#define HAND_ID 1
#else
#warning "WEAPON0 or WEAPON1 not specified. Falling back to WEAPON0."
#define HAND_ID 0
#endif

// exported
void EntityWeaponAttack(Entity* self);
void LoadWeaponPalette(s32 clutIndex);
void func_ptr_80170004(Entity* self);
void func_ptr_80170008(Entity* self);
void func_ptr_8017000C(Entity* self);
void func_ptr_80170010(Entity* self);
void func_ptr_80170014(Entity* self);
int GetWeaponId(void);
void EntityWeaponShieldSpell(Entity* self);
void func_ptr_80170024(Entity* self);
void func_ptr_80170028(Entity* self);
void WeaponUnused2C(void);
void WeaponUnused30(void);
void WeaponUnused34(void);
void WeaponUnused38(void);
void WeaponUnused3C(void);

// internals
extern SpriteParts* g_Animset[];
extern SpriteParts* g_Animset2[];
extern u16* g_Cluts[];
extern s32 g_HandId;

void DestroyEntity(Entity* entity);
void SetSpriteBank1(SpriteParts* animset);
void SetSpriteBank2(SpriteParts* animset);
void DecelerateX(s32 amount);
void DecelerateY(s32 amount);
void SetSpeedX(s32 speed);

#endif
