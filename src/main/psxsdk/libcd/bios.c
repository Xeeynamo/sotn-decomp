#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", getintr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_sync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_ready);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_cw);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_vol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_flush);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_initvol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_initintr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_init);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_datasync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_getsector);

extern int CD_TestParmNum;

void CD_set_test_parmnum(int parmNum) { CD_TestParmNum = parmNum; }

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", callback);
