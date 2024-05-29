// Not used in any current overlays. Seems to resemble Gaibon's big fireball,
// but is not actually called in NZ0. Will need to check future overlays for
// any actual uses.

extern u8 g_bigRedFireballAnim[];

void EntityBigRedFireball(Entity* self) {
    s32 temp;

    if (self->step == 0) {
        InitializeEntity(g_InitializeEntityData0);
        self->animSet = ANIMSET_DRA(2);
        self->palette = 0x81B6;
        self->unk6C = 0x70;
        self->zPriority = 192;
        self->drawFlags |= 0xC;
        self->drawMode |= 0x30;

        switch (self->ext.bigredfireball.switch_control) {
        case 1:
            if (self->ext.bigredfireball.speed > 3) {
                self->ext.bigredfireball.speed -= 3;
                self->ext.bigredfireball.angle -= 0x800;
            }
            break;

        case 2:
            self->ext.bigredfireball.angle +=
                self->ext.bigredfireball.speed * 192;
            break;
        }

        self->rotZ = self->ext.bigredfireball.angle &= 0xFFF;
        temp = (self->ext.bigredfireball.speed * 320) / 24;
        self->velocityX = temp * rsin(self->ext.bigredfireball.angle);
        self->velocityY = -(temp * rcos(self->ext.bigredfireball.angle));
    }

    if (self->animFrameIdx >= 13) {
        self->velocityX = self->velocityX / 4 * 3;
        self->velocityY = self->velocityY / 4 * 3;
    }

    MoveEntity();

    if (AnimateEntity(g_bigRedFireballAnim, self) == 0) {
        DestroyEntity(self);
    }
}
