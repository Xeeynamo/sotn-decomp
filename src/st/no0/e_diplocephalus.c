// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/e_diplocephalus", func_us_801CF4A8);

extern s16 D_us_80181D54[]; // sensors_ground
extern u8 D_us_80181D83[];  // anim frames

void EntityDiplocephalusFoot(Entity* self) {
    Entity* currentEntity;
    u16 x;

    switch (self->step) {
    case 0:
        currentEntity = g_CurrentEntity;
        g_CurrentEntity = self;
        InitializeEntity(g_EInitDiplocephalusFoot);
        g_CurrentEntity->hitboxOffY = 4;
        g_CurrentEntity->animCurFrame =
            D_us_80181D83[g_CurrentEntity->ext.diplocephalus.unk9E];
        g_CurrentEntity = currentEntity;
        // fallthrough
    case 1:
        currentEntity = g_CurrentEntity;
        g_CurrentEntity = self;
        if (UnkCollisionFunc3(D_us_80181D54) & 1) {
            g_CurrentEntity->step++;
        }
        g_CurrentEntity = currentEntity;
        break;
    case 2:
        if (g_CurrentEntity->step >= 4) {
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->velocityY = -0x2AAA4;
            self->ext.diplocephalus.unk9F = 0;
            self->ext.diplocephalus.velocityY = -0x71DU;
            self->animCurFrame--;
            self->step = 4;
        }
        break;
    case 3:
        if (self->facingLeft) {
            self->velocityX = -0x22AAA;
        } else {
            self->velocityX = 0x22AAA;
        }
        self->velocityY = -0x7FFFE;
        self->ext.diplocephalus.unk9F = 0;
        self->ext.diplocephalus.velocityY = 0x26AAA;
        self->animCurFrame--;
        self->step = 4;
        break;
    case 4:
        self->velocityY += self->ext.diplocephalus.velocityY;
        self->ext.diplocephalus.unk9F++;
        currentEntity = g_CurrentEntity;
        g_CurrentEntity = self;

        // Walk forward, spawning dust cloud when stepping
        if (UnkCollisionFunc3(&D_us_80181D54) & 1) {
            PlaySfxPositional(0x779);
            self->velocityX = 0;
            self->velocityY = 0;
            self->animCurFrame++;
            if (self->ext.diplocephalus.unk9E < 3) {
                if (g_CurrentEntity->facingLeft ^
                    (LOHU(self->ext.prim->x3) % 2)) {
                    EntityGreyPuffSpawner(self, 6, 3, 6, 16, 0, -4);
                } else {
                    EntityGreyPuffSpawner(self, 6, 3, -6, 16, 0, 4);
                }
            }
            self->step++;
        }
        g_CurrentEntity = currentEntity;
        break;
    case 5:
        self->ext.diplocephalus.unk9F++;
        break;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/e_diplocephalus", func_us_801CF910);

INCLUDE_ASM("st/no0/nonmatchings/e_diplocephalus", func_us_801CFBE8);

INCLUDE_ASM("st/no0/nonmatchings/e_diplocephalus", func_us_801D0718);

// Death explosion
INCLUDE_ASM("st/no0/nonmatchings/e_diplocephalus", func_us_801D0898);

// Fireball
INCLUDE_ASM("st/no0/nonmatchings/e_diplocephalus", func_us_801D0990);

// Main entity?
INCLUDE_ASM("st/no0/nonmatchings/e_diplocephalus", func_us_801D0E7C);
