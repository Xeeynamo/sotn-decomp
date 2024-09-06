// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

static SVECTOR D_80155EFC = {-8, -72, -4, 0};
static SVECTOR D_80155F04 = {8, -72, -4, 0};
static SVECTOR D_80155F0C = {-48, -32, -4, 0};
static SVECTOR D_80155F14 = {-8, -32, -4, 0};
static SVECTOR D_80155F1C = {8, -32, -4, 0};
static SVECTOR D_80155F24 = {48, -32, -4, 0};
static SVECTOR D_80155F2C = {-48, -16, -4, 0};
static SVECTOR D_80155F34 = {-8, -16, -4, 0};
static SVECTOR D_80155F3C = {8, -16, -4, 0};
static SVECTOR D_80155F44 = {48, -16, -4, 0};
static SVECTOR D_80155F4C = {-8, 72, -4, 0};
static SVECTOR D_80155F54 = {8, 72, -4, 0};
static SVECTOR D_80155F5C = {-24, -48, -4, 0};
static SVECTOR D_80155F64 = {-8, -48, -4, 0};
static SVECTOR D_80155F6C = {8, -48, -4, 0};
static SVECTOR D_80155F74 = {24, -48, -4, 0};
static SVECTOR D_80155F7C = {-24, -32, -4, 0};
static SVECTOR D_80155F84 = {24, -32, -4, 0};
static SVECTOR D_80155F8C = {-24, -16, -4, 0};
static SVECTOR D_80155F94 = {24, -16, -4, 0};
static SVECTOR D_80155F9C = {-24, 0, -4, 0};
static SVECTOR D_80155FA4 = {-8, 0, -4, 0};
static SVECTOR D_80155FAC = {8, 0, -4, 0};
static SVECTOR D_80155FB4 = {24, 0, -4, 0};
static SVECTOR D_80155FBC = {-8, -72, 4, 0};
static SVECTOR D_80155FC4 = {8, -72, 4, 0};
static SVECTOR D_80155FCC = {-48, -32, 4, 0};
static SVECTOR D_80155FD4 = {-8, -32, 4, 0};
static SVECTOR D_80155FDC = {8, -32, 4, 0};
static SVECTOR D_80155FE4 = {48, -32, 4, 0};
static SVECTOR D_80155FEC = {-48, -16, 4, 0};
static SVECTOR D_80155FF4 = {-8, -16, 4, 0};
static SVECTOR D_80155FFC = {8, -16, 4, 0};
static SVECTOR D_80156004 = {48, -16, 4, 0};
static SVECTOR D_8015600C = {-8, 72, 4, 0};
static SVECTOR D_80156014 = {8, 72, 4, 0};
static SVECTOR D_8015601C = {-24, -48, 4, 0};
static SVECTOR D_80156024 = {-8, -48, 4, 0};
static SVECTOR D_8015602C = {8, -48, 4, 0};
static SVECTOR D_80156034 = {24, -48, 4, 0};
static SVECTOR D_8015603C = {-24, -32, 4, 0};
static SVECTOR D_80156044 = {24, -32, 4, 0};
static SVECTOR D_8015604C = {-24, -16, 4, 0};
static SVECTOR D_80156054 = {24, -16, 4, 0};
static SVECTOR D_8015605C = {-24, 0, 4, 0};
static SVECTOR D_80156064 = {-8, 0, 4, 0};
static SVECTOR D_8015606C = {8, 0, 4, 0};
static SVECTOR D_80156074 = {24, 0, 4, 0};
static SVECTOR* D_8015607C[][4] = {
    &D_80155F14, &D_80155F1C, &D_80155F3C, &D_80155F34, &D_8015601C,
    &D_80156024, &D_80155FD4, &D_8015603C, &D_8015602C, &D_80156034,
    &D_80156044, &D_80155FDC, &D_8015604C, &D_80155FF4, &D_80156064,
    &D_8015605C, &D_80155FFC, &D_80156054, &D_80156074, &D_8015606C,
    &D_80155FD4, &D_80156024, &D_8015601C, &D_8015603C, &D_80156044,
    &D_80156034, &D_8015602C, &D_80155FDC, &D_80156064, &D_80155FF4,
    &D_8015604C, &D_8015605C, &D_80156074, &D_80156054, &D_80155FFC,
    &D_8015606C, &D_80155FDC, &D_8015602C, &D_80156024, &D_80155FD4,
    &D_80155FF4, &D_80155FD4, &D_8015603C, &D_8015604C, &D_80156054,
    &D_80156044, &D_80155FDC, &D_80155FFC, &D_8015606C, &D_80155FFC,
    &D_80155FF4, &D_80156064, &D_80155FFC, &D_80155FDC, &D_80155FD4,
    &D_80155FF4, &D_80155F04, &D_80155FC4, &D_8015602C, &D_80155F6C,
    &D_80155F6C, &D_8015602C, &D_80155FDC, &D_80155F1C, &D_80155F3C,
    &D_80155FFC, &D_8015606C, &D_80155FAC, &D_80155FAC, &D_8015606C,
    &D_80156014, &D_80155F54, &D_8015603C, &D_80155FD4, &D_80155F14,
    &D_80155F7C, &D_80155FDC, &D_80156044, &D_80155F84, &D_80155F1C,
    &D_8015602C, &D_80155FC4, &D_80155FBC, &D_80156024, &D_8015604C,
    &D_8015603C, &D_80155FCC, &D_80155FEC, &D_80156004, &D_80155FE4,
    &D_80156044, &D_80156054, &D_80156014, &D_8015606C, &D_80156064,
    &D_8015600C, &D_80156024, &D_80155FBC, &D_80155EFC, &D_80155F64,
    &D_80155FD4, &D_80156024, &D_80155F64, &D_80155F14, &D_80156064,
    &D_80155FF4, &D_80155F34, &D_80155FA4, &D_8015600C, &D_80156064,
    &D_80155FA4, &D_80155F4C, &D_80155F34, &D_80155FF4, &D_8015604C,
    &D_80155F8C, &D_80155F94, &D_80156054, &D_80155FFC, &D_80155F3C,
    &D_80155F34, &D_80155F3C, &D_80155FAC, &D_80155FA4, &D_80155FA4,
    &D_80155FAC, &D_80155F54, &D_80155F4C, &D_80155EFC, &D_80155F04,
    &D_80155F6C, &D_80155F64, &D_80155F64, &D_80155F6C, &D_80155F1C,
    &D_80155F14, &D_80155F24, &D_80155FE4, &D_80156004, &D_80155F44,
    &D_80155FBC, &D_80155FC4, &D_80155F04, &D_80155EFC, &D_80155FEC,
    &D_80155FCC, &D_80155F0C, &D_80155F2C, &D_80155F54, &D_80156014,
    &D_8015600C, &D_80155F4C, &D_80155FCC, &D_8015603C, &D_80155F7C,
    &D_80155F0C, &D_80155F8C, &D_8015604C, &D_80155FEC, &D_80155F2C,
    &D_80156044, &D_80155FE4, &D_80155F24, &D_80155F84, &D_80155F44,
    &D_80156004, &D_80156054, &D_80155F94, &D_80155F7C, &D_80155F14,
    &D_80155F34, &D_80155F8C, &D_80155F1C, &D_80155F84, &D_80155F94,
    &D_80155F3C, &D_80155F0C, &D_80155F7C, &D_80155F8C, &D_80155F2C,
    &D_80155F84, &D_80155F24, &D_80155F44, &D_80155F94};
