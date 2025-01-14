// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

extern u16 g_EInitParticle[];

void func_us_801BFA34(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitParticle);
        self->palette = PAL_OVL(0x19E);
        self->animSet = 2;
        self->animCurFrame = 9;
        self->drawMode = DRAW_TPAGE;
        self->rotX = 64;
        self->rotY = 64;
        self->rotZ = -0x400;
        self->velocityX = FIX(-5.0 / 4.0);
        self->zPriority += 8;
        self->drawFlags |= FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
    } else {
        self->rotX += 4;
        self->rotY += 14;
        self->animFrameDuration++;
        self->posX.val += self->velocityX;

        if (!(self->animFrameDuration & 1)) {
            self->animCurFrame++;
        }

        if (self->animFrameDuration >= 24) {
            DestroyEntity(self);
        }
    }
}

extern SVEC4 D_us_80181778[];
extern SVEC4 D_us_801817D8[];
extern SVEC4 D_us_801818C0[];
extern MATRIX D_us_80181920;
extern u32 D_psp_0929A6E8;
extern u32 D_psp_0929A6F8;

void func_us_801BFB40(Entity* self) {
    long sxy2, sxy3, p;
    Collider collider;
    SVECTOR rot;
    VECTOR trans;
    MATRIX m;
    u8 pad[16];
    MATRIX lightMatrix;
    CVECTOR color;
    u8 pad2[2];
    Primitive* prim;
    Entity* tempEntity;
    SVEC4* positions;
    SVEC4* normals;
    s32 primIndex;
    s16 posX, posY;
    s32 i;
    s32 opz;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BFB40.unk7C = prim;
            while (prim != NULL) {
                prim->tpage = 0xE;
                prim->clut = 0;
                prim->u0 = 0xE9;
                prim->u1 = prim->u0 + 0xE;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0x31;
                prim->v1 = prim->v0;
                prim->v2 = prim->v0 + 0xE;
                prim->v3 = prim->v2;
                prim->r0 = prim->b0 = prim->g0 = 0x80;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                if (self->params) {
                    prim->priority = 0xC0;
                } else {
                    prim->priority = 0xA0;
                }
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
            return;
        }
        DestroyEntity(self);
        return;
    case 1:
        switch (self->step_s) {
        case 0:
            self->velocityX = FIX(0.0625);
            self->velocityY = 0;
            self->step_s++;
            if (self->params) {
                self->velocityX = -(Random() & 7) * 0x2000;
                self->velocityY = -0x24000 - (Random() & 3) * 0x4000;
            }
            break;
        case 1:
            if (!self->params) {
                self->ext.et_801BFB40.unk80.vx += 0x40;
                self->ext.et_801BFB40.unk80.vy -= 0x10;
                self->ext.et_801BFB40.unk80.vz -= 0x10;
            } else {
                self->ext.et_801BFB40.unk80.vx += 0x40;
                self->ext.et_801BFB40.unk80.vy += 0x80;
                self->ext.et_801BFB40.unk80.vz -= 0x20;
            }
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!self->params) {
                if (self->velocityX > FIX(-1.5)) {
                    self->velocityX -= 0x400;
                }
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            if (!self->params) {
                posY += 8;
            } else {
                posY += 4;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (!self->params && (self->velocityX > FIX(-1.0)) &&
                (collider.effects & EFFECT_SOLID)) {
                if ((g_Timer & 7) == 0) {
                    self->posY.i.hi += collider.unk18;
                }
                self->velocityY = 0;
                self->ext.et_801BFB40.unk80.vx = 0;
                self->ext.et_801BFB40.unk80.vy = 0;
                self->ext.et_801BFB40.unk80.vz = 0;
            } else if (collider.effects & EFFECT_SOLID) {
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                self->posY.i.hi += collider.unk18;
                self->velocityY = -self->velocityY / 2;
                if (self->params) {
                    if (self->velocityY > FIX(-0.25)) {
                        tempEntity =
                            AllocEntity(&g_Entities[64], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(
                                E_INTENSE_EXPLOSION, self, tempEntity);
                            tempEntity->params = 0x10;
                        }
                        DestroyEntity(self);
                        return;
                    }
                } else {
                    for (i = 0; i < 4; i++) {
                        tempEntity =
                            AllocEntity(&g_Entities[64], &g_Entities[256]);
                        if (tempEntity != NULL) {
#ifdef VERSION_PSP
                            CreateEntityFromEntity(
                                D_psp_0929A6F8, self, tempEntity);
#else
                            CreateEntityFromEntity(E_ID_2F, self, tempEntity);
#endif
                            tempEntity->params = i;
                        }
                    }
                    if (self->velocityY > FIX(-1.25)) {
                        g_api.PlaySfx(0x644);
                        for (i = 0; i < 3; i++) {
                            tempEntity =
                                AllocEntity(&g_Entities[64], &g_Entities[256]);
                            if (tempEntity != NULL) {
#ifdef VERSION_PSP
                                CreateEntityFromEntity(
                                    D_psp_0929A6E8, self, tempEntity);
#else
                                CreateEntityFromEntity(
                                    E_ID_31, self, tempEntity);
#endif
                                tempEntity->params = i + 1;
                            }
                        }
                        DestroyEntity(self);
                        return;
                    }
                }
            }
            break;
        }
        prim = self->ext.et_801BFB40.unk7C;
        SetGeomScreen(0x400);
        rot.vx = self->ext.et_801BFB40.unk80.vx;
        rot.vy = self->ext.et_801BFB40.unk80.vy;
        rot.vz = self->ext.et_801BFB40.unk80.vz;
        RotMatrix(&rot, &m);
        trans.vx = 0;
        trans.vy = 0;
        trans.vz = 0x408;
        if (self->params) {
            trans.vz = 0x800;
        }
        TransMatrix(&m, &trans);
        SetRotMatrix(&m);
        SetTransMatrix(&m);
        if (!self->params) {
            color.r = 0xA0;
            color.g = 0xA0;
            color.b = 0xA0;
            color.cd = prim->type;
        } else {
            color.r = 0x90;
            color.g = 0x90;
            color.b = 0x90;
            color.cd = prim->type;
        }
        RotMatrix(&rot, &lightMatrix);
        SetBackColor(0x40, 0x40, 0x40);
        SetLightMatrix(&lightMatrix);
        SetColorMatrix(&D_us_80181920);
        SetFarColor(0x60, 0x60, 0x60);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        if (!self->params) {
            positions = D_us_801817D8;
        } else {
            positions = D_us_80181778;
        }
        normals = D_us_801818C0;
        prim = self->ext.et_801BFB40.unk7C;
        for (i = 0; i < 6; i++) {
            opz = RotAverageNclip4(
                positions->v0, positions->v1, positions->v2, positions->v3,
                (long*)(&prim->x0), (long*)(&prim->x1), (long*)(&prim->x2),
                (long*)(&prim->x3), &sxy2, &p, &sxy3);
            if (opz <= 0) {
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->drawMode = DRAW_COLORS | DRAW_UNK02;
                NormalColorCol(normals->v0, &color, (CVECTOR*)(&prim->r0));
                NormalColorCol(normals->v1, &color, (CVECTOR*)(&prim->r1));
                NormalColorCol(normals->v2, &color, (CVECTOR*)(&prim->r2));
                NormalColorCol(normals->v3, &color, (CVECTOR*)(&prim->r3));
            }
            positions++;
            normals++;
            prim = prim->next;
        }
        break;
    }
}

