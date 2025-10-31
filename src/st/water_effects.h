// SPDX-License-Identifier: AGPL-3.0-or-later
extern u16 g_WaterSounds[];
extern s16 g_WaterXTbl[];

#ifdef VERSION_PSP
static s16 g_splashAspects[] = {0, 1, 2, 4, -1, -2, -4, -4};
#else
static s16 g_splashAspects[] = {0, 1, 2, 4, -1, -2, -4, 0};
#endif
static s16 unused[] = {
    0x0000, -0x1000, -0x0C00, -0x0800, 0x1000, 0x0C00, 0x0800, 0x0000};
static s32 g_SplashYMovement[] = {
    FIX(-6.5), FIX(9.0 / 32), FIX(-5.5), FIX(17.0 / 64),
    FIX(-4.5), FIX(0.25),     FIX(-3.5), FIX(15.0 / 64)};
static s16 g_SurfacingYTbl[] = {0, 2, 4, 6, 8, 10};
static s32 g_SideWaterSpeeds[] = {
    22, -46, -24, -55, 14, -62, -12, -45, 2, -74, -4, -52, 9, -60, -6, -61};
static s16 g_SideWaterAngles[] = {
    0x000, 0x100, 0x080, 0x040, 0xF00, 0xF80, 0xFC0, 0x000};
static s32 g_SmallWaterDropVel[] = {
    FIX(-1.5),  FIX(-1.6875), FIX(-0.75),  FIX(-1.375),
    FIX(-0.25), FIX(-1.4375), FIX(-0.375), FIX(-1.875)};

static u16 func_801C4144(s16 arg0, s16 arg1, s16 arg2, s16* arg3) {
    s16 temp;
    s16* ptr;

    ptr = &g_WaterXTbl[arg0 * 8];
    arg1 -= *ptr++;
    if (arg1 < 0) {
        return 0;
    }
    *arg3++ = arg1;

    temp = *ptr++ - arg1;
    if (temp <= 0) {
        return 0;
    }
    *arg3 = temp;

    temp = g_splashAspects[*ptr++];
    if (temp) {
        temp = arg1 / temp;
    } else {
        temp = 0;
    }

    temp = *ptr++ - temp;
    if (temp > arg2) {
        return 0;
    }
    if (arg2 >= *ptr++) {
        return 0;
    }
    return ((arg2 + 0x7FFF) + 1) - temp;
}

