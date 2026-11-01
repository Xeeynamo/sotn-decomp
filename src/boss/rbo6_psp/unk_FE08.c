// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"

extern s32 D_psp_E_UNK_18;
extern s32 D_psp_E_UNK_19;
extern s32 D_psp_E_UNK_1A;
extern s32 D_psp_E_UNK_1B;
extern s32 D_psp_E_UNK_1C;
extern s32 D_psp_E_UNK_1D;
extern s32 D_psp_E_UNK_1E;
extern s32 D_psp_E_UNK_1F;
extern s32 D_psp_E_UNK_20;
extern s32 D_psp_E_UNK_21;
extern s32 D_psp_E_UNK_22;
extern s32 D_psp_E_UNK_23;
extern s32 D_psp_E_UNK_24;
extern s32 D_psp_E_UNK_25;
extern s32 D_psp_E_UNK_26;
extern s32 D_psp_E_UNK_27;
extern AnimateEntityFrame D_pspeu_0926B3F0[];
extern AnimateEntityFrame D_pspeu_0926B3F8[];
extern AnimateEntityFrame D_pspeu_0926B408[];
extern AnimateEntityFrame D_pspeu_0926B410[];
extern AnimateEntityFrame D_pspeu_0926B418[];
extern AnimateEntityFrame D_pspeu_0926B420[];
extern AnimateEntityFrame D_pspeu_0926B430[];
extern AnimateEntityFrame D_pspeu_0926B438[];
extern AnimateEntityFrame D_pspeu_0926B448[];
extern AnimateEntityFrame D_pspeu_0926B458[];
extern AnimateEntityFrame D_pspeu_0926B468[];
extern AnimateEntityFrame D_pspeu_0926B478[];
extern AnimateEntityFrame D_pspeu_0926B480[];
extern AnimateEntityFrame D_pspeu_0926B490[];
extern AnimateEntityFrame D_pspeu_0926B4A0[];
extern AnimateEntityFrame D_pspeu_0926B4A8[];
extern AnimateEntityFrame D_pspeu_0926B4E8[];
extern AnimateEntityFrame D_pspeu_0926B4F8[];
extern AnimateEntityFrame* D_pspeu_0926B500[];
extern Point16 D_pspeu_0926B518[];
extern Point16 D_pspeu_0926B530[];
extern s16 D_pspeu_0926B540[];
extern u16 D_pspeu_0926B548[];
extern s8 D_pspeu_0926B550;
extern u8 D_pspeu_0926B570[];
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

extern EInit D_us_80180540;

