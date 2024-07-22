#include "common.h"

const char D_800106B4[] = "%s:(%s) Sync=%s, Ready=%s\n";

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", getintr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_sync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_ready);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_cw);

const char aIdBiosCV177199[] =
    "$Id: bios.c,v 1.77 1996/05/13 06:58:16 suzu Exp $";

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_vol);

void CD_flush();

void CdFlush(void) {
    CD_flush();
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_initvol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_initintr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_init);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_datasync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_getsector);

extern int CD_TestParmNum;

void CD_set_test_parmnum(int parmNum) { CD_TestParmNum = parmNum; }

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", callback);
