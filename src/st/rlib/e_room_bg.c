// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

static u8 AnimFrames_801806C4[] = {0x40, 0x01, 0xFF, 0x00};
static u8 AnimFrames_801806C8[] = {0x40, 0x01, 0xFF, 0x00};
static u8 AnimFrames_801806CC[] = {0x40, 0x19, 0xFF, 0x00};
static u8 AnimFrames_801806D0[] = {
    0x04, 0x1A, 0x04, 0x1B, 0x04, 0x1C, 0x04, 0x1D, 0x04, 0x1E, 0x00, 0x00};
static u8 AnimFrames_801806DC[] = {
    0x03, 0x1F, 0x03, 0x20, 0x03, 0x21, 0x03, 0x20, 0x00, 0x00, 0x00, 0x00};
static u8 AnimFrames_801806E8[] = {0x40, 0x22, 0xFF, 0x00};
static u8 AnimFrames_801806EC[] = {0x40, 0x13, 0xFF, 0x00};
static u8 AnimFrames_801806F0[] = {0x40, 0x14, 0xFF, 0x00};

ObjInit2 BackgroundBlockInit[] = {
    {.animSet = ANIMSET_DRA(6),
     .zPriority = 0x1FA,
     .facingLeft = 0,
     .unk5A = 0,
     .palette = PAL_NULL,
     .drawFlags = ENTITY_DEFAULT,
     .blendMode = BLEND_TRANSP,
     .flags = 0,
     .animFrames = AnimFrames_801806C4},
    {.animSet = ANIMSET_OVL(8),
     .zPriority = 0x078,
     .facingLeft = 0x48,
     .unk5A = 0,
     .palette = 0x220,
     .drawFlags = ENTITY_ROTATE,
     .blendMode = BLEND_NO,
     .flags = 0,
     .animFrames = AnimFrames_801806C8},
    {.animSet = ANIMSET_OVL(8),
     .zPriority = 0x078,
     .facingLeft = 0x48,
     .unk5A = 0,
     .palette = 0x220,
     .drawFlags = ENTITY_ROTATE,
     .blendMode = BLEND_NO,
     .flags = 0,
     .animFrames = AnimFrames_801806CC},
    {.animSet = ANIMSET_OVL(8),
     .zPriority = 0x078,
     .facingLeft = 0x48,
     .unk5A = 0,
     .palette = 0x220,
     .drawFlags = ENTITY_DEFAULT,
     .blendMode = BLEND_TRANSP | BLEND_ADD,
     .flags = 0,
     .animFrames = AnimFrames_801806D0},
    {.animSet = ANIMSET_OVL(8),
     .zPriority = 0x078,
     .facingLeft = 0x48,
     .unk5A = 0,
     .palette = 0x220,
     .drawFlags = ENTITY_DEFAULT,
     .blendMode = BLEND_TRANSP | BLEND_ADD,
     .flags = 0,
     .animFrames = AnimFrames_801806DC},
    {.animSet = ANIMSET_OVL(8),
     .zPriority = 0x077,
     .facingLeft = 0x48,
     .unk5A = 0,
     .palette = 0x220,
     .drawFlags = ENTITY_DEFAULT,
     .blendMode = BLEND_TRANSP | BLEND_ADD,
     .flags = 0,
     .animFrames = AnimFrames_801806E8},
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x06C,
     .facingLeft = 0,
     .unk5A = 0,
     .palette = PAL_NULL,
     .drawFlags = ENTITY_DEFAULT,
     .blendMode = BLEND_NO,
     .flags = 0,
     .animFrames = AnimFrames_801806EC},
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x06C,
     .facingLeft = 0,
     .unk5A = 0,
     .palette = PAL_NULL,
     .drawFlags = ENTITY_DEFAULT,
     .blendMode = BLEND_NO,
     .flags = 0,
     .animFrames = AnimFrames_801806F0},
};

// The inverted castle draws its background blocks upside down.
#define BG_BLOCK_ROTATE_180
#include "../e_room_bg.h"