void func_us_8019EADC(Entity* self) {
    Entity* other;
    other = &g_Entities[80];
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi;
    if (!self->params) {
        self->posX.i.hi -= 0x34;
        self->posY.i.hi += 0x10;
    } else {
        self->posX.i.hi += 0x3B;
        self->posY.i.hi += 0x18;
    }
    self->palette = D_pspeu_0926C0A0;
    if ((D_pspeu_0926C060 & 1) && (self->step != 16)) {
        SetStep(16);
    }
    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(D_us_80180540);
        self->facingLeft = self->params;
        other = self + 1;
        CreateEntityFromCurrentEntity(D_psp_E_UNK_1B, other);
        other->params = self->params;
        other->zPriority = ((self->zPriority) + 1);
        /* fallthrough */
    case 1:                                         /* switch 1 */
        self->animCurFrame = 0xC;
        if (D_pspeu_0926C070 == 1) {
            SetStep(2);
        }
        if (D_pspeu_0926C088 == ((self->params) + 1)) {
            SetStep(3);
        }
        break;
    case 2:                                         /* switch 1 */
        switch (self->step_s) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            self->animCurFrame = 0xC;
            if (D_pspeu_0926C070 == 3) {
                self->step_s += 1;
            }
            break;
        case 1:                                     /* switch 2 */
            if ((!self->poseTimer) && (self->pose == 3)) {
                D_pspeu_0926C070 = 4;
            }
            if (AnimateEntity(&D_pspeu_0926B438, self) == 0) {
                D_pspeu_0926C070 = 5;
                SetSubStep(2);
            }
            break;
        case 2:                                     /* switch 2 */
            if (AnimateEntity(&D_pspeu_0926B468, self) == 0) {
                SetStep(1);
            }
            break;
        }
        break;
    case 3:                                         /* switch 1 */
        switch (self->step_s) {                        /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            if (AnimateEntity(&D_pspeu_0926B448, self) == 0) {
                SetSubStep(1);
            }
            if ((!self->poseTimer) && (self->pose == 2)) {
                PlaySfxPositional(0x662);
            }
            break;
        case 1:                                     /* switch 3 */
            if (AnimateEntity(&D_pspeu_0926B468, self) == 0) {
                D_pspeu_0926C088 = 3;
                SetStep(1);
            }
            break;
        }
        break;
    case 8:                                         /* switch 1 */
        if (AnimateEntity(&D_pspeu_0926B458, self) == 0) {
            self->pose = 0;
            self->poseTimer = 0;
        }
        break;
    case 16:                                        /* switch 1 */
        switch (self->step_s) {                        /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            self->pose = (0x10 - (s16) self->animCurFrame);
            self->step_s += 1;
            /* fallthrough */
        case 1:                                     /* switch 4 */
            if (AnimateEntity(&D_pspeu_0926B468, self) == 0) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s += 1;
            }
            break;
        }
        break;
    }
    if (D_pspeu_0926C068 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

extern EInit D_us_80180558;

void func_us_8019EE30(Entity* self) {
    Entity* other;
    s32 i;
    s32 offsetIndex;
    s8* hitbox;

    self->palette = D_pspeu_0926C0A0;
    if ((D_pspeu_0926C060 & 1) && (self->step != 0x10)) {
        SetStep(0x10);
    }
    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(D_us_80180558);
        self->facingLeft = self->params;
        self->parent = &g_Entities[0x50];
        if (!self->params) {
            self->nextPart = self + 2;
        } else {
            self->nextPart = &g_Entities[0x50];
        }
        /* fallthrough */
    case 1:                                         /* switch 1 */
        AnimateEntity(&D_pspeu_0926B418, self);
        if (D_pspeu_0926C070 == 1) {
            SetStep(2);
        }
        if (D_pspeu_0926C088 == ((self->params) + 1)) {
            self->animCurFrame = 0xA;
        }
        break;
    case 2:                                         /* switch 1 */
        switch (self->step_s) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            for(i = 0; i < 2; i++) {
                other = AllocEntity(&g_Entities[0x90], &g_Entities[0x98]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(D_psp_E_UNK_1F, other);
                    other->params = self->params;
                    other->zPriority = ((self->zPriority) + 4);
                }
            }
            self->animCurFrame = 9;
            self->step_s += 1;
            /* fallthrough */
        case 1:                                     /* switch 2 */
            if (D_pspeu_0926C070 == 3) {
                SetSubStep(2);
            }
            break;
        case 2:                                     /* switch 2 */
            AnimateEntity(&D_pspeu_0926B420, self);
            if (D_pspeu_0926C070 == 5) {
                SetSubStep(3);
            }
            break;
        case 3:                                     /* switch 2 */
            if (AnimateEntity(&D_pspeu_0926B430, self) == 0) {
                SetStep(1);
            }
            break;
        }
        break;
    case 16:                                        /* switch 1 */
        switch (self->step_s) {                        /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            self->hitboxState = 0;
            self->animCurFrame = 9;
            self->step_s += 1;
            break;
        case 1:
            break;
        }
        break;
    }
    other = self - 1;
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi;
    offsetIndex = other->animCurFrame - 12;
    if (offsetIndex < 0) {
        offsetIndex = 0;
    }
    if (offsetIndex > 4) {
        offsetIndex = 4;
    }
    if (!self->params) {
        self->posX.i.hi += D_pspeu_0926B518[offsetIndex].x;
    } else {
        self->posX.i.hi -= D_pspeu_0926B518[offsetIndex].x;
    }
    self->posY.i.hi += D_pspeu_0926B518[offsetIndex].y;
    hitbox = &D_pspeu_0926B550;
    hitbox += D_pspeu_0926B570[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
    if (D_pspeu_0926C068 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
        return;
    }
    self->hitboxState = 3;
}

extern EInit D_us_8018054C;

