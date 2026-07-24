// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

#define DECLARE_ENTITY(name) extern void name(Entity*)
DECLARE_ENTITY(RicEntityDummy);
DECLARE_ENTITY(RicEntityFactory);
DECLARE_ENTITY(RicEntitySmokePuff);
DECLARE_ENTITY(RicEntitySubwpnCross);
DECLARE_ENTITY(func_80169C10);
DECLARE_ENTITY(RicEntityHitByCutBlood);
DECLARE_ENTITY(RicEntitySubwpnCrossTrail);
DECLARE_ENTITY(RicEntitySubwpnHolyWater);
DECLARE_ENTITY(RicEntitySubwpnHolyWaterFlame);
DECLARE_ENTITY(func_80161C2C);
DECLARE_ENTITY(RicEntityWhip);
DECLARE_ENTITY(RicEntityCrashHydroStorm);
DECLARE_ENTITY(RicEntityCrashCrossBeam);
DECLARE_ENTITY(RicEntitySubwpnCrashCross);
DECLARE_ENTITY(RicEntityNotImplemented1);
DECLARE_ENTITY(RicEntityNotImplemented2);
DECLARE_ENTITY(RicEntityArmBrandishWhip);
DECLARE_ENTITY(func_80167964);
DECLARE_ENTITY(func_80161EF8);
DECLARE_ENTITY(RicEntityNotImplemented3);
DECLARE_ENTITY(RicEntityRevivalColumn);
DECLARE_ENTITY(RicEntityApplyMariaPowerAnim);
DECLARE_ENTITY(RicEntitySlideKick);
DECLARE_ENTITY(RicEntityBladeDash);
DECLARE_ENTITY(func_801623E0);
DECLARE_ENTITY(func_80162604);
DECLARE_ENTITY(RicEntityMaria);
DECLARE_ENTITY(RicEntityMariaPowers);
DECLARE_ENTITY(func_80160F0C);
DECLARE_ENTITY(RicEntityPlayerBlinkWhite);
DECLARE_ENTITY(RicEntitySubwpnCrashCrossParticles);
DECLARE_ENTITY(func_801641A0);
DECLARE_ENTITY(RicEntityShrinkingPowerUpRing);
DECLARE_ENTITY(RicEntitySubwpnHolyWaterBreakGlass);
DECLARE_ENTITY(RicEntitySubwpnThrownAxe);
DECLARE_ENTITY(RicEntityCrashAxe);
DECLARE_ENTITY(RicEntitySubwpnThrownDagger);
DECLARE_ENTITY(func_80160D2C);
DECLARE_ENTITY(RicEntityHitByIce);
DECLARE_ENTITY(RicEntityHitByLightning);
DECLARE_ENTITY(RicEntitySubwpnReboundStone);
DECLARE_ENTITY(RicEntitySubwpnThrownVibhuti);
DECLARE_ENTITY(RicEntitySubwpnAgunea);
DECLARE_ENTITY(RicEntityAguneaHitEnemy);
DECLARE_ENTITY(RicEntityCrashVibhuti);
DECLARE_ENTITY(RicEntityVibhutiCrashCloud);
DECLARE_ENTITY(RicEntityCrashReboundStone);
DECLARE_ENTITY(func_8016D9C4);
DECLARE_ENTITY(RicEntityCrashReboundStoneExplosion);
DECLARE_ENTITY(RicEntityCrashBible);
DECLARE_ENTITY(RicEntityCrashBibleBeam);
DECLARE_ENTITY(RicEntitySubwpnBible);
DECLARE_ENTITY(RicEntitySubwpnBibleTrail);
DECLARE_ENTITY(RicEntitySubwpnStopwatch);
DECLARE_ENTITY(RicEntitySubwpnStopwatchCircle);
DECLARE_ENTITY(RicEntityCrashStopwatch);
DECLARE_ENTITY(func_8016F198);
DECLARE_ENTITY(RicEntityAguneaCircle);
DECLARE_ENTITY(RicEntityAguneaLightning);
DECLARE_ENTITY(RicEntityCrashReboundStoneParticles);
DECLARE_ENTITY(RicEntityHitByDark);
DECLARE_ENTITY(RicEntityHitByHoly);
DECLARE_ENTITY(RicEntityCrashStopwatchDoneSparkle);
DECLARE_ENTITY(RicEntityStopwatchCrashLightning);
DECLARE_ENTITY(RicEntityTeleport);
DECLARE_ENTITY(func_060B0604);
DECLARE_ENTITY(func_060B9978);

