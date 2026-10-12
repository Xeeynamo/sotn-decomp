// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcen.h"

extern EInit g_EInitParticle;
typedef struct {
    u16 animSet;
    u16 unk5A;
    u16 paletteOffset;
    u16 blendMode;
    struct AnimateEntityFrame* frames;
} DeathFlamesInit;

static AnimateEntityFrame anim_flames_small[] = {
    {0x03, 0x01}, {0x03, 0x02}, {0x03, 0x03}, {0x03, 0x04}, {0x03, 0x05},
    {0x03, 0x06}, {0x03, 0x07}, {0x03, 0x08}, {0x03, 0x09}, {0x03, 0x0A},
    {0x03, 0x0B}, {0x03, 0x0C}, {0x03, 0x0D}, POSE_END,
};

// A sped up version which is almost identical to the second animation below
// Each animation frame plays for one frame less duration.
static AnimateEntityFrame anim_unused[] = {
    {0x02, 0x01}, {0x02, 0x02}, {0x02, 0x03}, {0x02, 0x04}, {0x02, 0x05},
    {0x02, 0x06}, {0x02, 0x07}, {0x02, 0x08}, {0x02, 0x09}, {0x02, 0x0A},
    {0x02, 0x0B}, {0x02, 0x0C}, {0x02, 0x0D}, {0x02, 0x0E}, POSE_END,
};

static AnimateEntityFrame anim_flames_main[] = {
    {0x03, 0x01}, {0x03, 0x02}, {0x03, 0x03}, {0x03, 0x04}, {0x03, 0x05},
    {0x03, 0x06}, {0x03, 0x07}, {0x03, 0x08}, {0x03, 0x09}, {0x03, 0x0A},
    {0x03, 0x0B}, {0x03, 0x0C}, {0x03, 0x0D}, POSE_END,
};

// Indexed off the params
// [0] = appears unused?
// [1] = small flames (orbs)
// [2] = circular flames (main)
// [3] = vertical flames (final burst)
static DeathFlamesInit deathFlamesInit[] = {
    {
        .animSet = ANIMSET_DRA(14),
        .unk5A = 0x79,
        // 0x2E0
        .paletteOffset = 0,
        .blendMode = BLEND_TRANSP | BLEND_ADD,
        .frames = anim_flames_small,
    },
    {
        .animSet = ANIMSET_DRA(14),
        .unk5A = 0x79,
        // 0x2EA
        .paletteOffset = 0xA,
        .blendMode = BLEND_TRANSP | BLEND_ADD,
        .frames = anim_flames_small,
    },
    {
        .animSet = ANIMSET_OVL(4),
        .unk5A = 0x58,
        // 0x2EE
        .paletteOffset = 0xE,
        .blendMode = BLEND_TRANSP | BLEND_ADD,
        .frames = anim_flames_main,
    },
    {
        .animSet = ANIMSET_OVL(4),
        .unk5A = 0x58,
        // 0x2EE
        .paletteOffset = 0xE,
        .blendMode = BLEND_TRANSP | BLEND_ADD,
        .frames = anim_flames_main,
    },
};

// Unused and stripped on PSP
static void func_us_8019D260(void) {
    Entity* entity;
    s16 angle;
    s32 i;
    u8 var_s4;

    var_s4 = Random() & 3;
    angle = ((Random() & 0xF) << 8) - ROT(180);

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(
                E_SHAFT_DEATH_FLAMES, g_CurrentEntity, entity);
            entity->ext.deathFlames.unk89 = 6 - i;
            entity->ext.deathFlames.unk88 = var_s4;
            entity->params = 2;
            entity->ext.deathFlames.angle = angle;
            entity->zPriority = g_CurrentEntity->zPriority + 1;
        }
    }
}

// Params
// 0 = unused?
// 1 = small flames (orbs)
// 2 = circular flames (main)
// 3 = vertical flames (final burst)
void EntityShaftDeathFlames(Entity* self) {
    typedef enum {
        INIT = 0,
        UNK_FLAMES = 1,
        ORB_FLAMES = 2,
        MAIN_FLAMES = 3,
        VERTICAL_FLAME = 4,
    } DeathFlamesStep;

    DeathFlamesInit* entityInit;
    s16 angle;
    s32 params;
    s32 scale;

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        entityInit = &deathFlamesInit[params];
        self->palette = entityInit->paletteOffset + PAL_SHAFT_DEATH_FLAMES;
        self->blendMode = entityInit->blendMode;
        self->animSet = entityInit->animSet;
        self->unk5A = entityInit->unk5A;
        self->ext.deathFlames.frames = entityInit->frames;
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

    case UNK_FLAMES:
        MoveEntity();
        self->velocityY = FIX(-1);
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    // The orbs flame out on death
    case ORB_FLAMES:
        if (!self->step_s) {
            self->rotate = Random() - 0x80;
            self->drawFlags = ENTITY_ROTATE;
            self->facingLeft = Random() & 1;
            angle = self->rotate;
            if (self->facingLeft) {
                angle = -angle;
            }
            self->velocityX = rsin(angle) * 0x10;
            self->velocityY = rcos(angle) * -0x10;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY = FIX(-1);
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    // The circular large burst of flames at the beginning of Shaft's death
    case MAIN_FLAMES:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->drawFlags |= ENTITY_ROTATE;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->rotate = rand() & 0xFFF;
            angle = self->rotate;
            if (self->facingLeft) {
                angle = -angle;
            }
            self->velocityX = rsin(angle) * 0x28;
            self->velocityY = rcos(angle) * -0x28;
            self->ext.deathFlames.unk8C = (Random() * 0x10) + FIX(0.0625);
            self->step_s++;
        }
        MoveEntity();
        self->opacity -= 1;
        angle = self->rotate;
        if (self->facingLeft) {
            angle = -angle;
        }
        self->velocityX +=
            (LOW(self->ext.deathFlames.unk8C) * rsin(angle)) >> 0xC;
        self->velocityY +=
            (-LOW(self->ext.deathFlames.unk8C) * rcos(angle)) >> 0xC;
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    // The final vertical burst of flames as Shaft dies
    case VERTICAL_FLAME:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = ((Random() << 9) - FIX(0.5)) - FIX(0.5);
            self->velocityY = FIX(-2.5);
            self->ext.deathFlames.unk90 = -(Random() * 0x10) - FIX(0.0625);
            self->step_s += 1;
        }
        MoveEntity();
        self->velocityY += self->ext.deathFlames.unk90;
        self->opacity -= 1;
        if (!AnimateEntity(self->ext.deathFlames.frames, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
