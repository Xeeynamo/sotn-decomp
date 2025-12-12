// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

static Point16 D_us_80180FC8[] = {
    {0x00F8, 0x0170},
    {0x027C, 0x02C8},
};

void EntityGearSidewaysSmall(Entity* self) {
    Entity* player;
    s16 angle;
    s32 offsetX;
    s32 offsetY;
    s32 collision;
    s32 params; // used for params and y-offset

    switch (self->step) {
    case 0x0:
        InitializeEntity(g_EInitEnvironment);
        self->zPriority = 0x6C;
        self->animCurFrame = 0xC;
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->velocityY = FIX(0.5);
        // fallthrough

    case 0x1:

        player = &PLAYER;
        if (self->ext.gearPuzzle.collision & 4) {
            offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            params = offsetY - self->ext.gearPuzzle.offsetY;
            player->posY.i.hi += params;
            D_80097488.y.i.hi += params;
        }

        self->rotate += 64;

        MoveEntity();
        offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        params = self->params;
        if (offsetY < D_us_80180FC8[params].x) {
            self->velocityY = FIX(0.5);
        }
        if (D_us_80180FC8[params].y < offsetY) {
            self->velocityY = -FIX(0.5);
        }

        offsetX = player->posX.i.hi;
        offsetY = player->posY.i.hi + 25;
        offsetX -= self->posX.i.hi;
        offsetY -= self->posY.i.hi;

        angle = ratan2(offsetY, offsetX);
        if (angle <= 0) {
            offsetX = (14 * rcos(angle)) << 4;
            offsetY = (14 * rsin(angle)) << 4;
            self->hitboxOffX = (s16)(offsetX >> 0x10);
            self->hitboxOffY = (s16)(offsetY >> 0x10);
            collision = GetPlayerCollisionWith(self, 6, 2, 4);
            if (collision & 4) {
                angle += 64;
                offsetX = (rcos(angle) * 14 * 16) - offsetX;
                offsetY = (rsin(angle) * 14 * 16) - offsetY;

                player = &PLAYER;
                player->posX.val += offsetX;
                player->posY.val += FIX(1) + offsetY;
                D_80097488.x.val += offsetX;
                D_80097488.y.val += offsetY;
            }
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
        break;
    }
    self->ext.gearPuzzle.collision = collision;
    self->ext.gearPuzzle.offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
}
