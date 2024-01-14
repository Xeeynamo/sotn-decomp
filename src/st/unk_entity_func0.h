void UnkEntityFunc0(s32 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos((u16)slope) * speed;
    entity = g_CurrentEntity;

    if (moveX < 0) {
        moveX += 15;
    }

    entity->velocityX = moveX >> 4;

    moveY = rsin((u16)slope) * speed;
    entity = g_CurrentEntity;

    if (moveY < 0) {
        moveY += 15;
    }

    entity->velocityY = moveY >> 4;
}