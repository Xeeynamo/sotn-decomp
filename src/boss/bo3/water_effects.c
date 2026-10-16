// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

extern EInit g_EInitInteractable;
extern EInit g_EInitCommon;
extern s16 water_surface_lines[];
extern s16 water_tile_rects[];
extern EInit g_EInitSpawner;

s16 D_us_80180C64 = 0;
u16 D_us_80180C66 = 0;
s16 D_us_80180C68[] = {0x0000, 0x04D0, 0x00D8, 0x00E8, 0x0068, 0x00B0,
                       0x00F0, 0x00F0, 0x0340, 0x0074, 0x00F0, 0x00F0};

s16 D_us_801B2870;
s16 D_us_801B2872;
u16 D_us_801B2874;

static void func_us_801A071C(void) {
    s16* data;
    s16* tileRects;
    s16* surfaceLines;
    s16 value;

    data = D_us_80180C68;
    tileRects = water_tile_rects;
    surfaceLines = water_surface_lines;
    data += 2;
    tileRects += 0x6E;
    surfaceLines += 0x70;

    value = 0xD8 - D_us_80180C64;
    if (value < 0x18) {
        value = 0;
    }
    *data = value;
    *tileRects = value;
    *surfaceLines = value;
    data += 4;
    tileRects += 4;
    surfaceLines += 5;

    if (D_us_80180C64 < 0xC0) {
        value = 0xF0;
    } else {
        value = 0x1A8 - D_us_80180C64;
    }
    *data = value;
    data += 4;
    *data = value;
    if (value > 0xE8) {
        value = 0xE8;
    }
    *surfaceLines = value;
    surfaceLines += 5;
    *surfaceLines = value;
    value++;
    *tileRects = value;
    tileRects += 4;
    *tileRects = value;
}

void func_us_801A07CC(Entity* self) {
    Entity* player;

    player = &PLAYER;
    D_us_801B2870 = 0;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        if (D_us_80180C64) {
            if (g_CastleFlags[SCYLLA_DEFEATED]) {
                self->step = 5;
            } else {
                self->step = 3;
            }
        } else if (g_CastleFlags[SCYLLA_DEFEATED]) {
            self->step = 6;
        }
        break;

    case 1:
        if (player->posX.i.hi >= 0x38) {
            D_us_80180C66 |= 1;
            self->ext.timer.t = 0x10;
            self->step++;
        }
        break;

    case 2:
        if (!--self->ext.timer.t) {
            self->step++;
        }
        break;

    case 3:
        if (self->ext.timer.t) {
            --self->ext.timer.t;
        } else {
            self->ext.timer.t = 3;
            if (D_us_80180C64 < 0xD0) {
                D_us_80180C64++;
                D_us_801B2870 = -1;
            } else {
                self->step++;
            }
        }
        func_us_801A071C();
        break;

    case 4:
        if (g_CastleFlags[SCYLLA_DEFEATED]) {
            D_us_80180C66 ^= 1;
            self->step++;
        }
        break;

    case 5:
        if (self->ext.timer.t) {
            --self->ext.timer.t;
        } else {
            self->ext.timer.t = 1;
            if (D_us_80180C64 > 0) {
                D_us_80180C64--;
                D_us_801B2870 = 1;
            } else {
                self->step++;
            }
        }
        func_us_801A071C();
        break;

    case 6:
        break;
    }
}

u16 func_us_801A09DC(s16 index, s16 x, s16 y, s16* out) {
    s16* data;
    s16 value;

    data = &D_us_80180C68[index * 4];
    x -= *data++;
    if (x < 0) {
        return 0;
    }
    *out++ = x;
    value = *data++ - x;
    if (value <= 0) {
        return 0;
    }
    *out = value;
    value = *data++;
    if (value > y) {
        return 0;
    }
    if (y >= *data++) {
        return 0;
    }
    return y + 0x8000 - value;
}

