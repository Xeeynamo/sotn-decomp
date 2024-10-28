// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801D7C20);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801D7D00);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801D7DAC);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801D8150);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801D8DF0);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801D8FFC);

void func_us_801D91C4(Entity* self) {
    s16 random;
    Entity* fakeEntity = self; // !FAKE

    if (self->step == 0) {
        self->params = 1;
        EntityExplosion(fakeEntity);
        self->zPriority = PLAYER.zPriority + 0x20;
        random = rand() & 0x7FF;
        self->velocityX = rcos(random) << 4 << 2;
        self->velocityY = -(rsin(random) << 4) << 2;
    } else {
        self->posX.val += self->velocityX;
        EntityExplosion(fakeEntity);
    }
}

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801D9264);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801DA488);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801DA6B4);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801DADD0);
