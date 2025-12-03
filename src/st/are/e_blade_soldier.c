// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

extern EInit D_us_80180B28;
extern EInit D_us_80180B28;
extern EInit D_us_80180B34;

static s16 D_us_80181D28[] = {
    0x0000, 0x0014, 0x0000, 0x0004, 0x0008, 0xFFFC, 0xFFF0, 0x0000,
};
static s16 D_us_80181D38[] = {
    0x0000,
    0x0014,
    0x000C,
    0x0000,
};
static u8 D_us_80181D40[] = {
    0x06, 0x01, 0x04, 0x02, 0x04, 0x03, 0x06, 0x04,
    0x05, 0x05, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00,
};
static u8 D_us_80181D50[] = {
    0x06, 0x01, 0x05, 0x06, 0x05, 0x05, 0x06, 0x04,
    0x04, 0x03, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00,
};
static u8 D_us_80181D60[] = {
    0x01, 0x01, 0x04, 0x21, 0x04, 0x22, 0x01, 0x01, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80181D6C[] = {
    0x01, 0x01, 0x04, 0x21, 0x06, 0x22, 0x04, 0x21, 0x01, 0x01, 0xFF, 0x00,
};
static u8 D_us_80181D78[] = {
    0x04, 0x01, 0x05, 0x21, 0x0F, 0x22, 0x06, 0x21, 0x04, 0x01, 0x00, 0x00,
};
static u8 D_us_80181D84[] = {
    0x05, 0x01, 0x05, 0x02, 0x05, 0x07, 0x06, 0x08, 0x03, 0x09, 0x03,
    0x0A, 0x03, 0x0B, 0x03, 0x0C, 0x02, 0x0D, 0x02, 0x0E, 0x04, 0x0D,
    0x04, 0x0E, 0x05, 0x0D, 0x06, 0x0E, 0x02, 0x0F, 0x02, 0x10, 0x01,
    0x11, 0x01, 0x12, 0x01, 0x13, 0x01, 0x14, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80181DB0[] = {
    0x03, 0x15, 0x04, 0x16, 0x04, 0x17, 0x03, 0x18, 0x02, 0x19, 0x02,
    0x1A, 0x02, 0x1B, 0x02, 0x1C, 0x02, 0x1D, 0x03, 0x1E, 0x04, 0x1F,
    0x04, 0x04, 0x04, 0x05, 0x04, 0x06, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80181DD0[] = {
    0x03, 0x15, 0x03, 0x16, 0x03, 0x20, 0x04, 0x04,
    0x04, 0x05, 0x04, 0x06, 0xFF, 0x00, 0x00, 0x00,
};

static u16 D_us_80181DE0[] = {
    0x0100, 0x0080, 0x0048, 0x0020, 0x0040, 0x0010, 0x0020, 0xFFE0};
static u8 D_us_80181DF0[] = {0x30, 0x20, 0x14, 0x0C, 0x18, 0x10, 0x40, 0x30};
static s32 D_us_80181DF8[] = {0x0000C000, 0x0001C000, 0x00018000, 0x00010000,
                              0x00020000, 0x0001C000, 0xFFFF8000, 0x00008000};
static s32 D_us_80181E18[] = {0xFFFB0000, 0xFFFD0000, 0xFFFE0000, 0xFFFD0000,
                              0xFFFC0000, 0xFFFF2000, 0xFFFA0000, 0xFFFB8000};
static s16 D_us_80181E38[] = {
    0xFFFC, 0x0000, 0x0004, 0xFFFC, 0xFFFC, 0x0004, 0xFFFA, 0x0006};
static s16 D_us_80181E48[] = {
    0xFFF0, 0xFFF8, 0xFFFC, 0xFFFC, 0x0009, 0x0009, 0x0002, 0xFFFE};
static u8 D_us_80181E58[] = {0x80, 0x08, 0x08, 0x40, 0xF0, 0xC0, 0xA0, 0x80};
static s16 D_us_80181E60[] = {
    0xFFF4, 0x0010, 0x0000, 0xFFF0, 0x0000, 0xFFF0,
};
static s8 D_us_80181E6C[] = {0x00, 0x02, 0x03, 0x04, 0x04, 0x04, 0x00, 0x00};
static s8 D_us_80181E74[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xEE,
    0x0C, 0x07, 0xEF, 0xF6, 0x0D, 0x09, 0xE7, 0xFD, 0x14, 0x03};

void func_us_801C4648(void) {
    s32 collisionTestOne;
    u16 collisionTestTwo;

    collisionTestOne = UnkCollisionFunc2(D_us_80181D38);
    if (collisionTestOne == 0x80) {
        collisionTestTwo = UnkCollisionFunc(D_us_80181E60, 3);
        if (collisionTestTwo & 2) {
            SetStep(6);
        }
    } else if (!g_CurrentEntity->ext.bladeMaster.unk7C) {
        if (GetDistanceToPlayerX() < 0x40 &&
            g_CurrentEntity->facingLeft ^ (GetSideToPlayer() & 1)) {
            SetStep(5);
        }
    } else {
        g_CurrentEntity->ext.bladeMaster.unk7C--;
    }
}

void SpawnDustParticles_801C4720(void) {
    Entity* newEntity;

    newEntity = AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
    if (newEntity != NULL) {
        CreateEntityFromEntity(E_INTENSE_EXPLOSION, g_CurrentEntity, newEntity);
        newEntity->posY.i.hi += 0x14;
        if (g_CurrentEntity->facingLeft) {
            newEntity->posX.i.hi -= 4;
        } else {
            newEntity->posX.i.hi += 4;
        }
        newEntity->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        newEntity->scaleX = newEntity->scaleY = 0x80;
        newEntity->zPriority = g_CurrentEntity->zPriority + 2;
        newEntity->params = 0x10;
    }
}

void func_us_801C47E4(Entity* self) {
    Entity* entity; // s0
    s32 i;          // s1
    s32 var_s2;     // s2

    if (self->flags & FLAG_DEAD) {
        SetStep(7);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B28);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_UNK_27, entity);
        break;
    case 1:
        if (UnkCollisionFunc3(D_us_80181D28)) {
            SetStep(2);
        }
        break;
    case 2:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(D_us_80181D78, self);
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(4);
        }
        break;
    case 3:
        if (!AnimateEntity(D_us_80181D40, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.ILLEGAL.u8[4] = self->facingLeft;

        if (self->ext.ILLEGAL.u8[4]) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        if (GetDistanceToPlayerX() < 0x4C) {
            self->step = 4;
        }

        func_us_801C4648();
        break;
    case 4:
        if (!AnimateEntity(D_us_80181D50, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.ILLEGAL.u8[4] = self->facingLeft ^ 1;

        if (self->ext.ILLEGAL.u8[4]) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        if (GetDistanceToPlayerX() > 0x5C) {
            self->step = 3;
        }

        func_us_801C4648();
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.bladeMaster.unk8C = 0x20;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(D_us_80181D84, self)) {
                if (!--self->ext.bladeMaster.unk8C) {
                    self->step_s++;
                }
            }

            if (self->animCurFrame == 0xF) {
                if (self->facingLeft) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
            }

            if (!self->poseTimer && self->pose == 0xF) {
                PlaySfxPositional(SFX_MULTI_NOISE_SWEEP_DOWN);
            }

            // NOTE: result appears unused?
            var_s2 = UnkCollisionFunc2(D_us_80181D38);
            break;
        case 2:
            if (Random() & 1) {
                self->ext.ILLEGAL.u32[5] = (u32)&D_us_80181DB0;
            } else {
                self->ext.ILLEGAL.u32[5] = (u32)&D_us_80181DD0;
            }
            SetSubStep(3);
            break;
        case 3:
            var_s2 = AnimateEntity(self->ext.ILLEGAL.u32[5], self);
            UnkCollisionFunc2(D_us_80181D38);

            if (abs(self->velocityX) > 0x10000) {
                SpawnDustParticles_801C4720();
            }

            self->velocityX -= self->velocityX / 16;
            // BUG! This abs looks to be written with incorrect bracket
            if (!var_s2 && abs(self->velocityX < FIX(0.25))) {
                self->step_s++;
            }

            break;
        case 4:
            var_s2 = ++self->ext.ILLEGAL.u8[8] & 7;
            self->ext.ILLEGAL.u8[0] = D_us_80181E58[var_s2];
            SetStep(4);
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            if (!(AnimateEntity(D_us_80181D60, self) & 1)) {
                var_s2 = self->ext.ILLEGAL.u8[4];
                if (!(Random() & 3)) {
                    var_s2 ^= 1;
                }

                if (var_s2) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }

                self->velocityY = FIX(-3.0);
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;
        case 1:
            if (UnkCollisionFunc3(D_us_80181D28)) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                self->step_s++;
            }
            CheckFieldCollision(D_us_80181E60, 2);
            break;
        case 2:
            if (!AnimateEntity(&D_us_80181D6C, self)) {
                SetStep(4);
            }
            break;
        }
        break;
    case 7:
        for (i = 0; i < 8; i++) {
            entity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (entity == NULL) {
                break;
            }

            CreateEntityFromCurrentEntity(E_BONE_HALBERD_PARTS, entity);
            entity->facingLeft = self->facingLeft;
            entity->params = i;
            entity->ext.bladeMaster.unk88 = D_us_80181DF0[i];
            if (self->facingLeft) {
                entity->posX.i.hi -= D_us_80181E38[i];
            } else {
                entity->posX.i.hi += D_us_80181E38[i];
            }
            entity->posY.i.hi += D_us_80181E48[i];
            entity->velocityX = D_us_80181DF8[i];
            entity->velocityY = D_us_80181E18[i];
        }

        entity = self + 1;
        DestroyEntity(entity);
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        DestroyEntity(self);
        break;
    }
}

void EntityBoneHalberdParts(Entity* self) {
    u8 temp_v0;

    if (self->step) {
        if (--self->ext.ILLEGAL.u8[0xC]) {
            self->rotate += D_us_80181DE0[self->params];
            FallEntity();
            MoveEntity();
            return;
        }
        self->entityId = 2;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }

    InitializeEntity(D_us_80180B28);
    self->hitboxState = 0;
    self->flags |=
        FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
        FLAG_UNK_00200000 | FLAG_UNK_2000;
    self->animCurFrame = self->params + 0x23;
    self->drawFlags = FLAG_DRAW_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

void func_us_801C4EDC(Entity* self) {
    s32 index;      // s1
    s8* ptr;        // s0
    Entity* parent; // s2

    if (!self->step) {
        InitializeEntity(D_us_80180B34);
        self->hitboxState = 1;
    }

    parent = self - 1;
    POS(self->posX) = POS(parent->posX);
    self->facingLeft = parent->facingLeft;
    index = parent->animCurFrame;
    index -= 0xF;
    if (index < 0) {
        index = 0;
    }
    if (index > 5) {
        index = 0;
    }
    ptr = &D_us_80181E6C[index];
    index = *ptr;
    ptr = &D_us_80181E74[index * 4];
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;

    if (parent->entityId != 0x26) {
        DestroyEntity(self);
    }
}
