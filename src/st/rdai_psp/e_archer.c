// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rdai/rdai.h"

s32 SpearGuardCheckCollision(void) {
    Collider collider;
    s32 x;
    s32 y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.i.hi -= 3;
    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi - 0x1E;
    g_api.CheckCollision(x, y, &collider, 0);

    if (collider.effects & EFFECT_SOLID) {
        y = (g_CurrentEntity->posY.i.hi += collider.unk20);
    } else {
        return false;
    }

    if (g_CurrentEntity->velocityX == 0) {
        return true;
    }

    if (g_CurrentEntity->velocityX > 0) {
        x += 0x20;
        y -= 0x24;
    } else {
        x -= 0x20;
        y += 0x1C;
    }
    g_api.CheckCollision(x, y, &collider, 0);
    if (!(collider.effects & EFFECT_UNK_8000)) {
        return false;
    }
    return true;
}

#include "../approach_s16.h"

static AnimateEntityFrame D_pspeu_09254098[] = {{8, 30}, {8, 31}, {8, 32}, POSE_LOOP(0)};
static AnimateEntityFrame D_pspeu_092540A0[] = {{1, 31}, {2, 33}, {16, 34}, {6, 33}, {1, 31}, POSE_END};
static AnimateEntityFrame D_pspeu_092540B0[] = {{1, 31}, {2, 35}, {16, 36}, {6, 35}, {1, 31}, POSE_END};
static AnimateEntityFrame D_pspeu_092540C0[] = {{22, 11}, {8, 12}, {16, 13}, POSE_END};
static AnimateEntityFrame D_pspeu_092540C8[] = {{22, 25}, {8, 26}, {16, 27}, POSE_END};
static AnimateEntityFrame D_pspeu_092540D0[] = {{15, 13}, {5, 12}, {5, 14}, {5, 15}, {2, 14}, {2, 15}, {2, 11}, POSE_END};
static AnimateEntityFrame D_pspeu_092540E0[] = {{22, 25}, {6, 16}, {6, 17}, {22, 18}, {6, 17}, {6, 16}, {22, 25}, POSE_END};
static s16 g_RdaiArcherOffsets[][2] = {
    {3, -4}, {4, -5}, {-5, 4}, {-9, 6}
};


extern EInit g_EInitRdaiUnk1F;

void func_us_801BF830(Entity* self) {
    Entity* other;
    s32 temp_s3;
    s32 i;
    s32 var_s2;

    if (self->step) {
        other = self + 4;
        if (other->entityId != E_UNK_1C && self->step != 3) {
            SetStep(3);
        }
    }
    switch (self->step) {
    case 0x0:
        InitializeEntity(g_EInitRdaiUnk1F);
        other = self + 1;
        for (i = 0; i < 3; i++, other++) {
            CreateEntityFromEntity(E_UNK_1F, self, other);
            other->params = i;
        }
        other = self + 4;
        CreateEntityFromEntity(E_UNK_1C, self, other);
        SetStep(1);
        break;
    case 0x1:
        if (!self->step_s) {
            self->ext.rdaiArcher.timer = 0x80;
            self->step_s += 1;
        }
        if (self->ext.rdaiArcher.unk84 == 0) {
            self->velocityX += 0x400;
            if (self->velocityX > FIX(0.75)) {
                self->velocityX = FIX(0.75);
            }
        } else {
            self->velocityX -= 0x400;
            if (self->velocityX < FIX(-0.75)) {
                self->velocityX = FIX(-0.75);
            }
        }
        AnimateEntity(&D_pspeu_09254098, self);
        SpearGuardCheckCollision();
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_UNK_RDAI_76A);
        }
        if (!--self->ext.rdaiArcher.timer) {
            SetStep(2);
        }
        break;
    case 0x2:
        switch (self->step_s) {
        case 0:
            SpearGuardCheckCollision();
            temp_s3 = self->velocityX -= self->velocityX >> 8;
            if (abs(temp_s3) < 0x8000) {
                self->ext.rdaiArcher.unk84 ^= 1;
                self->velocityX = 0;
                self->step_s += 1;
            }
            break;
        case 2:
            if (self->ext.rdaiArcher.unk84 == 0) {
                self->velocityX += 0x400;
                if (self->velocityX > FIX(0.75)) {
                    self->velocityX = FIX(0.75);
                }
            } else {
                self->velocityX -= 0x400;
                if (self->velocityX < FIX(-0.75)) {
                    self->velocityX = FIX(-0.75);
                }
            }
            /* fallthrough */
        case 1:
            SpearGuardCheckCollision();
            if (self->ext.rdaiArcher.unk84 == 0) {
                var_s2 = AnimateEntity(&D_pspeu_092540B0, self);
            } else {
                var_s2 = AnimateEntity(&D_pspeu_092540A0, self);
            }
            if (self->pose > 2) {
                self->step_s = 2;
            }
            if (var_s2 == 0) {
                SetStep(1);
            }
        }
        break;
    case 0x3:
        PlaySfxPositional(SFX_FLEA_ARMOR_EXPLODE);
        for (i = 0; i < 9; i++) {
            if (i != 7) {
                other = AllocEntity(&g_Entities[0xE0], (Entity*)&D_80097C98);
                if (other != NULL) {
                    CreateEntityFromEntity(E_UNK_21, self, other);
                    other->params = (i + 1);
                }
            }
        }
        PreventEntityFromRespawning(self);
        DestroyEntity(self);
        return;
    case 0xFF:
