// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

extern EInit g_EInitWyrm;
extern u16 D_us_80180C66;

struct EntityWyrm {
    ENTITY_SHARED;
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s16 timer;
    /* 0x82 */ s16 angle;
    /* 0x84 */ u8 count;
    /* 0x85 */ u8 tailAttack;
    /* 0x86 */ u8 flip;
};
SYNC_STRUCT(EntityWyrm);

AnimateEntityFrame D_us_80180FCC[] = {
    POSE(4, 0x49, 0), POSE(8, 0x4C, 0), POSE(8, 0x49, 0),
    POSE(8, 0x4D, 0), POSE(4, 0x49, 0), POSE_END};
AnimateEntityFrame D_us_80180FD8[] = {
    POSE(8, 0x49, 0), POSE(8, 0x4E, 0), POSE(8, 0x4F, 0), POSE_END};
AnimateEntityFrame D_us_80180FE0[] = {
    POSE(4, 0x4F, 0), POSE(8, 0x4E, 0), POSE(8, 0x49, 0), POSE_END};

static void DrawWyrmBody(void) {
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
    prim = ((struct EntityWyrm*)g_CurrentEntity)->prim;
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

static void CalcWyrmBodyPosition(void) {
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

void CalcWyrmBodyRotation(void) {
    Entity* entity;
    s32 i;
    s16 baseAngle;
    s32 posX;
    s32 posY;
    s32 distance;
    s32 dx;
    s32 dy;
    s16 angle;

    posX = g_CurrentEntity->posX.val;
    posY = g_CurrentEntity->posY.val;
    baseAngle = ((struct EntityWyrm*)g_CurrentEntity)->angle;
    entity = g_CurrentEntity + 1;
    for (i = 0; i < 11; i++, entity++) {
        dx = entity->posX.val - posX;
        dy = entity->posY.val - posY;
        angle = ratan2(dy, dx);
        angle += (rcos(baseAngle) << 8) >> 12;
        dx >>= 16;
        dy >>= 16;
        distance = SquareRoot0(dx * dx + dy * dy);
        if (distance > 0x20) {
            distance = 0x20;
        }
        posX = entity->posX.val = posX + ((distance * rcos(angle)) << 4);
        posY = entity->posY.val = posY + ((distance * rsin(angle)) << 4);
        entity->rotate = angle;
        baseAngle += 0x180;
    }
}

void EntityWyrm(struct EntityWyrm* self) {
    s32 i;
    Entity* entity;
    Primitive* prim;
    s32 primIndex;

    if (self->params && (g_BossMgrState & BOSS_MGR_DEFEAT)) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD && self->step == 2) {
        SetStep(3);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitWyrm);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 13);
        if (primIndex == -1) {
            DestroyEntity((Entity*)self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->prim = prim;
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
            DestroyEntity((Entity*)self);
            return;
        }
        self->nextPart = (Entity*)self + 1;
        self->parent = NULL;
        entity = (Entity*)self + 1;
        for (i = 0; i < 11; i++, entity++) {
            CreateEntityFromEntity(E_ID(WYRM_BODY_PART), (Entity*)self, entity);
            entity->parent = (Entity*)self;
            entity->nextPart = entity + 1;
            entity->params = i & 3;
        }
        entity = (Entity*)self + 12;
        CreateEntityFromEntity(E_ID(WYRM_HEAD), (Entity*)self, entity);
        entity->parent = (Entity*)self;
        entity->nextPart = (Entity*)self;
        entity->params = self->params;
        entity->zPriority = self->zPriority + 1;
        self->timer = self->params * 0x30;
        /* fall through */
    case 1:
        if (!self->params) {
            self->flip = 1;
            if (GetDistanceToPlayerX() < 192) {
                self->flip = 0;
                D_us_80180C66 |= 2;
                D_us_80180C66 |= 4;
                D_us_80180C66 |= 8;
                SetStep(2);
            }
        } else {
            self->flip = 1;
            if (!--self->timer) {
                self->flip = 0;
                SetStep(2);
            }
        }
        break;

    case 2:
        CalcWyrmBodyPosition();
        CalcWyrmBodyRotation();
        DrawWyrmBody();
        self->angle += 0x40;
        break;

    case 3:
        CalcWyrmBodyPosition();
        CalcWyrmBodyRotation();
        DrawWyrmBody();
        self->angle += 0x80;
        switch (self->step_s) {
        case 0:
            self->count = 11;
            self->timer = 1;
            if (!self->params) {
                g_CastleFlags[SCYLLA_WYRM_DEFEATED] |= 1;
                D_us_80180C66 &= ~2;
                D_us_80180C66 &= ~4;
                D_us_80180C66 &= ~8;
            }
            self->step_s++;
            /* fall through */
        case 1:
            if (!--self->timer) {
                self->timer = 0x10;
                entity = (Entity*)self + 1;
                prim = self->prim;
                for (i = 0; i < self->count; i++) {
                    prim = prim->next;
                    entity++;
                }
                prim = prim->next;
                prim->drawMode = DRAW_HIDE;
                ((struct EntityWyrm*)entity)->tailAttack = 1;
                if (!--self->count) {
                    self->step_s++;
                }
            }
            break;

        case 2:
            entity = (Entity*)self + 1;
            for (i = 0; i < 12; i++, entity++) {
                DestroyEntity(entity);
            }
            DestroyEntity((Entity*)self);
            break;
        }
        break;
    }
}

