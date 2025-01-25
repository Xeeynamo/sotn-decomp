// SPDX-License-Identifier: AGPL-3.0-or-later

static void SetCutsceneEnd(u8* ptr) {
#if !defined(VERSION_PSP)
    g_Dialogue.scriptEnd = ptr + 0x100000;
#else
    g_Dialogue.scriptEnd = ptr;
#endif
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}
