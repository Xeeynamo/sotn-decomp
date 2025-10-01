// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

u16 D_us_801805B0 = 0;
STATIC_PAD_DATA(4);
s32 D_us_801805B8 = 0;
s32 g_stone_flag = 0;

extern s32 D_us_801D43C0;
extern s32 D_us_801D43C4;
extern EInit g_EInitInteractable;

#ifdef VERSION_PSP
extern s32 D_pspeu_0926BCC8;
extern s32 D_pspeu_0926BCB8;
extern s32 D_pspeu_0926BCB0;
extern s32 D_pspeu_0926BCA0;
extern s32 D_pspeu_0926BC98;
#define E_ID(ID_17) D_pspeu_0926BCC8
#define E_ID(ID_19) D_pspeu_0926BCB8
#define E_ID(ID_1A) D_pspeu_0926BCB0
#define E_ID(ID_1C) D_pspeu_0926BCA0
#define E_ID(ID_1D) D_pspeu_0926BC98
#endif

// hit during enter sequence
void EntityUnkId18(Entity* self) {
    s32 i;
    Entity* dop;
    Entity* entity;
    s32 offsetX;
    s32 offsetY;
    s32 tangent;
    s16 angle;

    FntPrint("pl_demo_timer:%02x\n", g_Player.demo_timer);
    FntPrint("step:%02x\n", self->step);

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);

        self->animSet = 0;
        self->animCurFrame = 0;
        entity = self + 1;

        for (i = 1; i < 6; i++) {
            CreateEntityFromEntity(E_ID(ID_17), self, entity);
            entity->params = i + 0x100;
            entity++;
            CreateEntityFromEntity(E_ID(ID_17), self, entity);
            entity->params = i;
            entity++;
        };
        CreateEntityFromEntity(E_ID(ID_19), self, entity);
        entity++;
        CreateEntityFromEntity(E_ID(ID_1A), self, entity);
        break;

    case 1:
        if (GetDistanceToPlayerX() < 64) {
            g_Player.demo_timer = 2;
            if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
#ifdef VERSION_PSP
                g_Player.padSim = PAD_NONE;
#else
                g_Player.padSim = PAD_L1;
#endif
            } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
#ifdef VERSION_PSP
                g_Player.padSim = PAD_L1;
#else
                g_Player.padSim = PAD_R2;
#endif
            } else if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                g_Player.padSim = PAD_R1;
            } else {
                g_Player.demo_timer = 0x240;
                g_Player.padSim = 0;
                self->step = 3;
            }
        }
        break;

    case 2:
        if (!--self->ext.unkDoor.unk9C) {
            self->step++;
        }
        break;

    case 3:
        entity = self + 1;
        entity->ext.unkDoor.unk84 = 1;
        entity++;
        entity->ext.unkDoor.unk84 = 1;
        self->step++;
        break;

    case 4:
        if (D_us_801805B8 & 2) {
            // BUG! Sets Doppleganger 10 defeat flag instead of Doppleganger 40
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_DOPPLEGANGER_10_DEFEAT, TIMEATTACK_SET_RECORD);
            self->step++;
        }
        break;

    case 5:
        if (g_stone_flag == 0) {
            dop = &DOPPLEGANGER;
            offsetX = self->posX.i.hi - dop->posX.i.hi;
            offsetY = self->posY.i.hi - dop->posY.i.hi;
            angle = ratan2(-offsetY, offsetX);
            dop->posX.val += rcos(angle) << 4;
            dop->posY.val -= rsin(angle) << 4;

            tangent = (offsetX * offsetX) + (offsetY * offsetY);
            tangent = SquareRoot0(tangent);
            if (tangent < 8) {
                self->step++;
            }
        } else if (g_stone_flag == 2) {
            self->step++;
        }
        break;

    case 6:
        dop = &DOPPLEGANGER;
        dop->zPriority = 0x56;
        if (D_us_801805B8 & 4) {
            g_api.PlaySfx(SET_UNK_92);
#ifdef VERSION_PSP
            D_80097910 = 0x313;
#endif
            self->step++;
        }
        break;

    case 7:
        offsetX = 0x100 - g_Tilemap.scrollX.i.hi;
        offsetY = 0x80 - g_Tilemap.scrollY.i.hi;
        for (i = 0; i < 2; i++) {
            dop = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (dop != NULL) {
                CreateEntityFromCurrentEntity(E_ID(ID_1C), dop);
                dop->posX.i.hi = offsetX - 64 + (i * 128);
                dop->posY.i.hi = offsetY;
                dop->params = i;
            }
        }
        self->ext.unkDoor.unk9C = 0xC0;
        self->step++;
        break;

    case 8:
        if (!--self->ext.unkDoor.unk9C) {
            self->step++;
        }
        break;

    case 9:
        dop = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (dop != NULL) {
            CreateEntityFromEntity(E_ID(ID_1D), self, dop);
            dop->posX.i.hi = 0x100 - g_Tilemap.scrollX.i.hi;
            dop->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
            dop->params = 4;
            self->step++;
        }
        break;

    case 10:
