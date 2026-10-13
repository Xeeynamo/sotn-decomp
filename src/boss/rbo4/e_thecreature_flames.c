// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"

extern EInit g_EInitParticle;

static AnimateEntityFrame anim_flame[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(3, 3, 0),  POSE(3, 4, 0),
    POSE(3, 5, 0),  POSE(3, 6, 0),  POSE(3, 7, 0),  POSE(3, 8, 0),
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE_END,
};
static AnimateEntityFrame anim_unused[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(3, 3, 0),  POSE(3, 4, 0),
    POSE(3, 5, 0),  POSE(3, 6, 0),  POSE(3, 7, 0),  POSE(3, 8, 0),
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE_LOOP(0),
};
static AnimateEntityFrame anim_flame_head[] = {
    POSE(2, 1, 0),  POSE(2, 2, 0),  POSE(2, 3, 0),  POSE(2, 4, 0),
    POSE(2, 5, 0),  POSE(2, 6, 0),  POSE(2, 7, 0),  POSE(2, 8, 0),
    POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE(2, 14, 0), POSE_LOOP(0),
};
static EntityConfig flames_config[] = {
    {ANIMSET_OVL(4), 0x51, 0x0E, BLEND_TRANSP | BLEND_ADD, (u8*)anim_flame},
    {ANIMSET_OVL(5), 0x54, 0x0E, BLEND_TRANSP | BLEND_ADD,
     (u8*)anim_flame_head},
    {ANIMSET_OVL(4), 0x51, 0x0E, BLEND_TRANSP | BLEND_ADD, (u8*)anim_flame},
};

// params 0: rising flame from the body, 1: flame on the fallen head, 2: flame
// burst in a random direction
void EntityTheCreatureFlames(Entity* self) {
    EntityConfig* config;
    s32 params;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        config = &flames_config[params];
        self->palette = config->palette + 0x2E0;
        self->blendMode = config->blendMode;
        self->animSet = config->animSet;
        self->unk5A = config->unk5A;
        self->ext.theCreatureFlames.anim = config->animData;
        self->step = params + 1;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_19F);
            self->blendMode = BLEND_TRANSP;
            self->facingLeft = 1;
        }
        break;
    case 1:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0xC0;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 8) - FIX(0.5);
            self->velocityY = FIX(-0.75);
            self->ext.theCreatureFlames.accelY = -(Random() * 16) - FIX(0.25);
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += (s32)self->ext.theCreatureFlames.accelY;
        self->opacity -= 1;
        if (!AnimateEntity(self->ext.theCreatureFlames.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 2:
        if (!self->step_s) {
            self->velocityY = FIX(-0.25);
            self->step_s++;
        }
        MoveEntity();
        if (!AnimateEntity(self->ext.theCreatureFlames.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 3:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->drawFlags |= ENTITY_ROTATE;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->rotate = (rand() & 0x7FF) - ROT(90);
            angle = self->rotate;
            if (self->facingLeft) {
                angle = -angle;
            }
            self->velocityX = rsin(angle) * 40;
            self->velocityY = rcos(angle) * -40;
            self->ext.theCreatureFlames.accel = (Random() * 16) + 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->opacity -= 1;
        angle = self->rotate;
        if (self->facingLeft) {
            angle = -angle;
        }
        self->velocityX +=
            (self->ext.theCreatureFlames.accel * rsin(angle)) >> 12;
        self->velocityY +=
            (-self->ext.theCreatureFlames.accel * rcos(angle)) >> 12;
        if (!AnimateEntity(self->ext.theCreatureFlames.anim, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
