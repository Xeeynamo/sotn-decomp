#include "common.h"
#include "game.h"
#include "objects.h"
#include "sfx.h"

typedef enum {
    E_NONE,
    E_ENTITYFACTORY,
} EntityIDs;

typedef enum {
    Player_Stand,
    Player_Walk,
    Player_Crouch,
    Player_Fall,
    Player_Jump,
    Player_MorphBat,
    Player_AlucardStuck,
    Player_MorphMist,
    Player_HighJump,
    Player_UnmorphBat,
    Player_Hit,
    Player_StatusStone,
    Player_BossGrab, // Darkwing Bat and Akmodan II
    Player_KillWater,
    Player_UnmorphMist,
    Player_SwordWarp, // Alucard Sword and Osafune Katana
    Player_Kill,
    Player_Unk17,
    Player_Teleport, // also Grand Cross and Spiral Axe
    Player_FlameWhip,
    Player_Hydrostorm,
    Player_ThousandBlades,
    Player_RichterFourHolyBeasts,
    Player_Slide,
    Player_Unk24, // MorphWolf and Richter's Tackle
    Player_Unk25, // UnMorphWolf and Sprint
    Player_SlideKick,
    Player_Unk27, // other item crashes
    Player_SpellDarkMetamorphosis = 32,
    Player_SpellSummonSpirit,
    Player_SpellHellfire,
    Player_SpellTetraSpirit,
    Player_Spell36,
    Player_SpellSoulSteal,
    Player_Unk38,
    Player_SpellSwordBrothers,
    Player_AxearmorStand,
    Player_AxearmorWalk,
    Player_AxearmorJump,
    Player_AxearmorHit,
} PlayerSteps;

extern SpriteParts* D_801530AC[];
extern SpriteParts* D_80153AA0[];
extern SpriteParts* D_80153D24[];
extern SpriteParts* D_801541A8[];
extern void func_80159C04(void);
extern void DestroyEntity(Entity* entity);
extern void func_8015BB80(void);
extern void func_8015C178(void);
extern void SetPlayerStep(PlayerSteps step);
void func_8015C920(AnimationFrame* unk0);
extern void func_8015C93C(s32 speed);
extern s32 func_8015C9CC(void);
extern void SetSpeedX(s32 speed);
extern void func_8015CCC8(s32 arg0, s32 velocityX);
extern void func_8015CD98(s32 velocityX);
extern void func_8015CDE0(s32);
extern void func_8015CE7C(void);
extern void func_8015CF08(void);
extern bool func_8015DBB0(s32);
extern void DebugShowWaitInfo(const char* str);
extern void func_8015F9F0(Entity* entity);
extern void func_8015FAB8(Entity*);
extern s32 func_8015FDB0(POLY_GT4* poly, s16 posX, s16 posY);
extern Entity* CreateEntFactoryFromEntity(Entity* entity, u32 arg1, s32 arg2);

// Forward declarations for all the entity updating functions
void func_801603B4(Entity* self);
void EntityEntFactory(Entity* self);
void func_80160FC4(Entity* self);
void EntityCrossBoomerang(Entity* self);
void func_80169C10(Entity* self);
void func_8016147C(Entity* self);
void func_80169D74(Entity* self);
void EntityHolyWater(Entity* self);
void EntityHolyWaterFlame(Entity* self);
void func_80161C2C(Entity* self);
void func_80166784(Entity* self);
void EntityHydroStorm(Entity* self);
void EntityGiantSpinningCross(Entity* self);
void EntitySubwpnCrashCross(Entity* self);
void func_80167A58(Entity* self);
void func_80167A60(Entity* self);
void func_8016779C(Entity* self);
void func_80167964(Entity* self);
void func_80161EF8(Entity* self);
void func_80167A68(Entity* self);
void EntityRichterRevivalColumn(Entity* self);
void func_80161FF0(Entity* self);
void func_80160C38(Entity* self);
void func_80160E4C(Entity* self);
void func_801623E0(Entity* self);
void func_80162604(Entity* self);
void func_80162C84(Entity* self);
void func_80162870(Entity* self);
void func_80160F0C(Entity* self);
void func_80162C7C(Entity* self);
void func_80162EF8(Entity* self);
void EntitySubwpnCrashCrossParticles(Entity* self);
void func_801641A0(Entity* self);
void EntityShrinkingPowerUpRing(Entity* self);
void func_80167A70(Entity* self);
void EntitySubwpnCrashAgunea(Entity* self);
void EntitySubwpnCrashAxe(Entity* self);
void func_8016B0C0(Entity* self);
void func_80160D2C(Entity* self);
void EntityHitByIce(Entity* self);
void EntityHitByLightning(Entity* self);
void EntitySubwpnReboundStone(Entity* self);
void EntitySubwpnThrownVibhuti(Entity* self);
void EntitySubwpnAgunea(Entity* self);
void EntityAguneaHitEnemy(Entity* self);
void EntitySubwpnCrashVibhuti(Entity* self);
void func_8016D328(Entity* self);
void func_8016E324(Entity* self);
void func_8016D9C4(Entity* self);
void func_8016DF74(Entity* self);
void func_8016E9E4(Entity* self);
void func_8016E46C(Entity* self);
void EntitySubwpnBible(Entity* self);
void func_80172AE8(Entity* self);
void func_801719A4(Entity* self);
void func_8017161C(Entity* self);
void func_801705EC(Entity* self);
void func_8016F198(Entity* self);
void EntityStopWatchExpandingCircle(Entity* self);
void func_8017091C(Entity* self);
void func_8016D920(Entity* self);
void func_801601DC(Entity* self);
void func_8015FEA8(Entity* self);
void StopwatchCrashDoneSparkle(Entity* self);
void func_80170548(Entity* self);
void EntityTeleport(Entity* self);

