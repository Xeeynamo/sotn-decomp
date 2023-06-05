#ifndef CEN_H
#define CEN_H

#include "common.h"
#include "stage.h"

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
    E_STAGE_NAME_POPUP,
    E_EQUIP_ITEM_DROP,
    E_RELIC_ORB,
    E_HEART_DROP,
    E_ENEMY_BLOOD,
    E_SAVE_GAME_POPUP,
    E_DUMMY_0F,
    E_DUMMY_10,
} EntityIDs;

extern PfnEntityUpdate D_80180390[];
extern u16 D_80180410[]; // Init
extern u16 D_80180428[];
extern u16 D_80180458[];
extern ObjInit2 D_80180490[];
extern u16 D_801805D8[];
extern s32 D_8018068C[];
extern s16 D_80180BBC[];
extern s8 D_80180FE8[];
extern u16 D_801811C8[];
extern u16 D_801811D8[];
extern u8 D_80181238;
extern ObjInit2 D_8018125C[];
void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity);
extern LayoutObject* D_8019C764;
extern LayoutObject* D_8019C768;
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
void func_80192A3C(Entity*, LayoutObject*);
extern u16 func_80194E44(u16 arg0, u16 arg1, u16 arg2);
extern u8 D_8019C76C;
extern u8 D_8019C770;
#endif