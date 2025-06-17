// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

static s16 sensors_bone_pillar[] = {
    0x0000, 0x0020, 0x0000, 0x0004, 0x0004, 0xFFFC, 0xFFF8, 0x0000};
// This appears to be unused and deadstripped on PSP
static s16 unused[] = {
    0x0000, 0x0008, 0x0000, 0x0004, 0x0002, 0xFFFC, 0xFFFC, 0x0000,
    0x0000, 0x0024, 0x0000, 0x0004, 0x0002, 0xFFFC, 0xFFFC, 0x0000};
static s16 sensors_spike_ball[] = {0x0000, 0x000E, 0x0000, 0x0000};
static s16 D_us_80181C8C[] = {
    0x0002, 0xFFF1, 0x0002, 0xFFEF, 0xFFFC, 0x000A, 0xFFFC, 0x0009};
static s16 D_us_80181C9C[] = {0x0026, 0x0026, 0x000E, 0x000A};
static s16 D_us_80181CA4[] = {0x02C0, 0x0540, 0x0AC0, 0x0D40};
static u8 anim_bone_pillar_1[] = {
    0x30, 0x01, 0x02, 0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x01, 0x02, 0x02,
    0x02, 0x01, 0x02, 0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04,
    0x02, 0x05, 0x05, 0x04, 0x02, 0x06, 0x02, 0x04, 0x02, 0x06, 0x02, 0x07,
    0x02, 0x06, 0x02, 0x07, 0x02, 0x08, 0x02, 0x07, 0x02, 0x08, 0x02, 0x07,
    0x02, 0x06, 0x11, 0x04, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_bone_pillar_2[] = {
    0x30, 0x09, 0x02, 0x0A, 0x02, 0x09, 0x02, 0x0A, 0x02, 0x09, 0x02,
    0x0A, 0x02, 0x09, 0x02, 0x0A, 0x02, 0x09, 0x02, 0x0A, 0x02, 0x0B,
    0x02, 0x0C, 0x02, 0x0D, 0x02, 0x0E, 0x05, 0x0D, 0x02, 0x0F, 0x02,
    0x10, 0x02, 0x0F, 0x02, 0x10, 0x02, 0x11, 0x02, 0x10, 0x02, 0x11,
    0x02, 0x10, 0x02, 0x0F, 0x11, 0x0D, 0xFF, 0x00};
static u8 anim_fire_breath[] = {
    0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05, 0x03, 0x06,
    0x03, 0x07, 0x03, 0x08, 0x03, 0x09, 0x03, 0x0A, 0x03, 0x0B, 0xFF, 0x00};
static s16 D_us_80181D30[] = {
    0x0010, 0x0020, 0x0030, 0x0040, 0x0050, 0x0040, 0x0030, 0x0020};

extern s16* D_us_801BC7B0[];

void EntityBonePillarHead(Entity* self) {
    Collider collider;
    Entity* entity;
    s32 offsetX, offsetY;
    s32 i;
    s32 unkVar;
    s16 angle;
    s16* ptr;

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        SetStep(8);
    }
    if (self->ext.et_bonePillar.unk85) {
        self->ext.et_bonePillar.unk85 = 0;
        SetStep(0xA);
    }
    switch (self->step) {
    case 0x0:
        InitializeEntity(g_EInitBonePillarHead);
        self->palette = g_EInitBonePillarHead[3] + 1;
        self->animCurFrame = 1;
        self->flags |= FLAG_UNK_20000000;
        if (self->params & 0xFF) {
            self->hitboxOffX = -1;
            self->hitboxOffY = -14;
            self->animCurFrame = 9;
            SetStep(2);
            break;
        }
        self->hitboxOffX = -3;
        self->hitboxOffY = 13;
    case 0x1:
        if (UnkCollisionFunc3(sensors_bone_pillar) & 1) {
            if (self->params & 0x100) {
                entity = self + 1;
                CreateEntityFromCurrentEntity(E_BONE_PILLAR_SPIKE_BALL, entity);
                entity->posX.i.hi = self->posX.i.hi + 8;
                entity->posY.i.hi = self->posY.i.hi - 8;
                self->params = 0;
            } else {
                entity = self + 1;
                CreateEntityFromCurrentEntity(E_BONE_PILLAR_HEAD, entity);
                entity->params = 1;
                entity->posX.i.hi = self->posX.i.hi;
                entity->posY.i.hi = self->posY.i.hi;
            }
            SetStep(2);
        }
        break;
    case 0x2:
        if (GetDistanceToPlayerX() < 0x70) {
            SetStep(3);
        }
        break;
    case 0x3:
        if (!self->step_s) {
            self->ext.et_bonePillar.unk80 =
                D_us_80181D30[self->ext.et_bonePillar.unk84];
            self->ext.et_bonePillar.unk84++;
            self->ext.et_bonePillar.unk84 &= 7;
            self->step_s++;
        }
        if (self->params) {
            self->animCurFrame = 9;
        } else {
            self->animCurFrame = 1;
        }
        if (self->params == ((GetSideToPlayer() & 1) ^ 1)) {
            if (!--self->ext.et_bonePillar.unk80) {
                SetStep(4);
            }
        }
        if (GetDistanceToPlayerX() > 0x80) {
            SetStep(3);
        }
        break;
    case 0x4:
        if (g_Timer & 2) {
            self->palette = g_EInitBonePillarHead[3];
        } else {
            self->palette = g_EInitBonePillarHead[3] + 1;
        }
        if (self->params) {
            unkVar = AnimateEntity(anim_bone_pillar_2, self);
        } else {
            unkVar = AnimateEntity(anim_bone_pillar_1, self);
        }
        if (!unkVar) {
            self->palette = g_EInitBonePillarHead[3] + 1;
            SetStep(3);
        }
        if ((self->pose == 0x11) && (unkVar & 0x80)) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_BONE_PILLAR_FIRE, self, entity);
                entity->facingLeft = self->params;
                if (self->params) {
                    entity->posY.i.hi -= 0xE;
                } else {
                    entity->posY.i.hi += 8;
                }
            }
        }
        break;
    case 0x8:
        ptr = D_us_80181C8C;
        unkVar = 0;
        if (!self->params) {
            ptr += 4;
            unkVar = 2;
        }
        for (i = 0; i < 2; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_BONE_PILLAR_PIECES, self, entity);
                entity->params = i + unkVar;
                entity->posX.i.hi += *ptr++;
                entity->posY.i.hi += *ptr++;
            }
        }
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 2;
        }
        if (!self->params) {
            entity = self + 1;
            if (entity->entityId == E_BONE_PILLAR_HEAD ||
                entity->entityId == E_BONE_PILLAR_SPIKE_BALL) {
                entity->ext.et_bonePillar.unk85 = 1;
            }
        }
        PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
        DestroyEntity(self);
        break;
    case 0xA:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0x18;
            self->hitboxOffX = 0;
            self->hitboxOffY = 0;
            self->drawFlags |= FLAG_DRAW_ROTATE;
            self->velocityX = FIX(-0.75);
            self->velocityY = FIX(-1.0);
            self->flags &= ~FLAG_UNK_20000000;
            self->flags |= FLAG_UNK_02000000;
            self->step_s++;
        case 1:
            self->rotate -= 0x20;
            MoveEntity();
            self->velocityY += FIX(0.1875);
            for (ptr = D_us_80181CA4, i = 0; i < 4; i++, ptr++) {
                offsetX = self->posX.i.hi;
                offsetY = self->posY.i.hi;
                angle = self->rotate + *ptr;
                offsetX += ((rcos(angle) * 0xE) >> 0xC);
                offsetY += ((rsin(angle) * 0xE) >> 0xC);
                g_api.CheckCollision(offsetX, offsetY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    PlaySfxPositional(SFX_SKULL_KNOCK_B);
                    self->posY.i.hi += collider.unk18;
                    self->velocityY = -self->velocityY;
                    self->velocityY -= self->velocityY / 2;
                    break;
                }
            }
            if (self->flags & FLAG_DEAD) {
                PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
                self->hitboxState = 0;
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->step = 0;
                self->pfnUpdate = EntityExplosion;
                self->params = 1;
            }
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
}

