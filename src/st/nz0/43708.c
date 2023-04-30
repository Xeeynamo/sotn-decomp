#include "nz0.h"

void func_801C3708(void) {
    s32 temp = func_801BCF74(&D_8018216C);
    s32 temp2 = func_801BD720(&D_80182174, 3);

    if ((temp == 128) || (temp2 & 2)) {
        func_801BD52C(5);
        return;
    }

    if (g_CurrentEntity->unk7C.U8.unk0 == 0) {
        if (GetPlayerDistanceX() < 64) {
            if (g_CurrentEntity->facing != (GetPlayerSide() & 1)) {
                func_801BD52C(4);
            }
        }
    } else {
        g_CurrentEntity->unk7C.U8.unk0--;
    }
}

extern u16 D_80180C4C[]; // Init
extern s32 D_8018208C;   // subId
extern u8 D_80182090[];  // animation:
extern u8 D_801820A0[];  // animation:
extern u8 D_801820B0[];  // animation:
extern u8 D_801820CC[];  // animation:
extern u8 D_801820D8[];  // animation:
extern s8 D_801820F4[];  // unk88
extern s32 D_801820FC[]; // accelerationX
extern s32 D_80182118[]; // accelerationY
extern u16 D_80182134[]; // posX
extern u16 D_80182144[]; // posY
extern s8 D_80182154[2][4];
extern s32 D_8018215C;
extern s32 D_8018216C;
extern s32 D_80182174;

