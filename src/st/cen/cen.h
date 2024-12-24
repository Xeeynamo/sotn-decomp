// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef CEN_H
#define CEN_H

#include "common.h"
#include "stage.h"

#define OVL_EXPORT(x) CEN_##x

#define CASTLE_FLAG_BANK 0x00

typedef enum EntityIDs {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_ID_01,
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
    /* 0x0E */ E_SAVE_GAME_POPUP,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,
    /* 0x11 */ E_BACKGROUND_BLOCK,
    /* 0x12 */ E_ID_12,
    /* 0x13 */ E_ID_13,
    /* 0x14 */ E_ID_14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ E_CUTSCENE,
    /* 0x17 */ E_PLATFORM,
    /* 0x18 */ E_MARIA,
    /* 0x19 */ E_ROOM_DARKNESS,
    /* 0x1A */ E_ELEVATOR_STATIONARY_UNUSED,
    /* 0x1B */ E_ELEVATOR_STATIONARY,
    /* 0x1C */ E_MOVING_ELEVATOR,
    /* 0x80 */ E_BREAKABLE_UNK0 = 0x80,
} EntityIDs;

void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity);
void CreateEntityFromLayout(Entity*, LayoutEntity*);
u16 GetNormalizedAngle(u16 arg0, u16 arg1, u16 arg2);
void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

/*** Initializers ***/
extern EInit OVL_EXPORT(EInitBreakable);
extern u16 g_EInitObtainable[];
extern u16 g_EInitMaria[];
extern u16 g_EInitInteractable[];
extern u16 g_EInitCommon[];
extern u16 g_EInitParticle[];
extern u16 g_EInitElevator[]; // EntityElevator

extern u16* D_80180574[];
extern u8 D_80180594[];
extern u8 D_8018059C[];
extern u16 D_801805A4[];
extern u8 D_801805B4[];
extern s16 D_801805BC[];
extern u16 D_80180EEC[];
extern u16 D_80180F1C[];
extern s8 c_HeartPrizes[];
extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u8 g_ESoulStealOrbAnim[];
extern ObjInit D_8018125C[];

extern s32 g_SkipCutscene;
extern Dialogue g_Dialogue;
extern u32 g_CutsceneFlags;
extern s32 g_IsCutsceneDone;

#endif
