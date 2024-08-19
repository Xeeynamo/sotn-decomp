/*
 * Overlay: NP3
 * Description: Merman Room
 */

#include "np3.h"
#include "sfx.h"
#include "../e_merman2.h"

// EntitySplashWater ID 0x2D
void EntitySplashWater(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    u16 params = self->params;
    u16 temp_s2 = params >> 0xB;
    u16 temp_s5 = (params >> 8) & 7;
    u16 temp_s4 = (params >> 5) & 7;

    Primitive *prim, *prim2;
    Entity* newEntity;
    s16 primIndex;
    s16 temp_a0;
    s16 temp_a1;
    s16 temp_a2;
    u16 temp_t3;
    s16 temp_t8;
    char pad[0x4];
    s32 i;

    params &= 0xF;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        if (temp_s2 != 0 && temp_s4 != 7) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        } else {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        }
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            temp_t3 = self->posY.i.hi;
            temp_t8 = self->posX.i.hi;
            self->ext.waterEffects.unk82 = temp_t3 + tilemap->scrollY.i.hi;
            for (i = 0; prim != NULL; i++) {
                if (i % 2) {
                    prim->u0 = prim->u2 = prim2->u0;
                    prim->u1 = prim->u3 = prim2->u1;
                    prim->v0 = prim->v1 = prim2->v0;
                    prim->v2 = prim->v3 = prim2->v2;
                    prim->y2 = prim2->y2;
                    prim->y3 = prim2->y3;
                    prim->x2 = prim->x0 = prim2->x0;
                    prim->x3 = prim->x1 = prim2->x1;
                } else {
                    prim->u1 = prim->u3 = 0x20;
                    prim->v2 = prim->v3 = 0x7C;
                    prim->u0 = prim->u2 = 0;
                    prim->v0 = prim->v1 = 96;
                    prim->y2 = prim->y3 = temp_t3;
                    prim->x2 = prim->x0 = temp_t8 - 0xE;
                    prim->x3 = prim->x1 = temp_t8 + 0xE;
                    if (i >= 2) {
                        temp_a2 = D_80182168[temp_s4];
                        if (temp_s2 >= 0xF) {
                            prim->u0 = prim->u2 = prim2->u1;
                            prim->x0 = prim->x2 = prim2->x1;
                            temp_a1 = prim2->y3;
                            prim->y2 = temp_a1;
                            if (temp_a2 != 0) {
                                prim->y3 =
                                    temp_a1 - (prim->x1 - prim->x0) / temp_a2;
                            } else {
                                prim->y3 = temp_a1;
                            }
                        } else {
                            prim->u1 = prim->u3 = prim2->u0;
                            prim->x1 = prim->x3 = prim2->x0;
                            temp_a1 = prim2->y2;
                            prim->y3 = temp_a1;
                            if (temp_a2 != 0) {
                                prim->y2 =
                                    temp_a1 + (prim->x1 - prim->x0) / temp_a2;
                            } else {
                                prim->y2 = temp_a1;
                            }
                        }
                    } else {
                        if (temp_s2 != 0) {
                            if (temp_s2 >= 0xF) {
                                prim->u1 = prim->u3 =
                                    prim->u0 + (temp_s2 << 5) / 28;
                                prim->x1 = prim->x3 = temp_s2 + prim->x0;
                            } else {
                                prim->u0 = prim->u2 =
                                    prim->u2 + (temp_s2 << 5) / 28;
                                prim->x0 = prim->x2 = temp_s2 + prim->x2;
                            }
                        }
                        if (temp_s5 != 0) {
                            temp_a0 = D_80182168[temp_s5];
                            if (temp_a0 < 0) {
                                if (temp_t8 >= prim->x1) {
                                    prim->y2 += (prim->x1 - prim->x0) / temp_a0;
                                } else {
                                    prim->y2 += (temp_t8 - prim->x0) / temp_a0;
                                    prim->y3 = prim->y3 -
                                               (prim->x1 - temp_t8) / temp_a0;
                                }
                            } else if (prim->x0 >= temp_t8) {
                                prim->y3 -= (prim->x1 - prim->x0) / temp_a0;
                            } else {
                                prim->y2 += (temp_t8 - prim->x0) / temp_a0;
                                prim->y3 -= (prim->x1 - temp_t8) / temp_a0;
                            }
                        }
                    }
                }
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = 255;
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 128;
                prim->clut = 0x162;
                prim->tpage = 0x1A;
                prim->priority = self->zPriority + 2;
                prim->drawMode = 0x77;
                if (i % 2) {
                    prim->clut = 0x15F;
                    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                        prim->b1 = 0;
                    prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                        prim->b3 = 96;
                    prim->drawMode = 0x37;
                    prim->priority += 2;
                }
                prim2 = prim;
                prim = prim->next;
            }

            temp_a2 = (self->posX.i.hi - 120) >> 4;
            if (temp_a2 < -8) {
                temp_a2 = -8;
                temp_a2 = -8;
            }
            if (temp_a2 > 8) {
                temp_a2 = 8;
            }

            g_api.PlaySfxVolPan(D_8018122C, 0x7F, temp_a2);
            self->velocityY = D_80182188[params].x;
            self->ext.waterEffects.accelY = D_80182188[params].y;
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_WATER_DROP, newEntity);
                newEntity->velocityY = self->velocityY;
            }
            break;
        }
        DestroyEntity(self);
        return;

    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.waterEffects.accelY;
        if (self->velocityY > FIX(2.5)) {
            self->step++;
        }
        break;

    case 2:
        MoveEntity(self);
        if (g_PrimBuf[self->primIndex].r0 < 9) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    temp_t3 = self->ext.waterEffects.unk82 - self->posY.i.hi;
    temp_t3 -= tilemap->scrollY.i.hi;
    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; prim != NULL; i++) {
        prim->y0 = prim->y2 - temp_t3;
        prim->y1 = prim->y3 - temp_t3;
        if (i % 2) {
            if (prim->b3 >= 4) {
                prim->b3 += 252;
            }
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        } else {
            if (prim->b3 >= 8) {
                prim->b3 += 252;
            }
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
            if (prim->b3 <= 8) {
                if (prim->b1 >= 8) {
                    prim->b1 += 248;
                }
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1;
            }
        }
        prim = prim->next;
    }
}

