// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

extern u16 UNK_Invincibility0[];
void UpdateStageEntities(void) {
    Entity* entity;
    s16 iFramePalette;

    for (entity = &g_Entities[STAGE_ENTITY_START];
         entity < &g_Entities[TOTAL_ENTITY_COUNT]; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->step) {
#ifdef VERSION_BETA
            if (D_80096ED0_mad && !(entity->flags & FLAG_UNK_10000))
#else
            if (!(entity->flags & FLAG_UNK_10000))
#endif
                continue;
            if (entity->flags & 0xF) {
                iFramePalette = entity->nFramesInvincibility << 1;
                iFramePalette += entity->flags & 1;
                entity->palette = UNK_Invincibility0[iFramePalette];
                if ((--entity->flags & 0xF) == 0) {
                    entity->palette = entity->hitEffect;
                    entity->hitEffect = 0;
                }
            }
        }

        g_CurrentEntity = entity;
        entity->pfnUpdate(entity);
        entity->hitParams = 0;
        entity->hitFlags = 0;
    }
}
