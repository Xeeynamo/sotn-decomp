// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>
#include <sfx.h>

#ifndef SFX_BREAKABLE_HIT
#define SFX_BREAKABLE_HIT SFX_CANDLE_HIT
#endif

extern EInit g_EInitBreakable;

void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity);
void ReplaceBreakableWithItemDrop(Entity*);
Entity* AllocEntity(Entity* start, Entity* end);

void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->params >> 12;
    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->hitParams) { // If the candle is destroyed
            Entity* entityDropItem;
#if defined(DO_ROTATION)
#if defined(COND_ROTATION)
            if (!breakableType) {
#else
            if (1) {
#endif
                entity->drawFlags = ENTITY_DEFAULT;
                entity->rotate = ROT(0);
            }
#endif

#if defined(SPLIT_SFX)
            breakableType == 1 ? g_api.PlaySfx(SFX_GLASS_BREAK_C)
                               : g_api.PlaySfx(SFX_CANDLE_HIT_WHOOSH_A);
#else
            g_api.PlaySfx(SFX_BREAKABLE_HIT);
#endif
            entityDropItem = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entityDropItem);
                entityDropItem->params =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_EInitBreakable);
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        entity->blendMode = blend_modes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animSet = g_eBreakableanimSets[breakableType];
#if defined(DO_ROTATION)
#if defined(COND_ROTATION)
        if (!breakableType) {
#else
        if (1) {
#endif
            entity->drawFlags = ENTITY_ROTATE;
            entity->rotate = ROT(180);
        }
#endif
    }
}
