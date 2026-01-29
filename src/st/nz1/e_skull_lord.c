// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

INCLUDE_ASM("st/nz1/nonmatchings/e_skull_lord", EntitySkullLord);

INCLUDE_ASM("st/nz1/nonmatchings/e_skull_lord", EntitySkullLordOutline);

INCLUDE_ASM("st/nz1/nonmatchings/e_skull_lord", EntitySkullLordFlames);

extern EInit g_EInitSkullLord;
extern EInit D_us_80180BAC;

void EntitySkullLordPieces(Entity* self) {
    s32 rand;
    s16 angle;
    s32 step = (s32)self->step;

    switch (step) {
    case 0:
        InitializeEntity(D_us_80180BAC);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        rand = Random() & 3;
        if (rand == 3) {
            rand = 2;
        }
        self->animCurFrame = rand + 9;
        angle = self->ext.skullLord.unk82;
        rand = (Random() & 0xF) + 2;
        self->velocityX = rand * rcos(angle);
        rand = 0x20 - (Random() & 0x1F);
        self->velocityY = -rand * rsin(angle);
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTATE;
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->velocityX > 0) {
            self->rotate += 0x80;
        } else {
            self->rotate -= 0x80;
        }
        break;
    }
}
