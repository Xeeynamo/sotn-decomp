// SPDX-License-Identifier: AGPL-3.0-or-later
#include <weapon.h>

void EntityWeaponAttack(Entity* self);
void func_ptr_80170004(Entity* self);
void func_ptr_80170008(Entity* self);
void func_ptr_8017000C(Entity* self);
void func_ptr_80170010(void);
void func_ptr_80170014(Entity* self);
int GetWeaponId(void);
void LoadWeaponPalette(s32 clutIndex);
void EntityWeaponShieldSpell(Entity* self);
void func_ptr_80170024(Entity* self);
void func_ptr_80170028(Entity* self);

void WeaponUnused2C(void);
void WeaponUnused30(void);
void WeaponUnused34(void);
void WeaponUnused38(void);
void WeaponUnused3C(void);

Weapon WeaponOverlay = {
    EntityWeaponAttack, func_ptr_80170004, func_ptr_80170008,
    func_ptr_8017000C,  func_ptr_80170010, func_ptr_80170014,
    GetWeaponId,        LoadWeaponPalette, EntityWeaponShieldSpell,
    func_ptr_80170024,  func_ptr_80170028, WeaponUnused2C,
    WeaponUnused30,     WeaponUnused34,    WeaponUnused38,
    WeaponUnused3C,
};

#ifdef VERSION_PSP
// TODO: this should be WEAPON0_PTR
#ifdef WEAPON0
extern void D_8017A000[];
#define WEAPON_PTR D_8017A000
#else
extern void D_8017D000[];
#define WEAPON_PTR D_8017D000
#endif

void WeaponLoad(void) { memcpy(&WEAPON_PTR, &WeaponOverlay, sizeof(Weapon)); }
#endif // VERSION_PSP

#ifdef VERSION_PC
#include <psyz/module.h>
#include <string.h>

void Psyz_ModuleStart(void* param) {
    Weapon* o = param;
    memcpy(o, &WeaponOverlay, sizeof(Weapon));
}

void Psyz_ModuleStop(void) {}
#endif // VERSION_PC
