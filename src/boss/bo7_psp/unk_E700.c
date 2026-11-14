// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../bo7/bo7.h"

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", func_us_80195C50);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", EntityBreakable);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", EntityBreakableDebris);

// Snaps the boss to the arena floor once it falls low enough. Same routine
// as rbo0's copy, with bo7's higher floor (0xD0 vs 0xE0).
bool func_us_80194338(s16* offsets) {
    s32 posY;

    offsets++;
    posY = g_CurrentEntity->posY.i.hi + *offsets + g_Tilemap.scrollY.i.hi;
    posY = 0xD0 - posY;
    if (posY <= 0) {
        g_CurrentEntity->posY.i.hi += posY;
        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;
        return true;
    }
    return false;
}

extern EInit g_EInitCerberos;
extern s16 D_us_801806D8[];
extern s16 D_us_801806F0[][2];
extern AnimationFrame D_us_801806FC[];
extern AnimationFrame D_us_80180708[];
extern AnimationFrame D_us_8018071C[];
extern AnimationFrame D_us_8018072C[];
extern AnimationFrame D_us_8018073C[];
extern AnimationFrame D_us_80180748[];
extern AnimationFrame D_us_80180754[];
extern AnimationFrame D_us_80180760[];
extern AnimationFrame D_us_8018076C[];
extern AnimationFrame D_us_80180778[];
extern AnimationFrame D_us_80180788[];
extern s8 D_us_801807E4[][4];
extern u8 D_us_8018081C[];
extern s32 g_BossMgrState;
#if TARGET == TARGET_PSP
extern s32 E_ID(UNK_1D);
extern s32 E_ID(UNK_1E);
extern s32 E_ID(UNK_20);
#endif

