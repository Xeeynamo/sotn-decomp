#include "libcd_internal.h"

extern u8 CD_status;
extern u8 CD_mode;
extern u8 CD_com;

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

void CD_flush();

void CdFlush(void) { CD_flush(); }

extern s32 D_80032AB0;

s32 CdSetDebug(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_80032AB0;
    D_80032AB0 = arg0;
    return temp_v0;
}

const char aNone[] = "none";
extern char* D_80032AC8[];

char* CdComstr(u8 arg0) {
    if (arg0 > 0x1b) {
        return &aNone;
    }

    return D_80032AC8[arg0];
}

extern char* D_80032B48[];

char* CdIntstr(u8 intr) {
    if (intr > 6) {
        return &aNone;
    }
    return D_80032B48[intr];
}

void CD_sync();

void CdSync(void) { CD_sync(); }

void CD_ready();

void CdReady(void) { CD_ready(); }

long CdSyncCallback(void(*arg0)(void)) {
    CDCallback temp_v0;

    temp_v0 = CD_cbsync;
    CD_cbsync = arg0;
    return temp_v0;
}

long CdReadyCallback(void (*func)(void)) {
    void (*temp_v0)(u8, u8*);

    temp_v0 = CD_cbready;
    CD_cbready = func;
    return temp_v0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdControl);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdControlF);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdControlB);

void CD_vol();

s32 CdMix(void) {
    CD_vol();
    return 1;
}

s32 CD_getsector();

s32 CdGetSector(void) { return CD_getsector() == 0; }

void* DMACallback(int dma, void (*func)());

void CdDataCallback(void (*func)()) { DMACallback(3, func); }

void CD_datasync(int);

void CdDataSync(int mode) { CD_datasync(mode); }

// TODO: fix libcd.h
/* Location */
typedef struct {
    u_char minute;
    u_char second;
    u_char sector;
    u_char track;
} CdlLOC;

CdlLOC* CdIntToPos(int i, CdlLOC* p) {
    inline int ENCODE_BCD(n) {
        return ((n / 10) << 4) + (n % 10);
    }

    i += 150;
    p->sector = ENCODE_BCD(i % 75);
    p->second = ENCODE_BCD(i / 75 % 60);
    p->minute = ENCODE_BCD(i / 75 / 60);
    return p;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/sys", CdPosToInt);
