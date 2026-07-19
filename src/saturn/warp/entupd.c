// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

extern EntityEntry g_EntityNoopEntry;
extern EntityEntry g_WarpExplosionEntry;
extern EntityEntry g_WarpPrizeDropEntry;
extern EntityEntry g_WarpDamageDisplayEntry;
extern EntityEntry g_WarpRedDoorEntry;
extern EntityEntry g_WarpIntenseExplosionEntry;
extern EntityEntry g_WarpSoulStealOrbEntry;
extern EntityEntry g_WarpStageNamePopupEntry;
extern EntityEntry g_WarpEquipItemDropEntry;
extern EntityEntry g_WarpRelicOrbEntry;
extern EntityEntry g_WarpHeartDropEntry;
extern EntityEntry g_WarpEnemyBloodEntry;
extern EntityEntry g_WarpMessageBoxEntry;
extern EntityEntry g_WarpDummyEntry;
extern EntityEntry g_WarpUnkId13Entry;
extern EntityEntry g_WarpExplosionVariantsEntry;
extern EntityEntry g_WarpGreyPuffEntry;
extern EntityEntry g_WarpRoomEntry;
extern EntityEntry g_WarpSmallRocksEntry;

EntityEntry* g_WarpEntityUpdates[] = {
    &g_EntityNoopEntry,
    &g_WarpExplosionEntry,
    &g_WarpPrizeDropEntry,
    &g_WarpDamageDisplayEntry,
    &g_WarpRedDoorEntry,
    &g_WarpIntenseExplosionEntry,
    &g_WarpSoulStealOrbEntry,
    &g_EntityNoopEntry,
    &g_WarpStageNamePopupEntry,
    &g_WarpEquipItemDropEntry,
    &g_WarpRelicOrbEntry,
    &g_WarpHeartDropEntry,
    &g_WarpEnemyBloodEntry,
    &g_WarpMessageBoxEntry,
    &g_WarpDummyEntry,
    &g_EntityNoopEntry,
    &g_EntityNoopEntry,
    &g_EntityNoopEntry,
    &g_WarpUnkId13Entry,
    &g_WarpExplosionVariantsEntry,
    &g_WarpGreyPuffEntry,
    &g_WarpRoomEntry,
    &g_WarpSmallRocksEntry,
    NULL,
};
