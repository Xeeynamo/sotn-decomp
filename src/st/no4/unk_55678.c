// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D798C);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D7FAC);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D81B4);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D85A4);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D8654);

extern u8 D_us_80182780[];

void EntityUnkId3F(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitUnkId3F);
        if (!self->facingLeft) {
            self->velocityX = FIX(-4.0);
        } else {
            self->velocityX = FIX(4.0);
        }
        /* fallthrough */
    case 1:
        MoveEntity();
        AnimateEntity(D_us_80182780, self);
        if (self->flags & FLAG_DEAD) {
            self->step = 0;
            self->pfnUpdate = EntityExplosion;
            self->params = 0;
        }
    }
}

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D8DF0);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D8FE0);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D93E0);

static void func_us_801D9560(Primitive* prim) {
    s16 dx, dy;

    Tilemap* tilemap = &g_Tilemap;
    dx = LOH(prim->clut) - tilemap->scrollX.i.hi;
    dy = LOH(prim->tpage) - tilemap->scrollY.i.hi;

    prim->x0 = prim->x3 = dx - 0;
    prim->x1 = dx + (prim->u3 / 16 + 2);
    prim->x2 = dx - (prim->u3 / 16 + 2);

    prim->y1 = prim->y2 = dy - 0;
    prim->y0 = dy - (prim->u3 / 4 + 2);
    prim->y3 = dy + (prim->u3 / 4 + 2);
}

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801D95EC);

extern u8 D_us_801827F0[];
extern u8 D_us_80182800[];
extern u8 D_us_80182810[];
extern u8 D_us_80182818[];
extern u8 D_us_8018282C[];
extern s32 D_us_80182840[];
extern s32 D_us_80182860[];
extern u8 D_us_80182880[];
extern s16 D_us_801828B0[][3];
extern u8 D_us_8018291C[];
extern s16 D_us_8018295C[];
extern s16 D_us_80182A54[];
extern s16 D_us_80182A5C[];

