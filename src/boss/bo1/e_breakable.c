// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo1.h"

extern EInit g_EInitBreakable;

static AnimateEntityFrame anim_breakable_c1c[] = {
    {6, 4}, {6, 5}, {6, 6}, {6, 7}, {6, 8}, POSE_LOOP(0)};
static AnimateEntityFrame anim_breakable_c28[] = {
    {6, 9}, {6, 10}, {6, 11}, {6, 12}, {6, 13}, POSE_LOOP(0)};
static AnimateEntityFrame anim_breakable_c34[] = {
    {4, 14}, {4, 15}, {4, 14}, {4, 15}, {6, 16}, POSE_LOOP(0)};

static AnimateEntityFrame* g_eBreakableAnimations[] = {
    anim_breakable_c1c, anim_breakable_c28, anim_breakable_c34, NULL};
static u8 g_eBreakableHitboxes[] = {8, 8, 8, 8};
static u8 g_eBreakableExplosionTypes[] = {0, 0, 0, 0};
static u16 g_eBreakableanimSets[] = {
    ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2)};
static u8 blend_modes[] = {BLEND_TRANSP | BLEND_ADD, BLEND_TRANSP | BLEND_ADD,
                           BLEND_TRANSP | BLEND_ADD, BLEND_TRANSP | BLEND_ADD};
static u16 g_eBreakableZPriority[] = {0xA8, 0xA8, 0x60, 0x60};
static u8 unused[] = {0, 0, 0, 0, 0, 0, 0, 0};

void EntityBreakable(Entity* self) {
    u16 breakableType = self->params >> 12;
    if (self->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], self);
        if (self->hitParams) {
            Entity* entityDropItem;
            g_api.PlaySfx(SFX_CANDLE_HIT);
            entityDropItem = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entityDropItem);
                entityDropItem->params =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(self);
        }
    } else {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        self->zPriority = g_eBreakableZPriority[breakableType];
        self->blendMode = blend_modes[breakableType];
        self->hitboxHeight = g_eBreakableHitboxes[breakableType];
        self->animSet = g_eBreakableanimSets[breakableType];
    }
}
