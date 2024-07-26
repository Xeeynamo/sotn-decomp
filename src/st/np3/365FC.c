#include "np3.h"

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
        InitializeEntity(g_InitializeEntityData0);
        params = self->params & 0xF;
        obj = &D_8018129C[params];
        self->palette = obj->palette + 0xD0;
        self->drawMode = obj->drawMode;
        self->animSet = obj->animSet;
        self->unk5A = obj->unk2;
        self->ext.et38.unk80 = obj->unk8;
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
        self->velocityY = FIX(1.0);
        if (AnimateEntity((u8*)self->ext.et38.unk80, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 2:
        if (AnimateEntity((u8*)self->ext.et38.unk80, self) != 0) {
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
                break;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 3:
        if (self->step_s == 0) {
            self->drawFlags |= 4;
            switch (self->ext.et38.unk88) {
            case 1:
                if (self->ext.et38.unk89 >= 0x4) {
                    self->ext.et38.unk89 += 0xFD;
                    self->ext.et38.unk84 -= 0x800;
                }
                break;

            case 2:
                self->ext.et38.unk84 = (u16)self->ext.et38.unk84 +
                                       ((u8)self->ext.et38.unk89 * 0xC0);
                break;
            }
            self->ext.et38.unk84 = self->ext.et38.unk84 & 0xFFF;
            self->rotZ = self->ext.generic.unk84.S16.unk0 & 0xFFF;
            temp_s0 = self->ext.generic.unk88.U8.unk1 * 0x140;
            temp_s0 /= 28;
            self->velocityX = temp_s0 * rsin(self->ext.et38.unk84);
            self->velocityY = -(temp_s0 * rcos(self->ext.et38.unk84));
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
        if (AnimateEntity((u8*)self->ext.et38.unk80, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (self->step_s == 0) {
            rnd = Random();
            self->velocityY = FIX(-0.75);
            self->facingLeft = rnd & 1;
            self->rotX = 0xC0;
            self->drawFlags |= 1;
            self->step_s++;
        }
        MoveEntity();
        if (AnimateEntity((u8*)self->ext.et38.unk80, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
