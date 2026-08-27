// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", EntityBreakable);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", DecreaseBrightness);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A4594);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A4F14);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A367C);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A37B4);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A399C);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A3BE0);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A4028);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A9208_from_bo6);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_8019DB9C);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_8019EADC);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_8019EE30);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_8019F1CC);

void func_us_8019FA78(Entity* self) {
    extern u16 D_us_80180540;
    extern u32 D_pspeu_0926C0A0;
    extern s32 D_pspeu_0926C068;

    self->palette = (u16)D_pspeu_0926C0A0;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180540);
        self->animCurFrame = 0x11;
        /* fall through */
    case 1:
        self->animCurFrame = 0x11;
        break;
    }

    if (D_pspeu_0926C068 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

void func_us_8019FB04(Entity* self) {
    extern s32 D_pspeu_0926C0A0;
    extern u8* D_pspeu_0926B500[];
    extern s32 D_pspeu_0926C068;
    extern Entity g_Entities[256];
    extern u16 D_us_80180540;
    extern void InitializeEntity(u16*);

    u8* anim;
    Entity* source;

    self->palette = D_pspeu_0926C0A0;
    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180540);
        /* fall through */
    case 1:
        anim = D_pspeu_0926B500[self->params];
        AnimateEntity(anim, self);
        source = &g_Entities[80];
        self->posX.i.hi = source->posX.i.hi;
        self->posY.i.hi = source->posY.i.hi;
        break;
    }

    if (D_pspeu_0926C068 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_8019FBC0);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_8019FCB4);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A01A4);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A0710);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A0860);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A0AB4);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A0DC0);

void func_us_801A1150(Entity* self) {
    extern u16 D_us_80180540;
    extern u8 D_us_80180724;
    extern u8 D_pspeu_0926B410;
    s32 var_v0;

    if (!self->step) {
        InitializeEntity(&D_us_80180540);
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
    self->opacity = (u8)var_v0;
    if (var_v0 == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_D4E8", func_us_801A11DC);

void func_us_801A1B38(Entity* self) {
    Entity* real;

    if (*(s32*)0x0926C060 & 1) {
        DestroyEntity(self);
        return;
    }

    if (!self->step) {
        InitializeEntity((u16*)((u8*)(void*)func_us_801A1B38 + 0x80F8));
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }

    AnimateEntity((u8*)((u8*)(void*)func_us_801A1B38 + 0x1E620), self);

    real = self->ext.succubus.real;
    self->posX.i.hi = real->posX.i.hi;
    self->posY.i.hi = real->posY.i.hi + 0xC;

    if (*(s32*)0x0926C098 == 5) {
        DestroyEntity(self);
    }
}
