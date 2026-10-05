// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno2.h"

extern EInit g_EInitMalachi;
extern EInit D_us_80180904;
extern EInit D_us_80180910;
extern EInit g_EInitParticle;

static s16 sensors1[] = {0, 72, 8, 0};
static s16 sensors2[] = {0, 40, 0, 4, 8, -4, -16, 0};
// Does all the frames of the charge, then swipes the claw down
static AnimateEntityFrame anim_swipe_attack[] = {
    {32, 9}, {3, 10}, {3, 9},   {6, 11}, {6, 12}, {5, 13}, {5, 14}, {20, 13},
    {2, 15}, {2, 17}, {33, 16}, {3, 17}, {2, 18}, {2, 19}, {2, 20}, {2, 21},
    {2, 22}, {6, 9},  {3, 23},  {4, 24}, {3, 25}, POSE_END};
static AnimateEntityFrame anim_idle[] = {
    {3, 1}, {5, 2}, {5, 3}, {3, 4},      {3, 5},
    {5, 6}, {5, 7}, {3, 8}, POSE_LOOP(0)};
// Standing, leans backward with arms outstretched
static AnimateEntityFrame anim_gloat_init[] = {
    {2, 9}, {3, 10}, {3, 9}, {3, 11}, {3, 12}, {4, 13}, {3, 14}, POSE_END};
// Quick pulsing effect, stays leaned back but sort of shaking with energy
static AnimateEntityFrame anim_gloating[] = {{2, 13}, {2, 14}, POSE_LOOP(0)};
static AnimateEntityFrame anim_flying[] = {
    {6, 26}, {6, 27}, {6, 28}, {6, 29}, POSE_LOOP(0)};
static AnimateEntityFrame anim_liftoff[] = {
    {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 30}, {2, 31}, POSE_END};
static AnimateEntityFrame anim_landing[] = {
    {1, 1},  {1, 2}, {1, 3}, {1, 4}, {1, 30}, {1, 31},
    {5, 30}, {4, 4}, {3, 3}, {2, 2}, {2, 1},  POSE_END};
static AnimateEntityFrame anim_skull_hexagram_spawn[] = {
    {4, 32}, {4, 33}, {2, 34}, {2, 35}, {1, 36}, {1, 37}, {1, 38}, {1, 39},
    {1, 38}, {1, 39}, {1, 40}, {1, 39}, {1, 40}, {1, 41}, {1, 40}, {1, 41},
    {1, 42}, {1, 41}, {1, 42}, {1, 43}, {1, 42}, POSE_END};
static AnimateEntityFrame anim_skull_hexagram_flash[] = {
    {1, 43}, {1, 44}, POSE_LOOP(0)};

typedef enum {
    MAL_INIT,
    MAL_INIT_WAIT,
    MAL_IDLE,
    MAL_FLY,
    MAL_4_UNUSED, // does not exist at all
    MAL_HOP,
    MAL_SWIPE,
    MAL_SHOOT,
    MAL_8_UNUSED, // does not exist at all
    MAL_GLOAT,
    MAL_DEAD
} MalachiSteps;

