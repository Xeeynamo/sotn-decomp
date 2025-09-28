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
    g_Dialogue.unk10 = 0;
    g_Dialogue.nextLineX = 0;
    g_Dialogue.nextCharY = 0;
    g_Dialogue.nextCharTimer = 0;
    g_Dialogue.unk1A = 0;
    g_Dialogue.unk1B = 8; // Unsure if this is the same as unk17
    g_Dialogue.startY = g_Dialogue.nextLineY + 0x14;
#else
    g_Dialogue.nextLineY = g_Dialogue.startY + 0x14;
    g_Dialogue.nextCharX = g_Dialogue.nextLineX = CUTSCENE_UNK1_NEXT_X;
    g_Dialogue.nextCharY = 0;
    g_Dialogue.unk12 = 0;
    g_Dialogue.nextCharTimer = 0;
    g_Dialogue.unk17 = CUTSCENE_UNK1_UNK17;
#endif
}
