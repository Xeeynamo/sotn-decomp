// SPDX-License-Identifier: AGPL-3.0-or-later
s32 UnkCollisionFunc2(s16* posX) {
    Collider collider;
    s16 x, y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.i.hi += 3;
    x = g_CurrentEntity->posX.i.hi + *posX++;
    y = g_CurrentEntity->posY.i.hi + *posX++;
    g_api.CheckCollision(x, y, &collider, 0);

    if (collider.effects & EFFECT_SOLID) {
        g_CurrentEntity->posY.i.hi += collider.unk18;
    } else {
        return 0;
    }

    if (g_CurrentEntity->velocityX != 0) {
        if (g_CurrentEntity->velocityX < 0) {
            x -= *posX++;
        } else {
            x += *posX++;
        }
        y += *posX;
        y -= 7;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (collider.effects & EFFECT_UNK_8000 ||
                !(collider.effects & EFFECT_UNK_0002)) {
                return 0x61;
            }
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
            return 0xFF;
        }
        y += 15;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (collider.effects & EFFECT_UNK_8000) {
                return 0x61;
            }
            return 1;
        }
        g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
        g_CurrentEntity->velocityX = 0;

        return 0x80;
    }
    return 1;
}
