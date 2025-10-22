// SPDX-License-Identifier: MIT
#include "libcd_internal.h"
#include <common.h>

#include "registers.h"

extern CdlCB CD_cbready;
extern CdlCB CD_cbsync;
extern int CD_status;
extern unsigned char CD_mode;
extern unsigned char CD_com;
extern unsigned char CD_pos[];
extern int D_80032AB0;
extern char* D_80032AC8[];
extern char* D_80032B48[];

static int D_80032A24[] = {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0};

inline char CdStatus(void) { return CD_status; }

int CdMode(void) { return CD_mode; }

int CdLastCom(void) { return CD_com; }

unsigned char* CdLastPos(void) { return CD_pos; }

int CdReset(int mode) {
    if (mode == CdlModeAP) {
        CD_initintr();
        return 1;
    }

    if (CD_init()) {
        return 0;
    }

    if (mode == CdlModeDA && CD_initvol()) {
        return 0;
    }

    return 1;
}

void CdFlush(void) { CD_flush(); }

s32 CdSetDebug(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_80032AB0;
    D_80032AB0 = arg0;
    return temp_v0;
}

char* CdComstr(unsigned char com) {
    if (com > 0x1b) {
        return "none";
    }

    return D_80032AC8[com];
}

char* CdIntstr(u8 intr) {
    if (intr > 6) {
        return "none";
    }
    return D_80032B48[intr];
}

int CdSync(int mode, u_char* result) { return CD_sync(mode, result); }

int CdReady(int mode, u_char* result) { return CD_ready(mode, result); }

CdlCB CdSyncCallback(CdlCB func) {
    CdlCB old = CD_cbsync;
    CD_cbsync = func;
    return old;
}

CdlCB CdReadyCallback(CdlCB func) {
    CdlCB old = CD_cbready;
    CD_cbready = func;
    return old;
}

static inline cd_cw(u8 com, u8* param, u_char* result, s32 arg3) {
    CdlCB old = CD_cbsync;
    int count = 4;

    while (count--) {
        CD_cbsync = NULL;
        if (com != CdlNop && (CdStatus() & CdlStatShellOpen)) {
            CD_cw(CdlNop, NULL, NULL, 0);
        }
        if (param == NULL || D_80032A24[com] == 0 ||
            !CD_cw(CdlSetloc, param, result, 0)) {
            CD_cbsync = old;
            if (!CD_cw(com, param, result, arg3)) {
                return 0;
            }
        }
    }

    CD_cbsync = old;
    return -1;
}

int CdControl(u8 com, u8* param, u_char* result) {
    return cd_cw(com, param, result, 0) == 0;
}

int CdControlF(u8 com, u8* param) { return cd_cw(com, param, NULL, 1) == 0; }

int CdControlB(u8 com, u8* param, u_char* result) {
    if (cd_cw(com, param, result, 0)) {
        return 0;
    }
    return CD_sync(CdlSync, result) == CdlComplete;
}

int CdMix(CdlATV* vol) {
    CD_vol(vol);
    return 1;
}

int CdGetSector(void* madr, int size) { return CD_getsector(madr, size) == 0; }

long CdDataCallback(void (*func)()) { return DMACallback(3, func); }

void CdDataSync(int mode) { CD_datasync(mode); }

CdlLOC* CdIntToPos(int i, CdlLOC* p) {
    inline int ENCODE_BCD(n) { return ((n / 10) << 4) + (n % 10); }

    i += 150;
    p->sector = ENCODE_BCD(i % 75);
    p->second = ENCODE_BCD(i / 75 % 60);
    p->minute = ENCODE_BCD(i / 75 / 60);
    return p;
}

int CdPosToInt(CdlLOC* p) {
#define DECODE_BCD(x) (((x) >> 4) * 10 + ((x) & 0xF))

    u8 sector = p->sector;
    u8 second = p->second;
    u8 minute = p->minute;

    return (DECODE_BCD(minute) * 60 + DECODE_BCD(second)) * 75 +
           DECODE_BCD(sector) - 150;
}
