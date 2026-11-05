// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include "../../servant/tt_006/nosedevil.h"
#include "../../pc/stages/overlay.h"
#include <string.h>

extern ServantDesc nosedevil_ServantDesc;
void Psyz_ModuleStart(void* param) {
    ServantDesc* o = param;
    memcpy(o, &nosedevil_ServantDesc, sizeof(ServantDesc));
}

void Psyz_ModuleStop(void) {}
