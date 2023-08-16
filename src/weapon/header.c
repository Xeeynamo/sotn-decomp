#include <weapon.h>
#include "weapon_private.h"

Weapon g_Weapon = {
    EntityWeaponAttack, func_ptr_80170004, func_ptr_80170008, func_ptr_8017000C,
    func_ptr_80170010,  func_ptr_80170014, GetWeaponId,       LoadWeaponPalette,
    func_ptr_80170020,  func_ptr_80170024, func_ptr_80170028, WeaponUnused2C,
    WeaponUnused30,     WeaponUnused34,    WeaponUnused38,    WeaponUnused3C,
};
