// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

// This is data that psx requires for a match, but it is not currently known
// what this data actually is. While it appears unused, it has not been
// confirmed that it is actually unused.
u8 unk_data_psx[] = {
#include "gen/unk_data_psx.h"
};
