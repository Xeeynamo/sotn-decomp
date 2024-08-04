// Weapon ID #50. Used by weapons:
// Icebrand, Unknown#181, Unknown#199, Unknown#200, Unknown#201
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_050_1.h"
#include "w_050_2.h"
#define g_Animset w_050_1
#define g_Animset2 w_050_2

INCLUDE_ASM("weapon/nonmatchings/w_050", EntityWeaponAttack);

extern u8 D_162000_8017B000[6][8];

s32 func_162000_8017B784(Primitive* prim, s32 x, s32 y) {
    s32 size;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
    u8* uvPtr;

    // Should be able to do this as an array access but nope
    uvPtr = &D_162000_8017B000;
    uvPtr += prim->b0 * 8;

    if (prim->b0 >= 3) {
        size = 4;
    } else {
        size = 6;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    left = x - size;
    top = y - size;
    right = x + size;
    bottom = y + size;

    prim->x0 = left;
    prim->y0 = top;
    prim->x1 = right;
    prim->y1 = top;
    prim->x2 = left;
    prim->y2 = bottom;
    prim->x3 = right;
    prim->y3 = bottom;

    prim->u0 = *uvPtr++;
    prim->v0 = *uvPtr++;
    prim->u1 = *uvPtr++;
    prim->v1 = *uvPtr++;
    prim->u2 = *uvPtr++;
    prim->v2 = *uvPtr++;
    prim->u3 = *uvPtr++;
    prim->v3 = *uvPtr++;
    if (!(++prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}

extern s16 D_162000_8017B030[];

void func_162000_8017B87C(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0x41;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] * 2 / 3);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] * 2 / 3;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_162000_8017B030[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] * 2 / 3;
    }
}

void func_162000_8017BA38(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0x41;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] / 2);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] / 2;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_162000_8017B030[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] / 2;
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_050", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_050", func_ptr_80170008);

INCLUDE_ASM("weapon/nonmatchings/w_050", func_ptr_8017000C);

INCLUDE_ASM("weapon/nonmatchings/w_050", func_ptr_80170010);

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 50; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
