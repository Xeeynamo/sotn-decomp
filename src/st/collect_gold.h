extern u32 c_GoldPrizes[];
extern u8* g_goldCollectTexts[];

void CollectGold(u16 goldSize) {
    u16 goldSizeIndex;
#ifdef VERSION_BETA
    g_api.PlaySfx(0x69D); // MAD seems to use its own sfx id set.
#else
    g_api.PlaySfx(NA_SE_PL_COLLECT_GOLD);
#endif
    goldSizeIndex = goldSize - 2;
    g_Status.gold += c_GoldPrizes[goldSizeIndex];
    if (g_Status.gold > MAX_GOLD) {
        g_Status.gold = MAX_GOLD;
    }
#if STAGE != STAGE_STAGE_ST0
    if (g_unkGraphicsStruct.BottomCornerTextTimer) {
        g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
        g_unkGraphicsStruct.BottomCornerTextTimer = 0;
    }

    BottomCornerText(g_goldCollectTexts[goldSizeIndex], 1);
    DestroyEntity(g_CurrentEntity);
#endif
}
