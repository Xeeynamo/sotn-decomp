// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef CUTSCENE_UNK1_NEXT_X
#define CUTSCENE_UNK1_NEXT_X 2
#endif

#ifndef CUTSCENE_UNK1_UNK17
#define CUTSCENE_UNK1_UNK17 8
#endif

#ifdef VERSION_PC
static
#endif
    void
    CutsceneUnk1(void) {
#ifdef VERSION_HD
    g_Dialogue.nextLineX = 0;
    g_Dialogue.nextCharX = 0;
#else
    g_Dialogue.nextLineY = g_Dialogue.startY + 0x14;
    g_Dialogue.nextCharX = g_Dialogue.nextLineX = CUTSCENE_UNK1_NEXT_X;
#endif
    g_Dialogue.nextCharY = 0;
    g_Dialogue.unk12 = 0;
    g_Dialogue.nextCharTimer = 0;
    g_Dialogue.unk17 = CUTSCENE_UNK1_UNK17;
#ifdef VERSION_HD
    g_Dialogue.nextLineY = g_Dialogue.startY + 0x14;
#endif
}