// ID 0x2E
void EntitySurfacingWater(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    s16 left, right, bottom;
    Primitive* prim;
    s16 primIndex;
    s16 temp_t0;
    s32 rnd;
    s16 var_s2;
    u16 params;
    s16* ptr;
    s16 temp3;
    s16 tempv0;
    s16 x, y;
    s32 i, j;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        var_s2 = (self->posX.i.hi - 120) >> 4;
        if (var_s2 < -8) {
            var_s2 = -8;
        }
        if (var_s2 > 8) {
            var_s2 = 8;
        }
        params = self->params;
        if (!(params & 0x8000)) {
            g_api.PlaySfxVolPan(D_8018122E, 0x7F, var_s2);
        }
        params = (params >> 8) & 0x7F;
        prim = &g_PrimBuf[primIndex];
        right = self->posX.i.hi;
        bottom = self->posY.i.hi;
        left = right - 9;
        right += 9;
        self->ext.waterEffects.unk82 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

        for (i = 0; i < 2; i++) {
            prim->u2 = 0;
            prim->u0 = 0;
            prim->u1 = prim->u3 = 0x1E;
            prim->v0 = prim->v1 = 0x60;
            prim->v2 = prim->v3 = 0x7C;
            prim->y2 = prim->y3 = bottom;
            prim->x2 = prim->x0 = left;
            prim->x3 = prim->x1 = right;
            if (params != 0) {
                var_s2 = D_80182168[params];
                prim->y2 = prim->y2 + 9 / var_s2;
                prim->y3 = prim->y3 - 9 / var_s2;
            }
            prim->clut = 0x162;
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                255;
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                128;
            prim->tpage = 0x1A;
            prim->priority = self->zPriority + 2;
            prim->drawMode = 0x77;
            if (i != 0) {
                prim->clut = 0x161;
                prim->priority = self->zPriority + 4;
                prim->drawMode = 0x77;
            }
            prim = prim->next;
        }
        rnd = (rand() & 1) + 12;
        self->ext.waterEffects.topY.i.hi = D_801821A8[(u8)self->params] + rnd;
        self->velocityX = self->ext.waterEffects.unk8A * 16;
        if (params != 0) {
            self->velocityY = self->velocityX / var_s2;
            if (self->velocityY < 0) {
                self->velocityY = -self->velocityY;
            }
        }
        break;

    case 1:
        self->ext.waterEffects.topY.val -= FIX(0.25);
        break;
    }

    MoveEntity(self);

    //! FAKE:
    j = self->velocityX;

    if (self->velocityX != 0) {
        right = D_80181230[self->ext.waterEffects.unk88];
        ptr = D_80181230;
        if (self->velocityX < 0) {
            right += 6;
            x = right - tilemap->scrollX.i.hi;
            if (self->posX.i.hi < x) {
                DestroyEntity(self);
                return;
            }
        } else {
            ptr++;
            temp3 = tilemap->scrollX.i.hi + 6;
            x = right;
            x += (ptr[self->ext.waterEffects.unk88] - temp3);
            if (self->posX.i.hi >= x) {
                DestroyEntity(self);
                return;
            }
        }
    }

    j = 0;
    tempv0 = self->ext.waterEffects.unk82;
    x = self->posX.i.hi;
    y = self->posY.i.hi;

    bottom = tempv0 - y - tilemap->scrollY.i.hi;

    prim = &g_PrimBuf[self->primIndex];
    temp_t0 = x - 9;
    x += 9;

    while (j < 2) {
        prim->y2 = prim->y2 - bottom;
        prim->y3 = prim->y3 - bottom;
        prim->y0 = prim->y2 - self->ext.waterEffects.topY.i.hi;
        prim->y1 = prim->y3 - self->ext.waterEffects.topY.i.hi;
        prim->x2 = prim->x0 = temp_t0;
        prim->x3 = prim->x1 = x;
        prim->b1 += 248;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1;
        prim->b3 += 252;
        prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        if (prim->r0 < 9) {
            DestroyEntity(self);
            return;
        }
        prim = prim->next;
        j++;
    }
    self->ext.waterEffects.unk82 = self->posY.i.hi + tilemap->scrollY.i.hi;
}

