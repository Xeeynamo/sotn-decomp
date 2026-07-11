

extern const char* OVL_EXPORT(GoldCollectTexts)[10];
static void InitOnce() {
    static bool is_initialized = 0;
    if (is_initialized) {
        return;
    }
    is_initialized = 1;

    for (int i = 0; i < LEN(OVL_EXPORT(GoldCollectTexts)); i++) {
        OVL_EXPORT(GoldCollectTexts)
        [i] = AnsiToSotnMenuString(OVL_EXPORT(GoldCollectTexts)[i]);
    }
}
