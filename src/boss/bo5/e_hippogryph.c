// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

s32 g_BossMgrState = BOSS_MGR_IDLE;

static s32 death_ray_speeds[] = {
    FIX(4),      FIX(1.5),    FIX(2.8125), FIX(4.125),  FIX(3.25),
    FIX(2.25),   FIX(1.125),  FIX(4),      FIX(4.5),    FIX(3.0625),
    FIX(3.125),  FIX(2.9375), FIX(1.5),    FIX(4.875),  FIX(3.25),
    FIX(3.0625), FIX(4),      FIX(4.5),    FIX(2.8125), FIX(3),
    FIX(3.25),   FIX(4.25),   FIX(1.5),    FIX(3),      FIX(4.5),
    FIX(1.9375), FIX(3.125),  FIX(4.9375), FIX(4),      FIX(2.25),
    FIX(4.25),   FIX(3.0625), FIX(4),      FIX(1.5),    FIX(2.8125),
    FIX(4.125),  FIX(3.25),   FIX(2.25),   FIX(1.125),  FIX(4),
    FIX(4.5),    FIX(3.0625), FIX(3.125),  FIX(2.9375), FIX(1.5),
    FIX(4.875),  FIX(3.25),   FIX(3.0625), FIX(4),      FIX(4.5),
    FIX(2.8125), FIX(3),      FIX(3.25),   FIX(4.25),   FIX(1.5),
    FIX(3),      FIX(4.5),    FIX(1.9375), FIX(3.125),  FIX(4.9375),
    FIX(4),      FIX(2.25),   FIX(4.25),   FIX(3.0625)};
static s32 death_particle_speeds[] = {
    FIX(3),    FIX(1.5),  FIX(2.8125), FIX(3.125),
    FIX(2.25), FIX(2.25), FIX(1.125),  FIX(3.5)};
