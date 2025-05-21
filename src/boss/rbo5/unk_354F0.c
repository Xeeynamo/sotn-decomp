// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

extern AnimationFrame D_us_801806F4[];
extern EInit D_us_8018046C;
extern s32 D_us_801805B8;
extern u16 D_us_801806FC[][2];

void func_us_801B54F0(Entity* self) {
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
        if (PLAYER.posX.i.hi < 128) {
            g_Player.padSim = PAD_RIGHT;
            leftBlockFlag = 0;
            rightBlockFlag = 0x100;
        } else {
            g_Player.padSim = PAD_LEFT;
            leftBlockFlag = 0x100;
            rightBlockFlag = 0;
        }

        g_Player.demo_timer = 0x18;
        InitializeEntity(D_us_8018046C);
        self->animCurFrame = 0;
        self->ext.dopBGLight.unk84 = 0;

        if (!self->params) {
            self->params += leftBlockFlag;
            next = self + 1;
            for (i = 1; i < 4; i++, next++) {
                CreateEntityFromCurrentEntity(E_ID(ID_1B), next);
                next->params = i + leftBlockFlag;
            }

            for (i = 0; i < 4; i++, next++) {
                CreateEntityFromCurrentEntity(E_ID(ID_1B), next);
                next->params = i + rightBlockFlag;
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
        if (!self->params) {
            g_Player.padSim = 0;
            g_Player.demo_timer = 4;
        }
        // undeclared AnimateEntity
        if (!(AnimateEntity(D_us_801806F4, self))) {
            self->velocityY = FIX(4.0);
            self->step++;
        }
        break;

    case 3:
        if (!self->params) {
            g_Player.padSim = 0;
            g_Player.demo_timer = 0x18;
        }
        MoveEntity();
        self->velocityY += FIX(0.125);

        blockIndex = self->params & 0xFF;
        blockYPos = ((3 - blockIndex) * 16) + 96 + g_Tilemap.scrollY.i.hi;

        if (blockYPos < self->posY.i.hi) {
            if (blockIndex != 4) {
                next = self + 1;
                next->ext.ILLEGAL.u8[8] = 1;
            }
            self->posY.i.hi = blockYPos;
            tilemapIndex = 0xDE;
            if (!(self->params & 0x100)) {
                g_api.PlaySfx(SFX_EXPLODE_FAST_A);
                tilemapIndex = 0xC0;
            }
            tilemapIndex += ((3 - blockIndex) << 5);
            g_Tilemap.fg[tilemapIndex] = D_us_801806FC[7 - blockIndex][0];
            g_Tilemap.fg[tilemapIndex + 1] = D_us_801806FC[7 - blockIndex][1];
            self->velocityY = 0;
            self->step++;
        }
        break;
    case 4:
        if (D_us_801805B8 & 4) {
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
        g_Tilemap.fg[tilemapIndex] = D_us_801806FC[3 - blockIndex][0];
        g_Tilemap.fg[tilemapIndex + 1] = D_us_801806FC[3 - blockIndex][1];
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
