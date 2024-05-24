#ifndef RWRP_H
#define RWRP_H

#include "common.h"
#include "stage.h"

#define CASTLE_FLAG_BANK 0x00

// RWRP Sound IDs
#define SE_RWRP_ENTER 0x636
#define SE_RWRP_DEBRIS 0x644 // unused?

extern PfnEntityUpdate D_801803E0[];
extern u16 D_80180494[];
extern s16 D_80180A94[];
extern ObjInit2 D_80181134[];

void CreateEntityFromLayout(Entity*, LayoutEntity*);

// *** EntitySoulStealOrb properties START ***

extern u16 D_801810A0[]; // NOTE(sestren): Random angle offsets?
extern u16 D_801810B0[]; // NOTE(sestren): Animation frame properties?
extern u16 g_InitializeData0[];
extern u16 D_80181110[];

// *** EntitySoulStealOrb properties END ***
extern s32 c_GoldPrizes[];
extern u16 D_80180DC4[];
extern u16 D_80180DF4[];
extern u8* D_80180E08[];

extern u16 g_InitializeEntityData0[];

void InitializeEntity(u16 arg0[]);
void EntityUnkId15(Entity* entity);
void EntityExplosion(Entity* entity);

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
    E_UNK_11,
    E_UNK_12,
    E_UNK_13,
    E_UNK_14,
    E_ID_15,
} EntityIDs;

#endif
