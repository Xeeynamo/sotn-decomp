// SPDX-License-Identifier: MIT
#include "libcd_internal.h"
#include "../libspu/libspu_internal.h"
#include <common.h>

typedef struct {
    unsigned char sync;  // sync state
    unsigned char ready; // ready state
    unsigned char c;
} CD_intr;

typedef struct {
    CD_intr* intr;
    Result_t* result;
    unsigned char* cd_com;
    int* cd_status;
    unsigned char** cd_pos;
    char** aIdBiosCV177199;
} CD_init_struct;

typedef struct Alarm_t {
    int unk0;
    int unk4;
    char* unk8;
} Alarm_t;

Result_t D_80039260;
Result_t D_80039268;
Result_t D_80039270;
volatile Alarm_t Alarm;

CdlCB CD_cbsync = NULL;
CdlCB CD_cbready = NULL;
STATIC_PAD_DATA(4);
int D_80032AB0 = 0;
int CD_status = 0;
int CD_status1 = 0;
int CD_nopen = 0;
unsigned char CD_pos[] = {2, 0, 0, 0};
unsigned char CD_mode = 0;
unsigned char CD_com = 0;
char* D_80032AC8[] = {
    "CdlSync",    "CdlNop",
    "CdlSetloc",  "CdlPlay",
    "CdlForward", "CdlBackword",
    "CdlReadN",   "CdlStandby",
    "CdlStop",    "CdlPause",
    "CdlReset",   "CdlMute",
    "CdlDemute",  "CdlSetfilter",
    "CdlSetmode", "?",
    "CdlGetlocL", "CdlGetlocP",
    "?",          "CdlGetTN",
    "CdlGetTD",   "CdlSeekL",
    "CdlSeekP",   "?",
    "?",          "?",
    "?",          "CdlReadS",
    "?",          "?",
    "?",          "?",
};
char* D_80032B48[] = {
    "NoIntr",  "DataReady", "Complete", "Acknowledge",
    "DataEnd", "DiskError", "?",        "?",
};
static int D_80032B68[] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
                           0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0};
