// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "warp.h"

EntityEntry* g_WarpEntityUpdates[] = {
    &g_EntityNoopEntry,         &g_WarpExplosionEntry,
    &g_WarpPrizeDropEntry,      &g_WarpDamageDisplayEntry,
    &g_WarpRedDoorEntry,        &g_WarpIntenseExplosionEntry,
    &g_WarpSoulStealOrbEntry,   &g_EntityNoopEntry,
    &g_WarpStageNamePopupEntry, &g_WarpEquipItemDropEntry,
    &g_WarpRelicOrbEntry,       &g_WarpHeartDropEntry,
    &g_WarpEnemyBloodEntry,     &g_WarpMessageBoxEntry,
    &g_WarpDummyEntry,          &g_EntityNoopEntry,
    &g_EntityNoopEntry,         &g_EntityNoopEntry,
    &g_WarpUnkId13Entry,        &g_WarpExplosionVariantsEntry,
    &g_WarpGreyPuffEntry,       &g_WarpRoomEntry,
    &g_WarpSmallRocksEntry,     NULL,
};
