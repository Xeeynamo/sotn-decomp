// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"
#include <cutscene.h>

#ifndef VERSION_PSP
u8 cutscene_script[] = {
#include <gen/cutscene_script_psx.h>
#include <gen/cutscene_events.h>
};
#endif
