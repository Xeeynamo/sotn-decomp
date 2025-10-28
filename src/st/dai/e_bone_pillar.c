// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

enum BonePillarSteps {
    BONE_PILLAR_INIT,
    BONE_PILLAR_SPAWN_TOP,
    BONE_PILLAR_READY,
    BONE_PILLAR_ATTACK_LOOP,
    BONE_PILLAR_ATTACK,
    BONE_PILLAR_DEATH = 8,
    BONE_PILLAR_BOUNCE = 10,
    BONE_PILLAR_DEBUG = 255,
};

enum BonePillarSubSteps {
    BONE_PILLAR_BOUNCE_INIT,
    BONE_PILLAR_SKULL_BOUNCE,
};

enum SpikeBallSteps {
    BONE_PILLAR_BALL_INIT,
    BONE_PILLAR_BALL_LINK,
    BONE_PILLAR_BALL_BOUNCE,
    BONE_PILLAR_BALL_LAND,
    BONE_PILLAR_BALL_BOUNCE_INVINC,
};

enum FireBreathSteps {
    BONE_PILLAR_FIRE_INIT,
    BONE_PILLAR_FIRE_BREATH,
    BONE_PILLAR_FIRE_AFTERBURN,
    BONE_PILLAR_FIRE_EMBERS,
};

enum DeathPartsSteps {
    BONE_PILLAR_DEATH_INIT,
    BONE_PILLAR_DEATH_FADE,
    BONE_PILLAR_DEATH_PARTS,
    BONE_PILLAR_DEATH_EXPLODE,
};

static s16 sensors_bone_pillar[] = {0, 32, 0, 4, 4, -4, -8, 0};
static s16 unused[] = {0, 8, 0, 4, 2, -4, -4, 0, 0, 36, 0, 4, 2, -4, -4, 0};
static s16 sensors_spike_ball[] = {0, 14, 0, 0};
static s16 hitbox[] = {2, -15, 2, -17, -4, 10, -4, 9};
static s16 y_offset[] = {38, 38, 14, 10};
static s16 angles[] = {ROT(61.875), ROT(118.125), ROT(241.875), ROT(298.125)};
static AnimateEntityFrame anim_mouth_glow_bottom[] = {
    {48, 1}, {2, 2}, {2, 1}, {2, 2}, {2, 1}, {2, 2}, {2, 1}, {2, 2},  {2, 1},
    {2, 2},  {2, 3}, {2, 4}, {2, 5}, {5, 4}, {2, 6}, {2, 4}, {2, 6},  {2, 7},
    {2, 6},  {2, 7}, {2, 8}, {2, 7}, {2, 8}, {2, 7}, {2, 6}, {17, 4}, POSE_END};
static AnimateEntityFrame anim_mouth_glow_top[] = {
    {48, 9}, {2, 10}, {2, 9},  {2, 10},  {2, 9},  {2, 10}, {2, 9},
    {2, 10}, {2, 9},  {2, 10}, {2, 11},  {2, 12}, {2, 13}, {2, 14},
    {5, 13}, {2, 15}, {2, 16}, {2, 15},  {2, 16}, {2, 17}, {2, 16},
    {2, 17}, {2, 16}, {2, 15}, {17, 13}, POSE_END};
static AnimateEntityFrame anim_fire_breath[] = {
    {3, 1}, {3, 2}, {3, 3}, {3, 4},  {3, 5},  {3, 6},
    {3, 7}, {3, 8}, {3, 9}, {3, 10}, {3, 11}, POSE_END};
static s16 attack_intervals[] = {16, 32, 48, 64, 80, 64, 48, 32};

extern s16* sprites_dai_5[];

