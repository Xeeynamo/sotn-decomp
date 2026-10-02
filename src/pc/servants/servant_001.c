// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include "../../servant/tt_001/ghost.h"
#include "../../pc/stages/overlay.h"
#include <string.h>

extern ServantDesc ghost_ServantDesc;
void Psyz_ModuleStart(void* param) {
    ServantDesc* o = param;
    memcpy(o, &ghost_ServantDesc, sizeof(ServantDesc));
}

void Psyz_ModuleStop(void) {}
