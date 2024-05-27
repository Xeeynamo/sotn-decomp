#include "../wrp/wrp.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/st_update", Update);

extern u16 UNK_Invincibility0[];

void UpdateStageEntities(void) {
    Entity* entity;
    s16 temp;
    for (entity = &g_Entities[STAGE_ENTITY_START];
         entity < &g_Entities[TOTAL_ENTITY_COUNT]; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->step) {
            if (!(entity->flags & FLAG_UNK_10000))
                continue;
            if (entity->flags & 0xF) {
                temp = entity->nFramesInvincibility << 1;
                temp += entity->flags & 1;
                entity->palette = UNK_Invincibility0[temp];
                if ((--entity->flags & 0xF) == 0) {
                    entity->palette = entity->hitEffect;
                    entity->hitEffect = 0;
                }
            }
        }

        g_CurrentEntity = entity;
        entity->pfnUpdate(entity);
        entity->unk44 = 0;
        entity->hitFlags = 0;
    }
}
