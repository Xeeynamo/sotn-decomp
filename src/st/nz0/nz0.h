// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_NZ0

#define OVL_EXPORT(x) NZ0_##x

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
    /* 0x0E */ E_MESSAGE_BOX,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,
    /* 0x11 */ E_BACKGROUND_BLOCK,
    /* 0x12 */ E_LOCK_CAMERA,
    /* 0x13 */ E_UNK_ID13,
    /* 0x14 */ E_EXPLOSION_VARIANTS,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ E_PURPLE_BRICK_BG,         // func_pspeu_09237BA0
    /* 0x17 */ E_LEFT_SECRET_WALL,        // func_pspeu_0923C450
    /* 0x18 */ E_BOTT_SECRET_FLOOR,       // func_pspeu_0923C7C0
    /* 0x19 */ E_BP_FLOOR_BUTTON,         // func_pspeu_0923B1F0
    /* 0x1A */ E_BP_SPIKES,               // func_pspeu_0923B4D0
    /* 0x1B */ E_MOVABLE_BOX,             // func_pspeu_0923B860
    /* 0x1C */ E_CANNON_LEVER,            // func_pspeu_09237E20
    /* 0x1D */ E_CANNON,                  // func_pspeu_092380B0
    /* 0x1E */ E_CANNON_SHOT,             // func_pspeu_09238420
    /* 0x1F */ E_CANNON_WALL,             // func_pspeu_09238560
    /* 0x20 */ E_BLOOD_SKEL_ELEV_BUTTON,  // func_pspeu_09239D38
    /* 0x21 */ E_ELEVATOR_2,              // func_pspeu_0923A048
    /* 0x22 */ E_WALL_DEBRIS,             // func_pspeu_0923CAA0
    /* 0x23 */ E_RED_EYE_BUST,            // func_pspeu_0923A7A0
    /* 0x24 */ E_FLOOR_BUTTON,            // func_pspeu_0923BBE8
    /* 0x25 */ E_FLOOR_SPIKES,            // func_pspeu_0923BF70
    /* 0x26 */ E_BLOOD_SKELETON,          // func_pspeu_09252590
    /* 0x27 */ E_BONE_SCIMITAR,           // func_pspeu_09251348
    /* 0x28 */ E_BONE_SCIMITAR_PARTS,     // func_pspeu_09251D18
    /* 0x29 */ E_AXE_KNIGHT,              // func_pspeu_092427E0
    /* 0x2A */ E_AXE_KNIGHT_AXE,          // func_pspeu_09243338
    /* 0x2B */ E_BLOODY_ZOMBIE,           // func_pspeu_09243D18
    /* 0x2C */ E_BLOOD_DRIPS,             // func_pspeu_09244730
    /* 0x2D */ E_BLOOD_SPLATTER,          // func_pspeu_09243540
    /* 0x2E */ E_SKELETON,                // func_pspeu_09252B68
    /* 0x2F */ E_SKELETON_THROWN_BONE,    // func_pspeu_09253330
    /* 0x30 */ E_SKELETON_PIECES,         // func_pspeu_09253208
    /* 0x31 */ E_SPITTLEBONE,             // func_pspeu_0924F040
    /* 0x32 */ E_ROTATE_SPITTLEBONE,      // func_pspeu_0924F5B0
    /* 0x33 */ E_SPITTLEBONE_SPIT,        // func_pspeu_0924F7D0
    /* 0x34 */ E_GLOBE_TABLE,             // func_pspeu_0923C300
    /* 0x35 */ E_LIFE_MAX_TANK,           // func_pspeu_0923A9D0
    /* 0x36 */ E_BLUE_FLAME_TABLE,        // func_pspeu_09239BD0
    /* 0x37 */ E_RELIC_CONTAINER,         // func_pspeu_09239858
    /* 0x38 */ E_EXPLODE_PUFF_OPAQUE,     // func_pspeu_0923AC80
    /* 0x39 */ E_SUBWPN_CONTAINER,        // func_pspeu_09253478
    /* 0x3A */ E_FALLING_GLASS,           // func_pspeu_09253A58
    /* 0x3B */ E_FALLING_LIQUID,          // func_pspeu_09253BE8
    /* 0x3C */ E_LIQUID_BUBBLES,          // func_pspeu_09253DC0
    /* 0x3D */ E_func_801C7884,           // func_pspeu_09253EE0
    /* 0x3E */ E_BOSS_FIGHT_MANAGER,      // func_pspeu_09238700
    /* 0x3F */ E_BOSS_ROOM_BLOCK,         // func_pspeu_09238D50
    /* 0x40 */ E_SLOGRA,                  // func_pspeu_09259230
    /* 0x41 */ E_SLOGRA_SPEAR,            // func_pspeu_0925A420
    /* 0x42 */ E_SLOGRA_SPEAR_PROJECTILE, // func_pspeu_0925A668
    /* 0x43 */ E_GAIBON,                  // func_pspeu_09256FF8
    /* 0x44 */ E_GAIBON_UNK0,             // func_pspeu_09258B68
    /* 0x45 */ E_GAIBON_SMALL_FIREBALL,   // func_pspeu_09258C98
    /* 0x46 */ E_GAIBON_BIG_FIREBALL,     // func_pspeu_09258E00
    /* 0x47 */ E_UNK47,                   // func_pspeu_09239250
    /* 0x48 */ E_UNK48,                   // func_pspeu_09238F48
    /* 0x49 */ E_LIFE_UP_SPAWN,           // func_pspeu_09255978
    /* 0x4A */ E_UNK4A,                   // func_pspeu_0924FE70
    /* 0x4B */ E_UNK4B,                   // func_pspeu_0923E810
    /* 0x4C */ E_UNK4C,                   // func_pspeu_0925A980
    /* 0x4D */ E_UNK4D,                   // func_pspeu_0925A7B8
    NUM_ENTITIES,
} EntityIDs;

