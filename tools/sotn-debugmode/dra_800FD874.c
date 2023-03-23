#include <game.h>

u16 g_arg0;
u16 g_arg1;

void func_800FD874(u16 arg0, s32 arg1);
void (*ptr_800FD874)(u16 arg0, s32 arg1);

void InitDraTest800FD874(void) {
    g_arg0 = 0;
    g_arg1 = 0;
    ptr_800FD874 = 0x800FD874;
}

void UpdateDraTest800FD874(void) {
    FntPrint("* func_800FD874\n");
    FntPrint("arg0: %02X\n", g_arg0);
    FntPrint("arg1: %02X\n", g_arg1);

    if (g_pads->tapped & PAD_UP && g_arg0 > 0) {
        g_arg0--;
    }
    if (g_pads->tapped & PAD_DOWN) {
        g_arg0++;
    }
    if (g_pads->tapped & PAD_LEFT && g_arg1 > 0) {
        g_arg1--;
    }
    if (g_pads->tapped & PAD_RIGHT) {
        g_arg1++;
    }
    if (g_pads->tapped & PAD_L2) {
        ptr_800FD874(g_arg0, g_arg1);
    }
}