// ID 0x2F
void EntitySideWaterSplash(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s3;
    u16 params;
    s16 angle;
    u16 x, y;
    s32* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            while (prim != NULL) {
                prim->u0 = prim->u2 = 0xF0;
                prim->u1 = prim->u3 = 0xFF;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0xF;
                prim->clut = 0x161;
                prim->tpage = 0x1A;
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = prim->r0 = prim->g0 = prim->b0 = prim->r1 =
                        prim->g1 = prim->b1 = 128;
                prim->p1 = 0;
                prim->priority = self->zPriority + 2;
                prim->drawMode = 0x37;
                prim = prim->next;
            }
            params = self->params;
            temp_s0 = params & 0xF;
            if (temp_s0 == 0) {
                g_api.PlaySfx(D_8018122C);
            }
            angle = LOH(D_801821F4[(params >> 3) & 0x1E]);
            ptr = (s32*)&D_801821B4[temp_s0];
            temp_s1 = rcos(angle) * *ptr;
            temp_s3 = rsin(angle + 0x800) * *ptr;
            ptr++;
            temp_s1 += rsin(angle) * *ptr;
            temp_lo = rcos(angle) * *ptr;
            self->velocityX = temp_s1 + (((params & 0xFF00) << 0x10) >> 0xE);
            self->ext.waterEffects.accelY = FIX(22.0 / 128);
            self->velocityY = temp_s3 + temp_lo;
        } else {
        DestroyEntity:
            DestroyEntity(self);
            return;
        }
        break;

    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.waterEffects.accelY;
        break;
    }

    x = self->posX.i.hi;
    y = self->posY.i.hi;

    prim = &g_PrimBuf[self->primIndex];
    while (prim != NULL) {
        prim->x0 = prim->x2 = x - (prim->p1 / 2) - 4;
        prim->x1 = prim->x3 = x + (prim->p1 / 2) + 4;
        prim->y0 = prim->y1 = y - (prim->p1 / 2) - 4;
        prim->y2 = prim->y3 = y + (prim->p1 / 2) + 4;
        if (prim->b1 >= 3) {
            prim->b1 += 253;
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1;
            if (prim->b3 >= 4) {
                prim->b3 += 252;
            }
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
            prim->p1++;
            prim = prim->next;
        } else {
            goto DestroyEntity;
        }
    }
}

// ID 0x30
void EntitySmallWaterDrop(Entity* self) {
    s32 params = self->params;
    s16 temp_s5 = params & 0xFF00;
    Primitive *prim, *prim2;
    s16 primIndex;
    s32 var_v1;
    u16 x, y;

    params &= 0xFF;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;

        x = self->posX.i.hi;
        y = self->posY.i.hi;
        y -= Random() & 3;

        if (temp_s5 > 0) {
            x += Random() & 3;
        } else {
            x -= Random() & 3;
        }
        self->posX.i.hi = x;
        self->posY.i.hi = y;

        while (prim != NULL) {
            prim->v0 = prim->u0 = 2;
            prim->x0 = x;
            prim->y0 = y;
            prim->r0 = 96;
            prim->g0 = 96;
            prim->b0 = 128;
            prim->priority = self->zPriority + 2;
            prim->drawMode = 0x33;
            prim = prim->next;
        }
        var_v1 = D_80182204[params * 2];
        if (temp_s5 > 0) {
            var_v1 = -var_v1;
        }
        self->velocityX = var_v1 + (temp_s5 * 16);
        self->velocityY = D_80182204[params * 2 + 1];
        self->ext.waterEffects.accelY = FIX(0.25);
        break;

    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.waterEffects.accelY;
        break;
    }

    x = self->posX.i.hi;
    y = self->posY.i.hi;

    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = x;
    prim->y0 = y;
    if (prim->b0 >= 8) {
        prim->b0 += 248;
        prim->r0 = prim->g0 -= 6;
        return;
    }
    DestroyEntity(self);
}

// ID 0x31
void EntityWaterDrop(Entity* self) {
    u16 x = self->posX.i.hi;
    u16 y = self->posY.i.hi;
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 0x21);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.generic.unk7C.s = 0x2F;
        self->flags |= FLAG_HAS_PRIMS;

        while (1) {
            prim->drawMode = 0x73;
            prim->priority = self->zPriority + 2;

            if (prim->next == NULL) {
                prim->u0 = 0;
                prim->x0 = 0;
                prim->y0 = 0;
                prim->drawMode &= ~DRAW_HIDE;
                break;
            }

            prim->x1 = 0;
            LOH(prim->r1) = 0;
            LOW(prim->r2) = (rand() * 8) + self->velocityY;
            prim->y1 = y + (rand() & 15);
            LOH(prim->b1) = x + (rand() & 31) - 16;
            LOH(prim->u2) = (rand() & 15) + 32;
            prim->b0 = prim->g0 = prim->r0 = 255;
            prim->v0 = prim->u0 = 2;
            prim->x0 = LOH(prim->b1);
            prim->y0 = prim->y1;
            prim = prim->next;
        }
        break;

    case 1:
        if (--self->ext.generic.unk7C.s == 0) {
            DestroyEntity(self);
            return;
        }

        prim = &g_PrimBuf[self->primIndex];

        while (1) {
            if (prim->next == NULL) {
                prim->u0 = 0;
                prim->x0 = 0;
                prim->y0 = 0;
                prim->drawMode &= ~DRAW_HIDE;
                return;
            }
            LOH(prim->b1) = prim->x0;
            prim->y1 = prim->y0;
            LOH(prim->u2)--;
            if (LOH(prim->u2) == 0) {
                prim->drawMode |= DRAW_HIDE;
            }
            LOW(prim->x1) += LOW(prim->r2);
            if (LOW(prim->r2) > 0x8000) {
                prim->r0 += 252;
                prim->g0 += 252;
                prim->b0 += 252;
            } else {
                LOW(prim->r2) += 0x3800;
            }
            prim->x0 = LOW(prim->b1);
            prim->y0 = prim->y1;
            prim = prim->next;
        }
        break;
    }
}

