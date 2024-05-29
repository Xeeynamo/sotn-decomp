#include "stage.h"

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
    /* 0x28 */ E_BONE_SCIMITAR_HEAD = 0x28,
    /* 0x2A */ E_AXE_KNIGHT_AXE = 0x2A,
    /* 0x31 */ E_SPITTLEBONE = 0x31,
    /* 0x32 */ E_ROTATE_SPITTLEBONE,
    /* 0x33 */ E_SPITTLEBONE_SPIT,
    /* 0x38 */ E_FIRE = 0x38,
    /* 0x41 */ E_SLOGRA_SPEAR = 0x41,
    /* 0x42 */ E_SLOGRA_SPEAR_PROJECTILE = 0x42,
    /* 0x43 */ E_GAIBON = 0x43,
    /* 0x45 */ E_GAIBON_SMALL_FIREBALL = 0x45,
    /* 0x46 */ E_GAIBON_BIG_FIREBALL = 0x46,
} EntityIDs;

void DestroyEntity(Entity* item);
void func_8019B858(void);
void func_801BDD9C(void);
s32 func_801BD720(u16* hitSensors, s16 sensorCount);
s32 GetPlayerCollisionWith(Entity* entity, u16 w, u16 h, u16 flags);
void EntityExplosion(Entity*);
void func_801C33D8(const u32*, s32);
void EntityUnkId14(Entity* entity);
void EntityUnkId15(Entity* entity);
void func_801C4CC0(void);

extern u8 D_8003BE6F[];
extern PfnEntityUpdate PfnEntityUpdates[];
extern const u16 g_InitializeEntityData0[];
extern u16 D_80180BEC[];
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

// *** EntityBoneScimitar properties START ***

extern u16 D_80180C4C[];    // Init
extern s32 D_8018208C;      // Flag for special bone scimitar to appear or not
extern u8 D_80182090[];     // animation: Walking Forward
extern u8 D_801820A0[];     // animation: Walking Backwards
extern u8 D_801820B0[];     // animation: Swing Sword
extern u8 D_801820CC[];     // animation: Jumping
extern u8 D_801820D8[];     // animation: Landing
extern s8 D_801820F4[];     // Skeleton parts array selector
extern s32 D_801820FC[];    // Skeleton parts velocityX
extern s32 D_80182118[];    // Skeleton parts velocityY
extern u16 D_80182134[];    // Skeleton parts posX
extern u16 D_80182144[];    // Skeleton parts posY
extern s8 D_80182154[2][4]; // Skeleton attack timer cycle
extern s32 D_8018215C;
extern s32 D_8018216C;
extern s32 D_80182174;

// *** EntityBoneScimitar properties END ***

extern u16 D_80180C7C[];
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
extern s32 D_80181240;
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
extern s32 D_80181310[];
extern u8 D_80181340[];

// *** EntityGaibon properties END ***

extern u16 D_80180D3C[];
extern u16 D_80180D48[];
extern ObjInit2 D_80180D64[];
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
extern u16 UNK_Invincibility0[];
extern s16 D_80181978[];
extern u16 D_80181D9C[];
extern s32 D_80181DA8[];
extern const u8* D_80181E54[];
extern s32* D_80180EB8;
extern s32 D_80180ED0[];
extern s16 D_80181EDC[];
extern u32 D_80181EEC[];
extern ObjInit2 D_80182014[];

// *** EntityAxeKnight properties START ***

extern u16 D_80180C64[]; // Init
extern s32 D_80182180[];
extern s32 D_80182188[];
extern u8 D_80182210[]; // Animation: Walking
extern u8 D_80182220[]; // Animation: Ducking Throw
extern u8 D_80182244[]; // Animation: Standing Throw
extern u8 D_80182268[]; // Animation: Dying
extern s32 D_80182274[];
extern u8 D_80182284[];

// *** EntityAxeKnight properties END ***

extern s32 D_80182198[];
extern s32 D_8018219A[];

extern u8 D_801822B4[];
extern u16 D_801822D4[];
extern const u8 D_801822E4[];
extern const u8 D_801822EC[];
extern const u8 D_801822FC[];
extern const u8 D_80182320[];
extern const u8 D_80182334[];
extern const u8 D_8018237C[];
extern s32 D_801823C4;

// *** EntitySkeleton properties START ***

typedef enum {
    SKELETON_INIT,
    SKELETON_IDLE,
    SKELETON_WALK_TOWARDS_PLAYER,
    SKELETON_WALK_AWAY_FROM_PLAYER,
    SKELETON_ATTACK,
    SKELETON_JUMP,
    SKELETON_DESTROY
} SKELETON_STEPS;

extern u8 D_801823DC[];  // animation: Walking Forward
extern u8 D_801823EC[];  // animation: Walking Backwards
extern u8 D_801823FC[];  // animation: Throwing bone
extern u8 D_8018240C[];  // animation: Jumping?
extern u8 D_80182418[];  // animation: Jumping?
extern s8 D_80182430[];  // skeleton pieces array selector
extern s32 D_80182438[]; // velocityX
extern s32 D_80182450[]; // velocityY
extern u16 D_80182468[]; // posX
extern u16 D_80182474[]; // posY
extern u8 D_80182480[2][4];
extern s32 D_801824A8;
extern s32 D_801824C0;

// *** EntitySkeleton properties END ***

extern s32 D_801824B8;
extern s32 D_801824C0;
extern s32 D_801824CC;
extern s16 D_801824DC[];
extern u8 D_801824E2[];
extern u16 D_801824E4[];
extern u8 D_80181F30[];
extern u8 D_80180CF4[];
extern s32 D_80182600[];
extern s32 D_8018216C;
extern s32 D_80182174;
extern u16 g_InitializeData0[];
extern u16 D_80180BC8[];
extern u16 D_80181CA8[];
extern u16 D_80181CD8[];
extern u8* D_80181D3C[];
extern u16 D_80180C94[];
extern u16 D_80182424[];
extern u32* D_80181CEC[];
extern s32 c_GoldPrizes[];
extern u16 D_80180CA0[];
extern u32 D_80182488[];
extern u16 D_80180C58[];
extern u16 D_80180C58[];
extern s16 D_801820E4[];
extern u16 D_80180C04[];
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
extern u32 D_801822BC[];
extern u32 D_801822C8[];
extern s32 D_8018238C;
extern s32 D_801823A4;
extern const char D_801B058C[]; // "charal %x\n"
extern const char D_801B0598[]; // "charal %x\n"
extern const char D_801B08C8[]; // "charal %x\n"

extern s16 D_801CB68E;
extern u16 D_801CB690;
extern s16 D_801CB692;
extern s16 D_801CB694;
extern s16 D_801CB696;
extern s16 D_801CB69A;
extern s8 D_801CB69E;
extern s8 D_801CB69F;
extern Primitive* D_801CB6A0[];
extern s32 D_801CB6B8;
extern s32 D_801CB6BC;
extern s32 D_801CB6C0[];
extern u32 D_801CB734;
extern u16 D_801CB736[];

// *** EntitySoulStealOrb properties START ***

extern u16 D_80181F80[]; // NOTE(sestren): Random angle offsets?
extern u16 D_80181F90[]; // NOTE(sestren): Animation frame properties?
extern u8 D_80181FF0;

// *** EntitySoulStealOrb properties END ***

extern Dialogue g_Dialogue;
