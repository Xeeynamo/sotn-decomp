#include "faerie.h"

s16 D_us_80172C24[] = {
    0x0000,0x0022,
    0x0472,0xFFFF,
    0x000E,0x0000
};

s16 D_us_80172C30[] = {
    0x0000,0x0022,
    0x0473,0xFFFF,
    0x000E,0x0000
};

FaerieUnkRankedLookup_6504 D_us_80172C3C = {
    0x0000007F, D_us_80172C24,
    0x000000FF, D_us_80172C30
};

s16 D_us_80172C4C[] = {
    0x0000,0x0026,
    0x0476,0xFFFF,
    0x000E,0x0000
};

s16 D_us_80172C58[] = {
    0x0000,0x0026,
    0x0479,0xFFFF,
    0x000E,0x0000
};

s32 D_us_80172C64[1] = {
    0x0000007F
};
s32 D_us_80172C68 [3] = {
    D_us_80172C4C,
    0x000000FF,
    D_us_80172C58
};

/*  Once func_us_80176504 is merged, this is the correct layout.
FaerieUnkRankedLookup_6504 D_us_80172C64 = {
    0x0000007F, D_us_80172C4C,
    0x000000FF, D_us_80172C58
};
*/