PfnEntityUpdate entity_functions[] = {
    RicEntityDummy,
    RicEntityFactory,
    RicEntitySmokePuff,
    RicEntitySubwpnCross,
    func_80169C10,
    RicEntityHitByCutBlood,
    RicEntitySubwpnCrossTrail,
    RicEntitySubwpnHolyWater,
    RicEntitySubwpnHolyWaterFlame,
    func_80161C2C,
    RicEntityWhip,
    RicEntityCrashHydroStorm,
    RicEntityCrashCrossBeam,
    RicEntitySubwpnCrashCross,
    RicEntityNotImplemented1,
    RicEntityNotImplemented2,
    RicEntityArmBrandishWhip,
    func_80167964,
    RicEntityDummy,
    func_80161EF8,
    RicEntityNotImplemented3,
    RicEntityRevivalColumn,
    RicEntityApplyMariaPowerAnim,
    RicEntitySlideKick,
    RicEntityBladeDash,
    func_801623E0,
    func_80162604,
    RicEntityMaria,
    RicEntityMariaPowers,
    func_80160F0C,
    RicEntityDummy,
    RicEntityPlayerBlinkWhite,
    RicEntitySubwpnCrashCrossParticles,
    func_801641A0,
    RicEntityShrinkingPowerUpRing,
    RicEntitySubwpnHolyWaterBreakGlass,
    RicEntitySubwpnThrownAxe,
    RicEntityCrashAxe,
    RicEntitySubwpnThrownDagger,
    func_80160D2C,
    RicEntityHitByIce,
    RicEntityHitByLightning,
    RicEntitySubwpnReboundStone,
    RicEntitySubwpnThrownVibhuti,
    RicEntitySubwpnAgunea,
    RicEntityAguneaHitEnemy,
    RicEntityCrashVibhuti,
    RicEntityVibhutiCrashCloud,
    RicEntityCrashReboundStone,
    func_8016D9C4,
    RicEntityCrashReboundStoneExplosion,
    RicEntityCrashBible,
    RicEntityCrashBibleBeam,
    RicEntitySubwpnBible,
    RicEntitySubwpnBibleTrail,
    RicEntitySubwpnStopwatch,
    RicEntitySubwpnStopwatchCircle,
    RicEntityCrashStopwatch,
    func_8016F198,
    RicEntityAguneaCircle,
    RicEntityAguneaLightning,
    RicEntityCrashReboundStoneParticles,
    RicEntityHitByDark,
    RicEntityHitByHoly,
    RicEntityCrashStopwatchDoneSparkle,
    RicEntityStopwatchCrashLightning,
    RicEntityTeleport,
    func_060B0604,
    func_060B9978,
};

typedef struct {
    u8 childId;
    u8 amount;
    u8 packedCount;
    u8 timerCycle;
    u8 packedOrigin;
    u8 timerDelay;
} RichterFactoryBlueprint;

#define B_MAKE(entityId, amount, nPerCycle, isNonCritical, incParamsKind,      \
               timerCycle, kind, origin, timerDelay)                           \
    {(entityId),                                                               \
     (amount),                                                                 \
     ((nPerCycle) & 0x3F) | ((!!(incParamsKind)) << 6) |                       \
         ((!!(isNonCritical)) << 7),                                           \
     (timerCycle),                                                             \
     ((kind) & 7) | (((origin) & 31) << 3),                                    \
     (timerDelay)}

