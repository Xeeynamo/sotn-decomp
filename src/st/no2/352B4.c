// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

u8 D_us_80180D38[] = {
    0x2, 0x1, 0x2, 0x2, 0x2,  0x3, 0x2, 0x4,
    0x2, 0x5, 0x4, 0x6, 0xFF, 0x0, 0x0, 0x0,
};

void func_us_801B52B4(Entity* self) {
    s16 angle;
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->zPriority = 0xA0;
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = 0x8161;
        angle = GetAngleBetweenEntitiesShifted(self, g_Entities); // & 0xFF;
        SetEntityVelocityFromAngle(angle, 0x28);
        return;
    }
    MoveEntity();
    if (!AnimateEntity(D_us_80180D38, self)) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("st/no2/nonmatchings/352B4", func_us_801B5368);

INCLUDE_ASM("st/no2/nonmatchings/352B4", func_us_801B5578);

INCLUDE_ASM("st/no2/nonmatchings/352B4", func_us_801B56A4);

INCLUDE_ASM("st/no2/nonmatchings/352B4", func_us_801B5750);

INCLUDE_ASM("st/no2/nonmatchings/352B4", func_us_801B5948);
