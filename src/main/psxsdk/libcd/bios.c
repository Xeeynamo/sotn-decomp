#include "common.h"

const char D_800106B4[] = "%s:(%s) Sync=%s, Ready=%s\n";

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", getintr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_sync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_ready);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_cw);

const char aIdBiosCV177199[] =
    "$Id: bios.c,v 1.77 1996/05/13 06:58:16 suzu Exp $";

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_vol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_flush);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_initvol);

void* InterruptCallback(int irq, void (*f)());
int ResetCallback(void);
extern s32 CD_cbready;
extern s32 CD_cbsync;
extern s32 CD_status;
extern s32 CD_status1;
extern s32 callback;

void CD_initintr(void) {
    CD_cbready = 0;
    CD_cbsync = 0;
    CD_status1 = 0;
    CD_status = 0;
    ResetCallback();
    InterruptCallback(2, &callback);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_init);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_datasync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_getsector);

extern int CD_TestParmNum;

void CD_set_test_parmnum(int parmNum) { CD_TestParmNum = parmNum; }

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", callback);
