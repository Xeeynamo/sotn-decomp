// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>
#include "main_psp_private.h"
#include "mpeg/mpeg_private.h"

#include <pspgu.h>
#include <pspumd.h>
#include <psppower.h>

#define PLAY_NORMAL (0)
#define PLAY_RESTART (1)
#define PLAY_STOP (10)

// BSS
static s32 D_psp_08B1FB8C;
static s32 D_psp_08B1FB88 UNUSED;
static s32 playMode;
static u32 D_psp_08B1FB80;
static bool audioOn;
static s32 D_psp_08B1FB78;
static s32 D_psp_08B1FB74;
static bool D_psp_08B1FB70;
static s32 D_psp_08B1FB6C;
static s32 D_psp_08B1FB68;
static s32 D_psp_08B1FB64;
static bool D_psp_08B1FB60;
static s32 D_psp_08B1FB5C;
static s32 D_psp_08B1FB58;
static s32 D_psp_08B1FB54;
static s32 umd_cb;

extern s32 g_drawWallpaperBackground;
extern s32 D_psp_08B41FF0;
extern s32 dispThread;
extern s32 readThread;
extern s32 soundThread;
extern s32 power_cb;

s32 dispbuf_func(s32 args, void* argp);
s32 read_func(s32 args, void* argp);
s32 soundbuf_func(s32 args, void* argp);
s32 ringbufferCallBack(void* pBuf, s32 iNum, void* CallbackData);

s32 umd_func(s32 count, s32 arg, void* param) {
    D_psp_08B1FB58 = arg;
    if (arg & PSP_UMD_MEDIA_IN) {
        D_psp_08B1FB54 |= 1;
    } else if (arg & PSP_UMD_MEDIA_OUT) {
        D_psp_08B1FB54 = 0;
        D_psp_08B1FB58 = 0;
    }
    if (arg & PSP_UMD_READABLE) {
        D_psp_08B1FB58 = 2;
    } else if (arg & PSP_UMD_READY) {
        D_psp_08B1FB58 = 1;
    } else if (arg & PSP_UMD_NOT_READY) {
        D_psp_08B1FB58 = 0;
    }
    return 0;
}

void func_psp_0891228C(void) {
    volatile s32 ret;

    umd_cb = sceKernelCreateCallback("DVDUMD_SAMPLE", umd_func, NULL);
    if (umd_cb < 0) {
        umd_cb;
    }
    ret = sceUmdRegisterUMDCallBack(umd_cb);
    ret;
    if (sceUmdCheckMedium() == 0) {
        sceUmdWaitDriveStatCB(PSP_UMD_MEDIA_IN, 0);
    }
    ret = sceUmdActivate(PSP_UMD_MODE_POWERON, PSP_UMD_ALIAS_NAME);
    if (ret < 0) {
        sceUmdUnRegisterUMDCallBack(umd_cb);
        sceKernelDeleteCallback(umd_cb);
    }
    D_psp_08B1FB5C = 1;
    sceUmdWaitDriveStatCB(PSP_UMD_READABLE, 0);
    while (func_psp_089123B8() == 0) {
        sceKernelDelayThreadCB(100);
    }
    D_psp_08B1FB54 = 1;
}

s32 func_psp_08912398(s32 argc, void* argv) {
    s32 var_s0;

    while (true) {
        sceKernelDelayThreadCB(100);
    }
    return var_s0;
}

s32 func_psp_089123B8(void) {
    u8 var_s2;
    u8 var_s1;
    u8 var_s0;

    sceKernelWaitSemaCB(D_psp_08B1FB68, 1, NULL);
    sceKernelSignalSema(D_psp_08B1FB68, 1);
    var_s2 = 0;
    var_s1 = 0;
    var_s0 = 0;
    if (D_psp_08B1FB58 == 2 && D_psp_08B1FB54 == 1) {
        var_s0 = 1;
    }
    if (var_s0 && D_psp_08B1FB5C) {
        var_s1 = 1;
    }
    if (var_s1 && !D_psp_08B1FB60 != 0) {
        var_s2 = 1;
    }
    return var_s2;
}

