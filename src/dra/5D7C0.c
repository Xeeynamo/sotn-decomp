#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

u32 CheckEquipmentItemCount(u32 itemId, u32 equipType) {
    if (equipType < 5) {
        switch (equipType) {
        case 0:
            return (g_playerEquip[0] == itemId) + (g_playerEquip[1] == itemId);
        case 1:
            return g_playerEquip[2] == itemId;
        case 2:
            return g_playerEquip[3] == itemId;
        case 3:
            return g_playerEquip[4] == itemId;
        case 4:
            return (g_playerEquip[5] == itemId) + (g_playerEquip[6] == itemId);
        }
    }
    // seems to require missing return
}

// fix missing padding at end of jump table. ASPSX issue?
const u32 rodataPadding_800DCBD8 = 0;
