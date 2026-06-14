// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mpeg_private.h"

s32 soundbuf_vol = 0x8000;

static u32 soundLatestPts;
static s32 soundframeDelay;
static s32 soundframeCount;

s32 soundbuf_create(t_soundBuffer* pSound, s32 bufSize, s32 bufNum, s32 vol) {
    s32 i;
    s32 ret;

    pSound->buf = NULL;
    pSound->pts = NULL;
    ret = 0;
    if (sceWaveAudioSetSample(1, 0x800) != 0) {
        ret = -1;
        goto error;
    }
    pSound->lockSema = sceKernelCreateSema("sound_lock_sema", 0, 1, 1, NULL);
    pSound->startSema = sceKernelCreateSema("sound_start_sema", 0, 0, 1, NULL);
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
    {
        static s32 unk4;
        static s32 write;
        static s32 read;
        static s32 count;
        static s32 size;

        pSound->unk4 = &unk4;
        pSound->write = &write;
        pSound->read = &read;
        pSound->count = &count;
        pSound->size = &size;
    }

    soundbuf_vol = vol;
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
        pts = soundLatestPts + 0x1054;
    }
    soundLatestPts = pts;
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

void soundbuf_startAudio(t_soundBuffer* pSound) {
    sceKernelSignalSema(pSound->startSema, 1);
}

s32 soundbuf_func(s32 size, void* argp) {
    s32 var_s1 = 0;
    t_avSyncControl* pAvSync = (t_avSyncControl*)argp;
    t_soundBuffer* pSound = pAvSync->pSound;
    s32 var_s2 = 0;

    sceKernelWaitSema(pSound->startSema, 1, NULL);
    while (func_psp_089162F0(pSound) == 0) {
        if (func_psp_0891504C() && soundbuf_getCurrentCount(pSound) < 2) {
            soundbuf_vol = 0;
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
    sceWaveAudioWriteBlocking(1, soundbuf_vol, soundbuf_vol, 0);
    sceKernelExitThread(0);
    return 0;
}

static inline s32 soundbuf_swapbuf(t_soundBuffer* pSound, u8* buf) {
    s32 ret;

    sceWaveAudioSetSample(1, 0x800);
    sceWaveAudioWriteBlocking(1, soundbuf_vol, soundbuf_vol, 0);
    *pSound->read = (*pSound->read + 1) % *pSound->size;
    ret = sceWaveAudioWriteBlocking(1, soundbuf_vol, soundbuf_vol, buf);

    return ret;
}

s32 soundbuf_output(t_soundBuffer* pSound) {
    u8* currentBuf;

    currentBuf = pSound->buf[*pSound->read];

    return soundbuf_swapbuf(pSound, currentBuf);
}
