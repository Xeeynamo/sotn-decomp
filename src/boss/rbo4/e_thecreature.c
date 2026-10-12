// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"

extern EInit g_EInitTheCreature;
extern EInit g_EInitTheCreatureHead;
extern s32 g_BossMgrState;

enum TheCreatureSteps {
    THE_CREATURE_INIT,
    THE_CREATURE_IDLE,
    THE_CREATURE_WALK,
    THE_CREATURE_STOMP,
    THE_CREATURE_ROLL,
    THE_CREATURE_TURN,
    THE_CREATURE_DEATH,
    THE_CREATURE_DEBUG = 255,
};

enum TheCreatureRollSubsteps {
    THE_CREATURE_ROLL_CURL,
    THE_CREATURE_ROLL_INIT,
    THE_CREATURE_ROLL_MOVE,
    THE_CREATURE_ROLL_BOUNCE,
    THE_CREATURE_ROLL_STOP,
    THE_CREATURE_ROLL_UNCURL,
};

enum TheCreatureDeathSubsteps {
    THE_CREATURE_DEATH_INIT,
    THE_CREATURE_DEATH_LAND,
    THE_CREATURE_DEATH_DROP_HEAD,
    THE_CREATURE_DEATH_BURN,
    THE_CREATURE_DEATH_FLAMES,
    THE_CREATURE_DEATH_END,
};

enum TheCreatureHeadSteps {
    THE_CREATURE_HEAD_INIT,
    THE_CREATURE_HEAD_ATTACHED,
    THE_CREATURE_HEAD_FALL,
};

enum TheCreatureHeadFallSubsteps {
    THE_CREATURE_HEAD_FALL_INIT,
    THE_CREATURE_HEAD_FALL_DROP,
    THE_CREATURE_HEAD_FALL_BURN,
};

