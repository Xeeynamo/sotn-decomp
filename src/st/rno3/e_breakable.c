// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"
extern EInit OVL_EXPORT(EInitBreakable);

static u8 anim_1[] = {4, 1, 4, 2, 0, 0};
static u8 anim_2[] = {4, 0, 4, 0, 0};
static u8* g_eBreakableAnimations[8] = {anim_1, anim_2};
static u8 g_eBreakableHitboxes[8] = {8, 8};
static u8 g_eBreakableExplosionTypes[8] = {0, 0};

static u16 g_eBreakableanimSets[8] = {ANIMSET_DRA(3), ANIMSET_DRA(3)};
static u8 blend_modes[8] = {
    BLEND_TRANSP | BLEND_QUARTER,
    BLEND_TRANSP | BLEND_ADD,
};

// Stripped on PSP
static u8 unused[] = {0, 0, 0, 0, 0, 0, 0, 0};

void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->params >> 12;
    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);

        if (entity->hitParams) { // If the candle is destroyed
            Entity* entityDropItem;
            entity->drawFlags = ENTITY_DEFAULT;
            entity->rotate = 0;
            g_api.PlaySfx(SFX_CANDLE_HIT);
            entityDropItem = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entityDropItem);
                entityDropItem->params =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(OVL_EXPORT(EInitBreakable));
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        entity->blendMode = blend_modes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];

        entity->animSet = g_eBreakableanimSets[breakableType];
        entity->drawFlags = ENTITY_ROTATE;
        entity->rotate = 0x800;
    }
}
