// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define OVL_EXPORT(x) NZ0_##x

#define CASTLE_FLAG_BANK 0x7E

typedef enum {
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

    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_ID_15,
    /* 0x16 */ E_PURPLE_BRICK_BG,
    /* 0x17 */ E_LEFT_SECRET_WALL,
    /* 0x18 */ E_BOTT_SECRET_FLOOR,
    /* 0x19 */ E_BP_FLOOR_BUTTON,
    /* 0x1A */ E_BP_SPIKES,
    /* 0x1B */ E_MOVABLE_BOX,
    /* 0x1C */ E_CANNON_LEVER,
    /* 0x1D */ E_CANNON,
    /* 0x1E */ E_CANNON_SHOT,
    /* 0x1F */ E_CANNON_WALL,
    /* 0x20 */ E_BLOOD_SKEL_ELEV_BUTTON,
    /* 0x21 */ E_ELEVATOR_2,
    /* 0x22 */ E_WALL_DEBRIS,
    /* 0x23 */ E_RED_EYE_BUST,
    /* 0x24 */ E_FLOOR_BUTTON,
    /* 0x25 */ E_FLOOR_SPIKES,
    /* 0x26 */ E_BLOOD_SKELETON,
    /* 0x27 */ E_BONE_SCIMITAR,
    /* 0x28 */ E_BONE_SCIMITAR_HEAD,
    /* 0x29 */ E_AXE_KNIGHT,
    /* 0x2A */ E_AXE_KNIGHT_AXE,
    /* 0x2B */ E_BLOODY_ZOMBIE,
    /* 0x2C */ E_func_801C5D20,
    /* 0x2D */ E_BLOOD_SPLATTER,
    /* 0x2E */ E_SKELETON,
    /* 0x2F */ E_SKELETON_THROWN_BONE,
    /* 0x30 */ E_SKELETON_PIECES,
    /* 0x31 */ E_SPITTLEBONE = 0x31,
    /* 0x32 */ E_ROTATE_SPITTLEBONE,
    /* 0x33 */ E_SPITTLEBONE_SPIT,
    /* 0x34 */ E_GLOBE_TABLE,
    /* 0x35 */ E_LIFE_MAX_TANK,
    /* 0x36 */ E_BLUE_FLAME_TABLE,
    /* 0x37 */ E_RELIC_CONTAINER,
    /* 0x38 */ E_WARG_EXP_OPAQUE,
    /* 0x39 */ E_SUBWPN_CONTAINER,
    /* 0x3A */ E_func_801C7538,
    /* 0x3B */ E_func_801C7654,
    /* 0x3C */ E_func_801C77B8,
    /* 0x3D */ E_func_801C7884,
    /* 0x3E */ E_BOSS_FIGHT_MANAGER,
    /* 0x3F */ E_BOSS_ROOM_BLOCK,
    /* 0x40 */ E_SLOGRA,
    /* 0x41 */ E_SLOGRA_SPEAR,
    /* 0x42 */ E_SLOGRA_SPEAR_PROJECTILE,
    /* 0x43 */ E_GAIBON,
    /* 0x45 */ E_GAIBON_SMALL_FIREBALL = 0x45,
    /* 0x46 */ E_GAIBON_BIG_FIREBALL,
    /* 0x49 */ E_LIFE_UP_SPAWN = 0x49
} EntityIDs;

#define BOSS_FLAG_DOORS_CLOSED (1 << 0)
#define BOSS_FLAG_DOORS_OPEN (1 << 1)
#define BOSS_FLAG_FIGHT_BEGIN (1 << 2)
#define BOSS_FLAG_GAIBON_DEAD (1 << 3)
#define BOSS_FLAG_SLOGRA_DEAD (1 << 4)

void DestroyEntity(Entity* item);
void func_8019B858(void);
void func_801BDD9C(void);
s32 UnkCollisionFunc(u16* hitSensors, s16 sensorCount);
s32 GetPlayerCollisionWith(Entity* entity, u16 w, u16 h, u16 flags);
void EntityExplosion(Entity*);
void func_801C33D8(const u32*, s32);
void EntityUnkId14(Entity* entity);
void EntityUnkId15(Entity* entity);
void func_801C4CC0(void);

extern u8 D_8003BE6F[];
extern PfnEntityUpdate PfnEntityUpdates[];
extern u16 g_InitializeEntityData0[];
extern u16 g_EInitGeneric[]; // Init Elevator2
extern u16 g_eInitGeneric2[];
extern u16 D_80180C34[];

// *** EntityBloodSkeleton properties START ***

