#include "ric.h"

void UpdateEntityRichter(void);
void func_80156F40(s16 arg0);
void func_801603C4(void);
void func_8015E7B4(Unkstruct_8010BF64* arg0);

PlayerOvl RichterBelmont[] = {
    /* 0x00 */ UpdateEntityRichter,
    /* 0x04 */ func_80156F40,
    /* 0x08 */ func_801603C4,
    /* 0x0C */ func_8015E7B4,
};

s32* D_8013C010[4] = {
    &D_8013C010[LEN(D_8013C010)], &D_8013C010[LEN(D_8013C010)],
    &D_8013C010[LEN(D_8013C010)], &D_8013C010[LEN(D_8013C010)]};
