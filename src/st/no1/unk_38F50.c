// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

static u8 anim0[] = {4, 1, 4, 2, 4, 3, 0, 0};
static u8 anim1[] = {6, 4, 6, 5, 6, 6, 6, 7, 0, 0};
static u8 anim2[] = {4, 8, 4, 9, 4, 10, 0, 0};
static u8 anim3[] = {8, 11, 8, 12, 0, 0};
static u8 anim4[] = {4, 13, 4, 14, 4, 15, 0, 0};
static u8 anim5[] = {4, 16, 4, 17, 4, 18, 0, 0};
static u8 anim6[] = {8, 19, 8, 20, 8, 21, 8, 22, 0, 0};
static u8 anim7[] = {4, 23, 4, 24, 4, 25, 0, 0};
static u8 anim8[] = {1, 26, 1, 27, 0, 0};

static u8 D_us_801813FC[] = {1, 4, 8, 11, 13, 16, 19, 23, 26};

static u8* D_us_80181408[] = {
    anim0, anim1, anim2, anim3, anim4, anim5, anim6, anim7, anim8,
};

void func_us_801B8F50(Entity* self) {
    u8* anim;
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A1C);
        self->animCurFrame = D_us_801813FC[self->params];
        self->zPriority = 0x6A;
        break;

    case 1:
        if (g_CastleFlags[NO1_ELEVATOR_ACTIVATED]) {
            self->step++;
        }
        break;

    case 2:
        anim = D_us_80181408[self->params];
        AnimateEntity(anim, self);
        break;
    }
}
