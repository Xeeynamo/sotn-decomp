// SPDX-License-Identifier: AGPL-3.0-or-later
// Not used in any current overlays. Seems to resemble Gaibon's big fireball,
// but is not actually called in NZ0. Will need to check future overlays for
// any actual uses.

extern u8 g_bigRedFireballAnim[];

void EntityBigRedFireball(Entity* self) {
    s32 speedTemp;

    if (self->step == 0) {
        InitializeEntity(g_EInitParticle);
        self->animSet = ANIMSET_DRA(2);
        self->palette = PAL_OVL(0x1B6);
        self->unk6C = 0x70;
        self->zPriority = 192;
        self->drawFlags |= (FLAG_DRAW_ROTZ + FLAG_DRAW_UNK8);
        self->drawMode |= (DRAW_TPAGE + DRAW_TPAGE2);

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
        speedTemp = self->ext.bigredfireball.speed * 320 / 24; // = 13.333
        self->velocityX = speedTemp * rsin(self->ext.bigredfireball.angle);
        self->velocityY = -(speedTemp * rcos(self->ext.bigredfireball.angle));
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
