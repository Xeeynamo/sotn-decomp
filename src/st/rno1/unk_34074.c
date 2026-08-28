// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

extern EInit g_EInitParanthropusThrownBone;
extern EInit g_EInitParanthropusBoneHitbox;
extern EInit g_EInitInteractable;

extern Point16 bone_hitbox_offsets[];
extern Size16 bone_hitbox_dimensions[];
extern Point16 skull_positions[];

#include "../e_paranthropus_steps.h"

INCLUDE_ASM("st/rno1/nonmatchings/unk_34074", EntityParanthropus);

#include "../e_paranthropus_parts.h"
