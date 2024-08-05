void CheckFieldCollision(u16* hitSensors, s16 sensorCount) {
    s32 velocityX = g_CurrentEntity->velocityX;
    Collider collider;
    s16 x, y;
    s16 i;

    if (velocityX == 0) {
        return;
    }

    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;

    for (i = 0; i < sensorCount; i++) {
        if (velocityX < 0) {
            x += *hitSensors++;
        } else {
            x -= *hitSensors++;
        }
        y += *hitSensors++;

        g_api.CheckCollision(x, y, &collider, 0);

        if ((collider.effects & EFFECT_UNK_0002) &&
            (!(collider.effects & EFFECT_UNK_8000) || (i != 0))) {
            if (velocityX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            return;
        }
    }
}