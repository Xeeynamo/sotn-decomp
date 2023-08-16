#ifndef MAD_H
#define MAD_H

// hack to make the code compile for this weird overlay
#define STAGE_MAD_FIX
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
} EntityIDs;

void func_801908DC(s16);
void func_801909D8(s16);
void func_80190B7C(s16);
void func_80190C78(s16);
void CreateEntityFromCurrentEntity(u16, Entity*);
u8 func_80192914(s16 arg0, s16 arg1);
void ReplaceBreakableWithItemDrop(Entity*);
void CreateEntityFromEntity(u16 entityId, Entity* ent1, Entity* ent2);
void func_80198BC8(void* const, s32);
void func_8019344C(void);

// OFFSET FIXED
extern u8 D_8003BEE8[];
extern Entity* g_CurrentEntity;
extern Entity g_Entities[];
extern Entity D_8007D858[];
extern Entity D_8007EF1C;
extern s32 D_80097410;
extern s32 D_80097414;
extern s32 D_800973FC;

// TODO FIX
extern s32 D_80097908;

// ST/MAD
extern u16 D_8018052C[];
extern u16 UNK_Invincibility0[];
extern u16 D_80180544[];
extern ObjInit2 D_8018056C[];
extern u16 D_80180D1C[];
extern u16 D_80180D4C[];
extern s16 D_80180ED8[];
extern s32 D_80180E18[];
extern s32 D_80180EC4[];
extern s16 D_80180EDA[];
extern u16 D_80180F5C[];
extern u16 D_80180FBC[];
extern s32 D_80180FCC[];
extern s32 D_80180FE4[];
extern u8 D_80180FFC[];
extern u16 D_80181000[];
extern ObjInit2 D_801810F4[];
extern u16 g_InitializeEntityData0[];
extern s16 D_801809EC[];
extern u8 D_80181010[];
extern RoomHeader g_rooms[];
extern LayoutEntity* g_pStObjLayout[];
extern LayoutEntity* D_801803C8[];
extern PfnEntityUpdate PfnEntityUpdates[];

extern LayoutEntity* D_801997D8;
extern u16* D_801997DC;
extern u8 D_801997E0;
extern s8 D_801997E4;
extern u16 UNK_Update0[];

extern u16 g_eBreakableInit[];
extern u8* g_eBreakableAnimations[8];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableBlendModes[];

// *** EntitySoulStealOrb properties START ***

extern u16 D_80181068[]; // NOTE(sestren): Random angle offsets?
extern u16 D_80181078[]; // NOTE(sestren): Animation frame properties?
extern u8 D_801810D8;

// *** EntitySoulStealOrb properties END ***

#endif