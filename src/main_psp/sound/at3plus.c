// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include "sound_private.h"

#define BYTEALIGN (64)
#define MAX_SAMPLE (2048)
#define AUDIO_OUTPUT_SAMPLE MAX_SAMPLE
#define BUFFER_NUM (3)
#define WRITEBUF_SIZE (BUFFER_NUM * (MAX_SAMPLE))

#define SCE_WAVE_AUDIO_SMPL_MIN (64)
#define SCE_WAVE_AUDIO_VOL_MAX (0x8000)
#define FADEOUT_RATIO (SCE_WAVE_AUDIO_VOL_MAX / 128)

extern u32 D_psp_08DADCB4;

void setPlayMode(SceUID playFlag, u32 uiPlayMode);
static void play_atrac3plus(SceAtracArg* pPlayArg);
static void clearPlayMode(SceUID playFlag, u32 uiPlayMode);
static void waitPlayMode(SceUID playFlag, u32 uiPlayMode);
static void release_arg(SceAtracArg* pPlayArg);
static void at3plus_addData(s32 atracId, StrFile* pstrFile, s32* arg2);
static void reset_position(SceAtracArg* pPlayArg);
static void fadeoutOperation(
    s16* pusValue, s32 iFadeoutBorderSample, s32 iMuteBorderSample);

static s32 strFileOpen(StrFile* file, const char* filename, s32 flags) {
    if (memcmp(filename, "host0:", 6) == 0) {
        strcpy(file->assignName, "host0:");
        file->fd = sceIoOpen(filename, flags, 0);
    } else if (memcmp(filename, "ms0:", 4) == 0) {
        strcpy(file->assignName, "ms0:");
        file->fd = sceIoOpen(filename, flags, 0);
    } else if (memcmp(filename, PSP_UMD_ALIAS_NAME, 6) == 0) {
        strcpy(file->assignName, PSP_UMD_ALIAS_NAME);
        file->fd = DvdUmdRetryOpenCB(filename, flags, 0);
    } else {
        printf("fatal error : not supported device\n");
        return -1;
    }
    if (file->fd < 0) {
        printf("fatal error : file->fd = 0x%x\n", file->fd);
        return -1;
    }
    return 0;
}

static s32 strFileClose(StrFile* file) {
    SceInt64 result;
    s32 ret;

    if (file->fd >= 0) {
        ret = sceIoClose(file->fd);
        if (ret == SCE_KERNEL_ERROR_ASYNC_BUSY) {
            sceIoWaitAsync(file->fd, &result);
            ret = sceIoClose(file->fd);
        }
    } else {
        return -1;
    }
    return ret;
}

static s32 strFileRead(StrFile* file, void* buff, SceSize size) {
    s32 readsize;

    if (strcmp(file->assignName, PSP_UMD_ALIAS_NAME) == 0) {
        readsize = DvdUmdRetryRead(file->fd, buff, size);
    } else {
        readsize = sceIoRead(file->fd, buff, size);
    }
    return readsize;
}

static SceOff strFileLseek(StrFile* file, SceOff offset, s32 whence) {
    return sceIoLseek(file->fd, offset, whence);
}

s32 play_bgm(u32 args, void* argp) {
    s32 status;
    SceBGMArg* pBGMArg;
    SceAtracArg atracArg;

    pBGMArg = (SceBGMArg*)argp;

    sceKernelClearEventFlag(pBGMArg->playFlag, 0);
    setPlayMode(pBGMArg->playFlag, BGM_INIT_START);
    status = init_atrac3plus(pBGMArg, &atracArg);
    if (status < 0) {
        printf("status = 0x%x (in init_atrac3plus)\n", status);
        setPlayMode(pBGMArg->playFlag, BGM_PLAY_FINISH);
        goto TERM;
    }
    setPlayMode(pBGMArg->playFlag, BGM_INIT_END);
    waitPlayMode(pBGMArg->playFlag, BGM_PLAY_START | BGM_PLAY_FINISH);
    play_atrac3plus(&atracArg);

TERM:
    setPlayMode(pBGMArg->playFlag, BGM_PLAY_FINISH);
    sceKernelExitThread(0);
    return 0;
}

