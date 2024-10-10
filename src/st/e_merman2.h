// SPDX-License-Identifier: AGPL-3.0-or-later

extern u16 g_EInitCommon[];

typedef enum {
    MERMAN2_INIT,
    MERMAN2_SWIMMING_UP,
    MERMAN2_SWIMMING = 3,
    MERMAN2_JUMPING,
    MERMAN2_WALKING_TO_PLAYER,
    MERMAN2_SPIT_FIRE,
    MERMAN2_7,
    MERMAN2_DYING,
} Merman2Steps;

typedef enum {
    MERMAN2_JUMPING_SETUP,
    MERMAN2_JUMPING_UNDERWATER,
    MERMAN2_JUMPING_IN_AIR,
} Merman2JumpingSubSteps;

typedef enum {
    MERMAN2_WALKING_TO_PLAYER_SETUP,
    MERMAN2_WALKING_TO_PLAYER_FACE_PLAYER,
    MERMAN2_WALKING_TO_PLAYER_WALKING,
} Merman2WalkingToPlayerSubSteps;

typedef enum {
    MERMAN2_SPIT_FIRE_FACE_PLAYER,
    MERMAN2_SPIT_FIRE_ATTACK,
} Merman2SpitFireSubSteps;

void EntitySplashWater(Entity* self) {
    s32 primIndex;
    Tilemap* tilemap = &g_Tilemap;
    u16 params;
    u16 index1;
    u16 width;
    s16 aspect; // sets y size based on x size
    u16 index2;

    Primitive *prim, *prim2;
    Entity* newEntity;
    s16 selfY;
    s16 selfX;
    s32 i;

    params = self->params;
    width = params / 0x800;
    index1 = (params >> 8) & 7;
    index2 = (params >> 5) & 7;
    params &= 0xF;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        if (width && index2 != 7) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        } else {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        }
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        i = 0;
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        self->ext.waterEffects.unk82 = selfY + tilemap->scrollY.i.hi;
        for (; prim != NULL; i++, prim = prim->next) {
            if (i & 1) {
                prim->u0 = prim->u2 = prim2->u0;
                prim->u1 = prim->u3 = prim2->u1;
                prim->v0 = prim->v1 = prim2->v0;
                prim->v2 = prim->v3 = prim2->v2;
                prim->y2 = prim2->y2;
                prim->y3 = prim2->y3;
                prim->x2 = prim->x0 = prim2->x0;
                prim->x3 = prim->x1 = prim2->x1;
            } else {
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x20;
                prim->v0 = prim->v1 = 96;
                prim->v2 = prim->v3 = 0x7C;
                prim->y2 = prim->y3 = selfY;
                prim->x2 = prim->x0 = selfX - 0xE;
                prim->x3 = prim->x1 = selfX + 0xE;
                if (i > 1) {
                    aspect = g_splashAspects[index2];
                    if (width > 14) {
                        prim->u0 = prim->u2 = prim2->u1;
                        prim->x0 = prim->x2 = prim2->x1;
                        prim->y2 = prim2->y3;
                        if (aspect) {
                            prim->y3 =
                                prim->y2 - (prim->x1 - prim->x0) / aspect;
                        } else {
                            prim->y3 = prim->y2;
                        }
                    } else {
                        prim->u1 = prim->u3 = prim2->u0;
                        prim->x1 = prim->x3 = prim2->x0;
                        prim->y3 = prim2->y2;
                        if (aspect) {
                            prim->y2 =
                                prim->y3 + (prim->x1 - prim->x0) / aspect;
                        } else {
                            prim->y2 = prim->y3;
                        }
                    }
                } else {
                    if (width) {
                        if (width > 14) {
                            prim->u1 = prim->u3 = prim->u0 + (width << 5) / 28;
                            prim->x1 = prim->x3 = prim->x0 + width;
                        } else {
                            prim->u0 = prim->u2 += (width << 5) / 28;
                            prim->x0 = prim->x2 += width;
                        }
                    }
                    if (index1) {
                        aspect = g_splashAspects[index1];
                        if (aspect < 0) {
                            if (selfX >= prim->x1) {
                                prim->y2 += (prim->x1 - prim->x0) / aspect;
                            } else {
                                prim->y2 += (selfX - prim->x0) / aspect;
                                prim->y3 -= (prim->x1 - selfX) / aspect;
                            }
                        } else if (prim->x0 >= selfX) {
                            prim->y3 -= (prim->x1 - prim->x0) / aspect;
                        } else {
                            prim->y2 += (selfX - prim->x0) / aspect;
                            prim->y3 -= (prim->x1 - selfX) / aspect;
                        }
                    }
                }
            }
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                255;
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                128;
            prim->clut = 0x162;
            prim->tpage = 0x1A;
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            if (i & 1) {
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = 0;
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 96;
                prim->clut = 0x15F;
                prim->priority += 2;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
            }
            prim2 = prim;
        }

        aspect = (self->posX.i.hi - 120) >> 4;
        if (aspect < -8) {
            aspect = -8;
        }
        if (aspect > 8) {
            aspect = 8;
        }

        g_api.PlaySfxVolPan(g_SplashSfx, 0x7F, aspect);

        self->velocityY = g_SplashYMovement[params * 2];
        self->ext.waterEffects.accelY = g_SplashYMovement[params * 2 + 1];

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromCurrentEntity(E_WATER_DROP, newEntity);
            newEntity->velocityY = self->velocityY;
        }
        break;

    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.waterEffects.accelY;
        if (self->velocityY > FIX(2.5)) {
            self->step++;
        }
        break;

    case 2:
        MoveEntity(self);
        prim = &g_PrimBuf[self->primIndex];
        if (prim->r0 < 9) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    selfY =
        self->ext.waterEffects.unk82 - self->posY.i.hi - tilemap->scrollY.i.hi;
    for (i = 0, prim = &g_PrimBuf[self->primIndex]; prim != NULL; i++,
        prim = prim->next) {
        prim->y0 = prim->y2 - selfY;
        prim->y1 = prim->y3 - selfY;
        if (i & 1) {
            if (prim->b3 >= 4) {
                prim->b3 -= 4;
            }
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        } else {
            if (prim->b3 >= 8) {
                prim->b3 -= 4;
            }
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
            if (prim->b3 <= 8) {
                if (prim->b1 >= 8) {
                    prim->b1 -= 8;
                }
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1;
            }
        }
    }
}

