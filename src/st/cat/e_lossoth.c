// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

static u8 anim_walk[] = {0x0D, 0x01, 0x10, 0x02, 0x0D, 0x03, 0x10, 0x02, 0x00};
static u8 anim_throw_fireballs[] = {
    0x08, 0x04, 0x07, 0x05, 0x03, 0x06, 0x03, 0x07, 0x06,
    0x08, 0x05, 0x09, 0x04, 0x0A, 0x32, 0x03, 0xFF, 0x00};
static u8 anim_napalm_flare[] = {
    0x06, 0x0B, 0x04, 0x0C, 0x03, 0x0D, 0x06, 0x0E, 0x06,
    0x0F, 0x04, 0x10, 0x04, 0x11, 0x32, 0x03, 0xFF, 0x00};
static u8 anim_fireball_collide_burst[] = {
    0x04, 0x12, 0x03, 0x13, 0x02, 0x14, 0x02, 0x15, 0xFF, 0x00};
static u8 anim_death_walk[] = {
    0x11, 0x18, 0x14, 0x17, 0x11, 0x16, 0x14, 0x17, 0x00, 0x00};
static u8 anim_death_jacket_flames[] = {
    0x07, 0x19, 0x07, 0x1A, 0x07, 0x1B, 0x00, 0x00};
static u8 anim_lantern_smash[] = {
    0x05, 0x1C, 0x06, 0x1D, 0x07, 0x1E, 0x02, 0x1F,
    0x05, 0x20, 0x05, 0x21, 0x08, 0x22, 0xFF, 0x00};
static u8 anim_death_drop_knees[] = {0x0A, 0x26, 0x06, 0x23, 0x04, 0x24, 0x03,
                                     0x23, 0x03, 0x25, 0x41, 0x23, 0xFF, 0x00};
static u8 anim_lantern_glow[] = {
    0x02, 0x27, 0x02, 0x28, 0x02, 0x29, 0x02, 0x28, 0x00};

static s16 sensors_wall[] = {0, 18, 12, 0};
// nb. this resides in BSS on PSP
static s16 sensors_empty[] = {0, 0, 0, 0};
static s16 lossoth_sensors_ground[] = {0, 18, 0, 4, 12, -4, -24, 0};
static s16 lantern_sensors_ground[] = {0, 4, 0, 4, 4, -4, -8, 0};
static Point16 fireball_positions[3] = {
    {.x = 32, .y = 0}, {.x = 20, .y = -20}, {.x = 0, .y = -28}};
static Point32 fireball_velocities[3] = {{.x = FIX(1.375), .y = FIX(-2.5)},
                                         {.x = FIX(2), .y = FIX(-3.0)},
                                         {.x = FIX(2.5), .y = FIX(-4.0)}};
// Random intervals to walk towards player when aggro'd
static s16 walk_timers[] = {32, 64, 80, 96};
static Point16 death_jacket_flame_positions[3] = {
    {.x = 4, .y = -16}, {.x = -10, .y = -2}, {.x = 2, .y = 4}};

static void DrawNapalmEffect(Primitive* prim) {
    s32 primY;

    switch (prim->p3) {
    case 1:
        prim->v0 = prim->v1 = 0x58;
        prim->v2 = prim->v3 = 0x58;
        PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) =
            0x80;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        if (g_CurrentEntity->facingLeft) {
            prim->x0 -= 4;
            prim->x1 -= 4;
        } else {
            prim->x0 += 4;
            prim->x1 += 4;
        }
        prim->p3++;
        // fallthrough
    case 2:
        primY = prim->y2 - prim->y0;
        primY = (0x24 - primY) / 2;
        if (primY < 2) {
            primY = 2;
        }
        prim->y0 = prim->y1 -= primY;
        prim->v2 = prim->v3 += primY;
        prim->x3 = g_CurrentEntity->posX.i.hi;
        if (prim->v2 >= 0x7C) {
            prim->drawMode |= DRAW_COLORS;
            if (g_CurrentEntity->facingLeft) {
                prim->x3 = prim->x2 + 0x10;
            } else {
                prim->x3 = prim->x2 - 0x10;
            }
            prim->v2 = prim->v3 = 0x7C;
            prim->p3++;
        }
        break;
    case 3:
        prim->y0 = ++prim->y1;
        primY = prim->y2 - prim->y0;
        if (primY < 0x10) {
            prim->p3 = 4;
        }
        break;
    case 4:
        if (g_CurrentEntity->facingLeft) {
            prim->x1--;
            prim->x3--;
        } else {
            prim->x1++;
            prim->x3++;
        }
        if (!PrimDecreaseBrightness(prim, 7)) {
            prim->p3 = 0;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        }
        break;
    }
}