s32 func_801C6458(s16 yOffset) {
    s16 newY = yOffset + g_CurrentEntity->posY.i.hi;
    s32 expectedResult = 0;
    Collider collider;
    Entity* newEntity;
    s32 res;

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi, newY, &collider, 0);

    if (expectedResult == (collider.effects & EFFECT_SOLID)) {
        res = true;
    } else {
        res = false;
    }

    if (collider.effects & EFFECT_WATER) {
        if (!g_CurrentEntity->ext.merman.isUnderwater) {
            newEntity = AllocEntity(g_Entities + 232, g_Entities + 256);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_MERMAN_UNK0, g_CurrentEntity, newEntity);
                newEntity->posY.i.hi += yOffset;
                newEntity->zPriority = g_CurrentEntity->zPriority;
            }
            g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
            g_CurrentEntity->ext.merman.isUnderwater = true;
        }
    }
    return res;
}

void EntityMerman2(Entity* self) {
    s32 primIndex;
    Collider collider;
    Entity* newEntity;
    Entity* newEntity2;
    Primitive* prim;
    s16 posX, posY;
    s32 colRes;
    s32 offset;
    u32 colorOffset;
    s16* pos;
    s16 camY;
    s32 rnd;
    s32 i;

    if (self->ext.merman2.ignoreCol && (self->step < MERMAN2_7)) {
        SetStep(MERMAN2_7);
    }

    if ((self->flags & FLAG_DEAD) && (self->step < MERMAN2_DYING)) {
        PlaySfxPositional(0x71D);
        self->drawFlags = 0;
        if (self->flags & FLAG_HAS_PRIMS) {
            g_api.FreePrimitives(self->primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }
        self->hitboxState = 0;
        self->flags &= ~FLAG_UNK_20000000;
        SetStep(MERMAN2_DYING);
    }

    switch (self->step) {
    case MERMAN2_INIT:
        InitializeEntity(D_80180AB4);
        self->hitboxOffY = 8;
        self->zPriority = 0xA9;
        if (self->params != 0) {
            self->palette++;
        }
        self->velocityY = FIX(-1);
        break;

    case MERMAN2_SWIMMING_UP:
        AnimateEntity(D_8018229C, self);
        MoveEntity();
        posY = self->posY.i.hi - 24;
        g_api.CheckCollision(self->posX.i.hi, posY, &collider, 0);
        if (!(collider.effects & EFFECT_WATER)) {
            SetStep(MERMAN2_SWIMMING);
        }
        break;

    case MERMAN2_SWIMMING:
        if (self->step_s == 0) {
            rnd = Random() & 3;
            self->velocityX = D_80182224[rnd].x;
            self->velocityY = D_80182224[rnd].y;
            self->step_s++;
        }
        if (AnimateEntity(D_8018229C, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        MoveEntity();
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.effects & EFFECT_WATER)) {
            self->velocityY = FIX(0.5);
        }
        pos = D_80181230;
        pos += (self->params >> 8) & 1;
        posY += g_Tilemap.scrollY.i.hi;
        if (pos[4] < posY) {
            self->posY.i.hi = pos[4] - g_Tilemap.scrollY.i.hi - 24;
        }

        if ((u8)self->ext.merman2.timer++ > 32) {
            self->ext.merman2.timer = 0;
            self->step_s = 0;
            if ((GetDistanceToPlayerX() >= 48) && !(Random() & 1)) {
                SetStep(MERMAN2_JUMPING);
            }
        }
        break;

    case MERMAN2_JUMPING:
        switch (self->step_s) {
        case MERMAN2_JUMPING_SETUP:
            self->velocityX = 0;
            self->velocityY = FIX(-8.5);
            self->step_s++;
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                u32 v0;
                prim = &g_PrimBuf[primIndex];
                self->animCurFrame = 0;
                self->primIndex = primIndex;
                self->ext.merman2.prim = prim;
                self->flags |= FLAG_HAS_PRIMS;
                prim->tpage = 0x12;
                prim->clut = 0x28C;
                if (self->params & 1) {
                    prim->clut = 0x28D;
                }
                prim->u0 = 0;
                prim->u1 = 0x20;
                prim->v1 = prim->v0 = 0x38;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                v0 = prim->v0 + 0x38;
                prim->v2 = v0;
                prim->v3 = v0;

                if (self->facingLeft != 0) {
                    s16 posX = self->posX.i.hi;
                    prim->x0 = posX + 15;
                    prim->x1 = posX - 17;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                } else {
                    s16 posX = self->posX.i.hi;
                    prim->x0 = posX - 15;
                    prim->x1 = posX + 17;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                }
                prim->y0 = prim->y1 = self->posY.i.hi - 17;

                setRGB0(prim, 64, 64, 160);

                *(s32*)&prim->r1 = *(s32*)&prim->r0;
                *(s32*)&prim->r2 = *(s32*)&prim->r0;
                *(s32*)&prim->r3 = *(s32*)&prim->r0;

                prim->y3 = prim->y2 = prim->y0 + 0x38;
                prim->priority = self->zPriority;
                prim->drawMode = 6;
            } else {
                self->animCurFrame = 17;
                DestroyEntity(self);
            }
            break;

        case MERMAN2_JUMPING_UNDERWATER:
            MoveEntity();
            pos = D_80181230;
            pos += (self->params >> 8) & 1;
            posY = self->posY.i.hi;
            posY -= 24;
            camY = g_Tilemap.scrollY.i.hi + posY;
            if (camY < pos[3]) {
                g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
                newEntity = AllocEntity(g_Entities + 232, g_Entities + 256);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN_UNK0, self, newEntity);
                    newEntity->posY.i.hi -= 24;
                    newEntity->zPriority = self->zPriority;
                }
                self->rotZ = 0;
                self->drawFlags |= 4;
                self->step_s++;
            }
            break;

        case MERMAN2_JUMPING_IN_AIR:
            prim = self->ext.merman2.prim;
            if (self->velocityY > ~0xBFFF) {
                prim->drawMode = DRAW_HIDE;
                self->animCurFrame = 18;
                self->hitboxHeight = 8;
                self->rotZ -= 0x80;
            } else {
                if (self->facingLeft != 0) {
                    s16 posX = self->posX.i.hi;
                    prim->x0 = posX + 15;
                    prim->x1 = posX - 17;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                    prim->y1 = prim->y0 = self->posY.i.hi - 17;
                    prim->y3 = prim->y2 = prim->y0 + 0x38;
                } else {
                    s16 posX = self->posX.i.hi;
                    prim->x0 = posX - 15;
                    prim->x1 = posX + 17;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                    prim->y1 = prim->y0 = self->posY.i.hi - 17;
                    prim->y3 = prim->y2 = prim->y0 + 0x38;
                }

                colorOffset =
                    (u32)(((abs(self->velocityY) >> 0xC) - 10) & 0xFF) >> 1;

                setRGB0(prim, 128 - colorOffset, 128 - colorOffset,
                        colorOffset + 192);

                *(s32*)&prim->r1 = *(s32*)&prim->r0;
                *(s32*)&prim->r2 = *(s32*)&prim->r0;
                *(s32*)&prim->r3 = *(s32*)&prim->r0;
            }
            if (self->velocityY < 0) {
                newEntity = AllocEntity(g_Entities + 232, g_Entities + 256);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN2_UNK0, self, newEntity);
                    newEntity->posX.i.hi -= 6 - ((Random() & 3) * 4);
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
            if (self->velocityY > 0) {
                func_801C6458(0x1B);
            }
            if (self->ext.merman2.isUnderwater == 0) {
                if (func_801BC8E4(&D_80182248) & 1) {
                    g_api.FreePrimitives(self->primIndex);
                    self->hitboxHeight = 21;
                    self->flags &= ~FLAG_HAS_PRIMS;
                    self->drawFlags &= 0xFB;
                    SetStep(MERMAN2_WALKING_TO_PLAYER);
                }
            } else {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                               FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
                MoveEntity();
                self->velocityY += FIX(0.25);
            }
        }
        break;

    case MERMAN2_WALKING_TO_PLAYER:
        switch (self->step_s) {
        case MERMAN2_WALKING_TO_PLAYER_SETUP:
            if (AnimateEntity(D_80182294, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;

        case MERMAN2_WALKING_TO_PLAYER_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.merman2.timer = D_80182244[Random() & 3];
            self->step_s++;
            break;

        case MERMAN2_WALKING_TO_PLAYER_WALKING:
            AnimateEntity(D_80182270, self);
            colRes = func_801BCB5C(&D_80182268);
            if (colRes == 0xFF) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.375);
            } else {
                self->velocityX = FIX(0.375);
            }

            if (colRes & 0x80) {
                self->posX.val += self->velocityX;
            }

            if (!(self->params & 1) ||
                (self->velocityX *= 2, !(self->params & 1))) {
                if (!(self->posX.i.hi & 0xFF00)) {
                    self->ext.merman2.timer--;
                    if ((self->ext.merman2.timer & 0xFF) == 0) {
                        if (Random() % 2) {
                            SetStep(MERMAN2_SPIT_FIRE);
                        } else {
                            self->step_s--;
                        }
                    }
                    if (func_801C6458(0x1B)) {
                        self->ext.merman2.ignoreCol = 1;
                    }
                }
            } else {
                if (func_801C6458(0x1B)) {
                    self->ext.merman2.ignoreCol = 1;
                }
            }
        }
        break;

    case MERMAN2_SPIT_FIRE:
        switch (self->step_s) {
        case MERMAN2_SPIT_FIRE_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            break;

        case MERMAN2_SPIT_FIRE_ATTACK:
            if (AnimateEntity(D_8018227C, self) == 0) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
                newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
                i = 0;
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN2_UNK1, self, newEntity);
                    newEntity->posY.i.hi -= 12;
                    newEntity->facingLeft = self->facingLeft;
                }
                newEntity2 = g_Entities + 224;
                for (offset = 0; i < 3; i++, offset += 8) {
                    newEntity = AllocEntity(newEntity2, newEntity2 + 32);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(E_MERMAN2_UNK2, self, newEntity);
                        if (self->facingLeft != 0) {
                            newEntity->posX.i.hi += 8 + offset;
                        } else {
                            newEntity->posX.i.hi += -8 - offset;
                        }
                        newEntity->posY.i.hi -= 12;
                        newEntity->facingLeft = self->facingLeft;
                        if (i == 0) {
                            newEntity->params = 1;
                        }
                    }
                }
                self->ext.merman2.rotation = 1;
                self->rotZ = 0;
                self->drawFlags |= 4;
                if (self->facingLeft != 0) {
                    self->velocityX = FIX(-6);
                } else {
                    self->velocityX = FIX(6);
                }
                self->velocityY = FIX(-0.0625);
                self->posY.i.hi -= 1;
                self->step_s++;
            }
            break;

        case 2:
            if ((self->ext.merman2.rotation < 0x100) && (g_Timer & 1)) {
                self->ext.merman2.rotation *= 2;
            }
            if (self->velocityX != 0) {
                if (self->facingLeft != 0) {
                    self->velocityX += FIX(0.1875);
                } else {
                    self->velocityX -= FIX(0.1875);
                }
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            if (self->facingLeft != 0) {
                posX -= 20;
            } else {
                posX += 20;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
            }
            self->rotZ += self->ext.merman2.rotation;
            self->velocityY -= FIX(0.125);

            if (func_801BC8E4(&D_80182248) & 1) {
                if (self->facingLeft == 0) {
                    self->velocityX = FIX(2.5);
                } else {
                    self->velocityX = FIX(-5.0 / 2.0);
                }
                self->ext.merman2.rotation = 4;
                self->posY.i.hi += 10;
                self->step_s++;
            }
            func_801C6458(0x1B);
            if (self->ext.merman2.isUnderwater) {
                self->ext.merman2.ignoreCol = 1;
            }
            break;

        case 3:
            posY = self->posY.i.hi + 8;
            posX = self->posX.i.hi;
            if (self->facingLeft != 0) {
                posX -= 20;
            } else {
                posX += 20;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
            }
            MoveEntity();
            self->rotZ += 0xC0;
            if (self->rotZ > 0x1000) {
                self->posY.i.hi -= 10;
                self->drawFlags &= 0xFB;
                SetStep(MERMAN2_WALKING_TO_PLAYER);
            }
            if (func_801C6458(0x1B)) {
                self->ext.merman2.ignoreCol = 1;
            }
        }
        break;

    case MERMAN2_7:
        if (self->step_s == 0) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += FIX(0.25);
        if (!(func_801C6458(0x1B)) && !(self->ext.merman2.isUnderwater)) {
            self->ext.merman2.ignoreCol = 0;
            SetStep(MERMAN2_WALKING_TO_PLAYER);
        }
        break;

    case MERMAN2_DYING:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 14;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
            if (!(GetSideToPlayer() & 1)) {
                self->velocityX = FIX(-2);
            } else {
                self->velocityX = FIX(2);
            }
            self->velocityY = FIX(-1);
            self->step_s++;
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                u32 v0;
                prim = &g_PrimBuf[primIndex];
                self->primIndex = primIndex;
                self->ext.merman2.prim = prim;
                self->flags |= 0x800000;
                UnkPolyFunc2(prim);
                prim->tpage = 0x12;
                prim->clut = 0x292;
                if (self->params & 1) {
                    prim->clut = 0x293;
                }
                if (self->facingLeft != 0) {
                    u32 u1 = 0x1C8;
                    prim->u0 = 0xF0;
                    prim->u1 = u1;
                } else {
                    prim->u0 = 0xC8;
                    prim->u1 = 0xF0;
                }

                prim->v0 = prim->v1 = 0;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                v0 = prim->v0 + 0x30;
                prim->v2 = v0;
                prim->v3 = v0;

                prim->priority = self->zPriority + 1;
                prim->drawMode = 2;
                *(s16*)&prim->next->r2 = 0x28;
                *(s16*)&prim->next->b2 = 0x30;
                prim->next->b3 = 0x80;
                if (self->facingLeft != 0) {
                    prim->next->x1 = self->posX.i.hi - 3;
                } else {
                    prim->next->x1 = self->posX.i.hi + 3;
                }
                prim->next->y0 = self->posY.i.hi + 2;
            }
            UnkPrimHelper(prim);
            break;

        case 1:
            func_801BC8E4(&D_80182258);
            prim = self->ext.merman2.prim;
            self->velocityY -= FIX(0.1875);
            if (self->facingLeft != 0) {
                prim->next->x1 = self->posX.i.hi - 3;
            } else {
                prim->next->x1 = self->posX.i.hi + 3;
            }
            prim->next->y0 = self->posY.i.hi + 2;
            UnkPrimHelper(prim);
            if (!(g_Timer % 10)) {
                prim->clut += 2;
                if (prim->clut >= 0x2A0) {
                    prim->drawMode = DRAW_HIDE;
                    self->step_s++;
                } else {
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(E_MERMAN2_UNK3, self, newEntity);
                        newEntity->facingLeft = self->facingLeft;
                        newEntity->params = prim->clut;
                        newEntity->zPriority = self->zPriority;
                    }
                }
            }
            func_801C6458(0x1B);
            break;

        case 2:
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            func_801B653C();
            DestroyEntity(self);
        }
        break;
    }
}

