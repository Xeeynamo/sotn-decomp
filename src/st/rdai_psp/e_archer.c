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

extern AnimateEntityFrame D_pspeu_09254098[];
extern AnimateEntityFrame D_pspeu_092540A0[];
extern AnimateEntityFrame D_pspeu_092540B0[];
extern EInit g_EInitRdaiUnk1F;

void func_us_801BF830(Entity* self) {
    Entity* other;
    s32 temp_s3;
    s32 i;
    s32 var_s2;

    if (self->step){
        other = self + 4;
        if(other->entityId != 0x1C && self->step != 3){
            SetStep(3);
        }
    }
    switch (self->step) {                              /* switch 1; irregular */
    case 0x0:                                       /* switch 1 */
        InitializeEntity(g_EInitRdaiUnk1F);
        other = self + 1;
        for(i = 0; i < 3; i++, other++) {
            CreateEntityFromEntity(0x1F, self, other);
            other->params = i;
        }
        other = self + 4;
        CreateEntityFromEntity(0x1C, self, other);
        SetStep(1);
        break;
    case 0x1:                                       /* switch 1 */
        if (!self->step_s) {
            self->ext.ILLEGAL.s16[2] = 0x80;
            self->step_s += 1;
        }
        if (self->ext.ILLEGAL.u8[8] == 0) {
            self->velocityX += 0x400;
            if (self->velocityX > 0xC000) {
                self->velocityX = 0xC000;
            }
        } else {
            self->velocityX -= 0x400;
            if (self->velocityX < -0xC000) {
                self->velocityX = -0xC000;
            }
        }
        AnimateEntity(&D_pspeu_09254098, self);
        SpearGuardCheckCollision();
        if (!(g_Timer & 7)) {
            PlaySfxPositional(0x76A);
        }
        if (!--self->ext.ILLEGAL.s16[2]) {
            SetStep(2);
        }
        break;
    case 0x2:                                       /* switch 1 */
        switch (self->step_s) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            SpearGuardCheckCollision();
            temp_s3 = self->velocityX -= self->velocityX >> 8;
            if (abs(temp_s3) < 0x8000) {
                self->ext.ILLEGAL.u8[8] ^= 1;
                self->velocityX = 0;
                self->step_s += 1;
            }
            break;
        case 2:                                     /* switch 2 */
            if (self->ext.ILLEGAL.u8[8] == 0) {
                self->velocityX += 0x400;
                if (self->velocityX > 0xC000) {
                    self->velocityX = 0xC000;
                }
            } else {
                self->velocityX -= 0x400;
                if (self->velocityX < -0xC000) {
                    self->velocityX = -0xC000;
                }
            }
            /* fallthrough */
        case 1:                                     /* switch 2 */
            SpearGuardCheckCollision();
            if (self->ext.ILLEGAL.u8[8] == 0) {
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
    case 0x3:                                       /* switch 1 */
        PlaySfxPositional(0x6CA);
        for(i = 0; i < 9; i++) {
            if (i != 7) {
                other = AllocEntity(&g_Entities[0xE0], (Entity* ) &D_80097C98);
                if (other != NULL) {
                    CreateEntityFromEntity(0x21, self, other);
                    other->params = (i + 1);
                }
            }
        }
        PreventEntityFromRespawning(self);
        DestroyEntity(self);
        return;
    case 0xFF:                                      /* switch 1 */
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
extern s16 g_RdaiArcherOffsets[][2];

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

extern AnimateEntityFrame D_pspeu_092540C0[];
extern AnimateEntityFrame D_pspeu_092540C8[];
extern AnimateEntityFrame D_pspeu_092540D0[];
extern AnimateEntityFrame D_pspeu_092540E0[];
extern EInit g_EInitRdaiUnk1F;

void func_us_801C0240(Entity* self) {
    Entity* other;

    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(g_EInitRdaiUnk1F);
        self->drawFlags = 4;
        self->step = self->params;
        self->hitboxState = 0;
        if (self->params == 1) {
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                CreateEntityFromEntity(0x20, self, other);
                other->ext.ILLEGAL.u32[8] = (u32) self;
                other->zPriority = (self->zPriority - 1);
            }
        }
        break;
    case 1:                                         /* switch 1 */
        other = self - 1;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->zPriority = other->zPriority + 3;
        self->rotate = other->rotate;
        switch (self->ext.ILLEGAL.u8[9]) {                        /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            AnimateEntity(&D_pspeu_092540C8, self);
            if ((!self->poseTimer) && (self->pose == 1)) {
                PlaySfxPositional(0x6C9);
            }
            break;
        case 2:                                     /* switch 2 */
            self->animCurFrame = 0x1B;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        case 3:                                     /* switch 2 */
            AnimateEntity(&D_pspeu_092540E0, self);
            if ((!self->poseTimer) && (self->pose == 6)) {
                other = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
                if (other != NULL) {
                    CreateEntityFromEntity(0x20, self, other);
                    other->ext.ILLEGAL.u32[8] = (u32) self;
                    other->zPriority = self->zPriority - 1;
                }
                other = self - 1;
            }
            break;
        default:                                    /* switch 2 */
            self->animCurFrame = 0x19;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        }
        self->ext.ILLEGAL.u8[9] = other->ext.ILLEGAL.u8[9];
        if ((other->entityId) != 0x1C) {
            DestroyEntity(self);
            return;
        }
        break;
    case 2:                                         /* switch 1 */
        other = self - 2;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->zPriority = ((other->zPriority) - 1);
        self->rotate = other->rotate;
        self->animCurFrame = 0x1C;
        if ((other->entityId) != 0x1C) {
            DestroyEntity(self);
            return;
        }
        break;
    case 3:                                         /* switch 1 */
        other = self - 3;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->zPriority = ((other->zPriority) + 1);
        self->rotate = other->rotate;
        switch (self->ext.ILLEGAL.u8[9]) {                        /* switch 3; irregular */
        case 1:                                     /* switch 3 */
            AnimateEntity(&D_pspeu_092540C0, self);
            if (other->ext.ILLEGAL.u8[9] == 2) {
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.ILLEGAL.u8[9] = 2;
            }
            break;
        case 2:                                     /* switch 3 */
            AnimateEntity(&D_pspeu_092540D0, self);
            break;
        case 3:                                     /* switch 3 */
            self->animCurFrame = 0xB;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        default:                                    /* switch 3 */
            self->animCurFrame = 0xB;
            self->pose = 0;
            self->poseTimer = 0;
            break;
        }
        self->ext.ILLEGAL.u8[9] = other->ext.ILLEGAL.u8[9];
        if ((other->entityId) != 0x1C) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/rdai_psp/nonmatchings/rdai_psp/e_archer", func_us_801C0528);

INCLUDE_ASM("st/rdai_psp/nonmatchings/rdai_psp/e_archer", func_us_801C0898);
