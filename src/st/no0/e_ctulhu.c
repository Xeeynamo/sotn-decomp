// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

typedef enum {
    CTULHU_INIT,
    CTULHU_GROUND_INIT,
    CTULHU_IDLE,
    CTULHU_FLY,
    CTULHU_UNUSED_4,
    CTULHU_HOP,
    CTULHU_TRIPLE_FIREBALL,
    CTULHU_SINGLE_FIREBALL,
    CTULHU_ICE_SHOCKWAVE,
    CTULHU_PLAYER_DEAD,
    CTULHU_DEATH,
    CTULHU_DEBUG = 255
} CtulhuSteps;

static u16 sensors_unk[] = {0, 72, 8, 0};
static u16 sensors_ground[][2] = {{0, 40}, {0, 4}, {8, -4}, {-16, 0}};
static u8 anim_shockwave_throw[] = {
    0x31, 0x05, 0x03, 0x06, 0x03, 0x05, 0x06, 0x07, 0x06, 0x08, 0x05,
    0x09, 0x05, 0x0A, 0x14, 0x09, 0x02, 0x0B, 0x02, 0x0D, 0x21, 0x0C,
    0x03, 0x0D, 0x02, 0x0E, 0x02, 0x0F, 0x02, 0x10, 0x02, 0x11, 0x02,
    0x12, 0x06, 0x05, 0x03, 0x13, 0x04, 0x14, 0x03, 0x13, 0xFF, 0x00};
static u8 anim_idle_breath[] = {0x05, 0x01, 0x05, 0x02, 0x05, 0x03, 0x05, 0x04,
                                0x05, 0x03, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00};
static u8 anim_player_death_laugh[] = {
    0x02, 0x05, 0x03, 0x06, 0x03, 0x05, 0x03, 0x07,
    0x03, 0x08, 0x04, 0x09, 0x03, 0x0A, 0xFF, 0x00};
static u8 anim_laugh_static[] = {
    0x02, 0x09, 0x02, 0x0A, 0x00, 0x00, 0x00, 0x00};
static u8 anim_wing_flap[] = {
    0x06, 0x15, 0x06, 0x16, 0x06, 0x17, 0x06, 0x16, 0x00, 0x00, 0x00, 0x00};
static u8 anim_shoot_single_fireball[] = {
    0x04, 0x15, 0x03, 0x16, 0x02, 0x17, 0x02, 0x18, 0x02, 0x19, 0x02,
    0x1A, 0x04, 0x1B, 0x04, 0x1C, 0x04, 0x1D, 0x02, 0x18, 0x02, 0x19,
    0x03, 0x1A, 0x03, 0x15, 0x04, 0x16, 0x05, 0x17, 0x00, 0x00};
