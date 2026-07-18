// SPDX-License-Identifier: AGPL-3.0-or-later
#include "pc.h"
#include "servant.h"
#include "stages/overlay.h"
#include <string.h>

static const char* ovlNames[] = {
    NULL, "tt_000", "tt_001", "tt_002", "tt_003", "tt_004", "tt_005", "tt_006"};

void HandleServantPrg() {
    if (g_Servant == 0) {
        return;
    }
    if (g_Servant >= LEN(ovlNames)) {
        ERRORF("servant %d not valid", g_Servant);
        return;
    }
    const char* name = ovlNames[g_Servant];
    if (!name) {
        ERRORF("servant %d has no overlay", g_Servant);
        return;
    }
    if (!LoadServantOverlay(name, &g_ServantDesc)) {
        ERRORF("servant '%s' was not loaded", name);
    }
}

void HandleServantChr() {
    if (g_Servant == 0) {
        return;
    }
    char smolbuf[48];
    snprintf(smolbuf, sizeof(smolbuf), "disks/us/SERVANT/FT_00%d.BIN",
             g_Servant - 1);
    u8 temp[0x6000];
    FileReadToBuf(smolbuf, &temp, 0, 0x6000);
    LoadTPage(&temp, 0, 0, 0x2C0, 0x100, 0x100, 0x80);
    LoadTPage(&temp[0x4000], 0, 0, 0x2C0, 0x180, 0x80, 0x80);
}