extern EInit g_EInitLossoth;
void EntityLossoth(Entity* self) {
    Entity* newEntity;
    s32 i;
    u32 var_s2;

    typedef enum Step {
        INIT = 0,
        DROP_TO_GROUND = 1,
        IDLE_WALK = 2,
        PLAYER_AGGRO = 3,
        ATTACK_FIREBALLS = 4,
        ATTACK_NAPALM_FLARE = 5,
        DEATH = 8
    };

    if ((self->flags & FLAG_DEAD) && self->step < 8) {
        PlaySfxPositional(SFX_LOSSOTH_DEATH);
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitLossoth);
        self->animCurFrame = 1;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;

        // Handles lantern glow effect and some death flame out visuals
        newEntity = self + 1;
        CreateEntityFromEntity(E_LOSSOTH_EFFECTS, self, newEntity);
        newEntity->zPriority = self->zPriority + 1;

        newEntity = self + 2;
        CreateEntityFromEntity(E_UNK_43, self, newEntity);
        newEntity->params = 1;
        newEntity->ext.lossoth.unk9C = self;
        // fallthrough
    case DROP_TO_GROUND:
        if (UnkCollisionFunc3(lossoth_sensors_ground) & 1) {
            SetStep(IDLE_WALK);
        }
        break;
    case IDLE_WALK:
        if (!self->step_s) {
            self->ext.lossoth.timer = 0x40;
            self->step_s++;
        }
        AnimateEntity(anim_walk, self);
        UnkCollisionFunc2(sensors_wall);

        if (self->facingLeft) {
            self->velocityX = FIX(0.25);
        } else {
            self->velocityX = FIX(-0.25);
        }

        // When walk timer expires change direction and walk the other way
        if (!--self->ext.lossoth.timer) {
            self->facingLeft ^= 1;
            self->ext.lossoth.timer = 0x40;
        }

        // If player is close and we're looking at them, start aggro routine
        if (GetDistanceToPlayerX() < 0x60 &&
            ((GetSideToPlayer() & 1) ^ self->facingLeft)) {
            SetStep(PLAYER_AGGRO);
        }

        break;
    case PLAYER_AGGRO:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.lossoth.timer = walk_timers[Random() & 3];
            self->step_s++;
        }

        if (!AnimateEntity(anim_walk, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        var_s2 = UnkCollisionFunc2(sensors_wall);
        if (var_s2 & 0x80) {
            self->ext.lossoth.timer = 1;
        }

        // Speed up and move towards player
        if (self->facingLeft) {
            self->velocityX = FIX(0.4375);
        } else {
            self->velocityX = FIX(-0.4375);
        }

        if (!--self->ext.lossoth.timer) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;

            if (Random() & 1) {
                SetStep(ATTACK_NAPALM_FLARE);
            } else {
                SetStep(ATTACK_FIREBALLS);
            }

            if (var_s2 & 0x80) {
                SetStep(ATTACK_FIREBALLS);
            }
        }

        // If player has moved far enough away, end aggro
        if (GetDistanceToPlayerX() > 0xC0) {
            SetStep(IDLE_WALK);
        }

        break;
    case ATTACK_FIREBALLS:
        if (!AnimateEntity(anim_throw_fireballs, self)) {
            SetStep(PLAYER_AGGRO);
        }

        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(SFX_FIRE_SHOT);

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_LOSSOTH_FIREBALL, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->params = i;
                    if (self->facingLeft) {
                        newEntity->posX.i.hi += fireball_positions[i].x;
                    } else {
                        newEntity->posX.i.hi -= fireball_positions[i].x;
                    }
                    newEntity->posY.i.hi += fireball_positions[i].y;
                }
            }
        }
        break;
    case ATTACK_NAPALM_FLARE:
        if (!AnimateEntity(anim_napalm_flare, self)) {
            SetStep(PLAYER_AGGRO);
        }

        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(SFX_LOSSOTH_NAPALM_GRUNT);
            PlaySfxPositional(SFX_FIREBALL_SHOT_A);
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_LOSSOTH_NAPALM, self, newEntity);
                newEntity->facingLeft = self->facingLeft;
                if (self->facingLeft) {
                    newEntity->posX.i.hi += 8;
                } else {
                    newEntity->posX.i.hi -= 8;
                }
                newEntity->posY.i.hi += 18;
            }
        }
        break;
    case DEATH:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0x2E;
            self->hitboxState = 0;
            self->drawFlags |= FLAG_DRAW_OPACITY;
            self->opacity = 0x80;

            // Spawn three flames on the dying Lossoth's jacket
            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_LOSSOTH_FLAMES, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->ext.lossoth.lossothEntity = self;
                    if (i == 0) {
                        newEntity->zPriority = self->zPriority - 4;
                    } else {
                        newEntity->zPriority = self->zPriority + 4;
                    }
                    newEntity->params = i + 2;
                }
            }
            SetSubStep(1);
            break;
        case 1:
            if (!self->opacity) {
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->animCurFrame = 0x18;
                self->ext.lossoth.timer = 0;
                SetSubStep(2);
            }
            break;
        case 2:
            // On fire, wander back and forth for a bit
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
            }
            var_s2 = AnimateEntity(anim_death_walk, self);
            if (!self->poseTimer && self->pose == 2) {
                self->ext.lossoth.timer++;
            }
            UnkCollisionFunc2(sensors_wall);

            if (self->facingLeft ^ self->ext.lossoth.timer) {
                self->velocityX = FIX(0.25);
            } else {
                self->velocityX = FIX(-0.25);
            }

            if (!var_s2) {
                self->ext.lossoth.timer++;
                if (self->ext.lossoth.timer > 1) {
                    SetSubStep(3);
                }
            }

            if (!(g_Timer & 3)) {
                self->palette++;
                if (self->palette > PAL_DRA(0x21A)) {
                    self->palette = PAL_DRA(0x216);
                }
            }
            break;
        case 3:
            // Drop to knees and explode
            if (!AnimateEntity(anim_death_drop_knees, self)) {
                PlaySfxPositional(SFX_EXPLODE_A);
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                    newEntity->params = 2;
                    if (self->facingLeft) {
                        newEntity->posX.i.hi += 6;
                    } else {
                        newEntity->posX.i.hi -= 6;
                    }
                }
                self->ext.lossoth.timer = 0x10;
                self->step_s++;
            }

            if (!(g_Timer & 3)) {
                self->palette++;
                if (self->palette > PAL_DRA(0x21A)) {
                    self->palette = PAL_DRA(0x216);
                }
            }
            break;
        case 4:
            if (!--self->ext.lossoth.timer) {
                DestroyEntity(self);
                return;
            }

            if (!(g_Timer & 3)) {
                self->palette++;
                if (self->palette > PAL_DRA(0x21A)) {
                    self->palette = PAL_DRA(0x216);
                }
            }
            break;
        }
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
}