void EntityAlucardWaterEffect(Entity* self) {
    s16 sp10[2];
    s16 posX, posY;
    u16 sp28;
    Entity* tempEntity;
    s16 var_s1;
    s16 var_s3;
    s16 i;
    u16 sp30;
    u16 var_s6;
    u32 var_s7;
    u16 sp4A;
    s32 status;
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;

    posX = player->posX.i.hi + tilemap->scrollX.i.hi;
    status = g_Player.status;
    if (status & (PLAYER_STATUS_CROUCH | PLAYER_STATUS_TRANSFORM)) {
        if (status & PLAYER_STATUS_CROUCH) {
            sp4A = 0x14;
            var_s6 = 0x19;
            if (status & PLAYER_STATUS_WOLF_FORM) {
                sp4A = 0xA;
            }
        } else if (
            status & (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) {
            sp4A = 0xC;
            var_s6 = 5;
        } else if (status & PLAYER_STATUS_WOLF_FORM) {
            sp4A = 0x14;
            var_s6 = 0x19;
        }
    } else {
        sp4A = 0x28;
        var_s6 = 0x19;
    }
    posY = var_s6 + (player->posY.i.hi + tilemap->scrollY.i.hi);
    var_s3 = var_s1 = self->params;
    var_s3 &= 0xFF;
    var_s1 = var_s1 >> 8;
    for (i = 0; i < var_s1; i++, var_s3++) {
        sp28 = func_801C4144(var_s3, posX, posY, sp10);
        if (sp28) {
            sp30 = var_s3 * 8;
            break;
        }
    }
    var_s3 = sp28 & 0x7FFF;
    if (self->step) {
        if (F(player->velocityY).i.hi &&
            (status & (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) ==
                0) {
            if (F(player->velocityY).i.hi < 0) {
                if (!sp28) {
                    var_s1 = self->ext.aluwater.unk7C;
                    if (var_s1 && (var_s1 & 0x7FFF) < 17) {
                        var_s1 = self->ext.aluwater.unk88;
                        if (self->ext.aluwater.unk8C < 14) {
                            var_s7 = ((14 - self->ext.aluwater.unk8C) << 11) +
                                     (g_WaterXTbl[var_s1 + 2] << 8) +
                                     (g_WaterXTbl[var_s1 + 5] << 5);
                        } else {
                            if (self->ext.aluwater.unk8E < 14) {
                                var_s7 =
                                    ((self->ext.aluwater.unk8E + 14) << 11) +
                                    (g_WaterXTbl[var_s1 + 2] << 8) +
                                    (g_WaterXTbl[var_s1 + 6] << 5);
                            } else {
                                var_s7 = g_WaterXTbl[var_s1 + 2] << 8;
                            }
                        }
                        var_s1 = (var_s7 >> 8) & 7;
                        if (!var_s1 || var_s1 == 7) {
                            var_s1 = (var_s7 >> 5) & 7;
                            if (!var_s1 || var_s1 == 7) {
                                var_s1 = 0;
                            }
                        }
                        if (var_s1) {
                            for (i = 0; i < 8; i++) {
                                tempEntity = AllocEntity(
                                    &g_Entities[224], &g_Entities[256]);
                                if (tempEntity == NULL) {
                                    break;
                                }
                                CreateEntityFromEntity(
                                    E_SIDE_WATER_SPLASH, player, tempEntity);
                                tempEntity->params =
                                    (u16)g_WaterXTbl[self->ext.aluwater.unk88 +
                                                     7] +
                                    (var_s1 << 4) + i;
                                tempEntity->posY.i.hi += var_s6 - var_s3;
                                tempEntity->zPriority = player->zPriority;
                            }
                        } else {
                            tempEntity =
                                AllocEntity(&g_Entities[224], &g_Entities[256]);
                            if (tempEntity != NULL) {
                                CreateEntityFromEntity(
                                    E_SPLASH_WATER, player, tempEntity);
                                tempEntity->posX.i.hi =
                                    self->ext.aluwater.unk80 -
                                    tilemap->scrollX.i.hi;
                                tempEntity->posY.i.hi =
                                    self->ext.aluwater.unk82 -
                                    (self->ext.aluwater.unk7C & 0x7FFF) -
                                    tilemap->scrollY.i.hi;
                                tempEntity->zPriority = player->zPriority;
                                if (player->velocityY > FIX(-4)) {
                                    tempEntity->params = var_s7 + 1;
                                } else {
                                    tempEntity->params = var_s7;
                                }
                            }
                        }
                    }
                }
            } else if (sp28 && (var_s3 < 9) && !self->ext.aluwater.unk7C) {
                if (sp10[0] < 14) {
                    var_s7 =
                        ((14 - sp10[0]) << 11) + (g_WaterXTbl[sp30 + 2] << 8) +
                        (g_WaterXTbl[sp30 + 5] << 5);
                } else if (sp10[1] < 14) {
                    var_s7 =
                        ((sp10[1] + 14) << 11) + (g_WaterXTbl[sp30 + 2] << 8) +
                        (g_WaterXTbl[sp30 + 6] << 5);
                } else {
                    var_s7 = g_WaterXTbl[sp30 + 2] << 8;
                }
                var_s1 = (var_s7 >> 8) & 7;
                if (!var_s1 || var_s1 == 7) {
                    var_s1 = (var_s7 >> 5) & 7;
                    if (!var_s1 || var_s1 == 7) {
                        var_s1 = 0;
                    }
                }
                if (var_s1) {
                    for (i = 0; i < 8; i++) {
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity == NULL) {
                            break;
                        }
                        CreateEntityFromEntity(
                            E_SIDE_WATER_SPLASH, player, tempEntity);
                        tempEntity->params =
                            (u16)g_WaterXTbl[sp30 + 7] + (var_s1 << 4) + i;
                        tempEntity->posY.i.hi += var_s6 - var_s3;
                        tempEntity->zPriority = player->zPriority;
                    }
                } else {
                    tempEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (tempEntity != NULL) {
                        CreateEntityFromEntity(
                            E_SPLASH_WATER, player, tempEntity);
                        if (player->velocityY > FIX(4)) {
                            tempEntity->params = var_s7 + 1;
                        } else {
                            tempEntity->params = var_s7 + 2;
                        }
                        tempEntity->params =
                            var_s7; // this nullifies the above block!
                        tempEntity->posY.i.hi += var_s6 - var_s3;
                        tempEntity->zPriority = player->zPriority;
                    }
                }
            }
        } else if ((status & PLAYER_STATUS_MIST_FORM) == 0) {
            if (sp28 && !self->ext.aluwater.unk7E) {
                var_s1 = g_WaterXTbl[sp30 + 7];
                if (posX != self->ext.aluwater.unk80) {
                    if (var_s3 <= sp4A && sp10[0] >= 6 && sp10[1] >= 6) {
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(
                                E_SURFACING_WATER, player, tempEntity);
                            tempEntity->posY.i.hi += var_s6 - var_s3;
                            if (player->velocityX != 0) {
                                tempEntity->params = (sp4A - var_s3) >> 3;
                                if (tempEntity->params == 5) {
                                    tempEntity->params = 4;
                                }
                            } else {
                                tempEntity->params = 0;
                            }
                            tempEntity->params |= g_WaterXTbl[sp30 + 2] << 8;
                            tempEntity->ext.aluwater.unk88 = sp30;
                            tempEntity->ext.aluwater.unk8A = var_s1;
                            tempEntity->zPriority = player->zPriority;
                            self->ext.aluwater.unk7E = 8;
                        }
                    }
                } else if (
                    var_s1 && var_s3 <= sp4A && sp10[0] >= 6 && sp10[1] >= 6) {
                    tempEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (tempEntity != NULL) {
                        CreateEntityFromEntity(
                            E_SURFACING_WATER, player, tempEntity);
                        tempEntity->posY.i.hi += var_s6 - var_s3;
                        tempEntity->params = g_WaterXTbl[sp30 + 2] << 8;
                        tempEntity->ext.aluwater.unk88 = sp30;
                        tempEntity->ext.aluwater.unk8A = var_s1;
                        tempEntity->zPriority = player->zPriority;
                        self->ext.aluwater.unk7E = 8;
                    }
                }
            }
            if (sp28) {
                var_s1 = g_WaterXTbl[sp30 + 7];
                if (var_s1 > 0x1000 || var_s1 < -0x1000) {
                    if (var_s3 >= sp4A) {
                        if (status & PLAYER_STATUS_BAT_FORM) {
                            var_s1 = var_s1 * 3 / 4;
                        } else {
                            var_s1 /= 2;
                        }
                    } else {
                        var_s1 = (var_s1 * var_s3) / 0x50;
                    }
                    if ((var_s1 < 0 &&
                         !(g_Player.vram_flag & TOUCHING_L_WALL)) ||
                        (var_s1 > 0 &&
                         !(g_Player.vram_flag & TOUCHING_R_WALL))) {
                        player->posX.val += var_s1 << 4;
                    }
                }
            }
        }
        if (self->ext.aluwater.unk7E) {
            self->ext.aluwater.unk7E--;
        }
        D_80097448[0] = var_s3;
        if (status & (PLAYER_STATUS_CROUCH | PLAYER_STATUS_TRANSFORM)) {
            if (status & PLAYER_STATUS_CROUCH) {
                if (status & PLAYER_STATUS_WOLF_FORM) {
                    if (var_s3 > 4) {
                        D_80097448[1] = var_s3 - 4;
                    } else {
                        D_80097448[1] = 0;
                    }
                    if (var_s3 > 12) {
                        D_80097450 = var_s3 - 12;
                    } else {
                        D_80097450 = 0;
                    }
                } else {
                    if (var_s3 > 8) {
                        D_80097448[1] = var_s3 - 8;
                    } else {
                        D_80097448[1] = 0;
                    }
                    if (var_s3 > 0x18) {
                        D_80097450 = var_s3 - 0x18;
                    } else {
                        D_80097450 = 0;
                    }
                }
            } else if (
                status & (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) {
                if (var_s3 > 6) {
                    D_80097448[1] = var_s3 - 6;
                } else {
                    D_80097448[1] = 0;
                }
                if (var_s3 > 0x10) {
                    D_80097450 = var_s3 - 0x10;
                } else {
                    D_80097450 = 0;
                }
            } else if (status & PLAYER_STATUS_WOLF_FORM) {
                if (var_s3 > 8) {
                    D_80097448[1] = var_s3 - 8;
                } else {
                    D_80097448[1] = 0;
                }
                if (var_s3 > 0x18) {
                    D_80097450 = var_s3 - 0x18;
                } else {
                    D_80097450 = 0;
                }
            }
        } else {
            if (var_s3 > 0x10) {
                D_80097448[1] = var_s3 - 0x10;
            } else {
                D_80097448[1] = 0;
            }
            if (var_s3 > 0x30) {
                D_80097450 = var_s3 - 0x30;
            } else {
                D_80097450 = 0;
            }
        }
    } else {
        InitializeEntity(g_EInitSpawner);
    }
    self->ext.aluwater.unk7C = sp28;
    self->ext.aluwater.unk80 = posX;
    self->ext.aluwater.unk82 = posY;
    self->ext.aluwater.unk88 = sp30;
    self->ext.aluwater.unk8C = sp10[0];
    self->ext.aluwater.unk8E = sp10[1];
}

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
            PGREY(prim, 0) = PGREY(prim, 1) = 0xFF;
            PGREY(prim, 2) = PGREY(prim, 3) = 0x80;
            prim->clut = 0x162;
            prim->tpage = 0x1A;
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            if (i & 1) {
                PGREY(prim, 0) = PGREY(prim, 1) = 0x00;
                PGREY(prim, 2) = PGREY(prim, 3) = 0x60;
                prim->clut = PAL_FILL_WHITE;
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

        g_api.PlaySfxVolPan(g_WaterSounds[0], 0x7F, aspect);

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
            PGREY(prim, 2) = PGREY(prim, 3);
        } else {
            if (prim->b3 >= 8) {
                prim->b3 -= 4;
            }
            PGREY(prim, 2) = PGREY(prim, 3);
            if (prim->b3 <= 8) {
                if (prim->b1 >= 8) {
                    prim->b1 -= 8;
                }
                PGREY(prim, 0) = PGREY(prim, 1);
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
            g_api.PlaySfxVolPan(g_WaterSounds[1], 0x7F, temp_s3);
        }
#ifdef VERSION_PSP
        params = (params >> 5) & 0x7;
#else
        params = (params >> 8) & 0x7F;
#endif
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
        prim = &g_PrimBuf[primIndex];
        while (prim != NULL) {
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
            prim = prim->next;
        }
        params = self->params;
        if (!(params & 0xF)) {
            g_api.PlaySfx(g_WaterSounds[0]);
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

    prim = &g_PrimBuf[self->primIndex];
    while (prim != NULL) {
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
        prim = prim->next;
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
    } else {
        DestroyEntity(self);
        return;
    }
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

            prim->posX.i.lo = prim->posY.i.lo = 0;
            prim->velocityY.val = (rand() & PSP_RANDMASK) * 8 + self->velocityY;
            prim->posY.i.hi = y + (rand() & 15);
            prim->posX.i.hi = x + (rand() & 31) - 16;
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
