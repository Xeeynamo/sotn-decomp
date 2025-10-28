// SPDX-License-Identifier: AGPL-3.0-or-later

#ifdef VERSION_PSP
extern s32 E_ID(SPIKES_PARTS);
extern s32 E_ID(SPIKES_DUST);
extern s32 E_ID(SPIKES_DAMAGE);
#endif

enum SpikesSteps {
    SPIKES_INIT,
    SPIKES_INTERACT,
};

enum SpikesPartsSteps {
    SPIKES_PARTS_INIT,
    SPIKES_PARTS_MOVE,
};

enum SpikesMoveDirections {
    SPIKES_MOVE_RIGHT = 1,
    SPIKES_MOVE_LEFT = 2,
};

enum SpikesPointDirections {
    SPIKES_DEFAULT = 0,
    SPIKES_POINT_RIGHT = 1,
    SPIKES_POINT_LEFT = 2,
    SPIKES_ON_CEILING = 4,
    SPIKES_ON_FLOOR = 8,
};

#ifndef SPIKES_ELEMENT
#define SPIKES_ELEMENT ELEMENT_CUT | ELEMENT_UNK_10
#endif

static AnimateEntityFrame anim_dust[] = {
    {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {4, 6}, POSE_END};
#ifdef HAS_ORIENTATIONS
static u8 parts_params[][3] = {{5, 4, 6}, {1, 0, 2}, {9, 8, 10}};
#endif

void EntitySpikesDust(Entity* self) {
    s16 angle;

    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->zPriority = 160;
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = PAL_OVL(PAL_SPIKES_DUST);
        angle = GetAngleBetweenEntitiesShifted(self, &PLAYER);
        SetEntityVelocityFromAngle(angle, 40);
        return;
    }
    MoveEntity();
    if (!AnimateEntity(anim_dust, self)) {
        DestroyEntity(self);
    }
}

void EntitySpikesParts(Entity* self) {
    Collider collider;
    s16 posX, posY;
    u8 params;

    switch (self->step) {
    case SPIKES_PARTS_INIT:
        InitializeEntity(g_EInitEnvironment);
#ifdef SPIKES_PARTS_FRAME
        self->animCurFrame = SPIKES_PARTS_FRAME;
#endif
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->zPriority = 160;
        self->velocityX = 0;
        self->velocityY = 0;
        self->rotate = 0;
        self->ext.spikes.rotate = 0;
#ifdef HAS_ORIENTATIONS
        params = (self->params & 0xFF00) >> 8;
#else
        params = self->params;
#endif
        if (params & 1) {
            self->velocityX = FIX(0.5);
            self->rotate += ROT(1.40625);
            self->ext.spikes.rotate += 8; // 0.703125 degrees
        }
        if (params & 2) {
            self->velocityX = FIX(-0.5);
            self->rotate -= ROT(1.40625);
            self->ext.spikes.rotate -= 8;
        }
#ifdef HAS_ORIENTATIONS
        params = self->params & 0xFF;
        if (params & SPIKES_POINT_LEFT) {
            self->velocityX += FIX(-0.75);
            self->rotate -= ROT(90);
            self->ext.spikes.rotate += ROT(5.625);
        }
        if (params & SPIKES_POINT_RIGHT) {
            self->velocityX += FIX(0.75);
            self->rotate += ROT(90);
            self->ext.spikes.rotate -= ROT(5.625);
        }
        if (params & SPIKES_ON_CEILING) {
            self->velocityY += FIX(0.75);
            self->rotate -= ROT(180);
        }
        if (params & SPIKES_ON_FLOOR) {
            self->velocityY += FIX(-2.5);
        }
#else
        self->velocityY += FIX(0.75);
#endif
        self->velocityX += ((Random() & 3) << 13) - FIX(0.1875);
        self->velocityY += ((Random() & 3) << 13) - FIX(0.1875);
        // Randomly choose between rotating left or right either
        // 2.109375 degrees or 0.703125 degrees
        self->ext.spikes.rotate += ((Random() & 3) * 16) - 24;
        break;
    case SPIKES_PARTS_MOVE:
        MoveEntity();
        self->velocityY += FIX(0.15625);
        self->rotate += self->ext.spikes.rotate;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects) {
            if (collider.effects & EFFECT_SOLID) {
                self->velocityY = -self->velocityY / 2;
                self->ext.spikes.rotate *= 4;
            }
            if (collider.effects & EFFECT_UNK_0002) {
                self->velocityX = -self->velocityX;
            }
            if (abs(self->velocityY) < FIX(0.1875)) {
                DestroyEntity(self);
            }
        }
        break;
    }
}