void EntityBonePillarSkull(Entity* self) {
    Collider collider;
    Entity* entity;
    s32 offsetX, offsetY;
    s32 i;
    s32 tempVar;
    s16 angle;
    s16* ptr;

    if ((self->flags & FLAG_DEAD) && (self->step < BONE_PILLAR_DEATH)) {
        SetStep(BONE_PILLAR_DEATH);
    }
    if (self->ext.bonePillar.bottomDead) {
        self->ext.bonePillar.bottomDead = false;
        SetStep(BONE_PILLAR_BOUNCE);
    }
    switch (self->step) {
    case BONE_PILLAR_INIT:
        InitializeEntity(g_EInitBonePillarSkull);
        self->palette = g_EInitBonePillarSkull[3] + 1;
        self->animCurFrame = 1;
        self->flags |= FLAG_UNK_20000000;
        if (self->params & 0xFF) {
            self->hitboxOffX = -1;
            self->hitboxOffY = -14;
            self->animCurFrame = 9;
            SetStep(BONE_PILLAR_READY);
            break;
        }
        self->hitboxOffX = -3;
        self->hitboxOffY = 13;
    case BONE_PILLAR_SPAWN_TOP:
        if (UnkCollisionFunc3(sensors_bone_pillar) & 1) {
            if (self->params & 0x100) {
                entity = self + 1;
                CreateEntityFromCurrentEntity(E_BONE_PILLAR_SPIKE_BALL, entity);
                entity->posX.i.hi = self->posX.i.hi + 8;
                entity->posY.i.hi = self->posY.i.hi - 8;
                self->params = NULL;
            } else {
                entity = self + 1;
                CreateEntityFromCurrentEntity(E_BONE_PILLAR_SKULL, entity);
                entity->params = 1;
                entity->posX.i.hi = self->posX.i.hi;
                entity->posY.i.hi = self->posY.i.hi;
            }
            SetStep(BONE_PILLAR_READY);
        }
        break;
    case BONE_PILLAR_READY:
        if (GetDistanceToPlayerX() < 112) {
            SetStep(BONE_PILLAR_ATTACK_LOOP);
        }
        break;
    case BONE_PILLAR_ATTACK_LOOP:
        if (!self->step_s) {
            self->ext.bonePillar.timer =
                attack_intervals[self->ext.bonePillar.attackIntervalIdx];
            self->ext.bonePillar.attackIntervalIdx++;
            self->ext.bonePillar.attackIntervalIdx &= 7;
            self->step_s++;
        }
        if (self->params) {
            self->animCurFrame = 9;
        } else {
            self->animCurFrame = 1;
        }
        if (self->params == ((GetSideToPlayer() & 1) ^ 1)) { // Player on right
            if (!--self->ext.bonePillar.timer) {
                SetStep(BONE_PILLAR_ATTACK);
            }
        }
        if (GetDistanceToPlayerX() > 128) {
            SetStep(
                BONE_PILLAR_ATTACK_LOOP); // resets self->step_s to 0 which
                                          // increments attack interval index
        }
        break;
    case BONE_PILLAR_ATTACK:
        if (g_Timer & 2) {
            self->palette = g_EInitBonePillarSkull[3];
        } else {
            self->palette = g_EInitBonePillarSkull[3] + 1;
        }
        if (self->params) {
            tempVar = AnimateEntity(anim_mouth_glow_top, self);
        } else {
            tempVar = AnimateEntity(anim_mouth_glow_bottom, self);
        }
        if (!tempVar) { // if attack animation is not playing then the attack is
                        // complete, return to attack loop
            self->palette = g_EInitBonePillarSkull[3] + 1;
            SetStep(BONE_PILLAR_ATTACK_LOOP);
        }
        if ((self->pose == 17) && (tempVar & 0x80)) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_BONE_PILLAR_FIRE, self, entity);
                entity->facingLeft = self->params;
                if (self->params) {
                    entity->posY.i.hi -= 14;
                } else {
                    entity->posY.i.hi += 8;
                }
            }
        }
        break;
    case BONE_PILLAR_DEATH:
        ptr = hitbox;
        tempVar = 0;
        if (!self->params) {
            ptr += 4;
            tempVar = 2;
        }
        for (i = 0; i < 2; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_BONE_PILLAR_PARTS, self, entity);
                entity->params = i + tempVar;
                entity->posX.i.hi += *ptr++;
                entity->posY.i.hi += *ptr++;
            }
        }
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = EXPLOSION_SMALL_MULTIPLE;
        }
        if (!self->params) {
            entity = self + 1;
            if (entity->entityId == E_BONE_PILLAR_SKULL ||
                entity->entityId == E_BONE_PILLAR_SPIKE_BALL) {
                entity->ext.bonePillar.bottomDead = true;
            }
        }
        PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
        DestroyEntity(self);
        break;
    case BONE_PILLAR_BOUNCE:
        switch (self->step_s) {
        case BONE_PILLAR_BOUNCE_INIT:
            self->animCurFrame = 24;
            self->hitboxOffX = 0;
            self->hitboxOffY = 0;
            self->drawFlags |= FLAG_DRAW_ROTATE;
            self->velocityX = FIX(-0.75);
            self->velocityY = FIX(-1.0);
            self->flags &= ~FLAG_UNK_20000000;
            self->flags |= FLAG_UNK_02000000;
            self->step_s++;
        case BONE_PILLAR_SKULL_BOUNCE:
            self->rotate -= ROT(2.8125);
            MoveEntity();
            self->velocityY += FIX(0.1875);
            for (ptr = angles, i = 0; i < 4; i++, ptr++) {
                offsetX = self->posX.i.hi;
                offsetY = self->posY.i.hi;
                angle = self->rotate + *ptr;
                offsetX += ((rcos(angle) * 14) >> 12);
                offsetY += ((rsin(angle) * 14) >> 12);
                g_api.CheckCollision(offsetX, offsetY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    PlaySfxPositional(SFX_SKULL_KNOCK_B);
                    self->posY.i.hi += collider.unk18;
                    self->velocityY = -self->velocityY;
                    self->velocityY -= self->velocityY / 2;
                    break;
                }
            }
            if (self->flags & FLAG_DEAD) {
                PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
                self->hitboxState = 0;
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->step = BONE_PILLAR_INIT;
                self->pfnUpdate = EntityExplosion;
                self->params = EXPLOSION_FIREBALL;
            }
        }
        break;
    case BONE_PILLAR_DEBUG:
