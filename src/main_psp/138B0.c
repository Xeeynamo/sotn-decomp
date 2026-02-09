// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>
#include "main_psp_private.h"
#include "mpeg/mpeg_private.h"

#include <pspgu.h>
#include <pspumd.h>
#include <psppower.h>

typedef struct unkStruct {
    char* unk0;
    s32 unk4;
} unkStruct;

char D_psp_0893CD20[] = "DVDUMD_SAMPLE";
char D_psp_0893CD30[] = PSP_UMD_ALIAS_NAME;
char D_psp_0893CD38[] = "DVDUMD_CTRL";
extern s32 g_drawWallpaperBackground;
extern s32 D_psp_08B1FB54;
extern s32 D_psp_08B1FB58;
extern s32 D_psp_08B1FB5C;
extern s32 D_psp_08B1FB60;
extern s32 D_psp_08B1FB64;
extern s32 D_psp_08B1FB68;
extern s32 D_psp_08B1FB6C;
extern s32 D_psp_08B1FB70;
extern s32 D_psp_08B41FF0;
extern volatile s32 D_psp_08B1FB50;
extern s32 D_psp_08B1FB7C;
extern char D_psp_0893CDB8[];
extern char D_psp_0893CDC8[];
extern char D_psp_0893CDD4[];
extern u32 D_psp_08B1FB80;
extern s32 D_psp_08B1FB84;
extern s32 D_psp_08B42010;
extern s32 D_psp_08B42020;
extern s32 D_psp_08B42030;
extern s32 D_psp_08B1FB90;
extern unkStruct D_psp_0893CD98[];

void func_psp_089144BC(void);

s32 func_psp_089121BC(s32 count, s32 arg, void* param) {
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

    D_psp_08B1FB50 =
        sceKernelCreateCallback(D_psp_0893CD20, func_psp_089121BC, NULL);
    D_psp_08B1FB50;
    ret = sceUmdRegisterUMDCallBack(D_psp_08B1FB50);
    ret;
    if (sceUmdCheckMedium() == 0) {
        sceUmdWaitDriveStatCB(PSP_UMD_MEDIA_IN, 0);
    }
    ret = sceUmdActivate(PSP_UMD_MODE_POWERON, D_psp_0893CD30);
    if (ret < 0) {
        sceUmdUnRegisterUMDCallBack(D_psp_08B1FB50);
        sceKernelDeleteCallback(D_psp_08B1FB50);
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
        D_psp_0893CD38, func_psp_08912398, 0x32, 0x1000, 0, NULL);
    sp18;
    D_psp_08B41FF0 = sp18;
    sp1C = sceKernelStartThread(D_psp_08B41FF0, 0, 0);
    sp1C;
}

s32 func_psp_08912530(s32 count, s32 arg, void* param) {
    if (arg & PSP_POWER_CB_POWER_SWITCH) {
        D_psp_08B1FB70 = 1;
    }
    if (arg & PSP_POWER_CB_HOLD_SWITCH) {
    }
    if (arg & PSP_POWER_CB_STANDBY) {
    }
    if (arg & PSP_POWER_CB_RESUME_COMPLETE) {
        D_psp_08B1FB70 = 0;
        D_psp_08B1FB60 = 0;
        D_psp_08B1FB64++;
    }
    if (arg & PSP_POWER_CB_RESUMING) {
        D_psp_08B1FB60 = 1;
    }
    if (arg & PSP_POWER_CB_SUSPENDING) {
        D_psp_08B1FB60 = 1;
    }
    return 0;
}

s32 func_psp_089125F8(void) { return D_psp_08B1FB64; }

void func_psp_08912608(void) {
    sceKernelPowerLock(0);
    D_psp_08B1FB6C++;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08912640);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891269C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891273C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891274C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891275C);

void func_psp_089127D8(void* arg0) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089127E8);

s32 func_psp_08912814(void) { return 0x5333; }

s32 func_psp_08912820(s32 arg0, s32 arg1) {
    s32 temp_s0;

    func_psp_0892A8C0();
    DrawSync(0);
    VSync(0);
    temp_s0 = func_psp_089128C4(arg0, arg1);
    g_drawWallpaperBackground = 2;
    func_psp_08910044();
    func_psp_0891A800();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    func_psp_089144BC();
    func_psp_089144BC();
    func_psp_089144BC();
    return temp_s0;
}

