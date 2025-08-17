// SPDX-License-Identifier: MIT
#include "libcd_internal.h"
#include "../libspu/libspu_internal.h"
#include <common.h>

typedef struct {
    unsigned char sync;  // sync state
    unsigned char ready; // ready state
    unsigned char c;
} CD_flush_struct;

typedef struct Alarm_t {
    int unk0;
    int unk4;
    char* unk8;
} Alarm_t;

extern volatile unsigned char* D_80032D68;
extern volatile unsigned char* D_80032D6C;
extern volatile unsigned char* D_80032D70;
extern volatile unsigned char* D_80032D74;
extern volatile int* D_80032D78;
extern volatile CD_flush_struct D_80032D80;
extern union SpuUnion* D_80032D7C;
// TODO: CD_status is a word here, but a byte in sys.c
extern int CD_status;
extern int CD_status1;
extern volatile unsigned char D_80032D84;
extern int* D_80032D9C;
extern int* D_80032DA0;
extern int* D_80032DA4;
extern int* D_80032DA8;
extern volatile int* D_80032DAC;
extern int CD_TestParmNum;
extern char D_80039260[];
extern char D_80039268[];
extern volatile Alarm_t Alarm;
extern u8 CD_pos[];
extern s32 D_80032AB0;
extern char* D_80032AC8[];
extern char* D_80032B48[];
extern s32 D_80032BE8[];
extern s32 D_80032CE8[];
extern s8 aCdTimeout;

// this is a string constant in several of the
// uncompiled functions below
const char D_800106B4[] = "%s:(%s) Sync=%s, Ready=%s\n";

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", getintr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_sync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_ready);

static inline void _memcpy(void* _dst, void* _src, u32 _size) {
    char* pDst = (char*)_dst;
    char* pSrc = (char*)_src;

    if (pDst == 0) {
        return;
    }

    while (_size--) {
        *pDst++ = *pSrc++;
    }
}

static inline void callback(void) {
    int interrupt;
    unsigned char temp_s1;

    temp_s1 = *D_80032D68 & 3;

    while (true) {
        interrupt = getintr();
        if (interrupt == 0) {
            break;
        }

        if (interrupt & 4 && CD_cbready != NULL) {
            CD_cbready(D_80032D80.ready, &D_80039268);
        }
        if (interrupt & 2 && (CD_cbsync != NULL)) {
            CD_cbsync(D_80032D80.sync, &D_80039260);
        }
    }
    *D_80032D68 = temp_s1;
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
        puts(&aCdTimeout);
        printf(D_800106B4, ((Alarm_t*)&Alarm)->unk8, D_80032AC8[CD_com],
               D_80032B48[D_80032D80.sync], D_80032B48[D_80032D80.ready]);
        CD_flush();
        return -1;
    }
    return 0;
}

s32 CD_cw(u8 com, u8* param, u8* arg2, s32 arg3) {
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
    D_80032D80.sync = 0;
    if (D_80032BE8[com] != 0) {
        D_80032D80.ready = 0;
    }
    *D_80032D68 = 0;
    for (i = 0; i < D_80032BE8[com + 0x40]; i++) {
        *D_80032D70 = param[i];
    }
    CD_com = com;
    *D_80032D6C = com;
    if (arg3 != 0) {
        return 0;
    }

    set_alarm("CD_cw");

    while (D_80032D80.sync == 0) {
        if (get_alarm()) {
            return -1;
        }
        if (CheckCallback()) {
            callback();
        }
    }
    if ((D_80032D80.sync == 2) && (com == CdlSetmode)) {
        CD_mode = *param;
    }

    _memcpy(arg2, D_80039260, 8);

    return -(D_80032D80.sync == 5);
}

const char aIdBiosCV177199[] =
    "$Id: bios.c,v 1.77 1996/05/13 06:58:16 suzu Exp $";

int CD_vol(CdlATV* vol) {
    *D_80032D68 = 2;
    *D_80032D70 = vol->val0;
    *D_80032D74 = vol->val1;
    *D_80032D68 = 3;
    *D_80032D6C = vol->val2;
    *D_80032D70 = vol->val3;
    *D_80032D74 = 0x20;
    return 0;
}

int CD_flush(void) {
    *D_80032D68 = 1;
    while (*D_80032D74 & 7) {
        *D_80032D68 = 1;
        *D_80032D74 = 7;
        *D_80032D70 = 7;
    }

    D_80032D80.ready = D_80032D80.c = 0;
    D_80032D80.sync = 2;
    *D_80032D68 = 0;
    *D_80032D74 = 0;
    *D_80032D78 = 0x1325;
}

int CD_initvol(void) {
    CdlATV vol;

    if ((unsigned short)D_80032D7C->rxxnv.main_volx.left == 0) {
        if ((unsigned short)D_80032D7C->rxxnv.main_volx.right == 0) {
            D_80032D7C->rxxnv.main_vol.left = 0x3FFF;
            D_80032D7C->rxxnv.main_vol.right = 0x3FFF;
        }
    }

    D_80032D7C->rxxnv.cd_vol.left = 0x3FFF;
    D_80032D7C->rxxnv.cd_vol.right = 0x3FFF;
    D_80032D7C->rxxnv.spucnt = 0xC001;
    vol.val0 = vol.val2 = 0x80;
    vol.val1 = vol.val3 = 0;
    *D_80032D68 = 2;
    *D_80032D70 = vol.val0;
    *D_80032D74 = vol.val1;
    *D_80032D68 = 3;
    *D_80032D6C = vol.val2;
    *D_80032D70 = vol.val3;
    *D_80032D74 = 0x20;

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

    *D_80032D68 = 1;
    while (*D_80032D74 & 7) {
        *D_80032D68 = 1;
        *D_80032D74 = 7;
        *D_80032D70 = 7;
    }

    D_80032D80.ready = D_80032D80.c = 0;
    D_80032D80.sync = 2;

    *D_80032D68 = 0;
    *D_80032D74 = 0;
    *D_80032D78 = 0x1325;

    CD_cw(1U, NULL, NULL, 0);
    if (CD_status & 0x10) {
        CD_cw(1U, NULL, NULL, 0);
    }

    if (CD_cw(0xAU, NULL, NULL, 0) != 0) {
        return -1;
    }

    if (CD_cw(0xCU, NULL, NULL, 0) != 0) {
        return -1;
    }

    if (CD_sync(0, 0) != 2) {
        return -1;
    }
    return 0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_datasync);

int CD_getsector(void* buffer, size_t size) {
    *D_80032D68 = 0;
    *D_80032D74 = 0x80;
    *D_80032D9C = 0x20943;
    *D_80032D78 = 0x1323;
    *D_80032DA0 |= 0x8000;
    *D_80032DA4 = buffer;
    *D_80032DA8 = size | 0x10000;
    while (!(*D_80032D68 & 0x40)) {
    };
    *D_80032DAC = 0x11000000;
    while (*D_80032DAC & 0x01000000) {
    };
    *D_80032D78 = 0x1325;
    return 0;
}

void CD_set_test_parmnum(int parmNum) { CD_TestParmNum = parmNum; }
