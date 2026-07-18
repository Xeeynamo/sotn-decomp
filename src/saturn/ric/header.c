// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void RicInit(u16 params);
void RicMain(void);
void RicUpdatePlayerEntities(void);
s32 func_060B0610(void);
void func_060AC2DC(void);
void RicGetPlayerSensor(Collider* col);
void DisableAfterImage(s32 resetAnims, s32 arg1);
void RicSetInvincibilityFrames(s32 kind, s16 invincibilityFrames);
void func_060AA4F4(void);
Entity* RicCreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2);
void func_8015E484(void);
void func_8015F9F0(Entity* entity);
extern u8 D_060C2FA4[];
extern u8 D_060C2FE8[];

typedef struct {
    void* init;
    void* main;
    void* updatePlayerEntities;
    void* unk0C;
    void* unk10;
    void* getPlayerSensor;
    void* disableAfterImage;
    void* setInvincibilityFrames;
    void* unk20;
    void* unk24;
    void* createEntFactoryFromEntity;
    void* unk2C;
    void* getFreeEntity;
    void* unk34;
    void* unk38;
    void* data3C;
    void* data40;
} SaturnPlayerOvl;

SaturnPlayerOvl RIC_player = {
    RicInit,
    RicMain,
    RicUpdatePlayerEntities,
    func_060B0610,
    func_060AC2DC,
    RicGetPlayerSensor,
    DisableAfterImage,
    RicSetInvincibilityFrames,
    func_060B0610,
    func_060AA4F4,
    RicCreateEntFactoryFromEntity,
    func_8015E484,
    func_8015F9F0,
    func_060B0610,
    func_060B0610,
    D_060C2FA4,
    D_060C2FE8,
};
