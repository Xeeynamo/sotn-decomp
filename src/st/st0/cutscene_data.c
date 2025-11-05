// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include <cutscene.h>

#ifdef VERSION_PSP
u8 cutscene_script_it[] = {
#include "gen/cutscene_script_it.h"
};

u8 cutscene_script_sp[] = {
#include "gen/cutscene_script_sp.h"
};

u8 cutscene_script_fr[] = {
#include "gen/cutscene_script_fr.h"
};

u8 cutscene_script_ge[] = {
#include "gen/cutscene_script_ge.h"
};

u8 cutscene_script_en[] = {
#include "gen/cutscene_script_en.h"
};
#else
u8 OVL_EXPORT(cutscene_script)[] = {
#include "gen/cutscene_script_psx.h"
};
#endif
