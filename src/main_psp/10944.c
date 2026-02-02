// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspiofilemgr.h>

extern char D_psp_089B6330[];

void func_psp_0890F250(s8* arg0, char* arg1) {
    s32 i, j;
    s8* ptr;

    ptr = (s8*)"disc0:/PSP_GAME/USRDIR/res/ps/";
    i = 0;
    do {
        arg1[i] = ptr[i];
        i++;
    } while (ptr[i]);
    j = 0;
    do {
        arg1[i] = arg0[j];
        i++;
        j++;
    } while (arg0[j] != ';');
    arg1[i] = 0;
}

s32 func_psp_0890F300(char* file, SceIoStat* stat) {
    s32 ret;

    sceKernelDelayThreadCB(1);
    func_psp_08912608();
    sceKernelDelayThreadCB(1);
    ret = sceIoGetstat(file, stat);
    func_psp_08912640();
    sceKernelDelayThreadCB(1);
    return ret;
}

s32 func_psp_0890F374(s32 fd) {
    s32 ret;

    sceKernelDelayThreadCB(1);
    func_psp_08912608();
    sceKernelDelayThreadCB(1);
    ret = sceIoClose(fd);
    func_psp_08912640();
    sceKernelDelayThreadCB(1);
    return ret;
}

s32 func_psp_0890F3E0(char* file, s32 flags, s32 mode) {
    s32 ret;

    sceKernelDelayThreadCB(1);
    func_psp_08912608();
    sceKernelDelayThreadCB(1);
    ret = sceIoOpenAsync(file, flags, mode);
    func_psp_08912640();
    sceKernelDelayThreadCB(1);
    return ret;
}

s32 func_psp_0890F45C(s32 fd, s64 offset, s32 whence) {
    s32 ret;

    sceKernelDelayThreadCB(1);
    func_psp_08912608();
    sceKernelDelayThreadCB(1);
    ret = sceIoLseekAsync(fd, offset, whence);
    func_psp_08912640();
    sceKernelDelayThreadCB(1);
    return ret;
}

s32 func_psp_0890F4E0(s32 fd, void* buf, u32 nbyte) {
    s32 ret;

    sceKernelDelayThreadCB(1);
    func_psp_08912608();
    sceKernelDelayThreadCB(1);
    ret = sceIoReadAsync(fd, buf, nbyte);
    func_psp_08912640();
    sceKernelDelayThreadCB(1);
    return ret;
}

s32 func_psp_0890F55C(s32 fd, s64* result) {
    s32 ret;

    sceKernelDelayThreadCB(1);
    func_psp_08912608();
    sceKernelDelayThreadCB(1);
    ret = sceIoPollAsync(fd, result);
    func_psp_08912640();
    sceKernelDelayThreadCB(1);
    return ret;
}

s32 func_psp_0890F5D0(s32* arg0, s32 arg1) {
    volatile s32 ret;
    s64 result;

    while (true) {
        result = 0;
        ret = func_psp_0890F55C(*arg0, &result);
        if (ret == 0) {
            if ((s32)result < 0) {
                return -1;
            }
            return 0;
        }
        if (ret != 1) {
            return -1;
        }
        sceKernelDelayThreadCB(166);
    }
}

s32 func_psp_0890F670(s8* arg0) {
    s32 ret;

    sceKernelDelayThreadCB(166);
    while (func_psp_089123B8() == 0) {
        sceKernelDelayThreadCB(16666);
    }
    func_psp_0890F250(arg0, D_psp_089B6330);
    while (true) {
        ret = func_psp_0890F3E0(D_psp_089B6330, PSP_O_RDONLY, 0x1FF);
        if (ret < 0) {
            sceKernelDelayThreadCB(166);
            continue;
        }
        if (func_psp_0890F5D0(&ret, 0) == 0) {
            break;
        } else {
            while (func_psp_089123B8() == 0) {
                sceKernelDelayThreadCB(166);
            }
        }
    }

    return ret;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/10944", func_psp_0890F754);

void func_psp_0890F7CC(void* buf, s32* arg1, s32 offset, s32 nbyte, s8* arg4) {
    bool var_s0;
    s32 var_s1;

    var_s0 = false;
    sceKernelDelayThreadCB(166);
    while (func_psp_089123B8() == 0) {
        var_s0 = true;
        sceKernelDelayThreadCB(166);
    }
    while (true) {
        if (var_s0 || *arg1 == -1) {
            var_s0 = false;
            if (*arg1 != -1) {
                func_psp_0890F754(*arg1);
                *arg1 = -1;
            }
            func_psp_0890F250(arg4, D_psp_089B6330);
            while (true) {
                *arg1 = func_psp_0890F3E0(D_psp_089B6330, PSP_O_RDONLY, 0x1FF);
                if (*arg1 < 0) {
                    sceKernelDelayThreadCB(166);
                    continue;
                }
                if (func_psp_0890F5D0(arg1, 0)) {

                } else {
                    break;
                }
                while (func_psp_089123B8() == 0) {
                    sceKernelDelayThreadCB(166);
                }
            }
        }
        var_s1 = nbyte;
        var_s0 = false;
        while (true) {
            if (func_psp_0890F45C(*arg1, offset, 0) == 0) {
                break;
            }
            sceKernelDelayThreadCB(166);
        }
        if (func_psp_0890F5D0(arg1, 0)) {
            while (func_psp_089123B8() == 0) {
                sceKernelDelayThreadCB(166);
            }
            var_s0 = true;
        }
        if (var_s0) {
            sceKernelDelayThreadCB(166);
            continue;
        }
        sceKernelDelayThreadCB(166);
        var_s0 = false;
        while (true) {
            if (func_psp_0890F4E0(*arg1, buf, nbyte) == 0) {
                break;
            }
            sceKernelDelayThreadCB(166);
        }
        if (func_psp_0890F5D0(arg1, var_s1)) {
            while (func_psp_089123B8() == 0) {
                sceKernelDelayThreadCB(166);
            }
            var_s0 = true;
        }
        if (!var_s0) {
            break;
        }
        sceKernelDelayThreadCB(166);
    }

    sceKernelDelayThreadCB(166);
    sceKernelDcacheWritebackAll();
}

s32 func_psp_0890FA7C(s8* arg0) {
    SceIoStat stat;
    s8* src;
    s32 ret;
    s8* dst;

    dst = (s8*)D_psp_089B6330;
    src = (s8*)"disc0:/PSP_GAME/USRDIR/res/ps/";

    while (*src != 0) {
        *dst++ = *src++;
    }
    src = arg0;
    while (*src != 0 && *src != ';') {
        *dst++ = *src++;
    }
    *dst = 0;
    if ((ret = func_psp_0890F300(D_psp_089B6330, &stat)) != 0) {
        return -1;
    }
    return stat.st_size;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/10944", func_psp_0890FB70);

void func_psp_0890FBEC(char* arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_psp_0890FB70(arg0, arg1, arg2, arg3);
}
