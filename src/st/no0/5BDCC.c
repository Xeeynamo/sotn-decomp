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
        InitializeEntity(D_us_80180C14);
        self->animCurFrame = 5;
        self->hitboxOffY = 2;
        return;
    case OUIJA_TABLE_INIT_SUBENTITIES:
        if (UnkCollisionFunc3(D_us_801825D4) & 1) {
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

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DC194);

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DC64C);

void func_us_801DC754(void) {
    g_CurrentEntity->facingLeft = (GetSideToPlayer() & 1) ^ 1;
}

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DC788);
