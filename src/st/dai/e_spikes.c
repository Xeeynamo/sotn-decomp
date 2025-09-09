// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#ifdef VERSION_PSP
extern s32 E_ID(SPIKES_PARTS);
extern s32 E_ID(SPIKES_DUST);
extern s32 E_ID(SPIKES_DAMAGE);
#endif

static u8 anim_dust[] = {2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 4, 6, -1, 0, 0, 0};
static u8 spikes_params[][3] = {{5, 4, 6}, {1, 0, 2}, {9, 8, 10}, {0, 0, 0}};

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
    case 0:
        InitializeEntity(g_EInitStatueBlock);
        self->animCurFrame = 15;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->zPriority = 160;
        self->velocityX = 0;
        self->velocityY = 0;
        self->rotate = 0;
        self->ext.spikes.rotate = 0;
        params = (self->params & 0xFF00) >> 8;
        if ((params) & 1) {
            self->velocityX = FIX(0.5);
            self->rotate += ROT(1.40625);
            self->ext.spikes.rotate += 8;
        }
        if ((params) & 2) {
            self->velocityX = FIX(-0.5);
            self->rotate -= ROT(1.40625);
            self->ext.spikes.rotate -= 8;
        }
        params = self->params & 0xFF;
        if (params & 2) {
            self->velocityX += FIX(-0.75);
            self->rotate -= ROT(90);
            self->ext.spikes.rotate += 64;
        }
        if (params & 1) {
            self->velocityX += FIX(0.75);
            self->rotate += ROT(90);
            self->ext.spikes.rotate -= 64;
        }
        if (params & 4) {
            self->velocityY += FIX(0.75);
            self->rotate -= ROT(180);
        }
        if (params & 8) {
            self->velocityY += FIX(-2.5);
        }
        self->velocityX += ((Random() & 3) << 13) - FIX(0.1875);
        self->velocityY += ((Random() & 3) << 13) - FIX(0.1875);
        self->ext.spikes.rotate += ((Random() & 3) * 16) - 24;
        break;
    case 1:
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
    s32 count, tileIdxOffset;
    u32 tileType;
    u8 collisionType;
    u8 params;

    tilePosX = ((tileIdx % 80) * 16) + 8;
    tilePosY = ((tileIdx / 80) * 16) + 8;
    params = 0;
    tileIdx -= 81;
    for (count = 0; count < 3; tileIdx += 80, count++) {
        for (tileIdxOffset = 0; tileIdxOffset < 3; tileIdxOffset++) {
            tileType = (&g_Tilemap.fg[tileIdx])[tileIdxOffset];
            collisionType = g_Tilemap.tileDef->collision[tileType];
            if (collisionType == 3) {
                params |= spikes_params[count][tileIdxOffset];
            }
        }
    }
    tilePosX -= g_Tilemap.scrollX.i.hi;
    tilePosY -= g_Tilemap.scrollY.i.hi;
    for (count = 0; count < 3; count++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_ID(SPIKES_PARTS), entity);
            entity->posX.i.hi = tilePosX;
            entity->posY.i.hi = tilePosY;
            entity->params = params + (count << 8);
        }
    }
    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (entity != NULL) {
        CreateEntityFromCurrentEntity(E_INTENSE_EXPLOSION, entity);
        entity->posX.i.hi = tilePosX;
        entity->posY.i.hi = tilePosY;
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

    tilePosX = ((tileIdx % 80) * 16) + 8;
    tilePosY = ((tileIdx / 80) * 16) + 8;
    tilePosX -= g_Tilemap.scrollX.i.hi;
    tilePosY -= g_Tilemap.scrollY.i.hi;

    spikesDamage = g_CurrentEntity + 1;
    spikesDamage->posX.i.hi = tilePosX;
    spikesDamage->posY.i.hi = tilePosY;
}

void EntitySpikes(Entity* self) {
    Entity* playerPtr;
    Entity* entity;
    u32 tileIdx;
    u32 tileType;
    u8 collisionType;
    s32 count;
    s16 posX, posY;
    s16 scrollX, scrollY;

    playerPtr = &PLAYER;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID(SPIKES_DAMAGE), entity);
        break;
    case 1:
        entity = self + 1;
        entity->posX.i.hi = -16;
        entity->posY.i.hi = -16;
        posX = playerPtr->posX.i.hi;
        posY = playerPtr->posY.i.hi;
        scrollX = posX + g_Tilemap.scrollX.i.hi;
        scrollY = posY + g_Tilemap.scrollY.i.hi;
        tileIdx = (scrollX >> 4) + (scrollY >> 4) * g_Tilemap.hSize * 16;
        tileIdx -= 80;
        for (count = 0; count < 3; tileIdx += 80, count++) {
            tileType = g_Tilemap.fg[tileIdx];
            collisionType = g_Tilemap.tileDef->collision[tileType];
            if (collisionType > 243 && collisionType < 248) {
                if (g_api.CheckEquipmentItemCount(
                        ITEM_SPIKE_BREAKER, EQUIP_ARMOR)) {
                    g_Tilemap.fg[tileIdx] = NULL;
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
        self->attackElement = ELEMENT_CUT | ELEMENT_UNK_10 | ELEMENT_UNK_1;
        self->attack = 15;
        self->hitboxState = 1;
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->poseTimer = 4;
    }
}
