// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_18CC0", func_us_801D511C);

extern s16 g_DarkOctopusYOffsets[];

void func_us_801D58FC(Entity* self) {
    Entity* entity;

    if ((self->flags & FLAG_DEAD) && self->step < 2) {
        self->hitboxState = 0;
        self->drawFlags |= ENTITY_OPACITY;
        self->opacity = 0x80;
        self->ext.darkOctopus.initialOpacity = 0x80;
        SetStep(2);
    }

    entity = self - 1;
    self->posX.i.hi = entity->posX.i.hi;
    self->posY.i.hi = entity->posY.i.hi;
    self->posY.i.hi += g_DarkOctopusYOffsets[entity->animCurFrame];

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDarkOctopus);
        self->hitboxWidth = 6;
        self->hitboxHeight = 0xB;
        self->hitboxOffX = 1;
        self->hitboxOffY = -5;
        self->nextPart = self - 1;
        break;

    case 1:
        AnimateEntity(g_DarkOctopusAnim, self);
        break;

    case 2: {
        if (g_Timer % 8 == 0) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != 0) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 0x11;
            }
        }

        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != 0) {
                CreateEntityFromEntity(E_SUBWPN_IN_CONT, self, entity);
                entity->params = 2;
                self->ext.darkOctopus.linkedEntity = entity;
                entity->ext.darkOctopus.linkedEntity = self;
            } else {
                self->ext.darkOctopus.linkedEntity = NULL;
            }
            self->step_s++;
            break;

        case 1:
            self->opacity -= 4;
            if (self->opacity) {
                break;
            }
            self->blendMode = BLEND_NO;
            self->opacity = 0x80;
            self->poseTimer = 0;
            self->pose = 0;
            self->palette = 0x8224;
            self->drawFlags |= ENTITY_SCALEY;
            self->scaleY = 0x100;
            if (self->ext.darkOctopus.linkedEntity != NULL) {
                entity = self->ext.darkOctopus.linkedEntity;
                DestroyEntity(entity);
            }
            self->step_s++;
            break;

        case 2:
            self->scaleY -= 4;
            self->posY.val += FIX(0.1875);
            if (self->scaleY < 0x20) {
                self->step_s++;
            }
            break;

        case 3:
            DestroyEntity(self);
            break;
        }
        break;
    }
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_18CC0", func_us_801D5BA4);
