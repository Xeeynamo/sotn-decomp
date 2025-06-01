// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

static u8 anim0[] = {16, 11, 0, 0};
static u8 anim1[] = {8, 12, 8, 13, 8, 14, 8, 15, 8, 16, 0, 0};
static u8 anim2[] = {16, 50, 0, 0};
static u8 anim3[] = {16, 51, 0, 0};
static u8 anim4[] = {16, 41, 0, 0};
static u8 anim5[] = {16, 42, 0, 0};
static u8 anim6[] = {16, 43, 0, 0};
static u8 anim7[] = {16, 44, 0, 0};
static u8 anim8[] = {16, 38, 0, 0};
static u8 anim9[] = {16, 45, 0, 0};
static u8 anim10[] = {16, 46, 0, 0};
static u8 anim11[] = {16, 55, 0, 0};
static u8 anim12[] = {16, 2, 0, 0};
static u8 anim13[] = {16, 60, 255, 0};
static u8 anim14[] = {16, 61, 255, 0};
static u8 anim15[] = {16, 62, 255, 0};

static ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {0x8001, 105, 0, 0, 0x0, 0x0, 0, 0, anim0},
    {0x8001, 105, 0, 0, 0x0, 0x0, 48, 0, anim1},
    {0x8001, 192, 0, 0, 0x8068, 0x0, 0, 0, anim2},
    {0x8001, 191, 0, 0, 0x0, 0x8, 0, 0, anim3},
    {0x8001, 192, 0, 0, 0x8069, 0x0, 0, 0, anim2},
    {0x8001, 191, 0, 0, 0x8068, 0x8, 0, 0, anim3},
    {0x8001, 64, 0, 0, 0x0, 0x0, 0, 0, anim4},
    {0x8001, 64, 0, 0, 0x0, 0x0, 0, 0, anim5},
    {0x8001, 64, 0, 0, 0x0, 0x0, 0, 0, anim6},
    {0x8001, 64, 0, 0, 0x0, 0x0, 0, 0, anim7},
    {0x8001, 193, 0, 0, 0x0, 0x0, 0, 0, anim11},
    {0x8001, 64, 0, 0, 0x0, 0x0, 0, 0, anim12},
    {0x8001, 63, 1, 0, 0x0, 0x0, 0, 0, anim10},
    {0x8001, 62, 0, 0, 0x8049, 0xb, 0, 0, anim8},
    {0x8001, 61, 0, 0, 0x0, 0xb, 0, 0, anim8},
    {0x8001, 61, 0, 0, 0x8049, 0xb, 0, 0, anim8},
    {0x8001, 57, 0, 0, 0x0, 0x0, 0, 0, anim9},
    {0x8001, 57, 0, 0, 0x0, 0x0, 0, 0, anim10},
    {0x8001, 193, 0, 0, 0x0, 0x8, 0, 0, anim13},
    {0x8001, 193, 0, 0, 0x0, 0x8, 0, 0, anim14},
    {0x8001, 193, 0, 0, 0x0, 0x8, 0, 0, anim15}};

// params: Index of ObjInit to use
//         (== 1) Use a different hardcoded scaleY and scaleX value
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
    ObjInit2* objInit = &OVL_EXPORT(BackgroundBlockInit)[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->facingLeft = objInit->facingLeft;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}
