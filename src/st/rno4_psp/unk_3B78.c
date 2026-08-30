// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", EntityRdaiUnk33);

#include "../e_imp_death_particle.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BBE58_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BC650_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCA5C_from_rnz1);

void func_us_801BCB9C_from_rnz1(Entity* self) {
    Collider collider;
    Entity* entity;
    s32 i;
    s32 x;
    s32 y;

    if (self->flags & FLAG_DEAD) {
        if (self->step != 2) {
            self->hitboxState = 0;
            PlaySfxPositional(SFX_WALL_DEBRIS_A);
            SetStep(2);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRockKnightProjectile);
        if (self->params == 0) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(2.0);
        }
        self->velocityY = FIX(-2.0);
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        x = self->posX.i.hi;
        y = self->posY.i.hi + 8;
        g_api_CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            PlaySfxPositional(SFX_WALL_DEBRIS_A);
            self->hitboxState = 0;
            SetStep(2);
        }
        break;

    case 2:
        if (AnimateEntity(g_RockKnightProjectileBreakAnim, self) == 0) {
            for (i = 0; i < 7; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_4D, self, entity);
                    entity->params = Random() & 7;
                }
            }
            self->pfnUpdate = EntityExplosion;
            self->step = 0;
            self->params = 0x13;
            self->pose = 0;
            self->poseTimer = 0;
        }
        break;
    }
}

void func_us_801BCD80_from_rnz1(Entity* self) {
    s32 temp_s1;
    s16 temp_s0;

    if (!self->step) {
        InitializeEntity(g_EInitRockKnightDebris);
        self->animCurFrame = self->params + 0x48;
        temp_s1 = (Random() & 0x1F) + 0x10;
        temp_s0 = (Random() * 6) + 0x900;
        self->velocityX = temp_s1 * rcos((s32)temp_s0);
        self->velocityY = temp_s1 * rsin((s32)temp_s0);
    }
    MoveEntity();
    self->velocityY += FIX(0.125);
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCE4C_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCFC8_from_rnz1);

#define STEP_TOWARDS_EXTERNAL
#include "../step_towards.h"
#undef STEP_TOWARDS_EXTERNAL

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_pspeu_0923D170);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801D5E90);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801D68E0);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801D6B8C);
