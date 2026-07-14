// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"

extern EInit g_EInitEnvironment;
extern s32 D_us_801806AC;

// Very similar to RARE's e_boss_door but with
// additional checks for the boss state.
void EntityBossDoors(Entity* self) {
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
            self->posX.i.hi = 0x1B1 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 0x5A - g_Tilemap.scrollY.i.hi;

            nextEntity = self + 1;
            CreateEntityFromEntity(E_ID(BOSS_DOORS), self, nextEntity);
            nextEntity->posX.i.hi += 7;
            nextEntity->posY.i.hi -= 0xD;
            nextEntity->facingLeft = self->facingLeft;
            nextEntity->params = 0x100;

            nextEntity = self + 2;
            CreateEntityFromEntity(E_ID(BOSS_DOORS), self, nextEntity);
            nextEntity->posX.i.hi += 7;
            nextEntity->facingLeft = self->facingLeft;
            nextEntity->posY.i.hi -= 0x31;
            nextEntity->params = 0x200;

            self->posY.i.hi -= 0x40;
        } else {
            self->facingLeft = 0;
            self->posX.i.hi = 0x4F - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 0x6A - g_Tilemap.scrollY.i.hi;

            nextEntity = self + 1;
            CreateEntityFromEntity(E_ID(BOSS_DOORS), self, nextEntity);
            nextEntity->posX.i.hi -= 7;
            nextEntity->facingLeft = self->facingLeft;
            nextEntity->posY.i.hi -= 0x14;
            nextEntity->params = 0x100;

            nextEntity = self + 2;
            CreateEntityFromEntity(E_ID(BOSS_DOORS), self, nextEntity);
            nextEntity->posX.i.hi -= 6;
            nextEntity->posY.i.hi -= 0x41;
            nextEntity->facingLeft = self->facingLeft;
            nextEntity->params = 0x200;

            self->posY.i.hi -= 0x50;
        }
        g_Tilemap.fg[0xFB] = 0x1A5;
        g_Tilemap.fg[0xDB] = 0x1A6;
        g_Tilemap.fg[0xBB] = 0x1A7;
        g_Tilemap.fg[0x9B] = 0x1A6;
        g_Tilemap.fg[0x104] = 0x1A4;
        g_Tilemap.fg[0xE4] = 0x1A8;
        g_Tilemap.fg[0xC4] = 0x1A9;
        g_Tilemap.fg[0xA4] = 0x1A8;
        g_Tilemap.fg[0x84] = 0x1A9;
        // fallthrough
    case 1:
        if (D_us_801806AC) {
            if (!self->params) {
                self->ext.areBossDoor.timer = 64;
            } else {
                self->ext.areBossDoor.timer = 80;
            }
            g_Tilemap.fg[0xFB] = 0xF6;
            g_Tilemap.fg[0xDB] = 0xFE;
            g_Tilemap.fg[0xBB] = 0x106;
            g_Tilemap.fg[0x9B] = 0xFE;
            g_Tilemap.fg[0x104] = 0xEE;
            g_Tilemap.fg[0xE4] = 0x17F;
            g_Tilemap.fg[0xC4] = 0x187;
            g_Tilemap.fg[0xA4] = 0x17F;
            g_Tilemap.fg[0x84] = 0x187;
            self->step++;
        }
        break;
    case 2:
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

    case 3:
        if (!D_us_801806AC) {
            self->ext.areBossDoor.timer = 0x60;
            g_Tilemap.fg[0xFB] = 0x1A5;
            g_Tilemap.fg[0xDB] = 0x1A6;
            g_Tilemap.fg[0xBB] = 0x1A7;
            g_Tilemap.fg[0x9B] = 0x1A6;
            g_Tilemap.fg[0x104] = 0x1A4;
            g_Tilemap.fg[0xE4] = 0x1A8;
            g_Tilemap.fg[0xC4] = 0x1A9;
            g_Tilemap.fg[0xA4] = 0x1A8;
            g_Tilemap.fg[0x84] = 0x1A9;
            self->step++;
        }
        break;

    case 4:
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
    case 16:
        if (D_us_801806AC) {
            self->palette = (g_Timer & 1) + 1;
        } else {
            self->palette = PAL_NULL;
        }
        break;
    case 32:
        break;

    case 0xFF:
#include "../../st/pad2_anim_debug.h"
        break;
    }
}
