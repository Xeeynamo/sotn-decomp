// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo2.h"

/**
 * Restricts the current entity's horizontal position to the boss arena.
 *
 * Accounts for horizontal velocity and tilemap scrolling when checking
 * the arena boundaries.
 */
static void func_us_801B37D0(void) {
    s32 x = g_CurrentEntity->posX.i.hi + g_Tilemap.scrollX.i.hi;

    if (g_CurrentEntity->velocityX > 0) {
        x += 8;

        if (x > 0x1B0) {
            g_CurrentEntity->posX.i.hi = 0x1A8 - g_Tilemap.scrollX.i.hi;
        }
    }

    if (g_CurrentEntity->velocityX < 0) {
        x -= 8;

        if (x < 0x50) {
            g_CurrentEntity->posX.i.hi = 0x58 - g_Tilemap.scrollX.i.hi;
        }
    }
}

extern EInit g_EInitWerewolfARE;
extern s32 D_us_80180AAC;
extern s32 D_us_80180AB0;
extern s16 werewolf_sensors[];
extern s16 werewolf_sensors_ground[];
extern u8 werewolf_anim_idle[];
extern u8 werewolf_anim_walk[];
extern u8 werewolf_anim_punch[];
extern u8 werewolf_anim_jump[];
extern u8 werewolf_anim_energy_wave[];
extern u8 werewolf_anim_slide_attack[];
extern u8 werewolf_anim_charge_init[];
extern u8 werewolf_anim_charge_wait[];
extern u8 werewolf_anim_charge_attack[];
extern u8 werewolf_anim_charge_end[];
extern u8 werewolf_anim_death_pain[];
extern u8 werewolf_anim_death_melt[];
extern u8 werewolf_anim_spin_init[];
extern s8 werewolf_base_hitboxes[][4];
extern u8 werewolf_base_hitbox_indices[];
#if TARGET == TARGET_PSP
extern s32 E_ID(WEREWOLF_ATTACK_HITBOX);
extern s32 E_ID(UNK_1D);
extern s32 E_ID(WEREWOLF_SPIN_ATTACK_AFTER_IMAGE);
extern s32 E_ID(UNK_1F);
extern s32 E_ID(WEREWOLF_DEATH_FLAMES);
extern s32 E_ID(MINOTAUR_SPIT_LIQUID);
#endif

