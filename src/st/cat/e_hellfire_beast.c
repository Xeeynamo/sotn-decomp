// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

extern EInit g_EInitHellfireBeast;
extern EInit g_EInitHellfireBeastThorsHammer;
extern EInit g_EInitHellfireBeastFlamePillar;

// Used to set prim->r0,g0,b0 for the Thor's Hammer / Flame Pillar casts
static u8 attack_rgbs[2][3] = {{2, 1, 7}, {7, 4, 1}};
// EntityHellfireBeastThorsHammer, EntityHellfireBeastFlamePillar
static u16 attack_cluts[] = {PAL_DRA(0x16C), PAL_DRA(0x16D)};
static u16 attack_entityIds[] = {
    E_HELLFIRE_BEAST_THORS_HAMMER, E_HELLFIRE_BEAST_FLAME_PILLAR};
static s16 sensors_ground[] = {0, 46, 0, 4, 8, -4, -16, 0};
static s16 death_parts_sensors_ground[] = {0, 8, 0, 4, 8, -4, -16, 0};
static s16 sensors_wall[] = {0, 46, 32, 0};

static AnimateEntityFrame anim_idle_breathe[] = {
    {.duration = 7, .pose = 0x19}, {.duration = 7, .pose = 0x1A},
    {.duration = 7, .pose = 0x1B}, {.duration = 6, .pose = 0x1C},
    {.duration = 7, .pose = 0x1D}, POSE_LOOP(0)};
static AnimateEntityFrame anim_punch[] = {
    {.duration = 38, .pose = 0x1E},
    {.duration = 5, .pose = 0x1F},
    {.duration = 3, .pose = 0x20},
    {.duration = 3, .pose = 0x21},
    {.duration = 1, .pose = 0x22},
    {.duration = 1, .pose = 0x23},
    POSE_END};
static AnimateEntityFrame anim_punch_skid_stop[] = {
    {.duration = 4, .pose = 0x24},
    {.duration = 4, .pose = 0x25},
    {.duration = 6, .pose = 0x26},
    {.duration = 2, .pose = 0x27},
    {.duration = 3, .pose = 0x28},
    {.duration = 2, .pose = 0x29},
    {.duration = 16, .pose = 0x2A},
    {.duration = 5, .pose = 0x25},
    POSE_END};
static AnimateEntityFrame anim_punch_hard_stop[] = {
    {.duration = 1, .pose = 0x22}, {.duration = 3, .pose = 0x21},
    {.duration = 3, .pose = 0x20}, {.duration = 5, .pose = 0x1F},
    {.duration = 4, .pose = 0x19}, POSE_END};
static AnimateEntityFrame anim_unused_stutter[] = {
    {.duration = 4, .pose = 0x24},
    {.duration = 2, .pose = 0x25},
    {.duration = 2, .pose = 0x27},
    {.duration = 4, .pose = 0x19},
    POSE_END};
static AnimateEntityFrame anim_raise_arms_attack[] = {
    {.duration = 39, .pose = 0x19},
    {.duration = 2, .pose = 0x24},
    {.duration = 2, .pose = 0x25},
    {.duration = 2, .pose = 0x28},
    {.duration = 3, .pose = 0x33},
    {.duration = 2, .pose = 0x34},
    {.duration = 2, .pose = 0x35},
    {.duration = 2, .pose = 0x34},
    POSE_END};
static AnimateEntityFrame anim_attack_cast_wiggle[] = {
    {.duration = 1, .pose = 0x34}, {.duration = 1, .pose = 0x36}, POSE_LOOP(0)};

static Point16 death_parts_positions[6] = {
    {.x = -32, .y = -26}, {.x = -1, .y = -34}, {.x = -21, .y = -44},
    {.x = -16, .y = -24}, {.x = -30, .y = 1},  {.x = -13, .y = 1}};
// Indexed off self->params
static s16 death_parts_timer[6] = {32, 40, 64, 104, 96, 100};
// Sets sVec vy for each of 8 death part prims
static s16 death_parts_yOffsets[] = {
    0, 512, 896, 1536, -2048, -512, -3456, -1536};
// Sets the delay for each of 8 death part prims
static u8 death_parts_fall_delay[] = {40, 30, 16, 0, 44, 8, 32, 28};

typedef enum {
    INIT = 0,
    DROP_TO_GROUND = 1,
    IDLE = 2,
    UNUSED_STUTTER = 3,
    PUNCH_ATTACK = 4,
    ATTACK_INIT = 5,
    DEATH_INIT = 16,
    DEATH_PARTS_DROP = 17,
    DEATH_PARTS_EXPLODE = 19
} HellfireBeast_Step;

