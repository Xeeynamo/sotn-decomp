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

    idx = PLAYER.ext.player.anim - 0xA7;
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

    idx = PLAYER.ext.player.anim - 0xA7;
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

extern s16 D_107000_8017A74C[];
extern s32 D_107000_8017A758[];
extern Point16 D_107000_8017BBE8[];
extern s32 D_107000_8017BD28;

s32 func_ptr_80170004(Entity* self) {
    Point16 basePoint;
    Primitive* prim;
    s32 randy;
    s16 xVar;
    s16 yVar;
    s16 baseX;
    s16 baseY;
    s32 i;

    s16 temp_s3;
    s16 temp_s5;
    s16 temp_s0;

    s32 funcResult;

    u8 upperParams = (self->params >> 8) & 0x7F;

    switch (self->step) {
    case 0:
        for (i = 0; i < 16; i++) {
            D_107000_8017A758[i] = 0;
        }
        if (upperParams & 0x7F) {
            randy = rand() & 31; // rand int 0-31
            if (randy == 0) {
                for (i = 0; i < 16; i++) {
                    D_107000_8017A758[i] = 1;
                }
            } else {
                if (!(randy & 3)) {
                    for (i = 0; i < 16; i++) {
                        if (i % 3 == 0) {
                            D_107000_8017A758[i] = 1;
                        }
                    }
                }
                if ((randy & 3) == 3) {
                    for (i = 0; i < 16; i++) {
                        if (i % 9 == 0) {
                            D_107000_8017A758[i] = 1;
                        }
                    }
                } else {
                    for (i = 0; i < 16; i++) {
                        if (i % 5 == 0) {
                            D_107000_8017A758[i] = 1;
                        }
                    }
                }
            }
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_40000 | FLAG_UNK_20000;
        func_107000_8017B0AC(self, &basePoint, 0);
        // FAKE but makes register allocation work
        randy = basePoint.x;
        baseX = randy;
        baseY = basePoint.y;
        if (PLAYER.drawFlags & DRAW_UNK02) {
            if (0x42 < PLAYER.ext.player.anim &&
                PLAYER.ext.player.anim < 0x45) {
                self->posY.i.hi -= 1;
            } else {
                self->posY.i.hi -= 3;
            }
        }
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi;

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 8; i++) {
            temp_s5 = ((baseX * i) / 8) + xVar;
            temp_s0 = ((baseY * i) / 8) + yVar;
            temp_s3 = temp_s0 + (rand() % 10);
            temp_s0 = temp_s5 + (rand() % 4);

            D_107000_8017BBE8[i].x = temp_s0;
            D_107000_8017BBE8[i].y = temp_s3;

            prim->clut = D_107000_8017A74C[D_107000_8017BD28 % 6];
            prim->tpage = 0x1A;
            prim->g0 = prim->b1 = prim->b0 = 0;
            prim->g1 = i + 1;
            prim->g2 = 0;
            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = 0x339;
            if (rand() & 1) {
                prim->drawMode = 0x379;
            }
            prim = prim->next;
            D_107000_8017BD28++;
        }
        self->ext.timer.t = 32;
        self->step++;
        break;
    case 1:
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        switch (prim->g0) {
        case 0:
            if (--prim->g1 == 0) {
                prim->g0++;
            }
            break;
        case 1:
            xVar = D_107000_8017BBE8[i].x;
            yVar = D_107000_8017BBE8[i].y;
            funcResult = func_107000_8017ADF8(
                prim, D_107000_8017BBE8[i].x, D_107000_8017BBE8[i].y);
            D_107000_8017BBE8[i].y--;
            if (funcResult < 0) {
                prim->drawMode |= DRAW_HIDE;
                if (D_107000_8017A758[i] != 0) {
                    temp_s0 = self->posX.i.hi;
                    temp_s3 = self->posY.i.hi;
                    self->posX.i.hi = xVar;
                    self->posY.i.hi = yVar;
                    g_api.CreateEntFactoryFromEntity(
                        self, ((g_HandId + 1) << 0xC) | 64, 0);
                    self->posX.i.hi = temp_s0;
                    self->posY.i.hi = temp_s3;
                }
                prim->g0++;
                break;
            }
            prim->drawMode &= ~DRAW_HIDE;
            break;
        }
        prim = prim->next;
    }
}

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
