// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_RICHTER_H
#define SATURN_RICHTER_H

// Overlays run on top of the resident zero and game modules.
#include "game.h"
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_player.h>

void func_0600B0B8(SpritePart* part, void* arg1, s32 arg2);

extern s8* DAT_06085DE8[];
extern s8* DAT_06085E14[];

enum RicBlueprints {
    BP_SKID_SMOKE,
    BP_SMOKE_PUFF,
    BP_SUBWPN_CROSS,
    BP_SUBWPN_CROSS_PARTICLES,
    BP_EMBERS,
    BP_5,
    BP_SUBWPN_HOLYWATER,
    BP_HOLYWATER_FIRE,
    BP_HIT_BY_FIRE,
    BP_HOLYWATER_FLAMES,
    BP_WHIP,
    BP_MULTIPLE_EMBERS,
    BP_HYDROSTORM,
    BP_CRASH_CROSS,
    BP_CRASH_CROSSES_ONLY,
    BP_NOT_IMPLEMENTED_1,
    // 0x10
    BP_NOT_IMPLEMENTED_2,
    BP_ARM_BRANDISH_WHIP,
    BP_18,
    BP_AXE,
    BP_20,
    BP_NOT_IMPLEMENTED_3,
    BP_REVIVAL_COLUMN,
    BP_MARIA_POWERS_APPLIED,
    BP_SLIDE,
    BP_25,
    BP_BLADE_DASH,
    BP_BLUE_CIRCLE,
    BP_BLUE_SPHERE,
    BP_MARIA,
    BP_MARIA_POWERS_INVOKED,
    BP_31,
    // 0x20
    BP_NOT_IMPLEMENTED_4,
    BP_RIC_BLINK,
    BP_CRASH_CROSS_PARTICLES,
    BP_35,
    BP_36,
    BP_37,
    BP_38,
    BP_39,
    BP_HOLYWATER_GLASS,
    BP_CRASH_AXE,
    BP_42,
    BP_SUBWPN_DAGGER,
    BP_CRASH_DAGGER,
    BP_HIGH_JUMP,
    BP_HIT_BY_CUT,
    BP_HIT_BY_ICE,
    // 0x30
    BP_HIT_BY_THUNDER,
    BP_VIBHUTI,
    BP_REBOUND_STONE,
    BP_AGUNEA,
    BP_AGUNEA_HIT_ENEMY,
    BP_DEATH_BY_FIRE,
    BP_CRASH_VITHUBI,
    BP_VITHUBI_CRASH_CLOUD,
    BP_CRASH_REBOUND_STONE,
    BP_57,
    BP_CRASH_REBOUND_STONE_EXPLOSION,
    BP_CRASH_BIBLE,
    BP_CRASH_BIBLE_BEAM,
    BP_BIBLE,
    BP_BIBLE_TRAIL,
    BP_SUBWPN_STOPWATCH,
    // 0x40
    BP_STOPWATCH_CIRCLE,
    BP_CRASH_STOPWATCH,
    BP_66,
    BP_CRASH_AGUNEA,
    BP_CRASH_AGUNEA_THUNDER,
    BP_CRASH_REBOUND_STONE_PARTICLES,
    BP_HIT_BY_DARK,
    BP_HIT_BY_HOLY,
    BP_AGUNEA_THUNDER,
    BP_CRASH_STOPWATCH_LIGHTNING,
    BP_SMOKE_PUFF_2,
    BP_SKID_SMOKE_2,
    BP_SKID_SMOKE_3,
    BP_TELEPORT,
    NUM_BLUEPRINTS,
};

enum RicTimers {
    PL_T_POISON,
    PL_T_CURSE,
    PL_T_2,
    PL_T_3,
    PL_T_4,
    PL_T_5,
    PL_T_6,
    PL_T_7,
    PL_T_8,
    PL_T_ATTACK,
    PL_T_10,
    PL_T_RUN,
    PL_T_12,
    PL_T_INVINCIBLE_SCENE, // "dying" in the prologue
    PL_T_INVINCIBLE,
    PL_T_AFTERIMAGE_DISABLE,
};

