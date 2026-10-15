// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo7.h"

extern Primitive* FindFirstUnkPrim(Primitive* prim);
extern EInit g_EInitInteractable;
extern EInit g_EInitAkmodanII;
extern EInit D_us_80180444;
extern EInit D_us_80180450;
extern s32 g_BossMgrState;

// unused
static s16 sensors_unused[][2] = {{0, 32}, {0, 4}, {16, -4}, {-32, 0}};
s16 D_us_801805DC[] = {0, 32, 8, 0};
AnimateEntityFrame D_us_801805E4[] = {
    POSE(16, 16, 0), POSE(16, 1, 0), POSE(16, 16, 0), POSE(16, 1, 0), POSE_END};
AnimateEntityFrame D_us_801805F0[] = {
    POSE(64, 3, 0), POSE(2, 5, 0),  POSE(43, 6, 0),
    POSE(3, 7, 0),  POSE(21, 8, 0), POSE_END};
AnimateEntityFrame D_us_801805FC[] = {
    POSE(7, 9, 0),  POSE(7, 10, 0), POSE(7, 11, 0),
    POSE(7, 12, 0), POSE(7, 13, 0), POSE(7, 12, 0),
    POSE(7, 11, 0), POSE(7, 10, 0), POSE_LOOP(0)};
AnimateEntityFrame D_us_80180610[] = {
    POSE(3, 14, 0), POSE(10, 15, 0), POSE(3, 14, 0), POSE_END};
AnimateEntityFrame D_us_80180618[] = {
    POSE(6, 17, 0), POSE(36, 18, 0), POSE(4, 19, 0), POSE(32, 20, 0), POSE_END};
AnimateEntityFrame D_us_80180624[] = {
    POSE(5, 21, 0), POSE(5, 22, 0), POSE(5, 23, 0),
    POSE(5, 24, 0), POSE(5, 25, 0), POSE(5, 26, 0),
    POSE(5, 27, 0), POSE(5, 28, 0), POSE_LOOP(0)};
AnimateEntityFrame D_us_80180638[] = {
    POSE(4, 29, 0), POSE(21, 30, 0), POSE_END};
AnimateEntityFrame D_us_80180640[] = {
    POSE(4, 32, 0),  POSE(17, 33, 0), POSE(4, 34, 0), POSE(4, 35, 0),
    POSE(4, 36, 0),  POSE(4, 37, 0),  POSE(4, 38, 0), POSE(4, 39, 0),
    POSE(12, 40, 0), POSE(4, 39, 0),  POSE(4, 38, 0), POSE(4, 37, 0),
    POSE(4, 36, 0),  POSE(4, 35, 0),  POSE(4, 34, 0), POSE(4, 33, 0),
    POSE(4, 32, 0),  POSE_END};
static AnimateEntityFrame anim_burst_in[] = {
    POSE(2, 1, 0),  POSE(2, 8, 0),  POSE(2, 9, 0),
    POSE(2, 10, 0), POSE(2, 11, 0), POSE_END};