extern EInit g_EInitLossothEffects;
void EntityLossothEffects(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    Entity* entity;
    s32 posX;
    s32 i;
    s32 var_s4;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLossothEffects);
        self->hitboxState = 0;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        // fallthrough
    case 1:
        // Walk state, move lantern glow in step with Lossoth
        AnimateEntity(anim_lantern_glow, self);

        // self - 1 is the main Lossoth entity
        entity = self - 1;
        self->facingLeft = entity->facingLeft;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        if (entity->facingLeft) {
            self->posX.i.hi += 7;
        } else {
            self->posX.i.hi -= 7;
        }
        self->posY.i.hi += 6;
        if (entity->flags & FLAG_DEAD) {
            SetStep(2);
        }
        break;
    case 2:
        // Lossoth is dying
        switch (self->step_s) {
        case 0:
            // Drop lantern on ground
            self->animCurFrame = 0x1C;
            self->drawMode = DRAW_DEFAULT;
            if (self->facingLeft) {
                self->velocityX = FIX(-0.75);
            } else {
                self->velocityX = FIX(0.75);
            }
            self->step_s++;
            // fallthrough
        case 1:
            if (UnkCollisionFunc3(lantern_sensors_ground) & 1) {
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(anim_lantern_smash, self)) {
                self->drawFlags |= FLAG_DRAW_SCALEX;
                self->scaleX = 0x100;
                self->step_s++;
            }
            break;
        case 3:
            self->scaleX += 0x28;
            if (self->scaleX > 0x280) {
                self->step_s++;
            }
            break;
        case 4:
            // Flare up vertical death flames
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.lossoth.prim = prim;

            posX = self->posX.i.hi - 0x10;
            posY = self->posY.i.hi + 4;

            while (prim != NULL) {
                prim->tpage = 0x14;
                prim->clut = PAL_DRA(0x21F);
                prim->u0 = prim->u2 = 0xD4;
                prim->u1 = prim->u3 = 0xD6;
                prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0x50;
                prim->x0 = prim->x2 = posX;
                posX += 2;
                prim->x1 = prim->x3 = posX;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 = posY;
                PGREY(prim, 0) = 0x80;
                LOW(prim->r1) = LOW(prim->r2) = LOW(prim->r3) = LOW(prim->r0);
                prim->priority = self->zPriority + 1;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }

            self->animCurFrame = 0;
            self->step_s++;
            // fallthrough
        case 5:
            self->animCurFrame = 0x2E;
            self->palette = PAL_FLAG(0x21A);
            self->opacity = 0;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
            self->drawFlags = FLAG_DRAW_OPACITY;

            // self - 1 is the main Lossoth entity
            entity = self - 1;
            self->posX.i.hi = entity->posX.i.hi;
            self->posY.i.hi = entity->posY.i.hi;
            self->facingLeft = entity->facingLeft;
            PlaySfxPositional(SFX_EXPLODE_SMALL);
            self->step_s++;
            // fallthrough
        case 6:
            prim = self->ext.lossoth.prim;
            var_s4 = 0;
            while (prim != NULL) {
                prim->y0 = prim->y1 -= 4;
                prim->v2 = prim->v3 += 2;
                if (prim->v2 >= 0x7C) {
                    prim->v2 = prim->v3 = 0x7C;
                    var_s4 = 1;
                    self->step_s = 7;
                }
                prim = prim->next;
            }
            // fallthrough
        case 7:
            if (self->step_s == 7) {
                var_s4 = 1;
            }
            prim = self->ext.lossoth.prim;
            while (prim != NULL) {
                if (Random() & 1) {
                    prim->y0 = prim->y1 += 4;
                } else {
                    prim->y0 = prim->y1 -= 4;
                }
                prim = prim->next;
            }
            self->opacity += 4;
            if (self->opacity > 0x80) {
                self->opacity = 0x80;
                self->animCurFrame = 0;
                if (var_s4) {
                    self->step_s = 8;
                }
            }

            // self - 1 is the main Lossoth entity
            entity = self - 1;
            entity->opacity = (0x80 - self->opacity);

            // Spawn rising embers on the main Lossoth entity
            for (i = 0; i < 2; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_LOSSOTH_FLAMES, self, entity);
                    entity->posY.i.hi += 0x10;
                    entity->posX.i.hi += (Random() & 0x1F) - 0x10;
                    entity->zPriority = self->zPriority + 2;
                    entity->params = 6;
                }
            }
            break;
        case 8:
            prim = self->ext.lossoth.prim;
            while (prim != NULL) {
                PrimDecreaseBrightness(prim, 7);
                prim = prim->next;
            }
            break;
        }
    }

    // self - 1 is the main Lossoth entity
    entity = self - 1;
    if (entity->entityId != E_LOSSOTH) {
        DestroyEntity(self);
    }
}

