// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

// Tank (and decoration) at bottom of secret floor room. When broken,
// provides a Life Max Up
static u8 D_80180F1C[] = {
    0x01, 0x01, 0x01, 0x02, 0x01, 0x03, 0x01, 0x04, 0x01, 0x05,
    0x01, 0x06, 0x01, 0x07, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00};

static u8 D_80180F30[] = {
    0x0F, 0x09, 0x06, 0x0A, 0x05, 0x0B, 0x04, 0x0C, 0x03, 0x0D,
    0x03, 0x0E, 0x03, 0x0F, 0x03, 0x10, 0x03, 0x11, 0x03, 0x12,
    0x30, 0x13, 0x01, 0x14, 0xFF, 0x00, 0x00, 0x00};

static u16 D_80180F4C[] = {0x0003, 0x0000};

void EntityLifeMaxTank(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLifeMaxTank);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 12;
        self->hitboxOffY = -0xA;
        self->hitboxOffX = 0;
        self->hitboxState = 2;

    case 1:
        AnimateEntity(D_80180F1C, self);
        if (self->hitFlags) {
            PlaySfxPositional(SFX_GLASS_BREAK_A);
            self->hitboxState = 0;
            SetStep(2);
        }
        break;

    case 2:
        if (AnimateEntity(D_80180F30, self) == 0) {
            CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
            self[1].params = D_80180F4C[self->params];
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 2;
                newEntity->posY.i.hi -= 8;
            }
            self->step++;
        }
        break;

    case 3:
        newEntity = self;
        newEntity->animCurFrame = 20;
        break;
    }
}