void func_psp_0891249C(void) {
    volatile s32 sp1C;
    volatile s32 sp18;

    D_psp_08B1FB54 = 0;
    D_psp_08B1FB58 = 0;
    D_psp_08B1FB5C = 0;
    func_psp_0891228C();
    sp18 = sceKernelCreateThread(
        "DVDUMD_CTRL", func_psp_08912398, 0x32, 0x1000, 0, NULL);
    sp18;
    D_psp_08B41FF0 = sp18;
    sp1C = sceKernelStartThread(D_psp_08B41FF0, 0, 0);
    sp1C;
}

s32 power_func(s32 count, s32 arg, void* param) {
    if (arg & PSP_POWER_CB_POWER_SWITCH) {
        D_psp_08B1FB70 = true;
    }
    if (arg & PSP_POWER_CB_HOLD_SWITCH) {
    }
    if (arg & PSP_POWER_CB_STANDBY) {
    }
    if (arg & PSP_POWER_CB_RESUME_COMPLETE) {
        D_psp_08B1FB70 = false;
        D_psp_08B1FB60 = false;
        D_psp_08B1FB64++;
    }
    if (arg & PSP_POWER_CB_RESUMING) {
        D_psp_08B1FB60 = true;
    }
    if (arg & PSP_POWER_CB_SUSPENDING) {
        D_psp_08B1FB60 = true;
    }
    return 0;
}

s32 func_psp_089125F8(void) { return D_psp_08B1FB64; }

void func_psp_08912608(void) {
    sceKernelPowerLock(0);
    D_psp_08B1FB6C++;
}

void func_psp_08912640(void) {
    volatile s32* var_s0;

    if (D_psp_08B1FB6C <= 0) {
        var_s0 = &D_psp_08B1FB6C;
        *var_s0;
    }
    D_psp_08B1FB6C--;
    sceKernelPowerUnlock(0);
}

void func_psp_0891269C(void) {
    volatile s32 ret;

    D_psp_08B1FB60 = false;
    D_psp_08B1FB64 = 0;
    power_cb = sceKernelCreateCallback("DVDUMD_SAMPLE", power_func, NULL);
    if (power_cb < 0) {
        power_cb;
    }
    ret = scePowerRegisterCallback(0, power_cb);
    ret;
    D_psp_08B1FB6C = 0;
    D_psp_08B1FB68 = sceKernelCreateSema("p_off_lock_sema", 0, 1, 1, NULL);
}

void func_psp_0891273C(void) { D_psp_08B1FB74 = 0; }

void func_psp_0891274C(void) { D_psp_08B1FB8C = 0; }

s32 func_psp_0891275C(s32 arg0) {
    s32 ret;

    ret = func_psp_08919C8C(D_psp_08B1FB8C);
    D_psp_08B1FB8C += ((arg0 + 0x3FU) / 0x40) * 0x40;
    if (func_psp_08919C8C(D_psp_08B1FB8C) == 0) {
    }
    return ret;
}

void func_psp_089127D8(void* arg0) {}

void func_psp_089127E8(void) {
    dispThread = -1;
    readThread = -1;
    soundThread = -1;
}

s32 func_psp_08912814(void) { return 0x5333; }

s32 func_psp_08912820(s32 movieIdx, s32 restartButton) {
    s32 ret;

    func_psp_0892A8C0();
    DrawSync(0);
    VSync(0);
    ret = func_psp_089128C4(movieIdx, restartButton);
    g_drawWallpaperBackground = 2;
    func_psp_08910044();
    func_psp_0891A800();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    func_psp_089144BC();
    func_psp_089144BC();
    func_psp_089144BC();
    return ret;
}

typedef struct unkStruct {
    char* unk0;
    bool usesAudio;
} unkStruct;