#include "pad2_anim_debug.h"
    }
}

extern EInit g_EInitRdaiUnk1F;

#define RDAI_UNK1F_ANGLE(self) (*(s16*)((u8*)&(self)->ext + 0xC))

void EntityRdaiUnk1F(Entity* self) {
    Entity* entity;
    s32 velocity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRdaiUnk1F);
#if defined(VERSION_PSP)
        self->step = self->params + 1;
        self->hitboxOffX = -2;
        self->hitboxOffY = 6;
#else
        self->hitboxOffX = -2;
        self->hitboxOffY = 6;
        self->step = self->params + 1;
#endif
        break;

    case 1:
        self->animCurFrame = 2;
        entity = self - 1;
        if (entity->entityId != E_UNK_1E) {
            DestroyEntity(self);
            break;
        }
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->zPriority = entity->zPriority + 2;
        break;

    case 2:
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = 8;
        entity = self - 2;
        if (entity->entityId != E_UNK_1E) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_21, self, entity);
                entity->params = 8;
            }
            DestroyEntity(self);
            break;
        }
        self->posX.i.hi = entity->posX.i.hi + 0x1C;
        self->posY.i.hi = entity->posY.i.hi - 0x26;
        self->zPriority = entity->zPriority - 1;
        velocity = entity->velocityX >> 9;
        self->rotate -= velocity;
        RDAI_UNK1F_ANGLE(self) += velocity * 2;
        self->posY.i.hi += abs((rsin(RDAI_UNK1F_ANGLE(self)) << 3) >> 12);
        break;

    case 3:
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = 8;
        entity = self - 3;
        if (entity->entityId != E_UNK_1E) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_21, self, entity);
                entity->params = 8;
            }
            DestroyEntity(self);
            break;
        }
        self->posX.i.hi = entity->posX.i.hi - 0x20;
        self->posY.i.hi = entity->posY.i.hi + 0x18;
        self->zPriority = entity->zPriority + 1;
        velocity = entity->velocityX >> 9;
        self->rotate -= velocity;
        RDAI_UNK1F_ANGLE(self) += velocity * 2;
        self->posY.i.hi += abs((rsin(RDAI_UNK1F_ANGLE(self)) << 3) >> 12);
        break;
    }
}

#undef RDAI_UNK1F_ANGLE

extern EInit g_EInitArcher;

