// SPDX-License-Identifier: AGPL-3.0-or-later

#if STAGE != STAGE_ST0
void CollectHeartVessel(void) {
#ifdef VERSION_BETA
    if (0) {
#else
    if (g_PlayableCharacter != PLAYER_ALUCARD) {
#endif
        g_api.PlaySfx(SFX_HEART_PICKUP);
        g_Status.hearts += HEART_VESSEL_RICHTER;

        if (g_Status.hearts > g_Status.heartsMax) {
            g_Status.hearts = g_Status.heartsMax;
        }
    } else {
        g_api.PlaySfx(SFX_HEART_PICKUP);
        g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(g_CurrentEntity);
}

static void CollectLifeVessel(void) {
    g_api.PlaySfx(SFX_HEART_PICKUP);
    g_api.func_800FE044(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(g_CurrentEntity);
}
#endif

#if defined VERSION_BETA || (STAGE == STAGE_ST0 && !defined(VERSION_PSP))
static void CollectDummy(void) { DestroyEntity(g_CurrentEntity); }

Entity* func_801939C4(void) {
    g_CurrentEntity->step = 3;
    g_CurrentEntity->params = 4;
    return g_CurrentEntity;
}
#else
static void CollectDummy(u16 id) { DestroyEntity(g_CurrentEntity); }
#endif
