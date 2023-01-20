#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

u32 func_800FD7C0(u32 itemNum, u32 compareType) {
    if (compareType < 5) {
        switch (compareType) {
        case 0:
            return (player_equip_head[0] == itemNum) +
                   (player_equip_body == itemNum);
        case 1:
            return player_equip_cloak == itemNum;
        case 2:
            return player_equip_ring1 == itemNum;
        case 3:
            return player_equip_ring2 == itemNum;
        case 4:
            return (D_80097C14 == itemNum) + (D_80097C18 == itemNum);
        }
    }
    // seems to require missing return
}

// fix missing padding at end of jump table. ASPSX issue?
const u32 rodataPadding_800DCBD8 = 0;
