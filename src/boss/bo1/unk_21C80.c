// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo1.h"

extern s16 D_us_80180D00[];
extern u8 D_us_80180CE8[];
extern AnimateEntityFrame D_us_80180DE0[];
extern AnimateEntityFrame D_us_80180E10[];
extern AnimateEntityFrame D_us_80180E18[];
extern s16 D_us_80180DD0[];
extern s16 D_pspeu_092680A8[][2];
extern AnimateEntityFrame D_pspeu_092680F0[];
extern s16 D_us_80180D34[][5];
extern s32 D_us_80180CD8;
extern s32 D_us_80180CE4;
extern EInit D_us_80180B1C;
extern EInit D_us_80180B28;
extern EInit D_us_80180B34;
extern EInit D_us_80180B58;
extern EInit D_us_80180B4C;
extern s32 D_us_80180CE0;
extern s32 D_us_80180CD4;
extern s8 D_us_80180E34[];
extern u8 D_us_80180ED8[];
extern EInit g_EInitGranfaloon2;

#ifdef VERSION_PSP
extern s32 E_ID(UNK_1A);
extern s32 E_ID(UNK_1B);
extern s32 E_ID(UNK_1D);
extern s32 E_ID(UNK_1E);
extern s32 E_ID(UNK_1F);
extern s32 E_ID(UNK_20);
extern s32 E_ID(UNK_21);
extern s32 E_ID(UNK_22);
#endif

#include "../../st/approach_s16.h"

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A1878);

void func_us_801A2774(Entity* self) {
    Entity* newEntity;
    s32 i;
    s32 posX;
    s32 posY;
    s8* hitbox;
    s16* row;
    s16 angle;
    s32 hitboxIndex;

    if (D_us_80180CE4 & 1) {
        self->flags |= FLAG_DEAD;
    }
    if ((self->flags & FLAG_DEAD) && self->step < 3) {
        SetStep(3);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGranfaloon2);
        row = D_us_80180D34[self->params];
        self->animCurFrame = row[0];
        self->zPriority = row[1];
        hitbox = D_us_80180E34;
        hitboxIndex = D_us_80180ED8[self->animCurFrame];
        hitbox += hitboxIndex * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (row[4]) {
            newEntity = AllocEntity(&g_Entities[208], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_1E), self, newEntity);
                newEntity->params = self->params;
                newEntity->ext.et_801A2CC4.parent = self;
            }
        }
    case 1:
        self->hitboxState = 0;
        if (D_us_80180CD4) {
            self->hitboxState = 3;
            self->step++;
        }
        break;
    case 2:
        newEntity = self->ext.et_801A2CC4.parent;
        self->posX.i.hi = newEntity->posX.i.hi;
        self->posY.i.hi = newEntity->posY.i.hi;
        if (!newEntity->ext.et_801A2CC4.hitTimer) {
            break;
        }
        if (Random() & newEntity->ext.et_801A2CC4.hitTimer) {
            break;
        }
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (self->params != 8) {
            angle = D_us_80180D00[self->params];
            posX += ((rcos(angle) * 3) << 5) >> 12;
            posY += ((rsin(angle) * 3) << 5) >> 12;
        }
        newEntity = AllocEntity(&g_Entities[144], &g_Entities[192]);
        if (newEntity != NULL) {
            if (Random() & 1) {
                CreateEntityFromCurrentEntity(E_ID(UNK_20), newEntity);
            } else {
                CreateEntityFromCurrentEntity(E_ID(UNK_21), newEntity);
            }
            newEntity->zPriority = 0x4A;
            newEntity->posX.i.hi = posX;
            newEntity->posY.i.hi = posY;
            newEntity->params = self->params;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->animCurFrame = 0;
            D_us_80180CD8 |= 1 << self->params;
            D_us_80180CE0++;
            row = D_us_80180D34[self->params];
            for (i = 0; i < 2; i++) {
                newEntity = AllocEntity(&g_Entities[192], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_1D), self, newEntity);
                    newEntity->params = self->params + (i << 8);
                    newEntity->zPriority = 0x48;
                }
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            if (self->params != 8) {
                angle = D_us_80180D00[self->params];
                posX += ((rcos(angle) * 5) << 4) >> 12;
                posY += ((rsin(angle) * 5) << 4) >> 12;
            }
            for (i = 0; i < 0x18; i++) {
                newEntity = AllocEntity(&g_Entities[208], &g_Entities[240]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_1F), newEntity);
                    newEntity->zPriority = 0x4A;
                    newEntity->posX.i.hi = posX;
                    newEntity->posY.i.hi = posY;
                }
            }
            PlaySfxPositional(SFX_BO1_UNK_7C7);
            self->step_s++;
            break;
        case 1:
            break;
        }
        break;
    }
}