INCLUDE_ASM("st/no1/nonmatchings/unk_3FA34", func_us_801C01F0);

INCLUDE_ASM("st/no1/nonmatchings/unk_3FA34", func_us_801C05DC);

// bone throwing skeleton
INCLUDE_ASM("st/no1/nonmatchings/unk_3FA34", func_us_801C0A40);

// in the doppleganger room, maybe rotating door
INCLUDE_ASM("st/no1/nonmatchings/unk_3FA34", func_us_801C0B9C);

// black to gray transition for "Elevator activated." text?
s32 func_us_801C0E98(Primitive* prim) {
    if (prim->g0 > 96) {
        if (prim->b0 > 96) {
            if (prim->r0 <= 96) {
                prim->r0 += 2;
            } else {
                return 1;
            }
        } else {
            prim->b0 += 2;
        }
    } else {
        prim->g0 += 2;
    }

    if (prim->b2 > 96) {
        if (prim->r2 > 96) {
            if (prim->g2 <= 96) {
                prim->g2 += 2;
            }
        } else {
            prim->r2 += 2;
        }
    } else {
        prim->b2 += 2;
    }

    if (prim->g1 > 32) {
        if (prim->r1 > 32) {
            if (prim->b1 <= 32) {
                prim->b1 += 2;
            }
        } else {
            prim->r1 += 2;
        }
    } else {
        prim->g1 += 2;
    }
    if (prim->r3 > 32) {
        if (prim->g3 > 32) {
            if (prim->b3 > 32) {
                prim->b3 += 8;
            } else {
                prim->b3 += 4;
            }
            prim->g3 += 2;
        } else {
            prim->g3 += 4;
        }
        prim->r3 += 2;
    } else {
        prim->r3 += 4;
    }

    return 0;
}

