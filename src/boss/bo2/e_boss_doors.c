// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo2.h"

extern EInit D_us_80180524;
extern s32 D_us_80180B74;

void EntityBossDoors(Entity* self) {
    Entity* nextEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180524);
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
            CreateEntityFromEntity(E_BOSS_DOORS, self, nextEntity);
            nextEntity->posX.i.hi -= 7;
            nextEntity->posY.i.hi += 0xD;
            nextEntity->facingLeft = self->facingLeft;
            nextEntity->params = 0x100;

            nextEntity = self + 2;
            CreateEntityFromEntity(E_BOSS_DOORS, self, nextEntity);
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
            CreateEntityFromEntity(E_BOSS_DOORS, self, nextEntity);
            nextEntity->posX.i.hi += 7;
            nextEntity->facingLeft = self->facingLeft;
            nextEntity->posY.i.hi += 0x14;
            nextEntity->params = 0x100;

            nextEntity = self + 2;
            CreateEntityFromEntity(E_BOSS_DOORS, self, nextEntity);
            nextEntity->posX.i.hi += 6;
            nextEntity->posY.i.hi += 0x41;
            nextEntity->facingLeft = self->facingLeft;
            nextEntity->params = 0x200;

            self->posY.i.hi += 0x50;
        }
    case 1:
        if (D_us_80180B74) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
            if (self->params) {
                self->ext.areBossDoor.timer = 0x50;
            } else {
                self->ext.areBossDoor.timer = 0x40;
            }
            g_Tilemap.fg[0x104] = 0xF6;
            g_Tilemap.fg[0x124] = 0xFE;
            g_Tilemap.fg[0x144] = 0x106;
            g_Tilemap.fg[0x164] = 0xFE;
            g_Tilemap.fg[0xFB] = 0xEE;
            g_Tilemap.fg[0x11B] = 0x17F;
            g_Tilemap.fg[0x13B] = 0x187;
            g_Tilemap.fg[0x15B] = 0x17F;
            g_Tilemap.fg[0x17B] = 0x187;
            self->step++;
        }
        break;
    case 2:
        if (self->ext.areBossDoor.timer & 1) {
            self->posX.i.hi++;
        } else {
            self->posX.i.hi--;
        }
        self->posY.i.hi--;

        if (!--self->ext.areBossDoor.timer) {
            PlaySfxPositional(SFX_LEVER_METAL_BANG);
            self->step++;
        }
        break;
    case 3:
        if (!D_us_80180B74) {
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
        if (D_us_80180B74) {
            self->palette = (g_Timer & 1) + 1;
        } else {
            self->palette = 0;
        }
        break;
    case 32:
        break;
    case 255:
#include "../../st/pad2_anim_debug.h"
    }
}
