// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../sattypes.h"
#include <saturn_player.h>
#include <saturn_sprite.h>

static void NullInit(u16 params) {}
static void NullCallback(void) {}
static void NullSensor(Collider* collider) {}
static void NullDisableAfterImage(s32 resetAnims, s32 arg1) {}
static void NullInvincibility(s32 kind, s16 frames) {}
static Entity* NullFactory(Entity* source, u32 params, s32 arg2) {
    return NULL;
}
static void NullEntity(Entity* entity) {}

extern void* g_MariaSpriteBanks[];
extern SaturnPlayerGraphicsRecord g_MariaPlayerGraphicsRecords[];

SaturnPlayerOvl g_NullPlayer = {
    NullInit,
    NullCallback,
    NullCallback,
    NullCallback,
    NullCallback,
    NullSensor,
    NullDisableAfterImage,
    NullInvincibility,
    NullCallback,
    NullCallback,
    NullFactory,
    NullCallback,
    NullEntity,
    NullCallback,
    NullCallback,
    (u8*)g_MariaSpriteBanks,
    g_MariaPlayerGraphicsRecords,
};

void (*g_MariaMapMenuFunctions[19])(void);
