// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

extern EInit g_EInitBreakable;
static AnimateEntityFrame anim1[] = {{4, 1}, {4, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim2[] = {{4, 0}, {4, 0}, POSE_LOOP(0)};


static AnimateEntityFrame* anims[] = {anim1, anim2, NULL, NULL, NULL, NULL, NULL, NULL};
extern u8 D_us_8018062C[]; 
extern u8 D_us_80180634[];
extern u16 D_us_8018063C[];
extern u8 D_us_8018064C[];

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
                entity->params = D_us_80180634[breakableType];
            }
            ReplaceBreakableWithItemDrop(self);
        }
    } else {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        self->blendMode = D_us_8018064C[breakableType];
        self->hitboxHeight = D_us_8018062C[breakableType];
        self->animSet = D_us_8018063C[breakableType];
    }
}
