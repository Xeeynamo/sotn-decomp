// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"
#include <scratchpad.h>

static u8 anim_idle[] = {0x0A, 0x01, 0x0A, 0x02, 0x0A, 0x03, 0x0A, 0x04,
                         0x0A, 0x05, 0x0A, 0x04, 0x0A, 0x03, 0x00, 0x00};
static u8 anim_crystal[] = {0x20, 0x01, 0x08, 0x06, 0x08, 0x07, 0x08, 0x08,
                            0x18, 0x09, 0x06, 0x0A, 0x04, 0x0E, 0xFF, 0x00};
// chill attack anim
static u8 anim_ice_wind[] = {0x06, 0x0F, 0x06, 0x10, 0x06, 0x11, 0x00, 0x00};
// end chill anim
static u8 anim_ice_wind_end[] = {
    0x08, 0x0E, 0x08, 0x0B, 0x08, 0x0C, 0x08, 0x0D, 0x08, 0x0C,
    0x08, 0x0B, 0x08, 0x0A, 0x08, 0x02, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_rotate[] = {
    0x36, 0x12, 0x08, 0x13, 0x08, 0x14, 0x08, 0x15, 0x36, 0x16,
    0x08, 0x15, 0x08, 0x14, 0x08, 0x13, 0x00, 0x00, 0x00, 0x00};

static s32 posX_jitter[] = {0x0001FD80, 0x0001F600, 0x0001E9C0, 0x0001D8C0,
                            0x0001C320, 0x0001A940, 0x00018B40, 0x00016980};
static s32 posY_jitter[] = {0x00003220, 0x000063E0, 0x000094A0, 0x0000C3E0,
                            0x0000F160, 0x00011C80, 0x000144C0, 0x00016A00};
static u8 pos_jitter_idx[] = {5, 3, 4, 1, 6, 3, 2, 4, 0, 6, 3, 5, 7, 1, 4, 2};
static s16 posY_offsets[] = {-8, -8, -8, -4, 8, 8, 8, 4};
static s16 posX_offsets[] = {-8, 0, 8, 4, -8, 0, 8, -4};
// SVECTOR parts { vx, vy, vz }
static s16 D_us_801828B0[][3] = {
    {0, -36, 0},     {20, -16, 0},  {-20, -16, 0},  {20, 16, 0},
    {-20, 16, 0},    {0, 36, 0},    {0, -20, -16},  {10, -10, -16},
    {-10, -10, -16}, {10, 10, -16}, {-10, 10, -16}, {0, 20, -16},
    {0, -20, 16},    {10, -10, 16}, {-10, -10, 16}, {10, 10, 16},
    {-10, 10, 16},   {0, 20, 16}};

static u8 D_us_8018291C[] = {
    0x02, 0x00, 0x08, 0x06, 0x00, 0x01, 0x06, 0x07, 0x02, 0x08, 0x04,
    0x0A, 0x07, 0x01, 0x09, 0x03, 0x04, 0x0A, 0x05, 0x0B, 0x05, 0x0B,
    0x03, 0x09, 0x08, 0x06, 0x0A, 0x07, 0x0A, 0x07, 0x0B, 0x09, 0x02,
    0x00, 0x0E, 0x0C, 0x00, 0x01, 0x0C, 0x0D, 0x02, 0x0E, 0x04, 0x10,
    0x0D, 0x01, 0x0F, 0x03, 0x04, 0x10, 0x05, 0x11, 0x05, 0x11, 0x03,
    0x0F, 0x0E, 0x0C, 0x10, 0x0D, 0x10, 0x0D, 0x11, 0x0F};
// SVECTOR parts { vx, vy, vz }
static s16 D_us_8018295C[][3] = {
    {2048, 2048, 4096},   {-2048, 2048, 4096},   {3072, 0, 4096},
    {-3072, 0, 4096},     {2048, -2048, 4096},   {-2048, -2048, 4096},
    {0, 0, 4096},         {0, 0, 4096},          {2048, 2048, -4096},
    {-2048, 2048, -4096}, {3072, 0, -4096},      {-3072, 0, -4096},
    {2048, -2048, -4096}, {-2048, -2048, -4096}, {0, 0, -4096},
    {0, 0, -4096}};

static s16 unused[] = {
    16448,  16512,  -32704, 24672, 12448, 24624, 4112, 12352, 24624, 24672,
    -32608, -16256, 0,      -12,   12,    -12,   12,   -12,   12,    0,
    0,      -26,    0,      -12,   -26,   -26,   -12,  -12,   -12,   -26,
    0,      0,      0,      0,     12,    26,    12,   12,    26,    26,
    0,      0,      25,     12,    -16,   -4,    -4,   20,    -4,    20,
    20,     32,     -32,    -6,    -16,   -4,    -6,   22,    -4,    20,
    20,     22,     32,     48,    32,    48,    20,   22,    -4,    20,
    -6,     22,     -32,    -16,   -6,    -4};

static s16 icicle_posX_offsets[] = {-32, 16, 32, -16};
static s16 icicle_posY_offsets[] = {0, -24, 0, -24};

// SVECTOR parts { vx, vy, vz }
static s16 D_us_80182A64[][3] = {
    {0, -24, 0}, {-11, -3, 0}, {0, -3, -11}, {11, -3, 0}, {0, -3, 11},
    {-8, 8, -8}, {8, 8, -8},   {8, 8, 8},    {-8, 8, 8},  {0, 56, 0}};
static u8 D_us_80182AA0[] = {1, 0, 5, 2, 2, 0, 6, 3, 3, 0, 7, 4, 4, 0, 8, 1,
                             5, 2, 9, 6, 6, 3, 9, 7, 7, 4, 9, 8, 8, 1, 9, 5};

// SVECTOR parts { vx, vy, vz }
static s16 D_us_80182AC0[][3] = {
    {2048, 1024, 2048},  {-2048, 1024, 2048}, {-2048, 1024, -2048},
    {2048, 1024, -2048}, {0, -768, 3072},     {-3072, -768, 0},
    {0, -768, -3072},    {3072, -768, 0}};

static s16 ice_shard_angles[] = {
    -512, 128, 800, -704, 1856, 1088, -1312, -1792};
static s16 ice_shard_speeds[] = {512, 320, 416, 224, 288, 640, 384, 256};

#define offsetof(st, m) (size_t)((size_t) & (((st*)0)->m)) // __builtin_offsetof

static void func_us_801D9560(FrozenShadePrim* prim) {
    s16 dx, dy;

    Tilemap* tilemap = &g_Tilemap;
    dx = prim->posX.i.hi - tilemap->scrollX.i.hi;
    dy = prim->posY.i.hi - tilemap->scrollY.i.hi;

    prim->x0 = prim->x3 = dx - 0;
    prim->x1 = dx + (prim->u3 / 16 + 2);
    prim->x2 = dx - (prim->u3 / 16 + 2);

    prim->y1 = prim->y2 = dy - 0;
    prim->y0 = dy - (prim->u3 / 4 + 2);
    prim->y3 = dy + (prim->u3 / 4 + 2);
}

static void func_us_801D95EC(Entity* self) {
    Entity* player;
    s16 posY;
    s16 posX;
    s16 angle;

    player = &PLAYER;

    if (!(self->ext.frozenShade.unk86 & 0x1F)) {
        angle = Random() & 7;
        posY = self->ext.frozenShade.unkA2 - self->posY.i.hi +
               posY_offsets[angle] - g_Tilemap.scrollY.i.hi;
        posX = self->ext.frozenShade.unkA0 - self->posX.i.hi +
               posX_offsets[angle] - g_Tilemap.scrollX.i.hi;
        self->ext.frozenShade.unk88 = (s16)ratan2(posY, posX);
    }
    self->ext.frozenShade.unk86++;
    angle = self->ext.frozenShade.unk7E = GetNormalizedAngle(
        0x40, self->ext.frozenShade.unk7E, self->ext.frozenShade.unk88);
    self->posX.val += (rcos(angle) * 128) / 16;
    self->posY.val += (rsin(angle) * 128) / 16;
}

void EntityFrozenShade(Entity* self) {
    u8 u0, u1;
    s16 var_s4;
    s16 var_s0_3;
    s32 primIndex;
    Tilemap* tilemap;
    s16* point;
    SVECTOR* points[4];
    Point16* sxy[4];
    u8* iptr;
    CVECTOR* primaryColor;
    CVECTOR* color;
    VECTOR tempVector;
    MATRIX* mat;
    long* p;
    long* flag;
    Entity* tempEntity;
    FrozenShadePrim* prim;
    Primitive* prim2;
    s16 tempVar;
    s16 i, j;

    tilemap = &g_Tilemap;
    self->ext.frozenShade.unk9E++;
    if (self->step && !(self->flags & FLAG_DEAD)) {
        self->ext.frozenShade.unk7C++;
        if (self->ext.frozenShade.unk7C & 0x40) {
            self->opacity = (u8)(self->ext.frozenShade.unk7C & 0x3F) + 0x40;
        } else {
            self->opacity = 0x80 - (u8)(self->ext.frozenShade.unk7C & 0x3F);
        }
    }
    tempEntity = &PLAYER;
    if ((self->flags & FLAG_DEAD) && (self->step != 4)) {
        SetStep(4);
    }
    if (self->ext.frozenShade.unk82) {
        prim = (FrozenShadePrim*)&g_PrimBuf[self->primIndex];
        j = 0;
        if (self->ext.frozenShade.unk82 != 2) {
            if ((self->ext.frozenShade.unkA4 & 0x1F) == 0) {
                PlaySfxPositional(SFX_GLASS_SHARDS);
            }
            self->ext.frozenShade.unkA4++;
        }
        while (prim != NULL) {
            if (!prim->v2) {
                if (!prim->p3) {
                    if (self->facingLeft) {
                        prim->posX.val += posX_jitter[prim->u2];
                    } else {
                        prim->posX.val -= posX_jitter[prim->u2];
                    }
                    prim->posY.val +=
                        posY_jitter[prim->u2] - (prim->u3++ << 10);
                    func_us_801D9560(prim);
                    PRED(prim)--;
                    PGRN(prim)--;
                    PBLU(prim) -= 3;
                    if (prim->p2) {
                        tempEntity = &g_Entities[self->ext.frozenShade
                                                     .unkA8[prim->p2 - 1]];
                        if (tempEntity->hitFlags) {
                            for (i = 0; i < 11; i++) {
                                tempEntity->unk6D[i] = 0;
                            }
                            prim->drawMode = DRAW_HIDE;
                            prim->v2 = 0x40 - prim->u3;
                            prim = prim->next;
                            continue;
                        }
                    }
                    prim->p2 = 0;
                    if (prim->p1 == (self->ext.frozenShade.unk9E & 3) &&
                        prim->u3 < 0x30) {
                        tempEntity =
                            &g_Entities[self->ext.frozenShade.unkA8[j]];
                        tempEntity->posX.i.hi =
                            prim->posX.i.hi - tilemap->scrollX.i.hi;
                        tempEntity->posY.i.hi =
                            prim->posY.i.hi - tilemap->scrollY.i.hi;
                        tempEntity->hitboxWidth = prim->u3 / 8 + 1;
                        tempEntity->hitboxHeight = prim->u3 / 5 + 1;
                        j++;
                        prim->p2 = j;
                    }
                    if (prim->u3 == 0x40) {
                        prim->drawMode = DRAW_HIDE;
                        prim->v2 = 1;
                    }
                }
            } else if (prim->v2 != 0xFF) {
                if ((self->ext.frozenShade.unk82 == 2 ||
                     (self->flags & FLAG_DEAD)) &&
                    !prim->p3) {
                    prim->v2 = 0xFF;
                    if (self->ext.frozenShade.unk81 >= 0x1F) {
                        self->ext.frozenShade.unk82 = 0;
                        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                                       FLAG_UNK_20000000;
                    } else {
                        self->ext.frozenShade.unk81++;
                    }
                    prim = prim->next;
                    continue;
                }
                prim->v2--;
                if (!prim->v2) {
                    prim->p1 = self->ext.frozenShade.unk83;
                    prim->u2 = pos_jitter_idx[prim->p1];
                    prim->p1 &= 3;
                    prim->u3 = 0;
                    prim->p2 = 0;
                    prim->r0 = 0x40;
                    prim->g0 = 0x40;
                    prim->b0 = 0xC0;
                    prim->r1 = 0x40;
                    prim->g1 = 0x40;
                    prim->b1 = 0xC0;
                    prim->r2 = 0x40;
                    prim->g2 = 0x40;
                    prim->b2 = 0xC0;
                    prim->r3 = 0x40;
                    prim->g3 = 0x40;
                    prim->b3 = 0xC0;
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim->priority = g_unkGraphicsStruct.g_zEntityCenter - 0xB;
                    prim->p3 = 0;
                    prim->posY.val =
                        (self->posY.val + tilemap->scrollY.val) - FIX(7);
                    if (self->facingLeft) {
                        prim->posX.val =
                            (self->posX.val + tilemap->scrollX.val) + FIX(14);
                    } else {
                        prim->posX.val =
                            (self->posX.val + tilemap->scrollX.val) - FIX(14);
                    }
                    func_us_801D9560(prim);
                    self->ext.frozenShade.unk83++;
                    self->ext.frozenShade.unk83 &= 0xF;
                }
            }
            prim = prim->next;
        }
        for (i = j; i < 8; i++) {
            tempEntity = &g_Entities[self->ext.frozenShade.unkA8[i]];
            if (self->ext.frozenShade.unk82) {
                tempEntity->hitboxWidth = 0;
            } else {
                DestroyEntity(tempEntity);
            }
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFrozenShade);
        self->opacity = 0x40;
        self->palette += self->params;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_OPACITY;
        self->ext.frozenShade.unk7C = 0;
        if (self->posX.val < tempEntity->posX.val) {
            self->facingLeft = true;
            self->ext.frozenShade.unk7E = 0;
        } else {
            self->ext.frozenShade.unk7E = 0x800;
        }
        self->ext.frozenShade.unk8C = self->posY.val;
        self->ext.frozenShade.unkA0 = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        self->ext.frozenShade.unkA2 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        self->ext.frozenShade.unk84 = 0x10;
        self->ext.frozenShade.unk80 = 0;
        self->velocityY = FIX(0.25);
        primIndex = g_api.AllocPrimitives(PRIM_G4, 0x20);
        if (primIndex != -1) {
            prim = (FrozenShadePrim*)&g_PrimBuf[primIndex];
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            while (prim != NULL) {
                prim->p3 = 0;
                prim->v2 = 0xFF;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 1:
        AnimateEntity(anim_idle, self);
        tempVar = GetDistanceToPlayerX();
        var_s4 = tempEntity->posX.i.hi - self->posX.i.hi;
        if (tempVar < 0x10) {
            SetStep(2);
        } else if ((var_s4 < 0 && self->facingLeft) ||
                   (var_s4 >= 0 && !self->facingLeft)) {
            SetStep(2);
        }
        if ((self->posX.i.hi & 0x100) == 0 && !--self->ext.frozenShade.unk84) {
            if (tempVar < 0x60 && GetDistanceToPlayerY() < 0x40 && rand() & 3) {
                j = 0xA0;
                var_s0_3 = 0;
                for (tempEntity = &g_Entities[160];
                     tempEntity < &g_Entities[192]; tempEntity++) {
                    if (!tempEntity->entityId) {
                        DestroyEntity(tempEntity);
                        self->ext.frozenShade.unkA8[var_s0_3++] = j;
                        if (var_s0_3 >= 8) {
                            break;
                        }
                    }
                    j++;
                }
                if (var_s0_3 == 8) {
                    for (i = 0; i < 8; i++) {
                        tempEntity =
                            &g_Entities[self->ext.frozenShade.unkA8[i]];
                        CreateEntityFromCurrentEntity(
                            E_FROZEN_SHADE_CRYSTAL, tempEntity);
                        tempEntity->hitboxWidth = 0;
                    }
                    SetStep(3);
                    PlaySfxPositional(SFX_UI_SUBWEAPON_TINK);
                    self->ext.frozenShade.unk98 = 0;
                    self->ext.frozenShade.unk8A = 0;
                } else {
                    self->step = 5;
                    self->ext.frozenShade.unk8A = 0;
                }
            } else {
                self->step = 5;
                self->ext.frozenShade.unk8A = 0;
            }
        }
        func_us_801D95EC(self);
        break;

    case 2:
        // Player has switched sides, rotate to face
        AnimateEntity(anim_rotate, self);
        tempVar = GetDistanceToPlayerX();
        if (tempVar > 0x10) {
            tempVar = self->posX.i.hi - tempEntity->posX.i.hi;
            if (self->facingLeft) {
                if (tempVar > 0) {
                    if (self->pose == 5) {
                        SetStep(1);
                        self->facingLeft = false;
                        AnimateEntity(anim_idle, self);
                    }
                } else {
                    if (self->pose == 1) {
                        SetStep(1);
                        AnimateEntity(anim_idle, self);
                    }
                }
            } else if (tempVar < 0) {
                if (self->pose == 5) {
                    SetStep(1);
                    self->facingLeft = true;
                    AnimateEntity(anim_idle, self);
                }
            } else {
                if (self->pose == 1) {
                    SetStep(1);
                    AnimateEntity(anim_idle, self);
                }
            }
        }
        func_us_801D95EC(self);
        break;

    case 3:
        // Enter crystal state then begin wind attack
        switch (self->step_s) {
        case 0:
            if (self->velocityY < 0) {
                self->velocityY += 0x200;
            } else if (self->velocityY > 0) {
                self->velocityY -= 0x200;
            }
            tempVar = AnimateEntity(anim_crystal, self);
            j = self->ext.frozenShade.unk8A++;
            self->ext.frozenShade.unk98 += 0x20;
            SetGeomScreen(0x100);
            if (self->facingLeft) {
                var_s4 = self->posX.i.hi + 1;
            } else {
                var_s4 = self->posX.i.hi - 1;
            }
            SetGeomOffset(var_s4, self->posY.i.hi + 0xC);
            points[0] = (SVECTOR*)SP(offsetof(NO4_SCRATCHPAD, points[0]));
            points[1] = (SVECTOR*)SP(offsetof(NO4_SCRATCHPAD, points[1]));
            points[2] = (SVECTOR*)SP(offsetof(NO4_SCRATCHPAD, points[2]));
            points[3] = (SVECTOR*)SP(offsetof(NO4_SCRATCHPAD, points[3]));
            sxy[0] = (Point16*)SP(offsetof(NO4_SCRATCHPAD, sxy[0]));
            sxy[1] = (Point16*)SP(offsetof(NO4_SCRATCHPAD, sxy[1]));
            sxy[2] = (Point16*)SP(offsetof(NO4_SCRATCHPAD, sxy[2]));
            sxy[3] = (Point16*)SP(offsetof(NO4_SCRATCHPAD, sxy[3]));
            p = (long*)SP(offsetof(NO4_SCRATCHPAD, p));
            flag = (long*)SP(offsetof(NO4_SCRATCHPAD, flag));
            primaryColor = (CVECTOR*)SP(offsetof(NO4_SCRATCHPAD, primaryColor));
            color = (CVECTOR*)SP(offsetof(NO4_SCRATCHPAD, color));
            mat = (MATRIX*)SP(offsetof(NO4_SCRATCHPAD, mat));
            if (j > 0x10) {
                var_s4 = 0x10;
            } else {
                var_s4 = j;
            }
            primaryColor->r = var_s4 * 2;
            primaryColor->g = var_s4 * 3;
            primaryColor->b = var_s4 * 4;
            if (j < 0x30) {
                var_s4 = 0x1000;
            } else if (j > 0x40) {
                var_s4 = 0;
            } else {
                var_s4 = (0x40 - j) * 0x100;
            }
            mat->m[0][0] = mat->m[1][1] = mat->m[2][2] = 0x1000;
            mat->m[0][1] = mat->m[0][2] = mat->m[1][0] = mat->m[1][2] =
                mat->m[2][0] = mat->m[2][1] = 0;
            mat = RotMatrixY(self->ext.frozenShade.unk98, mat);
            SetLightMatrix(mat);
            tempVector.vx = tempVector.vy = tempVector.vz = var_s4;
            ScaleMatrix(mat, &tempVector);
            SetRotMatrix(mat);
            tempVector.vx = tempVector.vy = 0;
            tempVector.vz = 0x100;
            TransMatrix(mat, &tempVector);
            SetTransMatrix(mat);
            mat->m[0][0] = mat->m[1][0] = mat->m[2][0] = -0x400;
            mat->m[0][1] = mat->m[1][1] = mat->m[2][1] = 0x1000;
            mat->m[0][2] = mat->m[1][2] = mat->m[2][2] = 0x1800;
            SetColorMatrix(mat);
            SetBackColor(0x60, 0x60, 0x60);
            var_s4 = 0;
            iptr = D_us_8018291C;
            point = D_us_8018295C[0];
            prim = (FrozenShadePrim*)&g_PrimBuf[self->primIndex];
            while (prim != NULL) {
                for (i = 0; i < 4; i++) {
                    s16* temp = D_us_801828B0[*iptr];
                    points[i]->vx = *temp++;
                    points[i]->vy = *temp++;
                    points[i]->vz = *temp;
                    iptr++;
                }
                primIndex = RotAverage4(
                    points[0], points[1], points[2], points[3], (long*)sxy[0],
                    (long*)sxy[1], (long*)sxy[2], (long*)sxy[3], p, flag);
                points[0]->vx = *point++;
                points[0]->vy = *point++;
                points[0]->vz = *point++;
                NormalColorCol(points[0], primaryColor, color);
                if ((j == 0x24 || j == 0x25) && var_s4 == 9) {
                    color->r = color->g = color->b = 0xFF;
                }
                if ((j == 0x26 || j == 0x27) &&
                    (var_s4 == 14 || var_s4 == 15)) {
                    color->r = color->g = color->b = 0xFF;
                }
                if ((j == 0x28 || j == 0x29) && var_s4 == 12) {
                    color->r = color->g = color->b = 0xFF;
                }
                prim->x0 = sxy[0]->x;
                prim->x1 = sxy[1]->x;
                prim->x2 = sxy[2]->x;
                prim->x3 = sxy[3]->x;
                prim->y0 = sxy[0]->y;
                prim->y1 = sxy[1]->y;
                prim->y2 = sxy[2]->y;
                prim->y3 = sxy[3]->y;
                PRED(prim) = color->r;
                PGRN(prim) = color->g;
                PBLU(prim) = color->b;
                if (primIndex > 0x100) {
                    prim->priority = g_unkGraphicsStruct.g_zEntityCenter - 0xD;
                } else {
                    prim->priority = g_unkGraphicsStruct.g_zEntityCenter - 0xB;
                }
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
                prim->p3 = 1;
                prim = prim->next;
                var_s4++;
                if (var_s4 == 0x10) {
                    break;
                }
            }
            if (!tempVar) {
                self->step_s++;
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.frozenShade.unk84 = 0x80;
                self->ext.frozenShade.unkA4 = 0;
                self->ext.frozenShade.unk82++;
                self->ext.frozenShade.unk83 = 0;
                self->ext.frozenShade.unk81 = 0;
                self->velocityY = 0;
                if (self->facingLeft) {
                    self->velocityX = FIX(-0.75);
                } else {
                    self->velocityX = FIX(0.75);
                }
                self->flags &=
                    ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                      FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_UNK_20000000);
                j = 1;
                prim = (FrozenShadePrim*)&g_PrimBuf[self->primIndex];
                while (prim != NULL) {
                    prim->v2 = j;
                    j += 2;
                    prim = prim->next;
                }
            }
            break;

        case 1:
            AnimateEntity(anim_ice_wind, self);
            if (self->velocityX != 0) {
                if (self->facingLeft) {
                    self->velocityX += 0x600;
                } else {
                    self->velocityX -= 0x600;
                }
            }
            if (!--self->ext.frozenShade.unk84) {
                self->step_s++;
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.frozenShade.unk82++;
            }
            MoveEntity(self);
            break;

        case 2:
            if (!AnimateEntity(anim_ice_wind_end, self)) {
                SetStep(1);
                self->ext.frozenShade.unk7E = 0xC00;
                self->ext.frozenShade.unk84 = (rand() & 0x1F) + 0x80;
            }
            break;
        }
        MoveEntity();
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 9;
            self->ext.frozenShade.unk84 = 0x10;
            g_api.PlaySfx(SFX_FROZEN_SHADE_SCREAM);
            self->step_s++;
            break;

        case 1:
            if (!self->ext.frozenShade.unk84) {
                prim2 = &g_PrimBuf[self->primIndex];
                while (prim2 != NULL) {
                    if (prim2->p3) {
                        prim2->drawMode = DRAW_HIDE;
                    }
                    prim2 = prim2->next;
                }
                prim2 = &g_PrimBuf[self->primIndex];
                tempVar = 2;
                while (prim2 != NULL) {
                    if (prim2->drawMode == DRAW_HIDE) {
                        tempVar--;
                        if (tempVar) {
                            self->ext.frozenShade.unk90 = prim2;
                        } else {
                            self->ext.frozenShade.unk94 = prim2;
                            break;
                        }
                    }
                    prim2 = prim2->next;
                }
                if (!tempVar) {
                    prim2 = self->ext.frozenShade.unk90;
                    prim2->type = 4;
                    if (self->facingLeft) {
                        tempVar = self->posX.i.hi - 9;
                        u0 = 0xB8;
                        u1 = 0xA8;
                    } else {
                        tempVar = self->posX.i.hi - 7;
                        u0 = 0xA8;
                        u1 = 0xB8;
                    }
                    prim2->x0 = prim2->x2 = tempVar;
                    prim2->x1 = prim2->x3 = tempVar + 0x10;
                    prim2->y0 = prim2->y1 = self->posY.i.hi - 0x10;
                    prim2->y2 = prim2->y3 = self->posY.i.hi + 0x20;
                    PRED(prim2) = 0x80;
                    PBLU(prim2) = 0x80;
                    PGRN(prim2) = 0x80;
                    prim2->priority = g_unkGraphicsStruct.g_zEntityCenter - 0xD;
                    prim2->drawMode =
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                    if (self->hitEffect) {
                        prim2->clut = self->hitEffect;
                    } else {
                        prim2->clut = self->palette;
                    }
                    prim2->tpage = 0x13;
                    prim2->u0 = prim2->u2 = u0;
                    prim2->u1 = prim2->u3 = u1;
                    prim2->v0 = prim2->v1 = 0x10;
                    prim2->v2 = prim2->v3 = 0x40;
                    prim2->p3 = 2;

                    prim2 = self->ext.frozenShade.unk94;
                    prim2->type = 4;
                    prim2->x0 = prim2->x2 = tempVar;
                    prim2->x1 = prim2->x3 = tempVar + 0x10;
                    prim2->y0 = prim2->y1 = self->posY.i.hi + 0x20;
                    prim2->y2 = prim2->y3 = self->posY.i.hi + 0x20;
                    PRED(prim2) = 0x80;
                    PBLU(prim2) = 0x80;
                    PGRN(prim2) = 0x80;
                    prim2->priority = g_unkGraphicsStruct.g_zEntityCenter - 0xD;
                    prim2->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                      DRAW_UNK02 | DRAW_TRANSP;
                    if (self->hitEffect) {
                        prim2->clut = self->hitEffect;
                    } else {
                        prim2->clut = self->palette;
                    }
                    prim2->tpage = 0x13;
                    prim2->u0 = prim2->u2 = u0;
                    prim2->u1 = prim2->u3 = u1;
                    prim2->v0 = prim2->v1 = 0x40;
                    prim2->v2 = prim2->v3 = 0x40;
                    prim2->p3 = 2;
                    g_api.PlaySfx(SFX_GLASS_SHARDS);
                    self->animCurFrame = 0;
                    self->step_s++;
                    break;
                }
            } else {
                self->ext.frozenShade.unk84--;
            }
            break;

        case 2:
            tempVar = self->ext.frozenShade.unk84;
            var_s4 = 0;
#ifdef VERSION_PSP
            prim2 = self->ext.frozenShade.unk90;
            if (tempVar < 0x30) {
                prim2->v2 = prim2->v3--;
                prim2->y2 = prim2->y3--;
            } else if (tempVar == 0x30) {
                prim2->drawMode = DRAW_HIDE;
            }
#else
            if (tempVar < 0x30) {
                prim2 = self->ext.frozenShade.unk90;
                prim2->v2 = prim2->v3--;
                prim2->y2 = prim2->y3--;
            } else if (tempVar == 0x30) {
                prim2 = self->ext.frozenShade.unk90;
                prim2->drawMode = DRAW_HIDE;
            }
#endif
            var_s4 = prim2->y2;
            var_s0_3 = prim2->x2;
            prim2 = self->ext.frozenShade.unk94;
            if (tempVar < 0x30) {
                prim2->v0 = prim2->v1--;
                prim2->y0 = prim2->y1--;
            } else {
                prim2->x0--;
                prim2->x1++;
            }
            if (tempVar < 0x20) {
                prim2->x2--;
                prim2->x3++;
                PGREY(prim2, 2) = PGREY(prim2, 3) -= 4;
            } else {
                prim2->v2 = prim2->v3--;
                prim2->y2 = prim2->y3--;
                PGREY(prim2, 2) = PGREY(prim2, 3) = 0;
            }
            var_s4 = 1;
            if (self->ext.frozenShade.unk84 < 0x40) {
                prim = (FrozenShadePrim*)&g_PrimBuf[self->primIndex];
                while (prim != NULL) {
                    if (prim->drawMode == DRAW_HIDE) {
                        if (!prim->p3 && (prim->v2 != 0xFF)) {
                            prim = prim->next;
                            continue;
                        }
                        prim->posX.i.hi =
                            (prim2->x2 + prim2->x0) / 2 +
                            tilemap->scrollX.i.hi +
                            Random() *
                                (prim2->x3 + prim2->x1 - prim2->x2 -
                                 prim2->x0) /
                                0x200;
                        prim->posY.i.hi =
                            (prim2->y2 + prim2->y1) / 2 + tilemap->scrollY.i.hi;
                        prim->p3 = 4;
                        prim->u2 = 0;
                        prim->u3 = 0;
                        prim->r0 = 0x40;
                        prim->g0 = 0x40;
                        prim->b0 = 0xC0;
                        prim->r1 = 0x40;
                        prim->g1 = 0x40;
                        prim->b1 = 0xC0;
                        prim->r2 = 0x40;
                        prim->g2 = 0x40;
                        prim->b2 = 0xC0;
                        prim->r3 = 0x40;
                        prim->g3 = 0x40;
                        prim->b3 = 0xC0;
                        prim->priority =
                            g_unkGraphicsStruct.g_zEntityCenter - 0xD;
                        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE |
                                         DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
                        break;
                    }
                    prim = prim->next;
                }
            }
            self->ext.frozenShade.unk84++;
            if (self->ext.frozenShade.unk84 > 0x50) {
                DestroyEntity(self);
            }
            break;
        }
        prim = (FrozenShadePrim*)&g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            if (prim->p3 == 4) {
                prim->posY.val -= FIX(2);
                func_us_801D9560(prim);
                PRED(prim) -= 2;
                PGRN(prim) -= 2;
                PBLU(prim) -= 6;
                if (prim->r0 == 0) {
                    prim->drawMode = DRAW_HIDE;
                }
            }
            prim = prim->next;
        }
        break;

    case 5:
        AnimateEntity(anim_idle, self);
        switch (self->step_s) {
        case 0:
            if (self->velocityY < 0) {
                self->velocityY += 0x200;
            } else if (self->velocityY > 0) {
                self->velocityY -= 0x200;
            }
            if (++self->ext.frozenShade.unk8A > 0x40) {
                self->ext.frozenShade.unk8A = 0;
                self->ext.frozenShade.unk9C = rand() & 3;
                PlaySfxPositional(SFX_TINK_JINGLE);
                self->step_s++;
            }
            break;

        case 1:
#ifdef VERSION_PSP
            if (!self->ext.frozenShade.unk8A++) {
#else
            if (++self->ext.frozenShade.unk8A == 1) {
#endif
                tempVar = self->ext.frozenShade.unk9C;
                for (i = 0; i < 3; i++) {
                    tempEntity =
                        AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (tempEntity != NULL) {
                        CreateEntityFromCurrentEntity(
                            E_FROZEN_SHADE_ICICLE, tempEntity);
                        tempEntity->posX.i.hi += icicle_posX_offsets[tempVar];
                        tempEntity->posY.i.hi += icicle_posY_offsets[tempVar];
                        tempEntity->params = i;
                        tempEntity->ext.frozenShadeIcicle.unk8C = self;
                        tempVar++;
                        tempVar &= 3;
                    }
                }
            }
            if (self->ext.frozenShade.unk8A >= 0x40) {
                self->ext.frozenShade.unk84 = (rand() & 0x1F) + 0x80;
                SetStep(1);
            }
            break;
        }
        MoveEntity();
        break;
    }
    if (self->animCurFrame >= 10 && self->animCurFrame < 18) {
        self->hitboxWidth = 6;
        self->hitboxHeight = 12;
        self->hitboxOffX = 4;
        self->hitboxOffY = 0;
    } else {
        self->hitboxWidth = 4;
        self->hitboxHeight = 20;
        self->hitboxOffX = 0;
        self->hitboxOffY = 12;
    }
}

void EntityFrozenShadeCrystal(struct Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitFrozenShadeCrystal);
        self->hitboxState |= 6;
    }
}

