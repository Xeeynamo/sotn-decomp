// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitImpDeathParticle;
extern u8 g_ImpDeathParticleAnim[];

void EntityImpDeathParticle(Entity* self) {
    s32 speed;
    s16 angle;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(0x691);
        self->pfnUpdate = EntityExplosion;
        self->step = 0;
        self->params = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitImpDeathParticle);
        self->facingLeft = Random() & 1;
        speed = (Random() & 0x1F) + 0x10;
        angle = Random() * 6 + 0x900;
        self->velocityX = speed * rcos(angle);
        self->velocityY = speed * rsin(angle);
        self->posX.val += self->velocityX * 4;
        self->posY.val += self->velocityY * 4;
        self->ext.imp.timer = (Random() & 0x1F) + 0x10;
        self->rotate = angle;
        // fallthrough
    case 1:
        AnimateEntity(g_ImpDeathParticleAnim, self);
        MoveEntity();
        self->velocityX -= self->velocityX / 16;
        self->velocityY -= self->velocityY / 16;
        if (!--self->ext.imp.timer) {
            self->velocityX = 0;
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        if (self->velocityY < FIX(0.5)) {
            self->velocityY += FIX(0.03125);
        }
#if defined(VERSION_PSP)
        angle = self->rotate += 0x80;
        self->velocityX = (rcos(angle) << 15) >> 12;
#else
        self->rotate += 0x80;
        self->velocityX = (rcos(self->rotate) << 15) >> 12;
#endif
        break;
    }
}