void EntityWyrmBodyPart(struct EntityWyrm* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitWyrm);
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
        if (self->tailAttack) {
            SetStep(2);
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->timer = 0x10;
            self->step_s++;
            /* fall through */
        case 1:
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
            }
            if (!(self->timer & 3)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLODE_PUFF_OPAQUE), (Entity*)self, newEntity);
                    newEntity->rotate = self->rotate - 0x400;
                    newEntity->params = 0;
                    newEntity->zPriority = 0x89;
                }
            }
            if (!--self->timer) {
                self->step_s++;
            }
            break;

        case 2:
            break;
        }
        break;
    }
}

void EntityWyrmHead(struct EntityWyrm* self) {
    Entity* entity;
    s16 angle;
    s32 dx;
    s32 dy;

    if (self->params && (g_BossMgrState & BOSS_MGR_DEFEAT)) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        if (self->step < 6) {
            SetStep(6);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitWyrm);
        self->animCurFrame = 0x49;
        self->drawFlags = ENTITY_ROTATE;
        if (!self->params) {
            self->facingLeft = 1;
        }
        /* fall through */
    case 1:
        entity = (Entity*)self - 12;
        if (((struct EntityWyrm*)entity)->flip) {
            break;
        }
        self->step = 2;
        /* fall through */
    case 2:
        if (!AnimateEntity(D_us_80180FCC, (Entity*)self)) {
            entity = &PLAYER;
            dx = entity->posX.val - self->posX.val;
            dy = entity->posY.val - self->posY.val;
            angle = ratan2(dy, dx);
            self->velocityX = rcos(angle) << 5;
            self->velocityY = rsin(angle) << 5;
            self->timer = 0x40;
            self->animCurFrame = 0x49;
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            if (!self->params) {
                g_api.PlaySfx(SFX_SCYLLA_WYRM_WALL_DEBRIS);
            }
            self->step_s++;
        }
        MoveEntity();
        if (GetDistanceToPlayerX() < 0x38) {
            AnimateEntity(D_us_80180FD8, (Entity*)self);
            if (!self->poseTimer && self->pose == 2) {
                PlaySfxPositional(SFX_SCYLLA_WYRM_ATTACK);
            }
        }
        if (!--self->timer) {
            SetStep(4);
        }
        if (!self->params && !(g_Timer & 7)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(
                    E_ID(BREAKABLE_WALL_DEBRIS), entity);
                entity->posX.i.hi = 0xE0;
                entity->posY.i.hi = 0x24;
                angle = ((Random() & 0x3F) << 4) + 0x400;
                entity->velocityX = rcos(angle) << 4;
                entity->velocityY = rsin(angle) << 4;
            }
        }
        break;

    case 4:
        if (!AnimateEntity(D_us_80180FE0, (Entity*)self)) {
            SetStep(5);
        }
        break;

    case 5:
        entity = (Entity*)self - 12;
        dx = entity->posX.val - self->posX.val;
        dy = entity->posY.val - self->posY.val;
        angle = ratan2(dy, dx);
        angle += (rsin(self->angle) << 9) >> 12;
        self->velocityX = rcos(angle) << 5;
        self->velocityY = rsin(angle) << 5;
        MoveEntity();
        self->angle += 0x80;
        self->animCurFrame = 0x49;
        if (self->velocityY > FIX(0.5)) {
            self->animCurFrame = 0x4A;
        }
        if (self->velocityY < FIX(0.5)) {
            self->animCurFrame = 0x4B;
        }
        dx >>= 16;
        dy >>= 16;
        if (abs(dx) < 0x40) {
            SetStep(2);
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, (Entity*)self, entity);
                entity->params = 3;
                entity->zPriority = self->zPriority + 1;
            }
            self->animCurFrame = 0;
            self->hitboxState = 0;
            entity = (Entity*)self - 12;
            dx = entity->posX.val - self->posX.val;
            dy = entity->posY.val - self->posY.val;
            angle = ratan2(dy, dx);
            self->velocityX = rcos(angle) * 12;
            self->velocityY = rsin(angle) * 12;
            self->step_s++;
            /* fall through */
        case 1:
            MoveEntity();
            entity = (Entity*)self - 12;
            dx = entity->posX.val - self->posX.val;
            if (abs(dx) < 0x40) {
                self->velocityX = 0;
                self->velocityY = 0;
            }
            break;
        }
        break;
    }

    entity = (Entity*)self - 1;
    dx = self->posX.val - entity->posX.val;
    dy = self->posY.val - entity->posY.val;
    angle = ratan2(dy, dx);
    self->rotate = angle;
    if (!self->params) {
        self->rotate = 0x800 - angle;
    }
}
