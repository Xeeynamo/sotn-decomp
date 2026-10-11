// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo7/rbo7.h"

extern EInit D_us_8018042C;
extern s32 D_us_80180564;
extern s32 E_ID(UNK_16);
extern s16 D_pspeu_09255580[];
extern s16 D_pspeu_09255598[];
extern s16 D_pspeu_092555B0[];
extern s16 D_pspeu_092555C8[];

void func_us_801BAB18_from_bo0(Entity* self) {
    Entity* entity;
    s32 offsetX;
    s32 i;
    s32 fgIndex;
    s16* fgTiles;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018042C);
        self->zPriority = 0x69;
        self->animCurFrame = 14;
        if (self->params) {
            self->posX.i.hi = -0x18 - g_Tilemap.scrollX.i.hi;
        }
        if (self->params) {
            fgIndex = 0x322;
            fgTiles = D_pspeu_09255580;
        } else {
            fgIndex = 0x33F;
            fgTiles = D_pspeu_092555B0;
        }
        for (i = 0; i < 4; i++, fgTiles += 3) {
            (&g_Tilemap.fg[fgIndex])[0] = fgTiles[0];
            (&g_Tilemap.fg[fgIndex])[-1] = fgTiles[1];
            (&g_Tilemap.fg[fgIndex])[-2] = fgTiles[2];
            fgIndex -= 32;
        }
        /* fall through */
    case 1:
        entity = &PLAYER;
        offsetX = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (offsetX > 0x18) {
            D_us_80180564 = 1;
            if (self->params) {
                entity = self + 1;
                CreateEntityFromEntity(E_ID(UNK_16), self, entity);
                entity->posX.i.hi = 0x218 - g_Tilemap.scrollX.i.hi;
                entity->params = 0;
            }
            self->step++;
        }
        break;
    case 2:
        if (!self->step_s) {
            if (self->params) {
                self->velocityX = FIX(0.5);
            } else {
                self->velocityX = FIX(-0.5);
            }
            self->step_s++;
        }
        GetPlayerCollisionWith(self, 0x18, 0x20, 5);
        MoveEntity();
        offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->params) {
            if (offsetX > 0x18) {
                self->posX.i.hi = 0x18 - g_Tilemap.scrollX.i.hi;
                self->step++;
            }
        } else if (offsetX < 0x1E8) {
            self->posX.i.hi = 0x1E8 - g_Tilemap.scrollX.i.hi;
            self->step++;
        }
        break;
    case 3:
        if (self->params) {
            fgIndex = 0x322;
            fgTiles = D_pspeu_09255598;
        } else {
            fgIndex = 0x33F;
            fgTiles = D_pspeu_092555C8;
        }
        for (i = 0; i < 4; i++, fgTiles += 3) {
            (&g_Tilemap.fg[fgIndex])[0] = fgTiles[0];
            (&g_Tilemap.fg[fgIndex])[-1] = fgTiles[1];
            (&g_Tilemap.fg[fgIndex])[-2] = fgTiles[2];
            fgIndex -= 32;
        }
        self->step++;
        break;
    case 4:
        if (!D_us_80180564) {
            self->step++;
        }
        break;
    case 5:
        if (self->params) {
            fgIndex = 0x322;
            fgTiles = D_pspeu_09255580;
        } else {
            fgIndex = 0x33F;
            fgTiles = D_pspeu_092555B0;
        }
        for (i = 0; i < 4; i++, fgTiles += 3) {
            (&g_Tilemap.fg[fgIndex])[0] = fgTiles[0];
            (&g_Tilemap.fg[fgIndex])[-1] = fgTiles[1];
            (&g_Tilemap.fg[fgIndex])[-2] = fgTiles[2];
            fgIndex -= 32;
        }
        if (self->params) {
            self->velocityX = FIX(-0.5);
        } else {
            self->velocityX = FIX(0.5);
        }
        self->step++;
        break;
    case 6:
        MoveEntity();
        offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->params) {
            if (offsetX < -0x30) {
                self->step++;
            }
        } else if (offsetX > 0x230) {
            self->step++;
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
        break;
    }
}
