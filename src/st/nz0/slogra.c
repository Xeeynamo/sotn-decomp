#include "nz0.h"
#include "sfx.h"

#define GAIBON self[8]

typedef enum {
    SLOGRA_INIT,
    SLOGRA_FLOOR_ALIGN,
    SLOGRA_IDLE,
    SLOGRA_TAUNT_WITH_SPEAR,
    SLOGRA_SPEAR_POKE,
    SLOGRA_SPEAR_FIRE,
    SLOGRA_ATTACK,
    SLOGRA_KNOCKBACK = 8,
    SLOGRA_WALKING_WITH_SPEAR,
    SLOGRA_TAUNT_WITHOUT_SPEAR,
    SLOGRA_WALKING_WITHOUT_SPEAR,
    SLOGRA_LOSE_SPEAR,
    SLOGRA_GAIBON_COMBO_ATTACK,
    SLOGRA_DYING = 16,
    SLOGRA_DEBUG = 255,
} SlograSteps;

typedef enum {
    SLOGRA_FIRE_FACE_PLAYER,
    SLOGRA_FIRE_PROJECTILE,
    SLOGRA_FIRE_COOLDOWN,
    SLOGRA_FIRE_END,
} SlograSpearFireSubSteps;

typedef enum {
    SLOGRA_COMBO_ATTACK_START,
    SLOGRA_COMBO_ATTACK_PLUNGE,
    SLOGRA_COMBO_ATTACK_COOLDOWN,
} SlograComboAttackSubSteps;

typedef enum {
    SLOGRA_KNOCKBACK_FLOOR_CHECK,
    SLOGRA_KNOCKBACK_ACCEL,
    SLOGRA_KNOCKBACK_ARC,
} SlograKnockbackSubSteps;

typedef enum {
    SLOGRA_DYING_START,
    SLOGRA_DYING_EXPLODING,
    SLOGRA_DYING_END,
} SlograDyingSubSteps;

s32 EntitySlograSpecialCollision(u16* unused) {
    /**
     * This function keeps Slogra between safe
     * boundaries of the room when he gets hit by the player.
     * EntitySlogra passes D_8018105C to this function but it's unused
     */
    s32 ret = 0;
    s32 slograPosX;

    MoveEntity();
    g_CurrentEntity->velocityY += FIX(0.25);
    slograPosX = g_CurrentEntity->posX.i.hi + g_Tilemap.scrollX.i.hi;

    if (g_CurrentEntity->velocityX > 0 && slograPosX > 896) {
        g_CurrentEntity->posX.i.hi = 896 - g_Tilemap.scrollX.i.hi;
    }

    if (g_CurrentEntity->velocityX < 0 && slograPosX < 64) {
        g_CurrentEntity->posX.i.hi = 64 - g_Tilemap.scrollX.i.hi;
    }

    if (g_CurrentEntity->posY.i.hi + g_Tilemap.scrollY.i.hi > 416) {
        ret = 1;
        g_CurrentEntity->posY.i.hi = 416 - g_Tilemap.scrollY.i.hi;
        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;
    }

    return ret;
}

