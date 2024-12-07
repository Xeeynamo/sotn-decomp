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

// Main entity
extern s16 D_us_80181D28[]; // posX array?
extern u32 D_us_80181D30[]; // collider offsets
extern u32 D_us_80181D3C[]; // collider offsets
extern u32 D_us_80181D48[]; // collider offsets
extern s16 D_us_80181D74[]; // sensors_ground
extern u8 D_us_80181D88[];  // anim
extern u8 D_us_80181DA0[];  // anim

// Foot
extern u8 D_us_80181D83[]; // anim frames

// Some sort of death entity
// Perhaps the parts that go flying on death
void func_us_801CF4A8(Entity* self) {
    Entity* newEntity;

    if (self->ext.diplocephalus.parent->entityId != E_DIPLOCEPHALUS) {
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
        if (UnkCollisionFunc3(D_us_80181D54) & 1) {
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
    if (self->ext.diplocephalusUnk.parent->entityId != E_DIPLOCEPHALUS) {
        EntityExplosionSpawn(0, 0);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B3C);
        if (self->facingLeft) {
            self->ext.diplocephalusUnk.unkA8 = FIX(6);
            self->ext.diplocephalusUnk.unkAC = FIX(18);
        } else {
            self->ext.diplocephalusUnk.unkA8 = FIX(-6);
            self->ext.diplocephalusUnk.unkAC = FIX(-18);
        }
        // fallthrough
    case 1:
        entityOne = self->ext.diplocephalusUnk.unk90;
        entityTwo = self->ext.diplocephalusUnk.parent;
        self->posX.val =
            ((entityTwo->posX.val + self->ext.diplocephalusUnk.unkAC +
              entityOne->posX.val) /
             2) -
            self->ext.diplocephalusUnk.unkA8;
        if (!(self->ext.diplocephalusUnk.unk9E % 2)) {
            self->posX.val -= self->ext.diplocephalusUnk.unkAC -
                              self->ext.diplocephalusUnk.unkA8;
        }

        self->posY.val =
            ((entityTwo->posY.val + FIX(12) + entityOne->posY.val) / 2) -
            FIX(8);
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

        if (UnkCollisionFunc3(D_us_80181D64) & 1) {
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

void EntityDiplocephalus(Entity* self) {
    Entity* entityRef;
    s32 i;
    u8 random;

    self->hitParams |= self->ext.diplocephalus.hitParams;
    self->ext.diplocephalus.hitParams2 = self->hitParams;
    if ((self->flags & FLAG_DEAD) && self->step < 11) {
        self->step = 11;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDiplocephalus);
        // fallthrough

    case 1:
        self->step_s = 0;
        self->ext.diplocephalus.unk9C = 0;
        self->ext.diplocephalus.unk9E = 0;
        self->facingLeft = GetSideToPlayer() & 1;
        self->unk60 = self + 1;
        entityRef = self;

        for (i = 0; i < 4; i++) {
            DestroyEntity(++entityRef);
            CreateEntityFromCurrentEntity(E_ID_22, entityRef);
            if (i < 2) {
                entityRef->zPriority = self->zPriority + 8;
            } else {
                entityRef->zPriority = self->zPriority - 8;
            }
            entityRef->ext.diplocephalus.unk9D = 0;
            entityRef->facingLeft = self->facingLeft ^ 1;
            entityRef->ext.diplocephalus.parent = self;
            entityRef->ext.diplocephalus.unk9E = i + 1;
            entityRef->unk60 = entityRef + 1;
        }

        self->ext.diplocephalus.entity8C = entityRef;
        self->ext.diplocephalus.entity88 = entityRef - 1;
        self->ext.diplocephalus.entity84 = entityRef - 2;
        self->ext.diplocephalus.entity = entityRef - 3;

        for (i = 0; i < 4; i++) {
            entityRef++;
            CreateEntityFromCurrentEntity(E_ID_23, entityRef);
            if (i < 2) {
                entityRef->zPriority = self->zPriority + 4;
            } else {
                entityRef->zPriority = self->zPriority - 4;
            }
            entityRef->facingLeft = self->facingLeft ^ 1;
            entityRef->ext.diplocephalus.parent = self;
            entityRef->ext.diplocephalus.entity90 = entityRef - 4;
            entityRef->ext.diplocephalus.parent = self;
            entityRef->ext.diplocephalus.unk9E = i + 1;

            if (i % 2) {
                entityRef->ext.diplocephalus.unk9F = self->facingLeft ^ 1;
            } else {
                entityRef->ext.diplocephalus.unk9F = self->facingLeft;
            }
            (entityRef - 4)->ext.diplocephalus.entity90 = entityRef;
            entityRef->unk60 = entityRef + 1;
        }

        entityRef++;
        CreateEntityFromCurrentEntity(E_DIPLOCEPHALUS_TAIL, entityRef);
        entityRef->zPriority = self->zPriority;
        entityRef->facingLeft = self->facingLeft ^ 1;
        entityRef->ext.diplocephalus.parent = self;
        self->ext.diplocephalus.entityA0 = entityRef;
        entityRef->unk60 = entityRef + 1;

        entityRef += 9;
        DestroyEntity(entityRef);
        CreateEntityFromEntity(E_DIPLOCEPHALUS_TORSO, self, entityRef);
        entityRef->ext.diplocephalus.parent = self;
        self->ext.diplocephalus.parent = entityRef;

        entityRef = self;
        for (i = 0; i < 4; i++) {
            entityRef++;
            entityRef->posX.val = self->posX.val;
            if ((i + self->facingLeft) % 2) {
                entityRef->posX.val -= FIX(18);
            } else {
                entityRef->posX.val += FIX(18);
            }

            if (self->facingLeft ^ (i >> 1)) {
                entityRef->posX.val += FIX(6);
                entityRef->posX.val += FIX(3);
            } else {
                entityRef->posX.val -= FIX(6);
                entityRef->posX.val -= FIX(3);
            }
        }

        entityRef = self;
        for (i = 0; i < 4; i++) {
            entityRef++;
            entityRef->posY.val = self->posY.val + FIX(14);
            EntityDiplocephalusFoot(entityRef);
        }
        self->step++;
        break;

    case 2:
        entityRef = self + 1;
        self->velocityX = entityRef->velocityX;
        self->velocityY = entityRef->velocityY;
        MoveEntity();
        if (((entityRef->step < 2) ^ 1) & (((entityRef + 1)->step < 2) ^ 1) &
            (((entityRef + 2)->step < 2) ^ 1) &
            (((entityRef + 3)->step < 2) ^ 1)) {
            self->velocityY = 0;
            self->step++;
        }

        entityRef = self;
        for (i = 0; i < 4; i++) {
            entityRef++;
            EntityDiplocephalusFoot(entityRef);
        }
        break;

    case 3:
#ifdef VERSION_PSP
        if (self->ext.diplocephalus.unk9F++ == 0) {
#else
        if (++self->ext.diplocephalus.unk9F == 1) {
#endif
            self->velocityY = 0x7ED0;
            self->ext.diplocephalus.unk9D++;
        } else {
            self->velocityY -= FIX(0.03125);
        }

        if (self->ext.diplocephalus.unk9F == 32) {
            self->ext.diplocephalus.unk9F = 0;
            if (self->ext.diplocephalus.unk9D >= 2) {
                self->velocityY = 0;
                self->step_s ^= 1;
                self->ext.diplocephalus.entityA4 =
                    self + 4 - (self->step_s << 1);
                self->step = 4;
                if (self->ext.diplocephalus.unk9C ||
                    (CheckColliderOffsets(D_us_80181D30, self->facingLeft ^ 1) &
                     0xFF) ^
                        1) {
                    self->step = 6;
                    self->step_s ^= 1;
                }
            } else {
                break;
            }
        }

        self->ext.diplocephalus.unk9C |= self->hitParams;
        AnimateEntity(D_us_80181D88, self);
        MoveEntity();
        if (CheckColliderOffsets(D_us_80181D48, 1) & 0xFF & 0xFF & 1) {
            self->posY.i.hi -= 1;
        }

        break;

    case 4:
        entityRef = self->ext.diplocephalus.entityA4;
        EntityDiplocephalusFoot(entityRef);
        if (entityRef->ext.diplocephalus.unk9F > 0xC) {
            EntityDiplocephalusFoot(entityRef - 1);
        }

        if (entityRef->step == 5 && (entityRef - 1)->step == 5) {
            entityRef->step = 2;
            (entityRef - 1)->step = 2;
            g_api.func_80102CD8(1);
            self->step = 3;
            if (self->ext.diplocephalus.unk9C) {
                self->step = 6;
            }
        }

        self->velocityX = (entityRef - (self->step_s * 1))->velocityX >> 1;
        if (entityRef->ext.diplocephalus.unk9F >= 24) {
            self->velocityY = 0;
        } else {
            self->velocityY = entityRef->velocityY >> 2;
        }
        self->ext.diplocephalus.unk9C |= self->hitParams;
        AnimateEntity(D_us_80181D88, self);
        MoveEntity();
        break;

    case 6:
#ifdef VERSION_PSP
        if (self->ext.diplocephalus.unk9F++ == 0) {
#else
        if (++self->ext.diplocephalus.unk9F == 1) {
#endif
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->velocityY = 0x1B200;
        } else {
            self->velocityY -= FIX(1.0);
        }

        if (self->ext.diplocephalus.unk9F == 4) {
            self->step_s ^= 1;
            self->ext.diplocephalus.entityA4 = self + ((self->step_s << 1) + 1);
            self->step = 7;
            (self + 1)->step = 3;
            (self + 2)->step = 3;
            (self + 3)->step = 3;
            (self + 4)->step = 3;
            self->ext.diplocephalus.unk9E++;
            self->ext.diplocephalus.unk9F = 0;

            if ((self->ext.diplocephalus.unk9E % 2 &&
                 (CheckColliderOffsets(D_us_80181D3C, self->facingLeft ^ 1) &
                  0xFF) ^
                     1) ||
                self->ext.diplocephalus.unk9E > 8) {
                self->step = 3;
                self->ext.diplocephalus.unk9C = 0;
                self->ext.diplocephalus.unk9E = 0;
                self->ext.diplocephalus.unk9F = 0;
                self->velocityY = 0;
                self->params = 0;
                (self + 1)->step = 2;
                (self + 2)->step = 2;
                (self + 3)->step = 2;
                (self + 4)->step = 2;
                self->ext.diplocephalus.unk9D = 0;
                self->animFrameDuration = 0;
                self->animFrameIdx = 0;
                self->step_s ^= 1;

                for (i = 0; i < 3; i++) {
                    entityRef = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entityRef != NULL) {
                        CreateEntityFromEntity(E_OLROX_DROOL, self, entityRef);
                        if (self->facingLeft) {
                            entityRef->posX.i.hi -=
                                (i * 4) + 24 + (Random() & 3);
                        } else {
                            entityRef->posX.i.hi +=
                                (i * 4) + 24 + (Random() & 3);
                        }
                        entityRef->posY.i.hi += (i * 2) + 4;
                    }
                }
            }
        }

        AnimateEntity(D_us_80181DA0, self);
        MoveEntity();
        break;

    case 7:
        entityRef = self->ext.diplocephalus.entityA4;
        EntityDiplocephalusFoot(entityRef);
        if (entityRef->ext.diplocephalus.unk9F > 2) {
            EntityDiplocephalusFoot(entityRef + 1);
        }

        if ((entityRef + 1)->step == 5 && entityRef->step == 5) {
            entityRef->step = 3;
            (entityRef + 1)->step = 3;
            self->step = 6;
        }
        self->velocityX = (entityRef + (self->step_s * 1))->velocityX >> 1;
        if (entityRef->ext.diplocephalus.unk9F >= 6) {
            self->velocityY = 0;
        } else {
            self->velocityY = entityRef->velocityY >> 3;
        }
        AnimateEntity(D_us_80181DA0, self);
        MoveEntity();
        break;

    case 11:
        self->ext.diplocephalus.entityA0->step = 8;
        self->velocityX = 0;
        self->step++;
        entityRef = self;

        for (i = 0; i < 10; i++) {
            entityRef->hitboxState = 0;
            entityRef++;
        }

        break;

    case 12:
        if (self->ext.diplocephalus.entityA0->entityId !=
                E_DIPLOCEPHALUS_TAIL &&
            UnkCollisionFunc3(D_us_80181D74) & 1) {
            g_api.func_80102CD8(1);
            self->step++;
        }
        break;

    case 13:
        random = Random() & 1;
        entityRef = self;

        for (i = 0; i < 4; i++) {
            entityRef++;
            entityRef->step = 6;
            entityRef->params = random;
            entityRef->ext.diplocephalus.entity90->step = 6;
            entityRef->ext.diplocephalus.entity90->params = random;
        }
        self->ext.diplocephalus.velocityY = 0;

        for (i = 0; i < 3; i++) {
            entityRef = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entityRef != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entityRef);
                entityRef->params = 3;
                entityRef->posX.i.hi += D_us_80181D28[i];
                entityRef->zPriority = self->zPriority + 9;
            }
        }

        g_api.func_80102CD8(1);
        PlaySfxPositional(SFX_STUTTER_EXPLODE_C);
        self->ext.diplocephalus.unk9C = 0;
        self->ext.diplocephalus.unk9D = 0;
        self->animCurFrame = 0;
        entityRef = self->ext.diplocephalus.parent;
        DestroyEntity(entityRef);
        self->step++;
        break;

    case 14:
        if (self->ext.diplocephalus.unk9C++ >= 6) {
            self->ext.diplocephalus.unk9C = 0;
            if (self->ext.diplocephalus.unk9D < 24) {
                func_us_801D0898(self, 2);
                if (!(g_Timer & 2)) {
                    entityRef = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entityRef != NULL) {
                        CreateEntityFromEntity(E_EXPLOSION, self, entityRef);
                        entityRef->params = 2;
                    }
                }
                self->ext.diplocephalus.unk9D++;
            } else {
                DestroyEntity(self);
            }
        }
        break;
    }

    if (self->step < 11 && self->step > 2) {
        self->posX.val = (self->ext.diplocephalus.entity->posX.val +
                          self->ext.diplocephalus.entity8C->posX.val) /
                         2;
    }
}

void EntityDiplocephalusTorso(Entity* self) {
    Entity* parent;
    Entity* player;
    s32 step;
    s32 collision;
    s32 posX;
    s32 posY;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->ext.diplocephalusUnk.unkA4 =
            self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        self->ext.diplocephalusUnk.unkA8 =
            self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    }

    player = &PLAYER;
    parent = self->ext.diplocephalus.parent;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi -
           self->ext.diplocephalusUnk.unkA4;
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi -
           self->ext.diplocephalusUnk.unkA8;
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
    self->ext.diplocephalusUnk.unkA4 = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    self->ext.diplocephalusUnk.unkA8 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    if (parent->entityId != E_DIPLOCEPHALUS) {
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
