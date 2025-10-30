// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

static u8 D_us_80180EA8[] = {3, 1, 3, 2, 3, 3,  3, 4,  3, 5,  3, 6,  3,  7,
                             3, 8, 3, 9, 3, 10, 3, 11, 3, 12, 3, 13, -1, 0};
static u8 D_us_80180EC4[] = {
    3, 1, 3, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 7, 3, 8, -1, 0,
};
static u8 D_us_80180ED8[] = {2, 1, 2, 2, 2,  3, 2,  4, 2,  5, 2,  6, 2,  7,  2,
                             8, 2, 9, 2, 10, 2, 11, 2, 12, 2, 13, 2, 14, -1, 0};

static EntityConfig D_us_80180EF8[] = {
    {ANIMSET_OVL(10), 0x4D, 0, DRAW_DEFAULT, D_us_80180EA8},
    {ANIMSET_OVL(11), 0x56, 3, DRAW_TPAGE2 | DRAW_TPAGE, D_us_80180EC4},
    {ANIMSET_OVL(12), 0x53, 9, DRAW_DEFAULT, D_us_80180ED8},
};

void func_us_801B72E8(Entity* self) {
    s32 params;
    EntityConfig* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        ptr = &D_us_80180EF8[params];
        self->palette = ptr->palette + 0x226;
        self->drawMode = ptr->drawMode;
        self->animSet = ptr->animSet;
        self->unk5A = ptr->unk5A;
        self->ext.et_801B72E8.animData = ptr->animData;
        self->step = params + 1;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(0x19F);
            self->drawMode = DRAW_TPAGE;
            self->facingLeft = 1;
        }
        break;

    case 1:
        MoveEntity();
        self->velocityY = FIX(-1.0);
        if (!AnimateEntity(self->ext.et_801B72E8.animData, self)) {
            DestroyEntity(self);
        }
        break;

    case 2:
        MoveEntity();
        self->velocityY = FIX(-1.0);
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(self->ext.et_801B72E8.animData, self)) {
                self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
                self->drawFlags |= FLAG_DRAW_OPACITY;
                self->scaleX = self->scaleY = 256;
                self->opacity = 128;
                self->step_s++;
            }
            break;

        case 1:
            self->scaleX = self->scaleY += 4;
            self->opacity -= 16;
            if (!self->opacity) {
                DestroyEntity(self);
            }
            break;
        }
        break;

    case 3:
        MoveEntity();
        if (!AnimateEntity(self->ext.et_801B72E8.animData, self)) {
            DestroyEntity(self);
            return;
        }
        switch (self->step_s) {
        case 0:
            self->drawFlags = FLAG_DRAW_OPACITY;
            self->opacity = 128;
            self->step_s++;
            break;

        case 1:
            if (self->pose == 5) {
                self->step_s++;
            }
            break;

        case 2:
            self->opacity -= 4;
            break;
        }
        break;
    }
}
