// SPDX-License-Identifier: AGPL-3.0-or-later

// This function is messy, maybe there's a better way.
static void CollectHeart(u16 heartIdx) {
#if defined VERSION_BETA || STAGE == STAGE_ST0
    s8 heartPrizes[2] = {0x01, 0x05};
    s8 mad_unknown[2] = {0x01, 0x02};
#else
#define heartPrizes c_HeartPrizes
#endif

    g_api.PlaySfx(SFX_HEART_PICKUP);
    g_Status.hearts += heartPrizes[heartIdx];

    if (g_Status.hearts > g_Status.heartsMax) {
        g_Status.hearts = g_Status.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}
