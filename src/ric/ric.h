// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <sfx.h>

#define GAME_OVER 0x80000

#define CHECK_GROUND 1
#define CHECK_FALL 4
#define CHECK_FACING 8
#define CHECK_JUMP 0x10
#define CHECK_CRASH 0x40
#define CHECK_80 0x80
#define CHECK_GRAVITY_HIT 0x200
#define CHECK_ATTACK 0x1000
#define CHECK_CROUCH 0x2000
#define CHECK_GRAVITY_FALL 0x8000
#define CHECK_GRAVITY_JUMP 0x10000
#define CHECK_GROUND_AFTER_HIT 0x20000
#define CHECK_SLIDE 0x40000

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

enum RicSfxs {
    SFX_GRUNT_A = 0x6F9,
    SFX_GRUNT_B,
    SFX_GRUNT_C,
    SFX_GRUNT_SUBWPN_A,
    SFX_HYDROSTORM = 0x700,
    SFX_CROSS_CRASH,
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

enum RicEntities {
    E_NONE,
    E_FACTORY,                       // RicEntityFactory
    E_SMOKE_PUFF,                    // RicEntitySmokePuff
    E_SUBWPN_CROSS,                  // RicEntitySubwpnCross
    E_80169C10,                      // func_80169C10
    E_HIT_BY_CUT_BLOOD,              // RicEntityHitByCutBlood
    E_SUBWPN_CROSS_TRAIL,            // RicEntitySubwpnCrossTrail
    E_SUBWPN_HOLY_WATER,             // RicEntitySubwpnHolyWater
    E_SUBWPN_HOLY_WATER_FLAME,       // RicEntitySubwpnHolyWaterFlame
    E_80161C2C,                      // func_80161C2C
    E_WHIP,                          // RicEntityWhip
    E_CRASH_HYDROSTORM,              // RicEntityCrashHydroStorm
    E_CRASH_CROSS_BEAM,              // RicEntityCrashCrossBeam
    E_CRASH_CROSS_ROTATING,          // RicEntitySubwpnCrashCross
    E_NOT_IMPLEMENTED_1,             // RicEntityNotImplemented1
    E_NOT_IMPLEMENTED_2,             // RicEntityNotImplemented2
    E_ARM_BRANDISH_WHIP,             // RicEntityArmBrandishWhip
    E_80167964,                      // func_80167964
    E_DUMMY_18,                      // RicEntityDummy
    E_80161EF8,                      // func_80161EF8
    E_NOT_IMPLEMENTED_3,             // RicEntityNotImplemented3
    E_REVIVAL_COLUMN,                // RicEntityRevivalColumn
    E_APPLY_MARIA_POWER_ANIM,        // RicEntityApplyMariaPowerAnim
    E_SLIDE_KICK,                    // RicEntitySlideKick
    E_BLADE_DASH,                    // RicEntityBladeDash
    E_801623E0,                      // func_801623E0
    E_80162604,                      // func_80162604
    E_MARIA,                         // RicEntityMaria
    E_MARIA_POWERS,                  // RicEntityMariaPowers
    E_80160F0C,                      // func_80160F0C
    E_NOT_IMPLEMENTED_4,             // RicEntityNotImplemented4
    E_BLINK_WHITE,                   // RicEntityPlayerBlinkWhite
    E_SUBWPN_CRASH_CROSS_PARTICLES,  // RicEntitySubwpnCrashCrossParticles
    E_801641A0,                      // func_801641A0
    E_SHRINKING_POWERUP_RING,        // RicEntityShrinkingPowerUpRing
    E_80167A70,                      // func_80167A70
    E_SUBWPN_AXE,                    // RicEntitySubwpnAxe
    E_CRASH_AXE,                     // RicEntityCrashAxe
    E_SUBWPN_DAGGER,                 // RicEntitySubwpnDagger
    E_80160D2C,                      // func_80160D2C
    E_HIT_BY_ICE,                    // RicEntityHitByIce
    E_HIT_BY_LIGHTNING,              // RicEntityHitByLightning
    E_SUBWPN_REBOUND_STONE,          // RicEntitySubwpnReboundStone
    E_SUBWPN_VIBHUTI,                // RicEntitySubwpnThrownVibhuti
    E_SUBWPN_AGUNEA,                 // RicEntitySubwpnAgunea
    E_SUBWPN_AGUNEA_HIT_ENEMY,       // RicEntityAguneaHitEnemy
    E_CRASH_VIBHUTI,                 // RicEntityCrashVibhuti
    E_CRASH_VIBHUTI_CLOUD,           // RicEntityVibhutiCrashCloud
    E_CRASH_REBOUND_STONE,           // RicEntityCrashReboundStone
    E_8016D9C4,                      // func_8016D9C4
    E_CRASH_REBOUND_STONE_EXPLOSION, // RicEntityCrashReboundStoneExplosion
    E_CRASH_BIBLE,                   // RicEntityCrashBible
    E_CRASH_BIBLE_BEAM,              // RicEntityCrashBibleBeam
    E_SUBWPN_BIBLE,                  // RicEntitySubwpnBible
    E_SUBWPN_BIBLE_TRAIL,            // RicEntitySubwpnBibleTrail
    E_SUBWPN_STOPWATCH,              // RicEntitySubwpnStopwatch
    E_SUBWPN_STOPWATCH_CIRCLE,       // RicEntitySubwpnStopwatchCircle
    E_801705EC,                      // func_801705EC
    E_8016F198,                      // func_8016F198
    E_AGUNEA_CIRCLE,                 // RicEntityAguneaCircle
    E_AGUNEA_LIGHTNING,              // RicEntityAguneaLightning
    E_CRASH_REBOUND_STONE_PARTICLES, // RicEntityCrashReboundStoneParticles
    E_HIT_BY_DARK,                   // RicEntityHitByDark
    E_HIT_BY_HOLY,                   // RicEntityHitByHoly
    E_CRASH_STOPWATCH_DONE_PARTICLE, // RicEntityCrashStopwatchDoneSparkle
    E_80170548,                      // func_80170548
    E_TELEPORT,                      // RicEntityTeleport
    E_DUMMY_66,                      // RicEntityDummy
    NUM_ENTITIES,
};

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
    BP_NOT_IMPLEMENTED_4,
    BP_RIC_BLINK,
    BP_CRASH_CROSS_PARTICLES,
    BP_35,
    BP_36,
    BP_37,
    BP_38,
    BP_39,
    BP_UNUSED_40,
    BP_CRASH_AXE,
    BP_42,
    BP_SUBWPN_DAGGER,
    BP_CRASH_DAGGER,
    BP_HIGH_JUMP,
    BP_HIT_BY_CUT,
    BP_HIT_BY_ICE,
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
    BP_STOPWATCH_RIPPLE,
    BP_CRASH_STOPWATCH,
    BP_66,
    BP_CRASH_AGUNEA,
    BP_CRASH_AGUNEA_THUNDER,
    BP_CRASH_REBOUND_STONE_PARTICLES,
    BP_HIT_BY_DARK,
    BP_HIT_BY_HOLY,
    BP_AGUNEA_THUNDER,
    BP_73,
    BP_SMOKE_PUFF_2,
    BP_SKID_SMOKE_2,
    BP_SKID_SMOKE_3,
    BP_TELEPORT,
    NUM_BLUEPRINTS,
};

