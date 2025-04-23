// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"

// Entity 13. Made by blueprint 13. That's from subweapon 12.
// That's the crash for subweapon 4. That's the cross.
static u16 crash_cross_img_data[] = {
    0x94A5, 0x98C6, 0x9CE7, 0xA108, 0xA529, 0xA94A, 0xAD6B, 0xB18C,
    0xB5AD, 0xB9CE, 0xBDEF, 0xC210, 0xC631, 0xCA52, 0xCE73, 0xD294,
    0xD6B5, 0xDAD6, 0xDEF7, 0xE318, 0xE318, 0xE318, 0xE318, 0xE318,
    0xE318, 0xE318, 0xE318, 0xE318, 0xE318, 0xDEF7, 0xDAD6, 0xD6B5,
    0xD294, 0xCE73, 0xCA52, 0xC631, 0xC210, 0xBDEF, 0xB9CE, 0xB5AD,
    0xB18C, 0xAD6B, 0xA94A, 0xA529, 0xA108, 0x9CE7, 0x98C6, 0x94A5};
static RECT crash_cross_img_vram = {0x0301, 0x01F8, 0x0030, 0x0001};
void RicEntitySubwpnCrashCross(Entity* self) {
    s16 psp_s4;
    s16 psp_s3;
    s16 right;
    s16 left;
    Primitive* prim;

    psp_s4 = 3;
    psp_s3 = 1;
    self->posY.i.hi = 0x78;
    self->posX.i.hi = PLAYER.posX.i.hi;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->ext.crashcross.unk80 = 1;
        self->zPriority = 0xC2;
        self->ext.crashcross.subweaponId = PL_W_CRASH_CROSS;
        RicSetSubweaponParams(self);
        LoadImage(&crash_cross_img_vram, (u_long*)crash_cross_img_data);
        g_api.PlaySfx(SFX_CRASH_CROSS);
        g_api.PlaySfx(SFX_TELEPORT_BANG_B);
        self->step++;
        break;
    case 1:
        self->ext.crashcross.unk7E.val += psp_s4;
        self->ext.crashcross.unk82 += psp_s4 * 2;
        if (self->ext.crashcross.unk7E.i.lo >= 0x70) {
            RicCreateEntFactoryFromEntity(self, BP_CRASH_CROSSES_ONLY, 0);
            RicCreateEntFactoryFromEntity(self, BP_CRASH_CROSS_PARTICLES, 0);
            self->step++;
        }
        break;
    case 2:
        if (g_Timer & 1) {
            self->ext.crashcross.unk7C += psp_s3;
            self->ext.crashcross.unk80 += psp_s3 * 2;
            if (self->ext.crashcross.unk80 >= 0x2C) {
                self->step++;
                self->ext.crashcross.unk84 = 0x80;
            }
        }
        break;
    case 3:
        if (--self->ext.crashcross.unk84 == 0) {
            g_api.func_801027C4(0);
            left = self->posX.i.hi - self->ext.crashcross.unk7C;
            if (left < 0) {
                left = 0;
            }
            right = self->posX.i.hi + self->ext.crashcross.unk7C;
            if (right > 0xFF) {
                right = 0xFF;
            }
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            self->step++;
        }
        break;
    case 4:
        psp_s3 *= 3;
        left = abs(self->posX.i.hi - 0x80);
        psp_s3 = psp_s3 * (left + 0x80) / 112;
        self->ext.crashcross.unk7C += psp_s3;

        left = self->posX.i.hi - self->ext.crashcross.unk7C;
        if (left < 0) {
            left = 0;
        }
        right = self->posX.i.hi + self->ext.crashcross.unk7C;
        if (right > 0xFF) {
            right = 0xFF;
        }
        if (right - left > 0xF8) {
            g_Player.unk4E = 1;
            DestroyEntity(self);
            return;
        }
        break;
    }
    self->hitboxOffY = 0;
    self->hitboxHeight = self->ext.crashcross.unk7E.val;
    if (self->step == 4) {
        self->hitboxWidth = (right - left) >> 1;
        self->hitboxOffX = ((left + right) >> 1) - self->posX.i.hi;
    } else {
        self->hitboxWidth = self->ext.crashcross.unk7C;
        self->hitboxOffX = 0;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - self->ext.crashcross.unk7C;
    prim->y1 = prim->y0 = self->posY.i.hi - self->ext.crashcross.unk7E.val;
    prim->x1 = prim->x3 = prim->x0 + self->ext.crashcross.unk80;
    prim->y2 = prim->y3 = prim->y0 + self->ext.crashcross.unk82;
    prim->u0 = prim->u2 = 1;
    prim->u1 = prim->u3 = 0x30;
    prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
    prim->tpage = 0x11C;
    if (self->step == 4) {
        prim->x0 = prim->x2 = left;
        prim->x1 = prim->x3 = right;
    }
    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
    prim->priority = self->zPriority;
    g_Player.timers[PL_T_3] = 2;
}

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/pl_subweapon_cross", RicEntityRevivalColumn);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/pl_subweapon_cross", RicEntitySubwpnCross);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/pl_subweapon_cross", func_80169C10);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/pl_subweapon_cross", RicEntitySubwpnCrossTrail);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/pl_subweapon_cross", RicEntitySubwpnCrashCrossParticles);
