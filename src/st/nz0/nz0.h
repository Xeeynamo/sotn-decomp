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

void DestroyEntity(Entity* item);
void func_8018F928(Entity*);
void func_8019B858(void);
void func_801BDD9C(void);
s32 func_801BCF74(s32*);
s32 func_801BD720(u16* hitSensors, s16 sensorCount);
s32 func_801BD9A0(Entity* entity, s32 arg1, s32 arg2, s32 arg3);
void EntityExplosion(Entity*);
void func_801C29B0(s32 sfxId); // sfx
void func_801C33D8(const u32*, s32);
void func_801C0B24(Entity* entity);
void func_801C4CC0(void);

extern u8 D_8003BE6F[];
LayoutObject* D_801808EC[];
LayoutObject* D_801809C0[];
extern PfnEntityUpdate D_80180A90[];
extern const u16 D_80180BE0[];
extern u16 D_80180BEC[];
extern u16 D_80180BF8[];
extern u16 D_80180C1C[];
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
extern s32 D_801820FC[];    // Skeleton parts accelerationX
extern s32 D_80182118[];    // Skeleton parts accelerationY
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
extern u16* D_80180E54;
extern u16* D_80180E94;
extern s32 D_80180EB4;
extern u16 D_80180ED4[];
extern u16 D_80180EE0[];
extern s32 D_80180EEC;
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
extern s32 D_801813A4;
extern u16 D_801813B0[];
extern u16 D_80181574[];
extern s16 D_80181978[];
extern u16 D_80181D9C[];
extern s32 D_80181DA8[];
extern u8 D_80181DD0[];
extern u8 D_80181DD0[];
extern const u8* D_80181E54[];
extern u8 D_80181F1C[];
extern s32 D_80181F04[];
extern u16 D_80181F20[];
extern s16* D_80181F28;
extern s32* D_80180EB8;
extern s32 D_80180ED0[];
extern s16 D_80181EDC[];
extern u32 D_80181EEC[];
extern ObjInit2 D_80182014[];
extern LayoutObject* D_801CAA74;
extern u16* D_801CAA78;
extern u8 D_801CAA7C;
extern u8 D_801CAA80;

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
extern s32 D_80182438[]; // accelerationX
extern s32 D_80182450[]; // accelerationY
extern u16 D_80182468[]; // posX
extern u16 D_80182474[]; // posY
extern u8 D_80182480[2][4];
extern s32 D_801824A8;
extern s32 D_801824C0;

// *** EntitySkeleton properties END ***

extern s32 D_801824B8;
extern s32 D_801824C0;
extern s32 D_801824CC;
extern u8 D_801824E2[];
extern u8 D_80181F30[];
extern u8 D_80180CF4[];
extern s32 D_80182600[];
extern s32 D_8018216C;
extern s32 D_80182174;
extern u16 D_80180BD4[];
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
    u16 facing;
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
extern s32 D_801CB688;
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
extern s16 D_801CB6C4;
extern s16 D_801CB6C6;
extern s32 D_801CB6C8;
extern s32 D_801CB734;
extern u16 D_801CB736[];
extern u16 D_801CB740[];

// *** EntitySoulStealOrb properties START ***

extern u16 D_80181F80[]; // NOTE(sestren): Random angle offsets?
extern u16 D_80181F90[]; // NOTE(sestren): Animation frame properties?
extern u8 D_80181FF0;

// *** EntitySoulStealOrb properties END ***
