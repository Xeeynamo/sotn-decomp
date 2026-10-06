// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <psyz/module.h>
#include "overlay.h"
#include "../spawn_point.h"

static const char* OverlayPath(const char* name, char* buf, int len) {
    (void)buf;
    (void)len;
    return name;
}

// Psyz_ModuleOpen calls the overlay's Psyz_ModuleStart, which fills 'o'
static bool LoadOverlay(PsyzModule* current, const char* name, void* o) {
    char path[160];
    if (*current) {
        Psyz_ModuleClose(*current);
        *current = 0;
    }
    *current = Psyz_ModuleOpen(OverlayPath(name, path, sizeof(path)), o);
    if (!*current) {
        ERRORF("failed to load overlay '%s'", name);
        return false;
    }
    INFOF("loaded overlay '%s'", name);
    return true;
}

static PsyzModule CurrentStageOverlay;
bool LoadStageOverlay(const char* name, Overlay* o) {
    if (!LoadOverlay(&CurrentStageOverlay, name, o)) {
        return false;
    }
    SpawnPoint_HookOverlay(o);
    return true;
}

static PsyzModule CurrentServantOverlay;
bool LoadServantOverlay(const char* name, ServantDesc* o) {
    return LoadOverlay(&CurrentServantOverlay, name, o);
}

static PsyzModule CurrentWeaponOverlay[2];
bool LoadWeaponOverlay(const char* name, unsigned handId, Weapon* o) {
    if (handId >= LEN(CurrentWeaponOverlay)) {
        ERRORF("hand ID %d not valid", handId);
        return false;
    }
    return LoadOverlay(&CurrentWeaponOverlay[handId], name, o);
}
