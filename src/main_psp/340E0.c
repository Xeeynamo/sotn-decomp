// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspthreadman.h>
#include <pspiofilemgr.h>
#include <pspkerror.h>

typedef struct {
    u32 unk0;
    s32 unk4;
} unkStruct2;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    unkStruct2* unk14;
    s32 unk18;
    u32 unk1C;
    u32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    char unk34[0x40];
} unkStruct;

extern s32 D_psp_08B4205C;

static s32 D_psp_090DC8C4[6];
static s32 D_psp_090DC8C0;
static u8 D_psp_0908C8C0[0x50000];
static u8 D_psp_0906C8C0[0x20000]; // unused
static u8 D_psp_08FCC8C0[0xA0000];
static u8 D_psp_08FA08C0[0x2C000];
static u8 D_psp_08F958C0[0xB000];
static u8 D_psp_08F8A8C0[0xB000];
static u8 D_psp_08E2E8C0[0x15C000];
static u8 D_psp_08E2E8B0[0x10]; // unused
static unkStruct D_psp_08E2E5F8[6];

s32 func_psp_08933304(u32 args, void* argp);
void func_psp_08933760(unkStruct* arg0);
void func_psp_089337A8(unkStruct* arg0);
void func_psp_089337EC(s32 arg0);
void func_psp_08933830(s32 arg0);
void func_psp_08933954(unkStruct* arg0);
void func_psp_08933C30(s32 arg0, s32 arg1);
void func_psp_08933ED8(s32 arg0);

s32 func_psp_089329EC(s32 arg0, s32 arg1) {
    unkStruct2* var_s0;
    unkStruct2* var_s1;

    var_s1 = D_psp_08E2E5F8[arg0].unk14;
    var_s0 = D_psp_08E2E5F8[arg0].unk14;
    return (s32)var_s0 + (*(&var_s1[arg1].unk0 + 2) + 0x80);
}

s32 func_psp_08932A7C(s32 arg0, s32 arg1) {
    unkStruct2* var_s0;

    var_s0 = D_psp_08E2E5F8[arg0].unk14;
    return *(&var_s0[arg1].unk0 + 3);
}

void func_psp_08932AD4(s32 arg0) {
    s32 var_s0;
    unkStruct* var_s1;

    var_s0 = 0;
    func_psp_089337EC(0);
    var_s1 = D_psp_08E2E5F8;
    if (var_s1[0].unkC == arg0) {
        var_s0 = 1;
    }
    func_psp_08933830(0);
    if (var_s0 == 0) {
        func_psp_08933C30(0, arg0);
    }
}

void func_psp_08932B50(void) { func_psp_08933ED8(0); }

s32 func_psp_08932B74(void) { return func_psp_08933E38(0); }

s32 func_psp_08932B98(s32 arg0) { return func_psp_089329EC(0, arg0); }

s32 func_psp_08932BC4(s32 arg0) { return func_psp_08932A7C(0, arg0); }

s32 func_psp_08932BF0(void) { return func_psp_08932B98(0); }

s32 func_psp_08932C14(void) { return func_psp_08932B98(1); }

s32 func_psp_08932C38(void) { return func_psp_08932B98(2); }

s32 func_psp_08932C5C(void) { return func_psp_08932B98(3); }

s32 func_psp_08932C80(void) { return func_psp_08932BC4(3); }

s32 func_psp_08932CA4(void) { return func_psp_08932B98(4); }

s32 func_psp_08932CC8(void) { return func_psp_08932BC4(4); }

void func_psp_08932CEC(s32 arg0, s8 arg1) {
    if (arg1 < 0) {
        return;
    }
    func_psp_08933C30(arg0 + 1, arg1);
}

s32 func_psp_08932D34(s32 arg0) { return func_psp_08933E38(arg0 + 1); }

s32 func_psp_08932D60(s32 arg0, s32 arg1) {
    return func_psp_089329EC(arg0 + 1, arg1);
}

s32 func_psp_08932D94(s32 arg0, s32 arg1) {
    return func_psp_08932A7C(arg0 + 1, arg1);
}

s32 func_psp_08932DC8(s32 arg0) { return func_psp_08932D60(arg0, 0); }

s32 func_psp_08932DF4(s32 arg0) { return func_psp_08932D60(arg0, 1); }

s32 func_psp_08932E20(s32 arg0) { return func_psp_08932D60(arg0, 2); }

s32 func_psp_08932E4C(s32 arg0) { return func_psp_08932D94(arg0, 2); }

void func_psp_08932E78(s32 arg0) { func_psp_08933C30(3, arg0); }

