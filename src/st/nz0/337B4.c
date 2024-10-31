// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

// Breakable container holding Skill of Wolf, Bat Card, maybe others
static u8 anim_relic_container[] = {
    0x10, 0x02, 0x03, 0x01, 0x09, 0x02, 0x03, 0x01, 0x10, 0x02, 0x03, 0x01,
    0x05, 0x02, 0x03, 0x01, 0x40, 0x02, 0x03, 0x03, 0x10, 0x02, 0x03, 0x03,
    0x08, 0x02, 0x03, 0x01, 0x14, 0x02, 0x03, 0x03, 0x40, 0x02, 0x00, 0x00};
static u8 anim_relic_container_alt[] = {
    0x01, 0x05, 0x03, 0x09, 0x01, 0x06, 0x03, 0x09, 0x01, 0x07,
    0x03, 0x09, 0x01, 0x08, 0x03, 0x09, 0x00, 0x00, 0x00, 0x00};
static u8 anim_blue_flame_table[] = {
    0x01, 0x0A, 0x01, 0x0B, 0x01, 0x0C, 0x01, 0x0D, 0x01, 0x0E,
    0x01, 0x0F, 0x01, 0x10, 0x01, 0x11, 0x00, 0x00, 0x00, 0x00};
static u16 D_80180F9C[] = {0x0007, 0x0008, 0x0012, 0x0006};
void EntityRelicContainer(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitPrizeContainer);
        if (self->params & 0x100) {
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        } else {
            self->zPriority = 0x6A;
            self->hitboxWidth = 8;
            self->hitboxHeight = 12;
            self->hitboxOffX = 0;
            self->hitboxOffY = -0xA;
            self->hitboxState = 2;
            newEntity = self + 1;
            CreateEntityFromEntity(E_RELIC_CONTAINER, self, newEntity);
            newEntity->params = 0x100;
        }

    case 1:
        if (self->params & 0x100) {
            AnimateEntity(anim_relic_container_alt, self);
            break;
        }
        AnimateEntity(anim_relic_container, self);
        if (self->hitFlags) {
            self->hitboxState = 0;
            SetStep(2);
        }
        break;

    case 2:
        if (self->params > 0x1) {
            newEntity = self + 1;
            CreateEntityFromEntity(E_RELIC_ORB, self, newEntity);
            newEntity->params = D_80180F9C[self->params];
        } else {
            newEntity = self + 1;
            CreateEntityFromEntity(E_HEART_DROP, self, newEntity);
            newEntity->params = D_80180F9C[self->params];
        }

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->posY.i.hi -= 8;
            newEntity->params = 2;
        }
        PlaySfxPositional(SFX_GLASS_BREAK_E);
        self->step++;

    case 3:
        self->animCurFrame = 4;
        break;

    case 255:
#include "../pad2_anim_debug.h"
    }
}

// Table in room with bone-throwing skeleton. Drops a Resist Thunder.
void EntityBlueFlameTable(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitPrizeContainer);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 16;
        self->hitboxOffY = -0xA;
        self->hitboxOffX = 0;
        self->hitboxState = 2;

    case 1:
        AnimateEntity(anim_blue_flame_table, self);
        if (self->hitFlags != 0) {
            g_api.PlaySfx(SFX_CANDLE_HIT);
            self->hitboxState = 0;
            SetStep(2);
        }
        break;

    case 2:
        CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
        self[1].params = D_80180F9C[self->params];
        self->step++;

    case 3:
        self->animCurFrame = 18;
        break;
    }
}