void EntityCerberus(Entity* self) {
    Entity* entity;
    s32 i;
    s32 posX;
    s32 posY;
    s32 side;
    s8* hitbox;

    if (self->flags & FLAG_DEAD) {
        if (self->step != 8) {
            SetStep(8);
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCerberos);
        self->hitboxState = 0;
        SetStep(2);
        // fallthrough
    case 2:
        AnimateEntity(D_us_801806FC, self);
        if (g_BossMgrState & 2) {
            self->hitboxState = 3;
            SetStep(3);
        }
        break;
    case 3:
        if (!self->step_s) {
            self->ext.cerberus.timer = 0x40;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80180708, self)) {
            PlaySfxPositional(SFX_WARG_GROWL);
        }
        if (GetDistanceToPlayerX() < 0x68) {
            self->ext.cerberus.retreat = 1;
        }
        if (GetDistanceToPlayerX() > 0x80) {
            self->ext.cerberus.retreat = 0;
        }
        if (GetDistanceToPlayerX() > 0x30) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        MoveEntity();
        if (self->facingLeft ^ self->ext.cerberus.retreat) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (!--self->ext.cerberus.timer) {
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            entity = &PLAYER;
            SetStep(10);
            if (self->facingLeft) {
                posX = 0x200 - posX;
            }
            side = (GetSideToPlayer() & 1) ^ 1;
            if (posX < 0xD0 && self->facingLeft == side) {
                SetStep(9);
            }
            if (abs(posX) > 0x50 && self->facingLeft != side) {
                SetStep(9);
            }
            if (posX > 0x140 && self->facingLeft == side) {
                SetStep(6);
            }
            if (posX > 0x180 && self->facingLeft == side) {
                SetStep(4);
            }
            if ((g_Player.status & PLAYER_STATUS_BAT_FORM) ||
                (entity->posY.i.hi < 0xA0 &&
                 g_Player.vram_flag & TOUCHING_GROUND)) {
                SetStep(5);
            }
        }
        break;
    case 11:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_8018071C, self)) {
                if (self->facingLeft) {
                    self->velocityX = FIX(-6);
                } else {
                    self->velocityX = FIX(6);
                }
                self->ext.cerberus.timer = 0x40;
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX >> 6;
            if (!--self->ext.cerberus.timer) {
                SetStep(3);
            }
            break;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180754, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_80180748, self)) {
                PlaySfxPositional(SFX_WARG_ATTACK);
                PlaySfxPositional(SFX_SHAFT_FIRE_ATTACK);
                self->ext.cerberus.timer = 0x80;
                SetSubStep(2);
            }
            break;
        case 2:
            if (!(self->ext.cerberus.timer & 3)) {
                for (i = 0; i < 3; i++) {
                    entity = AllocEntity(&g_Entities[128], &g_Entities[224]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_ID(UNK_1E), self, entity);
                        if (self->facingLeft) {
                            entity->posX.i.hi -= D_us_801806F0[i][0];
                        } else {
                            entity->posX.i.hi += D_us_801806F0[i][0];
                        }
                        entity->posY.i.hi += D_us_801806F0[i][1];
                        entity->params = i;
                        entity->zPriority = self->zPriority + 1;
                        entity->facingLeft = self->facingLeft;
                    }
                }
            }
            if (!--self->ext.cerberus.timer) {
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(D_us_80180760, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 10:
        if (!AnimateEntity(D_us_8018073C, self)) {
            SetStep(3);
        }
        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(SFX_B07_STOMP);
            PlaySfxPositional(SFX_WARG_ATTACK);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_1D), self, entity);
                entity->facingLeft = self->facingLeft;
                if (self->facingLeft) {
                    entity->posX.i.hi += 0x18;
                } else {
                    entity->posX.i.hi -= 0x18;
                }
                entity->params = self->ext.cerberus.fireballIdx;
                entity->zPriority = self->zPriority + 1;
            }
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180778, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            self->velocityY = FIX(-6);
            if (self->facingLeft) {
                self->velocityX = FIX(-2.5);
            } else {
                self->velocityX = FIX(2.5);
            }
            self->step_s++;
            // fallthrough
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.21875);
            if (func_us_80194338(D_us_801806D8) & 1) {
                PlaySfxPositional(SFX_START_SLAM_B);
                g_api.ShakeCamera(1);
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180788, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180778, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            self->velocityY = FIX(-6);
            if (self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }
            self->step_s++;
            // fallthrough
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.21875);
            if (func_us_80194338(D_us_801806D8) & 1) {
                PlaySfxPositional(SFX_START_SLAM_B);
                g_api.ShakeCamera(1);
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180788, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            self->ext.cerberus.attackCount = 8;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(D_us_8018072C, self)) {
                if (!--self->ext.cerberus.attackCount) {
                    SetStep(3);
                }
            }
            if (!self->poseTimer && self->pose == 5) {
                PlaySfxPositional(SFX_B07_STOMP);
                PlaySfxPositional(SFX_WARG_ATTACK);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_1D), self, entity);
                    entity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x18;
                    } else {
                        entity->posX.i.hi -= 0x18;
                    }
                    entity->params = self->ext.cerberus.fireballIdx;
                    entity->zPriority = self->zPriority + 1;
                }
                self->ext.cerberus.fireballIdx++;
                if (self->ext.cerberus.fireballIdx > 2) {

                    self->ext.cerberus.fireballIdx = 0;
                }
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            g_BossMgrState |= 4;
            PlaySfxPositional(SFX_WARG_DEATH_HOWL);
            self->step_s++;
            // fallthrough
        case 1:
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_EXPLODE_B);
                entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_20), self, entity);
                    entity->params = 1;
                    entity->zPriority = self->zPriority + 1;
                    entity->posX.i.hi += (Random() & 0x3F) - 0x20;
                    entity->posY.i.hi += (Random() & 0x1F) - 0xC;
                }
            }
            if (!AnimateEntity(D_us_8018076C, self)) {
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
                self->ext.cerberus.timer = 0x50;
                self->step_s++;
            }
            break;
        case 2:
            entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_20), self, entity);
                entity->params = 2;
                entity->zPriority = self->zPriority + 1;
                entity->posX.i.hi += (Random() & 0x3F) - 0x20;
                if (self->facingLeft) {
                    entity->posX.i.hi -= 0xC;
                } else {
                    entity->posX.i.hi += 0xC;
                }
                entity->posY.i.hi += 0x18;
            }
            if (!--self->ext.cerberus.timer) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 3:
            g_BossMgrState |= 8;
            self->step_s++;
            break;
        case 4:
            break;
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
    }
    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->velocityX < 0) {
        if (posX < 0x68) {
            self->posX.i.hi = 0x68 - g_Tilemap.scrollX.i.hi;
        }
    } else if (posX > 0x1A0) {
        self->posX.i.hi = 0x1A0 - g_Tilemap.scrollX.i.hi;
    }
    hitbox = D_us_801807E4[0];
    hitbox += D_us_8018081C[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", func_us_801959E0);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", func_us_80195AF0);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", EntityBackgroundBlock);
