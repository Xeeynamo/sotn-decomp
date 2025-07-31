// SPDX-License-Identifier: AGPL-3.0-or-later

static u8 anim1[] = {8, 1, 8, 2, 0};
static u8 anim2[] = {6, 3, 6, 4, 6, 5,  6,  6, 6,   7,
                     6, 8, 6, 9, 6, 10, 15, 1, 255, 0};
static u8 anim3[] = {4, 1, 4, 10, 4, 9, 4, 8, 4,   7,
                     4, 6, 4, 5,  4, 4, 3, 3, 255, 0};
static s16 sensors1[] = {0, 20, 0, 4, 8, -4, -16, 0};
static s16 sensors2[] = {0, 20, 12, 0};

void EntityZombie(Entity* self) {
    Entity* newEntity;
    s32 temp_a0;

    if ((self->flags & FLAG_DEAD) && (self->step < 4)) {
        PlaySfxPositional(SFX_EXPLODE_SMALL);
        self->hitboxState = 0;
        // Spawn Zombie explosion
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLODE_PUFF_OPAQUE, self, newEntity);
            newEntity->zPriority = self->zPriority + 1;
            newEntity->posY.i.hi += 12;
            newEntity->params = 3;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitZombie);
        self->hitboxWidth = 8;
        self->hitboxHeight = 0;
        self->hitboxOffY = 0x10;
        self->zPriority += 4;
        if (g_Timer & 1) {
            self->palette++;
        }
        if (Random() & 1) {
            self->palette++;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        if (UnkCollisionFunc3(sensors1) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;

    case 2:
        if (AnimateEntity(anim2, self) == 0) {
            SetStep(3);
        }
        if (!self->poseTimer) {
            self->hitboxOffY -= 2;
            self->hitboxHeight += 2;
        }
        break;

    case 3:
        AnimateEntity(anim1, self);
        temp_a0 = UnkCollisionFunc2(sensors2);
        if (self->facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        if (temp_a0 & 0xC0) {
            self->hitboxState = 0;
            SetStep(4);
        }
        break;

    case 4:
        if (AnimateEntity(anim3, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
/*
 * An invisible entity that is responsible for spawning the "floor
 * zombies" that come up from the ground and swarm the player.
 * Every 32 to 95 frames, it will alternate spawning a zombie
 * on the right side or left side of the screen.
 * The exact position a zombie is spawned in is also randomized.
 */
void EntityZombieSpawner(Entity* self) {
    s32 temp;
    Entity* newEntity;

    if (!self->step) {
        InitializeEntity(g_EInitSpawner);
        self->flags &= FLAG_UNK_2000;
        self->ext.zombieSpawner.spawnDelay = 1;
    }

    if (g_CastleFlags[CASTLE_TURNED_ON]) {
        self->posX.i.hi = 128;
        if (!--self->ext.zombieSpawner.spawnDelay) {
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[168]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ZOMBIE, self, newEntity);
                temp = (Random() & 0x3F) + 96;

                if (self->ext.zombieSpawner.spawnSide != 0) {
                    newEntity->posX.i.hi += temp;
                } else {
                    newEntity->posX.i.hi -= temp;
                }
                newEntity->posY.i.hi -= 48;
                self->ext.zombieSpawner.spawnSide ^= 1;

                // Zombies are prevented from spawning too close to the
                // edges of the room.
                temp = g_Tilemap.scrollX.i.hi + newEntity->posX.i.hi;
                if ((temp < (g_Tilemap.x + 128)) ||
                    ((g_Tilemap.width - 128) < temp)) {
                    DestroyEntity(newEntity);
                }
            }
            self->ext.zombieSpawner.spawnDelay = (Random() & 0x3F) + 32;
        }
    }
}
