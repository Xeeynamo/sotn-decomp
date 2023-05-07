/*
 * Overlay: NZ0
 * Enemy: Spittle Bone
 */

#include "nz0.h"

// moves around on walls and drips poison
void EntitySpittleBone(Entity* self) {
    Entity* newEntity;
    s32 i;

    if ((self->flags & 0x100) && (self->step < 3)) {
        self->step = 3;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CAC);
        self->unk19 = 4;
        self->unk1E = 0;
        self->flags &= ~0x2200;
        self->facing = self->subId;
        break;

    case 1:
        if (func_801BCCFC(&D_801824CC) & 1) {
            newEntity = &self[1];
            self->ext.generic.unk7C.S8.unk0 = 0;
            CreateEntityFromEntity(0x32, self, newEntity);
            newEntity->facing = self->facing;
            newEntity->ext.generic.unk7C.S8.unk0 =
                self->ext.generic.unk7C.S8.unk0;
            if (self->facing != 0) {
                self->accelerationX = 0x10000;
                newEntity->posX.i.hi += 16;
            } else {
                self->accelerationX = -0x10000;
                newEntity->posX.i.hi -= 16;
            }
            newEntity->accelerationX = self->accelerationX;
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(&D_80182524, self);
        self->ext.generic.unk7C.U8.unk0 =
            func_801C1034(self->ext.generic.unk7C.U8.unk0);
        if (self->ext.generic.unk80.modeS16.unk2 != 0) {
            self->unk1E += self->ext.generic.unk80.modeS16.unk0;
            self->ext.generic.unk80.modeS16.unk2--;
            if (self->ext.generic.unk80.modeS16.unk2 == 0) {
                self->unk1E = self[1].unk1E;
            }
        }
        if (((self->ext.generic.unk7C.U8.unk0 & 0x3F) == 1) &&
            (!(Random() & 0x1F))) {
            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
            if (newEntity != 0) {
                CreateEntityFromEntity(0x33, self, newEntity);
                newEntity->ext.generic.unk84.unk = self;
                newEntity->posY.i.hi += 24;
            }
        }
        self->unk10 = (u32)rsin(self->unk1E) >> 8;
        self->unk12 = -(rcos(self->unk1E) * 16) >> 0xC;
        return;

    case 3:
        for (i = 0; i < 6; i++) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                func_801C1780(0x31, self, newEntity);
                newEntity->facing = self->facing;
                newEntity->flags = -0x37FFE000;
                newEntity->palette = 0x20D;
                newEntity->animCurFrame = i + 0x3A;
                newEntity->unk19 |= 4;
                newEntity->unk1E = self->unk1E;
                newEntity->step = 4;
                newEntity->accelerationX = D_80182504[i];
                newEntity->accelerationY = 0xFFFD0000 - ((Random() & 3) << 0xF);
                newEntity->ext.generic.unk80.modeS16.unk2 =
                    D_801824E2[i + 0x3A];
            }
        }

        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, self, newEntity);
            newEntity->subId = 1;
            newEntity->posX.i.hi += -(rsin(self->unk1E) * 0x10) >> 0xC;
            newEntity->posY.i.hi += -(rcos(self->unk1E) * 0x10) >> 0xC;
        }
        func_801C29B0(0x62B);
        DestroyEntity(self);
        break;

    case 4:
        MoveEntity();
        self->accelerationY += 0x2800;
        self->ext.generic.unk80.modeS16.unk2--;
        if (self->ext.generic.unk80.modeS16.unk2 == 0) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(2, self, newEntity);
                newEntity->subId = 0;
            }
            DestroyEntity(self);
        }
        break;
    }
}

const u32 rodataPadding_801B08B0 = 0;

// DECOMP_ME_WIP func_801C6B24 https://decomp.me/scratch/T0T7K mostly regalloc
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", func_801C6B24);

// spit projectile from spittle bone
// Unique
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", EntitySpittleBoneSpit);
