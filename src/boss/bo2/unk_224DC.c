// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo2.h"

extern u8* g_eBreakableAnimations[];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 blend_modes[];

#include "../../st/e_breakable.h"

INCLUDE_ASM("boss/bo2/nonmatchings/unk_224DC", func_us_801A2610);

INCLUDE_ASM("boss/bo2/nonmatchings/unk_224DC", func_us_801A269C);

#include "e_minotaur.h"

INCLUDE_ASM("boss/bo2/nonmatchings/unk_224DC", func_us_801A3E04);

INCLUDE_ASM("boss/bo2/nonmatchings/unk_224DC", func_us_801A460C);

#include "e_unk_29.h"

INCLUDE_ASM("boss/bo2/nonmatchings/unk_224DC", EntityBossTorch);

INCLUDE_ASM("boss/bo2/nonmatchings/unk_224DC", EntityBossDoors);
