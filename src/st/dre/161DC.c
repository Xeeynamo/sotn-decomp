#include "dre.h"

void func_801961DC(s16 arg0) {
    s16 temp_v0 = arg0 - g_unkGraphicsStruct.unkC;

    if (temp_v0 > 1) {
        g_unkGraphicsStruct.unkC++;
    } else if (temp_v0 < -1) {
        g_unkGraphicsStruct.unkC--;
    } else {
        g_unkGraphicsStruct.unkC = arg0;
    }
}

INCLUDE_ASM("st/dre/nonmatchings/161DC", EntityUnkId21);

// appears to load from the CD and freeze the game
INCLUDE_ASM("st/dre/nonmatchings/161DC", EntityUnkId23);
