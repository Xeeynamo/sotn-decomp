// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"
#define STAGE_IS_DRE

#define OVL_EXPORT(x) DRE_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

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
    /* 0x14 */ E_EXPLOSION_VARIANTS = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ E_3D_BACKGROUND_HOUSE,
    /* 0x17 */ E_3D_HOUSE_SPAWNER,
    /* 0x1A */ E_SUCCUBUS_PETAL = 0x1A,
    /* 0x1B */ E_SUCCUBUS_WING_OVERLAY,
    /* 0x1C */ E_SUCCUBUS_CLONE,
    /* 0x1D */ E_SUCCUBUS_PINK_BALL_PROJECTILE,
    /* 0x1E */ E_SUCCUBUS_WING_SPIKE,
    /* 0x1F */ E_SUCCUBUS_WING_SPIKE_TIP,
    /* 0x20 */ E_SUCCUBUS_CUTSCENE,
} DRE_EntityIDs;

void ReplaceBreakableWithItemDrop(Entity* arg0);
void DestroyEntity(Entity* entity);
void CreateEntitiesToTheRight(s16);
void CreateEntitiesToTheLeft(s16);
void CreateEntitiesAbove(s16);
void CreateEntitiesBelow(s16);
s32 func_8019AC78(u8, s16);
void PreventEntityFromRespawning(Entity* entity);
void FallEntity(void);
void func_8019B858(void);
void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity);
Entity* AllocEntity(Entity*, Entity*);
void func_8019A78C(void);
Entity* func_8019AC18(Entity*, Entity*);
void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

/* *** Initializers *** */
extern EInit g_EInitLockCamera;
extern EInit g_EInitObtainable;
extern u16 D_8018047C[];
extern EInit g_EInitInteractable;
extern u16 D_801804D0[]; // EntitySuccubus
extern u16 D_801804DC[];
extern u16 D_80180500[];
extern u8 D_80180580[];
extern u8 D_80180588[];
extern u16 D_80180590[];

extern s32 D_80180664;

/* *** EntitySuccubus animations START *** */
extern u8 D_8018066C[];
extern u8 D_80180674[];
extern u8 D_80180680[];
extern u8 D_80180694[];
extern u8 D_801806A0[];
extern u8 D_801806C4[];
extern u8 D_801806D4[];
extern u8 D_801806E8[];
extern u8 D_801806F8[];
extern u8 D_8018070C[];
extern u8 D_8018071C[];
extern u8 D_8018072C[];
extern u8 D_80180734[];
extern u8 D_80180748[];
extern u8 D_80180760[];
extern u8 D_80180768[];
extern u8 D_80180770[];
extern u8 D_80180778[];
extern u8 D_80180780[];
extern u8 D_8018079C[];
extern u8 D_801807AC[];
/* *** EntitySuccubus animations END *** */

extern s8 g_CloneShootOrder[4][7]; // 0x801807D4

extern u8 D_80180780[]; // Animation
extern const u8 D_80180794[];
extern u8 D_801807F8[][4];
extern u8 D_80180830[];
extern EInit g_EInitParticle;
extern EInit g_EInitCommon;
extern u16 D_801804F4[];
extern s8 c_HeartPrizes[];
extern u16 D_801804E8[];
extern u16 D_8018050C[];
extern u16 D_80180528[];
extern s32 D_80180664;
extern s32 D_80180668;
extern s16 D_801807F0[];
extern const char* D_80180938[];
extern s32 D_801811B0[];
extern u32 D_8018125C[];
extern s16 D_801812E4[];
extern u32 D_801812F4[];
extern s8 D_801816C0;
extern s8 D_801816C4; // Succubus facing assigned to it
extern u8 D_80181338[];
extern u16 D_801811A4[];
extern u16 D_801810B0[];
extern u16 D_801810E0[];

// *** EntitySoulStealOrb properties START ***

extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u8 g_ESoulStealOrbAnim[];

// *** EntitySoulStealOrb properties END ***

extern Primitive* D_801A3EF0[];
extern s32 D_801A3F08;
extern s32 D_801A3F0C;
extern s32 D_801A3F10[];

// For succubus cutscene
extern u8 D_8018088C[];
extern u8 D_80180890[];
extern u16 D_80180894[];
extern u16 D_8018089C[];
extern u16 D_801808A0[];
extern s16 D_801808A8[];
extern s32 g_SkipCutscene;
extern u32 g_CutsceneFlags;
extern s32 g_IsCutsceneDone;

extern u8 D_80180944[]; // Animation, EntityCSMoveAlucard

extern Dialogue g_Dialogue;
