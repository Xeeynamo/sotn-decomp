// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

typedef struct {
    u16 animSet;
    u16 unk5A;
    u16 palette;
    u16 drawMode;
    u8* animData;
} EntityConfig;

extern EntityConfig D_us_80180EF8[];

void func_us_801B72E8(Entity* self) {
    s32 entityOffset;
    EntityConfig* entityConfig;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        entityOffset = self->params & 0xF;
        entityConfig = &D_us_80180EF8[entityOffset];
        self->palette = entityConfig->palette + 0x226;
        self->drawMode = entityConfig->drawMode;
        self->animSet = entityConfig->animSet;
        self->unk5A = entityConfig->unk5A;
        self->ext.et_801B72E8.animData = entityConfig->animData;
        self->step = entityOffset + 1;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        if (self->params & 0xF0) {
            self->palette = 0x819F;
            self->drawMode = DRAW_TPAGE;
            self->facingLeft = 1;
        }
        break;

    case 1:
        MoveEntity();
        self->velocityY = FIX(-1.0);
        if (!AnimateEntity(self->ext.et_801B72E8.animData, self)) {
            DestroyEntity(self);
        }
        break;

    case 2:
        MoveEntity();
        self->velocityY = FIX(-1.0);
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(self->ext.et_801B72E8.animData, self)) {
                self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
                self->drawFlags |= FLAG_DRAW_OPACITY;
                self->scaleX = self->scaleY = 256;
                self->opacity = 128;
                self->step_s++;
            }
            break;
        case 1:
            self->scaleX = self->scaleY += 4;
            self->opacity -= 16;
            if (!self->opacity) {
                DestroyEntity(self);
            }
        }
        break;

    case 3:
        MoveEntity();
        if (!AnimateEntity(self->ext.et_801B72E8.animData, self)) {
            DestroyEntity(self);
            return;
        }
        switch (self->step_s) {
        case 0:
            self->drawFlags = FLAG_DRAW_OPACITY;
            self->opacity = 128;
            self->step_s++;
            break;
        case 1:
            if (self->pose == 5) {
                self->step_s++;
            }
            break;
        case 2:
            self->opacity -= 4;
            break;
        }
        break;
    }
}

extern EInit D_us_801808EC;
extern u16 D_us_80180F1C[12];
extern u16 D_us_80180F34[12];
extern u16 D_us_80180F4C[12];
extern u16 D_us_80180F64[12];

void func_us_801B7580(Entity* self) {
    s32 posX;
    Entity* player = &PLAYER;
    s32 tileRowCounter, tilemapIndex;
    s16* tileDataPtr;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801808EC);
        self->zPriority = 105;
        if (self->params) {
            self->posX.i.hi = (536 - g_Tilemap.scrollX.i.hi);
        }
        if (self->params) {
            tilemapIndex = 221;
            tileDataPtr = D_us_80180F4C;
        } else {
            tilemapIndex = 192;
            tileDataPtr = D_us_80180F1C;
        }
        tileRowCounter = 0;
        while (tileRowCounter < 4) {
            (&g_Tilemap.fg[tilemapIndex])[0] = tileDataPtr[0];
            (&g_Tilemap.fg[tilemapIndex])[1] = tileDataPtr[1];
            (&g_Tilemap.fg[tilemapIndex])[2] = tileDataPtr[2];
            tilemapIndex += 32;
            tileRowCounter++;
            tileDataPtr += 3;
        }
        return;

    case 1:
        posX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (posX < 488) {
            if (self->params) {
                player = self + 1;
                CreateEntityFromEntity(E_UNK_32, self, player);
                player->posX.i.hi = (-24 - g_Tilemap.scrollX.i.hi);
                player->params = 0;
            }
            self->step++;
            return;
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
            if (posX < 488) {
                self->posX.i.hi = 488 - g_Tilemap.scrollX.i.hi;
                self->step++;
            }
        } else if (posX > 24) {
            self->posX.i.hi = 24 - g_Tilemap.scrollX.i.hi;
            self->step++;
        }
        break;

    case 3:
        if (self->params) {
            tilemapIndex = 221;
            tileDataPtr = (s16*)D_us_80180F64;
        } else {
            tilemapIndex = 192;
            tileDataPtr = D_us_80180F34;
        }
        tileRowCounter = 0;
        while (tileRowCounter < 4) {
            g_Tilemap.fg[tilemapIndex] = tileDataPtr[0];
            g_Tilemap.fg[tilemapIndex + 1] = tileDataPtr[1];
            g_Tilemap.fg[tilemapIndex + 2] = tileDataPtr[2];
            tilemapIndex += 32;
            tileRowCounter++;
            tileDataPtr += 3;
        }
        self->step++;
        return;

    case 255:
#include "../pad2_anim_debug.h"
    }
}
