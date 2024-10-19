// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

// Id 0x38
static u8 D_80180FA4[] = {
    0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05,
    0x03, 0x06, 0x03, 0x07, 0x03, 0x08, 0x03, 0x09, 0x03, 0x0A,
    0x03, 0x0B, 0x03, 0x0C, 0x03, 0x0D, 0xFF, 0x00,
};
static u8 D_80180FC0[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05,
    0x02, 0x06, 0x02, 0x07, 0x02, 0x08, 0x02, 0x09, 0x02, 0x0A,
    0x02, 0x0B, 0x02, 0x0C, 0x02, 0x0D, 0x02, 0x0E, 0xFF, 0x00,
};
static Unkstruct_80180FE0 D_80180FE0[] = {
    {0x000E, 0x0079, 0x0000, 0x30, 0x00, D_80180FA4},
    {0x800B, 0x0057, 0x0000, 0x00, 0x00, D_80180FC0},
    {0x800B, 0x0057, 0x0003, 0x30, 0x00, D_80180FC0},
    {0x000E, 0x0079, 0x0004, 0x30, 0x00, D_80180FA4}};
void EntityWargExplosionPuffOpaque(Entity* self) {
    Unkstruct_80180FE0* obj;
    s32 velocityX;
    s32 velocityY;
    s32 params;
    s32 temp_s0;
    s32 adjVelocityX;
    s32 adjVelocityY;
    u32 temp_v0;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        obj = &D_80180FE0[params];
        self->palette = obj->palette + 0x2E0;
        self->drawMode = obj->drawMode;
        self->animSet = obj->animSet;
        self->unk5A = obj->unk2;
        self->ext.wargpuff.anim = obj->anim;
        self->step = params + 1;

        temp_v0 = self->params & 0xFF00;
        if (temp_v0 != 0) {
            self->zPriority = temp_v0 >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = 0x819F;
            self->drawMode = DRAW_TPAGE;
            self->facingLeft = 1;
        }
        break;

    case 1:
        MoveEntity();
        self->velocityY = FIX(-1);
        if (AnimateEntity(self->ext.wargpuff.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 2:
        if (AnimateEntity(self->ext.wargpuff.anim, self) != 0) {
            switch (self->step_s) {
            case 0:
                self->drawFlags = FLAG_DRAW_UNK8;
                self->unk6C = 0x80;
                self->step_s++;
                break;

            case 1:
                if (self->animFrameIdx == 5) {
                    self->step_s++;
                }
                break;

            case 2:
                self->unk6C += 0xFC;
                return;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 3:
        if (self->step_s == 0) {
            self->drawFlags |= FLAG_DRAW_ROTZ;
            switch (self->ext.wargpuff.unk88) {
            case 1:
                if (self->ext.wargpuff.unk89 >= 0x4) {
                    self->ext.wargpuff.unk89 += 0xFD;
                    self->ext.wargpuff.unk84 -= 0x800;
                }
                break;

            case 2:
                self->ext.wargpuff.unk84 =
                    (u16)self->ext.wargpuff.unk84 +
                    ((u8)self->ext.wargpuff.unk89 * 0xC0);
                break;
            }
            self->ext.wargpuff.unk84 = self->ext.wargpuff.unk84 & 0xFFF;
            self->rotZ = self->ext.wargpuff.unk84 & 0xFFF;
            temp_s0 = self->ext.wargpuff.unk89 * 0x140;
            temp_s0 /= 28;
            self->velocityX = temp_s0 * rsin(self->ext.wargpuff.unk84);
            self->velocityY = -(temp_s0 * rcos(self->ext.wargpuff.unk84));
            self->step_s++;
        }

        if (self->animFrameIdx >= 13) {
            velocityX = self->velocityX;
            if (velocityX < 0) {
                adjVelocityX = velocityX + 3;
            } else {
                adjVelocityX = velocityX;
            }
            self->velocityX = velocityX - (adjVelocityX >> 2);

            velocityY = self->velocityY;
            if (velocityY < 0) {
                adjVelocityY = velocityY + 3;
            } else {
                adjVelocityY = velocityY;
            }
            self->velocityY = velocityY - (adjVelocityY >> 2);
        }
        MoveEntity();
        if (AnimateEntity(self->ext.wargpuff.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (self->step_s == 0) {
            rnd = Random();
            self->velocityY = FIX(-0.75);
            self->facingLeft = rnd & 1;
            self->rotX = 0xC0;
            self->drawFlags |= FLAG_DRAW_ROTX;
            self->step_s++;
        }
        MoveEntity();
        if (AnimateEntity(self->ext.wargpuff.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
