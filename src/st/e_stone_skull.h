// Note: SKULL_SPEED is actually inverse speed! It's frames per pose.
static AnimateEntityFrame anim_hover[] = {
    {SKULL_SPEED, 1},
    {SKULL_SPEED, 2},
    {SKULL_SPEED, 3},
    {SKULL_SPEED, 4},
    {SKULL_SPEED, 5},
    {SKULL_SPEED, 6},
    {SKULL_SPEED, 7},
    {SKULL_SPEED, 8},
    {SKULL_SPEED, 9},
    {SKULL_SPEED, 10},
    {SKULL_SPEED, 11},
    {SKULL_SPEED, 12},
    {SKULL_SPEED, 13},
    {SKULL_SPEED, 14},
    {SKULL_SPEED, 15},
    {SKULL_SPEED, 16},
    POSE_LOOP(0),
};

#ifdef HITBOXES
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
#endif

extern EInit g_EInitStoneSkull;

void EntityStoneSkull(Entity* self) {
    s8* ptr;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStoneSkull);
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = STONE_SKULL_OPACITY;
        self->ext.stoneSkull.startingPosY =
            g_Tilemap.scrollY.i.hi + self->posY.i.hi;
        self->velocityY = FIX(1.0);
        /* fallthrough */
    case 1:
        AnimateEntity(anim_hover, self);
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
#include "pad2_anim_debug.h"
    }

#ifdef HITBOXES
    ptr = *hitbox_config;
    ptr += hitbox_indices[self->animCurFrame] * 4;
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
#endif

}