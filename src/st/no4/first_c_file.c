// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", EntityBreakable);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C123C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C12B0);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C15F8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C1844);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C1C94);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C1EE4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C21AC);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2474);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2850);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2B78);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2E60);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3160);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C34EC);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C37C8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3A04);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3CC4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3FB0);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4228);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4520);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4738);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4980);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4BD8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4D2C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5020);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C50FC);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5134);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5268);

extern s16 D_us_801815DC[]; // animCurFrame
extern u16 D_us_801815EC[]; // facingLeft
extern s16 D_us_801815FC[]; // rotZ
extern s32 D_us_8018160C[]; // velocityY

void func_us_801C542C(Entity* self) {
    u16 params = self->params;
    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = D_us_801815DC[params];
        self->facingLeft = D_us_801815EC[params];
        self->velocityY = D_us_8018160C[params];
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->rotZ = false;
    }
    if (F(self->velocityY).i.hi < 8) {
        F(self->velocityY).val += FIX(0.25);
    }
    MoveEntity();
    self->rotZ += D_us_801815FC[params];
}

extern s16 D_us_8018162C[];

void func_us_801C5518(Entity* self) {
    Tilemap* tmap = &g_Tilemap;
    u16 diff;
    s16* dataPtr;

    if (self->step == 0) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    dataPtr = &D_us_8018162C[self->params << 2];
    diff = ((s16)PLAYER.posX.i.hi + (s16)tmap->scrollX.i.hi - (s16)*dataPtr++);

    if (*dataPtr++ >= diff) {
        diff = (((s16)PLAYER.posY.i.hi + (s16)tmap->scrollY.i.hi) -
                (s16)*dataPtr++);
        if (*dataPtr >= diff) {
            if (PLAYER.velocityY < 0) {
                PLAYER.velocityY *= 7;
                PLAYER.velocityY /= 8;
            } else if (PLAYER.velocityY > 0) {
                PLAYER.nFramesInvincibility = 1;
            }
        }
    }
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5628);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C582C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5868);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C58A0);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C59E0);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5AD4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5C7C);

void func_us_801C6CEC(Entity* self) {

    Entity* prev = self - 1;

    if (self->step == 0) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x1C;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->zPriority = 0x9A;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
    }
    self->posX.i.hi = prev->posX.i.hi;
    self->rotZ = prev->rotZ;
    if (self->facingLeft != 0) {
        self->posX.i.hi += 4;
    } else {
        self->posX.i.hi -= 4;
    }
    self->posY.i.hi = prev->posY.i.hi;
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C6DA8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C7204);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C726C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C789C);

void func_us_801C7FA4(void) {}

extern u16 D_us_801817E8;

void func_us_801C7FAC(void) {
    s32 i;
    Tilemap* tileMap = &g_Tilemap;
    s16 offset = 0x595;
    u16* var_a2 = &D_us_801817E8;

    for (i = 0; i < 7; i++) {
        *(tileMap->fg + offset) = *var_a2++;
        offset++;
        *(tileMap->fg + offset) = *var_a2++;
        offset = offset + 0xCF;
    }
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C801C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C8248);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C82B8);
