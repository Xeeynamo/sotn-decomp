#include "debugmode.h"

Lba* g_Lba;
int g_StageIdCursor;
// D_800987B4 = g_StageSelectionCursor

void InitStageSelect(void) {
    g_Lba = 0x800A3C40;
    g_StageIdCursor = g_StageId;
}

void UpdateStageSelect(void) {
    Lba* lba;

    if (g_pads->repeat & PAD_UP) {
        g_StageIdCursor--;
        if (g_StageIdCursor < 0) {
            g_StageIdCursor = 0x4F;
        }
    }
    if (g_pads->repeat & PAD_DOWN) {
        g_StageIdCursor++;
        if (g_StageIdCursor >= 0x50) {
            g_StageIdCursor = 0;
        }
    }

    lba = &g_Lba[g_StageIdCursor];
    FntPrint("%02X %s (%s, %s)\n", g_StageIdCursor, lba->name, lba->ovlName,
             lba->gfxName);
    FntPrint("L2=Alucard\n");
    FntPrint("L1=Richter\n");

    if (g_pads->tapped & PAD_L2) {
        g_CurrentPlayableCharacter = 0;
    }
    if (g_pads->tapped & PAD_L1) {
        g_CurrentPlayableCharacter = 1;
    }

    if (g_pads->tapped & (PAD_L2 || PAD_L1)) {
        D_8003C734 = 4;
        D_80073060 = 2;
        g_StageId = g_StageIdCursor;
        g_IsTimeAttackUnlocked = 1;
    }
}
