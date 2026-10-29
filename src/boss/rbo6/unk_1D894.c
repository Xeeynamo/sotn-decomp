// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

void func_us_8019D330_from_rcen(Entity* self) {
    typedef struct {
        u16 animSet;
        u16 unk2;
        u16 palette;
        u8 blendMode;
        u8 unused;
        u32 animation;
    } Borbo6ParticleData;
    extern Borbo6ParticleData D_us_801806B4[];
    extern u16 g_EInitParticle;

    s16 temp_v1_3;
    s16 var_s0;
    s32 temp_a0;
    u16 temp_v1;
    u16 var_s0_2;
    Borbo6ParticleData* temp_v1_2;

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitParticle);
        temp_a0 = self->params & 0xF;
        temp_v1_2 = &D_us_801806B4[temp_a0];
        self->palette = temp_v1_2->palette + 0x2E0;
        self->blendMode = temp_v1_2->blendMode;
        self->animSet = temp_v1_2->animSet;
        self->unk5A = temp_v1_2->unk2;
        self->ext.et_801A518C.anim = (u8*)temp_v1_2->animation;
        self->step = temp_a0 + 1;
        temp_v1 = self->params;
        {
            u32 temp_v0;
            temp_v0 = temp_v1 & 0xFF00;
            if (temp_v0 != 0) {
                self->zPriority = temp_v0 >> 8;
            }
        }
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_19F);
            self->blendMode = BLEND_TRANSP;
            self->facingLeft = 1;
        }
        return;

    case 1:
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 2:
        MoveEntity();
        self->velocityY = FIX(-1.0);
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 3:
        if (self->step_s == 0) {
            self->drawFlags = ENTITY_OPACITY;
            self->drawFlags = ENTITY_OPACITY | ENTITY_ROTATE;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->rotate = rand() & 0xFFF;
            var_s0 = self->rotate;
            if (self->facingLeft) {
                var_s0 = -self->rotate;
            }
            self->velocityX = rsin((s32)var_s0) * 0x28;
            self->velocityY = -(rcos((s32)var_s0) * 0x28);
            self->ext.et_801A518C.acceleration = (Random() << 4) + 0x1000;
            self->step_s++;
        }
        MoveEntity();
        var_s0_2 = self->rotate;
        self->opacity += 0xFF;
        if (self->facingLeft) {
            var_s0_2 = -var_s0_2;
        }
        self->velocityX += (rsin((s32)(s16)var_s0_2) *
                            (s32)self->ext.et_801A518C.acceleration) >>
                           12;
        self->velocityY += (-(s32)self->ext.et_801A518C.acceleration *
                            rcos((s32)(s16)var_s0_2)) >>
                           12;
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (self->step_s == 0) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 9) + 0xFFFF0000;
            self->velocityY = FIX(-2.5);
            self->ext.et_801A518C.accelerationY = -(Random() << 4) - 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += (s32)self->ext.et_801A518C.accelerationY;
        self->opacity += 0xFF;
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    default:
        return;
    }
}
