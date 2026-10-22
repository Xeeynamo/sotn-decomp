// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

extern EInit g_EInitEnvironment;

void EntityRbo3Door(Entity* self) {
    Entity* next;
    s32 fgIndex;
    s32 i;
    s32 y;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->zPriority = 0x5C;
        if (self->params & 2) {
            self->animCurFrame = 14;
            break;
        }
        if (self->params & 1) {
            self->animCurFrame = 13;
            self->posX.i.hi = 464 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 32 - g_Tilemap.scrollY.i.hi;
        } else {
            self->animCurFrame = 12;
            self->posX.i.hi = 16 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 32 - g_Tilemap.scrollY.i.hi;
        }

        next = self + 1;
        CreateEntityFromEntity(E_ID(RBO3DOOR), self, next);
        next->params = 2;
        next->posY.i.hi = 160;
        if (self->params) {
            next->posX.i.hi += 16;
        }
        break;

    case 1:
        if (D_us_801806DC) {
            if (self->params & 2) {
                self->step = 8;
                break;
            }
            if (self->params) {
                fgIndex = 0xDE;
            } else {
                fgIndex = 0xC1;
            }
            for (i = 0; i < 4; i++) {
                g_Tilemap.fg[fgIndex] = 0x4B3;
                fgIndex += 0x20;
            }
            self->step = 2;
        }
        break;

    case 2:
        self->posY.val += FIX(1.125);
        if (self->posY.val > FIX(70)) {
            self->posY.val = FIX(70);
            self->step++;
        }
        break;

    case 3:
        if (!D_us_801806DC) {
            if (self->params) {
                fgIndex = 0xDE;
            } else {
                fgIndex = 0xC1;
            }
            for (i = 0; i < 4; i++) {
                g_Tilemap.fg[fgIndex] = 0;
                fgIndex += 0x20;
            }
            self->step++;
        }
        break;

    case 4:
        self->posY.val -= FIX(0.75);
        y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (y < 32) {
            self->posY.i.hi = 32 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;

    case 8:
        self->posY.val -= FIX(1.125);
        if (self->posY.val < FIX(129)) {
            self->posY.val = FIX(129);
            self->step++;
        }
        break;

    case 9:
        if (!D_us_801806DC) {
            self->step++;
        }
        break;

    case 10:
        self->posY.val += FIX(0.75);
        y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (y > 160) {
            self->posY.i.hi = 160 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;

    case 11:
        break;
    }
}
