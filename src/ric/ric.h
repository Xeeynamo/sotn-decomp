#include <game.h>
#include <sfx.h>

typedef enum {
    E_NONE,
    E_ENTITYFACTORY,
} EntityIDs;

// Richter mostly uses the same steps as Alucard, or uses unused Alucard steps.
// There are a couple steps that mean one thing for Alucard, and another for
// Richter. This enum handles Richter's version of the ones that overlap.
enum RicSteps {
    PL_S_STAND,
    PL_S_WALK,
    PL_S_CROUCH,
    PL_S_FALL,
    PL_S_JUMP,
    PL_S_5,
    PL_S_6,
    PL_S_7,
    PL_S_HIGHJUMP,
    PL_S_9,
    PL_S_HIT,
    PL_S_11,
    PL_S_BOSS_GRAB,
    PL_S_13,
    PL_S_14,
    PL_S_15,
    PL_S_DEAD,
    PL_S_17,
    PL_S_STAND_IN_AIR,
    PL_S_FLAME_WHIP,
    PL_S_HYDROSTORM,
    PL_S_THROW_DAGGERS,
    PL_S_22,
    PL_S_23,
    PL_S_BLADEDASH,
    PL_S_RUN,
    PL_S_26,
    PL_S_SUBWPN_CRASH,

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
    PL_T_9,
    PL_T_10,
    PL_T_RUN,
    PL_T_12,
    PL_T_INVINCIBLE,
    PL_T_INVINCIBILITY_CONSUMABLE,
    PL_T_15,
};

#define NO_AFTERIMAGE 0x08000000

extern s16* D_801530AC[];
extern SpriteParts* D_80153AA0[];
extern SpriteParts* D_80153D24[];
extern SpriteParts* D_801541A8[];
extern s32 D_80154F7C[];
extern s16 D_80154FBC[][10];
extern void func_80159C04(void);
extern void DestroyEntity(Entity* entity);
extern void func_8015BB80(void);
extern void RicHandleBladeDash(void);
extern void RicSetStep(int step);
void RicSetAnimation(AnimationFrame* anim);
extern void RicDecelerateX(s32 speed);
extern s32 RicCheckMovement(void);
extern void RicSetSpeedX(s32 speed);
extern void RicSetCrouch(s32 arg0, s32 velocityX);
extern void RicSetStand(s32 velocityX);
extern void RicSetWalk(s32);
extern void RicSetRun(void);
extern void func_8015CF08(void);
extern bool func_8015DBB0(s32);
static void DebugShowWaitInfo(const char* str);
extern void func_8015F9F0(Entity* entity);
extern void RicSetSubweaponParams(Entity*);
extern s32 func_8015FDB0(POLY_GT4* poly, s16 posX, s16 posY);
extern Entity* RicCreateEntFactoryFromEntity(
    Entity* entity, u32 arg1, s32 arg2);

// Forward declarations for all the entity updating functions
void func_801603B4(Entity* self);
void RicEntityEntFactory(Entity* self);
void func_80160FC4(Entity* self);
void EntityCrossBoomerang(Entity* self);
void func_80169C10(Entity* self);
void func_8016147C(Entity* self);
void EntityCrossShadow(Entity* self);
void RicEntityHolyWater(Entity* self);
void RicEntityHolyWaterFlame(Entity* self);
void func_80161C2C(Entity* self);
void func_80166784(Entity* self);
void EntityHydroStorm(Entity* self);
void RicEntityGiantSpinningCross(Entity* self);
void RicEntitySubwpnCrashCross(Entity* self);
void func_80167A58(Entity* self);
void func_80167A60(Entity* self);
void func_8016779C(Entity* self);
void func_80167964(Entity* self);
void func_80161EF8(Entity* self);
void func_80167A68(Entity* self);
void EntityRichterRevivalColumn(Entity* self);
void func_80161FF0(Entity* self);
void func_80160C38(Entity* self);
void BladeDashHelper(Entity* self);
void func_801623E0(Entity* self);
void func_80162604(Entity* self);
void func_80162C84(Entity* self);
void func_80162870(Entity* self);
void func_80160F0C(Entity* self);
void func_80162C7C(Entity* self);
void RicEntityPlayerBlinkWhite(Entity* self);
void RicEntitySubwpnCrashCrossParticles(Entity* self);
void func_801641A0(Entity* self);
void EntityShrinkingPowerUpRing(Entity* self);
void func_80167A70(Entity* self);
void EntitySubwpnCrashAgunea(Entity* self);
void EntitySubwpnCrashAxe(Entity* self);
void RicEntitySubwpnThrownDagger(Entity* self);
void func_80160D2C(Entity* self);
void RicEntityHitByIce(Entity* self);
void RicEntityHitByLightning(Entity* self);
void RicEntitySubwpnReboundStone(Entity* self);
void RicEntitySubwpnThrownVibhuti(Entity* self);
void RicEntitySubwpnAgunea(Entity* self);
void RicEntityAguneaHitEnemy(Entity* self);
void EntitySubwpnCrashVibhuti(Entity* self);
void RicEntityVibhutiCrashCloud(Entity* self);
void func_8016E324(Entity* self);
void func_8016D9C4(Entity* self);
void func_8016DF74(Entity* self);
void EntityBiblePage(Entity* self);
void EntityBiblePageBeam(Entity* self);
void RicEntitySubwpnBible(Entity* self);
void func_80172AE8(Entity* self);
void EntityStopwatch(Entity* self);
void EntityStopwatchCircle(Entity* self);
void func_801705EC(Entity* self);
void func_8016F198(Entity* self);
void EntityAguneaCircle(Entity* self);
void EntityAguneaLightning(Entity* self);
void func_8016D920(Entity* self);
void func_801601DC(Entity* self);
void func_8015FEA8(Entity* self);
void StopwatchCrashDoneSparkle(Entity* self);
void func_80170548(Entity* self);
extern void RicEntityTeleport(Entity* self);

