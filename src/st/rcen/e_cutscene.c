// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcen.h"
#include <cutscene.h>

extern u32 D_801BC3E8;
extern s32 D_801D6B00;
extern Dialogue OVL_EXPORT(Dialogue);
extern s32 OVL_EXPORT(SkipCutscene);

#include "../cutscene_unk1.h"

#include "../set_cutscene_script.h"

#include "../cutscene_unk3.h"

#include "../cutscene_unk4.h"

#include "../cutscene_actor_name.h"

#include "../set_cutscene_end.h"

#define CUTSCENE_TILEMAP_SCROLL
#include "../cutscene_run.h"

#include "../cutscene_skip.h"

#include "../cutscene_scale_avatar.h"

INCLUDE_RODATA("st/rcen/nonmatchings/e_cutscene", D_us_8019A08C);

INCLUDE_RODATA("st/rcen/nonmatchings/e_cutscene", D_us_8019A094);

INCLUDE_ASM("st/rcen/nonmatchings/e_cutscene", RCEN_EntityCutscene);
