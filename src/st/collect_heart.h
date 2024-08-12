#include "sfx.h"

void CollectHeart(u16 arg0) {
#ifdef VERSION_BETA
    s8 heartPrizes[2];
    s8 mad_unknown[2];

    __builtin_memcpy(heartPrizes, c_HeartPrizes[0], 2);
    __builtin_memcpy(mad_unknown, c_HeartPrizes[2], 2);
#else
    s8* heartPrizes = c_HeartPrizes;
#endif

    g_api.PlaySfx(SFX_HEART_PICKUP);
    g_Status.hearts += heartPrizes[arg0];

    if (g_Status.hearts > g_Status.heartsMax) {
        g_Status.hearts = g_Status.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}
