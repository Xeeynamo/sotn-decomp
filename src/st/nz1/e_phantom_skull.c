// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

extern EInit g_EInitPhantomSkull;
static u8 D_us_80182134[] = {
    0x01, 0x12, 0x02, 0x13, 0x02, 0x14, 0x02, 0x13, 0x03, 0x12, 0x03, 0x13,
    0x03, 0x14, 0x03, 0x13, 0x04, 0x12, 0x04, 0x13, 0x04, 0x14, 0x04, 0x13,
    0x05, 0x12, 0x05, 0x13, 0x10, 0x14, 0x05, 0x13, 0x01, 0x12, 0x00,
};
static s16 D_us_80182158[] = {
    FLT(0.25),
    FLT(0.375),
    FLT(0.5),
    FLT(0.625),
};

void EntityPhantomSkull(Entity* self) {
    Entity* entity;
    u8 timer;

    entity = &PLAYER;

    if (self->hitParams) {
        self->ext.phantom_skull.playerAngle =
            GetAngleBetweenEntitiesShifted(self, entity) - 0x80;
        self->ext.phantom_skull.acceleration = 0x1800;
        self->ext.phantom_skull.targetIsLeft = 0;
        self->step = 2;
    }

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_GHOST_ENEMY_HOWL);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 2;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitPhantomSkull);
        self->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE;
        break;
    case 1:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.phantom_skull.playerAngle =
            GetAngleBetweenEntitiesShifted(self, entity);
        self->ext.phantom_skull.playerAngle += -0x15 + ((Random() & 3) * 0x10);
        self->ext.phantom_skull.acceleration = D_us_80182158[Random() & 3];
        self->ext.phantom_skull.targetIsLeft = 0;
        self->step++;
        break;
    case 2:
        MoveEntity();
        SetEntityVelocityFromAngle(self->ext.phantom_skull.playerAngle,
                                   FLT_TO_I(self->ext.phantom_skull.velocity));
        if (self->ext.phantom_skull.targetIsLeft) {
            self->ext.phantom_skull.velocity -=
                self->ext.phantom_skull.acceleration;
        } else {
            self->ext.phantom_skull.velocity +=
                self->ext.phantom_skull.acceleration;
        }

        if (self->ext.phantom_skull.velocity > FLT(24)) {
            self->ext.phantom_skull.velocity = FLT(24);
            self->ext.phantom_skull.targetIsLeft = 1;
        }
        if (self->ext.phantom_skull.velocity < 0) {
            self->ext.phantom_skull.velocity = 0;
            self->ext.phantom_skull.targetIsLeft = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }

        if (self->ext.phantom_skull.timer++ > 4) {
            self->ext.phantom_skull.timer = 0;
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_PHANTOM_SKULL_TRAIL, self, entity);
                entity->facingLeft = self->facingLeft;
            }
        }
        break;
    case 3:
        if (!AnimateEntity(D_us_80182134, self)) {
            self->step = 1;
        }
        if (!self->poseTimer) {
            if ((self->pose % 4) == 0) {
                PlaySfxPositional(SFX_SKULL_BONK);
            }
        }
        break;
    case 16:
        if (g_pads[0].pressed & PAD_SQUARE) {
            if (!self->params) {
                self->animCurFrame--;
                self->params |= 1;
            }
        } else {
            self->params = 0;
        }
        break;
    }
}

extern EInit g_EInitPhantomSkullTrail;

void EntityPhantomSkullTrail(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitPhantomSkullTrail);
        self->hitboxState = 0;
        self->animCurFrame = 0x12;
        self->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags |= FLAG_DRAW_OPACITY;
        self->opacity = 0x40;
        break;
    case 1:
        self->opacity -= 2;
        if (self->opacity < 5) {
            DestroyEntity(self);
        }
        break;
    }
}
