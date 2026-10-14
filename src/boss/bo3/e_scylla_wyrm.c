// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

extern EInit g_EInitScyllawyrm;
extern s32 D_us_80180D48;
extern u16 D_us_80180C66;

AnimateEntityFrame D_us_80180FCC[] = {
    POSE(4, 0x49, 0), POSE(8, 0x4C, 0), POSE(8, 0x49, 0),
    POSE(8, 0x4D, 0), POSE(4, 0x49, 0), POSE_END};
AnimateEntityFrame D_us_80180FD8[] = {
    POSE(8, 0x49, 0), POSE(8, 0x4E, 0), POSE(8, 0x4F, 0), POSE_END};
AnimateEntityFrame D_us_80180FE0[] = {
    POSE(4, 0x4F, 0), POSE(8, 0x4E, 0), POSE(8, 0x49, 0), POSE_END};

// static once func_us_801A5338 is C
void func_us_801A4FB8(void) {
    Primitive* prim;
    Entity* entity;
    s32 posX;
    s32 posY;
    s16 angle;
    s32 offsetX;
    s32 offsetY;
    s32 i;

    posX = g_CurrentEntity->posX.val;
    posY = g_CurrentEntity->posY.val;
    prim = g_CurrentEntity->ext.scyllaWyrm.prim;
    prim->x1 = prim->x3 = posX;
    prim->y1 = prim->y3 = posY;
    prim->drawMode = DRAW_HIDE;
    entity = g_CurrentEntity + 1;
    for (i = 0; i < 12; i++, entity++) {
        offsetX = entity->posX.val - posX;
        offsetY = entity->posY.val - posY;
        angle = ratan2(offsetY, offsetX);
        if (!g_CurrentEntity->params) {
            angle += 0x400;
        } else {
            angle -= 0x400;
        }
        posX = (entity->posX.val + posX) / 2 >> 16;
        posY = (entity->posY.val + posY) / 2 >> 16;
        offsetX = (rcos(angle) << 4) >> 12;
        offsetY = (rsin(angle) << 4) >> 12;
        prim->x0 = posX + offsetX;
        prim->y0 = posY + offsetY;
        prim->x2 = posX - offsetX;
        prim->y2 = posY - offsetY;
        if (g_CurrentEntity->flags & 0xF) {
            prim->clut = g_CurrentEntity->palette & 0xFFF;
        } else {
            prim->clut = 0x205;
        }
        prim = prim->next;
        prim->x1 = posX + offsetX;
        prim->y1 = posY + offsetY;
        prim->x3 = posX - offsetX;
        prim->y3 = posY - offsetY;
        posX = entity->posX.val;
        posY = entity->posY.val;
    }
    prim->drawMode = DRAW_HIDE;
}

// static once func_us_801A5338 is C
void func_us_801A516C(void) {
    Entity* entity;
    s32 posX;
    s32 posY;
    s32 newX;
    s32 newY;
    Entity* next;
    s32 i;

    posX = g_CurrentEntity->posX.val;
    posY = g_CurrentEntity->posY.val;
    entity = g_CurrentEntity + 1;
    for (i = 0; i < 11; i++) {
        next = entity + 1;
        posX = (posX + next->posX.val) >> 1;
        posY = (posY + next->posY.val) >> 1;
        newX = posX - entity->posX.val;
        newY = posY - entity->posY.val;
        newX = (newX >> 2) + posX;
        newY = (newY >> 2) + posY;
        entity->posX.val = newX;
        entity->posY.val = newY;
        posX = newX;
        posY = newY;
        entity = next;
    }
}

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A51E4);

