
#include "common.h"
#include "game.h"
#include "objects.h"
#include "sfx.h"

typedef enum {
    E_NONE,
    E_UNK_1,
} EntityIDs;

typedef enum {
    Dummy,
} PlayerSteps;

extern void func_80159C04(void);
extern void func_80156C60(Entity* entity);
extern void func_8015BB80(void);
extern void func_8015C178(void);
extern void SetPlayerStep(PlayerSteps step);
void func_8015C920(AnimationFrame* unk0);
extern void func_8015C93C(s32 speed);
extern s32 func_8015C9CC(void);
extern void func_8015CA84(s32 speed);
extern void func_8015CCC8(s32 arg0, s32 accelerationX);
extern void func_8015CD98(s32 accelerationX);
extern void func_8015CDE0(s32);
extern void func_8015CE7C(void);
extern void func_8015CF08(void);
extern void func_8015D020(void);
extern bool func_8015DBB0(s32);
extern void func_8015E380(const char* str);
extern void func_8015F9F0(Entity* entity);
extern void func_8015FAB8(Entity*);
extern s32 func_8015FDB0(POLY_GT4* poly, s16 posX, s16 posY);
extern Entity* func_801606BC(Entity* entity, u32 arg1, s32 arg2);
extern void func_80162604(Entity* entity);
extern void func_80167964(Entity* entity);
extern s32 func_8016840C(s16 x, s16 y);
extern void func_80169C10(Entity* entity);
extern void func_80169D74(Entity* entity);

extern s32 D_80154570;
extern s32 D_8015459C;
extern s16 D_801545A8;
extern s16 D_801545AA;
extern s16 D_801545AC;
extern s16 D_801545EA[];
extern s16 D_80154604;
extern s16 D_80154606;
extern u8 D_80154674[][4];
extern SubweaponDef D_80154688[];
extern AnimationFrame* D_80154924;
extern s32 D_80154ED4;
extern s32 D_80154EF8;
extern s32 D_80155368[];
extern AnimationFrame* D_80155394;
extern AnimationFrame* D_8015539C;
extern AnimationFrame* D_801553BC;
extern AnimationFrame* D_80155488;
extern AnimationFrame* D_801554B0;
extern AnimationFrame* D_801554C0;
extern AnimationFrame* D_801554C8;
extern AnimationFrame* D_801554D0;
extern AnimationFrame* D_801554F0;
extern AnimationFrame* D_8015550C;
extern AnimationFrame* D_80155528;
extern AnimationFrame* D_80155534;
extern AnimationFrame* D_8015555C;
extern AnimationFrame* D_801555A8;
extern AnimationFrame D_801555E8[];
extern AnimationFrame D_80155638[];
extern AnimationFrame* D_80155670;
extern AnimationFrame* D_80155730;
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
extern s8 D_80156904;
extern s32 D_80174F74;
extern s32 D_80174F78;
extern s32 D_80174F7C;
extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;
extern s32 D_80174FFC;
extern s32 D_80175080;
extern u16 D_80175950;
extern u16 D_80175952;
extern u16 D_80175954;
extern s16 D_80175956;
