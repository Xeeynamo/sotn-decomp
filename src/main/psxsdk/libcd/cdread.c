// SPDX-License-Identifier: MIT
#include "common.h"
#include "psxsdk/libcd.h"

typedef struct {
    int sectors;
    u_long* unk4;
    u_long* unk8;
    int mode;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
    int unk20;
    CdlCB sync;
    CdlCB ready;
} cdreadStruct;

static CdlCB CD_ReadCallbackFunc = NULL;
static volatile cdreadStruct D_80032DBC = {0};

void cb_read(u_char arg0, u_char* result) {
    int pos[3];

    if (arg0 == 1) {
        if (D_80032DBC.unk14 > 0) {
            if (D_80032DBC.unk10 == 0x200) {
                CdGetSector(pos, 3);
                if (CdPosToInt(pos) != D_80032DBC.unk20) {
                    puts("CdRead: sector error\n");
                    D_80032DBC.unk14 = -1;
                }
            }
            CdGetSector(D_80032DBC.unk8, D_80032DBC.unk10);
            D_80032DBC.unk8 += D_80032DBC.unk10;
            D_80032DBC.unk14--;
            D_80032DBC.unk20++;
        }
    } else {
        D_80032DBC.unk14 = -1;
    }
    D_80032DBC.unk18 = VSync(-1);
    if (D_80032DBC.unk14 < 0) {
        cd_read_retry(true);
    }
    if (VSync(-1) > D_80032DBC.unk1C + 1200) {
        D_80032DBC.unk14 = -1;
    }
    if (D_80032DBC.unk14 && VSync(-1) <= D_80032DBC.unk1C + 1200) {
        return;
    }
    CdSyncCallback(D_80032DBC.sync);
    CdReadyCallback(D_80032DBC.ready);
    CdControl(CdlPause, NULL, NULL);
    if (CD_ReadCallbackFunc != NULL) {
        CD_ReadCallbackFunc(
            D_80032DBC.unk14 == 0 ? CdlComplete : CdlDiskError, result);
    }
}

int cd_read_retry(int retry) {
    char mode;
    int mode2;
    CdSyncCallback(NULL);
    CdReadyCallback(NULL);
    if (CdStatus() & CdlStatShellOpen) {
        if ((VSync(-1) % 0x40) == 0) {
            puts("CdRead: Shell open...\n");
        }
        CdControlF(CdlNop, NULL);
        D_80032DBC.unk1C = VSync(-1);
        D_80032DBC.unk14 = -1;
        return D_80032DBC.unk14;
    }
    if (retry) {
        puts("CdRead: retry...\n");
        CdControl(CdlPause, NULL, NULL);
        if (!CdControl(CdlSetloc, CdLastPos(), NULL)) {
            return D_80032DBC.unk14 = -1;
        }
    }
    CdFlush();
    mode2 = D_80032DBC.mode;
    mode = mode2; // FAKE
    if ((char)mode2 != CdMode() || retry) {
        if (!CdControl(CdlSetmode, &mode, NULL)) {
            D_80032DBC.unk14 = -1;
            return D_80032DBC.unk14;
        }
    }
    D_80032DBC.unk20 = CdPosToInt(CdLastPos());
    CdReadyCallback(&cb_read);
    D_80032DBC.unk8 = D_80032DBC.unk4;
    CdControlF(CdlReadN, NULL);
    D_80032DBC.unk14 = D_80032DBC.sectors;
    D_80032DBC.unk18 = VSync(-1);
    return D_80032DBC.unk14;
}

int CdRead(int sectors, u_long* buf, int mode) {
    D_80032DBC.mode = mode;
    switch (D_80032DBC.mode & (CdlModeSize0 | CdlModeSize1)) {
    case 0:
        D_80032DBC.unk10 = 0x200;
        break;
    case CdlModeSize1:
        D_80032DBC.unk10 = 0x249;
        break;
    default:
        D_80032DBC.unk10 = 0x246;
        break;
    }
    D_80032DBC.mode |= CdlModeSize1;
    D_80032DBC.unk4 = buf;
    D_80032DBC.sectors = sectors;
    D_80032DBC.sync = CdSyncCallback(NULL);
    D_80032DBC.ready = CdReadyCallback(NULL);
    D_80032DBC.unk1C = VSync(-1);
    if (CdStatus() & (CdlStatPlay | CdlStatSeek | CdlStatRead)) {
        CdControlB(CdlPause, NULL, NULL);
    }
    return cd_read_retry(false) > 0;
}

int CdReadSync(int mode, u_char* result) {
    int var_s0;

    while (true) {
        var_s0 = -1;
        if (VSync(-1) <= D_80032DBC.unk1C + 1200) {
            if (D_80032DBC.unk14 < 0 || VSync(-1) > D_80032DBC.unk18 + 60) {
                cd_read_retry(true);
                var_s0 = D_80032DBC.sectors;
            } else {
                var_s0 = D_80032DBC.unk14;
            }
        }
        if (mode != 0 || var_s0 <= 0) {
            CdReady(1, result);
            return var_s0;
        }
    }
}

CdlCB CdReadCallback(CdlCB func) {
    CdlCB prevFunc = CD_ReadCallbackFunc;
    CD_ReadCallbackFunc = func;
    return prevFunc;
}
