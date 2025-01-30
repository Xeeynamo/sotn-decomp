// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

// Check if CD data is ready as long as its not related to reading the position
// of the laser. The status is cached in the `g_StreamDiskIsReady` global.
//
// returns:
//     0 - disk isn't ready for a request
//     1 - disk is ready
s32 StreamDiskIsReady() {
    u8 res;
    int ret;

    // if CD data isn't ready
    if (CdSync(1, &res) == CdlNoIntr) {
        return g_StreamDiskIsReady = 0;
    }

    ret = CdLastCom();
    if (ret >= CdlGetlocL && ret <= CdlGetlocP || !(res & CdlStatShellOpen)) {
        // clear the command
        CdControlF(1, NULL);
        return g_StreamDiskIsReady = 0;
    }

    return g_StreamDiskIsReady = 1;
}

u_long* StreamNext(DECENV* dec) {
    u_long* addr;
    StHEADER* sector;
    int* rewindSwitch;
    int count;

    count = 0x40000;
    while (StGetNext(&addr, &sector)) {
        if (--count == 0) {
            dec->isdone = 1;
            return 0;
        }
    }

    rewindSwitch = g_StreamRewindSwitch;
    if (sector->frameCount >= g_StreamEndFrame) {
        *rewindSwitch = 1;
    }

    g_StreamWidth = sector->width;
    g_StreamHeight = sector->height;
    dec->rect[0].w = dec->rect[1].w = count = g_StreamWidth * 3 / 2;
    dec->rect[0].h = dec->rect[1].h = g_StreamHeight;
    dec->slice.h = g_StreamHeight;
    return addr;
}

void StreamNextVlc(DECENV* dec) {
    const int WAIT_TIME = 4;
    int count = WAIT_TIME;
    u_long* next;

    while ((next = StreamNext(dec)) == 0) {
        if (--count == 0)
            return;
    }

    D_801BC340++;
    dec->vlcid = dec->vlcid ? 0 : 1;
    DecDCTvlc(next, dec->vlcbuf[dec->vlcid]);
    StFreeRing(next);
}

void func_801B9924(void) {
    volatile u32 pad[4]; // FAKE
    SetDispMask(0);
    func_801B18F4();
}

void func_801B994C(DECENV* dec) {
    volatile s32 retries = 0x40000;

    while (dec->isdone == 0) {
        if (--retries == 0) {
            dec->isdone = 1;
            dec->rectid = dec->rectid ? 0 : 1;
            dec->slice.x = (s16)(u16)dec->rect[dec->rectid].x;
            dec->slice.y = (s16)(u16)dec->rect[dec->rectid].y;
        }
    }
    dec->isdone = 0;
}

// access to g_StreamIsRGB24 (in the two places it is accessed) is always as an
// array but only the first element is ever read.
extern u32 g_StreamIsRGB24[];

void func_801B99E4(void) {
    RECT rect;

    if (g_StreamDiskIsReady & 1) {
        return;
    }

    if ((*g_StreamIsRGB24 == 1) && D_8003C908) {
        StCdInterrupt();
        D_8003C908 = false;
    }

    rect = g_StreamEnv.dec.slice;
    LoadImage(&g_StreamEnv.dec.slice,
              (u_long*)g_StreamEnv.dec.imgbuf[g_StreamEnv.dec.imgid]);
    g_StreamEnv.dec.imgid = g_StreamEnv.dec.imgid == 0;
    g_StreamEnv.dec.slice.x = g_StreamEnv.dec.slice.x + g_StreamEnv.dec.slice.w;
    if (g_StreamEnv.dec.slice.x <
        g_StreamEnv.dec.rect[g_StreamEnv.dec.rectid].x +
            g_StreamEnv.dec.rect[g_StreamEnv.dec.rectid].w) {
        DecDCTout(g_StreamEnv.dec.imgbuf[g_StreamEnv.dec.imgid],
                  (g_StreamEnv.dec.slice.w * g_StreamEnv.dec.slice.h) / 2);
        return;
    }
    g_StreamEnv.dec.rectid = g_StreamEnv.dec.rectid == 0;
    g_StreamEnv.dec.slice.x = g_StreamEnv.dec.rect[g_StreamEnv.dec.rectid].x;
    g_StreamEnv.dec.slice.y = g_StreamEnv.dec.rect[g_StreamEnv.dec.rectid].y;
    g_StreamEnv.dec.isdone = 1;
}

void func_801B9B7C(DECENV* env, s16 x0, s16 y0, s16 x1, s32 y1) {
    s16 bitsPerPixel;
    s16 width;

    env->vlcbuf[0] = (void*)0x8013C000;
    env->vlcbuf[1] = (void*)0x8015E000;
    env->imgbuf[0] = (u16*)D_801D104C;
    env->vlcid = 0;
    env->imgbuf[1] = (u16*)&D_801D104C[0xb40];
    env->imgid = 0;
    env->rectid = 0;
    env->isdone = 0;

    if (*g_StreamIsRGB24 == 1) {
        width = 480;
        bitsPerPixel = 24;
    } else {
        width = 320;
        bitsPerPixel = 16;
    }

    env->rect[0] = (RECT){
        .x = x0,
        .y = y0,
        .w = width,
        .h = 240,
    };
    env->rect[1] = (RECT){
        .x = x1,
        .y = y1,
        .w = width,
        .h = 240,
    };
    env->slice = (RECT){
        .x = x0,
        .y = y0,
        .w = bitsPerPixel,
        .h = 240,
    };
}

void func_801B9C18(s32 unused, void (*callback)()) {
    const int START_FRAME = 1;

    s32* s0 = g_StreamRewindSwitch;
    DecDCTReset(0);
    *s0 = 0;
    DecDCToutCallback(callback);
    StSetRing((s32)(s0 + 2), 0x28);
    StSetStream(*g_StreamIsRGB24, START_FRAME, -1, NULL, NULL);
}

INCLUDE_ASM("st/sel/nonmatchings/stream", func_801B9C80);
