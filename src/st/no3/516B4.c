#include "no3.h"

// ID 0x35
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
                        temp_a2 = D_80183858[temp_s4];
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
                            temp_a0 = D_80183858[temp_s5];
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

            g_api.PlaySfxVolPan(D_801813A8, 0x7F, temp_a2);
            self->velocityY = D_80183878[params].x;
            self->ext.waterEffects.unk7C = D_80183878[params].y;
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
        self->velocityY += self->ext.waterEffects.unk7C;
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

// ID 0x36
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
            g_api.PlaySfxVolPan(D_801813AA, 0x7F, var_s2);
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
                var_s2 = D_80183858[params];
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
        self->ext.generic.unk84.S16.unk2 = D_80183898[(u8)self->params] + rnd;
        self->velocityX = self->ext.generic.unk88.S16.unk2 * 16;
        if (params != 0) {
            self->velocityY = self->velocityX / var_s2;
            if (self->velocityY < 0) {
                self->velocityY = -self->velocityY;
            }
        }
        break;

    case 1:
        self->ext.waterEffects.unk84.val -= 0x4000;
        break;
    }

    MoveEntity(self);

    //! FAKE:
    j = self->velocityX;

    if (self->velocityX != 0) {
        right = D_801813AC[self->ext.waterEffects.unk88];
        ptr = D_801813AC;
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
        prim->y0 = prim->y2 - self->ext.waterEffects.unk84.modeS16.unk2;
        prim->y1 = prim->y3 - self->ext.waterEffects.unk84.modeS16.unk2;
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

// ID 0x37
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
                g_api.PlaySfx(D_801813A8);
            }
            angle = LOH(D_801838E4[(params >> 3) & 0x1E]);
            ptr = (s32*)&D_801838A4[temp_s0];
            temp_s1 = rcos(angle) * *ptr;
            temp_s3 = rsin(angle + 0x800) * *ptr;
            ptr++;
            temp_s1 += rsin(angle) * *ptr;
            temp_lo = rcos(angle) * *ptr;
            self->velocityX = temp_s1 + (((params & 0xFF00) << 0x10) >> 0xE);
            self->ext.waterEffects.unk7C = 0x2C00;
            self->velocityY = temp_s3 + temp_lo;
        } else {
        DestroyEntity:
            DestroyEntity(self);
            return;
        }
        break;

    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.waterEffects.unk7C;
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

// ID 0x38
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
        var_v1 = D_801838F4[params * 2];
        if (temp_s5 > 0) {
            var_v1 = -var_v1;
        }
        self->velocityX = var_v1 + (temp_s5 * 16);
        self->velocityY = D_801838F4[params * 2 + 1];
        self->ext.waterEffects.unk7C = 0x4000;
        break;

    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.waterEffects.unk7C;
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

// ID 0x38
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

s32 func_801D2D40(s16 yVector) {
    s16 newY = yVector + g_CurrentEntity->posY.i.hi;
    s32 expectedResult = 0;
    Collider collider;
    Entity* newEntity;
    s32 res;

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi, newY, &collider, 0);
    res = expectedResult == (collider.effects & EFFECT_SOLID);

    if (collider.effects & EFFECT_WATER) {
        if (*(u8*)&g_CurrentEntity->ext.generic.unkA0 == 0) {
            newEntity = AllocEntity(g_Entities + 232, g_Entities + 256);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x3B, g_CurrentEntity, newEntity);
                newEntity->posY.i.hi += yVector;
                newEntity->zPriority = g_CurrentEntity->zPriority;
            }
            g_api.PlaySfx(SE_WATER_SPLASH);
            *(u8*)&g_CurrentEntity->ext.generic.unkA0 = 1;
        }
    }
    return res;
}

// another merman variant
INCLUDE_ASM("st/no3/nonmatchings/516B4", EntityMerman3);

// some sort of explosion
void EntityExplosion2(Entity* entity, s32 arg1) {
    Primitive* prim;
    s16 primIndex;

    if (entity->step == 0) {
        InitializeEntity(D_80180B48);
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
            prim->next->x1 = (u16)entity->posX.i.hi;
            prim->next->y0 = (u16)entity->posY.i.hi;
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
            prim->drawMode = 8;
        }
    }

    entity->ext.generic.unk84.U8.unk0++;
    if (!(entity->ext.generic.unk84.U8.unk0 % 4)) {
        entity->posY.i.hi++;
    }

    if (AnimateEntity(D_801839A0, entity) == 0) {
        DestroyEntity(entity);
    }
}

// medium sized water splash used with merman
void EntityMediumWaterSplash(Entity* entity) {
    Entity* newEntity;

    if (entity->step == 0) {
        InitializeEntity(D_80180B54);
        entity->animCurFrame = 0;
        if (entity->facingLeft != 0) {
            entity->velocityX = FIX(2);
            return;
        }
        entity->velocityX = FIX(-2);
        return;
    }
    AnimateEntity(D_80183994, entity);
    MoveEntity();
    if (entity->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, entity, newEntity);
            newEntity->params = 0;
        }
        DestroyEntity(entity);
    }
}