s32 func_psp_08932EA4(void) { return func_psp_08933E38(3); }

s32 func_psp_08932EC8(s32 arg0) { return func_psp_089329EC(3, arg0); }

s32 func_psp_08932EF4(s32 arg0) { return func_psp_08932A7C(3, arg0); }

s32 func_psp_08932F20(void) { return func_psp_08932EC8(0); }

s32 func_psp_08932F44(void) { return func_psp_08932EC8(1); }

s32 func_psp_08932F68(void) { return func_psp_08932EC8(2); }

s32 func_psp_08932F8C(void) { return func_psp_08932EC8(3); }

s32 func_psp_08932FB0(void) { return func_psp_08932EF4(3); }

void func_psp_08932FD4(s32 arg0) { func_psp_08933C30(4, arg0); }

s32 func_psp_08933000(void) { return func_psp_08933E38(4); }

s32 func_psp_08933024(s32 arg0) { return func_psp_089329EC(4, arg0); }

s32 func_psp_08933050(s32 arg0) { return func_psp_08932A7C(4, arg0); }

s32 func_psp_0893307C(void) { return func_psp_08933024(1); }

s32 func_psp_089330A0(void) { return func_psp_08933024(3); }

s32 func_psp_089330C4(void) { return func_psp_08933024(0); }

s32 func_psp_089330E8(void) { return func_psp_08933024(2); }

s32 func_psp_0893310C(void) { return func_psp_08933050(2); }

void func_psp_08933130(s32 arg0) { func_psp_08933C30(5, arg0); }

s32 func_psp_0893315C(void) { return func_psp_08933E38(5); }

s32 func_psp_08933180(s32 arg0) { return func_psp_089329EC(5, arg0); }

s32 func_psp_089331AC(void) { return func_psp_08933180(0); }

s32 func_psp_089331D0(SceUID fd, s32 arg1) {
    volatile s32 ret;
    SceInt64 res;

    res = 0;
    ret = sceIoPollAsync(fd, &res);
    if (ret == 0) {
        if ((s32)res < 0) {
            return -1;
        } else {
            return 1;
        }
    } else if (ret != 1) {
        return -1;
    } else {
        return 0;
    }
}

void func_psp_0893325C(unkStruct* arg0) {
    s32 ret;
    SceInt64 res;

    if (arg0->unk2C > 0) {
        ret = sceIoClose(arg0->unk2C);
        if (ret == SCE_KERNEL_ERROR_ASYNC_BUSY) {
            ret = sceIoWaitAsync(arg0->unk2C, &res);
            ret = sceIoClose(arg0->unk2C);
        }
        arg0->unk2C = -1;
    }
    arg0->unk10 = 0;
    sceKernelDelayThreadCB(499980);
}

