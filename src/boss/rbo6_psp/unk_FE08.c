// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"

extern s32 D_psp_E_UNK_18;
extern s32 D_psp_E_UNK_19;
extern s32 D_psp_E_UNK_1A;
extern s32 D_psp_E_UNK_1C;
extern s32 D_psp_E_UNK_1E;
extern s32 D_psp_E_UNK_20;
extern s32 D_psp_E_UNK_23;
extern s32 D_psp_E_UNK_24;
extern s32 D_psp_E_UNK_27;
extern AnimateEntityFrame D_pspeu_0926B3F0[];
extern AnimateEntityFrame D_pspeu_0926B3F8[];
extern AnimateEntityFrame D_pspeu_0926B4A0[];
extern u16 D_pspeu_0926B548[];
extern s8 D_pspeu_0926B580;
extern s32 D_pspeu_0926C060;
extern s32 D_pspeu_0926C068;
extern s32 D_pspeu_0926C070;
extern s32 D_pspeu_0926C078;
extern s32 D_pspeu_0926C080;
extern s32 D_pspeu_0926C088;
extern s32 D_pspeu_0926C090;
extern s32 D_pspeu_0926C098;
extern s32 D_pspeu_0926C0A0;
extern s32 D_pspeu_0926C6B8;
extern EInit g_EInitDraculaLvl98;