static s32 init_atrac3plus(SceBGMArg* pBGMArg, SceAtracArg* pPlayArg) {
    s32 filesize;
    s32 status;
    s32 iLoopStartSample, iLoopEndSample;
    u32 uiSecondBufferPosition;
    u32 uiDataByte;

    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 uiBitrate;
    u32 uiOutputCh;

    char* filename = "disc0:/PSP_GAME/USRDIR/res/ps/sound/XA/011a.at3";

    pPlayArg->strFile.fd = -1;
    pPlayArg->atracID = -1;
    pPlayArg->playFlag = pBGMArg->playFlag;
    pPlayArg->outputChannel = pBGMArg->iOutputChannel;
    pPlayArg->iVol = 0x8000;
    filesize = pBGMArg->fileSize;
    pPlayArg->fileSize = filesize;
    if (pPlayArg->fileSize == 0) {
        status = strFileOpen(&pPlayArg->strFile, pBGMArg->filename, 1);
        if (status < 0) {
            printf("status = 0x%x(in strFileOpen)\n", status);
            do {
                status = strFileOpen(&pPlayArg->strFile, filename, 1);
                sceKernelDelayThreadCB(100000);
            } while (status < 0);
        }
        filesize = strFileRead(&pPlayArg->strFile, pBGMArg->pucFirstBuf,
                               (u32)pBGMArg->iFirstBufSize >> 1);
        if (filesize < 0) {
            status = filesize;
            printf("status = 0x%x(in strFileRead)\n", status);
            goto RELEASE_ARG;
        }
    }
    pPlayArg->atracID = sceAtracSetDataAndGetID(pBGMArg->pucFirstBuf, filesize);
    if (pPlayArg->atracID < 0) {
        status = pPlayArg->atracID;
        printf("status = 0x%x(in sceAtracSetDataAndGetID)\n", status);
        goto RELEASE_ARG;
    }
    status = sceAtracGetSecondBufferInfo(
        pPlayArg->atracID, &uiSecondBufferPosition, &uiDataByte);
    if (status != PSP_ATRAC_ERROR_NONEED_SECOND_BUFFER) {
        s32 iReadSize;

        if (status < 0) {
            printf("status = 0x%x(in sceAtracGetSecondBufferInfo)\n", status);
            goto RELEASE_ARG;
        }
        status =
            strFileLseek(&pPlayArg->strFile, (s64)uiSecondBufferPosition, 0);
        if (status < 0) {
            printf("status = 0x%x(in strFileLseek)\n", status);
            goto RELEASE_ARG;
        }
        iReadSize = strFileRead(
            &pPlayArg->strFile, pBGMArg->pucSecondBuf, pBGMArg->iSecondBufSize);
        if (iReadSize < 0) {
            status = iReadSize;
            printf("status = 0x%x(in strFileRead)\n", iReadSize);
            goto RELEASE_ARG;
        }
        status = sceAtracSetSecondBuffer(
            pPlayArg->atracID, pBGMArg->pucSecondBuf, iReadSize);
        if (status < 0) {
            printf("status = 0x%x(in sceAtracSetSecondBuffer)\n", status);
            goto RELEASE_ARG;
        }
    }
    status = sceAtracGetSoundSample(pPlayArg->atracID, &pPlayArg->iEndSample,
                                    &iLoopStartSample, &iLoopEndSample);
    if (status < 0) {
        printf("status = 0x%x(in sceAtracGetSoundSample)\n", status);
        goto RELEASE_ARG;
    }
    if (pBGMArg->loop != 0) {
        status = sceAtracSetLoopNum(pPlayArg->atracID, -1);
        if (status < 0) {
            printf("status = 0x%x(in sceAtracSetLoopNum)  loop=%d\n", status,
                   pBGMArg->loop);
        }
    }
    sceAtracGetSoundSample(pPlayArg->atracID, &sp3C, &sp38, &sp34);
    sceAtracGetBitrate(pPlayArg->atracID, &uiBitrate);
    sceAtracGetOutputChannel(pPlayArg->atracID, &uiOutputCh);
    return 0;
RELEASE_ARG:
    release_arg(pPlayArg);
    return status;
}

