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
} EntityIDs;

// *** EntitySoulStealOrb properties START ***

extern u16 D_801810A0[]; // NOTE(sestren): Random angle offsets?
extern u16 D_801810B0[]; // NOTE(sestren): Animation frame properties?
extern u32 D_80181110[];

// *** EntitySoulStealOrb properties END ***