// SPDX-License-Identifier: AGPL-3.0-or-later
static void CollectLifeVessel(void) {
    g_api.PlaySfx(SFX_HEART_PICKUP);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}
