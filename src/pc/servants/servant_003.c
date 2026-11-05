// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include "../../servant/tt_003/demon.h"
#include "../../pc/stages/overlay.h"
#include <string.h>

extern ServantDesc demon_ServantDesc;
void Psyz_ModuleStart(void* param) {
    ServantDesc* o = param;
    memcpy(o, &demon_ServantDesc, sizeof(ServantDesc));
}

void Psyz_ModuleStop(void) {}
