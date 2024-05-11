// Weapon ID #51. Used by weapons:
// Estoc, Claymore, Flamberge, Zwei hander, Obsidian sword, Great Sword,
// Unknown#182, Unknown#183, Unknown#184, Unknown#185
#include "weapon_private.h"
#include "shared.h"

extern s16 D_169000_8017AD68; // R
extern s16 D_169000_8017AD6A; // B
extern s16 D_169000_8017AD6C; // G
extern s16 D_169000_8017AD6E; // step?
extern s16 D_169000_8017AD70; // A
extern s32 D_169000_8017AD74[];

void func_169000_8017B1DC(s32 arg0) {
    RECT rect;
    s32 colorsChanged;
    s32 palIndex;
    u16 color;

    colorsChanged = 0;
    switch (D_169000_8017AD6E) {
    case 0:
        D_169000_8017AD68 += 2;
        D_169000_8017AD6C += 2;
        D_169000_8017AD6A += 2;
        if (D_169000_8017AD68 >= D_169000_8017AD74[arg0 * 8 + 4]) {
            colorsChanged++;
            D_169000_8017AD68 = D_169000_8017AD74[arg0 * 8 + 4];
        }
        if (D_169000_8017AD6C >= D_169000_8017AD74[arg0 * 8 + 5]) {
            colorsChanged++;
            D_169000_8017AD6C = D_169000_8017AD74[arg0 * 8 + 5];
        }
        if (D_169000_8017AD6A >= D_169000_8017AD74[arg0 * 8 + 6]) {
            colorsChanged++;
            D_169000_8017AD6A = D_169000_8017AD74[arg0 * 8 + 6];
        }
        if (!D_169000_8017AD68 && !D_169000_8017AD6C && !D_169000_8017AD6A) {
            D_169000_8017AD70 = 0;
        } else {
            D_169000_8017AD70 = 1;
        }
        if (colorsChanged == 3) {
            D_169000_8017AD6E++;
        }
        break;
    case 1:
        D_169000_8017AD68 -= 2;
        D_169000_8017AD6C -= 2;
        D_169000_8017AD6A -= 2;
        if (D_169000_8017AD68 <= D_169000_8017AD74[arg0 * 8]) {
            colorsChanged++;
            D_169000_8017AD68 = D_169000_8017AD74[arg0 * 8];
        }
        if (D_169000_8017AD6C <= D_169000_8017AD74[arg0 * 8 + 1]) {
            colorsChanged++;
            D_169000_8017AD6C = D_169000_8017AD74[arg0 * 8 + 1];
        }
        if (D_169000_8017AD6A <= D_169000_8017AD74[arg0 * 8 + 2]) {
            colorsChanged++;
            D_169000_8017AD6A = D_169000_8017AD74[arg0 * 8 + 2];
        }
        if (!D_169000_8017AD68 && !D_169000_8017AD6C && !D_169000_8017AD6A) {
            D_169000_8017AD70 = 0;
        } else {
            D_169000_8017AD70 = 1;
        }
        if (colorsChanged == 3) {
            D_169000_8017AD6E++;
        }
        break;
    case 2:
        return;
    }

    color = D_169000_8017AD68 + (D_169000_8017AD6C << 5) +
            (D_169000_8017AD6A << 10) + (D_169000_8017AD70 << 15);
    palIndex = (g_HandId * 0x180);
    palIndex += arg0 << 5;
    D_8006EDCC[0][0x2B + palIndex] = color;

    rect.x = 0;
    rect.y = 0xF1;
    rect.w = 256;
    rect.h = 3;
    LoadImage(&rect, (u_long*)D_8006EDCC);
}

INCLUDE_ASM("weapon/nonmatchings/w_051", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_051", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_051", func_ptr_80170008);

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 51; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
