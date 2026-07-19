// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060E6B00(Entity* self);
void func_060E6C0C(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank08[];

EntityEntry g_Stage02EntityEntry14 = {
    g_Stage02SpriteBank08, func_060E6B00};

u16 g_Stage02Entity14Animation[16] = {
    0x0000, 0x00A2, 0x0081, 0x0481, 0x0461, 0x0861, 0x0861, 0x0C41,
    0x0C41, 0x1041, 0x1021, 0x1421, 0x1421, 0x1801, 0x1801, 0x1C01,
};

EntityEntry g_Stage02EntityEntry08 = {NULL, func_060E6C0C};
