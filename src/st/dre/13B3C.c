#include "dre.h"

// Petal projectile shot by succubus ID 0x1A
void EntitySuccubusPetal(Entity* self) {
    Entity* newEntity;
    s32 temp_s2;
    s16 angle;

    if (D_80180664 & 2) {
        self->flags |= 0x100;
    }
    if (self->hitFlags & 0x80) {
        D_80180668 = 1;
    }

    if (self->flags & 0x100) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804DC);
        self->unk19 = 4;
        self->rotAngle = rand() & 0xFFF;
        temp_s2 = Random() & 3;
        if (temp_s2 >= 3) {
            temp_s2 = 0;
        }
        self->animCurFrame = temp_s2 + 64;

        angle = ((Random() & 0x1F) * 16) + 0xC0;
        if (self->facing == 0) {
            angle = 0x800 - angle;
        } else {
            angle = angle;
        }
        temp_s2 = ((rand() * 4) + 0x38000) >> 0xC;
        self->accelerationX = temp_s2 * rcos(angle);
        self->accelerationY = temp_s2 * rsin(angle);
        self->ext.generic.unk80.modeS16.unk0 = (Random() & 0x1F) + 0x10;

    case 1:
        self->accelerationX = self->accelerationX - (self->accelerationX >> 6);
        self->accelerationY = self->accelerationY - (self->accelerationY >> 6);
        MoveEntity();
        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            self->ext.generic.unk80.modeS16.unk0 = (Random() & 0x1F) + 0x20;
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        self->rotAngle += self->ext.generic.unk80.modeS16.unk0;
        break;
    }
}

void EntityUnkId1B(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_801804E8);
    }

    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->animCurFrame = 0;
    entity->posY.i.hi = entity[-1].posY.i.hi;
    entity->facing = entity[-1].facing;

    if (entity[-1].animCurFrame == 0x32) {
        entity->animCurFrame = 0x3E;
    }

    if (entity[-1].animCurFrame == 0x33) {
        entity->animCurFrame = 0x3F;
    }

    entity->zPriority = PLAYER.zPriority + 4;
}

extern s32 D_80180660;

void EntityUnkId1C(Entity* self) {
    Entity* newEntity;
    s32 accelX;
    s8* hitbox;
    s32 i;

    if (D_80180660 == 0) {
        self->flags |= 0x100;
    }

    if (self->flags & 0x100) {
        if (self->step != 5) {
            if (D_80180660 != 0) {
                D_80180660--;
            }
            self->hitboxState = 0;
            self->flags |= 0x100;
            g_api.func_80134714(0x6D9, 0x54, 0);
            SetStep(5);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804F4);
        self->hitboxState = 0;
        accelX =
            self->ext.generic.unkA0 - (self->posX.i.hi + g_Camera.posX.i.hi)
            << 0x10;
        if (accelX < 0) {
            accelX += 0x3F;
        }
        self->accelerationX = accelX >> 6;
        self->ext.generic.unk80.modeS16.unk0 = 0x40;

    case 1:
        MoveEntity();
        newEntity = self->ext.generic.unk9C; // Get ptr from the real Succubus
        self->animCurFrame = newEntity->animCurFrame; // Sync animFrames from real Succubus
        self->facing = newEntity->facing;
        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            self->hitboxState = 3;
            SetStep(2);
        }
        break;

    case 2:
        newEntity = self->ext.generic.unk9C;
        self->animCurFrame = newEntity->animCurFrame;
        self->facing = newEntity->facing;
        if (newEntity->ext.generic.unk84.U8.unk1 != 0) {
            self->ext.generic.unk80.modeS16.unk0 = (self->params * 0x30) + 1;
            SetStep(3);
        }
        break;

    case 3:
        self->animCurFrame = 26;
        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            SetStep(4);
        }
        break;

    case 4:
        if (self->step_s == 0) {
            self->ext.generic.unk84.S8.unk1 = 0;
            self->step_s++;
        }

        if (AnimateEntity(D_80180780, self) == 0) {
            self->ext.generic.unk80.modeS16.unk0 = 0x120;
            SetStep(3);
        }

        if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
            func_801A046C(0x6E2);
            for (i = 0; i < 2; i++) {
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x1D, self, newEntity);
                    newEntity->params = i;
                    if (i != 0) {
                        newEntity->posX.i.hi -= 2;
                    } else {
                        newEntity->posX.i.hi += 2;
                    }
                    newEntity->ext.generic.unk9C = self;
                    newEntity->posY.i.hi -= 10;
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
        }
        if (self->animFrameIdx == 5 && self->animFrameDuration == 0) {
            func_801A046C(0x872);
            func_801A046C(0x87C);
            func_801A046C(0x62C);
            self->ext.generic.unk84.S8.unk1 = 1;
        }
        break;

    case 5:
        if (self->step_s == 0) {
            self->ext.generic.unk80.modeS16.unk0 = 0x20;
            self->step_s++;
        }
        if (self->ext.generic.unk80.modeS16.unk0 & 1) {
            self->animSet = 0;
        } else {
            self->animSet = ANIMSET_OVL(1);
        }
        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    hitbox = &D_80180830[self->animCurFrame][D_801807F8];
    hitbox--;
    hitbox++;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}