enum RicSubweapons {
    PL_W_NONE,
    PL_W_DAGGER,
    PL_W_AXE,
    PL_W_HOLYWATER,
    PL_W_CROSS,
    PL_W_BIBLE,
    PL_W_STOPWATCH,
    PL_W_REBNDSTONE,
    PL_W_VIBHUTI,
    PL_W_AGUNEA,
    PL_W_10,
    PL_W_HOLYWATER_FLAMES,
    PL_W_CRASH_CROSS,
    PL_W_CRASH_CROSS_BEAM,
    PL_W_WHIP,
    PL_W_15,
    PL_W_HYDROSTORM,
    PL_W_BIBLE_BEAM,
    PL_W_KICK,
    PL_W_19,
    PL_W_20,
    PL_W_21,
    PL_W_22,
    PL_W_23,
    PL_W_CRASH_VIBHUTI,
    PL_W_CRASH_REBOUND_STONE,
    PL_W_CRASH_AGUNEA,
    PL_W_27,
    PL_W_28,
    PL_W_CRASH_REBOUND_EXPLOSION,
    PL_W_30,
    NUM_WEAPONS,
};

extern s16* D_801530AC[];
extern SpriteParts* D_80153AA0[];
extern SpriteParts* D_80153D24[];
extern SpriteParts* D_801541A8[];
extern void func_80159C04(void);
extern void DestroyEntity(Entity* entity);
extern void func_8015BB80(void);
extern void RicHandleBladeDash(void);
extern void RicSetStep(int step);
void RicSetAnimation(AnimationFrame* anim);
extern void RicDecelerateX(s32 speed);
extern s32 RicCheckFacing(void);
extern void RicSetSpeedX(s32 speed);
extern void RicSetCrouch(s32 arg0, s32 velocityX);
extern void RicSetStand(s32 velocityX);
extern void RicSetWalk(s32);
extern void RicSetRun(void);
extern void RicSetFall(void);
extern bool RicCheckInput(s32 checks);
extern void RicSetSubweaponParams(Entity*);
extern s32 func_8015FDB0(Primitive* poly, s16 posX, s16 posY);
extern Entity* RicCreateEntFactoryFromEntity(
    Entity* entity, u32 arg1, s32 arg2);