// support function for `func_us_801C10F4`
void func_us_801C1090(s32* value, s32 target, s32 step) {
    if (*value < target) {
        *value += step;
    }
    if (*value > target) {
        *value -= step;
    }

    if (*value < 0) {
        *value = 0;
    }

    if (*value > 0x80) {
        *value = 0x80;
    }
}

// "Elevator activatd." text
extern Primitive* D_us_801D6380;
extern s32 D_us_801D6FFC;
extern s32 D_us_801D7000;
extern s32 D_us_801D7004;
extern s32 D_us_801D7008;
extern s32 D_us_801D700C;
extern s32 D_us_801D7010;
extern s32 D_us_801D7014;
extern s32 D_us_801D7018;
extern s32 D_us_801D701C;
extern s32 D_us_801D7020;
extern u16 g_EInitInteractable[];

void func_us_801C10F4(Entity* self) {
    DRAWENV drawEnv;
    RECT clipRect;
    Primitive* prim;
    s32 hasXOffset;
    s32 primIndex;

    FntPrint("elemess_step%x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.et_801C10F4.unk80 = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        D_us_801D6380 = prim;
        if (g_api.func_800EDB08((POLY_GT4*)prim) == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0xC5;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        if (g_api.func_800EDB08((POLY_GT4*)prim) == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0xC7;
        prim->drawMode = DRAW_UNK_800;

        prim = prim->next;
        self->ext.et_801C10F4.unk7C = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    case 1:
        D_us_801D7018 = 0;
        D_us_801D7014 = 0;
        D_us_801D7020 = 0;
        D_us_801D701C = 0;
        D_us_801D7004 = 0;
        D_us_801D7008 = 0;
        D_us_801D6FFC = 0;
        D_us_801D7000 = 0;
        D_us_801D700C = 0;
        D_us_801D7010 = 0;
        self->step++;
    case 2:
        func_us_801C1090(&D_us_801D7018, 0x80, 1);
        func_us_801C1090(&D_us_801D7014, 0x40, 1);
        func_us_801C1090(&D_us_801D7020, 0x80, 1);
        func_us_801C1090(&D_us_801D701C, 0x80, 1);
        func_us_801C1090(&D_us_801D7000, 0x80, 2);
        func_us_801C1090(&D_us_801D6FFC, 0, 1);
        func_us_801C1090(&D_us_801D7010, D_us_801D700C + 0x10, 2);
        func_us_801C1090(&D_us_801D700C, D_us_801D7000, 1);
        func_us_801C1090(&D_us_801D7008, D_us_801D700C, 1);
        func_us_801C1090(&D_us_801D7004, 0, 1);
        self->ext.et_801C10F4.unk80++;
        FntPrint("timer %x\n", self->ext.et_801C10F4.unk80);
        if (self->ext.et_801C10F4.unk80 > 0xE0) {
            self->ext.et_801C10F4.unk80 = 0;
            self->step++;
        }
        break;
    case 3:
        func_us_801C1090(&D_us_801D7018, 0, 1);
        func_us_801C1090(&D_us_801D7014, 0, 1);
        func_us_801C1090(&D_us_801D7020, 0, 1);
        func_us_801C1090(&D_us_801D701C, 0, 1);
        if (self->ext.et_801C10F4.unk80++ > 0x100) {
            DestroyEntity(self);
            return;
        }
    }

    prim = D_us_801D6380;
    drawEnv = g_CurrentBuffer->draw;
    drawEnv.isbg = 0;
    drawEnv.dtd = 1;
    drawEnv.r0 = 0;
    drawEnv.g0 = 0;
    drawEnv.b0 = 0;
    hasXOffset = drawEnv.ofs[0] != 0;
    clipRect.x = 0x180;
    clipRect.y = 0x100;
    clipRect.w = 0x80;
    clipRect.h = 0x18;
    drawEnv.clip = clipRect;
    drawEnv.ofs[0] = 0x180;
    drawEnv.ofs[1] = 0x100;
    SetDrawEnv(LOW(prim->r1), &drawEnv);
    prim->drawMode = DRAW_DEFAULT;
    prim->priority = 0xC5;

    prim = self->ext.et_801C10F4.unk7C;
    prim->tpage = 0x11;
    prim->type = PRIM_GT4;
    prim->clut = 0x19F;
    prim->u0 = prim->u2 = D_us_801D7004;
    prim->u1 = prim->u3 = D_us_801D7004 + (D_us_801D7008 - D_us_801D7004) / 2;
    prim->v0 = prim->v1 = 0;
    prim->v2 = prim->v3 = 0x18;
    prim->x0 = prim->x2 = D_us_801D7004 + 0x40;
    prim->x1 = prim->x3 =
        D_us_801D7004 + 0x40 + (D_us_801D7008 - D_us_801D7004) / 2;
    prim->y0 = prim->y1 = 0xA0;
    prim->y2 = prim->y3 = 0xB8;
    PGREY(prim, 0) = PGREY(prim, 2) = D_us_801D701C;
    PGREY(prim, 1) = PGREY(prim, 3) = D_us_801D701C;
    prim->priority = 0xC8;
    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;

    prim = prim->next;
    prim->type = PRIM_GT4;
    prim->tpage = 0x11;
    prim->clut = 0x19F;
    prim->u0 = prim->u2 = D_us_801D7004 + (D_us_801D7008 - D_us_801D7004) / 2;
    prim->u1 = prim->u3 = D_us_801D7008;
    prim->v0 = prim->v1 = 0;
    prim->v2 = prim->v3 = 0x18;
    prim->x0 = prim->x2 =
        D_us_801D7004 + 0x40 + (D_us_801D7008 - D_us_801D7004) / 2;
    prim->x1 = prim->x3 = D_us_801D7008 + 0x40;
    prim->y0 = prim->y1 = 0xA0;
    prim->y2 = prim->y3 = 0xB8;
    PGREY(prim, 0) = PGREY(prim, 2) = D_us_801D701C;
    PGREY(prim, 1) = PGREY(prim, 3) = D_us_801D7020;
    prim->priority = 0xC8;
    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;

    prim = prim->next;
    prim->tpage = 0x116;
    prim->u1 = prim->u3 = 0x80;
    prim->type = PRIM_GT4;
    prim->u0 = prim->u2 = 0;
    prim->v0 = prim->v1 = 0;
    prim->v2 = prim->v3 = 0x18;
    prim->x0 = prim->x2 = 0x40;
    prim->x1 = prim->x3 = 0xC0;
    prim->y0 = prim->y1 = 0xA0;
    prim->y2 = prim->y3 = 0xB8;
    prim->priority = 0xC8;
    prim->drawMode = DRAW_DEFAULT;

    prim = prim->next;
    prim->type = PRIM_GT4;
    if (hasXOffset != 0) {
        prim->tpage = 0x104;
    } else {
        prim->tpage = 0x100;
    }
    prim->u0 = prim->u2 = 0x40;
    prim->u1 = prim->u3 = 0xC0;
    prim->v0 = prim->v1 = 0xA0;
    prim->v2 = prim->v3 = 0xB8;
    prim->x0 = prim->x2 = 0;
    prim->x1 = prim->x3 = 0x80;
    prim->y0 = prim->y1 = 0;
    prim->y2 = prim->y3 = 0x18;
    prim->priority = 0xC6;
    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;

    prim = prim->next;
    prim->type = PRIM_G4;
    func_us_801C0E98(prim);
    prim->y0 = prim->y1 = 0;
    prim->y2 = prim->y3 = 0x18;
    prim->x0 = prim->x2 = D_us_801D700C;
    prim->x1 = prim->x3 = D_us_801D7010;
    prim->priority = 0xC6;
    prim->drawMode = DRAW_DEFAULT;

    prim = prim->next;
    prim->type = PRIM_TILE;
    prim->u0 = 0x80;
    prim->v0 = 0x18;
    prim->x0 = 0;
    prim->y0 = 0;
    PGREY(prim, 0) = 0;
    prim->priority = 0xC6;
    prim->drawMode = DRAW_DEFAULT;

    prim = prim->next;
    prim->type = PRIM_GT4;
    prim->tpage = 0x11;
    prim->clut = 0x19C;
    prim->u0 = prim->u2 = D_us_801D6FFC;
    prim->u1 = prim->u3 = D_us_801D7000;
    prim->v0 = prim->v1 = 0;
    prim->v2 = prim->v3 = 0x18;
    prim->x0 = prim->x2 = D_us_801D6FFC + 0x40;
    prim->x1 = prim->x3 = D_us_801D7000 + 0x40;
    prim->y0 = prim->y1 = 0xA0;
    prim->y2 = prim->y3 = 0xB8;
    PGREY(prim, 0) = PGREY(prim, 2) = D_us_801D7014;
    PGREY(prim, 1) = PGREY(prim, 3) = D_us_801D7018;
    prim->priority = 0xC4;
    prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;

    prim = prim->next;
    prim->type = PRIM_TILE;
    prim->u0 = 0x80;
    prim->v0 = 0x18;
    prim->x0 = 0x40;
    prim->y0 = 0xA0;
    PGREY(prim, 0) = 0;
    prim->priority = 0xC4;
    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
}
