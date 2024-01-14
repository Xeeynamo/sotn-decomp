void CollectHeart(u16 arg0) {
    s32* hearts;

    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    hearts = &g_Status.hearts;
    *hearts += c_HeartPrizes[arg0];

    if (g_Status.heartsMax < *hearts) {
        *hearts = g_Status.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}