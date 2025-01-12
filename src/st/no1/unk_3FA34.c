// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

extern u16 g_EInitParticle;

void func_us_801BFA34(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(&g_EInitParticle);
        self->palette = PAL_OVL(0x19E);
        self->animSet = 2;
        self->animCurFrame = 9;
        self->drawMode = DRAW_TPAGE;
        self->rotX = 64;
        self->rotY = 64;
        self->rotZ = -0x400;
        self->velocityX = FIX(-5.0 / 4.0);
        self->zPriority += 8;
        self->drawFlags |= FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
    } else {
        self->rotX += 4;
        self->rotY += 14;
        self->animFrameDuration++;
        self->posX.val += self->velocityX;

        if (!(self->animFrameDuration & 1)) {
            self->animCurFrame++;
        }

        if (self->animFrameDuration >= 24) {
            DestroyEntity(self);
        }
    }
}

INCLUDE_ASM("st/no1/nonmatchings/unk_3FA34", func_us_801BFB40);

INCLUDE_ASM("st/no1/nonmatchings/unk_3FA34", func_us_801C01F0);

INCLUDE_ASM("st/no1/nonmatchings/unk_3FA34", func_us_801C05DC);

// bone throwing skeleton
INCLUDE_ASM("st/no1/nonmatchings/unk_3FA34", func_us_801C0A40);

// in the doppleganger room, maybe rotating door
INCLUDE_ASM("st/no1/nonmatchings/unk_3FA34", func_us_801C0B9C);

// black to gray transition for "Elevator activated." text?
s32 func_us_801C0E98(Primitive* prim) {
    if (prim->g0 > 96) {
        if (prim->b0 > 96) {
            if (prim->r0 <= 96) {
                prim->r0 += 2;
            } else {
                return 1;
            }
        } else {
            prim->b0 += 2;
        }
    } else {
        prim->g0 += 2;
    }

    if (prim->b2 > 96) {
        if (prim->r2 > 96) {
            if (prim->g2 <= 96) {
                prim->g2 += 2;
            }
        } else {
            prim->r2 += 2;
        }
    } else {
        prim->b2 += 2;
    }

    if (prim->g1 > 32) {
        if (prim->r1 > 32) {
            if (prim->b1 <= 32) {
                prim->b1 += 2;
            }
        } else {
            prim->r1 += 2;
        }
    } else {
        prim->g1 += 2;
    }
    if (prim->r3 > 32) {
        if (prim->g3 > 32) {
            if (prim->b3 > 32) {
                prim->b3 += 8;
            } else {
                prim->b3 += 4;
            }
            prim->g3 += 2;
        } else {
            prim->g3 += 4;
        }
        prim->r3 += 2;
    } else {
        prim->r3 += 4;
    }

    return 0;
}

// support function for `func_us_801C10F4`
INCLUDE_ASM("st/no1/nonmatchings/unk_3FA34", func_us_801C1090);

// "Elevator activatd." text
INCLUDE_ASM("st/no1/nonmatchings/unk_3FA34", func_us_801C10F4);
