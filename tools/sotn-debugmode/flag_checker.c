#include <game.h>

int g_Flag;

void InitFlagChecker(void) { g_Flag = 0; }

void UpdateFlagChecker(void) {
    FntPrint("Flag: %02d L1=inc, L2=dec\n", g_Flag);
    FntPrint("Value: %02x\n", D_8003BDEC[g_Flag]);

    if (g_pads->pressed & PAD_UP) {
        g_Flag--;
    }
    if (g_pads->pressed & PAD_DOWN) {
        g_Flag++;
    }
    if (g_pads->tapped & PAD_LEFT) {
        g_Flag--;
    }
    if (g_pads->tapped & PAD_RIGHT) {
        g_Flag++;
    }

    if (g_Flag < 0) {
        g_Flag = 0;
    } else if (g_Flag >= LEN(D_8003BDEC)) {
        g_Flag = LEN(D_8003BDEC) - 1;
    }

    if (g_pads->tapped & PAD_L2) {
        D_8003BDEC[g_Flag]--;
    }

    if (g_pads->tapped & PAD_L1) {
        D_8003BDEC[g_Flag]++;
    }
}
