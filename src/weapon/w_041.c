#include "weapon_private.h"
#include "shared.h"

void func_123000_8017A914(void) {
    RECT rect;
    RECT rectDummy;
    s16 color;

    color = (g_GameTimer >> 1) % 2 ? 0x039C : 0x199D;
    D_8006EDCC[g_HandId][8] = color;

    rect.x = 0;
    rect.y = 0xF1;
    rect.w = 0x100;
    rect.h = 3;
    LoadImage(&rect, D_8006EDCC);
}

INCLUDE_ASM("weapon/nonmatchings/w_041", func_123000_8017A994);

INCLUDE_ASM("weapon/nonmatchings/w_041", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_041", func_ptr_80170004);

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 41; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
