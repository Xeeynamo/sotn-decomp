// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef STAGE_02_H
#define STAGE_02_H

#include "sattypes.h"
#include <saturn_sprite.h>

typedef struct UnkStruct_060e8350 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ char pad_0[0x14];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char pad_1A[0x4];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ struct UnkStruct_060e8350* unk20;
} UnkStruct_060e8350; // size = 0x24

typedef enum {
    E_NONE,
    E_BREAKABLE,
    E_EXPLOSION,
    E_PRIZE_DROP,
    E_NUMERIC_DAMAGE,
    E_RED_DOOR,
    E_INTENSE_EXPLOSION,
    E_SOUL_STEAL_ORB,
    E_ROOM_FOREGROUND,
    E_STAGE_NAME_POPUP,
    E_EQUIP_ITEM_DROP,
    E_RELIC_ORB,
    E_HEART_DROP,
    E_ENEMY_BLOOD,
    E_MESSAGE_BOX,
    E_DUMMY_0F,
    E_DUMMY_10,

    E_AXE_KNIGHT_AXE = 0x2A,
    E_BONE_SCIMITAR_PARTS = 0x28,
    E_FIRE = 0x38,
    E_SLOGRA_SPEAR = 0x41,
    E_SLOGRA_SPEAR_PROJECTILE = 0x42,
    E_GAIBON = 0x43,
    E_GAIBON_SMALL_FIREBALL = 0x45,
    E_GAIBON_BIG_FIREBALL = 0x46,
} EntityIDs;

s16 Random(void);
s32 AnimateEntityWithSpriteData(
    Entity* entity, const u8 frames[], const u8* spriteFrames[]);
Entity* AllocEntity(Entity*, Entity*);
void InitializeEntity(u16 arg0[]);
void PlaySfxPositional(s32 sfxId);
void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity);
void SetStep(u8 step);
void DestroyEntity(Entity* entity);

void func_0600AFA8(Unk0600B344*, SaturnSpriteFrameHeader*);
void func_0600B004(Unk0600B344*, s16*);
void TekiInit(Entity*, s32);
Unk0600B344* func_0600B344(s32, s32, s32, s32);
void func_06079BB4(Entity*);

extern SaturnSpriteFrameHeader* entityRedEyeBustData2[22];
extern SaturnSpriteResource entityRedEyeBustData;
extern SaturnSpriteResource g_Stage02TableWithGlobeResource;
extern u8 g_Stage02TableWithGlobeBreakAnim[];
extern u16 D_80180CC4[];
extern SaturnSpriteFrameHeader* g_Stage02TableWithGlobeFrames[19];
extern u16 g_Stage02TableWithGlobeDropParams[];
extern u8 g_Stage02TableWithGlobeIdleAnim[];
extern s16* g_Stage02SpittleBoneFrames[];
extern s16* g_Stage02Entity38Frames[];
extern s16* g_Stage02BoneScimitarFrames[];

#endif
