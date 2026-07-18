// SPDX-License-Identifier: AGPL-3.0-or-later

extern const char* g_goldCollectTexts[10];
static void InitOnce() {
    static bool is_initialized = 0;
    if (is_initialized) {
        return;
    }
    is_initialized = 1;

    unsigned len = LEN(g_goldCollectTexts);
    if (g_StageId == STAGE_ST0) {
        len = 1; // HACK
    }
    for (int i = 0; i < len; i++) {
        g_goldCollectTexts[i] = AnsiToSotnMenuString(g_goldCollectTexts[i]);
    }
}