static void SpawnDeathParts(void) {
    long p, flag;
    SVECTOR svecTwo;
    VECTOR vec;
    MATRIX matrix;
    SVECTOR emptySvec = {0};
    SVECTOR p0, p1, p2, p3;

    Primitive* prim;
    Entity* newEntity;
    s32 i;
    s16 posX;
    s16 posY;
    s32 rotAvg;
    s32 primIndex;

    switch (g_CurrentEntity->step_s) {
    case 0:
        // BUG? Immediately overwritten
        g_CurrentEntity->animCurFrame = 0x32;
        g_CurrentEntity->animCurFrame = 0;

        for (i = 5; i >= 0; i--) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_HELLFIRE_BEAST, g_CurrentEntity, newEntity);
                posX = death_parts_positions[i].x;
                posY = death_parts_positions[i].y;
                posX += 0x10;
                posY += 0x14;
                if (g_CurrentEntity->facingLeft) {
                    posX = -posX;
                }
                posX = newEntity->posX.i.hi += posX;
                posY = newEntity->posY.i.hi += posY;
                newEntity->params = i;
                newEntity->facingLeft = g_CurrentEntity->facingLeft;
                newEntity->step = DEATH_PARTS_DROP;
                newEntity->flags |= FLAG_UNK_2000;
            }
        }

        primIndex = g_api.AllocPrimitives(PRIM_G4, 8);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.hellfireBeast.prim = prim;

            i = 0;
            while (prim != NULL) {
                prim->r0 = 0x20;
                prim->g0 = 0x20;
                prim->b0 = 0x40;
                LOW(prim->r1) = LOW(prim->r0);

                prim->r2 = 0xC0;
                prim->g2 = 0xC0;
                prim->b2 = 0xD0;
                LOW(prim->r3) = LOW(prim->r2);

                prim->u0 = death_parts_fall_delay[i];
                LOH(prim->u2) = death_parts_yOffsets[i];
                prim->v0 = 0;
                prim->u1 = 1;
                prim->v1 = 0;

                prim->priority = g_CurrentEntity->zPriority + 1;
                prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
                i++;
            }
        } else {
            DestroyEntity(g_CurrentEntity);
            break;
        }
        g_CurrentEntity->step_s++;
        break;
    case 1:
        prim = g_CurrentEntity->ext.hellfireBeast.prim;
        SetGeomScreen(0x400);
        posX = g_CurrentEntity->posX.i.hi;
        posY = g_CurrentEntity->posY.i.hi + 0x2F;
        SetGeomOffset(posX, posY);
        while (prim != NULL) {
            if (prim->u0) {
                prim->u0--;
                prim = prim->next;
            } else {
                svecTwo.vx = 0;
                svecTwo.vy = LOH(prim->u2);
                svecTwo.vz = 0;
                RotMatrix(&emptySvec, &matrix);
                RotMatrixY(svecTwo.vy, &matrix);
                vec.vx = 0;
                vec.vy = 0;
                vec.vz = 0x400;
                TransMatrix(&matrix, &vec);
                SetRotMatrix(&matrix);
                SetTransMatrix(&matrix);

                p0.vx = p2.vx = -(prim->u1 - prim->v1);
                p1.vx = p3.vx = prim->u1 - prim->v1;
                p0.vy = p1.vy = -prim->v0;
                p2.vy = p3.vy = 0;
                p0.vz = p1.vz = p2.vz = p3.vz = -0x18;
                rotAvg = RotAverage4(
                    &p0, &p1, &p2, &p3, (long*)&prim->x0, (long*)&prim->x1,
                    (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
                if (rotAvg < 0x100) {
                    prim->priority = g_CurrentEntity->zPriority + 2;
                } else {
                    prim->priority = g_CurrentEntity->zPriority - 2;
                }

                if (prim->v0 > 0xF0) {
                    if (prim->u1 > 0xA) {
                        if (prim->v1 > prim->u1) {
                            prim->drawMode = DRAW_HIDE;
                        } else {
                            prim->v1++;
                        }
                    } else {
                        prim->u1++;
                    }
                } else {
                    prim->v0 += 0xF;
                    if (prim->v0 > 0xF0 && LOH(prim->u2) < 0) {
                        PlaySfxPositional(SFX_BONE_SWORD_SWISH_B);
                    }
                }
                prim = prim->next;
            }
        }
        break;
    }
}