static void play_atrac3plus(SceAtracArg* pPlayArg) {
    s32 status;
    u32 finishflag, uiWritePosition = 0, uiPlayPosition = 0;
    s32 iRemainFrame;
    s32 iReadThreshold;
    s32 iVol;
    s32* outputBuf;
    s32 aiOutputBuf[WRITEBUF_SIZE + (AUDIO_OUTPUT_SAMPLE - 1) + BYTEALIGN / 4 -
                    1];

    outputBuf =
        (s32*)((u32)(aiOutputBuf + BYTEALIGN / 4 - 1) & ~(BYTEALIGN - 1));
    status = sceAtracGetRemainFrame(pPlayArg->atracID, &iRemainFrame);
    if (status < 0) {
        printf("sceAtracGetRemainFrame err 0x%x\n", status);
    }
    iReadThreshold = iRemainFrame / 2;
    if (iReadThreshold < 1) {
        iReadThreshold = 1;
    }
    pPlayArg->unk28 = 0;
    do {
        u32 sample;
        s32 var_s6 = true;
        s32 var_s0 = false;
        if (checkPlayMode(pPlayArg->playFlag, BGM_UNK_20)) {
            clearPlayMode(pPlayArg->playFlag, BGM_UNK_20);
            waitPlayMode(pPlayArg->playFlag, BGM_UNK_40);
            clearPlayMode(pPlayArg->playFlag, BGM_UNK_40);
            sceKernelDelayThreadCB(83330);
            var_s0 = true;
            if (iRemainFrame != PSP_ATRAC_ALLDATA_IS_ON_MEMORY &&
                iRemainFrame != PSP_ATRAC_NONLOOP_STREAM_DATA_IS_ON_MEMORY) {
                at3plus_addData(
                    pPlayArg->atracID, &pPlayArg->strFile, &pPlayArg->unk28);
            }
            if (checkPlayMode(pPlayArg->playFlag, BGM_PLAY_FINISH)) {
                break;
            }
        }
        if (!var_s0) {
            status = sceAtracDecodeData(
                pPlayArg->atracID, (s16*)&outputBuf[uiWritePosition], &sample,
                &finishflag, &iRemainFrame);
            if (status < 0 && status != PSP_ATRAC_ERROR_NODATA_IN_BUFFER) {
                s32 innerInfo;
                sceAtracGetInternalErrorInfo(pPlayArg->atracID, &innerInfo);
                printf("innerInfo 0x%x\n", innerInfo);
                printf(
                    "sceAtracDecodeData err 0x%x (%08x)\n", status, innerInfo);
                sceKernelDelayThreadCB(100000);
                break;
            }
            uiWritePosition += sample;
        }
        if (uiWritePosition - uiPlayPosition >= AUDIO_OUTPUT_SAMPLE) {
            s32 output_samples = (uiWritePosition - uiPlayPosition) &
                                 ~(SCE_WAVE_AUDIO_SMPL_MIN - 1);

            if (checkPlayMode(pPlayArg->playFlag, BGM_PLAY_FINISH)) {
                setPlayMode(pPlayArg->playFlag, BGM_UNK_80);
                if (pPlayArg->outputChannel == 2 ||
                    checkPlayMode(pPlayArg->playFlag, BGM_UNK_100)) {
                    break;
                }
                iVol = pPlayArg->outputChannel == 1 ? func_psp_0892A9E0()
                                                    : pPlayArg->iVol;
                iVol -= FADEOUT_RATIO * output_samples >> 10;
                if (iVol < 0) {
                    break;
                }
                pPlayArg->iVol = iVol;
                if (pPlayArg->outputChannel == 1) {
                    func_psp_0892A9D4(iVol);
                }
            }
            if (checkPlayMode(pPlayArg->playFlag, BGM_RESET_POSITION)) {
                fadeoutOperation(
                    (s16*)&outputBuf[uiPlayPosition], output_samples,
                    uiWritePosition - uiPlayPosition);
            }
            var_s6 = false;
            sceWaveAudioSetSample(pPlayArg->outputChannel, output_samples);
            sceWaveAudioWriteBlocking(
                pPlayArg->outputChannel, pPlayArg->iVol, pPlayArg->iVol,
                &outputBuf[uiPlayPosition]);
            uiPlayPosition += output_samples;
            if (checkPlayMode(pPlayArg->playFlag, BGM_RESET_POSITION)) {
                reset_position(pPlayArg);
                clearPlayMode(pPlayArg->playFlag, BGM_RESET_POSITION);
            }
        }
        if (uiWritePosition >= WRITEBUF_SIZE) {
            uiWritePosition -= uiPlayPosition;
            memcpy(outputBuf, &outputBuf[uiPlayPosition],
                   sizeof(s32) * uiWritePosition);
            uiPlayPosition = 0;
        }
        if (iRemainFrame <= iReadThreshold &&
            iRemainFrame != PSP_ATRAC_ALLDATA_IS_ON_MEMORY &&
            iRemainFrame != PSP_ATRAC_NONLOOP_STREAM_DATA_IS_ON_MEMORY) {
            at3plus_addData(
                pPlayArg->atracID, &pPlayArg->strFile, &pPlayArg->unk28);
        }
        if (var_s6) {
            sceKernelDelayThreadCB(1000);
        }
    } while (!finishflag);

    sceWaveAudioWriteBlocking(pPlayArg->outputChannel, 0, 0, NULL);
    release_arg(pPlayArg);
}

