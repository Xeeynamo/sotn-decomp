#ifndef CEN_H
#define CEN_H

#include "common.h"
#include "stage.h"

typedef enum {
    E_NONE = 0x00,
    E_ID01 = 0x01,
    E_EXPLOSION = 0x02,
    E_PRIZE_DROP = 0x03,
    E_NUMERIC_DAMAGE = 0x04,
    E_RED_DOOR = 0x05,
    E_INTENSE_EXPLOSION = 0x06,
    E_SOUL_STEAL_ORB = 0x07,
    E_ROOM_FOREGROUND = 0x08,
    E_STAGE_NAME_POPUP = 0x09,
    E_EQUIP_ITEM_DROP = 0x0A,
    E_RELIC_ORB = 0x0B,
    E_HEART_DROP = 0x0C,
    E_ENEMY_BLOOD = 0x0D,
    E_SAVE_GAME_POPUP = 0x0E,
    E_DUMMY_0F = 0x0F,
    E_DUMMY_10 = 0x10,
    E_BACKGROUND_BLOCK = 0x11,
    E_ID12 = 0x12,
    E_ID13 = 0x13,
    E_ENTITY_EXPLOSION_14 = 0x14,
    E_ID15 = 0x15,
    E_ID16 = 0x16,
    E_PLATFORM = 0x17,
    E_MARIA = 0x18,
    E_ROOM_DARKNESS = 0x19,
    E_ELEVATOR_STATIONARY = 0x1A,
    E_ID1B = 0x1B,
    E_MOVING_ELEVATOR = 0x1C,
} EntityIDs;

void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity);
void func_80192A3C(Entity*, LayoutObject*);
extern u16 func_80194E44(u16 arg0, u16 arg1, u16 arg2);

extern LayoutObject* D_801801EC[];
extern LayoutObject* D_801802C0[];
extern PfnEntityUpdate D_80180390[];

/*** Initializers ***/
extern u16 D_80180404[];
extern u16 D_80180410[];
extern u16 D_80180428[];
extern u16 D_80180434[]; // EntityPlatform
extern u16 D_80180458[];
extern u16 D_8018047C[]; // EntityElevator

extern ObjInit2 D_80180490[];
extern s32 D_80180574[];
extern s8 D_80180594[];
extern u8 D_8018059C[];
extern s16 D_801805A4[];
extern s8 D_801805B4[];
extern u16 D_801805BC;
extern u16 D_801805D8[];
extern s32 D_8018068C[];
extern u8 D_80180768[]; // Animation
extern u8 D_80180780[]; // Animation
extern s16 D_80180BBC[];
extern u16 D_80180EEC[];
extern u16 D_80180F1C[];
extern s8 D_80180FE8[];
extern u16 D_801811C8[];
extern u16 D_801811D8[];
extern u8 D_80181238;
extern ObjInit2 D_8018125C[];
extern LayoutObject* D_8019C764;
extern u16* D_8019C768;
extern u8 D_8019C76C;
extern s16 D_8019D3B4;
extern s16 D_8019D3B6;
extern s32 D_8019D3B8;
extern s16 D_8019D37E;
extern u16 D_8019D380;
extern s16 D_8019D382;
extern s16 D_8019D384;
extern s16 D_8019D386;
extern s16 D_8019D38A;
extern s8 D_8019D38E;
extern s8 D_8019D38F;
extern s32 D_8019D424;
extern u8 D_8019C76C;
extern u8 D_8019C770;
#endif