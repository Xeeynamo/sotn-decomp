// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitBat;

static u8 bat_anim_fly[] = {4, 21, 1, 22, 1, 23, 1, 30, 1, 24, 1, 25, 4, 26,
                            2, 27, 2, 28, 2, 29, 1, 30, 2, 23, 2, 22, 0, 0};
static u8 bat_anim_drop[] = {5, 31, 5, 32, 5, 31, 5, 32, 5,  31, 5,   32, 4, 31,
                             4, 32, 3, 31, 3, 32, 2, 31, 12, 32, 255, 0,  0, 0};

void EntityBat(Entity* self) {
#ifdef STAGE_IS_RCAT
    Collider collider;
#endif
    Entity* newEntity;
    s16 xDistance;
    s16 yDistance;
    s32 posX;
    s32 posY;
    s32 var_s2;

    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 1;
        }
#ifdef STAGE_IS_RCAT
        g_api.PlaySfx(SFX_BAT_SCREECH);
#else
        PlaySfxPositional(SFX_BAT_SCREECH_SWISH);
#endif
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
#ifdef STAGE_IS_RCAT
        self->ext.batEnemy.yProximity = 0xC0;
        self->ext.batEnemy.xProximity = 0x78;
        self->ext.batEnemy.unk88 = (rand() & 0x3F) + 0x20;
#endif
        InitializeEntity(g_EInitBat);
        self->animCurFrame = 31;
        break;

    case 1:
        xDistance = GetDistanceToPlayerX();
        yDistance = GetDistanceToPlayerY();
#ifdef STAGE_IS_RCAT
        if ((xDistance < self->ext.batEnemy.xProximity) &&
            (yDistance < self->ext.batEnemy.yProximity) &&
#else
        if ((xDistance < 0x60) && (yDistance < 0x60) &&
#endif
            !(GetSideToPlayer() & 2)) {
            self->step++;
        }
        break;

    case 2:
        if (AnimateEntity(bat_anim_drop, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
#ifdef STAGE_IS_RCAT
            self->velocityY = FIX(1.125);
#else
            self->velocityY = FIX(0.875);
#endif
            if (self->facingLeft) {
                self->velocityX = FIX(0.25);
            } else {
                self->velocityX = FIX(-0.25);
            }
            self->pose = (Random() & 3) * 3;
            self->poseTimer = 0;
            self->step++;
        }
        break;

    case 3:
        AnimateEntity(bat_anim_fly, self);
        MoveEntity();

#ifdef STAGE_IS_RCAT
        var_s2 = 0;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += 0x20;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & (EFFECT_WATER | EFFECT_SOLID)) {
            self->velocityY = 0;
            var_s2 = 1;
        }

        if (GetDistanceToPlayerY() < self->ext.batEnemy.unk88) {
            var_s2 = 1;
        }

        if (var_s2) {
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->ext.batEnemy.accelY = 0x800;
            self->step = 4;
        }
#else
        if (GetDistanceToPlayerY() < 0x20) {
            if (self->facingLeft) {
                self->velocityX = FIX(1);
            } else {
                self->velocityX = FIX(-1);
            }
            self->ext.batEnemy.accelY = 0x800;
            self->step++;
        }
#endif
        break;

    case 4:
        AnimateEntity(bat_anim_fly, self);
        MoveEntity();
        if (self->velocityY < FIX(-1) || self->velocityY > FIX(1)) {
            self->ext.batEnemy.accelY = -self->ext.batEnemy.accelY;
        }
        self->velocityY += self->ext.batEnemy.accelY;
#ifdef STAGE_IS_RCAT
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (self->velocityY > 0) {
            posY += 4;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & (EFFECT_WATER | EFFECT_SOLID)) {
                self->velocityY = 0;
            }
        }
#endif
        break;
    }
}
