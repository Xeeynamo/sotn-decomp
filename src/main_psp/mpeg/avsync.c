// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mpeg_private.h"

static s32 videoLatestPts;
static const s32 videoIntervalSize = 0xBBC;

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
    videoLatestPts = 0;
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
        pts = videoLatestPts + videoIntervalSize;
    }
    videoLatestPts = pts;
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
        ret = DISPLAY_MODE_NORMAL;
        goto term;
    }
    if (soundbuf_getCurrentCount(pAvSync->pSound) == 0 ||
        dispbuf_getCurrentCount(pAvSync->pDisp) == 0) {
        ret = DISPLAY_MODE_NORMAL;
        goto term;
    }
    soundbuf_getPts(pAvSync->pSound, &soundPts);
    dispbuf_getPts(pAvSync->pDisp, &videoPts);
    ptsDiff = soundPts - videoPts;
    if (ptsDiff >= -videoIntervalSize * 2 && ptsDiff <= videoIntervalSize * 2) {
        ret = DISPLAY_MODE_NORMAL;
    } else if (ptsDiff > videoIntervalSize * 2) {
        ret = DISPLAY_MODE_SKIP;
    } else {
        ret = DISPLAY_MODE_WAIT;
    }
term:
    return ret;
}