extern s32 func_8016840C(s16 x, s16 y);

extern s16 D_80154568[];
extern s32 D_80154570;
extern s16 D_80154574[];
extern s16 D_80154594[];
extern s32 D_8015459C;
extern s16 D_801545A8;
extern s16 D_801545AA;
extern s16 D_801545AC;
extern u8 D_801545B0[];
extern u8 D_801545C4[16];
extern u8 D_801545D4[16];
// These appear to be a set of collision boxes
extern s16_pair D_801545E4[4];
extern s16_pair D_801545F4[4];
extern s16_pair D_80154604[14];
extern u16 D_8015463C[4];
extern u16 D_80154644[4];
extern u16 D_8015464C[8];
extern u16 D_8015465C[4];
extern u16 D_80154664[8];
extern u8 D_80154674[][4];
extern SubweaponDef D_80154688[];
extern u8 D_801548F4[6][8];
extern AnimationFrame* D_80154924;
extern PfnEntityUpdate D_8015495C[];
extern s32 D_80154ED4;
extern s32 D_80154EF8;
extern s16_pair* D_80155244[72];
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
extern AnimationFrame* D_80154E38;
extern s16 D_80154EAC[];
extern s32 D_80154EB4[];
extern s32 D_80154EC4[];
extern unkStr80154E5C D_80154E5C[];
extern s16 D_8015519C[][6];
extern s16 D_80155364[];
extern s32 D_8015538C;
extern AnimationFrame* D_80155394;
extern AnimationFrame* D_8015539C;
extern AnimationFrame* D_801553BC;
extern AnimationFrame D_80155480[];
extern AnimationFrame* D_80155488;
extern AnimationFrame* D_801554B0;
extern AnimationFrame D_801554C0[];
extern AnimationFrame* D_801554C8;
extern AnimationFrame* D_801554D0;
extern AnimationFrame D_801554E0[];
extern AnimationFrame* D_801554F0;
extern AnimationFrame* D_8015550C;
extern AnimationFrame D_80155528[];
extern AnimationFrame D_80155534[];
extern AnimationFrame D_8015555C[];
extern AnimationFrame D_80155588[];
extern AnimationFrame D_801555A8[];
extern AnimationFrame D_801555C8[];
extern AnimationFrame D_801555E8[];
extern AnimationFrame D_80155608[];
extern AnimationFrame D_80155638[];
extern AnimationFrame D_80155658[];
extern AnimationFrame* D_80155670;
extern AnimationFrame D_80155694[];
extern AnimationFrame D_8015569C[];
extern AnimationFrame D_801556C4[];
extern AnimationFrame D_80155704[];
extern AnimationFrame D_80155730[];
extern AnimationFrame D_80155738[];
extern AnimationFrame D_80155740[];
extern AnimationFrame* D_80155748;
extern AnimationFrame* D_80155750;
extern AnimationFrame* D_8015577C;
extern AnimationFrame* D_80155788;
extern AnimationFrame* D_8015579C;
extern AnimationFrame D_80155738[];
extern AnimationFrame D_801557AC[];
extern AnimationFrame* D_801557D8;
extern AnimationFrame D_80155840[];
extern AnimationFrame* D_801558B4;
extern AnimationFrame* D_801558D4;
extern AnimationFrame D_801558E4[];
extern AnimationFrame* D_801558DC;
extern AnimationFrame* D_8015591C;
extern AnimationFrame* D_80155950;
extern FrameProperty D_80155964;
extern Point16 D_801559AC[];
extern Point16 D_801559C8[];
extern Point16 D_801559E4[];
extern s16 D_80155A08;
extern Point16 D_80155A1C[];
extern s16 D_80155A40[];
extern Point16 D_80155A54[];
extern s16 D_80155A78[];
extern Point32 D_80155AAC[];
extern Point32 D_80155AE4[];
extern s32 D_80155B2C[9][9];
extern s16 D_80155C70[];
extern s16 D_80155C78[];
extern u16 D_80155C98[];
extern s16 D_80155CB8[];
extern s16 D_80155CCC[];
extern s16 D_80155CE0[];
extern s16 D_80155CF4[];
extern s16 D_80155D08[];
extern s16 D_80155D1C[];
extern s16 D_80155D30;
extern s16 D_80155D64[4][6];
extern Point32 D_80155D9C[];
extern u16 D_80155DDC[0x30];
extern RECT D_80155E3C;
extern AnimationFrame D_80155E44[];
extern s16 D_80155E68[];
extern u8 D_80155E70[][4];
extern AnimationFrame* D_80155EA8;
extern s16 D_80155EF0[];
extern SVECTOR* D_8015607C[][4];
extern s8 D_80156A28;
extern u8 D_8015635C[][5];
extern s8 D_80156904;
extern SVECTOR D_80156C50;
extern SVECTOR D_80156C58;
extern s32 D_80173B64;
extern s32 D_80174F74;
extern s32 D_80174F78;
extern s32 g_DebugWaitInfoTimer;
extern s32 D_80174F80[];
extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;
extern s16_pair D_80174FBC[];
extern s32 D_80174FFC;
extern s16_pair D_80175000[32];
extern s32 D_80175080;
extern s32 D_80175084;
extern Point16 D_80175088[][128];
extern s32 D_80175888;
extern s32 D_80175890;
extern s16_pair D_80175894[];
extern s32 D_801758AC;
extern s32 D_801758B0[];
extern Entity* D_801758CC[];
extern u32 D_801758D0;
extern ButtonComboState D_801758E0;
extern ButtonComboState D_801758E4;
extern u16 D_80175950;
extern u16 D_80175952;
extern u16 D_80175954;
extern s16 D_80175956;
extern s32 D_80175958[];
extern s32 D_801759D8[];