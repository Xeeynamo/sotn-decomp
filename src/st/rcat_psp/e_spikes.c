// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rcat/rcat.h"

enum SpikesSteps {
    SPIKES_INIT,
    SPIKES_INTERACT,
};

enum SpikesPartsSteps {
    SPIKES_PARTS_INIT,
    SPIKES_PARTS_MOVE,
};

enum SpikesMoveDirections {
    SPIKES_MOVE_RIGHT = 1,
    SPIKES_MOVE_LEFT = 2,
};

enum SpikesPointDirections {
    SPIKES_DEFAULT = 0,
    SPIKES_POINT_RIGHT = 1,
    SPIKES_POINT_LEFT = 2,
    SPIKES_ON_CEILING = 4,
    SPIKES_ON_FLOOR = 8,
};

INCLUDE_ASM("st/rcat_psp/nonmatchings/rcat_psp/e_spikes", EntitySpikesDust);

extern void (*D_91CF780)(s16 posX, s16 posY, Collider* collider, u32 unk);
extern u16 D_us_80181018;

void EntitySpikesParts(Entity* self) {
    Collider collider;
    s32 posX, posY;
    u8 params;

    switch (self->step) { // irregular
    case SPIKES_PARTS_INIT:
        InitializeEntity(&D_us_80181018);
        self->animCurFrame = 18;
        self->drawFlags |= ENTITY_ROTATE;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->zPriority = 160;
        self->velocityX = 0;
        self->velocityY = 0;
        self->rotate = 0;
        self->ext.spikes.rotate = 0;

        params = (self->params & 0xFF00) >> 8;

        if (params & 1) {
            self->velocityX = FIX(0.5);
            self->rotate += ROT(1.40625);
            self->ext.spikes.rotate += +8;
        }
        if (params & 2) {
            self->velocityX = -FIX(0.5);
            self->rotate -= ROT(1.40625);
            self->ext.spikes.rotate -= 8;
        }

        params = self->params & 0xFF;
        if (params & SPIKES_POINT_LEFT) {
            self->velocityX -= FIX(0.75);
            self->rotate -= ROT(90);
            self->ext.spikes.rotate += ROT(5.625);
        }
        if (params & SPIKES_POINT_RIGHT) {
            self->velocityX += FIX(0.75);
            self->rotate += ROT(90);
            self->ext.spikes.rotate -= ROT(5.625);
        }
        if (params & SPIKES_ON_CEILING) {
            self->velocityY += FIX(0.75);
            self->rotate -= ROT(180);
        }
        if (params & SPIKES_ON_FLOOR) {
            self->velocityY -= FIX(2.5);
        }
        self->velocityX += ((Random() & 3) << 13) - FIX(0.1875);
        self->velocityY += ((Random() & 3) << 13) - FIX(0.1875);
        self->ext.spikes.rotate += ((Random() & 3) * 16) - 24;
        break;
    case SPIKES_PARTS_MOVE:
        MoveEntity();
        self->velocityY += FIX(0.15625);
        self->rotate += self->ext.spikes.rotate;

        posX = self->posX.i.hi;
        posY = self->posY.i.hi;

        // Need to keep this conversion to compile to seh and not move
        D_91CF780((s16)posX, (s16)posY, &collider, 0);

        if (collider.effects) {
            if (collider.effects & EFFECT_SOLID) {
                self->velocityY = -self->velocityY / 2;
                self->ext.spikes.rotate *= 4;
            }
            if (collider.effects & EFFECT_UNK_0002) {
                self->velocityX = -self->velocityX;
            }
            if (abs(self->velocityY) < FIX(0.1875)) {
                DestroyEntity(self);
            }
        }
        break;
    }
}

INCLUDE_ASM("st/rcat_psp/nonmatchings/rcat_psp/e_spikes", SpikesBreak);

INCLUDE_ASM("st/rcat_psp/nonmatchings/rcat_psp/e_spikes", SpikesApplyDamage);

INCLUDE_ASM("st/rcat_psp/nonmatchings/rcat_psp/e_spikes", EntitySpikes);

INCLUDE_ASM("st/rcat_psp/nonmatchings/rcat_psp/e_spikes", EntitySpikesDamage);
