// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

INCLUDE_ASM("st/rtop/nonmatchings/204E8", func_us_801A04E8);

INCLUDE_ASM("st/rtop/nonmatchings/204E8", func_801A8328);

// same as TOP
// TODO: EntityStairSwitch
extern EInit D_us_801805C0;
void func_us_801A0B48(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_us_801805C0);
        self->animCurFrame = 5;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->hitboxState = 0;
        if (self->params != 0) {
            self->step = 4;
            self->zPriority += 2;
        } else {
            self->animCurFrame = 4;
            self->hitboxState = 0;
            self->palette += 1;
            g_Tilemap.fg[0x251B] = 0x328;
            self->step = 3;
        }
    }
}

// in upper castle, possibly stairs
void func_us_801A0BF4(Entity* self) {
    s32 i;
    s32 tilemapIndex;
    s32 posX;
    s32 posY;

    FntPrint("step %x\n", self->step);
    FntPrint("w_y %x\n", g_PlayerY);
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805C0);

        // cursed!
        *((volatile s16*) &self->animCurFrame) = 3;
        *((volatile s16*) &self->animCurFrame) = 0;
        self->zPriority += 2;
        self->step = 3;
        
        for (i = 0, tilemapIndex = 0x2724; i < 5; i++, tilemapIndex++) {
            g_Tilemap.fg[tilemapIndex] = 0x32E;
        }
        break;

    case 3:
        self->animCurFrame = 0;
        posX = LOH(PLAYER.posX.i.hi) + g_Tilemap.scrollX.i.hi;
        posY = LOH(PLAYER.posY.i.hi) + g_Tilemap.scrollY.i.hi;

        if (posX > 0x220 &&
            posX < 0x2C0 && posY > 0x460 && g_PlayerY >= 0x4DE) {
            g_Tilemap.height = 0x4FB;
            g_Tilemap.bottom = g_Tilemap.bottom - 3;
            self->step++;
        }
        break;
    }
}

INCLUDE_ASM("st/rtop/nonmatchings/204E8", func_us_801A0D4C);

INCLUDE_ASM("st/rtop/nonmatchings/204E8", func_us_801A1108);

INCLUDE_ASM("st/rtop/nonmatchings/204E8", func_us_801A13C0);

INCLUDE_ASM("st/rtop/nonmatchings/204E8", func_us_801A1940);

INCLUDE_ASM("st/rtop/nonmatchings/204E8", func_us_801A20A4);

INCLUDE_ASM("st/rtop/nonmatchings/204E8", func_us_801A21F8);

INCLUDE_ASM("st/rtop/nonmatchings/204E8", func_us_801A2408);
