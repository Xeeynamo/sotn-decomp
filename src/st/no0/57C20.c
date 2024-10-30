// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

extern Entity D_us_80180BCC[];

void func_us_801D7C20(Entity* self) {
    if (self->step != 0) {
        if (self->flags & FLAG_DEAD) {
            EntityExplosionSpawn(0, 0);
            return;
        }
        self->rotZ += 0x80;
        MoveEntity(0);
        if (self->posY.i.hi >= 0xF1) {
            DestroyEntity(self);
        }
    } else {
        InitializeEntity(D_us_80180BCC);
        self->posY.val -= FIX(1.0 / 16);
        GetDistanceToPlayerX();
        self->velocityX = self->facingLeft ? FIX(1.75) : -FIX(1.75);
        self->velocityY = 0;
        self->drawFlags = 4;
    }
}


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