// some sort of explosion: ID 0x36
void EntityExplosion2(Entity* entity, s32 arg1) {
    Primitive* prim;
    s16 primIndex;

    if (entity->step == 0) {
        InitializeEntity(D_80180AB4);
        entity->animCurFrame = 0;
        entity->hitboxState = 0;
        entity->zPriority += 4;
        if (entity->params != 0) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex == -1) {
                DestroyEntity(entity);
                return;
            }
            prim = &g_PrimBuf[primIndex];
            entity->primIndex = primIndex;
            *(s32*)&entity->ext.generic.unk7C.s = prim;
            entity->flags |= FLAG_HAS_PRIMS;
            UnkPolyFunc2(prim);
            prim->u0 = 0;
            prim->u1 = 0x20;
            prim->tpage = 0x1A;
            prim->clut = 0x1FF;
            prim->v3 = prim->v2 = 0x20;
            prim->v1 = prim->v0 = 0;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            LOH(prim->next->r2) = 0x40;
            LOH(prim->next->b2) = 0x40;
            LOH(prim->next->u1) = 0;
            prim->next->b3 = 0x60;
            prim->next->x1 = entity->posX.i.hi;
            prim->next->y0 = entity->posY.i.hi;
            prim->priority = entity->zPriority - 4;
            prim->drawMode = 6;
        }
    }

    if (entity->params != 0) {
        prim = *(s32*)&entity->ext.generic.unk7C.s;
        UnkPrimHelper(prim);
        prim->next->b3 += 252;
        LOH(prim->next->u1) -= 128;
        if (prim->next->b3 < 16) {
            prim->drawMode = DRAW_HIDE;
        }
    }

    entity->ext.generic.unk84.U8.unk0++;
    if (!(entity->ext.generic.unk84.U8.unk0 % 4)) {
        entity->posY.i.hi++;
    }

    if (AnimateEntity(D_801822B0, entity) == 0) {
        DestroyEntity(entity);
    }
}