s32 dispbuf_func(s32 args, void* argp);
s32 read_func(s32 args, void* argp);
s32 soundbuf_func(s32 args, void* argp);
s32 ringbufferCallBack(void* pBuf, s32 iNum, void* CallbackData);
void func_psp_08914E44(t_displayBuffer* pDisp);

s32 func_psp_089128C4(s32 arg0, s32 arg1) {
    SceMpeg mpeg;
    SceMpegRingbuffer ringbuf;
    SceMpegStream* pStream[2];
    SceMpegAu avcAu;
    SceMpegAu atracAu;
    char filename[0x200];
    StrFile strFile;
    s32 bufferSize[1];
    s32 workSize[1];
    s32 fileSize;
    s32 audioEsSize;
    s32 audioOutSize;
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
    unkStruct* temp_s4;

    u8* avcEsBuf;
    u8* pPSPStream;
    u8* pWorkBuf;
    u8* pAudioBuf;

    temp_s4 = &D_psp_0893CD98[arg0];
    memset(&pRing, 0, sizeof(t_ringBuffer));
    func_psp_0891274C();
    avcEsBuf = NULL;
    pPSPStream = NULL;
    pWorkBuf = NULL;
    pAudioBuf = NULL;
    temp_s6 = temp_s4->unk0;
    D_psp_08B1FB7C = temp_s4->unk4;
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
    if (D_psp_08B1FB7C != 0) {
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
    if (D_psp_08B1FB7C != 0) {
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
    if (D_psp_08B1FB7C != 0) {
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
    if (D_psp_08B1FB7C != 0) {
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
    D_psp_08B42010 =
        sceKernelCreateThread(D_psp_0893CDB8, dispbuf_func, 0x3F, 0x2000, 0, 0);
    D_psp_08B42020 =
        sceKernelCreateThread(D_psp_0893CDC8, read_func, 0x41, 0x2000, 0, 0);
    if (D_psp_08B1FB7C != 0) {
        D_psp_08B42030 = sceKernelCreateThread(
            D_psp_0893CDD4, soundbuf_func, 0x3D, 0x2000, 0, 0);
    }
    D_psp_08B1FB84 = 0;
    if (D_psp_08B1FB7C != 0) {
        soundbuf_reset(&pSound);
    }
    dispbuf_reset(&pDisp);
    read_reset(&pRing, fileSize, streamOffset);
    avsync_reset(&pAvSync);
    if (D_psp_08B1FB7C != 0) {
        sceKernelStartThread(D_psp_08B42030, sizeof(t_avSyncControl), &pAvSync);
    }
    sceKernelStartThread(D_psp_08B42010, sizeof(t_avSyncControl), &pAvSync);
    sceKernelStartThread(D_psp_08B42020, sizeof(t_ringBuffer), &pRing);
    if ((ret[0] = playMovie(
             &mpeg, &ringbuf, &pStreamData, &pRing, &pAvSync, arg1)) != 0) {
        if (D_psp_08B1FB84 == 1) {
            if (sceMpegFlushAllStream(&mpeg) != 0) {
                0;
                goto label6;
            }
            D_psp_08B1FB84 = 0;
        } else {
            if (D_psp_08B1FB84 == 0xA) {
                0;
                goto label6;
            }
        }
    }
    if (D_psp_08B1FB7C != 0) {
        sceKernelWaitThreadEnd(D_psp_08B42030, NULL);
    }
    sceKernelWaitThreadEnd(D_psp_08B42010, NULL);
    sceKernelWaitThreadEnd(D_psp_08B42020, NULL);
label6:
    if (D_psp_08B1FB7C != 0) {
        sceKernelWaitThreadEnd(D_psp_08B42030, NULL);
    }
    sceKernelWaitThreadEnd(D_psp_08B42010, NULL);
    sceKernelWaitThreadEnd(D_psp_08B42020, NULL);
    if (D_psp_08B1FB7C != 0) {
        sceKernelTerminateDeleteThread(D_psp_08B42030);
        D_psp_08B42030 = -1;
    }
    sceKernelTerminateDeleteThread(D_psp_08B42010);
    D_psp_08B42010 = -1;
    sceKernelTerminateDeleteThread(D_psp_08B42020);
    D_psp_08B42020 = -1;
label5:
    avsync_delete(&pAvSync);
label4:
    read_delete(&pRing);
label3:
    if (D_psp_08B1FB7C != 0) {
        soundbuf_delete(&pSound);
    }
label2:
    dispbuf_delete(&pDisp);
label1:
    if (D_psp_08B1FB7C != 0) {
        pAudioBuf = NULL;
    }
    sceMpegFreeAvcEsBuf(&mpeg, avcEsBuf);
    sceMpegUnRegistStream(&mpeg, pStream[0]);
    if (D_psp_08B1FB7C != 0) {
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

s32 func_psp_08913314(t_avSyncControl* pAvSync, t_ringBuffer* pRing) {
    s32 var_s0;

    if (D_psp_08B1FB7C != 0) {
        if (dispbuf_getCapacity(pAvSync->pDisp) == 0 &&
            soundbuf_getCapacity(pAvSync->pSound) == 0) {
            func_psp_08913CA0(pAvSync);
            var_s0 = 1;
        } else {
            var_s0 = -1;
        }
    } else {
        if (dispbuf_getCapacity(pAvSync->pDisp) == 0) {
            func_psp_08913CA0(pAvSync);
            var_s0 = 0;
        } else {
            var_s0 = -1;
        }
    }
    return var_s0;
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

s32 func_psp_08913B48(t_displayBuffer* pDisp, s32 arg1) {
    if (arg1 & PadReadPSP()) {
        D_psp_08B1FB84 = 1;
        return 1;
    }
    return 0;
}

s32 avsync_create(t_avSyncControl* pAvSync, t_displayBuffer* pDisp,
                  t_soundBuffer* pSound, s32 videoNum) {
    pAvSync->pDisp = pDisp;
    pAvSync->pSound = pSound;
    pAvSync->video.pts = NULL;
    pAvSync->video.pts = (u32*)func_psp_0891275C(videoNum * 4);
    if (pAvSync->video.pts == NULL) {
        return -1;
    }
    pAvSync->video.size = videoNum;
    return 0;
}

s32 avsync_reset(t_avSyncControl* pAvSync) {
    D_psp_08B1FB90 = 0;
    avsync_init_video(pAvSync);
    return 0;
}

s32 avsync_delete(t_avSyncControl* pAvSync) {
    if (pAvSync->video.pts != NULL) {
        func_psp_089127D8(pAvSync->video.pts);
        pAvSync->video.pts = NULL;
    }
    return 0;
}

s32 func_psp_08913CA0(t_avSyncControl* pAvSync) {
    func_psp_08914E44(pAvSync->pDisp);
    if (pAvSync->pSound != NULL) {
        func_psp_08916310(pAvSync->pSound);
    }
    return 0;
}

s32 avsync_init_video(t_avSyncControl* pAvSync) {
    pAvSync->video.write = 0;
    pAvSync->video.read = 0;
    pAvSync->video.count = 0;
    return 0;
}

s32 avsync_video_setPts(t_avSyncControl* pAvSync, s32 pts) {
    s32 ret = 0;

    if (pts == -1) {
        pts = D_psp_08B1FB90 + 0xBBC;
    }
    D_psp_08B1FB90 = pts;
    pAvSync->video.pts[pAvSync->video.write] = pts;
    pAvSync->video.count++;
    pAvSync->video.write = (pAvSync->video.write + 1) % pAvSync->video.size;
    return ret;
}

s32 avsync_video_getPts(t_avSyncControl* pAvSync, s32* pPts) {
    s32 ret = 0;

    *pPts = pAvSync->video.pts[pAvSync->video.read];
    pAvSync->video.count--;
    pAvSync->video.read = (pAvSync->video.read + 1) % pAvSync->video.size;
    return ret;
}

s32 avsync_Compare(t_avSyncControl* pAvSync) {
    s32 ret;
    s32 ptsDiff;
    u32 soundPts, videoPts;

    if (pAvSync->pSound == NULL) {
        ret = 1;
        goto term;
    }
    if (soundbuf_getCurrentCount(pAvSync->pSound) == 0 ||
        dispbuf_getCurrentCount(pAvSync->pDisp) == 0) {
        ret = 1;
        goto term;
    }
    soundbuf_getPts(pAvSync->pSound, &soundPts);
    dispbuf_getPts(pAvSync->pDisp, &videoPts);
    ptsDiff = soundPts - videoPts;
    if (ptsDiff >= -0x1778 && ptsDiff <= 0x1778) {
        ret = 1;
    } else if (ptsDiff > 0x1778) {
        ret = 2;
    } else {
        ret = 3;
    }
term:
    return ret;
}