void EntityBonePillarSpikeBall(Entity* self) {
    Collider collider;
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s32 posX, posY;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 3;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBonePillarSpikeBall);
        self->animCurFrame = 0x16;
        self->hitboxWidth = 0xD;
        self->hitboxHeight = 0xD;
        self->flags |= FLAG_UNK_02000000;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        prim->tpage = self->unk5A / 4;
        if (self->unk5A & 1) {
            posX = 0x80;
        } else {
            posX = 0;
        }
        if (self->unk5A & 2) {
            posY = 0x80;
        } else {
            posY = 0;
        }
        prim->clut = g_EInitBonePillarSpikeBall[3] + 2;
        prim->u0 = prim->u2 = posX + 0x50;
        prim->u1 = prim->u3 = posX + 0x70;
        prim->v0 = prim->v1 = posY + 0x30;
        prim->v2 = prim->v3 = posY + 0x50;
        prim->priority = self->zPriority - 1;
        prim->drawMode = DRAW_UNK02;
    case 1:
        if (self->ext.et_bonePillar.unk85) {
            self->drawFlags = FLAG_DRAW_ROTATE;
            self->hitPoints = 0x7FFF;
            self->hitboxState = 1;
            self->velocityX = FIX(-0.75);
            self->velocityY = FIX(-1.0);
            self->step++;
            entity = AllocEntity(&g_Entities[32], &g_Entities[47]);
            if (entity != NULL) {
                DestroyEntity(entity);
                entity->entityId = E_SEALED_DOOR;
                entity->pfnUpdate = EntityBonePillarSpikeBall;
                entity->attack = self->attack;
                entity->hitboxWidth = self->hitboxWidth;
                entity->hitboxHeight = self->hitboxHeight;
                entity->hitboxState = 2;
                entity->attackElement = ELEMENT_FIRE;
                entity->nFramesInvincibility = 0x10;
                entity->stunFrames = 4;
                entity->hitEffect = 1;
                entity->ext.et_bonePillar.unkB0.i.hi = 0;
                entity->flags =
                    FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
                g_api.func_80118894(entity);
                entity->step = 4;
                entity->ext.et_bonePillar.unkEntity = self;
                self->ext.et_bonePillar.unkEntity = entity;
            }
        }
        break;
    case 2:
        MoveEntity();
        self->rotate -= 0x40;
        self->velocityY += FIX(0.25);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 8;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (!self->ext.et_bonePillar.unk86) {
                self->ext.et_bonePillar.unk86 = 1;
                PlaySfxPositional(SFX_UNK_761);
            } else {
                PlaySfxPositional(SFX_METAL_CLANG_B);
            }
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY;
            self->velocityY -= self->velocityY / 2;

            if (abs(self->velocityY) < FIX(0.5)) {
                self->step++;
            }
        }
        break;
    case 3:
        UnkCollisionFunc2(sensors_spike_ball);
        self->rotate -= 0x80;
        self->velocityX = FIX(-1.75);
        break;
    case 4:
        entity = self->ext.et_bonePillar.unkEntity;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        if (entity->entityId != E_BONE_PILLAR_SPIKE_BALL) {
            DestroyEntity(self);
        }
        return;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - 0xF;
    prim->y0 = prim->y1 = self->posY.i.hi - 0x10;
    prim->x1 = prim->x3 = prim->x0 + 0x20;
    prim->y2 = prim->y3 = prim->y0 + 0x20;
    if (self->ext.et_bonePillar.unk85) {
        if (g_Timer & 2) {
            self->palette = g_EInitBonePillarSpikeBall[3];
            prim->clut = g_EInitBonePillarSpikeBall[3] + 2;
        } else {
            self->palette = g_EInitBonePillarSpikeBall[3] + 1;
            prim->clut = g_EInitBonePillarSpikeBall[3] + 3;
        }
    }
}

