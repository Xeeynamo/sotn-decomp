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

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_801A2848);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_801A2A58);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_801A2C9C);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", Entity3DHouseSpawner);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", Entity3DBackgroundHouse);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B4DA4);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B52B4);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B5368);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B5578);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B56A4);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B5750);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B5948);

INCLUDE_RODATA("st/no2/nonmatchings/33D8C", D_us_801B2E20);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B59C4);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B5FB8);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B65A4);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B6794);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B68EC);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B6E34);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B72E8);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B7580);
