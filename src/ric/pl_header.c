#include "ric.h"

void RicMain(void);
void RicInit(s16 arg0);
void func_801603C4(void);
void func_8015E7B4(Unkstruct_8010BF64* arg0);

PlayerOvl RIC_player = {
    RicMain,
    RicInit,
    func_801603C4,
    func_8015E7B4,
};

s32* D_8013C010[4] = {
    &D_8013C010[LEN(D_8013C010)], &D_8013C010[LEN(D_8013C010)],
    &D_8013C010[LEN(D_8013C010)], &D_8013C010[LEN(D_8013C010)]};
