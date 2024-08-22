// SPDX-License-Identifier: AGPL-3.0-only
#include "sfx.h"

void CollectHeartVessel(void) {
#ifdef VERSION_BETA
    if (0) { // MAD doesn't need to test character, is always alucard
#else
    if (g_PlayableCharacter != PLAYER_ALUCARD) {
#endif
        g_api.PlaySfx(SFX_HEART_PICKUP);
        g_Status.hearts += HEART_VESSEL_RICHTER;

        if (g_Status.hearts > g_Status.heartsMax) {
            g_Status.hearts = g_Status.heartsMax;
        }
    } else {
        // Alucard's version
        g_api.PlaySfx(SFX_HEART_PICKUP);
        g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(g_CurrentEntity);
}
