#include "nz0.h"

// DECOMP_ME_WIP EntityCloseBossRoom https://decomp.me/scratch/bqgN9 95.04 %
// figuring out D_80181014 struct might help
// trigger to stop music and close slogra/gaibon room
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/33FCC", EntityCloseBossRoom);

// blocks that move to close slogra/gaibon room
// assembler skips a nop
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/33FCC", EntityBossRoomBlock);
#else
void EntityBossRoomBlock(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D00);
        self->animCurFrame = 8;

    case 1:
        if (D_80181010 & 1) {
            self->ext.generic.unk80.modeS16.unk0 = 0x10;
            self->step++;
        }
        break;

    case 2:
        if (self->subId == 0) {
            self->accelerationX = 0x10000;
        } else {
            self->accelerationX = -0x10000;
        }
        MoveEntity();
        func_801BD9A0(self, 8, 8, 5);
        if (!(g_blinkTimer & 3)) {
            g_api.PlaySfx(0x608);
        }
        if (--self->ext.generic.unk80.modeS16.unk0) {
            break;
        }
        self->step++;
        break;

    case 3:
        func_801BD9A0(self, 8, 8, 5);
        if (D_80181010 & 2) {
            self->step++;
        }
        break;

    case 4:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        if (self->subId != 0) {
            self->accelerationX = 0x10000;
        } else {
            self->accelerationX = -0x10000;
        }
        MoveEntity();
        break;
    }
}
#endif

s32 func_801B4690(void) {
    s32 ret = 0;
    s32 temp;

    MoveEntity();
    g_CurrentEntity->accelerationY += 0x4000;
    temp = g_CurrentEntity->posX.i.hi + g_Camera.posX.i.hi;

    if ((g_CurrentEntity->accelerationX > 0) && (temp > 896)) {
        g_CurrentEntity->posX.i.hi = 896 - g_Camera.posX.i.hi;
    }

    if ((g_CurrentEntity->accelerationX < 0) && (temp < 64)) {
        g_CurrentEntity->posX.i.hi = 64 - g_Camera.posX.i.hi;
    }

    if ((g_CurrentEntity->posY.i.hi + g_Camera.posY.i.hi) > 416) {
        ret = 1;
        g_CurrentEntity->posY.i.hi = 416 - g_Camera.posY.i.hi;
        g_CurrentEntity->accelerationX = 0;
        g_CurrentEntity->accelerationY = 0;
    }

    return ret;
}

// slogra boss
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/33FCC", EntitySlogra);

void func_801B54A8(Entity* self) {
    s8* hitbox;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D18);

    case 1:
        self->facing = self[-1].facing;
        self->posX.i.hi = self[-1].posX.i.hi;
        self->posY.i.hi = self[-1].posY.i.hi;
        hitbox = D_801811E0;
        hitbox += 4 * D_80181218[self[-1].animCurFrame];
        self->unk10 = *hitbox++;
        self->unk12 = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (self[-1].ext.generic.unk84.U8.unk2 != 0) {
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->unk19 = 4;
            self->unk3C = 0;
            if (self->facing != 0) {
                self->accelerationX = -0x24000;
            } else {
                self->accelerationX = 0x24000;
            }
            self->accelerationY = -0x40000;
            self->animCurFrame = 0x23;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;

        case 1:
            MoveEntity();
            self->accelerationY += 0x2800;
            self->unk1E += 0x80;
            if (!(self->unk1E & 0xFFF)) {
                func_801C29B0(0x625);
            }
        }
    }
}

// projectile fired from slogra's spear
void EntitySlograSpearProjectile(Entity* self) {
    Entity* entity;

    if (self->flags & 0x100) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(ENTITY_EXPLOSION, self, entity);
            entity->subId = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D24);
        if (self->facing == 0) {
            self->accelerationX = -0x40000;
        } else {
            self->accelerationX = 0x40000;
        }

    case 1:
        if (AnimateEntity(D_80181160, self) == 0) {
            SetStep(2);
        }
        break;

    case 2:
        MoveEntity();
        AnimateEntity(D_80181170, self);
        break;
    }
}

// gaibon boss
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/33FCC", EntityGaibon);

void func_801B69E8(Entity* self) {
    Entity* prevEntity;
    s16 animCurFrame;

    if (self->step == 0) {
        InitializeEntity(D_80180D30);
        self->unk3C = 0;
    }

    prevEntity = &self[-1];
    self->facing = prevEntity->facing;
    self->palette = prevEntity->palette;
    self->posX.i.hi = prevEntity->posX.i.hi;
    self->posY.i.hi = prevEntity->posY.i.hi;
    self->animCurFrame = 0;

    if ((prevEntity->animCurFrame - 32) < 3U) {
        self->animCurFrame = 0x26;
    } else if (prevEntity->animCurFrame == 35) {
        self->animCurFrame = 0x27;
    } else if ((prevEntity->animCurFrame - 36) < 2U) {
        self->animCurFrame = 0x28;
    }

    if (prevEntity->objectId != 0x43) {
        DestroyEntity(self);
    }
}

// small red projectile from gaibon
void EntitySmallGaibonProjectile(Entity* self) {
    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->unk19 = 0;
        self->step = 0;
        self->objectId = 2;
        self->subId = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D3C);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->unk19 = 5;
        self->unk1A = 0xC0;
        self->accelerationX = (rcos(self->unk1E) * 0x28000) >> 0xC;
        self->accelerationY = (rsin(self->unk1E) * 0x28000) >> 0xC;
        self->palette = 0x81B6;
        self->unk1E -= 0x400;

    case 1:
        MoveEntity();
        AnimateEntity(D_8018136C, self);
        break;
    }
}

// large red projectile from gaibon
void EntityLargeGaibonProjectile(Entity* self) {
    Entity* newEntity;

    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->objectId = 2;
        self->unk19 = 0;
        self->step = 0;
        self->subId = 1;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D48);
        if (self->subId == 0) {
            self->animSet = 2;
            self->unk19 = 4;
            self->accelerationX = (rcos(self->unk1E) * 0x38000) >> 0xC;
            self->accelerationY = (rsin(self->unk1E) * 0x38000) >> 0xC;
            self->palette = 0x81B6;
            self->unk1E -= 0x400;
        } else {
            self->animSet = 14;
            self->unk5A = 0x79;
            self->unk19 = 0xD;
            self->unk1A = 0x100;
            self->unk6C = 0x80;
            self->palette = 0x81F3;
            self->blendMode = 0x30;
            self->step = 2;
            self->unk3C = 0;
            self->flags |= 0x2000;
        }
        break;

    case 1:
        MoveEntity();
        AnimateEntity(D_80181378, self);
        if (!(g_blinkTimer & 3)) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x46, self, newEntity);
                newEntity->subId = 1;
                newEntity->unk1E = self->unk1E;
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        break;

    case 2:
        self->unk6C += 0xFE;
        self->unk1A -= 4;
        if (AnimateEntity(D_80181388, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
