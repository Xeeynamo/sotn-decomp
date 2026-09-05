// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", EntityBreakable);

// decompiled in src/boss/bo1/e_explosion_flame.c
INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_8019D260_from_rcen);

void func_us_8019D330_from_rcen(Entity* self) {
    typedef struct {
        u16 animSet;
        u16 unk2;
        u16 palette;
        u8 blendMode;
        u8 unused;
        u32 animation;
    } Borbo6ParticleData;
    extern Borbo6ParticleData D_us_801806B4[];
    extern u16 g_EInitParticle;

    s16 temp_v1_3;
    s16 var_s0;
    s32 temp_a0;
    u16 temp_v1;
    u16 var_s0_2;
    Borbo6ParticleData* temp_v1_2;

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitParticle);
        temp_a0 = self->params & 0xF;
        temp_v1_2 = &D_us_801806B4[temp_a0];
        self->palette = temp_v1_2->palette + 0x2E0;
        self->blendMode = temp_v1_2->blendMode;
        self->animSet = temp_v1_2->animSet;
        self->unk5A = temp_v1_2->unk2;
        self->ext.et_801A518C.anim = (u8*)temp_v1_2->animation;
        self->step = temp_a0 + 1;
        temp_v1 = self->params;
        {
            u32 temp_v0;
            temp_v0 = temp_v1 & 0xFF00;
            if (temp_v0 != 0) {
                self->zPriority = temp_v0 >> 8;
            }
        }
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_19F);
            self->blendMode = BLEND_TRANSP;
            self->facingLeft = 1;
        }
        return;

    case 1:
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 2:
        MoveEntity();
        self->velocityY = FIX(-1.0);
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 3:
        if (self->step_s == 0) {
            self->drawFlags = ENTITY_OPACITY;
            self->drawFlags = ENTITY_OPACITY | ENTITY_ROTATE;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->rotate = rand() & 0xFFF;
            var_s0 = self->rotate;
            if (self->facingLeft) {
                var_s0 = -self->rotate;
            }
            self->velocityX = rsin((s32)var_s0) * 0x28;
            self->velocityY = -(rcos((s32)var_s0) * 0x28);
            self->ext.et_801A518C.acceleration = (Random() << 4) + 0x1000;
            self->step_s++;
        }
        MoveEntity();
        var_s0_2 = self->rotate;
        self->opacity += 0xFF;
        if (self->facingLeft) {
            var_s0_2 = -var_s0_2;
        }
        self->velocityX += (rsin((s32)(s16)var_s0_2) *
                            (s32)self->ext.et_801A518C.acceleration) >>
                           12;
        self->velocityY += (-(s32)self->ext.et_801A518C.acceleration *
                            rcos((s32)(s16)var_s0_2)) >>
                           12;
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (self->step_s == 0) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 9) + 0xFFFF0000;
            self->velocityY = FIX(-2.5);
            self->ext.et_801A518C.accelerationY = -(Random() << 4) - 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += (s32)self->ext.et_801A518C.accelerationY;
        self->opacity += 0xFF;
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    default:
        return;
    }
}

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_8019DB9C);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_8019EADC);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_8019EE30);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_8019F1CC);

void func_us_8019FA78(Entity* self) {
    extern u16 D_us_80180540;
    extern s32 D_us_801806E8;
    extern u16 D_us_80180704;

    self->palette = D_us_80180704;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180540);
        self->animCurFrame = 0x11;
        /* fall through */
    case 1:
        self->animCurFrame = 0x11;
        break;
    }

    if (D_us_801806E8 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

void func_us_8019FB04(Entity* self) {
    extern u16 D_us_80180704;
    extern s32 D_us_801806E8;
    extern u8* D_us_801807F4[];
    extern u16 D_us_80180540;
    extern void InitializeEntity(u16*);

    u16 value;

    self->palette = D_us_80180704;
    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180540);
        /* fall through */
    case 1:
        AnimateEntity(D_us_801807F4[self->params], self);
        value = g_Entities[E_BOSS_WEAPON].posX.i.hi;
        self->posX.i.hi = value;
        value = g_Entities[E_BOSS_WEAPON].posY.i.hi;
        self->posY.i.hi = value;
        break;
    }

    if (D_us_801806E8 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_8019FBC0);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_8019FCB4);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_801A01A4);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_801A0710);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_801A0860);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_801A0AB4);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_801A0DC0);

void func_us_801A1150(Entity* self) {
    extern u16 D_us_80180540;
    extern u8 D_us_80180724;
    s32 var_v0;

    if (!self->step) {
        InitializeEntity(&D_us_80180540);
        self->drawFlags = ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }
    AnimateEntity(&D_us_80180724, self);
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

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_1D690", func_us_801A11DC);

void func_us_801A1B38(Entity* self) {
    Entity* real;

    if (*(s32*)0x801806E4 & 1) {
        DestroyEntity(self);
        return;
    }

    if (!self->step) {
        InitializeEntity((u16*)((u32)func_us_801A1B38 - 0x215F8));
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }

    AnimateEntity((u8*)((u32)func_us_801A1B38 - 0x2134C), self);

    real = self->ext.succubus.real;
    self->posX.i.hi = real->posX.i.hi;
    self->posY.i.hi = real->posY.i.hi + 0xC;

    if (*(s32*)0x80180700 == 5) {
        DestroyEntity(self);
    }
}
