// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include "../../servant/tt_000/bat.h"
#include "../stages/overlay.h"
#include <string.h>

extern ServantDesc bat_ServantDesc;
void Psyz_ModuleStart(void* param) {
    ServantDesc* o = param;
    memcpy(o, &bat_ServantDesc, sizeof(ServantDesc));
}

void Psyz_ModuleStop(void) {}