void func_us_801A2BC4(Entity* self) {
    s16 angle;
    s16* row;
    s32 index;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B4C);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        index = self->params & 0xF;
        row = D_us_80180D34[index];
        angle = D_us_80180D00[index];
        if (self->params & 0x100) {
            angle -= 0x80;
            self->animCurFrame = row[3];
        } else {
            angle += 0x80;
            self->animCurFrame = row[2];
        }
        self->velocityX = rsin(angle) << 4;
        self->velocityY = rcos(angle) << 4;
        break;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.0625);
        break;
    }
}

void func_us_801A2CC4(Entity* self) {
    s16* row;
    Entity* parent;

    if (D_us_80180CE4 & 1) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B4C);
        self->zPriority = 0x3C;
        row = D_us_80180D34[self->params];
        self->animCurFrame = row[4];

    case 1:
        parent = self->ext.et_801A2CC4.parent;
        self->posX.i.hi = parent->posX.i.hi;
        self->posY.i.hi = parent->posY.i.hi;
        if (D_us_80180CD8 & (1 << self->params)) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A2D90(Entity* self) {
    s32 var_s0;
    s16 angle;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B4C);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        var_s0 = Random() & 3;
        self->animCurFrame = var_s0 + 0x79;
        self->drawFlags = ENTITY_ROTATE;
        self->facingLeft = Random() & 1;
        var_s0 = (Random() & 0x1F) + 0x10;
        angle = (Random() * 6) + 0x900;
        self->velocityX = (var_s0 * rcos(angle)) >> 1;
        self->velocityY = var_s0 * rsin(angle);
        if (self->params) {
            self->velocityX >>= 1;
            self->velocityY >>= 1;
        }
        self->posX.val += self->velocityX << 4;
        self->posY.val += self->velocityY << 4;
        self->ext.et_801A2CC4.unk80 = (Random() & 0x1F) + 0x10;

    case 1:
        MoveEntity();
        self->rotate += 0x40;
        if (self->velocityY < FIX(3.0)) {
            self->velocityY += 0x1400;
        }
        break;
    }
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (posY > 0x1C8) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A2F2C);

#ifdef VERSION_US
INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A3480);
#else
#define STUFF() /* TODO please inline this */                                  \
    self->rotate = angle - 0x400;                                              \
    self->posX.i.hi = parent->posX.i.hi;                                       \
    self->posY.i.hi = parent->posY.i.hi;                                       \
    self->posX.i.hi += ((rcos(angle) * 40) >> 12);                             \
    self->posY.i.hi += ((rsin(angle) * 40) >> 12);                             \
    if (0) {                                                                   \
    }
void func_us_801A3480(Entity* self) {
    Entity* parent;
    s16 angle;
    s32 index;

    if ((D_us_80180CE4 & 1) && self->step < 3) {
        SetStep(3);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B1C);
        self->animCurFrame = 0x3A;
        self->drawFlags = ENTITY_OPACITY;
        self->drawFlags |= ENTITY_ROTATE;
        self->opacity = D_us_80180DD0[self->params];
        self->rotate = D_us_80180D00[self->params] - 0x400;
    case 1:
        index = self->params;
        parent = self - 1;
        angle = parent->rotate + D_us_80180D00[index];
        STUFF();
        if (parent->ext.et_801A2CC4.unk84) {
            SetStep(2);
        }
        break;
    case 2:
        index = self->params;
        parent = self - 1;
        angle = parent->rotate + D_us_80180D00[index];
        STUFF();
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180E10, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            parent = self + 1;
            CreateEntityFromEntity(E_ID(UNK_1B), self, parent);
            parent->rotate = self->rotate;
            parent->zPriority = self->zPriority + 1;
            parent->ext.et_801A2CC4.parent = self;
            self->ext.et_801A2CC4.unk80 = 0x100;
            self->step_s++;

        case 2:
            parent = self + 1;
            if (parent->entityId != E_ID(UNK_1B)) {
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180E18, self)) {
                SetStep(1);
            }
            break;
        }
        break;
    case 3:
        index = self->params;
        parent = self - 1;
        angle = parent->rotate + D_us_80180D00[index];
        STUFF();
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->ext.et_801A2CC4.unk80 = self->params;
            self->step_s++;
            break;
        case 1:
            self->ext.et_801A2CC4.unk80++;
            if (!(self->ext.et_801A2CC4.unk80 & 7)) {
                parent = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (parent != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_22), self, parent);
                    parent->params = 3;
                    parent->zPriority = 0x70;
                }
            }
            if (D_us_80180CE4 & 8) {
                self->step_s++;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            DestroyEntity(self);
            break;
        }
        break;
    }
}
#endif

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A38EC);

