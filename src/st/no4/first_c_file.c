// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

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

void func_us_801C4BD8(Entity* self) {
    Tilemap* tmap;
    s16* dataPtr;
    s32 offsetX;

    if (self->step == 0) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    tmap = &g_Tilemap;
    dataPtr = &D_us_8018159C[self->params * 4];

    offsetX = (PLAYER.posX.i.hi + tmap->scrollX.i.hi - *dataPtr++);
    offsetX = (offsetX * *dataPtr++) / 4096;
    offsetX += *dataPtr++;

    if (offsetX < 0) {
        offsetX = 0;
    } else if (offsetX >= 0x80) {
        offsetX = 0x7F;
    }

    if (offsetX == 0) {
        if (D_us_80181108 != 0) {
            D_us_80181108 = 0;
            g_api_PlaySfx(0xA6);
            return;
        }
    }
    if (D_us_80181108 != 0) {
        g_api_func_80134678(offsetX, *dataPtr++);
        return;
    }

    g_api_PlaySfxVolPan(0x797, offsetX, *dataPtr++);
    D_us_80181108 = 1;
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4D2C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5020);

void func_us_801C50FC(void) {
    u16* tileIdx;
    s16 i;

    tileIdx = &g_Tilemap.fg[691];

    for (i = 0; i < 10; i++, tileIdx++) {
        *tileIdx = 0;
    }
}

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
    Tilemap* tmap;
    u16 diff;
    s16* dataPtr;

    if (self->step == 0) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    tmap = &g_Tilemap;
    dataPtr = &D_us_8018162C[self->params << 2];
    diff = PLAYER.posX.i.hi + tmap->scrollX.i.hi - *dataPtr++;

    if (*dataPtr++ >= diff) {
        diff = PLAYER.posY.i.hi + tmap->scrollY.i.hi - *dataPtr++;
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

void func_us_801C58A0(Entity* self) {
    Entity* newEnt;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] != 0) {
            func_us_801C5868();
            DestroyEntity(self);
        }
        break;
    case 1:
        if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] != 0) {
            newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_SKELETON_APE, newEnt);
                newEnt->params = 2;
                newEnt->posY.i.hi = newEnt->posY.i.hi - 96;
                newEnt->posX.i.hi = newEnt->posX.i.hi + 96;
                self->ext.prim = (Primitive*)(newEnt + 2); // I dont like this
            }
            self->step += 1;
        }
        break;
    case 2:
        if (self->ext.prim->x3 == 4U) {
            func_us_801C5868();
            func_us_801C5134();
            DestroyEntity(self);
        }
        break;
    }
}

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