void func_us_8019DB9C(Entity* self) {
    s32 distFromCenter;
    Entity* other;
    s16 angle;
    s32 xVar;
    s32 yVar;
    s32 i;

    if (self->hitFlags & 3) {
        if ((Random() & 7) == 0) {
            if (Random() & 1) {
                g_api.PlaySfx(SFX_DRACULA_PAIN_A);
            } else {
                g_api.PlaySfx(SFX_DRACULA_PAIN_B);
            }
        }
    }
    if ((self->flags & FLAG_DEAD) && (self->step != 12)) {
        SetStep(12);
    }
    switch (self->step) { /* switch 1; irregular */
    case 0x0:             /* switch 1 */
        InitializeEntity(g_EInitDraculaLvl98);
        self->zPriority = 0x80;
        self->hitboxOffY = -4;
        other = &g_Entities[81];
        for (i = 0; i < 5; i++, other++) {
            CreateEntityFromCurrentEntity(D_psp_E_UNK_19, other);
            other->zPriority = self->zPriority + 1;
            other->params = i;
        }
        other = &g_Entities[86];
        CreateEntityFromCurrentEntity(D_psp_E_UNK_1A, other);
        other->params = 0;
        other->zPriority = self->zPriority + 3;
        other += 2;
        CreateEntityFromCurrentEntity(D_psp_E_UNK_1A, other);
        other->params = 1;
        other->zPriority = self->zPriority + 3;
        other = &g_Entities[86];
        self->nextPart = other + 1;
        self->parent = NULL;
        other = &g_Entities[90];
        CreateEntityFromCurrentEntity(D_psp_E_UNK_18, other);
        other->zPriority = self->zPriority + 1;
        other = &g_Entities[91];
        for (i = 0; i < 3; i++, other += 6) {
            CreateEntityFromCurrentEntity(D_psp_E_UNK_1C, other);
            other->params = i;
            other->zPriority = self->zPriority + 6;
        }
        other = &g_Entities[109];
        CreateEntityFromCurrentEntity(D_psp_E_UNK_1E, other);
        other->zPriority = self->zPriority;
        SetStep(1);
        /* fallthrough */
    case 0x1: /* switch 1 */
        self->hitboxState = 0;
        D_pspeu_0926C068 = 1;
        switch (self->step_s) { /* switch 2; irregular */
        case 0:                 /* switch 2 */
            self->animCurFrame = 1;
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0;
            if (D_pspeu_0926C6B8 & 0x20) {
                self->ext.ILLEGAL.s16[2] = 0x80;
                self->step_s++;
            }
            break;
        case 1: /* switch 2 */
            AnimateEntity(&D_pspeu_0926B3F0, self);
            if (!--self->ext.ILLEGAL.s16[2]) {
                self->step_s++;
            }
            break;
        case 2: /* switch 2 */
            AnimateEntity(&D_pspeu_0926B3F0, self);
            self->opacity++;
            if ((self->opacity) >= 0x80) {
                self->drawFlags = ENTITY_DEFAULT;
                self->step_s++;
            }
            break;
        case 3: /* switch 2 */
            AnimateEntity(&D_pspeu_0926B3F0, self);
            if (D_pspeu_0926C6B8 & 2) {
                g_api.TimeAttackController(
                    TIMEATTACK_EVENT_UNUSED_28, TIMEATTACK_SET_VISITED);
                g_api.PlaySfx(SFX_DRACULA_BEHOLD_MY_TRUE_FORM);
                SetStep(2);
            }
            break;
        }
        break;
    case 0xC:                   /* switch 1 */
        switch (self->step_s) { /* switch 3; irregular */
        case 0:                 /* switch 3 */
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_UNUSED_28, TIMEATTACK_SET_RECORD);
            D_pspeu_0926C060 |= 1;
            self->hitboxState = 0;
            self->palette = 0x200;
            self->flags &= ~0xF;
            self->step_s++;
            break;
        case 1: /* switch 3 */
            other = &g_Entities[200];
            CreateEntityFromCurrentEntity(D_psp_E_UNK_27, other);
            other->flags |= FLAG_UNK_10000;
            other->params = 1;
            g_unkGraphicsStruct.unk28 = 0xFF;
            self->step_s++;
            break;
        case 2:
            // Distance from center
            xVar = 128 - self->posX.i.hi;
            yVar = 138 - self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            // Set velocity to push us back toward the center
            // Note: this angle stuff is a bit excessive, they could
            // have just had velocities as function of distances.
            self->velocityX = (rcos(angle) << 0xF) >> 0xC;
            self->velocityY = (rsin(angle) << 0xF) >> 0xC;
            MoveEntity();
            distFromCenter = SquareRoot0((xVar * xVar) + (yVar * yVar));
            if (distFromCenter < 3) {
                self->step_s++;
            }
            break;
        case 3: /* switch 3 */
            D_pspeu_0926C060 |= 2;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            break;
        case 4: /* switch 3 */
            // Test g_timer, but don't actually do anything. But PSP
            // needs something in the body, so I use "self".
            if (!(g_Timer & 0xF)) {
                self;
            }
            break;
        }
        break;
    case 0x2: /* switch 1 */
        AnimateEntity(&D_pspeu_0926B3F0, self);
        D_pspeu_0926C068 = 1;
        self->hitboxState = 0;
        switch (self->step_s) { /* switch 4; irregular */
        case 0:                 /* switch 4 */
            self->velocityY = FIX(6.0);
            self->step_s++;
            /* fallthrough */
        case 1: /* switch 4 */
            MoveEntity();
            self->velocityY -= FIX(0.25);
            if (self->posY.i.hi < -0x60) {
                SetStep(3);
            }
            break;
        }
        break;
    case 0x3: /* switch 1 */
        AnimateEntity(&D_pspeu_0926B4A0, self);
        D_pspeu_0926C068 = 0;
        self->hitboxState = 2;
        switch (self->step_s) { /* switch 5; irregular */
        case 0:                 /* switch 5 */
            self->velocityX = 0;
            self->velocityY = FIX(1.25);
            self->posY.i.hi = -0x50;
            self->posX.i.hi = 0x80;
            self->zPriority = 0x80;
            self->ext.ILLEGAL.s16[2] = 0;
            self->step_s++;
            /* fallthrough */
        case 1: /* switch 5 */
            if (!(self->ext.ILLEGAL.s16[2] & 0x3F)) {
                g_api.PlaySfx(SFX_DRACULA_FLY_IN);
            }
            self->ext.ILLEGAL.s16[2]++;
            MoveEntity();
            if (self->posY.i.hi > 0x90) {
                SetStep(4);
            }
            break;
        }
        break;
    case 0x4: /* switch 1 */
        if (!self->step_s) {
            self->ext.ILLEGAL.s16[2] = 0x40;
            self->step_s++;
        }
        AnimateEntity(&D_pspeu_0926B4A0, self);
        D_pspeu_0926C068 = 0;
        self->hitboxState = 2;
        MoveEntity();
        angle = self->ext.ILLEGAL.s16[3] += 0x20;
        self->velocityY = (rcos(angle) << 0xF) >> 0xC;
        if (!--self->ext.ILLEGAL.s16[2]) {
            SetStep(D_pspeu_0926B548[self->ext.ILLEGAL.u8[8]]);
            self->ext.ILLEGAL.u8[8]++;
            self->ext.ILLEGAL.u8[8] &= 3;
        }
        break;
    case 0x5: /* switch 1 */
        AnimateEntity(&D_pspeu_0926B4A0, self);
        D_pspeu_0926C068 = 0;
        self->hitboxState = 2;
        MoveEntity();
        angle = self->ext.ILLEGAL.s16[3] += 0x20;
        self->velocityY = (rcos(angle) << 0xF) >> 0xC;
        switch (self->step_s) { /* switch 6; irregular */
        case 0:                 /* switch 6 */
            D_pspeu_0926C070 = 1;
            other = &g_Entities[129];
            CreateEntityFromCurrentEntity(D_psp_E_UNK_20, other);
            other->zPriority = self->zPriority + 3;
            self->step_s++;
            /* fallthrough */
        case 1: /* switch 6 */
            if (D_pspeu_0926C070 == 2) {
                self->step_s++;
            }
            break;
        case 2: /* switch 6 */
            D_pspeu_0926C070 = 3;
            g_api.PlaySfx(SFX_DRACULA_SQUISH_GRUNT);
            self->step_s++;
            /* fallthrough */
        case 3: /* switch 6 */
            if (D_pspeu_0926C070 == 5) {
                self->ext.ILLEGAL.s16[2] = 0xA0;
                self->step_s++;
            }
            break;
        case 4: /* switch 6 */
            if (!--self->ext.ILLEGAL.s16[2]) {
                D_pspeu_0926C078++;
                if (D_pspeu_0926C078 > 7) {
                    D_pspeu_0926C078 = 0;
                }
                D_pspeu_0926C070 = 0;
                SetStep(6);
            }
            break;
        }
        break;
    case 0x6: /* switch 1 */
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = FIX(1.0);
            g_api.PlaySfx(SFX_DRACULA_LAUGH_A);
            self->step_s++;
        }
        AnimateEntity(&D_pspeu_0926B4A0, self);
        D_pspeu_0926C068 = 0;
        self->hitboxState = 2;
        MoveEntity();
        self->velocityY -= FIX(0.0625);
        if (self->posY.i.hi < -0x40) {
            SetStep(7);
        }
        break;
    case 0x7: /* switch 1 */
        if (!self->step_s) {
            self->posX.i.hi = 0x80;
            self->posY.i.hi = -0x40;
            self->velocityX = 0;
            self->velocityY = FIX(3.0);
            self->zPriority = 0x80;
            self->step_s++;
        }
        AnimateEntity(&D_pspeu_0926B3F0, self);
        D_pspeu_0926C068 = 1;
        self->hitboxState = 0;
        MoveEntity();
        self->velocityY -= self->velocityY >> 6;
        if (self->posY.i.hi > 0x70) {
            SetStep(8);
        }
        break;
    case 0x8: /* switch 1 */
        if (!self->step_s) {
            D_pspeu_0926C080 = 0;
            self->step_s++;
        }
        D_pspeu_0926C068 = 1;
        self->hitboxState = 0;
        if (!AnimateEntity(D_pspeu_0926B3F8, self)) {
            SetStep(2);
        }
        if ((!self->poseTimer) && (self->pose == 2)) {
            other = &g_Entities[132];
            CreateEntityFromEntity(D_psp_E_UNK_23, self, other);
            other->zPriority = self->zPriority + 1;
        }
        if ((!self->poseTimer) && (self->pose == 3)) {
            g_api.PlaySfx(SFX_DRACULA_MONSTER_MAGIC_ATTACK);
            D_pspeu_0926C080 = 1;
        }
        break;
    case 0x9: /* switch 1 */
        AnimateEntity(D_pspeu_0926B4A0, self);
        D_pspeu_0926C068 = 0;
        self->hitboxState = 2;
        MoveEntity();
        angle = self->ext.ILLEGAL.s16[3] += 0x20;
        self->velocityY = (rcos(angle) << 0xF) >> 0xC;
        switch (self->step_s) { /* switch 7; irregular */
        case 0:                 /* switch 7 */
            self->ext.ILLEGAL.u8[9] = 4;
            self->step_s++;
            /* fallthrough */
        case 1: /* switch 7 */
            other = &PLAYER;
            if (other->posX.i.hi < 0x80) {
                D_pspeu_0926C088 = 1;
                self->velocityX = FIX(-0.5);
            } else {
                D_pspeu_0926C088 = 2;
                self->velocityX = FIX(0.5);
            }
            self->ext.ILLEGAL.s16[2] = 0x28;
            self->step_s++;
            /* fallthrough */
        case 2: /* switch 7 */
            self->velocityX -= self->velocityX >> 4;
            if (!--self->ext.ILLEGAL.s16[2]) {
                if (D_pspeu_0926C088 == 1) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
                self->step_s++;
            }
            break;
        case 3: /* switch 7 */
            self->velocityX -= self->velocityX >> 4;
            if (D_pspeu_0926C088 == 3) {
                self->step_s++;
            }
            break;
        case 4: /* switch 7 */
            xVar = 0x80 - self->posX.i.hi;
            if (xVar > 0) {
                self->velocityX = FIX(1.125);
            }
            if (xVar < 0) {
                self->velocityX = FIX(-1.125);
            }
            if (abs(xVar) < 3) {
                self->velocityX = 0;
                if (!--self->ext.ILLEGAL.u8[9]) {
                    D_pspeu_0926C088 = 0;
                    SetStep(4);
                } else {
                    self->step_s = 1;
                }
            }
            break;
        }
        break;
    case 0xA: /* switch 1 */
        AnimateEntity(&D_pspeu_0926B4A0, self);
        D_pspeu_0926C068 = 0;
        self->hitboxState = 2;
        MoveEntity();
        angle = self->ext.ILLEGAL.s16[3] += 0x20;
        self->velocityY = (rcos(angle) << 0xF) >> 0xC;
        switch (self->step_s) { /* switch 8; irregular */
        case 0:                 /* switch 8 */
            D_pspeu_0926C090 = 1;
            self->step_s++;
            /* fallthrough */
        case 1: /* switch 8 */
            if (D_pspeu_0926C090 == 4) {
                D_pspeu_0926C090 = 0;
                SetStep(4);
            }
            break;
        }
        break;
    case 0xB: /* switch 1 */
        AnimateEntity(&D_pspeu_0926B4A0, self);
        D_pspeu_0926C068 = 0;
        self->hitboxState = 2;
        switch (self->step_s) { /* switch 9; irregular */
        case 0:                 /* switch 9 */
            D_pspeu_0926C098 = 1;
            self->step_s++;
            /* fallthrough */
        case 1: /* switch 9 */
            if (D_pspeu_0926C098 == 4) {
                self->ext.ILLEGAL.s16[2] = 0x40;
                self->step_s++;
            }
            break;
        case 2: /* switch 9 */
            if (!(self->ext.ILLEGAL.s16[2] & 0xF)) {
                other = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(D_psp_E_UNK_24, other);
                    other->zPriority = self->zPriority + 8;
                }
            }
            if (!--self->ext.ILLEGAL.s16[2]) {
                self->ext.ILLEGAL.s16[2] = 0x40;
                self->step_s++;
            }
            break;
        case 3: /* switch 9 */
            if (!--self->ext.ILLEGAL.s16[2]) {
                D_pspeu_0926C098 = 5;
                self->step_s++;
            }
            break;
        case 4: /* switch 9 */
            D_pspeu_0926C098 = 0;
            SetStep(4);
            break;
        }
        break;
    case 0xFF: /* switch 1 */
#include "../../st/pad2_anim_debug.h"
    }
    D_pspeu_0926C0A0 = self->palette;
}

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_8019EADC);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_8019EE30);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_8019F1CC);

void func_us_8019FA78(Entity* self) {
    extern u16 D_us_80180540;
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

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_8019FBC0);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_8019FCB4);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_801A01A4);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_801A0710);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_801A0860);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_801A0AB4);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_801A0DC0);

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

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_801A11DC);

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