void func_us_801A4394(Entity* self) {
    Entity* newEntity;
    s16 angle;
    s32 frame;
    s32 posY;

    if (D_us_80180CE4 & 1) {
        self->flags |= FLAG_DEAD;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B58);
        if (self->params != 8) {
            angle = D_us_80180D00[self->params];
            angle += Random() - 0x80;
            self->velocityX = (rcos(angle) << 15) >> 12;
            self->velocityY = (rsin(angle) << 15) >> 12;
        }
        frame = Random() & 3;
        if (frame == 3) {
            frame = 0;
        }
        self->facingLeft = Random() & 1;
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = (frame << 1) + 0x73;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.0625);
        self->rotate += 0x18;
        if (self->flags & FLAG_DEAD) {
            self->velocityY = 0;
            self->hitboxState = 0;
            self->animCurFrame++;
            self->ext.et_801A2CC4.unk80 = 0x40;
            PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.03125);
        if (!(self->ext.et_801A2CC4.unk80 & 7)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_22), self, newEntity);
                newEntity->params = 0;
                newEntity->zPriority = self->zPriority - 1;
                newEntity->posY.i.hi += 0x14;
            }
        }
        if (!--self->ext.et_801A2CC4.unk80) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (posY > 0x1C8) {
        DestroyEntity(self);
    }
}

void func_us_801A45D0(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 res;
    s32 posX;
    s32 posY;

    if (D_us_80180CE4 & 1) {
        self->flags |= FLAG_DEAD;
    }
    if ((self->flags & FLAG_DEAD) && self->step < 4) {
        SetStep(4);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B58);
        self->animCurFrame = 0x69;
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x12;
        self->facingLeft = Random() & 1;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.09375);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 0x12;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            self->step++;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;

        case 1:
            if (self->facingLeft) {
                self->velocityX = FIX(0.375);
            } else {
                self->velocityX = FIX(-0.375);
            }
            AnimateEntity(D_us_80180DE0, self);
            res = UnkCollisionFunc2(D_us_80180CE8);
            if (res & 0x80) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->ext.et_801A2CC4.unk80 = (Random() & 0xF) + 0x10;
            self->animCurFrame = 0x71;
            PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
            self->step_s++;

        case 1:
            if (!(self->ext.et_801A2CC4.unk80 & 0xF)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_22), self, newEntity);
                    newEntity->posY.i.hi += 0x18;
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->params = 1;
                }
            }
            if (!--self->ext.et_801A2CC4.unk80) {
                self->ext.et_801A2CC4.unk80 = 0x10;
                self->animCurFrame = 0x72;
                self->step_s++;
            }
            break;
        case 2:
            if (!(self->ext.et_801A2CC4.unk80 & 7)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_22), self, newEntity);
                    newEntity->posY.i.hi += 0x18;
                    newEntity->zPriority = self->zPriority - 1;
                }
            }
            if (!--self->ext.et_801A2CC4.unk80) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}

