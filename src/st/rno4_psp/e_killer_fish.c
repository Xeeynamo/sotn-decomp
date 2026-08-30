// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/e_killer_fish", EntityKillerFish);

extern AnimationFrame g_KillerFishDeathPuffAnim;

void EntityKillerFishDeathPuff(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
#ifdef VERSION_PSP
        self->pose = 0;
        self->poseTimer = 0;
#endif
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->palette = 0x2E8;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags = ENTITY_OPACITY;
#ifndef VERSION_PSP
        self->pose = 0;
        self->poseTimer = 0;
#endif
        self->opacity = 0x60;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->velocityY += FIX(-1.0);
        return;
    }
    self->posY.val += self->velocityY;
    if (AnimateEntity(&g_KillerFishDeathPuffAnim, self) == 0) {
        DestroyEntity(self);
    }
}