extern u16 D_80180C40[]; // InitProps
extern u8 D_80182610[];  // Animation: Walking?
extern s16 D_80182624[];
extern u8 D_80182638[]; // Animation: Disassemble
extern u8 D_80182654[]; // Animation: Reassemble
extern u8 D_80182670[]; // Animation: Reassemble faster ?
extern s32 D_80182694;
extern s32 D_801826AC;

// *** EntityBloodSkeleton properties END ***

extern u16 D_80180C88[];
extern u16 D_80180CAC[];
extern u16 D_80180CC4[];
extern s16 D_80180CE8[];
extern u16 D_80180D00[];

// *** EntitySlogra properties START ***

extern u16 D_80180D0C[]; // Init
extern u16 D_8018105C[];
extern s32 D_8018106C;
extern u8 D_80181074[]; // Animation
extern u8 D_80181080[]; // Animation: Taunt
extern u8 D_8018108C[]; // Animation: Firing projectiles
extern u8 D_8018109C[]; // Animation
extern u8 D_801810A8[]; // Animation
extern u8 D_801810B4[]; // Animation
extern u8 D_801810D4[]; // Animation
extern u8 D_801810E8[]; // Animation
extern u8 D_801810FC[]; // Animation
extern u8 D_80181108[]; // Animation
extern u8 D_80181114[]; // Animation
extern u8 D_80181128[]; // Animation
extern u8 D_80181140[]; // Animation
extern u8 D_80181150[]; // Animation
extern u8 D_80181158[]; // Animation
extern s32 D_80181178[];
extern u8 D_801811B8[];

// *** EntitySlogra properties END ***

extern u16 D_80180D18[];
extern u16 D_80180D24[];

// *** EntityGaibon properties START ***

extern u16 D_80180D30[];
extern u16 D_80180D36;
extern u16 D_80181240[];
extern u8 D_80181250[];
extern u8 D_80181264[];
extern u8 D_80181298[];
extern u8 D_801812AC[];
extern u8 D_801812C0[];
extern u8 D_801812CC[];
extern u8 D_801812DC[];
extern u8 D_801812F0[];
extern u8 D_801812FC[];
extern u8 D_80181304[];
extern s8 D_80181310[];
extern u8 D_80181340[];
extern u16 D_80180D30[];

// *** EntityGaibon properties END ***

extern u16 D_80180D3C[];
extern u16 D_80180D48[];
extern ObjInit D_80180D64[];
extern s32 D_80180E04[];
extern u8 D_80180E24[];
extern u8 D_80180E2C[];
extern s16 D_80180E34[];
extern s8 D_80180E44[];
extern u16* D_80180E54;
extern u16* D_80180E94;
extern s32 D_80180EB4;
extern u16 D_80180ED4[];
extern u16 D_80180EE0[];
extern bool g_CallElevator;
extern const u8 D_80180EF0[];
extern const u8 D_80180EF8[];
extern u16 D_80180F10[];
extern const u8 D_80180F1C[];
extern u8 D_80180F30[];
extern u16 D_80180F4C[];
extern const u8 D_80180F50[];
extern const u8 D_80180F74[];
extern u8 D_80180F88[];
extern u16 D_80180F9C[];
extern Unkstruct_80180FE0 D_80180FE0[];
extern s16 D_80181014[];
extern u32 g_randomNext;
extern s8 c_HeartPrizes[];
extern Entity* g_CurrentEntity;
extern s32 g_BossFlag; // original names: boss_flag / beri_flag
extern const u8 D_80181160[];
extern const u8 D_80181170[];
extern s8 D_801811E0[];
extern u8 D_80181218[];
extern const u8 D_8018136C[];
extern const u8 D_80181378[];
extern const u8 D_80181388[];
extern s32 g_ElevatorTarget;
extern s16 g_ElevatorTargetPos[];
extern u16 D_801813B0[];
extern const char* D_8018146C[];
extern s16 D_80181978[];
extern u16 D_80181D9C[];
extern s32 D_80181DA8[];
extern const u8* D_80181E54[];
extern s32* D_80180EB8;
extern s32 D_80180ED0[];
extern s16 D_80181EDC[];
extern u32 D_80181EEC[];
extern ObjInit D_80182014[];

