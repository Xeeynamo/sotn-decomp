#include "stage.h"

typedef enum EntityIDs {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION,
    /* 0x03 */ E_PRIZE_DROP,
    /* 0x04 */ E_NUMERIC_DAMAGE,
    /* 0x05 */ E_RED_DOOR,
    /* 0x06 */ E_INTENSE_EXPLOSION,
    /* 0x07 */ E_SOUL_STEAL_ORB,
    /* 0x08 */ E_ROOM_FOREGROUND,
    /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP,
    /* 0x0B */ E_RELIC_ORB,
    /* 0x0C */ E_HEART_DROP,
    /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_SAVE_GAME_POPUP,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,

    /* 0x11 */ E_ID_11 = 0x11,
    /* 0x15 */ E_ID_15 = 0x15,
} EntityIDs;

extern void CreateEntityFromCurrentEntity(u16, Entity*);
extern void ReplaceBreakableWithItemDrop(Entity*);
extern s32 func_801C5D18(Entity* entity, s32 arg1, s32 arg2, s32 arg3);
extern void func_801C8C84(
    Entity* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);
extern POLY_GT4* func_801D6DB8(POLY_GT4* poly);

LayoutEntity* D_80180850[];
extern u16 D_80180AB8[];
extern u16 D_80180AC4[];
extern u16 D_80180AD0[];
extern u16 D_80180ADC[];
extern u16 D_80180AE8[];
extern u16 D_80180B00[];
extern u16 D_80180B18[];
extern u16 D_80180B48[];
extern u16 D_80180B54[];
extern u16 D_80180B6C[];
extern u16 D_80180B84[];
extern u16 D_80180B90[];
extern u16 D_80180BA8[];
extern ObjInit2 D_80180BFC[];
extern SVEC4 D_80181024[];
extern u16 D_80181230[];
extern s32 g_TrapDoorFlag; // 0 = Closed, 1 = Open
extern u8 D_80181240[];
extern u16 D_80181258[];
extern u16 D_80181264[];
extern u16 D_8018127C[];
extern u16 D_80181294[];
extern u16 D_801812A0[];
extern u16 D_801812B8[];
extern u16 D_801812E2[];
extern u16 D_8018131E[];
extern u16 D_8018133C[];
extern u8 D_80181344[];
extern s32 D_8018134C;
extern s32 D_80181354;
extern s32 D_8018135C;
extern s32 D_80181364;
extern const u8 D_80181390[];
extern u16 D_8018139C[];
extern u16 D_8018139E[];
extern u16 D_801814EC[];
extern u16 D_801817F8[];
extern u8 D_801819D0[];
extern u8 D_801819DC[];
extern s32 D_801819E8[];
extern s32 D_801819EC[];
extern u8 D_80181B40[];
extern u8 D_80181B4C[];
extern u16 D_80181C8C[];
extern u16 UNK_Invincibility0[];
extern s16 D_801820C4[];
extern u16 D_801823F4[];
extern u8* D_80182438[];
extern u16 D_80182424[];
extern u8* D_80182488[];
extern u16 D_801824E8[];
extern s32 D_801824F4[];
extern u8* D_801825A0[];
extern u16 D_80182628[];
extern s32 D_80182650[];
extern u8 D_80182668[];
extern u16 D_8018266C[];
extern s32 D_80182638[];
extern u8 D_8018267C[];
extern ObjInit2 D_80182764[];
extern s32 c_GoldPrizes[];
extern u8 D_8018383C[];
extern u8 D_80183994[];
extern const u8 D_801839A0[];
extern u8 D_801839A8[];
extern u8 D_801839B0[];
extern u8 D_80183AF0[];
extern u8 D_80183B04[];
extern u16 D_80180B60[];
extern s16 D_80183BA8[];
extern s32 D_80183C30;
extern s32 D_80183C38;
extern u8 D_80183C44[];
extern u8 D_80183C60[];
extern u8 D_80183C7C[];
extern u8 D_80183C84[];
extern u8 D_80183C98[];
extern s32 D_80183CAC;
extern s32 D_80183CBC;
extern LayoutEntity* D_801D7110;
extern u16* D_801D7114;
extern s8 D_801D7118;
extern s8 D_801D711C;
extern s32 D_801D7D20;
extern s16 D_801D7D2A;
extern u16 D_801D7D2C;
extern s16 D_801D7D2E;
extern s16 D_801D7D30;
extern s16 D_801D7D32;
extern s16 D_801D7D36;
extern s8 D_801D7D3A;
extern s8 D_801D7D3B;
extern s32 D_801D7D54;
extern s32 D_801D7D58;
extern s16 D_801D7D60;
extern s16 D_801D7D62;
extern s32 D_801D7D64;
extern s32 D_801D7DD0;
extern u16 UNK_Update0[];

extern LayoutEntity* g_pStObjLayout[];
extern PfnEntityUpdate PfnEntityUpdates[];

// *** EntitySoulStealOrb properties START ***

extern u16 D_801826D0[]; // NOTE(sestren): Random angle offsets?
extern u16 D_801826E0[]; // NOTE(sestren): Animation frame properties?
extern u16 D_80182740[];

// *** EntitySoulStealOrb properties END ***