static AnimateEntityFrame anim_burst_loop[] = {
    POSE(2, 8, 0),  POSE(2, 9, 0),  POSE(2, 10, 0),
    POSE(2, 11, 0), POSE(2, 10, 0), POSE(2, 9, 0),
    POSE(2, 10, 0), POSE(2, 11, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_burst_out[] = {
    POSE(2, 12, 0), POSE(2, 13, 0), POSE(2, 14, 0), POSE_END};
static AnimateEntityFrame anim_flame[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(4, 3, 0),  POSE(4, 4, 0),
    POSE(4, 5, 0),  POSE(4, 6, 0),  POSE(4, 5, 0),  POSE(4, 4, 0),
    POSE(4, 5, 0),  POSE(4, 6, 0),  POSE(4, 7, 0),  POSE(4, 8, 0),
    POSE(4, 7, 0),  POSE(4, 8, 0),  POSE(4, 9, 0),  POSE(3, 10, 0),
    POSE(3, 11, 0), POSE(3, 12, 0), POSE(3, 13, 0), POSE(3, 14, 0),
    POSE(3, 15, 0), POSE(3, 16, 0), POSE(3, 17, 0), POSE(3, 18, 0),
    POSE(2, 19, 0), POSE(2, 20, 0), POSE(2, 21, 0), POSE(2, 22, 0),
    POSE(2, 23, 0), POSE(2, 24, 0), POSE_END};
// x, y offset of the grabbing hand for each frame
s16 D_us_801806CC[][2] = {
    {-26, -14}, {-24, 0}, {-32, 0}, {-30, -8}, {-16, -8}, {-18, -8}, {-16, -8},
    {-8, -8},   {8, -8},  {16, -8}, {18, -8},  {16, -8},  {-18, -8}, {-18, -8}};
s8 D_us_80180704[][4] = {
    {0, 0, 0, 0},   {4, -4, 4, 36}, {4, 0, 4, 32}, {4, 8, 4, 24},
    {-4, 0, 4, 32}, {-4, 4, 4, 28}, {12, 0, 4, 32}};
u8 D_us_80180720[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 1, 4, 4, 5, 5, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 6, 6, 2, 2, 2, 2, 2, 2, 0, 0, 0};
static s8 D_us_8018074C[][4] = {
    {0, 0, 0, 0},     {-20, -4, 4, 4},  {-16, -4, 8, 4},
    {-16, -4, 16, 4}, {-24, -4, 16, 4}, {-32, -4, 24, 4}};
static u8 D_us_80180764[] = {0, 1, 2, 3, 4, 5, 0, 0};
#ifdef VERSION_PSP
char D_pspeu_09255468[] = "step %x\n";
char D_pspeu_09255478[] = "step_s %x\n";
char D_pspeu_09255488[] = "NO DR_ENV \n";
char D_pspeu_09255498[] = "timer %x\n";
char D_pspeu_092554A8[] = "charal %x\n";
char D_pspeu_092554B8[] = "tsukami %x\n";
#endif

#if defined(VERSION_PSP) && !defined(NON_MATCHINGS)
INCLUDE_ASM("boss/rbo7/nonmatchings/e_akmodan_ii", EntityAkmodanII);
#else
// matches on US; PSP is close but has register allocation differences
void EntityAkmodanII(Entity* self) {
    Primitive* prim;
    Entity* entity;
    s32 x;
    s32 y;
    s32 i;
    s32 side;
    s32 idx;
    s8* hitbox;
    s32 primIndex;
    s16 angle;
    DRAWENV drawEnv;
    RECT clipRect;
    DR_ENV* dr_env;

    FntPrint("step %x\n", self->step);
    FntPrint("step_s %x\n", self->step_s);
    if (self->flags & FLAG_DEAD) {
        if (self->step != 8) {
            SetStep(8);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitAkmodanII);
        self->hitboxState = 0;
        self->ext.akmodanII.baseZPriority = self->zPriority;
        entity = self + 1;
        CreateEntityFromEntity(E_ID(AKMODAN_ATTACK_HITBOX), self, entity);
        /* fall through */
    case 1:
        entity = self + 2;
        CreateEntityFromEntity(E_ID(UNK_1A), self, entity);
        entity->params = 2;
        entity->zPriority = self->zPriority + 1;
        entity = self + 3;
        CreateEntityFromEntity(E_ID(UNK_1A), self, entity);
        entity->params = 3;
        entity->zPriority = self->zPriority - 1;
        SetStep(2);
        /* fall through */
    case 2:
        switch (self->step_s) {
        case 0:
            if (g_BossMgrState & BOSS_MGR_FIGHT_ON) {
                self->step_s++;
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_801805E4, self)) {
                PlaySfxPositional(SFX_STONE_MOVE_B);
                self->ext.akmodanII.unk84 = 1;
                SetSubStep(2);
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_801805F0, self)) {
                self->hitboxState = 3;
                SetStep(3);
            }
            break;
        }
        break;
    case 3:
        if (!self->step_s) {
            self->ext.akmodanII.timer = 0x80;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_801805FC, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (!self->poseTimer && (self->pose == 2 || self->pose == 8)) {
            PlaySfxPositional(SFX_AKMODAN_II_MOVE);
        }
        if (self->facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        UnkCollisionFunc2(D_us_801805DC);
        if (!(Random() & 0xF)) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_1D), self, entity);
                entity->posY.i.hi += 0x20;
                entity->zPriority = self->zPriority + 1;
                if (self->facingLeft) {
                    entity->posX.i.hi -= 6;
                } else {
                    entity->posX.i.hi += 6;
                }
            }
        }
        if (!--self->ext.akmodanII.timer) {
            SetStep(4);
        }
        side = (GetSideToPlayer() & 1) ^ 1;
        entity = &PLAYER;
        x = entity->velocityX;
        if (self->facingLeft) {
            x = -x;
        }
        if (GetDistanceToPlayerX() < 64 && GetDistanceToPlayerX() >= 57 &&
            self->facingLeft == side && x > 0) {
            SetStep(4);
        }
        if (self->hitFlags & 3) {
            SetStep(6);
        }
        if (GetDistanceToPlayerX() < 38 && self->facingLeft == side) {
            x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (x > 80 && x < 0x1B0) {
                SetStep(5);
            }
        }
        break;
    case 4:
        if (!AnimateEntity(D_us_80180640, self)) {
            self->hitboxOffX = 8;
            self->hitboxOffY = -0x24;
            self->hitboxWidth = 0x10;
            self->hitboxHeight = 0x24;
            SetStep(3);
        }
        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(SFX_AKMODAN_II_ARM_STRETCH);
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            /* fall through */
        case 1:
            if (!AnimateEntity(D_us_80180618, self)) {
                SetStep(3);
            }
            entity = &PLAYER;
            idx = self->animCurFrame - 0x11;
            x = D_us_801806CC[idx][0];
            y = D_us_801806CC[idx][1];
            if (self->facingLeft) {
                x = -x;
            }
            x += self->posX.i.hi;
            y += self->posY.i.hi;
            x -= entity->posX.i.hi;
            y -= entity->posY.i.hi;
            if (abs(x) < 8 && abs(y) < 12 &&
                !(g_Player.status &
                  (PLAYER_STATUS_AXEARMOR | PLAYER_STATUS_DEAD |
                   PLAYER_STATUS_INVINCIBLE | PLAYER_STATUS_STONE |
                   PLAYER_STATUS_UNK40 | PLAYER_STATUS_WOLF_FORM |
                   PLAYER_STATUS_MIST_FORM))) {
                g_Player.grabState = GRAB_START;
                g_Player.grabDamage = 8;
                g_Player.grabReactionEffect = GRAB_REACTION_NORMAL;
                self->ext.akmodanII.savedTileX = g_Tilemap.x;
                self->ext.akmodanII.savedTileWidth = g_Tilemap.width;
                self->ext.akmodanII.savedTileY = g_Tilemap.y;
                self->ext.akmodanII.savedTileHeight = g_Tilemap.height;
                g_Tilemap.x = g_Tilemap.scrollX.i.hi;
                g_Tilemap.width = g_Tilemap.scrollX.i.hi + 0x100;
                self->ext.akmodanII.unk86 = 0;
                self->ext.akmodanII.grabbing = 1;
                self->step_s = 2;
            }
            break;
        case 2:
            entity = &PLAYER;
            idx = self->animCurFrame - 0x11;
            x = D_us_801806CC[idx][0];
            y = D_us_801806CC[idx][1];
            if (self->facingLeft) {
                x = -x;
            }
            x += self->posX.i.hi;
            y += self->posY.i.hi;
            x -= entity->posX.i.hi;
            y -= entity->posY.i.hi;
            if (x > 0) {
                entity->posX.i.hi += 1;
            }
            if (x < 0) {
                entity->posX.i.hi -= 1;
            }
            if (y > 0) {
                entity->posY.i.hi += 1;
            }
            if (y < 0) {
                entity->posY.i.hi -= 1;
            }
            if (x == 0 && y == 0) {
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180618, self)) {
                SetSubStep(4);
            }
            break;
        case 4:
            side = AnimateEntity(D_us_80180624, self);
            if (side & 0x80) {
                self->poseTimer -= self->ext.akmodanII.unk86;
            }
            if (!side) {
                self->ext.akmodanII.unk86++;
                g_Player.grabDamage =
                    g_api.enemyDefs[ENEMY_AKMODAN_II_GRAB].attack / 2;
                g_Player.grabState = GRAB_DAMAGE;
            }
            if (self->animCurFrame >= 0x15 && self->animCurFrame < 0x1A) {
                self->zPriority = g_unkGraphicsStruct.g_zEntityCenter + 4;
            } else {
                self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 4;
            }
            if (self->ext.akmodanII.unk86 >= 4) {
                SetSubStep(5);
            }
            break;
        case 5:
            g_Player.grabDamage = g_api.enemyDefs[ENEMY_AKMODAN_II_GRAB].attack;
            g_Player.grabState = GRAB_RELEASE;
            self->ext.akmodanII.grabbing = 0;
            entity = &PLAYER;
            if (self->facingLeft) {
                entity->velocityX = FIX(6.0);
            } else {
                entity->velocityX = FIX(-6.0);
            }
            entity->velocityY = FIX(-2.0);
            if (g_Player.status & PLAYER_STATUS_DEAD) {
                entity->velocityX = 0;
            }
            self->zPriority = self->ext.akmodanII.baseZPriority;
            g_Tilemap.x = self->ext.akmodanII.savedTileX;
            g_Tilemap.width = self->ext.akmodanII.savedTileWidth;
            self->step_s++;
            /* fall through */
        case 6:
            if (!AnimateEntity(D_us_80180638, self)) {
                SetStep(3);
            }
            break;
        }
        if (self->step_s >= 3 && self->step_s < 6) {
            idx = self->animCurFrame - 0x11;
            x = D_us_801806CC[idx][0];
            y = D_us_801806CC[idx][1];
            if (self->facingLeft) {
                x = -x;
            }
            entity = &PLAYER;
            entity->posX.i.hi = self->posX.i.hi + x;
            entity->posY.i.hi = self->posY.i.hi + y;
        }
        break;
    case 6:
        if (!self->step_s) {
            entity = &PLAYER;
            x = entity->posX.i.hi - self->posX.i.hi;
            y = entity->posY.i.hi - self->posY.i.hi;
            angle = ratan2(y, x);
            angle += 0x400;
            for (i = 0; i < 8; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_1C), self, entity);
                    entity->rotate = angle;
                    if (self->facingLeft) {
                        entity->posX.i.hi -= 4;
                    } else {
                        entity->posX.i.hi += 4;
                    }
                    entity->zPriority = self->zPriority + 1;
                }
            }
            PlaySfxPositional(SFX_AKMODAN_II_PAIN);
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80180610, self)) {
            SetStep(3);
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            g_BossMgrState |= BOSS_MGR_DEFEAT;
            if (self->ext.akmodanII.grabbing) {
                g_Tilemap.x = self->ext.akmodanII.savedTileX;
                g_Tilemap.width = self->ext.akmodanII.savedTileWidth;
                g_Player.grabState = GRAB_NONE;
            }
            PlaySfxPositional(SFX_AKMODAN_II_DEATH);
            self->step_s++;
            /* fall through */
        case 1:
            if (!AnimateEntity(D_us_80180610, self)) {
                self->step_s++;
            }
            break;
        case 2:
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
            if (primIndex == -1) {
                self->step = 0;
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.akmodanII.prim = prim;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                FntPrint("NO DR_ENV \n");
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            prim->priority = 0x13;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_DEFAULT;
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 1;
            if (self->params) {
                y = 0x180;
            } else {
                y = 0x100;
            }
            clipRect.x = 0;
            clipRect.y = y;
            clipRect.w = 0x80;
            clipRect.h = 0x80;
            drawEnv.clip = clipRect;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &drawEnv);
            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                FntPrint("NO DR_ENV \n");
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            prim->priority = 0x16;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_UNK_800;
            prim = prim->next;
            self->ext.akmodanII.deathPrim = prim;
            if (self->params) {
                y = 0xFF;
            } else {
                y = 0x7F;
            }
            prim->type = PRIM_GT4;
            prim->tpage = 0x110;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x3F;
            prim->v0 = prim->v1 = y - 0x70;
            prim->v2 = prim->v3 = y;
            prim->x0 = prim->x2 = self->posX.i.hi - 0x20;
            prim->x1 = prim->x3 = prim->x0 + 0x3F;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x1F;
            prim->y0 = prim->y1 = prim->y2 - 0x70;
            prim->priority = self->ext.akmodanII.baseZPriority + 1;
            prim->drawMode =
                DRAW_TRANSP | DRAW_UNK02 | DRAW_TPAGE | DRAW_TPAGE2;
            prim = prim->next;
            prim->type = PRIM_TILE;
            if (self->params) {
                y = 0x80;
            } else {
                y = 0;
            }
            prim->x0 = 0;
            prim->y0 = y;
            prim->u0 = 0x80;
            prim->v0 = 0x80;
            prim->r0 = prim->g0 = prim->b0 = 0;
            prim->priority = 0x15;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            self->zPriority = 0x14;
            if (self->params) {
                self->zPriority += 4;
            }
            if (self->params) {
                y = 0x100;
            } else {
                y = 0x80;
            }
            self->posX.i.hi = 0x20;
            self->posY.i.hi = y - 0x20;
            self->palette = g_EInitAkmodanII[3];
            self->flags &= ~(FLAG_POS_CAMERA_LOCKED | 0xF);
            self->step_s++;
            break;
        case 3:
            self->palette = PAL_FLAG(0x1C7);
            self->flags |= FLAG_POS_CAMERA_LOCKED;
            self->zPriority = self->ext.akmodanII.baseZPriority;
            prim = self->ext.akmodanII.deathPrim;
            self->posX.i.hi = prim->x0 + 0x20;
            self->posY.i.hi = prim->y2 - 0x1F;
            prim = self->ext.akmodanII.prim;
            prim->type = PRIM_ENV;
            dr_env = PRIM_DR_ENV(prim);
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 0;
            drawEnv.dtd = 0;
            if (self->params) {
                y = 0x180;
            } else {
                y = 0x100;
            }
            clipRect.x = 0;
            clipRect.y = y;
            clipRect.w = 0x80;
            clipRect.h = 0x80;
            drawEnv.clip = clipRect;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &drawEnv);
            prim->priority = 0x13;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
            self->ext.akmodanII.timer = 0x100;
            self->step_s++;
            /* fall through */
        case 4:
            prim = self->ext.akmodanII.deathPrim;
            x = (Random() & 0x1F) - 0x10;
            y = -(Random() & 0x3F) + 0x20;
            side = Random() & 1;
            FntPrint("timer %x\n", self->ext.akmodanII.timer);
            if (!--self->ext.akmodanII.timer) {
                self->ext.akmodanII.timer = 0x50;
                self->step_s++;
            }
            entity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                 &g_Entities[TOTAL_ENTITY_COUNT]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(
                    E_ID(AKMODAN_DEATH_EFFECT), entity);
                entity->posX.i.hi += x;
                entity->posY.i.hi += y - 8;
                entity->facingLeft = side;
                entity->params = 0;
            }
            if (!(g_Timer & 7)) {
                entity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                     &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(AKMODAN_DEATH_EFFECT), entity);
                    entity->posX.i.hi = x + 0x20;
                    if (self->params) {
                        entity->posY.i.hi = y + 0xE4;
                    } else {
                        entity->posY.i.hi = y + 0x64;
                    }
                    entity->facingLeft = side;
                    entity->params = 1;
                    entity->zPriority = 0x14;
                    if (self->params) {
                        entity->zPriority += 4;
                    }
                }
            }
            break;
        case 5:
            if (!--self->ext.akmodanII.timer) {
                self->step_s++;
            }
            break;
        case 6:
            if (self->flags & FLAG_HAS_PRIMS) {
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
            }
            primIndex = g_api.func_800EDB58(0x16, 0x100);
            if (primIndex == -1) {
                self->step_s = 6;
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.akmodanII.deathPrim = prim;
            prim->type = PRIM_GT4;
            prim->tpage = 0x12;
            prim->clut = 0x1C7;
            prim->u0 = prim->u2 = 0x28;
            prim->u3 = 0;
            prim->u1 = 0;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xC0;
            x = self->posX.i.hi;
            y = self->posY.i.hi;
            if (self->facingLeft) {
                prim->x0 = prim->x2 = x - 0x18;
                prim->x1 = prim->x3 = x + 0x10;
            } else {
                prim->x1 = prim->x3 = x - 0x10;
                prim->x0 = prim->x2 = x + 0x18;
            }
            prim->y2 = prim->y3 = y + 0x20;
            prim->y0 = prim->y1 = y - 0x20;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
            self->ext.akmodanII.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0x12;
                prim->clut = 0x1C7;
                prim->u1 = prim->v1 = 1;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_HIDE;
                prim->p3 = 0;
                prim = prim->next;
            }
            self->animCurFrame = 0;
            self->ext.akmodanII.timer = 1;
            self->ext.akmodanII.deathY = 0;
            PlaySfxPositional(SFX_AKMODAN_II_DISSOLVE);
            self->step_s++;
            break;
        case 7:
            if (!--self->ext.akmodanII.timer) {
                self->ext.akmodanII.timer = 6;
                x = self->posX.i.hi - 0x10;
                y = self->posY.i.hi - 0x20 + self->ext.akmodanII.deathY;
                for (i = 0; i < 0x28; i++) {
                    prim = self->ext.akmodanII.prim;
                    prim = FindFirstUnkPrim(prim);
                    if (prim != NULL) {
                        prim->p3 = 2;
                        prim->u0 = i;
                        prim->v0 = self->ext.akmodanII.deathY + 0x80;
                        if (self->facingLeft) {
                            prim->x0 = x + 0x20 - i;
                        } else {
                            prim->x0 = x + i;
                        }
                        prim->y0 = y;
                        if (self->facingLeft) {
                            LOW(prim->x1) = -i << 12;
                        } else {
                            LOW(prim->x1) = i << 12;
                        }
                        LOW(prim->x2) = 0;
                        prim->x3 = 0;
                        prim->y3 = 0;
                        LOH(prim->u2) = Random() & 0x1F;
                        prim->drawMode = DRAW_UNK02;
                    }
                }
                prim = self->ext.akmodanII.deathPrim;
                prim->v0 = ++prim->v1;
                prim->y0 = ++prim->y1;
                self->ext.akmodanII.deathY++;
                if (self->ext.akmodanII.deathY >= 0x40) {
                    self->step_s++;
                }
            }
            /* fall through */
        case 8:
            prim = self->ext.akmodanII.prim;
            side = 0;
            while (prim->next != NULL) {
                if (prim->p3 == 2) {
                    side |= 1;
                    if (!LOH(prim->u2)) {
                        LOH(prim->u2) = 0x20;
                        prim->p3 = 8;
                    } else {
                        LOH(prim->u2)--;
                    }
                }
                if (prim->p3 == 8) {
                    side |= 1;
                    x = prim->x0 << 16;
                    x += LOHU(prim->x3);
                    y = prim->y0 << 16;
                    y = y + LOHU(prim->y3);
                    x += LOW(prim->x1);
                    y += LOW(prim->x2);
                    prim->x0 = x >> 16;
                    prim->y0 = y >> 16;
                    LOHU(prim->x3) = x & 0xFFFF;
                    LOHU(prim->y3) = y & 0xFFFF;
                    LOW(prim->x2) -= 0x4000;
                    LOH(prim->u2)--;
                    if (!LOH(prim->u2)) {
                        prim->drawMode = DRAW_HIDE;
                        prim->p3 = 0;
                    }
                }
                prim = prim->next;
            }
            prim->x0 = prim->y0 = -0x10;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;
            if (!side) {
                g_BossMgrState |= BOSS_MGR_TERMINATED;
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                self->step_s++;
            }
            break;
        case 9:
            break;
        }
        break;
    case 0xFF:
        FntPrint("charal %x\n", self->animCurFrame);
        self->hitboxState = 1;
        self->hitboxWidth = self->hitboxHeight = 2;
        self->hitboxOffX = self->hitboxOffY = 0;
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1;
            return;
        }
        self->step_s = 0;
        return;
    }
    hitbox = D_us_80180704[0];
    hitbox += D_us_80180720[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
    FntPrint("tsukami %x\n", g_Player.grabState);
}
#endif