#ifdef VERSION_PSP
        self->step++;
        break;
    case 11:
#endif
        break;
    }

#ifndef VERSION_PSP
    FntPrint("stone_flag:%02x\n", g_stone_flag);
#endif
    g_stone_flag = 0;
    D_us_801D43C0 = self->posX.i.hi;
    D_us_801D43C4 = self->posY.i.hi;
}

extern EInit EInitUnk17;
static s16 D_us_801805C0[] = {
    0x80, 0x80, 0x100, 0x300, 0x500, 0x700,
};
static s16 D_us_801805CC[] = {
    0xC, 0xC, 0x12, 0x16, 0x20, 0x26,
};
static s16 D_us_801805D8[] = {
    0x100, 0x100, 0xF8, 0xF2, 0xEE, 0xEC,
};
static u8 D_us_801805E4[] = {1, 0x62, 0x1, 0x63, 0};
static u8 D_us_801805EC[] = {1, 0x64, 0x1, 0x65, 0};
static u8 D_us_801805F4[] = {2, 0x62, 0x2, 0x63, 0};
static u8 D_us_801805FC[] = {2, 0x64, 0x2, 0x65, 0};

void EntityUnkId17(Entity* self) {
    s32 flag;
    s32 primIndex;
    s16 xOffset, yOffset;
    s16 magnitude;
    Entity* tempEntity;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(EInitUnk17);
        self->drawFlags |= FLAG_DRAW_OPACITY | FLAG_DRAW_ROTATE |
                           FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        if ((self->params & 0xF) > 1) {
            self->opacity = 0x20;
        } else {
            self->opacity = 0x80;
        }
        self->scaleX = D_us_801805D8[self->params & 0xF];
        self->scaleY = self->scaleX;
        if ((self->params & 0xF) % 2) {
            self->rotate = -0x400;
        } else {
            self->rotate = 0;
        }
        self->zPriority = (0x40 - self->params) & 0xF;
        if (self->params & 0x100) {
            self->animCurFrame = 0x64;
        } else {
            self->animCurFrame = 0x62;
        }
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BDA0C.unk7C = prim;
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        } else {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801BDA0C.unk84 = 0;
        self->ext.et_801BDA0C.unk80 = 0;
        break;
    case 1:
        self->palette = PAL_OVL(0x4F);
        if (self->ext.et_801BDA0C.unk84) {
            self->ext.et_801BDA0C.unk9C = 64;
            self->step++;
        }
        break;

    case 2:
        flag = self->params & 0xFF;
        if (flag != 1) {
            self->step++;
        } else {
            if (self->params & 0x100) {
                AnimateEntity(D_us_801805EC, self);
            } else {
                AnimateEntity(D_us_801805E4, self);
            }
            if ((g_Timer & 0xF) == 0) {
                g_api.PlaySfx(SFX_STONE_MOVE_B);
            }
            if (!--self->ext.et_801BDA0C.unk9C) {
                self->step++;
            }
        }
        break;

    case 3:
        if (g_Timer % 2 == 0) {
            self->palette++;
            if (self->palette > PAL_OVL(0x58)) {
                g_api.PlaySfx(SFX_ELECTRICITY);
                self->palette = PAL_OVL(0x4F);
                self->step++;
                if (self->params == 5) {
                    (self + 1)->ext.et_801BDA0C.unk84 = 1;
                }
            }
        }
        break;

    case 4:
        magnitude = self->ext.et_801BDA0C.unk80 / FIX(1);
        xOffset = (rcos(self->rotate - 0x400) * magnitude) >> 0xC;
        yOffset = (rsin(self->rotate - 0x400) * magnitude) >> 0xC;
        prim = self->ext.et_801BDA0C.unk7C;
        self->posX.i.hi = prim->x0 + xOffset;
        self->posY.i.hi = prim->y0 + yOffset;
        if (self->params & 0x100) {
            AnimateEntity(D_us_801805EC, self);
        } else {
            AnimateEntity(D_us_801805E4, self);
        }
        if ((g_Timer & 0xF) == 0) {
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        if (self->params & 0x100) {
            self->ext.et_801BDA0C.unk88 -= D_us_801805C0[self->params & 0xF];
        } else {
            self->ext.et_801BDA0C.unk88 += D_us_801805C0[self->params & 0xF];
        }
        self->ext.et_801BDA0C.unk80 += self->ext.et_801BDA0C.unk88;
        if (abs(self->ext.et_801BDA0C.unk80) > FIX(12)) {
            (self + 2)->ext.et_801BDA0C.unk84 = 1;
            self->step++;
            if (self->params == 5) {
                (self + 1)->ext.et_801BDA0C.unk84 = 1;
            }
        }
        tempEntity = self + 2;
        if (tempEntity->opacity < 0x80) {
            tempEntity->opacity++;
        }
        break;

    case 5:
        tempEntity = self + 2;
        if (tempEntity->opacity < 0x80) {
            tempEntity->opacity += 2;
        }
        magnitude = self->ext.et_801BDA0C.unk80 / 0x10000;
        xOffset = (rcos(self->rotate - 0x400) * magnitude) >> 0xC;
        yOffset = (rsin(self->rotate - 0x400) * magnitude) >> 0xC;
        prim = self->ext.et_801BDA0C.unk7C;
        self->posX.i.hi = prim->x0 + xOffset;
        self->posY.i.hi = prim->y0 + yOffset;
        if (self->params & 0x100) {
            AnimateEntity(D_us_801805FC, self);
        } else {
            AnimateEntity(D_us_801805F4, self);
        }
        self->rotate += D_us_801805CC[self->params & 0xF];
        if (self->params & 0x100) {
            self->ext.et_801BDA0C.unk88 -= D_us_801805C0[self->params & 0xF];
        } else {
            self->ext.et_801BDA0C.unk88 += D_us_801805C0[self->params & 0xF];
        }
        self->ext.et_801BDA0C.unk80 += self->ext.et_801BDA0C.unk88;
        if (self->ext.et_801BDA0C.unk80 > FIX(64)) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityUnkId1C(Entity* self) {
    s32 offsetX;

    switch (self->step) {
    case 0:
        InitializeEntity(EInitUnk17);
        self->rotate = -0x400;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        if (self->params & 1) {
            self->animCurFrame = 0x64;
            self->velocityX = FIX(-0.5);
        } else {
            self->animCurFrame = 0x62;
            self->velocityX = FIX(0.5);
        }
        self->zPriority = 0x5E;
        // fallthrough

    case 1:
        MoveEntity();
        if (self->params & 1) {
            AnimateEntity(D_us_801805EC, self);
        } else {
            AnimateEntity(D_us_801805E4, self);
        }
        offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->velocityX > 0) {
            if (offsetX > DISP_STAGE_W) {
                self->step++;
            }
        } else if (offsetX < DISP_STAGE_W) {
            self->step++;
        }
        break;

    case 2:
        self->posX.i.hi = DISP_STAGE_W - g_Tilemap.scrollX.i.hi;
        if (self->params & 1) {
            self->animCurFrame = 0x64;
        } else {
            self->animCurFrame = 0x62;
        }
        break;
    }
}

static s32 D_us_80180604[] = {
    FLT(0),    FLT(0.125), FLT(0.25), FLT(0.375), FLT(0.5),  FLT(0.625),
    FLT(0.75), FLT(0.875), FLT(1),    FLT(1.125), FLT(1.25), FLT(1.375),
    FLT(1.5),  FLT(1.625), FLT(1.75), FLT(1.875),
};
static s32 D_us_801D26D4;
static s32 D_us_801D26D8;
static s32 D_us_801D26DC;

void EntityUnkId19(Entity* self) {
    Primitive* prim;
    Primitive* lastPrim;
    s32 primIndex;
    s32 i;
    s32 angle;
    s32 moveX;
    s32 moveY;

    s16 xOffset;
    s16 posX;
    s16 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        break;

    case 1:
        if (self->ext.et_801BE2C8.unk84) {
            self->step++;
            self->ext.et_801BE2C8.unk84 = 0;
        }
        break;

    case 2:
        primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 0x30);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->r0 = prim->g0 = prim->b0 = 8;
                prim->priority = 0xD0;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                lastPrim = prim;
                prim = prim->next;
            }
            self->ext.et_801BE2C8.unk80 = lastPrim;
        } else {
            DestroyEntity(self);
            return;
        }
        self->step++;
        break;

    case 3:

        xOffset = (self - 1)->ext.et_801BDA0C.unk80 / FIX(1.0);
        if (xOffset < 0) {
            xOffset = -xOffset;
        }

        posX = self->posX.i.hi;
        posY = self->posY.i.hi - 0x28;
        prim = self->ext.prim;
        for (i = 0; i < 32; i++) {
            prim->x0 = posX - xOffset - 0x20 + i;
            prim->y0 = posY - 0x20 + i;
            prim->u0 = xOffset * 2 + 0x40 - i * 2;
            prim->v0 = 0x94 - i * 2;
            prim = prim->next;
        }

        while (prim != NULL) {
            prim->x0 = posX - xOffset;
            prim->y0 = posY;
            prim->u0 = xOffset * 2;
            prim->v0 = 0x54;
            prim = prim->next;
        }

        lastPrim = self->ext.et_801BE2C8.unk80;
        if (self->ext.et_801BE2C8.unk84) {
            lastPrim->x0 = 0;
            lastPrim->y0 = 0;
            lastPrim->u0 = 0xFF;
            lastPrim->v0 = 0xFF;
            if (lastPrim->r0 < 248) {
                lastPrim->r0 += 8;
                lastPrim->g0 = lastPrim->b0 = lastPrim->r0;
            } else {
                (self + 1)->ext.et_801BE2C8.unk84 = 1;
                self->step++;
            }
        }
        break;

    case 4:
        prim = self->ext.prim;
        prim->type = PRIM_TILE;
        prim->r0 = prim->b0 = prim->g0 = 0xFF;
        prim->priority = 0x40;
        prim = prim->next;

        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        prim = self->ext.et_801BE2C8.unk80;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        CreateEntityFromEntity(E_ID_16, self, &DOPPLEGANGER);
        // BUG! Sets Doppleganger 10 defeat flag instead of Doppleganger 40
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_DOPPLEGANGER_10_DEFEAT, TIMEATTACK_SET_VISITED);
        (self + 1)->ext.et_801BE2C8.unk84 = 1;
        self->step++;
        break;

    case 5:
        lastPrim = self->ext.et_801BE2C8.unk80;

        if (lastPrim->r0 > 8) {
            lastPrim->r0 -= 8;
            lastPrim->g0 = lastPrim->b0 = lastPrim->r0;
            break;
        }
        g_api.FreePrimitives(self->primIndex);
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x10);
        if (primIndex == -1) {
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        moveY = self->posY.i.hi;
        moveX = self->posX.i.hi;

        for (i = 0; i < 16; i++) {
            angle = i << 8;
            prim->x0 = moveX + (((rcos(angle) >> 4) * 64) >> 8);
            prim->y0 = moveY - (((rsin(angle) >> 4) * 64) >> 8);
            prim->u0 = 32 + (((rcos(angle) >> 4) * 0x1E) >> 8);
            prim->v0 = 0xE0 - (((rsin(angle) >> 4) * 0x1E) >> 8);

            angle = (i + 1) << 8;
            prim->x1 = moveX + (((rcos(angle) >> 4) * 64) >> 8);
            prim->y1 = moveY - (((rsin(angle) >> 4) * 64) >> 8);
            prim->u1 = 32 + (((rcos(angle) >> 4) * 0x1E) >> 8);
            prim->v1 = 0xE0 - (((rsin(angle) >> 4) * 0x1E) >> 8);

            prim->y2 = prim->y3 = moveY;
            prim->x2 = prim->x3 = moveX;
            prim->u2 = prim->u3 = 0x20;
            prim->v2 = prim->v3 = 0xE0;

            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            prim->priority = 0x40;
            prim->drawMode = DRAW_UNK_400 | DRAW_COLORS | DRAW_UNK02;
            prim = prim->next;
        }
        D_us_801D26D4 = 0x100;
        self->step++;
    case 6:
        // same as the warp room background
        D_us_801D26D8 += 16;
        D_us_801D26DC = (rsin(D_us_801D26D8) >> 8) + 0xD0;
        if (D_us_801D26DC < 0) {
            D_us_801D26DC = 0;
        }
        if (D_us_801D26DC > 0xFF) {
            D_us_801D26DC = 0xFF;
        }

        D_us_801D26D4 = (rcos(D_us_801D26D8) >> 8) + 0xD0;

        prim = self->ext.prim;

        for (i = 0; i < 16; i++) {
            angle = D_us_80180604[(i + 0) % 16];
            prim->r0 =
                ((rsin(angle) + FIX(1.0 / 16)) >> 6) * D_us_801D26D4 / 256;
            angle = D_us_80180604[(i + 5) % 16];
            prim->g0 =
                ((rsin(angle) + FIX(1.0 / 16)) >> 6) * D_us_801D26D4 / 256;
            angle = D_us_80180604[(i + 10) % 16];
            prim->b0 =
                ((rsin(angle) + FIX(1.0 / 16)) >> 6) * D_us_801D26D4 / 256;
            angle = D_us_80180604[(i + 1) % 16];
            prim->r1 =
                ((rsin(angle) + FIX(1.0 / 16)) >> 6) * D_us_801D26D4 / 256;
            angle = D_us_80180604[(i + 6) % 16];
            prim->g1 =
                ((rsin(angle) + FIX(1.0 / 16)) >> 6) * D_us_801D26D4 / 256;
            angle = D_us_80180604[(i + 11) % 16];
            prim->b1 =
                ((rsin(angle) + FIX(1.0 / 16)) >> 6) * D_us_801D26D4 / 256;

            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                D_us_801D26DC;

            D_us_80180604[i] += 32;
            prim = prim->next;
        }
        break;
    }
}