static int D_80032BE8[] = {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0};
static int D_80032C68[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                           0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static int D_80032CE8[] = {0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0,
                           0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#include "registers.h"

static volatile int* D_80032D78 = (int*)0x1F801020;
static volatile SPU_RXX* D_80032D7C = (SPU_RXX*)0x1F801C00;
static volatile CD_intr Intr = {0};

static inline void _memcpy(void* _dst, void* _src, size_t _size) {
    char* pDst = (char*)_dst;
    char* pSrc = (char*)_src;

    if (pDst == 0) {
        return;
    }

    while (_size--) {
        *pDst++ = *pSrc++;
    }
}

static inline void set_alarm(char* name) {
    // schedule timeout for 960 vblanks from now
    ((Alarm_t*)&Alarm)->unk0 = VSync(-1) + 960;
    ((Alarm_t*)&Alarm)->unk4 = 0;
    ((Alarm_t*)&Alarm)->unk8 = name;
}

static inline int get_alarm(void) {
    if (((Alarm_t*)&Alarm)->unk0 < VSync(-1) ||
        ((Alarm_t*)&Alarm)->unk4++ > 0x3C0000) {
        puts("CD timeout: ");
        printf("%s:(%s) Sync=%s, Ready=%s\n", ((Alarm_t*)&Alarm)->unk8,
               D_80032AC8[CD_com], D_80032B48[Intr.sync],
               D_80032B48[Intr.ready]);
        CD_flush();
        return -1;
    }
    return 0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", getintr);

static inline void callback(void) {
    int interrupt;
    unsigned char temp_s1;

    temp_s1 = *libcd_CDRegister0 & 3;

    while (true) {
        interrupt = getintr();
        if (interrupt == 0) {
            break;
        }

        if ((interrupt & 4) && CD_cbready != NULL) {
            CD_cbready(Intr.ready, &D_80039268);
        }
        if ((interrupt & 2) && CD_cbsync != NULL) {
            CD_cbsync(Intr.sync, &D_80039260);
        }
    }
    *libcd_CDRegister0 = temp_s1;
}

int CD_sync(int mode, Result_t* result) {
    s32 i;
    s32 sync;

    set_alarm("CD_sync");

    while (true) {
        if (get_alarm()) {
            return -1;
        }

        if (CheckCallback()) {
            callback();
        }

        sync = Intr.sync;
        if (sync == 2 || sync == 5) {
            Intr.sync = 2;
            _memcpy(result, &D_80039260, sizeof(Result_t));
            return sync;
        }

        if (mode != 0) {
            return 0;
        }
    }
}

int CD_ready(int mode, Result_t* result) {
    s32 i;
    s32 c;
    s32 ready;

    set_alarm("CD_ready");
    while (true) {
        if (get_alarm()) {
            return -1;
        }
        if (CheckCallback()) {
            callback();
        }
        c = Intr.c;
        if (c != 0) {
            Intr.c = 0;
            _memcpy(result, &D_80039270, sizeof(Result_t));
            return c;
        }
        ready = Intr.ready;
        if (ready != 0) {
            Intr.ready = 0;
            _memcpy(result, &D_80039268, sizeof(Result_t));
            return ready;
        }
        if (mode != 0) {
            return 0;
        }
    }
}

int CD_cw(u8 com, u8* param, Result_t* result, s32 arg3) {
    s32 i;

    if (D_80032AB0 > 1) {
        printf("%s...\n", D_80032AC8[com]);
    }
    if ((D_80032CE8[com] != 0) && (param == NULL)) {
        if (D_80032AB0 > 0) {
            printf("%s: no param\n", D_80032AC8[com]);
        }
        return -2;
    }
    CD_sync(0, 0);
    if (com == CdlSetloc) {
        for (i = 0; i < 4; i++) {
            CD_pos[i] = param[i];
        }
    }
    Intr.sync = 0;
    if (D_80032BE8[com] != 0) {
        Intr.ready = 0;
    }
    *libcd_CDRegister0 = 0;
    for (i = 0; i < D_80032BE8[com + 0x40]; i++) {
        *libcd_CDRegister2 = param[i];
    }
    CD_com = com;
    *libcd_CDRegister1 = com;
    if (arg3 != 0) {
        return 0;
    }

    set_alarm("CD_cw");

    while (Intr.sync == 0) {
        if (get_alarm()) {
            return -1;
        }
        if (CheckCallback()) {
            callback();
        }
    }
    if ((Intr.sync == 2) && (com == CdlSetmode)) {
        CD_mode = *param;
    }

    _memcpy(result, &D_80039260, sizeof(Result_t));

    return -(Intr.sync == 5);
}

int CD_vol(CdlATV* vol) {
    *libcd_CDRegister0 = 2;
    *libcd_CDRegister2 = vol->val0;
    *libcd_CDRegister3 = vol->val1;
    *libcd_CDRegister0 = 3;
    *libcd_CDRegister1 = vol->val2;
    *libcd_CDRegister2 = vol->val3;
    *libcd_CDRegister3 = 0x20;
    return 0;
}

int CD_flush(void) {
    *libcd_CDRegister0 = 1;
    while (*libcd_CDRegister3 & 7) {
        *libcd_CDRegister0 = 1;
        *libcd_CDRegister3 = 7;
        *libcd_CDRegister2 = 7;
    }

    Intr.ready = Intr.c = 0;
    Intr.sync = 2;
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0;
    *D_80032D78 = 0x1325;
}

int CD_initvol(void) {
    CdlATV vol;

    if (D_80032D7C->main_volx.left == 0 && D_80032D7C->main_volx.right == 0) {
        D_80032D7C->main_vol.left = 0x3FFF;
        D_80032D7C->main_vol.right = 0x3FFF;
    }

    D_80032D7C->cd_vol.left = 0x3FFF;
    D_80032D7C->cd_vol.right = 0x3FFF;
    D_80032D7C->spucnt = 0xC001;
    vol.val0 = vol.val2 = 0x80;
    vol.val1 = vol.val3 = 0;
    *libcd_CDRegister0 = 2;
    *libcd_CDRegister2 = vol.val0;
    *libcd_CDRegister3 = vol.val1;
    *libcd_CDRegister0 = 3;
    *libcd_CDRegister1 = vol.val2;
    *libcd_CDRegister2 = vol.val3;
    *libcd_CDRegister3 = 0x20;

    return 0;
}

void CD_initintr(void) {
    CD_cbready = NULL;
    CD_cbsync = NULL;
    CD_status1 = 0;
    CD_status = 0;
    ResetCallback();
    InterruptCallback(2, callback);
}

static CD_init_struct D_80032D84 = {
    .intr = &Intr,
    .result = &D_80039260,
    .cd_com = &CD_com,
    .cd_status = &CD_status,
    .cd_pos = &CD_pos,
    .aIdBiosCV177199 = "$Id: bios.c,v 1.77 1996/05/13 06:58:16 suzu Exp $"};
static volatile int* D_80032D9C = (int*)0x1F801018;
static volatile int* D_80032DA0 = (int*)0x1F8010F0;
static volatile int* D_80032DA4 = (int*)0x1F8010B0;
static volatile int* D_80032DA8 = (int*)0x1F8010B4;
static volatile int* D_80032DAC = (int*)0x1F8010B8;

int CD_init(void) {
    puts("CD_init:");
    printf("addr=%08x\n", &D_80032D84);
    CD_com = 0;
    CD_mode = 0;
    CD_cbready = NULL;
    CD_cbsync = NULL;
    CD_status1 = 0;
    CD_status = 0;
    ResetCallback();
    InterruptCallback(2, callback);

    *libcd_CDRegister0 = 1;
    while (*libcd_CDRegister3 & 7) {
        *libcd_CDRegister0 = 1;
        *libcd_CDRegister3 = 7;
        *libcd_CDRegister2 = 7;
    }

    Intr.ready = Intr.c = 0;
    Intr.sync = 2;

    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0;
    *D_80032D78 = 0x1325;

    CD_cw(CdlNop, NULL, NULL, 0);
    if (CD_status & 0x10) {
        CD_cw(CdlNop, NULL, NULL, 0);
    }

    if (CD_cw(CdlReset, NULL, NULL, 0)) {
        return -1;
    }

    if (CD_cw(CdlDemute, NULL, NULL, 0)) {
        return -1;
    }

    if (CD_sync(0, 0) != CdlComplete) {
        return -1;
    }
    return 0;
}

int CD_datasync(int mode) {
    int ret;

    set_alarm("CD_datasync");
    while (true) {
        if (get_alarm()) {
            ret = -1;
            break;
        }
        if (!(*D_80032DAC & 0x01000000)) {
            ret = 0;
            break;
        }
        if (mode != 0) {
            ret = 1;
            break;
        }
    }
    return ret;
}

int CD_getsector(void* buffer, size_t size) {
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0x80;
    *D_80032D9C = 0x20943;
    *D_80032D78 = 0x1323;
    *D_80032DA0 |= 0x8000;
    *D_80032DA4 = buffer;
    *D_80032DA8 = size | 0x10000;
    while (!(*libcd_CDRegister0 & 0x40)) {
    };
    *D_80032DAC = 0x11000000;
    while (*D_80032DAC & 0x01000000) {
    };
    *D_80032D78 = 0x1325;
    return 0;
}

void CD_set_test_parmnum(int parmNum) { D_80032CE8[25] = parmNum; }