extern s32 func_8016840C(s16 x, s16 y);

extern s16 D_80154568[];
extern s32 g_IsPrologueStage;
extern s16 D_80154574[];
extern s16 D_80154594[];
extern s32 D_8015459C;
extern RECT D_801545A0;
extern s16 D_801545A8;
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
extern u8 D_801548F4[6][8];
extern AnimationFrame D_80154924[];
extern PfnEntityUpdate D_8015495C[];
extern AnimationFrame D_80154ED4[];
extern AnimationFrame D_80154EF8[];
extern Point16* D_80155244[72];
extern s32 D_80155368[];
extern FactoryBlueprint g_RicFactoryBlueprints[];
extern u8 D_80154C40[];
extern u16 D_80154C50[];
extern s32 D_80154C5C[];
extern u16 D_80154C74[];
extern AnimationFrame D_80154C80[];
extern u8 D_80154CE4[];
extern u8 D_80154CF4[];
extern unkStr_8011E4BC* D_80154DA0[];
extern AnimationFrame D_80154DC8[];
extern AnimationFrame D_80154E04[];
extern AnimationFrame D_80154E38[];
extern s16 D_80154EAC[];
extern s32 D_80154EB4[];
extern s32 D_80154EC4[];
extern unkStr80154E5C D_80154E5C[];
extern s16 D_8015519C[][6];
extern s16 D_80155364[];
extern AnimationFrame* D_8015538C[];
extern AnimationFrame D_80155394[];
extern AnimationFrame D_8015539C[];
extern AnimationFrame anim_stand[];
extern AnimationFrame D_80155480[];
extern AnimationFrame ric_anim_walk[];
extern AnimationFrame anim_land_strong_impact[];
extern AnimationFrame anim_crouch[];
extern AnimationFrame anim_land_from_run[];
extern AnimationFrame anim_crouch_from_stand[];
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
extern AnimationFrame D_80155730[];
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
extern Point16 D_801559AC[];
extern Point16 D_801559C8[];
extern Point16 D_801559E4[];
extern s16 D_80155A08[];
extern Point16 D_80155A1C[];
extern s16 D_80155A40[];
extern Point16 D_80155A54[];
extern s16 D_80155A78[];
extern Point32 D_80155AAC[];
extern Point32 D_80155AE4[];
extern s32 D_80155B2C[][9];
extern s16 D_80155C70[4];
extern s16 D_80155C78[];
extern u16 D_80155C98[];
extern s16 D_80155CB8[];
extern s16 D_80155CCC[];
extern s16 D_80155CE0[];
extern s16 D_80155CF4[];
extern s16 D_80155D08[];
extern s16 D_80155D1C[];
extern s16 D_80155D30[];
extern s16 D_80155D64[4][6];
extern Point32 D_80155D9C[];
extern u16 D_80155DDC[0x30];
extern RECT D_80155E3C;
extern AnimationFrame D_80155E44[];
extern s16 D_80155E68[];
extern u8 D_80155E70[][4];
extern s16 D_80155E98[];
extern AnimationFrame D_80155EA8[];
extern s32 D_80155EE0[];
extern s16 D_80155EF0[];
extern SVECTOR* D_8015607C[][4];
extern s8 D_80156A28;
extern u8 D_8015635C[];
extern s8 D_80156904;
extern s32 D_80173B64;
extern u8 D_80173B68[];
extern s16 D_80174F68;
extern s16 D_80174F6C;
extern s32 D_80174F70;
extern s32 D_80174F74;
extern s32 D_80174F78;
extern s32 g_DebugWaitInfoTimer;
extern s32 D_80174F80[];
extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;
extern Point16 D_80174FBC[];
extern s32 D_80174FFC;
extern Point16 D_80175000[32];
extern u32 D_80175080;
extern s32 D_80175084;
extern Point16 D_80175088[][128];
extern s32 D_80175888;
extern s32 D_8017588C;
extern s32 D_80175890;
extern Point16 g_BiblePos[];
extern s32 D_801758AC;
extern s32 g_AguneaParams[];
extern Entity* D_801758CC[];
extern u32 D_801758D0;
extern ButtonComboState g_bladeDashButtons;
extern ButtonComboState D_801758E4;
extern u16 g_RicDebugCurFrame;
extern u16 g_RicDebugDrawFlags;
extern u16 g_RicDebugPalette;
extern s16 g_IsRicDebugEnter;
extern s32 D_80175958[];
extern s32 D_801759D8[];
