// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include "../../servant/tt_004/sword.h"
#include "../../pc/stages/overlay.h"
#include <string.h>

extern ServantDesc sword_ServantDesc;
void Psyz_ModuleStart(void* param) {
    ServantDesc* o = param;
    memcpy(o, &sword_ServantDesc, sizeof(ServantDesc));
}

void Psyz_ModuleStop(void) {}
