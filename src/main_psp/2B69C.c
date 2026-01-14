// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspthreadman.h>
#include <pspiofilemgr.h>
#include <pspatrac3.h>
#include <pspkerror.h>

extern char D_psp_08962F50[];
extern char D_psp_08962FCC[];
extern char D_psp_08962E90[];
extern u32 D_psp_08DADCB4;

typedef struct {
    SceUID fd;
    char assignName[10];
} StrFile;

typedef struct {
    s32 atracID;       // ATRAC playback ID
    StrFile strFile;   // File structure
    SceUID playFlag;   // Event flag indicating status Used for cueing, playing,
                       // and ending
    s32 outputChannel; // Channel when outputting to libwave
    s32 iEndSample;
} SceAtracArg;

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_08929FA8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A018);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A0C4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A0F0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A1EC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A21C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A28C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A2D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A3D4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A414);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A620);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A70C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A76C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A7E0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A8C0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A8FC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A97C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A998);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", SsSetSerialVol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", func_psp_0892A9E0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", strFileOpen);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", strFileClose);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", strFileRead);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", strFileLseek);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", play_bgm);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", init_atrac3plus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", play_atrac3plus);

void createPlayModeFlag(const char* name) {
    sceKernelCreateEventFlag(name, PSP_EVENT_WAITMULTIPLE, 0x00000000, NULL);
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

    if ((status = sceKernelPollEventFlag(playFlag, uiPlayMode, 1, NULL)) ==
        SCE_KERNEL_ERROR_OK) {
        ret = 1;
    } else {
        if (status < 0 && status != SCE_KERNEL_ERROR_EVF_COND) {
            printf("status = 0x%x(in sceKernelPollEventFlag)\n", status);
        }
    }
    return ret;
}

void waitPlayMode(SceUID playFlag, u32 uiPlayMode) {
    sceKernelWaitEventFlag(playFlag, uiPlayMode, PSP_EVENT_WAITOR, NULL, NULL);
}

void clearPlayMode(SceUID playFlag, u32 uiPlayMode) {
    s32 status;

    status = sceKernelClearEventFlag(playFlag, ~uiPlayMode);
    if (status < 0) {
        printf("status = 0x%x(in sceKernelClearEventFlag)\n", status);
    }
}

void release_arg(SceAtracArg* pPlayArg) {
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

void at3plus_addData(s32 atracId, StrFile* pstrFile, s32* arg2) {
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
        if (strcmp(pstrFile->assignName, D_psp_08962E90) == 0) {
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

void reset_position(SceAtracArg* pPlayArg) {
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
            printf(D_psp_08962FCC, status);
            goto ERROR_OCCURED;
        }
        firstBufRead =
            strFileRead(&pPlayArg->strFile, bufferInfo.pucWritePositionFirstBuf,
                        bufferInfo.uiWritableByteFirstBuf);
        if (firstBufRead < 0) {
            status = firstBufRead;
            printf(D_psp_08962F50, status);
            goto ERROR_OCCURED;
        }
    }
    if (bufferInfo.uiMinWriteByteSecondBuf > 0) {
        status = strFileLseek(
            &pPlayArg->strFile, (SceOff)bufferInfo.uiReadPositionSecondBuf,
            PSP_SEEK_SET);
        if (status < 0) {
            printf(D_psp_08962FCC, status);
            goto ERROR_OCCURED;
        }
        secondBufRead = strFileRead(
            &pPlayArg->strFile, bufferInfo.pucWritePositionSecondBuf,
            bufferInfo.uiWritableByteSecondBuf);
        if (secondBufRead < 0) {
            printf(D_psp_08962F50, secondBufRead);
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

void fadeoutOperation(
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

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", DvdUmdIoInit);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", DvdUmdIoTerm);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", DvdUmdRetryOpenCB);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2B69C", DvdUmdRetryRead);
