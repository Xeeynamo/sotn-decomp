// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_RStage15SpriteBank27;

void func_060EA600(Entity* self);
void func_060EAE6C(Entity* self);
void func_060EAFF8(Entity* self);
void func_060EB150(Entity* self);

EntityEntry g_RStage15EntityCopperArmor = {
    &g_RStage15SpriteBank27, func_060EA600};
s16 g_RStage15CopperArmorInitOffset[2] = {0, 28};

EntityEntry g_RStage15EntityEntry52 = {&g_RStage15SpriteBank27, func_060EAE6C};
s16 g_RStage15CopperArmorWeaponInitOffset[2] = {0, 28};

EntityEntry g_RStage15EntityEntry54 = {&g_RStage15SpriteBank27, func_060EAFF8};
s16 g_RStage15CopperArmorShieldInitOffset[2] = {0, 28};

EntityEntry g_RStage15EntityEntry53 = {&g_RStage15SpriteBank27, func_060EB150};

u8 g_RStage15CopperArmorDeathAnim[10] = {
    4, 3, 4, 4, 4, 5, 4, 6, 0xFF, 0xFF,
};
u16 g_RStage15CopperArmorDeathAnimPadding = 0;
u8* g_RStage15CopperArmorAnimations[] = {
    g_RStage15CopperArmorDeathAnim,
};
