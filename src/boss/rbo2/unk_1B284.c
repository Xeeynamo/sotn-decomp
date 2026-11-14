// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo2.h"
#include "sfx.h"

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", EntityBreakable);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019A98C_from_rcen);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019B430);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_801CDC80);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019B52C);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019C718);

extern EInit D_us_801804AC;
extern u8 D_us_80180708[];
extern u8 D_us_80180718[];
extern u8 D_us_8018072C[];
extern u8 D_us_80180744[];
extern u8 D_us_8018075C[];
extern s32 g_BossMgrState;

void func_us_8019C924(Entity* self) {
    Entity* entity;
    s32 dx;
    s32 dy;
    s16 angle;
    s32 animDone;
    s32 dist;
    EnemyDef* enemyDef;

    FntPrint("ball_step %x\n", self->step);
    if (g_BossMgrState & 8) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = EXPLOSION_BIG;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804AC);
        self->hitboxState = 0;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = self->scaleY = 0x80;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        PlaySfxPositional(SFX_RAPID_SYNTH_BUBBLE_SHORT);
        // fallthrough
    case 1:
        if (!AnimateEntity(D_us_80180708, self)) {
            self->step++;
        }
        // fallthrough
    case 2:
        self->scaleX += 4;
        if (self->scaleX > 0x100) {
            self->hitboxState = 1;
            self->drawFlags = ENTITY_DEFAULT;
            SetStep(3);
        }
        self->scaleY = self->scaleX;
        break;

    case 3:
        AnimateEntity(D_us_80180718, self);
        entity = self->ext.rbo2Ball.parent;
        if (entity->ext.rbo2Ball.unk88) {
            self->ext.rbo2Ball.angle = ROT(90);
            SetStep(4);
        }
        break;

    case 4:
        AnimateEntity(D_us_80180718, self);
        MoveEntity();
        entity = &PLAYER;
        dx = entity->posX.i.hi;
        dy = entity->posY.i.hi;
        dx += (Random() & 0x3F) - 0x20;
        dy += (Random() & 0x3F) - 0x20;
        dx -= self->posX.i.hi;
        dy -= self->posY.i.hi;
        angle = ratan2(dy, dx);
        angle = LimitAngleChange(0x40, self->ext.rbo2Ball.angle, angle);
        self->velocityX = (rcos(angle) * FIX(0.4375)) >> 12;
        self->velocityY = (rsin(angle) * FIX(0.4375)) >> 12;
        self->ext.rbo2Ball.angle = angle;
        entity = self->ext.rbo2Ball.parent;
        if (entity->ext.rbo2Ball.unk89) {
            SetStep(5);
        }
        break;

    case 5:
        AnimateEntity(D_us_80180718, self);
        MoveEntity();
        entity = self->ext.rbo2Ball.parent;
        if (!self->params) {
            dx = entity->posX.i.hi - 0x20;
        } else {
            dx = entity->posX.i.hi + 0x20;
        }
        dy = entity->posY.i.hi - 0x1C;
        dx -= self->posX.i.hi;
        dy -= self->posY.i.hi;
        angle = ratan2(dy, dx);
        self->velocityX = (rcos(angle) * FIX(1.75)) >> 12;
        self->velocityY = (rsin(angle) * FIX(1.75)) >> 12;
        dist = SquareRoot0(dx * dx + dy * dy);
        if (dist < 4) {
            self->ext.rbo2Ball.unk8A = 1;
            self->step++;
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            AnimateEntity(D_us_80180718, self);
            entity = self->ext.rbo2Ball.parent;
            if (entity->ext.rbo2Ball.unk8B) {
                self->ext.rbo2Ball.unk8A = 0;
                SetSubStep(1);
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_8018072C, self)) {
                SetStep(7);
            }
            break;
        }
        break;

    case 7:
        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[176], &g_Entities[184]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_19), self, entity);
                entity->ext.rbo2Ball.parent = self;
                if (!self->params) {
                    entity->ext.rbo2Ball.unkA0 = self + 1;
                } else {
                    entity->ext.rbo2Ball.unkA0 = self - 1;
                }
                entity->facingLeft = self->params;
                entity->zPriority = self->zPriority + 1;
                self->ext.rbo2Ball.unk8C = 0;
                PlaySfxPositional(SFX_LOW_SYNTH_BUBBLES);
                self->step_s++;
            }
            break;
        case 1:
            self->ext.rbo2Ball.timer = 0x60;
            self->step_s++;
            break;
        case 2:
            if (!--self->ext.rbo2Ball.timer) {
                self->step_s = 0;
            }
            break;
        }
        if (g_Timer & 1) {
            self->animCurFrame = 0x39;
        } else {
            self->animCurFrame = 0;
        }
        MoveEntity();
        entity = self->ext.rbo2Ball.parent;
        dy = entity->posY.i.hi - 0x1C;
        if (!self->params) {
            dx = entity->posX.i.hi - 0x50;
        } else {
            dx = entity->posX.i.hi + 0x50;
        }
        dx -= self->posX.i.hi;
        dy -= self->posY.i.hi;
        angle = ratan2(dy, dx);
        self->velocityX = (rcos(angle) * FIX(0.875)) >> 12;
        self->velocityY = (rsin(angle) * FIX(0.875)) >> 12;
        dist = SquareRoot0(dx * dx + dy * dy);
        if (dist < 3) {
            self->velocityX = 0;
            self->velocityY = 0;
        }
        if (g_BossMgrState & 4) {
            SetStep(8);
        }
        break;

    case 8:
        switch (self->step_s) {
        case 0:
            animDone = AnimateEntity(D_us_80180744, self);
            MoveEntity();
            entity = self->ext.rbo2Ball.parent;
            if (!self->params) {
                dx = entity->posX.i.hi - 0x20;
            } else {
                dx = entity->posX.i.hi + 0x20;
            }
            dy = entity->posY.i.hi - 0x1C;
            dx -= self->posX.i.hi;
            dy -= self->posY.i.hi;
            angle = ratan2(dy, dx);
            self->velocityX = (rcos(angle) * FIX(1.75)) >> 12;
            self->velocityY = (rsin(angle) * FIX(1.75)) >> 12;
            dist = SquareRoot0(dx * dx + dy * dy);
            if (dist < 4 && !animDone) {
                self->ext.rbo2Ball.unk8A = 1;
                SetSubStep(1);
            }
            break;
        case 1:
            AnimateEntity(D_us_80180718, self);
            entity = self->ext.rbo2Ball.parent;
            if (entity->ext.rbo2Ball.unk8C) {
                self->facingLeft = self->params;
                SetSubStep(2);
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_8018075C, self)) {
                enemyDef = &g_api.enemyDefs[ENEMY_DEATH_UNK_168];
                self->attackElement = enemyDef->attackElement;
                self->attack = enemyDef->attack;
                self->hitboxWidth = enemyDef->hitboxWidth;
                self->hitboxHeight = enemyDef->hitboxHeight;
                self->hitboxState = 1;
                self->blendMode = BLEND_NO;
                self->drawFlags = ENTITY_ROTATE;
                SetStep(9);
            }
            break;
        }
        break;

    case 9:
        switch (self->step_s) {
        case 0:
            self->ext.rbo2Ball.unk8A = 1;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            func_801CDC80(&self->rotate, 0, 0x40);
            entity = self->ext.rbo2Ball.parent;
            dy = entity->posY.i.hi - 0x10;
            if (!self->params) {
                dx = entity->posX.i.hi - 0x20;
            } else {
                dx = entity->posX.i.hi + 0x20;
            }
            dx -= self->posX.i.hi;
            dy -= self->posY.i.hi;
            angle = ratan2(dy, dx);
            self->velocityX = (rcos(angle) * FIX(0.875)) >> 12;
            self->velocityY = (rsin(angle) * FIX(0.875)) >> 12;
            dist = SquareRoot0(dx * dx + dy * dy);
            if (dist < 3) {
                self->velocityX = 0;
                self->velocityY = 0;
            }
            entity = self->ext.rbo2Ball.parent;
            if (entity->ext.rbo2Ball.unk8D) {
                self->ext.rbo2Ball.unk8A = 0;
                self->step_s++;
            }
            break;
        case 2:
            entity = &PLAYER;
            dx = entity->posX.i.hi - self->posX.i.hi;
            dy = entity->posY.i.hi - self->posY.i.hi;
            angle = ratan2(dy, dx);
            self->ext.rbo2Ball.angle = angle;
            self->ext.rbo2Ball.speed = FIX(6);
            self->step_s++;
            // fallthrough
        case 3:
            MoveEntity();
            self->rotate -= ROT(22.5);
            if (!(self->rotate & 0xF00)) {
                PlaySfxPositional(SFX_DEATH_SCYTHE_SWISH);
            }
            angle = self->ext.rbo2Ball.angle;
            self->velocityX = (self->ext.rbo2Ball.speed * rcos(angle)) >> 12;
            self->velocityY = (self->ext.rbo2Ball.speed * rsin(angle)) >> 12;
            self->ext.rbo2Ball.speed -= self->ext.rbo2Ball.speed >> 4;
            if (self->ext.rbo2Ball.speed < FIX(0.25)) {
                self->ext.rbo2Ball.timer = 0x20;
                self->step_s++;
            }
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[208], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_1A), self, entity);
                    entity->params = self->animCurFrame;
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                }
            }
            break;
        case 4:
            self->rotate -= ROT(45);
            self->rotate &= 0xFFF;
            if (!(self->rotate & 0xF00)) {
                PlaySfxPositional(SFX_DEATH_SCYTHE_SWISH);
            }
            if (!--self->ext.rbo2Ball.timer) {
                self->step_s++;
            }
            break;
        case 5:
            MoveEntity();
            func_801CDC80(&self->rotate, 0, 0x40);
            entity = self->ext.rbo2Ball.parent;
            dy = entity->posY.i.hi - 0x10;
            if (!self->params) {
                dx = entity->posX.i.hi - 0x20;
            } else {
                dx = entity->posX.i.hi + 0x20;
            }
            dx -= self->posX.i.hi;
            dy -= self->posY.i.hi;
            angle = ratan2(dy, dx);
            dist = SquareRoot0(dx * dx + dy * dy);
            if (dist > 0x20) {
                angle = LimitAngleChange(0x60, self->ext.rbo2Ball.angle, angle);
            }
            self->velocityX = (rcos(angle) * FIX(3)) >> 12;
            self->velocityY = (rsin(angle) * FIX(3)) >> 12;
            self->ext.rbo2Ball.angle = angle;
            if (dist < 8) {
                self->step_s = 0;
            }
            break;
        }
        break;
    }
}

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019D4CC);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019D950);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019DA04);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019E558);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019E920);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019ECCC);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019ED80);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", polarPlacePartsWithAngvel);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_801CDD00);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_801CDD80);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_801CDF1C);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_801CE1E8);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_801CE228);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", polarPlacePartsList);

