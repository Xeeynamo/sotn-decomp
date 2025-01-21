#include "common.h"
#include "../libspu/libspu_internal.h"
#include <psxsdk/libcd.h>

const char D_800106B4[] = "%s:(%s) Sync=%s, Ready=%s\n";

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", getintr);

int CD_sync(int, int);
INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_sync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_ready);

s32 CD_cw(u_char arg0, u_char* arg1, u_char* arg2, int arg3);
INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/bios", CD_cw);

const char aIdBiosCV177199[] =
    "$Id: bios.c,v 1.77 1996/05/13 06:58:16 suzu Exp $";

extern u8* D_80032D6C;
extern volatile u8* D_80032D68;
extern volatile u8* D_80032D70;
extern volatile u8* D_80032D74;

s32 CD_vol(CdlATV* arg0) {
    *D_80032D68 = 2;
    *D_80032D70 = arg0->val0;
    *D_80032D74 = arg0->val1;
    *D_80032D68 = 3;
    *D_80032D6C = arg0->val2;
    *D_80032D70 = arg0->val3;
    *D_80032D74 = 0x20;
    return 0;
}

extern volatile s32* D_80032D78;

typedef struct {
    u8 a, b, c;
} CD_flush_struct;

extern volatile CD_flush_struct D_80032D80;
extern volatile u8 D_80032D81[];
extern volatile u8 D_80032D82;

int CD_flush(void) {
    *D_80032D68 = 1;
    while (*D_80032D74 & 7) {
        *D_80032D68 = 1;
        *D_80032D74 = 7;
        *D_80032D70 = 7;
    }

    D_80032D80.b = D_80032D80.c = 0;
    D_80032D80.a = 2;
    *D_80032D68 = 0;
    *D_80032D74 = 0;
    *D_80032D78 = 0x1325;
}

extern union SpuUnion* D_80032D7C;

s32 CD_initvol(void) {
    u8 data[4];

    if ((u16)D_80032D7C->rxxnv.main_volx.left == 0) {
        if ((u16)D_80032D7C->rxxnv.main_volx.right == 0) {
            D_80032D7C->rxxnv.main_vol.left = 0x3FFF;
            D_80032D7C->rxxnv.main_vol.right = 0x3FFF;
        }
    }

    D_80032D7C->rxxnv.cd_vol.left = 0x3FFF;
    D_80032D7C->rxxnv.cd_vol.right = 0x3FFF;
    D_80032D7C->rxxnv.spucnt = 0xC001;
    data[0] = data[2] = 0x80;
    data[1] = data[3] = 0;
    *D_80032D68 = 2;
    *D_80032D70 = data[0];
    *D_80032D74 = data[1];
    *D_80032D68 = 3;
    *D_80032D6C = data[2];
    *D_80032D70 = data[3];
    *D_80032D74 = 0x20;

    return 0;
}

int ResetCallback(void);
extern int (*CD_cbready)(u8, char*);
extern int (*CD_cbsync)(u8, char*);
extern s32 CD_status;
extern s32 CD_status1;
void callback(void);

void CD_initintr(void) {
    CD_cbready = NULL;
    CD_cbsync = NULL;
    CD_status1 = 0;
    CD_status = 0;
    ResetCallback();
    InterruptCallback(2, callback);
}

extern volatile u8 D_80032D84;
extern u_char CD_mode;
extern u_char CD_com;

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

    D_80032D80.b = D_80032D80.c = 0;
    D_80032D80.a = 2;

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

extern s32* D_80032D9C;
extern s32* D_80032DA0;
extern s32* D_80032DA4;
extern s32* D_80032DA8;
extern volatile s32* D_80032DAC;

s32 CD_getsector(void* buffer, size_t size) {
    *D_80032D68 = 0;
    *D_80032D74 = 0x80;
    *D_80032D9C = 0x20943;
    *D_80032D78 = 0x1323;
    *D_80032DA0 |= 0x8000;
    *D_80032DA4 = buffer;
    *D_80032DA8 = size | 0x10000;
    while (!(*D_80032D68 & 0x40)) {};
    *D_80032DAC = 0x11000000;
    while (*D_80032DAC & 0x01000000) {};
    *D_80032D78 = 0x1325;
    return 0;
}


extern int CD_TestParmNum;

void CD_set_test_parmnum(int parmNum) { CD_TestParmNum = parmNum; }

s32 getintr();
extern char D_80039260[];
extern char D_80039268[];

void callback(void) {
    s32 interrupt;
    u8 temp_s1;

    temp_s1 = *D_80032D68 & 3;

    while (true) {
        interrupt = getintr();
        if (interrupt == 0) {
            break;
        }

        if (interrupt & 4) {
            if (CD_cbready != NULL) {
                CD_cbready(D_80032D80.b, &D_80039268);
            }
        }
        if (interrupt & 2 && (CD_cbsync != NULL)) {
            CD_cbsync(D_80032D80.a, &D_80039260);
        }
    }
    *D_80032D68 = temp_s1;
}