void func_us_8019F1CC(Entity* self) {
    Entity* previous;
    Entity* other;
    s32 sqMag;
    s16 angle;
    s32 i;
    s32 xVar2;
    s32 yVar2;
    s32 xVar;
    s32 yVar;

    self->palette = D_pspeu_0926C0A0;
    if ((D_pspeu_0926C060 & 1) && ((self->step) != 0x10)) {
        SetStep(0x10);
    }
    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(D_us_8018054C);
        other = self + 1;
        for(i = 0; i < 5; i++, other++) {
            CreateEntityFromCurrentEntity(D_psp_E_UNK_1D, other);
            other->zPriority = self->zPriority - i;
        }
        /* fallthrough */
    case 1:                                         /* switch 1 */
        AnimateEntity(&D_pspeu_0926B478, self);
        other = &g_Entities[0x50];
        xVar = other->posX.i.hi + D_pspeu_0926B530[self->params].x;
        yVar = other->posY.i.hi + D_pspeu_0926B530[self->params].y;
        self->posX.i.hi = xVar;
        self->posY.i.hi = yVar;
        self->zPriority = ((other->zPriority) + 2);
        self->hitboxState = 0;
        if (D_pspeu_0926C090 == ((self->params) + 1)) {
            self->zPriority = ((other->zPriority) + 6);
            SetStep(2);
        }
        if (D_pspeu_0926C098 == 1) {
            self->zPriority = ((other->zPriority) + 6);
            SetStep(3);
        }
        break;
    case 2:                                         /* switch 1 */
        self->hitboxState = 3;
        switch (self->step_s) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = other->posY.i.hi - self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = (rcos(angle) << 0x12) >> 0xC;
            self->velocityY = (rsin(angle) << 0x12) >> 0xC;
            PlaySfxPositional(0x866);
            self->step_s += 1;
            /* fallthrough */
        case 1:                                     /* switch 2 */
            MoveEntity();
            if (AnimateEntity(&D_pspeu_0926B480, self) == 0) {
                SetSubStep(2);
            }
            break;
        case 2:                                     /* switch 2 */
            AnimateEntity(&D_pspeu_0926B490, self);
            MoveEntity();
            other = &g_Entities[0x50];
            xVar = other->posX.i.hi + D_pspeu_0926B530[self->params].x;
            yVar = other->posY.i.hi + D_pspeu_0926B530[self->params].y;
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = rcos(angle) << 5;
            self->velocityY = rsin(angle) << 5;
            if ((abs(xVar) < 3) && (abs(yVar) < 3)) {
                D_pspeu_0926C090 += 1;
                SetStep(1);
            }
            break;
        }
        break;
    case 3:                                         /* switch 1 */
        switch (self->step_s) {                           /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            angle = D_pspeu_0926B540[self->params];
            self->velocityX = (rcos(angle) << 0x12) >> 0xC;
            self->velocityY = (rsin(angle) << 0x12) >> 0xC;
            self->step_s++;
            /* fallthrough */
        case 1:                                     /* switch 3 */
            MoveEntity();
            if (AnimateEntity(&D_pspeu_0926B480, self) == 0) {
                g_api.PlaySfx(0x62F);
                other = AllocEntity(&g_Entities[0xC0], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(D_psp_E_UNK_25, other);
                    other->ext.ILLEGAL.u32[8] = (u32) self;
                    other->zPriority = (self->zPriority + 1);
                }
                D_pspeu_0926C098 += 1;
                self->step_s += 1;
            }
            break;
        case 2:                                     /* switch 3 */
            if (D_pspeu_0926C098 == 5) {
                self->step_s += 1;
            }
            break;
        case 3:                                     /* switch 3 */
            AnimateEntity(&D_pspeu_0926B490, self);
            MoveEntity();
            other = &g_Entities[0x50];
            xVar = other->posX.i.hi + D_pspeu_0926B530[self->params].x;
            yVar = other->posY.i.hi + D_pspeu_0926B530[self->params].y;
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = rcos(angle) * 0x28;
            self->velocityY = rsin(angle) * 0x28;
            if ((abs(xVar) < 3) && (abs(yVar) < 3)) {
                SetStep(1);
            }
            break;
        }
        break;
    case 16:                                        /* switch 1 */
        switch (self->step_s) {                        /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            self->hitboxState = 0;
            self->animCurFrame = 0x12;
            MoveEntity();
            other = &g_Entities[0x50];
            xVar = other->posX.i.hi + D_pspeu_0926B530[self->params].x;
            yVar = other->posY.i.hi + D_pspeu_0926B530[self->params].y;
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = rcos(angle) * 0x28;
            self->velocityY = rsin(angle) * 0x28;
            if ((abs(xVar) < 3) && (abs(yVar) < 3)) {
                self->zPriority = ((other->zPriority) + 2);
                self->step_s += 1;
            }
            break;
        case 1:                                     /* switch 4 */
            other = &g_Entities[0x50];
            xVar = other->posX.i.hi + D_pspeu_0926B530[self->params].x;
            yVar = other->posY.i.hi + D_pspeu_0926B530[self->params].y;
            self->posX.i.hi = xVar;
            self->posY.i.hi = yVar;
            break;
        }
        break;
    }
    other = &g_Entities[0x50];
    xVar2 = other->posX.val + (D_pspeu_0926B530[self->params].x << 0x10);
    yVar2 = other->posY.val + (D_pspeu_0926B530[self->params].y << 0x10);
    
    other = self + 5;
    for(i = 0; i < 5; i++) {
        previous = other - 1;
        xVar2 = (xVar2 + previous->posX.val) >> 1;
        yVar2 = (yVar2 + previous->posY.val) >> 1;
        xVar = xVar2 - other->posX.val;
        yVar = yVar2 - other->posY.val;
        xVar2 = (xVar >> 2) + xVar2;
        yVar2 = (yVar >> 2) + yVar2;
        other->posX.val = xVar2;
        other->posY.val = yVar2;
        other->zPriority = (self->zPriority - 5 + i);
        other = previous;
    }
    other = &g_Entities[0x50];
    xVar2 = other->posX.i.hi + D_pspeu_0926B530[self->params].x;
    yVar2 = other->posY.i.hi + D_pspeu_0926B530[self->params].y;
    other = self + 5;
    for(i = 0; i < 6; i++, other--) {
        xVar = other->posX.i.hi - xVar2;
        yVar = other->posY.i.hi - yVar2;
        angle = ratan2(yVar, xVar);
        sqMag = (xVar * xVar) + (yVar * yVar);
        if (sqMag > 0x90) {
            other->posX.i.hi = xVar2 + ((rcos(angle) * 0xC) >> 0xC);
            other->posY.i.hi = yVar2 + ((rsin(angle) * 0xC) >> 0xC);
        }
        xVar2 = other->posX.i.hi;
        yVar2 = other->posY.i.hi;
    }
    if (D_pspeu_0926C068 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

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

    if (D_pspeu_0926C068 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

void func_us_8019FB04(Entity* self) {
    AnimateEntityFrame* anim;
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

    if (D_pspeu_0926C068 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

void func_us_8019FBC0(Entity* self) {
    Entity* other;
    other = &g_Entities[0x50];
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi;
    self->palette = D_pspeu_0926C0A0;
    if ((D_pspeu_0926C060 & 1) && (self->step != 0x10)) {
        SetStep(0x10);
    }
    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(D_us_80180540);
        /* fallthrough */
    case 1:
        AnimateEntity(D_pspeu_0926B4A8, self);
        break;
    case 16:
        self->animCurFrame = 0x1B;
        break;
    }
    if (D_pspeu_0926C068 != 0) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

extern EInit g_EInitInteractable;

void func_us_8019FCB4(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    Entity* other;
    s16 angle;
    s16 yVar;
    s16 xVar;
    s32 i;
    s32 color;

    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        for(self->ext.prim = prim; prim != NULL; prim = prim->next) {
            prim->tpage = 0x14;
            prim->clut = 0x201;
            prim->priority = ((self->zPriority) - 1);
            prim->drawMode = 8;
        }
        prim = self->ext.prim;
        for(i = 0; i < 2; prim = prim->next, i++) {
            prim->u0 = 0xC1;
            prim->u1 = 0xFF;
            prim->u2 = 0xC1;
            prim->u3 = 0xFF;
            prim->v0 = 1;
            prim->v1 = 1;
            prim->v2 = 0x47;
            prim->v3 = 0x47;
            prim->priority = ((self->zPriority) - 2);
            prim = prim->next;
            prim->u0 = 1;
            prim->u1 = 0xBF;
            prim->u2 = 1;
            prim->u3 = 0xBF;
            prim->v0 = 1;
            prim->v1 = 1;
            prim->v2 = 0xB4;
            prim->v3 = 0xB4;
        }
    case 1:
        other = &g_Entities[0x50];
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->ext.ILLEGAL.s16[3] += 0x10;
        angle = self->rotate = (rsin(self->ext.ILLEGAL.s16[3]) << 7) >> 0xC;
        prim = self->ext.prim;
        for(i = 0; i < 2; i++) {
            if (i == 0) {
                xVar = self->posX.i.hi - 8;
            } else {
                xVar = self->posX.i.hi + 8;
            }
            yVar = self->posY.i.hi - 0x34;
            prim->x1 = xVar;
            prim->y1 = yVar;
            prim->x3 = xVar;
            prim->y3 = yVar + 0x46;
            if (i == 0) {
                xVar = xVar - ((rcos(angle) * 0x3E) >> 0xC);
            } else {
                xVar = xVar + ((rcos(angle) * 0x3E) >> 0xC);
            }
            yVar = yVar + ((rsin(angle) * 0x3E) >> 0xC);
            prim->x0 = xVar;
            prim->y0 = yVar;
            if (i == 0) {
                prim->x2 = xVar + ((rsin(angle) * 0x46) >> 0xC);
            } else {
                prim->x2 = xVar - ((rsin(angle) * 0x46) >> 0xC);
            }
            prim->y2 = yVar + ((rcos(angle) * 0x46) >> 0xC);
            prim->drawMode = 2;
            prim = prim->next;
            if (i == 0) {
                xVar = xVar + 0x18;
            } else {
                xVar = xVar - 0x18;
            }
            yVar = yVar - 0x78;
            prim->x1 = xVar;
            prim->y1 = yVar;
            prim->x3 = xVar;
            prim->y3 = yVar + 0xB3;
            if (i == 0) {
                xVar = xVar - ((rcos(angle) * 0xBE) >> 0xC);
            } else {
                xVar = xVar + ((rcos(angle) * 0xBE) >> 0xC);
            }
            yVar = yVar + ((rsin(angle) * 0xBE) >> 0xC);
            prim->x0 = xVar;
            prim->y0 = yVar;
            if (i == 0) {
                prim->x2 = xVar + ((rsin(angle) * 0xB3) >> 0xC);
            } else {
                prim->x2 = xVar - ((rsin(angle) * 0xB3) >> 0xC);
            }
            prim->y2 = yVar + ((rcos(angle) * 0xB3) >> 0xC);
            prim->drawMode = 2;
            prim = prim->next;
        }
    }
    prim = self->ext.prim;
    color = D_pspeu_0926C0A0 & 0xFFF;
    if (color == 0x200) {
        color = 0x201;
    }
    while (prim != NULL) {
        prim->clut = color;
        if (D_pspeu_0926C068 != 0) {
            prim->drawMode |= 8;
        }
        prim = prim->next;
    }
    FntPrint("color %x\n", D_pspeu_0926C0A0);
    
}

void func_us_801A01A4(Entity* self){
    Entity* other;
    s16 arctan;
    s32 primIndex;
    s32 length;
    Primitive* prim2;
    Primitive* prim;
    u8 var_s7;
    s32 i;
    s16 angle1;
    s32 xVar;
    s32 yVar;
    s16 angle2;
    
    if (D_pspeu_0926C060 & 1) {
        DestroyEntity(self);
        return;
    }
    if (D_pspeu_0926C070 == 2) {
        DestroyEntity(self);
        return;
    }
    if (!self->params) {
        self->ext.ILLEGAL.u32[8] = (u32) &g_Entities[0x56];
        self->ext.ILLEGAL.u32[9] = (u32) &g_Entities[0x58];
    } else {
        self->ext.ILLEGAL.u32[9] = (u32) &g_Entities[0x56];
        self->ext.ILLEGAL.u32[8] = (u32) &g_Entities[0x58];
    }
    other = (Entity*)self->ext.ILLEGAL.u32[8];
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi;
    if (!(g_Timer & 0xF)) {
        // This is bad. Not proper arguments. Necessitates empty
        // prototype in gameapi.
        // Probably supposed to be PlaySfxVolPan
        g_api.PlaySfx(0x869, 0x70, 0);
    }
    switch (self->step) {                               /* irregular */
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x14);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        self->ext.ILLEGAL.u32[1] = (u32) prim;
        i = 0; 
        while(prim != NULL) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->u0 = prim->u1 = (i * 0x10) + 0x90;
            prim->u2 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v2 = 0xD0;
            prim->v1 = prim->v3 = 0xC0;
            prim->r0 = prim->g0 = prim->b0 = 0x50;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority + 1;
            prim->drawMode = 8;
            prim = prim->next;
            i += 1;
            if (i > 5) {
                i = 0;
            }
        }
    case 1:
        prim = self->ext.prim;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->x1 = prim->x0;
        prim->y1 = prim->y1 - 0x10;
        prim->x2 = self->posX.i.hi;
        prim->y2 = self->posY.i.hi;
        prim->x3 = prim->x2;
        prim->y3 = prim->y2 - 0x10;
        self->ext.ILLEGAL.u32[1] = (u32) prim;
        self->ext.ILLEGAL.s16[4] = (Random() * 0x10);
        while (prim != NULL) {
            prim->r0 = prim->g0 = prim->b0 = 0x50;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = 8;
            prim = prim->next;
        }
        self->ext.ILLEGAL.s16[8] = 0;
        self->step += 1;
    case 2:
        for(i = 0; true; i++){
            prim = (Primitive*)self->ext.ILLEGAL.u32[1];
            angle1 = self->ext.ILLEGAL.s16[4];
            other = (Entity*)self->ext.ILLEGAL.u32[9];
            xVar = other->posX.i.hi;
            yVar = other->posY.i.hi;
            xVar -= prim->x2;
            yVar -= prim->y2;
            if ((abs(xVar) < 0x10) && (abs(yVar) < 0x10)) {
                self->step = 1;
                return;
            }
            if ((abs(xVar) < 0x20) && (abs(yVar) < 0x20)) {
                var_s7 = 1;
            } else {
                var_s7 = 0;
            }
            if (!self->ext.ILLEGAL.s16[8]) {
                self->ext.ILLEGAL.s16[8] = 4;
                if (var_s7) {
                    self->ext.ILLEGAL.s16[8] = 2;
                }
                arctan = ratan2(-yVar, xVar);
                angle2 = arctan - angle1;
                if (angle2 > 0x800) {
                    angle2 = angle2 - 0x1000;
                }
                if (angle2 < -0x800) {
                    angle2 = angle2 + 0x1000;
                }
                if (!var_s7) {
                    angle2 /= 4;
                } else {
                    angle2 /= 2;
                }
                self->ext.ILLEGAL.s16[5] = angle2;
            }
            angle1 += self->ext.ILLEGAL.s16[5];
            if (!var_s7) {
                angle1 += (0x60 - ((Random() & 3) << 6));
            }
            angle1 &= 0xFFF;
            prim2 = prim->next;
            if (prim2 == NULL) {
                self->step = 1;
                return;
            }
            LOW(prim2->x0) = LOW(prim->x2);
            LOW(prim2->x1) = LOW(prim->x3);
            self->ext.ILLEGAL.s16[4] = angle1;
            self->ext.ILLEGAL.u32[1] = (u32) prim2;
            xVar = (rcos(angle1) * 0xC) >> 0xC;
            yVar = -((rsin(angle1) * 0xC) >> 0xC);
            prim2->x2 = (prim2->x0 + xVar);
            prim2->y2 = (prim2->y0 + yVar);
            angle2 = angle1 - 0x400;
            length = 0x10;
            xVar = (length * rcos(angle2)) >> 0xC;
            yVar = -((length * rsin(angle2)) >> 0xC);
            xVar = prim2->x3 = (prim2->x2 + xVar);
            yVar = prim2->y3 = (prim2->y2 + yVar);
            prim2->drawMode = 0x77;
            self->ext.ILLEGAL.s16[8]--;
        }
    case 3:
        for(prim = self->ext.prim; prim != NULL; prim = prim->next) {
            prim->drawMode = 8;
        }
        self->step = 1;
        return;
    }
}

void func_us_801A0710(Entity* self) {
    Entity* other;
    s32 temp_s1;

    if (D_pspeu_0926C060 & 1) {
        DestroyEntity(self);
        return;
    }
    other = &g_Entities[0x50];
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi + 0x10;
    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(D_us_80180540);
        self->animCurFrame = 0x2A;
        self->drawFlags = 3;
        self->scaleX = self->scaleY = 0;
        /* fallthrough */
    case 1:
        self->scaleX = self->scaleY += 0x10;
        if (self->scaleX > 0x180) {
            self->step += 1;
        }
        break;
    case 2:
        other = &g_Entities[0x82];
        CreateEntityFromCurrentEntity(D_psp_E_UNK_21, other);
        other->zPriority = self->zPriority + 1;
        self->step += 1;
        break;
    case 3:
        if (D_pspeu_0926C070 == 2) {
            self->step += 1;
        }
        break;
    case 4:
        temp_s1 = self->scaleX;
        temp_s1 -= 0x20;
        self->scaleX = self->scaleY = temp_s1;
        if (temp_s1 < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A0860(Entity* self) {
    Entity* other;
    s32 scaleY;
    s32 i;

    if (D_pspeu_0926C060 & 1) {
        DestroyEntity(self);
        return;
    }
    other = &g_Entities[0x50];
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi + 0x10;
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180540);
        self->animCurFrame = D_pspeu_0926C078 + 0x2D;
        self->drawFlags = 3;
        self->scaleX = self->scaleY = 0;
        self->drawFlags |= 8;
        self->opacity = 0;
        /* fallthrough */
    case 1:
        self->scaleX = self->scaleY += 8;
        if (self->scaleX >= 0x100) {
            self->scaleX = self->scaleY = 0x100;
            self->step += 1;
        }
        /* fallthrough */
    case 2:
        self->opacity += 2;
        if (self->opacity >= 0x80) {
            D_pspeu_0926C070 = 2;
            self->step = 3;
        }
        break;
    case 3:
        if (D_pspeu_0926C070 == 4) {
            g_api.PlaySfx(0x868);
            self->step += 1;
        }
        break;
    case 4:
        self->scaleX += 8;
        scaleY = self->scaleY;
        scaleY -= 0x18;
        if (scaleY < 0) {
            scaleY = 0;
        }
        self->scaleY = scaleY;
        for(i = 0; i < 0x10; i++) {
            other = AllocEntity(&g_Entities[0xC0], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(D_psp_E_UNK_22, self, other);
                other->zPriority = self->zPriority + 1;
            }
        }
        if (scaleY == 0) {
            self->animCurFrame = 0;
            self->ext.ILLEGAL.s16[2] = 0x50;
            self->step += 1;
        }
        break;
    case 5:
        if (!--self->ext.ILLEGAL.s16[2]) {
            g_api.PlaySfx(0x672);
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A0AB4(Entity* self) {
    s32 xVar;
    s32 yVar;
    Entity* other;
    s16 angle;
    s32 speed;

    if (D_pspeu_0926C060 & 1) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(D_us_80180540);
        self->drawFlags = 3;
        self->scaleX = self->scaleY = (Random() & 0x7F) + 0x80;
        self->blendMode = 0x10;
        angle = rand() & 0xFFF;
        speed = (Random() & 0x1F) + 0x10;
        self->velocityX = speed * rcos(angle);
        self->velocityY = speed * rsin(angle);
        self->posX.val = self->posX.val + (self->velocityX * 4);
        self->posY.val += self->velocityY * 4;
        self->ext.ILLEGAL.s16[2] = ((Random() & 0x1F) + 0x10);
        /* fallthrough */
    case 1:
        MoveEntity();
        AnimateEntity(&D_pspeu_0926B4E8, self);
        self->velocityX -= self->velocityX >> 5;
        self->velocityY -= self->velocityY >> 5;
        if (D_pspeu_0926C070 == 5) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step += 1;
        }
        break;
    case 2:
        AnimateEntity(&D_pspeu_0926B4E8, self);
        if (!--self->ext.ILLEGAL.s16[2]) {
            self->step += 1;
        }
        if (!(g_Timer & 7)) {
            g_api.PlaySfx(0x673);
        }
        break;
    case 3:
        MoveEntity();
        if (self->scaleX > 0x20) {
            self->scaleX = self->scaleY -= 2;
        }
        other = &g_Entities[0x50];
        xVar = other->posX.i.hi - self->posX.i.hi;
        yVar = other->posY.i.hi - 0x18 - self->posY.i.hi;
        angle = ratan2(yVar, xVar);
        if (self->ext.ILLEGAL.s32[4] < FIX(3)) {
            self->ext.ILLEGAL.s32[4] += 0x1000;
        }
        speed = self->ext.ILLEGAL.s32[4];
        self->velocityX = (speed * rcos(angle)) >> 0xC;
        self->velocityY = (speed * rsin(angle)) >> 0xC;
        speed = (xVar * xVar) + (yVar * yVar);
        if (speed < 0x40) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180564;

void func_us_801A0DC0(Entity* self) {
    Entity* other;
    s32 scale;
    s32 xVar;
    s32 yVar;

    if (D_pspeu_0926C060 & 1) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(D_us_80180564);
        self->drawFlags = 3;
        self->scaleX = self->scaleY = 0;
        self->blendMode |= 0x30;
        self->drawFlags |= 8;
        self->opacity = 0x60;
        self->hitboxState = 0;
        /* fallthrough */
    case 1:
        AnimateEntity(&D_pspeu_0926B408, self);
        scale = self->scaleX;
        scale += 0x10;
        if (scale > 0xCC) {
            scale = 0xCC;
        }
        self->scaleX = self->scaleY = scale;
        if (D_pspeu_0926C080 != 0) {
            self->ext.ILLEGAL.s16[2] = 0x60;
            other = &PLAYER;
            xVar = other->posX.val - self->posX.val;
            yVar = other->posY.val - self->posY.val;
            self->velocityX = xVar / 96;
            self->velocityY = yVar / 96;
            self->step += 1;
        }
        if (!(g_Timer & 0x1F)) {
            g_api.PlaySfxVolPan(0x6DE, 0x50, 0);
        }
        break;
    case 2:
        AnimateEntity(&D_pspeu_0926B408, self);
        MoveEntity();
        scale = 0x6000 / (self->ext.ILLEGAL.s16[2] + 0x18);
        self->scaleX = self->scaleY = scale;
        if (!(self->ext.ILLEGAL.s16[2] & 3)) {
            other = AllocEntity(&g_Entities[0xC0], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(D_psp_E_UNK_26, self, other);
                other->scaleX = other->scaleY = self->scaleX;
                other->zPriority = self->zPriority;
                other->opacity = self->opacity;
            }
        }
        if (!(self->ext.ILLEGAL.s16[2] & 0xF)) {
            g_api.PlaySfxVolPan(0x6E2, 0x80 - self->ext.ILLEGAL.s16[2] / 2, 0);
        }
        if (!--self->ext.ILLEGAL.s16[2]) {
            g_api.PlaySfx(0x661);
            self->zPriority = g_unkGraphicsStruct.g_zEntityCenter + 8;
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = other->posY.i.hi - self->posY.i.hi;
            scale = self->scaleX * 20 / 256;
            if (((xVar * xVar) + (yVar * yVar)) < (scale * scale)) {
                self->hitboxOffX = xVar;
                self->hitboxOffY = yVar;
                self->hitboxState = 1;
            }
            self->step += 1;
            return;
        }
        break;
    case 3:
        DestroyEntity(self);
        break;
    }
}

void func_us_801A1150(Entity* self) {
    s32 opacity;

    if (!self->step) {
        InitializeEntity(D_us_80180540);
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->drawFlags |= ENTITY_OPACITY;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }
    AnimateEntity(D_pspeu_0926B410, self);
    opacity = self->opacity;
    opacity -= 2;
    if (opacity < 0) {
        opacity = 0;
    }
    self->opacity = (u8)opacity;
    if (opacity == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_FE08", func_us_801A11DC);

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