#include "../pad2_anim_debug.h"
    }
}

void EntityBonePillarSpikeBall(Entity* self) {
    Collider collider;
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s32 posX, posY;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = EXPLOSION_BIG;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case BONE_PILLAR_BALL_INIT:
        InitializeEntity(g_EInitBonePillarSpikeBall);
        self->animCurFrame = 22;
        self->hitboxWidth = 13;
        self->hitboxHeight = 13;
        self->flags |= FLAG_UNK_02000000;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        prim->tpage = self->unk5A / 4;
        if (self->unk5A & 1) {
            posX = 128;
        } else {
            posX = 0;
        }
        if (self->unk5A & 2) {
            posY = 128;
        } else {
            posY = 0;
        }
        prim->clut = g_EInitBonePillarSpikeBall[3] + 2;
        prim->u0 = prim->u2 = posX + 80;
        prim->u1 = prim->u3 = posX + 112;
        prim->v0 = prim->v1 = posY + 48;
        prim->v2 = prim->v3 = posY + 80;
        prim->priority = self->zPriority - 1;
        prim->drawMode = DRAW_UNK02;
    case BONE_PILLAR_BALL_LINK:
        if (self->ext.bonePillar.bottomDead) {
            self->drawFlags = FLAG_DRAW_ROTATE;
            self->hitPoints = 32767;
            self->hitboxState = 1;
            self->velocityX = FIX(-0.75);
            self->velocityY = FIX(-1.0);
            self->step++;
            entity = AllocEntity(&g_Entities[32], &g_Entities[47]);
            // Creates a new entity and links the two entities
            // The new entity is intentionally given a bogus entityId
            // All of this is done in order to give the ball invinvibility while
            // it is bouncing
            if (entity != NULL) {
                DestroyEntity(entity);
                entity->entityId = E_SEALED_DOOR;
                entity->pfnUpdate = EntityBonePillarSpikeBall;
                entity->attack = self->attack;
                entity->hitboxWidth = self->hitboxWidth;
                entity->hitboxHeight = self->hitboxHeight;
                entity->hitboxState = 2;
                entity->attackElement = ELEMENT_FIRE;
                entity->nFramesInvincibility = 16;
                entity->stunFrames = 4;
                entity->hitEffect = 1;
                // This is the only reference to ext.bonePillar.unkB2.
                entity->ext.bonePillar.unkB2 = 0;
                entity->flags =
                    FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
                g_api.func_80118894(entity);
                entity->step = BONE_PILLAR_BALL_BOUNCE_INVINC;
                entity->ext.bonePillar.linkEntity = self;
                self->ext.bonePillar.linkEntity = entity;
            }
        }
        break;
    case BONE_PILLAR_BALL_BOUNCE:
        MoveEntity();
        self->rotate -= ROT(5.625);
        self->velocityY += FIX(0.25);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 8;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (!self->ext.bonePillar.isBouncing) {
                self->ext.bonePillar.isBouncing = true;
                PlaySfxPositional(SFX_PLATE_LORD_BALL_IMPACT);
            } else {
                PlaySfxPositional(SFX_METAL_CLANG_B);
            }
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY;
            self->velocityY -= self->velocityY / 2;

            if (abs(self->velocityY) < FIX(0.5)) {
                self->step++;
            }
        }
        break;
    case BONE_PILLAR_BALL_LAND:
        UnkCollisionFunc2(sensors_spike_ball);
        self->rotate -= ROT(11.25);
        self->velocityX = FIX(-1.75);
        break;
    case BONE_PILLAR_BALL_BOUNCE_INVINC:
        entity = self->ext.bonePillar.linkEntity;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        if (entity->entityId != E_BONE_PILLAR_SPIKE_BALL) {
            DestroyEntity(self);
        }
        return;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - 15;
    prim->y0 = prim->y1 = self->posY.i.hi - 16;
    prim->x1 = prim->x3 = prim->x0 + 32;
    prim->y2 = prim->y3 = prim->y0 + 32;
    if (self->ext.bonePillar.bottomDead) {
        if (g_Timer & 2) {
            self->palette = g_EInitBonePillarSpikeBall[3];
            prim->clut = g_EInitBonePillarSpikeBall[3] + 2;
        } else {
            self->palette = g_EInitBonePillarSpikeBall[3] + 1;
            prim->clut = g_EInitBonePillarSpikeBall[3] + 3;
        }
    }
}

