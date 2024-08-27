#include "ric.h"

void RicMain(void);
void RicInit(s16 arg0);
void RicUpdatePlayerEntities(void);
void func_8015E7B4(Unkstruct_8010BF64* arg0);

PlayerOvl RIC_player = {
    RicMain,
    RicInit,
    RicUpdatePlayerEntities,
    func_8015E7B4,
};

s32* D_8013C010[4] = {
    &D_8013C010[LEN(D_8013C010)], &D_8013C010[LEN(D_8013C010)],
    &D_8013C010[LEN(D_8013C010)], &D_8013C010[LEN(D_8013C010)]};