void func_us_801A5338(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 i;
    s32 primIndex;

    if (self->params && (D_us_80180D48 & 2)) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD && self->step == 2) {
        SetStep(3);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitScyllawyrm);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 13);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.scyllaWyrm.prim = prim;
        for (i = 0; i < 13; i++) {
            prim->tpage = 0x13;
            prim->clut = 0x205;
            prim->v0 = prim->v1 = 0x60;
            prim->v2 = prim->v3 = 0x7F;
            prim->u0 = prim->u2 = 0xFF - i * 14;
            prim->u1 = prim->u3 = 0xF1 - i * 14;
            prim->priority = 0x88;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        if (!self->params && g_CastleFlags[SCYLLA_WYRM_DEFEATED]) {
            DestroyEntity(self);
            return;
        }
        self->nextPart = self + 1;
        self->parent = NULL;
        entity = self + 1;
        for (i = 0; i < 11; i++, entity++) {
            CreateEntityFromEntity(E_ID(UNK_3B), self, entity);
            entity->parent = self;
            entity->nextPart = entity + 1;
            entity->params = i & 3;
        }
        entity = self + 12;
        CreateEntityFromEntity(E_ID(UNK_3C), self, entity);
        entity->parent = self;
        entity->nextPart = self;
        entity->params = self->params;
        entity->zPriority = self->zPriority + 1;
        self->ext.scyllaWyrm.timer = self->params * 0x30;
        /* fall through */
    case 1:
        if (!self->params) {
            self->ext.scyllaWyrm.unk86 = 1;
            if (GetDistanceToPlayerX() < 192) {
                self->ext.scyllaWyrm.unk86 = 0;
                D_us_80180C66 |= 2;
                D_us_80180C66 |= 4;
                D_us_80180C66 |= 8;
                SetStep(2);
            }
        } else {
            self->ext.scyllaWyrm.unk86 = 1;
            if (!--self->ext.scyllaWyrm.timer) {
                self->ext.scyllaWyrm.unk86 = 0;
                SetStep(2);
            }
        }
        break;

    case 2:
        func_us_801A516C();
        func_us_801A51E4();
        func_us_801A4FB8();
        self->ext.scyllaWyrm.angle += 0x40;
        break;

    case 3:
        func_us_801A516C();
        func_us_801A51E4();
        func_us_801A4FB8();
        self->ext.scyllaWyrm.angle += 0x80;
        switch (self->step_s) {
        case 0:
            self->ext.scyllaWyrm.count = 11;
            self->ext.scyllaWyrm.timer = 1;
            if (!self->params) {
                g_CastleFlags[SCYLLA_WYRM_DEFEATED] |= 1;
                D_us_80180C66 &= ~2;
                D_us_80180C66 &= ~4;
                D_us_80180C66 &= ~8;
            }
            self->step_s++;
            /* fall through */
        case 1:
            if (!--self->ext.scyllaWyrm.timer) {
                self->ext.scyllaWyrm.timer = 0x10;
                entity = self + 1;
                prim = self->ext.scyllaWyrm.prim;
                for (i = 0; i < self->ext.scyllaWyrm.count; i++) {
                    prim = prim->next;
                    entity++;
                }
                prim = prim->next;
                prim->drawMode = DRAW_HIDE;
                entity->ext.scyllaWyrm.unk85 = 1;
                if (!--self->ext.scyllaWyrm.count) {
                    self->step_s++;
                }
            }
            break;

        case 2:
            entity = self + 1;
            for (i = 0; i < 12; i++, entity++) {
                DestroyEntity(entity);
            }
            DestroyEntity(self);
            break;
        }
        break;
    }
}

void func_us_801A57A4(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitScyllawyrm);
        self->animSet = 2;
        self->animCurFrame = 0;
        self->unk5A = 0;
        self->palette = 0;
        /* fall through */
    case 1:
        if ((g_Timer & 3) == self->params) {
            self->hitboxState = 3;
        } else {
            self->hitboxState = 0;
        }
        if (self->ext.scyllaWyrm.unk85) {
            SetStep(2);
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->ext.scyllaWyrm.timer = 0x10;
            self->step_s++;
            /* fall through */
        case 1:
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
            }
            if (!(self->ext.scyllaWyrm.timer & 3)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLODE_PUFF_OPAQUE), self, newEntity);
                    newEntity->rotate = self->rotate - 0x400;
                    newEntity->params = 0;
                    newEntity->zPriority = 0x89;
                }
            }
            if (!--self->ext.scyllaWyrm.timer) {
                self->step_s++;
            }
            break;

        case 2:
            break;
        }
        break;
    }
}

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A5948);
