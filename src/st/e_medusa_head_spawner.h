// SPDX-License-Identifier: AGPL-3.0-or-later
#include <types.h>

typedef struct {
    s16 yMax;
    s16 yMin;
    s16 spawnDelay;
    s16 spawnCount;
    s16 yellowChance; // chance out of 16 that medusa head will be yellow
    s16 zPriority;
} MedusaHeadSpawnerParams;

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

void EntityMedusaHeadYellow(Entity* self);
void EntityMedusaHeadBlue(Entity* self);

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
        InitializeEntity(g_EInitSpawner);
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
