// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include "sound_private.h"

#define STACKSIZE (1024 * 64)

static u8* firstBuffers[2];
static u8* secondBuffers[2];
static s32 threadIDs[2];
static SceBGMArg bgmArgs[2];
static s32 playFlags[2];
static s32 status;
static s32 thread_status;
static bool dvd_umdAssignFlag;

s32 play_bgm(u32 args, void* argp);

s32 strFileAssign(char* filename) {
    if (memcmp(filename, PSP_UMD_ALIAS_NAME, 6) == 0 && !dvd_umdAssignFlag) {
        dvd_umdAssignFlag = true;
        if (sceUmdActivate(PSP_UMD_MODE_POWERON, PSP_UMD_ALIAS_NAME) < 0) {
            return -1;
        }
        DvdUmdIoInit();
    }
    return 0;
}

s32 strFileUnassign(void) {
    s32 ret;

    ret = 1;
    if (dvd_umdAssignFlag) {
        if (sceUmdDeactivate(2, PSP_UMD_ALIAS_NAME) >= 0) {
            dvd_umdAssignFlag = false;
        }
        ret = DvdUmdIoTerm();
    }
    return ret;
}

s32 func_psp_0892A2D8(void) {
    s32 i;
    s32 var_s3;

    var_s3 = 0;
    for (i = 0; i < 2; i++) {
        firstBuffers[i] = (u8*)func_psp_08919C8C(var_s3);
        secondBuffers[i] = (u8*)func_psp_08919C8C(var_s3 + 0x20040);
        var_s3 += 0x30080;
        threadIDs[i] = -1;
    }
    playFlags[0] = createPlayModeFlag("AT3plusBGMFlag0");
    if (playFlags[0] < 0) {
        status = playFlags[0];
        return -3;
    }
    playFlags[1] = createPlayModeFlag("AT3plusBGMFlag1");
    if (playFlags[1] < 0) {
        status = playFlags[1];
        return -3;
    }
    return 0;
}

void func_psp_0892A3D4(void) {
    if (func_psp_08917E4C() != 0) {
        status = -1;
    }
    status = strFileUnassign();
}

s32 func_psp_0892A414(
    s32 arg0, char* filename, bool loop, s32 arg3, u8* buf, s32 fileSize) {
    if (arg0 < 0 || arg0 >= 2) {
        return -1;
    }
    func_psp_0892A620(arg0, false);
    status = strFileAssign(filename);
    if (status < 0) {
        return -1;
    }
    bgmArgs[arg0].filename = filename;
    bgmArgs[arg0].pucFirstBuf = (buf != NULL) ? buf : firstBuffers[arg0];
    bgmArgs[arg0].iFirstBufSize = 0x20000;
    bgmArgs[arg0].pucSecondBuf = secondBuffers[arg0];
    bgmArgs[arg0].iSecondBufSize = 0x10000;
    bgmArgs[arg0].iOutputChannel = arg0 + 1;
    bgmArgs[arg0].playFlag = playFlags[arg0];
    bgmArgs[arg0].loop = loop;
    bgmArgs[arg0].fileSize = (buf != NULL) ? fileSize : 0;
    threadIDs[arg0] = sceKernelCreateThread(
        "at3 thread 0", play_bgm, KERNEL_USER_HIGHEST_PRIORITY, STACKSIZE, 0,
        NULL);
    if (threadIDs[arg0] < 0) {
        status = threadIDs[arg0];
        threadIDs[arg0] = -1;
        return -1;
    }
    status = sceKernelStartThread(
        threadIDs[arg0], sizeof(SceBGMArg), &bgmArgs[arg0]);
    if (status != 0) {
        threadIDs[arg0] = -1;
        return -2;
    }
    return 0;
}

s32 func_psp_0892A620(s32 arg0, bool arg1) {
    if (arg0 < 0 || arg0 >= 2) {
        return -1;
    }
    if (threadIDs[arg0] >= 0) {
        setPlayMode(playFlags[arg0], BGM_UNK_40);
        setPlayMode(playFlags[arg0], BGM_PLAY_FINISH);
        if (arg1) {
            setPlayMode(playFlags[arg0], BGM_UNK_100);
        }
        sceKernelDelayThreadCB(1000);
        thread_status = sceKernelWaitThreadEnd(threadIDs[arg0], NULL);
        if (thread_status != SCE_KERNEL_ERROR_OK) {
            status = thread_status;
        }
        thread_status = sceKernelDeleteThread(threadIDs[arg0]);
        if (thread_status != SCE_KERNEL_ERROR_OK) {
            status = thread_status;
        }
        threadIDs[arg0] = -1;
    }
    return 0;
}

s32 func_psp_0892A70C(s32 arg0) {
    if (arg0 < 0 || arg0 >= 2) {
        return -1;
    }
    if (threadIDs[arg0] >= 0) {
        setPlayMode(playFlags[arg0], BGM_UNK_20);
    }
    return 0;
}

s32 func_psp_0892A76C(s32 arg0) {
    if (arg0 < 0 || arg0 >= 2) {
        return -1;
    }
    if (threadIDs[arg0] >= 0) {
        setPlayMode(playFlags[arg0], BGM_PLAY_START);
        setPlayMode(playFlags[arg0], BGM_UNK_40);
    }
    return 0;
}

s32 func_psp_0892A7E0(s32 arg0) {
    s32 ret = 0;

    if (arg0 < 0 || arg0 >= 2) {
        return ret;
    }
    if (checkPlayMode(playFlags[arg0], BGM_UNK_80)) {
        ret |= BGM_UNK_80;
    }
    if (checkPlayMode(playFlags[arg0], BGM_PLAY_FINISH)) {
        ret |= BGM_PLAY_FINISH;
    }
    if (checkPlayMode(playFlags[arg0], BGM_UNK_20)) {
        ret |= BGM_UNK_20;
    }
    if (checkPlayMode(playFlags[arg0], BGM_PLAY_START)) {
        ret |= BGM_PLAY_START;
    }
    if (checkPlayMode(playFlags[arg0], BGM_INIT_END)) {
        ret |= BGM_INIT_END;
    }
    if (checkPlayMode(playFlags[arg0], BGM_INIT_START)) {
        ret |= BGM_INIT_START;
    }
    return ret;
}

void func_psp_0892A8C0(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_psp_0892A620(i, false);
    }
}

void func_psp_0892A8FC(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (threadIDs[i] >= 0) {
            if (checkPlayMode(playFlags[i], BGM_INIT_END)) {
                setPlayMode(playFlags[i], BGM_PLAY_START);
            }
        }
    }
}

void func_psp_0892A97C(s32 arg0, s32 arg1) {
    setPlayMode(playFlags[arg0], BGM_UNK_80);
}

void func_psp_0892A998(void) {
    setPlayMode(playFlags[0], 0x0FFFFFFF);
    setPlayMode(playFlags[1], 0x0FFFFFFF);
}

static s32 D_psp_08962E7C = 0x8000;

void func_psp_0892A9D4(s32 arg0) { D_psp_08962E7C = arg0; }

s32 func_psp_0892A9E0(void) { return D_psp_08962E7C; }
