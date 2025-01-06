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
        if (phi_s1->x != chunkX || phi_s1->y != chunkY ||
            phi_s1->stageId != g_StageId) {
            continue;
        }

        if (phi_s1->eventId == TIMEATTACK_EVENT_INVALID) {
            return phi_s1->unk10 + 2;
        }
        if (TimeAttackController(phi_s1->eventId, TIMEATTACK_GET_RECORD) == 0) {
            return phi_s1->unk10 + 2;
        }
    }
}

void func_800F0940(void) {
    switch (g_BgLayers[0].scrollKind) {
    case 1:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi;
        g_BgLayers[0].scrollY.i.hi = g_Tilemap.scrollY.i.hi;
        break;
    case 2:
        g_BgLayers[0].scrollX.i.hi = (g_Tilemap.scrollX.i.hi / 2);
        g_BgLayers[0].scrollY.i.hi = (g_Tilemap.scrollY.i.hi / 2) + 0x76;
        break;
    case 3:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi / 2;
        g_BgLayers[0].scrollY.i.hi = g_Tilemap.scrollY.i.hi;
        break;
    case 4:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi;
        g_BgLayers[0].scrollY.i.hi = g_Tilemap.scrollY.i.hi / 2;
        if (g_StageId == STAGE_RCHI) {
            g_BgLayers[0].scrollY.i.hi += 0x80;
        }
        break;
    case 5:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi / 2;
        g_BgLayers[0].scrollY.i.hi = g_Tilemap.scrollY.i.hi / 2;
        if (g_StageId == STAGE_RDAI) {
            g_BgLayers[0].scrollX.i.hi += 0x80;
        }
        break;
    case 6:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi / 2;
        g_BgLayers[0].scrollY.i.hi =
            (g_Tilemap.scrollY.i.hi / 2 - ((g_Tilemap.vSize - 1) * 128)) +
            (g_BgLayers[0].h * 128);
        if (g_StageId == STAGE_RDAI) {
            g_BgLayers[0].scrollX.i.hi += 0x80;
            g_BgLayers[0].scrollY.i.hi = g_Tilemap.scrollY.i.hi / 2;
        }
        break;
    case 7:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi / 2;
        g_BgLayers[0].scrollY.i.hi = 4;
        break;
    default:
        g_BgLayers[0].scrollX.i.hi = 0;
        g_BgLayers[0].scrollY.i.hi = 4;
        break;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", SetNextRoomToLoad);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_800F0CD8);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E7BC0);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E7DA8);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E7E38);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E7E90);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E7ED8);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E7F38);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E7F98);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E8008);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E80E0);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E81A8);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E83E8);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E8518);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E8620);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E8658);