static s16 D_us_80180644[] = {
    0x0000, 0x0600, 0x0E00, 0x0100, 0x0800, 0x0A00, 0x0200, 0x0400, 0x0C00, 0,
};
static s16 D_us_80180658[] = {
    4, 8, 13, -0x18, -0x14, -12, 21, -12, 2, 0,
};
static s16 D_us_8018066C[] = {
    20, 8, 12, 13, 16, 6, 12, 16, 8, 4,
};

void EntityUnkId1A(Entity* self) {
    s32 primIndex;
    s16 rotate;
    s16 scaleY;
    long p, flag;
    SVECTOR p0, p1, p2, p3;
    u8 pad[4];
    VECTOR trans;
    MATRIX m;
    Primitive* lastPrim;
    Primitive* prim;
    s16 t;
    s16 iter;
    s32 i, j;
    s16* zPointer;
    s16 posX, posY; // unused

    SVECTOR rot = {0};

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        break;

    case 1:
        if (self->ext.et_801BE2C8.unk84) {
            self->step++;
        }
        break;

    case 2:
        self->ext.et_801BE2C8.unk84 = 0;
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x180);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BE2C8.unk7C = prim;
            while (prim != NULL) {
                prim->tpage = 0x1A;
                prim->clut = 0x15F;
                prim->u0 = prim->u2 = 0x20;
                prim->u1 = prim->u3 = 0x28;
                prim->v0 = prim->v1 = 0xA0;
                prim->v2 = prim->v3 = 0xA8;
                prim->r0 = prim->g0 = prim->b0 = 16;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = 0xD0;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
                lastPrim = prim;
                prim = prim->next;
            }
            self->ext.et_801BE2C8.unk80 = lastPrim;
            lastPrim->x0 = lastPrim->x2 = 0;
            lastPrim->x1 = lastPrim->x3 = 0;
            lastPrim->y0 = lastPrim->y1 = 0;
            lastPrim->y2 = lastPrim->y3 = 0;
            PGREY(lastPrim, 0) = 255;
            LOW(lastPrim->r1) = LOW(lastPrim->r0);
            LOW(lastPrim->r2) = LOW(lastPrim->r0);
            LOW(lastPrim->r3) = LOW(lastPrim->r0);
            lastPrim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
        } else {
            DestroyEntity(self);
            return;
        }
        zPointer = self->ext.et_801BE2C8.unk88;
        for (i = 0; i < 8; i++) {
            *zPointer = D_us_80180644[i];
            zPointer++;
        }
        self->ext.et_801BE2C8.unkA0 = 0;
        g_api.PlaySfx(SFX_RBO5_UNK_7AE);
        self->step++;
        break;

    case 3:
        iter = 0;
        zPointer = self->ext.et_801BE2C8.unk88;
        prim = self->ext.et_801BE2C8.unk7C;
        SetGeomScreen(DISP_STAGE_W);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        for (i = 0; i < 8; i++) {
            scaleY = 0x280;
            rotate = *zPointer;
            RotMatrix(&rot, &m);
            RotMatrixY(scaleY, &m);
            RotMatrixZ(rotate, &m);
            trans.vx = 0;
            trans.vy = 0;
            trans.vz = 0x140;
            TransMatrix(&m, &trans);
            SetRotMatrix(&m);
            SetTransMatrix(&m);
            t = D_us_8018066C[i] - self->ext.et_801BE2C8.unkA0 / 16;
            if (t < 0) {
                t = 0;
            }
            p0.vx = 0;
            p0.vy = 0 - t;
            p0.vz = 0;

            p1.vx = t - 0;
            p1.vy = 0;
            p1.vz = 0;

            p2.vx = 0 - t;
            p2.vy = 0;
            p2.vz = 0;

            p3.vx = 0;
            p3.vy = t - 0;
            p3.vz = 0;
            for (j = 0; p0.vx < 0xC0; j++, prim = prim->next) {
                if (iter > 0x170) {
                    break;
                }
                RotAverage4(
                    &p0, &p1, &p2, &p3, (long*)&prim->x0, (long*)&prim->x1,
                    (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
                prim->r0 = 0x20 - (i % 3) * 8 - j / 4;
                if (prim->r0 > 0x80) {
                    prim->r0 = 0;
                }
                prim->g0 = 0x20 - (i % 2) * 8 - j / 4;
                if (prim->g0 > 0x80) {
                    prim->g0 = 0;
                }
                prim->b0 = 0x20 - (i % 4) * 8 - j / 4;
                if (prim->b0 > 0x80) {
                    prim->b0 = 0;
                }
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                iter++;
                posX = prim->x0;
                posY = prim->y0;
                p0.vx += 3;
                p1.vx += 3;
                p2.vx += 3;
                p3.vx += 3;
            }
            *zPointer += D_us_80180658[i];
            zPointer++;
        }
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = self->ext.et_801BE2C8.unk80;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        if (self->ext.et_801BE2C8.unk84) {
            self->ext.et_801BE2C8.unkA0 += 4;
        }
        if (self->ext.et_801BE2C8.unkA0 > 0x200) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            DestroyEntity(self);
        }
        if (g_Player.demo_timer == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

static s16 D_us_80180680[] = {
    0x01E0, 0x0061, 0x006E, 0x006F, 0x01FF, 0x01E0,
};

static u8 D_us_8018068C[8] = {
    false, false, true, true, true, false, false, false,
};

static s16 D_us_80180694[] = {
    0x0373, 0x0000, 0x0000, 0x0000, 0x075E, 0x0001, 0x0001, 0x0001,
    0x0000, 0x0000, 0x0000, 0x072D, 0x0001, 0x0001, 0x0001, 0x075D,
    0x0000, 0x0000, 0x0000, 0x03F2, 0x0001, 0x0001, 0x0001, 0x075C,
    0x0000, 0x0000, 0x0000, 0x0375, 0x0001, 0x0001, 0x0001, 0x0765,
    0x0375, 0x0000, 0x0000, 0x0969, 0x0762, 0x0001, 0x0001, 0x0764,
    0x0933, 0x0000, 0x0000, 0x0951, 0x0761, 0x0001, 0x0001, 0x0763,
};

void func_us_801B5004(Tilemap* map, s32 arg1) {
    Tilemap* tmap;
    s16 tilePos;
    u16* tileData;
    s32 i;

    tmap = &g_Tilemap;
    tilePos = D_us_80180680[arg1 >> 1];
    tileData = &D_us_80180694[arg1 << 2];

    i = 0;
    for (i = 0; i < 4; i++) {
        tmap->fg[tilePos] = *tileData++;
        tilePos += tmap->hSize << 4;
    }
}

#ifdef VERSION_PSP
extern s32 D_us_801805B0;
#endif

extern EInit g_EInitCommon;

void EntityUnkId1E(Entity* self) {
    Entity* entity;
    u16 params;
    u16 temp_s1;
    s16 offsetY;

    params = self->params;
    temp_s1 = (D_us_801805B0 & (1 << params));
    params <<= 1;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(15);
        self->animCurFrame = 0x25;
        self->facingLeft = D_us_8018068C[params >> 1];
        self->zPriority = 0x9E;
        if (temp_s1) {
            func_us_801B5004((Tilemap*)self, params + 1);
            self->step = 4;
            break;
        }
        func_us_801B5004((Tilemap*)self, params);
        self->posY.i.hi -= 0x48;
        break;
    case 1:
        if (temp_s1) {
            self->step++;
            self->velocityY = FIX(4.0);
        }
        break;
    case 2:
        if (self->facingLeft) {
            self->posX.i.hi += 8;
        } else {
            self->posX.i.hi -= 8;
        }
        GetPlayerCollisionWith(self, 0x10U, 0x20U, 0xBU);
        if (self->facingLeft) {
            self->posX.i.hi -= 8;
        } else {
            self->posX.i.hi += 8;
        }
        MoveEntity();
        offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (offsetY < 128) {
            break;
        }
        g_api.PlaySfxVolPan(SFX_EXPLODE_B, 0x7F, -6);
        func_us_801B5004((Tilemap*)self, params + 1);
        self->velocityY = FIX(-1.0);
        self->step++;
        break;
    case 3:
        self->velocityY += FIX(1.0 / 8);
        MoveEntity();
        offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (offsetY >= 128) {
            self->posY.i.hi = 128 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;
    case 4:
        if (self->params != 1) {
            self->step++;
        }
        D_80097928 = 1;
        D_80097910 = 0x31D;
        self->step++;
        break;
    case 5:
        if (self->params != 1) {
            self->step++;
        } else {
            if (g_api.func_80131F68() == false) {
                D_80097928 = 0;
                g_api.PlaySfx(D_80097910);
                self->step++;
            }
        }
        break;
    case 6:
        if (D_us_801805B8 & 2) {
            if (self->params != 1) {
                self->step++;
            } else {
                // BUG! Sets Doppleganger 10 defeat flag instead of Doppleganger
                // 40
                g_api.TimeAttackController(
                    TIMEATTACK_EVENT_DOPPLEGANGER_10_DEFEAT,
                    TIMEATTACK_SET_RECORD);
                self->step++;
            }
        }
        break;
    case 7:
        if (D_us_801805B8 & 4) {
            if (self->params != 1) {
                self->step++;
            } else {
                g_api.PlaySfx(SET_UNK_92);
                self->step++;
            }
        }
        break;
    case 8:
        if (self->params != 1) {
            self->step++;
        } else {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(ID_1D), self, entity);
                entity->posX.i.hi = 0x80;
                entity->posY.i.hi = 0x70;
                entity->params = 4;
                self->step++;
            }
        }
        break;
    case 9:
        self->step++;
        LOW(D_us_801805B0) = 0;
        break;
    case 10:
        if (!temp_s1) {
            self->step++;
            self->velocityY = FIX(-1);
            // n.b.! first arg should be a Tilemap*
            func_us_801B5004((Tilemap*)self, params);
        }
        break;
    case 11:
        if (self->facingLeft) {
            self->posX.i.hi += 8;
        } else {
            self->posX.i.hi -= 8;
        }
        GetPlayerCollisionWith(self, 0x10U, 0x20U, 0xB);
        if (self->facingLeft) {
            self->posX.i.hi -= 8;
        } else {
            self->posX.i.hi += 8;
        }
        MoveEntity();
        offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (offsetY < 57) {
            self->step++;
        }
        break;
    case 12:
        break;
    }
}
