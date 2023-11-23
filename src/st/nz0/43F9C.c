/*
 * Overlay: NZ0
 * Enemy: Axe Knight
 * Description: Low level Axe Knight
 */

#include "nz0.h"

void func_801C3F9C(Unkstruct_801C3F9C** self) {
    Collider collider;
    Entity* newEntity;
    s16 temp;

    UnkPrimHelper();
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
        if (collider.effects % 2) {
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
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
                newEntity->posX.i.hi = (*self)->unk14;
                newEntity->posY.i.hi = (*self)->unk0A;
                newEntity->params = 0;
            }
            func_801C29B0(0x655);
            UnkPolyFunc0(self);
        }
        return;
    }
}

// Called by EntityAxeKnight
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/43F9C", func_801C4198);

void func_801C4550(void) {
    if (g_CurrentEntity->ext.generic.unk80.modeS16.unk2 > 0) {
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2 -= 3;
    } else {
        SetStep(D_801822B4[(Random() & 7)]);
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2 = 256;
    }
}

typedef enum {
    AXE_KNIGHT_INIT,
    AXE_KNIGHT_IDLE,
    AXE_KNIGHT_WALK_TOWARDS_PLAYER,
    AXE_KNIGHT_WALK_AWAY_FROM_PLAYER,
    AXE_KNIGHT_STANDING_THROW,
    AXE_KNIGHT_DUCKING_THROW,
    AXE_KNIGHT_UNUSED, // Charge Attack missing step from the blue AxeKnight
    AXE_KNIGHT_ARCING_THROW, // Unused, present in the blue AxeKnight
    AXE_KNIGHT_DYING,
} EntityAxeKnightSteps;

