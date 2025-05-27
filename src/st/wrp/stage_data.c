// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

u8 stage_title_jp[] = {
#include "gen/stage_title_jp.h"
};
u8 stage_placeholder[] = {
#include "gen/stage_placeholder.h"
};
u16 D_80181D08[] = {
#include "gen/D_80181D08.h"
};
u16 D_80181D28[] = {
#include "gen/D_80181D28.h"
};

#if defined(VERSION_US)
#include "gen/tilemap_01D68.h"
#include "gen/tilemap_01F68.h"
#include "gen/tilemap_02168.h"
#include "gen/tilemap_02368.h"
#include "gen/tilemap_02568.h"
#include "gen/tilemap_02768.h"
#include "gen/tiledef_02D68.h"
#include "gen/tiledef_06D78.h"

#elif defined(VERSION_HD)
#include "gen/tilemap_01D6C.h"
#include "gen/tilemap_01F6C.h"
#include "gen/tilemap_0216C.h"
#include "gen/tilemap_0236C.h"
#include "gen/tilemap_0256C.h"
#include "gen/tilemap_0276C.h"
#include "gen/tiledef_02D6C.h"
#include "gen/tiledef_06D7C.h"

#endif
