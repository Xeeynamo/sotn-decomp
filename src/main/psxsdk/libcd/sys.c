#include "common.h"

extern u8 CD_status;
extern u8 CD_mode;
extern u8 CD_com;

int CdStatus(void) { return CD_status; }

int CdMode(void) { return CD_mode; }

int CdLastCom(void) { return CD_com; }

extern int CD_pos;

int* CdLastPos(void) { return &CD_pos; }

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdReset);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdFlush);

extern s32 D_80032AB0;

s32 CdSetDebug(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_80032AB0;
    D_80032AB0 = arg0;
    return temp_v0;
}

const char aNone[] = "none";

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdComstr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdIntstr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdSync);

void CD_ready();

void CdReady(void) { CD_ready(); }

extern s32 CD_cbsync;

s32 CdSyncCallback(s32 arg0) {
    s32 temp_v0;

    temp_v0 = CD_cbsync;
    CD_cbsync = arg0;
    return temp_v0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdReadyCallback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdControl);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdControlF);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdControlB);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdMix);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdGetSector);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdDataCallback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdDataSync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdIntToPos);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdPosToInt);
