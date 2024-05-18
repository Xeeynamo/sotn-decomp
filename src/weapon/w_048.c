// Weapon ID #48. Used by weapons:
// Thunderbrand, Unknown#178
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_048", EntityWeaponAttack);

extern s16 D_154000_8017B000[];

void func_154000_8017B810(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.unkAC - 0x41;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_154000_8017B000[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_154000_8017B000[idx * 4 + 2] / 2);
        } else {
            outPoint->x = -(D_154000_8017B000[idx * 4 + 2]);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_154000_8017B000[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_154000_8017B000[idx * 4 + 2] / 2;
        } else {
            outPoint->x = D_154000_8017B000[idx * 4 + 2];
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_154000_8017B000[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_154000_8017B000[idx * 4 + 3] / 2;
    } else {
        outPoint->y = D_154000_8017B000[idx * 4 + 3];
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_048", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_048", func_ptr_80170008);

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 48; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
