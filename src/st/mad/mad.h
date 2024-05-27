#ifndef MAD_H
#define MAD_H

// MAD was compiled earlier than the very first retail release, the JP 1.0 ver.
// Since MAD is compiled with the US version, we need first to undefine it
#undef _internal_version_us
#define _internal_version_beta
#define VERSION_BETA
#define INCLUDE_ASM_OLD

#include "stage.h"

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
    E_ID_15 = 0x15
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
void EntityUnkId15(Entity* entity);

// ST/MAD
extern u16 g_InitializeData0[];
extern u16 D_8018052C[];
extern u16 UNK_Invincibility0[];
extern u16 g_eInitGeneric2[];
extern ObjInit2 D_8018056C[];
extern u16 D_80180D1C[];
extern u16 D_80180D4C[];
extern u16 D_80180E10[];
extern s16 D_80180ED8[];
extern s32 D_80180E18[];
extern s32 D_80180EC4[];
extern s16 D_80180EDA[];
extern u16 D_80180F5C[];
extern u16 D_80180FBC[];
extern s32 D_80180FCC[];
extern ObjInit2 D_801810F4[];
extern u16 g_InitializeEntityData0[];
extern s16 D_801809EC[];
extern u8 D_80181010[];
extern u16 g_testCollEnemyLookup[];
extern u8 g_testCollLuckCutoff[];
extern u8 g_testColluCoords[];
extern u8 g_testCollvCoords[];
extern u16 g_testCollElementLookup[10];
extern u8 g_testColliFrames[10];
extern u16 g_testCollPrizeTable[];
extern u16 g_testCollRandTable;
extern RoomHeader g_rooms[];
extern LayoutEntity* g_pStObjLayoutHorizontal[];
extern LayoutEntity* g_pStObjLayoutVertical[];
extern PfnEntityUpdate PfnEntityUpdates[];

extern LayoutEntity* g_LayoutObjHorizontal;
extern LayoutEntity* g_LayoutObjVertical;
extern u8 g_LayoutObjPosHorizontal;
extern u8 g_LayoutObjPosVertical;

extern u16 g_eBreakableInit[];
extern u8* g_eBreakableAnimations[8];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableDrawModes[];

// *** EntitySoulStealOrb properties START ***

extern u16 D_80181068[]; // NOTE(sestren): Random angle offsets?
extern u16 D_80181078[]; // NOTE(sestren): Animation frame properties?
extern u8 D_801810D8;

// *** EntitySoulStealOrb properties END ***

#endif