static unkStruct D_psp_0893CD98[] = {
    {"MOVIE/logo.pmf;1", true},
    {"MOVIE/no2.pmf;1", true},
    {"MOVIE/no3.pmf;1", true},
    {"MOVIE/no4.pmf;1", true},
};

s32 func_psp_089128C4(s32 movieIdx, s32 restartButton) {
    SceMpeg mpeg;
    SceMpegRingbuffer ringbuf;
    SceMpegStream* pStream[2];
    SceMpegAu avcAu;
    SceMpegAu atracAu;
    char filename[0x200];

    StrFile strFile;

    s32 bufferSize[1], workSize[1], fileSize;
    s32 audioEsSize, audioOutSize;
    s32 streamOffset;
    s32 ret[1];

    t_displayBuffer pDisp;
    t_ringBuffer pRing;
    t_soundBuffer pSound;
    t_avSyncControl pAvSync;
    t_mpegStreamData pStreamData;

    SceMpegAvcMode decodeMode;
    s32 var_s7;
    char* temp_s6;
    unkStruct* ptr;

    u8* avcEsBuf;
    u8* pPSPStream;
    u8* pWorkBuf;
    u8* pAudioBuf;

    ptr = &D_psp_0893CD98[movieIdx];
    memset(&pRing, 0, sizeof(t_ringBuffer));
    func_psp_0891274C();
    avcEsBuf = NULL;
    pPSPStream = NULL;
    pWorkBuf = NULL;
    pAudioBuf = NULL;
    temp_s6 = ptr->unk0;
    audioOn = ptr->usesAudio;
    decodeMode.iUnk0 = -1;
    decodeMode.iPixelFormat = 3;
    ret[0] = sceMpegInit();
    if (ret[0] != 0) {
        0;
        goto label0;
    }
    bufferSize[0] = sceMpegRingbufferQueryMemSize(0x780);
    if (bufferSize[0] < 0) {
        0;
        goto label0;
    }
    workSize[0] = sceMpegQueryMemSize(0);
    if (workSize[0] < 0) {
        0;
        goto label0;
    }
    pPSPStream = (void*)func_psp_0891275C(bufferSize[0]);
    if (pPSPStream == NULL) {
        0;
        goto label0;
    }
    pWorkBuf = (void*)func_psp_0891275C(workSize[0]);
    if (pWorkBuf == NULL) {
        0;
        goto label0;
    }
    ret[0] = sceMpegRingbufferConstruct(
        &ringbuf, 0x780, pPSPStream, bufferSize[0], ringbufferCallBack,
        &strFile);
    if (ret[0] != 0) {
        0;
        goto label0;
    }
    ret[0] =
        sceMpegCreate(&mpeg, pWorkBuf, workSize[0], &ringbuf, 0x200, 0, NULL);
    if (ret[0] != 0) {
        0;
        goto label0;
    }
    ret[0] = sceMpegAvcDecodeMode(&mpeg, &decodeMode);
    func_psp_0890F250(temp_s6, &filename);
    var_s7 = 0;
    strFile.fd = -1;
    sceDisplayWaitVblankStartCB();
    D_psp_08B1FB80 = func_psp_089125F8();
    while (true) {
        sceDisplayWaitVblankStartCB();
        if (D_psp_08B1FB80 < func_psp_089125F8()) {
            func_psp_08916830(&strFile);
            D_psp_08B1FB80 = func_psp_089125F8();
            continue;
        }

        if (func_psp_089123B8() == 0) {
            func_psp_08916830(&strFile);
            continue;
        }
        if ((ret[0] = func_psp_08916724(&strFile, &filename, PSP_O_RDONLY)) >=
            0) {
            sceDisplayWaitVblankStartCB();
        } else {
            0;
            continue;
        }

        if (func_psp_089123B8() == 0) {
            func_psp_08916830(&strFile);
            continue;
        }
        if ((ret[0] = readHeader(&mpeg, &strFile, &fileSize, &streamOffset)) ==
            0) {
            sceDisplayWaitVblankStartCB();
        } else {
            func_psp_08916830(&strFile);
            continue;
        }

        if (func_psp_089123B8() == 0) {
            func_psp_08916830(&strFile);
            continue;
        }
        if ((ret[0] = func_psp_089168E8(
                 &strFile, streamOffset, PSP_SEEK_SET)) >= 0) {
            sceDisplayWaitVblankStartCB();
        } else {
            0;
            continue;
        }
        break;
    }
    sceKernelDelayThreadCB(16666);
    pStream[0] = sceMpegRegistStream(&mpeg, 0, 0);
    if (pStream[0] == NULL) {
        0;
        goto label1;
    }
    if (audioOn) {
        pStream[1] = sceMpegRegistStream(&mpeg, 1, 0);
        if (pStream[1] == NULL) {
            0;
            goto label1;
        }
    }
    avcEsBuf = sceMpegMallocAvcEsBuf(&mpeg);
    if (avcEsBuf == NULL) {
        0;
        goto label1;
    }
    ret[0] = sceMpegInitAu(&mpeg, avcEsBuf, &avcAu);
    if (ret[0] != 0) {
        0;
        goto label1;
    }
    if (audioOn) {
        ret[0] = sceMpegQueryAtracEsSize(&mpeg, &audioEsSize, &audioOutSize);
        if (ret[0] != 0) {
            0;
            goto label1;
        }
        pAudioBuf = (u8*)func_psp_0891275C(audioEsSize);
        if (pAudioBuf == NULL) {
            0;
            goto label1;
        }
        ret[0] = sceMpegInitAu(&mpeg, pAudioBuf, &atracAu);
        if (ret[0] != 0) {
            0;
            goto label1;
        }
    }
    pStreamData.pAvcStream = pStream[0];
    pStreamData.pAtracStream = pStream[1];
    pStreamData.pAvcAu = &avcAu;
    pStreamData.pAtracAu = &atracAu;
    if (dispbuf_create(&pDisp, 0x78000, 1, decodeMode.iPixelFormat) < 0) {
        0;
        goto label2;
    }
    if (audioOn) {
        if (soundbuf_create(&pSound, audioOutSize, 4, func_psp_08912814()) <
            0) {
            0;
            goto label3;
        }
    }
    if (read_create(&pRing, &ringbuf, &strFile) < 0) {
        0;
        goto label4;
    }
    if (audioOn) {
        if (avsync_create(&pAvSync, &pDisp, &pSound, 3) < 0) {
            0;
            goto label5;
        }
    } else {
        if (avsync_create(&pAvSync, &pDisp, NULL, 3) < 0) {
            0;
            goto label5;
        }
    }
    sceKernelChangeThreadPriority(sceKernelGetThreadId(), 0x40);
    dispThread = sceKernelCreateThread(
        "displayThread", dispbuf_func, 0x3F, 0x2000, 0, 0);
    readThread =
        sceKernelCreateThread("readThread", read_func, 0x41, 0x2000, 0, 0);
    if (audioOn) {
        soundThread = sceKernelCreateThread(
            "soundThread", soundbuf_func, 0x3D, 0x2000, 0, 0);
    }
    playMode = PLAY_NORMAL;
    if (audioOn) {
        soundbuf_reset(&pSound);
    }
    dispbuf_reset(&pDisp);
    read_reset(&pRing, fileSize, streamOffset);
    avsync_reset(&pAvSync);
    if (audioOn) {
        sceKernelStartThread(soundThread, sizeof(t_avSyncControl), &pAvSync);
    }
    sceKernelStartThread(dispThread, sizeof(t_avSyncControl), &pAvSync);
    sceKernelStartThread(readThread, sizeof(t_ringBuffer), &pRing);
    if ((ret[0] = playMovie(&mpeg, &ringbuf, &pStreamData, &pRing, &pAvSync,
                            restartButton)) != 0) {
        if (playMode == PLAY_RESTART) {
            if (sceMpegFlushAllStream(&mpeg) != 0) {
                0;
                goto label6;
            }
            playMode = PLAY_NORMAL;
        } else {
            if (playMode == PLAY_STOP) {
                0;
                goto label6;
            }
        }
    }
    if (audioOn) {
        sceKernelWaitThreadEnd(soundThread, NULL);
    }
    sceKernelWaitThreadEnd(dispThread, NULL);
    sceKernelWaitThreadEnd(readThread, NULL);
label6:
    if (audioOn) {
        sceKernelWaitThreadEnd(soundThread, NULL);
    }
    sceKernelWaitThreadEnd(dispThread, NULL);
    sceKernelWaitThreadEnd(readThread, NULL);
    if (audioOn) {
        sceKernelTerminateDeleteThread(soundThread);
        soundThread = -1;
    }
    sceKernelTerminateDeleteThread(dispThread);
    dispThread = -1;
    sceKernelTerminateDeleteThread(readThread);
    readThread = -1;
label5:
    avsync_delete(&pAvSync);
label4:
    read_delete(&pRing);
label3:
    if (audioOn) {
        soundbuf_delete(&pSound);
    }
label2:
    dispbuf_delete(&pDisp);
label1:
    if (audioOn) {
        pAudioBuf = NULL;
    }
    sceMpegFreeAvcEsBuf(&mpeg, avcEsBuf);
    sceMpegUnRegistStream(&mpeg, pStream[0]);
    if (audioOn) {
        sceMpegUnRegistStream(&mpeg, pStream[1]);
    }
label0:
    func_psp_08916830(&strFile);
    sceMpegDelete(&mpeg);
    sceMpegRingbufferDestruct(&ringbuf);
    sceMpegFinish();
    if (pWorkBuf != NULL) {
        func_psp_089127D8(pWorkBuf);
    }
    if (pPSPStream != NULL) {
        func_psp_089127D8(pPSPStream);
    }

    return (ret[0] == 0xA) ? 1 : 0;
}