void func_us_801DB1E8(Entity* self) {
    Primitive* prim;
    u8* iptr;
    s16* ptr;
    s16* point;
    s32 i;

    SVECTOR* points[4];
    Point16* sxy[4];
    CVECTOR* primaryColor;
    CVECTOR* color;
    VECTOR tempVector;
    MATRIX* mat;
    long* p;
    long* flag;

    SetGeomScreen(0x100);
    SetGeomOffset(self->posX.i.hi, self->posY.i.hi);

    points[0] = (SVECTOR*)SP(offsetof(NO4_SCRATCHPAD, points[0]));
    points[1] = (SVECTOR*)SP(offsetof(NO4_SCRATCHPAD, points[1]));
    points[2] = (SVECTOR*)SP(offsetof(NO4_SCRATCHPAD, points[2]));
    points[3] = (SVECTOR*)SP(offsetof(NO4_SCRATCHPAD, points[3]));
    sxy[0] = (Point16*)SP(offsetof(NO4_SCRATCHPAD, sxy[0]));
    sxy[1] = (Point16*)SP(offsetof(NO4_SCRATCHPAD, sxy[1]));
    sxy[2] = (Point16*)SP(offsetof(NO4_SCRATCHPAD, sxy[2]));
    sxy[3] = (Point16*)SP(offsetof(NO4_SCRATCHPAD, sxy[3]));
    p = (long*)SP(offsetof(NO4_SCRATCHPAD, p));
    flag = (long*)SP(offsetof(NO4_SCRATCHPAD, flag));
    primaryColor = (CVECTOR*)SP(offsetof(NO4_SCRATCHPAD, primaryColor));
    color = (CVECTOR*)SP(offsetof(NO4_SCRATCHPAD, color));
    mat = (MATRIX*)SP(offsetof(NO4_SCRATCHPAD, mat));

    primaryColor->r = self->ext.frozenShadeIcicle.r;
    primaryColor->g = self->ext.frozenShadeIcicle.g;
    primaryColor->b = self->ext.frozenShadeIcicle.b;

    mat->m[0][0] = mat->m[1][1] = mat->m[2][2] = 0x1000;
    mat->m[0][1] = mat->m[0][2] = mat->m[1][0] = mat->m[1][2] = mat->m[2][0] =
        mat->m[2][1] = 0;
    mat = RotMatrixY(self->ext.frozenShade.unk7C, mat);
    mat = RotMatrixZ(self->ext.frozenShade.unk7E, mat);
    SetLightMatrix(mat);
    tempVector.vy = self->ext.frozenShadeIcicle.unk82;
    tempVector.vx = tempVector.vz = self->ext.frozenShadeIcicle.unk80;
    ScaleMatrix(mat, &tempVector);
    SetRotMatrix(mat);
    tempVector.vx = tempVector.vy = 0;
    tempVector.vz = 0x100;
    TransMatrix(mat, &tempVector);
    SetTransMatrix(mat);
    mat->m[0][0] = mat->m[1][0] = mat->m[2][0] = -0x600;
    mat->m[0][1] = mat->m[1][1] = mat->m[2][1] = 0x600;
    mat->m[0][2] = mat->m[1][2] = mat->m[2][2] = 0x1000;
    SetColorMatrix(mat);
    SetBackColor(0x60, 0x60, 0x80);
    iptr = D_us_80182AA0;
    point = D_us_80182AC0[0];
    prim = &g_PrimBuf[self->primIndex];

    while (prim != NULL) {
        for (i = 0; i < 4; iptr++, i++) {
            ptr = D_us_80182A64[*iptr];
            points[i]->vx = *ptr++;
            points[i]->vy = *ptr++;
            points[i]->vz = *ptr;
        }

        i = RotAverage4(
            points[0], points[1], points[2], points[3], (long*)sxy[0],
            (long*)sxy[1], (long*)sxy[2], (long*)sxy[3], p, flag);
        points[0]->vx = *point++;
        points[0]->vy = *point++;
        points[0]->vz = *point++;
        NormalColorCol(points[0], primaryColor, color);
        prim->x0 = sxy[0]->x;
        prim->x1 = sxy[1]->x;
        prim->x2 = sxy[2]->x;
        prim->x3 = sxy[3]->x;
        prim->y0 = sxy[0]->y;
        prim->y1 = sxy[1]->y;
        prim->y2 = sxy[2]->y;
        prim->y3 = sxy[3]->y;
        PRED(prim) = color->r;
        PGRN(prim) = color->g;
        PBLU(prim) = color->b;
        prim->priority = self->zPriority + 0x42 - i;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->p3 = 1;
        prim = prim->next;
    }
}