void EntityMalachi(Entity* self) {
    RECT clipRect;
    DRAWENV drawEnv;

    s32 xVar;
    s32 primIndex;
    u32 coll;
    DR_ENV* dr_env;
    s32 yVar;
    Entity* other;
    Primitive* prim;

    if ((g_Player.status & PLAYER_STATUS_DEAD) && (self->step < 9)) {
        SetStep(MAL_GLOAT);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 10)) {
        self->hitboxState = 0;
        SetStep(MAL_DEAD);
    }
    if (self->ext.malachi.shootCooldown) {
        self->ext.malachi.shootCooldown--;
    }
    switch (self->step) {
    case MAL_INIT:
        InitializeEntity(g_EInitMalachi);
        other = self + 1;
        CreateEntityFromCurrentEntity(E_MALACHI_SHOOTER, other);
        self->ext.malachi.halfHP = self->hitPoints;
        self->ext.malachi.halfHP /= 2;
        /* fallthrough */
    case MAL_INIT_WAIT:
        if (UnkCollisionFunc3(sensors2) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(MAL_IDLE);
        }
        break;
    case MAL_IDLE:
        if (!self->step_s) {
            self->ext.malachi.timer = 0x40;
            self->step_s++;
            if (self->hitPoints < self->ext.malachi.halfHP) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->ext.malachi.timer = 0x20;
            }
        }
        AnimateEntity(anim_idle, self);
        self->ext.malachi.timer--;
        if (self->hitPoints < self->ext.malachi.halfHP) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (!self->ext.malachi.timer) {
                SetStep(MAL_HOP);
            }
        } else {
            if (self->ext.malachi.timer == 0x20) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft == ((GetSideToPlayer() & 1) ^ 1)) {
                SetStep(MAL_FLY);
            }
            if (!self->ext.malachi.timer) {
                self->step_s = 0;
            }
        }
        break;
    case MAL_FLY:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(anim_liftoff, self) == 0) {
                self->ext.malachi.flightHeight =
                    (self->posY.i.hi + g_Tilemap.scrollY.i.hi) - 0x20;
                SetSubStep(1);
            }
            break;
        case 1:
            self->velocityX = 0;
            self->velocityY = FIX(-4.0);
            self->animCurFrame = 0x1A;
            self->step_s++;
            /* fallthrough */
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.1875);
            yVar = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            yVar -= self->ext.malachi.flightHeight;
            if ((yVar <= 0) || (self->velocityY > 0)) {
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(anim_flying, self);
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_WING_FLAP_A);
            }
            yVar = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            yVar -= self->ext.malachi.flightHeight;
            if (yVar == 0) {
                self->ext.malachi.timer = 0x80;
                self->velocityY = 0;
                self->step_s++;
            } else if (yVar < 0) {
                self->posY.i.hi++;
            } else {
                self->posY.i.hi--;
            }
            break;
        case 4:
            AnimateEntity(anim_flying, self);
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_WING_FLAP_A);
            }
            coll = UnkCollisionFunc2(sensors1);
            if (coll & 0x80) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft) {
                self->velocityX = FIX(0.75);
            } else {
                self->velocityX = FIX(-0.75);
            }
            if (!self->ext.malachi.shootCooldown) {
                SetStep(MAL_SHOOT);
                self->ext.malachi.fly_to_shoot = 1;
            }
            if (!self->ext.malachi.timer) {
                if (coll == 1) {
                    SetSubStep(5);
                }
            } else {
                self->ext.malachi.timer--;
            }
            break;
        case 5:
            self->animCurFrame = 0x1C;
            if (UnkCollisionFunc3(sensors2) & 1) {
                SetSubStep(6);
            }
            break;
        case 6:
            if (AnimateEntity(anim_landing, self) == 0) {
                if (!self->ext.malachi.shootCooldown) {
                    SetStep(MAL_SHOOT);
                    self->ext.malachi.fly_to_shoot = 0;
                } else {
                    SetStep(MAL_IDLE);
                }
            }
            break;
        }
        break;
    case MAL_HOP:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(1.75);
            } else {
                self->velocityX = FIX(-1.75);
            }
            self->velocityY = FIX(-5.0);
            self->animCurFrame = 0x1A;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if (self->velocityY > 0) {
                self->step_s++;
                if (!self->ext.malachi.hopTimer) {
                    self->ext.malachi.hopTimer = 2;
                } else {
                    self->ext.malachi.hopTimer--;
                }
            }
            break;
        case 2:
            self->animCurFrame = 0x1C;
            if (UnkCollisionFunc3(sensors2) & 1) {
                SetSubStep(3);
            }
            break;
        case 3:
            if (AnimateEntity(anim_landing, self) == 0) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                SetSubStep(0);
                if (!self->ext.malachi.shootCooldown) {
                    SetStep(MAL_SHOOT);
                    self->ext.malachi.fly_to_shoot = 0;
                }
                if (GetDistanceToPlayerX() < 0x48) {
                    SetStep(MAL_SWIPE);
                }
            }
            break;
        }
        break;
    case MAL_SWIPE:
        if (AnimateEntity(anim_swipe_attack, self) == 0) {
            SetStep(MAL_IDLE);
        }
        break;
    case MAL_SHOOT:
        switch (self->step_s) {
        case 0:
            // Grab our attached EnittyMalachiShooter and set it to shoot
            other = self + 1;
            other->step_s = 0;
            other->step = 2;
            other->pose = 0;
            other->poseTimer = 0;
            self->ext.malachi.timer = 0x80;
            PlaySfxPositional(SFX_MAGIC_NOISE_SWEEP);
            self->step_s++;
            /* fallthrough */
        case 1:
            if (self->ext.malachi.fly_to_shoot) {
                AnimateEntity(anim_flying, self);
                if (!self->poseTimer && self->pose == 1) {
                    PlaySfxPositional(SFX_WING_FLAP_A);
                }
            }
            if (!--self->ext.malachi.timer) {
                self->ext.malachi.shootCooldown = 0x180;
                SetStep(MAL_IDLE);
                if (self->ext.malachi.fly_to_shoot) {
                    SetStep(MAL_FLY);
                    self->step_s = 5;
                }
            }
            break;
        }
        break;
    case MAL_GLOAT:
        switch (self->step_s) {
        case 0:
            if (UnkCollisionFunc3(sensors2) & 1) {
                self->step_s++;
            }
            break;
        case 1:
            if (AnimateEntity(anim_gloat_init, self) == 0) {
                SetSubStep(2);
            }
            break;
        case 2:
            AnimateEntity(anim_gloating, self);
            if ((g_Player.status & PLAYER_STATUS_DEAD) == 0) {
                SetStep(MAL_IDLE);
            }
            break;
        }
        break;
    case MAL_DEAD:
        switch (self->step_s) {
        case 0:
            other = self + 1;
            DestroyEntity(other);
            if (self->animCurFrame > 12 && self->animCurFrame < 23) {
                self->animCurFrame = 1;
            }
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
            if (primIndex == -1) {
                self->step = 0;
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.malachi.prim = prim;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            prim->priority = 0xF;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_DEFAULT;
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 1;
            drawEnv.r0 = drawEnv.g0 = drawEnv.b0 = 0;
            if (self->params) {
                yVar = 0x180;
            } else {
                yVar = 0x100;
            }
            clipRect.x = 0;
            clipRect.y = yVar;
            clipRect.w = 0x80;
            clipRect.h = 0x80;
            drawEnv.clip = clipRect;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &drawEnv);
            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            prim->priority = 0x12;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_UNK_800;
            prim = prim->next;
            self->ext.malachi.deathPrim = prim;
            if (self->params) {
                yVar = 0xFF;
            } else {
                yVar = 0x7F;
            }
            prim->type = PRIM_GT4;
            prim->tpage = 0x110;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x3F;
            prim->v0 = prim->v1 = yVar - 0x70;
            prim->v2 = prim->v3 = yVar;
            prim->x0 = prim->x2 = self->posX.i.hi - 0x20;
            prim->x1 = prim->x3 = prim->x0 + 0x40;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x28;
            prim->y0 = prim->y1 = prim->y2 - 0x70;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
            prim->type = PRIM_TILE;
            if (self->params) {
                yVar = 0x80;
            } else {
                yVar = 0;
            }
            prim->x0 = 0;
            prim->y0 = yVar;
            prim->u0 = 0x80;
            prim->v0 = 0x80;
            prim->r0 = prim->g0 = prim->b0 = 0;
            prim->priority = 0x11;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            self->zPriority = 0x10;
            if (self->params) {
                self->zPriority += 4;
            }
            if (self->params) {
                yVar = 0x100;
            } else {
                yVar = 0x80;
            }
            self->posX.i.hi = 0x20;
            self->posY.i.hi = yVar - 0x28;
            self->palette = g_EInitMalachi[3];
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
            self->step_s++;
            break;

        case 1:
            self->animCurFrame = 0;
            prim = self->ext.malachi.prim;
            prim->type = PRIM_ENV;
            dr_env = *(DR_ENV**)&prim->r1;
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 0;
            drawEnv.dtd = 0;
            if (self->params) {
                yVar = 0x180;
            } else {
                yVar = 0x100;
            }
            clipRect.x = 0;
            clipRect.y = yVar;
            clipRect.w = 0x80;
            clipRect.h = 0x80;
            drawEnv.clip = clipRect;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &drawEnv);
            prim->priority = 0xF;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next; // pointless since we never access it after this
            self->ext.malachi.flightHeight = 0x28;
            self->ext.malachi.timer = 0x10;
            self->step_s++;
            /* fallthrough */
        case 2:
            prim = self->ext.malachi.deathPrim;
            xVar = Random() & 0x3F;
            yVar = self->ext.malachi.flightHeight;
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_EXPLODE_B);
                other = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(E_EXPLOSION, other);
                    other->posX.i.hi = prim->x0 + xVar;
