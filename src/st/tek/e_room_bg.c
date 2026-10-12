// SPDX-License-Identifier: AGPL-3.0-or-later
#include "tek.h"

extern EInit g_EInitCommon;

// TEK stores every field of the background block in its own table
static u16 g_animSet[] = {6, 0};
static u8 g_anim[] = {0x40, 1, 0xFF, 0};
static u16 g_zPriority[] = {0x1FA, 0x40, 0x9E, 0x9E, 0x80, 0};
static u16 g_unk5A[12] = {0};
static u16 g_palette[12] = {0};
static u16 g_drawFlags[12] = {0};
static u16 g_blendMode[] = {0x10, 0, 0, 0, 0, 0, 0x10, 0};
static u32 g_flags[11] = {0};
static u32 g_facingLeft[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
static u8* g_animFrames[] = {g_anim};

void EntityBackgroundBlock(Entity* self) {
    u16 params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = g_animSet[params];
        self->zPriority = g_zPriority[params];
        self->unk5A = g_unk5A[params];
        self->palette = g_palette[params];
        self->drawFlags = g_drawFlags[params];
        self->blendMode = g_blendMode[params];
        if (g_flags[params]) {
            self->flags = g_flags[params];
        }
        self->facingLeft = g_facingLeft[params];
    }
    AnimateEntity(g_animFrames[params], self);
}
