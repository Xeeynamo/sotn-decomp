// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// The mouse across from the Doppleganger 10 exit
extern AnimationFrame D_us_80180F48[];
extern AnimationFrame D_us_80180F6C[];
extern AnimationFrame D_us_80180F7C[];
extern s32 D_us_80180F84[];

void func_us_801B7D34(Entity* self) {
    s16 offsetX;
    s16 offsetY;

    offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = -0x7FFF;
        self->zPriority = PLAYER.zPriority - 0x10;
        self->facingLeft = true;
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
        self->anim = D_us_80180F48;
        break;

    case 1:
        if (self->animFrameDuration < 0) {
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->anim = D_us_80180F6C;
            self->velocityX = D_us_80180F84[self->facingLeft];
            // n.b.! this is one higher than INT16_MAX making
            //       it actually INT16_MIN. the first decrement
            //       below rolls the value back to positive before
            //       any comparison which is only against zero.
            self->ext.et_801B7D34.timer = (INT16_MAX + 1);
            self->step++;
        }
        break;

    case 2:
        if (--self->ext.et_801B7D34.timer == 0) {
            if (!self->facingLeft) {
                if (offsetX < 0x1e0 && offsetX > 0x1a0) {
                    self->step = 3;
                    self->animFrameIdx = 0;
                    self->animFrameDuration = 0;
                    self->anim = D_us_80180F7C;
                    self->ext.et_801B7D34.unk7E = 3;
                    self->velocityY = FIX(-2.75);
                    break;
                }
            }

            self->step = 1;
            self->animFrameIdx = 3;
            self->animFrameDuration = 0;
            self->anim = D_us_80180F48;

        } else {
            self->posX.val += self->velocityX;
            if ((self->facingLeft == false && offsetX < 0x198) ||
                (self->facingLeft == true && offsetX > 0x208)) {
                self->facingLeft ^= true;
                self->velocityX = D_us_80180F84[self->facingLeft];
                if (!(rand() & 3)) {
                    self->ext.et_801B7D34.timer = (rand() & 0xF) + 0x18;
                } else {
                    self->ext.et_801B7D34.timer = (INT16_MAX + 1);
                }
            }
        }
        break;

    case 3:
        self->velocityY += FIX(7.0 / 32.0);
        self->posY.val += self->velocityY;
        if (self->velocityY > 0) {
            offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi - 0x8DD;
            if (offsetY >= 0) {
                self->posY.i.hi -= offsetY;
                self->posY.i.lo = 0;
                if (--self->ext.et_801B7D34.unk7E) {
                    self->velocityY = FIX(-2.75);
                    self->animFrameIdx = 0;
                    self->animFrameDuration = 0;
                } else {
                    self->step = 1;
                    self->animFrameIdx = 3;
                    self->animFrameDuration = 0;
                    self->anim = D_us_80180F48;
                }
            }
        }
        break;
    }

    g_api.UpdateAnim(NULL, NULL);
}