static u8 anim_fly_from_ground[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04,
    0x02, 0x1E, 0x02, 0x1F, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_shoot_triple_fireball[] = {
    0x01, 0x20, 0x01, 0x02, 0x01, 0x20, 0x01, 0x02, 0x01, 0x20, 0x01, 0x02,
    0x01, 0x20, 0x01, 0x02, 0x01, 0x20, 0x01, 0x02, 0x01, 0x20, 0x01, 0x02,
    0x01, 0x20, 0x01, 0x02, 0x01, 0x20, 0x01, 0x02, 0x01, 0x20, 0x01, 0x02,
    0x01, 0x20, 0x01, 0x02, 0x01, 0x20, 0x06, 0x21, 0x03, 0x22, 0x02, 0x23,
    0x02, 0x24, 0x08, 0x23, 0x04, 0x25, 0x04, 0x22, 0x10, 0x02, 0x00, 0x00};
static u8 anim_fireball[] = {
    0x02, 0x26, 0x02, 0x27, 0x02, 0x28, 0x02, 0x29, 0x02, 0x2A, 0x00, 0x00};
static u8 anim_land[] = {
    0x01, 0x01, 0x01, 0x02, 0x01, 0x03, 0x01, 0x04, 0x01, 0x1E, 0x01, 0x1F,
    0x05, 0x1E, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00};
static s16 triple_fireball_rot_z[] = {0x0180, 0x0000, 0xFE80, 0x0000};
extern u8 anim_death[] = {
    0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05,
    0x03, 0x06, 0x03, 0x07, 0x03, 0x08, 0x03, 0x09, 0x03, 0x0A,
    0x03, 0x0B, 0x03, 0x0C, 0x03, 0x0D, 0xFF, 0x00};
extern s16* ctulhu_shockwave_uvs[]; // uvs for shockwave

void EntityCtulhu(Entity* self) {
    Primitive* prim;
    Entity* newEntity;
    DR_ENV* dr_env;
    RECT clipRect;
    DRAWENV drawEnv;
    s32 primIndex;
    s32 colRet;
    s32 posX;
    s32 posY;
    s32 i;
    s16 angle;

    if ((g_Player.status & PLAYER_STATUS_DEAD) &&
        self->step < CTULHU_PLAYER_DEAD) {
        SetStep(CTULHU_PLAYER_DEAD);
    }

    if ((self->flags & FLAG_DEAD) && self->step < CTULHU_DEATH) {
        self->hitboxState = 0;
        PlaySfxPositional(0x757);
        SetStep(CTULHU_DEATH);
    }

    switch (self->step) {
    case CTULHU_INIT:
        InitializeEntity(g_EInitCtulhu);
        self->animCurFrame = 1;
        // fallthrough
    case CTULHU_GROUND_INIT:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(CTULHU_IDLE);
        }
        break;
    case CTULHU_IDLE:
        if (!self->step_s) {
            self->ext.ctulhu.timer = 0x40;
            self->step_s++;
        }
        AnimateEntity(anim_idle_breath, self);
        if (self->ext.ctulhu.timer == 0x20) {
            self->facingLeft ^= 1;
        }

        // When player is close enough to the direction Ctulhu is looking,
        // switch to attack routine
        if (self->facingLeft == ((GetSideToPlayer() & 1) ^ 1) &&
            GetDistanceToPlayerX() < 0x48) {
            SetStep(CTULHU_HOP);
        }

        if (!--self->ext.ctulhu.timer) {
            SetStep(CTULHU_FLY);
        }
        break;
    case CTULHU_FLY:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_fly_from_ground, self)) {
                self->ext.ctulhu.y =
                    self->posY.i.hi + g_Tilemap.scrollY.i.hi - 0x20;
                SetSubStep(1);
            }
            break;
        case 1:
            self->velocityX = 0;
            self->velocityY = FIX(-4);
            self->animCurFrame = 0x15;
            self->step_s++;
            // fallthrough
        case 2:
            MoveEntity();
            self->velocityY += FIX(3.0 / 16);
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            posY -= self->ext.ctulhu.y;
            if (posY <= 0 || self->velocityY > 0) {
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(anim_wing_flap, self);
            if (!self->animFrameDuration && self->animFrameIdx == 3) {
                PlaySfxPositional(SFX_WING_FLAP_A);
            }
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            posY -= self->ext.ctulhu.y;
            if (posY == 0) {
                self->ext.ctulhu.timer = 0x80;
                self->velocityY = 0;
                self->step_s++;
            } else if (posY < 0) {
                self->posY.i.hi++;
            } else {
                self->posY.i.hi--;
            }
            break;
        case 4:
            // Fly horizontally for a period
            AnimateEntity(anim_wing_flap, self);
            if (!self->animFrameDuration && self->animFrameIdx == 3) {
                PlaySfxPositional(SFX_WING_FLAP_A);
            }
            colRet = UnkCollisionFunc2(sensors_unk);
            if (colRet & 0x80) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft) {
                self->velocityX = FIX(0.75);
            } else {
                self->velocityX = FIX(-0.75);
            }

            if (!self->ext.ctulhu.timer) {
                if (colRet == 1) {
                    SetSubStep(5);
                }
            } else {
                self->ext.ctulhu.timer--;
            }
            break;
        case 5:
            // Land again
            self->animCurFrame = 6;
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                PlaySfxPositional(SFX_EXPLODE_B);
                SetSubStep(6);
            }
            break;
        case 6:
            if (!AnimateEntity(anim_land, self)) {
                SetStep(CTULHU_IDLE);
            }
            break;
        }
        break;
    case CTULHU_HOP:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->velocityY = FIX(-4);
            self->animCurFrame = 0x15;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(3.0 / 16);
            if (self->velocityY > 0) {
                self->step_s++;
                if (!self->ext.ctulhu.hopCount) {
                    self->ext.ctulhu.hopCount = 2;
                    SetStep(CTULHU_SINGLE_FIREBALL);
                } else {
                    self->ext.ctulhu.hopCount--;
                }
            }
            break;
        case 2:
            self->animCurFrame = 6;
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                PlaySfxPositional(SFX_EXPLODE_B);
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(anim_land, self)) {
                if (GetDistanceToPlayerX() > 0x40) {
                    self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                }
                SetSubStep(0);

                // When Ctulhu has done a hop after shooting a single fireball,
                // shoot a triple
                if (self->ext.ctulhu.hopCount == 1) {
                    SetStep(CTULHU_TRIPLE_FIREBALL);
                    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;

                    // If Ctulhu has chased the player far enough, or fired
                    // enough triple fireballs, it can fire an ice shockwave
                    if (posX > 0x400) {
                        self->facingLeft = 1;
                        self->ext.ctulhu.tripleFireballCount = 3;
                    }
                    if (++self->ext.ctulhu.tripleFireballCount > 2) {
                        self->ext.ctulhu.tripleFireballCount = 0;
                        SetStep(CTULHU_ICE_SHOCKWAVE);
                    }
                } else {
                    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                    if (self->facingLeft) {
                        if (posX > g_Tilemap.width - 0x80) {
                            self->facingLeft = 0;
                        }
                    } else if (posX < g_Tilemap.x + 0x80) {
                        self->facingLeft = 1;
                    }
                }
            }
        }
        break;
    case CTULHU_SINGLE_FIREBALL:
        if (!AnimateEntity(anim_shoot_single_fireball, self)) {
            SetStep(CTULHU_HOP);
            self->step_s = 2;
        }

        if (self->animFrameIdx == 8 && !self->animFrameDuration) {
            newEntity = &PLAYER;
            posX = newEntity->posX.i.hi - self->posX.i.hi;
            posY = newEntity->posY.i.hi - self->posY.i.hi;
            if (!self->facingLeft) {
                posX = -posX;
            }
            angle = ratan2(-posY, posX);
            if (angle > 0x280) {
                angle = 0x280;
            }
            if (angle < -0x280) {
                angle = -0x280;
            }
            if (GetDistanceToPlayerY() < 0x60) {
                PlaySfxPositional(SFX_FM_EXPLODE_SWISHES);
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_CTULHU_FIREBALL, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        newEntity->posX.i.hi += 0x10;
                    } else {
                        newEntity->posX.i.hi -= 0x10;
                    }
                    newEntity->posY.i.hi -= 0x16;
                    newEntity->rotZ = angle;
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
        }
        break;
    case CTULHU_TRIPLE_FIREBALL:
        if (!AnimateEntity(anim_shoot_triple_fireball, self)) {
            SetStep(CTULHU_HOP);
        }
        if (GetDistanceToPlayerY() < 0x60 && self->animCurFrame == 0x24 &&
            !self->animFrameDuration) {
            PlaySfxPositional(SFX_FM_EXPLODE_SWISHES);
            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_CTULHU_FIREBALL, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        newEntity->posX.i.hi += 0x10;
                    } else {
                        newEntity->posX.i.hi -= 0x10;
                    }
                    newEntity->posY.i.hi -= 0x14;
                    newEntity->rotZ = triple_fireball_rot_z[i];
                }
            }
        }
        break;
    case CTULHU_ICE_SHOCKWAVE:
        if (!AnimateEntity(anim_shockwave_throw, self)) {
            SetStep(CTULHU_IDLE);
        }

        if (GetDistanceToPlayerY() < 0x60 && self->animFrameIdx == 0x9 &&
            !self->animFrameDuration) {
            // Don't think SFX can overlap so this laugh never plays?
            PlaySfxPositional(SFX_CTULHU_LAUGH);
            PlaySfxPositional(SFX_FM_THUNDER_EXPLODE);
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_CTULHU_ICE_SHOCKWAVE, self, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->zPriority = self->zPriority + 1;

                if (self->facingLeft) {
                    newEntity->posX.i.hi += 0x20;
                } else {
                    newEntity->posX.i.hi -= 0x20;
                }

                // Possible bug?
#ifdef VERSION_PSP
                1;
#else
                newEntity->posY.i.hi = newEntity->posY.i.hi;
#endif
            }
        }
        break;
    case CTULHU_PLAYER_DEAD:
        switch (self->step_s) {
        case 0:
            // Once Ctulhu is on the group begin laughing SFX
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                PlaySfxPositional(SFX_CTULHU_LAUGH);
                self->step_s++;
            }
            break;
        case 1:
            if (!AnimateEntity(anim_player_death_laugh, self)) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(0x759);
            }
            AnimateEntity(anim_laugh_static, self);
            // If player is revived, return back to standard action
            if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
                SetStep(CTULHU_IDLE);
            }
        }
        break;
    case CTULHU_DEATH:
        switch (self->step_s) {
        case 0:
            if (self->animCurFrame > 8 && self->animCurFrame < 19) {
                self->animCurFrame = 0x14;
            }
            primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 8);
            if (primIndex == -1) {
                self->step_s = 0;
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            dr_env = g_api.AllocateDrawEnvironment((POLY_GT4*)prim);
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
                posY = 0x180;
            } else {
                posY = 0x100;
            }

            clipRect.x = 0;
            clipRect.y = posY;
            clipRect.w = 0x80;
            clipRect.h = 0x80;
            drawEnv.clip = clipRect;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &drawEnv);
            prim = prim->next;

            if (g_api.AllocateDrawEnvironment((POLY_GT4*)prim) == NULL) {
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

            self->ext.ctulhu.deathExplosionPrim = prim;
            if (self->params) {
                posY = 0xFF;
            } else {
                posY = 0x7F;
            }

            prim->type = PRIM_GT4;
            prim->tpage = 0x110;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x3F;
            prim->v0 = prim->v1 = posY - 0x70;
            prim->v2 = prim->v3 = posY;
            prim->x0 = prim->x2 = self->posX.i.hi - 0x20;
            prim->x1 = prim->x3 = prim->x0 + 0x40;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x28;
            prim->y0 = prim->y1 = prim->y2 - 0x70;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
            prim->type = PRIM_TILE;
            if (self->params) {
                posY = 0x80;
            } else {
                posY = 0;
            }
            prim->x0 = 0;
            prim->y0 = posY;
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
                posY = 0x100;
            } else {
                posY = 0x80;
            }

            self->posX.i.hi = 0x20;
            self->posY.i.hi = posY - 0x28;

            self->palette = g_EInitCtulhu[3];
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
            self->step_s++;
            break;
        case 1:
            self->animCurFrame = 0;
            prim = self->ext.prim;
            prim->type = PRIM_ENV;

            dr_env = (DR_ENV*)LOW(prim->r1);
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 0;
            drawEnv.dtd = 0;

            if (self->params) {
                posY = 0x180;
            } else {
                posY = 0x100;
            }

            clipRect.x = 0;
            clipRect.y = posY;
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
            prim = prim->next;

            self->ext.ctulhu.y = 0x28;
            self->ext.ctulhu.timer = 0x10;
            self->step_s++;
            // fallthrough
        case 2:
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_FM_EXPLODE_B);
            }
            prim = self->ext.ctulhu.deathExplosionPrim;
            posX = Random() & 0x3F;
            posY = self->ext.ctulhu.y;
            if (!(g_Timer & 0xF)) {
                newEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                        &g_Entities[TOTAL_ENTITY_COUNT]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
                    newEntity->posX.i.hi = prim->x0 + posX;
#ifdef VERSION_PSP
                    newEntity->posY.i.hi = prim->y2 - 0x30 + posY;
#else
                    newEntity->posY.i.hi = prim->y2 + posY - 0x30;
#endif
                    newEntity->params = 3;
                }
            }
            newEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                    &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_CTULHU_DEATH, newEntity);
                newEntity->posX.i.hi = self->posX.i.hi - 0x20 + posX;
                newEntity->posY.i.hi = self->posY.i.hi + posY + 4;
                newEntity->facingLeft = colRet;
                newEntity->params = 1;
                newEntity->zPriority = 0x10;
                if (self->params) {
                    newEntity->zPriority += 4;
                }
            }
            if (!--self->ext.ctulhu.timer) {
                self->ext.ctulhu.timer = 2;
                self->ext.ctulhu.y -= 2;
                if (self->ext.ctulhu.y < -0x28) {
                    self->ext.ctulhu.timer = 0x40;
                    self->step_s++;
                }
            }
            break;
        case 3:
            if (!--self->ext.ctulhu.timer) {
                DestroyEntity(self);
                return;
            }
        }
        break;
    case CTULHU_DEBUG:
