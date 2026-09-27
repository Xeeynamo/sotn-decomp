// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno2.h"

INCLUDE_ASM("st/rno2/nonmatchings/unk_439A4", EntityMalachi);

INCLUDE_ASM("st/rno2/nonmatchings/unk_439A4", func_us_801C4960);

INCLUDE_ASM("st/rno2/nonmatchings/unk_439A4", func_us_801C4C0C);

void func_us_801C4EA8(Entity* self) {
    extern u8 g_Unk2EAnim;
#ifdef VERSION_PSP
    s16 angle;
#else
    s32 angle;
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
#ifndef VERSION_PSP
        angle = self->rotate;
#endif
        self->animSet = 0xE;
        self->unk5A = 0x5C;
        self->palette = 0x2EE;
        self->drawFlags = ENTITY_ROTATE | ENTITY_SCALEX;
        self->scaleX = 0x60;
        self->scaleY = 0xC0;
        self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
#ifdef VERSION_PSP
        angle = self->rotate;
        self->velocityX = rsin(angle) << 4;
        self->velocityY = (-rcos(angle)) << 4;
#else
        self->velocityX = rsin(angle) << 4;
        self->velocityY = -(rcos(angle) << 4);
#endif
    case 1:
        MoveEntity();
        if (AnimateEntity(&g_Unk2EAnim, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
