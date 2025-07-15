// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B3D8C);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B3F30);

void EntityFrozenShadeCrystal(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 1;
        self->zPriority = 0xA0;
    }
}

void func_us_801B41A4(void) {
    if (g_CurrentEntity->step == 0) {
        g_CurrentEntity->step += 1;
    }
    g_GpuBuffers[0].draw.r0 = 0x20;
    g_GpuBuffers[0].draw.g0 = 0x18;
    g_GpuBuffers[0].draw.b0 = 0x28;
    g_GpuBuffers[1].draw.r0 = 0x20;
    g_GpuBuffers[1].draw.g0 = 0x18;
    g_GpuBuffers[1].draw.b0 = 0x28;
}

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B4210);