void EntityHellfireBeast(Entity* self) {
    Primitive* prim;
    Entity* entity;
    s32 primIndex;
    u8* ptr;
    s16 attackCastPosX;
    s16 attackCastPosY;
    u8 animResult;
    u16 newEntityId;

    if (self->flags & FLAG_DEAD && self->step < DEATH_INIT) {
        if (self->flags & FLAG_HAS_PRIMS) {
            primIndex = self->primIndex;
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }
        if (self->ext.hellfireBeast.attackEntity != NULL) {
            entity = self->ext.hellfireBeast.attackEntity;
            DestroyEntity(entity);
        }
        self->hitboxState = 0;
        self->ext.hellfireBeast.timer = 0x100;
        PlaySfxPositional(SFX_HELLFIRE_BEAST_DEATH);
        SetStep(DEATH_INIT);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitHellfireBeast);
        // Spawn facing the player
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_HELLFIRE_BEAST_PUNCH_HITBOX, entity);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.hellfireBeast.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x1A;
            prim->clut = PAL_DRA(0x208);
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x3F;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xFF;
            prim->priority = self->zPriority - 2;
            prim->drawMode = DRAW_HIDE;
            prim->p3 |= 0x10;
            LOH(prim->next->r2) = 0x40;
            LOH(prim->next->b2) = 0x40;
            prim = prim->next;
            prim = prim->next;

            self->ext.hellfireBeast.primTwo = prim;
            prim->tpage = 0x12;
            prim->clut = PAL_DRA(0x230);
            prim->u0 = prim->u2 = 0xA0;
            prim->u1 = prim->u3 = 0xBF;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xD7;
            prim->priority = self->zPriority + 1;
        } else {
            DestroyEntity(self);
            return;
        }
        break;
    case DROP_TO_GROUND:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            self->step++;
        }
        break;
    case IDLE:
        if (!self->step_s) {
            self->ext.hellfireBeast.timer = 0x40;
            self->step_s++;
        } else {
            if (!AnimateEntity(anim_idle_breathe, self)) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            }

            if (self->ext.hellfireBeast.timer) {
                self->ext.hellfireBeast.timer--;
            } else if (GetDistanceToPlayerX() < 64) {
                // If player is close, use slide punch attack
                SetStep(PUNCH_ATTACK);
            } else {
                // Otherwise prep lightning / flame pillar attack
                SetStep(ATTACK_INIT);
            }
        }
        break;
    case UNUSED_STUTTER:
        // This case appears unused - the animation is similar to part of the
        // punch animation so may have been intended to be part of that logic
        animResult = AnimateEntity(anim_unused_stutter, self);
        if (animResult & 0x80 && self->pose == 4) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        if (!animResult) {
            SetStep(IDLE);
        }
        break;
    case PUNCH_ATTACK:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            break;
        case 1:
            UnkCollisionFunc2(sensors_wall);
            if (!AnimateEntity(anim_punch, self)) {
                PlaySfxPositional(SFX_BONE_SWORD_SWISH_B);
                self->ext.hellfireBeast.timer = 0xC;
                SetSubStep(2);
            }
            if (self->pose == 4) {
                self->velocityX = FIX(-4.0);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
            }
            break;
        case 2:
            UnkCollisionFunc2(sensors_wall);
            if (self->facingLeft) {
                self->velocityX -= FIX(1.0 / 6.0);
            } else {
                self->velocityX += FIX(1.0 / 6.0);
            }

            if (!--self->ext.hellfireBeast.timer) {
                SetSubStep(3);
                if (!self->velocityX) {
                    SetSubStep(4);
                } else if (self->facingLeft) {
                    EntityGreyPuffSpawner(self, 5, 3, 0x18, 0x30, 2, -7);
                } else {
                    EntityGreyPuffSpawner(self, 5, 3, -0x18, 0x30, 2, 7);
                }
            }
            break;
        case 3:
            UnkCollisionFunc2(sensors_wall);
            if (self->pose > 2) {
                self->velocityX -= self->velocityX / 8;
            }

            if (!AnimateEntity(anim_punch_skid_stop, self)) {
                SetStep(IDLE);
            }
            break;
        case 4:
            if (!AnimateEntity(anim_punch_hard_stop, self)) {
                SetStep(IDLE);
            }
            break;
        }
        break;
    case ATTACK_INIT:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_raise_arms_attack, self)) {
                // Pick a random cast attack
                // 0 = Lightning
                // 1 = Flame pillar
                self->ext.hellfireBeast.attackChoice = Random() & 1;
                SetSubStep(1);
            }
            break;
        case 1:
            // Begin the cast
            switch (self->ext.hellfireBeast.attackChoice) {
            // Lightning
            case 0:
                if (self->facingLeft) {
                    attackCastPosX = 0x24;
                } else {
                    attackCastPosX = -0x24;
                }
                attackCastPosY = -8;
                break;
            // Flame pillar
            case 1:
                // Pillar appears beneath the player's feet
                attackCastPosX = PLAYER.posX.i.hi - self->posX.i.hi;
                attackCastPosY = 0x2F;
                break;
            default:
                attackCastPosX = 0x24;
                attackCastPosY = -8;
                break;
            }

            prim = self->ext.hellfireBeast.prim;
            prim->clut = attack_cluts[self->ext.hellfireBeast.attackChoice];
            LOH(prim->next->u1) = 0;
            prim->next->x2 = 0;
            prim->next->y2 = 0;
            prim->next->b3 = 0;
            prim->next->x1 = self->posX.i.hi;
            prim->next->x1 += attackCastPosX;
            prim->next->y0 = self->posY.i.hi + attackCastPosY;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            prim = self->ext.hellfireBeast.primTwo;
            if (self->facingLeft) {
                prim->x0 = prim->x2 = self->posX.i.hi - 0xFFDF;
                prim->x1 = prim->x3 = prim->x0 - 0x20;
            } else {
                prim->x0 = prim->x2 = self->posX.i.hi + 0xFFDF;
                prim->x1 = prim->x3 = prim->x0 + 0x20;
            }
            prim->y0 = prim->y1 = self->posY.i.hi + 0xFFEF;
            prim->y2 = prim->y3 = prim->y1 + 0x18;

            PGREY(prim, 0) = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_TRANSP | DRAW_UNK02 | DRAW_COLORS |
                             DRAW_TPAGE | DRAW_TPAGE2 | DRAW_UNK_400;
            self->ext.hellfireBeast.timer = 0x20;
            self->step_s++;
            break;
        case 2:
            // Spawn the attack entity of choice
            prim = self->ext.hellfireBeast.prim;
            prim->next->b3 += 4;
            prim->next->x2 = prim->next->y2 += 0x30;

            prim = self->ext.hellfireBeast.primTwo;
            ptr = attack_rgbs[self->ext.hellfireBeast.attackChoice];
            prim->r0 += *ptr++;
            prim->g0 += *ptr++;
            prim->b0 += *ptr++;
            LOW(prim->r2) = LOW(prim->r0);

            if (self->ext.hellfireBeast.timer % 2) {
                prim->drawMode |= DRAW_HIDE;
            } else {
                prim->drawMode &= ~DRAW_HIDE;
            }

            if (!--self->ext.hellfireBeast.timer) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    newEntityId =
                        attack_entityIds[self->ext.hellfireBeast.attackChoice];
                    CreateEntityFromEntity(newEntityId, self, entity);
                    entity->facingLeft = self->facingLeft;
                    prim = self->ext.hellfireBeast.prim;
                    entity->posX.i.hi = prim->next->x1;
                    entity->posY.i.hi = prim->next->y0;
                    self->ext.hellfireBeast.attackEntity = entity;
                    self->step_s++;
                } else {
                    self->ext.hellfireBeast.attackEntity = NULL;
                    SetStep(IDLE);
                    return;
                }
            }
            break;
        case 3:
            AnimateEntity(anim_attack_cast_wiggle, self);
            prim = self->ext.hellfireBeast.primTwo;
            if (self->animCurFrame == 0x34) {
                prim->drawMode |= DRAW_HIDE;
            } else {
                prim->drawMode &= ~DRAW_HIDE;
            }

            entity = self->ext.hellfireBeast.attackEntity;
            if (!entity->entityId) {
                self->ext.hellfireBeast.attackEntity = NULL;
                prim = self->ext.hellfireBeast.primTwo;
                prim->drawMode = DRAW_HIDE;
                self->animCurFrame = 0x25;
                self->step_s++;
            }
            break;
        case 4:
            prim = self->ext.hellfireBeast.prim;
            prim->next->b3 -= 8;
            if (prim->next->b3 < 0x10) {
                prim->drawMode = DRAW_HIDE;
                SetStep(IDLE);
            }
            break;
        }

        prim = self->ext.hellfireBeast.prim;
        UnkPrimHelper(prim);
        switch (g_Timer % 3) {
        case 0:
            prim->clut = PAL_DRA(0x300);
            break;
        case 1:
            prim->clut = PAL_DRA(0x15F);
            break;
        case 2:
            prim->clut = attack_cluts[self->ext.hellfireBeast.attackChoice];
            break;
        }

        break;
    case DEATH_INIT:
        SpawnDeathParts();
        if (!--self->ext.hellfireBeast.timer) {
            DestroyEntity(self);
            return;
        }
        break;
    case DEATH_PARTS_DROP:
        // Death parts are spawned with params 0-5 (6 total)
        InitializeEntity(g_EInitHellfireBeast);
        self->hitboxState = 0;
        self->animCurFrame = self->params + 0x2B;
        self->ext.hellfireBeast.timer = death_parts_timer[self->params];
        if (self->params < 3) {
            self->zPriority += 4;
        }
        if (self->params < 4) {
            self->zPriority++;
        } else {
            self->drawFlags |= FLAG_DRAW_ROTATE;
        }
        SetStep(DEATH_PARTS_EXPLODE);
        break;
    case DEATH_PARTS_EXPLODE:
        if (self->ext.hellfireBeast.timer) {
            self->ext.hellfireBeast.timer--;
            if (!self->ext.hellfireBeast.timer) {
                // BUG! This plays the same sound effect either way
                if (self->params == 2) {
                    PlaySfxPositional(SFX_WEAPON_STAB_B);
                } else {
                    PlaySfxPositional(SFX_WEAPON_STAB_B);
                }
            }
            break;
        }

        // Once the death parts hit the ground, burst into flames and despawn
        if (UnkCollisionFunc3(death_parts_sensors_ground) & 1) {
            PlaySfxPositional(SFX_EXPLODE_B);
            MakeExplosions();
            DestroyEntity(self);
            return;
        }

        self->rotate += self->ext.hellfireBeast.deathPartsRotate;
        self->ext.hellfireBeast.deathPartsRotate += 2;
        self->velocityY -= FIX(0.125);
        break;
    }

    if (self->animCurFrame > 0x1F && self->animCurFrame < 0x24) {
        self->hitboxOffX = -9;
        self->hitboxOffY = 0xF;
        self->hitboxWidth = 0xC;
        self->hitboxHeight = 0x1E;
    } else {
        self->hitboxOffX = 0;
        self->hitboxOffY = 9;
        self->hitboxWidth = 0xE;
        self->hitboxHeight = 0x23;
    }
}

