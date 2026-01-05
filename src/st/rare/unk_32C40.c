// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

INCLUDE_ASM("st/rare/nonmatchings/unk_32C40", func_us_801B2C40);

INCLUDE_ASM("st/rare/nonmatchings/unk_32C40", func_us_801B30A8);

INCLUDE_ASM("st/rare/nonmatchings/unk_32C40", func_us_801B33F4);

void func_us_801B3938(u16* target) {
    ET_RareUnk20* self = &g_CurrentEntity->ext.rareUnk20;

    self->offsetX = target[0] - self->posX;
    self->offsetY = target[1] - self->posY;
    self->offsetZ = target[2] - self->posZ;
    self->baseX = self->posX;
    self->baseY = self->posY;
    self->baseZ = self->posZ;
}

void func_us_801B398C(void) {
    ET_RareUnk20* self = &g_CurrentEntity->ext.rareUnk20;
    s32 t = self->lerpT;

    self->posX = self->baseX + (self->offsetX * t) / 4096;
    self->posY = self->baseY + (self->offsetY * t) / 4096;
    self->posZ = self->baseZ + (self->offsetZ * t) / 4096;
}

INCLUDE_ASM("st/rare/nonmatchings/unk_32C40", func_us_801B3A1C);

INCLUDE_ASM("st/rare/nonmatchings/unk_32C40", func_us_801B3B34);

INCLUDE_ASM("st/rare/nonmatchings/unk_32C40", func_us_801B4E9C);
