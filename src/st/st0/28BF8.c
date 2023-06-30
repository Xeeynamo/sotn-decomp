/*
 * Overlay: ST0
 * Description: Cutscene of Richter talking to Dracula
 */

#include "st0.h"

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", func_801A8BF8);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", func_801A8CB0);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", func_801A8E34);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", func_801A8E60);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", func_801A910C);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", EntityDialogue);

void func_801AA218(s16 arg0) {
    s16 temp_a1 = ((0xE0 - arg0) / 2) + 0x80;
    s16 temp_v1 = temp_a1 - *D_8009740C;

    if (temp_v1 >= 3) {
        *D_8009740C = *D_8009740C + 2;
    } else if (temp_v1 < -2) {
        *D_8009740C = *D_8009740C - 2;
    } else {
        *D_8009740C = temp_a1;
    }
}

void EntityCutscene(Entity* self) {
    Unkstruct8* roomLayout = &g_CurrentRoomTileLayout;
    Entity* player = &PLAYER;
    u16 posX;

    self->posX.i.hi = player->posX.i.hi;
    self->posY.i.hi = player->posY.i.hi - 1;

    if ((self->step != 14) && (D_801C24C8 != 0) && (D_801C2580 != 0) &&
        (self->step >= 5)) {
        self->step = 15;
        self->animSet = 0;
        self->animCurFrame = 0;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180598);
        self->unk5A = 0x46;
        self->palette = 0x120;
        break;

    case 1:
        if (self->step_s != 0) {
            if ((player->step < 3) || (player->step == 25)) {
                posX = player->posX.i.hi + roomLayout->unkA;
                if (posX > 0x8000) {
                    posX = 0;
                }
                if (posX > 0xA0) {
                    g_Player.D_80072EF4 = 0x8000;
                } else {
                    g_Player.D_80072EF4 = 0x2000;
                }
                g_Entities[1].ext.generic.unk7C.S8.unk0 = 1;
                g_Player.D_80072EFC = 0xFF;
                func_801AA218(posX);
                SetStep(2);
            }
        } else {
            if ((player->posX.i.hi + roomLayout->unkA) < 0xE1) {
                D_8003C8B8 = 0;
                self->step_s++;
            }
        }
        break;

    case 2:
        posX = player->posX.i.hi + roomLayout->unkA;
        if (posX > 0x8000) {
            posX = 0;
        }

        if ((g_Player.D_80072EF4 == 0x8000) && (posX <= 0xA0) ||
            (g_Player.D_80072EF4 == 0x2000) && (posX >= 0x9F)) {
            g_Player.D_80072EFC = 1;
            g_Player.D_80072EF4 = 0x8000;
            self->ext.generic.unk7C.s = 0x18;
            D_801C257C |= 1;
            self->step++;
        }
        func_801AA218(posX);
        break;

    case 3:
        posX = player->posX.i.hi + roomLayout->unkA;
        if (posX > 0x8000) {
            posX = 0;
        }
        func_801AA218(posX);
        g_Player.D_80072EFC = 1;
        g_Player.D_80072EF4 = 0;
        if (!--self->ext.generic.unk7C.u) {
            SetStep(4);
        }
        break;

    case 4:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180830, self) == 0) {
            self->step++;
            g_CurrentRoom.width = 0x100;
        }
        player->animCurFrame = self->animCurFrame;
        break;

    case 5:
        g_Player.D_80072EFC = 1;
        player->animCurFrame = self->animCurFrame;
        if (D_801C257C & 0x400) {
            player->animCurFrame = 0;
            self->animSet = 0x8005;
            self->animCurFrame = 1;
            SetStep(6);
        }
        break;

    case 6:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018083C, self) == 0) {
            if (D_801C257C & 0x800) {
                SetStep(7);
            }
        }
        player->animCurFrame = 0;
        break;

    case 7:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018084C, self) == 0) {
            if (D_801C257C & 0x1000) {
                SetStep(8);
            }
        }
        player->animCurFrame = 0;
        break;

    case 8:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018085C, self) == 0) {
            if (D_801C257C & 0x2000) {
                SetStep(9);
            }
        }
        player->animCurFrame = 0;
        break;

    case 9:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180864, self) == 0) {
            if (D_801C257C & 0x4000) {
                SetStep(10);
            }
        }
        player->animCurFrame = 0;
        break;

    case 10:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018086C, self) == 0) {
            if (D_801C257C & 0x8000) {
                SetStep(11);
            }
        }
        player->animCurFrame = 0;
        break;

    case 11:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018087C, self) == 0) {
            if (D_801C257C & 0x10000) {
                SetStep(12);
            }
        }
        player->animCurFrame = 0;
        break;

    case 12:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180884, self) == 0) {
            if (D_801C257C & 0x20000) {
                SetStep(13);
            }
        }
        player->animCurFrame = 0;
        break;

    case 13:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018088C, self) == 0) {
            if (D_801C257C & 0x40000) {
                SetStep(14);
            }
        }
        player->animCurFrame = 0;
        break;

    case 14:
        g_Player.D_80072EFC = 1;
        player->animCurFrame = 0;
        if (AnimateEntity(D_80180894, self) == 0) {
            self->animCurFrame = 0;
            player->animCurFrame = 7;
            SetStep(15);
        }
        break;

    case 15:
        g_Player.D_80072EFC = 1;
        player->animCurFrame = 7;
        if (D_801C257C & 4) {
            g_Player.D_80072EF4 = 0x8000;
            DestroyEntity(self);
            D_8003C8B8 = 1;
        }
        break;
    }
}