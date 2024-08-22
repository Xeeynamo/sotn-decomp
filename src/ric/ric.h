// SPDX-License-Identifier: AGPL-3.0-only
#include <game.h>
#include <sfx.h>

typedef enum {
    E_NONE,
    E_ENTITYFACTORY,
} EntityIDs;

#define GAME_OVER 0x80000
#define NO_AFTERIMAGE 0x08000000

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
    PL_T_9,
    PL_T_10,
    PL_T_RUN,
    PL_T_12,
    PL_T_INVINCIBLE,
    PL_T_INVINCIBILITY_CONSUMABLE,
    PL_T_15,
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
};

#define NO_AFTERIMAGE 0x08000000

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
extern s32 func_8015FDB0(POLY_GT4* poly, s16 posX, s16 posY);
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
extern u8 D_801548F4[6][8];
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
extern AnimationFrame ric_ric_anim_stand_in_air[];
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
