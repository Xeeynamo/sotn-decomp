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
    E_ABSORB_ORB,
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
void func_801B5794(u8);
void EntityExplosion(Entity*);

extern u16 D_80180574[];
extern u16 D_8018058C[];
extern u16 D_801805A4[];
extern u16 D_801805BC[];
extern u16 D_801805D4[];
extern ObjInit2 D_80180638[];
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
extern s16 D_801C24D2;
extern u16 D_801C24D4;
extern s16 D_801C24D6;
extern s16 D_801C24D8;
extern s16 D_801C24DA;
extern s16 D_801C24DE;
extern s8 D_801C24E2;
extern s8 D_801C24E3;
extern u16 D_801C2584[];
