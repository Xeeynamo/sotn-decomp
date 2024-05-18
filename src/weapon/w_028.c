// Weapon ID #28. Used by weapons:
// Skull shield, Unknown#212
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_028", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 28; }

extern s16 D_C8000_8017AB18;
extern s16 D_C8000_8017AB1A;

void func_C8000_8017B3D4(void) {
    RECT rect;
    s16 temp;

    if (D_C8000_8017AB1A & 1) {
        if (++D_C8000_8017AB18 >= 0x20) {
            D_C8000_8017AB1A++;
            D_C8000_8017AB18 = 0x1F;
        }
    } else {
        if (--D_C8000_8017AB18 < 0) {
            D_C8000_8017AB1A++;
            D_C8000_8017AB18 = 0;
        }
    }

    temp = g_Clut[0x113B + g_HandId * 0x180];
    temp &= 0xFFE0;
    temp += D_C8000_8017AB18;
    g_Clut[0x113B + g_HandId * 0x180] = temp;

    rect.x = 0;
    rect.y = 0xF1;
    rect.w = 0x100;
    rect.h = 3;
    LoadImage(&rect, &g_Clut[0x1100]);
}

INCLUDE_ASM("weapon/nonmatchings/w_028", EntityWeaponShieldSpell);

INCLUDE_ASM("weapon/nonmatchings/w_028", func_ptr_80170024);

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