static u8 D_8015635C[][5] = {
    {0x38, 0x08, 0x10, 0x10, 0x0D}, {0x58, 0x08, 0x10, 0x10, 0x0E},
    {0x58, 0x08, 0x10, 0x10, 0x1E}, {0x58, 0x08, 0x10, 0x10, 0x2E},
    {0x58, 0x08, 0x10, 0x10, 0x3E}, {0x58, 0x08, 0x10, 0x10, 0x4E},
    {0x58, 0x08, 0x10, 0x10, 0x5E}, {0x58, 0x08, 0x10, 0x10, 0x6E},
    {0x58, 0x08, 0x10, 0x10, 0x7E}, {0x68, 0x08, 0x10, 0x10, 0x4E},
    {0x68, 0x08, 0x10, 0x10, 0x2E}, {0x68, 0x08, 0x10, 0x10, 0x0E},
    {0x68, 0x08, 0x10, 0x10, 0x6E}, {0x68, 0x18, 0x10, 0x10, 0x4E},
    {0x68, 0x30, 0x10, 0x10, 0x0E}, {0x68, 0x30, 0x10, 0x10, 0x0E},
    {0x68, 0x30, 0x10, 0x10, 0x0E}, {0x68, 0x30, 0x10, 0x10, 0x0E},
    {0x68, 0x30, 0x10, 0x10, 0x0E}, {0x68, 0x30, 0x10, 0x10, 0x0E},
    {0x68, 0x30, 0x10, 0x10, 0x4E}, {0x68, 0x30, 0x10, 0x10, 0x4E},
    {0x68, 0x30, 0x10, 0x10, 0x4E}, {0x68, 0x30, 0x10, 0x10, 0x4E},
    {0x68, 0x30, 0x10, 0x10, 0x4E}, {0x68, 0x30, 0x10, 0x10, 0x4E},
    {0x68, 0x30, 0x10, 0x10, 0x4E}, {0x68, 0x30, 0x10, 0x10, 0x4E},
    {0x68, 0x30, 0x10, 0x10, 0x4E}, {0x68, 0x30, 0x10, 0x10, 0x4E},
    {0x38, 0x18, 0x10, 0x10, 0x0F}, {0x38, 0x28, 0x10, 0x48, 0x0F},
    {0x50, 0x20, 0x10, 0x18, 0x0F}, {0x50, 0x38, 0x10, 0x10, 0x0F},
    {0x70, 0x48, 0x08, 0x08, 0x0F}, {0x70, 0x48, 0x08, 0x08, 0x0F},
    {0x70, 0x48, 0x08, 0x08, 0x4F}, {0x70, 0x48, 0x08, 0x08, 0x4F},
    {0x50, 0x50, 0x18, 0x08, 0x0F}, {0x50, 0x50, 0x18, 0x08, 0x4F},
    {0x50, 0x50, 0x18, 0x08, 0x1F}, {0x50, 0x50, 0x18, 0x08, 0x5F},
    {0x68, 0x58, 0x10, 0x10, 0x0F}, {0x68, 0x58, 0x10, 0x10, 0x1F},
    {0x50, 0x58, 0x18, 0x10, 0x0F}, {0x50, 0x58, 0x18, 0x10, 0x1F}};
