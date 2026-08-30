// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno2/rno2.h"

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1ED70", func_us_801B4DA4_from_bo0);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1ED70", func_us_801B3D8C_from_bo0);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1ED70", func_us_801B3F30_from_bo0);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1ED70", func_us_801B4148_from_bo0);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1ED70", func_us_801B41A4_from_bo0);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1ED70", func_us_801B4210_from_bo0);

void EntityBackgroundBlock(Entity* self) {
    extern ObjInit2 BackgroundBlockInit[];
    extern EInit g_EInitCommon;

    ObjInit2* objInit = &BackgroundBlockInit[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = LOHU(objInit->facingLeft);
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->blendMode = objInit->blendMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1ED70", EntityPrisoner);
