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

extern u16 g_EInitWaterObject[];
extern s16 g_WaterXTbl[];           // pos TBL
extern Point32 g_merman2Swimvels[]; // accel_x TBL
extern s32 g_merman_coll1;          // Collision data
extern u8 g_merman_walkanim_init[]; // Animation
extern u8 g_merman2_swim_anim[];    // Animation
extern u8 g_merman2_walktimers[];   // timers
extern s32 g_merman2_coll3;         // Collision data
extern u16 g_merman_coll2;          // Collision data
extern u8 g_merman2_walkanim[];     // Animation
extern u8 g_merman2_spitfire[];     // Animation

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
        self->drawFlags = FLAG_DRAW_DEFAULT;
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
        InitializeEntity(g_EInitWaterObject);
        self->hitboxOffY = 8;
        self->zPriority = 0xA9;
        if (self->params != 0) {
            self->palette++;
        }
        self->velocityY = FIX(-1);
        break;

    case MERMAN2_SWIMMING_UP:
        AnimateEntity(g_merman2_swim_anim, self);
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
            self->velocityX = g_merman2Swimvels[rnd].x;
            self->velocityY = g_merman2Swimvels[rnd].y;
            self->step_s++;
        }
        if (AnimateEntity(g_merman2_swim_anim, self) == 0) {
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
        pos = g_WaterXTbl;
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
                prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            } else {
                self->animCurFrame = 17;
                DestroyEntity(self);
            }
            break;

        case MERMAN2_JUMPING_UNDERWATER:
            MoveEntity();
            pos = g_WaterXTbl;
            pos += (self->params >> 8) & 1;
            posY = self->posY.i.hi;
            posY -= 24;
            camY = g_Tilemap.scrollY.i.hi + posY;
            if (camY < pos[3]) {
                g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_MERMAN_JUMP_WATER, self, newEntity);
                    newEntity->posY.i.hi -= 24;
                    newEntity->zPriority = self->zPriority;
                }
                self->rotZ = 0;
                self->drawFlags |= FLAG_DRAW_ROTZ;
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
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN2_JUMP_AIR, self, newEntity);
                    newEntity->posX.i.hi -= 6 - ((Random() & 3) * 4);
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
            if (self->velocityY > 0) {
                CheckMermanEnteringWater(0x1B);
            }
            if (self->ext.merman2.isUnderwater == 0) {
                if (UnkCollisionFunc3(&g_merman_coll1) & 1) {
                    g_api.FreePrimitives(self->primIndex);
                    self->hitboxHeight = 21;
                    self->flags &= ~FLAG_HAS_PRIMS;
                    self->drawFlags &=
                        FLAG_DRAW_UNK80 | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                        FLAG_DRAW_UNK10 | FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY |
                        FLAG_DRAW_ROTX;
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
            if (AnimateEntity(g_merman_walkanim_init, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;

        case MERMAN2_WALKING_TO_PLAYER_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.merman2.timer = g_merman2_walktimers[Random() & 3];
            self->step_s++;
            break;

        case MERMAN2_WALKING_TO_PLAYER_WALKING:
            AnimateEntity(g_merman2_walkanim, self);
            colRes = UnkCollisionFunc2(&g_merman_coll2);
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
                    if (CheckMermanEnteringWater(0x1B)) {
                        self->ext.merman2.ignoreCol = 1;
                    }
                }
            } else {
                if (CheckMermanEnteringWater(0x1B)) {
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
            if (AnimateEntity(g_merman2_spitfire, self) == 0) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
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
                        CreateEntityFromEntity(
                            E_MERMAN2_SPIT_FIRE, self, newEntity);
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
                self->drawFlags |= FLAG_DRAW_ROTZ;
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

            if (UnkCollisionFunc3(&g_merman_coll1) & 1) {
                if (self->facingLeft == 0) {
                    self->velocityX = FIX(2.5);
                } else {
                    self->velocityX = FIX(-5.0 / 2.0);
                }
                self->ext.merman2.rotation = 4;
                self->posY.i.hi += 10;
                self->step_s++;
            }
            CheckMermanEnteringWater(0x1B);
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
                self->drawFlags &=
                    FLAG_DRAW_UNK80 | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                    FLAG_DRAW_UNK10 | FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY |
                    FLAG_DRAW_ROTX;
                SetStep(MERMAN2_WALKING_TO_PLAYER);
            }
            if (CheckMermanEnteringWater(0x1B)) {
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
        if (!(CheckMermanEnteringWater(0x1B)) &&
            !(self->ext.merman2.isUnderwater)) {
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
                self->flags |= FLAG_HAS_PRIMS;
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
                prim->drawMode = DRAW_UNK02;
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
            UnkCollisionFunc3(&g_merman2_coll3);
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
                        CreateEntityFromEntity(
                            E_MERMAN2_DYING, self, newEntity);
                        newEntity->facingLeft = self->facingLeft;
                        newEntity->params = prim->clut;
                        newEntity->zPriority = self->zPriority;
                    }
                }
            }
            CheckMermanEnteringWater(0x1B);
            break;

        case 2:
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            CreateExplosionPuff();
            DestroyEntity(self);
        }
        break;
    }
}

