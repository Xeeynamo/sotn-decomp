#include <game.h>

int g_SfxId;

void InitSfxPlayer(void) { g_SfxId = 1; }
void UpdateSfxPlayer(void) {
    FntPrint("* sfx player (L2=play)");
    FntPrint("* sfxID: %03X", g_SfxId);

    if (g_pads->pressed & PAD_UP) {
        g_SfxId--;
    }
    if (g_pads->pressed & PAD_DOWN) {
        g_SfxId++;
    }
    if (g_pads->tapped & PAD_LEFT) {
        g_SfxId--;
    }
    if (g_pads->tapped & PAD_RIGHT) {
        g_SfxId++;
    }

    if (g_SfxId < 0) {
        g_SfxId = 0;
    } else if (g_SfxId > 0xFFF) {
        g_SfxId = 0xFFF;
    }

    if (g_pads->tapped & PAD_CROSS) {
        g_api.PlaySfx(g_SfxId);
    }

    FntFlush(-1);
}