void EntityBonePillarFireBreath(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 posX, posY;
    s16* ptr;

    switch (self->step) {
    case BONE_PILLAR_FIRE_INIT:
        InitializeEntity(g_EInitBonePillarFireBreath);
        self->animSet = NULL;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.bonePillar.prim = prim;
        prim->tpage = 19;
        prim->clut = PAL_BONE_PILLAR_FIRE;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        self->hitboxWidth = 21;
        self->hitboxHeight = 24;
        if (self->facingLeft) {
            prim->x0 = posX + 48;
            prim->x1 = posX - 4;
            prim->x2 = posX + 64;
            prim->x3 = posX + 4;
            prim->y0 = posY - 96;
            prim->y1 = posY - 8;
            prim->y2 = posY - 32;
            prim->y3 = posY + 8;
            self->hitboxOffX = -32;
            self->hitboxOffY = -24;
        } else {
            prim->x0 = posX - 64;
            prim->x1 = posX - 4;
            prim->x2 = posX - 48;
            prim->x3 = posX + 4;
            prim->y0 = posY;
            prim->y1 = posY - 8;
            prim->y2 = posY + 64;
            prim->y3 = posY + 8;
            self->hitboxOffX = -32;
            self->hitboxOffY = 30;
        }
        PlaySfxPositional(SFX_FIREBALL_SHOT_A);
    case BONE_PILLAR_FIRE_BREATH:
        if (!AnimateEntity(anim_fire_breath, self)) {
            self->hitboxState = 0;
            self->step++;
            return;
        }
        prim = self->ext.bonePillar.prim;
        ptr = sprites_dai_5[self->animCurFrame];
        ptr += 8;
        prim->u0 = prim->u2 = *ptr++;
        prim->v0 = prim->v1 = *ptr++;
        prim->u1 = prim->u3 = *ptr++;
        prim->v2 = prim->v3 = *ptr++;
        break;
    case BONE_PILLAR_FIRE_AFTERBURN:
        for (prim = self->ext.bonePillar.prim; prim != NULL;
             prim = prim->next) {
            prim->type = PRIM_TILE;
            if (self->facingLeft) {
                posX = (Random() & 0x1F) + 16;
            } else {
                posX = -(Random() & 0x1F) - 16;
            }
            prim->x0 = self->posX.i.hi + posX;
            posY = self->posY.i.hi - posX;
            prim->y0 = posY - (Random() & 0x1F) + 8;
            prim->u0 = 1;
            prim->v0 = 1;
            prim->r0 = 224;
            prim->b0 = 136;
            prim->g0 = 160;
            prim->p2 = (Random() & 7) + 1;
            prim->priority = self->zPriority + 1;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        }
        // Attack timer
        self->ext.bonePillar.timer = 48;
        self->step++;
    case BONE_PILLAR_FIRE_EMBERS:
        for (prim = self->ext.bonePillar.prim; prim != NULL;
             prim = prim->next) {
            if (!(g_Timer % prim->p2)) {
                prim->y0--;
            }
            prim->r0 -= 2;
            prim->g0 -= 2;
            prim->b0 -= 2;
        }
        if (!--self->ext.bonePillar.timer) {
            DestroyEntity(self);
        }
    }
}

void EntityBonePillarDeathParts(Entity* self) {
    Collider collider;
    s32 posX, posY;

    switch (self->step) {
    case BONE_PILLAR_DEATH_INIT:
        InitializeEntity(g_EInitBonePillarParts);
        self->hitboxState = 0;
        self->animCurFrame = (self->params & 0xF) + 18;
        self->zPriority += self->params & 0xF;
        if (self->params & 1) {
            self->ext.bonePillar.timer = 24;
        } else {
            self->ext.bonePillar.timer = 12;
        }
        break;
    case BONE_PILLAR_DEATH_FADE:
        if (!--self->ext.bonePillar.timer) {
            self->step++;
        }
        break;
    case BONE_PILLAR_DEATH_PARTS:
        MoveEntity();
        self->velocityY += FIX(0.15625);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + y_offset[self->params];
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            self->ext.bonePillar.timer = 14;
            self->step++;
        }
        break;
    case BONE_PILLAR_DEATH_EXPLODE:
        if (!--self->ext.bonePillar.timer) {
            self->step = BONE_PILLAR_INIT;
            self->pfnUpdate = EntityExplosion;
            self->params = EXPLOSION_SMALL;
        }
    }
}
