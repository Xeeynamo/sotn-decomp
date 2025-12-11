// SPDX-License-Identifier: AGPL-3.0-or-later
#include <types.h>

void EntityMedusaHeadBlue(Entity* self);

void EntityMedusaHeadYellow(Entity* self) {
    self->params = 1;
    EntityMedusaHeadBlue(self);
}

static u8 anim_medusa_head[] = {8, 1, 8, 2, 0, 0};

typedef struct {
    s32 velocityX;
    s16 posX;
    s16 facingLeft;
} MedusaHeadInitParams;

static MedusaHeadInitParams medusaHeadInitParams[] = {
    {.velocityX = FIX(1.125), .posX = -16, .facingLeft = 1},
    {.velocityX = FIX(-1.125), .posX = 272, .facingLeft = 0},
};

extern EInit g_EInitMedusaHeadBlue;
extern EInit g_EInitMedusaHeadYellow;

void EntityMedusaHeadBlue(Entity* self) {
    s32 side;
    Entity* player = &PLAYER;

    if (self->flags & FLAG_DEAD) {
        EntityExplosionSpawn(0, 0);
        return;
    }
    if (self->step) {
        AnimateEntity(anim_medusa_head, self);
        if (self->velocityY > 0) {
            self->animCurFrame += 2;
        }
        self->velocityY += self->ext.medusaHead.accelY;
        side = self->velocityY;
        if (side < 0) {
            side = -side;
        }
        if (side >= FIX(2.5)) {
            self->ext.medusaHead.accelY = -self->ext.medusaHead.accelY;
        }
        MoveEntity();
        return;
    }

    if (!self->params) {
        InitializeEntity(g_EInitMedusaHeadBlue);
    } else {
        InitializeEntity(g_EInitMedusaHeadYellow);
    }

    self->posY.i.hi = player->posY.i.hi - 0;
    side = 0;
    if (player->posX.i.hi < 0x50) {
        side = 1;
    } else if (player->posX.i.hi < 0xB1) {
        if ((rand() & 3) == 0) {
            side = player->facingLeft;
        } else {
            side = ((player->facingLeft + 1) & 1);
        }
    }
    self->posX.i.hi = medusaHeadInitParams[side].posX;
    self->velocityX = medusaHeadInitParams[side].velocityX;
    self->facingLeft = medusaHeadInitParams[side].facingLeft;
    self->velocityY = FIX(2.5) - ((Random() & 0xF) * FIX(2.5) >> 3);
    if (self->velocityY > 0) {
        self->ext.medusaHead.accelY = FIX(-5.0 / 32);
    } else {
        self->ext.medusaHead.accelY = FIX(5.0 / 32);
    }
}