void func_us_801A0A80(Entity* self) {
    s16 sp34[2];
    s16 posX, posY;
    u16 sp3C, sp3A;
    Entity* tempEntity;
    s16 var_s1;
    s16 var_s3;
    s16 i;
    u16 sp28;
    u32 var_s7;
    s32 status;
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;

    posX = player->posX.i.hi + tilemap->scrollX.i.hi;
    status = g_Player.status;
    if (status & (PLAYER_STATUS_CROUCH | PLAYER_STATUS_TRANSFORM)) {
        if (status & PLAYER_STATUS_CROUCH) {
            sp3C = 0x14;
            sp3A = 0x19;
            if (status & PLAYER_STATUS_WOLF_FORM) {
                sp3C = 0xA;
            }
        } else if (
            status & (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) {
            sp3C = 0xC;
            sp3A = 5;
        } else if (status & PLAYER_STATUS_WOLF_FORM) {
            sp3C = 0x14;
            sp3A = 0x19;
        }
    } else {
        sp3C = 0x28;
        sp3A = 0x19;
    }
    posY = sp3A + (player->posY.i.hi + tilemap->scrollY.i.hi);
    var_s3 = var_s1 = self->params;
    var_s3 &= 0xFF;
    var_s1 = var_s1 >> 8;
    for (i = 0; i < var_s1; i++, var_s3++) {
        sp28 = func_us_801A09DC(var_s3, posX, posY, sp34);
        if (sp28) {
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
                    var_s1 = D_us_801B2874;
                    if (var_s1 && (var_s1 & 0x7FFF) < 17) {
                        if (self->ext.aluwater.unk8C < 14) {
                            var_s7 = (14 - self->ext.aluwater.unk8C) << 11;
                        } else if (self->ext.aluwater.unk8E < 14) {
                            var_s7 = (self->ext.aluwater.unk8E + 14) << 11;
                        } else {
                            var_s7 = 0;
                        }
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(
                                E_ID(UNK_2F), player, tempEntity);
                            tempEntity->posX.i.hi = self->ext.aluwater.unk80 -
                                                    tilemap->scrollX.i.hi;
                            tempEntity->posY.i.hi = self->ext.aluwater.unk82 -
                                                    (D_us_801B2874 & 0x7FFF) -
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
            } else if (sp28 && (var_s3 < 9) && !D_us_801B2874) {
                if (sp34[0] < 14) {
                    var_s7 = (14 - sp34[0]) << 11;
                } else if (sp34[1] < 14) {
                    var_s7 = (sp34[1] + 14) << 11;
                } else {
                    var_s7 = 0;
                }
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_2F), player, tempEntity);
                    if (player->velocityY > FIX(4)) {
                        tempEntity->params = var_s7 + 1;
                    } else {
                        tempEntity->params = var_s7 + 2;
                    }
                    tempEntity->params = var_s7;
                    tempEntity->posY.i.hi += sp3A - var_s3;
                    tempEntity->zPriority = player->zPriority;
                }
            }
        } else if ((status & PLAYER_STATUS_MIST_FORM) == 0) {
            if (sp28 && !self->ext.aluwater.unk7E) {
                if (posX != self->ext.aluwater.unk80) {
                    if (var_s3 <= sp3C && sp34[0] >= 6 && sp34[1] >= 6) {
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(
                                E_ID(UNK_30), player, tempEntity);
                            tempEntity->posY.i.hi += sp3A - var_s3;
                            if (player->velocityX != 0) {
                                tempEntity->params = (sp3C - var_s3) >> 3;
                                if (tempEntity->params == 5) {
                                    tempEntity->params = 4;
                                }
                            } else {
                                tempEntity->params = 0;
                            }
                            tempEntity->ext.aluwater.unk8A = 0;
                            tempEntity->zPriority = player->zPriority;
                            self->ext.aluwater.unk7E = 8;
                        }
                    }
                }
            }
        }
        if (self->ext.aluwater.unk7E) {
            self->ext.aluwater.unk7E--;
        }
        g_unkGraphicsStruct.D_80097448 = var_s3;
        if (status & (PLAYER_STATUS_CROUCH | PLAYER_STATUS_TRANSFORM)) {
            if (status & PLAYER_STATUS_CROUCH) {
                if (status & PLAYER_STATUS_WOLF_FORM) {
                    if (var_s3 > 4) {
                        g_unkGraphicsStruct.D_8009744C = var_s3 - 4;
                    } else {
                        g_unkGraphicsStruct.D_8009744C = 0;
                    }
                    if (var_s3 > 12) {
                        g_unkGraphicsStruct.D_80097450 = var_s3 - 12;
                    } else {
                        g_unkGraphicsStruct.D_80097450 = 0;
                    }
                } else {
                    if (var_s3 > 8) {
                        g_unkGraphicsStruct.D_8009744C = var_s3 - 8;
                    } else {
                        g_unkGraphicsStruct.D_8009744C = 0;
                    }
                    if (var_s3 > 0x18) {
                        g_unkGraphicsStruct.D_80097450 = var_s3 - 0x18;
                    } else {
                        g_unkGraphicsStruct.D_80097450 = 0;
                    }
                }
            } else if (
                status & (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) {
                if (var_s3 > 6) {
                    g_unkGraphicsStruct.D_8009744C = var_s3 - 6;
                } else {
                    g_unkGraphicsStruct.D_8009744C = 0;
                }
                if (var_s3 > 0x10) {
                    g_unkGraphicsStruct.D_80097450 = var_s3 - 0x10;
                } else {
                    g_unkGraphicsStruct.D_80097450 = 0;
                }
            } else if (status & PLAYER_STATUS_WOLF_FORM) {
                if (var_s3 > 8) {
                    g_unkGraphicsStruct.D_8009744C = var_s3 - 8;
                } else {
                    g_unkGraphicsStruct.D_8009744C = 0;
                }
                if (var_s3 > 0x18) {
                    g_unkGraphicsStruct.D_80097450 = var_s3 - 0x18;
                } else {
                    g_unkGraphicsStruct.D_80097450 = 0;
                }
            }
        } else {
            if (var_s3 > 0x10) {
                g_unkGraphicsStruct.D_8009744C = var_s3 - 0x10;
            } else {
                g_unkGraphicsStruct.D_8009744C = 0;
            }
            if (var_s3 > 0x30) {
                g_unkGraphicsStruct.D_80097450 = var_s3 - 0x30;
            } else {
                g_unkGraphicsStruct.D_80097450 = 0;
            }
        }
        FntPrint("mizu %x\n", var_s3);
    } else {
        InitializeEntity(g_EInitSpawner);
    }
    D_us_801B2874 = sp28;
    self->ext.aluwater.unk80 = posX;
    self->ext.aluwater.unk82 = posY;
    self->ext.aluwater.unk8C = sp34[0];
    self->ext.aluwater.unk8E = sp34[1];
}

