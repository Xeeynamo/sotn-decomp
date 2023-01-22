#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

u32 CheckEquipmentItemCount(u32 itemId, u32 equipType) {
    if (equipType < 5) {
        switch (equipType) {
        case 0:
            return (player_equip_head[0] == itemId) +
                   (player_equip_body == itemId);
        case 1:
            return player_equip_cloak == itemId;
        case 2:
            return player_equip_ring1 == itemId;
        case 3:
            return player_equip_ring2 == itemId;
        case 4:
            return (D_80097C14 == itemId) + (D_80097C18 == itemId);
        }
    }
    // seems to require missing return
}

// fix missing padding at end of jump table. ASPSX issue?
const u32 rodataPadding_800DCBD8 = 0;