#include "../pad2_anim_debug.h"
    }
    if (self->animCurFrame >= 11 && self->animCurFrame < 15) {
        LOH(self->hitboxOffX) = -0x12;
        LOH(self->hitboxOffY) = 0x11;
        self->hitboxWidth = 0x16;
        self->hitboxHeight = 0x16;
    } else {
        LOH(self->hitboxOffX) = -1;
        LOH(self->hitboxOffY) = 1;
        self->hitboxWidth = 0x13;
        self->hitboxHeight = 0x26;
    }
}

void EntityCtulhuFireball(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    s32 primIndex;
    s16 rotZ;

    if (!self->step) {
        InitializeEntity(g_EInitCtulhuFireball);
        self->drawFlags = FLAG_DRAW_ROTZ;
        rotZ = self->rotZ;
        if (self->facingLeft) {
            rotZ = -rotZ;
        } else {
            rotZ = rotZ + 0x800;
        }
        self->velocityX = rcos(rotZ) * 48;
        self->velocityY = rsin(rotZ) * 48;

        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        prim->tpage = 20;
        prim->clut = g_EInitCtulhuFireball[3] + 1;
        prim->u0 = prim->u2 = 224;
        prim->u1 = prim->u3 = 255;
        prim->v0 = prim->v1 = 48;
        prim->v2 = prim->v3 = 79;
        prim->priority = self->zPriority - 1;
        prim->drawMode =
            DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
    }

    AnimateEntity(anim_fireball, self);
    MoveEntity();
    prim = self->ext.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 24;
    prim->x1 = prim->x3 = self->posX.i.hi + 24;
    prim->y0 = prim->y1 = self->posY.i.hi - 24;
    prim->y2 = prim->y3 = self->posY.i.hi + 24;

    if (g_Timer & 1) {
        prim->drawMode =
            DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
    } else {
        prim->drawMode = DRAW_HIDE;
    }

    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, self, newEntity);
            newEntity->params = 2;
        }
        DestroyEntity(self);
    }
}

