// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

static Point32 D_us_80181620[] = {
    {.x = 0xFFFE0000, .y = 0xFFFF8000}, {.x = 0xFFFE2000, .y = 0xFFFE8000},
    {.x = 0xFFFDC000, .y = 0xFFFEC000}, {.x = 0xFFFE4000, .y = 0xFFFEE000},
    {.x = 0xFFFE2000, .y = 0xFFFEE000}, {.x = 0xFFFE0000, .y = 0xFFFF0000},
    {.x = 0xFFFDE000, .y = 0xFFFEC000}, {.x = 0x00000000, .y = 0x00000000}};
static u16 tile_positions[2][4] = {
    {0x00DF, 0x00FF, 0x011F, 0x013F}, {0x02C0, 0x02E0, 0x0300, 0x0320}};
static u16 tiles[2][4] = {
    {0x051E, 0x001D, 0x001D, 0x001D}, {0x0025, 0x0000, 0x0000, 0x0000}};
static s32 D_us_80181680 = 0;
extern EInit g_EInitEnvironment;
extern EInit g_EInitParticle;

void func_us_801BA164(Entity* self) {
    Primitive* prim;
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
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BA164.prim = prim;

            for (i = 0; prim != NULL; i++, prim = prim->next) {
                prim->u0 = 2;
                prim->v0 = 2;
                prim->x0 = self->posX.i.hi;
                prim->y0 = self->posY.i.hi;
                prim->r0 = 0x60;
                prim->g0 = 0x40;
                prim->b0 = 0x60;
                LOW(prim->r2) = D_us_80181620[i].x;
                LOW(prim->x2) = D_us_80181620[i].y;
                if (self->params & 0x10) {
                    var_s3 = LOW(prim->r2);
                    LOW(prim->r2) = LOW(prim->x2);
                    LOW(prim->x2) = -var_s3;
                }

                if (self->params & 1) {
                    LOW(prim->r2) = -LOW(prim->r2);
                }

                LOW(prim->r1) = 0;
                LOW(prim->x1) = 0;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_DEFAULT;
            }
        } else {
            DestroyEntity(self);
            return;
        }
    // fallthrough
    case 1:
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        prim = self->ext.et_801BA164.prim;
        while (prim != NULL) {
            var_s1 = (LOH(prim->b1) << 0x10) + LOH(prim->r1);
            var_s1 += LOW(prim->r2);
            LOW(prim->r1) = var_s1;
            prim->x0 = posX + LOH(prim->b1);
            var_s1 = (prim->y1 << 0x10) + prim->x1;
            var_s1 += LOW(prim->x2);
            LOW(prim->x1) = var_s1;
            prim->y0 = posY + prim->y1;
            LOW(prim->x2) += 0x1000;
            prim = prim->next;
        }
        break;
    }
}

void func_us_801BA388(Entity* self) {
    Collider collider;
    s32 i;
    s32 tilePos;
    Entity* newEntity;
    s16 posX;
    s16 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->animCurFrame = self->params + 0x10;
        if (self->params) {
            self->posX.i.hi = 7 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 0x141 - g_Tilemap.scrollY.i.hi;
        } else {
            self->posX.i.hi = 0x1F7 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 0x41 - g_Tilemap.scrollY.i.hi;
        }

        for (i = 0; i < 4; i++) {
            tilePos = tile_positions[self->params][i];
            g_Tilemap.fg[tilePos] = tiles[1][i];
        }
        DestroyEntity(self);
        break;
    case 1:
        if (D_us_80181680) {
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
            if (!(D_us_80181680 & 0x10)) {
                D_us_80181680 |= 0x10;
                g_api.func_80102CD8(1);
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
                CreateEntityFromEntity(E_UNK_2A, self, newEntity);
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
                CreateEntityFromEntity(E_UNK_2A, self, newEntity);
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
            tilePos = tile_positions[self->params][i];
            g_Tilemap.fg[tilePos] = tiles[0][i];
        }

        self->step++;
        break;
    case 5:
        for (i = 0; i < 4; i++) {
            tilePos = tile_positions[self->params][i];
            g_Tilemap.fg[tilePos] = tiles[1][i];
        }

        self->step++;
        break;
    case 6:
        self->posY.i.hi--;
        break;
    }
}