void EntitySlogra(Entity* self) {
    Entity* newEntity;
    s32 entityOnFloor;
    u8* animation;
    s32 hitPoints;
    s8* hitbox;

    self->ext.GS_Props.pickupFlag = 0;

    FntPrint("beri_flag %x\n", g_BossFlag);

    if (self->step >= SLOGRA_TAUNT_WITH_SPEAR) {
        if ((self->hitFlags & 3) && (self->step != SLOGRA_KNOCKBACK)) {
            SetStep(SLOGRA_KNOCKBACK);
        }
        if (self->ext.GS_Props.nearDeath == false) {
            hitPoints = g_api.enemyDefs[243].hitPoints;
            if (hitPoints < 0) {
                hitPoints += 3;
            }
            if ((self->hitPoints < (hitPoints >> 2)) &&
                (self->step != SLOGRA_LOSE_SPEAR)) {
                SetStep(SLOGRA_LOSE_SPEAR);
            }
        }
    }

    if ((self->flags & FLAG_DEAD) && (self->step != SLOGRA_DYING)) {
        SetStep(SLOGRA_DYING);
    }

    if (GAIBON.ext.GS_Props.grabedAscending) {
        if (self->step != SLOGRA_DYING) {
            if (self->step != SLOGRA_GAIBON_COMBO_ATTACK) {
                SetStep(SLOGRA_GAIBON_COMBO_ATTACK);
            }
        }
    }

    switch (self->step) {
    case SLOGRA_INIT:
        InitializeEntity(D_80180D0C);
        CreateEntityFromCurrentEntity(E_SLOGRA_SPEAR, &self[1]);

    case SLOGRA_FLOOR_ALIGN:
        if (EntitySlograSpecialCollision(D_8018105C) & 1) {
            SetStep(SLOGRA_IDLE);
        }
        break;

    case SLOGRA_IDLE:
        AnimateEntity(D_80181080, self);
        if (self->hitFlags != 0) {
            g_BossFlag |= BOSS_FLAG_FIGHT_BEGIN;
        }
        if (g_BossFlag & BOSS_FLAG_FIGHT_BEGIN) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        break;

    case SLOGRA_TAUNT_WITH_SPEAR:
        if (AnimateEntity(D_80181080, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        break;

    case SLOGRA_WALKING_WITH_SPEAR:
        if (self->step_s == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->ext.GS_Props.attackMode != 0) { // shoot projectile ?
                self->ext.GS_Props.flag = 1;
            } else {
                self->ext.GS_Props.flag = 0;
            }
            self->ext.GS_Props.timer = 128;
            self->step_s++;
        }
        AnimateEntity(D_80181074, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;

        if (self->facingLeft != self->ext.GS_Props.flag) {
            self->velocityX = FIX(0.75);
        } else {
            self->velocityX = FIX(-0.75);
        }
        func_801BCF74(&D_8018106C);
        if (self->ext.GS_Props.flag == 0) {
            if (GetDistanceToPlayerX() < 72) {
                if (self->ext.GS_Props.attackMode == 0) {
                    self->ext.GS_Props.timer = 1;
                } else {
                    self->ext.GS_Props.flag ^= 1;
                }
            }
        }
        if (self->ext.GS_Props.flag != 0) {
            if (GetDistanceToPlayerX() > 112) {
                if (self->ext.GS_Props.attackMode != 0) {
                    self->ext.GS_Props.timer = 1;
                } else {
                    self->ext.GS_Props.flag ^= 1;
                }
            }
        }
        if (!(Random() % 64)) {
            SetStep(SLOGRA_TAUNT_WITH_SPEAR);
        }
        if (--self->ext.GS_Props.timer == 0) {
            if (self->ext.GS_Props.attackMode != 0) {
                SetStep(SLOGRA_SPEAR_FIRE);
            } else {
                SetStep(SLOGRA_SPEAR_POKE);
            }

            self->ext.GS_Props.attackMode ^= 1;
        }
        break;

    case SLOGRA_SPEAR_POKE:
        if (self->step_s == 0) {
            func_801C29B0(NA_SE_EN_SLOGRA_HISSING);
            self->step_s++;
        }
        if (AnimateEntity(D_801810B4, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
            func_801C29B0(NA_SE_EN_SLOGRA_SPEAR_SLASH);
        }
        break;

    case SLOGRA_SPEAR_FIRE:
        switch (self->step_s) {
        case SLOGRA_FIRE_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;

        case SLOGRA_FIRE_PROJECTILE:
            if (AnimateEntity(D_8018108C, self) == 0) {
                func_801C29B0(NA_SE_EN_SLOGRA_SPEAR_PROJECTILE);
                newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_SLOGRA_SPEAR_PROJECTILE, self, newEntity);
                    if (self->facingLeft != 0) {
                        newEntity->posX.i.hi += 68;
                    } else {
                        newEntity->posX.i.hi -= 68;
                    }
                    newEntity->posY.i.hi -= 6;
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->zPriority = self->zPriority + 1;
                }
                SetSubStep(SLOGRA_FIRE_COOLDOWN);
            }
            break;

        case SLOGRA_FIRE_COOLDOWN:
            if (AnimateEntity(D_8018109C, self) == 0) {
                SetSubStep(SLOGRA_FIRE_END);
            }
            break;

        case SLOGRA_FIRE_END: // go back to standing position
            if (AnimateEntity(D_801810A8, self) == 0) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
            }
            break;
        }
        break;

    case SLOGRA_KNOCKBACK: // Knocked up, Chance to get picked up by gaibon
        switch (self->step_s) {
        case SLOGRA_KNOCKBACK_FLOOR_CHECK:
            if (EntitySlograSpecialCollision(D_8018105C) & 1) {
                self->step_s++;
            }
            break;

        case SLOGRA_KNOCKBACK_ACCEL:
            self->velocityY = FIX(-4);
            if (!(GetSideToPlayer() & 1)) {
                self->velocityX = FIX(-0.5);
            } else {
                self->velocityX = FIX(0.5);
            }
            func_801C29B0(NA_SE_EN_SLOGRA_HURT);
            self->step_s++;

        case SLOGRA_KNOCKBACK_ARC:
            if (0x18000 > self->velocityY) {
                self->ext.GS_Props.pickupFlag = 1;
            }
            entityOnFloor = EntitySlograSpecialCollision(D_8018105C);
            self->velocityY -= 0x2400;
            if (self->ext.GS_Props.nearDeath != 0) {
                animation = &D_80181114;
            } else {
                animation = &D_801810D4;
            }
            if (AnimateEntity(animation, self) == 0 && entityOnFloor & 1) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
                if (self->ext.GS_Props.nearDeath != 0) {
                    SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
                }
            }
        }
        break;

    case SLOGRA_LOSE_SPEAR:
        entityOnFloor = EntitySlograSpecialCollision(D_8018105C);
        if (AnimateEntity(D_801810E8, self) == 0) {
            if (entityOnFloor & 1) {
                SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
            }
        }
        if (self->animFrameIdx >= 2) {
            self->ext.GS_Props.nearDeath = 1;
        }
        break;

    case SLOGRA_TAUNT_WITHOUT_SPEAR:
        if (AnimateEntity(D_80181108, self) == 0) {
            SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
        }
        break;

    case SLOGRA_WALKING_WITHOUT_SPEAR:
        if (self->step_s == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.GS_Props.flag = 1;
            self->ext.GS_Props.timer = 128;
            self->step_s++;
        }
        AnimateEntity(D_801810FC, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;

        if (!(self->facingLeft == self->ext.GS_Props.flag)) {
            self->velocityX = FIX(0.75);
        } else {
            self->velocityX = FIX(-0.75);
        }

        func_801BCF74(&D_8018106C);
        if (self->ext.GS_Props.flag == 0) {
            if (GetDistanceToPlayerX() < 72) {
                self->ext.GS_Props.flag ^= 1;
            }
            if (self->ext.GS_Props.flag != 0) {
                if (GetDistanceToPlayerX() > 112) {
                    self->ext.GS_Props.flag ^= 1;
                }
            }
        } else {
            if (GetDistanceToPlayerX() > 112) {
                self->ext.GS_Props.flag ^= 1;
            }
        }
        if (!(Random() % 64)) {
            SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
        }
        if (--self->ext.GS_Props.timer == 0) {
            SetStep(SLOGRA_ATTACK);
        }
        break;

    case SLOGRA_ATTACK: // Attack without spear
        if (AnimateEntity(D_80181128, self) == 0) {
            SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
        }
        if (self->animFrameIdx == 7 && self->animFrameDuration == 0) {
            func_801C29B0(NA_SE_EN_SLOGRA_BEAK_ATTACK);
        }
        break;

    case SLOGRA_GAIBON_COMBO_ATTACK:
        switch (self->step_s) {
        case SLOGRA_COMBO_ATTACK_START: // inmobilize, Gaibon picks him up
            if (!GAIBON.ext.GS_Props.grabedAscending) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->step_s++;
            }
            break;

        case SLOGRA_COMBO_ATTACK_PLUNGE:
            if (self->ext.GS_Props.nearDeath != 0) {
                AnimateEntity(D_80181140, self);
            } else {
                AnimateEntity(D_80181158, self);
            }

            MoveEntity();
            self->velocityY += FIX(0.25);
            if (self->posY.i.hi + g_Tilemap.scrollY.i.hi > 416) {
                self->posY.i.hi = 416 - g_Tilemap.scrollY.i.hi;
                func_801C29B0(SFX_DOOR_CLOSE_A); // Slogra Floor Stomp
                g_api.func_80102CD8(1);
                self->ext.GS_Props.timer = 16;
                self->step_s++;
            }
            break;

        case SLOGRA_COMBO_ATTACK_COOLDOWN:
            if (--self->ext.GS_Props.timer == 0) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
                if (self->ext.GS_Props.nearDeath != 0) {
                    SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
                }
            }
            break;
        }
        break;

    case SLOGRA_DYING:
        switch (self->step_s) {
        case SLOGRA_DYING_START:
            self->hitboxState = 0;
            if (self->ext.GS_Props.nearDeath == 0) {
                self->ext.GS_Props.nearDeath = 1;
            }
            self->ext.GS_Props.timer = 64;
            func_801C29B0(NA_SE_EN_SLOGRA_DEATH_EXPLOSION);
            self->step_s++;

        case SLOGRA_DYING_EXPLODING:
            EntitySlograSpecialCollision(D_8018105C);
            AnimateEntity(D_80181150, self);
            if (!(g_Timer % 4)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                    newEntity->posX.i.hi -= 16 - (Random() & 31);
                    newEntity->posY.i.hi -= 16 - (Random() & 31);
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->params = 1;
                }
            }

            if (--self->ext.GS_Props.timer == 0) {
                self->step_s++;
            }
            break;

        case SLOGRA_DYING_END:
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 3;
                newEntity->posY.i.hi += 16;
            }
            g_BossFlag |= BOSS_FLAG_SLOGRA_DEAD;
            DestroyEntity(self);
            return;
        }
        break;

    case SLOGRA_DEBUG:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params == 0) {
                self->animCurFrame++;
                self->params |= 1;
            } else {
                break;
            }
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
    hitbox = &D_801811B8[self->animCurFrame][D_80181178];
    hitbox--;
    hitbox++;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}

