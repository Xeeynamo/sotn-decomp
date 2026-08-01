// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

extern EInit D_us_801806B8;
extern u8 D_us_80180BEC[];
extern u8 D_us_80180BFC[];

void EntityCandleTable(Entity* self) {
    Entity* newEntity;

    switch (self->step) { /* irregular */
    case 0:
        InitializeEntity(D_us_801806B8);
        self->zPriority = 0x74;
        if (self->params & 0x400) {
            self->animCurFrame = 0x11;
            self->step = 4;
            break;
        }
        if (self->params & 0x200) {
            self->animCurFrame = 0x12;
            self->step = 4;
            break;
        }
        if (self->params & 0x100) {
            self->blendMode = BLEND_TRANSP | BLEND_QUARTER;
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0xC0;
        } else {
            self->zPriority += 4;
            self->hitboxWidth = 8;
            self->hitboxHeight = 0xC;
            self->hitboxOffY = 0xA;
            self->hitboxOffX = 0;
            self->hitboxState = 2;
            newEntity = self + 1;
            CreateEntityFromEntity(0x29, self, newEntity);
            newEntity->params = 0x100;
        }
    case 1:
        if (self->params & 0x100) {
            AnimateEntity(D_us_80180BFC, self);
            break;
        }
        AnimateEntity(D_us_80180BEC, self);
        if (self->hitFlags) {
            SetStep(2);
        }
        break;
    case 2:
        newEntity = self + 1;
        CreateEntityFromEntity(0xC, self, newEntity);
        newEntity->params = 6;
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, self, newEntity);
            newEntity->params = 2;
            newEntity->posY.i.hi -= 8;
        }
        self->hitboxState = 0;
        self->step++;
        /* fallthrough */
    case 3:
        self->animCurFrame = 8;
    case 4:
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
}
