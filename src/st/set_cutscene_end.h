// SPDX-License-Identifier: AGPL-3.0-or-later
static void SetCutsceneEnd(u8* ptr) {
    g_Dialogue.scriptEnd = ptr + 0x100000;
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}
