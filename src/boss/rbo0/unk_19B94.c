// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"

typedef struct {
    u16 animSet;
    u16 unk5A;
    u16 palette;
    u16 blendMode;
    AnimateEntityFrame* frames;
} Unk80180D98;

static AnimateEntityFrame D_us_80180D5C[] = {
    POSE(3, 0x01, 0), POSE(3, 0x02, 0), POSE(3, 0x03, 0), POSE(3, 0x04, 0),
    POSE(3, 0x05, 0), POSE(3, 0x06, 0), POSE(3, 0x07, 0), POSE(3, 0x08, 0),
    POSE(3, 0x09, 0), POSE(3, 0x0A, 0), POSE(3, 0x0B, 0), POSE(3, 0x0C, 0),
    POSE(3, 0x0D, 0), POSE_END};
static AnimateEntityFrame D_us_80180D78[] = {
    POSE(2, 0x01, 0), POSE(2, 0x02, 0), POSE(2, 0x03, 0), POSE(2, 0x04, 0),
    POSE(2, 0x05, 0), POSE(2, 0x06, 0), POSE(2, 0x07, 0), POSE(2, 0x08, 0),
    POSE(2, 0x09, 0), POSE(2, 0x0A, 0), POSE(2, 0x0B, 0), POSE(2, 0x0C, 0),
    POSE(2, 0x0D, 0), POSE(2, 0x0E, 0), POSE_END};

Unk80180D98 D_us_80180D98[] = {
    {ANIMSET_DRA(14), 0x79, 0x00, 0x30, D_us_80180D5C},
    {ANIMSET_OVL(5), 0x57, 0x00, 0x00, D_us_80180D78},
    {ANIMSET_OVL(5), 0x57, 0x03, 0x30, D_us_80180D78},
    {ANIMSET_DRA(14), 0x79, 0x04, 0x30, D_us_80180D5C},
    {ANIMSET_DRA(14), 0x79, 0x09, 0x30, D_us_80180D5C},
    {ANIMSET_OVL(5), 0x57, 0x0F, 0x30, D_us_80180D78},
    {ANIMSET_DRA(14), 0x79, 0x0E, 0x70, D_us_80180D5C},
    {ANIMSET_DRA(14), 0x79, 0x0A, 0x30, D_us_80180D5C},
    {ANIMSET_DRA(14), 0x79, 0x06, 0x30, D_us_80180D5C},
    {ANIMSET_DRA(14), 0x79, 0x0E, 0x30, D_us_80180D5C},
};

extern EInit g_EInitParticle;

void EntityDeathFlames(Entity* self) {
    Unk80180D98* temp_v1_2;
    s32 params;
    s32 scale;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        temp_v1_2 = &D_us_80180D98[params];
        self->palette = temp_v1_2->palette + 0x2E0;
        self->blendMode = temp_v1_2->blendMode;
        self->animSet = temp_v1_2->animSet;
        self->unk5A = temp_v1_2->unk5A;
        self->ext.deathFlames.frames = temp_v1_2->frames;
        self->step = params + 1;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_19F);
            self->blendMode = BLEND_TRANSP;
            self->facingLeft = true;
        }
        break;

    case 1:
        MoveEntity();
        self->velocityY = FIX(-1);
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    case 2:
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    case 3:
        if (!self->step_s) {
            self->drawFlags |= ENTITY_ROTATE;
            switch (self->ext.deathFlames.unk88) {
            case 1:
                if (self->ext.deathFlames.unk89 > 3) {
                    self->ext.deathFlames.unk89 -= 3;
                    self->ext.deathFlames.angle =
                        self->ext.deathFlames.angle - 0x800;
                }
                break;
            case 2:
                self->ext.deathFlames.angle +=
                    self->ext.deathFlames.unk89 * 0xC0;
                break;
            }
            self->ext.deathFlames.angle &= 0xFFF;
            self->rotate = self->ext.deathFlames.angle;
            scale = (self->ext.deathFlames.unk89 * 0x140) / 28;
            self->velocityX = scale * rsin(self->ext.deathFlames.angle);
            self->velocityY = -(scale * rcos(self->ext.deathFlames.angle));
            self->step_s++;
        }
        if (self->pose > 12) {
            self->velocityX -= self->velocityX / 4;
            self->velocityY -= self->velocityY / 4;
        }
        MoveEntity();
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    case 4:
        if (!self->step_s) {
            self->facingLeft = Random() & 1;
            self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x80;
            self->step_s++;
            self->velocityY = FIX(-0.125);
        }
        MoveEntity();
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    case 5:
        if (!self->step_s) {
            self->facingLeft = Random() & 1;
            self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x80;
            self->step_s++;
            self->velocityY = FIX(0.125);
        }
        MoveEntity();
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    case 6:
        if (!self->step_s) {
            self->facingLeft = Random() & 1;
            self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x80;
            self->step_s++;
        }
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    case 7:
        if (!self->step_s) {
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 7) - FIX(0.25);
            self->velocityY = FIX(-1.0);
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x100;
            self->step_s++;
        }
        MoveEntity();
        self->scaleX = self->scaleY += 2;
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    case 8:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 9) - FIX(0.5);
            self->velocityY = FIX(-0.5);
            self->ext.deathFlames.unk8C = -(Random() * 0x10) - 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += self->ext.deathFlames.unk8C;
        self->opacity -= 1;
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    case 9:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 9) - FIX(0.5);
            self->velocityY = FIX(-0.5);
            self->ext.deathFlames.unk8C = -(Random() * 0x10) - 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += self->ext.deathFlames.unk8C;
        self->opacity -= 1;
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    case 10:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 9) - FIX(0.5);
            self->velocityY = FIX(-0.5);
            self->ext.deathFlames.unk8C = -(Random() * 0x10) - 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += self->ext.deathFlames.unk8C;
        self->opacity -= 1;
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