RichterFactoryBlueprint blueprints[] = {
    B_MAKE(0x02, 5, 1, 1, 1, 2, 0, 0, 0),
    B_MAKE(0x02, 3, 1, 1, 1, 4, 0, 4, 0),
    B_MAKE(0x03, 1, 1, 1, 1, 0, 1, 3, 8),
    B_MAKE(0x04, 3, 1, 1, 1, 2, 0, 0, 0),
    B_MAKE(0x05, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x06, 1, 1, 1, 1, 1, 0, 0, 4),
    B_MAKE(0x07, 1, 1, 1, 1, 0, 1, 3, 8),
    B_MAKE(0x08, 1, 1, 1, 1, 0, 1, 0, 0),
    B_MAKE(0x09, 6, 1, 1, 1, 12, 0, 7, 0),
    B_MAKE(0x09, 128, 1, 1, 1, 3, 0, 7, 8),
    B_MAKE(0x0A, 15, 15, 0, 1, 0, 2, 3, 0),
    B_MAKE(0x05, 72, 1, 1, 1, 2, 3, 2, 0),
    B_MAKE(0x0B, 48, 1, 0, 1, 6, 1, 10, 48),
    B_MAKE(0x0D, 1, 1, 0, 1, 0, 1, 10, 0),
    B_MAKE(0x0C, 6, 1, 1, 1, 24, 1, 1, 0),
    B_MAKE(0x0E, 16, 16, 0, 1, 0, 0, 3, 0),
    B_MAKE(0x0F, 15, 15, 1, 1, 0, 0, 3, 0),
    B_MAKE(0x10, 1, 1, 0, 1, 0, 4, 3, 0),
    B_MAKE(0x11, 1, 1, 1, 1, 0, 0, 1, 0),
    B_MAKE(0x24, 1, 1, 1, 1, 0, 1, 3, 8),
    B_MAKE(0x13, 1, 1, 1, 1, 0, 0, 8, 0),
    B_MAKE(0x14, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x15, 1, 1, 0, 1, 0, 3, 0, 0),
    B_MAKE(0x16, 4, 1, 0, 1, 24, 3, 0, 0),
    B_MAKE(0x02, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x17, 1, 1, 1, 1, 0, 1, 0, 0),
    B_MAKE(0x18, 1, 1, 1, 1, 0, 1, 0, 0),
    B_MAKE(0x19, 1, 1, 1, 1, 0, 3, 0, 0),
    B_MAKE(0x1A, 1, 1, 1, 1, 0, 3, 0, 0),
    B_MAKE(0x1B, 1, 1, 0, 1, 0, 5, 0, 0),
    B_MAKE(0x1C, 4, 1, 1, 1, 4, 3, 0, 0),
    B_MAKE(0x27, 1, 1, 1, 1, 0, 1, 0, 0),
    B_MAKE(0x1E, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x1F, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x20, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x21, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x22, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x22, 1, 1, 1, 1, 0, 0, 0, 4),
    B_MAKE(0x22, 1, 1, 1, 1, 0, 0, 0, 8),
    B_MAKE(0x22, 1, 1, 1, 1, 0, 0, 0, 12),
    B_MAKE(0x23, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x25, 8, 8, 0, 1, 0, 1, 10, 32),
    B_MAKE(0x05, 3, 1, 1, 1, 3, 0, 0, 0),
    B_MAKE(0x26, 1, 1, 1, 1, 0, 1, 3, 8),
    B_MAKE(0x26, 128, 1, 0, 1, 4, 6, 9, 8),
    B_MAKE(0x1D, 1, 1, 1, 1, 0, 1, 0, 0),
    B_MAKE(0x05, 12, 1, 1, 1, 2, 0, 7, 0),
    B_MAKE(0x28, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x29, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x2B, 1, 1, 1, 1, 0, 1, 2, 8),
    B_MAKE(0x2A, 1, 1, 1, 1, 0, 1, 2, 4),
    B_MAKE(0x2C, 1, 1, 1, 1, 0, 1, 2, 4),
    B_MAKE(0x2D, 1, 1, 1, 1, 0, 0, 2, 0),
    B_MAKE(0x09, 72, 1, 1, 1, 2, 3, 2, 16),
    B_MAKE(0x2E, 1, 1, 0, 1, 0, 0, 10, 18),
    B_MAKE(0x2F, 1, 1, 1, 1, 0, 6, 0, 0),
    B_MAKE(0x30, 1, 1, 0, 1, 0, 0, 10, 0),
    B_MAKE(0x31, 1, 1, 1, 1, 0, 1, 0, 0),
    B_MAKE(0x32, 1, 1, 0, 1, 0, 1, 0, 0),
    B_MAKE(0x33, 1, 1, 0, 1, 0, 1, 10, 0),
    B_MAKE(0x34, 1, 1, 1, 1, 0, 1, 0, 0),
    B_MAKE(0x35, 1, 1, 1, 1, 0, 1, 0, 0),
    B_MAKE(0x36, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x37, 1, 1, 1, 1, 0, 1, 0, 0),
    B_MAKE(0x38, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x39, 1, 1, 0, 1, 0, 0, 10, 0),
    B_MAKE(0x3A, 2, 1, 1, 1, 2, 0, 0, 0),
    B_MAKE(0x3B, 1, 1, 0, 1, 0, 1, 10, 20),
    B_MAKE(0x3C, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x3D, 1, 1, 1, 1, 0, 3, 0, 0),
    B_MAKE(0x3E, 96, 1, 1, 1, 4, 0, 3, 0),
    B_MAKE(0x3F, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x40, 1, 1, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x41, 1, 1, 1, 1, 0, 1, 0, 0),
    B_MAKE(0x02, 1, 1, 1, 1, 0, 1, 0, 0),
    B_MAKE(0x02, 4, 1, 1, 1, 2, 0, 6, 0),
    B_MAKE(0x02, 6, 6, 1, 1, 0, 0, 0, 0),
    B_MAKE(0x42, 1, 1, 0, 1, 0, 3, 0, 0),
    B_MAKE(0x44, 1, 1, 1, 1, 0, 0, 0, 0),
};

