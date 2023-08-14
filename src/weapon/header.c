#include <weapon.h>
#include "weapon_private.h"

void func_ptr_80170008(void);
void func_ptr_8017000C(void);
void func_ptr_80170010(void);
void func_ptr_80170014(void);
int func_ptr_80170018(void);
void func_ptr_80170020(void);
void func_ptr_80170024(void);
void func_ptr_80170028(void);
void func_ptr_8017002C(void);
void func_ptr_80170030(void);
void func_ptr_80170034(void);
void func_ptr_80170038(void);
void func_ptr_8017003C(void);

Weapon g_Weapon = {
    EntityWeaponAttack, func_ptr_80170004, func_ptr_80170008, func_ptr_8017000C,
    func_ptr_80170010,  func_ptr_80170014, func_ptr_80170018, LoadWeaponPalette,
    func_ptr_80170020,  func_ptr_80170024, func_ptr_80170028, func_ptr_8017002C,
    func_ptr_80170030,  func_ptr_80170034, func_ptr_80170038, func_ptr_8017003C,
};