void func_us_801A493C(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 posX;
    s32 posY;
    s16 angle;

    if (D_us_80180CE4 & 1) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B34);
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        angle = self->rotate;
        self->velocityX = (rcos(angle) * 3) << 5;
        self->velocityY = (rsin(angle) * 3) << 5;
    case 1:
        MoveEntity();
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (!self->ext.et_801A2CC4.hasHit) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->ext.et_801A2CC4.hasHit = 1;
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_22), newEntity);
                    newEntity->posX.i.hi += Random() & 0xF;
                    newEntity->posY.i.hi += Random() & 0xF;
                    newEntity->zPriority = 0x70;
                    newEntity->params = 2;
                }
            }
        }
        if (posX < 0 || posY < 0 || posX > 0x200 || posY > 0x200) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A4AF4(Entity* self) {
    Primitive* prim;
    Point16* pt;
    s16 angle;
    s32 i;
    s32 offX;
    s32 offY;
    s32 primIndex;
    Entity* player;
    s32 baseX;
    s32 baseY;

    if (D_us_80180CE4 & 1) {
        DestroyEntity(self);
        goto end;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B28);
        self->hitboxWidth = self->hitboxHeight = 4;
        self->zPriority = 0x38;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xD);
        if (primIndex == -1) {
            DestroyEntity(self);
            goto end;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801A4AF4.prim = prim;
        prim->tpage = 0x14;
        prim->clut = 0x200;
        prim->u0 = prim->u2 = 0x38;
        prim->u1 = prim->u3 = 0x40;
        prim->v0 = prim->v1 = 0x28;
        prim->v2 = prim->v3 = 0x40;
        prim->r0 = prim->g0 = prim->b0 = 0xE0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x38;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        for (i = 0; i < 0xB; i++) {
            prim->tpage = 0x14;
            prim->clut = 0x200;
            prim->u0 = prim->u2 = 0x38;
            prim->u1 = prim->u3 = 0x40;
            prim->v0 = prim->v1 = 0x50;
            prim->v2 = prim->v3 = 0x58;
            prim->r0 = prim->g0 = prim->b0 = 0xC0 - (i << 4);
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0x38;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        prim->tpage = 0x14;
        prim->clut = 0x200;
        prim->u0 = prim->u2 = 0x38;
        prim->u1 = prim->u3 = 0x40;
        prim->v0 = prim->v1 = 0x40;
        prim->v2 = prim->v3 = 0x28;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x38;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        pt = self->ext.et_801A4AF4.trail;
        for (i = 0; i < 0xE; i++) {
            pt->x = self->posX.i.hi;
            pt->y = self->posY.i.hi;
            pt++;
        }
        angle = self->rotate;
        self->velocityX = rcos(angle) << 7;
        self->velocityY = rsin(angle) << 7;
        self->ext.et_801A4AF4.angle = angle;
        self->ext.et_801A4AF4.timer = 0xC;

    case 1:
        MoveEntity();
        player = &g_Entities[0];
        angle = GetAngleBetweenEntities(self, player);
        angle = LimitAngleChange(0x80, self->ext.et_801A4AF4.angle, angle);
        self->velocityX = rcos(angle) << 7;
        self->velocityY = rsin(angle) << 7;
        self->ext.et_801A4AF4.angle = angle;
        if (!--self->ext.et_801A4AF4.timer) {
            self->zPriority = 0x50;
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        offX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        offY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (offX < -0x40 || offY < -0x40 || offX > 0x240 || offY > 0x200) {
            DestroyEntity(self);
            goto end;
        }
        break;
    }
    pt = &self->ext.et_801A4AF4.trail[13];
    for (i = 0; i < 0xD; i++) {
        pt->x = pt[-1].x - g_ScrollDeltaX;
        pt->y = pt[-1].y - g_ScrollDeltaY;
        pt--;
    }
    pt = self->ext.et_801A4AF4.trail;
    pt->x = self->posX.i.hi;
    pt->y = self->posY.i.hi;
    pt = self->ext.et_801A4AF4.trail;
    prim = self->ext.et_801A4AF4.prim;
    baseX = pt->x;
    baseY = pt->y;
    prim = self->ext.et_801A4AF4.prim;
    offX = pt[1].x - baseX;
    offY = pt[1].y - baseY;
    angle = ratan2(offY, offX);
    angle -= 0x400;
    offX = (rcos(angle) << 1) >> 12;
    offY = (rsin(angle) << 1) >> 12;
    prim->x0 = baseX + offX;
    prim->y0 = baseY + offY;
    prim->x1 = baseX - offX;
    prim->y1 = baseY - offY;
    prim->priority = self->zPriority;
    pt++;
    for (i = 0; i < 0xB; i++) {
        offX = pt->x - baseX;
        offY = pt->y - baseY;
        angle = ratan2(offY, offX);
        angle -= 0x400;
        baseX = (pt->x + baseX) / 2;
        baseY = (pt->y + baseY) / 2;
        offX = (rcos(angle) << 2) >> 12;
        offY = (rsin(angle) << 2) >> 12;
        prim->x2 = baseX + offX;
        prim->y2 = baseY + offY;
        prim->x3 = baseX - offX;
        prim->y3 = baseY - offY;
        prim->priority = self->zPriority;
        prim = prim->next;
        prim->x0 = baseX + offX;
        prim->y0 = baseY + offY;
        prim->x1 = baseX - offX;
        prim->y1 = baseY - offY;
        baseX = pt->x;
        baseY = pt->y;
        pt++;
    }
    prim->x1 = prim->x3 = pt->x;
    prim->y1 = prim->y3 = pt->y;
    prim->priority = self->zPriority;
end:;
}
