// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz0.h"

extern EInit g_EInitImp;
extern EInit g_EInitImpSmoke;
// Imp flapping wings
static u8 anim_imp[] = {
    4, 1, 4, 2, 4, 3, 4, 4, 4, 5, 4, 6, 4, 5, 4, 4, 4, 3, 4, 2, 4, 1, 0};
// Smoke puff from Alucard when jammed by imp
static u8 anim_imp_smoke[] = {2,  7, 2,  8, 2,  9, 2,  10, 2,  11, 2,  12,  2,
                              13, 2, 14, 2, 15, 2, 16, 2,  17, 2,  18, 255, 0};

#include "../e_imp.h"

// The little smoke puff that shows up above and behind Alucard's head
void EntityImpSmoke(Entity* self) {
    Entity* player;
    if (!self->step) {
        InitializeEntity(g_EInitImpSmoke);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter + 4;
        player = &PLAYER;
        self->posX.i.hi = player->posX.i.hi;
        self->posY.i.hi = player->posY.i.hi - 0x18;
        if (player->facingLeft) {
            self->posX.i.hi -= 6;
        } else {
            self->posX.i.hi += 6;
        }
        g_api.PlaySfx(SFX_BONE_THROW);
    }
    self->posY.val -= FIX(0.5);
    if (AnimateEntity(&anim_imp_smoke, self) == 0) {
        DestroyEntity(self);
    }
}
