// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"
#include <scratchpad.h>

extern EInit D_us_80180A34;

#ifdef VERSION_PSP
extern s32 E_ID(ID_34);
#endif

static s16 D_us_80181474[][3] = {
    {0x086, 0x07E, 0x100}, {0x068, 0x080, 0x0E0}, {0x088, 0x098, 0x108},
    {0x070, 0x070, 0x0C0}, {0x090, 0x090, 0x120}, {0x074, 0x094, 0x0C0},
    {0x098, 0x080, 0x100}, {0x000, 0x000, 0x100},
};

// unused
static s16 D_us_801814A4[] = {0x16, 0x17, 0x18, 0x19, 0x00, 0x00, 0x00, 0x01};

static s16 D_us_801814B4[] = {
    0x000, 0x070, 0x080, 0x0A0, 0x0C0, 0x0E0, 0x100, 0x000};

static u8 D_us_801814C4[] = {
    0x20, 0xD0, 0x00, 0x28, 0x15, 0x20, 0xD0, 0x18, 0x28, 0x15, 0x00, 0x00};

static SVECTOR D_us_801814D0 = {FLT(0), FLT(0), FLT(0)};

static SVECTOR D_us_801814D8 = {FLT(0), FLT(0), FLT(1)}; // unused

// This is the spyglass at the bottom of NO1
void func_us_801BA290(Entity* self) {
    long p, flag;
    s32 pad[23];
    SVECTOR rotA, rotB, rotC, rotD;
    VECTOR trans;
    MATRIX m;
    s32 pad2[18];
    DRAWENV drawEnv;
    RECT clipRect;

    s16 dy;
    DR_ENV* dr_env;
    Primitive* prim;
    Primitive* prim2;
    s32 primIndex;
    u8 rnd;
    s32 i;
    Entity* tempEntity;

    if (self->step > 1 && self->step < 7) {
        g_Player.padSim = 0;
        g_Player.demo_timer = 2;
        g_api.func_8010DFF0(0, 1);
        g_api.func_8010E168(1, 0x20);
    }
    if (self->ext.et_801BA290.unkA4) {
        PLAYER.animCurFrame = 0;
        self->animCurFrame = 0;
    } else {
        self->animCurFrame = 0x3D;
    }
    self->ext.et_801BA290.unk9C = g_CastleFlags[NO1_WEATHER] & 1;
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809C8);
        self->animCurFrame = 0x3D;
        self->facingLeft = 1;
        self->hitboxState = 1;
        self->hitPoints = 0x7FFE;
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->flags |= FLAG_NOT_AN_ENEMY;
        self->ext.et_801BA290.unkA4 = 0;
        break;

    case 1:

        if (self->hitFlags && (g_pads[0].pressed & PAD_UP) &&
#ifdef VERSION_PSP
            !(g_Player.status + 0xF0000000)) {
#else
            (g_Player.status == PLAYER_STATUS_UNK10000000)) {
#endif
            g_Player.padSim = 0;
            g_Player.demo_timer = 2;
            g_PauseAllowed = false;
            g_api.PlaySfx(SFX_TINK_JINGLE);
            self->step++;
        }
        break;

    case 2:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x19);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BA290.unkAC = prim;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                g_PauseAllowed = true;
                DestroyEntity(self);
                return;
            }

            prim->type = PRIM_ENV;
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 0;
            drawEnv.r0 = 0;
            drawEnv.g0 = 0;
            drawEnv.b0 = 0;
            drawEnv.dtd = 0;
            drawEnv.ofs[0] = 0;
            clipRect.x = 0;
            clipRect.w = 0x100;
            clipRect.y = 0x14;
            clipRect.h = 0;
            drawEnv.clip = clipRect;
            SetDrawEnv(dr_env, &drawEnv);
            prim->priority = 0x4D;
            prim->drawMode = DRAW_UNK_1000 | DRAW_HIDE;
            prim = prim->next;

            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }

            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_UNK_800 | DRAW_HIDE;
            prim->priority = 0xDE;
            prim = prim->next;

            self->ext.et_801BA290.unk7C = prim;
            while (prim != NULL) {
                prim->r0 = prim->g0 = prim->b0 = 0x80;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim = prim->next;
            }
            self->step++;
            break;
        }
        g_PauseAllowed = true;
        DestroyEntity(self);
        break;

    case 3:
        prim = self->ext.et_801BA290.unk7C;
        for (i = 0; i < 2; i++) {
            prim->tpage = 0xE;
            if (self->ext.et_801BA290.unk9C != 0) {
                prim->clut = 0x204;
            } else {
                prim->clut = 0x206;
            }
            prim->u0 = 1;
            prim->u1 = 0x7F;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0x80;
            prim->v1 = prim->v0;
            prim->v2 = 0xEF;
            prim->v3 = prim->v2;
            prim->r0 = 0xC0;
            prim->g0 = 0xC0;
            prim->b0 = 0x60;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0x47;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            prim = prim->next;
        }
        for (i = 0; i < 2; i++) {
            prim->tpage = 0xE;
            if (self->ext.et_801BA290.unk9C != 0) {
                prim->clut = 0x203;
            } else {
                prim->clut = 0x205;
            }
            prim->u0 = 1;
            prim->u1 = 0x7F;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0x41;
            prim->v1 = prim->v0;
            prim->v2 = 0x51;
            prim->v3 = prim->v2;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0x47;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            prim = prim->next;
        }
        for (i = 0; i < 8; i++) {
            prim->tpage = 0xE;
            if (self->ext.et_801BA290.unk9C != 0) {
                prim->clut = 0x203;
            } else {
                prim->clut = 0x205;
            }
            prim->u0 = 1;
            prim->u1 = 0x7F;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0x5A;
            prim->v1 = prim->v0;
            prim->v2 = 0x79;
            prim->v3 = prim->v2;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0x47;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            prim = prim->next;
        }
        self->ext.et_801BA290.unk88 = prim;
        for (i = 0; i < 2; i++) {
            prim->type = PRIM_TILE;
            prim->x0 = 0;
            prim->x1 = 0x104;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->y0 = 0;
            prim->y1 = prim->y0;
            prim->y2 = 0xFF;
            prim->y3 = prim->y2;
            prim->u0 = 0xFF;
            prim->v0 = 0xFF;
            prim->r0 = 0;
            prim->b0 = 0;
            prim->g0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0xE4 + i * 2;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.et_801BA290.unk8C = prim;
        for (i = 0; i < 2; i++) {
            prim->tpage = 0x1A;
            prim->clut = PAL_FILL_WHITE;
            prim->u0 = 0;
            prim->u1 = 0x3F;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xC0;
            prim->v1 = prim->v0;
            prim->v2 = 0xFF;
            prim->v3 = prim->v2;
            prim->x0 = 0x50;
            prim->x1 = 0xB0;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->y0 = 0x50;
            prim->y1 = prim->y0;
            prim->y2 = 0xB0;
            prim->y3 = prim->y2;
            prim->r0 = 0;
            prim->b0 = 0;
            prim->g0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0xE3 + i * 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.et_801BA290.unk90 = prim;
        for (i = 0; i < 2; i++) {
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_19F;
            prim->u0 = 0;
            prim->u1 = 0x3F;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xC0;
            prim->v1 = prim->v0;
            prim->v2 = 0xFF;
            prim->v3 = prim->v2;
            prim->x0 = 0x40;
            prim->x1 = 0xC0;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->y0 = 0x40;
            prim->y1 = prim->y0;
            prim->y2 = 0xC0;
            prim->y3 = prim->y2;
            prim->r0 = 0;
            prim->b0 = 0;
            prim->g0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0xE3 + i * 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.et_801BA290.unk84 = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0xE;
        prim->clut = 0x44;
        prim->u0 = 0xD0;
        prim->u1 = 0xF8;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 0;
        prim->v1 = prim->v0;
        prim->v2 = 0x18;
        prim->v3 = prim->v2;
        LOH(prim->next->r2) = 0x28;
        LOH(prim->next->b2) = 0x18;
        LOH(prim->next->u1) = 0xB80;
        prim->next->b3 = 0x80;
        prim->next->x1 = 0x80;
        prim->next->y0 = 0x7E;
        prim->priority = 0x48;
        prim->drawMode = DRAW_UNK02;
        rnd = Random() & 3;
        if (!rnd) {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        prim = prim->next;

        self->ext.et_801BA290.unk98 = prim;
        prim->tpage = 0xE;
        prim->clut = PAL_UNK_19F;
        prim->u0 = 0xD0;
        prim->u1 = 0xF8;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 0;
        prim->v1 = prim->v0;
        prim->v2 = 0x16;
        prim->v3 = prim->v2;
        prim->r0 = 0x10;
        prim->g0 = 0x10;
        prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->p1 = 0;
        prim->p2 = 0;
        prim->priority = 0x44;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        if (self->ext.et_801BA290.unk9C == 0) {
            prim->drawMode = DRAW_HIDE;
        }
        if (!rnd) {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;

        self->ext.et_801BA290.unk94 = prim;
        prim->type = PRIM_TILE;
        prim->x0 = 0;
        prim->y0 = 0;
        prim->u0 = 0xFF;
        prim->v0 = 0x80;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0xE8;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        prim->type = PRIM_TILE;
        prim->x0 = 0;
        prim->y0 = 0x80;
        prim->u0 = 0xFF;
        prim->v0 = 0x80;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0xE8;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        self->ext.et_801BA290.unk80 = 0xB80;
        self->step++;
        break;

    case 4:
        prim = self->ext.et_801BA290.unk88;
        prim->type = PRIM_G4;
        prim->r0 += 4;
        prim->g0 = prim->b0 = prim->r0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        if (prim->r0 > 0xF0) {
            prim->type = PRIM_TILE;
            self->ext.et_801BA290.unkA4 = 1;
            g_Tilemap.flags ^= 1;
            prim = self->ext.et_801BA290.unkAC;
            for (i = 0; i < 2; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            self->step_s = 0;
            self->step++;
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            prim = self->ext.et_801BA290.unk94;
            prim->x0 = 0;
            prim->y0 = 0U;
            prim->u0 = 0x50;
            prim->v0 = 0xFF;
            prim->drawMode = DRAW_DEFAULT;
            prim2 = prim->next;
            prim = prim2;

            prim->x0 = 0xB0;
            prim->y0 = 0;
            prim->u0 = 0x50;
            prim->v0 = 0xFF;
            prim->drawMode = DRAW_DEFAULT;
            prim = self->ext.et_801BA290.unk88;
            for (i = 0; i < 2; i++) {
                prim->x0 = prim->x2 = 0x50;
                prim->x1 = prim->x3 = 0xB0;
                prim->u0 = 0x60;
#ifdef VERSION_PSP
                prim->r0 = 0x40;
#else
                prim->r0 = 0x80;
#endif
                prim->g0 = prim->b0 = prim->r0;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim = prim->next;
            }
            self->step_s++;
            break;

        case 1:
            prim = self->ext.et_801BA290.unk90;
            for (i = 0; i < 2; i++) {
                prim->r0++;
                prim->g0 = prim->b0 = prim->r0;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                if (prim->r0 == 0x30) {
                    g_api.PlaySfx(SFX_TELESCOPE_SHUTTER_CLICK);
                    self->step_s = 2;
                }
                prim = prim->next;
            }
            break;

        case 2:
            prim = self->ext.et_801BA290.unk8C;
            for (i = 0; i < 2; i++) {
                prim->r0++;
                prim->g0 = prim->b0 = prim->r0;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                if (prim->r0 == 0x20) {
                    self->step_s = 3;
                }
                prim = prim->next;
            }
            break;

        case 3:
            self->ext.et_801BA290.unk80 -= 8;
            if (self->ext.et_801BA290.unk80 < 0x380) {
                self->ext.et_801BA290.unk82 = 0x80;
                self->step_s++;
                prim = self->ext.et_801BA290.unk84;
                LOW(prim->next->u0) = -0x1000;
                for (i = 0; i < 3; i++) {
                    tempEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (tempEntity != NULL) {
                        CreateEntityFromCurrentEntity(E_ID(ID_34), tempEntity);
                        rnd = Random() & 7;
                        if ((Random() & 1) == 0) {
                            rnd = 7;
                        }
                        tempEntity->posX.i.hi = D_us_80181474[rnd][0];
                        tempEntity->posY.i.hi = D_us_80181474[rnd][1];
                        tempEntity->scaleX = D_us_80181474[rnd][2];
                    }
                }
            }
            break;

        case 4:
            if (!--self->ext.et_801BA290.unk82) {
                g_api.PlaySfx(SFX_TELESCOPE_SHUTTER_CLICK);
                self->step_s = 0;
                self->step++;
            }
            break;
        }
        SetGeomScreen(0x400);
        rotD.vx = 0;
        rotD.vy = 0;
        rotD.vz = 0;
        RotMatrix(&D_us_801814D0, &m);
        trans.vx = -0x80;
        trans.vy = -0x80;
        trans.vz = self->ext.et_801BA290.unk80;
        TransMatrix(&m, &trans);
        SetRotMatrix(&m);
        SetTransMatrix(&m);
        SetGeomOffset(0x80, 0x80);
        for (i = 0; i < 7; i++) {
            rotA.vx = 0;
            rotB.vx = 0x8F;
            rotC.vx = 0xFE;
            rotA.vy = D_us_801814B4[i];
            rotB.vy = D_us_801814B4[i];
            rotC.vy = D_us_801814B4[i];
            rotA.vz = 0;
            rotB.vz = 0;
            rotC.vz = 0;
            rotA.pad = 0;
            rotB.pad = 0;
            rotC.pad = 0;
            RotTransPers3(&rotA, &rotB, &rotC, &SPAD(0)[i * 3], &SPAD(1)[i * 3],
                          &SPAD(2)[i * 3], &p, &flag);
        }
        prim = self->ext.et_801BA290.unk7C;
        rnd = 0;
        for (i = 0; i < 6; i++) {
            LOW(prim->x0) = SPAD(0)[i * 3];
            LOW(prim->x1) = SPAD(1)[i * 3];
            LOW(prim->x2) = SPAD(3)[i * 3];
            LOW(prim->x3) = SPAD(4)[i * 3];
            prim = prim->next;

            LOW(prim->x0) = SPAD(1)[i * 3];
            LOW(prim->x1) = SPAD(2)[i * 3];
            LOW(prim->x2) = SPAD(4)[i * 3];
            LOW(prim->x3) = SPAD(5)[i * 3];
            prim = prim->next;
            rnd += 3;
        }
        prim = self->ext.et_801BA290.unk84;
        LOH(prim->next->u1) = 0x400 - self->ext.et_801BA290.unk80;
        UpdateAnimation(D_us_801814C4, prim);
        UnkPrimHelper(prim);
        prim2 = self->ext.et_801BA290.unk98;
        UpdateAnimation(D_us_801814C4, prim2);
        prim2->x2 = prim->x2;
        prim2->x3 = prim->x3;
        prim2->x0 = prim2->x2;
        prim2->x1 = prim2->x3;
        prim2->y2 = prim->y2;
        prim2->y3 = prim->y3;
        dy = prim->y2 - prim->y0;
        prim2->y0 = prim2->y2 + dy;
        prim2->y1 = prim2->y3 + dy;
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            prim = self->ext.et_801BA290.unk8C;
            for (i = 0; i < 2; i++) {
                if (prim->y0 != 0x80) {
                    prim->y0 += 2;
                    prim->y1 = prim->y0;
                }
                if (prim->y2 != 0x80) {
                    prim->y2 -= 2;
                    prim->y3 = prim->y2;
                }
                prim = prim->next;
            }
            prim = self->ext.et_801BA290.unk90;
            for (i = 0; i < 2; i++) {
                if (prim->y0 != 0x80) {
                    prim->y0 += 2;
                    prim->y1 = prim->y0;
                }
                if (prim->y2 != 0x80) {
                    prim->y2 -= 2;
                    prim->y3 = prim->y2;
                } else {
                    self->step_s = 1;
                }
                prim = prim->next;
            }
            break;

        case 1:
            g_Tilemap.flags ^= 1;
            self->ext.et_801BA290.unkA4 = 0;
            prim = self->ext.et_801BA290.unk7C;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                if (prim == self->ext.et_801BA290.unk94) {
                    break;
                }
            }
            prim = self->ext.et_801BA290.unkAC;
            for (i = 0; i < 2; i++) {
                prim->drawMode |= DRAW_HIDE;
                prim = prim->next;
            }
            prim = self->ext.et_801BA290.unk94;
            prim->x0 = 0;
            prim->y0 = 0;
            prim->u0 = 0xFF;
            prim->v0 = 0x80;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;

            prim->x0 = 0;
            prim->y0 = 0x80;
            prim->u0 = 0xFF;
            prim->v0 = 0x80;
            prim->drawMode = DRAW_DEFAULT;
            self->step_s++;
            break;

        case 2:
            prim = self->ext.et_801BA290.unk94;
            prim->y0 -= 8;
            prim = prim->next;

            prim->y0 += 8;
            if (prim->y0 > 0x100) {
                self->step_s++;
            }
            break;

        case 3:
            primIndex = self->primIndex;
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
            self->hitboxState = 0;
            g_PauseAllowed = true;
            self->step++;
            break;
        }
        break;
    }
}

static u8 D_us_801814E0[] = {
    8,   103, 4,   104, 4,   105, 8,   106, 8,   107, 4,
    108, 4,   109, 8,   110, 8,   111, 8,   112, -1,  0,
};

static s16 delays[] = {32, 24, 16, 4, 8, 28, 40, 14};

// Triggers when fully zoomed in after interacting with the spyglass
// Likely the fish function
void func_us_801BB4C0(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A34);
        self->animCurFrame = 0;
        self->zPriority = 0x49;
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleY = self->scaleX;
        self->ext.fish.timer = delays[Random() & 7];
        if (self->scaleX < 0x100) {
            self->zPriority -= 4;
        }
        break;
    case 1:
        if (!--self->ext.fish.timer) {
            self->step++;
            return;
        }
        break;
    case 2:
        if (!AnimateEntity(D_us_801814E0, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
