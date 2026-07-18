// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../servant/tt_000/bat.h"
#include "../stages/overlay.h"
#include <string.h>

extern ServantDesc bat_ServantDesc;
OVL_API void InitServant(ServantDesc* o) {
    memcpy(o, &bat_ServantDesc, sizeof(ServantDesc));
}