void func_us_801BFE6C(Entity* self) {
    Entity* entity;
    s32 i;
    s32 animIndex;
    s16 angle;
    s32 deltaX;
    s32 deltaY;

    entity = self - 4;
    self->posX.i.hi = entity->posX.i.hi + 0x28;
    self->posY.i.hi = entity->posY.i.hi + 0x10;
    animIndex = entity->animCurFrame - 0x21;
    if (animIndex >= 0) {
        s16* offsets = (s16*)g_RdaiArcherOffsets;
        offsets += animIndex * 2;
        self->posX.i.hi += offsets[0];
        self->posY.i.hi += offsets[1];
    }

    if ((self->flags & FLAG_DEAD) && self->step != 3) {
        SetStep(3);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitArcher);
        self->animCurFrame = 0x1D;
#if defined(VERSION_PSP)
        entity = self + 1;
        CreateEntityFromEntity(E_UNK_1D, self, entity);
        entity->params = 1;
        entity->nextPart = self;
        self->nextPart = entity;
        entity = self + 2;
        CreateEntityFromEntity(E_UNK_1D, self, entity);
        entity->params = 2;
        entity = self + 3;
        CreateEntityFromEntity(E_UNK_1D, self, entity);
        entity->params = 3;
#else
        CreateEntityFromEntity(E_UNK_1D, self, self + 1);
        (self + 1)->params = 1;
        (self + 1)->nextPart = self;
        self->nextPart = self + 1;
        CreateEntityFromEntity(E_UNK_1D, self, self + 2);
        (self + 2)->params = 2;
        CreateEntityFromEntity(E_UNK_1D, self, self + 3);
        (self + 3)->params = 3;
#endif
        // fallthrough

    case 1:
        if (!self->step_s) {
            self->ext.rdaiArcher.timer = 0x80;
            self->ext.rdaiArcher.mode = 0;
            self->step_s++;
        }
        entity = &PLAYER;
        deltaX = entity->posX.i.hi - self->posX.i.hi;
        deltaY = entity->posY.i.hi - self->posY.i.hi;
        angle = ratan2(deltaY, deltaX);
        if (angle > 0x200) {
            angle = 0x200;
        }
        if (angle < -0x200) {
            angle = -0x200;
        }
        func_801CDC80(&self->rotate, angle, 8);
        if (!--self->ext.rdaiArcher.timer) {
            SetStep(2);
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->ext.rdaiArcher.timer = 0x60;
            self->ext.rdaiArcher.mode = 1;
            self->step_s++;
            // fallthrough
        case 1:
            entity = &PLAYER;
            deltaX = entity->posX.i.hi - self->posX.i.hi;
            deltaY = entity->posY.i.hi - self->posY.i.hi;
            angle = ratan2(deltaY, deltaX);
            if (angle > 0x200) {
                angle = 0x200;
            }
            if (angle < -0x200) {
                angle = -0x200;
            }
            func_801CDC80(&self->rotate, angle, 8);
            if (!--self->ext.rdaiArcher.timer) {
                PlaySfxPositional(SFX_ARROW_SHOT_D);
                self->ext.rdaiArcher.mode = 2;
                self->ext.rdaiArcher.timer = 0x30;
                self->step_s++;
            }
            break;

        case 2:
            if (!--self->ext.rdaiArcher.timer) {
                self->ext.rdaiArcher.mode = 3;
                self->ext.rdaiArcher.timer = 0x80;
                self->step_s++;
            }
            break;

        case 3:
            if (!--self->ext.rdaiArcher.timer) {
                SetStep(1);
            }
            break;
        }
        break;

    case 3:
        for (i = 0; i < 3; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_21, self, entity);
                entity->params = i + 0x13;
            }
        }
        DestroyEntity(self);
        break;
    }
}
extern EInit g_EInitRdaiUnk1F;

