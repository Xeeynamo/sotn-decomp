// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

// hit during enter sequence
INCLUDE_ASM("boss/bo4/nonmatchings/doors", func_us_801B4BF0);

// hit during enter sequence
INCLUDE_ASM("boss/bo4/nonmatchings/doors", func_us_801B5040);

extern EInit D_us_80180458;
extern u8 D_us_801805CC[];
extern u8 D_us_801805D4[];

void func_us_801B55DC(Entity* self) {
    s32 offsetX;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180458);
        self->drawFlags |= FLAG_DRAW_ROTZ;
        self->rotZ = -0x400;
        if (self->params & 1) {
            self->animCurFrame = 0x64;
            self->velocityX = FIX(-0.5);
        } else {
            self->animCurFrame = 0x62;
            self->velocityX = FIX(0.5);
        }
        self->zPriority = 0x5E;
        // fallthrough

    case 1:
        MoveEntity();
        if (self->params & 1) {
            AnimateEntity(D_us_801805D4, self);
        } else {
            AnimateEntity(D_us_801805CC, self);
        }

        offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->velocityX > 0) {
            if (offsetX > 0x100) {
                self->step++;
            }
        } else if (offsetX < 0x100) {
            self->step++;
        }

        if (!(g_Timer & 0xF)) {
            g_api.PlaySfx(SFX_STONE_MOVE_B);
            return;
        }
        break;

    case 2:
        self->posX.i.hi = 0x100 - g_Tilemap.scrollX.i.hi;
        if (self->params & 1) {
            self->animCurFrame = 0x64;
        } else {
            self->animCurFrame = 0x62;
        }
        break;
    }
}

// light effects
INCLUDE_ASM("boss/bo4/nonmatchings/doors", func_us_801B5774);

INCLUDE_RODATA("boss/bo4/nonmatchings/doors", D_us_801B4168);

// hit during enter sequence
INCLUDE_ASM("boss/bo4/nonmatchings/doors", func_us_801B5FB0);

// 4-segment block doors
INCLUDE_ASM("boss/bo4/nonmatchings/doors", func_us_801B65FC);
