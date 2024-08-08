#include <game.h>

extern void (*D_8013C000)(void);
extern void (*D_8013C004)(s32);
extern void (*D_8013C008)(void);
extern void (*D_8013C00C)(void);

static void Stub_8013C004(int isPrologue) { func_80109594(); }

void UpdateEntityRichter(void);
void func_80156F40(s16 arg0);
void func_801603C4(void);
void func_8015E7B4(Unkstruct_8010BF64* arg0);

void InitPlayerRic(void) {
    g_PlayableCharacter = PLAYER_RICHTER;

    g_PlOvl.D_8013C000 = UpdateEntityRichter;
    g_PlOvl.D_8013C004 = func_80156F40;
    g_PlOvl.D_8013C008 = func_801603C4;
    g_PlOvl.D_8013C00C = func_8015E7B4;
}
