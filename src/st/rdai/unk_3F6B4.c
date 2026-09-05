// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

#include "../e_spear_guard_collision.h"

#include "../approach_s16.h"

INCLUDE_ASM("st/rdai/nonmatchings/unk_3F6B4", func_us_801BF830);

// Child parts share one implementation; only the fixed EInit address is local.
#include "../e_rdai_unk1f.h"

#include "../e_rdai_archer.h"

INCLUDE_ASM("st/rdai/nonmatchings/unk_3F6B4", func_us_801C0240);

INCLUDE_ASM("st/rdai/nonmatchings/unk_3F6B4", func_us_801C0528);

INCLUDE_ASM("st/rdai/nonmatchings/unk_3F6B4", func_us_801C0898);
