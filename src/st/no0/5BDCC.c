// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

#define VASE self + 1
#define BEAKER self + 2
#define WALKING_TABLE self + 3

extern u16 D_us_80180C14[];
extern s16 D_us_801825CC[];
extern u16 D_us_801825D4[];
extern u8 D_us_801825F4[];

typedef enum {
    /* 0 */ OUIJA_TABLE_INIT,
    /* 1 */ OUIJA_TABLE_INIT_SUBENTITIES,
    /* 2 */ OUIJA_TABLE_COME_ALIVE,
    /* 3 */ OUIJA_TABLE_ATTACK,
    /* 4 */ OUIJA_TABLE_UNUSED,
    /* 255 */ OUIJA_TABLE_DEBUG = 255,
} OuijaTableSteps;

// Main Ouija Table entity
void EntityOuijaTable(Entity* self) {
    Entity* entity;

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 1;
        }
        PlaySfxPositional(SFX_STUTTER_FIREBALL);
        // Destroy the spinning objects on the table
        entity = VASE;
        entity->flags = entity->flags | FLAG_UNK_2000;

        entity = BEAKER;
        entity->flags = entity->flags | FLAG_UNK_2000;
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case OUIJA_TABLE_INIT:
        InitializeEntity(D_us_80180C14);
        self->animCurFrame = 5;
        self->hitboxOffY = 2;
        return;
    case OUIJA_TABLE_INIT_SUBENTITIES:
        if (UnkCollisionFunc3(D_us_801825D4) & 1) {
            // Spawn objects on the table
            entity = VASE;
            CreateEntityFromEntity(E_OUIJA_TABLE_COMPONENT, self, entity);
            entity->params = 0;
            entity->ext.ouijaTableContents.parent = self;
            entity->posX.i.hi -= 4;
            entity->posY.i.hi -= 16;

            entity = BEAKER;
            CreateEntityFromEntity(E_OUIJA_TABLE_COMPONENT, self, entity);
            entity->params = 1;
            entity->ext.ouijaTableContents.parent = self;
            entity->posX.i.hi += 2;
            entity->posY.i.hi -= 20;

            entity = WALKING_TABLE;
            CreateEntityFromEntity(E_OUIJA_TABLE_COMPONENT, self, entity);
            entity->params = 2;
            entity->ext.ouijaTableContents.parent = self;

            if (self->params) {
                entity->posX.i.hi += 24;
                entity->facingLeft = 1;
            } else {
                entity->posX.i.hi -= 24;
            }
#ifndef VERSION_PSP
            // Looks like a coding error
            entity->posY.i.hi = entity->posY.i.hi;
#endif
            self->step++;
        }
        break;
    case OUIJA_TABLE_COME_ALIVE:
        // When player approaches, spring to life
        if ((GetDistanceToPlayerX() < 80) && (GetDistanceToPlayerY() < 64)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            entity = BEAKER;
            entity->ext.ouijaTableContents.spawned = true;

            entity = VASE;
            entity->ext.ouijaTableContents.spawned = true;
            SetStep(3);
        }
        break;
    case OUIJA_TABLE_ATTACK:
        if (!self->step_s) {
            self->ext.ouijaTable.attackTimer = 128;
            self->step_s += 1;
        }
        if (AnimateEntity(D_us_801825F4, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        UnkCollisionFunc2(D_us_801825CC);

        if (self->facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        if (!(--self->ext.ouijaTable.attackTimer)) {
            self->ext.ouijaTable.attackTimer = 192;
            // Throw out one of the objects on the table
            if (self->ext.ouijaTable.thrownVase != 0) {
                entity = VASE;
            } else {
                entity = BEAKER;
            }
            entity->ext.ouijaTableContents.isThrown = true;
            // Alternate between throwing vase and beaker
            self->ext.ouijaTable.thrownVase ^= 1;
        }
        break;
    case OUIJA_TABLE_UNUSED:
        break;
    case OUIJA_TABLE_DEBUG:
#include "../pad2_anim_debug.h"
    }
}

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DC194);

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DC64C);

void func_us_801DC754(void) {
    g_CurrentEntity->facingLeft = (GetSideToPlayer() & 1) ^ 1;
}

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DC788);
