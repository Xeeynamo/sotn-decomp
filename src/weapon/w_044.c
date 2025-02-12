// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #44. Used by weapons:
// Heart Refresh
#include "weapon_private.h"
#include "w_044_1.h"
#include "w_044_2.h"
#define g_Animset w_044_1
#define g_Animset2 w_044_2
#include "sfx.h"

static u16 D_138000_8017A040[] = {
    COLOR16(0, 0, 0, 0),    COLOR16(31, 0, 0, 1),   COLOR16(24, 16, 4, 1),
    COLOR16(31, 24, 4, 1),  COLOR16(13, 9, 3, 1),   COLOR16(20, 13, 7, 1),
    COLOR16(24, 18, 12, 1), COLOR16(25, 23, 20, 1), COLOR16(4, 5, 21, 1),
    COLOR16(7, 9, 31, 1),   COLOR16(4, 6, 4, 1),    COLOR16(8, 9, 8, 1),
    COLOR16(13, 13, 12, 1), COLOR16(16, 18, 18, 1), COLOR16(21, 22, 22, 1),
    COLOR16(24, 27, 30, 1), COLOR16(0, 0, 0, 0),    COLOR16(2, 0, 0, 1),
    COLOR16(3, 0, 0, 1),    COLOR16(5, 0, 0, 1),    COLOR16(7, 1, 0, 1),
    COLOR16(8, 1, 0, 1),    COLOR16(10, 1, 1, 1),   COLOR16(12, 2, 1, 1),
    COLOR16(14, 2, 1, 1),   COLOR16(15, 2, 1, 1),   COLOR16(17, 3, 1, 1),
    COLOR16(19, 3, 2, 1),   COLOR16(20, 3, 2, 1),   COLOR16(22, 4, 2, 1),
    COLOR16(24, 4, 2, 1),   COLOR16(26, 5, 3, 1),   COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
};

static s32 D_138000_8017A260[] = {
    0x000, 0x100, 0x200, 0x300, 0x400, 0x500, 0x600, 0x700,
    0x800, 0x900, 0xA00, 0xB00, 0xC00, 0xD00, 0xE00, 0xF00};

static u16* g_WeaponCluts[] = {D_138000_8017A040};
static s32 g_HandId = HAND_ID;

#include "shared.h"

extern s32 D_80097420;
extern s32 D_138000_8017A260[];