extern s32 D_801824CC;
extern s16 D_801824DC[];
extern u8 D_801824E2[];
extern u16 D_801824E4[];
extern u8 D_80181F30[];
extern u8 D_80180CF4[];
extern s32 D_80182600[];
extern u16 g_InitializeData0[];
extern u16 D_80180BC8[];
extern u16 D_80181CA8[];
extern u16 D_80181CD8[];
extern u8* g_SubweaponAnimPrizeDrop[];
extern u16 D_80180C94[];
extern u16 D_80180CA0[];
extern s32 D_80182504[];
extern u8 D_80182524[];

// *** EntitySubWeaponContainer properties START ***

#define ENTITY_SUBWPNCONT_DEBRIS_COUNT 9
typedef enum {
    SUBWPNCONT_INIT,
    SUBWPNCONT_IDLE,
    SUBWPNCONT_BREAK,
    SUBWPNCONT_DEBUG = 255
} SUBWPNCONT_STEPS;

typedef struct SubWpnContDebris {
    u16 posX;
    u16 posY;
    u16 params;
    u16 facingLeft;
} SubWpnContDebris;

extern SubWpnContDebris D_80182584[ENTITY_SUBWPNCONT_DEBRIS_COUNT];

// *** EntitySubWeaponContainer properties END ***

// *** EntityLeftSecretRoomWall properties START ***

typedef enum {
    LEFT_SECRET_ROOM_WALL_INIT,
    LEFT_SECRET_ROOM_WALL_IDLE,
    LEFT_SECRET_ROOM_WALL_BREAK,
    LEFT_SECRET_ROOM_WALL_CHECK
} LEFT_SECRET_ROOM_WALL_STEPS;

// *** EntityLeftSecretRoomWall properties END ***

// *** EntityBottomSecretRoomFloor properties START ***

typedef enum {
    BOTTOM_SECRET_ROOM_FLOOR_INIT,
    BOTTOM_SECRET_ROOM_FLOOR_IDLE,
    BOTTOM_SECRET_ROOM_FLOOR_BREAK,
    BOTTOM_SECRET_ROOM_FLOOR_CHECK
} BOTTOM_SECRET_ROOM_FLOOR_STEPS;

// *** EntityBottomSecretRoomFloor properties END ***

// *** EntitySpittleBoneSpit properties START ***

extern u16 D_80180CB8[]; // Init
extern u8 D_80182534[];  // animation:
extern u8 D_8018253C[];
extern u8 D_80182540[];

// *** EntitySpittleBoneSpit properties END ***

extern s32 D_801825CC[]; // SubWeapons params table
extern u8 D_801825F0[];
extern u16 D_80180C70[];
extern u16 D_80180CD0[];
extern u16 D_80180CDC[];
extern const char D_801B058C[]; // "charal %x\n"
extern const char D_801B0598[]; // "charal %x\n"
extern const char D_801B08C8[]; // "charal %x\n"

extern Primitive* D_801CB6A0[];
extern s32 D_801CB6B8;
extern s32 D_801CB6BC;
extern s32 D_801CB6C0[];
extern u16 D_801CB736[];

// *** EntitySoulStealOrb properties START ***

extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u8 g_ESoulStealOrbAnim[];

// *** EntitySoulStealOrb properties END ***

extern Dialogue g_Dialogue;
// For EntityLifeUpSpawn
extern u16 D_80182850[];
extern SVECTOR D_8018287C;
extern SVECTOR D_80182830;
extern SVECTOR D_80182838;
extern SVECTOR D_80182840;
extern SVECTOR D_80182848;

// For EntityMariaCutscene
extern s32 D_801CB684;
extern s32 D_801CB73C;
extern u8 D_801813C8[];
extern u8 D_801813CC[];
extern u16 D_801813D0[];
extern u16 D_801813D4[];
extern u16 D_801813D8[];
extern s16 D_801813DC[];
extern const char D_80183B0C[];
extern u32 g_mariaCutsceneFlags;

// EntityMaria, mostly animations
extern u16 g_MariaInit[];
extern u8 D_80181474[];
extern u8 D_80181490[];
extern u8 D_801814A0[];
extern u8 D_801814BC[];
extern u8 D_801814C8[];
extern u8 D_801814E8[];
extern u8 D_801814F8[];
extern u8 D_80181510[];
extern u8 D_8018151C[];
extern u8 D_80181530[];
extern u8 D_80181538[];

// for func_801C4198
extern u16 D_80180C6A;

// for EntityMagicallySealedDoor
extern u8 g_eBlueDoorUV[3][8];
extern u16 g_eBlueDoorTiles[2][8];
extern char D_80182710[];

// for func_801B0AA4
extern u16 D_80180C10;
extern u8 D_80180DBC[];
extern u8 D_80180DC0[];
extern u16 D_80180DC4[];
