// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../servant/tt_002/faerie.h"
#include "../../pc/stages/overlay.h"
#include <string.h>

extern ServantDesc faerie_ServantDesc;
OVL_API void InitServant(ServantDesc* o) {
    memcpy(o, &faerie_ServantDesc, sizeof(ServantDesc));
}
