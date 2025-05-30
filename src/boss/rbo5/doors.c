// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

// hit during enter sequence
extern s32 D_us_801805B8;
extern s32 g_stone_flag;
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

void func_us_801B3690(Entity* self) {
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
            dop =
                AllocEntity(g_Entities + 224, g_Entities + TOTAL_ENTITY_COUNT);
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
        dop = AllocEntity(g_Entities + 160, g_Entities + 192);
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

extern EInit D_us_8018046C;
extern s16 D_us_801805C0[];
extern s16 D_us_801805CC[];
extern s16 D_us_801805D8[];
extern u8 D_us_801805E4[];
extern u8 D_us_801805EC[];
extern u8 D_us_801805F4[];
extern u8 D_us_801805FC[];

void func_us_801B3B0C(Entity* self) {
    s32 flag;
    s32 primIndex;
    s16 xOffset, yOffset;
    s16 magnitude;
    Entity* tempEntity;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018046C);
        self->drawFlags |= FLAG_DRAW_OPACITY | FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY |
                           FLAG_DRAW_ROTX;
        if ((self->params & 0xF) > 1) {
            self->opacity = 0x20;
        } else {
            self->opacity = 0x80;
        }
        self->rotX = D_us_801805D8[self->params & 0xF];
        self->rotY = self->rotX;
        if ((self->params & 0xF) % 2) {
            self->rotZ = -0x400;
        } else {
            self->rotZ = 0;
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
            if (self->palette > 0x8058) {
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
        magnitude = self->ext.et_801BDA0C.unk80 / 0x10000;
        xOffset = (rcos(self->rotZ - 0x400) * magnitude) >> 0xC;
        yOffset = (rsin(self->rotZ - 0x400) * magnitude) >> 0xC;
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
        xOffset = (rcos(self->rotZ - 0x400) * magnitude) >> 0xC;
        yOffset = (rsin(self->rotZ - 0x400) * magnitude) >> 0xC;
        prim = self->ext.et_801BDA0C.unk7C;
        self->posX.i.hi = prim->x0 + xOffset;
        self->posY.i.hi = prim->y0 + yOffset;
        if (self->params & 0x100) {
            AnimateEntity(D_us_801805FC, self);
        } else {
            AnimateEntity(D_us_801805F4, self);
        }
        self->rotZ += D_us_801805CC[self->params & 0xF];
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

extern EInit D_us_8018046C;
extern u8 D_us_801805E4[];
extern u8 D_us_801805EC[];

void func_us_801B40A8(Entity* self) {
    s32 offsetX;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018046C);
        self->rotZ = -0x400;
        self->drawFlags |= FLAG_DRAW_ROTZ;
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

// light effects
INCLUDE_ASM("boss/rbo5/nonmatchings/doors", func_us_801B4210);

extern s16 D_us_80180644[];
extern s16 D_us_8018066C[];
extern s16 D_us_80180658[];

void func_us_801B4A30(Entity* self) {
    s32 primIndex;
    s16 rotZ;
    s16 rotY;
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
                prim->r0 = prim->g0 = prim->b0 = 0x10;
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
            PGREY(lastPrim, 0) = 0xFF;
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
        SetGeomScreen(0x100);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        for (i = 0; i < 8; i++) {
            rotY = 0x280;
            rotZ = *zPointer;
            RotMatrix(&rot, &m);
            RotMatrixY(rotY, &m);
            RotMatrixZ(rotZ, &m);
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
                    &p0, &p1, &p2, &p3, (long*)(&prim->x0), (long*)(&prim->x1),
                    (long*)(&prim->x2), (long*)(&prim->x3), &p, &flag);
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

extern s16 D_us_80180680[];
extern s16 D_us_80180694[];
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

INCLUDE_ASM("boss/rbo5/nonmatchings/doors", func_us_801B5070);
