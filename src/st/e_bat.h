// SPDX-License-Identifier: AGPL-3.0-or-later
static u8 bat_anim_fly[] = {4, 21, 1, 22, 1, 23, 1, 30, 1, 24, 1, 25, 4, 26,
                            2, 27, 2, 28, 2, 29, 1, 30, 2, 23, 2, 22, 0, 0};
static u8 bat_anim_drop[] = {5, 31, 5, 32, 5, 31, 5, 32, 5,  31, 5,   32, 4, 31,
                             4, 32, 3, 31, 3, 32, 2, 31, 12, 32, 255, 0,  0, 0};

void EntityBat(Entity* self) {
    Entity* newEntity;
    s16 xDistance;
    s16 yDistance;

    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 1;
        }
        PlaySfxPositional(SFX_BAT_SCREECH_SWISH);
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBat);
        self->animCurFrame = 31;
        break;

    case 1:
        xDistance = GetDistanceToPlayerX();
        yDistance = GetDistanceToPlayerY();
        if ((xDistance < 0x60) && (yDistance < 0x60) &&
            !(GetSideToPlayer() & 2)) {
            self->step++;
        }
        break;

    case 2:
        if (AnimateEntity(bat_anim_drop, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->velocityY = FIX(0.875);
            if (self->facingLeft) {
                self->velocityX = FIX(0.25);
            } else {
                self->velocityX = FIX(-0.25);
            }
            self->animFrameIdx = (Random() & 3) * 3;
            self->animFrameDuration = 0;
            self->step++;
        }
        break;

    case 3:
        AnimateEntity(bat_anim_fly, self);
        MoveEntity();
        if (GetDistanceToPlayerY() < 0x20) {
            if (self->facingLeft) {
                self->velocityX = FIX(1);
            } else {
                self->velocityX = FIX(-1);
            }
            self->ext.batEnemy.accelY = 0x800;
            self->step++;
        }
        break;

    case 4:
        AnimateEntity(bat_anim_fly, self);
        MoveEntity();
        if (self->velocityY < FIX(-1) || self->velocityY > FIX(1)) {
            self->ext.batEnemy.accelY = -self->ext.batEnemy.accelY;
        }
        // accelY is already an s32, but psp needs the cast. I dunno.
        self->velocityY += (s32)self->ext.batEnemy.accelY;
        break;
    }
}
