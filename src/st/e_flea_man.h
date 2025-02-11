// SPDX-License-Identifier: AGPL-3.0-or-later
static s32 fidgetVelocityX[] = {FIX(-2), FIX(-0.875), FIX(1.5), 0, FIX(-2.5)};
static s32 fidgetVelocityY[] = {
    FIX(-0.5), FIX(-6), FIX(-3), FIX(-3.5), FIX(-4)};
static u8 anim_stand[] = {0x04, 0x10, 0x04, 0x11, 0x04, 0x12, 0x04, 0x13, 0x00};
static s16 sensors_ground[][2] = {{0, 10}, {0, 4}, {6, -4}, {-12, 0}};
static s16 sensors_move_y[][2] = {{0, -8}, {4, 0}, {-8, 0}};
static s16 sensors_move_x[][2] = {{-9, 6}, {0, -12}};

extern s32 D_us_80181ACC;

// Checks for collisions while the entity is moving downward, updating position
// if collision occurs. This is similar to other function CheckFieldCollision
static void CheckFieldCollisionY(s16 hitSensors[], s16 sensorCount) {
    Collider collider;
    s32 velocityY;
    s16 currentPosX;
    s16 currentPosY;
    s16 i;

    velocityY = g_CurrentEntity->velocityY;
    if (velocityY >= 0) {
        return;
    }

    currentPosX = g_CurrentEntity->posX.i.hi;
    currentPosY = g_CurrentEntity->posY.i.hi;

    for (i = 0; i < sensorCount; i++) {
        currentPosX += *hitSensors++;
        currentPosY += *hitSensors++;

        g_api.CheckCollision(currentPosX, currentPosY, &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->posY.i.hi += collider.unk20;
            break;
        }
    }
}

static void UpdateFacingDirection(void) {
    g_CurrentEntity->facingLeft = (GetSideToPlayer() & 1) ^ 1;
}

void EntityFleaMan(Entity* self) {
    u32 distanceX;
    u8 rand;
    u8 index;

#ifdef STAGE_IS_LIB
    if (D_us_80181ACC & 1) {
        self->flags |= FLAG_DEAD;
    }
#endif

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
        EntityExplosionSpawn(1, 0);
        return;
    }

    if (self->ext.fleaMan.unk7C) {
        self->ext.fleaMan.unk7C--;
        self->hitboxState = 0;
    } else {
        self->hitboxState = 19;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFleaMan);
        self->animCurFrame = 16;
        if (self->params & 1) {
            self->facingLeft = 1;
            self->velocityX = 0x140;
            self->velocityY = 0xA0;
            self->step = 2;
        } else {
            self->step = 1;
        }

#ifndef VERSION_PSP
        if (self->ext.fleaMan.unk7C) {
            self->step = 3;
        }
#endif
        break;

    case 1:
        AnimateEntity(anim_stand, self);
        UpdateFacingDirection();
        if (GetDistanceToPlayerX() < 0x60 && GetDistanceToPlayerY() < 0x40) {
            self->step = 3;
        }
        break;

    case 2:
        self->zPriority = 0;
        MoveEntity();
        break;

    case 3:
        UpdateFacingDirection();
        if (self->hitParams && self->hitParams < 4) {
            index = 2;
        } else {
            rand = Random() & 7;
            distanceX = GetDistanceToPlayerX();

            if (distanceX < 0x50) {
                switch (rand) {
                case 0:
                case 1:
                    index = 3;
                    break;
                case 2:
                    index = 2;
                    break;
                case 3:
                    index = 1;
                    break;
                default:
                    index = 0;
                    break;
                }
            } else if (distanceX <= 0x7F) {
                switch (rand) {
                case 0:
                    index = 3;
                    break;
                case 1:
                    index = 2;
                    break;
                case 2:
                    index = 0;
                    break;
                default:
                    if (self->facingLeft ^ PLAYER.facingLeft) {
                        index = 0;
                    } else {
                        index = 1;
                    }
                    break;
                }
            } else {
                index = 4;
            }
        }

        distanceX = fidgetVelocityX[index];
        if (self->facingLeft) {
            self->velocityX = -distanceX;
        } else {
            self->velocityX = distanceX;
        }

        self->velocityY = fidgetVelocityY[index];
        if (index == 1) {
            PlaySfxPositional(SFX_BLIPS_C);
        } else if (index == 0 || index == 2) {
            PlaySfxPositional(SFX_BLIPS_D);
        }

        self->step++;
        break;

    case 4:
        if (self->velocityY > FIX(-0.25) && self->velocityY < FIX(0.25)) {
            index = 19;
        } else if (self->velocityY < 0) {
            index = 20;
        } else {
            index = 18;
        }
        self->animCurFrame = index;
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            self->step = 3;
        }
        CheckFieldCollisionY(*sensors_move_y, 3);
        CheckFieldCollision(sensors_move_x, 2);
        break;
    }
}