void func_us_801B385C(Entity* self) {
    Entity* entity;
    s8* ptr;
    s32 i;
    s32 posY;
    s32 arrived;
    s16 angle;

    FntPrint("wolf_step %x\n", self->step);
    FntPrint("wolf_set_step %x\n", self->ext.werewolfARE.nextStep);
    if (self->flags & FLAG_DEAD && self->step < 0x20) {
        SetStep(0x20);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitWerewolfARE);
        self->hitboxState = 0;
        self->zPriority += 8;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID(WEREWOLF_ATTACK_HITBOX), entity);
        // fallthrough
    case 1:
        AnimateEntity(werewolf_anim_idle, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        UnkCollisionFunc3(werewolf_sensors_ground);
        switch (self->step_s) {
        case 0:
            self->palette = PAL_FLAG(PAL_FILL_WHITE);
            self->drawFlags |= ENTITY_OPACITY;
            self->blendMode = BLEND_SUB | BLEND_TRANSP;
            self->opacity = 0;
            self->step_s++;
            // fallthrough
        case 1:
            self->opacity += 4;
            if (self->opacity == 0x80) {
                self->palette = g_EInitWerewolfARE[3];
                self->blendMode = BLEND_NO;
                self->opacity = 0;
                self->step_s++;
            }
            break;
        case 2:
            self->opacity += 4;
            if (self->opacity == 0x80) {
                self->drawFlags = ENTITY_DEFAULT;
                D_us_80180AB0 = 1;
                self->step_s++;
            }
            break;
        case 3:
            if (D_us_80180AAC) {
                self->hitboxState = 3;
                SetStep(2);
            }
            break;
        }
        break;
    case 2:
        if (!self->step_s) {
            if (!self->ext.werewolfARE.moveTimer) {
                self->ext.werewolfARE.moveTimer = 0x20;
            }
            self->ext.werewolfARE.isReady = false;
            self->step_s++;
        }

        AnimateEntity(werewolf_anim_idle, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->ext.werewolfARE.moveTimer) {
            self->ext.werewolfARE.moveTimer--;
        } else {
            self->ext.werewolfARE.isReady = true;
        }

        if (self->ext.werewolfARE.targetPosX) {
            self->ext.werewolfARE.isReady = false;
            SetStep(4);
        } else if (self->ext.werewolfARE.hasNextStep) {
            self->ext.werewolfARE.isReady = false;
            self->ext.werewolfARE.hasNextStep = false;
            SetStep(self->ext.werewolfARE.nextStep);
        } else {
            entity = &PLAYER;
            i = entity->velocityX;
            if (self->facingLeft) {
                i = -i;
            }
            if (self->facingLeft == entity->facingLeft &&
                GetDistanceToPlayerX() < 0x38 && i > 0) {
                self->ext.werewolfARE.isReady = false;
                SetStep(6);
            }
        }
        break;
    case 4:
        if (!self->step_s) {
            i = self->ext.werewolfARE.targetPosX;
            entity = &PLAYER;
            if (self->posX.i.hi > entity->posX.i.hi) {
                i = entity->posX.i.hi + i;
                i += g_Tilemap.scrollX.i.hi;
                if (i > 0x190) {
                    i = 0x190;
                }
            } else {
                i = entity->posX.i.hi - i;
                i += g_Tilemap.scrollX.i.hi;
                if (i < 0x70) {
                    i = 0x70;
                }
            }
            self->ext.werewolfARE.targetPosX = i;
            i = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            i = self->ext.werewolfARE.targetPosX - i;
            if (i > 0) {
                self->velocityX = FIX(1.125);
            } else {
                self->velocityX = FIX(-1.125);
            }
            self->step_s++;
        }
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(werewolf_anim_walk, self);
        UnkCollisionFunc2(werewolf_sensors);
        arrived = false;
        i = self->posX.i.hi + g_Tilemap.scrollX.i.hi -
            self->ext.werewolfARE.targetPosX;
        if (self->velocityX > 0) {
            if (i > 0) {
                arrived = true;
            }
        } else if (i < 0) {
            arrived = true;
        }
        if (arrived) {
            self->ext.werewolfARE.targetPosX = 0;
            SetStep(2);
        }
        break;
    case 6:
        if (!AnimateEntity(werewolf_anim_punch, self)) {
            SetStep(2);
        }
        if (!self->poseTimer && self->pose == 6) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            entity = self + 3;
            i = entity->posX.i.hi - self->posX.i.hi;
            if (self->facingLeft == entity->facingLeft && abs(i) < 0x20) {
                self->ext.werewolfARE.signal = true;
            } else {
                self->ext.werewolfARE.signal = false;
            }
            entity->ext.minotaur.signal = self->ext.werewolfARE.signal ^ 1;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(werewolf_anim_jump, self)) {
                self->animCurFrame = 0x2F;
                self->velocityX = FIX(-2.0);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->velocityY = FIX(-2.0);
                SetSubStep(3);
            }
            break;
        case 3:
            if (UnkCollisionFunc3(werewolf_sensors_ground) & 1) {
                self->step_s++;
            }
            break;
        case 4:
            if (!AnimateEntity(werewolf_anim_energy_wave, self)) {
                SetStep(4);
            }
            if (!self->poseTimer && self->pose == 4) {
                PlaySfxPositional(SFX_EXPLODE_F);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_1D), self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->posY.i.hi -= 0x10;
                    entity->ext.werewolfARE.parent = self + 3;
                    entity->ext.werewolfARE.signal =
                        self->ext.werewolfARE.signal;
                }
            }
            break;
        }
        break;
    case 10:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }
        UnkCollisionFunc2(werewolf_sensors);
        if (!AnimateEntity(werewolf_anim_slide_attack, self)) {
            SetStep(2);
        }
        self->velocityX -= self->velocityX / 16;
        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(SFX_SCRAPE_B);
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }
        }
        break;
    case 12:
        if (!self->step_s) {
            if (!AnimateEntity(werewolf_anim_charge_init, self)) {
                self->ext.werewolfARE.timer = 0x80;
                self->step_s++;
            }
        } else {
            AnimateEntity(werewolf_anim_charge_wait, self);
            if (!--self->ext.werewolfARE.timer) {
                SetStep(14);
            }
        }
        break;
    case 14:
        if (self->flags & 0xF) {
            self->blendMode = BLEND_NO;
        } else {
            if (g_Timer & 1) {
                self->blendMode = BLEND_ADD | BLEND_TRANSP;
            } else {
                self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
            }
        }
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.werewolfARE.signal = false;
            self->step_s++;
            // fallthrough
        case 1:
            if (self->ext.werewolfARE.signal) {
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(werewolf_anim_charge_attack, self)) {
                SetSubStep(3);
            }
            if (!self->poseTimer && self->pose == 1) {
                if (self->facingLeft) {
                    self->velocityX = FIX(6.0);
                } else {
                    self->velocityX = FIX(-6.0);
                }
                self->ext.werewolfARE.timer = 0x30;
            }
            break;
        case 3:
            UnkCollisionFunc2(werewolf_sensors);
            self->velocityX -= self->velocityX / 64;
            self->animCurFrame = 0x2B;
            if (!--self->ext.werewolfARE.timer) {
                SetSubStep(4);
            }
            break;
        case 4:
            UnkCollisionFunc2(werewolf_sensors);
            self->velocityX -= self->velocityX / 16;
            if (!AnimateEntity(werewolf_anim_charge_end, self)) {
                self->blendMode = BLEND_NO;
                SetStep(4);
            }
            break;
        }
        break;
    case 0x12:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(3.5);
            } else {
                self->velocityX = FIX(-3.5);
            }
            self->velocityY = 0;
            self->ext.werewolfARE.timer = 0x20;
            self->animCurFrame = 0x17;
            self->drawFlags |= ENTITY_ROTATE;
            self->step_s++;
            // fallthrough
        case 1:
            UnkCollisionFunc2(werewolf_sensors);
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 8)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (!(self->ext.werewolfARE.timer & 3)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(WEREWOLF_SPIN_ATTACK_AFTER_IMAGE), self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }
            if (!--self->ext.werewolfARE.timer) {
                self->step_s = 2;
            }
            break;
        case 2:
            self->drawFlags = ENTITY_DEFAULT;
            SetStep(4);
            break;
        }
        break;
    case 0x16:
        switch (self->step_s) {
        case 0:
            self->ext.werewolfARE.signal = false;
            entity = self + 3;
            if (self->posX.i.hi > entity->posX.i.hi) {
                self->facingLeft = 0;
            } else {
                self->facingLeft = 1;
            }
            if (self->facingLeft) {
                self->velocityX = FIX(3.5);
            } else {
                self->velocityX = FIX(-3.5);
            }
            self->velocityY = 0;
            if (entity->flags & FLAG_DEAD) {
                SetStep(10);
                return;
            }
            self->step_s++;
        case 1:
            if (!AnimateEntity(werewolf_anim_spin_init, self)) {
                self->animCurFrame = 0x17;
                self->drawFlags |= ENTITY_ROTATE;
                self->step_s++;
            }
            break;
        case 2:
            UnkCollisionFunc2(werewolf_sensors);
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (!(self->ext.werewolfARE.timer & 3)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(WEREWOLF_SPIN_ATTACK_AFTER_IMAGE), self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }
            entity = self + 3;
            i = self->posX.i.hi - entity->posX.i.hi;
            if (self->facingLeft) {
                i = -i;
            }
            if (i < 0x20) {
                entity->ext.minotaur.signal = true;
                self->rotate = 0;
                self->step_s++;
            }
            if (entity->flags & FLAG_DEAD) {
                SetSubStep(7);
            }
            break;
        case 3:
            self->velocityY = FIX(-8.5);
            entity = &PLAYER;
            i = entity->posX.val - self->posX.val;
            i /= 64;
            self->velocityX = i;
            self->animCurFrame = 8;
            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            self->step_s++;
            break;
        case 4:
            MoveEntity();
            self->velocityY += FIX(0.25);
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (posY < 0x2C) {
                self->posY.i.hi = 0x2C - g_Tilemap.scrollY.i.hi;
                self->ext.werewolfARE.timer = 8;
                self->step_s++;
            }
            break;
        case 5:
            self->animCurFrame = 0x17;
            self->rotate -= ROT(33.75);
            if (!--self->ext.werewolfARE.timer) {
                self->ext.werewolfARE.timer = 0xC;
                self->step_s++;
            }
            break;
        case 6:
            self->animCurFrame = 0x1B;
            self->rotate = 0;
            if (!--self->ext.werewolfARE.timer) {
                entity = &PLAYER;
                angle = GetAngleBetweenEntities(self, entity);
                self->velocityX = rcos(angle) * 0x50;
                self->velocityY = rsin(angle) * 0x50;
                self->ext.werewolfARE.attack = self->attack;
                self->attack *= 2;
                self->step_s++;
            }
            break;
        case 7:
            self->animCurFrame = 0x17;
            self->rotate -= ROT(33.75);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (UnkCollisionFunc3(werewolf_sensors_ground) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                self->attack = self->ext.werewolfARE.attack;
                self->ext.werewolfARE.timer = 0x10;
                self->step_s++;
            }
            if (!(self->ext.werewolfARE.timer & 3)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(WEREWOLF_SPIN_ATTACK_AFTER_IMAGE), self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }
            break;
        case 8:
            self->drawFlags = ENTITY_DEFAULT;
            self->animCurFrame = 0xC;
            if (!--self->ext.werewolfARE.timer) {
                SetStep(4);
            }
            break;
        }
        break;
    case 0x18:
        switch (self->step_s) {
        case 0:
            self->ext.werewolfARE.signal = false;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            // fallthrough
        case 1:
            if (self->ext.werewolfARE.signal) {
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(werewolf_anim_spin_init, self)) {
                self->animCurFrame = 0x17;
                self->drawFlags |= ENTITY_ROTATE;
                if (self->facingLeft) {
                    self->velocityX = FIX(3.5);
                } else {
                    self->velocityX = FIX(-3.5);
                }
                self->ext.werewolfARE.timer = 0x40;
                self->step_s++;
            }
            break;
        case 3:
            UnkCollisionFunc2(werewolf_sensors);
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (!(self->ext.werewolfARE.timer & 3)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(WEREWOLF_SPIN_ATTACK_AFTER_IMAGE), self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }
            entity = self + 3;
            if (!(entity->flags & FLAG_DEAD)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(MINOTAUR_SPIT_LIQUID), self, entity);
                    angle = entity->rotate = self->rotate;
                    if (self->facingLeft) {
                        angle = -angle;
                    }
                    entity->posX.val += rsin(angle) * 0xC0;
                    entity->posY.val += rcos(angle) * -0xC0;
                    entity->facingLeft = self->facingLeft;
                    entity->zPriority = self->zPriority + 1;
                }
            }
            if (!--self->ext.werewolfARE.timer) {
                self->step_s++;
            }
            break;
        case 4:
            self->drawFlags = ENTITY_DEFAULT;
            SetStep(4);
            break;
        }
        break;
    case 0x14:
        if (self->flags & 0xF) {
            self->blendMode = BLEND_NO;
        } else {
            if (g_Timer & 1) {
                self->blendMode = BLEND_ADD | BLEND_TRANSP;
            } else {
                self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
            }
        }
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.werewolfARE.signal = false;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(werewolf_anim_spin_init, self)) {
                self->step_s++;
            }
            break;
        case 2:
            self->velocityX = 0;
            self->velocityY = FIX(-4.0);
            self->drawFlags = ENTITY_ROTATE;
            self->step_s++;
            // fallthrough
        case 3:
            MoveEntity();
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (g_Timer & 1) {
                self->animCurFrame = 0x18;
            } else {
                self->animCurFrame = 0x19;
            }
            if (!(self->ext.werewolfARE.timer & 3)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(WEREWOLF_SPIN_ATTACK_AFTER_IMAGE), self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (posY < 0x28) {
                self->step_s++;
            }
            break;
        case 4:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 5:
            MoveEntity();
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }
            if (g_Timer & 1) {
                self->animCurFrame = 0x18;
            } else {
                self->animCurFrame = 0x19;
            }
            if (self->ext.werewolfARE.signal) {
                self->drawFlags = ENTITY_DEFAULT;
                self->animCurFrame = 0xA;
                self->velocityX = 0;
                self->velocityY = FIX(2.0);
                self->step_s++;
            }
            break;
        case 6:
            if (UnkCollisionFunc3(werewolf_sensors_ground) & 1) {
                self->animCurFrame = 0xB;
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_1F), self, entity);
                    entity->posY.i.hi += 0x1B;
                    entity->zPriority = self->zPriority - 1;
                }
                PlaySfxPositional(SFX_FIREBALL_SHOT_A);
                self->ext.werewolfARE.timer = 0x40;
                self->step_s++;
            }
            break;
        case 7:
            if (!--self->ext.werewolfARE.timer) {
                self->blendMode = BLEND_NO;
                SetStep(4);
            }
            break;
        }
        break;
    case 0x20:
        entity = self + 3;
        self->ext.werewolfARE.isReady = true;
        entity->ext.minotaur.signal = true;
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->rotate = 0;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (UnkCollisionFunc3(werewolf_sensors_ground) & 1) {
                self->step_s++;
            }
            // fallthrough
        case 2:
            if (!AnimateEntity(werewolf_anim_death_pain, self)) {
                PlaySfxPositional(SFX_EXPLODE_A);
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(WEREWOLF_DEATH_FLAMES), self, entity);
                    entity->posY.i.hi += 0x1B;
                    entity->zPriority = self->zPriority;
                }
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(werewolf_anim_death_melt, self)) {
                SetSubStep(4);
            }
            break;
        case 4:
            self->ext.werewolfARE.targetPosX = 0;
            self->animCurFrame = 0;
            break;
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
    }

    ptr = *werewolf_base_hitboxes;
    ptr += werewolf_base_hitbox_indices[self->animCurFrame] * 4;
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
    func_us_801B37D0();
}

#include "e_werewolf_attack_hitbox.h"

INCLUDE_ASM("boss/bo2/nonmatchings/unk_337D0", func_us_801B503C);

#include "e_werewolf_after_image.h"

INCLUDE_ASM("boss/bo2/nonmatchings/unk_337D0", func_us_801B52FC);

INCLUDE_ASM("boss/bo2/nonmatchings/unk_337D0", EntityWerewolfDeathFlames);
