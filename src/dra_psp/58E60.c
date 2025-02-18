// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/58E60", func_psp_091357E0);

INCLUDE_ASM("dra_psp/psp/dra_psp/58E60", EntityTeleport);

// Entity #66. Made by final blueprint, #122. Created in PlayerStepStand.
void EntityPlayerSleepZ(Entity* self) {
    if (PLAYER.step != Player_Stand || PLAYER.step_s != Player_Stand_ChairSit) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(17);
        self->velocityY = FIX(-0.375);
        SetSpeedX(FIX(0.25));
        self->unk5A = 0x50;
        self->palette = PAL_OVL(0x19F);
        self->anim = D_800AE294;

        self->posY.i.hi -= 16;
        self->posX.val += self->velocityX << 5;
        self->flags = FLAG_UNK_100000;
        self->facingLeft = 0;
        self->step++;
        break;

    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/58E60", func_psp_091367A0);

INCLUDE_ASM("dra_psp/psp/dra_psp/58E60", func_psp_09136BF8);

INCLUDE_ASM("dra_psp/psp/dra_psp/58E60", func_psp_09136D18);

INCLUDE_ASM("dra_psp/psp/dra_psp/58E60", func_psp_09136E18);
