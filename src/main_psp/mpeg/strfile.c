// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mpeg_private.h"

#include <pspumd.h>

s32 func_psp_08916630(char* filename) {
    s32 ret;

    if (memcmp(filename, "host0", 5) != 0) {
        if (memcmp(filename, "disc0", 5) == 0) {
            do {
                sceUmdActivate(PSP_UMD_MODE_POWERON, PSP_UMD_ALIAS_NAME);
                ret = sceUmdGetErrorStat();
                if (ret < 0) {
                    sceKernelDelayThreadCB(100);
                }
            } while (ret < 0);
            do {
                ret = sceUmdWaitDriveStatCB(PSP_UMD_READABLE, 100);
            } while (ret < 0);
            goto term;
        }
        if (memcmp(filename, "ms0:", 3) != 0) {
            return -1;
        }
        goto term;
    }
term:
    return 1;
}

s32 func_psp_08916724(StrFile* file, char* filename, s32 flags) {
    if (memcmp(filename, "host0", 5) == 0 ||
        memcmp(filename, "disc0", 5) == 0 ||
        memcmp(filename, "prfat0", 6) == 0 || memcmp(filename, "ms0", 3) == 0) {
        func_psp_08916630(filename);
        file->fd = sceIoOpen(filename, flags, 0777);
        if (file->fd < 0) {
            return -1;
        }
    } else {
        return -1;
    }
    strcpy(&file->unk16, filename);
    return 1;
}

s32 func_psp_08916830(StrFile* file) {
    s32 ret;

    if (file->fd >= 0) {
        ret = sceIoClose(file->fd);
        file->fd = -1;
    } else {
        return -1;
    }
    return ret;
}

s32 func_psp_0891689C(StrFile* file, void* buff, s32 size) {
    s32 readsize;

    readsize = sceIoRead(file->fd, buff, size);

    return readsize;
}

SceOff func_psp_089168E8(StrFile* file, SceOff offset, s32 whence) {
    return sceIoLseek(file->fd, offset, whence);
}
