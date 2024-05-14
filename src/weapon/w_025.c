// Weapon ID #25. Used by weapons:
// Goddess shield, Unknown#209
#include "weapon_private.h"
#include "shared.h"

void func_B3000_8017AF14(const char* fmt, u_long end) {
    while (PadRead(0) != end) {
        FntPrint(fmt);
        DrawSync(0);
        VSync(0);
        FntFlush(-1);
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_025", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 25; }

INCLUDE_ASM("weapon/nonmatchings/w_025", EntityWeaponShieldSpell);

INCLUDE_ASM("weapon/nonmatchings/w_025", func_ptr_80170024);

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