s32 g_SplashYMovement[] = {FIX(-6.5), FIX(9.0 / 32), FIX(-5.5), FIX(17.0 / 64),
                           FIX(-4.5), FIX(0.25),     FIX(-3.5), FIX(15.0 / 64)};
s16 g_SurfacingYTbl[] = {0, 2, 4, 6, 8, 10};
static s16 water_slow_zones[] = {
    0x260, 0x020, 0x0D0, 0x080, 0x470, 0x020,
    0x0D0, 0x080, 0x0C0, 0x02C, 0x0E0, 0x500,
};
s16 D_us_80180CC4[] = {0x01E0, 0x0060, 0x0061, 0x006E, 0x01FF, 0x01E0};
u8 D_us_80180CD0[] = {0, 0, 0, 1, 1, 0, 0, 0};
u16 D_us_80180CD8[] = {
    0x0373, 0x0000, 0x0000, 0x0000, 0x075E, 0x0001, 0x0001, 0x0001,
    0x0375, 0x0000, 0x0000, 0x0000, 0x0765, 0x0001, 0x0001, 0x0001,
    0x03F2, 0x0000, 0x0000, 0x0000, 0x075C, 0x0001, 0x0001, 0x0001,
    0x072D, 0x0000, 0x0000, 0x0000, 0x075D, 0x0001, 0x0001, 0x0001,
    0x0375, 0x0000, 0x0000, 0x0969, 0x0762, 0x0001, 0x0001, 0x0764,
    0x0933, 0x0000, 0x0000, 0x0951, 0x0761, 0x0001, 0x0001, 0x0763};
static s16 g_splashAspects[] = {0, 1, 2, 4, -1, -2, -4, 0};

void func_us_801A1120(Entity* self) {
    s32 primIndex;
    Tilemap* tilemap = &g_Tilemap;
    u16 params;
    u16 index1;
    u16 width;
    s16 aspect;
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
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
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
                if (width) {
                    if (width > 14) {
                        prim->u1 = prim->u3 = prim->u0 + (width << 5) / 28;
                        prim->x1 = prim->x3 = prim->x0 + width;
                    } else {
                        prim->u0 = prim->u2 += (width << 5) / 28;
                        prim->x0 = prim->x2 += width;
                    }
                }
            }
            PGREY(prim, 0) = PGREY(prim, 1) = 0xFF;
            PGREY(prim, 2) = PGREY(prim, 3) = 0x80;
            prim->clut = PAL_CC_MAGIC_HUD_EFFECT;
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
        g_api.PlaySfxVolPan(SFX_WATER_SPLASH_JUMP, 0x7F, aspect);

        self->velocityY = g_SplashYMovement[params * 2];
        self->ext.waterEffects.accelY = g_SplashYMovement[params * 2 + 1];

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromCurrentEntity(E_ID(WATER_DROP), newEntity);
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
        prim->y2 = prim->y3 += D_us_801B2870;
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

