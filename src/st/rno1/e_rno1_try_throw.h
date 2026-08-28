// SPDX-License-Identifier: AGPL-3.0-or-later

typedef enum {
    JACKO_INIT,
    JACKO_1,
    JACKO_WALK_FWD,
    JACKO_WALK_BACK,
    JACKO_THROW,
    JACKO_JUMP,
    JACKO_DEAD
} JackOBonesSteps;

extern s16 D_us_80181CFC[];
extern s16 D_us_80181D04[];

static void TryThrow(void) {
    s32 collisionResult;
    u16 collisionFlags;

    collisionResult = UnkCollisionFunc2(D_us_80181CFC);
    collisionFlags = UnkCollisionFunc(D_us_80181D04, 3);
    if (collisionResult == 0x80 || (collisionFlags & 2)) {
        SetStep(JACKO_JUMP);
        return;
    }
    if (!g_CurrentEntity->ext.jackoBones.throwTimer) {
        SetStep(JACKO_THROW);
        return;
    }
    g_CurrentEntity->ext.jackoBones.throwTimer--;
}
