// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcen.h"
#include <cutscene.h>

#ifdef VERSION_PSP
u8 cutscene_script_pre_fight_it[] = {
#include <gen/cutscene_script_pre_fight_it.h>
};
u8 cutscene_script_pre_fight_sp[] = {
#include <gen/cutscene_script_pre_fight_sp.h>
};
u8 cutscene_script_pre_fight_fr[] = {
#include <gen/cutscene_script_pre_fight_fr.h>
};
u8 cutscene_script_pre_fight_ge[] = {
#include <gen/cutscene_script_pre_fight_ge.h>
};
u8 cutscene_script_pre_fight_en[] = {
#include <gen/cutscene_script_pre_fight_en.h>
};

u8 cutscene_script_post_fight_it[] = {
#include <gen/cutscene_script_post_fight_it.h>
};
u8 cutscene_script_post_fight_sp[] = {
#include <gen/cutscene_script_post_fight_sp.h>
};
u8 cutscene_script_post_fight_fr[] = {
#include <gen/cutscene_script_post_fight_fr.h>
};
u8 cutscene_script_post_fight_ge[] = {
#include <gen/cutscene_script_post_fight_ge.h>
};
u8 cutscene_script_post_fight_en[] = {
#include <gen/cutscene_script_post_fight_en.h>
};
#else
// Not really clear what this belongs to. Maybe it's e_layout data
STATIC_PAD_DATA(4);

u8 cutscene_script[] = {
#include <gen/cutscene_script_psx.h>
#include <gen/cutscene_events.h>
};
#endif
