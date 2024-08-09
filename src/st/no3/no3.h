#include "stage.h"

#define OVL_EXPORT(x) NO3_##x

#define CASTLE_FLAG_BANK 0x34

// NO3 Sound IDs
#define SE_SKEL_SWORD_SWING 0x66D
#define SE_LEVER_SWITCH_MOVE 0x675
#define SE_FLOOR_SWITCH_CLICK 0x676
// #define 0x684
#define SE_OWL_WING_FLAP 0x68C
#define SE_WARG_DEATH_EXPLODE 0x697
#define SE_BAT_DEATH 0x69C
#define SE_DEATH_SWIPES 0x6A2
// #define 0x6C7
#define SE_NO3_ALUCARD_JUMP 0x6EF
#define SE_MERMAN_DEATH 0x71D
#define SE_WARG_DEATH_HOWL 0x780
#define SE_WARG_PAIN 0x781
#define SE_WARG_ATTACK 0x782
#define SE_WARG_GROWL 0x783
#define SE_NO3_WINDOW_CLOSE 0x79D
#define SE_VO_DEATH_STEALS 0x7A0
#define SE_VO_DEATH_LAUGH 0x7A1
#define SE_ITEM_YOINK 0x7A2
#define SE_TREE_BRANCH 0x7A4
#define SE_CASTLE_GATE_MOVE 0x7A5
#define SE_WATER_SPLASH 0x7C2

void EntityUnkId14(Entity* entity);
void EntityUnkId15(Entity* entity);

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
    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_ID_15 = 0x15,
    /* 0x17 */ E_BG_LIGHTNING = 0x17,
    /* 0x27 */ E_FALLING_ROCK_2 = 0x27,
    /* 0x35 */ E_SPLASH_WATER = 0x35,
    /* 0x36 */ E_SURFACING_WATER,
    /* 0x37 */ E_SIDE_WATER_SPLASH,
    /* 0x38 */ E_SMALL_WATER_DROP,
    /* 0x39 */ E_WATER_DROP,
    /* 0x3D */ E_MEDIUM_WATER_SPLASH = 0x3D,
    /* 0x59 */ E_ID_59 = 0x59,
    /* 0x5B */ E_ID_5B = 0x5B,
    /* 0x5D */ E_FALLING_ROCK = 0x5D,
    /* 0x5E */ E_ID_5E,
    /* 0x62 */ E_ID_62 = 0x62,
} EntityIDs;

extern void CreateEntityFromCurrentEntity(u16, Entity*);
extern void ReplaceBreakableWithItemDrop(Entity*);
extern s32 GetPlayerCollisionWith(Entity* entity, u16 w, u16 h, u16 flags);
extern Primitive* FindFirstUnkPrim(Primitive* poly);

extern u16 g_InitializeData0[];
extern u16 g_InitializeEntityData0[];
extern s16 D_80182A38[];
extern u8 D_80182A48[];
extern u16 D_80180AD0[];
extern u16 g_EInitGeneric[];
extern u16 D_80180AF4[];
extern u16 g_eInitGeneric2[];
extern u16 D_80180B18[];
extern u16 D_80180B48[];
extern u16 D_80180B54[];
extern u16 D_80180B6C[];
extern u16 D_80180B84[];
extern u16 D_80180B90[];
extern u16 D_80180BA8[];
extern ObjInit2 D_80180BFC[];
extern u8 D_80180DC0[];
extern u8 D_80180DC8[];
extern u16 D_80180DD0[];
extern SVEC4 D_80181024[];
extern SVEC4 D_801810A4;
extern MATRIX D_801810D4;
extern SVECTOR* D_8018110C;
extern u8 D_80181118[];
extern u16 D_80181120[];
extern u16 D_80181130[8];
extern s16 D_801811D0[][2];
extern s16 D_801811E0[];
extern SVECTOR D_801811F0[];
extern u8 D_801811F8;
extern u8 D_80181218[];
extern u8 D_80181224[];
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
extern u16 D_801813A8;
extern u16 D_801813AA;
extern u16 D_801813AC[];
extern u16 D_801813AA;
extern u16 D_801813AC[];
extern Point16 D_801813DC[];
extern Point16 D_80181468[];
extern u16 D_801814EC[];
extern u16 D_801817F8[];
extern u8 D_801819D0[];
extern u8 D_801819DC[];
extern s32 D_801819E8[];
extern s32 D_801819EC[];
extern const char* D_80181ACC[];
extern s16 D_80181AD4[];
extern s16 D_80181AE0[];
extern Point16 D_80181AEC[];

// *** EntityDeath Animations *** //
extern u8 D_80181B04[];
extern u8 D_80181B28[];
extern u8 D_80181B34[];
extern u8 D_80181B58[];
extern u8 D_80181B68[];
extern u8 D_80181B70[];
extern u8 D_80181B74[];
extern u8 D_80181B84[];
extern u8 D_80181B8C[];
extern u8 D_80181B94[];
extern u8 D_80181BB4[];
extern u8 D_80181BC8[];
extern u8 D_80181BE0[];

extern u8 D_80181B40[];
extern u8 D_80181B4C[];
extern Unkstruct_80180FE0 D_80181C5C[];
extern u16 D_80181C8C[];
extern s16 D_801820C4[];
extern s16 D_801832D8[];
extern u8 D_801832E8[];
extern u16 D_801823F4[];
extern u16 D_80182424[];
extern u8* D_80182488[];
extern u16 D_801824E8[];
extern s8 c_HeartPrizes[];
extern s32 D_801824F4[];
extern u8* D_801825A0[];
extern u16 D_80182628[];
extern s32 D_80182638[];
extern u8 D_8018267C[];
extern ObjInit2 D_80182764[];
extern u8 D_8018383C[];
extern s32 D_801838F4[];
extern s16 D_80183858[];
extern Point32 D_80183878[];
extern s16 D_80183898[];
extern s64 D_801838A4[];
extern u8 D_801838E4[];
extern s16 D_80183858[];
extern Point32 D_80183878[];
extern s16 D_80183858[];
extern s16 D_80183898[];
extern s16 D_80183858[];
extern s16 D_80183898[];
extern u8 D_80183994[];
extern const u8 D_801839A0[];
extern u8 D_801839A8[];
extern u8 D_801839B0[];
extern Point32 D_801839C0[];
extern u16 D_801839E8[];
extern u8 D_801839F4[];
extern u16 D_801839FC[];
extern s32 D_80183A0C[];
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
extern s32 D_801D7D20;
extern s32 D_801D7D54;
extern s32 D_801D7D58;
extern u32 D_801D7DD0;

extern PfnEntityUpdate PfnEntityUpdates[];

// *** EntitySoulStealOrb properties START ***

extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u8 g_ESoulStealOrbAnim[];

// *** EntitySoulStealOrb properties END ***

extern SVECTOR D_801B73E0;

// For EntityDeathCutscene
extern u8 D_80181A28[];
extern u8 D_80181A2C[];
extern u16 D_80181A30[];
extern u16 D_80181A34[];
extern u16 D_80181A38[];
extern s16 D_80181A3C[];
extern const char D_801813F0[];
extern s32 D_801D7D20;
extern u32 D_801D7DD0;
extern s32 D_801D7DD4;
extern u16 D_801D7D60;
extern const char D_80184CE0[];
extern s32 D_801D7D5C;

extern Dialogue g_Dialogue;
