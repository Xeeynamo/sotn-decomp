/*
 * Overlay: NZ0
 * Enemy: Axe Knight
 */

#include "nz0.h"

// aspatch skips a nop. TODO: fix compiler
// matching in decomp.me: https://decomp.me/scratch/oDgqZ
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/43F9C", func_801C3F9C);
#else
void func_801C3F9C(Unkstruct_801C3F9C** self) {
    Collider collider;
    Entity* newEntity;
    s16 temp;

    func_801C9930();
    switch ((*self)->unk24) {
    case 0:
        (*self)->unk0C = 0;
        (*self)->unk10 = -0x10000;
        (*self)->unk24 = 1;
        (*self)->unk2C = 0x100;
        break;

    case 1:
        temp = (*self)->unk0A + ((*self)->unk1E / 3);
        g_api.CheckCollision((*self)->unk14, temp, &collider, 0);
        if (collider.unk0 % 2) {
            (*self)->unk0A = (*self)->unk0A + collider.unk18;
            if ((*self)->unk10 < 0x4000) {
                (*self)->unk2C = 1;
            }
            (*self)->unk10 = -(*self)->unk10;
            (*self)->unk10 -= (*self)->unk10 / 2;
        }
        (*self)->unk10 += 0x1800;
        (*self)->unk2C--;
        if ((*self)->unk2C == 0) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(ENTITY_EXPLOSION, newEntity);
                newEntity->posX.i.hi = (*self)->unk14;
                newEntity->posY.i.hi = (*self)->unk0A;
                newEntity->subId = 0;
            }
            func_801C29B0(0x655);
            func_801CA0D0(self);
        }
        return;
    }
}
#endif

// Called by EntityAxeKnight
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/43F9C", func_801C4198);

void func_801C4550(void) {
    if (g_CurrentEntity->unk80.modeS16.unk2 > 0) {
        g_CurrentEntity->unk80.modeS16.unk2 -= 3;
    } else {
        func_801BD52C(D_801822B4[(Random() & 7)]);
        g_CurrentEntity->unk80.modeS16.unk2 = 0x100;
    }
}