void func_us_801A16E4(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Primitive* prim;
    u16 params;
    s16 aspect;
    s32 primIndex;
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
        aspect = (self->posX.i.hi - 120) >> 4;
        if (aspect < -8) {
            aspect = -8;
        }
        if (aspect > 8) {
            aspect = 8;
        }
        params = self->params;
        if (!(params & 0x8000)) {
            g_api.PlaySfxVolPan(SFX_WATER_SPLASH_MOVE, 0x7F, aspect);
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
            PGREY(prim, 0) = PGREY(prim, 1) = 255;
            PGREY(prim, 2) = PGREY(prim, 3) = 128;
            prim->clut = PAL_CC_MAGIC_HUD_EFFECT;
            prim->tpage = 0x1A;
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            if (i != 0) {
                prim->clut = PAL_CC_STONE_EFFECT;
                prim->priority = self->zPriority + 4;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }
        self->ext.waterEffects.topY.i.hi =
            g_SurfacingYTbl[self->params & 0xFF] + 12 + (rand() & 1);
        break;

    case 1:
        self->ext.waterEffects.topY.val -= FIX(0.25);
        break;
    }

    self->posY.i.hi += D_us_801B2870;
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

#include "../../st/water_slow_zone.h"

static void func_us_801B5004(Tilemap* map, s32 arg1) {
    Tilemap* tmap;
    s16 tilePos;
    u16* tileData;
    s32 i;

    tmap = &g_Tilemap;
    tilePos = D_us_80180CC4[arg1 >> 1];
    tileData = &D_us_80180CD8[arg1 << 2];

    for (i = 0; i < 4; i++) {
        tmap->fg[tilePos] = *tileData++;
        tilePos += tmap->hSize << 4;
    }
}

void func_us_801A1BE8(Entity* self) {
    u16 params;
    u16 flag;
    s16 y;

    params = self->params;
    flag = D_us_80180C66 & (1 << params);
    params <<= 1;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x25;
        self->facingLeft = D_us_80180CD0[params >> 1];
        self->zPriority = 0x9E;
        if (flag) {
            func_us_801B5004((Tilemap*)self, params + 1);
            self->step = 4;
            break;
        }
        func_us_801B5004((Tilemap*)self, params);
        self->posY.i.hi -= 0x40;
        break;

    case 1:
        if (flag) {
            self->step++;
            self->velocityY = FIX(4);
        }
        break;

    case 2:
        if (self->facingLeft) {
            self->posX.i.hi += 8;
        } else {
            self->posX.i.hi -= 8;
        }
        GetPlayerCollisionWith(self, 0x10, 0x20, 0xB);
        if (self->facingLeft) {
            self->posX.i.hi -= 8;
        } else {
            self->posX.i.hi += 8;
        }
        MoveEntity();
        y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (y < 0x80) {
            break;
        }
        g_api.PlaySfxVolPan(SFX_EXPLODE_B, 0x7F, -6);
        func_us_801B5004((Tilemap*)self, params + 1);
        self->velocityY = FIX(-1);
        self->step++;
        break;

    case 3:
        self->velocityY += FIX(0.125);
        MoveEntity();
        y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (y >= 0x80) {
            self->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;

    case 4:
        if (!flag) {
            self->step++;
            self->velocityY = FIX(-1);
            func_us_801B5004((Tilemap*)self, params);
        }
        break;

    case 5:
        if (self->facingLeft) {
            self->posX.i.hi += 8;
        } else {
            self->posX.i.hi -= 8;
        }
        GetPlayerCollisionWith(self, 0x10, 0x20, 0xB);
        if (self->facingLeft) {
            self->posX.i.hi -= 8;
        } else {
            self->posX.i.hi += 8;
        }
        MoveEntity();
        y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (y < 0x41) {
            self->step++;
        }
        break;

    case 6:
        break;
    }
}

#include "../../st/entity_splash_water.h"

#include "../../st/entity_water_drop.h"
