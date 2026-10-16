// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rlib/rlib.h"

INCLUDE_ASM("st/rlib_psp/nonmatchings/rlib_psp/unk_F0D8", func_pspeu_09246758);

INCLUDE_ASM("st/rlib_psp/nonmatchings/rlib_psp/unk_F0D8", func_us_801AE534);

INCLUDE_ASM("st/rlib_psp/nonmatchings/rlib_psp/unk_F0D8", func_us_801AED4C);

extern EInit D_us_80180688;
extern AnimationFrame D_us_80181888;

void func_us_801AEFE0(Entity* self) {
    Entity* parent;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180688);
        self->blendMode = BLEND_TRANSP;
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_B);
        /* fall through */
    case 1:
        parent = self->ext.et_801AEFE0.parent;
        self->posX.val = parent->posX.val;
        self->posY.val = parent->posY.val;
        if (AnimateEntity(&D_us_80181888, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_8018067C;
extern AnimationFrame D_us_8018189C;

void func_us_801D8D44_from_no4(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018067C);
        if (self->facingLeft) {
            self->velocityX = FIX(6);
        } else {
            self->velocityX = FIX(-6);
        }
        /* fall through */
    case 1:
        MoveEntity();
        AnimateEntity(&D_us_8018189C, self);
        if (self->flags & FLAG_DEAD) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/rlib_psp/nonmatchings/rlib_psp/unk_F0D8", func_us_801AF11C);