// green knight that throws axes
void EntityAxeKnight(Entity* self) {
    Entity* newEntity;
    u8 animStatus;
    s8* hitbox;
    s16 temp;

    if (self->flags & 0x100) {
        if (self->step != 8) {
            func_801C29B0(NA_SE_VO_AXE_KNIGHT_SCREAM);
            func_801B3B78();
            self->unk3C = 0;
            self->unk80.modeS16.unk0 = 0x41;
            self->zPriority -= 0x10;
            func_801BD52C(8);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180C64);
        self->facing = (GetPlayerSide() & 1) ^ 1;
        self->unk12 = 0xA;
        self->unk7C.S8.unk1 = 0;
        self->unk80.modeS16.unk2 = 0x200;

    case 1:
        if (func_801BCCFC(&D_80182188) & 1) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
            func_801BD52C(2);
        }
        break;

    case 2:
        if (self->step_s == 0) {
            if (self->facing == 0) {
                self->accelerationX = -0x3000;
            } else {
                self->accelerationX = 0x3000;
            }
            self->step_s++;
        }

        animStatus = AnimateEntity(D_80182210, self);
        if (self->animFrameDuration == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
        }

        if (animStatus == 0) {
            if (self->facing == 0) {
                self->accelerationX = -0x3000;
            } else {
                self->accelerationX = 0x3000;
            }
            if (GetPlayerDistanceX() < 0x60) {
                func_801BD52C(3);
                self->unk7C.S8.unk0 = 1;
            }
        }

        if ((self->animFrameIdx == 1) || (self->animFrameIdx == 4)) {
            if (self->facing == 0) {
                self->accelerationX -= 0x300;
            } else {
                self->accelerationX += 0x300;
            }
        } else if (self->facing != 0) {
            self->accelerationX -= 0x300;
        } else {
            self->accelerationX += 0x300;
        }

        if (func_801BCF74(&D_80182180) & 0x60) {
            self->posX.val -= self->accelerationX;
            self->accelerationX = 0;
        }
        func_801C4550();
        break;

    case 3:
        if (self->step_s == 0) {
            if (self->facing == 0) {
                self->accelerationX = 0x3000;
            } else {
                self->accelerationX = -0x3000;
            }
            self->step_s++;
        }

        animStatus = AnimateEntity(D_80182210, self);
        if (self->animFrameDuration == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
        }
        if (animStatus == 0) {
            if (self->facing == 0) {
                self->accelerationX = 0x3000;
            } else {
                self->accelerationX = -0x3000;
            }

            if (GetPlayerDistanceX() >= 0x51) {
                func_801BD52C(2);
                self->unk7C.S8.unk0 = 0;
            }
        }

        if ((self->animFrameIdx == 1) || (self->animFrameIdx == 4)) {
            if (self->facing == 0) {
                self->accelerationX += 0x200;
            } else {
                self->accelerationX -= 0x200;
            }
        } else if (self->facing != 0) {
            self->accelerationX += 0x200;
        } else {
            self->accelerationX -= 0x200;
        }

        if (func_801BCF74(&D_80182180) & 0x60) {
            self->posX.val -= self->accelerationX;
            self->accelerationX = 0;
        }
        func_801C4550();
        break;

    case 4:
        animStatus = AnimateEntity(D_80182244, self);
        if (animStatus == 0) {
        label:
            if (GetPlayerDistanceX() < 89) {
                func_801BD52C(3);
                self->unk7C.S8.unk0 = 1;
            } else {
                func_801BD52C(2);
                self->unk7C.S8.unk0 = 0;
            }
        } else if ((animStatus & 0x80) && (self->animFrameIdx == 7)) {
            func_801C29B0(NA_SE_VO_AXE_KNIGHT_THROW);
            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(0x2A, newEntity);
                newEntity->facing = self->facing;
                newEntity->posY.i.hi -= 12;
                if (newEntity->facing != 0) {
                    newEntity->posX.i.hi += 8;
                } else {
                    newEntity->posX.i.hi -= 8;
                }
            }
        }
        break;

    case 5:
        animStatus = AnimateEntity(D_80182220, self);
        if (animStatus != 0) {
            if ((animStatus & 0x80) && (self->animFrameIdx == 6)) {
                func_801C29B0(NA_SE_VO_AXE_KNIGHT_THROW);
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(0x2A, newEntity);
                    newEntity->facing = self->facing;
                    newEntity->subId = 1;
                    newEntity->posY.i.hi += 12;
                    if (newEntity->facing != 0) {
                        newEntity->posX.i.hi += 8;
                    } else {
                        newEntity->posX.i.hi -= 8;
                    }
                }
            }
        } else {
            goto label;
        }
        break;

    case 7:
        animStatus = AnimateEntity(D_80182244, self);
        if (animStatus == 0) {
            if (GetPlayerDistanceX() >= 0x59) {
                func_801BD52C(2);
                self->unk7C.S8.unk0 = 0;
            } else {
                func_801BD52C(3);
                self->unk7C.S8.unk0 = 1;
            }
            break;
        }

        if ((animStatus & 0x80) && (self->animFrameIdx == 7)) {
            func_801C29B0(NA_SE_VO_AXE_KNIGHT_THROW);
            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(0x2A, newEntity);
                newEntity->facing = self->facing;
                newEntity->subId = 2;
                newEntity->posY.i.hi -= 40;
                if (newEntity->facing != 0) {
                    newEntity->posX.i.hi += 16;
                } else {
                    newEntity->posX.i.hi -= 16;
                }
            }
        }
        break;

    case 8:
        if (self->unk80.modeS16.unk0 != 0) {
            temp = --self->unk80.modeS16.unk0;
            if (!(self->unk80.modeS16.unk0 & 7)) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(2, self, newEntity);
                    temp >>= 3;
                    newEntity->subId = 2;
                    newEntity->posX.i.hi += D_80182198[temp];
                    newEntity->posY.i.hi += D_8018219A[temp];
                }
            }
        }

        if (AnimateEntity(D_80182268, self) == 0) {
            if (func_801C4198(self) != 0) {
                DestroyEntity(self);
                return;
            }
            if (self->step_s < 16) {
                self->animCurFrame = 0;
            }
        }
        break;
    }

    hitbox = 4 * D_80182284[self->animCurFrame] + D_80182274 - 1; // Weird ?
    hitbox++;
    self->unk10 = *hitbox++;
    self->unk12 = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}

void func_801C4CC0(void) { // Axe rotation
    if (g_CurrentEntity->subId != 0) {
        g_CurrentEntity->unk1E += 0x80;
    } else {
        g_CurrentEntity->unk1E -= 0x80;
    }

    g_CurrentEntity->unk1E &= 0xFFF;
}

void EntityAxeKnightThrowingAxe(Entity* entity) {
    s32 accelerationX;

    if (entity->flags & 0x100) {
        func_801C29B0(0x66B);
        func_801BD568(0, 0);
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180C70);
        entity->unk19 = 4;
        entity->accelerationY = D_801822C8[entity->subId];
        accelerationX = D_801822BC[entity->subId];

        if (entity->facing == 0) {
            entity->accelerationX = -accelerationX;
        } else {
            entity->accelerationX = accelerationX;
        }

        entity->unk7C.s = -0x40;

        if (entity->subId == 2) {
            entity->step++;
            return;
        }
        break;

    case 1:
        func_801C4CC0();
        if ((u16)entity->unk7C.s < 0x20) {
            if (entity->facing != 0) {
                entity->accelerationX -= 0x2000;
            } else {
                entity->accelerationX += 0x2000;
            }
        }

        entity->unk7C.s++;
        MoveEntity();
        break;

    case 2:
        func_801C4CC0();
        entity->accelerationY += 0x2000;
        MoveEntity();
        break;
    }
}