void func_us_801C0240(Entity* self) {
    Entity* other;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRdaiUnk1F);
        self->drawFlags = ENTITY_ROTATE;
        self->step = self->params;
        self->hitboxState = 0;
        if (self->params == 1) {
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                CreateEntityFromEntity(E_UNK_20, self, other);
                other->ext.rdaiArcher.unk9C = self;
                other->zPriority = (self->zPriority - 1);
            }
        }
        break;
    case 1:
        other = self - 1;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->zPriority = other->zPriority + 3;
        self->rotate = other->rotate;
        switch (self->ext.rdaiArcher.mode) {
        case 1:
            AnimateEntity(&D_pspeu_092540C8, self);
            if ((!self->poseTimer) && (self->pose == 1)) {
                PlaySfxPositional(SFX_BONE_CREAK);
            }
            break;
        case 2:
            self->animCurFrame = 0x1B;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        case 3:
            AnimateEntity(&D_pspeu_092540E0, self);
            if ((!self->poseTimer) && (self->pose == 6)) {
                other = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_UNK_20, self, other);
                    other->ext.rdaiArcher.unk9C = self;
                    other->zPriority = self->zPriority - 1;
                }
                other = self - 1;
            }
            break;
        default:
            self->animCurFrame = 0x19;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        }
        self->ext.rdaiArcher.mode = other->ext.rdaiArcher.mode;
        if (other->entityId != E_UNK_1C) {
            DestroyEntity(self);
            return;
        }
        break;
    case 2:
        other = self - 2;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->zPriority = ((other->zPriority) - 1);
        self->rotate = other->rotate;
        self->animCurFrame = 0x1C;
        if (other->entityId != E_UNK_1C) {
            DestroyEntity(self);
            return;
        }
        break;
    case 3:
        other = self - 3;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->zPriority = ((other->zPriority) + 1);
        self->rotate = other->rotate;
        switch (self->ext.rdaiArcher.mode) {
        case 1:
            AnimateEntity(&D_pspeu_092540C0, self);
            if (other->ext.rdaiArcher.mode == 2) {
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.rdaiArcher.mode = 2;
            }
            break;
        case 2:
            AnimateEntity(&D_pspeu_092540D0, self);
            break;
        case 3:
            self->animCurFrame = 0xB;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        default:
            self->animCurFrame = 0xB;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        }
        self->ext.rdaiArcher.mode = other->ext.rdaiArcher.mode;
        if (other->entityId != E_UNK_1C) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180884;

void func_us_801C0528(Entity* self) {
    Entity* other;
    s16 angle;
    s32 var_s1;
    s32 var_s3;

    switch (self->step) { /* irregular */
    case 0:
        InitializeEntity(D_us_80180884);
        self->animCurFrame = 0x16;
        self->drawFlags |= ENTITY_ROTATE;
        self->hitboxState = 0;
        if (self->params) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                           FLAG_UNK_00200000 | FLAG_UNK_2000;
            self->animCurFrame += self->params;
            if ((self->params) == 1) {
                self->velocityX = FIX(0.5);
            } else {
                self->velocityX = FIX(-0.5);
            }
            self->step = 4;
            return;
        }
    case 1:
        other = self->ext.rdaiArcher.unk9C;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->rotate = other->rotate;
        angle = self->rotate;
        var_s3 = 0x18;
        if (other->animCurFrame == 0x1A) {
            var_s3 = 0xE;
        }
        if (other->animCurFrame == 0x1B) {
            var_s3 = 8;
        }
        self->posX.i.hi += (var_s3 * rcos(angle)) >> 0xC;
        self->posY.i.hi += (var_s3 * rsin(angle)) >> 0xC;
        if (other->entityId != E_UNK_1D) {
            DestroyEntity(self);
            return;
        }
        if ((other->ext.rdaiArcher.mode) == 2) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->velocityX = (rcos(angle) * 0x50000) >> 0xC;
            self->velocityY = (rsin(angle) * 0x50000) >> 0xC;
            self->hitboxState = 3;
            self->hitboxOffX = (rcos(angle) * 8) >> 0xC;
            self->hitboxOffY = (rsin(angle) * 8) >> 0xC;
            self->hitboxWidth = self->hitboxHeight = 4;
            self->step = 2;
        }
        break;
    case 2:
        MoveEntity();
        if (self->flags & FLAG_DEAD) {
            for (var_s1 = 0; var_s1 < 2; var_s1++) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_UNK_20, self, other);
                    other->params = var_s1 + 1;
                    other->rotate = self->rotate;
                }
            }
            DestroyEntity(self);
            return;
        }
        if (self->hitFlags & 0x80) {
            other = &PLAYER;
            self->ext.rdaiArcher.unk94 = other->posX.i.hi - self->posX.i.hi;
            self->ext.rdaiArcher.unk96 = other->posY.i.hi - self->posY.i.hi;
            self->ext.rdaiArcher.timer = 0x20;
            self->hitboxState = 0;
            self->step += 1;
            return;
        }
        break;
    case 3:
        other = &PLAYER;
        self->posX.i.hi = other->posX.i.hi - self->ext.rdaiArcher.unk94;
        self->posY.i.hi = other->posY.i.hi - self->ext.rdaiArcher.unk96;
        if (!--self->ext.rdaiArcher.timer) {
            DestroyEntity(self);
            return;
        }
        break;
    case 4:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->params == 1) {
            self->rotate += ROT(2.8125);
        } else {
            self->rotate -= ROT(2.8125);
        }
        break;
    }
}