s32 func_psp_08933304(u32 args, void* argp) {
    unkStruct** var_s6;
    char filePath[0x200];
    s32 var_s3;
    s32 ret;
    s32 var_s5;
    s32 i;
    unkStruct2* temp_s2;
    unkStruct* temp_s0;

    var_s5 = 1;
    var_s6 = (unkStruct**)argp;
    temp_s0 = *var_s6;
    func_psp_08933760(temp_s0);
    temp_s0->unk10 = 0;
    temp_s0->unk1C = 0;
    temp_s0->unk8 = -1;
    func_psp_0890F250(temp_s0->unk34, &filePath);
    func_psp_089337A8(temp_s0);
    while (var_s5) {
        func_psp_08933760(temp_s0);
        if (func_psp_089123B8() == 0) {
            func_psp_0893325C(temp_s0);
        } else {
            switch (temp_s0->unk10) {
            case 0:
                temp_s0->unk2C = sceIoOpenAsync(filePath, 1, 0x1FF);
                if (temp_s0->unk2C >= 0) {
                    temp_s0->unk10++;
                    temp_s0->unk1C = 0;
                }
                break;
            case 1:
                var_s3 = func_psp_089331D0(temp_s0->unk2C, 0);
                if (var_s3 > 0) {
                    temp_s0->unk10++;
                } else if (var_s3 < 0) {
                    func_psp_0893325C(temp_s0);
                }
                break;
            case 2:
                ret = sceIoReadAsync(
                    temp_s0->unk2C,
                    (void*)((((u32)temp_s0->unk14 + temp_s0->unk1C) &
                             0x0FFFFFFF) |
                            0x40000000),
                    0x800);
                if (ret >= 0) {
                    temp_s0->unk10++;
                } else {
                    func_psp_0893325C(temp_s0);
                }
                break;
            case 3:
                var_s3 = func_psp_089331D0(temp_s0->unk2C, temp_s0->unk18);
                if (var_s3 > 0) {
                    temp_s0->unk10++;
                    temp_s0->unk1C = 0x800;
                    temp_s2 = temp_s0->unk14;
                    temp_s0->unk24 = 0x80;
                    for (i = 0; i < temp_s2->unk0; i++) {
                        temp_s0->unk24 += (&temp_s2[i] + 1)->unk4;
                    }
                } else if (var_s3 < 0) {
                    func_psp_0893325C(temp_s0);
                }
                break;
            case 4:
                temp_s0->unk20 = temp_s0->unk24 - temp_s0->unk1C;
                if (temp_s0->unk20 > 0x6400) {
                    temp_s0->unk20 = 0x6400;
                }
                ret = sceIoReadAsync(
                    temp_s0->unk2C,
                    (void*)((((u32)temp_s0->unk14 + temp_s0->unk1C) &
                             0x0FFFFFFF) |
                            0x40000000),
                    temp_s0->unk20);
                if (ret >= 0) {
                    temp_s0->unk10++;
                } else {
                    func_psp_0893325C(temp_s0);
                }
                break;
            case 5:
                var_s3 = func_psp_089331D0(temp_s0->unk2C, temp_s0->unk18);
                if (var_s3 > 0) {
                    temp_s0->unk1C += temp_s0->unk20;
                    if (temp_s0->unk1C >= temp_s0->unk24) {
                        temp_s0->unk10++;
                    } else {
                        temp_s0->unk10 = 4;
                    }
                } else if (var_s3 < 0) {
                    func_psp_0893325C(temp_s0);
                }
                break;
            case 6:
                ret = sceIoClose(temp_s0->unk2C);
                if (temp_s0->unk4 == 0 && func_psp_08932CC8()) {
                    memcpy(D_psp_0908C8C0, (void*)func_psp_08932CA4(),
                           func_psp_08932CC8());
                    D_psp_090DC8C0 = func_psp_08932CC8();
                }
                temp_s0->unk2C = -1;
                var_s5 = 0;
                break;
            }
        }
        func_psp_089337A8(temp_s0);
        sceDisplayWaitVblankStartCB();
    }
    func_psp_08933760(temp_s0);
    temp_s0->unk28 = -1;
    temp_s0->unk2C = -1;
    temp_s0->unk8 = temp_s0->unkC;
    func_psp_089337A8(temp_s0);
    sceKernelExitDeleteThread(0);
    return 0;
}

void func_psp_08933760(unkStruct* arg0) {
    sceKernelWaitSema(D_psp_090DC8C4[arg0->unk30], 1, NULL);
}

void func_psp_089337A8(unkStruct* arg0) {
    sceKernelSignalSema(D_psp_090DC8C4[arg0->unk30], 1);
}

void func_psp_089337EC(s32 arg0) {
    sceKernelWaitSema(D_psp_090DC8C4[arg0], 1, NULL);
}

void func_psp_08933830(s32 arg0) {
    sceKernelSignalSema(D_psp_090DC8C4[arg0], 1);
}

void func_psp_08933870(unkStruct* arg0) {
    arg0->unk8 = -1;
    arg0->unkC = -1;
    arg0->unk10 = 0;
    arg0->unk28 = -1;
    arg0->unk2C = -1;
}

void func_psp_089338BC(unkStruct* arg0, u32 arg1) {
    volatile s32 ret;
    unkStruct* sp18;

    sp18 = arg0;

    func_psp_08933954(arg0);
    arg0->unk28 = sceKernelCreateThread(
        "BACKREADL", &func_psp_08933304, arg1, 0x1000, 0, NULL);
    if (arg0->unk28 < 0) {
        (volatile) arg0;
    }
    ret = sceKernelStartThread(arg0->unk28, 4, &sp18);
    (volatile) ret;
}

void func_psp_08933954(unkStruct* arg0) {
    s32 ret;
    SceInt64 res;

    if (arg0->unk28 >= 0) {
        sceKernelTerminateDeleteThread(arg0->unk28);
        if (arg0->unk2C >= 0) {
            ret = sceIoClose(arg0->unk2C);
            if (ret == SCE_KERNEL_ERROR_ASYNC_BUSY) {
                ret = sceIoWaitAsync(arg0->unk2C, &res);
                ret = sceIoClose(arg0->unk2C);
            }
            arg0->unk2C = -1;
        }
        arg0->unk28 = -1;
    }
}

