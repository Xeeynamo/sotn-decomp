// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo1.h"

typedef struct {
    /* 0x0 */ u16 animSet;
    /* 0x2 */ u16 unk5A;
    /* 0x4 */ u16 palette;
    /* 0x6 */ u16 blendMode;
    /* 0x8 */ AnimateEntityFrame* anim;
} EInitUnk22;

extern EInit g_EInitParticle;

static AnimateEntityFrame anim0[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(3, 3, 0),  POSE(3, 4, 0),
    POSE(3, 5, 0),  POSE(3, 6, 0),  POSE(3, 7, 0),  POSE(3, 8, 0),
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE_END};
static AnimateEntityFrame anim1[] = {
    POSE(3, 1, 0),  POSE(3, 2, 0),  POSE(3, 3, 0),  POSE(3, 4, 0),
    POSE(3, 5, 0),  POSE(3, 6, 0),  POSE(3, 7, 0),  POSE(3, 8, 0),
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE_END};
static UNUSED AnimateEntityFrame anim2[] = { // unused, copy of anim1
    POSE(2, 1, 0),  POSE(2, 2, 0),  POSE(2, 3, 0),  POSE(2, 4, 0),
    POSE(2, 5, 0),  POSE(2, 6, 0),  POSE(2, 7, 0),  POSE(2, 8, 0),
    POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE_END};
static AnimateEntityFrame anim3[] = {
    POSE(2, 1, 0),  POSE(2, 2, 0),  POSE(2, 3, 0),  POSE(2, 4, 0),
    POSE(2, 5, 0),  POSE(2, 6, 0),  POSE(2, 7, 0),  POSE(2, 8, 0),
    POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE(2, 14, 0), POSE_END};
static EInitUnk22 D_pspeu_092683B0[] = {
    {ANIMSET_DRA(14), 0x0079, 0x0000, BLEND_ADD | BLEND_TRANSP, anim0},
    {ANIMSET_DRA(14), 0x0079, 0x0000, BLEND_QUARTER | BLEND_TRANSP, anim0},
    {ANIMSET_OVL(4), 0x0058, 0x000F, BLEND_TRANSP, anim3},
    {ANIMSET_OVL(4), 0x0058, 0x0004, BLEND_ADD | BLEND_TRANSP, anim3},
    {ANIMSET_DRA(14), 0x0079, 0x0004, BLEND_ADD | BLEND_TRANSP, anim0},
    {ANIMSET_OVL(5), 0x0059, 0x0006, BLEND_ADD | BLEND_TRANSP, anim1},
    {ANIMSET_OVL(5), 0x0059, 0x0006, BLEND_ADD | BLEND_TRANSP, anim1},
};

#ifdef VERSION_PSP
extern s32 E_ID(EXPLOSION_FLAME);
#endif

void func_us_8019D260_from_rcen(void) {
    s16 temp_s3;
    s32 i;
    s8 temp_s4;
    Entity* entity;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(
                E_ID(EXPLOSION_FLAME), g_CurrentEntity, entity);
            entity->ext.et_801A518C.unk89 = 6 - i;
            entity->ext.et_801A518C.unk88 = temp_s4;
            entity->params = 2;
            entity->ext.et_801A518C.unk84 = temp_s3;
            entity->zPriority = g_CurrentEntity->zPriority + 1;
        }
    }
}

void EntityExplosionFlame(Entity* self) {
    s32 var_s3;
    EInitUnk22* initEntry;
    s16 angle;
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        var_s3 = self->params & 0xF;
        initEntry = &D_pspeu_092683B0[var_s3];
        self->palette = initEntry->palette + PAL_EXPLOSION_FLAME;
        self->blendMode = initEntry->blendMode;
        self->animSet = initEntry->animSet;
        self->unk5A = initEntry->unk5A;
        self->ext.et_801A518C.anim = (u8*)initEntry->anim;
        self->step = var_s3 + 1;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_19F);
            self->blendMode = BLEND_TRANSP;
            self->facingLeft = 1;
        }
        break;
    case 1:
        switch (self->step_s) {
        case 0:
            angle = self->rotate - 0x400;
            self->velocityX = rcos(angle) << 4;
            self->velocityY = rsin(angle) << 4;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            if (!AnimateEntity(self->ext.et_801A518C.anim, self)) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            angle = self->rotate - 0x400;
            self->velocityX = rcos(angle) << 4;
            self->velocityY = rsin(angle) << 4;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            if (!AnimateEntity(self->ext.et_801A518C.anim, self)) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    case 3:
        if (!AnimateEntity(self->ext.et_801A518C.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 4:
        if (!self->step_s) {
            self->velocityY = FIX(-0.25);
            self->step_s++;
        }
        MoveEntity();
        if (!AnimateEntity(self->ext.et_801A518C.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 5:
        if (!self->step_s) {
            angle = self->rotate;
            self->velocityX = rcos(angle) << 4;
            self->velocityY = rsin(angle) << 4;
            self->rotate -= 0x400;
            self->step_s++;
        }
        MoveEntity();
        if (!AnimateEntity(self->ext.et_801A518C.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 6:
        if (!self->step_s) {
            self->rotate += (0x100 - (Random() << 1));
            angle = self->rotate;
            self->velocityX = (rcos(angle) * 7) << 2;
            self->velocityY = (rsin(angle) * 7) << 2;
            self->rotate += 0x400;
            self->blendMode = BLEND_ADD | BLEND_TRANSP;
            self->drawFlags =
                ENTITY_OPACITY | ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = 0x20;
            self->scaleY = 0xC0;
            self->opacity = 0x80;
            self->step_s++;
        }
        MoveEntity();
        self->scaleX += 6;
        self->scaleY += 2;
        self->opacity -= 1;
        MoveEntity();
        if (!AnimateEntity(self->ext.et_801A518C.anim, self)) {
            DestroyEntity(self);
        }
        break;
    case 7:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->drawFlags |= ENTITY_SCALEX;
            self->opacity = 0x80;
            self->facingLeft = (Random() & 1);
            self->velocityX = (Random() << 8) - 0x8000;
            self->velocityY = 0xFFFD8000;
            self->ext.et_801A518C.acceleration = -(Random() << 4) - 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += (s32)self->ext.et_801A518C.acceleration;
        self->opacity -= 1;
        if (self->pose == 8 && !self->poseTimer) {
            newEntity = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ID(EXPLOSION_FLAME), self, newEntity);
                newEntity->params = 6;
                newEntity->scaleX = self->scaleX;
            }
        }
        if (!AnimateEntity(self->ext.et_801A518C.anim, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
