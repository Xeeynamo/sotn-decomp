// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rcat/rcat.h"
#ifdef VERSION_PSP
extern s32 E_ID(SPIKES_PARTS);
extern s32 E_ID(SPIKES_DUST);
extern s32 E_ID(SPIKES_DAMAGE);
#endif
#define HAS_ORIENTATIONS
#define SPIKES_TILE_WIDTH 48
#define SPIKES_ELEMENT ELEMENT_CUT | ELEMENT_UNK_10 | ELEMENT_UNK_1
#define DAMAGE_ENT_START g_CurrentEntity[1]
#define DAMAGE_ENT_END g_CurrentEntity[4]

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

static AnimateEntityFrame anim_dust[] = {
    {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {4, 6}, POSE_END};
#ifdef HAS_ORIENTATIONS
static u8 parts_params[][3] = {{5, 4, 6}, {1, 0, 2}, {9, 8, 10}};
#endif

extern u16 g_EInitParticle;
extern u16 g_EInitInteractable;
extern u16 D_us_80181018;

void EntitySpikesDust(Entity* self) {
    s16 angle;

    if (!self->step) {
        InitializeEntity(&g_EInitParticle);
        self->zPriority = 160;
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = PAL_FLAG(PAL_SPIKES_DUST);
        angle = GetAngleBetweenEntitiesShifted(self, &PLAYER);
        SetEntityVelocityFromAngle(angle, 40);
        return;
    }
    MoveEntity();
    if (AnimateEntity(anim_dust, self) == 0) {
        DestroyEntity(self);
    }
}

void EntitySpikesParts(Entity* self) {
    Collider collider;
    s32 posX, posY;
    u8 params;

    switch (self->step) { // irregular
    case SPIKES_PARTS_INIT:
        InitializeEntity(&D_us_80181018);
        self->animCurFrame = 18;
        self->drawFlags |= ENTITY_ROTATE;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->zPriority = 160;
        self->velocityX = 0;
        self->velocityY = 0;
        self->rotate = 0;
        self->ext.spikes.rotate = 0;

        params = (self->params & 0xFF00) >> 8;

        if (params & 1) {
            self->velocityX = FIX(0.5);
            self->rotate += ROT(1.40625);
            self->ext.spikes.rotate += +8;
        }
        if (params & 2) {
            self->velocityX = -FIX(0.5);
            self->rotate -= ROT(1.40625);
            self->ext.spikes.rotate -= 8;
        }

        params = self->params & 0xFF;
        if (params & SPIKES_POINT_LEFT) {
            self->velocityX -= FIX(0.75);
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
            self->velocityY -= FIX(2.5);
        }
        self->velocityX += ((Random() & 3) << 13) - FIX(0.1875);
        self->velocityY += ((Random() & 3) << 13) - FIX(0.1875);
        self->ext.spikes.rotate += ((Random() & 3) * 16) - 24;
        break;
    case SPIKES_PARTS_MOVE:
        MoveEntity();
        self->velocityY += FIX(0.15625);
        self->rotate += self->ext.spikes.rotate;

        posX = self->posX.i.hi;
        posY = self->posY.i.hi;

        // Need to keep this conversion to compile to seh and not move
        g_api.CheckCollision((s16)posX, (s16)posY, &collider, 0);

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

extern s32 D_psp_E_SPIKES_DUST;
extern s32 D_psp_E_SPIKES_PARTS;
extern Entity g_Entities_224;

void SpikesBreak(u32 tileIdx) {
    Entity* entity;
    s16 tilePosX, tilePosY;
    s32 count;
    s32 tileIdxOffset;
    u32 tileType;
    u8 collisionType;
    u8 params;

    tilePosX = ((tileIdx % SPIKES_TILE_WIDTH) * 16) + 8;
    tilePosY = ((tileIdx / SPIKES_TILE_WIDTH) * 16) + 8;
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
    tilePosX -= g_Tilemap.scrollX.i.hi;
    tilePosY -= g_Tilemap.scrollY.i.hi;

    for (count = 0; count < 3; count++) {
        entity = AllocEntity(&g_Entities_224, (Entity*)&D_80097C98);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(D_psp_E_SPIKES_PARTS, entity);
            entity->posX.i.hi = tilePosX;
            entity->posY.i.hi = tilePosY;
            entity->params = params + (count << 8);
        }
    }

    entity = AllocEntity(&g_Entities_224, (Entity*)&D_80097C98);
    if (entity != NULL) {
        CreateEntityFromCurrentEntity(E_INTENSE_EXPLOSION, entity);
        entity->posX.i.hi = tilePosX;
        entity->posY.i.hi = tilePosY;
        // params & 0xF0 to EntityIntenseExplosion uses the dust cloud palette
        entity->params = 16;
    }
    entity = AllocEntity(&g_Entities_224, (Entity*)&D_80097C98);
    if (entity != NULL) {
        CreateEntityFromCurrentEntity(D_psp_E_SPIKES_DUST, entity);
        entity->posX.i.hi = tilePosX;
        entity->posY.i.hi = tilePosY;
    }
}

void SpikesApplyDamage(u32 tileIdx) {
    Entity* spikesDamage;

    s16 tilePosX, tilePosY;

    tilePosX = ((tileIdx % SPIKES_TILE_WIDTH) * 16) + 8;
    tilePosY = ((tileIdx / SPIKES_TILE_WIDTH) * 16) + 8;
    tilePosX -= g_Tilemap.scrollX.i.hi;
    tilePosY -= g_Tilemap.scrollY.i.hi;
    spikesDamage = &g_CurrentEntity[1];

    spikesDamage->posX.i.hi = tilePosX;
    spikesDamage->posY.i.hi = tilePosY;

    spikesDamage = AllocEntity(&DAMAGE_ENT_START, &DAMAGE_ENT_END);
    if (spikesDamage != NULL) {
        CreateEntityFromCurrentEntity(E_ID(SPIKES_DAMAGE), spikesDamage);
        spikesDamage->posX.i.hi = tilePosX;
        spikesDamage->posY.i.hi = tilePosY;
    }
}

INCLUDE_ASM("st/rcat_psp/nonmatchings/rcat_psp/e_spikes", EntitySpikes);

void EntitySpikesDamage(Entity* self) {
    if (!self->step) {
        InitializeEntity(&g_EInitInteractable);
        self->attackElement = SPIKES_ELEMENT;
        self->attack = 15;
        self->hitboxState = 1;
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->poseTimer = 4;
        return;
    }
    DestroyEntity(self);
}
