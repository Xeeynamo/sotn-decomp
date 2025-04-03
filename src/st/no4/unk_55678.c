// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>
#include "common.h"
#include "no4.h"

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D798C);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D7FAC);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D81B4);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D85A4);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D8654);

extern u8 D_us_80182780[];

void EntityUnkId3F(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitUnkId3F);
        if (!self->facingLeft) {
            self->velocityX = FIX(-4.0);
        } else {
            self->velocityX = FIX(4.0);
        }
        /* fallthrough */
    case 1:
        MoveEntity();
        AnimateEntity(D_us_80182780, self);
        if (self->flags & FLAG_DEAD) {
            self->step = 0U;
            self->pfnUpdate = EntityExplosion;
            self->params = 0x0;
        }
    }
}

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
