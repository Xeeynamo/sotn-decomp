// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

typedef struct {
    s16 yMax;
    s16 yMin;
    s16 spawnDelay;
    s16 spawnCount;
    s16 yellowChance; // chance out of 15 that medusa head will be yellow
    s16 zPriority;
} MedusaHeadSpawnerParams;

typedef struct {
    s32 velocityX;
    s16 posX;
    s16 facingLeft;
} MedusaHeadInitParams;

// clang-format off
static MedusaHeadSpawnerParams medusaHeadSpawnerParams[] = {
    {.yMax = 0x20, .yMin = 0x200, .spawnDelay = 0xC0, .spawnCount = 0x06, .yellowChance = 0x00, .zPriority = 0x00},
    {.yMax = 0x00, .yMin = 0x1B0, .spawnDelay = 0xC0, .spawnCount = 0x04, .yellowChance = 0x02, .zPriority = 0x00},
    {.yMax = 0x00, .yMin = 0xF00, .spawnDelay = 0x80, .spawnCount = 0x08, .yellowChance = 0x08, .zPriority = 0x00},
    {.yMax = 0x00, .yMin = 0xF00, .spawnDelay = 0x50, .spawnCount = 0x20, .yellowChance = 0x10, .zPriority = 0x00},
    {.yMax = 0x00, .yMin = 0xF00, .spawnDelay = 0x30, .spawnCount = 0x20, .yellowChance = 0x08, .zPriority = 0xB0},
    {.yMax = 0x00, .yMin = 0x1E0, .spawnDelay = 0x80, .spawnCount = 0x10, .yellowChance = 0x08, .zPriority = 0x00},
    {.yMax = 0x00, .yMin = 0xF00, .spawnDelay = 0x50, .spawnCount = 0x10, .yellowChance = 0x10, .zPriority = 0x00},
    {.yMax = 0x00, .yMin = 0xF00, .spawnDelay = 0x50, .spawnCount = 0x10, .yellowChance = 0x10, .zPriority = 0x00},
};
// clang-format on

static u8 anim_medusa_head[] = {8, 1, 8, 2, 0, 0, 0, 0};

static MedusaHeadInitParams medusaHeadInitParams[] = {
    {.velocityX = FIX(1.125), .posX = 0xFFF0, .facingLeft = 1},
    {.velocityX = FIX(-1.125), .posX = 0x0110, .facingLeft = 0},
};

extern void EntityMedusaHeadYellow(Entity* self);
extern void EntityMedusaHeadBlue(Entity* self);

void EntityMedusaHeadSpawner(Entity* self) {
    Entity* tempEntity;

    u8 index = self->params;
    MedusaHeadSpawnerParams* params = medusaHeadSpawnerParams;
    params += index;
    FntPrint("y:%02x\n", g_Tilemap.scrollY.i.hi);
    if (self->flags & FLAG_DEAD) {
        DestroyEntity(self);
        return;
    }
    if (!self->step) {
        InitializeEntity(D_us_8018095C);
        self->flags &= ~FLAG_UNK_2000;
    }
    if ((g_Tilemap.scrollY.i.hi >= params->yMax) &&
        (g_Tilemap.scrollY.i.hi <= params->yMin) &&
        (LOH(PLAYER.posY.i.hi) >= 0x20) && (PLAYER.posY.i.hi < 0xC1)) {
        if (self->ext.medusaHead.timer) {
            self->ext.medusaHead.timer--;
            return;
        }
        tempEntity = AllocEntity(
            &g_Entities[128], &g_Entities[128 + params->spawnCount]);
        if (tempEntity != NULL) {
            DestroyEntity(tempEntity);
            if ((rand() & 0xF) < params->yellowChance) {
                tempEntity->entityId = E_MEDUSA_HEAD_YELLOW;
                tempEntity->pfnUpdate = EntityMedusaHeadYellow;
            } else {
                tempEntity->entityId = E_MEDUSA_HEAD_BLUE;
                tempEntity->pfnUpdate = EntityMedusaHeadBlue;
            }
            tempEntity->zPriority = params->zPriority;
            self->ext.medusaHead.timer = params->spawnDelay;
            return;
        }
        self->ext.medusaHead.timer++;
    }
}

void EntityMedusaHeadYellow(Entity* self) {
    self->params = 1;
    EntityMedusaHeadBlue(self);
}

// Medusa Head
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
        InitializeEntity(g_EInitMedussaHeadYellow);
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
