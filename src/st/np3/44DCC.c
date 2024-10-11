// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"
#include "../e_merman2.h"

// ID 0x35
void EntityHighWaterSplash(Entity* self) {
    s8 temp; // probably !FAKE

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = ANIMSET_DRA(2);
        self->velocityY = FIX(-5);
        self->palette = 0x8162;
        self->drawMode = DRAW_TPAGE;
        self->palette = 0x8018;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->unk6C = 0xA0;
        self->rotX = 0x100;
        self->rotY = 0x1A0;
        self->drawFlags |= FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        self->ext.mermanWaterSplash.unk85 = 0x11;
        self->ext.mermanWaterSplash.unk84 = self->params;
        self->drawFlags |= FLAG_DRAW_UNK8;
        break;

    case 1:
        temp = self->ext.mermanWaterSplash.unk84 - 1;
        self->ext.mermanWaterSplash.unk84--;
        self->ext.mermanWaterSplash.unk85--;
        if (!(temp & 0xFF)) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_801822C0, self);
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotX += 6;
        self->rotY -= 4;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        if (!--self->ext.mermanWaterSplash.unk85) {
            self->velocityY = 0;
            self->step++;
        }
        break;

    case 3:
        if (AnimateEntity(D_801822C0, self) == 0) {
            MoveEntity();
            self->velocityY += FIX(0.25);
            self->rotX += 6;
            self->rotY -= 4;
        }
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityDeadMerman(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitWaterObject);
        self->animCurFrame = 13;
        self->ext.merman.timer = 0x20;
        self->hitboxState = 0;
        self->velocityY = FIX(0.0625);
        self->palette = self->params + 0xE;
        self->unk6C = 0x80;
        self->drawFlags |= FLAG_DRAW_UNK8;
        self->flags |= FLAG_UNK_2000;
        return;
    }
    MoveEntity();
    self->velocityY += FIX(0.0625);
    self->unk6C += 0xFE;
    if (--self->ext.merman.timer == 0) {
        DestroyEntity(self);
    }
}

void EntityMermanSpawner(Entity* self) {
    Entity* newEntity;
    u16 temp_s0_2;
    u16 temp_s0;
    s32 temp2;
    s16 temp;

    if (self->step == 0) {
        InitializeEntity(D_80180A60);
        self->flags |= FLAG_UNK_2000;
    }

    if (!(g_Timer & 0x3F)) {
        Entity* player = &PLAYER;
        temp = g_Tilemap.scrollY.i.hi + player->posY.i.hi;
        if (temp >= 256) {
            temp_s0 = g_Tilemap.scrollX.i.hi + player->posX.i.hi;
            temp_s0_2 = 128;
            temp_s0_2 = temp_s0 - temp_s0_2 + Random();
            temp_s0 = temp_s0_2 - 64;
            if (temp_s0 <= 0x280) {
                temp2 = 496;
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[170]);
                if (newEntity != 0) {
                    if (Random() & 1) {
                        CreateEntityFromCurrentEntity(
                            E_MERMAN_SPAWNER_32, newEntity);
                        newEntity->params = Random() & 1;
                    } else {
                        CreateEntityFromCurrentEntity(
                            E_MERMAN_SPAWNER_39, newEntity);
                    }
                    newEntity->posX.i.hi = temp_s0_2 - g_Tilemap.scrollX.i.hi;
                    newEntity->posY.i.hi = temp2 - g_Tilemap.scrollY.i.hi;
                }
            }
        }
    }
}
