// SPDX-License-Identifier: AGPL-3.0-or-later

#include "rbo3.h"
extern EInit D_us_801804BC;
s32 D_us_8018072C = 0;
#ifdef VERSION_PSP
extern s32 E_ID(UNK_29);
#endif

void func_us_80192D64(Entity* self) {
    s32 i;
    s32 fg;
    s32 fgIndex;
    s32 y;
    Entity* next;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804BC);
        self->zPriority = 0x5C;
        if (self->params & 2) {
            self->animCurFrame = 0xE;
            return;
        }
        if (self->params & 1) {
            self->animCurFrame = 13;
            self->posX.i.hi = 48 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 224 - g_Tilemap.scrollY.i.hi;
        } else {
            self->animCurFrame = 12;
            self->posX.i.hi = 496 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 224 - g_Tilemap.scrollY.i.hi;
        }

        next = self + 1;
        CreateEntityFromEntity(E_ID(UNK_29), self, next);

        next->params = 2;
        next->posY.i.hi = 96;
        if (self->params) {
            next->posX.i.hi -= 16;
        }
        break;

    case 1:
        if (D_us_8018072C) {
            if (self->params & 2) {
                self->step = 8;
                break;
            }
            if (self->params) {
                fgIndex = 0xC1;
            } else {
                fgIndex = 0xDE;
            }

            for (i = 0; i < 4; i++) {
                g_Tilemap.fg[fgIndex] = 0x4B3;
                fgIndex += 0x20;
            }

            self->step = 2;
        }
        break;

    case 2:
        self->posY.val -= FIX(1.125);
        if (self->posY.i.hi < 186) {
            self->posY.i.hi = 186;
            self->step++;
        }
        break;

    case 3:
        if (D_us_8018072C == 0) {
            if (self->params) {
                fgIndex = 0xC1;
            } else {
                fgIndex = 0xDE;
            }

            for (i = 0; i < 4; i++) {
                g_Tilemap.fg[fgIndex] = 0;
                fgIndex += 0x20;
            }
            self->step++;
        }
        break;
    case 4:
        self->posY.val += FIX(0.75);
        y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (y > 0xE0) {
            self->posY.i.hi = 0xE0 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;

    case 5:
    case 6:
    case 7:
        break;
    case 8:
        self->posY.val += FIX(1.125);
        if (self->posY.i.hi > 127) {
            self->posY.i.hi = 127;
            self->step++;
        }
        break;
    case 9:
        if (D_us_8018072C == 0) {
            self->step++;
        }
        break;
    case 10:
        self->posY.val -= FIX(0.75);
        y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (y < 96) {
            self->posY.i.hi = 96 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;
    case 11:
        break;
    }
}
