// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

static s32 D_us_80180FD0 = 0;
static s16 D_us_80180FD4[] = {
    0x200,
    0x800,
    0x300,
    0xE00,
};
static s16 D_us_801C1680[4];

void EntityWallGear(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->zPriority = 0x6C;
        self->animCurFrame = 0xC;
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->velocityY = FIX(0.5);
        self->hitboxState = 2;
        self->hitPoints = S16_MAX;
        self->hitboxWidth = self->hitboxHeight = 0x10;
        self->rotate = D_us_801C1680[self->params];
        self->rotate &= 0xF00;
        // fallthrough

    case 1:
        self->hitboxState = 2;
#ifdef VERSION_PSP
        if (self->params != 1 || self->posY.i.hi >= 97)
#endif
        {
            if (self->hitFlags) {
                self->ext.gearPuzzle.cooldownTimer = 16;
                self->step++;
            }
            D_us_801C1680[self->params] = self->rotate;
        }
        break;

    case 2:
        self->hitboxState = 0;
        self->rotate += 16;
        if (!--self->ext.gearPuzzle.cooldownTimer) {
            self->rotate &= 0xFFF;
            if (self->rotate == D_us_80180FD4[self->params]) {
                D_us_80180FD0 |= 1 << self->params;
                PlaySfxPositional(SFX_SWITCH_CLICK);
            } else {
                D_us_80180FD0 &= 0xFF - (1 << self->params);
                PlaySfxPositional(SFX_LEVER_METAL_BANG);
            }
            self->step = 1;
        }
        break;
    }
}

static s16 D_us_80180FDC[] = {
    0x0580, 0x0581, 0x0581, 0x0582, 0x0456, 0x0472, 0x0472, 0x0454,
};

void EntitySecretAreaDoor(Entity* self) {
    s32 i;
    Entity* entity;
    s16* var_a1;
    s32 fgIndex;
    s32 offsetX;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->animCurFrame = 7;
        if (D_us_80180FD0 == 0xF) {
            self->step = 2;
        } else {
            self->step = 1;
        }
        break;

    case 1:
        switch (self->step_s) {
        case 0:
            self->posX.i.hi = 8 - g_Tilemap.scrollX.i.hi;
            if (D_us_80180FD0 == 0xF) {
                PlaySfxPositional(SFX_STONE_MOVE_B);
                self->step_s++;
            }
            break;

        case 1:
            self->posX.val -= FIX(0.5);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                entity->params = 0x10;
                entity->posY.i.hi += 0x20;
                entity->posX.i.hi -= (Random() & 7);
            }
            offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (offsetX < -15) {
                SetStep(2);
            }
            break;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            self->posX.i.hi = -16 - g_Tilemap.scrollX.i.hi;
            if (D_us_80180FD0 != 0xF) {
                PlaySfxPositional(SFX_STONE_MOVE_B);
                self->step_s++;
            }
            break;
        case 1:
            self->posX.val += FIX(0.5);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                entity->params = 0x10;
                entity->posY.i.hi += 0x20;
                entity->posX.i.hi -= (Random() & 7);
            }
            offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (offsetX > 7) {
                SetStep(1);
            }
            break;
        }
        break;
    }
    GetPlayerCollisionWith(self, 8, 0x20, 5);
    if (D_us_80180FD0 == 0xF) {
        var_a1 = &D_us_80180FDC[4];
    } else {
        var_a1 = D_us_80180FDC;
    }
    fgIndex = 0x360;
    for (i = 0; i < 4; i++, var_a1++, fgIndex += 16) {
        g_Tilemap.fg[fgIndex] = *var_a1;
    }
}
