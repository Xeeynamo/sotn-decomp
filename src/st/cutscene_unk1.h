// SPDX-License-Identifier: AGPL-3.0-or-later

// st0 uses a union for g_Dialogue
#ifdef STAGE_IS_ST0
#define G_DIALOGUE g_Dialogue.std
#else
#define G_DIALOGUE g_Dialogue
#endif

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
    G_DIALOGUE.nextLineX = 0;
    G_DIALOGUE.nextCharX = 0;
#else
    G_DIALOGUE.nextLineY = G_DIALOGUE.startY + 0x14;
    G_DIALOGUE.nextCharX = G_DIALOGUE.nextLineX = CUTSCENE_UNK1_NEXT_X;
#endif
    G_DIALOGUE.nextCharY = 0;
    G_DIALOGUE.unk12 = 0;
    G_DIALOGUE.nextCharTimer = 0;
    G_DIALOGUE.unk17 = CUTSCENE_UNK1_UNK17;
#ifdef VERSION_HD
    G_DIALOGUE.nextLineY = G_DIALOGUE.startY + 0x14;
#endif
}
