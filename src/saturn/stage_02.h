#ifndef STAGE_02_H
#define STAGE_02_H

#include "sattypes.h"

struct Unk0600B344* func_0600B344(s32, s32, s32, s32);
struct Unk060ED26C {
    s32 unk0;
    u8 pad[4];
    u16 unk8;
    u16 unk10;
};
extern struct Unk060ED26C entityRedEyeBustData;
void func_0607B264(Entity*, s32);

struct Unk2 {
    u8 pad[0x1c];
    u32 unk28;
};
extern struct Unk2 entityRedEyeBustData2;

void func_0600AFA8(struct Unk0600B344*, u32);

extern u16 D_80180CC4[];
extern const u8 D_80180EF0[];
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
    E_SAVE_GAME_POPUP,
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

extern u16 D_80180F10[];
extern const u8 D_80180EF8[];
s32 AnimateEntity(Entity* entity, const u8 frames[], const u8 frames2[]);
void InitializeEntity(u16 arg0[]);
void func_801C29B0(s32 sfxId); // sfx
void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity);
void SetStep(u8 step);

void func_06079BB4(Entity*);
void func_0607B264(Entity*, s32);

struct Unk0600B344* func_0600B344(s32, s32, s32, s32);
extern struct Unk060ED26C D_060ED26C;
extern u8 dat_060ed174[];

#endif