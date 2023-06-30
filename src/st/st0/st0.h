#include "stage.h"

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
} EntityIDs;

extern const char* D_801A7984;
extern const char* D_801A7990;
extern const char* D_801A799C;

extern PfnEntityUpdate PfnEntityUpdates[];
extern bool g_isSecretStairsButtonPressed;
extern bool g_isDraculaFirstFormDefeated;

void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity);
s16 func_801B4C78();
void MoveEntity();
void SetStep(u8);
void EntityExplosion(Entity*);

// *** Initializers ***

extern u16 D_801805E0[]; // Init EntityDracula
extern u16 D_801805EC[]; // Init EntityDraculaFireball
extern u16 D_80180610[]; // Init EntityDraculaMegaFireball
extern u16 D_8018061C[]; // Init EntityDraculaRainAttack

extern u16 D_80180574[];
extern u16 D_8018058C[];
extern u16 D_801805A4[];
extern u16 D_801805BC[];
extern u16 D_801805D4[];
extern u16 D_80180628[];
extern ObjInit2 D_80180638[];
extern s16 D_801808F8[];

// *** EntityDracula properties START ***

extern u8 D_80180914[]; // Animation
extern u8 D_80180924[]; // Animation
extern u8 D_80180934[]; // Animation
extern u8 D_80180944[]; // Animation
extern u8 D_80180954[]; // Animation
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
extern point16 D_80180A58[];
extern s32 D_801C2578;
extern s32 D_801C257C;

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
extern s16 D_801C24D2;
extern u16 D_801C24D4;
extern s16 D_801C24D6;
extern s16 D_801C24D8;
extern s16 D_801C24DA;
extern s16 D_801C24DE;
extern s8 D_801C24E2;
extern s8 D_801C24E3;
extern u16 D_801C2584[];

// *** EntitySoulStealOrb properties START ***

extern u16 D_80181F54[]; // NOTE(sestren): Random angle offsets?
extern u16 D_80181F64[]; // NOTE(sestren): Animation frame properties?
extern u8 D_80181FC4;

// *** EntitySoulStealOrb properties END ***
