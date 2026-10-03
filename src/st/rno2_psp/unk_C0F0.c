// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno2/rno2.h"

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_C0F0", EntityMalachi);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_C0F0", func_us_801C4960);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_C0F0", func_us_801C4C0C);

extern EInit g_EInitParticle;
extern AnimateEntityFrame g_Unk2EAnim[];

void func_us_801C4EA8(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 0xE;
        self->unk5A = 0x5C;
        self->palette = 0x2EE;
        self->drawFlags = 5;
        self->scaleX = 0x60;
        self->scaleY = 0xC0;
        self->blendMode = 0x70;
        angle = self->rotate;
        self->velocityX = rsin(angle) * 0x10;
        self->velocityY = rcos(angle) * -0x10;
        /* fallthrough */
    case 1:
        MoveEntity();
        if (AnimateEntity(g_Unk2EAnim, self) == 0) {
            DestroyEntity(self);
        }
    }
}

