// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

#define VASE self + 1
#define BEAKER self + 2
#define WALKING_TABLE self + 3

static s16 sensors_special[] = {0, 17, 8, 0};
static s16 sensors_ground[][2] = {{0, 16}, {0, 4}, {8, -4}, {-16, 0}};
extern u16 sensors_ground_components[][2] = {{0, 4}, {0, 4}, {4, -4}, {-8, 0}};
static u8 anim_walk[] = {
    0x02, 0x05, 0x03, 0x06, 0x04, 0x07, 0x05, 0x08, 0x06, 0x09, 0x05, 0x08,
    0x04, 0x07, 0x03, 0x06, 0x02, 0x05, 0x03, 0x04, 0x04, 0x03, 0x05, 0x02,
    0x06, 0x01, 0x05, 0x02, 0x04, 0x03, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00};

typedef enum {
    /* 0 */ OUIJA_TABLE_INIT,
    /* 1 */ OUIJA_TABLE_INIT_SUBENTITIES,
    /* 2 */ OUIJA_TABLE_COME_ALIVE,
    /* 3 */ OUIJA_TABLE_ATTACK,
    /* 4 */ OUIJA_TABLE_UNUSED,
    /* 255 */ OUIJA_TABLE_DEBUG = 255,
} OuijaTableSteps;

typedef enum {
    /* 0 */ OUIJA_COMPONENT_INIT,
    /* 1 */ OUIJA_COMPONENT_CHECK_SPAWN,
    /* 2 */ OUIJA_COMPONENT_INIT_POS,
    /* 3 */ OUIJA_COMPONENT_CIRCLE_TABLE,
    /* 4 */ OUIJA_COMPONENT_SEEK_ATTACK,
    /* 8 */ OUIJA_COMPONENT_DEATH = 8,
    /* 16 */ OUIJA_COMPONENT_NOOP = 16
} OuijaTableComponentSteps;

typedef enum {
    /* 0 */ OUIJA_COMPONENT_BEGIN_DEATH,
    /* 1 */ OUIJA_COMPONENT_FALL_TO_FLOOR,
    /* 2 */ OUIJA_COMPONENT_DIE_IN_FLAMES
} OuijaTableComponentDeathSubSteps;

