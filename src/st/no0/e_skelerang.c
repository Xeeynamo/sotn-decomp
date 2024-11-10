// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/e_skelerang", func_us_801D191C);

INCLUDE_ASM("st/no0/nonmatchings/e_skelerang", func_us_801D20A4);

void func_us_801D2318(Entity* entity) {
    Entity* parent;
    if (!entity->step) {
        InitializeEntity(g_EInitInteractable);
    }
    parent = entity - 1;
    if (parent->entityId != 0x2E) {
        DestroyEntity(entity);
    }
}
