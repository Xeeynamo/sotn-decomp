// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include <cutscene.h>

#ifdef VERSION_PSP

u8 cutscene_data_it[] = {
#include "gen/cutscene_data_it.h"
};

u8 cutscene_data_sp[] = {
#include "gen/cutscene_data_sp.h"
};

u8 cutscene_data_fr[] = {
#include "gen/cutscene_data_fr.h"
};

u8 cutscene_data_ge[] = {
#include "gen/cutscene_data_ge.h"
};

u8 cutscene_data_en[] = {
#include "gen/cutscene_data_en.h"
};

#else
u8 OVL_EXPORT(cutscene_data)[] = {
#include "gen/cutscene_data.h"
};

#endif

static u8 unused[] UNUSED = {
    32, 88, 8, 128, 8, 128, 0, 0, 0, 33, 90, 10, 160, 7, 120, 255, 255, 0};
