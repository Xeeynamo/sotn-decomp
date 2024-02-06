#include <game.h>

extern void (*D_8013C000)(void);
extern void (*D_8013C004)(s32);
extern void (*D_8013C008)(void);
extern void (*D_8013C00C)(void);

void EntityAlucard(void);
void func_80109594(void);
void func_8011A4D0(void);
void func_8010BF64(Unkstruct_8010BF64* arg0);

static void Stub_8013C004(int isPrologue) { func_80109594(); }

void InitPlayerRic(void) {
    // TODO Richter is not yet implemented, fall back to Alucard
    g_PlayableCharacter = PLAYER_ALUCARD;

    g_PlOvl.D_8013C000 = EntityAlucard;
    g_PlOvl.D_8013C004 = Stub_8013C004;
    g_PlOvl.D_8013C008 = func_8011A4D0;
    g_PlOvl.D_8013C00C = func_8010BF64;
}
