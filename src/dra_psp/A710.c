// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

extern RoomBossTeleport D_800A297C[];
s32 func_800F087C(u32 chunkX, u32 chunkY) {
    RoomBossTeleport* phi_s1;

    for (phi_s1 = &D_800A297C[0]; true; phi_s1++) {
        if (phi_s1->x == 0x80) {
            return 0;
        }
        // All must match, otherwise we jump out.
        if (phi_s1->x != chunkX || phi_s1->y != chunkY || phi_s1->stageId != g_StageId){
            continue;
        }
        
        if(phi_s1->eventId == TIMEATTACK_EVENT_INVALID){
            return phi_s1->unk10 + 2;
        }
        if(TimeAttackController(phi_s1->eventId, TIMEATTACK_GET_RECORD) == 0) {
            return phi_s1->unk10 + 2;
        }
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E7150);
