// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

extern u16 D_us_80180D8C[];
extern EInit D_us_80180790;

void func_us_801A9BEC(Entity* self) {
    u8 srcIdx;
    s32 dstBase;
    s32 i, j;

    switch(self->step) {
        case 0: // only one case so this is a static entity
        InitializeEntity(D_us_80180790);
        self->animCurFrame = 0;
        dstBase = 0x50F;
        srcIdx = 0;
        for(i = 0; i < 6; i++) {
            for(j = 0; j < 4; j++) {
                g_Tilemap.fg[dstBase - j] = D_us_80180D8C[srcIdx];
                srcIdx++;
            }
            dstBase -= 0x30;
        }
        self->step = 3;
    }
}
