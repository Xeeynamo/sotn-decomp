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
extern void func_8015D020(void);
extern bool func_8015DBB0(s32);
extern void DebugShowWaitInfo(const char* str);
extern void func_8015F9F0(Entity* entity);
extern void func_8015FAB8(Entity*);
extern s32 func_8015FDB0(POLY_GT4* poly, s16 posX, s16 posY);
extern Entity* CreateEntFactoryFromEntity(Entity* entity, u32 arg1, s32 arg2);
extern void func_80162604(Entity* entity);
extern void func_80167964(Entity* entity);
extern s32 func_8016840C(s16 x, s16 y);
extern void func_80169C10(Entity* entity);
extern void func_80169D74(Entity* entity);

extern s16 D_80154568[];
extern s32 D_80154570;
extern s32 D_8015459C;
extern s16 D_801545A8;
extern s16 D_801545AA;
extern s16 D_801545AC;
extern s16 D_801545EA[];
extern s16_pair D_80154604[];
extern u8 D_80154674[][4];
extern SubweaponDef D_80154688[];
extern AnimationFrame* D_80154924;
extern s32 D_80154ED4;
extern s32 D_80154EF8;
extern s32 D_80155368[];
extern AnimationFrame D_80154C80[];
extern AnimationFrame D_80154DC8[];
extern AnimationFrame D_80154E04[];
extern AnimationFrame* D_80154E38;
extern AnimationFrame* D_80155394;
extern AnimationFrame* D_8015539C;
extern AnimationFrame* D_801553BC;
extern AnimationFrame D_80155480[];
extern AnimationFrame* D_80155488;
extern AnimationFrame* D_801554B0;
extern AnimationFrame* D_801554C0;
extern AnimationFrame* D_801554C8;
extern AnimationFrame* D_801554D0;
extern AnimationFrame* D_801554F0;
extern AnimationFrame* D_8015550C;
extern AnimationFrame D_80155528[];
extern AnimationFrame* D_80155534;
extern AnimationFrame D_8015555C[];
extern AnimationFrame* D_801555A8;
extern AnimationFrame D_801555E8[];
extern AnimationFrame D_80155638[];
extern AnimationFrame* D_80155670;
extern AnimationFrame* D_80155730;
extern AnimationFrame D_80155740[];
extern AnimationFrame* D_80155748;
extern AnimationFrame* D_80155750;
extern AnimationFrame* D_8015577C;
extern AnimationFrame* D_80155788;
extern AnimationFrame* D_8015579C;
extern AnimationFrame* D_801557D8;
extern AnimationFrame* D_801558B4;
extern AnimationFrame* D_801558D4;
extern AnimationFrame* D_801558DC;
extern AnimationFrame* D_8015591C;
extern AnimationFrame* D_80155950;
extern s16 D_80155CB8[];
extern s16 D_80155CCC[];
extern s16 D_80155CE0[];
extern s16 D_80155CF4[];
extern s16 D_80155D08[];
extern s16 D_80155D1C[];
extern s16 D_80155D30;
extern s16 D_80155E68[];
extern AnimationFrame* D_80155EA8;
extern SVECTOR* D_8015607C[][4];
extern u8 D_8015635C[][5];
extern s8 D_80156904;
extern SVECTOR D_80156C50;
extern SVECTOR D_80156C58;
extern s32 D_80174F74;
extern s32 D_80174F78;
extern s32 g_DebugWaitInfoTimer;
extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;
extern s32 D_80174FFC;
extern s32 D_80175080;
extern s32 D_801758B0[];
extern Entity* D_801758CC[];
extern u32 D_801758D0;
extern u16 D_80175950;
extern u16 D_80175952;
extern u16 D_80175954;
extern s16 D_80175956;
extern s32 D_80175958[];
extern s32 D_801759D8[];