// spawns EntityMediumWaterSplash, part of merman splash
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
            prim->x0 = self->posX.i.hi + D_801839E8[i];
            prim->y0 = self->posY.i.hi - 12;
            LOW(sp.y3) = D_801839C0[i].x;
            prim->y1 = sp.y1;
            prim->y3 = sp.y3;
            LOW(sp.x3) = D_801839C0[i].y;
            prim->x2 = sp.x2;
            prim->x3 = sp.x3;
            prim->p1 = 0;
            prim->p3 = 1;
            prim->p2 = i % 2;
            prim->priority = self->zPriority + 2;
            prim->drawMode = 0x33;
            prim = prim->next;
        }

        posPtr = &D_801839FC;
        velPtr = &D_80183A0C;

        for (i = 0; i < 7; i++) {
            newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_MEDIUM_WATER_SPLASH, self, newEntity);
                newEntity->params = D_801839F4[i];
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

// some kind of falling object
void EntityFallingObject2(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180B48);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->flags |= 0x2000;
        self->zPriority += 4;
    }
    MoveEntity();
    self->velocityY += FIX(0.15625);
    if (AnimateEntity(D_801839A8, self) == 0) {
        DestroyEntity(self);
    }
}

void EntityUnkId3D(Entity* self) {
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
        AnimateEntity(D_801839B0, self);
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
        if (AnimateEntity(D_801839B0, self) == 0) {
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

// falling object, larger
void EntityLargeFallingObject(Entity* self) {
    u8 temp_v0;

    if (self->step == 0) {
        InitializeEntity(D_80180B48);
        self->animCurFrame = 13;
        self->ext.generic.unk84.S8.unk0 = 0x20;
        self->hitboxState = 0;
        self->velocityY = FIX(0.0625);
        self->palette = self->params + 0xE;
        self->unk6C = 0x80;
        self->drawFlags |= 8;
        self->flags |= 0x2000;
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
        InitializeEntity(D_80180AD0);
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
                        CreateEntityFromCurrentEntity(E_ID_3A, newEntity);
                        newEntity->params = Random() & 1;
                    } else {
                        CreateEntityFromCurrentEntity(E_ID_41, newEntity);
                    }
                    newEntity->posX.i.hi = temp_s0_2 - g_Tilemap.scrollX.i.hi;
                    newEntity->posY.i.hi = temp2 - g_Tilemap.scrollY.i.hi;
                }
            }
        }
    }
}

INCLUDE_ASM("st/no3/nonmatchings/516B4", EntityMerman);

// fireball shot by merman
void EntityMermanFireball(Entity* self) {
    Entity* entity;

    if (self->step == 0) {
        InitializeEntity(D_80180B6C);
        self->hitboxWidth = 6;
        self->animCurFrame = 0;
        self->hitboxHeight = 3;

        if (self->facingLeft != 0) {
            self->velocityX = 0x10000 | 0x8000; // LINT_IGNORE
        } else {
            self->velocityX = 0xFFFE0000 | 0x8000; // LINT_IGNORE
        }

        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotY = self->rotX = 0x80;

        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID_15, self, entity);
            entity->ext.generic.unk94 = 4;
            entity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            entity->zPriority = self->zPriority + 8;
            entity->rotY = entity->rotX = 192;
        }
    } else {
        AnimateEntity(D_80183AF0, self);
        MoveEntity();

        if (self->rotX < 0x100) {
            self->rotY = self->rotX += 8;
        }

        if (self->flags & FLAG_DEAD) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(2, self, entity);
                entity->params = 0;
            }
            DestroyEntity(self);
        }
    }
}

// some sort of falling object
void EntityFallingObject(Entity* arg0) {
    if (arg0->step == 0) {
        InitializeEntity(D_80180B60);
        arg0->animCurFrame = 0;
        arg0->hitboxState = 0;
        arg0->zPriority += 4;
        arg0->flags |= FLAG_UNK_2000;
    }
    MoveEntity();
    arg0->velocityY += FIX(5.0 / 32.0);
    if (AnimateEntity(D_80183B04, arg0) == 0) {
        DestroyEntity(arg0);
    }
}

extern u8 D_80183B44[];
extern s32 D_80183B30[];
extern u16 D_80183B48[];

// part of explosion when merman dies
void EntityMermanExplosion(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_InitializeEntityData0);
        self->palette = PAL_OVL(0x2BB);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = D_80183B44[self->params];
        self->velocityY = D_80183B30[self->params];
        self->step++;
        return;
    } else {
        self->animFrameDuration++;
        self->posY.val += self->velocityY;
    }

    if (!(self->animFrameDuration & 1)) {
        self->animCurFrame++;
    }

    if (D_80183B48[self->params] < self->animFrameDuration) {
        DestroyEntity(self);
    }
}
