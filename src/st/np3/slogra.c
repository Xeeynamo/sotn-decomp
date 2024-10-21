// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"
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
    SLOGRA_GAIBON_RETREAT,
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
    SLOGRA_DYING_START,
    SLOGRA_DYING_EXPLODING,
    SLOGRA_DYING_END,
} SlograDyingSubSteps;

void EntitySlogra(Entity* self) {
    Entity* newEntity;
    s32 hitPoints;
    u8* animation;
    s8* hitbox;

    self->ext.GS_Props.pickupFlag = 0;

    if (self->step != SLOGRA_INIT) {
        if ((self->hitFlags & 3) && (self->step != SLOGRA_KNOCKBACK)) {
            SetStep(SLOGRA_KNOCKBACK);
        }
        if (self->ext.GS_Props.nearDeath == 0) {
            hitPoints = g_api.enemyDefs[243].hitPoints;
            if (hitPoints < 0) {
                hitPoints += 3;
            }
            if ((self->hitPoints < (hitPoints >> 2)) &&
                (self->step != SLOGRA_LOSE_SPEAR)) {
                self->hitboxState = 0;
                PlaySfxPositional(SFX_SLOGRA_ROAR_DEFEAT);
                SetStep(SLOGRA_LOSE_SPEAR);
            }
        }
        if (GAIBON.ext.GS_Props.grabedAscending != 0) {
            if ((self->step != SLOGRA_DYING) &&
                (self->step != SLOGRA_GAIBON_COMBO_ATTACK)) {
                SetStep(SLOGRA_GAIBON_COMBO_ATTACK);
            }
        }
        if (D_801812CC != 0) {
            self->hitboxState = 0;
            if (self->step != SLOGRA_GAIBON_RETREAT) {
                SetStep(SLOGRA_GAIBON_RETREAT);
            }
        }
    }

    switch (self->step) {
    case SLOGRA_INIT:
        if (g_CastleFlags[SG_KILL_ALCH] || g_CastleFlags[SG_RETR_ENTR]) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_EInitSlograNP3);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        CreateEntityFromCurrentEntity(E_SLOGRA_SPEAR, &self[1]);

    case SLOGRA_FLOOR_ALIGN:
        if (UnkCollisionFunc3(&D_801812D0) & 1) {
            SetStep(SLOGRA_IDLE);
        }
        break;

    case SLOGRA_IDLE:
        AnimateEntity(D_801812F4, self);
        if (GetDistanceToPlayerX() < 96) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        break;

    case SLOGRA_TAUNT_WITH_SPEAR:
        if (AnimateEntity(D_801812F4, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        break;

    case SLOGRA_WALKING_WITH_SPEAR:
        if (self->step_s == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->ext.GS_Props.attackMode != 0) {
                self->ext.GS_Props.flag = 1;
            } else {
                self->ext.GS_Props.flag = 0;
            }
            self->ext.GS_Props.timer = 128;
            self->step_s++;
        }
        AnimateEntity(D_801812E8, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->facingLeft != self->ext.GS_Props.flag) {
            self->velocityX = FIX(0.75);
        } else {
            self->velocityX = FIX(-0.75);
        }
        UnkCollisionFunc2(&D_801812E0);
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
        self->ext.GS_Props.timer--;
        if (self->ext.GS_Props.timer == 0) {
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
            PlaySfxPositional(SFX_SLOGRA_ROAR);
            self->step_s++;
        }
        if (AnimateEntity(D_80181328, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
            PlaySfxPositional(SFX_BOSS_WING_FLAP);
        }
        break;

    case SLOGRA_SPEAR_FIRE:
        switch (self->step_s) {
        case SLOGRA_FIRE_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;

        case SLOGRA_FIRE_PROJECTILE:
            if (AnimateEntity(D_80181300, self) == 0) {
                PlaySfxPositional(SFX_FM_EXPLODE_SWISHES);
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
            if (AnimateEntity(D_80181310, self) == 0) {
                SetSubStep(SLOGRA_FIRE_END);
            }
            break;

        case SLOGRA_FIRE_END:
            if (AnimateEntity(D_8018131C, self) == 0) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
            }
            break;
        }
        break;

    case SLOGRA_KNOCKBACK:
        if (self->step_s == 0) {
            PlaySfxPositional(NA_SE_EN_SLOGRA_HURT);
            self->step_s++;
        }
        if (self->ext.GS_Props.nearDeath != 0) {
            animation = &D_80181388;
        } else {
            animation = &D_80181348;
        }
        if (AnimateEntity(animation, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
            if (self->ext.GS_Props.nearDeath != 0) {
                SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
            }
        }
        break;

    case SLOGRA_LOSE_SPEAR:
        if (AnimateEntity(D_8018135C, self) == 0) {
            D_801812CC = 1;
            SetStep(SLOGRA_GAIBON_RETREAT);
        }
        if (self->animFrameIdx >= 2) {
            self->ext.GS_Props.nearDeath = 1;
        }
        break;

    case SLOGRA_TAUNT_WITHOUT_SPEAR:
        if (AnimateEntity(D_8018137C, self) == 0) {
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

        AnimateEntity(D_80181370, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->facingLeft != self->ext.GS_Props.flag) {
            self->velocityX = FIX(0.75);
        } else {
            self->velocityX = FIX(-0.75);
        }

        UnkCollisionFunc2(&D_801812E0);
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
            if (GetDistanceToPlayerX() >= 0x71) {
                self->ext.GS_Props.flag ^= 1;
            }
        }
        if (!(Random() % 64)) {
            SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
        }
        self->ext.GS_Props.timer--;
        if (self->ext.GS_Props.timer == 0) {
            SetStep(SLOGRA_ATTACK);
        }
        break;

    case SLOGRA_ATTACK: // Attack without spear
        if (AnimateEntity(D_8018139C, self) == 0) {
            SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
        }
        if (self->animFrameIdx == 7 && self->animFrameDuration == 0) {
            PlaySfxPositional(SFX_BONE_THROW);
        }
        break;

    case SLOGRA_GAIBON_COMBO_ATTACK: // Unused
        switch (self->step_s) {
        case SLOGRA_COMBO_ATTACK_START:
            if (GAIBON.ext.GS_Props.grabedAscending == 0) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->step_s++;
            }
            break;

        case 1:
            if (self->ext.GS_Props.nearDeath != 0) {
                AnimateEntity(D_801813B4, self);
            } else {
                AnimateEntity(D_801813CC, self);
            }

            if (UnkCollisionFunc3(&D_801812D0) & 1) {
                g_api.func_80102CD8(1);
                self->ext.GS_Props.timer = 16;
                self->step_s++;
            }
            break;

        case SLOGRA_COMBO_ATTACK_COOLDOWN:
            self->ext.GS_Props.timer--;
            if (self->ext.GS_Props.timer == 0) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
                if (self->ext.GS_Props.nearDeath != 0) {
                    SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
                }
            }
            break;
        }
        break;

    case SLOGRA_GAIBON_RETREAT:
        if (self->ext.GS_Props.nearDeath != 0) {
            AnimateEntity(D_8018137C, self);
        } else {
            AnimateEntity(D_801812F4, self);
        }
        break;

    case SLOGRA_DYING: // Unused
        switch (self->step_s) {
        case SLOGRA_DYING_START:
            self->hitboxState = 0;
            if (self->ext.GS_Props.nearDeath == 0) {
                self->ext.GS_Props.nearDeath = 1;
            }
            self->ext.GS_Props.timer = 64;
            PlaySfxPositional(SFX_STUTTER_EXPLODE_A);
            g_CastleFlags[SG_RETR_ENTR] |= 1;
            self->step_s++;

        case SLOGRA_DYING_EXPLODING:
            UnkCollisionFunc3(&D_801812D0);
            AnimateEntity(D_801813C4, self);
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
            self->ext.GS_Props.timer--;
            if (self->ext.GS_Props.timer == 0) {
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
    hitbox = D_801813EC;
    hitbox += 4 * D_8018142C[self->animCurFrame];
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}

void EntitySlograSpear(Entity* self) {
    s8* hitbox;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSlograSpearNP3);

    case 1:
        self->facingLeft = self[-1].facingLeft;
        self->posX.i.hi = self[-1].posX.i.hi;
        self->posY.i.hi = self[-1].posY.i.hi;
        hitbox = D_80181454;
        hitbox += 4 * D_8018148C[self[-1].animCurFrame];
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
            self->animCurFrame = 35;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.15625);
            self->rotZ += 0x80;
            if (!(self->rotZ & 0xFFF)) {
                PlaySfxPositional(SFX_ARROW_SHOT_A);
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
        InitializeEntity(g_EInitSlograProjectileNP3);
        if (self->facingLeft == 0) {
            self->velocityX = FIX(-4);
        } else {
            self->velocityX = FIX(4);
        }

    case 1:
        if (AnimateEntity(D_801813D4, self) == 0) {
            SetStep(SLOGRA_IDLE);
        }
        break;

    case 2:
        MoveEntity();
        AnimateEntity(D_801813E4, self);
        break;
    }
}
