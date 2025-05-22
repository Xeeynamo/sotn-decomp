// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

extern EInit D_us_80180458;
extern s32 D_us_801805A0;
extern u8 D_us_80180668[];
extern u16 D_us_80180670[][2];

#ifdef VERSION_PSP
extern s32 D_pspeu_0926BCA8;
#endif

// 4-segment block doors
// n.b.! the equivalent RBO5 function, `func_us_801B54F0`
//       appears the same as the PSP version of this BO4
//       version.
void func_us_801B65FC(Entity* self) {
    Entity* next;
    s32 i;
    s32 tilemapIndex;
    s32 leftRightOffset;
    s32 rightBlockFlag;
    s32 leftBlockFlag;
    u32 blockIndex;
    s32 offsetX;
    s32 blockYPos;

    switch (self->step) {
    case 0:
        // are you coming from the left door or right door
        if (PLAYER.posX.i.hi < 0x80) {
            g_Player.padSim = PAD_RIGHT;
#ifdef VERSION_PSP
            leftBlockFlag = 0;
            rightBlockFlag = 0x100;
#endif
        } else {
            g_Player.padSim = PAD_LEFT;
#ifdef VERSION_PSP
            leftBlockFlag = 0x100;
            rightBlockFlag = 0;
#endif
        }

        g_Player.demo_timer = 0x18;
        InitializeEntity(D_us_80180458);
        self->animCurFrame = 0;
        self->ext.dopBGLight.unk84 = 0;

        if (!self->params) {
            self->params += leftBlockFlag;
            next = self + 1;
            for (i = 1; i < 4; i++, next++) {
                // no declaration
                CreateEntityFromCurrentEntity(E_ID(ID_1B), next);
#ifdef VERSION_PSP
                next->params = i + leftBlockFlag;
#else
                next->params = i;
#endif
            }

            for (i = 0; i < 4; i++, next++) {
                // no declaration
                CreateEntityFromCurrentEntity(E_ID(ID_1B), next);
#ifdef VERSION_PSP
                next->params = i + rightBlockFlag;
#else
                next->params = 0x100 + i;
#endif
            }
        }

        self->posY.i.hi = 0x68 - g_Tilemap.scrollY.i.hi;
        if (self->params & 0x100) {
            self->posX.i.hi = 0x1F0 - g_Tilemap.scrollX.i.hi;
        } else {
            self->posX.i.hi = 0x10 - g_Tilemap.scrollX.i.hi;
        }

        break;

    case 1:
        if ((!self->params) && (g_Player.demo_timer < 9)) {
            g_Player.padSim = 0;
            g_Player.demo_timer = 4;
            self->ext.dopBGLight.unk84 = 1;
        }

        if (self->ext.dopBGLight.unk84) {
            self->step = 2;
        }
        break;

    case 2:
#ifdef VERSION_PSP
        if (!self->params) {
#endif
            g_Player.padSim = PAD_NONE;
            g_Player.demo_timer = 4;

#ifdef VERSION_PSP
        }
#endif
        // undeclared AnimateEntity
        if (!AnimateEntity(D_us_80180668, self)) {
            self->velocityY = FIX(4.0);
            self->step++;
        }
        break;

    case 3:
#ifdef VERSION_PSP
        if (!self->params) {
#endif
            g_Player.padSim = 0;
            g_Player.demo_timer = 0x18;

#ifdef VERSION_PSP
        }
#endif
        MoveEntity();
        self->velocityY += FIX(0.125);

        blockIndex = self->params & 0xFF;
        blockYPos = ((3 - blockIndex) * 16) + 96 + g_Tilemap.scrollY.i.hi;

        if (blockYPos < self->posY.i.hi) {
            if (blockIndex != 4) {
                next = self + 1;
                next->ext.dopBGLight.unk84 = 1;
            }
            self->posY.i.hi = blockYPos;
            tilemapIndex = 0xDE;
            if (!(self->params & 0x100)) {
                g_api.PlaySfx(SFX_DOOR_CLOSE_B);
                tilemapIndex = 0xC0;
            }
            tilemapIndex += ((3 - blockIndex) << 5);
            g_Tilemap.fg[tilemapIndex] = D_us_80180670[7 - blockIndex][0];
            g_Tilemap.fg[tilemapIndex + 1] = D_us_80180670[7 - blockIndex][1];
            self->velocityY = 0;
            self->step++;
        }
        break;
    case 4:
        if (D_us_801805A0 & 4) {
            self->step++;
        }
        break;

    case 5:
        tilemapIndex = 0xC0;
        blockIndex = self->params & 0xFF;
        if (self->params & 0x100) {
            tilemapIndex = 0xDE;
        }
        tilemapIndex += ((3 - blockIndex) << 5);
        g_Tilemap.fg[tilemapIndex] = D_us_80180670[3 - blockIndex][0];
        g_Tilemap.fg[tilemapIndex + 1] = D_us_80180670[3 - blockIndex][1];
        self->step++;
        break;

    case 6:
        if (self->params & 0x100) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        MoveEntity();

        offsetX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        if (offsetX < -32 || offsetX > 0x220) {
            self->step++;
        }
        break;
    case 7:
        break;
    }
}