void EntityBonePillarFireBreath(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 posX, posY;
    s16* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBonePillarFireBreath);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_bonePillar.prim = prim;
        prim->tpage = 0x13;
        prim->clut = 0x221;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        self->hitboxWidth = 0x15;
        self->hitboxHeight = 0x18;
        if (self->facingLeft) {
            prim->x0 = posX + 0x30;
            prim->x1 = posX - 4;
            prim->x2 = posX + 0x40;
            prim->x3 = posX + 4;
            prim->y0 = posY - 0x60;
            prim->y1 = posY - 8;
            prim->y2 = posY - 0x20;
            prim->y3 = posY + 8;
            self->hitboxOffX = -0x20;
            self->hitboxOffY = -0x18;
        } else {
            prim->x0 = posX - 0x40;
            prim->x1 = posX - 4;
            prim->x2 = posX - 0x30;
            prim->x3 = posX + 4;
            prim->y0 = posY;
            prim->y1 = posY - 8;
            prim->y2 = posY + 0x40;
            prim->y3 = posY + 8;
            self->hitboxOffX = -0x20;
            self->hitboxOffY = 0x1E;
        }
        PlaySfxPositional(SFX_FIREBALL_SHOT_A);
    case 1:
        if (!AnimateEntity(anim_fire_breath, self)) {
            self->hitboxState = 0;
            self->step += 1;
            return;
        }
        prim = self->ext.et_bonePillar.prim;
        ptr = D_us_801BC7B0[self->animCurFrame];
        ptr += 8;
        prim->u0 = prim->u2 = *ptr++;
        prim->v0 = prim->v1 = *ptr++;
        prim->u1 = prim->u3 = *ptr++;
        prim->v2 = prim->v3 = *ptr++;
        break;
    case 2:
        for (prim = self->ext.et_bonePillar.prim; prim != NULL;
             prim = prim->next) {
            prim->type = PRIM_TILE;
            if (self->facingLeft) {
                posX = (Random() & 0x1F) + 0x10;
            } else {
                posX = -(Random() & 0x1F) - 0x10;
            }
            prim->x0 = self->posX.i.hi + posX;
            posY = self->posY.i.hi - posX;
            prim->y0 = posY - (Random() & 0x1F) + 8;
            prim->u0 = 1;
            prim->v0 = 1;
            prim->r0 = 0xE0;
            prim->b0 = 0x88;
            prim->g0 = 0xA0;
            prim->p2 = (Random() & 7) + 1;
            prim->priority = self->zPriority + 1;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        }
        self->ext.et_bonePillar.unk80 = 0x30;
        self->step++;
    case 3:
        for (prim = self->ext.et_bonePillar.prim; prim != NULL;
             prim = prim->next) {
            if (!(g_Timer % prim->p2)) {
                prim->y0--;
            }
            prim->r0 -= 2;
            prim->g0 -= 2;
            prim->b0 -= 2;
        }
        if (!--self->ext.et_bonePillar.unk80) {
            DestroyEntity(self);
        }
    }
}

void EntityBonePillarDeathParts(Entity* self) {
    Collider collider;
    s32 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBonePillarPieces);
        self->hitboxState = 0;
        self->animCurFrame = (self->params & 0xF) + 0x12;
        self->zPriority += self->params & 0xF;
        if (self->params & 1) {
            self->ext.et_bonePillar.unk80 = 0x18;
        } else {
            self->ext.et_bonePillar.unk80 = 0xC;
        }
        break;
    case 1:
        if (!--self->ext.et_bonePillar.unk80) {
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.15625);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + D_us_80181C9C[self->params];
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            self->ext.et_bonePillar.unk80 = 0xE;
            self->step++;
        }
        break;
    case 3:
        if (!--self->ext.et_bonePillar.unk80) {
            self->step = 0;
            self->pfnUpdate = EntityExplosion;
            self->params = 0;
        }
    }
}
