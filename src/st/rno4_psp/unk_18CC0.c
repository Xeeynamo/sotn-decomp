// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_18CC0", func_us_801D511C);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_18CC0", func_us_801D58FC);

// https://www.decomp.me/scratch/85Slq

extern u16 D_us_80180B54;
extern s16 D_us_801822DC;

void func_us_801D5BA4(Entity* self) {
    Entity* ent;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180B54);
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_ROTATE;
        self->drawFlags |= ENTITY_OPACITY;
        self->blendMode = BLEND_SUB | BLEND_TRANSP;
        self->opacity = 0x40;
        self->scaleX = 0x10;
        self->scaleY = 0x40;
        ent = g_Entities;
        self->zPriority = ent->zPriority + 1;
        self->rotate = self->ext.et_801D5BA4.unk84;
        self->ext.et_801D5BA4.unk88 = 0x30;
        self->step_s = 0;
        return;

    case 1:
        UnkCollisionFunc2(&D_us_801822DC);
        self->velocityX =
            rsin(self->ext.et_801D5BA4.unk84) * self->ext.et_801D5BA4.unk88;
        self->velocityY =
            -rcos(self->ext.et_801D5BA4.unk84) * self->ext.et_801D5BA4.unk88;
        if (self->ext.et_801D5BA4.unk88 > 12) {
            self->ext.et_801D5BA4.unk88 -= 2;
        }
        switch (self->step_s) {
        case 0:
            self->scaleX += 8;
            self->scaleY += 0x10;
            if (self->scaleX == 0x100) {
                self->scaleY = 0x100;
                self->ext.et_801D5BA4.unk88 = 4;
                self->hitboxState = 0;
                self->step_s += 1;
                return;
            }
            break;

        case 1:
            self->scaleX += 8;
            self->scaleY += 8;
            self->opacity -= 2;
            if (!self->opacity) {
                DestroyEntity(self);
            }
        }
    }
}