// Horizontal lightning attack cast
void EntityHellfireBeastThorsHammer(Entity* self) {
    u8 prevV0;
    s16 angle;
    s16 posX;
    s16 posY;
    s32 primIndex;

    Primitive* prim;
    Primitive* nextPrim;
    s16 var_s2;
    s32 dx;
    s16 var_s4;
    s32 dy;
    u8 var_s6;
    u8 var_s7;
    s16 i;
    s32 fake;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHellfireBeastThorsHammer);
        self->hitboxWidth = self->hitboxHeight = 0;
        self->animSet = 2;
        self->animCurFrame = 0;
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.hellfireBeastThorsHammer.prim = prim;
            prim->x0 = prim->x1 = self->posX.i.hi;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->r0 = 0x60;
            prim->g0 = 0x20;
            prim->b0 = 0x80;
            PGREY(prim, 1) = 0x20;
            prim->priority = self->zPriority + 8;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        } else {
            DestroyEntity(self);
            break;
        }
        PlaySfxPositional(SFX_BAT_ECHO_C);
        // fallthrough
    case 1:
        prim = self->ext.hellfireBeastThorsHammer.prim;
        if (!self->step_s) {
            if (self->facingLeft) {
                prim->x0 += 0x20;
            } else {
                prim->x0 -= 0x20;
            }

            if (prim->x0 & 0xFF00) {
                self->step_s++;
            }
        } else if (!PrimDecreaseBrightness(prim, 7)) {
            self->step++;
        }
        break;
    case 2:
        primIndex = self->primIndex;
        g_api.FreePrimitives(primIndex);
        self->flags &= ~FLAG_HAS_PRIMS;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x40);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.hellfireBeastThorsHammer.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0x13;
                prim->clut = PAL_DRA(0x24A);
                prim->v0 = prim->v2 = 0x20;
                prim->v1 = prim->v3 = 0x10;
