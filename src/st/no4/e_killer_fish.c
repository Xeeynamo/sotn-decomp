// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

#ifdef VERSION_PSP
extern s32 D_psp_E_KILLER_FISH_DEATH_PUFF;
#endif

static u8 anim_iddle[] = {
    0x0A, 0x01, 0x0A, 0x02, 0x0A, 0x03, 0x0A, 0x02, 0x00, 0x00, 0x00, 0x00};
static u8 anim_swim[] = {
    0x0A, 0x04, 0x0A, 0x05, 0x0A, 0x06, 0x0A, 0x05, 0x0A, 0x04,
    0x0A, 0x0D, 0x0A, 0x0E, 0x0A, 0x0D, 0x00, 0x00, 0x00, 0x00};
static u8 anim_rotate[] = {
    0x0A, 0x07, 0x0A, 0x08, 0x0A, 0x09, 0x0A, 0x0A, 0x0A, 0x0B, 0xFF, 0x00};

// { posX.i.hi, posY.i.hi }
static s16 death_puff_positions[][2] = {
    {32, -8}, {0, 4}, {-24, -2}, {14, 12}, {-12, 8},
};

void EntityKillerFish(Entity* self) {
    Entity* entity;
    s16* ptr;
    s32 i;
    u16 params;

    if (self->flags & FLAG_DEAD && self->step != 4) {
        OVL_EXPORT(SetStep)(4);
    }

    params = self->params;
    switch (self->step) {
    case 0:
        OVL_EXPORT(InitializeEntity)(g_EInitKillerFish);
        self->facingLeft = params & 1;
        break;
    case 1:
        // Idle
        // nb. Interesting this is using the in-built rand() and not
        // OVL_EXPORT(Random)()
        if (!OVL_EXPORT(AnimateEntity)(anim_iddle, self) && !(rand() & 3)) {
            OVL_EXPORT(SetStep)(2);
            self->ext.killerFish.swimTimer = 0x100;
        }
        break;
    case 2:
        // Swim
        if (OVL_EXPORT(AnimateEntity)(anim_swim, self) & 0x80 &&
            (self->pose == 3 || self->pose == 7)) {
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
        }
        if (self->velocityX != 0) {
            if (self->facingLeft) {
                self->velocityX -= FIX(0.015625);
            } else {
                self->velocityX += FIX(0.015625);
            }
        }
        OVL_EXPORT(MoveEntity)();
        if (!--self->ext.killerFish.swimTimer) {
            self->velocityX = 0;
            OVL_EXPORT(SetStep)(3);
        }
        break;
    case 3:
        // Finished swimming one direction
        if (!OVL_EXPORT(AnimateEntity)(anim_rotate, self)) {
            if (self->ext.killerFish.swimCount++ & 1) {
                // On even numbered trips (left side), wait idle for a bit
                OVL_EXPORT(SetStep)(1);
            } else {
                // Otherwise swim back the other direction
                self->ext.killerFish.swimTimer = 0x100;
                OVL_EXPORT(SetStep)(2);
            }
            self->animCurFrame = 1;
            self->facingLeft ^= 1;
            if (self->facingLeft) {
                self->posX.i.hi += 8;
            } else {
                self->posX.i.hi -= 8;
            }
        }
        break;
    case 4:
        // Death
        PlaySfxPositional(SFX_EXPLODE_B);
        ptr = death_puff_positions[0];

        for (i = 0; i < LEN(death_puff_positions); i++) {
            entity =
                OVL_EXPORT(AllocEntity)(&g_Entities[224], &g_Entities[256]);
            if (entity == NULL) {
                break;
            }
            OVL_EXPORT(CreateEntityFromCurrentEntity)
            (E_ID(KILLER_FISH_DEATH_PUFF), entity);
            if (self->facingLeft) {
                entity->posX.i.hi += *ptr++;
            } else {
                entity->posX.i.hi -= *ptr++;
            }
            entity->posY.i.hi += *ptr++;
        }

        DestroyEntity(self);
        return;
    }

    params = self->animCurFrame;
    if (params == 9) {
        // Hitbox shrinks slightly in the middle of changing directions
        self->hitboxWidth = 6;
        self->hitboxOffX = -0xA;
    } else {
        self->hitboxWidth = 0x14;
        self->hitboxOffX = 0;
        if (params >= 10 && params < 13) {
            self->hitboxWidth = 0x10;
            self->hitboxOffX = 4;
        }
    }
    self->hitboxOffY = 2;
    self->hitboxHeight = 8;
}

static u8 anim_death_puff[] = {
    0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05,
    0x03, 0x06, 0x03, 0x07, 0x03, 0x08, 0x03, 0x09, 0x03, 0x0A,
    0x03, 0x0B, 0x03, 0x0C, 0x03, 0x0D, 0xFF, 0x00};

void EntityKillerFishDeathPuff(Entity* self) {
    if (!self->step) {
        OVL_EXPORT(InitializeEntity)(OVL_EXPORT(EInitParticle));
        self->pose = 0;
        self->poseTimer = 0;
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->palette = 0x2E8;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0x60;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->velocityY += -0x8000 - 0x8000;
        return;
    }

    self->posY.val += self->velocityY;
    if (!OVL_EXPORT(AnimateEntity)(anim_death_puff, self)) {
        DestroyEntity(self);
    }
}
