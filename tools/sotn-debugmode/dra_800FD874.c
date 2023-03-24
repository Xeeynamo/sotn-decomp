#include <game.h>

u16 g_itemId;
u16 g_itemCategory;

void InitDraTest800FD874(void) {
    g_itemId = 0;
    g_itemCategory = 0;
}

void UpdateDraTest800FD874(void) {
    FntPrint("L2=Add\n");
    FntPrint("ID:  %02X\n", g_itemId);
    FntPrint("Cat: %02X\n", g_itemCategory);

    if (g_pads->tapped & PAD_UP && g_itemId > 0) {
        g_itemId--;
    }
    if (g_pads->tapped & PAD_DOWN) {
        g_itemId++;
    }
    if (g_pads->tapped & PAD_LEFT && g_itemCategory > 0) {
        g_itemCategory--;
    }
    if (g_pads->tapped & PAD_RIGHT) {
        g_itemCategory++;
    }
    if (g_pads->tapped & PAD_L2) {
        g_api.AddToInventory(g_itemId, g_itemCategory);
    }
}