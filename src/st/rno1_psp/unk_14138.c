// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno1/rno1.h"

void func_us_801B8F50_from_no1(Entity* self) {
    extern u16 D_us_8018073C;
    extern u8 D_us_80180BF8[];
    extern void* D_us_80180C04[];
    void* anim;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_8018073C);
        self->animCurFrame = D_us_80180BF8[self->params];
        self->zPriority = 0x6A;
        break;

    case 1:
        if (g_CastleFlags[NO1_ELEVATOR_ACTIVATED]) {
            self->step += 1;
        }
        break;

    case 2:
        anim = D_us_80180C04[self->params];
        AnimateEntity(anim, self);
        break;
    }
}