s32 createPlayModeFlag(const char* name) {
    return sceKernelCreateEventFlag(
        name, PSP_EVENT_WAITMULTIPLE, 0x00000000, NULL);
}

void setPlayMode(SceUID playFlag, u32 uiPlayMode) {
    s32 status;

    status = sceKernelSetEventFlag(playFlag, uiPlayMode);
    if (status < 0) {
        printf("status = 0x%x(in sceKernelSetEventFlag)\n", status);
    }
}

s32 checkPlayMode(SceUID playFlag, u32 uiPlayMode) {
    s32 status;
    s32 ret = 0;

    if ((status = sceKernelPollEventFlag(playFlag, uiPlayMode, PSP_EVENT_WAITOR,
                                         NULL)) == SCE_KERNEL_ERROR_OK) {
        ret = 1;
    } else {
        if (status < 0 && status != SCE_KERNEL_ERROR_EVF_COND) {
            printf("status = 0x%x(in sceKernelPollEventFlag)\n", status);
        }
    }
    return ret;
}

static void waitPlayMode(SceUID playFlag, u32 uiPlayMode) {
    sceKernelWaitEventFlag(playFlag, uiPlayMode, PSP_EVENT_WAITOR, NULL, NULL);
}

static void clearPlayMode(SceUID playFlag, u32 uiPlayMode) {
    s32 status;

    status = sceKernelClearEventFlag(playFlag, ~uiPlayMode);
    if (status < 0) {
        printf("status = 0x%x(in sceKernelClearEventFlag)\n", status);
    }
}

static void release_arg(SceAtracArg* pPlayArg) {
    s32 status;

    if (pPlayArg->atracID >= 0) {
        status = sceAtracReleaseAtracID(pPlayArg->atracID);
        if (status < 0) {
            printf("status = 0x%x(in sceAtracReleaseAtracID)\n", status);
        }
    }
    if (pPlayArg->strFile.fd >= 0) {
        status = strFileClose(&pPlayArg->strFile);
        if (status < 0) {
            printf("status = 0x%x(in strFileClose)\n", status);
        }
    }
}

