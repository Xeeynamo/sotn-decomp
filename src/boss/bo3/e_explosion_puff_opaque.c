// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

#include "../../st/create_explosion_puff.h"

static AnimateEntityFrame D_us_80180FE8[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(3, 3, 0),  POSE(3, 4, 0),
    POSE(3, 5, 0),  POSE(3, 6, 0),  POSE(3, 7, 0),  POSE(3, 8, 0),
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE_END};
static AnimateEntityFrame D_us_80181004[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(3, 3, 0),  POSE(3, 4, 0),
    POSE(3, 5, 0),  POSE(3, 6, 0),  POSE(3, 7, 0),  POSE(3, 8, 0),
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE_END};
static AnimateEntityFrame D_us_80181020[] = {
    POSE(2, 1, 0),  POSE(2, 2, 0),  POSE(2, 3, 0),  POSE(2, 4, 0),
    POSE(2, 5, 0),  POSE(2, 6, 0),  POSE(2, 7, 0),  POSE(2, 8, 0),
    POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE_END};
// unused
static AnimateEntityFrame anim_unused[] = {
    POSE(2, 1, 0),  POSE(2, 2, 0),  POSE(2, 3, 0),  POSE(2, 4, 0),
    POSE(2, 5, 0),  POSE(2, 6, 0),  POSE(2, 7, 0),  POSE(2, 8, 0),
    POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE(2, 14, 0), POSE_END};
static EntityConfig puff_config[] = {
    {ANIMSET_DRA(0xE), 0x0079, 0x0000, DRAW_TPAGE | DRAW_TPAGE2,
     (u8*)D_us_80180FE8},
    {ANIMSET_OVL(3), 0x0054, 0x0009, DRAW_TPAGE | DRAW_TPAGE2,
     (u8*)D_us_80181020},
    {ANIMSET_OVL(3), 0x0054, 0x0009, DRAW_TPAGE | DRAW_TPAGE2,
     (u8*)D_us_80181004},
    {ANIMSET_OVL(3), 0x0054, 0x0009, DRAW_TPAGE | DRAW_TPAGE2,
     (u8*)D_us_80181004},
};

extern EInit g_EInitParticle;

void EntityExplosionPuffOpaque(Entity* self) {
    EntityConfig* obj;
    s32 params;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        obj = &puff_config[params];
        self->palette = obj->palette + PAL_PUFF_OPAQUE_OFFSET;
        self->blendMode = obj->blendMode;
        self->animSet = obj->animSet;
        self->unk5A = obj->unk5A;
        self->ext.opaquePuff.anim = obj->animData;
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
        switch (self->step_s) {
        case 0:
            self->drawFlags = ENTITY_ROTATE;
            angle = self->rotate;
            self->velocityX = rcos(angle) << 4;
            self->velocityY = rsin(angle) << 4;
            self->step_s++;
            /* fall through */
        case 1:
            MoveEntity();
            if (!AnimateEntity(self->ext.opaquePuff.anim, self)) {
                DestroyEntity(self);
            }
            break;
        }
        break;

    case 2:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0xC0;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 8) - 0x8000;
            self->velocityY = FIX(-0.75);
            self->ext.opaquePuff.unk8C = -(Random() << 4) - 0x4000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += (s32)self->ext.opaquePuff.unk8C;
        self->opacity -= 1;
        if (!AnimateEntity(self->ext.opaquePuff.anim, self)) {
            DestroyEntity(self);
        }
        break;

    case 3:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 10) - FIX(2);
            self->velocityY = FIX(-2.25);
            self->ext.opaquePuff.unk8C = -(Random() << 4) - 0x2000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += (s32)self->ext.opaquePuff.unk8C;
        self->opacity -= 1;
        if (!AnimateEntity(self->ext.opaquePuff.anim, self)) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 9) - 0x8000 - 0x8000;
            self->velocityY = FIX(-2.5);
            self->ext.opaquePuff.unk8C = -(Random() << 4) - 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += (s32)self->ext.opaquePuff.unk8C;
        self->opacity -= 1;
        if (!AnimateEntity(self->ext.opaquePuff.anim, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