void EntityMediumWaterSplash(Entity* entity) {
    Entity* newEntity;

    if (entity->step == 0) {
        InitializeEntity(D_80180AC0);
        entity->animCurFrame = 0;
        if (entity->facingLeft != 0) {
            entity->velocityX = FIX(2);
            return;
        }
        entity->velocityX = FIX(-2);
        return;
    }
    AnimateEntity(D_801822A4, entity);
    MoveEntity();
    if (entity->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
            newEntity->params = 0;
        }
        DestroyEntity(entity);
    }
}

void EntityMermanWaterSplash(Entity* self) {
    Unkstruct_801C7954 sp;
    Entity* newEntity;
    Primitive* prim;
    s16 primIndex;
    s16* posPtr;
    s32* velPtr;
    u8 temp;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        break;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.mermanWaterSplash.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;

        for (i = 0; prim != NULL; i++) {
            prim->g0 = prim->r0 = 64;
            prim->b0 = 160;
            prim->v0 = prim->u0 = 2;
            prim->x0 = self->posX.i.hi + D_801822F8[i];
            prim->y0 = self->posY.i.hi - 12;
            LOW(sp.y3) = D_801822D0[i].x;
            prim->y1 = sp.y1;
            prim->y3 = sp.y3;
            LOW(sp.x3) = D_801822D0[i].y;
            prim->x2 = sp.x2;
            prim->x3 = sp.x3;
            prim->p1 = 0;
            prim->p3 = 1;
            prim->p2 = i % 2;
            prim->priority = self->zPriority + 2;
            prim->drawMode = 0x33;
            prim = prim->next;
        }

        posPtr = &D_8018230C;
        velPtr = &D_8018231C;

        for (i = 0; i < 7; i++) {
            newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_MEDIUM_WATER_SPLASH, self, newEntity);
                newEntity->params = D_80182304[i];
                newEntity->posX.i.hi = newEntity->posX.i.hi + posPtr[i];
                newEntity->velocityX = velPtr[i];
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        self->ext.mermanWaterSplash.unk84 = 0;
        self->ext.mermanWaterSplash.unk86 = 0;
        self->step++;
        break;

    case 2:
        prim = self->ext.mermanWaterSplash.prim;
        temp = false;
        while (prim != NULL) {
            if (prim->p1 == 0) {
                sp.x0 = prim->x0;
                sp.x1 = prim->x1;
                sp.y0 = prim->y0;
                sp.y2 = prim->y2;
                sp.y1 = prim->y1;
                sp.y3 = prim->y3;
                sp.x2 = prim->x2;
                sp.x3 = prim->x3;
                temp |= true;
                LOW(sp.x1) += LOW(sp.y3);
                LOW(sp.y2) += LOW(sp.x3);
                LOW(sp.x3) += 0x2000;
                if ((LOW(sp.x3) > 0) && (prim->p2 != 0) && (prim->p3 != 0)) {
                    if (LOH(sp.x0) > self->posX.i.hi) {
                        LOW(sp.y3) += 0x4000;
                    } else {
                        LOW(sp.y3) -= 0x4000;
                    }
                    prim->p3 = 0;
                }
                if (prim->y0 & 0xFF00) {
                    prim->p1 = 1;
                    prim->drawMode |= 8;
                }
                prim->x0 = sp.x0;
                prim->x1 = sp.x1;
                prim->y0 = sp.y0;
                prim->y2 = sp.y2;
                prim->x2 = sp.x2;
                prim->x3 = sp.x3;
                prim->y1 = sp.y1;
                prim->y3 = sp.y3;
            }
            prim = prim->next;
        }
        if (!temp) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

void func_801C7D80(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180AB4);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->flags |= FLAG_UNK_2000;
        self->zPriority += 4;
    }
    MoveEntity();
    self->velocityY += FIX(0.15625);
    if (AnimateEntity(D_801822B8, self) == 0) {
        DestroyEntity(self);
    }
}