static void SpikesBreak(u32 tileIdx) {
    Entity* entity;
    s16 tilePosX, tilePosY;
    s32 count;
#ifdef HAS_ORIENTATIONS
    s32 tileIdxOffset;
    u32 tileType;
    u8 collisionType;
    u8 params;
#endif

    tilePosX = ((tileIdx % SPIKES_TILE_WIDTH) * 16) + 8;
    tilePosY = ((tileIdx / SPIKES_TILE_WIDTH) * 16) + 8;
#ifdef HAS_ORIENTATIONS
    params = 0;
    tileIdx -= SPIKES_TILE_WIDTH + 1;
    for (count = 0; count < 3; tileIdx += SPIKES_TILE_WIDTH, count++) {
        for (tileIdxOffset = 0; tileIdxOffset < 3; tileIdxOffset++) {
            tileType = (&g_Tilemap.fg[tileIdx])[tileIdxOffset];
            collisionType = g_Tilemap.tileDef->collision[tileType];
            if (collisionType == 3) {
                params |= parts_params[count][tileIdxOffset];
            }
        }
    }
#endif
    tilePosX -= g_Tilemap.scrollX.i.hi;
    tilePosY -= g_Tilemap.scrollY.i.hi;
    for (count = 0; count < 3; count++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_ID(SPIKES_PARTS), entity);
            entity->posX.i.hi = tilePosX;
            entity->posY.i.hi = tilePosY;
#ifdef HAS_ORIENTATIONS
            entity->params = params + (count << 8);
#else
            entity->params = count;
#endif
        }
    }
    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (entity != NULL) {
        CreateEntityFromCurrentEntity(E_INTENSE_EXPLOSION, entity);
        entity->posX.i.hi = tilePosX;
        entity->posY.i.hi = tilePosY;
        // params & 0xF0 to EntityIntenseExplosion uses the dust cloud palette
        entity->params = 16;
    }
    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (entity != NULL) {
        CreateEntityFromCurrentEntity(E_ID(SPIKES_DUST), entity);
        entity->posX.i.hi = tilePosX;
        entity->posY.i.hi = tilePosY;
    }
}

static void SpikesApplyDamage(u32 tileIdx) {
    Entity* spikesDamage;
    s16 tilePosX, tilePosY;

    tilePosX = ((tileIdx % SPIKES_TILE_WIDTH) * 16) + 8;
    tilePosY = ((tileIdx / SPIKES_TILE_WIDTH) * 16) + 8;
    tilePosX -= g_Tilemap.scrollX.i.hi;
    tilePosY -= g_Tilemap.scrollY.i.hi;

#ifdef HAS_ORIENTATIONS
    spikesDamage = &g_CurrentEntity[1];
#ifdef DAMAGE_ENT_ON_HIT
    spikesDamage->posX.i.hi = tilePosX;
    spikesDamage->posY.i.hi = tilePosY;
#endif
#endif

#ifdef DAMAGE_ENT_ON_HIT
    // Create the damage entity at tile location
    spikesDamage = AllocEntity(&DAMAGE_ENT_START, &DAMAGE_ENT_END);
    if (spikesDamage != NULL) {
        CreateEntityFromCurrentEntity(E_ID(SPIKES_DAMAGE), spikesDamage);
        spikesDamage->posX.i.hi = tilePosX;
        spikesDamage->posY.i.hi = tilePosY;
    }
#else
    // Move the damage entity to tile location
    spikesDamage->posX.i.hi = tilePosX;
    spikesDamage->posY.i.hi = tilePosY;
#endif
}

void EntitySpikes(Entity* self) {
#ifdef HAS_ORIENTATIONS
    Entity* entity;
#else
    u32 newTileType;
#endif
    Entity* playerPtr;
    u32 tileIdx;
    u32 tileType;
    u8 collisionType;
    s32 count;
    s16 posX, posY;
    s16 scrollX, scrollY;

    playerPtr = &PLAYER;
    switch (self->step) {
    case SPIKES_INIT:
        InitializeEntity(g_EInitSpawner);
#ifdef DAMAGE_ENT_ON_SPAWN
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID(SPIKES_DAMAGE), entity);
#endif
#ifdef HAS_ORIENTATIONS
        break;
    case SPIKES_INTERACT:
        entity = self + 1;
        entity->posX.i.hi = -16;
        entity->posY.i.hi = -16;
#else
        g_GpuBuffers[0].draw.r0 = 0x10;
        g_GpuBuffers[0].draw.g0 = 0x10;
        g_GpuBuffers[0].draw.b0 = 0x10;
        g_GpuBuffers[1].draw.r0 = 0x10;
        g_GpuBuffers[1].draw.g0 = 0x10;
        g_GpuBuffers[1].draw.b0 = 0x10;
    /* fallthrough */
    case SPIKES_INTERACT:
#endif
        posX = playerPtr->posX.i.hi;
        posY = playerPtr->posY.i.hi;
        scrollX = posX + g_Tilemap.scrollX.i.hi;
        scrollY = posY + g_Tilemap.scrollY.i.hi;
        tileIdx = (scrollX >> 4) + (scrollY >> 4) * g_Tilemap.hSize * 16;
        tileIdx -= SPIKES_TILE_WIDTH;
        for (count = 0; count < 3; tileIdx += SPIKES_TILE_WIDTH, count++) {
            tileType = g_Tilemap.fg[tileIdx];
            collisionType = g_Tilemap.tileDef->collision[tileType];
            if (collisionType > 243 && collisionType < 248) {
                if (g_api.CheckEquipmentItemCount(
                        ITEM_SPIKE_BREAKER, EQUIP_ARMOR)) {
#ifdef HAS_ORIENTATIONS
                    g_Tilemap.fg[tileIdx] = 0;
#else
                    switch (tileType) {
                    case 0x6AE:
                        newTileType = 0x6B1;
                        break;

                    case 0x6AF:
                        newTileType = 0x6B2;
                        break;

                    case 0x6B0:
                        newTileType = 0x6B3;
                        break;
                    }
                    g_Tilemap.fg[tileIdx] = newTileType;
#endif
                    SpikesBreak(tileIdx);
                    g_api.PlaySfx(SFX_EXPLODE_FAST_A);
                } else {
                    SpikesApplyDamage(tileIdx);
                }
            }
        }
        break;
    }
}

void EntitySpikesDamage(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->attackElement = SPIKES_ELEMENT;
        self->attack = 15;
        self->hitboxState = 1;
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->poseTimer = 4;
#ifdef DAMAGE_ENT_ON_HIT
    } else {
        DestroyEntity(self);
#endif
    }
}
