// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

static s32 feetVelX[] = {FIX(2), FIX(-2), FIX(0.5), FIX(-0.5)};
static s32 legVelX[] = {FIX(1.25), FIX(-1.25), FIX(0.125), FIX(-0.125)};
static s32 legVelY[][8] = {
    {FIX(2.5), FIX(1.5), FIX(0.8125), FIX(1.25), FIX(1.25), FIX(2), FIX(1),
     FIX(0.5)},
    {FIX(1.25), FIX(1.9375), FIX(1), FIX(0.625), FIX(1.5), FIX(1.125),
     FIX(0.25), FIX(1.125)},
};

static s16 D_us_80181D28[] = {-16, 0, 16};

static s16 D_us_80181D30[] = {64, 16, 64, 32, 255};
static s16 D_us_80181D3C[] = {-72, 16, -72, 36, 255};
static s16 D_us_80181D48[] = {0, 24, 0, 20, 255};

static s16 D_us_80181D54[] = {0, 16, 0, 4, 8, -4, -16, 0};
static s16 D_us_80181D64[] = {0, 8, 0, 4, 8, -4, -16, 0};
static s16 D_us_80181D74[] = {0, 10, 0, 4, 8, -4, -16, 0};

static u8 D_us_80181D84[] = {12, 14, 16, 18};

static u8 anim0[] = {6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 6,
                     6, 6, 5, 6, 4, 6, 3, 6, 2, 0, 0};
static u8 anim1[] = {4, 1, 4, 2, 2, 3, 4, 2, 0, 0};
static u8 anim2[] = {6, 7, 6, 8, 0, 0};
static u8 anim3[] = {6, 9, 6, 10, 0, 0};

u8 CheckColliderOffsets(s16* arg0, s32 facing);
void func_us_801D0898(Entity* self, s32 count);

