// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sound_private.h"

// clang-format off
#define SCE_ERROR_ERRNO_ENOENT			0x80010002		// Associated file or directory does not exist
#define SCE_ERROR_ERRNO_EBADF			0x80010009		// Invalid file descriptor
#define SCE_ERROR_ERRNO_ENOMEM			0x8001000C		// Not enough memory
#define SCE_ERROR_ERRNO_EFAULT			0x8001000E		// Invalid address
#define SCE_ERROR_ERRNO_ENODEV			0x80010013		// Associated device was not found
#define SCE_ERROR_ERRNO_EINVAL			0x80010016		// Invalid argument
#define SCE_ERROR_ERRNO_ENAMETOOLONG	0x8001005B		// File name or path name is too long
#define SCE_ERROR_ERRNO_NOMAIN_ADDR		0x8001B001		// Specified address outside of MAIN memory
#define SCE_ERROR_ERRNO_EUNIT			0x8001B002		// Unit number is invalid
#define SCE_ERROR_ERRNO_EFSIZE			0x8001B003		// File size is invalid
#define SCE_UMD_NOT_DEVICE_READY		0x80210001		// Device not ready
#define SCE_UMD_LBA_OUTOFRANGE			0x80210002		// Access beyond last LBA
#define SCE_UMD_NO_MEDIUM				0x80210003		// No medium
// clang-format on

static s32 gDvdUmdIoSemaphoreId = -1;

s32 DvdUmdIoInit(void) {
    s32 ret;

    if (gDvdUmdIoSemaphoreId >= 0) {
        return SCE_KERNEL_ERROR_OK;
    }
    ret = sceKernelCreateSema("UMD_SAMPLE_IO_SEMA", 0, 1, 1, NULL);
    if (ret < 0) {
        return ret;
    }
    gDvdUmdIoSemaphoreId = ret;
    return SCE_KERNEL_ERROR_OK;
}

s32 DvdUmdIoTerm(void) {
    s32 uid;

    if (gDvdUmdIoSemaphoreId >= 0) {
        sceUmdCancelWaitDriveStat();
        sceKernelWaitSema(gDvdUmdIoSemaphoreId, 1, NULL);
        uid = gDvdUmdIoSemaphoreId;
        gDvdUmdIoSemaphoreId = -1;
        sceKernelDeleteSema(uid);
    }
    return SCE_KERNEL_ERROR_OK;
}

static inline s32 DvdUmdRetryWaitSema(void) {
    return sceKernelWaitSema(gDvdUmdIoSemaphoreId, 1, NULL);
}

static inline s32 DvdUmdRetrySignalSema(void) {
    return sceKernelSignalSema(gDvdUmdIoSemaphoreId, 1);
}

s32 DvdUmdRetryOpenCB(const char* filepath, s32 flag, s32 mode) {
    s32 ret;

    while (true) {
        if (!(sceUmdGetDriveStat() & PSP_UMD_READABLE)) {
            ret = sceUmdWaitDriveStat(PSP_UMD_READABLE);
            if (ret < 0) {
                sceKernelDelayThreadCB(100000);
                break;
            }
        }
        ret = DvdUmdRetryWaitSema();
        if (ret < 0) {
            sceKernelDelayThreadCB(100000);
            break;
        }
        ret = sceIoOpen(filepath, flag, mode);
        sceKernelSignalSema(gDvdUmdIoSemaphoreId, 1);
        if (ret >= 0 || ret == SCE_ERROR_ERRNO_EUNIT ||
            ret == SCE_ERROR_ERRNO_ENODEV || ret == SCE_ERROR_ERRNO_ENOENT ||
            ret == SCE_ERROR_ERRNO_ENOMEM || ret == SCE_ERROR_ERRNO_EINVAL ||
            ret == SCE_ERROR_ERRNO_ENAMETOOLONG) {
            break;
        }
        sceKernelDelayThreadCB(100000);
    }
    return ret;
}

s32 DvdUmdRetryRead(s32 fd, void* readbuf, u32 readsize) {
    volatile s32 ret;

    while (true) {
        if (!(sceUmdGetDriveStat() & PSP_UMD_READABLE)) {
            ret = sceUmdWaitDriveStat(PSP_UMD_READABLE);
            if (ret < 0) {
                break;
            }
        }
        ret = DvdUmdRetryWaitSema();
        if (ret < 0) {
            break;
        }
        ret = sceIoRead(fd, readbuf, readsize);
        DvdUmdRetrySignalSema();
        if (ret >= 0 || ret == SCE_ERROR_ERRNO_EBADF ||
            ret == SCE_ERROR_ERRNO_EINVAL || ret == SCE_ERROR_ERRNO_ENODEV ||
            ret == SCE_ERROR_ERRNO_EFSIZE || ret == SCE_ERROR_ERRNO_EFAULT ||
            ret == SCE_UMD_LBA_OUTOFRANGE ||
            ret == SCE_ERROR_ERRNO_NOMAIN_ADDR ||
            ret == SCE_ERROR_ERRNO_ENAMETOOLONG) {
            break;
        }
        if (ret == SCE_UMD_NO_MEDIUM || ret == SCE_UMD_NOT_DEVICE_READY ||
            sceUmdGetDriveStat() & PSP_UMD_MEDIA_OUT) {
            ret = sceUmdWaitDriveStat(PSP_UMD_MEDIA_IN);
            if (ret < 0) {
                break;
            }
        }
        ret = sceUmdWaitDriveStat(PSP_UMD_READABLE);
        if (ret < 0) {
            break;
        }
    }
    return ret;
}
