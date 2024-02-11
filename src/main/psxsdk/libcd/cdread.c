#include "common.h"
#include "psxsdk/libcd.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/cdread", cb_read);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/cdread", cd_read_retry);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/cdread", CdRead);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/cdread", CdReadSync);

extern CdlCB CD_ReadCallbackFunc;

CdlCB CdReadCallback(CdlCB func) {
    CdlCB prevFunc = CD_ReadCallbackFunc;
    CD_ReadCallbackFunc = func;
    return prevFunc;
}