extern s16* sprites_rdai_2[];

extern EInit D_us_80180890;

void func_us_801C0898(Entity* self) {
    Entity* other;
    s16 temp_s4;
    s32 temp_s3;
    s32 temp_s2;
    s16* temp_s1;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180890);
        self->animCurFrame = self->params;
        temp_s1 = sprites_rdai_2[self->animCurFrame];
        temp_s3 = temp_s1[2];
        temp_s2 = temp_s1[3];
        temp_s3 += temp_s1[4] / 2;
        temp_s2 += temp_s1[5] / 2;
        self->ext.rdaiArcher.unk94 = temp_s3;
        self->ext.rdaiArcher.unk96 = temp_s2;
        self->ext.rdaiArcher.timer = ((Random() & 0xF) + 8);
        temp_s4 = ratan2(temp_s2, temp_s3);
        self->velocityX = (rcos(temp_s4) << 0x11) >> 0xC;
        self->velocityY = (rsin(temp_s4) << 0x11) >> 0xC;
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, other);
            other->posX.i.hi += temp_s3;
            other->posY.i.hi += temp_s2;
            other->params = 1;
        }
        if (self->params > 0x12) {
            self->step = 2;
        }
        break;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (!--self->ext.rdaiArcher.timer) {
            PlaySfxPositional(SFX_EXPLODE_D);
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, other);
                other->posX.i.hi += self->ext.rdaiArcher.unk94;
                other->posY.i.hi += self->ext.rdaiArcher.unk96;
                other->params = 1;
            }
            DestroyEntity(self);
            return;
        }
        break;
    case 2:
        switch (self->params) {
        case 19:
            if (!self->step_s) {
                self->velocityY = FIX(-2.5);
                self->ext.rdaiArcher.timer = 0x10;
                self->step_s += 1;
            }
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!--self->ext.rdaiArcher.timer) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->posX.i.hi += self->ext.rdaiArcher.unk94;
                    other->posY.i.hi += self->ext.rdaiArcher.unk96;
                    other->params = 1;
                }
                DestroyEntity(self);
                return;
            }
            break;
        case 20:
            if (!self->step_s) {
                self->ext.rdaiArcher.timer = 0x18;
                self->velocityX = 0;
                self->velocityY = 0;
                self->step_s += 1;
            }
            MoveEntity();
            self->velocityY += FIX(0.03125);
            if (!--self->ext.rdaiArcher.timer) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->posX.i.hi += self->ext.rdaiArcher.unk94;
                    other->posY.i.hi += self->ext.rdaiArcher.unk96;
                    other->params = 1;
                }
                DestroyEntity(self);
                return;
            }
            break;
        case 21:
            if (!self->step_s) {
                self->ext.rdaiArcher.timer = 0x40;
                self->velocityY = 0;
            }
            MoveEntity();
            self->velocityY += FIX(0.1875);
        }
        break;
    }
}
