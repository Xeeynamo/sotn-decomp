#include "stage.h"

#undef STAGE
#define STAGE STAGE_ST0

#define DISP_ALL_H 240
#define DISP_STAGE_W 256
#define DISP_STAGE_H DISP_ALL_H
#define DISP_UNK2_W 512
#define DISP_UNK2_H DISP_ALL_H

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
    E_DUMMY_09,
    E_EQUIP_ITEM_DROP,
    E_DUMMY_0B,
    E_DUMMY_0C,
    E_DUMMY_0D,
    E_DUMMY_0E,
    E_DUMMY_0F,
    E_DUMMY_10,
    E_ID_26 = 0x26,
    E_SECRET_BUTTON = 0x28,
    E_SECRET_STAIRS = 0x29,
} EntityIDs;

void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity);
s16 GetSideToPlayer();
void MoveEntity();
void SetStep(u8);
void EntityExplosion(Entity*);

extern const char* D_801A7984;
extern const char* D_801A7990;
extern const char* D_801A799C;

extern s8 c_HeartPrizes[10];

extern PfnEntityUpdate PfnEntityUpdates[];
extern bool g_isSecretStairsButtonPressed;
extern bool g_isDraculaFirstFormDefeated;

LayoutObject* D_80180314[];
LayoutObject* D_801803E8[];

// *** Initializers ***
extern u16 D_80180574[];
extern u16 D_8018058C[];
extern u16 D_80180598[]; // Init EntityCutscene
extern u16 D_801805A4[];
extern u16 D_801805BC[];
extern u16 D_801805D4[]; // Init EntityStageTitleCard
extern u16 D_801805E0[]; // Init EntityDracula
extern u16 D_801805EC[]; // Init EntityDraculaFireball
extern u16 D_80180610[]; // Init EntityDraculaMegaFireball
extern u16 D_8018061C[]; // Init EntityDraculaRainAttack
extern u16 D_80180628[];

extern ObjInit2 D_80180638[];

// *** func_801A805C properties START ***

extern s32 D_801806D0[]; // animation
extern u8 D_801806F8[];  // hitboxHeight
extern u8 D_80180704[];  // params
extern u16 D_80180710[]; // palette
extern s16 D_80180724[]; // animSet
extern s16 D_80180738[]; // unk5A
extern s8 D_8018074C[];  // blendMode
extern s16 D_80180758[]; // hitboxOffY
extern u8 D_80180770[];  // params

// *** func_801A805C properties END ***

// *** EntityCutscene properties START ***

extern u8 D_80180830[]; // Animation
extern u8 D_8018083C[]; // Animation
extern u8 D_8018084C[]; // Animation
extern u8 D_8018085C[]; // Animation
extern u8 D_80180864[]; // Animation
extern u8 D_8018086C[]; // Animation
extern u8 D_8018087C[]; // Animation
extern u8 D_80180884[]; // Animation
extern u8 D_8018088C[]; // Animation
extern u8 D_80180894[]; // Animation

// *** EntityCutscene properties END ***

extern Point16 D_801808A0[];
extern u16 D_801808B0[];
extern s16 D_801808F8[];
extern s32 D_80180908;

// *** EntityDracula properties START ***

extern u8 D_80180914[]; // Animation
extern u8 D_80180924[]; // Animation
extern u8 D_80180934[]; // Animation
extern u8 D_80180944[]; // Animation
extern u8 D_80180954[]; // Animation
extern u8 D_80180964[]; // Animation
extern u8 D_8018097C[]; // Animation
extern u8 D_801809A4[]; // Animation
extern u8 D_80180A0C[]; // Animation
extern u8 D_80180A20[]; // Animation
extern u8 D_80180A2C[]; // Animation
extern u8 D_80180BA0[]; // Animation
extern u8 D_80180BB8[]; // Animation
extern u8 D_80180BCC[]; // Animation
extern u8 D_80180BDC[]; // Animation
extern u16 D_80180A48[];
extern Point16 D_80180A58[];
extern LayoutObject* D_801C00A0;
extern u8 D_801C00A8;
extern u8 D_801C00AC;
extern s16 D_801C2508;
extern s16 D_801C250A;
extern s32 D_801C250C;
extern s32 D_801C2578;
extern s32 D_801C257C;
extern u16 D_80181CAC[];
extern u16 D_80181CDC[];
extern u32 D_80181CF0[];

// *** EntityDracula properties END ***

extern s16 D_80181990[];
extern s16 D_801815EC[];
extern u32 D_80181D7C[];
extern u16 D_80181DA4[];
extern u8* D_80181E28[];
extern s16 D_80181E3C[];
extern s16 D_80181E3E[];
extern s16 D_80181EB0[];
extern u32 D_80181EC0[];
extern s32 D_80181ED8[];
extern u8 D_80181EF0[];
extern u16 D_80181EF4[];
extern u16 D_80181F04[];
extern u8 D_801824CC[];
extern u16* D_801C00A4;
extern s32 D_801C24C8;
extern s32 D_801C24CC;
extern Primitive* D_801C24E4[];
extern s32 D_801C24FC;
extern s32 D_801C2500;
extern s32 D_801C2504[];
extern s16 D_801C2508;
extern s16 D_801C24D2;
extern u16 D_801C24D4;
extern s16 D_801C24D6;
extern s16 D_801C24D8;
extern s16 D_801C24DA;
extern s16 D_801C24DE;
extern s8 D_801C24E2;
extern s8 D_801C24E3;
extern s32 D_801C257C;
extern s32 D_801C2580;
extern u16 D_801C2584[];

// *** EntitySoulStealOrb properties START ***

extern u16 D_80181F54[]; // NOTE(sestren): Random angle offsets?
extern u16 D_80181F64[]; // NOTE(sestren): Animation frame properties?
extern u8 D_80181FC4;

// *** EntitySoulStealOrb properties END ***
