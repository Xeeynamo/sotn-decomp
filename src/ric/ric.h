// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <sfx.h>

#define OVL_EXPORT(x) RIC_##x

#define RIC_SPRITE_COUNT 197 // useful to sync PSX and PSP

#define GAME_OVER 0x80000

enum RicInputChecks {
    CHECK_GROUND = 1,
    CHECK_FALL = 4,
    CHECK_FACING = 8,
    CHECK_JUMP = 0x10,
    CHECK_CRASH = 0x40,
    CHECK_80 = 0x80,
    CHECK_GRAVITY_HIT = 0x200,
    CHECK_ATTACK = 0x1000,
    CHECK_CROUCH = 0x2000,
    CHECK_GRAVITY_FALL = 0x8000,
    CHECK_GRAVITY_JUMP = 0x10000,
    CHECK_GROUND_AFTER_HIT = 0x20000,
    CHECK_SLIDE = 0x40000,
};

// Richter mostly uses the same steps as Alucard, or uses unused Alucard
// steps.
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

#include "ric_shared.h"

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
    E_HOLYWATER_BREAK_GLASS,         // RicEntitySubwpnHolyWaterBreakGlass
    E_SUBWPN_AXE,                    // RicEntitySubwpnThrownAxe
    E_CRASH_AXE,                     // RicEntityCrashAxe
    E_SUBWPN_DAGGER,                 // RicEntitySubwpnKnife
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
    E_CRASH_STOPWATCH,               // RicEntityCrashStopwatch
    E_8016F198,                      // func_8016F198
    E_AGUNEA_CIRCLE,                 // RicEntityAguneaCircle
    E_AGUNEA_LIGHTNING,              // RicEntityAguneaLightning
    E_CRASH_REBOUND_STONE_PARTICLES, // RicEntityCrashReboundStoneParticles
    E_HIT_BY_DARK,                   // RicEntityHitByDark
    E_HIT_BY_HOLY,                   // RicEntityHitByHoly
    E_CRASH_STOPWATCH_DONE_PARTICLE, // RicEntityCrashStopwatchDoneSparkle
    E_CRASH_STOPWATCH_LIGHTNING,     // RicEntityStopwatchCrashLightning
    E_TELEPORT,                      // RicEntityTeleport
    E_DUMMY_66,                      // RicEntityDummy
    NUM_ENTITIES,
};

// NOTE: B_MAKE from DRA is different than RIC or MARIA!
// Parsing is done in RicEntityFactory
// entityId: what entity to spawn based on the Entity Set
// amount: How many entities to spawn in total
// nPerCycle: how many entities to spawn at once without waiting for tCycle
// isNonCritical: 'true' for particles, 'false' for gameplay related entities
//   false: keep searching for a free entity slot every frame to make the entity
//   true: when there are no entities available then just forgets about it
// incParamsKind: the technique used to set the self->params to the new entity
//   false: it is set from 0 to 'nPerCycle'
//   true: it is set from 0 to 'amount'
// timerCycle: wait frames per cycle until 'amount' of entities are made
// kind: refer to `BlueprintKind` for a list of options
// origin: position where the entity will spawn from
// timerDelay: how many frames to wait before starting to make the first entity
#define B_MAKE(entityId, amount, nPerCycle, isNonCritical, incParamsKind,      \
               timerCycle, kind, origin, timerDelay)                           \
    {(entityId),                                                               \
     (amount),                                                                 \
     ((nPerCycle) & 0x3F) | ((!!(incParamsKind)) << 6) |                       \
         ((!!(isNonCritical)) << 7),                                           \
     (timerCycle),                                                             \
     ((kind) & 7) | (((origin) & 31) << 3),                                    \
     timerDelay}
enum BlueprintKind {
    // cannot collide with any other entity, used for decoration
    B_DECORATION,

    // can collide to stage items, like candles or enemies
    B_WEAPON,

    // same as above, but new entity replaces the previous one
    B_WEAPON_UNIQUE,

    // graphics and particle effects
    B_EFFECTS,

    // Exclusive to the whip entity controller, entity slot 31
    B_WHIP,

    // Exclusive to young Maria during the prologue, entity slot 48
    B_CUTSCENE_MARIA,

    // Used by subweapon crashes that use a lot of particiles that deal
    // damage
    B_WEAPON_CHILDREN,

    B_KIND_7, // unused
    NUM_BLUEPRINT_KIND,
};
enum BlueprintOrigin {
    // Spawned entities have a life-cycle on their own and
    B_ORIGIN_DEFAULT,

    // Entity moves with the camera, remaining static on the screen.
    B_ORIGIN_FOLLOW_CAMERA,

    // Entity remains attached to the player.
    B_ORIGIN_FOLLOW_PLAYER,

    // The player moves when getting hit with a velocity that corresponds to
    // the
    // severity of the attack received, and we want tjhe effect to follow
    // the
    // player when moving during that phase.
    B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_HIT,

    // Entity remains attached to the player, but only with step==PL_S_RUN
    B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_RUNNING,

    B_ORIGIN_5, // unused, same behaviour as B_ORIGIN_FOLLOW_CAMERA
    B_ORIGIN_6, // unused, same behaviour as B_ORIGIN_FOLLOW_CAMERA

    // Useful when the player is about to use a subweapon: once the command
    // is
    // issued, there is a fraction of delay until the subweapon is spawned
    // to
    // allow the attack to be synchronized with the animaiton. If the player
    // is
    // hit during that fraction, the spawning of the subweapon is
    // effectively
    // canceled.
    B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_NOT_HIT,

    // Spawned entites remain attached to their parent.
    B_ORIGIN_FOLLOW_PARENT_ENTITY,

    // A subweapon crash will spawn different particles that should get
    // de-spawned when the attack terminates.
    B_ORIGIN_SUBWEAPON_CRASH_PARTICLE,
};

extern PlayerOvl RIC_player;

extern s16* D_801530AC[];
extern SpriteParts* D_80153AA0[];
extern SpriteParts* D_80153D24[];
extern SpriteParts* D_801541A8[];
extern void DestroyEntity(Entity* entity);
extern void RicStepBladeDash(void);
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
extern Entity* RicCreateEntFactoryFromEntity(
    Entity* entity, u32 arg1, s32 arg2);

extern s32 func_8016840C(s16 x, s16 y);

extern s16 D_80154568[];
extern s32 g_IsPrologueStage;
extern u16 D_80154574[];
extern u16 D_80154594[];
extern s32 D_8015459C;
extern RECT D_801545A0;
extern s16 g_DeadPrologueTimer;
extern s16 D_801545AA;
extern s16 D_801545AC;
extern u8 D_801545B0[];
extern u8 D_801545C4[16];
extern u8 D_801545D4[16];
// These appear to be a set of collision boxes
extern Point16 g_RicSensorsCeiling[];
extern Point16 g_RicSensorsFloor[];
extern Point16 g_RicSensorsWall[];
extern s16 g_RicSensorsCeilingDefault[];
extern s16 g_RicSensorsFloorDefault[];
extern s16 g_RicSensorsWallDefault[];
extern s16 g_RicSensorsCeilingCrouch[];
extern s16 g_RicSensorsWallCrouch[];

extern u8 uv_anim_801548F4[6][8];

extern s8 D_80156A28;
extern s8 D_80156904;

extern ButtonComboState g_RicComboButtons[2];
extern DebugInfo g_RicDebug;
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