extern EInit g_EInitLossothAttack;
void EntityLossothFireball(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 params;
    s32 posX;
    s32 posY;

    if (self->hitParams || self->flags & FLAG_DEAD) {
        self->drawFlags = FLAG_DRAW_DEFAULT;
        self->pfnUpdate = EntityExplosion;
        self->step = 0;
        self->params = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLossothAttack);
        self->animCurFrame = 0x2B;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->rotate = Random() * 0x10;
        params = self->params;
        self->velocityX = fireball_velocities[params].x;
        self->velocityY = fireball_velocities[params].y;
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        self->rotate -= 0xC0;
        if (!(g_Timer & 3)) {
            // Spawn embers as the fireballs move
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_LOSSOTH_FLAMES, self, newEntity);
                newEntity->rotate = self->rotate;
            }
        }
        if (self->velocityX > 0) {
            posX = self->posX.i.hi + 8;
        } else {
            posX = self->posX.i.hi - 8;
        }
        posY = self->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->flags |= FLAG_DEAD;
        }

        if (self->velocityY != 0) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->posY.i.hi += collider.unk18;
                self->rotate = 0;
                SetStep(2);
            }

            if (collider.effects & EFFECT_UNK_8000) {
                self->flags |= FLAG_DEAD;
            }
        }
        break;
    case 2:
        // If firewall collides with a solid surface like floors or walls
        // play a burst animation
        if (!AnimateEntity(anim_fireball_collide_burst, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern Primitive* FindFirstUnkPrim(Primitive* poly);
void EntityLossothNapalmFlare(Entity* self) {
    Primitive* prim;
    Entity* newEntity;
    s32 primIndex;
    s32 var_s2;
    s32 paletteOffset;

    FntPrint("f_step %x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLossothAttack);
        self->animCurFrame = 0;
        self->hitboxWidth = 0xC;
        self->hitboxOffX = 0x10;
        self->hitboxHeight = 8;
        self->hitboxOffY = -8;
#ifdef VERSION_US
        self->hitboxState = 1;
#endif
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.lossoth.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0x14;
            prim->clut = PAL_DRA(0x21A);
            prim->u0 = prim->u2 = 0x80;
            prim->u1 = prim->u3 = 0x90;
            prim->v0 = prim->v1 = 0x58;
            prim->v2 = prim->v3 = 0x58;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            prim->p3 = 0;
            prim = prim->next;
        }

        if (self->facingLeft) {
            self->velocityX = FIX(2.0);
        } else {
            self->velocityX = FIX(-2.0);
        }

        self->ext.lossothNapalm.unk9C = self->ext.lossothNapalm.prim;
        self->ext.lossothNapalm.unkA0.val = 0;
        prim = self->ext.lossothNapalm.unk9C;
        prim->x0 = prim->x2 = self->posX.i.hi;
        prim->y0 = prim->y2 = self->posY.i.hi;
        break;
    case 1:
        var_s2 = UnkCollisionFunc2(sensors_empty);
        self->ext.lossothNapalm.unkA0.val -= abs(self->velocityX);
        if (var_s2 & 0x80) {
            self->ext.lossothNapalm.unkA0.val = 0;
            self->step++;
        }
        if (self->ext.lossothNapalm.unkA0.i.hi <= 0) {
            prim = self->ext.lossothNapalm.unk9C;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y1 = prim->y3 = self->posY.i.hi;
            prim->p3 = 1;

            prim = self->ext.lossothNapalm.prim;
            prim = FindFirstUnkPrim(prim);
            self->ext.lossothNapalm.unk9C = prim;
            if (prim == NULL) {
                DestroyEntity(self);
                return;
            }

            if (self->velocityX > 0) {
                prim->x0 = prim->x2 = self->posX.i.hi - 8;
            } else {
                prim->x0 = prim->x2 = self->posX.i.hi + 8;
            }
            prim->y0 = prim->y2 = self->posY.i.hi;
            self->ext.lossothNapalm.unkA0.val += (Random() << 8) + 0x80000;
        }

        if (!(g_Timer & 3)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_LOSSOTH_FLAMES, self, newEntity);
                newEntity->zPriority = self->zPriority + 2;
                newEntity->params = 1;
            }
        }
        break;
    case 2:
        self->hitboxState = 0;
        if (!self->ext.lossothNapalm.unkA5) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = self->ext.lossothNapalm.prim;
    var_s2 = 0;
    paletteOffset = self->ext.lossothNapalm.paletteOffset;
    while (prim != NULL) {
        prim->clut = paletteOffset + PAL_DRA(0x21A);
        if (prim->p3) {
            DrawNapalmEffect(prim);
            var_s2++;
        }
        paletteOffset++;
        if (paletteOffset > 4) {
            paletteOffset = 0;
        }
        prim = prim->next;
    }
    self->ext.lossothNapalm.unkA5 = var_s2;
    if (!(g_Timer & 3)) {
        self->ext.lossothNapalm.paletteOffset += 1;
        if (self->ext.lossothNapalm.paletteOffset > 4) {
            self->ext.lossothNapalm.paletteOffset = 0;
        }
    }
}