void EntitySurfacingWater(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Primitive* prim;
    s32 primIndex;
    s16 temp_s3;
    u16 params;
    s16 x, y;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        temp_s3 = (self->posX.i.hi - 120) >> 4;
        if (temp_s3 < -8) {
            temp_s3 = -8;
        }
        if (temp_s3 > 8) {
            temp_s3 = 8;
        }
        params = self->params;
        if (!(params & 0x8000)) {
            g_api.PlaySfxVolPan(g_SurfacingSfx, 0x7F, temp_s3);
        }
        params = (params >> 8) & 0x7F;
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        self->ext.waterEffects.unk82 = y + tilemap->scrollY.i.hi;
        prim = &g_PrimBuf[primIndex];
        for (i = 0; i < 2; i++) {
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x1E;
            prim->v0 = prim->v1 = 0x60;
            prim->v2 = prim->v3 = 0x7C;
            prim->y2 = prim->y3 = y;
            prim->x2 = prim->x0 = x - 9;
            prim->x3 = prim->x1 = x + 9;
            if (params) {
                temp_s3 = g_splashAspects[params];
                prim->y2 += 9 / temp_s3;
                prim->y3 -= 9 / temp_s3;
            }
            PGREY(prim, 0) = PGREY(prim, 1) = 255;
            PGREY(prim, 2) = PGREY(prim, 3) = 128;

            prim->clut = 0x162;
            prim->tpage = 0x1A;
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            if (i != 0) {
                prim->clut = 0x161;
                prim->priority = self->zPriority + 4;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }
        self->ext.waterEffects.topY.i.hi =
            g_SurfacingYTbl[self->params & 0xFF] + 12 + (rand() & 1);
        self->velocityX = self->ext.waterEffects.unk8A * 16;
        if (params) {
            self->velocityY = self->velocityX / temp_s3;
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
    i = self->velocityX;
    if (i != 0) {
        x = g_WaterXTbl[self->ext.waterEffects.unk88];
        if (i < 0) {
            x += 6 - tilemap->scrollX.i.hi;
            if (self->posX.i.hi < x) {
                DestroyEntity(self);
                return;
            }
        } else {
            x += (g_WaterXTbl[self->ext.waterEffects.unk88 + 1] - 6 -
                  tilemap->scrollX.i.hi);
            if (self->posX.i.hi >= x) {
                DestroyEntity(self);
                return;
            }
        }
    }

    x = self->posX.i.hi;
    y = self->ext.waterEffects.unk82 - self->posY.i.hi - tilemap->scrollY.i.hi;

    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < 2; i++) {
        prim->y2 -= y;
        prim->y3 -= y;
        prim->y0 = prim->y2 - self->ext.waterEffects.topY.i.hi;
        prim->y1 = prim->y3 - self->ext.waterEffects.topY.i.hi;
        prim->x2 = prim->x0 = x - 9;
        prim->x3 = prim->x1 = x + 9;
        prim->b1 -= 8;
        PGREY(prim, 0) = PGREY(prim, 1);
        prim->b3 -= 4;
        PGREY(prim, 2) = PGREY(prim, 3);
        if (prim->r0 < 9) {
            DestroyEntity(self);
            return;
        }
        prim = prim->next;
    }
    self->ext.waterEffects.unk82 = self->posY.i.hi + tilemap->scrollY.i.hi;
}

void EntitySideWaterSplash(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 velY;
    u16 params;
    s16 angle;
    s32 velX;
    s16 y;
    s16 x;
    s32* speedPtr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        for (prim = &g_PrimBuf[primIndex]; prim != NULL; prim = prim->next) {
            prim->u0 = prim->u2 = 0xF0;
            prim->u1 = prim->u3 = 0xFF;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0xF;
            prim->clut = 0x161;
            prim->tpage = 0x1A;
            PGREY(prim, 0) = PGREY(prim, 1) = 128;
            PGREY(prim, 2) = PGREY(prim, 3) = 128;

            prim->p1 = 0;
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        }
        params = self->params;
        if (!(params & 0xF)) {
            g_api.PlaySfx(g_SplashSfx);
        }
        angle = g_SideWaterAngles[(params >> 4) & 0xF];
        // Two speeds. Get the pointer for the first one.
        speedPtr = &g_SideWaterSpeeds[(params & 0xF) * 2];
        velX = rcos(angle) * *speedPtr;
        velY = rsin(angle + 0x800) * *speedPtr++; // Now increment
        // use the second speed in the speed array now
        velX += rsin(angle) * *speedPtr;
        velY += rcos(angle) * *speedPtr;
        velX += (s16)(params & 0xFF00) * 4;
        self->velocityX = velX;
        self->velocityY = velY;
        self->ext.waterEffects.accelY = FIX(22.0 / 128);
        break;

    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.waterEffects.accelY;
        break;
    }

    x = self->posX.i.hi;
    y = self->posY.i.hi;

    for (prim = &g_PrimBuf[self->primIndex]; prim != NULL; prim = prim->next) {
        prim->x0 = prim->x2 = x - (prim->p1 / 2) - 4;
        prim->x1 = prim->x3 = x + (prim->p1 / 2) + 4;
        prim->y0 = prim->y1 = y - (prim->p1 / 2) - 4;
        prim->y2 = prim->y3 = y + (prim->p1 / 2) + 4;
        if (prim->b1 >= 3) {
            prim->b1 -= 3;
        } else {
            DestroyEntity(self);
            return;
        }
        PGREY(prim, 0) = PGREY(prim, 1);
        if (prim->b3 >= 4) {
            prim->b3 -= 4;
        }
        PGREY(prim, 2) = PGREY(prim, 3);
        prim->p1++;
    }
}

