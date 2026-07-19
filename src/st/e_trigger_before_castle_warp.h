// SPDX-License-Identifier: AGPL-3.0-or-later
extern EInit g_EInitInteractable;

void EntityTriggerBeforeCastleWarp(Entity* self) {
    FntPrint("alive \n");
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        g_api.func_800EA5E4(0xC001);
        g_api.func_800EA5E4(0xC002);
        g_api.func_800EA5E4(0xC003);
        g_api.func_800EA5E4(0xC004);
        g_api.func_800EA5E4(0xC005);
        g_api.func_800EA5E4(0xC006);
        g_api.func_800EA5E4(0xC007);
        g_api.func_800EA5E4(0xC008);
        g_api.func_800EA5E4(0xC009);
    case 1:
        break;
    }
}
