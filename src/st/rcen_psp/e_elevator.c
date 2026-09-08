// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rcen/rcen.h"

INCLUDE_ASM("st/rcen_psp/nonmatchings/rcen_psp/e_elevator", func_801904B8);

INCLUDE_ASM("st/rcen_psp/nonmatchings/rcen_psp/e_elevator", func_us_8019FE9C);

extern EInit g_EInitElevator;

u8 GetPlayerCollisionWith(Entity* self, u16 w, u16 h, u16 flags);

void EntityUnkId1B(Entity* self) {
    Entity* entity = self + self->params;
    u8 isTouchingPlayer;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevator);
        if (self->params & 16) {
            self->animCurFrame = self->params & 15;
            self->zPriority = 0x6A;
            self->step = 2;
            return;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        self->posX.i.hi = entity->posX.i.hi;
        if (self->params == 1) {
            self->posY.i.hi = entity->posY.i.hi + 27;
            isTouchingPlayer = GetPlayerCollisionWith(self, 12, 8, 4);
        } else {
            self->posY.i.hi = entity->posY.i.hi - 32;
            isTouchingPlayer = GetPlayerCollisionWith(self, 12, 8, 6);
        }
        self->ext.cenElevator.playerCollision = isTouchingPlayer;
        break;
    }
}