void func_us_801957C0(Entity* self) {
    Entity* entity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180444);
        self->hitboxState = 0;
        if (self->params == 2) {
            self->step = 2;
        }
        if (self->params == 3) {
            self->step = 3;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0;
            entity = self - self->params;
            if (entity->ext.akmodanII.unk84) {
                self->animCurFrame = 4;
                self->ext.akmodanII.timer = 64;
                self->step_s++;
            }
            break;
        case 1:
            if (self->facingLeft) {
                self->velocityX = FIX(0.75);
            } else {
                self->velocityX = FIX(-0.75);
            }
            self->step_s++;
        case 2:
            MoveEntity();
            if (!--self->ext.akmodanII.timer) {
                self->zPriority -= 2;
                self->step_s++;
            }
            break;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0;
            entity = self - self->params;
            if (entity->ext.akmodanII.unk84) {
                self->animCurFrame = 2;
                self->step_s++;
            }
            break;
        case 1:
            break;
        }
        break;
    }
}

void EntityAkmodanaAttackHitbox(Entity* self) {
    s32 animFrame;
    s8* hitbox;
    Entity* harpy;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180444);
        /* fall through */
    case 1:
        harpy = self - 1;
        self->facingLeft = harpy->facingLeft;
        self->posX.val = harpy->posX.val;
        self->posY.val = harpy->posY.val;

        animFrame = harpy->animCurFrame;
        animFrame -= 0x23;
        if (animFrame < 0) {
            animFrame = 0;
        }

        hitbox = D_us_8018074C[0];
        animFrame = D_us_80180764[animFrame];
        hitbox += animFrame * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;

        if (harpy->entityId != E_ID(AKMODAN_II)) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_80195A8C(Entity* self) {
    s16 angle;

    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180450);
        self->blendMode = BLEND_TRANSP;
        self->drawFlags = ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
        self->hitboxWidth = self->hitboxHeight = 6;
        self->rotate += 0x180 - Random() * 3;
        angle = self->rotate;
        self->posX.i.hi += (rsin(angle) * 8) >> 12;
        self->posY.i.hi += (rcos(angle) * -28) >> 12;
        self->velocityX = rsin(angle) * 24;
        self->velocityY = rcos(angle) * -24;
        self->scaleX = 0x60;
        self->scaleY = 0x60;
        self->ext.akmodanII.unk86 = 0;
        /* fall through */
    case 1:
        if (!AnimateEntity(anim_burst_in, self)) {
            SetStep(2);
        }
        MoveEntity();
        self->scaleX += 0xC;
        self->scaleY += 0xC;
        break;
    case 2:
        if (!self->step_s) {
            self->velocityX >>= 2;
            self->velocityY >>= 2;
            self->step_s++;
        }
        MoveEntity();
        if (!AnimateEntity(anim_burst_loop, self)) {
            self->ext.akmodanII.unk86++;
        }
        if (self->ext.akmodanII.unk86 > 16) {
            self->drawFlags |= ENTITY_OPACITY;
            self->opacity = 0x80;
            self->hitboxState = 0;
            SetStep(3);
        }
        break;
    case 3:
        self->opacity -= 2;
        self->scaleX += 0x18;
        self->scaleY += 0x18;
        if (!AnimateEntity(anim_burst_out, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_80195D04(Entity* self) {
    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180450);
        self->animSet = 5;
        self->palette += 0x8000;
        self->unk5A = 0;
        self->blendMode = BLEND_TRANSP;
        self->velocityY = FIX(-0.375);
        self->hitboxWidth = self->hitboxHeight = 3;
        /* fall through */
    case 1:
        MoveEntity();
        if (self->pose > 25) {
            self->hitboxState = 0;
        }
        if (!AnimateEntity(anim_flame, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

static AnimateEntityFrame D_us_8018076C[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(3, 3, 0),  POSE(3, 4, 0),
    POSE(3, 5, 0),  POSE(3, 6, 0),  POSE(3, 7, 0),  POSE(3, 8, 0),
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE_END};

void EntityAkmodanDeathEffect(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 14;
        self->unk5A = 121;
        self->drawFlags = ENTITY_OPACITY;
        if (self->params) {
            self->palette = PAL_UNK_2EE;
            self->opacity = 8;
            self->blendMode = BLEND_TRANSP | BLEND_SUB;
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        } else {
            self->palette = PAL_UNK_2E4;
            self->zPriority += 2;
            self->opacity = 0x14;
            self->blendMode = BLEND_TRANSP | BLEND_ADD;
        }
        /* fall through */
    case 1:
        self->posY.val -= FIX(1);
        if (!AnimateEntity(D_us_8018076C, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
