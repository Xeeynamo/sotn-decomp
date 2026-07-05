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
    OVL_EXPORT(Dialogue).nextLineX = 0;
    OVL_EXPORT(Dialogue).nextCharX = 0;
#else
    OVL_EXPORT(Dialogue).nextLineY = OVL_EXPORT(Dialogue).startY + 0x14;
    OVL_EXPORT(Dialogue).nextCharX = OVL_EXPORT(Dialogue).nextLineX =
        CUTSCENE_UNK1_NEXT_X;
#endif
    OVL_EXPORT(Dialogue).nextCharY = 0;
    OVL_EXPORT(Dialogue).unk12 = 0;
    OVL_EXPORT(Dialogue).nextCharTimer = 0;
    OVL_EXPORT(Dialogue).unk17 = CUTSCENE_UNK1_UNK17;
#ifdef VERSION_HD
    OVL_EXPORT(Dialogue).nextLineY = OVL_EXPORT(Dialogue).startY + 0x14;
#endif
}
