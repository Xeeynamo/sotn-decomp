// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo2.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;
extern const char* actor_names[];

#include "../../st/cutscene_unk1.h"

#include "../../st/set_cutscene_script.h"

#include "../../st/cutscene_unk3.h"

#include "../../st/cutscene_unk4.h"

#include "../../st/cutscene_actor_name.h"

#include "../../st/set_cutscene_events.h"

#define CUTSCENE_TILEMAP_SCROLL
#include "../../st/cutscene_events.h"

#include "../../st/cutscene_scale_avatar.h"

INCLUDE_RODATA("boss/rbo2/nonmatchings/e_cutscene_dialogue", D_us_8019AE04);

INCLUDE_RODATA("boss/rbo2/nonmatchings/e_cutscene_dialogue", D_us_8019AE0C);

INCLUDE_ASM("boss/rbo2/nonmatchings/e_cutscene_dialogue", EntityCutsceneDialogue);