// some sort of explosion
void EntityExplosion2(Entity* self) {
    Primitive* prim;
    s16 primIndex;

    if (self->step == 0) {
        InitializeEntity(g_EInitWaterObject);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->zPriority += 4;
        if (self->params != 0) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.entityExplosion2.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
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
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            prim->priority = self->zPriority - 4;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        }
    }

    if (self->params != 0) {
        prim = self->ext.entityExplosion2.prim;
        UnkPrimHelper(prim);
        prim->next->b3 += 252;
        LOH(prim->next->u1) -= 128;
        if (prim->next->b3 < 16) {
            prim->drawMode = DRAW_HIDE;
        }
    }

    self->ext.entityExplosion2.unk84++;
    if (!(self->ext.entityExplosion2.unk84 % 4)) {
        self->posY.i.hi++;
    }

    if (AnimateEntity(g_explosion2anim, self) == 0) {
        DestroyEntity(self);
    }
}

// medium sized water splash used with merman
void EntityMediumWaterSplash(Entity* entity) {
    Entity* newEntity;

    if (entity->step == 0) {
        InitializeEntity(g_EInitWaterSplash);
        entity->animCurFrame = 0;
        if (entity->facingLeft != 0) {
            entity->velocityX = FIX(2);
            return;
        }
        entity->velocityX = FIX(-2);
        return;
    }
    AnimateEntity(g_MediumWaterSplashAnim, entity);
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
        InitializeEntity(g_EInitInteractable);
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
            prim->x0 = self->posX.i.hi + g_MermanSplashXOffset[i];
            prim->y0 = self->posY.i.hi - 12;
            LOW(sp.y3) = g_Merman2XY[i].x;
            prim->y1 = sp.y1;
            prim->y3 = sp.y3;
            LOW(sp.x3) = g_Merman2XY[i].y;
            prim->x2 = sp.x2;
            prim->x3 = sp.x3;
            prim->p1 = 0;
            prim->p3 = 1;
            prim->p2 = i % 2;
            prim->priority = self->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }

        posPtr = &g_Merman2posPtr;
        velPtr = &g_Merman2velPtr;

        for (i = 0; i < 7; i++) {
            newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_HIGH_WATER_SPLASH, self, newEntity);
                newEntity->params = g_HighWaterSplashParams[i];
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
                    prim->drawMode |= DRAW_HIDE;
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

void EntityFallingObject2(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitWaterObject);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->flags |= FLAG_UNK_2000;
        self->zPriority += 4;
    }
    MoveEntity();
    self->velocityY += FIX(0.15625);
    if (AnimateEntity(g_FallingObject2Anim, self) == 0) {
        DestroyEntity(self);
    }
}
