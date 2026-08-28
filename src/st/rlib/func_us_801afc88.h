// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitSchmoo;
extern AnimationFrame D_us_8018198C;
extern AnimationFrame D_us_80181998;

void func_us_801AFC88(Entity* self) {
    Entity* entity;
    s32 sideToPlayer;
    s32 distanceToPlayer;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_EXPLODE_B);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSchmoo);
        self->drawFlags = ENTITY_ROTATE;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        /* fall through */
    case 1:
        AnimateEntity(&D_us_8018198C, self);
        MoveEntity();
        sideToPlayer = GetSideToPlayer();

        if (self->facingLeft) {
            self->velocityX += FIX(0.046875);
            if (self->velocityX > FIX(3)) {
                self->velocityX = FIX(3);
            }
        } else {
            self->velocityX -= FIX(0.046875);
            if (self->velocityX < FIX(-3)) {
                self->velocityX = FIX(-3);
            }
        }

        if (sideToPlayer & 2) {
            self->velocityY -= FIX(0.046875);
            if (self->velocityY < FIX(-1.5)) {
                self->velocityY = FIX(-1.5);
            }
        } else {
            self->velocityY += FIX(0.046875);
            if (self->velocityY > FIX(1.5)) {
                self->velocityY = FIX(1.5);
            }
        }

        sideToPlayer = (sideToPlayer & 1) ^ 1;
        distanceToPlayer = GetDistanceToPlayerX();
        if (sideToPlayer != self->facingLeft && distanceToPlayer >= 0x59) {
            SetStep(2);
        }
        break;

    case 2:
        MoveEntity();
        switch (self->step_s) {
        case 0:
            self->velocityX -= self->velocityX >> 4;
            self->velocityY -= self->velocityY >> 4;
            if (abs(self->velocityX) < FIX(0.25)) {
                self->step_s++;
            }
            break;

        case 1:
            self->velocityX -= self->velocityX >> 8;
            self->velocityY -= self->velocityY >> 8;
            if (AnimateEntity(&D_us_80181998, self) == 0) {
                SetStep(1);
            }
            if (!self->poseTimer && self->pose == 2) {
                self->facingLeft ^= 1;
            }
            break;
        }
        break;
    }

    self->rotate = -abs(self->velocityX >> 8);
}
