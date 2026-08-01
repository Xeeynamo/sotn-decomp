// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage16SpriteBank26;

void func_060E7ED0(Entity* self);
void func_060E7FC4(Entity* self);
void func_060E86BC(Entity* self);
void func_060E8AC0(Entity* self);
void func_060E887C(Entity* self);

EntityEntry g_Stage16EntityWillOWisp = {&g_Stage16SpriteBank26, func_060E7ED0};
EntityEntry g_Stage16EntityEntry40 = {&g_Stage16SpriteBank26, func_060E7FC4};
EntityEntry g_Stage16EntityEntry41 = {NULL, func_060E86BC};
EntityEntry g_Stage16EntityEntry42 = {NULL, func_060E8AC0};
EntityEntry g_Stage16EntityEntry43 = {NULL, func_060E887C};
