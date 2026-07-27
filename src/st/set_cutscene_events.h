// SPDX-License-Identifier: AGPL-3.0-or-later
void SetCutsceneEvents(u8* ptr) {
    g_Dialogue.eventCur = CS_PTR(ptr);
    g_Dialogue.timer = 0;
    g_Dialogue.hasEvents = 1;
}
