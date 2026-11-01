// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

extern EInit g_EInitBreakable;
static AnimateEntityFrame anim1[] = {{4, 1}, {4, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim2[] = {{4, 0}, {4, 0}, POSE_LOOP(0)};

static AnimateEntityFrame* anims[8] = {anim1, anim2};
static u8 hitboxHeights[8] = {8, 8};
static u8 params_allzero[8] = {0, 0};
static u16 animsets[8] = {3, 3};
static u8 blends[8] = {
    BLEND_TRANSP | BLEND_QUARTER,
    BLEND_TRANSP | BLEND_ADD,
};
static u8 unused[8] = {0};

void EntityBreakable(Entity* self) {
    Entity* entity;
    u16 breakableType;

    breakableType = self->params >> 12;
    if (self->step) {
        AnimateEntity(anims[breakableType], self);
        if (self->hitParams) {
            g_api.PlaySfx(SFX_CANDLE_HIT);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
                entity->params = params_allzero[breakableType];
            }
            ReplaceBreakableWithItemDrop(self);
        }
    } else {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        self->blendMode = blends[breakableType];
        self->hitboxHeight = hitboxHeights[breakableType];
        self->animSet = animsets[breakableType];
    }
}
