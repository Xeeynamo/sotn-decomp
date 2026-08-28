// SPDX-License-Identifier: AGPL-3.0-or-later

typedef enum {
    NOVA_INIT,
    NOVA_1,
    NOVA_IDLE,
    NOVA_WALK_FWD,
    NOVA_WALK_BACK,
    NOVA_5,
    NOVA_CHARGE,
    NOVA_SHOOT,
    NOVA_DEAD
} NovaSkeletonSteps;

extern s16 D_us_80181D20[];

void TryShoot(void) {
    // return value not used, but function has side effects
    s32 unused = UnkCollisionFunc2(D_us_80181D20);

    // if cooldown has expired...
    if (!g_CurrentEntity->ext.nova.cooldown) {
        if (GetDistanceToPlayerX() >= 0x80) {
            return;
        }
        if (g_CurrentEntity->facingLeft ^ (GetSideToPlayer() & 1)) {
            SetStep(NOVA_CHARGE);
        }
    } else {
        g_CurrentEntity->ext.nova.cooldown--;
    }
}