s32 func_psp_089132C8(t_avSyncControl* pAvSync, t_ringBuffer* pRing) {
    s32 ret;

    if (func_psp_0891527C(pRing)) {
        ret = 1;
    } else {
        ret = -1;
    }
    return ret;
}

s32 startCheck(t_avSyncControl* pAvSync, t_ringBuffer* pRing) {
    s32 ret;

    if (audioOn) {
        if (dispbuf_getCapacity(pAvSync->pDisp) == 0 &&
            soundbuf_getCapacity(pAvSync->pSound) == 0) {
            avsync_startAudioVideo(pAvSync);
            ret = 1;
        } else {
            ret = -1;
        }
    } else {
        if (dispbuf_getCapacity(pAvSync->pDisp) == 0) {
            avsync_startAudioVideo(pAvSync);
            ret = 0;
        } else {
            ret = -1;
        }
    }
    return ret;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", playMovie);

s32 readHeader(
    SceMpeg* pMpeg, StrFile* pStrFile, s32* pFilesize, s32* strOffset) {
    s32 iReadSize[1];
    s32 ret;
    u8 stream_buf[0x800];

    if (func_psp_089168E8(pStrFile, 0, PSP_SEEK_SET) < 0) {
        ret = -1;
        goto term;
    }
    if ((iReadSize[0] = func_psp_0891689C(pStrFile, stream_buf, 0x800)) <
        0x800) {
        ret = -1;
        goto term;
    }
    if (sceMpegQueryStreamOffset(pMpeg, stream_buf, strOffset) != 0) {
        ret = -1;
        goto term;
    }
    if (sceMpegQueryStreamSize(stream_buf, pFilesize) != 0) {
        ret = -1;
        goto term;
    }
    if (func_psp_089168E8(pStrFile, 0, PSP_SEEK_SET) < 0) {
        ret = -1;
        goto term;
    }
    ret = 0;
term:
    return ret;
}

s32 pad_read(t_displayBuffer* pDisp, s32 restartButton) {
    if (restartButton & PadReadPSP()) {
        playMode = PLAY_RESTART;
        return 1;
    }
    return 0;
}