#ifdef VERSION_PSP
                PGREY(prim, 0) = 0xF0;
#else
                PGREY(prim, 0) = 0xC0;
#endif
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            break;
        }
        self->ext.hellfireBeastThorsHammer.unk8C = 0;
        self->ext.hellfireBeastThorsHammer.unk90 = 0;
        self->ext.hellfireBeastThorsHammer.unk8A = 4;
        self->hitboxState = 1;
        self->ext.hellfireBeastThorsHammer.castTimer = 0x80;
        self->step++;
        // fallthrough
    case 3:
        posX = self->posX.i.hi +
               (self->ext.hellfireBeastThorsHammer.unk8C >> 0x10);
        posY = self->posY.i.hi;
        if (self->facingLeft) {
            posY -= 8;
        } else {
            posY += 8;
        }

        self->ext.hellfireBeastThorsHammer.unk8C +=
            self->ext.hellfireBeastThorsHammer.unk90;
        if (self->facingLeft) {
            self->ext.hellfireBeastThorsHammer.unk90 += 0x4000;
        } else {
            self->ext.hellfireBeastThorsHammer.unk90 -= 0x4000;
        }

        if (self->facingLeft) {
            var_s4 = 0;
        } else {
            var_s4 = ROT(180);
        }

        var_s4 += (0xD0 - ((Random() & 7) << 6));
        var_s6 = self->ext.hellfireBeastThorsHammer.unk94 * 0x10;
        self->ext.hellfireBeastThorsHammer.unk94++;
        if (self->ext.hellfireBeastThorsHammer.unk94 > 6) {
            self->ext.hellfireBeastThorsHammer.unk94 = 1;
        }

        i = 1;
        prim = self->ext.hellfireBeastThorsHammer.prim;
        prim->x0 = self->posX.i.hi;
        prim->x1 = prim->x0;
        prim->y0 = self->posY.i.hi;
        if (self->facingLeft) {
            prim->y0 -= 8;
            prim->y1 = prim->y0 + 0x10;
        } else {
            prim->y0 += 8;
            prim->y1 = prim->y0 - 0x10;
        }

        prim->x2 = self->posX.i.hi;
        prim->y2 = prim->y0;
        prim->x3 = prim->x2;
        prim->y3 = prim->y1;

        while (true) {
            dx = posX - prim->x2;
            dy = posY - prim->y2;
            if (!self->ext.hellfireBeastThorsHammer.unk88) {
                self->ext.hellfireBeastThorsHammer.unk88 = 4;
                angle = ratan2(-dy, dx);
                var_s2 = angle - var_s4;
                if (var_s2 > ROT(180)) {
                    var_s2 = ROT(360) - var_s2;
                }
                if (var_s2 < ROT(-180)) {
                    var_s2 = ROT(360) + var_s2;
                }
                var_s2 /= 4;
                self->ext.hellfireBeastThorsHammer.unk86 = var_s2;
            }

            var_s4 += self->ext.hellfireBeastThorsHammer.unk86;
            var_s4 &= 0xFFF;

            nextPrim = prim->next;
            if (nextPrim == NULL) {
                self->step++;
                break; // exits while loop
            }

            LOW(nextPrim->x0) = LOW(prim->x2);
            LOW(nextPrim->x1) = LOW(prim->x3);
            dx = (rcos(var_s4) * 0xC) >> 0xC;
            dy = -((rsin(var_s4) * 0xC) >> 0xC);
            nextPrim->x2 = nextPrim->x0 + dx;
            nextPrim->y2 = nextPrim->y0 + dy;

            var_s2 = var_s4 - 0x400;
            var_s7 = 0x10;
            dx = (var_s7 * rcos(var_s2)) >> 0xC;
            dy = -(var_s7 * rsin(var_s2) >> 0xC);
            nextPrim->x3 = nextPrim->x2 + dx;
            nextPrim->y3 = nextPrim->y2 + dy;

            nextPrim->u1 = var_s6;
            nextPrim->u0 = var_s6;
            nextPrim->u2 = nextPrim->u3 = nextPrim->u0 + 0xF;
            var_s6 += 0x10;
            if (var_s6 > 0x60) {
                var_s6 = 0x10;
            }

            if (!(g_Timer % 2)) {
                prevV0 = nextPrim->v0;
                nextPrim->v0 = nextPrim->v2 = nextPrim->v1;
                nextPrim->v1 = nextPrim->v3 = prevV0;
            }
            nextPrim->drawMode = DRAW_COLORS | DRAW_UNK02;
            prim = nextPrim;
            self->ext.hellfireBeastThorsHammer.unk88--;
            i++;

            if (i <= self->ext.hellfireBeastThorsHammer.unk8A) {
                continue;
            }

            dx = nextPrim->x0 - self->posX.i.hi;
            dx = abs(dx);
            if (dx > 0x1FF) {
                dx = 0x1FF;
            }
            self->hitboxOffX = -dx / 2;
            self->hitboxWidth = dx / 2;
            self->hitboxHeight = 8;
            self->hitboxOffY = 8;

            // FAKE! PSX requires some trickery here, was not able to resolve
#ifdef VERSION_US
            fake = 8;
            while (prim != NULL) {
                prim->drawMode = fake;
                prim = prim->next;
            }

            if (0) {
                while (posY)
                    ;
            }
#else
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
#endif

            if (!(g_Timer % 3) &&
                self->ext.hellfireBeastThorsHammer.unk8A < 0x40) {
                self->ext.hellfireBeastThorsHammer.unk8A++;
            }
            if (!(self->ext.hellfireBeastThorsHammer.castTimer & 0x1F)) {
                g_api.PlaySfx(SFX_ELECTRICITY);
            }

            if (!--self->ext.hellfireBeastThorsHammer.castTimer) {
                self->step++;
            }
            break; // exits while loop
        }
        break;
    case 4:
        DestroyEntity(self);
        break;
    }
}

