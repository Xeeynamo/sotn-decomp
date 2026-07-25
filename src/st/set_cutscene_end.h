// SPDX-License-Identifier: AGPL-3.0-or-later
void SetCutsceneEnd(u8* ptr) {
    g_Dialogue.scriptEnd = CS_PTR(ptr);
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}