// decompiled in src/boss/bo1/e_explosion_flame.c
INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019D260_from_rcen);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019F260);

extern EInit g_EInitInteractable;
extern s32 g_BossMgrState;
extern u32 g_CutsceneFlags;

void EntityBossFightManager(Entity* self) {
    Entity* entity;
    u32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->flags |= FLAG_UNK_10000;
        // fallthrough

    case 1:
        posX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
        if ((posX - 0x41) < 0x17F) {
            g_BossMgrState |= BOSS_MGR_ROOM_ENTERED;
            self->step++;
        }
        break;

    case 2:
        if (g_CastleFlags[DEATH_FIGHT_CS] ||
            (g_PlayableCharacter != PLAYER_ALUCARD) ||
            (g_DemoMode != Demo_None)) {
            posX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
            if ((posX - 0x81) >= 0xFF) {
                break;
            }
        } else if (!(g_CutsceneFlags & 2)) {
            break;
        }
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_DEATH_DEFEAT, TIMEATTACK_SET_VISITED);
        stopMusicFlag = true;
        currentMusicId = MU_DEATH_BALLAD;
        g_BossMgrState |= BOSS_MGR_DEATH_FIGHT_ON;
        self->step++;
        break;

    case 3:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        // fallthrough

    case 4:
        if (g_BossMgrState & BOSS_MGR_DEATH_DEFEAT) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_DEATH_DEFEAT, TIMEATTACK_SET_RECORD);
            g_api.PlaySfx(SET_UNK_90);
            currentMusicId = MU_ABANDONED_PIT;
            self->step++;
        }
        break;

    case 5:
        if (g_BossMgrState & BOSS_MGR_DEATH_REWARD_READY) {
            self->step++;
        }
        break;

    case 6:
        posX = 0x100 - g_Tilemap.scrollX.i.hi;
        posY = 0x80 - g_Tilemap.scrollY.i.hi;
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_LIFE_UP_SPAWN, self, entity);
            entity->posX.i.hi = posX;
            entity->posY.i.hi = posY;
            entity->params = 0x15;
            stopMusicFlag = true;
            currentMusicId = MU_ABANDONED_PIT;
            g_BossMgrState |= BOSS_MGR_DEATH_REWARD_SPAWNED;
            self->step++;
        }
        break;

    case 7:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    }

    FntPrint("set_step %x\n", self->step);
    FntPrint("boss_flag %x\n", g_BossMgrState);
}