void EntityHellfireBeastFlamePillarAnimation(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->zPriority = 0x100;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        if (self->params) {
            self->rotate = ROT(180);
            self->velocityY = FIX(1.0);
        } else {
            self->rotate = 0;
            self->velocityY = FIX(-1.0);
        }
    }
    self->posY.val += self->velocityY;
    self->poseTimer++;
    if (!(self->poseTimer % 2)) {
        self->animCurFrame += 1;
    }
    if (self->poseTimer > 0xF) {
        DestroyEntity(self);
    }

#ifdef VERSION_PSP
    if (self->ext.hellfireBeastThorsHammer.entity != NULL &&
        !self->ext.hellfireBeastThorsHammer.entity->entityId) {
#else
    if (!self->ext.hellfireBeastThorsHammer.entity->entityId) {
#endif
        DestroyEntity(self);
    }
}

extern Primitive* FindFirstUnkPrim(Primitive* prim);
static void UpdateFlamePillarPrims(Primitive* prim) {
    Primitive* p;
    s16 posX;
    s16 posY;
    s16 var_s1;
    s16 var_s2;

    posX = g_CurrentEntity->posX.i.hi;
    posY = g_CurrentEntity->posY.i.hi - prim->p1;
    var_s1 = -prim->p1 * 6;
    prim->y0 = posY - ((g_CurrentEntity->ext.hellfireBeastFlamePillar.unk80 *
                        rsin(var_s1 + ROT(180))) >>
                       0xC);
    prim->y1 =
        posY -
        ((g_CurrentEntity->ext.hellfireBeastFlamePillar.unk80 * rsin(var_s1)) >>
         0xC);
    if (g_CurrentEntity->facingLeft) {
        prim->x0 =
            posX - ((g_CurrentEntity->ext.hellfireBeastFlamePillar.unk80 *
                     rcos(var_s1 + ROT(180))) >>
                    0xC);
        prim->x1 =
            posX - ((g_CurrentEntity->ext.hellfireBeastFlamePillar.unk80 *
                     rcos(var_s1)) >>
                    0xC);
    } else {
        prim->x0 =
            posX + ((g_CurrentEntity->ext.hellfireBeastFlamePillar.unk80 *
                     rcos(var_s1 + ROT(180))) >>
                    0xC);
        prim->x1 =
            posX + ((g_CurrentEntity->ext.hellfireBeastFlamePillar.unk80 *
                     rcos(var_s1)) >>
                    0xC);
    }

    posY += 0x20;
    var_s1 = -(g_CurrentEntity->posY.i.hi - posY) * 6;
    prim->y3 =
        posY -
        ((g_CurrentEntity->ext.hellfireBeastFlamePillar.unk80 * rsin(var_s1)) >>
         0xC);

    if (g_CurrentEntity->facingLeft) {
        prim->x2 =
            posX - ((g_CurrentEntity->ext.hellfireBeastFlamePillar.unk80 *
                     rcos(var_s1 + ROT(180))) >>
                    0xC);
        prim->x3 =
            posX - ((g_CurrentEntity->ext.hellfireBeastFlamePillar.unk80 *
                     rcos(var_s1)) >>
                    0xC);
    } else {
        prim->x2 =
            posX + ((g_CurrentEntity->ext.hellfireBeastFlamePillar.unk80 *
                     rcos(var_s1 + ROT(180))) >>
                    0xC);
        prim->x3 =
            posX + ((g_CurrentEntity->ext.hellfireBeastFlamePillar.unk80 *
                     rcos(var_s1)) >>
                    0xC);
    }

    var_s2 = g_CurrentEntity->posY.i.hi - 0x88;
    if (prim->y0 < var_s2) {
        prim->y0 = var_s2;
    }
    if (prim->y1 < var_s2) {
        prim->y1 = var_s2;
    }
    if (prim->y2 < var_s2) {
        prim->y2 = var_s2;
    }
    if (prim->y3 < var_s2) {
        prim->y3 = var_s2;
    }

    if (prim->y2 > g_CurrentEntity->posY.i.hi) {
        prim->y2 = g_CurrentEntity->posY.i.hi;
    }

    if (prim->y3 > g_CurrentEntity->posY.i.hi) {
        prim->y3 = g_CurrentEntity->posY.i.hi;
    }

    if (prim->p1 > 0xA8) {
        prim->drawMode = DRAW_HIDE;
        prim->p3 = 0;
    }

    if (prim->p1 == 0x20) {
        p = g_CurrentEntity->ext.hellfireBeastFlamePillar.prim;
        p = FindFirstUnkPrim(p);
        if (p != NULL) {
            p->p3 = 1;
            p->p1 = 0;
            p->y0 = p->y1 = g_CurrentEntity->posY.i.hi;
            p->y2 = p->y3 = g_CurrentEntity->posY.i.hi;
            p->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 |
                          DRAW_TRANSP;
        }
    }
}

