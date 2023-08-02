#include "mar.h"

// 0.990 - ('NZ0', 'func_801B0958') - (decompiled)
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018AC0C);

// 0.990 - ('NP3', 'func_801B2540') - (decompiled)
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018ACD4);

// 0.990 - ('NP3', 'EntityBreakable') - (decompiled)
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018AE90);

// 0.990 - ('NZ0', 'func_801B74CC') - (decompiled)
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018AFC4);

// 0.990 - ('NZ0', 'func_801B7520') - (decompiled)
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018B018);

// 1.000 - ('NZ0', 'func_801B76E4') - (decompiled)
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018B1DC);

// 0.990 - ('ST0', 'func_801A8BF8') - (decompiled)
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018B238);

// 0.990 - ('ST0', 'func_801A8CB0') - (decompiled)
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018B2F0);

// 0.990 - ('NZ0', 'func_801B797C') - (decompiled)
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018B474);

// 0.990 - ('ST0', 'func_801A8E60') - (decompiled)
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018B4A0);

// 0.990 - ('ST0', 'func_801A910C') - (decompiled)
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018B74C);

// 0.969 - ('NZ0', 'EntityMariaCutscene')
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018B850);

// https://decomp.me/scratch/qHybN Matching,
// on hold until D_80097400 type discovery is resolved
INCLUDE_ASM("asm/us/boss/mar/nonmatchings/AC0C", func_8018C90C);

void func_8018CA94(Entity* self) {
    s32 posX;
    s32 posX2;
    s32 temp;
    s32 var_a2_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    u16 temp_v1;
    u16 temp_v1_2;
    u16 temp_v1_4;

    if ((D_8019AE70 != 0) && (self->step < 12)) {
        SetStep(12);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801803B4);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 1;
        self->unk5A = 0x48;
        self->palette = 0x210;
        break;

    case 1:
        if (D_8019AF20 & 4) {
            self->animCurFrame = 2;
            self->step++;
        }
        break;

    case 2:
        if (D_8019AF20 & 8) {
            SetStep(3);
        }
        break;

    case 3:
        AnimateEntity(D_80180690, self);
        if (D_8019AF20 & 0x10) {
            SetStep(4);
        }
        break;

    case 4:
        AnimateEntity(D_801806A4, self);
        if (D_8019AF20 & 0x20) {
            SetStep(5);
            return;
        }
        break;

    case 5:
        AnimateEntity(D_801806B8, self);
        if (D_8019AF20 & 0x40) {
            SetStep(6);
        }
        break;

    case 6:
        self->animCurFrame = 19;
        if (D_8019AF20 & 0x80) {
            self->step++;
        }
        break;

    case 7:
        self->animCurFrame = 18;
        if (D_8019AF20 & 0x100) {
            self->step++;
        }
        break;

    case 8:
        AnimateEntity(D_801806CC, self);
        if (D_8019AF20 & 0x200) {
            SetStep(9);
        }
        break;

    case 9:
        AnimateEntity(D_801806E4, self);
        if (D_8019AF20 & 0x400) {
            SetStep(10);
        }
        break;

    case 10:
        AnimateEntity(D_801806EC, self);
        if (D_8019AF20 & 0x800) {
            SetStep(11);
        }
        break;

    case 11:
        AnimateEntity(D_80180700, self);
        if (D_8019AF20 & 0x1000) {
            SetStep(12);
        }
        break;

    case 12:
        if (AnimateEntity(D_80180718, self) == 0) {
            SetStep(13);
            self->velocityX = FIX(1.5);
        }
        break;

    case 13:
        if ((AnimateEntity(D_80180724, self) & 0x80) &&
            ((self->animFrameIdx == 3) || (self->animFrameIdx == 7))) {
            posX = self->posX.i.hi - 120;
            temp = posX >> 4;

            if (posX < 0) {
                temp = (self->posX.i.hi - 105) >> 4;
            }
            if (temp < -8) {
                temp = -8;
            }
            if (temp > 8) {
                temp = 8;
            }
            g_api.func_80134714(0x64C, 0x50, temp);
        }

        MoveEntity();
        if (self->posX.i.hi >= 0xB9) {
            SetStep(14);
            self->velocityY = FIX(-4);
            return;
        }
        break;

    case 14:
        AnimateEntity(D_80180738, self);
        self->velocityY += FIX(0.1875);
        MoveEntity();
        if ((self->velocityY > 0) && (self->posY.i.hi >= 132)) {
            self->velocityY = 0;
            SetStep(15);
        }
        break;

    case 15:
        if ((AnimateEntity(D_80180724, self) & 0x80) &&
            ((self->animFrameIdx == 3) || (self->animFrameIdx == 7))) {
            posX2 = self->posX.i.hi - 120;
            temp = posX2 >> 4;

            if (posX2 < 0) {
                temp = (self->posX.i.hi - 105) >> 4;
            }
            if (temp < -8) {
                temp = -8;
            }
            if (temp > 8) {
                temp = 8;
            }
            g_api.func_80134714(0x64C, 0x50, temp);
        }

        MoveEntity();
        if (self->posX.i.hi > 256) {
            D_8019AF20 |= 0x2000;
        }
        if (self->posX.i.hi > 272) {
            func_80190388(self);
        }
        break;
    }
}
