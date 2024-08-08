#include <stage.h>
#include <sfx.h>

static u8 D_801805A8[] = {4, 1, 4, 2, 0, 0, 0, 0};
static u8 D_801805B0[] = {4, 0, 4, 0, 0, 0, 0, 0};
static u8* g_eBreakableAnimations[] = {
    D_801805A8, D_801805B0, NULL, NULL, NULL, NULL, NULL, NULL,
};
static u8 g_eBreakableHitboxes[] = {
    8, 8, 0, 0, 0, 0, 0, 0,
};

#ifndef VERSION_PSP // on PSP this is in the BSS section, not data
static u8 g_eBreakableExplosionTypes[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
};
#else
extern u8 g_eBreakableExplosionTypes[];
#endif

static u16 g_eBreakableanimSets[] = {
    3, 3, 0, 0, 0, 0, 0, 0,
};
static u8 g_eBreakableDrawModes[] = {
    DRAW_TPAGE | DRAW_TPAGE2 | DRAW_UNK_40,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
};

#ifndef VERSION_PSP
// on PSP this might be either optimised out to BSS or completely removed
static u8 unused[] = {0, 0, 0, 0, 0, 0, 0, 0};
#endif

extern u16 g_eBreakableInit[];

void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity);
void ReplaceBreakableWithItemDrop(Entity*);
Entity* AllocEntity(Entity* start, Entity* end);

void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->params >> 12;
    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity* entityDropItem;
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
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter.unk - 0x14;
        entity->drawMode = g_eBreakableDrawModes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animSet = g_eBreakableanimSets[breakableType];
    }
}