// ID 0x35
void func_801C7E18(Entity* self) {
    s8 temp; // probably !FAKE

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
        self->animSet = ANIMSET_DRA(2);
        self->velocityY = FIX(-5);
        self->palette = 0x8162;
        self->drawMode = DRAW_TPAGE;
        self->palette = 0x8018;
        self->drawMode = 0x30;
        self->unk6C = 0xA0;
        self->rotX = 0x100;
        self->rotY = 0x1A0;
        self->drawFlags |= 3;
        self->ext.generic.unk84.S8.unk1 = 0x11;
        self->ext.generic.unk84.S8.unk0 = self->params;
        self->drawFlags |= 8;
        break;

    case 1:
        temp = self->ext.generic.unk84.S8.unk0 - 1;
        self->ext.generic.unk84.S8.unk0--;
        self->ext.generic.unk84.S8.unk1--;
        if (!(temp & 0xFF)) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_801822C0, self);
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotX += 6;
        self->rotY -= 4;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        if (!--self->ext.generic.unk84.U8.unk1) {
            self->velocityY = 0;
            self->step++;
        }
        break;

    case 3:
        if (AnimateEntity(D_801822C0, self) == 0) {
            MoveEntity();
            self->velocityY += FIX(0.25);
            self->rotX += 6;
            self->rotY -= 4;
        }
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityLargeFallingObject(Entity* self) {
    u8 temp_v0;

    if (self->step == 0) {
        InitializeEntity(D_80180AB4);
        self->animCurFrame = 13;
        self->ext.generic.unk84.S8.unk0 = 0x20;
        self->hitboxState = 0;
        self->velocityY = FIX(0.0625);
        self->palette = self->params + 0xE;
        self->unk6C = 0x80;
        self->drawFlags |= 8;
        self->flags |= FLAG_UNK_2000;
        return;
    }
    MoveEntity();
    temp_v0 = self->ext.generic.unk84.U8.unk0 - 1;
    self->ext.generic.unk84.U8.unk0--;
    self->velocityY += FIX(0.0625);
    self->unk6C += 0xFE;
    if (temp_v0 == 0) {
        DestroyEntity(self);
    }
}