void EntityBoneScimitar(Entity* self) {
    Entity* newEntity;
    Entity* new_var;
    u16* var_s3;
    u8 animStatus;
    s32 var_s4;
    s32 i;

    if (self->flags & 0x100) {
        self->step = 7;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180C4C);
        if (self->subId != 0) {
            self->palette += self->subId;
            self->flags &= ~0xC0000C00;
            self->unk9C = g_Camera.posX.i.hi + self->posX.i.hi;
            if (self->subId & D_8018208C) {
                DestroyEntity(self);
                return;
            }
        }
        self->unk7C.S8.unk0 = 80;
        self->unk80.modeS8.unk0 = 0;
        self->unk84.S8.unk0 = 0;
        break;

    case 1:
        if (func_801BCCFC(&D_8018215C) != 0) {
            self->step++;
            if (self->subId != 0) {
                func_801BD52C(6);
            }
        }
        break;

    case 2:
        if (AnimateEntity(D_80182090, self) == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
        }
        self->unk80.modeS8.unk0 = self->facing;
        if (self->unk80.modeS8.unk0 == 0) {
            self->accelerationX = -0x8000;
        } else {
            self->accelerationX = 0x8000;
        }
        if (GetPlayerDistanceX() < 76) {
            self->step = 3;
        }
        func_801C3708();
        break;

    case 3:
        if (AnimateEntity(D_801820A0, self) == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
        }
        self->unk80.modeS8.unk0 = self->facing ^ 1;

        if (self->unk80.modeS8.unk0 == 0) {
            self->accelerationX = -0x8000;
        } else {
            self->accelerationX = 0x8000;
        }

        if (GetPlayerDistanceX() >= 93) {
            self->step = 2;
        }
        func_801C3708();
        break;

    case 4:
        animStatus = AnimateEntity(D_801820B0, self);
        if (self->animCurFrame == 12) {
            self->hitboxWidth = 20;
            self->hitboxHeight = 17;
            *(s16*)&self->unk10 = -11;
            self->unk12 = -14;
        } else {
            self->hitboxWidth = 8;
            self->hitboxHeight = 18;
            *(s16*)&self->unk10 = -1;
            self->unk12 = 0;
        }

        if (*(s32*)&self->animFrameIdx == 7) {
            func_801C29B0(0x66D);
        }

        if (animStatus == 0) {
            func_801BD52C(3);
            self->unk7C.S8.unk0 =
                D_80182154[self->subId % 2][(++self->unk84.S8.unk0) & 3];
            if (self->subId != 0) {
                func_801BD52C(6);
            }
        }
        break;

    case 5:
        switch (self->unk2E) {
        case 0:
            if (!(AnimateEntity(D_801820CC, self) & 1)) {
                u8 facing_ = self->unk80.modeS8.unk0;
                s32 facing;

                if (Random() % 4) {
                    facing = facing_;
                } else {
                    facing_ ^= 1;
                    facing = facing_;
                }
                if (facing == 0) {
                    self->accelerationX = -0x20000;
                } else {
                    self->accelerationX = 0x20000;
                }

                self->accelerationY = -0x30000;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->unk2E++;
            }
            break;

        case 1:
            if (func_801BCCFC(&D_8018215C) != 0) {
                self->unk2E++;
            }
            func_801BD848(&D_80182174, 2);
            break;

        case 2:
            if (AnimateEntity(D_801820D8, self) == 0) {
                func_801BD52C(3);
            }
        }
        break;

    case 6:
        self->facing = (GetPlayerSide() & 1) ^ 1;
        func_801BCF74(&D_8018216C);
        if (((((u32)self->accelerationX) >> 0x1F) ^ self->facing) != 0) {
            AnimateEntity(D_80182090, self);
        } else {
            AnimateEntity(D_801820A0, self);
        }

        switch (self->unk2E) {
        case 0:
            self->accelerationX = 0x8000;
            if (((s16)((g_Camera.posX.i.hi + self->posX.i.hi) -
                       ((u16)self->unk9C))) >= 33) {
                self->unk2E++;
            }
            break;

        case 1:
            self->accelerationX = -0x8000;
            if (((s16)((g_Camera.posX.i.hi + ((u16)self->posX.i.hi)) -
                       ((u16)self->unk9C))) < (-0x20)) {
                self->unk2E--;
            }
            break;
        }

        if (self->unk7C.U8.unk0 != 0) {
            self->unk7C.U8.unk0--;
            return;
        }
        if ((GetPlayerDistanceX() < 48) && (GetPlayerDistanceY() < 32)) {
            func_801BD52C(4);
        }
        break;

    case 7:
        g_api.PlaySfx(NA_SE_EN_SKELETON_DESTROY);
        for (i = 0; i < 7; i++) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(0x28, newEntity);
            newEntity->facing = self->facing;
            newEntity->subId = i;
            newEntity->unk88.S8.unk0 = D_801820F4[i];

            if (self->facing != 0) {
                newEntity->posX.i.hi -= D_80182134[i];
            } else {
                newEntity->posX.i.hi += D_80182134[i];
            }
            newEntity->posY.i.hi += D_80182144[i];
            newEntity->accelerationX = D_801820FC[i];
            newEntity->accelerationY = D_80182118[i];
            newEntity->subId |= self->subId << 8;
        }

        newEntity = &self[1];
        if (self->subId != 0) {
            CreateEntityFromEntity(ENTITY_INVENTORY_DROP, self, newEntity);
            if (!(self->subId & 1)) {
                self[1].subId = 0x1A; // Red rust
            } else {
                self[1].subId = 0x13; // Short sword
            }
            newEntity->subId |= 0x8000;
            D_8018208C |= self->subId;
        }
        DestroyEntity(self);
        break;
    }
}

// debris that rotates and falls down
void EntityFallingDebris(Entity* entity) {
    if (entity->step) {
        entity->unk88.S8.unk0--;
        if (entity->unk88.S8.unk0 & 0xFF) {
            entity->unk1E += D_801820E4[entity->subId];
            FallEntity();
            MoveEntity();
            return;
        }
        entity->objectId = ENTITY_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->subId = 0;
        entity->step = 0;
        return;
    }
    InitializeEntity(D_80180C58);
    entity->unk19 = 4;
    entity->animCurFrame = *(u8*)&entity->subId + 16;

    if (entity->facing != 0) {
        entity->accelerationX = -entity->accelerationX;
    }

    if (entity->subId & 0xF00) {
        entity->palette += entity->subId / 256;
    }
}

// aspatch skips a nop. TODO: fix compiler
// matching in decomp.me: https://decomp.me/scratch/oDgqZ
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/43708", func_801C3F9C);
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
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/43708", func_801C4198);

void func_801C4550(void) {
    if (g_CurrentEntity->unk80.modeS16.unk2 > 0) {
        g_CurrentEntity->unk80.modeS16.unk2 -= 3;
    } else {
        func_801BD52C(D_801822B4[(Random() & 7)]);
        g_CurrentEntity->unk80.modeS16.unk2 = 0x100;
    }
}