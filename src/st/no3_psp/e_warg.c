// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no3/no3.h"

// func_801CF58C
static void func_pspeu_09252C78(Entity* self) {
    self->velocityX = 0;
    self->ext.warg.unk86 = 0x100;
    SetStep(6);
    g_api.PlaySfx(SFX_WARG_GROWL);
    self->ext.warg.unk80 = 0x20;
}

// func_801CF5E0
static void func_pspeu_09252CD8(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    s16 temp_v0;

    // I think this could be a mistake. The == gets
    // evaluated before the & 1. In other places they use
    // GetSideToPlayer() & 1 but I think if they wanted to
    // do that here they should have put it in parentheses.
    // Makes no difference to ultimate behavior, but does mean
    // we get some weird bonus insructions (xor, sltiu) on PSP.
    if (self->facingLeft == GetSideToPlayer() & 1) {
        SetStep(5);
        return;
    }

    if (!self->ext.warg.unk86) {
        func_pspeu_09252C78(self);
        return;
    }

    temp_v0 = self->ext.warg.unk84 - self->posX.i.hi - tilemap->scrollX.i.hi;

    if (temp_v0 > 16) {
        SetStep(3);
        if (self->facingLeft) {
            self->ext.warg.unk7C = 0;
        } else {
            self->ext.warg.unk7C = 1;
        }
    } else if (temp_v0 < -16) {
        SetStep(3);
        if (self->facingLeft) {
            self->ext.warg.unk7C = 1;
        } else {
            self->ext.warg.unk7C = 0;
        }
    } else {
        SetStep(7);
    }

    self->ext.warg.unk80 = 0;
    self->ext.warg.unk82 = 32;
}

// func_801CF6D8
static void func_pspeu_09252E60(Entity* self) {
    u16 xDist = GetDistanceToPlayerX();

    if (self->ext.warg.unk86) {
        if (xDist < 0x60) {
            self->ext.warg.unk86 -= 2;
            if (self->ext.warg.unk86 < 0) {
                self->ext.warg.unk86 = 0;
            }
        } else {
            self->ext.warg.unk86--;
        }
    }
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_warg", EntityWarg);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_warg", EntityUnkId4B);

// clumsy thing, linter splits the line which breaks INCLUDE_ASM
// clang-format off
INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_warg", EntityWargExplosionPuffTransparent);
// clang-format on