void EntityFrozenShadeIcicle(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s16 velocity;
    u16 i;

    if (self->hitFlags & 0x80) {
        entity = &PLAYER;
        self->ext.frozenShadeIcicle.posX = self->posX.i.hi - entity->posX.i.hi;
        self->ext.frozenShadeIcicle.posY = self->posY.i.hi - entity->posY.i.hi;
        self->ext.frozenShadeIcicle.unk84 = 0;
        self->step = 6;
    }

    entity = self->ext.frozenShadeIcicle.unk8C;
    if ((self->flags & FLAG_DEAD ||
         (entity->flags & FLAG_DEAD && self->step != 4)) &&
        self->step < 5) {
        if (self->step < 2) {
            DestroyEntity(self);
            return;
        }
        self->step = 5;
        self->ext.frozenShadeIcicle.unk84 = 0;
        self->ext.frozenShadeIcicle.angle =
            (self->ext.frozenShadeIcicle.unk7E + 0x400) & 0xFFF;
        g_api.PlaySfx(SFX_DRA_GLASS_BREAK);
    }

    entity = self->unk60;
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 8);
        if (primIndex == -1) {
            return;
        }

        entity = AllocEntity(self, &g_Entities[192]);
        if (entity == NULL) {
            return;
        }

        CreateEntityFromCurrentEntity(E_FROZEN_SHADE_ICICLE_UNK, entity);
        self->unk60 = entity;
        entity->unk60 = self;
        entity->unk5C = self;
        InitializeEntity(g_EInitFrozenShadeIcicle);
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        self->hitboxState = 0;
        prim = &g_PrimBuf[primIndex];
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        self->ext.frozenShadeIcicle.unk7C = 0;
        self->ext.frozenShadeIcicle.unk7E = 0;
        self->ext.frozenShadeIcicle.unk82 = 0x1200;
        self->ext.frozenShadeIcicle.unk80 = 0;
        self->ext.frozenShadeIcicle.unk84 = 0;
        self->ext.frozenShadeIcicle.r = 0x10;
        self->ext.frozenShadeIcicle.g = 0x10;
        self->ext.frozenShadeIcicle.b = 0x10;
        break;
    case 1:
        self->ext.frozenShadeIcicle.unk7C += 0x20;
        self->ext.frozenShadeIcicle.unk82 -= 0x80;
        self->ext.frozenShadeIcicle.unk80 += 0x78;
        self->ext.frozenShadeIcicle.r += 1;
        self->ext.frozenShadeIcicle.g += 3;
        self->ext.frozenShadeIcicle.b += 7;

        if (++self->ext.frozenShadeIcicle.unk84 > 0x10) {
            self->step++;
            self->ext.frozenShadeIcicle.unk84 =
                (((self->params) * 0x18) + 0x20);
            self->hitboxState = 0xE;
        }
        func_us_801DB1E8(self);
        break;
    case 2:
        self->ext.frozenShadeIcicle.unk7C += 0x20;
        if (!(--self->ext.frozenShadeIcicle.unk84)) {
            self->step++;
            self->ext.frozenShadeIcicle.unk84 = 0;
            self->ext.frozenShadeIcicle.angle =
                (GetAngleBetweenEntities(self, &PLAYER) - 0x400) & 0xFFF;
        }
        func_us_801DB1E8(self);
        break;
    case 3:
        self->ext.frozenShadeIcicle.unk7C += 0x20;
        i = GetNormalizedAngle(0x40, self->ext.frozenShadeIcicle.unk7E,
                               self->ext.frozenShadeIcicle.angle);
        self->ext.frozenShadeIcicle.unk7E = i;
        if (self->ext.frozenShadeIcicle.angle == i) {
            self->step++;
            PlaySfxPositional(SFX_UI_SUBWEAPON_TINK);
            self->ext.frozenShadeIcicle.unk84 = 8;
            self->ext.frozenShadeIcicle.angle += 0x400;
        }
        func_us_801DB1E8(self);
        break;
    case 4:
        self->ext.frozenShadeIcicle.unk7C += 0x20;
        if (!self->ext.frozenShadeIcicle.unk84) {
            UnkEntityFunc0(self->ext.frozenShadeIcicle.angle, 0x600);
            MoveEntity(self);
        } else {
            self->ext.frozenShadeIcicle.unk84--;
        }
        func_us_801DB1E8(self);
        break;
    case 5:
        if (++self->ext.frozenShadeIcicle.unk84 >= 0x20) {
            DestroyEntity(self);
            return;
        }
        self->ext.frozenShadeIcicle.r--;
        self->ext.frozenShadeIcicle.g -= 2;
        self->ext.frozenShadeIcicle.b -= 4;
        prim = &g_PrimBuf[self->primIndex];
        i = 0;
        func_us_801DB1E8(self);
        while (prim != NULL) {
            UnkEntityFunc0(
                (self->ext.frozenShadeIcicle.angle + ice_shard_angles[i]) &
                    0xFFF,
                ice_shard_speeds[i] * self->ext.frozenShadeIcicle.unk84);
            velocity = F(self->velocityX).i.hi;
            prim->x0 += velocity;
            prim->x1 += velocity;
            prim->x2 += velocity;
            prim->x3 += velocity;
            velocity = F(self->velocityY).i.hi;
            prim->y0 += velocity;
            prim->y1 += velocity;
            prim->y2 += velocity;
            prim->y3 += velocity;
            prim = prim->next;
            i++;
        }

        break;
    case 6:
        entity = &PLAYER;
        self->posX.i.hi = entity->posX.i.hi + self->ext.frozenShadeIcicle.posX;
        self->posY.i.hi = entity->posY.i.hi + self->ext.frozenShadeIcicle.posY;
        if (++self->ext.frozenShadeIcicle.unk84 >= 0x20) {
            DestroyEntity(self);
            return;
        }
        self->ext.frozenShadeIcicle.r--;
        self->ext.frozenShadeIcicle.g -= 2;
        self->ext.frozenShadeIcicle.b -= 4;
        func_us_801DB1E8(self);
        break;
    }

    entity->params = (self->ext.frozenShadeIcicle.unk7E + 0x400) & 0xFFF;
}

// Not certain what this is, appears to be something related to
// despawning the icicles
void EntityFrozenShadeIcicleUnk(Entity* self) {
    Entity* parent;

    parent = self->unk60;
    if ((parent->entityId != E_FROZEN_SHADE_ICICLE) ||
        (parent->unk60 != self)) {
        DestroyEntity(self);
    }

    if (!self->step) {
        InitializeEntity(g_EInitFrozenShadeIcicle);
        self->flags &= ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                         FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA);
        self->hitboxWidth = 2;
        self->hitboxHeight = 2;
    }

    self->posX.val = parent->posX.val;
    self->posY.val = parent->posY.val;
    if (parent->hitboxState) {
        self->hitboxState = parent->hitboxState | 1;
    } else {
        self->hitboxState = 0;
    }
    UnkEntityFunc0(self->params, 0x1800);
    MoveEntity(self);
}