static AnimateEntityFrame anim_prepare_spit_fire[] = {
    POSE(5, 54, 0), POSE(5, 55, 0), POSE(5, 56, 0), POSE(5, 57, 0),
    POSE(5, 58, 0), POSE(3, 59, 0), POSE(3, 60, 0), POSE(3, 61, 0),
    POSE(3, 60, 0), POSE(3, 59, 0), POSE(5, 58, 0), POSE(5, 57, 0),
    POSE(5, 56, 0), POSE(5, 55, 0), POSE(5, 54, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_run[] = {
    POSE(8, 1, 0), POSE(8, 2, 0), POSE(8, 3, 0),
    POSE(8, 4, 0), POSE(8, 5, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_flap[] = {
    POSE(2, 6, 0),  POSE(6, 7, 0),  POSE(8, 8, 0),
    POSE(8, 9, 0),  POSE(6, 10, 0), POSE(5, 11, 0),
    POSE(7, 12, 0), POSE(6, 13, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_hover[] = {
    POSE(2, 6, 0),  POSE(4, 7, 0),  POSE(4, 8, 0),
    POSE(4, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0),
    POSE(4, 12, 0), POSE(3, 13, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_fire_breath[] = {
    POSE(4, 26, 0), POSE(3, 25, 0), POSE(2, 24, 0), POSE(2, 23, 0),
    POSE(2, 14, 0), POSE(2, 15, 0), POSE(2, 16, 0), POSE(4, 17, 0),
    POSE(4, 18, 0), POSE(4, 19, 0), POSE(4, 20, 0), POSE(7, 21, 0),
    POSE(8, 22, 0), POSE(9, 23, 0), POSE(7, 24, 0), POSE(4, 25, 0),
    POSE(2, 26, 0), POSE(2, 27, 0), POSE(7, 28, 0), POSE(7, 29, 0),
    POSE(7, 30, 0), POSE_END};
static AnimateEntityFrame anim_glide[] = {
    POSE(1, 33, 0), POSE(2, 34, 0), POSE(3, 35, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_grab_approach[] = {
    POSE(6, 36, 0), POSE(6, 37, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_grab[] = {
    POSE(6, 38, 0), POSE(6, 39, 0), POSE(16, 40, 0), POSE_END};
static AnimateEntityFrame anim_grab_lift[] = {
    POSE(3, 41, 0), POSE(3, 42, 0), POSE(3, 43, 0), POSE(3, 44, 0),
    POSE(3, 45, 0), POSE(3, 46, 0), POSE(3, 47, 0), POSE_END};
static AnimateEntityFrame anim_grab_carry[] = {
    POSE(6, 41, 0), POSE(6, 42, 0), POSE(6, 43, 0), POSE(6, 44, 0),
    POSE(6, 45, 0), POSE(6, 46, 0), POSE(6, 47, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_takeoff[] = {
    POSE(2, 55, 0), POSE(2, 56, 0), POSE(2, 57, 0), POSE(2, 58, 0),
    POSE(2, 27, 0), POSE(2, 26, 0), POSE(1, 41, 0), POSE(5, 42, 0),
    POSE(5, 43, 0), POSE(1, 49, 0), POSE_END};
static AnimateEntityFrame anim_takeoff_end[] = {
    POSE(6, 50, 0), POSE(6, 51, 0), POSE(6, 52, 0), POSE(6, 53, 0),
    POSE(1, 6, 0),  POSE(1, 8, 0),  POSE(1, 9, 0),  POSE(1, 10, 0),
    POSE(1, 11, 0), POSE(1, 12, 0), POSE(2, 13, 0), POSE(4, 6, 0),
    POSE(4, 8, 0),  POSE(4, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0),
    POSE(3, 12, 0), POSE(4, 13, 0), POSE_END};
static AnimateEntityFrame anim_charge[] = {
    POSE(6, 54, 0), POSE(6, 55, 0), POSE(6, 56, 0), POSE(6, 57, 0),
    POSE(6, 58, 0), POSE(4, 59, 0), POSE(4, 60, 0), POSE(4, 61, 0),
    POSE(4, 62, 0), POSE(6, 63, 0), POSE(6, 64, 0), POSE(6, 65, 0),
    POSE(7, 66, 0), POSE(7, 67, 0), POSE(7, 68, 0), POSE_END};
static AnimateEntityFrame anim_idle[] = {
    POSE(10, 69, 0), POSE(10, 70, 0), POSE(10, 71, 0),
    POSE(10, 72, 0), POSE(10, 73, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_knockback[] = {
    POSE(5, 74, 0), POSE(4, 75, 0), POSE(4, 76, 0), POSE(4, 77, 0),
    POSE(4, 78, 0), POSE(4, 79, 0), POSE_END};
static AnimateEntityFrame anim_dive[] = {
    POSE(6, 81, 0), POSE(6, 82, 0), POSE(6, 83, 0), POSE(6, 84, 0), POSE_END};
static AnimateEntityFrame anim_dive_land[] = {
    POSE(6, 84, 0), POSE(6, 85, 0), POSE(7, 86, 0), POSE(9, 87, 0),
    POSE_LOOP(0)};
static AnimateEntityFrame anim_land[] = {
    POSE(2, 100, 0), POSE(3, 99, 0), POSE(4, 98, 0), POSE(4, 97, 0),
    POSE(5, 96, 0),  POSE(6, 95, 0), POSE(5, 94, 0), POSE(4, 93, 0),
    POSE(4, 92, 0),  POSE(2, 91, 0), POSE(4, 97, 0), POSE(10, 88, 0),
    POSE(15, 89, 0), POSE_END};
static AnimateEntityFrame anim_swoop_land[] = {
    POSE(3, 90, 0),  POSE(3, 91, 0),  POSE(3, 92, 0),  POSE(3, 93, 0),
    POSE(3, 94, 0),  POSE(4, 95, 0),  POSE(3, 96, 0),  POSE(2, 97, 0),
    POSE(2, 98, 0),  POSE(2, 99, 0),  POSE(2, 100, 0), POSE(3, 101, 0),
    POSE(5, 102, 0), POSE(8, 103, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_lay_eggs[] = {
    POSE(6, 69, 0), POSE(6, 70, 0),  POSE(6, 71, 0), POSE(6, 72, 0),
    POSE(6, 73, 0), POSE(8, 67, 0),  POSE(8, 68, 0), POSE(8, 49, 0),
    POSE(8, 77, 0), POSE(10, 78, 0), POSE(6, 91, 0), POSE(6, 92, 0),
    POSE(6, 93, 0), POSE(6, 94, 0),  POSE(6, 95, 0), POSE(6, 96, 0),
    POSE(6, 97, 0), POSE(6, 98, 0),  POSE(3, 69, 0), POSE(3, 70, 0),
    POSE_END};
AnimateEntityFrame anim_dead[] = {
    POSE(12, 110, 0), POSE(11, 111, 0), POSE(10, 112, 0), POSE(9, 113, 0),
    POSE(8, 114, 0),  POSE(7, 115, 0),  POSE(6, 116, 0),  POSE(5, 120, 0),
    POSE(5, 121, 0),  POSE(7, 122, 0),  POSE(8, 123, 0),  POSE(10, 124, 0),
    POSE(10, 125, 0), POSE(52, 126, 0), POSE_END};
static AnimateEntityFrame anim_dead_fade[] = {
    POSE(5, 54, 0), POSE(5, 55, 0), POSE(5, 56, 0), POSE(5, 57, 0),
    POSE(5, 58, 0), POSE(5, 59, 0), POSE(5, 60, 0), POSE(5, 61, 0),
    POSE(5, 60, 0), POSE(5, 59, 0), POSE_END};
static AnimateEntityFrame anim_egg_idle[] = {
    POSE(24, 104, 0), POSE(24, 105, 0), POSE(24, 106, 0), POSE_END};
static AnimateEntityFrame anim_egg_fly[] = {
    POSE(8, 107, 0), POSE(8, 108, 0), POSE(8, 109, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_fire_grow[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(2, 2, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_fire_fade[] = {
    POSE(2, 4, 0), POSE(2, 5, 0), POSE(2, 6, 0), POSE(2, 7, 0), POSE_END};
static AnimateEntityFrame anim_fire_spark[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(2, 2, 0), POSE(2, 3, 0),
    POSE(2, 4, 0), POSE(2, 5, 0), POSE(2, 6, 0), POSE(2, 7, 0), POSE_END};
static AnimateEntityFrame anim_feather_fall[] = {
    POSE(4, 127, 0), POSE(5, 128, 0), POSE(6, 129, 0), POSE(7, 130, 0),
    POSE(8, 131, 0), POSE(7, 132, 0), POSE(6, 133, 0), POSE(5, 134, 0),
    POSE(4, 135, 0), POSE(3, 136, 0), POSE(2, 137, 0), POSE(2, 138, 0),
    POSE_LOOP(0)};
static AnimateEntityFrame anim_feather_sway[] = {
    POSE(30, 139, 0), POSE(8, 140, 0), POSE(30, 141, 0), POSE(8, 140, 0),
    POSE_LOOP(0)};
static AnimateEntityFrame anim_unused[] = {
    POSE(2, 64, 0),   POSE(32, 15, 0),  POSE(15, 2, 0),   POSE(80, 32, 0),
    POSE(241, 15, 0), POSE(2, 80, 0),   POSE(32, 241, 0), POSE(15, 0, 0),
    POSE(2, 96, 0),   POSE(32, 241, 0), POSE(15, 1, 0),   POSE(96, 32, 0),
    POSE(15, 15, 0),  POSE(1, 112, 0),  POSE(32, 241, 0), POSE(15, 1, 0),
    POSE(112, 32, 0), POSE(15, 15, 0),  POSE_LOOP(0),     POSE_LOOP(0),
    POSE(2, 64, 0),   POSE(32, 15, 0),  POSE(15, 2, 0),   POSE(80, 32, 0),
    POSE(241, 15, 0), POSE(2, 80, 0),   POSE(32, 15, 0),  POSE(15, 2, 0),
    POSE(80, 32, 0),  POSE(241, 15, 0), POSE(2, 80, 0),   POSE(32, 15, 0),
    POSE(15, 2, 0),   POSE(96, 32, 0),  POSE(241, 15, 0), POSE(2, 96, 0),
    POSE(32, 15, 0),  POSE(15, 2, 0),   POSE(112, 32, 0), POSE(241, 15, 0),
    POSE(2, 112, 0),  POSE(32, 15, 0),  POSE(15, 255, 0), POSE_LOOP(0)};
static s16 sensors_floor[] = {0, 25, 0, 4, 12, -4, -24, 0};
static s16 sensors_egg[] = {0, 7, 0, 4, 8, -4, -16, 0};
static s16 sensors_feather[] = {0, 7, 0, 4, 8, -4, -16, 0};
static s16 collider_ground[] = {0, 64, 255, 0};
static s16 collider_front[] = {48, 28, 255, 0};

enum {
    STEP_INIT,
    STEP_IDLE,
    STEP_2,
    STEP_PREPARE_SPIT_FIRE,
    STEP_TAKEOFF,
    STEP_FLY = 6,
    STEP_RETURN_TO_GROUND = 8,
    STEP_10 = 10,
    STEP_12 = 12,
    STEP_RUN = 13,
    STEP_CHARGE = 16,
    STEP_GRAB = 18,
    STEP_LAY_EGGS = 20,
    STEP_22 = 22,
    STEP_HIT = 32,
    STEP_DEAD = 36,
    STEP_48 = 48,
    STEP_50 = 50,
    STEP_130 = 130,
};

static u8 attack_steps[] = {
    STEP_12,      STEP_TAKEOFF, STEP_12,      STEP_TAKEOFF,
    STEP_12,      STEP_12,      STEP_TAKEOFF, STEP_LAY_EGGS,
    STEP_TAKEOFF, STEP_12,      STEP_CHARGE,  STEP_RUN,
    STEP_RUN,     STEP_CHARGE,  STEP_RUN,     STEP_RUN};
s16 D_us_80180AFC[] = {22, 18, 6, 8, -10, 18, -26, 20};

static void SetHippogryphStep(u8 step) {
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->ext.hippogryph.unk7D = 0;
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
}

void func_us_801A19FC(u8 count, s16 posY) {
    Entity* entity;
    s32 i;

    for (i = 0; i < count; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            DestroyEntity(entity);
            MakeEntityFromId(E_ID(HIPPOGRYPH), g_CurrentEntity, entity);
            entity->flags =
                FLAG_DESTROY_IF_OUT_OF_CAMERA |
                FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_POS_CAMERA_LOCKED |
                FLAG_UNK_00200000 | FLAG_UNK_2000;
            entity->posX.i.hi += (Random() & 0x3F) - 0x20;
            entity->posY.i.hi += (Random() & 0x3F) - 0x20 + posY;
            entity->velocityY = -FIX(0.25);
            if (Random() & 1) {
                entity->zPriority++;
            }
            entity->step = STEP_48;
            entity->params = Random() & 1;
            if (entity->params) {
                entity->step = STEP_50;
                if (Random() & 1) {
                    entity->ext.hippogryph.unk8C = 0xD00;
                    entity->velocityX = -FIX(0.8125);
                } else {
                    entity->ext.hippogryph.unk8C = -0xD00;
                    entity->velocityX = FIX(0.8125);
                }
            }
            if (g_CurrentEntity->step == STEP_22) {
                if (g_CurrentEntity->facingLeft) {
                    g_CurrentEntity->velocityX += FIX(0.25);
                } else {
                    g_CurrentEntity->velocityX -= FIX(0.25);
                }
            }
        }
    }
}

bool CheckHippogryphFloorCollision(s16* sensors) {
    s32 posY;

    if (UnkCollisionFunc3(sensors) & 1) {
        return true;
    } else {
        posY = g_CurrentEntity->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (posY > 183) {
            g_CurrentEntity->posY.i.hi = 183 - g_Tilemap.scrollY.i.hi;
            g_CurrentEntity->velocityX = 0;
            g_CurrentEntity->velocityY = 0;
            return true;
        }
        return false;
    }
}

extern s32 D_us_80180B74;
extern EInit g_EInitHippogryph;

void EntityFireBreath(Entity* self);

void EntityHippogryph(Entity* self) {
    s32 primIndex;
    Pos tmp;
    Pos tmp2;
    Pos pos;
    Pos vel;
    Entity* entity;
    Entity* player;
    Primitive* prim;
    s32 x;
    s32 y;
    u8 count;
    s32 i;
    s32 dist;
    u8 angle;

    entity = &PLAYER;
    if (self->hitParams && (self->step & 1)) {
        if (self->facingLeft) {
            self->velocityX = -FIX(1.5);
        } else {
            self->velocityX = FIX(1.5);
        }
        self->velocityY = -FIX(4);
        SetHippogryphStep(STEP_HIT);
    }
    if ((self->flags & FLAG_DEAD) && self->step < 0x22) {
        self->hitboxState = 0;
        HIH(self->velocityX) = 0; // equivalent of i.hi = 0
        HIH(self->velocityY) = 0; // equivalent of i.hi = 0
        self->ext.hippogryph.flyTimer = 0;
        self->animCurFrame = 0x6E;
        if (self->ext.hippogryph.unk94 != NULL) {
            DestroyEntity(self->ext.hippogryph.unk94);
        }
        if (self->flags & FLAG_HAS_PRIMS) {
            primIndex = self->primIndex;
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }
        SetHippogryphStep(STEP_DEAD);
    }

    switch (self->step) {
    case STEP_INIT:
        InitializeEntity(g_EInitHippogryph);
        self->ext.hippogryph.zPriority = self->zPriority;
        self->zPriority = entity->zPriority + 1;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.hippogryph.unk7D = 1;
        break;
    case STEP_IDLE:
        self->hitboxState = 0;
        AnimateEntity(anim_idle, self);
        if (self->ext.hippogryph.unk7D && GetDistanceToPlayerX() < 128) {
            SetHippogryphStep(STEP_PREPARE_SPIT_FIRE);
            if (!D_us_801806DC) {
                g_api.TimeAttackController(
                    TIMEATTACK_EVENT_HYPPOGRYPH_DEFEAT, TIMEATTACK_SET_VISITED);
            }
            D_us_801806DC |= 1;
            self->hitboxState = 3;
            self->nextPart = self + 1;
            CreateEntityFromEntity(E_ID(UNK_23), self, self + 1);
        }
        break;
    case STEP_PREPARE_SPIT_FIRE:
        if (!AnimateEntity(anim_prepare_spit_fire, self)) {
            SetHippogryphStep(STEP_TAKEOFF);
        }
        break;
    case STEP_TAKEOFF:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_takeoff, self)) {
                self->animCurFrame = 0x31;
                self->velocityY = -FIX(5);
                self->ext.hippogryph.flyTimer = 4;
                self->ext.hippogryph.unk7D = 0;
                self->step_s++;
            }
            if (self->animCurFrame == 0x29 && !self->ext.hippogryph.unk7D) {
                func_us_801A19FC(4, 0);
                self->ext.hippogryph.unk7D = 1;
                if (self->facingLeft) {
                    self->velocityX = FIX(0.375);
                } else {
                    self->velocityX = -FIX(0.375);
                }
                self->posY.i.hi -= 4;
            }
            if (self->ext.hippogryph.unk7D) {
                MoveEntity();
                if (self->animCurFrame == 0x2A || self->animCurFrame == 0x2B) {
                    self->velocityY -= FIX(0.375);
                }
            }
            y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (y < 0x72) {
                self->animCurFrame = 0x31;
                self->velocityY = -FIX(4.5);
                self->ext.hippogryph.unk7D = 0;
                self->step_s = 2;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.1171875);
            if (!--self->ext.hippogryph.flyTimer) {
                self->pose = 0;
                self->ext.hippogryph.flyTimer = 0;
                self->step_s++;
            }
            y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (y < 0x72) {
                self->animCurFrame = 0x31;
                self->velocityY = -FIX(4.5);
                self->ext.hippogryph.unk7D = 0;
                self->step_s = 2;
            }
            break;

        case 2:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!AnimateEntity(anim_takeoff_end, self)) {
                SetHippogryphStep(STEP_FLY);
            }
            break;
        }
        break;
    case STEP_FLY:
        if (!self->step_s) {
            self->ext.hippogryph.flyTimer = 0x50;
            if (self->facingLeft) {
                self->velocityX = FIX(1.75);
            } else {
                self->velocityX = -FIX(1.75);
            }
            self->velocityY = 0;
            self->step_s++;
        }
        MoveEntity();
        AnimateEntity(anim_flap, self);
        if (!self->poseTimer && self->pose == 1) {
            PlaySfxPositional(SFX_HIPPOGRYPH_WING_FLAP);
        }
        if (self->animCurFrame == 6 || self->animCurFrame == 7) {
            self->velocityY -= FIX(0.15625);
        } else {
            self->velocityY += FIX(0.0546875);
        }
        if (!--self->ext.hippogryph.flyTimer) {
            x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (self->velocityX < 0) {
                x = 0x200 - x;
            }
            if (GetDistanceToPlayerX() > 80 && x < 0x90) {
                self->velocityX = 0;
                self->velocityY = 0;
                SetHippogryphStep(STEP_22);
            } else if (x < 0x180) {
                SetHippogryphStep(STEP_RETURN_TO_GROUND);
            } else {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                SetHippogryphStep(STEP_FLY);
            }
        }
        break;
    case STEP_RETURN_TO_GROUND:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(0.5);
            } else {
                self->velocityX = -FIX(0.5);
            }
            self->velocityY = FIX(3.5);
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(anim_dive, self)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            MoveEntity();
            y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (y > 0x88) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s = 2;
            }
            break;
        case 2:
            AnimateEntity(anim_dive_land, self);
            MoveEntity();
            if (CheckColliderOffsets(collider_ground, 0)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.hippogryph.unk7D = 0;
                self->step_s++;
            }
            break;
        case 3:
            if ((CheckHippogryphFloorCollision(sensors_floor) & 1) &&
                !self->ext.hippogryph.unk7D) {
                self->ext.hippogryph.unk7D = 1;
            }
            self->velocityY -= FIX(0.484375);
            if (self->velocityY <= FIX(0.5)) {
                self->velocityY = FIX(0.5);
            }
            if (!AnimateEntity(anim_land, self) && self->ext.hippogryph.unk7D) {
                SetHippogryphStep(STEP_10);
                self->ext.hippogryph.unk7D = 0;
            }
            break;
        }
        break;
    case STEP_10:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        count = Random() & 7;
        dist = GetDistanceToPlayerX();
        if (dist > 80) {
            count += 4;
        }
        if (dist > 128) {
            count += 4;
        }
        SetHippogryphStep(attack_steps[count]);
        break;
    case STEP_12:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_fire_breath, self)) {
                self->step_s++;
                self->ext.hippogryph.flyTimer = 0x40;
                PlaySfxPositional(SFX_HIPPOGRYPH_FIRE_ATTACK);
            }
            if (!self->poseTimer && self->pose == 4) {
                PlaySfxPositional(SFX_ELECTRICITY);
            }
            break;
        case 1:
            if (self->ext.hippogryph.flyTimer % 2) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(FIRE_BREATH), self, entity);
                    entity->pfnUpdate = EntityFireBreath;
                    entity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x1D;
                    } else {
                        entity->posX.i.hi -= 0x1D;
                    }
                    entity->posY.i.hi -= 2;
                    entity->params = self->ext.hippogryph.unk7D;
                }
                if (self->ext.hippogryph.unk7D) {
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                } else {
                    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                }
                if (entity != NULL) {
                    DestroyEntity(entity);
                    CreateEntityFromEntity(E_ID(FIRE_BREATH), self, entity);
                    entity->pfnUpdate = EntityFireBreath;
                    entity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x1D;
                    } else {
                        entity->posX.i.hi -= 0x1D;
                    }
                    entity->posY.i.hi -= 2;
                    entity->params = 2;
                    entity->params += self->ext.hippogryph.unk7D;
                }
                self->ext.hippogryph.unk7D ^= 1;
            }
            if (!--self->ext.hippogryph.flyTimer) {
                self->ext.hippogryph.unk7D = 0;
                SetHippogryphStep(STEP_10);
            }
            break;
        }
        break;
    case STEP_RUN:
        if (!self->ext.hippogryph.unk7D) {
            self->ext.hippogryph.unk7D = 1;
            self->ext.hippogryph.flyTimer = 0x80;
            if (self->facingLeft) {
                self->velocityX = FIX(1.25);
            } else {
                self->velocityX = -FIX(1.25);
            }
            self->velocityY = 0;
        }
        MoveEntity();
        AnimateEntity(anim_run, self);
        if (self->animCurFrame == 5) {
            if (!self->poseTimer) {
                PlaySfxPositional(SFX_STOMP_HARD_A);
            }
            if (self->facingLeft) {
                self->velocityX -= FIX(0.109375);
            } else {
                self->velocityX += FIX(0.109375);
            }
        }
        if (self->animCurFrame == 1) {
            if (self->facingLeft) {
                self->velocityX += FIX(0.109375);
            } else {
                self->velocityX -= FIX(0.109375);
            }
        }
        x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->facingLeft) {
            if (x > 0x180) {
                self->facingLeft = 0;
                self->velocityX = -FIX(1.25);
                self->pose = 0;
                self->poseTimer = 0;
            }
        } else if (x < 0x80) {
            self->facingLeft = 1;
            self->velocityX = FIX(1.25);
            self->pose = 0;
            self->poseTimer = 0;
        }
        if (!CheckColliderOffsets(collider_front, self->facingLeft)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetHippogryphStep(STEP_TAKEOFF);
        }
        if (!--self->ext.hippogryph.flyTimer) {
            SetHippogryphStep(STEP_10);
        }
        break;
    case STEP_CHARGE:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_charge, self)) {
                func_us_801A19FC(4, 0);
                self->ext.hippogryph.flyTimer = 0x40;
                if (self->facingLeft) {
                    self->velocityX = FIX(4.5);
                } else {
                    self->velocityX = -FIX(4.5);
                }
                self->velocityY = 0;
                self->pose = 0;
                self->poseTimer = 0;
                self->animCurFrame = 0x21;
                self->step_s++;
            }
            break;

        case 1:
            if (self->ext.hippogryph.flyTimer < 0x20) {
                AnimateEntity(anim_glide, self);
            }
            MoveEntity();
            self->velocityY -= FIX(1.0 / 16);
            y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (y < 0x48) {
                self->step_s++;
            }
            break;

        case 2:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetHippogryphStep(STEP_FLY);
            break;
        }
        break;
    case STEP_LAY_EGGS:
        if (!AnimateEntity(anim_lay_eggs, self)) {
            self->ext.hippogryph.unk7D = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetHippogryphStep(STEP_TAKEOFF);
        }
        if (self->animCurFrame == 0x4D && !self->ext.hippogryph.unk7D) {
            self->ext.hippogryph.unk7D = 1;
            count = (Random() & 1) + 2;
            for (i = 0; i < count; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(HIPPOGRYPH_EGG), self, entity);
                    entity->ext.hippogryphEgg.timer = (Random() & 0x1F) + 0xC0;
                    if (self->facingLeft) {
                        entity->posX.i.hi -= 0x10;
                        entity->velocityX = -i * FIX(0.5) + FIX(0.5);
                    } else {
                        entity->posX.i.hi += 0x10;
                        entity->velocityX = i * FIX(0.5) - FIX(0.5);
                    }
                }
            }
        }
        break;
    case STEP_GRAB:
        switch (self->step_s) {
        case 0:
            AnimateEntity(anim_grab_approach, self);
            MoveEntity();
            if (GetDistanceToPlayerY() < 80) {
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            if (!AnimateEntity(anim_grab, self)) {
                self->step_s++;
            }
            self->velocityY -= FIX(1.0 / 32);
            if (!g_Player.grabState) {
                x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                if (self->facingLeft) {
                    x = 0x200 - x;
                }
                if (x >= 0x80) {
                    player = &PLAYER;
                    x = player->posX.i.hi - self->posX.i.hi;
                    y = player->posY.i.hi - self->posY.i.hi;
                    if (y < 0) {
                        y = 0x80;
                    }
                    if (abs(x) < 0xC && y < 0x38 &&
                        !(g_Player.status &
                          (PLAYER_STATUS_UNK40000000 | PLAYER_STATUS_UNK800000 |
                           PLAYER_STATUS_UNK400000 | PLAYER_STATUS_DEAD |
                           PLAYER_STATUS_INVINCIBLE | PLAYER_STATUS_STONE |
                           PLAYER_STATUS_UNK40 | PLAYER_STATUS_UNK10 |
                           PLAYER_STATUS_MIST_FORM))) {
                        PlaySfxPositional(SFX_HIPPOGRYPH_SQUAWK);
                        g_Player.grabState = 1;
                        g_Player.grabDamage = 0x10;
                        g_Player.grabReactionEffect = 0;
                        self->posX.i.hi = player->posX.i.hi;
                        self->posY.i.hi = player->posY.i.hi - 0x20;
                    }
                }
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY -= FIX(0.375);
            if (!AnimateEntity(anim_grab_lift, self)) {
                self->ext.hippogryph.flyTimer = 0x40;
                self->step_s++;
                if (!g_Player.grabState) {
                    self->velocityY -= FIX(0.375);
                }
            }
            break;
        case 3:
            if (g_Player.grabState) {
                AnimateEntity(anim_grab_carry, self);
                if (!(--self->ext.hippogryph.flyTimer % 47)) {
                    func_us_801A19FC(8, -8);
                    g_Player.grabState = 3;
                    g_Player.grabDamage = 0x10;
                }
            } else {
                AnimateEntity(anim_flap, self);
                if (!self->poseTimer && self->pose == 1) {
                    PlaySfxPositional(SFX_HIPPOGRYPH_WING_FLAP);
                }
            }
            MoveEntity();
            y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (y < 0x48) {
                g_Player.grabState = 0;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                SetHippogryphStep(STEP_FLY);
            }
            break;
        }
        if (g_Player.grabState) {
            entity->posX.i.hi = self->posX.i.hi;
            entity->posY.i.hi = self->posY.i.hi + 0x20;
        }
        break;
    case STEP_22:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (!AnimateEntity(anim_hover, self)) {
                self->ext.hippogryph.unk7D++;
            }
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_HIPPOGRYPH_WING_FLAP);
            }
            MoveEntity();
            if (self->animCurFrame == 6 || self->animCurFrame == 7) {
                self->velocityY -= FIX(0.15625);
            } else {
                self->velocityY += FIX(1.0 / 16);
            }
            if (self->ext.hippogryph.unk7D > 1) {
                self->ext.hippogryph.unk7D = 0;
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
                if (self->facingLeft) {
                    self->velocityX = FIX(4);
                } else {
                    self->velocityX = -FIX(4);
                }
                self->velocityY = FIX(4.5);
            }
            break;
        case 1:
            MoveEntity();
            AnimateEntity(anim_glide, self);
            self->velocityY -= FIX(0.09375);
            if (self->velocityY <= FIX(0.5)) {
                self->velocityY = FIX(0.5);
            }
            if (CheckColliderOffsets(collider_ground, 0)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.hippogryph.unk7D = 0;
                self->step_s++;
            }
            break;
        case 2:
            self->velocityY -= FIX(0.21875);
            if (CheckHippogryphFloorCollision(sensors_floor) & 1) {
                self->ext.hippogryph.unk7D = 1;
            }
            if (self->facingLeft) {
                self->velocityX -= FIX(1.0 / 16);
            } else {
                self->velocityX += FIX(1.0 / 16);
            }
            if (self->animCurFrame == 0x5E) {
                func_us_801A19FC(2, -2);
            }
            if (!AnimateEntity(anim_swoop_land, self) &&
                self->ext.hippogryph.unk7D) {
                SetHippogryphStep(STEP_10);
            }
            break;
        }
        break;
    case STEP_HIT:
        AnimateEntity(anim_knockback, self);
        if (CheckHippogryphFloorCollision(sensors_floor) & 1) {
            self->animCurFrame = 0x50;
            SetHippogryphStep(STEP_10);
        }
        break;
    case STEP_DEAD:
        switch (self->step_s) {
        case 0:
            if (g_Player.grabState) {
                g_Player.grabState = 0;
            }
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_HYPPOGRYPH_DEFEAT, TIMEATTACK_SET_RECORD);
            g_BossMgrState |= BOSS_MGR_DEFEAT;
            self->velocityY = 0;
            x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (x < 0x38) {
                self->velocityX = FIX(0.5);
            }
            if (x < 0x1D8) {
                self->velocityX = -FIX(0.5);
            }
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.25);
            y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (y > 0x80) {
                self->step_s++;
            }
            break;
        case 2:
            if (CheckHippogryphFloorCollision(sensors_floor) & 1) {
                func_us_801A19FC(0x16, -0x20);
                self->step_s = 3;
            } else {
                y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
                if (y > 0xB7) {
                    func_us_801A19FC(0x16, -0x20);
                    self->posY.i.hi = 0xB7 - g_Tilemap.scrollY.i.hi;
                    self->velocityX = 0;
                    self->velocityY = 0;
                    self->step_s = 3;
                }
            }
            break;
        case 3:
            primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 2);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.hippogryph.prim = prim;
                while (prim != NULL) {
                    prim->r0 = 0x80;
                    prim->r1 = 0x40;
                    prim->g0 = 0x60;
                    prim->g1 = 0x20;
                    prim->b0 = 0x60;
                    prim->b1 = 0x20;
                    prim->x0 = prim->x1 = self->posX.i.hi;
                    prim->y0 = prim->y1 = self->posY.i.hi;
                    prim->priority = self->zPriority + 2;
                    prim->drawMode =
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                    prim = prim->next;
                }
                self->step_s++;
            } else {
                self->ext.hippogryph.prim = NULL;
                self->step_s = 5;
            }
            self->zPriority = self->ext.hippogryph.zPriority - 8;
            break;
        case 4:
            self->ext.hippogryph.flyTimer += 6;
            if (self->ext.hippogryph.flyTimer > 0x80) {
                i = -8;
            } else {
                i = 6;
            }
            prim = self->ext.hippogryph.prim;
            prim->x1 += i;
            prim = prim->next;
            prim->x1 -= i;
            if (self->ext.hippogryph.flyTimer > 0xF0) {
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                self->ext.hippogryph.flyTimer = 0;
                self->step_s++;
            }
            break;
        case 5:
            i = 0;
            primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0x6F);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.hippogryph.prim = prim;
                for (i = 0; i < 0x1F; i++) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = 0x60;
                    prim->g0 = 0x40;
                    prim->b0 = 0x40;
                    prim->r1 = 0x10;
                    prim->g1 = 8;
                    prim->b1 = 8;
                    prim->x0 = prim->x1 = self->posX.i.hi;
                    prim->y0 = prim->y1 = self->posY.i.hi;
                    tmp.x.val = death_ray_speeds[i];
                    prim->x2 = tmp.x.i.hi;
                    prim->x3 = tmp.x.i.lo;
                    prim->y2 = 0;
                    prim->y3 = 0;
                    prim->priority = self->zPriority + 2;
                    prim->drawMode =
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                    prim = prim->next;
                }
                self->ext.hippogryph.prim2 = prim;
                for (i = 0; i < 0x50; i++) {
                    prim->type = PRIM_TILE;
                    prim->r0 = 0x70;
                    prim->g0 = 0x70;
                    prim->b0 = 0x70;
                    prim->u0 = 2;
                    prim->v0 = 2;
                    prim->priority = self->zPriority + 2;
                    prim->drawMode =
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                    prim->x0 = self->posX.i.hi;
                    prim->y0 = self->posY.i.hi;
                    prim->x1 = 0;
                    prim->y1 = 0;
                    count = Random() & 7;
                    angle = Random() & 0xF;
                    dist =
                        (death_particle_speeds[count] * rsin(angle << 8)) >> 12;
                    vel.x.val = dist;
                    prim->x2 = vel.x.i.hi;
                    prim->x3 = vel.x.i.lo;
                    dist =
                        (death_particle_speeds[count] * rcos(angle << 8)) >> 12;
                    vel.y.val = dist;
                    prim->y2 = vel.y.i.hi;
                    prim->y3 = vel.y.i.lo;
                    prim->r1 = Random() & 0x17;
                    prim->r2 = 0;
                    prim = prim->next;
                }
                self->step_s++;
            } else {
                self->step_s = 8;
            }
            break;
        case 6:
            AnimateEntity(anim_dead_fade, self);
            prim = self->ext.hippogryph.prim2;
            for (i = 0; i < 0x50; i++) {
                if (prim->r1) {
                    prim->r1--;
                } else {
                    pos.x.i.hi = prim->x0;
                    pos.x.i.lo = prim->x1;
                    pos.y.i.hi = prim->y0;
                    pos.y.i.lo = prim->y1;
                    vel.x.i.hi = prim->x2;
                    vel.x.i.lo = prim->x3;
                    vel.y.i.hi = prim->y2;
                    vel.y.i.lo = prim->y3;
                    pos.x.val += vel.x.val;
                    pos.y.val += vel.y.val;
                    prim->x0 = pos.x.i.hi;
                    prim->x1 = pos.x.i.lo;
                    prim->y0 = pos.y.i.hi;
                    prim->y1 = pos.y.i.lo;
                    prim->r2++;
                    if (prim->r2 > 0x20) {
                        prim->u0 = prim->v0 = 1;
                    }
                    if (prim->r2 > 0x30) {
                        prim->u0 = prim->v0 = 0;
                    }
                }
                prim = prim->next;
            }
            prim = self->ext.hippogryph.prim;
            for (i = 0; i < 0x1F; i++) {
                tmp.x.i.hi = prim->x2;
                tmp.x.i.lo = prim->x3;
                tmp2.y.i.hi = prim->y2;
                tmp2.y.i.lo = prim->y3;
                if (self->ext.hippogryph.flyTimer < 0xC) {
                    tmp2.y.val += tmp.x.val;
                }
                prim->x1 =
                    prim->x0 +
                    ((tmp2.y.i.hi *
                      rcos((i << 7) + self->ext.hippogryph.flyTimer * 16)) >>
                     12);
                prim->y1 =
                    prim->y0 +
                    ((tmp2.y.i.hi *
                      rsin((i << 7) + self->ext.hippogryph.flyTimer * 16)) >>
                     12);
                prim->y2 = tmp2.y.i.hi;
                prim->y3 = tmp2.y.i.lo;
                prim = prim->next;
            }
            if (self->ext.hippogryph.flyTimer++ > 0x30) {
                self->blendMode = BLEND_ADD | BLEND_TRANSP;
                self->drawFlags |= ENTITY_OPACITY;
                self->opacity = 0x80;
                self->step_s++;
            }
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_GUARD_TINK);
            }
            break;
        case 7:
            prim = self->ext.hippogryph.prim2;
            for (i = 0; i < 0x50; i++) {
                if (prim->r1) {
                    prim->r1--;
                } else {
                    pos.x.i.hi = prim->x0;
                    pos.x.i.lo = prim->x1;
                    pos.y.i.hi = prim->y0;
                    pos.y.i.lo = prim->y1;
                    vel.x.i.hi = prim->x2;
                    vel.x.i.lo = prim->x3;
                    vel.y.i.hi = prim->y2;
                    vel.y.i.lo = prim->y3;
                    pos.x.val += vel.x.val;
                    pos.y.val += vel.y.val;
                    prim->x0 = pos.x.i.hi;
                    prim->x1 = pos.x.i.lo;
                    prim->y0 = pos.y.i.hi;
                    prim->y1 = pos.y.i.lo;
                    prim->r2++;
                    if (prim->r2 > 0x20) {
                        prim->u0 = prim->v0 = 1;
                    }
                    if (prim->r2 > 0x30) {
                        prim->u0 = prim->v0 = 0;
                    }
                }
                prim = prim->next;
            }
            prim = self->ext.hippogryph.prim;
            i = 0;
            for (i = 0; i < 0x1F; i++) {
                prim->r0 -= 2;
                prim->g0--;
                prim->b0--;
                tmp.x.i.hi = -prim->x2;
                tmp.x.i.lo = -prim->x3;
                tmp2.y.i.hi = prim->y2;
                tmp2.y.i.lo = prim->y3;
                if (self->ext.hippogryph.flyTimer < 0x14) {
                    tmp2.y.val += tmp.x.val;
                }
                prim->x1 =
                    prim->x0 +
                    ((tmp2.y.i.hi *
                      rcos((i << 7) + self->ext.hippogryph.flyTimer * 16)) >>
                     12);
                prim->y1 =
                    prim->y0 +
                    ((tmp2.y.i.hi *
                      rsin((i << 7) + self->ext.hippogryph.flyTimer * 16)) >>
                     12);
                prim->y2 = tmp2.y.i.hi;
                prim->y3 = tmp2.y.i.lo;
                prim = prim->next;
            }
            self->opacity -= 4;
            if (self->opacity > 0xE0) {
                self->opacity = 0;
            }
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_GUARD_TINK);
            }
            if (self->ext.hippogryph.flyTimer++ > 0x4D) {
                self->ext.hippogryph.flyTimer = 0;
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                self->step_s++;
            }
            break;
        case 8:
            x = 0x100 - g_Tilemap.scrollX.i.hi;
            y = 0x80 - g_Tilemap.scrollY.i.hi;
            player = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (player != NULL) {
                CreateEntityFromCurrentEntity(E_ID(LIFE_UP_SPAWN), player);
                player->posX.i.hi = x;
                player->posY.i.hi = y;
                player->params = 6;
                D_us_80180B74 = 0;
                CreateEntityFromCurrentEntity(E_ID(CUTSCENE), &g_Entities[200]);
                self->step_s++;
            }
            break;

        case 9:
            break;
        }
        break;
    case STEP_48:
        AnimateEntity(anim_feather_fall, self);
        self->velocityY -= FIX(0.21875);
        if (UnkCollisionFunc3(sensors_feather) & 1) {
            DestroyEntity(self);
        }
        break;
    case STEP_50:
        AnimateEntity(anim_feather_sway, self);
        self->velocityX += (s32)self->ext.hippogryph.unk8C;
        if (self->velocityX < -FIX(0.8125) || self->velocityX > FIX(0.8125)) {
            self->ext.hippogryph.unk8C = -self->ext.hippogryph.unk8C;
        }
        self->velocityY -= FIX(0.21875);
        if (UnkCollisionFunc3(sensors_feather) & 1) {
            DestroyEntity(self);
        }
        break;
    case STEP_130:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[0].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        break;
    }

    count = self->animCurFrame;
    if (count >= 14 && count < 25) {
        self->hitboxWidth = 6;
        self->hitboxHeight = 0x14;
        self->hitboxOffX = 8;
        self->hitboxOffY = -8;
    } else if (count >= 58 && count < 64) {
        self->hitboxWidth = 6;
        self->hitboxHeight = 0x14;
        self->hitboxOffX = 0;
        self->hitboxOffY = -8;
    } else {
        self->hitboxWidth = 0x14;
        self->hitboxHeight = 8;
        self->hitboxOffX = 0;
        self->hitboxOffY = -2;
    }
}