void EntityDiplocephalusFoot(Entity* self) {
    Entity* newEntity;

    if (self->ext.diploBody.diplo->entityId != E_DIPLOCEPHALUS) {
        EntityExplosionSpawn(0, 0);
        return;
    }

    switch (self->step) {
    case 6:
        self->drawFlags = DRAW_COLORS;
        self->hitboxState = 0;
        self->velocityY =
            legVelY[self->params][self->ext.diploBody.unk9E - 1] - FIX(8);
        self->ext.diploBody.velocityY = self->velocityY;
        self->step++;
        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_ID_13, self, newEntity);
            newEntity->params = 2;
            newEntity->ext.ent13.parent = self;
        }
        break;

    case 7:
        self->velocityX = feetVelX[self->ext.diploBody.unk9E - 1];
        if (self->facingLeft ^ 1) {
            self->velocityX = -self->velocityX;
        }

        if (self->ext.diploBody.unk9E % 2) {
            self->rotate += ROT(22.5);
        } else {
            self->rotate -= ROT(22.5);
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

static void UpdateFoot(Entity* self) {
    Entity* currentEntity;
    u16 x;

    switch (self->step) {
    case 0:
        currentEntity = g_CurrentEntity;
        g_CurrentEntity = self;
        InitializeEntity(g_EInitDiplocephalusFoot);
        g_CurrentEntity->hitboxOffY = 4;
        g_CurrentEntity->animCurFrame =
            D_us_80181D84[g_CurrentEntity->ext.diploBody.unk9E - 1];
        g_CurrentEntity = currentEntity;
        /* fallthrough */
    case 1:
        currentEntity = g_CurrentEntity;
        g_CurrentEntity = self;
        if (UnkCollisionFunc3(D_us_80181D54) & EFFECT_SOLID) {
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
            self->ext.diploBody.unk9F = 0;
            self->ext.diploBody.velocityY = -0x71D;
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
        self->ext.diploBody.unk9F = 0;
        self->ext.diploBody.velocityY = 0x26AAA;
        self->animCurFrame--;
        self->step = 4;
        break;

    case 4:
        self->velocityY += (s32)self->ext.diploBody.velocityY;
        self->ext.diploBody.unk9F++;
        currentEntity = g_CurrentEntity;
        g_CurrentEntity = self;

        // Walk forward, spawning dust cloud when stepping
        if (UnkCollisionFunc3(D_us_80181D54) & EFFECT_SOLID) {
            PlaySfxPositional(SFX_DIPLOCEPHALUS_STOMP);
            self->velocityX = 0;
            self->velocityY = 0;
            self->animCurFrame++;
            if (self->ext.diploBody.unk9E < 3) {
                if (g_CurrentEntity->facingLeft ^
                    (self->ext.diploBody.diplo->step % 2)) {
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
        self->ext.diploBody.unk9F++;
        break;
    }
}

void EntityDiplocephalusLeg(Entity* self) {
    Entity* tempEntity;
    Entity* diplo;

    if (self->ext.diploBody.diplo->entityId != E_DIPLOCEPHALUS) {
        EntityExplosionSpawn(0, 0);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B3C);
        if (self->facingLeft) {
            self->ext.diploBody.unkA8 = FIX(6);
            self->ext.diploBody.unkAC = FIX(18);
        } else {
            self->ext.diploBody.unkA8 = FIX(-6);
            self->ext.diploBody.unkAC = FIX(-18);
        }
        /* fallthrough */
    case 1:
        tempEntity = self->ext.diploBody.unk90;
        diplo = self->ext.diploBody.diplo;
        self->posX.val = (((s32)diplo->posX.val + self->ext.diploBody.unkAC +
                           tempEntity->posX.val) /
                          2) -
                         self->ext.diploBody.unkA8;
        if ((self->ext.diploBody.unk9E % 2) == 0) {
            self->posX.val -=
                self->ext.diploBody.unkAC - self->ext.diploBody.unkA8;
        }

        self->posY.val =
            ((diplo->posY.val + FIX(12) + tempEntity->posY.val) / 2) - FIX(8);
        if (self->ext.diploBody.unk9E % 2) {
            self->posY.val -= FIX(4.0);
        }

        if (self->ext.diploBody.unk9E < 3) {
            AnimateEntity(anim2, self);
        } else {
            AnimateEntity(anim3, self);
        }
        break;

    case 6:
        self->drawFlags = ENTITY_ROTATE;
        self->hitboxState = 0;
        self->velocityY =
            legVelY[self->params][self->ext.diploBody.unk9E + 3] - FIX(8);
        self->ext.diploBody.velocityY = self->velocityY;
        self->step++;

        tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (tempEntity != NULL) {
            DestroyEntity(tempEntity);
            CreateEntityFromEntity(E_ID_13, self, tempEntity);
            tempEntity->params = 2;
            tempEntity->ext.ent13.parent = self;
        }
        break;

    case 7:
        self->velocityX = legVelX[self->ext.diploBody.unk9E - 1];
        if (self->facingLeft ^ 1) {
            self->velocityX = -self->velocityX;
        }

        if (self->ext.diploBody.unk9E % 2) {
            self->rotate += ROT(22.5);
        } else {
            self->rotate -= ROT(22.5);
        }

        if (UnkCollisionFunc3(D_us_80181D64) & EFFECT_SOLID) {
            self->ext.diploBody.velocityY /= 2;
            if (self->ext.diploBody.velocityY == 0) {
                PlaySfxPositional(SFX_EXPLODE_B);
                EntityExplosionSpawn(0, 0);
            } else {
                self->velocityY = self->ext.diploBody.velocityY;
            }
        }
        break;
    }
}

void EntityDiplocephalus(Entity* self) {
    Entity* entityRef;
    s32 i;
    u8 var_s2;

    self->hitParams |= self->ext.diplo.hitParams;
    self->ext.diplo.hitParams2 = self->hitParams;
    if ((self->flags & FLAG_DEAD) && self->step < 11) {
        self->step = 11;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDiplocephalus);
        /* fallthrough */
    case 1:
        self->step_s = 0;
        self->ext.diplo.unk9C = 0;
        self->ext.diplo.unk9E = 0;
        self->facingLeft = GetSideToPlayer() & 1;
        self->nextPart = self + 1;
        entityRef = self;

        for (i = 0; i < 4; i++) {
            DestroyEntity(++entityRef);
            CreateEntityFromCurrentEntity(E_DIPLOCEPHALUS_FOOT, entityRef);
            if (i < 2) {
                entityRef->zPriority = self->zPriority + 8;
            } else {
                entityRef->zPriority = self->zPriority - 8;
            }
            entityRef->ext.diploBody.unk9D = 0;
            entityRef->facingLeft = self->facingLeft ^ 1;
            entityRef->ext.diploBody.diplo = self;
            entityRef->ext.diploBody.unk9E = i + 1;
            entityRef->nextPart = entityRef + 1;
        }

        self->ext.diplo.foot3 = entityRef;
        self->ext.diplo.foot2 = entityRef - 1;
        self->ext.diplo.foot1 = entityRef - 2;
        self->ext.diplo.foot0 = entityRef - 3;

        for (i = 0; i < 4; i++) {
            entityRef++;
            CreateEntityFromCurrentEntity(E_DIPLOCEPHALUS_LEG, entityRef);
            if (i < 2) {
                entityRef->zPriority = self->zPriority + 4;
            } else {
                entityRef->zPriority = self->zPriority - 4;
            }
            entityRef->facingLeft = self->facingLeft ^ 1;
            entityRef->ext.diploBody.diplo = self;
            entityRef->ext.diploBody.unk90 = entityRef - 4;
            entityRef->ext.diploBody.diplo = self;
            entityRef->ext.diploBody.unk9E = i + 1;

            if (i % 2) {
                entityRef->ext.diploBody.unk9F = self->facingLeft ^ 1;
            } else {
                entityRef->ext.diploBody.unk9F = self->facingLeft;
            }
            (entityRef - 4)->ext.diploBody.unk90 = entityRef;
            entityRef->nextPart = entityRef + 1;
        }

        entityRef++;
        CreateEntityFromCurrentEntity(E_DIPLOCEPHALUS_TAIL, entityRef);
        entityRef->zPriority = self->zPriority;
        entityRef->facingLeft = self->facingLeft ^ 1;
        entityRef->ext.diploTail.diplo = self;
        self->ext.diplo.tail = entityRef;
        entityRef->nextPart = entityRef + 1;

        entityRef += 9;
        DestroyEntity(entityRef);
        CreateEntityFromEntity(E_DIPLOCEPHALUS_TORSO, self, entityRef);
        entityRef->ext.diploBody.diplo = self;
        self->ext.diplo.torso = entityRef;

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
            UpdateFoot(entityRef);
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
            UpdateFoot(entityRef);
        }
        break;

    case 3:
#ifdef VERSION_PSP
        if (self->ext.diplo.unk9F++ == 0) {
#else
        if (++self->ext.diplo.unk9F == 1) {
#endif
            self->velocityY = 0x7ED0;
            self->ext.diplo.unk9D++;
        } else {
            self->velocityY -= FIX(0.03125);
        }

        if (self->ext.diplo.unk9F == 32) {
            self->ext.diplo.unk9F = 0;
            if (self->ext.diplo.unk9D < 2) {
                break;
            }
            self->velocityY = 0;
            self->step_s ^= 1;
            self->ext.diplo.activeFoot = self + 4 - (self->step_s << 1);
            self->step = 4;
            if (self->ext.diplo.unk9C ||
                CheckColliderOffsets(D_us_80181D30, self->facingLeft ^ 1) ^ 1) {
                self->step = 6;
                self->step_s ^= 1;
            }
        }

        self->ext.diplo.unk9C |= self->hitParams;
        AnimateEntity(anim0, self);
        MoveEntity();
        var_s2 = CheckColliderOffsets(D_us_80181D48, 1);
        if (var_s2 & 1) {
            self->posY.i.hi -= 1;
        }
        break;

    case 4:
        entityRef = self->ext.diplo.activeFoot;
        UpdateFoot(entityRef);
        if (entityRef->ext.diploBody.unk9F > 12) {
            UpdateFoot(entityRef - 1);
        }

        if (entityRef->step == 5 && (entityRef - 1)->step == 5) {
            entityRef->step = 2;
            (entityRef - 1)->step = 2;
            g_api.func_80102CD8(1);
            self->step = 3;
            if (self->ext.diplo.unk9C) {
                self->step = 6;
            }
        }

        self->velocityX = (entityRef - (self->step_s * 1))->velocityX >> 1;
        if (entityRef->ext.diploBody.unk9F >= 24) {
            self->velocityY = 0;
        } else {
            self->velocityY = entityRef->velocityY >> 2;
        }
        self->ext.diplo.unk9C |= self->hitParams;
        AnimateEntity(anim0, self);
        MoveEntity();
        break;

    case 6:
#ifdef VERSION_PSP
        if (self->ext.diplo.unk9F++ == 0) {
#else
        if (++self->ext.diplo.unk9F == 1) {
#endif
            self->poseTimer = 0;
            self->pose = 0;
            self->velocityY = 0x1B200;
        } else {
            self->velocityY -= FIX(1.0);
        }

        if (self->ext.diplo.unk9F == 4) {
            self->step_s ^= 1;
            self->ext.diplo.activeFoot = self + ((self->step_s << 1) + 1);
            self->step = 7;
            (self + 1)->step = 3;
            (self + 2)->step = 3;
            (self + 3)->step = 3;
            (self + 4)->step = 3;
            self->ext.diplo.unk9E++;
            self->ext.diplo.unk9F = 0;

            if ((self->ext.diplo.unk9E % 2 &&
                 CheckColliderOffsets(D_us_80181D3C, self->facingLeft ^ 1) ^
                     1) ||
                self->ext.diplo.unk9E > 8) {
                self->step = 3;
                self->ext.diplo.unk9C = 0;
                self->ext.diplo.unk9E = 0;
                self->ext.diplo.unk9F = 0;
                self->velocityY = 0;
                self->params = 0;
                (self + 1)->step = 2;
                (self + 2)->step = 2;
                (self + 3)->step = 2;
                (self + 4)->step = 2;
                self->ext.diplo.unk9D = 0;
                self->poseTimer = 0;
                self->pose = 0;
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
        AnimateEntity(anim1, self);
        MoveEntity();
        break;

    case 7:
        entityRef = self->ext.diplo.activeFoot;
        UpdateFoot(entityRef);
        if (entityRef->ext.diploBody.unk9F > 2) {
            UpdateFoot(entityRef + 1);
        }

        if ((entityRef + 1)->step == 5 && entityRef->step == 5) {
            entityRef->step = 3;
            (entityRef + 1)->step = 3;
            self->step = 6;
        }
        self->velocityX = (entityRef + (self->step_s * 1))->velocityX >> 1;
        if (entityRef->ext.diploBody.unk9F >= 6) {
            self->velocityY = 0;
        } else {
            self->velocityY = entityRef->velocityY >> 3;
        }
        AnimateEntity(anim1, self);
        MoveEntity();
        break;

    case 11:
        self->ext.diplo.tail->step = 8;
        self->velocityX = 0;
        self->step++;
        entityRef = self;

        for (i = 0; i < 10; i++) {
            entityRef->hitboxState = 0;
            entityRef++;
        }
        break;

    case 12:
        if (self->ext.diplo.tail->entityId != E_DIPLOCEPHALUS_TAIL &&
            UnkCollisionFunc3(D_us_80181D74) & EFFECT_SOLID) {
            g_api.func_80102CD8(1);
            self->step++;
        }
        break;

    case 13:
        var_s2 = Random() & 1;
        entityRef = self;

        for (i = 0; i < 4; i++) {
            entityRef++;
            entityRef->step = 6;
            entityRef->params = var_s2;
            entityRef->ext.diploBody.unk90->step = 6;
            entityRef->ext.diploBody.unk90->params = var_s2;
        }
        self->ext.diplo.unk98 = 0;

        for (i = 0; i < LEN(D_us_80181D28); i++) {
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
        self->ext.diplo.unk9C = 0;
        self->ext.diplo.unk9D = 0;
        self->animCurFrame = 0;
        entityRef = self->ext.diplo.torso;
        DestroyEntity(entityRef);
        self->step++;
        break;

    case 14:
        if (self->ext.diplo.unk9C++ >= 6) {
            self->ext.diplo.unk9C = 0;
            if (self->ext.diplo.unk9D < 24) {
                func_us_801D0898(self, 2);
                if (!(g_Timer & 2)) {
                    entityRef = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entityRef != NULL) {
                        CreateEntityFromEntity(E_EXPLOSION, self, entityRef);
                        entityRef->params = 2;
                    }
                }
                self->ext.diplo.unk9D++;
            } else {
                DestroyEntity(self);
            }
        }
        break;
    }

    if (self->step < 11 && self->step > 2) {
        self->posX.val = (self->ext.diplo.foot0->posX.val +
                          self->ext.diplo.foot3->posX.val) /
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
        self->ext.diploBody.unkA4 = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        self->ext.diploBody.unkA8 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    }

    player = &PLAYER;
    parent = self->ext.diploBody.diplo;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi - self->ext.diploBody.unkA4;
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi - self->ext.diploBody.unkA8;
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
    self->ext.diploBody.unkA4 = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    self->ext.diploBody.unkA8 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    if (parent->entityId != E_DIPLOCEPHALUS) {
        DestroyEntity(self);
    }
}

// Death explosion
void func_us_801D0898(Entity* self, s32 count) {
    Entity* newEntity;
    s32 i;
    s8 dx, dy;

    for (i = 0; i < count; i++) {
        dx = (Random() & 0x3F) - 0x20;
        dy = (Random() & 0x1F) - 0xF;
        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 1;
            newEntity->posX.i.hi += dx;
            newEntity->posY.i.hi += dy;
            newEntity->zPriority = self->zPriority + 2;
        }
    }
}
