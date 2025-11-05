// SPDX-License-Identifier: AGPL-3.0-or-later

// st0 uses a union for g_Dialogue
#ifdef STAGE_IS_ST0
#define G_DIALOGUE g_Dialogue.std
#else
#define G_DIALOGUE g_Dialogue
#endif

#ifdef VERSION_PC
static
#endif
    void
    SetCutsceneEnd(u8* ptr) {
#if !defined(VERSION_PSP)
    G_DIALOGUE.scriptEnd = ptr + 0x100000;
#else
    G_DIALOGUE.scriptEnd = ptr;
#endif
    G_DIALOGUE.timer = 0;
    G_DIALOGUE.unk3C = 1;
}
