// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo1.h"

typedef struct EntityPrim {
    struct EntityPrim* next;
#if defined(VERSION_PC) || defined(VERSION_PSP)
    u_long dummy;
#endif
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 type;
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ u8 u0;
    /* 0x0D */ u8 v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ f32 posX;
    /* 0x14 */ f32 posY;
    /* 0x18 */ u8 u1;
    /* 0x19 */ u8 v1;
    /* 0x1A */ u16 tpage;
    /* 0x1C */ f32 velocityX;
    /* 0x20 */ f32 velocityY;
    /* 0x24 */ u8 u2;
    /* 0x25 */ u8 v2;
    /* 0x26 */ u16 priority;
    /* 0x28 */ u8 r3;
    /* 0x29 */ u8 g3;
    /* 0x2A */ u8 b3;
    /* 0x2B */ u8 p3;
    /* 0x2C */ s16 x3;
    /* 0x2E */ s16 y3;
    /* 0x30 */ u8 u3;
    /* 0x31 */ u8 v3;
    /* 0x32 */ u16 drawMode;
} EntityPrim; /* size=0x34 */

static Point32 D_pspeu_092682F0[] = {
    {FIX(-2), FIX(-0.5)},       {FIX(-1.875), FIX(-1.5)},
    {FIX(-2.25), FIX(-1.25)},   {FIX(-1.75), FIX(-1.125)},
    {FIX(-1.875), FIX(-1.125)}, {FIX(-2), FIX(-1)},
    {FIX(-2.125), FIX(-1.25)},  {FIX(0), FIX(0)}};
static u16 D_pspeu_09268330[2][4] = {
    {0x00DF, 0x00FF, 0x011F, 0x013F}, {0x02C0, 0x02E0, 0x0300, 0x0320}};
static u16 D_pspeu_09268340[2][4] = {
    {0x051E, 0x001D, 0x001D, 0x001D}, {0x0025, 0x0000, 0x0000, 0x0000}};
s32 is_boss_playing = 0;
static s32 D_us_801B2378;
extern EInit g_EInitParticle;
extern EInit g_EInitBossDoor;

#ifdef VERSION_PSP
extern s32 E_ID(UNK_17);
extern s32 E_ID(EXPLOSION_FLAME);
#endif

void func_us_801BA164_from_cat(Entity* self) {
    EntityPrim* prim;
    s32 var_s1;
    s32 i;
    s32 var_s3;
    s16 posX;
    s16 posY;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->ext.et_801BA164.unk80 = 0x40;
        primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 8);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = (EntityPrim*)&g_PrimBuf[primIndex];
            self->ext.et_801BA164.prim = (Primitive*)prim;
            i = 0;
            while (prim->next != NULL) {
                prim->u0 = 2;
                prim->v0 = 2;
                prim->x0 = self->posX.i.hi;
                prim->y0 = self->posY.i.hi;
                prim->r0 = 0x60;
                prim->g0 = 0x40;
                prim->b0 = 0x60;
                prim->velocityX.val = D_pspeu_092682F0[i].x;
                prim->velocityY.val = D_pspeu_092682F0[i].y;
                if (self->params & 0x10) {
                    var_s3 = prim->velocityX.val;
                    prim->velocityX.val = prim->velocityY.val;
                    prim->velocityY.val = -var_s3;
                }
                if (self->params & 1) {
                    prim->velocityX.val = -prim->velocityX.val;
                }
                prim->posX.val = 0;
                prim->posY.val = 0;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_DEFAULT;
                i++;
                prim = prim->next;
            }
            prim->u0 = prim->v0 = 0;
            prim->x0 = prim->y0 = 0;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;
        } else {
            DestroyEntity(self);
            break;
        }
    case 1:
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        prim = (EntityPrim*)self->ext.et_801BA164.prim;
        while (prim->next != NULL) {
            var_s1 = (prim->posX.i.hi << 0x10) + prim->posX.i.lo;
            var_s1 += prim->velocityX.val;
            prim->posX.val = var_s1;
            prim->x0 = posX + prim->posX.i.hi;
            var_s1 = (prim->posY.i.hi << 0x10) + prim->posY.i.lo;
            var_s1 += prim->velocityY.val;
            prim->posY.val = var_s1;
            prim->y0 = posY + prim->posY.i.hi;
            prim->velocityY.val += 0x1000;
            prim = prim->next;
        }
        prim->u0 = prim->v0 = 0;
        prim->x0 = prim->y0 = 0;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        if (!--self->ext.et_801BA164.unk80) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityBossDoor(Entity* self) {
    Collider collider;
    s32 i;
    s32 tilePos;
    Entity* newEntity;
    s16 posX;
    s16 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBossDoor);
        self->animCurFrame = self->params + 0x10;
        if (self->params) {
            self->posX.i.hi = 7 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 0x141 - g_Tilemap.scrollY.i.hi;
        } else {
            self->posX.i.hi = 0x1F7 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 0x41 - g_Tilemap.scrollY.i.hi;
        }
        for (i = 0; i < 4; i++) {
            tilePos = D_pspeu_09268330[self->params][i];
            g_Tilemap.fg[tilePos] = D_pspeu_09268340[1][i];
        }
        if (D_us_801B2378) {
            DestroyEntity(self);
            break;
        }
        is_boss_playing = 0;
        self->zPriority = 0x5F;
    case 1:
        if (is_boss_playing) {
            self->step++;
        }
        break;
    case 2:
        self->posY.val += self->velocityY;
        self->velocityY += FIX(0.5);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 0x20;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects) {
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY;
            self->velocityY /= 4;
            if (!(is_boss_playing & 0x10)) {
                PlaySfxPositional(SFX_EXPLODE_B);
                is_boss_playing |= 0x10;
            }
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, newEntity);
                newEntity->posX.i.hi += ((Random() & 7) * 2) - 8;
                newEntity->posY.i.hi += 0x20;
                newEntity->params = 16;
            }

            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_17), self, newEntity);
                newEntity->posY.i.hi += 0x20;
                if (self->params) {
                    newEntity->posX.i.hi += 8;
                } else {
                    newEntity->posX.i.hi -= 8;
                }
                newEntity->params = self->params;
            }

            if (self->velocityY > FIX(-0.125)) {
                self->step++;
            }
        }

        if (!self->ext.et_801BA164.unk84 && self->velocityY > FIX(4.0)) {
            self->ext.et_801BA164.unk84 = true;
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_17), self, newEntity);
                newEntity->posY.i.hi += 0x10;
                if (self->params) {
                    newEntity->posX.i.hi += 8;
                } else {
                    newEntity->posX.i.hi -= 8;
                }
                newEntity->params = self->params + 0x10;
            }
        }
        break;
    case 3:
        for (i = 0; i < 4; i++) {
            tilePos = D_pspeu_09268330[self->params][i];
            g_Tilemap.fg[tilePos] = D_pspeu_09268340[0][i];
        }

        self->step++;
        break;
    case 4:
        if (!is_boss_playing) {
            self->step++;
        }
        break;
    case 5:
        for (i = 0; i < 4; i++) {
            tilePos = D_pspeu_09268330[self->params][i];
            g_Tilemap.fg[tilePos] = D_pspeu_09268340[1][i];
        }
        self->step++;
        break;
    case 6:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        self->posY.i.hi -= 1;
        break;
    }
}
