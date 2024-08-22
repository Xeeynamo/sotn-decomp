// SPDX-License-Identifier: AGPL-3.0-only
extern u32 c_GoldPrizes[];
extern const char* g_goldCollectTexts[];

#include "sfx.h"

void CollectGold(u16 goldSize) {
    g_api.PlaySfx(SFX_GOLD_PICKUP);
    goldSize -= 2;
    g_Status.gold += c_GoldPrizes[goldSize];
    if (g_Status.gold > MAX_GOLD) {
        g_Status.gold = MAX_GOLD;
    }
#if STAGE != STAGE_ST0
    if (g_unkGraphicsStruct.BottomCornerTextTimer) {
        g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
        g_unkGraphicsStruct.BottomCornerTextTimer = 0;
    }

    BottomCornerText(g_goldCollectTexts[goldSize], 1);
    DestroyEntity(g_CurrentEntity);
#endif
}
