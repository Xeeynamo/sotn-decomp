// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../main_psp_private.h"
#include "mpeg_private.h"

#include <pspgu.h>

#define PLAY_NORMAL (0)
#define PLAY_SKIP (1)
#define PLAY_STOP (10)

// BSS
static s32 D_psp_08B1FB8C;
static s32 D_psp_08B1FB88 UNUSED;
static s32 playMode;
static u32 D_psp_08B1FB80;
static bool audioOn;
static s32 D_psp_08B1FB78;

extern s32 g_drawWallpaperBackground;
extern s32 dispThread;
extern s32 readThread;
extern s32 soundThread;

s32 dispbuf_func(s32 args, void* argp);
s32 read_func(s32 args, void* argp);
s32 soundbuf_func(s32 args, void* argp);
s32 ringbufferCallBack(void* pBuf, s32 iNum, void* CallbackData);

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

s32 func_psp_08912820(s32 movieIdx, s32 skipButton) {
    s32 ret;

    func_psp_0892A8C0();
    DrawSync(0);
    VSync(0);
    ret = func_psp_089128C4(movieIdx, skipButton);
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

s32 func_psp_089128C4(s32 movieIdx, s32 skipButton) {
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
            strFileClose(&strFile);
            D_psp_08B1FB80 = func_psp_089125F8();
            continue;
        }

        if (func_psp_089123B8() == 0) {
            strFileClose(&strFile);
            continue;
        }
        if ((ret[0] = strFileOpen(&strFile, &filename, PSP_O_RDONLY)) >= 0) {
            sceDisplayWaitVblankStartCB();
        } else {
            0;
            continue;
        }

        if (func_psp_089123B8() == 0) {
            strFileClose(&strFile);
            continue;
        }
        if ((ret[0] = readHeader(&mpeg, &strFile, &fileSize, &streamOffset)) ==
            0) {
            sceDisplayWaitVblankStartCB();
        } else {
            strFileClose(&strFile);
            continue;
        }

        if (func_psp_089123B8() == 0) {
            strFileClose(&strFile);
            continue;
        }
        if ((ret[0] = strFileLseek(&strFile, streamOffset, PSP_SEEK_SET)) >=
            0) {
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
        "displayThread", dispbuf_func, 0x3F, 0x2000, 0, NULL);
    readThread =
        sceKernelCreateThread("readThread", read_func, 0x41, 0x2000, 0, NULL);
    if (audioOn) {
        soundThread = sceKernelCreateThread(
            "soundThread", soundbuf_func, 0x3D, 0x2000, 0, NULL);
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
                            skipButton)) != 0) {
        if (playMode == PLAY_SKIP) {
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
    strFileClose(&strFile);
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

INCLUDE_ASM("main_psp/nonmatchings/main_psp/mpeg/13E40", playMovie);

s32 readHeader(
    SceMpeg* pMpeg, StrFile* pStrFile, s32* pFilesize, s32* strOffset) {
    s32 iReadSize[1];
    s32 ret;
    u8 stream_buf[0x800];

    if (strFileLseek(pStrFile, 0, PSP_SEEK_SET) < 0) {
        ret = -1;
        goto term;
    }
    if ((iReadSize[0] = strFileReadNoRetry(pStrFile, stream_buf, 0x800)) <
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
    if (strFileLseek(pStrFile, 0, PSP_SEEK_SET) < 0) {
        ret = -1;
        goto term;
    }
    ret = 0;
term:
    return ret;
}

s32 pad_read(t_displayBuffer* pDisp, s32 skipButton) {
    if (skipButton & PadReadPSP()) {
        playMode = PLAY_SKIP;
        return 1;
    }
    return 0;
}