u16 g_RichterFactoryBlueprintPadding = 0;

u8 entity_ranges[7][2] = {
    {0x30, 0x3F}, {0x20, 0x2F}, {0x10, 0x1E}, {0x10, 0x3F},
    {0x1F, 0x1F}, {0x30, 0x30}, {0x10, 0x2F},
};

s16 pos_x_80154C50[] = {0, -4, -8, -12, -16, -20};

s32 velocity_x_80154C5C[] = {
    FIX(-0.1875), FIX(-0.25), FIX(-0.375), FIX(-0.5), FIX(-0.625), FIX(-0.75),
};

s16 rot_x_80154C74[] = {0x30, 0x40, 0x50, 0x60, 0x70, 0x80};

AnimationFrame anim_smoke_puff[] = {
    POSE(1, 0x01, 0), POSE(1, 0x02, 0), POSE(1, 0x03, 0), POSE(1, 0x04, 0),
    POSE(1, 0x05, 0), POSE(1, 0x06, 0), POSE(1, 0x07, 0), POSE(1, 0x08, 0),
    POSE(1, 0x09, 0), POSE(1, 0x0A, 0), POSE(1, 0x0B, 0), POSE(1, 0x0C, 0),
    POSE(1, 0x0D, 0), POSE(1, 0x0E, 0), POSE(1, 0x0F, 0), POSE(1, 0x10, 0),
    POSE(1, 0x11, 0), POSE(1, 0x12, 0), POSE(1, 0x13, 0), POSE(1, 0x14, 0),
    POSE(1, 0x15, 0), POSE(1, 0x16, 0), POSE(1, 0x17, 0), POSE(1, 0x18, 0),
    POSE_END,
};

u8 sensors1_80154CE4[] = {2, 9, 3, 10, 1, 8, 4, 11, 0, 7, 5, 12, 6, 13};
u8 sensors2_80154CF4[] = {2, 9, 3, 10, 4, 11, 5, 12, 6, 13};

typedef struct {
    u8 count;
    u8 red;
    u8 green;
    u8 blue;
    u8 width;
    u8 height;
    s16 zPriorityOffset;
    s16 drawMode;
    s16 variant;
    u32 flags;
} RicBloodParticleProperties;

typedef char RicBloodParticleProperties_size
    [sizeof(RicBloodParticleProperties) == 0x10 ? 1 : -1];

static RicBloodParticleProperties D_80154D00 = {
    0x08, 0xC0, 0x60, 0x00, 1, 1, 4, 0x33, 3, 0x08800000};
