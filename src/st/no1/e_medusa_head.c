// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

typedef struct {
    s16 yMax;
    s16 yMin;
    s16 timer;
    s16 count;
    s16 chance;
    s16 zPriority;
} MedusaHeadSpawnerParams;

typedef struct {
    s32 velocityX;
    s16 posX;
    s16 facingLeft;
} MedusaHeadParams;

extern u16 D_us_8018095C[];
extern u16 D_us_80180B48[];
extern u16 D_us_80180B54[];
extern MedusaHeadSpawnerParams D_us_801833D0[];
extern u8 D_us_80183430[];
extern MedusaHeadParams D_us_80183438[];

extern void func_us_801D5808(Entity* self);
extern void func_us_801D582C(Entity* self);

// Medusa Head spawner
void func_us_801D563C(Entity* self) {
    Entity* tempEntity;

    u8 index = self->params;
    MedusaHeadSpawnerParams* params = D_us_801833D0;
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
        tempEntity =
            AllocEntity(&g_Entities[128], &g_Entities[128 + params->count]);
        if (tempEntity != NULL) {
            DestroyEntity(tempEntity);
            if ((rand() & 0xF) < params->chance) {
                tempEntity->entityId = E_ID_5B;
                tempEntity->pfnUpdate = func_us_801D5808;
            } else {
                tempEntity->entityId = E_ID_5A;
                tempEntity->pfnUpdate = func_us_801D582C;
            }
            tempEntity->zPriority = params->zPriority;
            self->ext.medusaHead.timer = params->timer;
            return;
        }
        self->ext.medusaHead.timer++;
    }
}

// Medusa Head helper
void func_us_801D5808(Entity* self) {
    self->params = 1;
    func_us_801D582C(self);
}

// Medusa Head
void func_us_801D582C(Entity* self) {
    s32 dir;
    Entity* player = &PLAYER;

    if (self->flags & FLAG_DEAD) {
        EntityExplosionSpawn(0, 0);
        return;
    }
    if (self->step) {
        AnimateEntity(D_us_80183430, self);
        if (self->velocityY > 0) {
            self->animCurFrame += 2;
        }
        self->velocityY += self->ext.medusaHead.accelY;
        dir = self->velocityY;
        if (dir < 0) {
            dir = -dir;
        }
        if (dir >= FIX(2.5)) {
            self->ext.medusaHead.accelY = -self->ext.medusaHead.accelY;
        }
        MoveEntity();
        return;
    }

    if (!self->params) {
        InitializeEntity(D_us_80180B48);
    } else {
        InitializeEntity(D_us_80180B54);
    }

    self->posY.i.hi = player->posY.i.hi - 0;
    dir = 0;
    if (player->posX.i.hi < 0x50) {
        dir = 1;
    } else if (player->posX.i.hi < 0xB1) {
        if ((rand() & 3) == 0) {
            dir = player->facingLeft;
        } else {
            dir = ((player->facingLeft + 1) & 1);
        }
    }
    self->posX.i.hi = D_us_80183438[dir].posX;
    self->velocityX = D_us_80183438[dir].velocityX;
    self->facingLeft = D_us_80183438[dir].facingLeft;
    self->velocityY = FIX(2.5) - ((Random() & 0xF) * FIX(2.5) >> 3);
    if (self->velocityY > 0) {
        self->ext.medusaHead.accelY = FIX(-5.0 / 32);
    } else {
        self->ext.medusaHead.accelY = FIX(5.0 / 32);
    }
}