#ifdef VERSION_PSP
                    other->posY.i.hi = prim->y2 - 0x30 + yVar;
#else
                    other->posY.i.hi = prim->y2 + yVar - 0x30;
#endif
                    other->params = 3;
                }
            }
            other = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromCurrentEntity(E_CTULHU_DEATH, other);
                other->posX.i.hi = (self->posX.i.hi - 0x20) + xVar;
                other->posY.i.hi = self->posY.i.hi + yVar + 4;
                other->facingLeft = coll; // Uninitialized!
                other->params = 1;
                other->zPriority = 0x10;
                if (self->params) {
                    other->zPriority += 4;
                }
            }
            if (!--self->ext.malachi.timer) {
                self->ext.malachi.timer = 2;
                self->ext.malachi.flightHeight -= 2;
                if (self->ext.malachi.flightHeight < -0x28) {
                    self->ext.malachi.timer = 0x40;
                    self->step_s++;
                }
            }
            break;
        case 3:
            if (!--self->ext.malachi.timer) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
    if (self->animCurFrame >= 15 && self->animCurFrame < 19) {
        self->hitboxOffX = -0x12;
        self->hitboxOffY = 0x11;
        self->hitboxWidth = 0x16;
        self->hitboxHeight = 0x16;
    } else {
        self->hitboxOffX = -1;
        self->hitboxOffY = 1;
        self->hitboxWidth = 0x13;
        self->hitboxHeight = 0x26;
    }
}