static RicBloodParticleProperties D_80154D10 = {
    0x10, 0xC0, 0xC0, 0xC0, 1, 1, 2, 0x33, 1, 0x0C800000};
static RicBloodParticleProperties D_80154D20 = {
    0x08, 0x7F, 0x7F, 0x7F, 2, 2, 2, 0x33, 0, 0x08800000};
static RicBloodParticleProperties D_80154D30 = {
    0x06, 0x7F, 0xFF, 0xFF, 1, 1, 4, 0x73, 3, 0x08800000};
static RicBloodParticleProperties D_80154D40 = {
    0x0C, 0xC0, 0x60, 0x00, 1, 1, 4, 0x33, 3, 0x08800000};
static RicBloodParticleProperties D_80154D50 = {
    0x0C, 0x7F, 0x00, 0x00, 3, 3, 2, 0x02, 4, 0x0C800000};
static RicBloodParticleProperties D_80154D60 = {
    0x08, 0x1F, 0x1F, 0x7F, 1, 1, 4, 0x33, 6, 0x0C800000};
static RicBloodParticleProperties D_80154D70 = {
    0x14, 0x7F, 0x7F, 0xC0, 1, 1, -2, 0x33, 7, 0x0C800000};
static RicBloodParticleProperties D_80154D80 = {
    0x06, 0xC0, 0xC0, 0xC0, 2, 2, 2, 0x7B, 8, 0x08800000};
static RicBloodParticleProperties D_80154D90 = {
    0x10, 0x7F, 0x7F, 0x7F, 1, 1, 2, 0x33, 9, 0x08800000};

RicBloodParticleProperties* D_80154DA0[] = {
    &D_80154D00, &D_80154D10, &D_80154D20, &D_80154D30, &D_80154D40,
    &D_80154D50, &D_80154D60, &D_80154D70, &D_80154D80, &D_80154D90,
};

AnimationFrame anim_80154DC8[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(2, 4, 0), POSE(2, 5, 0),
    POSE(2, 4, 0), POSE(2, 3, 0), POSE(2, 4, 0), POSE(2, 3, 0), POSE(2, 4, 0),
    POSE(2, 5, 0), POSE(1, 6, 0), POSE(1, 7, 0), POSE(1, 8, 0), POSE_END,
};

