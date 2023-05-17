#include "dra.h"
#include "sfx.h"

void func_800E493C(void) {
    if (g_Settings.isSoundMono == false) {
        PlaySfx(SET_SOUNDMODE_STEREO);
    } else {
        PlaySfx(SET_SOUNDMODE_MONO);
    }
}

void func_800E4970(void) {
    SetGameState(Game_NowLoading);
    g_GameStep = 2;
    ClearBackbuffer();
    func_800E3574();
    func_800EAD7C();
    func_801065F4(0);
    func_800EDA94();
    func_800EA538(0);
    func_800ECE2C();
    func_800EAEEC();
    func_800EDAE4();
    PlaySfx(0x12);
    PlaySfx(0xB);
    func_80132760();
    func_800E493C();
}

void func_800E4A04(void) { s32 pad[3]; }

#if defined(VERSION_US)
INCLUDE_ASM("asm/us/dra/nonmatchings/play", HandlePlay);
#elif defined(VERSION_HD)
INCLUDE_ASM("asm/hd/dra/nonmatchings/play", HandlePlay);
#endif
