// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno2/rno2.h"

extern EInit g_EInitMalachi;
extern EInit D_us_80180904;
extern EInit D_us_80180910;
extern EInit g_EInitParticle;

static s16 sensors1[] = {0, 72, 8, 0};
static s16 sensors2[] = {0, 40, 0, 4, 8, -4, -16, 0};
// Does all the frames of the charge, then swipes the claw down
static AnimateEntityFrame anim_charge_swipe[] = {
    {32, 9}, {3, 10}, {3, 9},   {6, 11}, {6, 12}, {5, 13}, {5, 14}, {20, 13},
    {2, 15}, {2, 17}, {33, 16}, {3, 17}, {2, 18}, {2, 19}, {2, 20}, {2, 21},
    {2, 22}, {6, 9},  {3, 23},  {4, 24}, {3, 25}, POSE_END};
static AnimateEntityFrame anim_idle[] = {
    {3, 1}, {5, 2}, {5, 3}, {3, 4},      {3, 5},
    {5, 6}, {5, 7}, {3, 8}, POSE_LOOP(0)};
// Standing, leans backward with arms outstretched
static AnimateEntityFrame anim_charge[] = {
    {2, 9}, {3, 10}, {3, 9}, {3, 11}, {3, 12}, {4, 13}, {3, 14}, POSE_END};
// Quick pulsing effect, stays leaned back but sort of shaking with energy
static AnimateEntityFrame anim_charging[] = {{2, 13}, {2, 14}, POSE_LOOP(0)};
static AnimateEntityFrame anim_flying[] = {
    {6, 26}, {6, 27}, {6, 28}, {6, 29}, POSE_LOOP(0)};
static AnimateEntityFrame anim_landing[] = {
    {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 30}, {2, 31}, POSE_END};
static AnimateEntityFrame anim_another_landing[] = {
    {1, 1},  {1, 2}, {1, 3}, {1, 4}, {1, 30}, {1, 31},
    {5, 30}, {4, 4}, {3, 3}, {2, 2}, {2, 1},  POSE_END};
static AnimateEntityFrame anim_skull_hexagram_spawn[] = {
    {4, 32}, {4, 33}, {2, 34}, {2, 35}, {1, 36}, {1, 37}, {1, 38}, {1, 39},
    {1, 38}, {1, 39}, {1, 40}, {1, 39}, {1, 40}, {1, 41}, {1, 40}, {1, 41},
    {1, 42}, {1, 41}, {1, 42}, {1, 43}, {1, 42}, POSE_END};
