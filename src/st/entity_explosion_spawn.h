// SPDX-License-Identifier: AGPL-3.0-or-later

void EntityExplosionSpawn(u16 params, u16 arg1) {
    Entity* entity;
#if STAGE != STAGE_ST0
    if (arg1 != 0) {
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

    entity = g_CurrentEntity;
    entity->drawFlags = FLAG_DRAW_DEFAULT;
    entity->entityId = E_EXPLOSION;
    entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    entity->params = params;
    entity->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}