AnimationFrame anim_80154E04[] = {
    POSE(1, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE(2, 14, 0), POSE(2, 15, 0), POSE(2, 16, 0),
    POSE(2, 17, 0), POSE(2, 18, 0), POSE(3, 19, 0), POSE(4, 20, 0),
    POSE_END,
};

AnimationFrame anim_80154E38[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(2, 4, 0), POSE(2, 5, 0),
    POSE(2, 6, 0), POSE(2, 7, 0), POSE(2, 8, 0), POSE_END,
};

typedef struct {
    s16 xOffset;
    s16 yOffset;
    s32 velocityX;
    s32 velocityY;
    s16 timer;
    s16 textureIndex;
    u16 paletteIndex;
    u8 uBase;
    u8 vBase;
} RicMariaPowerProperties;

typedef char RicMariaPowerProperties_size
    [sizeof(RicMariaPowerProperties) == 0x14 ? 1 : -1];

RicMariaPowerProperties D_80154E5C[] = {
    {-0x40, 0, FIX(2.5), 0, 0x60, 0, 0, 0x80, 0x00},
    {0x40, 0, FIX(-2.5), 0, 0x48, 1, 1, 0x00, 0x80},
    {0, -0x40, 0, FIX(2.5), 0x30, 2, 2, 0x00, 0x00},
    {0, 0x40, 0, FIX(-2.5), 0x18, 3, 3, 0x80, 0x00},
};

u16 D_80154EAC[] = {8, 6, 5, 7};
s32 D_80154EB4[] = {FIX(5.0 / 3.0), FIX(-5.0 / 3.0), FIX(1.0 / 3.0), -0xD555};
s32 D_80154EC4[] = {FIX(-2.0), FIX(-5.0 / 3.0), FIX(-3.0), -0x25555};

AnimationFrame anim_maria_walk[] = {
    POSE(4, 1, 0), POSE(4, 2, 0), POSE(4, 3, 0), POSE(4, 4, 0), POSE(4, 5, 0),
    POSE(4, 6, 0), POSE(4, 7, 0), POSE(4, 8, 0), POSE_LOOP(0),
};

AnimationFrame anim_maria_offering_powers[] = {
    POSE(0x08, 0x09, 0), POSE(0x08, 0x0D, 0), POSE(0x40, 0x0A, 0),
    POSE(0x02, 0x0B, 0), POSE(0x02, 0x0C, 0), POSE(0x06, 0x0D, 0),
    POSE(0x07, 0x0E, 0), POSE(0x06, 0x0F, 0), POSE(0x05, 0x0E, 0),
    POSE(0x04, 0x0D, 0), POSE(0x03, 0x0F, 0), POSE(0x03, 0x0E, 0),
    POSE(0x03, 0x0D, 0), POSE(0x03, 0x0E, 0), POSE(0x03, 0x0F, 0),
    POSE(0x03, 0x0E, 0), POSE(0x03, 0x0D, 0), POSE(0x04, 0x0E, 0),
    POSE(0x05, 0x0F, 0), POSE(0x06, 0x0E, 0), POSE(0x07, 0x0D, 0),
    POSE(0x30, 0x0E, 0), POSE(0x0C, 0x09, 0), POSE(0x0D, 0x10, 0),
    POSE(0x08, 0x11, 0), POSE(0x0C, 0x12, 0), POSE(0xB0, 0x13, 0),
    POSE(0x0A, 0x14, 0), POSE(0x0A, 0x15, 0), POSE(0x0A, 0x16, 0),
    POSE(0x30, 0x17, 0), POSE(0xD0, 0x18, 0), POSE_END,
};

s32 D_80154F7C[16] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

s16 D_80154FBC[24][10] = {
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0080, 0x0080, 0x0080, 0x0060, 0x0031,
     0x0200},
    {0x0000, 0x0002, 0x0006, 0x015F, 0x0080, 0x0080, 0x0080, 0x0040, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0080, 0x7000, 0x7000, 0x0040, 0x0031,
     0x0140},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0080, 0x7000, 0x0100, 0x0010, 0x0031,
     0x0180},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0080, 0x7000, 0x7000, 0x0010, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x00A0, 0x7000, 0x00C0, 0x7000, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0080, 0x7000, 0x0080, 0x7002, 0x0031,
     0x0100},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0080, 0x0080, 0x7000, 0x0070, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0080, 0x7000, 0x0100, 0x7006, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0100, 0x0100, 0x0200, 0x7001, 0x0031,
     0x0100},
    {0x0000, 0x0000, 0x0000, 0x0166, 0x0080, 0x0080, 0x0080, 0x7005, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x0102, 0x0080, 0x7000, 0x7000, 0x0040, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0080, 0x7100, 0x0080, 0x7005, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0080, 0x0080, 0x0080, 0x7005, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x0102, 0x0080, 0x7000, 0x0100, 0x0040, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x0102, 0x0080, 0x7000, 0x0080, 0x0040, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x0102, 0x0080, 0x0080, 0x7000, 0x0000, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x0102, 0x0200, 0x0080, 0x0200, 0x0000, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0080, 0x0080, 0x7000, 0x0000, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0090, 0x0400, 0x0400, 0x7007, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x0102, 0x0080, 0x0080, 0x0080, 0x0000, 0x0031,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x015F, 0x0080, 0x0080, 0x0080, 0x0010, 0x0031,
     0x0200},
    {0x0008, 0x0000, 0x0008, 0x0165, 0x0080, 0x0080, 0x0080, 0x7007, 0x0051,
     0x0200},
    {0x0000, 0x0000, 0x0000, 0x0168, 0x7100, 0x7100, 0x0100, 0x7007, 0x0031,
     0x0200},
};

s16 D_8015519C[8][6] = {
    {0x0000, 0x0000, 0x0100, 0x0100, 0x0100, 0x0100},
    {0x0500, 0x0A00, 0x0100, 0x0100, 0x0100, 0x0000},
    {0x0000, 0x0000, 0x0100, 0x7000, 0x7000, 0x0200},
    {0x0000, 0x0000, 0x7100, 0x7100, 0x0100, 0x1000},
    {0x0000, 0x0000, 0x7100, 0x0100, 0x7000, 0x0800},
    {0x0000, 0x0000, 0x0100, 0x7100, 0x0100, 0x0400},
    {0x0500, 0x0A00, 0x0100, 0x0100, 0x0100, 0x0100},
    {0x0500, 0x0A00, 0x0100, 0x0200, 0x7100, 0x0100},
};

