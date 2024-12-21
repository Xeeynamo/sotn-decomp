// SPDX-License-Identifier: AGPL-3.0-or-later
#include "pc.h"
#include "servant.h"
#include <string.h>

extern ServantDesc bat_ServantDesc;
extern ServantDesc ghost_ServantDesc;
extern ServantDesc faerie_ServantDesc;
extern ServantDesc g_ServantDesc;

// To add a new servant, replace proper null with it's servant desc
ServantDesc* servantDescs[] = {
    NULL, &bat_ServantDesc, &ghost_ServantDesc, &faerie_ServantDesc, NULL, NULL,
    NULL};

void HandleServantPrg() { g_ServantDesc = *servantDescs[g_Servant]; }

void HandleServantChr() {
    char smolbuf[48];
    snprintf(smolbuf, sizeof(smolbuf), "disks/us/SERVANT/FT_00%d.BIN",
             g_Servant - 1);
    u8 temp[0x6000];
    FileReadToBuf(smolbuf, &temp, 0, 0x6000);
    LoadTPage(&temp, 0, 0, 0x2C0, 0x100, 0x100, 0x80);
    LoadTPage(&temp[0x4000], 0, 0, 0x2C0, 0x180, 0x80, 0x80);
}
