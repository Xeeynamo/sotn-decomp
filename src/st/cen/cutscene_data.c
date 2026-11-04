// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

#if VERSION >= VER_JP10

#include <cutscene.h>

u8 cutscene_data[] = {
#include <gen/cutscene_data.h>
};

#endif
