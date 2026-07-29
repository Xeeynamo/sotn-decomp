// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060E3F58(Entity* self);
void func_060E4064(Entity* self);

EntityEntry g_Stage15EntityEntry14 = {
    &g_SaturnSharedSpriteBank8Resource, func_060E3F58};

u32 g_Stage15Entity14Parameters[2] = {8, 0xB0};

u16 g_Stage15Entity14Animation[16] = {
    0x0000, 0x00A2, 0x0081, 0x0481, 0x0461, 0x0861, 0x0861, 0x0C41,
    0x0C41, 0x1041, 0x1021, 0x1421, 0x1421, 0x1801, 0x1801, 0x1C01,
};

EntityEntry g_Stage15EntityEntry08 = {NULL, func_060E4064};
