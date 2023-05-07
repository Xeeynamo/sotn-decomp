#include "stage.h"

typedef enum { E_AXE_KNIGHT_AXE = 0x2A, E_BONE_SCIMITAR_HEAD = 0x28 } ObjectIds;

void DestroyEntity(Entity*item);
void func_8018F928(Entity*);
void func_8019B858(void);
void func_801BDD9C(void);
s32 func_801BCF74(s32*);
s32 func_801BD720(u16* hitSensors, s16 sensorCount);
s32 func_801BD9A0(Entity*entity, s32 arg1, s32 arg2, s32 arg3);
void EntityExplosion(Entity*);
void func_801C29B0(s32 sfxId); // sfx
void func_801C33D8(const u32*, s32);
void func_801C0B24(Entity*entity);
void func_801C4CC0(void);
void EntityEquipItemDrop(Entity*);

extern u8 D_8003BE6F[];
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
extern u8 D_80182638[];  // Animation: Disassemble
extern u8 D_80182654[];  // Animation: Reassemble
extern u8 D_80182670[];  // Animation: Reassemble faster ?
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
extern u16 D_80180D18[];
extern u16 D_80180D24[];
extern u16 D_80180D30[];
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
extern u8 D_80180F30;
extern u16 D_80180F4C[];
extern const u8 D_80180F50[];
extern const u8 D_80180F74[];
extern u8 D_80180F88[];
extern u16 D_80180F9C[];
extern u32 g_randomNext;
extern s8 c_HeartPrizes[];
extern Entity*g_CurrentEntity;
extern s32 D_80181010;
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
extern u8 D_80181DD0;
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
extern LayoutObject* D_801CAA78;
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
extern const u8 D_80181F30;
extern const u16* D_80180CF4;
extern s32 D_80182600[];
extern s32 D_8018216C;
extern s32 D_80182174;
extern u16 D_80180BD4[];
extern u16 D_80181CD8[];
extern u8* D_80181D3C[];
extern const u16 D_80180C94[];
extern u16 D_80182424[];
extern const u32* D_80181CEC[];
extern const s32 c_GoldPrizes[];
extern const u16 D_80180CA0[];
extern u32 D_80182488[];
extern const u16 D_80180C58[];
extern s16 D_801820E4[];
extern const u16 D_80180C04[];
extern s32 D_80182504[];
extern u8 D_80182524;

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
    u16 subId;
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

extern s32 D_801825CC[]; // SubWeapons subId table
extern u8 D_801825F0;
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
extern s16 D_801CB6C4;
extern s16 D_801CB6C6;
extern s32 D_801CB6C8;
extern s32 D_801CB734;
extern u16 D_801CB736[];
extern u16 D_801CB740[];