// Main Ouija Table entity
void EntityOuijaTable(Entity* self) {
    Entity* otherEntity;

    if (self->flags & FLAG_DEAD) {
        otherEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (otherEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, otherEntity);
            otherEntity->params = 1;
        }
        PlaySfxPositional(SFX_STUTTER_FIREBALL);
        // Destroy the spinning objects on the table
        otherEntity = VASE;
        otherEntity->flags |= FLAG_UNK_2000;

        otherEntity = BEAKER;
        otherEntity->flags |= FLAG_UNK_2000;
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case OUIJA_TABLE_INIT:
        InitializeEntity(g_EInitOuijaTable);
        self->animCurFrame = 5;
        self->hitboxOffY = 2;
        return;
    case OUIJA_TABLE_INIT_SUBENTITIES:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            // Spawn objects on the table
            otherEntity = VASE;
            CreateEntityFromEntity(E_OUIJA_TABLE_COMPONENT, self, otherEntity);
            otherEntity->params = 0;
            otherEntity->ext.ouijaTableContents.parent = self;
            otherEntity->posX.i.hi -= 4;
            otherEntity->posY.i.hi -= 16;

            otherEntity = BEAKER;
            CreateEntityFromEntity(E_OUIJA_TABLE_COMPONENT, self, otherEntity);
            otherEntity->params = 1;
            otherEntity->ext.ouijaTableContents.parent = self;
            otherEntity->posX.i.hi += 2;
            otherEntity->posY.i.hi -= 20;

            otherEntity = WALKING_TABLE;
            CreateEntityFromEntity(E_OUIJA_TABLE_COMPONENT, self, otherEntity);
            otherEntity->params = 2;
            otherEntity->ext.ouijaTableContents.parent = self;

            if (self->params) {
                otherEntity->posX.i.hi += 24;
                otherEntity->facingLeft = 1;
            } else {
                otherEntity->posX.i.hi -= 24;
            }
#ifndef VERSION_PSP
            // Looks like a coding error
            otherEntity->posY.i.hi = otherEntity->posY.i.hi;
#endif
            self->step++;
        }
        break;
    case OUIJA_TABLE_COME_ALIVE:
        // When player approaches, spring to life
        if ((GetDistanceToPlayerX() < 80) && (GetDistanceToPlayerY() < 64)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            otherEntity = BEAKER;
            otherEntity->ext.ouijaTableContents.spawned = true;

            otherEntity = VASE;
            otherEntity->ext.ouijaTableContents.spawned = true;
            SetStep(3);
        }
        break;
    case OUIJA_TABLE_ATTACK:
        if (!self->step_s) {
            self->ext.ouijaTable.attackTimer = 128;
            self->step_s += 1;
        }
        if (AnimateEntity(anim_walk, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        UnkCollisionFunc2(sensors_special);

        if (self->facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        if (!(--self->ext.ouijaTable.attackTimer)) {
            self->ext.ouijaTable.attackTimer = 192;
            // Throw out one of the objects on the table
            if (self->ext.ouijaTable.unk90 != 0) {
                otherEntity = VASE;
            } else {
                otherEntity = BEAKER;
            }
            otherEntity->ext.ouijaTableContents.isThrown = true;
            // Alternate between throwing vase and beaker
            self->ext.ouijaTable.unk90 ^= 1;
        }
        break;
    case OUIJA_TABLE_UNUSED:
        break;
    case OUIJA_TABLE_DEBUG:
#include "../pad2_anim_debug.h"
    }
}

// Ouija table components (beaker, vase, walking table)
void EntityOuijaTableComponent(Entity* self) {
    Entity* otherEntity;
    s32 posX, posY;
    s32 hitFlags;
    s16 angle;

    if (self->step < OUIJA_COMPONENT_DEATH) {
        otherEntity = self->ext.ouijaTableContents.parent;
        if (otherEntity->entityId != E_OUIJA_TABLE) {
            SetStep(OUIJA_COMPONENT_DEATH);
        }
    }

    switch (self->step) {
    case OUIJA_COMPONENT_INIT:
        InitializeEntity(g_EInitOuijaTableComponent);
        switch (self->params) {
        // Vase
        case 0:
            self->animCurFrame = 10;
            break;

        // Beaker
        case 1:
            self->animCurFrame = 12;
            break;

        // Walking table
        case 2:
            self->animCurFrame = 14;
            self->hitboxState = 0;
            self->step = OUIJA_COMPONENT_NOOP;
            break;

        // Unknown? Doesn't seem like this param is used
        case 3:
            self->animCurFrame = 15;
            self->hitboxState = 0;
            self->step = OUIJA_COMPONENT_NOOP;
            break;
        }
        break;

    case OUIJA_COMPONENT_CHECK_SPAWN:
        if (self->ext.ouijaTableContents.spawned) {
            self->step = OUIJA_COMPONENT_INIT_POS;
        }
        break;

    case OUIJA_COMPONENT_INIT_POS:
        MoveEntity();
        otherEntity = self->ext.ouijaTableContents.parent;
        posX = otherEntity->posX.i.hi;
        posY = otherEntity->posY.i.hi - 32;
        posY += ((rcos(self->ext.ouijaTableContents.unk8E) * 8) >> 12);
        posX += ((rsin(self->ext.ouijaTableContents.unk8E) * 18) >> 12);
        posX -= self->posX.i.hi;
        posY -= self->posY.i.hi;
        angle = ratan2(posY, posX);
        self->velocityX = (rcos(angle) * FIX(1.5)) >> 12;
        self->velocityY = (rsin(angle) * FIX(1.5)) >> 12;
        // Beaker and vase move in opposite directions
        if (self->params) {
            self->ext.ouijaTableContents.unk8E += 48;
        } else {
            self->ext.ouijaTableContents.unk8E -= 48;
        }

        if (abs(posX) < 2 && abs(posY) < 2) {
            self->step = OUIJA_COMPONENT_CIRCLE_TABLE;
        }
        break;

    case OUIJA_COMPONENT_CIRCLE_TABLE:
        // Components fly in a circular pattern around the table
        otherEntity = self->ext.ouijaTableContents.parent;
        posX = otherEntity->posX.i.hi;
        posY = otherEntity->posY.i.hi - 32;
        posY += ((rcos(self->ext.ouijaTableContents.unk8E) * 8) >> 12);
        posX += ((rsin(self->ext.ouijaTableContents.unk8E) * 18) >> 12);
        self->posX.i.hi = posX;
        self->posY.i.hi = posY;
        // Beaker and vase move in opposite directions
        if (self->params) {
            self->ext.ouijaTableContents.unk8E += 48;
        } else {
            self->ext.ouijaTableContents.unk8E -= 48;
        }

        // Fly towards player in attack motion
        if (self->ext.ouijaTableContents.isThrown) {
            otherEntity = &PLAYER;
            angle = GetAngleBetweenEntities(self, otherEntity);
            self->velocityX = (rcos(angle) << 18) >> 12;
            self->velocityY = (rsin(angle) << 18) >> 12;
            self->step = OUIJA_COMPONENT_SEEK_ATTACK;
        }
        break;

    case OUIJA_COMPONENT_SEEK_ATTACK:
        hitFlags = self->hitFlags;
        if (self->ext.ouijaTableContents.isThrown) {
            if (hitFlags & 0x80) {
                self->ext.ouijaTableContents.isThrown = false;
            } else if (hitFlags) {
                self->velocityX = 0;
                self->velocityY = 0;
            }
        }
        MoveEntity();

        self->velocityX -= self->velocityX / 32;
        self->velocityY -= self->velocityY / 32;

        // Once velocity is dampened to min value, return to origin
        if (abs(self->velocityX) < FIX(0.5) &&
            abs(self->velocityY) < FIX(0.5)) {
            self->ext.ouijaTableContents.isThrown = false;
            self->step = OUIJA_COMPONENT_INIT_POS;
        }
        break;

    case OUIJA_COMPONENT_DEATH:
        switch (self->step_s) {
        case OUIJA_COMPONENT_BEGIN_DEATH:
            self->hitboxState = 0;
            self->velocityX = 0;
            self->velocityY = 0;
            self->drawFlags = FLAG_DRAW_ROTZ;
            self->step_s++;
            // fallthrough

        case OUIJA_COMPONENT_FALL_TO_FLOOR:
            // When hit, components rotate and fall to floor
            // After hitting the floor, begin death timer
            self->rotZ += 64;
            if (UnkCollisionFunc3(sensors_ground_components) & 1) {
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->animCurFrame++;
                self->ext.ouijaTableContents.timer = 32;
                PlaySfxPositional(SFX_SKULL_BONK);
                self->step_s++;
            }
            break;

        case OUIJA_COMPONENT_DIE_IN_FLAMES:
            // Once death timer expires, burst into flames and get destroyed
            if (!(--self->ext.ouijaTableContents.timer)) {
                otherEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (otherEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, otherEntity);
                    otherEntity->params = 0;
                }
                PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
                DestroyEntity(self);
            }
            break;
        }
        break;

    case 16:
        break;
    }
}
