// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>
#include "main_psp_private.h"

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspgu.h>
#include <pspdisplay.h>
#include <pspumd.h>
#include <psppower.h>
#include <pspmpeg.h>
#include <pspiofilemgr.h>

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
extern s32 D_psp_089B7140[2][0xD000];
extern ScePspIMatrix4 D_psp_0893CDE0;
extern s16 D_psp_08B1FBB4;
extern s16 D_psp_08B1FBB6;
extern s32 D_psp_08C62A30;
extern s32 D_psp_08B1FBA8;
extern s32 D_psp_08B1FBAC;
extern s16 D_psp_08B1FBB0;
extern s16 D_psp_08B1FBB2;
extern s32 D_psp_08B1FBB8;
extern s32 D_psp_0893CE60;
extern s32 soundframeCount;
extern s32 soundframeDelay;
extern s32 D_psp_08B1FB7C;
extern u32 D_psp_08B1FBF8;
extern char D_psp_0893CE64[];
extern char D_psp_0893CE74[];
extern s32 D_psp_08B1FBDC;
extern s32 D_psp_08B1FBE0;
extern s32 D_psp_08B1FBE4;
extern s32 D_psp_08B1FBE8;
extern s32 D_psp_08B1FBEC;
extern char D_psp_0893CE20[];
extern char D_psp_0893CE2C[];
extern char D_psp_0893CE38[];
extern s32 D_psp_08B1FB94;
extern s32 D_psp_08B1FB98;
extern s32 D_psp_08B1FB9C;
extern s32 D_psp_08B1FBA0;
extern s32 D_psp_08B1FBA4;
extern char D_psp_0893CDB8[];
extern char D_psp_0893CDC8[];
extern char D_psp_0893CDD4[];
extern u32 D_psp_08B1FB80;
extern s32 D_psp_08B1FB84;
extern s32 D_psp_08B42010;
extern s32 D_psp_08B42020;
extern s32 D_psp_08B42030;
extern char D_psp_0893CE4C[];
extern s32 D_psp_08B1FBBC;
extern s32 D_psp_08B1FBC0;
extern s32 D_psp_08B1FBC4;
extern u32 D_psp_08B1FBC8;
extern s32 D_psp_08B1FBD8;
extern s32 D_psp_08B1FB90;
extern s32 D_psp_08B1FB78;

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

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08912814);

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

typedef struct t_displayBuffer {
    s32 startSema;
    s32 lockSema;
    s32 displayWaitSema;
    u8** buf;
    u32* pts;
    s32* write;
    s32* read;
    s32* count;
    s32* size;
    s32 pixelFormat;
    s32* displayMode;
} t_displayBuffer;

typedef struct t_soundBuffer {
    s32 lockSema;
    s32* unk4;
    u8** buf;
    u32* pts;
    s32* write;
    s32* read;
    s32* count;
    s32* size;
    s32 startSema;
} t_soundBuffer;

typedef struct t_avSync_Video {
    u32* pts;
    s32 write;
    s32 read;
    s32 count;
    s32 size;
} t_avSync_Video;

typedef struct t_avSyncControl {
    t_displayBuffer* pDisp;
    t_soundBuffer* pSound;
    t_avSync_Video video;
} t_avSyncControl;

typedef struct unkStruct {
    char* unk0;
    s32 unk4;
} unkStruct;

typedef struct unkStruct2 {
    u32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u32 unk10;
    u32 unk14;
    s32 unk18;
    u8* unk1C;
    s32 unk20;
    u8 unk24;
    u8 unk25;
    s16 unk26;
    u32 unk28;
    u32 unk2C;
    s32 unk30;
} unkStruct2;

typedef struct StrFile {
    s32 fd;
    s32 unk4;
    unkStruct2* unk8;
    s32 unkC;
    s32 unk10;
    s16 unk14;
    s16 unk16;
    u8 unk18[0x200];
} StrFile;

typedef struct t_mpegStreamData {
    SceMpegStream* pAvcStream;
    SceMpegAu* pAvcAu;
    SceMpegStream* pAtracStream;
    SceMpegAu* pAtracAu;
} t_mpegStreamData;

typedef struct t_ringBuffer {
    s32 dataLen;
    s32 decodeSleepSema;
    SceMpegRingbuffer* pRingbuf;
    s32* statusFlag;
    s32 unk10;
    u8* unk14;
    StrFile* pStrFile;
    unkStruct2 unk1C;
} t_ringBuffer;

