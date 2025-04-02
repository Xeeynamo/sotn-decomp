// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>
#include "common.h"
#include "no4.h"

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_801C4144);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", EntityAlucardWaterEffect);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", EntitySplashWater);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", EntitySurfacingWater);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", EntitySideWaterSplash);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", EntitySmallWaterDrop);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", EntityWaterDrop);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D798C);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D7FAC);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D81B4);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D85A4);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D8654);

//#ifndef NON_MATCHING
//INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D8D44);
//#else

// asm/us/st/no1/data/e_skeleton.data.s:glabel D_us_80182780
extern u8 D_us_80182780[];

void func_us_801D8D44(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180C34);
        if (!self->facingLeft) {
            self->velocityX = FIX(-4.0);
        } else {
            self->velocityX = FIX(4.0);
        }
        /* fallthrough */
    case 1:
        MoveEntity();
        AnimateEntity(D_us_80182780, self);
        if (self->flags & 0x100) {
            self->step = 0U;
            self->pfnUpdate = EntityExplosion;
            self->params = 0x0;
        }
    }
}
//#endif

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D8DF0);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D8FE0);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D93E0);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D9560);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D95EC);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D96FC);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DB194);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DB1E8);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DB65C);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DBBEC);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DBCDC);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DBE1C);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DBE50);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DBFAC);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DC824);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DC944);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DCA9C);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DD410);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DD688);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DDBBC);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DDCAC);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DDCE4);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DE0F0);
