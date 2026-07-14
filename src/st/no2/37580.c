// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

#ifdef VERSION_PSP
extern s32 E_ID(ID_32);
#endif

static s16 D_us_80180F1C[] = {0x021, 0x022, 0x048, 0x028, 0x029, 0x027,
                              0x028, 0x029, 0x027, 0x028, 0x029, 0x027};
static s16 D_us_80180F34[] = {0x6BF, 0x6C1, 0x6C5, 0x6C0, 0x6C2, 0x6C4,
                              0x6C0, 0x6C2, 0x6C4, 0x6C0, 0x6C2, 0x6C4};
static s16 D_us_80180F4C[] = {0x020, 0x021, 0x022, 0x027, 0x028, 0x029,
                              0x027, 0x028, 0x029, 0x027, 0x028, 0x029};
static s16 D_us_80180F64[] = {0x6C3, 0x6BF, 0x6C1, 0x6C4, 0x6C0, 0x6C2,
                              0x6C4, 0x6C0, 0x6C2, 0x6C4, 0x6C0, 0x6C2};

void func_us_801B7580(Entity* self) {
    s32 posX;
    Entity* player;
    s32 tileRowCounter, tilemapIndex;
    s16* tileDataPtr;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801808EC);
        self->zPriority = 0x69;
        if (self->params) {
            self->posX.i.hi = 0x218 - g_Tilemap.scrollX.i.hi;
        }
        if (self->params) {
            tilemapIndex = 0xDD;
            tileDataPtr = D_us_80180F4C;
        } else {
            tilemapIndex = 0xC0;
            tileDataPtr = D_us_80180F1C;
        }
        tileRowCounter = 0;
        while (tileRowCounter < 4) {
            (g_Tilemap.fg + 0)[tilemapIndex] = tileDataPtr[0];
            (g_Tilemap.fg + 1)[tilemapIndex] = tileDataPtr[1];
            (g_Tilemap.fg + 2)[tilemapIndex] = tileDataPtr[2];
            tilemapIndex += 0x20;
            tileRowCounter++;
            tileDataPtr += 3;
        }
        break;

    case 1:
        player = &PLAYER;
        posX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (posX < 0x1E8) {
            if (self->params) {
                player = self + 1;
                CreateEntityFromEntity(E_ID(ID_32), self, player);
                player->posX.i.hi = -0x18 - g_Tilemap.scrollX.i.hi;
                player->params = 0;
            }
            self->step++;
        }
        break;

    case 2:
        if (!self->step_s) {
            if (self->params) {
                self->velocityX = FIX(-0.5);
            } else {
                self->velocityX = FIX(0.5);
            }
            self->step_s++;
        }
        GetPlayerCollisionWith(self, 24, 32, 5);
        MoveEntity();
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->params) {
            if (posX < 0x1E8) {
                self->posX.i.hi = 0x1E8 - g_Tilemap.scrollX.i.hi;
                self->step++;
            }
        } else {
            if (posX > 0x18) {
                self->posX.i.hi = 0x18 - g_Tilemap.scrollX.i.hi;
                self->step++;
            }
        }
        break;

    case 3:
        if (self->params) {
            tilemapIndex = 0xDD;
            tileDataPtr = D_us_80180F64;
        } else {
            tilemapIndex = 0xC0;
            tileDataPtr = D_us_80180F34;
        }
        tileRowCounter = 0;
        while (tileRowCounter < 4) {
            (g_Tilemap.fg + 0)[tilemapIndex] = tileDataPtr[0];
            (g_Tilemap.fg + 1)[tilemapIndex] = tileDataPtr[1];
            (g_Tilemap.fg + 2)[tilemapIndex] = tileDataPtr[2];
            tilemapIndex += 0x20;
            tileRowCounter++;
            tileDataPtr += 3;
        }
        self->step++;
        break;

    case 255:
#include "../pad2_anim_debug.h"
    }
}