// Pink ball projectile shot by succubus duplicates ID 0x1D
void EntityPinkBallProjectile(Entity* self) {
    Entity* entity;
    s16 temp_s0;
    s16 temp_v0;

    if (D_80180664 & 2) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180500);
        self->blendMode = 0x30;
        self->unk19 = 3;
        self->unk1C = 0;
        self->unk1A = 0;

    case 1:
        self->unk1A = self->unk1C += 4;
        if (self->unk1A > 256) {
            self->unk19 = 0;
        }
        AnimateEntity(D_80180794, self);

        entity = self->ext.generic.unk9C;
        if (entity->ext.generic.unk84.U8.unk1 != 0) {
            self->unk19 = 0;
            self->step++;
        }
        if (entity->flags & 0x100) {
            DestroyEntity(self);
        }
        break;

    case 2:
        temp_s0 = (self->params << 0xA) + 0x200;
        self->accelerationX = rcos(temp_s0) * 0x38;
        self->accelerationY = rsin(temp_s0) * 0x38;
        self->ext.generic.unkA2 = temp_s0;
        self->ext.generic.unk80.modeS16.unk0 = 128;
        self->step++;

    case 3:
        AnimateEntity(D_80180794, self);
        MoveEntity();
        temp_v0 = func_8019AF08(self, g_Entities);
        temp_s0 = func_8019AF88(0x10, self->ext.generic.unkA2, temp_v0);
        self->accelerationX = rcos(temp_s0) * 0x38;
        self->accelerationY = rsin(temp_s0) * 0x38;
        self->ext.generic.unkA2 = temp_s0;

        if (self->hitFlags & 0x80) {
            self->step = 4;
        }

        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            self->step = 4;
        }
        break;

    case 4:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        AnimateEntity(D_80180794, self);
        MoveEntity();
        break;
    }
}

// Extending wing spike from succubus ID 0x1E
void EntitySuccubusWingSpike(Entity* self) {
    s32 temp_s2;
    s16 var_s0;

    if (D_80180664 & 2) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804E8);
        self->unk19 = 4;
        self->animCurFrame = 0;
        var_s0 = D_801807F0[self->params];
        self->rotAngle = var_s0;
        self->unk19 |= 1;
        self->unk1A = 0x100;
        CreateEntityFromEntity(0x1F, self, &self[1]);
        self[1].facing = self->facing;
        self[1].params = self->params;
        self[1].rotAngle = self->rotAngle;

    case 1:
        if (self->ext.generic.unk9C->ext.generic.unk84.U8.unk1 != 0) {
            self->step++;
        }
        break;

    case 2:
        self->animCurFrame = 85;
        self->unk1A += 0x40;
        if (self->unk1A > 0x600) {
            self->unk1A = 0x600;
        }

        if (self->ext.generic.unk9C->ext.generic.unk84.U8.unk1 == 0) {
            self->step++;
        }
        break;

    case 3:
        self->unk1A -= 0x40;
        if (self->unk1A < 0x100) {
            DestroyEntity(self);
            return;
        }
    }

    var_s0 = self->rotAngle;
    temp_s2 = (self->unk1A * 0xB) >> 6;
    if (self->facing == 0) {
        var_s0 = 0x800 - var_s0;
    }

    self[1].posX.i.hi = self->posX.i.hi;
    self[1].posY.i.hi = self->posY.i.hi;
    self[1].posX.i.hi += temp_s2 * rcos(var_s0) >> 0xC;
    self[1].posY.i.hi -= temp_s2 * rsin(var_s0) >> 0xC;
}

void EntityUnkId1F(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_8018050C);
        entity->animCurFrame = 0;
        entity->unk19 = 4;
        entity->hitboxState = 0;
    case 1:
        if (entity[-1].animCurFrame != 0) {
            entity->hitboxState = 1;
            entity->animCurFrame = 0x56;
        }
        if (entity->hitFlags != 0) {
            D_80180668 = 1;
        }
        if (entity[-1].entityId != 0x1E) {
            DestroyEntity(entity);
        }
    }
}