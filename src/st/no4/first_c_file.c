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

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5518);

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

typedef enum {
    BREAKABLE_CRYSTAL_FLOOR_INIT,
    BREAKABLE_CRYSTAL_FLOOR_IDLE,
    BREAKABLE_CRYSTAL_FLOOR_BREAK,
    BREAKABLE_CRYSTAL_FLOOR_CHECK
} BREAKABLE_CRYSTAL_FLOOR_STEPS;

extern s16 D_us_80181880[];

void EntityBreakableCrystalFloor(Entity* self) {
    Entity* newEntity;
    s16* tileLayoutPtr;
    s32 tilePos;
    s32 i;

    // NOTE: Behind the breakable floor, the background layer is originally
    // empty in the tilemap data (all black)
    switch (self->step) {
    case BREAKABLE_CRYSTAL_FLOOR_INIT:
        // Overwrite the background tiles so when the floor is broken, the cave
        // wall is visible
        // Overwrite the foreground tiles based on whether the floor has
        // already been broken or not
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 16;
        self->hitboxHeight = 16;
        self->hitboxState = 2;
        if (g_CastleFlags[NO4_SECRET_FLOOR_OPEN]) {
            i = 0x12;
        } else {
            i = 0;
        }
        tileLayoutPtr = &D_us_80181880[i];
        tilePos = 0x2D3;
        (&g_BgLayers[0].layout[tilePos])[1] = 0x3FE;
        (&g_BgLayers[0].layout[tilePos])[2] = 0x3FF;
        (&g_BgLayers[0].layout[tilePos])[17] = 0x401;
        (&g_BgLayers[0].layout[tilePos])[18] = 0x402;
        for (i = 0; i < 2; i++, tileLayoutPtr += 3) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[1] = tileLayoutPtr[1];
            (&g_Tilemap.fg[tilePos])[2] = tileLayoutPtr[2];
            tilePos += 0x10;
        }
        if (g_CastleFlags[NO4_SECRET_FLOOR_OPEN]) {
            DestroyEntity(self);
            return;
        }
        // fallthrough
    case BREAKABLE_CRYSTAL_FLOOR_IDLE:
        // Initially, go into an idle state
        // When hit, process to the break-and-check states
        if (self->hitFlags) {
            self->step++;
        }
        break;
    case BREAKABLE_CRYSTAL_FLOOR_BREAK:
        // Update the tiles with every break and spawn puffs of smoke
        self->ext.breakableCrystalFloor.breakCount++;
        tileLayoutPtr =
            &D_us_80181880[self->ext.breakableCrystalFloor.breakCount * 6];
        tilePos = 0x2D3;
        for (i = 0; i < 2; i++, tileLayoutPtr += 3) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[1] = tileLayoutPtr[1];
            (&g_Tilemap.fg[tilePos])[2] = tileLayoutPtr[2];
            tilePos += 0x10;
        }
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
        }
        // There is a cooldown of 32 frames between breaks
        self->ext.breakableCrystalFloor.resetTimer = 32;
        self->step += 1;
        if (self->ext.breakableCrystalFloor.breakCount == 3) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
            }
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            g_CastleFlags[NO4_SECRET_FLOOR_OPEN] = 1;
            g_api_func_800F1FC4(NO4_SECRET_FLOOR_OPEN);
            DestroyEntity(self);
            return;
        }
        break;
    case BREAKABLE_CRYSTAL_FLOOR_CHECK:
        // Wait for cooldown to finish, then switch to idle state
        if (!--self->ext.breakableCrystalFloor.resetTimer) {
            self->step = BREAKABLE_CRYSTAL_FLOOR_IDLE;
            return;
        }
        break;
    }
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C89F4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C8CC4);
