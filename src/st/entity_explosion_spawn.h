// SPDX-License-Identifier: AGPL-3.0-or-later

void EntityExplosionSpawn(u16 params, u16 arg1) {
#if STAGE != STAGE_ST0
    if (arg1) {
#if defined VERSION_BETA
        g_api.PlaySfx(arg1);
#else
        PlaySfxPositional(arg1);
#endif
    }
#endif
    if (params == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    g_CurrentEntity->entityId = E_EXPLOSION;
    g_CurrentEntity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    g_CurrentEntity->params = params;
    g_CurrentEntity->animCurFrame = 0;
    g_CurrentEntity->drawFlags = FLAG_DRAW_DEFAULT;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}