void EntityCtulhuIceShockwave(Entity* self) {
    Primitive* prim;
    s16* ptr;
    s32 primIndex;
    s32 v2;

    if (g_Timer & 1) {
        self->palette = g_EInitCtulhuIceShockwave[3];
    } else {
        self->palette = g_EInitCtulhuIceShockwave[3] + 1;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCtulhuIceShockwave);
        self->animCurFrame = 44;
        self->hitboxOffX = 7;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTY;
        self->rotY = 256;
        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 128);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        while (prim != NULL) {
            prim->p3 = 0;
            prim->priority = self->zPriority - 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        // Fallthrough
    case 1:
        if (self->facingLeft) {
            self->velocityX = FIX(4.0);
        } else {
            self->velocityX = FIX(-4.0);
        }
        MoveEntity();

        if (g_Timer & 1) {
            self->rotY = 264;
        } else {
            self->rotY = 248;
        }

        if (self->ext.ctulhu.shockwavePrim == NULL) {
            prim = self->ext.prim;
            prim = FindFirstUnkPrim(prim);
            self->ext.ctulhu.shockwavePrim = prim;

            if (prim != NULL) {
                prim->p3 = 8;
                prim->tpage = 26;
                prim->clut = 0x1F5;
                prim->u0 = prim->u2 = 4;
                prim->u1 = prim->u3 = 28;
                prim->v0 = prim->v1 = prim->v2 = prim->v3 = 96;
                PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) =
                    PGREY(prim, 3) = 128;
                prim->x0 = prim->x2 = prim->x1 = prim->x3 = self->posX.i.hi;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    self->posY.i.hi + 40;
                prim->priority = self->zPriority - 1;
                prim->drawMode =
                    DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            }
        }

        if (self->ext.ctulhu.shockwavePrim != NULL) {
            prim = self->ext.ctulhu.shockwavePrim;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = (prim->y1 -= 12);
            v2 = prim->v2;
            v2 += 4;
            if (v2 > 120) {
                v2 = 120;
                prim->p3 = 2;
                self->ext.ctulhu.shockwavePrim = NULL;
            }
            prim->v2 = prim->v3 = v2;
        }

        if (!self->ext.ctulhu.timer) {
            self->ext.ctulhu.timer = 2;
            prim = self->ext.prim;
            prim = FindFirstUnkPrim(prim);
            if (prim != NULL) {
                prim->p3 = 4;
                prim->p1 = 0;
                prim->p2 = 0;
                prim->tpage = 23;
                prim->clut = 0x234;
                PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) =
                    PGREY(prim, 3) = 96;
                prim->x0 = prim->x2 = self->posX.i.hi + 16;
                prim->x1 = prim->x3 = self->posX.i.hi - 16;
                prim->y0 = prim->y1 = self->posY.i.hi - 24;
                prim->y2 = prim->y3 = self->posY.i.hi + 48;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
            }
        } else {
            self->ext.ctulhu.timer -= 1;
        }

        if (self->flags & FLAG_DEAD) {
            self->drawFlags |= FLAG_DRAW_UNK8;
            self->unk6C = 128;
            self->hitboxState = 0;
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->unk6C -= 8;
        self->rotY += 24;
        self->velocityX -= self->velocityX / 8;

        if (g_Timer & 1) {
            self->animCurFrame = 0;
        } else {
            self->animCurFrame = 44;
        }

        if (!self->unk6C) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = self->ext.prim;
    while (prim != NULL) {
        if (!(prim->drawMode & DRAW_HIDE)) {
            if (prim->p3 == 2) {
                PrimDecreaseBrightness(prim, 5);

                if (g_Timer & 1) {
                    prim->u0 = prim->u2 = 4;
                    prim->u1 = prim->u3 = 28;
                } else {
                    prim->u0 = prim->u2 = 28;
                    prim->u1 = prim->u3 = 4;
                }

                prim->y0 = (prim->y1 += 3);
                prim->v2 = (prim->v3 -= 1);

                prim->x2 -= (F(self->velocityX).i.hi) >> 1;
                prim->x3 += (F(self->velocityX).i.hi) >> 1;
                if (prim->x0 != prim->x2) {
                    prim->x0 = prim->x2;
                    prim->x1 = prim->x3;
                } else {
                    prim->x0 = prim->x2 + 4;
                    prim->x1 = prim->x3 + 4;
                }

                if (prim->y0 > prim->y2 || prim->v2 < prim->v0) {
                    prim->p3 = 0;
                    prim->drawMode = DRAW_HIDE;
                }
            }

            if (prim->p3 == 4) {
                PrimDecreaseBrightness(prim, 4);
                if (prim->y2 - prim->y0 > 32) {
                    prim->y0 = (prim->y1 += 2);
                }
                if (!prim->p2) {
                    prim->p1++;
                    if (prim->p1 > 13) {
                        prim->p3 = 0;
                        prim->drawMode = DRAW_HIDE;
                    }
#ifdef VERSION_PSP
                    // Looks to be a bug fix on PSP
                    // PSX can index outside size of ctulhu_shockwave_uvs
                    else {
#endif
                        ptr = ctulhu_shockwave_uvs[prim->p1];
                        ptr += 8;
                        prim->u0 = prim->u2 = *ptr++;
                        prim->v0 = prim->v1 = *ptr++;
                        prim->u1 = prim->u3 = *ptr++;
                        prim->v2 = prim->v3 = *ptr++;
                        prim->p2 = 3;
#ifdef VERSION_PSP
                    }
#endif
                } else {
                    prim->p2 -= 1;
                }
            }
        }
        prim = prim->next;
    }

    if (self->velocityX > 0) {
        if (self->posX.i.hi > 384) {
            DestroyEntity(self);
        }
    } else if (self->posX.i.hi < -128) {
        DestroyEntity(self);
    }
}

void EntityCtulhuDeath(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 14;
        self->unk5A = 121;
        self->palette = PAL_OVL(0x2CE);
        self->drawFlags = FLAG_DRAW_UNK8;
        self->unk6C = 16;
        if (self->params) {
            self->unk6C = 16;
            self->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        } else {
            self->zPriority += 2;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
        // fallthrough
    case 1:
        self->posY.val += 0xFFFF0000;
        if (!AnimateEntity(anim_death, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
