// Weapon ID #48. Used by weapons:
// Thunderbrand, Unknown#178
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_048_1.h"
#include "w_048_2.h"
#define g_Animset w_048_1
#define g_Animset2 w_048_2

INCLUDE_ASM("weapon/nonmatchings/w_048", EntityWeaponAttack);

extern s16 D_154000_8017B000[];

void func_154000_8017B810(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0x41;
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

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 48; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
