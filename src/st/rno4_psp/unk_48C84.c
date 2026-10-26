// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_48C84", func_pspeu_09246618_from_bo3);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_48C84", func_us_801A07CC_from_bo3);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_48C84", func_us_801C5518_from_no4);

extern u16 D_us_80181610[];

static void func_us_801C9048(s32 arg0) {
    s16 tilePos;
    s32 i;
    u16* tileLayoutPtr;

    Tilemap* tilemap;
    tilemap = &g_Tilemap;

    tilePos = 0x1E0;
    tileLayoutPtr = &(D_us_80181610[arg0 * 4]);

    for (i = 0; i < 4; ++i) {
        tilemap->fg[tilePos] = *(tileLayoutPtr++);
        tilePos += 0x50;
    }
}

extern s16 D_us_801815DC;
extern EInit g_EInitCommon;

void func_us_801C909C(Entity* self) {
    s16 screen_pos;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x25;
        if (D_us_801815DC) {
            func_us_801C9048(1);
            self->step = 0x4;
            break;
        }
        func_us_801C9048(0);
        self->posY.i.hi -= 0x40;
        break;

    case 1:
        if (D_us_801815DC) {
            self->step += 1;
            self->velocityY = FIX(4.0);
        }

        break;

    case 2:
        self->posX.i.hi -= 8;
        GetPlayerCollisionWith(self, 0x10, 0x20, 9);
        self->posX.i.hi += 8;
        MoveEntity();
        screen_pos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (screen_pos >= 0x80) {
            g_api.PlaySfxVolPan(SFX_EXPLODE_B, 0x7F, -6);
            func_us_801C9048(1);
            self->velocityY = FIX(-1.0);
            self->step += 1;
        }
        break;

    case 3:
        self->velocityY += FIX(0.125);
        MoveEntity();
        screen_pos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (screen_pos >= 0x80) {
            self->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
            self->step = 6;
        }
        break;

    case 4:
        if (!D_us_801815DC) {
            self->step += 1;
            self->velocityY = FIX(-1.0);
        }
        break;

    case 5:
        self->posX.i.hi -= 8;
        GetPlayerCollisionWith(self, 0x10, 0x20, 0xB);
        self->posX.i.hi += 8;
        MoveEntity();
        screen_pos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (screen_pos < 0x41) {
            func_us_801C9048(0);
            self->step += 1;
        }
        break;

    case 6:
        break;
    }
}
