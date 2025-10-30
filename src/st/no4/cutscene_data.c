// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"
#include <cutscene.h>

#ifdef VERSION_PSP
// Played when the ferryman takes the player right across the river
u8 cutscene_data_ferryman_right_it[] = {
#include "gen/cutscene_data_ferryman_right_it.h"
};

u8 cutscene_data_ferryman_right_sp[] = {
#include "gen/cutscene_data_ferryman_right_sp.h"
};

u8 cutscene_data_ferryman_right_fr[] = {
#include "gen/cutscene_data_ferryman_right_fr.h"
};

u8 cutscene_data_ferryman_right_ge[] = {
#include "gen/cutscene_data_ferryman_right_ge.h"
};

u8 cutscene_data_ferryman_right_en[] = {
#include "gen/cutscene_data_ferryman_right_en.h"
};

// Played when the ferryman takes the player left across the river
u8 cutscene_data_ferryman_left_it[] = {
#include "gen/cutscene_data_ferryman_left_it.h"
};

u8 cutscene_data_ferryman_left_sp[] = {
#include "gen/cutscene_data_ferryman_left_sp.h"
};

u8 cutscene_data_ferryman_left_fr[] = {
#include "gen/cutscene_data_ferryman_left_fr.h"
};

u8 cutscene_data_ferryman_left_ge[] = {
#include "gen/cutscene_data_ferryman_left_ge.h"
};

u8 cutscene_data_ferryman_left_en[] = {
#include "gen/cutscene_data_ferryman_left_en.h"
};
#else
// The ferryman_right script starts one byte to the left of alignment, so having
// it as a second variable results in a byte of padding that breaks the match.
u8 cutscene_data_ferryman_left[] = {
#include "gen/cutscene_data_ferryman_left_psx.h"
#include "gen/cutscene_data_ferryman_right_psx.h"
};
#endif
