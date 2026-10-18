// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;

#ifdef VERSION_PSP
#define CUTSCENE_UNK1_NEXT_X 0
#define CUTSCENE_UNK1_UNK17 2

#include "../../get_lang.h"

#include "../../st/cutscene_actor_name.h"

#include "../../st/cutscene_unk3.h"

#include "../../st/cutscene_unk4.h"

#include "../../st/cutscene_unk1.h"

#include "../../st/set_cutscene_script.h"

#include "../../st/set_cutscene_events.h"

#define CUTSCENE_WAIT_FOR_FLAG_REWIND
#include "../../st/cutscene_events.h"
#else
static const char* actor_names[] = {_S("Alucard"), _S("Maria")};

#include "../../st/cutscene_unk1.h"

#include "../../st/set_cutscene_script.h"

#include "../../st/cutscene_unk3.h"

#include "../../st/cutscene_unk4.h"

#include "../../st/cutscene_actor_name.h"

#include "../../st/set_cutscene_events.h"

#define CUTSCENE_WAIT_FOR_FLAG_REWIND
#include "../../st/cutscene_events.h"

#include "../../st/cutscene_scale_avatar.h"
#endif

INCLUDE_ASM("boss/bo5/nonmatchings/e_cutscene_dialogue", EntityCutscene);
