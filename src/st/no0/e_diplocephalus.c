// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/e_diplocephalus", func_us_801CF4A8);

extern s16 D_us_80181D54[]; // sensors_ground
extern u8 D_us_80181D83[];  // anim frames

void EntityDiplocephalusFoot(Entity* self) {
    Entity* currentEntity;
    u16 x;

    switch (self->step) {
    case 0:
        currentEntity = g_CurrentEntity;
        g_CurrentEntity = self;
        InitializeEntity(g_EInitDiplocephalusFoot);
        g_CurrentEntity->hitboxOffY = 4;
        g_CurrentEntity->animCurFrame =
            D_us_80181D83[g_CurrentEntity->ext.diplocephalus.unk9E];
        g_CurrentEntity = currentEntity;
        // fallthrough
    case 1:
        currentEntity = g_CurrentEntity;
        g_CurrentEntity = self;
        if (UnkCollisionFunc3(D_us_80181D54) & 1) {
            g_CurrentEntity->step++;
        }
        g_CurrentEntity = currentEntity;
        break;
    case 2:
        if (g_CurrentEntity->step >= 4) {
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->velocityY = -0x2AAA4;
            self->ext.diplocephalus.unk9F = 0;
            self->ext.diplocephalus.velocityY = -0x71DU;
            self->animCurFrame--;
            self->step = 4;
        }
        break;
    case 3:
        if (self->facingLeft) {
            self->velocityX = -0x22AAA;
        } else {
            self->velocityX = 0x22AAA;
        }
        self->velocityY = -0x7FFFE;
        self->ext.diplocephalus.unk9F = 0;
        self->ext.diplocephalus.velocityY = 0x26AAA;
        self->animCurFrame--;
        self->step = 4;
        break;
    case 4:
        self->velocityY += self->ext.diplocephalus.velocityY;
        self->ext.diplocephalus.unk9F++;
        currentEntity = g_CurrentEntity;
        g_CurrentEntity = self;

        // Walk forward, spawning dust cloud when stepping
        if (UnkCollisionFunc3(&D_us_80181D54) & 1) {
            PlaySfxPositional(0x779);
            self->velocityX = 0;
            self->velocityY = 0;
            self->animCurFrame++;
            if (self->ext.diplocephalus.unk9E < 3) {
                if (g_CurrentEntity->facingLeft ^
                    (self->ext.diplocephalus.parent->step % 2)) {
                    EntityGreyPuffSpawner(self, 6, 3, 6, 16, 0, -4);
                } else {
                    EntityGreyPuffSpawner(self, 6, 3, -6, 16, 0, 4);
                }
            }
            self->step++;
        }
        g_CurrentEntity = currentEntity;
        break;
    case 5:
        self->ext.diplocephalus.unk9F++;
        break;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/e_diplocephalus", func_us_801CF910);

// Main entity?
INCLUDE_ASM("st/no0/nonmatchings/e_diplocephalus", func_us_801CFBE8);

// Likely the torso entity that player can stand on top of
void func_us_801D0718(Entity* self) {
    Entity* parent;
    Entity* player;
    s32 step;
    s32 collision;
    s32 posX;
    s32 posY;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->ext.diplocephalus.posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        self->ext.diplocephalus.posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    }

    player = &PLAYER;
    parent = self->ext.diplocephalus.parent;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    posX =
        self->posX.i.hi + g_Tilemap.scrollX.i.hi - self->ext.diplocephalus.posX;
    posY =
        self->posY.i.hi + g_Tilemap.scrollY.i.hi - self->ext.diplocephalus.posY;
    collision = 0;
    step = parent->step;
    if (step < 13) {
        collision = GetPlayerCollisionWith(self, 8, 18, 4) & 0xFF;
        if (collision) {
            player->posX.i.hi += posX;
            player->posY.i.hi += 2;
            D_80097488.x.i.hi += posX;
            D_80097488.y.i.hi += 2;
        }
    }
    self->ext.diplocephalus.posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    self->ext.diplocephalus.posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    // Parent is func_us_801CFBE8 (self - 1)
    if (parent->entityId != 0x21) {
        DestroyEntity(self);
    }
}

// Death explosion...
void func_us_801D0898(Entity* self, s32 count) {
    Entity* newEntity;
    s32 i;
    s8 randomX;
    s8 randomY;

    for (i = 0; i < count; i++) {
        randomX = (Random() & 0x3F) - 0x20;
        randomY = (Random() & 0x1F) - 0xF;
        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 1;
            newEntity->posX.i.hi += randomX;
            newEntity->posY.i.hi += randomY;
            newEntity->zPriority = self->zPriority + 2;
        }
    }
}