extern s32 func_8016840C(s16 x, s16 y);

extern s16 D_80154568[];
extern s32 g_IsPrologueStage;
extern s16 D_80154574[];
extern s16 D_80154594[];
extern s32 D_8015459C;
extern RECT D_801545A0;
extern s16 g_DeadPrologueTimer;
extern s16 D_801545AA;
extern s16 D_801545AC;
extern u8 D_801545B0[];
extern u8 D_801545C4[16];
extern u8 D_801545D4[16];
// These appear to be a set of collision boxes
extern Point16 D_801545E4[4];
extern Point16 D_801545F4[4];
extern Point16 D_80154604[14];
extern u16 D_8015463C[4];
extern u16 D_80154644[4];
extern u16 D_8015464C[8];
extern u16 D_8015465C[4];
extern u16 D_80154664[8];

extern u8 D_80154674[][4]; // TODO AnimationFrames*[]
extern SubweaponDef D_80154688[];
extern u8 uv_anim_801548F4[6][8];
extern FactoryBlueprint g_RicFactoryBlueprints[];

extern s8 D_80156A28;
extern s8 D_80156904;

extern ButtonComboState g_bladeDashButtons;
extern ButtonComboState D_801758E4;
extern u16 g_RicDebugCurFrame;
extern u16 g_RicDebugDrawFlags;
extern u16 g_RicDebugPalette;
extern s16 g_IsRicDebugEnter;
extern s32 D_80175958[32];
extern s32 D_801759D8[32];

// pl_anims.c
extern AnimationFrame* D_8015538C[];
extern AnimationFrame ric_anim_press_up[];
extern AnimationFrame ric_anim_stop_run[];
extern AnimationFrame ric_anim_stand[];
extern AnimationFrame ric_anim_stand_relax[];
extern AnimationFrame ric_anim_walk[];
extern AnimationFrame ric_anim_crouch_from_stand2[];
extern AnimationFrame ric_anim_crouch[];
extern AnimationFrame ric_anim_land_from_air_run[];
extern AnimationFrame ric_anim_crouch_from_stand[];
extern AnimationFrame D_801554E0[];
extern AnimationFrame D_801554F0[];
extern AnimationFrame D_8015550C[];
extern AnimationFrame D_80155528[];
extern AnimationFrame D_80155534[];
extern AnimationFrame D_80155544[];
extern AnimationFrame D_8015555C[];
extern AnimationFrame D_80155588[];
extern AnimationFrame D_801555A8[];
extern AnimationFrame D_801555C8[];
extern AnimationFrame D_801555E8[];
extern AnimationFrame ric_anim_throw_daggers[];
extern AnimationFrame D_80155638[];
extern AnimationFrame ric_anim_stand_in_air[];
extern AnimationFrame ric_anim_run[];
extern AnimationFrame ric_anim_stun[];
extern AnimationFrame D_8015569C[];
extern AnimationFrame D_801556C4[];
extern AnimationFrame D_80155704[];
extern AnimationFrame ric_anim_brandish_whip[];
extern AnimationFrame D_80155738[];
extern AnimationFrame D_80155740[];
extern AnimationFrame D_80155748[];
extern AnimationFrame D_80155750[];
extern AnimationFrame D_8015577C[];
extern AnimationFrame D_80155788[];
extern AnimationFrame ric_anim_high_jump[];
extern AnimationFrame D_80155738[];
extern AnimationFrame ric_anim_point_finger_up[];
extern AnimationFrame ric_anim_blade_dash[];
extern AnimationFrame ric_anim_flame_whip[];
extern AnimationFrame D_801558B4[];
extern AnimationFrame D_801558D4[];
extern AnimationFrame D_801558E4[];
extern AnimationFrame D_801558DC[];
extern AnimationFrame D_8015591C[];
extern AnimationFrame D_80155950[];
extern FrameProperty D_80155964[];
