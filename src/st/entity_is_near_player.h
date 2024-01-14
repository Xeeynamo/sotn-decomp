bool EntityIsNearPlayer(Entity* self) {
    s16 posX = PLAYER.posX.i.hi - self->posX.i.hi;
    s16 posY;

    posX = ABS(posX);

    if (posX < 17) {
        posY = PLAYER.posY.i.hi - self->posY.i.hi;
        posY = ABS(posY);
        return posY < 33;
    }
    return 0;
}