// green knight that throws axes
void EntityAxeKnight(Entity* self) {
    Entity* newEntity;
    u8 animStatus;
    s8* hitbox;
    s16 temp;

    if (self->flags & 0x100) {
        if (self->step != AXE_KNIGHT_DYING) {
            func_801C29B0(NA_SE_VO_AXE_KNIGHT_SCREAM);
            func_801B3B78();
            self->hitboxState = 0;
            self->ext.generic.unk80.modeS16.unk0 = 65;
            self->zPriority -= 0x10;
            SetStep(AXE_KNIGHT_DYING);
        }
    }

    switch (self->step) {
    case AXE_KNIGHT_INIT:
        InitializeEntity(D_80180C64);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->hitboxOffY = 10;
        self->ext.generic.unk7C.S8.unk1 = 0;
        self->ext.generic.unk80.modeS16.unk2 = 512;

    case AXE_KNIGHT_IDLE:
        if (func_801BCCFC(&D_80182188) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
        }
        break;

    case AXE_KNIGHT_WALK_TOWARDS_PLAYER:
        if (self->step_s == 0) {
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.1875);
            } else {
                self->velocityX = FIX(0.1875);
            }
            self->step_s++;
        }

        animStatus = AnimateEntity(D_80182210, self);
        if (self->animFrameDuration == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        if (animStatus == 0) {
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.1875);
            } else {
                self->velocityX = FIX(0.1875);
            }
            if (GetDistanceToPlayerX() < 96) {
                SetStep(AXE_KNIGHT_WALK_AWAY_FROM_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 1;
            }
        }

        if ((self->animFrameIdx == 1) || (self->animFrameIdx == 4)) {
            if (self->facingLeft == 0) {
                self->velocityX -= 0x300;
            } else {
                self->velocityX += 0x300;
            }
        } else if (self->facingLeft != 0) {
            self->velocityX -= 0x300;
        } else {
            self->velocityX += 0x300;
        }

        if (func_801BCF74(&D_80182180) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        func_801C4550();
        break;

    case AXE_KNIGHT_WALK_AWAY_FROM_PLAYER:
        if (self->step_s == 0) {
            if (self->facingLeft == 0) {
                self->velocityX = FIX(0.1875);
            } else {
                self->velocityX = FIX(-0.1875);
            }
            self->step_s++;
        }

        animStatus = AnimateEntity(D_80182210, self);
        if (self->animFrameDuration == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (animStatus == 0) {
            if (self->facingLeft == 0) {
                self->velocityX = FIX(0.1875);
            } else {
                self->velocityX = FIX(-0.1875);
            }

            if (GetDistanceToPlayerX() > 80) {
                SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 0;
            }
        }

        if ((self->animFrameIdx == 1) || (self->animFrameIdx == 4)) {
            if (self->facingLeft == 0) {
                self->velocityX += 0x200;
            } else {
                self->velocityX -= 0x200;
            }
        } else if (self->facingLeft != 0) {
            self->velocityX += 0x200;
        } else {
            self->velocityX -= 0x200;
        }

        if (func_801BCF74(&D_80182180) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        func_801C4550();
        break;

    case AXE_KNIGHT_STANDING_THROW:
        animStatus = AnimateEntity(D_80182244, self);
        if (animStatus == 0) {
        label:
            if (GetDistanceToPlayerX() < 89) {
                SetStep(AXE_KNIGHT_WALK_AWAY_FROM_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 1;
            } else {
                SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 0;
            }
        } else if ((animStatus & 0x80) && (self->animFrameIdx == 7)) {
            func_801C29B0(NA_SE_VO_AXE_KNIGHT_THROW);
            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_AXE_KNIGHT_AXE, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->posY.i.hi -= 12;
                if (newEntity->facingLeft != 0) {
                    newEntity->posX.i.hi += 8;
                } else {
                    newEntity->posX.i.hi -= 8;
                }
            }
        }
        break;

    case AXE_KNIGHT_DUCKING_THROW:
        animStatus = AnimateEntity(D_80182220, self);
        if (animStatus != 0) {
            if ((animStatus & 0x80) && (self->animFrameIdx == 6)) {
                func_801C29B0(NA_SE_VO_AXE_KNIGHT_THROW);
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_AXE_KNIGHT_AXE, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->params = 1;
                    newEntity->posY.i.hi += 12;
                    if (newEntity->facingLeft != 0) {
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

    case AXE_KNIGHT_ARCING_THROW: // unused
        animStatus = AnimateEntity(D_80182244, self);
        if (animStatus == 0) {
            if (GetDistanceToPlayerX() > 88) {
                SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 0;
            } else {
                SetStep(AXE_KNIGHT_WALK_AWAY_FROM_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 1;
            }
            break;
        }

        if ((animStatus & 0x80) && (self->animFrameIdx == 7)) {
            func_801C29B0(NA_SE_VO_AXE_KNIGHT_THROW);
            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_AXE_KNIGHT_AXE, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->params = 2;
                newEntity->posY.i.hi -= 40;
                if (newEntity->facingLeft != 0) {
                    newEntity->posX.i.hi += 16;
                } else {
                    newEntity->posX.i.hi -= 16;
                }
            }
        }
        break;

    case AXE_KNIGHT_DYING:
        if (self->ext.generic.unk80.modeS16.unk0 != 0) {
            temp = --self->ext.generic.unk80.modeS16.unk0;
            if (!(self->ext.generic.unk80.modeS16.unk0 & 7)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                    temp >>= 3;
                    newEntity->params = 2;
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
    hitbox = &D_80182284[self->animCurFrame][D_80182274];
    hitbox++;
    hitbox--;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}

void EntityAxeKnightRotateAxe(void) {
    if (g_CurrentEntity->params != 0) {
        g_CurrentEntity->rotZ += 0x80;
    } else {
        g_CurrentEntity->rotZ -= 0x80;
    }

    g_CurrentEntity->rotZ &= 0xFFF;
}

void EntityAxeKnightThrowingAxe(Entity* entity) {
    s32 velocityX;

    if (entity->flags & 0x100) {
        func_801C29B0(NA_SE_EN_AXE_KNIGHT_BREAK_AXE);
        func_801BD568(0, 0);
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180C70);
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->velocityY = D_801822C8[entity->params];
        velocityX = D_801822BC[entity->params];

        if (entity->facingLeft == 0) {
            entity->velocityX = -velocityX;
        } else {
            entity->velocityX = velocityX;
        }

        entity->ext.generic.unk7C.s = -0x40;

        if (entity->params == 2) {
            entity->step++;
            return;
        }
        break;

    case 1:
        EntityAxeKnightRotateAxe();
        if ((u16)entity->ext.generic.unk7C.s < 0x20) {
            if (entity->facingLeft != 0) {
                entity->velocityX -= FIX(0.125);
            } else {
                entity->velocityX += FIX(0.125);
            }
        }

        entity->ext.generic.unk7C.s++;
        MoveEntity();
        break;

    case 2:
        EntityAxeKnightRotateAxe();
        entity->velocityY += FIX(0.125);
        MoveEntity();
        break;
    }
}