void EntitySmallWaterDrop(Entity* self) {
    u16 params = self->params;
    s16 upperParams = params & 0xFF00;
    Primitive *prim, *prim2;
    s32 primIndex;
    s32 xVel;
    s16 x, y;

    params &= 0xFF;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];

        x = self->posX.i.hi;
        y = self->posY.i.hi;
        y -= Random() & 3;

        if (upperParams > 0) {
            x += Random() & 3;
        } else {
            x -= Random() & 3;
        }
        self->posX.i.hi = x;
        self->posY.i.hi = y;

        while (prim != NULL) {
            prim->u0 = 2;
            prim->v0 = 2;
            prim->x0 = x;
            prim->y0 = y;
            prim->r0 = 96;
            prim->g0 = 96;
            prim->b0 = 128;
            prim->priority = self->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        xVel = g_SmallWaterDropVel[params * 2];
        if (upperParams > 0) {
            xVel = -xVel;
        }
        self->velocityX = xVel + (upperParams * 16);
        self->velocityY = g_SmallWaterDropVel[params * 2 + 1];
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
        prim->b0 -= 8;
        prim->r0 = prim->g0 -= 6;
        return;
    }
    DestroyEntity(self);
}

void EntityWaterDrop(Entity* self) {
    s16 x = self->posX.i.hi;
    s16 y = self->posY.i.hi;
    FakePrim* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 0x21);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        self->ext.timer.t = 0x2F;
        prim = (FakePrim*)&g_PrimBuf[primIndex];

        while (1) {
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim->priority = self->zPriority + 2;

            if (prim->next == NULL) {
                prim->drawMode &= ~DRAW_HIDE;
                prim->y0 = prim->x0 = prim->w = 0;
                break;
            }

            prim->posX.i.lo = prim->posY.i.lo = 0; // halfword at 0x10?
            prim->velocityY.val = (rand() * 8) + self->velocityY; // word at
                                                                  // 0x1C
            prim->posY.i.hi = y + (rand() & 15);
            prim->posX.i.hi = x + (rand() & 31) - 16; // halfword at 0x12
            prim->delay = (rand() & 15) + 32;
            prim->x0 = prim->posX.i.hi;
            prim->y0 = prim->posY.i.hi;
            prim->r0 = 255;
            prim->g0 = 255;
            prim->b0 = 255;
            prim->w = 2;
            prim->h = 2;
            prim = prim->next;
        }
        break;

    case 1:
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }

        prim = (FakePrim*)&g_PrimBuf[self->primIndex];

        while (1) {
            if (prim->next == NULL) {
                prim->drawMode &= ~DRAW_HIDE;
                prim->y0 = prim->x0 = prim->w = 0;
                return;
            }
            prim->posX.i.hi = prim->x0;
            prim->posY.i.hi = prim->y0;
            if (!--prim->delay) {
                prim->drawMode |= DRAW_HIDE;
            }
            prim->posY.val += prim->velocityY.val;
            if (prim->velocityY.val > FIX(0.5)) {
                prim->r0 -= 4;
                prim->g0 -= 4;
                prim->b0 -= 4;
            } else {
                prim->velocityY.val += FIX(28.0 / 128);
            }
            prim->x0 = prim->posX.i.hi;
            prim->y0 = prim->posY.i.hi;
            prim = prim->next;
        }
        break;
    }
}

// Detects if the merman is splashing into water.
// If so, creates a splash effect, and sets merman underwater to true.
bool CheckMermanEnteringWater(s16 yOffset) {
    Collider collider;
    Entity* newEntity;
    s32 res = false;

    s16 x = g_CurrentEntity->posX.i.hi;
    s16 y = g_CurrentEntity->posY.i.hi + yOffset;
    g_api.CheckCollision(x, y, &collider, 0);

    if (!(collider.effects & EFFECT_SOLID)) {
        res = true;
    }

    if (collider.effects & EFFECT_WATER) {
        if (!g_CurrentEntity->ext.merman.isUnderwater) {
            newEntity = AllocEntity(g_Entities + 232, g_Entities + 256);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_MERMAN_JUMP_WATER, g_CurrentEntity, newEntity);
                newEntity->posY.i.hi += yOffset;
                newEntity->zPriority = g_CurrentEntity->zPriority;
            }
            g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
            g_CurrentEntity->ext.merman.isUnderwater = true;
        }
    }
    return res;
}
