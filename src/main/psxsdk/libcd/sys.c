#include "libcd_internal.h"
#include <common.h>

extern u8 CD_status;

int CdStatus(void) { return CD_status; }

int CdMode(void) { return CD_mode; }

int CdLastCom(void) { return CD_com; }

extern int CD_pos;

int* CdLastPos(void) { return &CD_pos; }

int CdReset(int mode) {
    if (mode == 2) {
        CD_initintr();
        return 1;
    }

    if (CD_init()) {
        return 0;
    }

    if (mode == 1 && CD_initvol() != 0) {
        return 0;
    }

    return 1;
}

void CdFlush(void) { CD_flush(); }

extern s32 D_80032AB0;

s32 CdSetDebug(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_80032AB0;
    D_80032AB0 = arg0;
    return temp_v0;
}

extern char* D_80032AC8[];

char* CdComstr(unsigned char com) {
    if (com > 0x1b) {
        return "none";
    }

    return D_80032AC8[com];
}

extern char* D_80032B48[];

char* CdIntstr(u8 intr) {
    if (intr > 6) {
        return "none";
    }
    return D_80032B48[intr];
}

int CdSync(int mode, u_char* result) { return CD_sync(mode, result); }

int CdReady(int mode, u_char* result) { return CD_ready(mode, result); }

long CdSyncCallback(void (*func)(void)) {
    CdlCB old = CD_cbsync;
    CD_cbsync = func;
    return old;
}

long CdReadyCallback(void (*func)(void)) {
    CdlCB old = CD_cbready;
    CD_cbready = func;
    return old;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdControl);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdControlF);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdControlB);

int CdMix(CdlATV* vol) {
    CD_vol(vol);
    return 1;
}

int CdGetSector(void* madr, int size) { return CD_getsector(madr, size) == 0; }

void* DMACallback(int dma, void (*func)());

long CdDataCallback(void (*func)()) { return DMACallback(3, func); }

void CD_datasync(int);

void CdDataSync(int mode) { CD_datasync(mode); }

CdlLOC* CdIntToPos(int i, CdlLOC* p) {
    inline int ENCODE_BCD(n) { return ((n / 10) << 4) + (n % 10); }

    i += 150;
    p->sector = ENCODE_BCD(i % 75);
    p->second = ENCODE_BCD(i / 75 % 60);
    p->minute = ENCODE_BCD(i / 75 / 60);
    return p;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdPosToInt);
