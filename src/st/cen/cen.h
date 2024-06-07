#ifndef CEN_H
#define CEN_H

#include "common.h"
#include "stage.h"

#define CASTLE_FLAG_BANK 0x00

// CEN Sound IDs
#define SE_CEN_ELEVATOR_MOVE 0x60D
#define SE_CEN_PLATFORM_STOP 0x64F
#define SE_CEN_ELEVATOR_DOOR 0X675

typedef enum {
    E_SHARED_END = E_DUMMY_10,
    /* 0x11 */ E_BACKGROUND_BLOCK,
    /* 0x12 */ E_ID_12,
    /* 0x13 */ E_ID_13,
    /* 0x14 */ E_ID_14,
    /* 0x15 */ E_ID_15,
    /* 0x16 */ E_ID_16,
    /* 0x17 */ E_PLATFORM,
    /* 0x18 */ E_MARIA,
    /* 0x19 */ E_ROOM_DARKNESS,
    /* 0x1A */ E_ELEVATOR_STATIONARY,
    /* 0x1B */ E_ID_1B,
    /* 0x1C */ E_MOVING_ELEVATOR,
} EntityIDs;

void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity);
void CreateEntityFromLayout(Entity*, LayoutEntity*);
extern u16 GetNormalizedAngle(u16 arg0, u16 arg1, u16 arg2);
void EntityUnkId14(Entity* entity);
void EntityUnkId15(Entity* entity);

extern PfnEntityUpdate PfnEntityUpdates[];

/*** Initializers ***/
extern u16 D_80180404[];
extern u16 g_InitializeData0[];
extern u16 D_80180428[];
extern u16 g_EInitGeneric[];
extern u16 g_eInitGeneric2[];
extern u16 D_8018047C[]; // EntityElevator

extern ObjInit2 D_80180490[];
extern s32 D_80180574[];
extern s8 D_80180594[];
extern u8 D_8018059C[];
extern s16 D_801805A4[];
extern s8 D_801805B4[];
extern u16 D_801805BC;
extern u16 D_801805D8[];
extern const char* D_80180684[];
extern s32 D_8018068C[];
extern u8 D_80180768[]; // Animation
extern u8 D_80180780[]; // Animation
extern s16 D_80180BBC[];
extern u16 D_80180EEC[];
extern u16 D_80180F1C[];
extern s8 c_HeartPrizes[];
extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u8 g_ESoulStealOrbAnim[];
extern ObjInit2 D_8018125C[];

extern s16 D_8019D37E;
extern u16 D_8019D380;
extern s16 D_8019D382;
extern s16 D_8019D384;
extern s16 D_8019D386;
extern s16 D_8019D38A;
extern s8 D_8019D38E;
extern s8 D_8019D38F;
extern u32 D_8019D424;

extern u16 g_InitializeEntityData0[];

extern Dialogue g_Dialogue;

#endif
