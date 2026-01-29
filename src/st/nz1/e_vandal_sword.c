// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

INCLUDE_ASM("st/nz1/nonmatchings/e_vandal_sword", VandalSwordDrawAlastor);

extern Entity g_Entities_224;
extern int g_Timer;
extern Entity* g_CurrentEntity;

void VandalSwordTargetPlayer(void) {
    Entity* temp_v0 = NULL;

    if (g_Timer & 7)
        goto done;

    temp_v0 = AllocEntity(
        &g_Entities_224, (Entity*)((char*)&g_Entities_224 + 0x1780));
    if (temp_v0 == NULL)
        goto done;

    CreateEntityFromEntity(E_VANDAL_SWORD_DEATH, g_CurrentEntity, temp_v0);
    temp_v0->rotate = (s16)(u16)g_CurrentEntity->rotate;
    temp_v0->facingLeft = g_CurrentEntity->facingLeft;

done:
    return;
}

bool VandalSwordTrail(s16* val, s16 target, s16 step) {
    if (abs(*val - target) < step) {
        *val = target;
        return true;
    }
    if (*val > target) {
        *val -= step;
    }
    if (*val < target) {
        *val += step;
    }
    return false;
}

INCLUDE_ASM("st/nz1/nonmatchings/e_vandal_sword", EntityVandalSword);

INCLUDE_ASM("st/nz1/nonmatchings/e_vandal_sword", EntityVandalSwordHitbox);

INCLUDE_ASM("st/nz1/nonmatchings/e_vandal_sword", EntityVandalSwordDeath);