static s16 sensors_walk[] = {0, 23, 32, 0};
static s16 sensors_unused[][2] = {{0, 23}, {0, 4}, {8, -4}, {-16, 0}};
static s16 sensors_roll[] = {0, 23, 4, 0};
static s16 sensors_ground[][2] = {{0, 23}, {0, 4}, {4, -4}, {-8, 0}};
static s16 sensors_head[][2] = {{0, 12}, {0, 4}, {4, -4}, {-8, 0}};
static AnimateEntityFrame anim_idle[] = {
    POSE(6, 1, 0), POSE(6, 2, 0), POSE(6, 3, 0), POSE(6, 4, 0),
    POSE(6, 3, 0), POSE(6, 2, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_walk[] = {
    POSE(6, 1, 0), POSE(6, 5, 0), POSE(6, 6, 0), POSE(6, 7, 0),
    POSE(6, 6, 0), POSE(6, 5, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_hammer[] = {
    POSE(6, 8, 0),  POSE(6, 9, 0),  POSE(6, 10, 0), POSE(6, 11, 0),
    POSE(6, 12, 0), POSE(6, 13, 0), POSE(6, 14, 0), POSE(6, 13, 0),
    POSE(6, 12, 0), POSE(6, 13, 0), POSE(6, 14, 0), POSE(6, 13, 0),
    POSE(6, 12, 0), POSE(2, 15, 0), POSE(2, 16, 0), POSE(2, 17, 0),
    POSE(1, 18, 0), POSE_END};
static AnimateEntityFrame anim_burn[] = {
    POSE(8, 21, 0), POSE_END,        POSE(8, 22, 0), POSE(8, 23, 0),
    POSE(8, 24, 0), POSE(64, 25, 0), POSE_END};
static AnimateEntityFrame anim_curl[] = {
    POSE(8, 27, 0), POSE(8, 28, 0), POSE(8, 29, 0), POSE_END};
static AnimateEntityFrame anim_uncurl[] = {
    POSE(8, 29, 0), POSE(8, 28, 0), POSE(8, 27, 0), POSE_END};
static AnimateEntityFrame anim_turn[] = {
    POSE(8, 19, 0), POSE(8, 20, 0), POSE(8, 20, 0), POSE(8, 19, 0), POSE_END};
static AnimateEntityFrame anim_death[] = {
    POSE(8, 7, 0), POSE(8, 8, 0), POSE(8, 9, 0), POSE_END};
static s8 hitbox_data[][4] = {
    {0, 0, 0, 0},       {-13, -17, 23, 38}, {-82, -96, 0, 0}, {-14, -21, 0, 0},
    {-11, -11, 21, 33}, {-10, -8, 20, 30},  {3, -1, 21, 21},
};
static u8 hitbox_frames[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 1, 4, 5, 6, 0,
};
static s8 head_hitbox_data[][4] = {
    {0, 0, 0, 0},      {-82, -96, 0, 0}, {-24, -73, 36, 22}, {-6, -77, 37, 17},
    {28, -34, 17, 48}, {31, 2, 13, 21},  {-14, -21, 0, 0},   {3, -1, 25, 25},
};
static u8 head_hitbox_frames[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
    3, 4, 5, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 7, 0,
};

void EntityTheCreature(Entity* self) {
    Entity* entity;
    s8* hitbox;
    s32 collision;
    s32 posX;

    if ((self->flags & FLAG_DEAD) && self->step != THE_CREATURE_DEATH) {
        SetStep(THE_CREATURE_DEATH);
    }
    switch (self->step) {
    case THE_CREATURE_INIT:
        InitializeEntity(g_EInitTheCreature);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID(THE_CREATURE_HEAD), entity);
        SetStep(THE_CREATURE_IDLE);
    case THE_CREATURE_IDLE:
        AnimateEntity(anim_idle, self);
        self->hitboxState = 0;
        if (g_BossMgrState & BOSS_MGR_FIGHT_ON) {
            self->hitboxState = 3;
            SetStep(THE_CREATURE_WALK);
        }
        break;
    case THE_CREATURE_WALK:
        if (!self->step_s) {
            self->ext.theCreature.timer = 0x40;
            self->step_s++;
        }
        AnimateEntity(anim_walk, self);
        collision = UnkCollisionFunc2(sensors_walk);
        // blocked by a wall or a slope
        if (collision & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        // keep 104 to 128 pixels away from the player: back off when closer,
        // walk forward again when farther
        if (GetDistanceToPlayerX() < 104) {
            self->ext.theCreature.backOff = 1;
        }
        if (GetDistanceToPlayerX() > 128) {
            self->ext.theCreature.backOff = 0;
        }
        if (self->facingLeft ^ self->ext.theCreature.backOff) {
            self->velocityX = FIX(-0.5);
        } else {
            self->velocityX = FIX(0.5);
        }
        // every 64 frames attack: stomp with the hammer when the player is
        // close, otherwise roll towards them. It also rolls when close but
        // stuck against a wall or at the edge of a ledge.
        if (!--self->ext.theCreature.timer) {
            if (GetDistanceToPlayerX() < 80) {
                SetStep(THE_CREATURE_STOMP);
                if (collision & 0xE0) {
                    SetStep(THE_CREATURE_ROLL);
                }
            } else {
                SetStep(THE_CREATURE_ROLL);
            }
        }
        collision = GetSideToPlayer() & 1;
        // the player went behind
        if (self->facingLeft != collision) {
            SetStep(THE_CREATURE_TURN);
        }
        break;
    case THE_CREATURE_TURN:
        if (!AnimateEntity(anim_turn, self)) {
            SetStep(THE_CREATURE_WALK);
        }
        if (!self->poseTimer && self->pose == 2) {
            self->facingLeft ^= 1;
        }
        break;
    case THE_CREATURE_STOMP:
        if (!self->step_s) {
            if (!AnimateEntity(anim_hammer, self)) {
                g_api.ShakeCamera(1);
                PlaySfxPositional(SFX_THE_CREATURE_HAMMER);
                self->ext.theCreature.timer = 0x20;
                self->step_s++;
            }
            if (!self->poseTimer && self->pose == 4) {
                PlaySfxPositional(SFX_THE_CREATURE_ATTACK);
            }
        } else if (!--self->ext.theCreature.timer) {
            SetStep(THE_CREATURE_WALK);
        }
        break;
    case THE_CREATURE_ROLL:
        switch (self->step_s) {
        case THE_CREATURE_ROLL_CURL:
            if (!AnimateEntity(anim_curl, self)) {
                self->step_s++;
            }
            break;
        case THE_CREATURE_ROLL_INIT:
            self->animCurFrame = 0x1E;
            self->drawFlags = ENTITY_ROTATE;
            self->rotate = 0;
            self->ext.theCreature.timer = 0x200;
            self->step_s++;
        case THE_CREATURE_ROLL_MOVE:
            if (self->facingLeft) {
                self->velocityX = FIX(-3);
            } else {
                self->velocityX = FIX(3);
            }
            self->rotate += ROT(16.875);
            collision = UnkCollisionFunc2(sensors_roll);
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_STONE_MOVE_B);
            }
            // hit a wall or rolled off a ledge: jump up and bounce
            if (collision & 0x80) {
                self->velocityX = 0;
                self->velocityY = FIX(-4);
                PlaySfxPositional(SFX_SHAFT_ORB_BOUNCE);
                self->step_s++;
            }
            // after 512 frames, stop once it is in the middle of the arena
            if (self->ext.theCreature.timer) {
                self->ext.theCreature.timer--;
            } else {
                posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                if (posX > 0xC0 && posX < 0x140) {
                    self->ext.theCreature.timer = 0x30;
                    SetSubStep(THE_CREATURE_ROLL_STOP);
                }
            }
            break;
        case THE_CREATURE_ROLL_BOUNCE:
            self->rotate += ROT(22.5);
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                PlaySfxPositional(SFX_EXPLODE_A);
                self->velocityY = -self->velocityY;
                self->velocityY -= self->velocityY >> 1;
                // every landing halves the speed; when slow enough turn around
                // and roll back
                if (abs(self->velocityY) < FIX(0.5)) {
                    self->facingLeft ^= 1;
                    self->step_s--;
                }
            }
            break;
        case THE_CREATURE_ROLL_STOP:
            self->rotate -= ROT(22.5);
            self->velocityX -= self->velocityX >> 4;
            collision = UnkCollisionFunc2(sensors_roll);
            if (!--self->ext.theCreature.timer) {
                self->drawFlags = ENTITY_DEFAULT;
                self->step_s++;
            }
            break;
        case THE_CREATURE_ROLL_UNCURL:
            if (!AnimateEntity(anim_uncurl, self)) {
                SetStep(THE_CREATURE_WALK);
            }
            break;
        }
        break;
    case THE_CREATURE_DEATH:
        switch (self->step_s) {
        case THE_CREATURE_DEATH_INIT:
            g_BossMgrState |= BOSS_MGR_DEFEAT;
            self->hitboxState = 0;
            if (self->rotate) {
                self->rotate = 0;
            }
            self->animCurFrame = 1;
            PlaySfxPositional(SFX_THE_CREATURE_DEATH);
            self->step_s++;
            break;
        case THE_CREATURE_DEATH_LAND:
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                self->step_s++;
            }
            break;
        case THE_CREATURE_DEATH_DROP_HEAD:
            if (!AnimateEntity(anim_death, self)) {
                PlaySfxPositional(SFX_THE_CREATURE_HEAD_FALL);
                entity = self + 1;
                entity->ext.theCreature.detach = 1;
                self->step_s++;
            }
            break;
        case THE_CREATURE_DEATH_BURN:
            if (!AnimateEntity(anim_burn, self)) {
                self->ext.theCreature.timer = 0x50;
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
                self->step_s++;
            }
            break;
        case THE_CREATURE_DEATH_FLAMES:
            entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(THE_CREATURE_FLAMES), self, entity);
                entity->params = 0;
                entity->zPriority = self->zPriority + 2;
                entity->posX.i.hi += (Random() & 0x1F) - 0x10;
                entity->posY.i.hi += 0x1C;
            }
            entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(THE_CREATURE_FLAMES), self, entity);
                entity->params = 2;
                entity->zPriority = self->zPriority + 2;
                entity->posX.i.hi += (Random() & 0x1F) - 0x10;
                entity->posY.i.hi += 0x1C;
            }
            if (!--self->ext.theCreature.timer) {
                g_BossMgrState |= BOSS_MGR_TERMINATED;
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case THE_CREATURE_DEATH_END:
            break;
        }
        break;
    case THE_CREATURE_DEBUG:
#include "../../st/pad2_anim_debug.h"
    }
    hitbox = hitbox_data[0];
    hitbox += hitbox_frames[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}

// The head is an invisible hitbox that follows the body and covers the hammer.
// When the body dies it detaches, falls and burns.
void EntityTheCreatureHead(Entity* self) {
    Entity* entity;
    s8* hitbox;
    s32 frame;

    FntPrint("step %x\n", self->step);
    switch (self->step) {
    case THE_CREATURE_HEAD_INIT:
        InitializeEntity(g_EInitTheCreatureHead);
    case THE_CREATURE_HEAD_ATTACHED:
        entity = self - 1;
        frame = entity->animCurFrame;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->facingLeft = entity->facingLeft;
        frame = entity->animCurFrame;
        hitbox = head_hitbox_data[0];
        hitbox += head_hitbox_frames[frame] * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (self->ext.theCreature.detach) {
            SetStep(THE_CREATURE_HEAD_FALL);
        }
        break;
    case THE_CREATURE_HEAD_FALL:
        switch (self->step_s) {
        case THE_CREATURE_HEAD_FALL_INIT:
            entity = self - 1;
            self->posX.i.hi = entity->posX.i.hi;
            self->posY.i.hi = entity->posY.i.hi;
            self->facingLeft = entity->facingLeft;
            self->zPriority = entity->zPriority + 1;
            self->hitboxState = 0;
            self->animCurFrame = 26;
            if (self->facingLeft) {
                self->posX.i.hi += 4;
            } else {
                self->posX.i.hi -= 4;
            }
            self->posY.i.hi -= 39;
            self->drawFlags = ENTITY_ROTATE;
            self->step_s++;
        case THE_CREATURE_HEAD_FALL_DROP:
            self->animCurFrame = 26;
            self->rotate += ROT(11.25);
            if (UnkCollisionFunc3(sensors_head) & 1) {
                self->ext.theCreature.timer = 0x30;
                self->step_s++;
            }
            break;
        case THE_CREATURE_HEAD_FALL_BURN:
            if (!(self->ext.theCreature.timer & 0xF)) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_B);
            }
            if (self->ext.theCreature.timer & 1) {
                entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(THE_CREATURE_FLAMES), self, entity);
                    entity->params = 1;
                    entity->zPriority = self->zPriority + 1;
                    entity->posX.i.hi += (Random() & 7) - 4;
                    entity->posY.i.hi += (Random() & 7) - 4;
                }
            }
            if (!--self->ext.theCreature.timer) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        }
        break;
    }
    entity = self - 1;
    if (entity->entityId != E_ID(THE_CREATURE)) {
        DestroyEntity(self);
    }
}