extern EInit g_EInitFireBreath;

void EntityFireBreath(Entity* self) {
    Entity* entity;

    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFireBreath);
        self->hitboxState = 0;
        self->animSet = 2;
        self->animCurFrame = 1;
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_OPACITY;
        self->drawFlags |= ENTITY_ROTATE;
        self->blendMode |= BLEND_TRANSP | BLEND_ADD;
        self->opacity = 0x80;
        self->rotate = ROT(315);
        self->scaleX = self->scaleY = 0x20;
        if (self->facingLeft) {
            self->velocityX = FIX(4.40625);
        } else {
            self->velocityX = -FIX(4.40625);
        }
        if (self->params) {
            self->velocityY = FIX(0.1875);
        } else {
            self->velocityY = -FIX(0.375);
        }
        if (self->params >= 2) {
            self->opacity = 0x7C;
            self->velocityY = 0;
            if (self->params == 3) {
                self->hitboxState = 1;
            }
        }
        break;

    case 1:
        AnimateEntity(anim_fire_grow, self);
        MoveEntity();
        self->velocityY -= FIX(0.078125);
        self->opacity -= 5;
        self->scaleX += 0x18;
        self->scaleY = self->scaleX;
        if (self->scaleX > 0xF0) {
            self->velocityX = self->velocityX / 4;
            self->pose = 0;
            self->poseTimer = 0;
            self->step++;
        }
        if (self->params == 3 && (Random() & 1)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromEntity(E_ID(UNK_26), self, entity);
                entity->facingLeft = self->facingLeft;
                entity->params = self->params;
                entity->scaleX = self->scaleX;
                entity->scaleY = self->scaleY;
            }
        }
        if (!self->params && (Random() & 7)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromEntity(E_ID(UNK_26), self, entity);
                entity->facingLeft = self->facingLeft;
                entity->params = self->params;
                entity->scaleX = self->scaleX;
                entity->scaleY = self->scaleY;
            }
        }
        break;

    case 2:
        MoveEntity();
        if (!AnimateEntity(anim_fire_fade, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitParticle;

void func_us_801A3E78(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_OPACITY;
        self->drawFlags |= ENTITY_ROTATE;
        self->blendMode |= BLEND_TRANSP | BLEND_ADD;
        self->opacity = 0x80;
        if (self->facingLeft) {
            self->velocityX = FIX(1);
        } else {
            self->velocityX = -FIX(1);
        }
        if (self->params) {
            self->velocityY = FIX(0.5);
            return;
        }
        self->velocityY = -FIX(1);
        return;

    case 1:
        MoveEntity();
        if (self->facingLeft) {
            self->velocityX -= FIX(0.125);
        } else {
            self->velocityX += FIX(0.125);
        }
        self->velocityY -= FIX(0.0625);
        if (self->params) {
            self->rotate -= ROT(5.625);
        } else {
            self->rotate += ROT(5.625);
        }
        self->scaleX -= 0xA;
        self->opacity -= 6;
        if (!AnimateEntity(anim_fire_spark, self)) {
            DestroyEntity(self);
        }
        return;
    }
}

extern EInit g_EInitHippogryphEgg;

void EntityHippogryphEgg(Entity* self) {
    Entity* entity;

    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            DestroyEntity(entity);
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHippogryphEgg);
        self->hitboxState = 2;
        self->drawFlags |= ENTITY_ROTATE;
        self->rotate = ((Random() & 3) << 9) - 0x300;
        self->ext.hippogryphEgg.rotateDir = 1;
        return;
    case 1:
        if (UnkCollisionFunc3(sensors_egg) & 1) {
            self->step++;
        }
    case 2:
        if (!self->ext.hippogryphEgg.timer) {
            if (AnimateEntity(anim_egg_idle, self)) {
                return;
            }
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 0;
            }
            self->facingLeft = GetSideToPlayer() & 1;
            self->drawFlags = ENTITY_DEFAULT;
            if (self->facingLeft) {
                self->velocityX = -FIX(2.5);
            } else {
                self->velocityX = FIX(2.5);
            }
            self->velocityY = -FIX(0.25);
            self->pose = 0;
            self->poseTimer = 0;
            self->hitboxState = 3;
            PlaySfxPositional(SFX_NO1_BIRD_CYCLE);
            self->step++;
            return;
        } else if (self->ext.hippogryphEgg.timer-- < 8) {
            self->rotate += self->ext.hippogryphEgg.rotateDir << 9;
            self->ext.hippogryphEgg.rotateDir =
                -self->ext.hippogryphEgg.rotateDir;
            return;
        }
        break;
    case 3:
        AnimateEntity(anim_egg_fly, self);
        MoveEntity();
        self->velocityY -= FIX(0.0390625);
        break;
    }
}

