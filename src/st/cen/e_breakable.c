// SPDX-License-Identifier: AGPL-3.0-or-later

#include "cen.h"
#include "game.h"
#include "sfx.h"

static u8 anim_1[] = {3, 14, 4, 15, 4, 16, 4, 17, 4, 18, 4, 19, 3, 20};
static u8 anim_2[] = {3, 21, 4, 22, 4, 23, 4, 24, 4, 25, 4, 26, 3, 27};

static u8* g_eBreakableAnimations[] = {
    anim_1, anim_2, NULL, NULL, NULL, NULL, NULL, NULL};
static u8 g_eBreakableHitboxes[] = {12, 20, 0, 0, 0, 0, 0, 0};

static u8 g_eBreakableExplosionTypes[] = {3, 3, 0, 0, 0, 0, 0, 0};

static u16 g_eBreakableanimSets[] = {
    ANIMSET_OVL(1), ANIMSET_OVL(1), 0, 0, 0, 0, 0, 0,
};

static u8 g_eBreakableDrawModes[] = {
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
};

static s16 xyOffsets[] = {
    -4, -4, 3, -6, 2, 9, -4, 12, 0, 2, 0, 15, 0, 31,
};

void EntityBreakable(Entity* self) {
    Entity* newEntity;
    u16* ptr;
    s32 j;
    s32 i;
    u16 breakableType = self->params >> 0xC;

    if (self->step == 0) {
        InitializeEntity(OVL_EXPORT(EInitBreakable));
        self->zPriority = 0xB0;
        self->drawMode = g_eBreakableDrawModes[breakableType];
        newEntity = &self[1];
        self->hitboxHeight = g_eBreakableHitboxes[breakableType];
        self->animSet = g_eBreakableanimSets[breakableType];
        DestroyEntity(newEntity);
        CreateEntityFromEntity(E_BACKGROUND_BLOCK, self, newEntity);
        if (breakableType != 0) {
            self[1].posY.i.hi -= 32;
        } else {
            self[1].posY.i.hi -= 16;
        }
        newEntity->params = 1;
    }

    AnimateEntity(g_eBreakableAnimations[breakableType], self);

    if (self->hitParams) {
        g_api.PlaySfx(SFX_CANDLE_HIT);
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != 0) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
            newEntity->params =
                g_eBreakableExplosionTypes[breakableType] | 0x10;
        }

        for (ptr = &xyOffsets, i = 0; i < 4; i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != 0) {
                CreateEntityFromEntity(E_BREAKABLE_UNK0, self, newEntity);
                newEntity->posX.i.hi += *ptr;
                ptr++;
                newEntity->posY.i.hi = newEntity->posY.i.hi + *ptr;
                ptr++;
                if (breakableType != 0) {
                    newEntity->posY.i.hi -= 20;
                }
                newEntity->params = i;
            }
        }

        if (breakableType != 0) {
            for (j = 0; j < 3; j++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(E_BREAKABLE_UNK0, self, newEntity);
                    newEntity->posX.i.hi += *ptr;
                    ptr++;
                    newEntity->posY.i.hi += *ptr;
                    ptr++;
                    newEntity->params = j + 4;
                }
            }
        }
        ReplaceBreakableWithItemDrop(self);
        DestroyEntity(&self[1]);
    }
}
