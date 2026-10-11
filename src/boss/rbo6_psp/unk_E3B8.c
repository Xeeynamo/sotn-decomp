// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"

extern EInit D_us_80180540;
extern s32 D_pspeu_0926C060;
extern s32 D_pspeu_0926C068;
extern s32 D_pspeu_0926C0A0;
extern u8* D_pspeu_0926B500[];
extern u8 D_pspeu_0926B410;
extern s32 D_pspeu_0926C098;
extern u8 D_pspeu_0926B4F8[];

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A4F14);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A367C);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A37B4);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A399C);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A3BE0);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A4028);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A9208_from_bo6);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_8019DB9C);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_8019EADC);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_8019EE30);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_8019F1CC);

void func_us_8019FA78(Entity* self) {

    self->palette = D_pspeu_0926C0A0;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180540);
        self->animCurFrame = 0x11;
        /* fall through */
    case 1:
        self->animCurFrame = 0x11;
        break;
    }

    if (D_pspeu_0926C068) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

void func_us_8019FB04(Entity* self) {

    u8* anim;
    Entity* source;

    self->palette = D_pspeu_0926C0A0;
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180540);
        /* fall through */
    case 1:
        anim = D_pspeu_0926B500[self->params];
        AnimateEntity(anim, self);
        source = &g_Entities[80];
        self->posX.i.hi = source->posX.i.hi;
        self->posY.i.hi = source->posY.i.hi;
        break;
    }

    if (D_pspeu_0926C068) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_8019FBC0);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_8019FCB4);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A01A4);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A0710);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A0860);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A0AB4);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A0DC0);

void func_us_801A1150(Entity* self) {
    s32 var_v0;

    if (!self->step) {
        InitializeEntity(D_us_80180540);
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->drawFlags |= ENTITY_OPACITY;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }
    AnimateEntity(&D_pspeu_0926B410, self);
    var_v0 = self->opacity;
    var_v0 -= 2;
    if (var_v0 < 0) {
        var_v0 = 0;
    }
    self->opacity = var_v0;
    if (!var_v0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_E3B8", func_us_801A11DC);

void func_us_801A1B38(Entity* self) {
    Entity* real;

    if (D_pspeu_0926C060 & 1) {
        DestroyEntity(self);
        return;
    }

    if (!self->step) {
        InitializeEntity(D_us_80180540);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }

    AnimateEntity(D_pspeu_0926B4F8, self);

    real = self->ext.succubus.real;
    self->posX.i.hi = real->posX.i.hi;
    self->posY.i.hi = real->posY.i.hi + 0xC;

    if (D_pspeu_0926C098 == 5) {
        DestroyEntity(self);
    }
}