void EntityHellfireBeastFlamePillar(Entity* self) {
    DRAWENV drawEnv;
    RECT rect = {.x = 0, .y = 256, .w = 64, .h = 64};

    Primitive* prim;
    Entity* newEntity;
    s32 i;
    s32 primIndex;
    DR_ENV* drEnv;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHellfireBeastFlamePillar);
        self->animSet = 2;
        self->animCurFrame = 0;
        self->hitboxWidth = self->hitboxHeight = 0;
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.hellfireBeastFlamePillar.prim = prim;

            prim->x0 = prim->x1 = self->posX.i.hi;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->r0 = 0xC0;
            prim->g0 = 0x80;
            prim->b0 = 0x20;
            PGREY(prim, 1) = 0x20;
            prim->priority = self->zPriority + 8;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        } else {
            DestroyEntity(self);
            break;
        }

        PlaySfxPositional(SFX_BAT_ECHO_C);
        // fallthrough
    case 1:
        prim = self->ext.hellfireBeastFlamePillar.prim;
        if (!self->step_s) {
            prim->y0 -= 0x20;
            if (prim->y0 & 0xFF00) {
                self->step_s++;
            }
        } else if (!PrimDecreaseBrightness(prim, 7)) {
            self->step++;
        }
        break;
    case 2:
        primIndex = self->primIndex;
        g_api.FreePrimitives(primIndex);
        self->flags &= ~FLAG_HAS_PRIMS;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x12);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.hellfireBeast.primThree = prim;

            drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
            if (drEnv == NULL) {
                DestroyEntity(self);
                break;
            }

            prim->type = PRIM_ENV;
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 1;
            drawEnv.clip = rect;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(drEnv, &drawEnv);
            prim->priority = 0xFF;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
            if (drEnv == NULL) {
                DestroyEntity(self);
                break;
            }

            prim->type = PRIM_ENV;
            prim->priority = 0x101;
            prim->drawMode = DRAW_UNK_800 | DRAW_HIDE;
            prim = prim->next;

            self->ext.hellfireBeastFlamePillar.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0x110;
                prim->u0 = prim->u1 = 0;
                prim->u2 = prim->u3 = 0x12;
                prim->v0 = prim->v2 = 0;
                prim->v1 = prim->v3 = 0x3F;
