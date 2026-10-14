// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

typedef struct {
    AnimateEntityFrame* anim;
    s16 values[4];
} ScyllaPartInit;

s32 D_us_80180D48 = 0;

AnimateEntityFrame D_us_80180D4C[] = {
    POSE(18, 1, 0), POSE(18, 2, 0), POSE(18, 3, 0),
    POSE(18, 2, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180D58[] = {
    POSE(4, 1, 0), POSE(7, 5, 0), POSE(7, 6, 0),  POSE(7, 7, 0),
    POSE(7, 8, 0), POSE(7, 9, 0), POSE(7, 10, 0), POSE_END,
};

AnimateEntityFrame D_us_80180D68[] = {
    POSE(8, 7, 0), POSE(8, 8, 0), POSE(8, 9, 0), POSE(8, 10, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180D74[] = {
    POSE(4, 9, 0),  POSE(4, 10, 0), POSE(2, 7, 0),  POSE(2, 6, 0),
    POSE(1, 11, 0), POSE(1, 12, 0), POSE(1, 13, 0), POSE(48, 14, 0),
    POSE(6, 15, 0), POSE(6, 16, 0), POSE(2, 1, 0),  POSE_END,
};

AnimateEntityFrame D_us_80180D8C[] = {
    POSE(2, 1, 0),  POSE(10, 20, 0), POSE(10, 21, 0), POSE(8, 22, 0),
    POSE(8, 23, 0), POSE(8, 24, 0),  POSE(1, 25, 0),  POSE_END,
};

AnimateEntityFrame D_us_80180D9C[] = {
    POSE(8, 22, 0), POSE(8, 23, 0), POSE(8, 24, 0),
    POSE(8, 25, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180DA8[] = {
    POSE(2, 22, 0),  POSE(8, 23, 0), POSE(10, 26, 0),
    POSE(10, 27, 0), POSE(8, 1, 0),  POSE_END,
};

AnimateEntityFrame D_us_80180DB4[] = {
    POSE(1, 1, 0),   POSE(3, 17, 0),  POSE(3, 18, 0),
    POSE(16, 19, 0), POSE(16, 19, 0), POSE(6, 18, 0),
    POSE(6, 17, 0),  POSE(1, 1, 0),   POSE_END,
};

AnimateEntityFrame D_us_80180DC8[] = {
    POSE(1, 1, 0), POSE(4, 17, 0), POSE(4, 18, 0), POSE(64, 19, 0), POSE_END,
};

AnimateEntityFrame D_us_80180DD4[] = {
    POSE(20, 28, 0), POSE(20, 29, 0), POSE(20, 30, 0),
    POSE(20, 29, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180DE0[] = {
    POSE(1, 28, 0),
    POSE(1, 31, 0),
    POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180DE8[] = {
    POSE(1, 28, 0),  POSE(10, 32, 0), POSE(16, 33, 0), POSE(10, 34, 0),
    POSE(16, 35, 0), POSE(10, 36, 0), POSE(16, 37, 0), POSE(8, 38, 0),
    POSE(8, 39, 0),  POSE(8, 40, 0),  POSE(8, 41, 0),  POSE(8, 28, 0),
    POSE_END,
};

AnimateEntityFrame D_us_80180E04[] = {
    POSE(2, 28, 0), POSE(6, 46, 0), POSE(6, 47, 0),
    POSE(6, 48, 0), POSE(6, 49, 0), POSE(22, 50, 0),
    POSE(8, 32, 0), POSE(1, 33, 0), POSE_END,
};

AnimateEntityFrame D_us_80180E18[] = {
    POSE(4, 33, 0), POSE(6, 42, 0), POSE(6, 43, 0), POSE(6, 44, 0),
    POSE(6, 45, 0), POSE(2, 28, 0), POSE_END,
};

// unused
static AnimateEntityFrame anim_unused_0[] = {
    POSE(32, 28, 0), POSE(4, 36, 0),  POSE(6, 37, 0),  POSE(4, 51, 0),
    POSE(6, 52, 0),  POSE(4, 53, 0),  POSE(26, 54, 0), POSE(6, 53, 0),
    POSE(6, 52, 0),  POSE(4, 51, 0),  POSE(4, 34, 0),  POSE(6, 35, 0),
    POSE(6, 55, 0),  POSE(4, 56, 0),  POSE(26, 57, 0), POSE(6, 56, 0),
    POSE(6, 55, 0),  POSE(4, 32, 0),  POSE(6, 33, 0),  POSE(6, 58, 0),
    POSE(4, 59, 0),  POSE(26, 60, 0), POSE(6, 59, 0),  POSE(6, 58, 0),
    POSE(2, 28, 0),  POSE_END,
};

AnimateEntityFrame D_us_80180E5C[] = {
    POSE(16, 28, 0), POSE(4, 36, 0), POSE(6, 37, 0),  POSE(4, 51, 0),
    POSE(6, 52, 0),  POSE(4, 53, 0), POSE(10, 54, 0), POSE_END,
};

AnimateEntityFrame D_us_80180E6C[] = {
    POSE(16, 54, 0), POSE(6, 53, 0), POSE(6, 52, 0), POSE(4, 51, 0),
    POSE(4, 34, 0),  POSE(6, 35, 0), POSE(6, 55, 0), POSE(4, 56, 0),
    POSE(10, 57, 0), POSE_END,
};

AnimateEntityFrame D_us_80180E80[] = {
    POSE(16, 57, 0), POSE(6, 56, 0),  POSE(6, 55, 0),
    POSE(4, 32, 0),  POSE(6, 33, 0),  POSE(6, 58, 0),
    POSE(4, 59, 0),  POSE(10, 60, 0), POSE_END,
};

AnimateEntityFrame D_us_80180E94[] = {
    POSE(16, 60, 0), POSE(6, 59, 0), POSE(6, 58, 0), POSE(2, 28, 0), POSE_END,
};

static AnimateEntityFrame D_us_80180EA0[] = {
    POSE(20, 61, 0), POSE(20, 62, 0), POSE(20, 63, 0),
    POSE(20, 62, 0), POSE_LOOP(0),
};

static AnimateEntityFrame D_us_80180EAC[] = {
    POSE(4, 62, 0),  POSE(20, 63, 0), POSE(20, 62, 0),
    POSE(20, 61, 0), POSE(16, 62, 0), POSE_LOOP(0),
};

static AnimateEntityFrame D_us_80180EB8[] = {
    POSE(20, 64, 0), POSE(20, 65, 0), POSE(20, 66, 0),
    POSE(20, 65, 0), POSE_LOOP(0),
};

static AnimateEntityFrame D_us_80180EC4[] = {
    POSE(20, 67, 0),
    POSE(20, 68, 0),
    POSE(20, 69, 0),
    POSE_LOOP(0),
};

static AnimateEntityFrame D_us_80180ECC[] = {
    POSE(20, 70, 0), POSE(20, 71, 0), POSE(20, 72, 0),
    POSE(20, 71, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180ED8[] = {
    POSE(8, 80, 0), POSE(8, 81, 0), POSE(8, 82, 0),
    POSE(8, 83, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180EE4[] = {
    POSE(1, 85, 0), POSE(1, 88, 0), POSE(1, 86, 0), POSE(1, 89, 0),
    POSE(1, 87, 0), POSE(1, 90, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180EF4[] = {
    POSE(4, 91, 0), POSE(4, 92, 0), POSE(4, 93, 0), POSE(4, 94, 0),
    POSE(1, 85, 0), POSE(1, 88, 0), POSE(1, 86, 0), POSE(1, 89, 0),
    POSE(1, 87, 0), POSE(1, 90, 0), POSE_END,
};

AnimateEntityFrame D_us_80180F0C[] = {
    POSE(7, 95, 0), POSE(7, 96, 0), POSE(7, 97, 0),
    POSE(7, 98, 0), POSE(7, 99, 0), POSE_END,
};

AnimateEntityFrame D_us_80180F18[] = {
    POSE(8, 100, 0), POSE(8, 101, 0), POSE(8, 100, 0),
    POSE(8, 102, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180F24[] = {
    POSE(4, 100, 0), POSE(4, 101, 0), POSE(4, 100, 0),
    POSE(4, 102, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180F30[] = {
    POSE(2, 100, 0), POSE(8, 103, 0), POSE(8, 104, 0),  POSE(8, 105, 0),
    POSE(8, 106, 0), POSE(8, 107, 0), POSE(16, 108, 0), POSE_END,
};

AnimateEntityFrame D_us_80180F40[] = {
    POSE(8, 109, 0), POSE(8, 108, 0), POSE(8, 110, 0),
    POSE(8, 108, 0), POSE_LOOP(0),
};

ScyllaPartInit D_us_80180F4C[] = {
    {D_us_80180EA0, {0x0086, 0x0078, 0x00B0, 0x0000}},
    {D_us_80180EAC, {0x0084, 0x0088, 0x00B0, 0x0000}},
    {D_us_80180EB8, {0x0090, 0x0050, 0x00AC, 0x0000}},
    {D_us_80180EC4, {0x0086, 0x0024, 0x0090, 0x0000}},
    {D_us_80180ECC, {0x0084, 0x0020, 0x0088, 0x0000}},
};

s16 D_us_80180F88[] = {16, 8, 8, 8};

s16 D_us_80180F90[] = {0, 8, 0, 4, 4, -4, -8, 0};

s16 D_us_80180FA0[] = {-16, -16, 0, 0};

s16 D_us_80180FA8[] = {16, -16, 0, 0};

s16 D_us_80180FB0[] = {-16, 16, 0, 0};

s16 D_us_80180FB8[] = {16, 16, 0, 0};

// unused
static AnimateEntityFrame anim_unused_1[] = {
    POSE(16, 73, 0), POSE(16, 74, 0), POSE(16, 73, 0),
    POSE(16, 75, 0), POSE_LOOP(0),
};

#ifdef VERSION_PSP
char D_pspeu_09266160[] = "charal %x\n";
#endif

// static once func_us_801A42A8 is C
s32 func_us_801A2A90(Primitive* prim, s32 amount) {
    s32 isEnd;
    s32 i, j;
    u8* pColor;
    s32 col;

    pColor = &prim->r0;
    isEnd = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++, pColor++) {
            col = *pColor;
            col = col - amount;
            if (col <= 0) {
                col = 0;
            } else {
                isEnd = 1;
            }
            *pColor = col;
        }
        pColor += 9;
    }
    return isEnd;
}

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A2AEC);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A365C);

extern EInit D_us_801805B8;

void func_us_801A3CD8(Entity* self) {
    ScyllaPartInit* part;

    if (D_us_80180D48 & 0x10) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805B8);
        part = &D_us_80180F4C[self->params];
        self->zPriority = part->values[0];
        self->posX.i.hi = part->values[1] - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = part->values[2] - g_Tilemap.scrollY.i.hi;
        /* fall through */
    case 1:
        part = &D_us_80180F4C[self->params];
        AnimateEntity(part->anim, self);
        if (D_us_80180D48 & 2) {
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            if (D_us_80180D48 & 0x40) {
                self->step_s++;
            }
            break;

        case 1:
            self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY;
            self->scaleX = self->scaleY = 0x100;
            self->step_s++;
            /* fall through */
        case 2:
            if (self->scaleX > 0x80) {
                self->scaleX = --self->scaleY;
            }
            break;
        }
        part = &D_us_80180F4C[self->params];
        AnimateEntity(part->anim, self);
        break;
    }
}

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A3EE0);

extern EInit g_EInitInteractable;

void func_us_801A42A8(Entity* self) {
    Primitive* prim;
    s32 dy;
    s32 isDone;
    s32 primIndex;
    s32 dx;

    if (D_us_80180D48 & 2) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.func_800EDB58(PRIM_LINE_G2_ALT, 0x12);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.scyllaBeam.prim = prim;
        while (prim != NULL) {
            prim->r0 = 0x20;
            prim->g0 = 0x28;
            prim->b0 = 0xC0;
            prim->r1 = 0x10;
            prim->g1 = 0x10;
            prim->b1 = 0x60;
            prim->priority = 0x98;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.scyllaBeam.timer = (Random() & 7) * self->params;
        /* fall through */
    case 1:
        if (self->ext.scyllaBeam.timer) {
            self->ext.scyllaBeam.timer--;
            break;
        }
        dx = 0x5C - g_Tilemap.scrollX.i.hi;
        dy = 0x54 - g_Tilemap.scrollY.i.hi;
        dx = (dx - self->posX.i.hi) << 16;
        dy = (dy - self->posY.i.hi) << 16;
        dx /= 32;
        self->velocityX = dx;
        self->velocityY = FIX(-8.25);
        prim = self->ext.scyllaBeam.prim;
        self->ext.scyllaBeam.curPrim = prim;
        prim->x0 = prim->x1 = self->posX.i.hi;
        prim->y0 = prim->y1 = self->posY.i.hi;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        self->ext.scyllaBeam.timer = 0x20;
        self->step++;
        /* fall through */
    case 2:
        switch (self->step_s) {
        case 0:
            MoveEntity();
            self->velocityY += FIX(0.25);
            if (self->velocityY > 0) {
                self->step_s++;
            }
            break;

        case 1:
            dy = 0x54 - g_Tilemap.scrollY.i.hi;
            dy = (dy - self->posY.i.hi) << 16;
            self->velocityY = dy / self->ext.scyllaBeam.timer;
            self->step_s++;
            /* fall through */
        case 2:
            MoveEntity();
            break;
        }
        prim = self->ext.scyllaBeam.curPrim;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        self->ext.scyllaBeam.timer--;
        if (!self->ext.scyllaBeam.timer) {
            self->step++;
        } else if (!(self->ext.scyllaBeam.timer & 3)) {
            prim = prim->next;
            self->ext.scyllaBeam.curPrim = prim;
            prim->x0 = prim->x1 = self->posX.i.hi;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        }
        /* fall through */
    case 3:
        isDone = true;
        prim = self->ext.scyllaBeam.prim;
        while (prim->next != NULL) {
            if (prim->drawMode != DRAW_HIDE) {
                if (!func_us_801A2A90(prim, 1)) {
                    prim->drawMode = DRAW_HIDE;
                } else {
                    isDone = false;
                }
            }
            prim = prim->next;
        }
        prim->x0 = prim->x1 = prim->y0 = prim->y1 = 0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        if (isDone) {
            DestroyEntity(self);
        }
        break;
    }
}

#ifndef VERSION_PSP
const u32 D_us_8019CA94[3] = {0, 0, 0};
#endif

extern EInit D_us_801805D0;

void func_us_801A4680(Entity* self) {
    Entity* entity;
    s16 angle;
    s32 i;
    s32 dx;
    s32 dy;

    if (D_us_80180D48 & 2) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        for (i = 0; i < 5; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_39), self, entity);
                entity->zPriority = self->zPriority;
                entity->params = 1;
            }
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805D0);
        self->zPriority = 0x8C;
        self->hitboxState = 0;
        /* fall through */
    case 1:
        if (!AnimateEntity(D_us_80180F0C, self)) {
            self->velocityY = FIX(-4);
            self->ext.scyllaParticle.unk80 = 0x50;
            self->hitboxState = 2;
            SetStep(2);
        }
        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(SFX_BONE_SWORD_SWISH_C);
        }
        break;

    case 2:
        AnimateEntity(D_us_80180F18, self);
        MoveEntity();
        self->velocityY -= self->velocityY >> 4;
        if (!--self->ext.scyllaParticle.unk80) {
            self->ext.scyllaParticle.unk80 = 0x80;
            self->rotate = Random() << 4;
            self->step++;
        }
        break;

    case 3:
        AnimateEntity(D_us_80180F18, self);
        MoveEntity();
        angle = self->rotate += ROT(2.8125);
        self->velocityY = rsin(angle) << 3;
        if (!--self->ext.scyllaParticle.unk80) {
            SetStep(4);
        }
        break;

    case 4:
        if (!AnimateEntity(D_us_80180F30, self)) {
            SetStep(5);
        }
        break;

    case 5:
        entity = &PLAYER;
        dx = entity->posX.i.hi - self->posX.i.hi;
        dy = entity->posY.i.hi - self->posY.i.hi;
        angle = ratan2(dy, dx);
        self->velocityX = rcos(angle) * 7 << 4;
        self->velocityY = rsin(angle) * 7 << 4;
        if (self->velocityX > 0) {
            self->facingLeft = 0;
        } else {
            self->facingLeft = 1;
        }
        self->hitboxState = 3;
        PlaySfxPositional(SFX_ARROW_SHOT_A);
        self->step++;
        /* fall through */
    case 6:
        AnimateEntity(D_us_80180F40, self);
        MoveEntity();
        break;
    }
}

extern EInit D_us_801805DC;

void func_us_801A4988(Entity* self) {
    Entity* entity;
    s16 angle;
    s32 i;
    s32 dx;
    s32 dy;

    if (D_us_80180D48 & 2) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        for (i = 0; i < 0x10; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_39), self, entity);
                entity->zPriority = self->zPriority;
            }
        }
        PlaySfxPositional(SFX_SCYLLA_BUBBLE_BURST);
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805DC);
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->hitPoints = 0;
        /* fall through */
    case 1:
        if (!AnimateEntity(D_us_80180EF4, self)) {
            SetStep(2);
        }
        break;

    case 2:
        entity = &PLAYER;
        dx = entity->posX.i.hi - self->posX.i.hi;
        dy = entity->posY.i.hi - self->posY.i.hi;
        angle = ratan2(dy, dx);
        if (angle > 0x200) {
            angle = 0x200;
        }
        if (angle < -0x180) {
            angle = -0x180;
        }
        self->velocityX = rcos(angle) * 5 << 4;
        self->velocityY = rsin(angle) * 5 << 4;
        self->ext.scyllaFireball.angle = angle;
        PlaySfxPositional(SFX_EXPLODE_B);
        self->step++;
        /* fall through */
    case 3:
        AnimateEntity(D_us_80180EE4, self);
        MoveEntity();
        entity = &PLAYER;
        angle = GetAngleBetweenEntities(self, entity);
        angle = LimitAngleChange(8, self->ext.scyllaFireball.angle, angle);
        self->velocityX = rcos(angle) * 5 << 4;
        self->velocityY = rsin(angle) * 5 << 4;
        self->ext.scyllaFireball.angle = angle;
        break;
    }
}

extern EInit D_us_801805E8;

void func_us_801A4C0C(Entity* self) {
    Entity* newEntity;
    s32 posY;
    s16 posX;
    u32 pad[10];

    if (D_us_80180D48 & 2) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805E8);
        self->drawFlags = ENTITY_ROTATE;
        self->params = Random() & 3;
        self->animCurFrame = self->params + 0x6F;
        self->rotate = rand() & 0xFFF;
        PlaySfxPositional(SFX_WALL_DEBRIS_B);
        /* fall through */
    case 1:
        self->rotate += ROT(11.25);
        if (self->posY.i.hi < 0x80) {
            MoveEntity();
            self->velocityY += FIX(0.125);
            break;
        }
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + D_us_80180F88[self->params];
        posY += g_Tilemap.scrollY.i.hi;
        if (posY > 0xD8 && !self->ext.scyllaParticle.splashed) {
            self->ext.scyllaParticle.splashed = true;
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ID(SPLASH_WATER), self, newEntity);
                newEntity->params = 0;
                newEntity->posY.i.hi = 0xD8 - g_Tilemap.scrollY.i.hi;
            }
        }
        if (UnkCollisionFunc3(D_us_80180F90) & 1) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x11;
            } else {
                FntPrint("no WORK !!\n");
            }
            DestroyEntity(self);
            break;
        }
        self->velocityY -= FIX(0.125);
        break;
    }
}

extern EInit D_us_801805F4;

void func_us_801A4E24(Entity* self) {
    s32 speed;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805F4);
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        if (!self->params) {
            self->scaleX = self->scaleY = (Random() & 0x7F) + 0x40;
        } else {
            self->scaleX = self->scaleY = (Random() & 0x3F) + 0x20;
        }
        self->blendMode = BLEND_TRANSP;
        self->facingLeft = Random() & 1;
        speed = (Random() & 0x1F) + 0x10;
        angle = Random() * 6 + 0x900;
        self->velocityX = (speed * rcos(angle)) >> 1;
        self->velocityY = speed * rsin(angle);
        if (self->params) {
            self->velocityX >>= 1;
            self->velocityY >>= 1;
        }
        self->posX.val += self->velocityX << 2;
        self->posY.val += self->velocityY << 2;
        self->ext.scyllaParticle.unk80 = (Random() & 0x1F) + 0x10;
        /* fall through */
    case 1:
        AnimateEntity(D_us_80180F24, self);
        MoveEntity();
        if (self->velocityY < FIX(3)) {
            self->velocityY += FIX(5.0 / 64);
        }
        break;
    }
}
