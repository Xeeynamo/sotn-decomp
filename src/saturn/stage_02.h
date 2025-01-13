// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef STAGE_02_H
#define STAGE_02_H

#include "sattypes.h"

typedef struct UnkStruct_060e8350 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ char pad_0[0x14];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char pad_1A[0x4];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ struct UnkStruct_060e8350* unk20;
} UnkStruct_060e8350; // size = 0x24

typedef struct {
    s32 unk0;
    u8 pad[4];
    u16 unk8;
    u16 unk10;
} Unk060ED26C;

typedef struct {
    u8 pad[0x1c];
    u32 unk28;
} Unk2;

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
    E_BONE_SCIMITAR_HEAD = 0x28,
    E_FIRE = 0x38,
    E_SLOGRA_SPEAR = 0x41,
    E_SLOGRA_SPEAR_PROJECTILE = 0x42,
    E_GAIBON = 0x43,
    E_GAIBON_SMALL_FIREBALL = 0x45,
    E_GAIBON_BIG_FIREBALL = 0x46,
} EntityIDs;

s16 Random(void);
s32 AnimateEntity(Entity* entity, const u8 frames[], const u8 frames2[]);
Entity* AllocEntity(Entity*, Entity*);
void InitializeEntity(u16 arg0[]);
void func_801C29B0(s32 sfxId); // sfx
void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity);
void SetStep(u8 step);

void func_0600AFA8(Unk0600B344*, u32);
void func_0600B004(Unk0600B344*, s32);
void func_0607B264(Entity*, s32);
Unk0600B344* func_0600B344(s32, s32, s32, s32);
void func_06079BB4(Entity*);
void func_0607B264(Entity*, s32);

extern Unk060ED26C entityRedEyeBustData;
extern Unk2 entityRedEyeBustData2;
extern Unk060ED26C D_060ED26C;
extern u8 dat_060ed174[];
extern u16 D_80180CC4[];
extern const u8 D_80180EF0[];
extern u16 D_80180F10[];
extern const u8 D_80180EF8[];
extern s32 DAT_060f4e6c[];
extern s32 DAT_060f237c[];
extern s32 DAT_060f2878[];

#endif