#ifdef VERSION_PSP
                PGREY(prim, 0) = 0xC0;
#else
                PGREY(prim, 0) = 0x60;
#endif
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p3 = 0;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            break;
        }

        prim = self->ext.hellfireBeastFlamePillar.prim;
        prim = FindFirstUnkPrim(prim);
        if (prim != NULL) {
            prim->p3 = 1;
            prim->p1 = 0;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->y2 = prim->y3 = self->posY.i.hi;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        }
        self->ext.hellfireBeastFlamePillar.unk80 = 0x18;
        self->ext.hellfireBeastFlamePillar.castTimer = -0x10;
        PlaySfxPositional(SFX_FIREBALL_SHOT_A);
        self->step++;

        break;
    case 3:
        prim = self->ext.hellfireBeast.primThree;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        prim->drawMode = DRAW_UNK_800;

        // NB. Strange way to write a single loop iteration...
        // Maybe the number of iterations changed during development?
        for (i = 0; i <= 0; i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(
                    E_HELLFIRE_BEAST_FLAME_PILLAR_ANIM, newEntity);
                newEntity->posX.i.hi = Random() & 0xF;
                newEntity->posY.i.hi = 0x20;
                newEntity->params = Random() & 1;
                newEntity->ext.hellfireBeastThorsHammer.entity = self;
            }
        }

        prim = self->ext.hellfireBeastFlamePillar.prim;
        while (prim != NULL) {
            if (prim->p3) {
                UpdateFlamePillarPrims(prim);
            }
            prim = prim->next;
        }

        prim = self->ext.hellfireBeastFlamePillar.prim;
        while (prim != NULL) {
            prim->p1 += 2;
            prim = prim->next;
        }

        self->ext.hellfireBeastFlamePillar.castTimer++;
        if (self->ext.hellfireBeastFlamePillar.castTimer < 0) {
            prim = self->ext.hellfireBeastFlamePillar.prim;
            while (prim != NULL) {
                prim->p1 += 6;
                prim = prim->next;
            }

            if (self->ext.hellfireBeastFlamePillar.unk80 < 0x20) {
                self->ext.hellfireBeastFlamePillar.unk80++;
            }
        } else {
            self->hitboxWidth = 0xC;
            self->hitboxHeight = 0x30;
            self->hitboxOffX = -4;
            self->hitboxOffY = -0x30;
            if (!(self->ext.hellfireBeastFlamePillar.castTimer % 8)) {
                PlaySfxPositional(SFX_EXPLODE_B);
            }
        }
        if (self->ext.hellfireBeastFlamePillar.castTimer > 0x60) {
            self->ext.hellfireBeastFlamePillar.unk80--;
            self->hitboxState = 0;
            if (self->ext.hellfireBeastFlamePillar.unk80 < 0) {
                DestroyEntity(self);
            }
        }
        break;
    }
}

extern EInit g_EInitHellfireBeastPunchHitbox;
void EntityHellfireBeastPunchHitbox(Entity* self) {
    Entity* hellfireBeast = self - 1;

    if (!self->step) {
        InitializeEntity(g_EInitHellfireBeastPunchHitbox);
        self->hitboxWidth = 0xA;
        self->hitboxHeight = 4;
        self->hitboxOffX = -0x24;
        self->hitboxOffY = 4;
    }
    self->posX.i.hi = hellfireBeast->posX.i.hi;
    self->posY.i.hi = hellfireBeast->posY.i.hi;
    self->facingLeft = hellfireBeast->facingLeft;
    if (hellfireBeast->animCurFrame == 0x23) {
        self->hitboxState = 1;
    } else {
        self->hitboxState = 0;
    }
    if (!hellfireBeast->entityId) {
        DestroyEntity(self);
    }
}