#ifdef VERSION_PSP
extern s32 E_ID(EXPLOSION);
extern s32 E_ID(CANNON_SHOT);
extern s32 E_ID(WALL_DEBRIS);
#endif

#define BOSS_FLAG_DOORS_CLOSED (1 << 0)
#define BOSS_FLAG_DOORS_OPEN (1 << 1)
#define BOSS_FLAG_FIGHT_BEGIN (1 << 2)
#define BOSS_FLAG_GAIBON_DEAD (1 << 3)
#define BOSS_FLAG_SLOGRA_DEAD (1 << 4)

#define PAL_PUFF_OPAQUE_OFFSET 0x2E0

void DestroyEntity(Entity* item);
void func_8019B858(void);
void func_801BDD9C(void);
s32 UnkCollisionFunc(s16* hitSensors, s16 sensorCount);
s32 GetPlayerCollisionWith(Entity* entity, u16 w, u16 h, u16 flags);
void EntityExplosion(Entity*);
void func_801C33D8(const u32*, s32);
void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);
void func_801C4CC0(void);

extern EInit g_EInitBloodyZombie;

extern EInit g_EInitParticle;
extern EInit g_EInitInteractable; // Init Elevator2
extern EInit g_EInitCommon;
extern EInit g_EInitEnemy3;

// *** EntityBloodSkeleton properties START ***

extern EInit g_EInitBloodSkeleton;

// *** EntityBloodSkeleton properties END ***

extern EInit g_EInitSkeleton;
extern EInit g_EInitSpittleBone;
extern EInit g_EInitTableWithGlobe;
extern EInit g_EInitSubwpnCloche;
extern EInit g_EInitBossDoor;

// *** EntitySlogra properties START ***

extern EInit g_EInitSlogra; // Init
extern s16 D_8018105C[];
extern s16 D_8018106C[];
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
extern u8 D_80181160[];
extern u8 D_80181170[];
extern u8 D_80181178[][4];
extern u8 D_801811B8[];
extern s8 D_801811E0[][4];
extern u8 D_80181218[];

// *** EntitySlogra properties END ***

extern EInit g_EInitSlograSpear;
extern EInit g_EInitSlograProjectile;

// *** EntityGaibon properties START ***

extern EInit g_EInitGaibon;
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

// *** EntityGaibon properties END ***

extern EInit g_EInitGaibonProjectile;
extern EInit g_EInitGaibonLargeProjectile;
extern s32 D_80180E04[];
extern u8 D_80180E24[];
extern u8 D_80180E2C[];
extern s16 D_80180E34[];
extern s8 D_80180E44[];
extern u32 g_randomNext;
extern s8 c_HeartPrizes[];
extern Entity* g_CurrentEntity;
extern s32 g_BossFlag; // original names: boss_flag / beri_flag
extern u8 D_8018136C[];
extern u8 D_80181378[];
extern u8 D_80181388[];
extern s16 D_80181978[];
extern u16 D_80181D9C[];
extern s32 D_80181DA8[];
extern const u8* D_80181E54[];
extern s16 D_80181EDC[];
extern u32 D_80181EEC[];
extern ObjInit D_80182014[];

extern u8 D_80181F30[];
extern EInit g_EInitSubwpnClochePieces;
extern EInit g_EInitObtainable;
extern u16 D_80180BC8[];
extern u16 D_80181CA8[];
extern u16 D_80181CD8[];
extern u8* g_SubweaponAnimPrizeDrop[];

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

extern EInit g_EInitSpittleBoneSpit;

// *** EntitySpittleBoneSpit properties END ***

extern EInit g_EInitAxeKnight;
extern EInit g_EInitAxeKnightAxe;
extern EInit g_EInitLifeMaxTank;
extern EInit g_EInitPrizeContainer;
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

// For EntityLifeUpSpawn
extern u16 D_80182850[];
extern SVECTOR D_8018287C;
extern SVECTOR D_80182830;
extern SVECTOR D_80182838;
extern SVECTOR D_80182840;
extern SVECTOR D_80182848;

// EntityMaria, mostly animations
extern EInit g_EInitSpawner;
