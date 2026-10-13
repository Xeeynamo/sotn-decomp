// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"

extern EInit g_EInitBossDoor;

// set by EntityBossFightManager while the fight is on
s32 D_us_80180810 = 0;
static AnimateEntityFrame anim_appear[] = {
    POSE(1, 0x72, 0), POSE(1, 0x73, 0), POSE(1, 0x74, 0), POSE_END};
// tiles written in the foreground, the first four open the exit, the last four
// close it
static u16 door_tiles[][2] = {
    {0x0410, 0x0438}, {0x03FC, 0x040E}, {0x03BC, 0x03CA}, {0x03A2, 0x03A1},
    {0x05B5, 0x05B4}, {0x05B3, 0x05B2}, {0x05B1, 0x05B0}, {0x05AF, 0x05AE},
};

void EntityBossDoors(Entity* self) {
    Entity* nextEntity;
    s32 i;
    s32 params;
    s32 fgIndex;
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBossDoor);
        self->animCurFrame = 0;
        self->ext.et_801C0B9C.unk84 = 0;
        if (!self->params) {
            nextEntity = self + 1;
            for (i = 1; i < 4; i++, nextEntity++) {
                CreateEntityFromCurrentEntity(E_ID(BOSS_DOORS), nextEntity);
                nextEntity->params = i;
            }

            for (i = 0; i < 4; i++, nextEntity++) {
                CreateEntityFromCurrentEntity(E_ID(BOSS_DOORS), nextEntity);
                nextEntity->params = i + 0x100;
            }
        }
        self->posY.i.hi = 0x68 - g_Tilemap.scrollY.i.hi;
        if (self->params & 0x100) {
            self->posX.i.hi = 0x1F0 - g_Tilemap.scrollX.i.hi;
        } else {
            self->posX.i.hi = 0x10 - g_Tilemap.scrollX.i.hi;
        }
        break;
    case 1:
        // the first piece of each side drops when the fight starts, the
        // others when the piece before them landed
        if (D_us_80180810 && !(self->params & 0xFF)) {
            self->step = 2;
        }
        if (self->ext.et_801C0B9C.unk84) {
            self->step = 2;
        }
        break;
    case 2:
        if (!AnimateEntity(anim_appear, self)) {
            self->velocityY = FIX(4);
            self->step++;
        }
        break;
    case 3:
        MoveEntity();
        self->velocityY += FIX(0.125);

        params = self->params & 0xFF;
        posY = (((3 - params) * 0x10) + 0x60) + g_Tilemap.scrollY.i.hi;
        if (posY < self->posY.i.hi) {
            if (params != 4) {
                nextEntity = self + 1;
                nextEntity->ext.et_801C0B9C.unk84 = 1;
            }
            self->posY.i.hi = posY;
            fgIndex = 0xC0;
            if (self->params & 0x100) {
                g_api.PlaySfx(SFX_DOOR_CLOSE_B);
                fgIndex = 0xDE;
            }
            fgIndex += ((3 - params) << 5);
            (&g_Tilemap.fg[fgIndex])[0] = door_tiles[7 - params][0];
            (&g_Tilemap.fg[fgIndex])[1] = door_tiles[7 - params][1];
            self->velocityY = 0;
            self->step++;
        }
        break;
    case 4:
        if (!D_us_80180810) {
            self->step++;
        }
        break;
    case 5:
        fgIndex = 0xC0;
        params = self->params & 0xFF;
        if (self->params & 0x100) {
            fgIndex = 0xDE;
        }

        fgIndex += ((3 - params) << 5);
        (&g_Tilemap.fg[fgIndex])[0] = door_tiles[3 - params][0];
        (&g_Tilemap.fg[fgIndex])[1] = door_tiles[3 - params][1];
        self->step++;
    case 7:
        break;
    case 6:
        if (self->params & 0x100) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        MoveEntity();
        posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        if (posX < -0x20 || posX > 0x220) {
            self->step++;
        }
        break;
    }
}
