// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_PLAYER_H
#define SATURN_PLAYER_H

#include "sattypes.h"

typedef void (*SaturnPlayerInitCallback)(u16 params);
typedef void (*SaturnPlayerCallback)(void);
typedef s32 (*SaturnPlayerStatusCallback)(void);
typedef void (*SaturnPlayerSensorCallback)(Collider* collider);
typedef void (*SaturnPlayerDisableAfterImageCallback)(s32 resetAnims, s32 arg1);
typedef void (*SaturnPlayerInvincibilityCallback)(
    s32 kind, s16 invincibilityFrames);
typedef Entity* (*SaturnPlayerCreateFactoryCallback)(
    Entity* source, u32 factoryParams, s32 arg2);
typedef void (*SaturnPlayerEntityCallback)(Entity* entity);

typedef struct {
    u32 sourceOffset;
    u32 byteCount;
} SaturnPlayerGraphicsRecord;

typedef struct {
    SaturnPlayerInitCallback init;
    SaturnPlayerCallback main;
    SaturnPlayerCallback updatePlayerEntities;
    SaturnPlayerCallback reserved0C;
    SaturnPlayerCallback reserved10;
    SaturnPlayerSensorCallback getPlayerSensor;
    SaturnPlayerDisableAfterImageCallback disableAfterImage;
    SaturnPlayerInvincibilityCallback setInvincibilityFrames;
    SaturnPlayerCallback reserved20;
    SaturnPlayerCallback reserved24;
    SaturnPlayerCreateFactoryCallback createEntFactoryFromEntity;
    SaturnPlayerCallback reserved2C;
    SaturnPlayerEntityCallback assignEnemyId;
    SaturnPlayerCallback reserved34;
    SaturnPlayerCallback reserved38;
    u8* data3C;
    SaturnPlayerGraphicsRecord* graphicsRecords;
} SaturnPlayerOvl;

#endif
