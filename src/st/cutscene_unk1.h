// SPDX-License-Identifier: AGPL-3.0-or-later
#ifdef STAGE_IS_LIB
#define CUTSCENE_UNK1_NEXT_X 0x42
#else
#define CUTSCENE_UNK1_NEXT_X 2
#endif

static void CutsceneUnk1(void) {
    g_Dialogue.nextLineY = g_Dialogue.startY + 0x14;
    g_Dialogue.nextCharX = g_Dialogue.nextLineX = CUTSCENE_UNK1_NEXT_X;
    g_Dialogue.nextCharY = 0;
    g_Dialogue.unk12 = 0;
    g_Dialogue.nextCharTimer = 0;
    g_Dialogue.unk17 = 8;
}