void func_us_801D96FC(Entity* self) {
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
    Primitive* prim;
    Primitive* prim2;
    s16 tempVar;
    s16 i, j;

    tilemap = &g_Tilemap;
    self->ext.et_801D96FC.unk9E++;
    if (self->step && !(self->flags & FLAG_DEAD)) {
        self->ext.et_801D96FC.unk7C++;
        if (self->ext.et_801D96FC.unk7C & 0x40) {
            self->unk6C = (u8)(self->ext.et_801D96FC.unk7C & 0x3F) + 0x40;
        } else {
            self->unk6C = 0x80 - (u8)(self->ext.et_801D96FC.unk7C & 0x3F);
        }
    }
    tempEntity = &PLAYER;
    if ((self->flags & FLAG_DEAD) && (self->step != 4)) {
        SetStep(4);
    }
    if (self->ext.et_801D96FC.unk82) {
        prim = &g_PrimBuf[self->primIndex];
        j = 0;
        if (self->ext.et_801D96FC.unk82 != 2) {
            if ((self->ext.et_801D96FC.unkA4 & 0x1F) == 0) {
                PlaySfxPositional(0x6B0);
            }
            self->ext.et_801D96FC.unkA4++;
        }
        while (prim != NULL) {
            if (!prim->v2) {
                if (!prim->p3) {
                    if (self->facingLeft) {
                        LOW(prim->u0) += D_us_80182840[prim->u2];
                    } else {
                        LOW(prim->u0) -= D_us_80182840[prim->u2];
                    }
                    LOW(prim->u1) +=
                        D_us_80182860[prim->u2] - (prim->u3++ << 10);
                    func_us_801D9560(prim);
                    PRED(prim)--;
                    PGRN(prim)--;
                    PBLU(prim) -= 3;
                    if (prim->p2) {
                        tempEntity = &g_Entities[self->ext.et_801D96FC
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
                    if (prim->p1 == (self->ext.et_801D96FC.unk9E & 3) &&
                        prim->u3 < 0x30) {
                        tempEntity =
                            &g_Entities[self->ext.et_801D96FC.unkA8[j]];
                        tempEntity->posX.i.hi =
                            LOH(prim->clut) - tilemap->scrollX.i.hi;
                        tempEntity->posY.i.hi =
                            LOH(prim->tpage) - tilemap->scrollY.i.hi;
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
                if ((self->ext.et_801D96FC.unk82 == 2 ||
                     (self->flags & FLAG_DEAD)) &&
                    !prim->p3) {
                    prim->v2 = 0xFF;
                    if (self->ext.et_801D96FC.unk81 >= 0x1F) {
                        self->ext.et_801D96FC.unk82 = 0;
                        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                                       FLAG_UNK_20000000;
                    } else {
                        self->ext.et_801D96FC.unk81++;
                    }
                    prim = prim->next;
                    continue;
                }
                prim->v2--;
                if (!prim->v2) {
                    prim->p1 = self->ext.et_801D96FC.unk83;
                    prim->u2 = D_us_80182880[prim->p1];
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
                    LOW(prim->u1) =
                        (self->posY.val + tilemap->scrollY.val) - FIX(7);
                    if (self->facingLeft) {
                        LOW(prim->u0) =
                            (self->posX.val + tilemap->scrollX.val) + FIX(14);
                    } else {
                        LOW(prim->u0) =
                            (self->posX.val + tilemap->scrollX.val) - FIX(14);
                    }
                    func_us_801D9560(prim);
                    self->ext.et_801D96FC.unk83++;
                    self->ext.et_801D96FC.unk83 &= 0xF;
                }
            }
            prim = prim->next;
        }
        for (i = j; i < 8; i++) {
            tempEntity = &g_Entities[self->ext.et_801D96FC.unkA8[i]];
            if (self->ext.et_801D96FC.unk82) {
                tempEntity->hitboxWidth = 0;
            } else {
                DestroyEntity(tempEntity);
            }
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180C64);
        self->unk6C = 0x40;
        self->palette += self->params;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_UNK8;
        self->ext.et_801D96FC.unk7C = 0;
        if (self->posX.val < tempEntity->posX.val) {
            self->facingLeft = true;
            self->ext.et_801D96FC.unk7E = 0;
        } else {
            self->ext.et_801D96FC.unk7E = 0x800;
        }
        self->ext.et_801D96FC.unk8C = self->posY.val;
        self->ext.et_801D96FC.unkA0 = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        self->ext.et_801D96FC.unkA2 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        self->ext.et_801D96FC.unk84 = 0x10;
        self->ext.et_801D96FC.unk80 = 0;
        self->velocityY = FIX(0.25);
        primIndex = g_api.AllocPrimitives(PRIM_G4, 0x20);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
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
        AnimateEntity(D_us_801827F0, self);
        tempVar = GetDistanceToPlayerX();
        var_s4 = tempEntity->posX.i.hi - self->posX.i.hi;
        if (tempVar < 0x10) {
            SetStep(2);
        } else if ((var_s4 < 0 && self->facingLeft) ||
                   (var_s4 >= 0 && !self->facingLeft)) {
            SetStep(2);
        }
        if ((self->posX.i.hi & 0x100) == 0 && !--self->ext.et_801D96FC.unk84) {
            if (tempVar < 0x60 && GetDistanceToPlayerY() < 0x40 && rand() & 3) {
                j = 0xA0;
                var_s0_3 = 0;
                for (tempEntity = &g_Entities[160];
                     tempEntity < &g_Entities[192]; tempEntity++) {
                    if (!tempEntity->entityId) {
                        DestroyEntity(tempEntity);
                        self->ext.et_801D96FC.unkA8[var_s0_3++] = j;
                        if (var_s0_3 >= 8) {
                            break;
                        }
                    }
                    j++;
                }
                if (var_s0_3 == 8) {
                    for (i = 0; i < 8; i++) {
                        tempEntity =
                            &g_Entities[self->ext.et_801D96FC.unkA8[i]];
                        CreateEntityFromCurrentEntity(E_ID_46, tempEntity);
                        tempEntity->hitboxWidth = 0;
                    }
                    SetStep(3);
                    PlaySfxPositional(SFX_UI_TINK);
                    self->ext.et_801D96FC.unk98 = 0;
                    self->ext.et_801D96FC.unk8A = 0;
                } else {
                    self->step = 5;
                    self->ext.et_801D96FC.unk8A = 0;
                }
            } else {
                self->step = 5;
                self->ext.et_801D96FC.unk8A = 0;
            }
        }
        func_us_801D95EC(self);
        break;

    case 2:
        AnimateEntity(D_us_8018282C, self);
        tempVar = GetDistanceToPlayerX();
        if (tempVar > 0x10) {
            tempVar = self->posX.i.hi - tempEntity->posX.i.hi;
            if (self->facingLeft) {
                if (tempVar > 0) {
                    if (self->pose == 5) {
                        SetStep(1);
                        self->facingLeft = false;
                        AnimateEntity(D_us_801827F0, self);
                    }
                } else {
                    if (self->pose == 1) {
                        SetStep(1);
                        AnimateEntity(D_us_801827F0, self);
                    }
                }
            } else if (tempVar < 0) {
                if (self->pose == 5) {
                    SetStep(1);
                    self->facingLeft = true;
                    AnimateEntity(D_us_801827F0, self);
                }
            } else {
                if (self->pose == 1) {
                    SetStep(1);
                    AnimateEntity(D_us_801827F0, self);
                }
            }
        }
        func_us_801D95EC(self);
        break;

    case 3:
        switch (self->step_s) {
        case 0:
            if (self->velocityY < 0) {
                self->velocityY += 0x200;
            } else if (self->velocityY > 0) {
                self->velocityY -= 0x200;
            }
            tempVar = AnimateEntity(D_us_80182800, self);
            j = self->ext.et_801D96FC.unk8A++;
            self->ext.et_801D96FC.unk98 += 0x20;
            SetGeomScreen(0x100);
            if (self->facingLeft) {
                var_s4 = self->posX.i.hi + 1;
            } else {
                var_s4 = self->posX.i.hi - 1;
            }
            SetGeomOffset(var_s4, self->posY.i.hi + 0xC);
            points[0] = SP2(0, SVECTOR);
            points[1] = SP2(2, SVECTOR);
            points[2] = SP2(4, SVECTOR);
            points[3] = SP2(6, SVECTOR);
            sxy[0] = SP2(8, Point16);
            sxy[1] = SP2(9, Point16);
            sxy[2] = SP2(10, Point16);
            sxy[3] = SP2(11, Point16);
            p = SP2(12, long);
            flag = SP2(13, long);
            primaryColor = SP2(14, CVECTOR);
            color = SP2(15, CVECTOR);
            mat = SP2(16, MATRIX);
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
            mat = RotMatrixY(self->ext.et_801D96FC.unk98, mat);
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
            point = D_us_8018295C;
            prim = &g_PrimBuf[self->primIndex];
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
                self->ext.et_801D96FC.unk84 = 0x80;
                self->ext.et_801D96FC.unkA4 = 0;
                self->ext.et_801D96FC.unk82++;
                self->ext.et_801D96FC.unk83 = 0;
                self->ext.et_801D96FC.unk81 = 0;
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
                prim = &g_PrimBuf[self->primIndex];
                while (prim != NULL) {
                    prim->v2 = j;
                    j += 2;
                    prim = prim->next;
                }
            }
            break;

        case 1:
            AnimateEntity(D_us_80182810, self);
            if (self->velocityX != 0) {
                if (self->facingLeft) {
                    self->velocityX += 0x600;
                } else {
                    self->velocityX -= 0x600;
                }
            }
            if (!--self->ext.et_801D96FC.unk84) {
                self->step_s++;
                self->pose = 0;
                self->poseTimer = 0;
                self->ext.et_801D96FC.unk82++;
            }
            MoveEntity(self);
            break;

        case 2:
            if (!AnimateEntity(D_us_80182818, self)) {
                SetStep(1);
                self->ext.et_801D96FC.unk7E = 0xC00;
                self->ext.et_801D96FC.unk84 = (rand() & 0x1F) + 0x80;
            }
            break;
        }
        MoveEntity();
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 9;
            self->ext.et_801D96FC.unk84 = 0x10;
            g_api.PlaySfx(0x733);
            self->step_s++;
            break;

        case 1:
            if (!self->ext.et_801D96FC.unk84) {
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
                            self->ext.et_801D96FC.unk90 = prim2;
                        } else {
                            self->ext.et_801D96FC.unk94 = prim2;
                            break;
                        }
                    }
                    prim2 = prim2->next;
                }
                if (!tempVar) {
                    prim2 = self->ext.et_801D96FC.unk90;
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

                    prim2 = self->ext.et_801D96FC.unk94;
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
                    g_api.PlaySfx(0x6B0);
                    self->animCurFrame = 0;
                    self->step_s++;
                    break;
                }
            } else {
                self->ext.et_801D96FC.unk84--;
            }
            break;

        case 2:
            tempVar = self->ext.et_801D96FC.unk84;
            var_s4 = 0;
#ifdef VERSION_PSP
            prim2 = self->ext.et_801D96FC.unk90;
            if (tempVar < 0x30) {
                prim2->v2 = prim2->v3--;
                prim2->y2 = prim2->y3--;
            } else if (tempVar == 0x30) {
                prim2->drawMode = DRAW_HIDE;
            }
#else
            if (tempVar < 0x30) {
                prim2 = self->ext.et_801D96FC.unk90;
                prim2->v2 = prim2->v3--;
                prim2->y2 = prim2->y3--;
            } else if (tempVar == 0x30) {
                prim2 = self->ext.et_801D96FC.unk90;
                prim2->drawMode = DRAW_HIDE;
            }
#endif
            var_s4 = prim2->y2;
            var_s0_3 = prim2->x2;
            prim2 = self->ext.et_801D96FC.unk94;
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
            if (self->ext.et_801D96FC.unk84 < 0x40) {
                prim = &g_PrimBuf[self->primIndex];
                while (prim != NULL) {
                    if (prim->drawMode == DRAW_HIDE) {
                        if (!prim->p3 && (prim->v2 != 0xFF)) {
                            prim = prim->next;
                            continue;
                        }
                        LOH(prim->clut) =
                            (prim2->x2 + prim2->x0) / 2 +
                            tilemap->scrollX.i.hi +
                            Random() *
                                (prim2->x3 + prim2->x1 - prim2->x2 -
                                 prim2->x0) /
                                0x200;
                        LOH(prim->tpage) =
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
            self->ext.et_801D96FC.unk84++;
            if (self->ext.et_801D96FC.unk84 > 0x50) {
                DestroyEntity(self);
            }
            break;
        }
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            if (prim->p3 == 4) {
                LOW(prim->u1) -= 0x20000;
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
        AnimateEntity(D_us_801827F0, self);
        switch (self->step_s) {
        case 0:
            if (self->velocityY < 0) {
                self->velocityY += 0x200;
            } else if (self->velocityY > 0) {
                self->velocityY -= 0x200;
            }
            if (++self->ext.et_801D96FC.unk8A > 0x40) {
                self->ext.et_801D96FC.unk8A = 0;
                self->ext.et_801D96FC.unk9C = rand() & 3;
                PlaySfxPositional(0x6AE);
                self->step_s++;
            }
            break;

        case 1:
#ifdef VERSION_PSP
            if (!self->ext.et_801D96FC.unk8A++) {
#else
            if (++self->ext.et_801D96FC.unk8A == 1) {
#endif
                tempVar = self->ext.et_801D96FC.unk9C;
                for (i = 0; i < 3; i++) {
                    tempEntity =
                        AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (tempEntity != NULL) {
                        CreateEntityFromCurrentEntity(E_ID_47, tempEntity);
                        tempEntity->posX.i.hi += D_us_80182A54[tempVar];
                        tempEntity->posY.i.hi += D_us_80182A5C[tempVar];
                        tempEntity->params = i;
                        // probably uses a different ext struct
                        tempEntity->ext.et_801D96FC.unk8C = (u32)self;
                        tempVar++;
                        tempVar &= 3;
                    }
                }
            }
            if (self->ext.et_801D96FC.unk8A >= 0x40) {
                self->ext.et_801D96FC.unk84 = (rand() & 0x1F) + 0x80;
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

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DB194);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DB1E8);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DB65C);

INCLUDE_ASM("st/no4/nonmatchings/unk_55678", func_us_801DBBEC);
