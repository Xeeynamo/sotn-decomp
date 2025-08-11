// SPDX-License-Identifier: AGPL-3.0-or-later
extern EInit g_EInitInteractable;

void EntityTriggerBeforeCastleWarp(Entity* self) {
    FntPrint("alive \n");
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        g_api.func_800EA5E4(0xC001U);
        g_api.func_800EA5E4(0xC002U);
        g_api.func_800EA5E4(0xC003U);
        g_api.func_800EA5E4(0xC004U);
        g_api.func_800EA5E4(0xC005U);
        g_api.func_800EA5E4(0xC006U);
        g_api.func_800EA5E4(0xC007U);
        g_api.func_800EA5E4(0xC008U);
        g_api.func_800EA5E4(0xC009U);
    }
}
