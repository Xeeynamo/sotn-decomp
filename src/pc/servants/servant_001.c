// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../servant/tt_001/ghost.h"
#include "../../pc/stages/overlay.h"
#include <string.h>

extern ServantDesc ghost_ServantDesc;
OVL_API void InitServant(ServantDesc* o) {
    memcpy(o, &ghost_ServantDesc, sizeof(ServantDesc));
}
