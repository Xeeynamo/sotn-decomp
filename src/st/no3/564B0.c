#include "no3.h"

//INCLUDE_ASM("asm/us/st/no3/nonmatchings/56264", EntityZombie);

void EntityZombie(Entity* self) {
    Entity* newEntity;
    s32 temp_a0;

    if ((self->flags & 0x100) && (self->step < 4)) {
        func_801CAD28(NA_SE_EN_ZOMBIE_EXPLODE);
        self->unk3C = 0;
        // Spawn Zombie explosion
        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(0x62, self, newEntity);
            newEntity->zPriority = self->zPriority + 1;
            newEntity->subId = 3;
            newEntity->posY.i.hi += 12;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BA8);
        self->hitboxWidth = 8;
        self->unk12 = 0x10;
        self->hitboxHeight = 0;
        self->zPriority += 4;
        if (g_blinkTimer & 1) {
            self->palette++;
        }
        if (Random() & 1) {
            self->palette++;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        if (func_801C5074(&D_80183CAC) & 1) {
            self->facing = (func_801C4FD4() & 1) ^ 1;
            self->step++;
        }
        break;

    case 2:
        if (AnimateEntity(D_80183C84, self) == 0) {
            func_801C58A4(3);
        }
        if (self->animFrameDuration == 0) {
            self->unk12 -= 2;
            self->hitboxHeight += 2;
        }
        break;

    case 3:
        AnimateEntity(D_80183C7C, self);
        temp_a0 = func_801C52EC(&D_80183CBC);
        if (self->facing != 0) {
            self->accelerationX = 0x8000;
        } else {
            self->accelerationX = -0x8000;
        }

        if (temp_a0 & 0xC0) {
            self->unk3C = 0;
            func_801C58A4(4);
        }
        break;

    case 4:
        if (AnimateEntity(D_80183C98, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

const u8 rodataPadding_377CC[] = { 0, 0 };