// Weapon ID #26. Used by weapons:
// Shaman shield, Unknown#210
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_026", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 26; }

extern s16 D_BA000_8017AA98;
extern s16 D_BA000_8017AA9A;

void func_BA000_8017B37C(void) {
    RECT rect;
    s16 temp;

    if (D_BA000_8017AA9A & 1) {
        if (++D_BA000_8017AA98 >= 0x20) {
            D_BA000_8017AA9A++;
            D_BA000_8017AA98 = 0x1F;
        }
    } else {
        if (--D_BA000_8017AA98 < 0) {
            D_BA000_8017AA9A++;
            D_BA000_8017AA98 = 0;
        }
    }

    temp = g_Clut[0x112D + g_HandId * 0x180];
    temp &= 0xFC1F;
    temp += D_BA000_8017AA98 << 5;
    g_Clut[0x112D + g_HandId * 0x180] = temp;

    rect.x = 0;
    rect.y = 0xF1;
    rect.w = 0x100;
    rect.h = 3;
    LoadImage(&rect, &g_Clut[0x1100]);
}

INCLUDE_ASM("weapon/nonmatchings/w_026", EntityWeaponShieldSpell);

const s32 D_BA000_8017AB7C[] = {
    0xFFE40008,
    0x00000000,
};
const s32 D_BA000_8017AB84[] = {
    0xFFE40038,
    0x00000000,
};
const s32 D_BA000_8017AB8C[] = {
    0x001C0008,
    0x00000000,
};
const s32 D_BA000_8017AB94[] = {
    0x001C0038,
    0x00000000,
};

INCLUDE_ASM("weapon/nonmatchings/w_026", func_ptr_80170024);

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