void EntityLossothFlames(Entity* self) {
    Entity* lossoth;
    s32 params;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLossoth);
#ifdef VERSION_US
        self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->hitboxState = 0;
#else
        self->flags |= FLAG_UNK_2000;
#endif

        switch (self->params) {
        // Fireball embers
        case 0:
            self->drawFlags |= FLAG_DRAW_ROTATE;
            self->animCurFrame = 0x2D;
            self->ext.lossoth.timer = 0x10;
            self->velocityX = rcos(self->rotate) * 0x10;
            self->velocityY = rsin(self->rotate) * 0x10;
            self->step = 1;
            break;
        // Napalm embers
        case 1:
            self->animCurFrame = 0x2D;
            self->ext.lossoth.timer = 0x20;
            self->velocityX = FIX(0);
            self->velocityY = FIX(-0.75);
            self->step = 1;
            break;
        // Death flame embers
        case 6:
            self->animCurFrame = 0x2D;
            self->ext.lossoth.timer = (Random() & 0x1F) + 0x10;
            self->velocityX = FIX(0);
            self->velocityY = FIX(-0.25) - (Random() << 8);
            self->step = 1;
            break;
        // 2,3,4 = Death flames on jacket
        default:
            self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleY = self->scaleX = 0;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
            self->ext.lossoth.timer = 0x40;
            self->step = 2;
            break;
        }
        break;
    case 1:
        // Standard embers
        MoveEntity();
        if (!--self->ext.lossoth.timer) {
            DestroyEntity(self);
        }
        break;
    case 2:
        // Death flames on jacket
        if (self->ext.lossoth.timer) {
            self->ext.lossoth.timer--;
            break;
        }

        self->scaleY = self->scaleX += 4;
        if (self->scaleX > 0x100) {
            self->drawFlags = FLAG_DRAW_DEFAULT;
        }

        AnimateEntity(anim_death_jacket_flames, self);
        params = self->params - 2;
        lossoth = self->ext.lossoth.lossothEntity;
        self->posX.i.hi = lossoth->posX.i.hi;
        self->posY.i.hi = lossoth->posY.i.hi;
        if (self->facingLeft) {
            self->posX.i.hi -= death_jacket_flame_positions[params].x;
        } else {
            self->posX.i.hi += death_jacket_flame_positions[params].x;
        }
        self->posY.i.hi += death_jacket_flame_positions[params].y;

        // When the lossoth is death walking, move the flames in step
        if (lossoth->animCurFrame > 0x22 && lossoth->animCurFrame < 0x26) {
            if (self->facingLeft) {
                self->posX.i.hi += 8;
            } else {
                self->posX.i.hi -= 8;
            }
            self->posY.i.hi += 4;
        }

        if (lossoth->entityId != E_LOSSOTH) {
            DestroyEntity(self);
        }
        break;
    }
}