static const SVECTOR D_80156C50 = {0, 0, 0};
static const SVECTOR D_80156C58 = {-96, 0, 0};
void RicEntityCrashCrossBeam(Entity* self) {
    MATRIX m;
    SVECTOR rot;
    VECTOR trans1;
    SVECTOR pos;
    SVECTOR sp50;
    s32 z;
    s32 nclip;
    Primitive* prim;
    s32 temp_v1;
    s32 i;
    u8* primUVCoords;
    SVECTOR* temp_a3;
    SVECTOR** vectors_ptr;
    u16 priority;

    pos = D_80156C50;
    sp50 = D_80156C58;
    if (self->step == 0) {
        self->primIndex = g_api.func_800EDB58(PRIM_GT4, LEN(D_8015635C));
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->tpage = 0x1C;
            prim->drawMode = 0x100 | DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.giantcross.subweaponId = PL_W_CRASH_CROSS_BEAM;
        RicSetSubweaponParams(self);
        self->hitboxHeight = 0x50;
        self->hitboxWidth = 0xC;
        self->posY.i.hi = 0x160;
        self->velocityY = FIX(-6.0);
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->facingLeft = 0;
        self->ext.giantcross.unk7C = 0;
        self->ext.giantcross.unk7E = 0x400;
        g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
        self->step++;
        primUVCoords = &D_8015635C[0];
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < LEN(D_8015635C); i++, prim = prim->next,
            primUVCoords += 5) {
            prim->clut = (primUVCoords[4] & 0xF) | 0x1A0;
            switch (primUVCoords[4] & 0xF0) {
            case 0x10:
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x20:
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1];
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1];
                break;
            case 0x30:
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1];
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1];
                break;
            case 0x40:
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x50:
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x60:
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1];
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1];
                break;
            case 0x70:
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1];
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1];
                break;
            default:
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                break;
            }
        }
        return;
    }
    if (self->posY.i.hi < -0x40) {
        DestroyEntity(self);
        return;
    }
    if (self->posY.i.hi < 0) {
        self->velocityY -= FIX(0.5);
    }
    self->posY.val += self->velocityY;
    self->ext.giantcross.unk7C += 0x60;
    self->ext.giantcross.unk7E += 0x60;
    trans1.vx = -(rcos(self->ext.giantcross.unk7C) * 0x60) >> 0xC;
    trans1.vy = self->posY.i.hi - 0x80;
    trans1.vz = ((rsin(self->ext.giantcross.unk7C) * 0x60) >> 0xC) + 0x180;
    rot.vy = self->ext.giantcross.unk7E;
    rot.vz = 0x40;
    rot.vx = 0;

    SetGeomOffset(self->posX.i.hi, 120);
    gte_SetGeomScreen(320);
    RotMatrix(&rot, &m);
    TransMatrix(&m, &trans1);
    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);
    gte_ldv0(&pos);
    gte_rtps();
    prim = &g_PrimBuf[self->primIndex];
    vectors_ptr = &D_8015607C;
    gte_stsxy2(&prim->x0);
    gte_stszotz(&z);
    self->hitboxOffX = prim->x0 - self->posX.i.hi;
    self->hitboxOffY = prim->y0 - self->posY.i.hi;
    for (i = 0; i < LEN(D_8015635C); i++, prim = prim->next, vectors_ptr += 4) {
        gte_ldv3(vectors_ptr[0], vectors_ptr[1], vectors_ptr[3]);
        gte_rtpt();
        temp_a3 = vectors_ptr[2];
        prim->type = 4;
        gte_nclip();
        prim->drawMode = 8;
        gte_stopz(&nclip);
        if (nclip < 0) {
            continue;
        }
        gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);
        gte_ldv0(temp_a3);
        gte_rtps();
        prim->drawMode = DRAW_DEFAULT;
        if (z < 16) {
            priority = 0x1F6;
        } else if (z >= 999) {
            priority = 0x10;
        } else {
            priority = 0x120;
            priority -= z;
        }
        prim->priority = priority;
        gte_stsxy(&prim->x3);
    }
}