void func_psp_08933A10(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        D_psp_090DC8C4[i] = sceKernelCreateSema("BACKREAD_SEMA", 0, 1, 1, NULL);
    }
    for (i = 0; i < 6; i++) {
        D_psp_08E2E5F8[i].unk30 = i;
        func_psp_08933870(&D_psp_08E2E5F8[i]);
    }
    D_psp_08E2E5F8[0].unk14 = (unkStruct2*)D_psp_08E2E8C0;
    D_psp_08E2E5F8[1].unk14 = (unkStruct2*)D_psp_08F8A8C0;
    D_psp_08E2E5F8[2].unk14 = (unkStruct2*)D_psp_08F958C0;
    D_psp_08E2E5F8[3].unk14 = (unkStruct2*)D_psp_08FA08C0;
    D_psp_08E2E5F8[4].unk14 = (unkStruct2*)D_psp_08FCC8C0;
    D_psp_08E2E5F8[5].unk14 = (unkStruct2*)D_psp_08FCC8C0;
    D_psp_08E2E5F8[0].unk18 = LEN(D_psp_08E2E8C0);
    D_psp_08E2E5F8[1].unk18 = LEN(D_psp_08F8A8C0);
    D_psp_08E2E5F8[2].unk18 = LEN(D_psp_08F958C0);
    D_psp_08E2E5F8[3].unk18 = LEN(D_psp_08FA08C0);
    D_psp_08E2E5F8[4].unk18 = LEN(D_psp_08FCC8C0);
    D_psp_08E2E5F8[5].unk18 = LEN(D_psp_08FCC8C0);
    D_psp_090DC8C0 = 0;
}

void func_psp_08933BA0(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        func_psp_08933954(&D_psp_08E2E5F8[i]);
        sceKernelDeleteSema(D_psp_08E2E5F8[i].unk30);
    }
}

void func_psp_08933C30(s32 arg0, s32 arg1) {
    u8 temp_s1;
    unkStruct* temp_s0;

    temp_s1 = 0x3E;
    func_psp_089337EC(arg0);
    temp_s0 = &D_psp_08E2E5F8[arg0];
    if (arg0 == 4 || arg0 == 5 || temp_s0->unk8 != arg1) {
        temp_s0->unkC = arg1;
        temp_s0->unk8 = -1;
        temp_s0->unk4 = arg0;
        switch (arg0) {
        case 0:
            sprintf(temp_s0->unk34, "%sSTP%02d.BIN;1", D_psp_08B4205C, arg1);
            func_psp_089338BC(temp_s0, temp_s1);
            break;
        case 1:
        case 2:
            sprintf(temp_s0->unk34, "%sW%cP%02d.BIN;1", D_psp_08B4205C,
                    arg0 + 0x2F, arg1);
            func_psp_089338BC(temp_s0, temp_s1 - 1);
            break;
        case 3:
            sprintf(temp_s0->unk34, "%sTP%02d.BIN;1", D_psp_08B4205C, arg1);
            func_psp_089338BC(temp_s0, temp_s1 - 1);
            break;
        case 4:
            sprintf(temp_s0->unk34, "%sPLP%01d.BIN;1", D_psp_08B4205C, arg1);
            func_psp_089338BC(temp_s0, temp_s1);
            break;
        case 5:
            sprintf(temp_s0->unk34, "%sOTP%01d.BIN;1", D_psp_08B4205C, arg1);
            func_psp_089338BC(temp_s0, temp_s1);
            break;
        }
    }
    func_psp_08933830(arg0);
}

s32 func_psp_08933E38(s32 arg0) {
    s32 var_s1;
    unkStruct* temp_s0;

    var_s1 = 0;
    func_psp_089337EC(arg0);
    temp_s0 = &D_psp_08E2E5F8[arg0];
    if (temp_s0->unkC == -1) {
        var_s1 = 1;
    } else if (temp_s0->unkC == temp_s0->unk8) {
        var_s1 = 1;
    }
    func_psp_08933830(arg0);
    return var_s1;
}

void func_psp_08933ED8(s32 arg0) {
    unkStruct* temp_s0;

    func_psp_089337EC(arg0);
    temp_s0 = &D_psp_08E2E5F8[arg0];
    func_psp_08933954(temp_s0);
    func_psp_08933830(arg0);
    sceDisplayWaitVblankStartCB();
    temp_s0->unkC = -1;
    temp_s0->unk8 = -1;
}

u8* func_psp_08933F5C(void) { return D_psp_0908C8C0; }

s32 func_psp_08933F6C(void) { return D_psp_090DC8C0; }
