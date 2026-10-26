// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

INCLUDE_ASM("st/rno4/nonmatchings/e_jack_o_bones", TryThrow);

INCLUDE_ASM("st/rno4/nonmatchings/e_jack_o_bones", EntityJackOBones);

void EntityJackOBonesDeathParts(Entity* self) {
    extern EInit g_EInitJackOBones2;
    extern u16 g_JackOBonesDeathPartsRotSpeeds[];
    if (self->step) {
        if (--self->ext.jackoBones.deathPartLife) {
            self->rotate += g_JackOBonesDeathPartsRotSpeeds[self->params];
            FallEntity();
            MoveEntity();
            return;
        }
        self->entityId = E_EXPLOSION;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }
    InitializeEntity(g_EInitJackOBones2);
    self->animCurFrame = (self->params & 0xFF) + 15;
    if (self->params & 0x100) {
        self->palette++;
    }
    self->drawFlags = ENTITY_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/e_jack_o_bones", EntityJackOBonesJack);
