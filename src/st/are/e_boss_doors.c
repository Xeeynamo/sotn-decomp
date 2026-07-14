// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

extern EInit g_EInitEnvironment;

#ifdef VERSION_PSP
extern s32 E_ID(BOSS_DOORS);
#endif

void EntityBossDoors(Entity* self) {
    static s32 doors_active = false;
    Entity* nextEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        if (self->params & 0x100) {
            self->animCurFrame = 2;
            self->zPriority = 0x6A;
            self->step = 16;
            break;
        }

        if (self->params & 0x200) {
            self->animCurFrame = 3;
            self->zPriority = 0x6B;
            self->step = 32;
            break;
        }

        self->animCurFrame = 1;
        self->zPriority = 0x6A;
        if (!self->params) {
            self->facingLeft = 1;
            self->posX.i.hi = 0x4F - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 0xA6 - g_Tilemap.scrollY.i.hi;

            nextEntity = self + 1;
            CreateEntityFromEntity(E_ID(BOSS_DOORS), self, nextEntity);
            nextEntity->posX.i.hi -= 7;
            nextEntity->posY.i.hi += 0xD;
            nextEntity->facingLeft = self->facingLeft;
            nextEntity->params = 0x100;

            nextEntity = self + 2;
            CreateEntityFromEntity(E_ID(BOSS_DOORS), self, nextEntity);
            nextEntity->posX.i.hi -= 8;
            nextEntity->facingLeft = self->facingLeft;
            nextEntity->posY.i.hi += 0x31;
            nextEntity->params = 0x200;

            self->posY.i.hi += 0x40;
        } else {
            self->facingLeft = 0;
            self->posX.i.hi = 0x1B1 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 0x96 - g_Tilemap.scrollY.i.hi;

            nextEntity = self + 1;
            CreateEntityFromEntity(E_ID(BOSS_DOORS), self, nextEntity);
            nextEntity->posX.i.hi += 7;
            nextEntity->facingLeft = self->facingLeft;
            nextEntity->posY.i.hi += 0x14;
            nextEntity->params = 0x100;

            nextEntity = self + 2;
            CreateEntityFromEntity(E_ID(BOSS_DOORS), self, nextEntity);
            nextEntity->posX.i.hi += 6;
            nextEntity->posY.i.hi += 0x41;
            nextEntity->facingLeft = self->facingLeft;
            nextEntity->params = 0x200;

            self->posY.i.hi += 0x50;
        }

        break;
    case 1:
        break;
    case 2:
        if (self->ext.areBossDoor.timer & 1) {
            self->posX.i.hi++;
        } else {
            self->posX.i.hi--;
        }
        self->posY.i.hi--;

        if (!--self->ext.areBossDoor.timer) {
            self->step++;
        }
        break;
    case 3:
        if (!doors_active) {
            self->ext.areBossDoor.timer = 0x60;
            g_Tilemap.fg[0x104] = 0x1A5;
            g_Tilemap.fg[0x124] = 0x1A6;
            g_Tilemap.fg[0x144] = 0x1A7;
            g_Tilemap.fg[0x164] = 0x1A6;
            g_Tilemap.fg[0xFB] = 0x1A4;
            g_Tilemap.fg[0x11B] = 0x1A8;
            g_Tilemap.fg[0x13B] = 0x1A9;
            g_Tilemap.fg[0x15B] = 0x1A8;
            g_Tilemap.fg[0x17B] = 0x1A9;
            self->step++;
        }
        break;
    case 4:
        if (self->ext.areBossDoor.timer & 1) {
            self->posX.i.hi++;
        } else {
            self->posX.i.hi--;
        }
        self->posY.i.hi++;

        if (!--self->ext.areBossDoor.timer) {
            self->step++;
        }
        break;
    case 16:
        // Adds a very subtle shimmer on the door gear when doors are locked.
        // This is only viewable during the boss fight.
        if (doors_active) {
            self->palette = (g_Timer & 1) + 1;
        } else {
            self->palette = 0;
        }
        break;
    case 32:
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
}
