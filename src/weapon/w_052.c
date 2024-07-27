// Weapon ID #52. Used by weapons:
// Alucard shield, Unknown#214
#include "weapon_private.h"
#include "shared.h"

extern u8 D_170000_8017ABC4[];
extern f32 D_170000_8017CBD0[11][4];

INCLUDE_ASM("weapon/nonmatchings/w_052", EntityWeaponAttack);

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 52; }

INCLUDE_ASM("weapon/nonmatchings/w_052", EntityWeaponShieldSpell);

s32 func_ptr_80170004(Entity* self) {
    Primitive* prim;
    s16 playerY;
    s16 primWidth;
    s16 primXCenter;
    s16 primYCenter;
    u16 playerX;
    s16 primHeight;
    u8* uvPtr;

    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 11);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        if (g_HandId) {
            self->ext.shield.unk86 = 0x129;
            self->ext.shield.unk7D = 0x80;
        } else {
            self->ext.shield.unk86 = 0x111;
            self->ext.shield.unk7D = 0;
        }
        uvPtr = &D_170000_8017ABC4;
        playerX = PLAYER.posX.i.hi;
        playerY = PLAYER.posY.i.hi - 8;
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 11; i++) {
            prim->u0 = prim->u2 = *uvPtr++;
            prim->v0 = prim->v1 = *uvPtr++;
            prim->u1 = prim->u3 = *uvPtr++;
            prim->v2 = prim->v3 = *uvPtr++;
            prim->v0 += self->ext.shield.unk7D;
            prim->v1 += self->ext.shield.unk7D;
            prim->v2 += self->ext.shield.unk7D;
            prim->v3 += self->ext.shield.unk7D;
            prim->tpage = 0x19;
            prim->clut = self->ext.shield.unk86 + i;
            prim->priority = self->zPriority - 2;
            prim->drawMode = DRAW_DEFAULT;
            prim->r0 = (rand() & 0xF) + 1;
            D_170000_8017CBD0[i][0].i.hi = playerX;
            D_170000_8017CBD0[i][1].i.hi = playerY;
            D_170000_8017CBD0[i][2].val = (rand() * 6) + FIX(-1.5);
            D_170000_8017CBD0[i][3].val = FIX(-2) - (rand() * 4);
            prim = prim->next;
        }
        self->ext.shield.unk94 = 0x20;
        self->ext.shield.unk80 = 0x20;
        self->step++;
        break;
    case 1:
        self->ext.shield.unk94 += 0x10;
        if (self->ext.shield.unk94 > 0xC0) {
            self->ext.shield.unk94 = 0xC0;
        }
        for (i = 0; i < 11; i++) {
            D_170000_8017CBD0[i][0].val += D_170000_8017CBD0[i][2].val;
            D_170000_8017CBD0[i][1].val += D_170000_8017CBD0[i][3].val;
            D_170000_8017CBD0[i][3].val += 0x2000;
        }
        if (--self->ext.shield.unk80 == 0) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 11; i++) {
                prim->g0 = 1;
                prim = prim->next;
            }
            self->ext.shield.unk80 = 0x60;
            self->step++;
        }
        break;
    case 2:
        if ((self->ext.shield.unk80 >= 0x48) &&
            (self->ext.shield.unk80 % 4 == 0)) {
            g_api.PlaySfx(SFX_SUBWPN_THROW);
        }
        if (--self->ext.shield.unk80 == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 11; i++) {
        switch (prim->g0) {
        case 0:
            primXCenter = D_170000_8017CBD0[i][0].i.hi;
            primYCenter = D_170000_8017CBD0[i][1].i.hi;
            if (i == 6) {
                primHeight = self->ext.shield.unk94 * 12 / 256;
            } else {
                primHeight = self->ext.shield.unk94 * 16 / 256;
            }
            primWidth = self->ext.shield.unk94 * 12 / 256;
            prim->x0 = prim->x2 = primXCenter - primWidth;
            prim->x1 = prim->x3 = primXCenter + primWidth;
            prim->y0 = prim->y1 = primYCenter - primHeight;
            prim->y2 = prim->y3 = primYCenter + primHeight;
            break;
        case 1:
            if (--prim->r0 == 0) {
                prim->g0++;
            }
            break;
        case 2:
            if ((prim->x1 - prim->x0) >= 5) {
                prim->x0++;
                prim->x1--;
            } else {
                prim->x0 = prim->x1 - 2;
            }
            prim->y0 -= 18;
            prim->y2 -= 6;
            prim->y1 = prim->y0;
            prim->y3 = prim->y2;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            if (prim->y2 < 0) {
                prim->g0++;
            }
            break;
        case 3:
            prim->drawMode = DRAW_HIDE;
            break;
        }
        prim = prim->next;
    }
}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
