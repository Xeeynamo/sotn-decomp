// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

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
    // there seems to be two new values on Saturn
    PL_T_INVINCIBLE_SCENE = 15, // "dying" in the prologue
    PL_T_INVINCIBLE,
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

AnimationFrame D_8015550C[];
AnimationFrame D_801554F0[];
extern s32 g_IsPrologueStage;
