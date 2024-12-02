// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

// func_us_801CF4A8
extern s32 D_us_80181CC4[];    // velocityX
extern s32 D_us_80181CE8[][8]; // velocityY
extern s16 D_us_80181D54[];    // sensors_ground

// func_us_801CF910
extern s32 D_us_80181CD4[]; // velocityX
extern s16 D_us_80181D64[]; // sensors_ground
extern u8 D_us_80181DAC[];  // anims
extern u8 D_us_80181DB4[];  // anims

// Foot
extern u8 D_us_80181D83[]; // anim frames

// Some sort of death entity
// Perhaps the parts that go flying on death
void func_us_801CF4A8(Entity* self) {
    Entity* newEntity;

    if (self->ext.diplocephalus.parent->entityId != 0x21) {
        EntityExplosionSpawn(0, 0);
        return;
    }

    switch (self->step) {
    case 6:
        self->drawFlags = DRAW_COLORS;
        self->hitboxState = 0;
        self->velocityY =
            D_us_80181CE8[self->params][self->ext.diplocephalus.unk9E - 1] -
            FIX(8);
        self->ext.diplocephalus.velocityY = self->velocityY;
        self->step++;
        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_UNK_ID_13, self, newEntity);
            newEntity->params = 2;
            newEntity->ext.diplocephalus.entity = self;
        }
        break;
    case 7:
        self->velocityX = D_us_80181CC4[self->ext.diplocephalus.unk9E];
        if (self->facingLeft ^ 1) {
            self->velocityX = -self->velocityX;
        }

        if (self->ext.diplocephalus.unk9E % 2) {
            self->rotZ += 0x100;
        } else {
            self->rotZ -= 0x100;
        }

        if (UnkCollisionFunc3(D_us_80181D54) & EFFECT_SOLID) {
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 3;
                newEntity->zPriority = self->zPriority + 9;
            }
            g_api.func_80102CD8(1);
            DestroyEntity(self);
        }
        break;
    }
}

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

void func_us_801CF910(Entity* self) {
    Entity* entityOne;
    Entity* entityTwo;

    // func_us_801CFBE8 (self + 1)
    if (self->ext.diplocephalusUnk.parent->entityId != 0x21) {
        EntityExplosionSpawn(0, 0);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B3C);
        if (self->facingLeft) {
            self->ext.diplocephalusUnk.posY = 0x60000;
            self->ext.diplocephalusUnk.unkAC = 0x120000;
        } else {
            self->ext.diplocephalusUnk.posY = -0x60000;
            self->ext.diplocephalusUnk.unkAC = -0x120000;
        }
        // fallthrough
    case 1:
        entityOne = self->ext.diplocephalusUnk.unk90;
        entityTwo = self->ext.diplocephalusUnk.parent;
        self->posX.val =
            ((entityTwo->posX.val + self->ext.diplocephalusUnk.unkAC +
              entityOne->posX.val) /
             2) -
            self->ext.diplocephalusUnk.posY;
        if (!(self->ext.diplocephalusUnk.unk9E % 2)) {
            self->posX.val -= self->ext.diplocephalusUnk.unkAC -
                              self->ext.diplocephalusUnk.posY;
        }

        self->posY.val =
            ((entityTwo->posY.val + 0xC0000 + entityOne->posY.val) / 2) -
            0x80000;
        if (self->ext.diplocephalusUnk.unk9E % 2) {
            self->posY.val -= FIX(4.0);
        }

        if (self->ext.diplocephalusUnk.unk9E < 3) {
            AnimateEntity(D_us_80181DAC, self);
        } else {
            AnimateEntity(D_us_80181DB4, self);
        }

        break;
    case 6:
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->hitboxState = 0;
        self->velocityY =
            D_us_80181CE8[self->params][self->ext.diplocephalusUnk.unk9E + 3] -
            FIX(8);
        self->ext.diplocephalusUnk.velocityY = self->velocityY;
        self->step++;

        entityOne = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entityOne != NULL) {
            DestroyEntity(entityOne);
            CreateEntityFromEntity(E_UNK_ID_13, self, entityOne);
            entityOne->params = 2;
            entityOne->ext.diplocephalusUnk.entity = self;
        }
        break;
    case 7:
        self->velocityX = D_us_80181CD4[self->ext.diplocephalusUnk.unk9E];
        if (self->facingLeft ^ 1) {
            self->velocityX = -self->velocityX;
        }

        if (self->ext.diplocephalusUnk.unk9E % 2) {
            self->rotZ += 0x100;
        } else {
            self->rotZ -= 0x100;
        }

        if (UnkCollisionFunc3(&D_us_80181D64) & 1) {
            self->ext.diplocephalusUnk.velocityY /= 2;
            if (self->ext.diplocephalusUnk.velocityY == 0) {
                PlaySfxPositional(SFX_EXPLODE_B);
                EntityExplosionSpawn(0, 0);
                return;
            }
            self->velocityY = self->ext.diplocephalusUnk.velocityY;
        }
        break;
    }
}

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

// Death explosion
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