s32 dispbuf_func(s32 args, void* argp);
s32 read_func(s32 args, void* argp);
s32 soundbuf_func(s32 args, void* argp);
SceOff func_psp_089168E8(StrFile*, SceOff, s32);
s32 ringbufferCallBack(void* pBuf, s32 iNum, void* CallbackData);
void func_psp_08914E44(t_displayBuffer* pDisp);
void func_psp_08916310(t_soundBuffer* pSound);

extern unkStruct D_psp_0893CD98[];
extern t_ringBuffer* D_psp_08B1FBCC;
extern StrFile* D_psp_08B1FBD0;
extern unkStruct2* D_psp_08B1FBD4;

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
        if ((ret[0] = func_psp_08916724(&strFile, &filename, 1)) >= 0) {
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

    if (func_psp_0891527C(pRing) != 0) {
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

s32 func_psp_08913F5C(t_displayBuffer* pDisp) {
    s32* dispList;

    sceGuInit();
    dispList = D_psp_089B7140[0];
    sceGuStart(0, dispList, sizeof(D_psp_089B7140[0]));
    sceGuDrawBuffer(GU_PSM_5551, GU_VRAM_BP_0, GU_VRAM_WIDTH);
    sceGuDispBuffer(GU_SCR_WIDTH, GU_SCR_HEIGHT, GU_VRAM_BP_1, GU_VRAM_WIDTH);
    sceGuDepthBuffer(GU_VRAM_BP_2, GU_VRAM_WIDTH);
    sceGuOffset(0, 0);
    sceGuScissor(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuTexFilter(GU_LINEAR, GU_LINEAR);
    sceGuTexWrap(GU_REPEAT, GU_REPEAT);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuClearColor(0x00000000);
    sceGuClearDepth(0);
    sceGuClearStencil(0);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_DISPLAY_ON);
    D_psp_08B1FBB0 = 0;
    D_psp_08B1FBB2 = 0;
    D_psp_08B1FBB4 = 0x140;
    D_psp_08B1FBB6 = 0xF0;
    D_psp_08B1FBB8 = 0;
    return 0;
}

void draw_frame(t_displayBuffer* pDisp, u8* buffer) {
    s32* dispList = D_psp_089B7140[0];
    s32 x, y;
    s32 w, h;

    sceGuStart(GU_IMMEDIATE, dispList, sizeof(D_psp_089B7140[0]));
    sceGuClear(GU_CLEAR_ALL);
    sceGuTexMode(GU_PSM_T8, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
    sceGuTexImage(0, 0x200, 0x200, 0x200, (u8*)(WALLPAPER_TEX_ADDR));
    sceGuClutMode(GU_PSM_5551, 0, 0xFF, 0);
    sceGuClutLoad(32, (u8*)(WALLPAPER_CLUT_ADDR));
    sceGuEnable(GU_TEXTURE_2D);
    sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0x00000000);
    sceGuEnable(GU_BLEND);
    sceGuColor(0xFFFFFFFF);
    sceGuSpriteMode(GU_SCR_WIDTH, GU_SCR_HEIGHT, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuDrawSprite(0, 0, 0, 0, 0, GU_NOFLIP, GU_NOROTATE);
    sceGuBlendFunc(
        GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0x00000000, 0x00000000);
    {
        const ScePspIMatrix4 dither = D_psp_0893CDE0;
        sceGuSetDither(&dither);
        sceGuEnable(GU_DITHER);
    }
    switch (pDisp->pixelFormat) {
    case GU_PSM_8888:
        sceGuTexMode(GU_PSM_8888, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
        break;
    case GU_PSM_5650:
        sceGuTexMode(GU_PSM_5650, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
        break;
    case GU_PSM_5551:
        sceGuTexMode(GU_PSM_5551, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
        break;
    case GU_PSM_4444:
        sceGuTexMode(GU_PSM_4444, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
        break;
    }
    sceGuTexImage(0, 0x200, 0x200, 0x200, buffer);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0x00000000);
    sceGuEnable(GU_BLEND);
    sceGuColor(0xFFFFFFFF);
    switch (D_psp_08C62A30) {
    case SCREEN_MODE_FULL:
        w = 418;
        h = 272;
        break;
    case SCREEN_MODE_PERFECT:
        w = 369;
        h = 240;
        break;
    }
    x = (GU_SCR_WIDTH - w) / 2;
    y = (GU_SCR_HEIGHT - h) / 2;
    sceGuSpriteMode(D_psp_08B1FBB4, D_psp_08B1FBB6, w, h);
    sceGuDrawSprite(x, y, 0, 0, 0, GU_NOFLIP, GU_NOROTATE);
    sceGuBlendFunc(
        GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0x00000000, 0x00000000);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
}

void func_psp_089144BC(void) {
    s32* dispList = D_psp_089B7140[0];

    sceGuStart(0, dispList, sizeof(D_psp_089B7140[0]));
    sceGuTexMode(GU_PSM_T8, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
    sceGuTexImage(0, 0x200, 0x200, 0x200, (u8*)(WALLPAPER_TEX_ADDR));
    sceGuClutMode(GU_PSM_5551, 0, 0xFF, 0);
    sceGuClutLoad(32, (u8*)(WALLPAPER_CLUT_ADDR));
    sceGuEnable(GU_TEXTURE_2D);
    sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0x00000000);
    sceGuEnable(GU_BLEND);
    sceGuColor(0xFFFFFFFF);
    sceGuSpriteMode(GU_SCR_WIDTH, GU_SCR_HEIGHT, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuDrawSprite(0, 0, 0, 0, 0, GU_NOFLIP, GU_NOROTATE);
    sceGuBlendFunc(
        GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0x00000000, 0x00000000);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    sceDisplayWaitVblankStartCB();
    EndFrame();
}

s32 dispbuf_create(
    t_displayBuffer* pDisp, s32 arg1, s32 dispNum, s32 pixelFormat) {
    s32 ret = 0;
    u8* ptr;

    pDisp->buf = NULL;
    pDisp->startSema = sceKernelCreateSema(D_psp_0893CE20, 0, 0, 1, NULL);
    pDisp->lockSema = sceKernelCreateSema(D_psp_0893CE2C, 0, 1, 1, NULL);
    pDisp->displayWaitSema = sceKernelCreateSema(D_psp_0893CE38, 0, 0, 1, NULL);
    pDisp->buf = (u8**)func_psp_0891275C(dispNum * 4);
    if (pDisp->buf == NULL) {
        ret = -1;
        goto error;
    }
    pDisp->pts = (u32*)func_psp_0891275C(dispNum * 4);
    if (pDisp->pts == NULL) {
        ret = -1;
        goto error;
    }
    pDisp->pixelFormat = pixelFormat;
    if (func_psp_08913F5C(pDisp) != 0) {
        ret = -1;
        goto error;
    }
    ptr = sceGeEdramGetAddr();
    ptr += 0xCC000;
    *pDisp->buf = ptr;
    pDisp->write = &D_psp_08B1FB94;
    pDisp->read = &D_psp_08B1FB98;
    pDisp->count = &D_psp_08B1FB9C;
    pDisp->size = &D_psp_08B1FBA0;
    pDisp->displayMode = &D_psp_08B1FBA4;
    ptr = ptr; // FAKE
    *pDisp->size = dispNum;
    goto term;
error:
    if (pDisp->buf != NULL) {
        func_psp_089127D8(pDisp->buf);
    }
    if (pDisp->pts != NULL) {
        func_psp_089127D8(pDisp->pts);
    }
term:
    return ret;
}

s32 dispbuf_reset(t_displayBuffer* pDisp) {
    u8* ptr;

    D_psp_08B1FBA8 = 0;
    D_psp_08B1FBAC = 0;

    *pDisp->write = 0;
    *pDisp->read = 0;
    *pDisp->count = 0;
    *pDisp->displayMode = 1;
    sceKernelPollSema(pDisp->startSema, 1);
    sceKernelPollSema(pDisp->displayWaitSema, 1);
    ptr = (u8*)sceGeEdramGetAddr();
    sceDisplaySetFrameBuf(ptr, GU_VRAM_WIDTH, PSP_DISPLAY_PIXEL_FORMAT_5551,
                          PSP_DISPLAY_SETBUF_NEXTFRAME);
    return 0;
}

s32 dispbuf_delete(t_displayBuffer* pDisp) {
    sceKernelDeleteSema(pDisp->startSema);
    sceKernelDeleteSema(pDisp->lockSema);
    sceKernelDeleteSema(pDisp->displayWaitSema);
    if (pDisp->buf != NULL) {
        func_psp_089127D8(pDisp->buf);
    }
    if (pDisp->pts != NULL) {
        func_psp_089127D8(pDisp->pts);
    }
    return 0;
}

s32 dispbuf_getDrawbuf(t_displayBuffer* pDisp, u8** buffer) {
    s32 ret;

    ret = dispbuf_getCapacity(pDisp);
    if (ret > 0) {
        *buffer = pDisp->buf[*pDisp->write];
    } else {
        *buffer = NULL;
    }
    return ret;
}

s32 dispbuf_dataSet(t_displayBuffer* pDisp) {
    sceKernelWaitSema(pDisp->lockSema, 1, NULL);
    (*pDisp->count)++;
    *pDisp->write = (*pDisp->write + 1) % *pDisp->size;
    sceKernelSignalSema(pDisp->lockSema, 1);
    return 0;
}

s32 dispbuf_getCapacity(t_displayBuffer* pDisp) {
    return *pDisp->size - *pDisp->count;
}

s32 dispbuf_getCurrentCount(t_displayBuffer* pDisp) { return *pDisp->count; }

s32 func_psp_08914B08(t_displayBuffer* pDisp) {
    s32 ret;

    if (dispbuf_getMode(pDisp) == 0xFF) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

s32 dispbuf_setPts(t_displayBuffer* pDisp, u32 pts) {
    s32 ret = 0;

    pDisp->pts[*pDisp->write] = pts;

    return ret;
}

s32 dispbuf_getPts(t_displayBuffer* pDisp, u32* pPts) {
    s32 ret = 0;

    *pPts = pDisp->pts[*pDisp->read];

    return ret;
}

s32 dispbuf_setMode(t_displayBuffer* pDisp, s32 mode) {
    *pDisp->displayMode = mode;
    return 0;
}

s32 dispbuf_getMode(t_displayBuffer* pDisp) { return *pDisp->displayMode; }

s32 dispbuf_func(s32 size, void* argp) {
    s32 currentMode;
    t_avSyncControl* pAvSync;
    t_displayBuffer* pDisp;

    pAvSync = (t_avSyncControl*)argp;
    pDisp = pAvSync->pDisp;
    sceKernelWaitSema(pDisp->startSema, 1, NULL);
    while (func_psp_08914B08(pDisp) == 0) {
        if (func_psp_089123B8() != 0) {
            currentMode = dispbuf_getMode(pDisp);
            if (currentMode != 4) {
                currentMode = avsync_Compare(pAvSync);
                dispbuf_setMode(pDisp, currentMode);
            }
            if (dispbuf_getCurrentCount(pDisp) > 0) {
                if (currentMode == 1 || currentMode == 2) {
                    dispbuf_show(pDisp);
                    sceKernelWaitSema(pDisp->lockSema, 1, NULL);
                    (*pDisp->count)--;
                    sceKernelSignalSema(pDisp->lockSema, 1);
                }
                sceKernelSignalSema(pDisp->displayWaitSema, 1);
                D_psp_08B1FBA8++;
            } else {
                D_psp_08B1FBAC++;
            }
        }
        sceDisplayWaitVblankStartCB();
    }
    while (dispbuf_getCurrentCount(pDisp) > 0) {
        dispbuf_show(pDisp);
        sceKernelWaitSema(pDisp->lockSema, 1, NULL);
        (*pDisp->count)--;
        sceKernelSignalSema(pDisp->lockSema, 1);
        sceDisplayWaitVblankStartCB();
        D_psp_08B1FBA8++;
    }
    sceDisplayWaitVblankStartCB();
    sceKernelExitThread(0);
    return 0;
}

void func_psp_08914E44(t_displayBuffer* pDisp) {
    sceKernelSignalSema(pDisp->startSema, 1);
}

s32 dispbuf_show(t_displayBuffer* pDisp) {
    u8* buffer;

    if (*pDisp->displayMode == 1) {
        u8* buffer = *pDisp->buf;
        draw_frame(pDisp, buffer);
        sceDisplayWaitVblankStartCB();
        EndFrame();
    }
    return 0;
}

void func_psp_08914EE0(s32 arg0, s32 arg1) {
    D_psp_08B1FBB4 = arg0;
    D_psp_08B1FBB6 = arg1;
}

s32 read_create(
    t_ringBuffer* pRing, SceMpegRingbuffer* pRB, StrFile* pStrFile) {
    pRing->pStrFile = pStrFile;
    pRing->pRingbuf = pRB;
    pRing->statusFlag = &D_psp_08B1FBBC;
    pRing->decodeSleepSema = sceKernelCreateSema(D_psp_0893CE4C, 0, 0, 1, NULL);
    pRing->unk14 = (u8*)func_psp_0891275C(0x10000);
    pRing->pStrFile; // FAKE
    return 0;
}

s32 read_reset(t_ringBuffer* pRing, s32 fileSize, s32 arg2) {
    *pRing->statusFlag = 0;
    pRing->dataLen = fileSize;
    pRing->unk1C.unk30 = arg2;
    D_psp_08B1FBC0 = 0;
    D_psp_08B1FBC4 = 0;
    return 0;
}

s32 read_delete(t_ringBuffer* pRing) {
    sceKernelDeleteSema(pRing->decodeSleepSema);
    if (pRing->unk14 != NULL) {
        func_psp_089127D8(pRing->unk14);
    }
    return 0;
}

s32 func_psp_0891504C(void) { return func_psp_08915070(NULL); }

s32 func_psp_08915070(t_ringBuffer* pRing) { return D_psp_08B1FBC4; }

s32 func_psp_08915088(t_ringBuffer* pRing) {
#undef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))

    unkStruct2* temp_s0;
    u32 temp_s3;

    temp_s0 = &pRing->unk1C;
    temp_s3 = read_getCapacity(pRing);
    if (D_psp_08B1FBC4 != 0) {
        return 1;
    }
    if (temp_s3 < MIN(0x3C0, pRing->dataLen / 0x800)) {
        return 1;
    }
    if (((pRing->dataLen / 0x800) - (temp_s0->unk28 / 0x800)) <
        MIN(0x3C0, pRing->dataLen / 0x800)) {
        if (temp_s3 < (pRing->dataLen - temp_s0->unk28)) {
            return 1;
        }
    }
    return 0;
}

s32 func_psp_08915228(t_ringBuffer* pRing) {
    *pRing->statusFlag = 0xFF;
    return 0;
}

s32 read_getCapacity(t_ringBuffer* pRing) {
    return sceMpegRingbufferAvailableSize(pRing->pRingbuf);
}

s32 func_psp_0891527C(t_ringBuffer* pRing) { return D_psp_08B1FBC0; }

void func_psp_08915294(
    unkStruct2* arg0, s32 arg1, u8* arg2, s32 arg3, u32 arg4, s32 arg5) {
    if (arg1 < 0) {
    }
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = arg5;
    arg0->unk10 = 0;
    arg0->unk24 = 0;
    arg0->unk14 = 0;
    arg0->unk1C = arg2;
    arg0->unk18 = arg3;
    arg0->unk20 = arg4;
    arg0->unk28 = 0;
}

u32 func_psp_08915324(unkStruct2* arg0) { return arg0->unk8; }

u32 func_psp_08915340(unkStruct2* arg0) { return arg0->unk4; }

void func_psp_0891535C(unkStruct2* arg0, s32 arg1) {
    arg0->unk4 += arg1;
    arg0->unk8 += arg1;
}

void func_psp_0891539C(unkStruct2* arg0, u32 arg1) {
    if (arg0->unk4 >= arg1) {
        arg0->unk4 -= arg1;
    } else {
        arg0->unk4 = 0;
    }
    arg0->unk10 += arg1;
    arg0->unk10 %= arg0->unk18;
    arg0->unk14 += arg1;
    arg0->unk28 += arg1;
}

u32 func_psp_08915454(unkStruct2* arg0) { return arg0->unk14; }

s32 ringbufferCallBack(void* pBuf, s32 iNum, void* CallbackData) {
    s32 iTypeSize = 0x800;

    volatile s32 iReadSize;
    StrFile* pStrFile;
    unkStruct2* temp_s0;

    pStrFile = (StrFile*)CallbackData;

    temp_s0 = pStrFile->unk8;
    if (iNum == 0) {
        return -1;
    }
    if (pStrFile->fd == -1) {
        return -2;
    }
    if (func_psp_089123B8() == 0) {
        return -3;
    }
    if (temp_s0->unk2C < func_psp_089125F8()) {
        return -3;
    }
    func_psp_08912608();
    if (func_psp_089123B8() == 0 || D_psp_08B1FBC8 != func_psp_089125F8()) {
        func_psp_08912640();
        return -3;
    }
    iReadSize = func_psp_0891689C(pStrFile, pBuf, iTypeSize * iNum);
    func_psp_08912640();
    if (iReadSize > 0) {
        func_psp_0891535C(temp_s0, iReadSize);
        temp_s0->unk24 = 0;
        temp_s0->unk0 += iReadSize;
        temp_s0->unk0 %= temp_s0->unk18;
        func_psp_0891539C(temp_s0, iReadSize * 0x800);
    } else {
        return -3;
    }
    if ((iReadSize % iTypeSize) != 0) {
        iReadSize % iTypeSize;
        return -3;
    }

    iReadSize = iReadSize / iTypeSize;
    return iReadSize;
}

s32 read_func(s32 args, void* argp) {
#undef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))

    s32 readSize[1];
    s32 capacitySize[1];
    s32 packNum[1];

    D_psp_08B1FBCC = (t_ringBuffer*)argp;
    D_psp_08B1FBD0 = D_psp_08B1FBCC->pStrFile;
    D_psp_08B1FBD4 = &D_psp_08B1FBCC->unk1C;
    D_psp_08B1FBCC->pStrFile->unk8 = &D_psp_08B1FBCC->unk1C;
    D_psp_08B1FBD0->unk4 = 0;
    D_psp_08B1FBD4->unk2C = func_psp_089125F8();
    func_psp_08915294(
        D_psp_08B1FBD4, D_psp_08B1FBD0->fd, D_psp_08B1FBCC->unk14, 0x10000,
        D_psp_08B1FBCC->dataLen, D_psp_08B1FBCC->unk1C.unk30);
    while (*D_psp_08B1FBCC->statusFlag != 0xFF) {
        readSize[0] = 0;
        sceKernelDelayThreadCB(16666);
        if (func_psp_089123B8() != 0) {
            capacitySize[0] =
                sceMpegRingbufferAvailableSize(D_psp_08B1FBCC->pRingbuf);
            if (*D_psp_08B1FBCC->statusFlag == 0) {
                if (D_psp_08B1FBD4->unk2C < func_psp_089125F8()) {
                    func_psp_08916830(D_psp_08B1FBD0);
                    D_psp_08B1FBD4->unk2C = func_psp_089125F8();
                    D_psp_08B1FBD0->unk4 = 1;
                }
                if (D_psp_08B1FBD0->unk4 == 1 || D_psp_08B1FBD0->fd == -1) {
                    func_psp_08912608();
                    if ((D_psp_08B1FBD8 = func_psp_08916724(
                             D_psp_08B1FBD0, &D_psp_08B1FBD0->unk16, 1)) >= 0) {
                        D_psp_08B1FBD0->unk4 = 2;
                    }
                    func_psp_08912640();
                    continue;
                }
                if (D_psp_08B1FBD0->unk4 == 2) {
                    func_psp_08912608();
                    if ((D_psp_08B1FBD8 = func_psp_089168E8(
                             D_psp_08B1FBD0, D_psp_08B1FBD4->unk8,
                             PSP_SEEK_SET)) >= 0) {
                        D_psp_08B1FBC8 = func_psp_089125F8();
                        D_psp_08B1FBD0->unk4 = 0;
                    }
                    func_psp_08912640();
                    continue;
                }
            }
            if ((*D_psp_08B1FBCC->statusFlag == 0 ||
                 *D_psp_08B1FBCC->statusFlag == 2) &&
                capacitySize[0] > 0 &&
                func_psp_08915340(D_psp_08B1FBD4) <
                    MIN(0x3C0000, D_psp_08B1FBCC->dataLen)) {
                packNum[0] = MIN(((D_psp_08B1FBCC->dataLen -
                                   func_psp_08915324(D_psp_08B1FBD4)) /
                                  0x800),
                                 capacitySize[0]);
                if (packNum[0] >= 0x20) {
                    packNum[0] = 0x20;
                }
                if (packNum[0] > 0) {
                    readSize[0] = sceMpegRingbufferPut(
                        D_psp_08B1FBCC->pRingbuf, packNum[0], capacitySize[0]);
                    if (readSize[0] < 0) {
                        D_psp_08B1FBCC->pRingbuf;
                        switch (readSize[0]) {
                        case -1:
                            break;
                        case -2:
                            D_psp_08B1FBD0->unk4 = 1;
                            break;
                        case -3:
                            func_psp_08916830(D_psp_08B1FBD0);
                            D_psp_08B1FBD0->unk4 = 1;
                            break;
                        }
                    }
                }
            } else {
                readSize[0] = 0;
            }
        } else {
            func_psp_08916830(D_psp_08B1FBD0);
            D_psp_08B1FBD0->unk4 = 1;
        }
        if (*D_psp_08B1FBCC->statusFlag == 0 &&
            func_psp_08915324(D_psp_08B1FBD4) >= D_psp_08B1FBCC->dataLen) {
            *D_psp_08B1FBCC->statusFlag = 2;
        }
        if (D_psp_08B1FBC4 == 0 && *D_psp_08B1FBCC->statusFlag == 2) {
            if (func_psp_08915454(D_psp_08B1FBD4) >=
                func_psp_08915324(D_psp_08B1FBD4)) {
                D_psp_08B1FBC4 = 1;
            }
        }
        if (D_psp_08B1FBC0 == 0) {
            if (func_psp_08915454(D_psp_08B1FBD4) >=
                MIN(0x3C0000, D_psp_08B1FBCC->dataLen)) {
                D_psp_08B1FBC0 = 1;
            }
        }
    }
    sceKernelExitThread(0);
    return 0;
}

s32 soundbuf_create(t_soundBuffer* pSound, s32 bufSize, s32 bufNum, s32 arg3) {
    s32 i;
    s32 ret;

    pSound->buf = NULL;
    pSound->pts = NULL;
    ret = 0;
    if (sceWaveAudioSetSample(1, 0x800) != 0) {
        ret = -1;
        goto error;
    }
    pSound->lockSema = sceKernelCreateSema(D_psp_0893CE64, 0, 1, 1, NULL);
    pSound->startSema = sceKernelCreateSema(D_psp_0893CE74, 0, 0, 1, NULL);
    pSound->buf = (u8**)func_psp_0891275C(bufNum * 4);
    if (pSound->buf == NULL) {
        ret = -1;
        goto error;
    }
    for (i = 0; i < bufNum; i++) {
        pSound->buf[i] = NULL;
    }
    for (i = 0; i < bufNum; i++) {
        pSound->buf[i] = (u8*)func_psp_0891275C(bufSize);
        pSound->buf[i] = (u8*)(((u32)pSound->buf[i] & 0x0FFFFFFF) | 0x40000000);
        if (pSound->buf[i] == NULL) {
            ret = -1;
            goto error;
        }
    }
    pSound->pts = (u32*)func_psp_0891275C(0x10);
    if (pSound->pts == NULL) {
        ret = -1;
        goto error;
    }
    pSound->unk4 = &D_psp_08B1FBDC;
    pSound->write = &D_psp_08B1FBE0;
    pSound->read = &D_psp_08B1FBE4;
    pSound->count = &D_psp_08B1FBE8;
    pSound->size = &D_psp_08B1FBEC;
    D_psp_0893CE60 = arg3;
    *pSound->size = bufNum;
    goto term;
error:
    if (pSound->buf != NULL) {
        for (i = 0; i < *pSound->size; i++) {
            pSound->buf[i] = NULL;
        }
        func_psp_089127D8(pSound->buf);
    }
    if (pSound->pts != NULL) {
        func_psp_089127D8(pSound->pts);
    }
term:
    return ret;
}

s32 soundbuf_reset(t_soundBuffer* pSound) {
    soundframeCount = 0;
    soundframeDelay = 0;
    sceKernelPollSema(pSound->startSema, 1);
    *pSound->unk4 = 0;
    *pSound->write = 0;
    *pSound->read = 0;
    *pSound->count = 0;
    return 0;
}

s32 soundbuf_delete(t_soundBuffer* pSound) {
    s32 i;

    sceKernelDeleteSema(pSound->lockSema);
    sceKernelDeleteSema(pSound->startSema);
    if (pSound->buf != NULL) {
        for (i = 0; i < *pSound->size; i++) {
            pSound->buf[i] = 0;
        }
        func_psp_089127D8(pSound->buf);
    }
    if (pSound->pts != NULL) {
        func_psp_089127D8(pSound->pts);
    }
    return 0;
}

s32 soundbuf_getDrawbuf(t_soundBuffer* pSound, u8** buffer) {
    s32 ret;

    ret = soundbuf_getCapacity(pSound);
    if (ret > 0) {
        *buffer = pSound->buf[*pSound->write];
    } else {
        *buffer = NULL;
    }
    return ret;
}

s32 soundbuf_setPts(t_soundBuffer* pSound, u32 pts) {
    s32 ret = 0;

    if (pts == -1) {
        pts = D_psp_08B1FBF8 + 0x1054;
    }
    D_psp_08B1FBF8 = pts;
    pSound->pts[*pSound->write] = pts;

    return ret;
}

s32 soundbuf_getPts(t_soundBuffer* pSound, u32* pPts) {
    s32 ret = 0;

    *pPts = pSound->pts[*pSound->read];

    return ret;
}

s32 soundbuf_setBuf(t_soundBuffer* pSound) {
    sceKernelWaitSema(pSound->lockSema, 1, NULL);
    (*pSound->count)++;
    sceKernelSignalSema(pSound->lockSema, 1);
    *pSound->write = (*pSound->write + 1) % *pSound->size;
    return 0;
}

s32 soundbuf_getCapacity(t_soundBuffer* pSound) {
    return *pSound->size - *pSound->count;
}

s32 soundbuf_getCurrentCount(t_soundBuffer* pSound) { return *pSound->count; }

s32 func_psp_089162C8(t_soundBuffer* pSound) {
    *pSound->unk4 = 1;
    return 0;
}

s32 func_psp_089162F0(t_soundBuffer* pSound) { return *pSound->unk4; }

void func_psp_08916310(t_soundBuffer* pSound) {
    sceKernelSignalSema(pSound->startSema, 1);
}

s32 soundbuf_func(s32 size, void* argp) {
    s32 var_s1 = 0;
    t_avSyncControl* pAvSync = (t_avSyncControl*)argp;
    t_soundBuffer* pSound = pAvSync->pSound;
    s32 var_s2 = 0;

    sceKernelWaitSema(pSound->startSema, 1, NULL);
    while (func_psp_089162F0(pSound) == 0) {
        if (func_psp_0891504C() != 0 && soundbuf_getCurrentCount(pSound) < 2) {
            D_psp_0893CE60 = 0;
            break;
        }
        if (func_psp_089123B8() != 0 && soundbuf_getCurrentCount(pSound) > 0) {
            var_s2 = soundbuf_output(pSound);
            if (var_s1 <= 0) {
                var_s1++;
            } else {
                sceKernelWaitSema(pSound->lockSema, 1, NULL);
                (*pSound->count)--;
                sceKernelSignalSema(pSound->lockSema, 1);
            }
            soundframeCount++;
        } else {
            soundframeDelay++;
            sceDisplayWaitVblankStartCB();
        }
    }

    while (soundbuf_getCurrentCount(pSound) > 0) {
        soundbuf_output(pSound);
        sceKernelWaitSema(pSound->lockSema, 1, NULL);
        (*pSound->count)--;
        sceKernelSignalSema(pSound->lockSema, 1);
        soundframeCount++;
    }
    sceWaveAudioWriteBlocking(1, D_psp_0893CE60, D_psp_0893CE60, 0);
    sceKernelExitThread(0);
    return 0;
}

static inline s32 soundbuf_swapbuf(t_soundBuffer* pSound, u8* buf) {
    s32 ret;

    sceWaveAudioSetSample(1, 0x800);
    sceWaveAudioWriteBlocking(1, D_psp_0893CE60, D_psp_0893CE60, 0);
    *pSound->read = (*pSound->read + 1) % *pSound->size;
    ret = sceWaveAudioWriteBlocking(1, D_psp_0893CE60, D_psp_0893CE60, buf);

    return ret;
}

s32 soundbuf_output(t_soundBuffer* pSound) {
    u8* currentBuf;

    currentBuf = pSound->buf[*pSound->read];

    return soundbuf_swapbuf(pSound, currentBuf);
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916630);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916724);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916830);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891689C);

SceOff func_psp_089168E8(StrFile* pStrFile, SceOff offset, s32 whence) {
    return sceIoLseek(pStrFile->fd, offset, whence);
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891692C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916984);
