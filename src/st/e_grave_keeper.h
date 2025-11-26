// SPDX-License-Identifier: AGPL-3.0-or-later
extern EInit g_EInitGraveKeeper;
static s16 sensors_ground[] = {0, 23, 0, 4, 8, -4, -16, 0};
static s16 D_us_801826CC[] = {0, 23, 8, 0};
static s16 D_us_801826D4[] = {-12, 16, 0, -16};
static u8 anim_walk[] = {
    0x0C, 0x01, 0x06, 0x02, 0x0C, 0x03, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00};
static u8 anim_jump[] = {
    0x01, 0x01, 0x02, 0x06, 0x03, 0x07, 0x01, 0x08, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_punch[] = {
    0x04, 0x01, 0x04, 0x04, 0x16, 0x05, 0x08, 0x04, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_dash[] = {
    0x08, 0x01, 0x02, 0x02, 0x03, 0x03, 0x02, 0x01, 0x02, 0x08, 0xFF, 0x00};
static u8 anim_stand[] = {
    0x08, 0x0B, 0x08, 0x0C, 0x08, 0x0D, 0x08, 0x01, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_duck[] = {
    0x01, 0x01, 0x04, 0x0D, 0x04, 0x0C, 0x04, 0x0B, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_kick_land[] = {
    0x03, 0x06, 0x03, 0x07, 0x03, 0x06, 0x04, 0x01, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_kick[] = {0x02, 0x01, 0x02, 0x02, 0x03, 0x03, 0x02, 0x02,
                         0x08, 0x08, 0x18, 0x09, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_death[] = {0x06, 0x01, 0x08, 0x0E, 0x06, 0x0F, 0x06, 0x10,
                          0x06, 0x11, 0x06, 0x12, 0x16, 0x13, 0xFF, 0x00};

extern EInit g_EInitGraveKeeperHitbox;

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight}
static s16 hitbox_data[][4] = {
    // all other anim frames
    {0, 0, 0, 0},
    // anim frame 5
    {-17, -5, 8, 4},
    // anim frame 9
    {-16, 0, 8, 4},
    // anim frame 10
    {-18, 16, 8, 4}};

typedef enum GraveKeeperStep {
    GRAVE_KEEPER_INIT = 0,
    GRAVE_KEEPER_CHECK_SENSORS = 1,
    GRAVE_KEEPER_WAIT_FOR_AGGRO = 2,
    GRAVE_KEEPER_STAND = 3,
    GRAVE_KEEPER_WALK_TOWARD = 4,
    GRAVE_KEEPER_WALK_AWAY = 5,
    GRAVE_KEEPER_JUMP_LANDED = 6,
    GRAVE_KEEPER_WALL_JUMP = 7,
    GRAVE_KEEPER_PUNCH_CLOSE = 8,
    GRAVE_KEEPER_PUNCH_DASH = 9,
    GRAVE_KEEPER_JUMP_KICK = 10,
    GRAVE_KEEPER_GROUND_KICK = 11,
    GRAVE_KEEPER_DEATH = 12,
    GRAVE_KEEPER_DUCK = 13
};

// Spawns dust at the Grave Keeper's feet in various scenarios
// such as standing up from idle, dashing, and landing after jumping
static void SpawnDustParticles(void) {
    Entity* dustEntity;

    dustEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (dustEntity != NULL) {
        CreateEntityFromEntity(
            E_INTENSE_EXPLOSION, g_CurrentEntity, dustEntity);
        dustEntity->posY.i.hi += 0x18;
        if (g_CurrentEntity->facingLeft) {
            dustEntity->posX.i.hi -= 8;
        } else {
            dustEntity->posX.i.hi += 8;
        }

        dustEntity->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        dustEntity->scaleX = dustEntity->scaleY = 0xA0;
        dustEntity->zPriority = g_CurrentEntity->zPriority + 2;
        dustEntity->params = 0x10;
    }
}

void func_us_801D12E0(u32 resetColliderEffects) {
    Collider collider;
    s32 posX;
    s32 posY;

    posX = g_CurrentEntity->posX.i.hi;
    posY = g_CurrentEntity->posY.i.hi;
    if (g_CurrentEntity->velocityX > 0) {
        posX += 0x10;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (resetColliderEffects) {
            collider.effects = EFFECT_NONE;
        }
        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->posX.i.hi += collider.unk14;
            g_CurrentEntity->facingLeft ^= 1;
            g_CurrentEntity->ext.graveKeeper.unk82 = 0;
            g_CurrentEntity->ext.graveKeeper.resetColliderEffects = 1;
            SetStep(GRAVE_KEEPER_JUMP_KICK);
            return;
        }

        posX += g_Tilemap.scrollX.i.hi;
        if (g_Tilemap.width < posX) {
            g_CurrentEntity->facingLeft ^= 1;
            g_CurrentEntity->ext.graveKeeper.unk82 = 0;
            g_CurrentEntity->ext.graveKeeper.resetColliderEffects = 1;
            SetStep(GRAVE_KEEPER_JUMP_KICK);
        }
    } else {
        posX -= 0x10;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (resetColliderEffects) {
            collider.effects = EFFECT_NONE;
        }
        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->posX.i.hi += collider.unk1C;
            g_CurrentEntity->facingLeft ^= 1;
            g_CurrentEntity->ext.graveKeeper.unk82 = 0;
            g_CurrentEntity->ext.graveKeeper.resetColliderEffects = 1;
            SetStep(GRAVE_KEEPER_JUMP_KICK);
            return;
        }

        posX += g_Tilemap.scrollX.i.hi;
        if (posX < g_Tilemap.x) {
            g_CurrentEntity->facingLeft ^= 1;
            g_CurrentEntity->ext.graveKeeper.unk82 = 0;
            g_CurrentEntity->ext.graveKeeper.resetColliderEffects = 1;
            SetStep(GRAVE_KEEPER_JUMP_KICK);
        }
    }
}

void EntityGraveKeeper(Entity* self) {
    Entity* entity;
    Entity* player;
    s32 collisionDetected;
    s32 playerMovingSameDirection;
    s32 distanceToPlayer;
    s32 var_s5;
    s32 pad[9];

    if (self->flags & FLAG_DEAD && self->step != 0xC) {
        entity = self + 1;
        DestroyEntity(entity);
        self->hitboxState = 0;
        SetStep(GRAVE_KEEPER_DEATH);
    }

    switch (self->step) {
    case GRAVE_KEEPER_INIT:
        InitializeEntity(g_EInitGraveKeeper);
        self->animCurFrame = 0xB;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_GRAVE_KEEPER_HITBOX, entity);
#ifdef STAGE_IS_ARE
        self->zPriority = 0x5C;
#endif
        // fallthrough
    case GRAVE_KEEPER_CHECK_SENSORS:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            SetStep(GRAVE_KEEPER_WAIT_FOR_AGGRO);
        }
        break;
    case GRAVE_KEEPER_WAIT_FOR_AGGRO:
        self->animCurFrame = 0xB;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->hitboxHeight = 8;
        self->hitboxOffY = 8;
        // Sit and wait for player to aggro
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(GRAVE_KEEPER_STAND);
        }
        break;
    case GRAVE_KEEPER_STAND:
        // Player has aggro'd, stand and prepare to fight
        if (!self->step_s) {
            SpawnDustParticles();
            self->step_s++;
        }
        if (!AnimateEntity(anim_stand, self)) {
            self->hitboxHeight = 0x14;
            self->hitboxOffY = 0;
            SetStep(GRAVE_KEEPER_WALK_TOWARD);
        }
        break;
    case GRAVE_KEEPER_WALK_TOWARD:
    case GRAVE_KEEPER_WALK_AWAY:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }
        UnkCollisionFunc2(D_us_801826CC);
        if (!AnimateEntity(anim_walk, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.graveKeeper.unk82 = 1;
        }

        if (self->facingLeft) {
            self->velocityX = FIX(0.75);
        } else {
            self->velocityX = FIX(-0.75);
        }

        if (self->step == 5) {
            // walk backwards away from player
            self->velocityX = -self->velocityX;
        }

        switch (self->step) {
        case GRAVE_KEEPER_WALK_TOWARD:
            // If we're too close, walk backwards away from player
            if (GetDistanceToPlayerX() < 0x40) {
                SetStep(GRAVE_KEEPER_WALK_AWAY);
            }

            // BUG: This may be uninitialised!
            if (collisionDetected & 0x80) {
                collisionDetected = UnkCollisionFunc(D_us_801826D4, 2);
                if (collisionDetected & 2) {
                    SetStep(GRAVE_KEEPER_WALL_JUMP);
                }
            }
            break;
        case GRAVE_KEEPER_WALK_AWAY:
            // If we're too far away, walk towards player
            if (GetDistanceToPlayerX() > 0x80) {
                SetStep(GRAVE_KEEPER_WALK_TOWARD);
            }
            break;
        }

        if (self->facingLeft != (GetSideToPlayer() & 1)) {
            player = &PLAYER;
            distanceToPlayer = GetDistanceToPlayerX();
            // BUG: this goes unused
            var_s5 = PLAYER.posY.i.hi - self->posY.i.hi;
            if ((PLAYER.step_s & 0x40) && distanceToPlayer < 0x30) {
                if (PLAYER.step == Player_Crouch) {
                    self->ext.graveKeeper.unk82 = 2;
                    SetStep(GRAVE_KEEPER_WALL_JUMP);
                } else {
                    // If we're walking away and the player attempts to attack
                    // close while standing, we can duck the attack
                    SetStep(GRAVE_KEEPER_DUCK);
                }
            } else if (self->ext.graveKeeper.unk82) {
                playerMovingSameDirection = 0;
                self->ext.graveKeeper.unk82 = 0;
                if (self->facingLeft) {
                    if (player->velocityX <= 0) {
                        playerMovingSameDirection |= 1;
                    }
                } else if (player->velocityX >= 0) {
                    playerMovingSameDirection |= 1;
                }

                if (PLAYER.step == Player_Jump && distanceToPlayer > 0x40) {
                    if (playerMovingSameDirection & 1) {
                        self->ext.graveKeeper.unk82 = 0;
                    } else {
                        self->ext.graveKeeper.unk82 = 1;
                    }
                    SetStep(GRAVE_KEEPER_JUMP_KICK);
                } else if (distanceToPlayer < 0x40) {
                    if (!playerMovingSameDirection & 1) {
                        SetStep(GRAVE_KEEPER_GROUND_KICK);
                    } else {
                        SetStep(GRAVE_KEEPER_PUNCH_CLOSE);
                    }
                } else if (distanceToPlayer < 0x100) {
                    if (!playerMovingSameDirection & 1) {
                        SetStep(GRAVE_KEEPER_JUMP_KICK);
                    } else {
                        SetStep(GRAVE_KEEPER_PUNCH_DASH);
                    }
                }
            }
        }
        break;
    case GRAVE_KEEPER_DUCK:
        if (!self->step_s) {
            SpawnDustParticles();
            self->step_s++;
        }
        self->hitboxHeight = 8;
        self->hitboxOffY = 8;
        if (!AnimateEntity(anim_duck, self) && !(PLAYER.step_s & 0x40)) {
            SetStep(GRAVE_KEEPER_STAND);
        }
        break;
    case GRAVE_KEEPER_WALL_JUMP:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_jump, self)) {
                if (self->facingLeft) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
                self->velocityY = FIX(-4.0);
                if (self->ext.graveKeeper.unk82 & 2) {
                    self->velocityX = -self->velocityX;
                }
                SetSubStep(1);
            }
            break;
        case 1:
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                // We've hit the ground so return back to walk phase
                PlaySfxPositional(SFX_STOMP_HARD_B);
                SetStep(GRAVE_KEEPER_WALK_TOWARD);
            } else {
                func_us_801D12E0(self->ext.graveKeeper.resetColliderEffects);
            }
        }
        break;
    case GRAVE_KEEPER_PUNCH_CLOSE:
        // Player is close enough to punch from stationary
        if (!AnimateEntity(anim_punch, self)) {
            if (Random() & 1) {
                SetStep(GRAVE_KEEPER_WALK_TOWARD);
            } else {
                SetStep(GRAVE_KEEPER_GROUND_KICK);
            }
        }

        if (self->pose == 2 && !self->poseTimer) {
            PlaySfxPositional(SFX_GRAVE_KEEPER_HIYAH);
        }
        break;
    case GRAVE_KEEPER_PUNCH_DASH:
        // Player is farther away, we need to dash punch
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_dash, self)) {
                PlaySfxPositional(SFX_GRAVE_KEEPER_HIYAH);
                if (self->facingLeft) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
                self->ext.graveKeeper.walkTimer = 0x40;
                self->poseTimer = 0;
                self->pose = 0;
                self->step_s++;
            }
            break;
        case 2:
            self->velocityX -= self->velocityX / 0x20;
            if (!AnimateEntity(anim_punch, self)) {
                SetStep(GRAVE_KEEPER_WALK_TOWARD);
                break;
            }
            if (self->pose == 2 && !self->poseTimer) {
                PlaySfxPositional(SFX_WEAPON_SWISH_C);
            }
            if (self->pose == 4) {
                self->velocityX = 0;
            }
            // fallthrough
        case 1:
            collisionDetected = UnkCollisionFunc2(D_us_801826CC);
            if (collisionDetected & 0x80) {
                self->ext.graveKeeper.unk82 = 0;
                SetStep(GRAVE_KEEPER_JUMP_KICK);
            }

            if (!--self->ext.graveKeeper.walkTimer) {
                SetStep(GRAVE_KEEPER_WALK_TOWARD);
                break;
            }

            if (GetDistanceToPlayerX() < 0x30) {
                self->step_s = 2;
            }

            if (self->step_s == 1 && !(g_Timer & 7)) {
                SpawnDustParticles();
            }
        }
        break;
    case GRAVE_KEEPER_JUMP_KICK:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_jump, self)) {
                PlaySfxPositional(SFX_GRAVE_KEEPER_GRAAH);
                if (self->ext.graveKeeper.unk82 & 1) {
                    // Player is jumping away, do a bigger jump
                    self->velocityX = FIX(3.0);
                    self->velocityY = FIX(-6.0);
                } else {
                    self->velocityX = FIX(2.5);
                    self->velocityY = FIX(-4.0);
                }

                if (!self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->ext.graveKeeper.kickHitPlayer = 0;
                self->step_s++;
            }
            break;
        case 1:
            entity = self + 1;
            if (entity->hitFlags & 0x80) {
                // We hit the player, bounce back slightly and land
                PlaySfxPositional(SFX_WEAPON_HIT_A);
                self->velocityX = -self->velocityX / 2;
                self->velocityY = FIX(-3.0);
                self->ext.graveKeeper.kickHitPlayer = 1;
                self->step_s++;
            }
            // fallthrough
        case 2:
            if (self->velocityY > FIX(65535.0)) {
                self->velocityY -= FIX(0.0625);
                self->animCurFrame = 0xA;
            }

            if (self->velocityY > FIX(1.0)) {
                collisionDetected = UnkCollisionFunc3(sensors_ground);
                if (collisionDetected & 1) {
                    self->ext.graveKeeper.resetColliderEffects = 0;
                    PlaySfxPositional(SFX_STOMP_HARD_B);
                    SetStep(GRAVE_KEEPER_JUMP_LANDED);
                    break;
                }
            } else {
                MoveEntity();
                self->velocityY += FIX(0.25);
            }

            if (!self->ext.graveKeeper.kickHitPlayer) {
                func_us_801D12E0(self->ext.graveKeeper.resetColliderEffects);
            }
            break;
        }
        break;
    case GRAVE_KEEPER_JUMP_LANDED:
        // We've landed back on the ground, return to walk phase
        if (!self->step_s) {
            SpawnDustParticles();
            self->step_s++;
        }
        if (!AnimateEntity(anim_kick_land, self)) {
            SetStep(GRAVE_KEEPER_WALK_TOWARD);
        }
        break;
    case GRAVE_KEEPER_GROUND_KICK:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
        }
        if (self->pose == 4 && !self->poseTimer) {
            PlaySfxPositional(SFX_GRAVE_KEEPER_HIYAH);
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
        }

        UnkCollisionFunc2(D_us_801826CC);
        self->velocityX -= self->velocityX / 0x20;
        if (self->velocityX != 0 && !(g_Timer & 7)) {
            SpawnDustParticles();
        }

        if (!AnimateEntity(anim_kick, self)) {
            SetStep(GRAVE_KEEPER_WALK_TOWARD);
        }
        break;
    case GRAVE_KEEPER_DEATH:
        // Death becomes us
        switch (self->step_s) {
        case 0:
            self->velocityX = FIX(2.0);
            if ((GetSideToPlayer() & 1) ^ 1) {
                self->velocityX = -self->velocityX;
            }
            PlaySfxPositional(SFX_GRAVE_KEEPER_DEATH);
            self->step_s++;
            break;
        case 1:
            UnkCollisionFunc2(D_us_801826CC);
            self->velocityX -= self->velocityX / 0x20;
            if (!AnimateEntity(anim_death, self)) {
                self->step_s++;
            }
            break;
        case 2:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 3;
            }
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            DestroyEntity(self);
            break;
        }
        break;
    }
}

void EntityGraveKeeperHitbox(Entity* self) {
    Entity* parent;
    s32 idx;
    s16* ptr;

    if (!self->step_s) {
        InitializeEntity(g_EInitGraveKeeperHitbox);
    }

    parent = self - 1;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    self->facingLeft = parent->facingLeft;

    switch (parent->animCurFrame) {
    case 5:
        idx = 1 * LEN(hitbox_data);
        break;
    case 9:
        idx = 2 * LEN(hitbox_data);
        break;
    case 10:
        idx = 3 * LEN(hitbox_data);
        break;
    default:
        idx = 0 * LEN(hitbox_data);
        break;
    }

    ptr = hitbox_data[0] + idx;
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
    if (parent->entityId != E_GRAVE_KEEPER) {
        DestroyEntity(self);
    }
}
