// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

typedef struct {
    s16 x, y, r;
} PosRot;

static PosRot D_us_80180FEC[] = {
    {0x01C0, 0x0028, 0x0200},
    {0x0250, 0x0028, 0x0C00},
};

void EntityPendulumAnchor(Entity* self) {
    s32 i;
    PosRot* var_a0;
    Entity* entity;
    s32 temp_v0;
    s32 var_s1;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->animCurFrame = 13;

        entity = self + 1;
        // chain entities
        for (i = 0; i < 7; i++, entity++) {
            CreateEntityFromEntity(E_ID(PENDULUM_BONE_CHAIN), self, entity);
        }
        // weight creation
        CreateEntityFromEntity(E_ID(PENDULUM_WEIGHT), self, entity);
        var_a0 = D_us_80180FEC;
        if (self->params) {
            var_a0++;
        }
        self->posX.i.hi = var_a0->x - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = var_a0->y - g_Tilemap.scrollY.i.hi;
        self->ext.pendulum.weightAngle = var_a0->r;
        // fallthrough

    case 1:
        self->ext.pendulum.chainAngle =
            (rsin(self->ext.pendulum.weightAngle) * 96) >> 12;
        self->ext.pendulum.weightAngle += 0x18;
        self->ext.pendulum.weightAngle &= 0xFFF;
        if ((self->ext.pendulum.weightAngle & 0x7FF) < 0x18) {
            PlaySfxPositional(SFX_BONE_CREAK);
        }
        break;
    }
}

void EntityPendulumBoneChain(Entity* self) {
    Entity* entity;
    s32 posX;
    s32 posY;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->animCurFrame = 0xA;
        self->drawFlags = FLAG_DRAW_ROTATE;
        // fallthrough

    case 1:
        entity = self - 1;
        posX = entity->posX.val;
        posY = entity->posY.val;
        angle = entity->ext.pendulum.chainAngle;
        angle += angle / 8;
        self->ext.pendulum.chainAngle = angle;
        self->rotate = angle;

        angle += 0x400;

        posX += FLT_TO_FIX(rcos(angle)) * 16;
        posY += FLT_TO_FIX(rsin(angle)) * 16;

        self->posX.val = posX;
        self->posY.val = posY;
        break;
    }
}

void EntityPendulumWeight(Entity* self) {
    Entity* entity;
    s32 collision;
    s32 posX;
    s32 posY;
    s32 offset;
    s16 rotation;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->hitboxWidth = self->hitboxHeight = 0xC;
        self->hitboxState = 1;
        self->animCurFrame = 0xB;
        self->drawFlags = FLAG_DRAW_ROTATE;
        // fallthrough

    case 1:
        entity = self - 1;
        posX = entity->posX.val;
        posY = entity->posY.val;
        rotation = entity->ext.pendulum.chainAngle;
        self->ext.pendulum.chainAngle = rotation;
        self->rotate = rotation;
        rotation += 0x400;
        posX += (rcos(rotation) * 0x18) * 16;
        posY += (rsin(rotation) * 0x18) * 16;
        self->posX.val = posX;
        self->posY.val = posY;
        entity = &PLAYER;
        if (self->ext.pendulum.collision & 4) {
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            offset = posY - self->ext.pendulum.offsetY;
            entity->posY.i.hi += offset + 1;
            D_80097488.y.i.hi += offset + 1;
        }

        collision = GetPlayerCollisionWith(self, 0xC, 0xC, 4);
        if (collision & 4) {
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            offset = posX - self->ext.pendulum.offsetX;
            entity->posX.i.hi += offset;
            D_80097488.x.i.hi += offset;
        }
        break;
    }

    self->ext.pendulum.collision = collision;
    self->ext.pendulum.offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    self->ext.pendulum.offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
}
