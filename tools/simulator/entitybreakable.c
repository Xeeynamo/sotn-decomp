#include "sotn.h"
#include <sfx.h>

u8 D_801805A8[] = {4, 1, 4, 2, 0, 0, 0, 0};
u8 D_801805B0[] = {4, 0, 4, 0, 0, 0, 0, 0};
u8* g_eBreakableAnimations[] = {
    /* 5B8 */ D_801805A8,
    /* 5BC */ D_801805B0,
    /* 5C0 */ 0,
    /* 5C4 */ 0,
    /* 5C8 */ 0,
    /* 5CC */ 0,
    /* 5D0 */ 0,
    /* 5D4 */ 0,
};
u8 g_eBreakableExplosionTypes[] = {
    /* 5E0 */ 0,
    /* 5E1 */ 0,
    /* 5E2 */ 0,
    /* 5E3 */ 0,
    /* 5E4 */ 0,
    /* 5E5 */ 0,
    /* 5E6 */ 0,
    /* 5E7 */ 0,
};
u16 g_eBreakableInit[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
u8 g_eBreakableBlendModes[] = {
    /* 5F8 */ 0x70,
    /* 5F9 */ 0x30,
    /* 5FA */ 0x00,
    /* 5FB */ 0x00,
    /* 5FC */ 0x00,
    /* 5FD */ 0x00,
    /* 5FE */ 0x00,
    /* 5FF */ 0x00,
    /* 600 */ 0x00,
    /* 601 */ 0x00,
    /* 602 */ 0x00,
    /* 603 */ 0x00,
    /* 604 */ 0x00,
    /* 605 */ 0x00,
    /* 606 */ 0x00,
    /* 607 */ 0x00,
};
u8 g_eBreakableHitboxes[] = {
    /* 5D8 */ 8,
    /* 5D9 */ 8,
    /* 5DA */ 0,
    /* 5DB */ 0,
    /* 5DC */ 0,
    /* 5DD */ 0,
    /* 5DE */ 0,
    /* 5DF */ 0,
};
u16 g_eBreakableanimSets[] = {
    /* 5E8 */ 3,
    /* 5EA */ 3,
    /* 5EC */ 0,
    /* 5EE */ 0,
    /* 5F0 */ 0,
    /* 5F2 */ 0,
    /* 5F4 */ 0,
    /* 5F6 */ 0,
};

void ReplaceBreakableWithItemDrop(Entity* self) {
    u16 subId;

    PreventEntityFromRespawning(self);

#if STAGE != STAGE_ST0
    if (!(g_Status.relics[10] & 2)) {
        DestroyEntity(self);
        return;
    }
#endif

    subId = self->subId &= 0xFFF;

    if (subId < 0x80) {
        self->objectId = ENTITY_PRICE_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityPrizeDrop;
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
    } else {
        subId -= 0x80;
        self->objectId = ENTITY_INVENTORY_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityEquipItemDrop;
    }

    self->subId = subId;
    self->unk6D = 0x10;
    self->step = 0;
}

void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->subId >> 0xC;
    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity* entityDropItem;
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            entityDropItem =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(ENTITY_EXPLOSION, entityDropItem);
                entityDropItem->subId =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_zEntityCenter.S16.unk0 - 0x14;
        entity->blendMode = g_eBreakableBlendModes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animSet = g_eBreakableanimSets[breakableType];
    }
}