static void at3plus_addData(s32 atracId, StrFile* pstrFile, s32* arg2) {
    u8* pucWritePointer;
    u32 uiWritableByte, uiReadPosition;
    s32 status, iAddByte;

    if (*arg2 == 0) {
        status = sceAtracGetStreamDataInfo(
            atracId, &pucWritePointer, &uiWritableByte, &uiReadPosition);
        if (status < 0) {
            printf("sceAtracGetStreamDataInfo = 0x%x\n", status);
            goto READ_FAIL;
        }
        if (uiWritableByte > 0x2000) {
            uiWritableByte = 0x2000;
        }
        status = strFileLseek(pstrFile, (SceOff)uiReadPosition, PSP_SEEK_SET);
        if (status < 0) {
            printf("strFileLseek Error = 0x%x\n", status);
            goto READ_FAIL;
        }
        D_psp_08DADCB4 = uiWritableByte;
        if (strcmp(pstrFile->assignName, PSP_UMD_ALIAS_NAME) == 0) {
            sceIoReadAsync(pstrFile->fd, pucWritePointer, uiWritableByte);
            *arg2 = 1;
        } else {
            iAddByte = sceIoRead(pstrFile->fd, pucWritePointer, uiWritableByte);
        }
        if (iAddByte <= 0) {
            printf("strFileReadNoRetry Error = 0x%x\n",
                   iAddByte); // TODO: inlined function ?
            goto READ_FAIL;
        }
    }
    if (*arg2 == 1 && sceIoPollAsync(pstrFile->fd, (SceInt64*)&iAddByte) == 0) {
        iAddByte = D_psp_08DADCB4;
        *arg2 = -1;
    }
    if (*arg2 < 0) {
        status = sceAtracAddStreamData(atracId, iAddByte);
        *arg2 = 0;
        if (status < 0) {
            printf("sceAtracAddStreamData = 0x%x\n", status);
        }
    }
READ_FAIL:
    return;
}

static void reset_position(SceAtracArg* pPlayArg) {
    PspBufferInfo bufferInfo;
    s32 status;
    s32 firstBufRead = 0, secondBufRead = 0;

    status =
        sceAtracGetBufferInfoForResetting(pPlayArg->atracID, 0, &bufferInfo);
    if (status < 0) {
        printf("status = 0x%x(in sceAtracGetBufferInfoForResetting)\n", status);
        goto ERROR_OCCURED;
    }
    if (bufferInfo.uiMinWriteByteFirstBuf > 0) {
        status = strFileLseek(
            &pPlayArg->strFile, (SceOff)bufferInfo.uiReadPositionFirstBuf,
            PSP_SEEK_SET);
        if (status < 0) {
            printf("status = 0x%x(in strFileLseek)\n", status);
            goto ERROR_OCCURED;
        }
        firstBufRead =
            strFileRead(&pPlayArg->strFile, bufferInfo.pucWritePositionFirstBuf,
                        bufferInfo.uiWritableByteFirstBuf);
        if (firstBufRead < 0) {
            status = firstBufRead;
            printf("status = 0x%x(in strFileRead)\n", status);
            goto ERROR_OCCURED;
        }
    }
    if (bufferInfo.uiMinWriteByteSecondBuf > 0) {
        status = strFileLseek(
            &pPlayArg->strFile, (SceOff)bufferInfo.uiReadPositionSecondBuf,
            PSP_SEEK_SET);
        if (status < 0) {
            printf("status = 0x%x(in strFileLseek)\n", status);
            goto ERROR_OCCURED;
        }
        secondBufRead = strFileRead(
            &pPlayArg->strFile, bufferInfo.pucWritePositionSecondBuf,
            bufferInfo.uiWritableByteSecondBuf);
        if (secondBufRead < 0) {
            printf("status = 0x%x(in strFileRead)\n", secondBufRead);
            goto ERROR_OCCURED;
        }
    }
    status = sceAtracResetPlayPosition(
        pPlayArg->atracID, 0, firstBufRead, secondBufRead);
    if (status < 0) {
        printf("status = 0x%x (in sceAtracResetPlayPosition)\n", status);
    }
    status = sceAtracSetLoopNum(pPlayArg->atracID, -1);
    if (status < 0) {
        printf("status = 0x%x(in sceAtracSetLoopNum)\n", status);
    }
ERROR_OCCURED:
    return;
}

static void fadeoutOperation(
    s16* pusValue, s32 iFadeoutBorderSample, s32 iMuteBorderSample) {
    float fadeoutratio = 1.0f / iFadeoutBorderSample;
    float fadeout;
    s32 i;

    for (i = 0; i < iFadeoutBorderSample; i++) {
        fadeout = ((iFadeoutBorderSample - 1) - i) * fadeoutratio;
        pusValue[2 * i] = pusValue[2 * i] * fadeout;
        pusValue[2 * i + 1] = pusValue[2 * i + 1] * fadeout;
    }
    for (; i < iMuteBorderSample; i++) {
        pusValue[2 * i] = 0;
        pusValue[2 * i + 1] = 0;
    }
}