// This entity always exists attached to the Malachi
// It sits in the slot above the Malachi.
void EnittyMalachiShooter(Entity* self) {
    Entity* other;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180904);
        self->hitboxWidth = 0x19;
        self->hitboxHeight = 0xE;
        self->hitboxOffX = -0x2B;
        self->hitboxOffY = 0x1B;
        /* fallthrough */
    case 1:
        self->animCurFrame = 0;
        other = self - 1;
        self->facingLeft = other->facingLeft;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        if (other->animCurFrame == 0xF) {
            self->hitboxState = 1;
        } else {
            self->hitboxState = 0;
        }
        break;
    // The malachi itself sets this step, which commands to shoot a ball
    case 2:
        switch (self->step_s) {
        case 0:
            other = self - 1;
            self->facingLeft = other->facingLeft;
            self->posX.i.hi = other->posX.i.hi;
            self->posY.i.hi = other->posY.i.hi;
            if (self->facingLeft) {
                self->posX.i.hi += 0x20;
            } else {
                self->posX.i.hi -= 0x20;
            }
            self->zPriority = other->zPriority + 1;
            self->blendMode = BLEND_ADD | BLEND_TRANSP;
            if (AnimateEntity(anim_skull_hexagram_spawn, self) == 0) {
                self->ext.malachi.timer = 0x40;
                SetSubStep(1);
            }
            break;
        case 1:
            AnimateEntity(anim_skull_hexagram_flash, self);
            if (!--self->ext.malachi.timer) {
                PlaySfxPositional(SFX_EXPLODE_A);
                other = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_MALACHI_BALL, self, other);
                    other->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        other->posX.i.hi += 8;
                    } else {
                        other->posX.i.hi -= 8;
                    }
                }
                self->drawFlags = ENTITY_OPACITY;
                self->opacity = 0x80;
                if (self->facingLeft) {
                    self->velocityX = FIX(-8.0);
                } else {
                    self->velocityX = FIX(8.0);
                }
                self->step_s++;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityX -= self->velocityX / 4;
            self->opacity -= 4;
            if (!self->opacity) {
                self->drawFlags = ENTITY_DEFAULT;
                self->blendMode = BLEND_NO;
                self->animCurFrame = 0;
                SetStep(1);
            }
        }
        break;
    }
}

