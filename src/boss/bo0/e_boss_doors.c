// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo0.h"

extern EInit g_EInitBossDoors;
extern s32 D_us_80181190;

static s16 D_us_80181374[] = {
    0x0021, 0x0022, 0x0048, 0x0028, 0x0029, 0x0027,
    0x0028, 0x0029, 0x0027, 0x0028, 0x0029, 0x0027,
};

static s16 D_us_8018138C[] = {
    0x06BF, 0x06C1, 0x06C5, 0x06C0, 0x06C2, 0x06C4,
    0x06C0, 0x06C2, 0x06C4, 0x06C0, 0x06C2, 0x06C4,
};

static s16 D_us_801813A4[] = {
    0x0020, 0x0021, 0x0022, 0x0027, 0x0028, 0x0029,
    0x0027, 0x0028, 0x0029, 0x0027, 0x0028, 0x0029,
};

static s16 D_us_801813BC[] = {
    0x06C3, 0x06BF, 0x06C1, 0x06C4, 0x06C0, 0x06C2,
    0x06C4, 0x06C0, 0x06C2, 0x06C4, 0x06C0, 0x06C2,
};

void EntityBossDoors(Entity* self) {
    Entity* entity;
    s32 offsetX;
    s32 i;
    s32 fgIndex;
    s16* fgTiles;

    switch (self->step) {
    case 0:
        if (D_us_80181190) {
            DestroyEntity(self);
            return;
        }

        InitializeEntity(g_EInitBossDoors);
        self->zPriority = 0x69;
        if (self->params) {
            self->posX.i.hi = 0x218 - g_Tilemap.scrollX.i.hi;
        }
        if (self->params) {
            fgIndex = 0xDD;
            fgTiles = D_us_801813A4;
        } else {
            fgIndex = 0xC0;
            fgTiles = D_us_80181374;
        }

        for (i = 0; i < 4; i++, fgTiles += 3) {
            (&g_Tilemap.fg[fgIndex])[0] = fgTiles[0];
            (&g_Tilemap.fg[fgIndex])[1] = fgTiles[1];
            (&g_Tilemap.fg[fgIndex])[2] = fgTiles[2];
            fgIndex += 32;
        }

        break;
    case 1:
        entity = &PLAYER;
        offsetX = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (offsetX < 0x1E8) {
            if (self->params) {
                entity = self + 1;
                CreateEntityFromEntity(E_ID(BOSS_DOORS), self, entity);
                entity->posX.i.hi = -0x18 - g_Tilemap.scrollX.i.hi;
                entity->params = 0;
            }
            PlaySfxPositional(SFX_STONE_MOVE_B);
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
        GetPlayerCollisionWith(self, 0x18, 0x20, 5);
        MoveEntity();
        if (!(g_Timer & 0xF)) {
            PlaySfxPositional(SFX_STONE_MOVE_B);
        }
        offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->params) {
            if (offsetX < 0x1E8) {
                self->posX.i.hi = 0x1E8 - g_Tilemap.scrollX.i.hi;
                self->step++;
            }
        } else if (offsetX > 0x18) {
            self->posX.i.hi = 0x18 - g_Tilemap.scrollX.i.hi;
            self->step++;
        }
        break;
    case 3:
        if (self->params) {
            fgIndex = 0xDD;
            fgTiles = D_us_801813BC;
        } else {
            fgIndex = 0xC0;
            fgTiles = D_us_8018138C;
        }
        for (i = 0; i < 4; i++, fgTiles += 3) {
            (&g_Tilemap.fg[fgIndex])[0] = fgTiles[0];
            (&g_Tilemap.fg[fgIndex])[1] = fgTiles[1];
            (&g_Tilemap.fg[fgIndex])[2] = fgTiles[2];
            fgIndex += 32;
        }
        self->step++;
        break;
    case 4:
        if (D_us_80181190) {
            self->step++;
        }
        break;
    case 5:
        if (self->params) {
            fgIndex = 0xDD;
            fgTiles = D_us_801813A4;
        } else {
            fgIndex = 0xC0;
            fgTiles = D_us_80181374;
        }
        for (i = 0; i < 4; i++, fgTiles += 3) {
            (&g_Tilemap.fg[fgIndex])[0] = fgTiles[0];
            (&g_Tilemap.fg[fgIndex])[1] = fgTiles[1];
            (&g_Tilemap.fg[fgIndex])[2] = fgTiles[2];
            fgIndex += 32;
        }
        if (self->params) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        self->step++;
        break;
    case 6:
        MoveEntity();
        offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->params) {
            if (offsetX > 0x218) {
                DestroyEntity(self);
                return;
            }
        } else if (offsetX < -0x18) {
            DestroyEntity(self);
            return;
        }
        break;

    case 0xFF:
#include "../../st/pad2_anim_debug.h"
        break;
    }
}
