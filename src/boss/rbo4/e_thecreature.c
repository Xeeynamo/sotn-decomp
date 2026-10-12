// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"

#ifdef VERSION_PSP
extern s32 E_ID(THE_CREATURE);
extern s32 E_ID(THE_CREATURE_HEAD);
extern s32 E_ID(UNK_18);
#endif

extern EInit g_EInitTheCreature;
extern EInit g_EInitTheCreatureHead;
extern s32 D_us_801807EC;

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

    if ((self->flags & FLAG_DEAD) && self->step != 6) {
        SetStep(6);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTheCreature);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID(THE_CREATURE_HEAD), entity);
        SetStep(1);
    case 1:
        AnimateEntity(anim_idle, self);
        self->hitboxState = 0;
        if (D_us_801807EC & 1) {
            self->hitboxState = 3;
            SetStep(2);
        }
        break;
    case 2:
        if (!self->step_s) {
            self->ext.theCreature.timer = 0x40;
            self->step_s++;
        }
        AnimateEntity(anim_walk, self);
        collision = UnkCollisionFunc2(sensors_walk);
        if (collision & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        if (GetDistanceToPlayerX() < 104) {
            self->ext.theCreature.unk84 = 1;
        }
        if (GetDistanceToPlayerX() > 128) {
            self->ext.theCreature.unk84 = 0;
        }
        if (self->facingLeft ^ self->ext.theCreature.unk84) {
            self->velocityX = FIX(-0.5);
        } else {
            self->velocityX = FIX(0.5);
        }
        if (!--self->ext.theCreature.timer) {
            if (GetDistanceToPlayerX() < 80) {
                SetStep(3);
                if (collision & 0xE0) {
                    SetStep(4);
                }
            } else {
                SetStep(4);
            }
        }
        collision = GetSideToPlayer() & 1;
        if (self->facingLeft != collision) {
            SetStep(5);
        }
        break;
    case 5:
        if (!AnimateEntity(anim_turn, self)) {
            SetStep(2);
        }
        if (!self->poseTimer && self->pose == 2) {
            self->facingLeft ^= 1;
        }
        break;
    case 3:
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
            SetStep(2);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_curl, self)) {
                self->step_s++;
            }
            break;
        case 1:
            self->animCurFrame = 0x1E;
            self->drawFlags = ENTITY_ROTATE;
            self->rotate = 0;
            self->ext.theCreature.timer = 0x200;
            self->step_s++;
        case 2:
            if (self->facingLeft) {
                self->velocityX = FIX(-3);
            } else {
                self->velocityX = FIX(3);
            }
            self->rotate += 0xC0;
            collision = UnkCollisionFunc2(sensors_roll);
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_STONE_MOVE_B);
            }
            if (collision & 0x80) {
                self->velocityX = 0;
                self->velocityY = FIX(-4);
                PlaySfxPositional(SFX_SHAFT_ORB_BOUNCE);
                self->step_s++;
            }
            if (self->ext.theCreature.timer) {
                self->ext.theCreature.timer--;
            } else {
                posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                if (posX > 0xC0 && posX < 0x140) {
                    self->ext.theCreature.timer = 0x30;
                    SetSubStep(4);
                }
            }
            break;
        case 3:
            self->rotate += 0x100;
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                PlaySfxPositional(SFX_EXPLODE_A);
                self->velocityY = -self->velocityY;
                self->velocityY -= self->velocityY >> 1;
                if (abs(self->velocityY) < FIX(0.5)) {
                    self->facingLeft ^= 1;
                    self->step_s--;
                }
            }
            break;
        case 4:
            self->rotate -= 0x100;
            self->velocityX -= self->velocityX >> 4;
            collision = UnkCollisionFunc2(sensors_roll);
            if (!--self->ext.theCreature.timer) {
                self->drawFlags = ENTITY_DEFAULT;
                self->step_s++;
            }
            break;
        case 5:
            if (!AnimateEntity(anim_uncurl, self)) {
                SetStep(2);
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            D_us_801807EC |= 2;
            self->hitboxState = 0;
            if (self->rotate) {
                self->rotate = 0;
            }
            self->animCurFrame = 1;
            PlaySfxPositional(SFX_THE_CREATURE_DEATH);
            self->step_s++;
            break;
        case 1:
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(anim_death, self)) {
                PlaySfxPositional(SFX_THE_CREATURE_HEAD_FALL);
                entity = self + 1;
                entity->ext.theCreature.unk85 = 1;
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(anim_burn, self)) {
                self->ext.theCreature.timer = 0x50;
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
                self->step_s++;
            }
            break;
        case 4:
            entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_18), self, entity);
                entity->params = 0;
                entity->zPriority = self->zPriority + 2;
                entity->posX.i.hi += (Random() & 0x1F) - 0x10;
                entity->posY.i.hi += 0x1C;
            }
            entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_18), self, entity);
                entity->params = 2;
                entity->zPriority = self->zPriority + 2;
                entity->posX.i.hi += (Random() & 0x1F) - 0x10;
                entity->posY.i.hi += 0x1C;
            }
            if (!--self->ext.theCreature.timer) {
                D_us_801807EC |= 4;
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 5:
            break;
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
    }
    hitbox = hitbox_data[0];
    hitbox += hitbox_frames[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}

void EntityTheCreatureHead(Entity* self) {
    Entity* entity;
    s8* hitbox;
    s32 frame;

    FntPrint("step %x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTheCreatureHead);
    case 1:
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
        if (self->ext.theCreature.unk85) {
            SetStep(2);
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
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
        case 1:
            self->animCurFrame = 26;
            self->rotate += 0x80;
            if (UnkCollisionFunc3(sensors_head) & 1) {
                self->ext.theCreature.timer = 0x30;
                self->step_s++;
            }
            break;
        case 2:
            if (!(self->ext.theCreature.timer & 0xF)) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_B);
            }
            if (self->ext.theCreature.timer & 1) {
                entity = AllocEntity(&g_Entities[192], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_18), self, entity);
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