extern EInit g_EInitInteractable;

static u8 hitbox_frames[] = {
    0, 0, 0, 0, 0, 0, 1, 0, 3, 3, 3, 4, 0, 2, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 6, 6, 1, 1, 1, 6, 6, 6, 6, 6, 0, 0, 0, 1, 6, 6, 6, 6, 1,
    0, 3, 3, 4, 0, 1, 1, 3, 0, 1, 6, 2, 0, 0, 1, 1, 5, 6, 6, 6, 6,
    6, 6, 6, 6, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 6,
    6, 6, 6, 6, 1, 1, 1, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0};

void EntityHippogryphHitbox(Entity* self) {
    Entity* parent;
    u8 frame;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->hitPoints = 0x7FFE;
        self->hitboxState = 2;
        self->flags |= FLAG_SUPPRESS_STUN;
        self->attack = 0;
        self->attackElement = ELEMENT_NONE;
        self->parent = self - 1;
        self->nextPart = self - 1;
    }

    parent = self - 1;
    frame = parent->animCurFrame;
    if (frame > 0x67) {
        frame = 0;
    }

    frame = hitbox_frames[frame];
    switch (frame) {
    case 0:
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->hitboxWidth = 0;
        self->hitboxHeight = 0;
        break;
    case 1:
        self->hitboxOffX = 8;
        self->hitboxOffY = -24;
        self->hitboxWidth = 20;
        self->hitboxHeight = 18;
        break;
    case 2:
        self->hitboxOffX = 12;
        self->hitboxOffY = -8;
        self->hitboxWidth = 18;
        self->hitboxHeight = 8;
        break;
    case 3:
        self->hitboxOffX = -2;
        self->hitboxOffY = 24;
        self->hitboxWidth = 8;
        self->hitboxHeight = 18;
        break;
    case 4:
        self->hitboxOffX = 6;
        self->hitboxOffY = 10;
        self->hitboxWidth = 16;
        self->hitboxHeight = 10;
        break;
    case 5:
        self->hitboxOffX = 16;
        self->hitboxOffY = -32;
        self->hitboxWidth = 22;
        self->hitboxHeight = 22;
        break;
    case 6:
        self->hitboxOffX = 2;
        self->hitboxOffY = -32;
        self->hitboxWidth = 12;
        self->hitboxHeight = 24;
        break;
    }

    self->facingLeft = parent->facingLeft;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    if (parent->entityId != E_ID(HIPPOGRYPH)) {
        DestroyEntity(self);
    }
}

void EntityFireDamageHitbox(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitFireBreath);
        self->hitboxWidth = 24;
        self->hitboxHeight = 4;
        self->hitboxOffX = -48;
        self->hitboxOffY = -2;
    }
}
