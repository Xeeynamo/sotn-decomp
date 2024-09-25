s32 CheckEntityValid(Entity* entity) {
    if (entity->hitboxState == 0)
        return 0;
    if (entity->posX.i.hi < -16)
        return 0;
    if (entity->posX.i.hi > 272)
        return 0;
    if (entity->posY.i.hi > 240)
        return 0;
    if (entity->posY.i.hi < 0)
        return 0;
    if (entity->hitPoints >= 0x7000)
        return 0;
    if (entity->hitPoints <= 0)
        return 0;

    return 1;
}