Point16 g_RichterIceShardPoints[] = {
    {-2, -24}, {0, -8},   {2, 8},    {0, 24},  {6, -12},  {8, 0},
    {7, 12},   {-8, -12}, {-9, 0},   {-7, 12}, {-14, -6}, {-15, 7},
    {13, -7},  {16, 8},   {-7, -22}, {6, -21}, {-8, 21},  {7, 22},
};

Point16* g_RichterIceShardTriangles[] = {
    &g_RichterIceShardPoints[0],  &g_RichterIceShardPoints[4],
    &g_RichterIceShardPoints[1],  &g_RichterIceShardPoints[4],
    &g_RichterIceShardPoints[5],  &g_RichterIceShardPoints[1],
    &g_RichterIceShardPoints[5],  &g_RichterIceShardPoints[2],
    &g_RichterIceShardPoints[1],  &g_RichterIceShardPoints[5],
    &g_RichterIceShardPoints[6],  &g_RichterIceShardPoints[2],
    &g_RichterIceShardPoints[6],  &g_RichterIceShardPoints[3],
    &g_RichterIceShardPoints[2],  &g_RichterIceShardPoints[2],
    &g_RichterIceShardPoints[3],  &g_RichterIceShardPoints[9],
    &g_RichterIceShardPoints[2],  &g_RichterIceShardPoints[9],
    &g_RichterIceShardPoints[8],  &g_RichterIceShardPoints[1],
    &g_RichterIceShardPoints[2],  &g_RichterIceShardPoints[8],
    &g_RichterIceShardPoints[1],  &g_RichterIceShardPoints[8],
    &g_RichterIceShardPoints[7],  &g_RichterIceShardPoints[1],
    &g_RichterIceShardPoints[7],  &g_RichterIceShardPoints[0],
    &g_RichterIceShardPoints[4],  &g_RichterIceShardPoints[12],
    &g_RichterIceShardPoints[5],  &g_RichterIceShardPoints[12],
    &g_RichterIceShardPoints[13], &g_RichterIceShardPoints[5],
    &g_RichterIceShardPoints[13], &g_RichterIceShardPoints[6],
    &g_RichterIceShardPoints[5],  &g_RichterIceShardPoints[7],
    &g_RichterIceShardPoints[8],  &g_RichterIceShardPoints[10],
    &g_RichterIceShardPoints[8],  &g_RichterIceShardPoints[11],
    &g_RichterIceShardPoints[10], &g_RichterIceShardPoints[8],
    &g_RichterIceShardPoints[9],  &g_RichterIceShardPoints[11],
    &g_RichterIceShardPoints[0],  &g_RichterIceShardPoints[7],
    &g_RichterIceShardPoints[14], &g_RichterIceShardPoints[0],
    &g_RichterIceShardPoints[15], &g_RichterIceShardPoints[4],
    &g_RichterIceShardPoints[3],  &g_RichterIceShardPoints[16],
    &g_RichterIceShardPoints[9],  &g_RichterIceShardPoints[6],
    &g_RichterIceShardPoints[17], &g_RichterIceShardPoints[3],
    &g_RichterIceShardPoints[14], &g_RichterIceShardPoints[7],
    &g_RichterIceShardPoints[10], &g_RichterIceShardPoints[15],
    &g_RichterIceShardPoints[12], &g_RichterIceShardPoints[4],
    &g_RichterIceShardPoints[11], &g_RichterIceShardPoints[9],
    &g_RichterIceShardPoints[16], &g_RichterIceShardPoints[13],
    &g_RichterIceShardPoints[17], &g_RichterIceShardPoints[6],
};

u16 g_RichterLightningPaletteIndices[] = {0x194, 0x199};

s32 g_RichterLightningColorFactors[] = {
    0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x7F, 0x3F, 0x7F,
};
