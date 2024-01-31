#include <game.h>

extern void (*D_8013C000)(void);
extern void (*D_8013C004)(s32);
extern void (*D_8013C008)(void);
extern void (*D_8013C00C)(void);

void EntityAlucard(void);
void func_80109594(void);
void func_8011A4D0(void);
void func_8010BF64(Unkstruct_8010BF64* arg0);

void InitPlayerRic(void) {
    // TODO Richter is not yet implemented, fall back to Alucard
    g_PlayableCharacter = PLAYER_ALUCARD;
    D_8013C000 = EntityAlucard;
    D_8013C004 = func_80109594;
    D_8013C008 = func_8011A4D0;
    D_8013C00C = func_8010BF64;
}
