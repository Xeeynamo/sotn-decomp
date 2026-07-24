// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

void func_060DC040(Entity* self);
void EntityRedEyeBust(Entity* self);
void func_060DC4EC(Entity* self);
void func_060DC510(Entity* self);
void func_060DC7B4(Entity* self);
void func_060DCA54(Entity* self);
void func_060DCCD4(Entity* self);
void func_060DCFA4(Entity* self);
void func_060DD20C(Entity* self);
void func_060DD3E8(Entity* self);
void func_060DD690(Entity* self);
void func_060DD790(Entity* self);
void func_060DD8D8(Entity* self);
void func_060DDB80(Entity* self);

extern SaturnSpriteResource entityRedEyeBustData;

EntityEntry g_Stage02EntityEntry00 = {NULL, func_060DC040};
EntityEntry g_Stage02EntityEntry34 = {&entityRedEyeBustData, EntityRedEyeBust};
EntityEntry g_Stage02EntityEntry16 = {NULL, func_060DC4EC};
EntityEntry g_Stage02EntityEntry35 = {&entityRedEyeBustData, func_060DC510};
EntityEntry g_Stage02EntityEntry36 = {&entityRedEyeBustData, func_060DC7B4};

u32 g_Stage02EntityEntryPadding0 = 0;

EntityEntry g_Stage02EntityEntry24 = {&entityRedEyeBustData, func_060DCA54};
EntityEntry g_Stage02EntityEntry25 = {&entityRedEyeBustData, func_060DCCD4};
EntityEntry g_Stage02EntityEntry26 = {&entityRedEyeBustData, func_060DCFA4};

u32 g_Stage02EntityParameters0[3] = {0x10, 0x00100000, 0};

EntityEntry g_Stage02EntityEntry27 = {&entityRedEyeBustData, func_060DD20C};
EntityEntry g_Stage02EntityEntry28 = {&entityRedEyeBustData, func_060DD3E8};
EntityEntry g_Stage02EntityEntry29 = {&entityRedEyeBustData, func_060DD690};
EntityEntry g_Stage02EntityEntry30 = {&entityRedEyeBustData, func_060DD790};

u32 g_Stage02EntityEntryPadding1 = 0;

EntityEntry g_Stage02EntityEntry31 = {&entityRedEyeBustData, func_060DD8D8};
EntityEntry g_Stage02EntityEntry32 = {&entityRedEyeBustData, func_060DDB80};
