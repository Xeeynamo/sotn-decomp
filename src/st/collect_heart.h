#include "sfx.h"

void CollectHeart(u16 arg0) {
    s32* hearts;

    g_api.PlaySfx(SFX_ITEM_PICKUP);
    g_Status.hearts += c_HeartPrizes[arg0];

    if (g_Status.hearts > g_Status.heartsMax) {
        g_Status.hearts = g_Status.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}