void EntityMalachiBall(Entity* self) {
    Entity* other;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180910);
        self->animCurFrame = 0x2D;
        self->drawFlags = ENTITY_SCALEX;
        self->scaleX = 0;
        if (self->facingLeft) {
            self->velocityX = FIX(8.0);
        } else {
            self->velocityX = FIX(-8.0);
        }
        /* fallthrough */
    case 1:
        MoveEntity();
        self->velocityX -= self->velocityX / 4;
        self->scaleX += 0x10;
        if (self->scaleX > 0x100) {
            self->drawFlags = ENTITY_ROTATE;
            if (self->facingLeft) {
                self->velocityX = FIX(0.625);
            } else {
                self->velocityX = FIX(-0.625);
            }
            PlaySfxPositional(SFX_MALACHI_ROLLING_ORB);
            self->ext.malachi.timer = 0;
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->rotate -= ROT(2.109375);
        if (g_Timer & 2) {
            self->palette = D_us_80180910[3];
        } else {
            self->palette = D_us_80180910[3] + 1;
        }
        self->ext.malachi.timer++;
        if (!(self->ext.malachi.timer & 0x3F)) {
            PlaySfxPositional(SFX_MALACHI_ROLLING_ORB);
        }
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_MALACHI_BALL_WISP, self, other);
            angle = Random() * 0x10;
            other->posX.i.hi += ((rcos(angle) * 28) >> 0xC);
            other->posY.i.hi += ((rsin(angle) * 28) >> 0xC);
            other->zPriority = self->zPriority + 1;
            if (self->facingLeft) {
                angle += ROT(180);
            }
            other->rotate = angle;
        }
        if (self->velocityX > 0) {
            if (self->posX.i.hi > 0x140) {
                DestroyEntity(self);
            }
        } else {
            if (self->posX.i.hi < -0x40) {
                DestroyEntity(self);
            }
        }
        break;
    }
}

// Data comes after the charal string for main malachi, so down here.
// These are the little green wisps that appear around the edges of
// the malachi ball.
static AnimateEntityFrame anim_green_flame[] = {
    {2, 1}, {2, 2}, {2, 3},  {2, 4},  {2, 5},  {2, 6},  {2, 7},
    {2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 12}, {2, 13}, POSE_END};

void EntityMalachiBallWisp(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 0xE;
        self->unk5A = 0x5C;
        self->palette = 0x2EE;
        self->drawFlags = ENTITY_ROTATE | ENTITY_SCALEX;
        self->scaleX = 0x60;
        self->scaleY = 0xC0;
        self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
        angle = self->rotate;
        self->velocityX = rsin(angle) * 0x10;
        self->velocityY = rcos(angle) * -0x10;
        /* fallthrough */
    case 1:
        MoveEntity();
        if (AnimateEntity(anim_green_flame, self) == 0) {
            DestroyEntity(self);
        }
    }
}