static AnimateEntityFrame anim_skull_hexagram_flash[] = {
    {1, 43}, {1, 44}, POSE_LOOP(0)};

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
        SetStep(9);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 10)) {
        self->hitboxState = 0;
        SetStep(10);
    }
    if (self->ext.malachi.unk82) {
        self->ext.malachi.unk82--;
    }
    switch (self->step) {
    case 0x0:
        InitializeEntity(g_EInitMalachi);
        other = self + 1;
        CreateEntityFromCurrentEntity(E_UNK_2C, other);
        self->ext.malachi.unk88 = self->hitPoints;
        self->ext.malachi.unk88 /= 2;
        /* fallthrough */
    case 0x1:
        if (UnkCollisionFunc3(sensors2) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(2);
        }
        break;
    case 0x2:
        if (!self->step_s) {
            self->ext.malachi.unk80 = 0x40;
            self->step_s += 1;
            if (self->hitPoints < self->ext.malachi.unk88) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->ext.malachi.unk80 = 0x20;
            }
        }
        AnimateEntity(anim_idle, self);
        self->ext.malachi.unk80--;
        if (self->hitPoints < self->ext.malachi.unk88) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (!self->ext.malachi.unk80) {
                SetStep(5);
            }
        } else {
            if (self->ext.malachi.unk80 == 0x20) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft == ((GetSideToPlayer() & 1) ^ 1)) {
                SetStep(3);
            }
            if (!self->ext.malachi.unk80) {
                self->step_s = 0;
            }
        }
        break;
    case 0x3:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(anim_landing, self) == 0) {
                self->ext.malachi.unk9C =
                    (self->posY.i.hi + g_Tilemap.scrollY.i.hi) - 0x20;
                SetSubStep(1);
            }
            break;
        case 1:
            self->velocityX = 0;
            self->velocityY = FIX(-4.0);
            self->animCurFrame = 0x1A;
            self->step_s += 1;
            /* fallthrough */
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.1875);
            yVar = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            yVar -= self->ext.malachi.unk9C;
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
            yVar -= self->ext.malachi.unk9C;
            if (yVar == 0) {
                self->ext.malachi.unk80 = 0x80;
                self->velocityY = 0;
                self->step_s += 1;
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
            if (!self->ext.malachi.unk82) {
                SetStep(7);
                self->ext.malachi.unk85 = 1;
            }
            if (!self->ext.malachi.unk80) {
                if (coll == 1) {
                    SetSubStep(5);
                }
            } else {
                self->ext.malachi.unk80--;
            }
            break;
        case 5:
            self->animCurFrame = 0x1C;
            if (UnkCollisionFunc3(sensors2) & 1) {
                SetSubStep(6);
            }
            break;
        case 6:
            if (AnimateEntity(anim_another_landing, self) == 0) {
                if (!self->ext.malachi.unk82) {
                    SetStep(7);
                    self->ext.malachi.unk85 = 0;
                } else {
                    SetStep(2);
                }
            }
            break;
        }
        break;
    case 0x5:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(1.75);
            } else {
                self->velocityX = FIX(-1.75);
            }
            self->velocityY = FIX(-5.0);
            self->animCurFrame = 0x1A;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if (self->velocityY > 0) {
                self->step_s += 1;
                if (!self->ext.malachi.unk84) {
                    self->ext.malachi.unk84 = 2;
                } else {
                    self->ext.malachi.unk84 -= 1;
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
            if (AnimateEntity(anim_another_landing, self) == 0) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                SetSubStep(0);
                if (!self->ext.malachi.unk82) {
                    SetStep(7);
                    self->ext.malachi.unk85 = 0;
                }
                if (GetDistanceToPlayerX() < 0x48) {
                    SetStep(6);
                }
            }
            break;
        }
        break;
    case 0x6:
        if (AnimateEntity(anim_charge_swipe, self) == 0) {
            SetStep(2);
        }
        break;
    case 0x7:
        switch (self->step_s) {
        case 0:
            other = self + 1;
            other->step_s = 0;
            other->step = 2;
            other->pose = 0;
            other->poseTimer = 0;
            self->ext.malachi.unk80 = 0x80;
            PlaySfxPositional(SFX_MAGIC_NOISE_SWEEP);
            self->step_s += 1;
            /* fallthrough */
        case 1:
            if (self->ext.malachi.unk85) {
                AnimateEntity(anim_flying, self);
                if (!self->poseTimer && self->pose == 1) {
                    PlaySfxPositional(SFX_WING_FLAP_A);
                }
            }
            if (!--self->ext.malachi.unk80) {
                self->ext.malachi.unk82 = 0x180;
                SetStep(2);
                if (self->ext.malachi.unk85) {
                    SetStep(3);
                    self->step_s = 5;
                }
            }
            break;
        }
        break;
    case 0x9:
        switch (self->step_s) {
        case 0:
            if (UnkCollisionFunc3(sensors2) & 1) {
                self->step_s++;
            }
            break;
        case 1:
            if (AnimateEntity(anim_charge, self) == 0) {
                SetSubStep(2);
            }
            break;
        case 2:
            AnimateEntity(anim_charging, self);
            if ((g_Player.status & PLAYER_STATUS_DEAD) == 0) {
                SetStep(2);
            }
            break;
        }
        break;
    case 0xA:
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
            self->ext.malachi.primA4 = prim;
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
            self->step_s += 1;
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
            self->ext.malachi.unk9C = 0x28;
            self->ext.malachi.unk80 = 0x10;
            self->step_s += 1;
            /* fallthrough */
        case 2:
            prim = self->ext.malachi.primA4;
            xVar = Random() & 0x3F;
            yVar = self->ext.malachi.unk9C;
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_EXPLODE_B);
                other = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(E_EXPLOSION, other);
                    other->posX.i.hi = prim->x0 + xVar;
                    other->posY.i.hi = (prim->y2 - 0x30) + yVar;
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
            if (!--self->ext.malachi.unk80) {
                self->ext.malachi.unk80 = 2;
                self->ext.malachi.unk9C -= 2;
                if (self->ext.malachi.unk9C < -0x28) {
                    self->ext.malachi.unk80 = 0x40;
                    self->step_s++;
                }
            }
            break;
        case 3:
            if (!--self->ext.malachi.unk80) {
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

void func_us_801C4960(Entity* self) {
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
                self->ext.malachi.unk80 = 0x40;
                SetSubStep(1);
            }
            break;
        case 1:
            AnimateEntity(anim_skull_hexagram_flash, self);
            if (!--self->ext.malachi.unk80) {
                PlaySfxPositional(SFX_EXPLODE_A);
                other = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_UNK_2D, self, other);
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
                self->step_s += 1;
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

void func_us_801C4C0C(Entity* self) {
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
            self->ext.malachi.unk80 = 0;
            self->step += 1;
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
        self->ext.malachi.unk80++;
        if (!(self->ext.malachi.unk80 & 0x3F)) {
            PlaySfxPositional(SFX_MALACHI_ROLLING_ORB);
        }
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_UNK_2E, self, other);
            angle = Random() * 0x10;
            other->posX.i.hi += ((rcos(angle) * 0x1C) >> 0xC);
            other->posY.i.hi += ((rsin(angle) * 0x1C) >> 0xC);
            other->zPriority = self->zPriority + 1;
            if (self->facingLeft) {
                angle += 0x800;
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

// Data comes after the charal string for main malachi
static AnimateEntityFrame anim_green_flame[] = {
    {2, 1}, {2, 2}, {2, 3},  {2, 4},  {2, 5},  {2, 6},  {2, 7},
    {2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 12}, {2, 13}, POSE_END};

void func_us_801C4EA8(Entity* self) {
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