// Richter mostly uses the same steps as Alucard, or uses unused Alucard steps.
// There are a couple steps that mean one thing for Alucard, and another for
// Richter. This enum handles Richter's version of the ones that overlap.
enum RicSteps {
    PL_S_STAND,
    PL_S_WALK,
    PL_S_CROUCH,
    PL_S_FALL,
    PL_S_JUMP,
    PL_S_5, // unused
    PL_S_6, // unused
    PL_S_7, // unused
    PL_S_HIGHJUMP,
    PL_S_9, // unused
    PL_S_HIT,
    PL_S_11, // unused
    PL_S_BOSS_GRAB,
    PL_S_13, // unused
    PL_S_14, // unused
    PL_S_15, // unused
    PL_S_DEAD,
    PL_S_17, // unused
    PL_S_STAND_IN_AIR,
    PL_S_FLAME_WHIP,
    PL_S_HYDROSTORM,
    PL_S_THROW_DAGGERS,
    PL_S_DEAD_PROLOGUE,
    PL_S_SLIDE,
    PL_S_BLADEDASH,
    PL_S_RUN,
    PL_S_SLIDE_KICK,
    PL_S_SUBWPN_CRASH,
    PL_S_28, // unused
    PL_S_29, // unused
    PL_S_30, // unused
    PL_S_31, // unused
    PL_S_INIT,
    PL_S_DEBUG = 0xF0,
};

AnimationFrame D_801554F0[];
AnimationFrame D_8015550C[];
AnimationFrame D_80155534[];
extern s32 g_IsPrologueStage;

/* Declarations moved here by tools/saturn/move_declarations.py */
extern SaturnPlayerGraphicsRecord g_RichterPlayerGraphicsRecords[191];
extern void* g_RichterSpriteBanks[17];
void func_8015E484(void);
Entity* RicCreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2);
void func_060AA4F4(s32 spawnParticles);
extern Unk0605DB60 d_0605DB60[];
u16 SPR_2LookupTblNoToVram(u16 tableNo);
void func_060BCA84(void);
void DisableAfterImage(s32 resetAnims, s32 arg1);
void func_060AC2DC(void);
s32 func_060B0610(void);
void RicUpdatePlayerEntities(void);
void RicMain(void);
void RicInit(u16 params);
extern s32 D_060CEEDC[];
extern s32 D_060CEE6C[];
void func_060BC834(void);
extern s16 g_RichterMapRevealRowIndices[];
void func_060BB9BC(s32*);
extern s32 g_RichterSavedMapPlaneConfig;
extern s32 g_RichterSavedMapVramBase;
extern u8 g_RichterCastleMapBitmap[240][160];
extern u32 g_RichterCastleMapState;
void func_060BB330();
extern s16 D_80155D30[];
extern u8 D_060BF1A4[];
extern u16 g_RichterSpritePackage3AllocationIndex;
extern SubweaponDef ric_subweapons_def[];
extern u8 D_80174FB8;
extern u8 D_80174FB4;
extern u8 D_80174FB0;
extern u8 D_80174FAC;
extern u8 D_80154674[][4];
extern Point32 g_RicSensorsWall[NUM_VERTICAL_SENSORS * 2];
extern Point32 g_RicSensorsFloor[NUM_HORIZONTAL_SENSORS];
extern Point32 g_RicSensorsCeiling[NUM_HORIZONTAL_SENSORS];
extern AnimationFrame ric_anim_blade_dash[];
extern AnimationFrame D_8015577C[1];
extern AnimationFrame D_80155750[];
extern AnimationFrame ric_anim_high_jump[];
void RicSetRun(void);
extern AnimationFrame ric_anim_crouch_from_stand[];
extern AnimationFrame ric_anim_crouch_from_stand2[];
extern void func_060A6428(u16 arg0);
extern s32 throw_dagger_timer;
extern u32 g_SubwpnCrashTimer;
extern u16 D_80155528[];
extern AnimationFrame ric_anim_stop_run[];
extern s32 D_80154568[];
extern AnimationFrame anim_80154E38[];
extern u8 g_RichterMapRevealPattern[11];
extern u8 g_RichterMapIconIndices[8];
extern Point16 g_RichterMapUiPositionsA[12];
extern Point16 g_RichterMapUiPositionsB[5];
extern Point16 g_RichterMapUiPositionsC[21];
extern Point16 g_RichterMapUiPositionsD[14];
extern Point16 g_RichterMapUiPositionsE[16];
extern Point16 g_RichterMapUiPositionsF[11];
void func_060BACEC(u8 walls, u8* dst);
void func_060BAED0(u8 walls, u8* dst);
void func_060BB09C(u8 walls, u8* dst);
void func_060BB184(void);
/* End moved declarations */

#endif
