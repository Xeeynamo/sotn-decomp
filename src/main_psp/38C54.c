// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspiofilemgr.h>

typedef struct {
    s32 (*unk0)(void);
} unk_08935640;

INCLUDE_ASM("main_psp/nonmatchings/main_psp/38C54", func_psp_08937560);

void func_psp_089375A0(void) { func_psp_0893573C(); }

void func_psp_089375C0(s32* arg0, s32 arg1) {
    s32* var_s1 = arg0;
    s32* var_s0 = arg0;
    s32 var_s2 = var_s0[5];

    sceKernelDcacheWritebackAll();
    sceKernelIcacheInvalidateAll();
    if (var_s2 != 0) {
        var_s1 = (s32*)((u32)var_s1 + arg1);
        memset(var_s1, 0, var_s2);
    }
    func_psp_089356A0((unk_08935640*)var_s0[6], var_s0[7], 0, 0);
}

void func_psp_08937650() {}

s32 func_psp_08937658(char* file, void* buf) {
    s32 size;
    s32 fd;
    s32 ret;
    s32 var_s3;

    fd = -1;
    var_s3 = 0;
    ret = 0;
    fd = sceIoOpen(file, PSP_O_RDONLY, 0);
    if (fd >= 0) {
        ret = sceIoLseek(fd, 0, PSP_SEEK_END);
        sceIoLseek(fd, 0, PSP_SEEK_SET);
    }
    if (ret != 0) {
        size = ret;
        ret = sceIoRead(fd, buf, size);
        if (ret != size) {
            ret = -1;
        }
    }
    if (fd >= 0) {
        sceIoClose(fd);
    }
    return ret;
}

s32 func_psp_08937740(char* file, void* buf) {
    s32 size = 0;
    bool ret = false;

    size = func_psp_08937658(file, buf);
    if (size > 0) {
        func_psp_08937650(buf);
        func_psp_089375C0(buf, size);
        ret = true;
    }
    return ret;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/38C54", func_psp_089377B8);