void EntityWeaponAttack(Entity* self) {
    const int PrimCount = 17;
    bool doLastblock;
    Primitive* prim;
    s16 selfY;
    s16 base;
    s16 selfY_bottom;
    s16 offset;
    u16 vCoord;
    s16 sine;
    s16 angle;
    s32 i;
    s16 lastBlockYShift;
    u16 clut;

    clut = 0x110;
    vCoord = 0;
    if (g_HandId != 0) {
        clut += 0x18;
        vCoord += 0x80;
    }

    doLastblock = false;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimBuffers(PRIM_GT4, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < (PrimCount - 1); i++) {
            if (i < 8) {
                prim->u1 = prim->u3 = (7 - i) * 8 + 0x40;
                prim->u0 = prim->u2 = prim->u1 + 7;
            } else {
                prim->u0 = prim->u2 = (i - 8) * 8 + 0x40;
                prim->u1 = prim->u3 = prim->u0 + 7;
            }
            if (i == 0 || i == 15) {
                prim->u0 = prim->u2 = 0x7A;
                prim->u1 = prim->u3 = 0x7C;
            }

            prim->v0 = prim->v1 = vCoord + 0x48;
            prim->v2 = prim->v3 = vCoord + 0x7F;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim->priority = 0x1BC;
            prim->clut = clut;
            prim->tpage = 0x19;
            prim = prim->next;
        }

        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x37;
        prim->v0 = prim->v1 = vCoord + 0x48;
        prim->v2 = prim->v3 = vCoord + 0x7F;
        prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
            prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 = prim->g3 =
                0x80;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_COLORS | DRAW_TRANSP;
        prim->priority = 0x1BE;
        prim->clut = clut + 1;
        prim->tpage = 0x19;
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->ext.weapon.unk8A = 0x40;
        self->ext.weapon.unk94 = 0x180;
        self->ext.weapon.unk90 = 0;
        self->ext.weapon.unk82 = 0x40;
        self->posY.i.hi = 64;
        g_api.PlaySfx(SFX_TRANSFORM_3X);
        g_unkGraphicsStruct.unk20 = 2;
        self->step++;
        break;
    case 1:
        self->ext.weapon.unk90 += 4;
        if (self->ext.weapon.unk90 > 0x100) {
            self->ext.weapon.unk90 = 0x100;
        }
        self->ext.weapon.unk94 -= 4;
        if (self->ext.weapon.unk94 < 0x40) {
            self->step++;
        }
        break;
    case 2:
        self->ext.weapon.unk90 += 4;
        if (self->ext.weapon.unk90 > 0x100) {
            self->ext.weapon.unk90 = 0x100;
        }
        self->ext.weapon.unk94--;
        if (self->ext.weapon.unk94 < 0) {
            self->ext.weapon.unk94 = 0;
            g_api.func_80118C28(2);

            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < (PrimCount - 1); i++) {
                prim->u0 = prim->u2 = i * 8;
                prim->u1 = prim->u3 = prim->u0 + 8;
                prim->v0 = prim->v1 = vCoord + 0;
                prim->v2 = prim->v3 = vCoord + 0x47;
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }

            // BUG? this will always fail
            if (i == 15) {
                prim->u1--;
                prim->u3--;
            }

            self->ext.weapon.unk82 += 8;
            self->posY.i.hi -= 8;
            self->ext.weapon.lifetime = 32;
            self->step++;
        }
        break;
    case 3:
        if (--self->ext.weapon.lifetime == 0) {
            self->rotX = 0;
            self->rotY = 0x80;
            self->ext.weapon.unk7E = 0xA;
            self->step++;
        }
        break;
    case 4:
        doLastblock = true;
        self->rotX += self->ext.weapon.unk7E;
        self->ext.weapon.unk7E += 2;
        if (self->rotX > 0x200) {
            self->rotY--;
            if (self->rotX > 0x380) {
                g_Status.hearts += 500;
                if (g_Status.hearts >= g_Status.heartsMax) {
                    g_Status.hearts = g_Status.heartsMax;
                }
                g_api.PlaySfx(SFX_TELEPORT_BANG_B);
                self->step++;
            }
        }
        break;
    case 5:
        doLastblock = true;
        self->rotX += self->ext.weapon.unk7E;
        self->ext.weapon.unk7E += 2;
        self->rotY--;
        if (self->rotY < 0) {
            self->rotY = 0;
        }

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < (PrimCount - 1); i++) {
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }

        self->ext.weapon.unk90 -= 3;
        self->ext.weapon.unk94 += 6;
        if (self->ext.weapon.unk90 < 0) {
            D_80097420 = 0;
            self->ext.weapon.unk90 = 0;
            DestroyEntity(self);
            return;
        }
        break;
    }

    selfY = self->posY.i.hi;
    selfY_bottom = self->posY.i.hi + self->ext.weapon.unk82;
    offset = 64;
    base = 192;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < (PrimCount - 1); i++) {
        angle = D_138000_8017A260[i];
        sine = (rsin(angle) >> 5) * self->ext.weapon.unk94 / 256;
        prim->y0 = selfY + sine;
        prim->y2 = selfY_bottom + sine;

        angle = D_138000_8017A260[(i + 1) % 16];
        sine = (rsin(angle) >> 5) * self->ext.weapon.unk94 / 256;
        prim->y1 = selfY + sine;
        prim->y3 = selfY_bottom + sine;

        prim->x0 = prim->x2 = offset + ((base - offset) * i / 16);
        prim->x1 = prim->x3 = offset + ((base - offset) * (i + 1) / 16);
        angle = D_138000_8017A260[i];
        prim->r0 = prim->g0 = prim->b0 = prim->r2 = prim->g2 = prim->b2 =
            ((rsin(angle) + FIX(1.0 / 16.0)) >> 6) * self->ext.weapon.unk90 /
            256;
        angle = D_138000_8017A260[(i + 1) % 16];
        prim->r1 = prim->g1 = prim->b1 = prim->r3 = prim->g3 = prim->b3 =
            ((rsin(angle) + FIX(1.0 / 16.0)) >> 6) * self->ext.weapon.unk90 /
            256;

        D_138000_8017A260[i] += self->ext.weapon.unk8A;

        prim = prim->next;
    }

    prim->drawMode |= DRAW_HIDE;
    sine = 0x80;
    lastBlockYShift = 0x68;
    if (doLastblock) {
        prim->x0 = +(((rcos(0x600) >> 8) * self->rotX) >> 8) + sine;
        prim->y0 = -(((rsin(0x600) >> 8) * self->rotX) >> 8) + lastBlockYShift;
        prim->x1 = +(((rcos(0x200) >> 8) * self->rotX) >> 8) + sine;
        prim->y1 = -(((rsin(0x200) >> 8) * self->rotX) >> 8) + lastBlockYShift;
        prim->x2 = +(((rcos(0xA00) >> 8) * self->rotX) >> 8) + sine;
        prim->y2 = -(((rsin(0xA00) >> 8) * self->rotX) >> 8) + lastBlockYShift;
        prim->x3 = +(((rcos(0xE00) >> 8) * self->rotX) >> 8) + sine;
        prim->y3 = -(((rsin(0xE00) >> 8) * self->rotX) >> 8) + lastBlockYShift;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                self->rotY;
        prim->drawMode &= ~DRAW_HIDE;
    }
}

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 44; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