void EntitySlograSpear(Entity* self) {
    s8* hitbox;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D18);

    case 1:
        self->facingLeft = self[-1].facingLeft;
        self->posX.i.hi = self[-1].posX.i.hi;
        self->posY.i.hi = self[-1].posY.i.hi;
        hitbox = D_801811E0;
        hitbox += 4 * D_80181218[self[-1].animCurFrame];
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (self[-1].ext.GS_Props.nearDeath != 0) {
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->drawFlags = FLAG_DRAW_ROTZ;
            self->hitboxState = 0;
            if (self->facingLeft != 0) {
                self->velocityX = FIX(-2.25);
            } else {
                self->velocityX = FIX(2.25);
            }
            self->velocityY = FIX(-4);
            self->animCurFrame = 0x23;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.15625);
            self->rotZ += 0x80;
            if (!(self->rotZ & 0xFFF)) {
                func_801C29B0(SFX_ARROW_SHOT_A);
            }
        }
    }
}

// projectile fired from slogra's spear
void EntitySlograSpearProjectile(Entity* self) {
    Entity* entity;

    if (self->flags & FLAG_DEAD) {
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
        InitializeEntity(D_80180D24);
        if (self->facingLeft == 0) {
            self->velocityX = FIX(-4);
        } else {
            self->velocityX = FIX(4);
        }

    case 1:
        if (AnimateEntity(D_80181160, self) == 0) {
            SetStep(SLOGRA_IDLE);
        }
        break;

    case 2:
        MoveEntity();
        AnimateEntity(D_80181170, self);
        break;
    }
}
