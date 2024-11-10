// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/e_skelerang", func_us_801D191C);

INCLUDE_ASM("st/no0/nonmatchings/e_skelerang", func_us_801D20A4);

extern u16 g_EInitInteractable[];

void func_us_801D2318(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(g_EInitInteractable);
    }
    if ((entity - 1)->entityId != 0x2E) {
        DestroyEntity(entity);
    }
}
