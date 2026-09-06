// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_185B0", func_us_801A362C);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_185B0", EntityBackgroundBlock);

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_185B0", func_us_801B1738);

void func_us_801B2864(Entity* self) {
    extern u16 g_EInitInteractable;
    extern s32 D_pspeu_0926C6C8;
    extern u8 D_pspeu_0926BB70;

    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitInteractable);
        self->flags |= FLAG_UNK_10000;
        self->palette = PAL_UNK_19E;
        self->palette = 0x2E2;
        self->palette = 0x2E5;
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        self->drawFlags = ENTITY_ROTATE;
        self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
        self->facingLeft = Random() & 1;
        angle = self->rotate;
        if (self->facingLeft) {
            self->rotate = -(s16)angle;
        }
        self->velocityX = rsin((s32)(s16)angle) * 0x28;
        self->velocityY = rcos((s32)(s16)angle) * -0x28;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0xE0;
        self->scaleY = 0x140;
        if (D_pspeu_0926C6C8 != 0) {
            self->scaleX = 0x120;
            self->scaleY = 0x120;
        }
        /* fall through */
    case 1:
        MoveEntity();
        if (AnimateEntity(&D_pspeu_0926BB70, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
