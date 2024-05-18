// Weapon ID #37. Used by weapons:
// Short sword, Jewel sword, Stone sword, Unknown#198
#include "weapon_private.h"
#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_037", EntityWeaponAttack);

extern u8 D_107000_8017A6E4[6][8];

s32 func_107000_8017ADF8(Primitive* prim, s32 x, s32 y) {
    s32 size;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
    u8* uvPtr;

    // Should be able to do this as an array access but nope
    uvPtr = &D_107000_8017A6E4;
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

extern s16 D_107000_8017A714[];

void func_107000_8017AEF0(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.unkAC - 0xA7;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_107000_8017A714[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_107000_8017A714[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_107000_8017A714[idx * 4 + 2] * 2 / 3);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_107000_8017A714[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_107000_8017A714[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_107000_8017A714[idx * 4 + 2] * 2 / 3;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_107000_8017A714[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_107000_8017A714[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_107000_8017A714[idx * 4 + 3] * 2 / 3;
    }
}

void func_107000_8017B0AC(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.unkAC - 0xA7;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_107000_8017A714[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_107000_8017A714[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_107000_8017A714[idx * 4 + 2] / 2);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_107000_8017A714[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_107000_8017A714[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_107000_8017A714[idx * 4 + 2] / 2;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_107000_8017A714[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_107000_8017A714[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_107000_8017A714[idx * 4 + 3] / 2;
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_037", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_037", func_ptr_80170008);

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 37; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
