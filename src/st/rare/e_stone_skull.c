// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

static AnimateEntityFrame D_us_80181BE4[] = {
    {.duration = 8, .pose = 0x01},
    {.duration = 8, .pose = 0x02},
    {.duration = 8, .pose = 0x03},
    {.duration = 8, .pose = 0x04},
    {.duration = 8, .pose = 0x05},
    {.duration = 8, .pose = 0x06},
    {.duration = 8, .pose = 0x07},
    {.duration = 8, .pose = 0x08},
    {.duration = 8, .pose = 0x09},
    {.duration = 8, .pose = 0x0A},
    {.duration = 8, .pose = 0x0B},
    {.duration = 8, .pose = 0x0C},
    {.duration = 8, .pose = 0x0D},
    {.duration = 8, .pose = 0x0E},
    {.duration = 8, .pose = 0x0F},
    {.duration = 8, .pose = 0x10},
    POSE_LOOP(0),
};

// This is indexed off the animCurFrame
// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
static s8 hitbox_config[][4] = {
    {0, 0, 0, 0},    {1, 1, 7, 13},   {3, 2, 9, 11},   {-1, 1, 10, 11},
    {-1, 2, 12, 10}, {-2, 1, 12, 10}, {-2, 1, 10, 10}, {1, 2, 7, 11},
    {1, 1, 8, 13},   {3, 1, 12, 10},  {5, 1, 13, 9},   {3, 0, 13, 8},
    {2, 0, 12, 8},   {3, 1, 10, 11},  {0, 2, 7, 12},
};
static u8 hitbox_indices[] = {
    0, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 11, 12, 13, 14,
};
extern EInit g_EInitStoneSkull;

void EntityStoneSkull(Entity* self) {
    s8* ptr;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStoneSkull);
        self->drawFlags = FLAG_DRAW_OPACITY;
        self->opacity = 0xFF;
        self->ext.stoneSkull.startingPosY =
            g_Tilemap.scrollY.i.hi + self->posY.i.hi;
        self->velocityY = FIX(1.0);
        /* fallthrough */
    case 1:
        AnimateEntity(D_us_80181BE4, self);
        MoveEntity();
        posY = (self->posY.i.hi + g_Tilemap.scrollY.i.hi);
        posY = self->ext.stoneSkull.startingPosY - posY;
        if (self->velocityY > 0) {
            posY += self->params;
        } else {
            posY -= self->params;
        }

        if (posY < 0) {
            self->velocityY -= FIX(0.125);
            if (self->velocityY < FIX(-1.0)) {
                self->velocityY = FIX(-1.0);
            }
        } else {
            self->velocityY += FIX(0.125);
            if (self->velocityY > FIX(1.0)) {
                self->velocityY = FIX(1.0);
            }
        }

        break;
    case 255:
#include "../pad2_anim_debug.h"
    }

    ptr = *hitbox_config;
    ptr += hitbox_indices[self->animCurFrame] * 4;
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
}