void EntityMermanSpawner(Entity* self) {
    Entity* newEntity;
    u16 temp_s0_2;
    u16 temp_s0;
    s32 temp2;
    s16 temp;

    if (self->step == 0) {
        InitializeEntity(D_80180A60);
        self->flags |= FLAG_UNK_2000;
    }

    if (!(g_Timer & 0x3F)) {
        Entity* player = &PLAYER;
        temp = g_Tilemap.scrollY.i.hi + player->posY.i.hi;
        if (temp >= 256) {
            temp_s0 = g_Tilemap.scrollX.i.hi + player->posX.i.hi;
            temp_s0_2 = 128;
            temp_s0_2 = temp_s0 - temp_s0_2 + Random();
            temp_s0 = temp_s0_2 - 64;
            if (temp_s0 <= 0x280) {
                temp2 = 496;
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[170]);
                if (newEntity != 0) {
                    if (Random() & 1) {
                        CreateEntityFromCurrentEntity(0x32, newEntity);
                        newEntity->params = Random() & 1;
                    } else {
                        CreateEntityFromCurrentEntity(0x39, newEntity);
                    }
                    newEntity->posX.i.hi = temp_s0_2 - g_Tilemap.scrollX.i.hi;
                    newEntity->posY.i.hi = temp2 - g_Tilemap.scrollY.i.hi;
                }
            }
        }
    }
}
