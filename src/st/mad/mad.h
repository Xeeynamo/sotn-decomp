// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef MAD_H
#define MAD_H

// MAD was compiled earlier than the very first retail release, the JP 1.0 ver.
// Since MAD is compiled with the US version, we need first to undefine it
#undef _internal_version_us
#define _internal_version_beta
#define VERSION_BETA
#define INCLUDE_ASM_OLD

#include "stage.h"

#define OVL_EXPORT(x) MAD_##x

// This is 0xA9 in all other overlays, there may be an underlying reason.
// For now it's just an overriding define.
#define NUM_HAND_ITEMS 0xAD

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
    E_DUMMY_0E,
    E_DUMMY_0F,
    E_DUMMY_10,
    E_ID_14 = 0x14,
    E_GREY_PUFF
} EntityIDs;

void CreateEntitiesToTheRight(s16);
void CreateEntitiesToTheLeft(s16);
void CreateEntitiesAbove(s16);
void CreateEntitiesBelow(s16);
void CreateEntityFromCurrentEntity(u16, Entity*);
u8 func_80192914(s16 arg0, s16 arg1);
void ReplaceBreakableWithItemDrop(Entity*);
void CreateEntityFromEntity(u16 entityId, Entity* ent1, Entity* ent2);
void BottomCornerText(u8* str, u8 lowerLeft);
void func_8019344C(void);
void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

// DRA - all the exclusive global variables
extern s32 D_80096ED0_mad;

// ST/MAD
extern u16 g_InitializeData0[];
extern u16 g_eInitGeneric2[];
extern u16 D_80180538[];
extern ObjInit D_8018056C[];
extern u8 D_801805B4[];
extern u8 D_801805BC[];
extern u16 D_801805C4[];
extern u16 aluric_subweapons_idx[];
extern u16 aluric_subweapons_id[];
extern u16 D_80180E10[];
extern s32 D_80180E18[];
extern s32 D_80180EC4[];
extern s16 g_collectXVelTable[];
extern s16 g_collectYVelTable[];
extern u16 g_HeartDropArray[];
extern u16 D_80180FBC[];
extern s32 D_80180FCC[];
extern ObjInit D_801810F4[];
extern u16 g_InitializeEntityData0[];
extern u8 g_UnkEntityAnimData[];
// extern u16 g_testCollEnemyLookup[];
// extern u8 g_testCollLuckCutoff[];
// extern u8 g_testColluCoords[];
// extern u8 g_testCollvCoords[];
// extern u16 g_testCollElementLookup[10];
// extern u8 g_testColliFrames[10];
// extern u16 g_testCollPrizeTable[];
// extern u16 g_testCollRandTable;
extern RoomHeader g_rooms[];
extern PfnEntityUpdate PfnEntityUpdates[];

extern u16 g_eBreakableInit[];
extern u8* g_eBreakableAnimations[8];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableDrawModes[];

// *** EntitySoulStealOrb properties START ***

extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u8 g_ESoulStealOrbAnim[];

// *** EntitySoulStealOrb properties END ***

extern s16 D_80199DE8;

#endif
