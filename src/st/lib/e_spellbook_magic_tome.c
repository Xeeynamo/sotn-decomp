// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

static SVECTOR D_us_80182F44 = {4, 0, 16};
static SVECTOR D_us_80182F4C = {0, 0, 16};
static SVECTOR D_us_80182F54 = {4, 28, 16};
static SVECTOR D_us_80182F5C = {0, 28, 16};
static SVECTOR D_us_80182F64 = {0, 0, -16};
static SVECTOR D_us_80182F6C = {4, 0, -16};
static SVECTOR D_us_80182F74 = {0, 28, -16};
static SVECTOR D_us_80182F7C = {4, 28, -16};
static SVECTOR D_us_80182F84 = {0, 0, 16};
static SVECTOR D_us_80182F8C = {-4, 0, 16};
static SVECTOR D_us_80182F94 = {0, 28, 16};
static SVECTOR D_us_80182F9C = {-4, 28, 16};
static SVECTOR D_us_80182FA4 = {-4, 0, -16};
static SVECTOR D_us_80182FAC = {0, 0, -16};
static SVECTOR D_us_80182FB4 = {-4, 28, -16};
static SVECTOR D_us_80182FBC = {0, 28, -16};
static SVECTOR D_us_80182FC4 = {0, 28, 0};
static SVECTOR* D_us_80182FCC[] = {
    &D_us_80182F44, &D_us_80182F54, &D_us_80182F6C, &D_us_80182F7C,
    &D_us_80182F4C, &D_us_80182F44, &D_us_80182F64, &D_us_80182F6C,
    &D_us_80182F54, &D_us_80182F5C, &D_us_80182F7C, &D_us_80182F74,
    &D_us_80182F44, &D_us_80182F4C, &D_us_80182F54, &D_us_80182F5C,
    &D_us_80182F64, &D_us_80182F6C, &D_us_80182F74, &D_us_80182F7C,
    &D_us_80182F5C, &D_us_80182F4C, &D_us_80182F74, &D_us_80182F64,
    &D_us_80182F9C, &D_us_80182F8C, &D_us_80182FB4, &D_us_80182FA4,
    &D_us_80182F8C, &D_us_80182F84, &D_us_80182FA4, &D_us_80182FAC,
    &D_us_80182F94, &D_us_80182F9C, &D_us_80182FBC, &D_us_80182FB4,
    &D_us_80182F84, &D_us_80182F8C, &D_us_80182F94, &D_us_80182F9C,
    &D_us_80182FA4, &D_us_80182FAC, &D_us_80182FB4, &D_us_80182FBC,
    &D_us_80182F84, &D_us_80182F94, &D_us_80182FAC, &D_us_80182FBC};
static u8 D_us_8018308C[] = {0x0A, 0x04, 0x25, 0x23};
static u8 D_us_80183090[] = {0x2A, 0x2C, 0x45, 0x4B};
static u8 D_us_80183094[] = {0x02, 0x04, 0x05, 0x23};
static u8 D_us_80183098[] = {0x4A, 0x2C, 0x4D, 0x4B};
static u8 D_us_8018309C[] = {0x5A, 0x2C, 0x75, 0x4B};
static u8 D_us_801830A0[] = {0x52, 0x54, 0x6D, 0x73};
static u8 D_us_801830A4[] = {0x52, 0x2C, 0x55, 0x4B};
static u8 D_us_801830A8[] = {0x72, 0x54, 0x75, 0x73};
static u8 D_us_801830AC[] = {0x0A, 0x54, 0x2D, 0x73};
static u8 D_us_801830B0[] = {0x2A, 0x54, 0x45, 0x73};
static u8 D_us_801830B4[] = {0x02, 0x54, 0x05, 0x73};
static u8 D_us_801830B8[] = {0x4A, 0x54, 0x4D, 0x73};
static u8 D_us_801830BC[] = {0x52, 0x04, 0x6D, 0x23};
static u8 D_us_801830C0[] = {0x4A, 0x04, 0x4D, 0x23};
static u8 D_us_801830C4[] = {0x02, 0x2C, 0x1D, 0x4B};
static u8 D_us_801830C8[] = {0x22, 0x2C, 0x25, 0x4B};
static u8 D_us_801830CC[] = {0x2A, 0x02, 0x45, 0x05};
static u8 D_us_801830D0[] = {0x2A, 0x0A, 0x45, 0x0D};
static u8 D_us_801830D4[] = {0x2A, 0x12, 0x45, 0x15};
static u8 D_us_801830D8[] = {0x2A, 0x1A, 0x45, 0x1D};
static u8* D_us_801830DC[] = {
    D_us_8018308C, D_us_80183094, D_us_801830C0, D_us_801830C0,
    D_us_801830C0, D_us_801830BC, D_us_80183090, D_us_80183098,
    D_us_801830C8, D_us_801830C8, D_us_801830C8, D_us_801830C4};
static u8* D_us_8018310C[] = {
    D_us_8018309C, D_us_801830A4, D_us_801830C0, D_us_801830C0,
    D_us_801830C0, D_us_801830BC, D_us_801830A0, D_us_801830A8,
    D_us_801830C8, D_us_801830C8, D_us_801830C8, D_us_801830C4};
static u8* unused[] = {
    D_us_801830AC, D_us_801830B4, D_us_801830C0, D_us_801830C0,
    D_us_801830C0, D_us_801830BC, D_us_801830B0, D_us_801830B8,
    D_us_801830C8, D_us_801830C8, D_us_801830C8, D_us_801830C4};
static unkBookStruct D_us_8018316C[] = {
    {&D_us_80180920, 0xF500, 0xF5C0, 0x0024, 0x000E, 0x15},
    {&D_us_80180938, 0xF600, 0xF660, 0x0030, 0x000E, 0x16},
    {&D_us_80180950, 0xF600, 0xF640, 0x001C, 0x0014, 0x17}};

void func_us_801D1BCC(void) {
    SVECTOR rot;
    VECTOR trans;
    MATRIX m;
    SVECTOR** vecPtr;
    Primitive* prim;
    s32 i, j;
    s32* scratchpad1;
    long* scratchpad2;

    SetGeomScreen(0x200);
    SetGeomOffset(g_CurrentEntity->posX.i.hi, g_CurrentEntity->posY.i.hi);
    rot.vx = g_CurrentEntity->ext.spellbookMagicTome.unk9C.vx;
    rot.vy = g_CurrentEntity->ext.spellbookMagicTome.unk9C.vy;
    rot.vz = g_CurrentEntity->ext.spellbookMagicTome.unk9C.vz;
    rot.vz -= g_CurrentEntity->ext.spellbookMagicTome.unk82 / 2;
    RotMatrix(&rot, &m);
    SetRotMatrix(&m);
    trans.vx = 0;
    trans.vy = 0;
    trans.vz = g_CurrentEntity->ext.spellbookMagicTome.unk8A + 0x200;
    TransMatrix(&m, &trans);
    SetTransMatrix(&m);
    scratchpad1 = SPAD(0);
    scratchpad2 = (long*)SPAD(1);
    vecPtr = D_us_80182FCC;
    prim = g_CurrentEntity->ext.spellbookMagicTome.unk7C;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 6; j++) {
            if ((j == 5) && !g_CurrentEntity->ext.spellbookMagicTome.unk82) {
                vecPtr += 4;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            } else {
                gte_ldv3(vecPtr[0], vecPtr[1], vecPtr[2]);
                gte_rtpt();
                if (g_CurrentEntity->palette & PAL_UNK_FLAG) {
                    prim->clut = g_CurrentEntity->palette & 0xFFF;
                } else {
                    prim->clut = g_CurrentEntity->palette;
                    if (j > 1) {
                        prim->clut++;
                    }
                }
                gte_stsxy3_gt3(prim);
                gte_nclip();
                gte_stopz(scratchpad1);
                if (*scratchpad1 < 0) {
                    prim->drawMode = DRAW_HIDE;
                } else {
                    prim->drawMode = DRAW_UNK02;
                }
                gte_ldv0(vecPtr[3]);
                gte_rtps();
                gte_stsxy((long*)&prim->x3);
                gte_avsz4();
                gte_stotz(scratchpad2);
                prim->priority =
                    ((g_CurrentEntity->ext.spellbookMagicTome.unk8A + 0x200) /
                         4 -
                     *scratchpad2) +
                    0x90;
                vecPtr += 4;
                prim = prim->next;
            }
        }
        rot.vz += g_CurrentEntity->ext.spellbookMagicTome.unk82;
        RotMatrix(&rot, &m);
        SetRotMatrix(&m);
    }
    rot.vz = g_CurrentEntity->ext.spellbookMagicTome.unk9C.vz;
    RotMatrix(&rot, &m);
    SetRotMatrix(&m);
    gte_ldv0(&D_us_80182FC4);
    gte_rtps();
    gte_stsxy((long*)&g_CurrentEntity->ext.spellbookMagicTome.unk84);
    g_CurrentEntity->ext.spellbookMagicTome.unk84 -= g_CurrentEntity->posX.i.hi;
    g_CurrentEntity->ext.spellbookMagicTome.unk86 -= g_CurrentEntity->posY.i.hi;
    gte_stszotz(scratchpad2);
    g_CurrentEntity->ext.spellbookMagicTome.unk88 =
        ((g_CurrentEntity->ext.spellbookMagicTome.unk8A + 0x200) / 4 -
         *scratchpad2) +
        0x90;
}

void func_us_801D1F50(RECT* rect) {
    SVECTOR* temp_s1 = &g_CurrentEntity->ext.spellbookMagicTome.unk9C;
    SVECTOR* temp_s0 = &g_CurrentEntity->ext.spellbookMagicTome.unkA4;
    temp_s0->vx = rect->x - temp_s1->vx;
    temp_s0->vy = rect->y - temp_s1->vy;
    temp_s0->vz = rect->w - temp_s1->vz;
    temp_s0->vx = (temp_s0->vx + 0x2000) % 0x1000;
    if (temp_s0->vx > 0x800) {
        temp_s0->vx -= 0x1000;
    }
    temp_s0->vy = (temp_s0->vy + 0x2000) % 0x1000;
    if (temp_s0->vy > 0x800) {
        temp_s0->vy -= 0x1000;
    }
    temp_s0->vz = (temp_s0->vz + 0x2000) % 0x1000;
    if (temp_s0->vz > 0x800) {
        temp_s0->vz -= 0x1000;
    }
    temp_s0->vx /= rect->h;
    temp_s0->vy /= rect->h;
    temp_s0->vz /= rect->h;
}

void func_us_801D2108(void) {
    SVECTOR* temp_s1 = &g_CurrentEntity->ext.spellbookMagicTome.unk9C;
    SVECTOR* temp_s0 = &g_CurrentEntity->ext.spellbookMagicTome.unkA4;
    temp_s1->vx += temp_s0->vx;
    temp_s1->vy += temp_s0->vy;
    temp_s1->vz += temp_s0->vz;
}

bool func_us_801D2148(RECT* rects) {
    RECT* rect;

    rect = &rects[g_CurrentEntity->pose];
    if (g_CurrentEntity->poseTimer == 0) {
        if (!rect->h) {
            return false;
        }
        func_us_801D1F50(rect);
        g_CurrentEntity->poseTimer = rect->h;
    }
    if (!--g_CurrentEntity->poseTimer) {
        g_CurrentEntity->pose++;
    }
    func_us_801D2108();
    return true;
}

bool func_801CDC80(s16* val, s16 target, s16 step) {
    if (abs(*val - target) < step) {
        *val = target;
        return true;
    }
    if (*val > target) {
        *val -= step;
    }
    if (*val < target) {
        *val += step;
    }
    return false;
}

void EntitySpellbook(Entity* self) {
    s32 dx, dy;
    RECT rect;
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    u8* ptr;
    u32 palette;
    s16 angle;
    s32 mag;

    if ((self->flags & FLAG_DEAD) && self->step < 8) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpellbook);
        self->hitboxState = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xC);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.spellbookMagicTome.unk7C = prim;
        palette = 0x25A;
        self->palette = palette;
        for (i = 0; i < 12; i++) {
            ptr = D_us_801830DC[i];
            if (i % 6 < 2) {
                prim->clut = palette + 0;
            } else {
                prim->clut = palette + 1;
            }
            prim->tpage = 0x15;
            prim->u0 = prim->u2 = ptr[0];
            prim->u1 = prim->u3 = ptr[2];
            prim->v0 = prim->v1 = ptr[1];
            prim->v2 = prim->v3 = ptr[3];
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            ptr += 4;
        }
        tempEntity = self + 1;
        CreateEntityFromCurrentEntity(E_ID_3E, tempEntity);
        tempEntity->params = 0;
        self->ext.spellbookMagicTome.unk9C.vx = 0x400;
        self->ext.spellbookMagicTome.unk8A = 0x300;
        SetStep(2);
        break;

    case 2:
        if (GetDistanceToPlayerX() < 0x40 && GetDistanceToPlayerY() < 0x40) {
            SetStep(3);
        }
        break;

    case 3:
        self->ext.spellbookMagicTome.unk8A -= 0x10;
        if (self->ext.spellbookMagicTome.unk8A < 0) {
            self->ext.spellbookMagicTome.unk8A = 0;
            self->hitboxState = 3;
            SetStep(4);
        }
        break;

    case 4:
        if (!self->step_s) {
            self->ext.spellbookMagicTome.unk8E = 0x200;
            self->step_s++;
        }
        MoveEntity();
        tempEntity = &PLAYER;
        angle = GetAngleBetweenEntities(self, tempEntity);
        angle =
            GetNormalizedAngle(0x10, self->ext.spellbookMagicTome.unk8C, angle);
        mag = self->ext.spellbookMagicTome.unk90;
        self->velocityX = (mag * rcos(angle)) >> 0xC;
        self->velocityY = (mag * rsin(angle)) >> 0xC;
        self->ext.spellbookMagicTome.unk8C = angle;
        mag += 0x400;
        if (mag > FIX(0.75)) {
            mag = FIX(0.75);
        }
        if (self->hitFlags & 3) {
            mag = FIX(-0.75);
        }
        self->ext.spellbookMagicTome.unk90 = mag;
        if (!self->ext.spellbookMagicTome.unk80) {
            self->ext.spellbookMagicTome.unk80 = 0x40;
            self->ext.spellbookMagicTome.unkA4.vx = (Random() & 0x1F) - 0x10;
            self->ext.spellbookMagicTome.unkA4.vy = (Random() & 0x1F) - 0x10;
            self->ext.spellbookMagicTome.unkA4.vz = (Random() & 0x1F) - 0x10;
        } else {
            self->ext.spellbookMagicTome.unk80--;
        }
        func_us_801D2108();
        if (!--self->ext.spellbookMagicTome.unk8E) {
            SetStep(5);
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            tempEntity = &PLAYER;
            angle = GetAngleBetweenEntities(self, tempEntity);
            rect.x = 0x280;
            rect.y = angle + 0x800;
            rect.w = 0x440;
            rect.h = 0x20;
            func_us_801D1F50(&rect);
            self->ext.spellbookMagicTome.unk80 = 0x20;
            self->step_s++;
            /* fallthrough */
        case 1:
            func_us_801D2108();
            if (!--self->ext.spellbookMagicTome.unk80) {
                self->step_s++;
            }
            break;

        case 2:
            if (func_801CDC80(
                    &self->ext.spellbookMagicTome.unk82, 0x300, 0x20)) {
                self->step_s++;
            }
            break;

        case 3:
            tempEntity = self + 1;
            tempEntity->ext.spellbookMagicTome.unk94 = 1;
            self->step_s++;
            break;

        case 4:
            tempEntity = self + 1;
            if (!tempEntity->ext.spellbookMagicTome.unk94) {
                self->step_s++;
            }
            break;

        case 5:
            if (func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0, 0x10)) {
                SetStep(4);
            }
            break;
        }
        break;

    case 8:
        if ((Random() & 0xF) == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->params = 1;
                tempEntity->posX.i.hi += self->ext.spellbookMagicTome.unk84 / 2;
                tempEntity->posY.i.hi += self->ext.spellbookMagicTome.unk86 / 2;
                tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->posY.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->zPriority = 0xD0;
            }
        }
        if ((g_Timer & 0xF) == 0) {
            PlaySfxPositional(SFX_EXPLODE_B);
        }
        switch (self->step_s) {
        case 0:
            self->ext.spellbookMagicTome.unkA4.vx = 0x40;
            self->ext.spellbookMagicTome.unkA4.vy = 0x40;
            self->ext.spellbookMagicTome.unkA4.vz = 0x40;
            self->ext.spellbookMagicTome.unk80 = 0x80;
            self->hitboxState = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0x200, 0x10);
            func_us_801D2108();
            if (g_Timer & 1) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID_31, self, tempEntity);
                    tempEntity->posX.i.hi +=
                        self->ext.spellbookMagicTome.unk84 / 2;
                    tempEntity->posY.i.hi +=
                        self->ext.spellbookMagicTome.unk86 / 2;
                    dx = self->ext.spellbookMagicTome.unk84;
                    dy = self->ext.spellbookMagicTome.unk86;
                    angle = ratan2(dy, dx);
                    tempEntity->rotate = angle;
                    tempEntity->zPriority = self->ext.spellbookMagicTome.unk88;
                    dx = (Random() & 0x1F) - 0x10;
                    tempEntity->posX.i.hi += (dx * rcos(angle + 0x400)) >> 0xC;
                    tempEntity->posY.i.hi += (dx * rsin(angle + 0x400)) >> 0xC;
                }
            }
            if ((self->ext.spellbookMagicTome.unk80 & 7) == 0) {
                PlaySfxPositional(SFX_SPELLBOOK_DEATH);
            }
            if (!--self->ext.spellbookMagicTome.unk80) {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
                self->step_s++;
            }
            break;

        case 2:
            MoveEntity();
            func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0x700, 8);
            self->velocityY += FIX(0.0625);
            break;
        }
        break;

    case 32:
        if ((g_Timer & 0xF) == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_ID_31, self, tempEntity);
                tempEntity->posX.i.hi += self->ext.spellbookMagicTome.unk84;
                tempEntity->posY.i.hi += self->ext.spellbookMagicTome.unk86;
            }
        }
        if (g_pads[1].pressed & PAD_TRIANGLE) {
            self->ext.spellbookMagicTome.unk9C.vx += 0x10;
        }
        if (g_pads[1].pressed & PAD_CROSS) {
            self->ext.spellbookMagicTome.unk9C.vx -= 0x10;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            self->ext.spellbookMagicTome.unk9C.vy += 0x10;
        }
        if (g_pads[1].pressed & PAD_SQUARE) {
            self->ext.spellbookMagicTome.unk9C.vy -= 0x10;
        }
        if (g_pads[1].pressed & PAD_RIGHT) {
            self->ext.spellbookMagicTome.unk9C.vz += 0x10;
        }
        if (g_pads[1].pressed & PAD_LEFT) {
            self->ext.spellbookMagicTome.unk9C.vz -= 0x10;
        }
        if (g_pads[1].pressed & PAD_UP) {
            self->ext.spellbookMagicTome.unk82 += 0x10;
        }
        if (g_pads[1].pressed & PAD_DOWN) {
            self->ext.spellbookMagicTome.unk82 -= 0x10;
        }
        if (g_pads[0].pressed & PAD_UP) {
            self->ext.spellbookMagicTome.unk8A += 0x10;
        }
        if (g_pads[0].pressed & PAD_DOWN) {
            self->ext.spellbookMagicTome.unk8A -= 0x10;
        }
        if (g_pads[1].pressed & PAD_SELECT) {
            self->ext.spellbookMagicTome.unk9C.vx = 0;
            self->ext.spellbookMagicTome.unk9C.vy = 0;
            self->ext.spellbookMagicTome.unk9C.vz = 0;
            self->ext.spellbookMagicTome.unk82 = 0;
        }
        FntPrint("x:%4x\n", self->ext.spellbookMagicTome.unk9C.vx);
        FntPrint("y:%4x\n", self->ext.spellbookMagicTome.unk9C.vy);
        FntPrint("z:%4x\n", self->ext.spellbookMagicTome.unk9C.vz);
        FntPrint("hz:%4x\n", self->ext.spellbookMagicTome.unk8A);
        FntPrint("w:%4x\n", self->ext.spellbookMagicTome.unk82);
        break;
    }
    func_us_801D1BCC();
    self->hitboxOffX = self->ext.spellbookMagicTome.unk84 / 2;
    self->hitboxOffY = self->ext.spellbookMagicTome.unk86 / 2;
}

void func_us_801D2CE0(Entity* self) {
    s16 rotate;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180908);
        self->animCurFrame = (Random() & 0xF) + 1;
        rotate = self->rotate;
        rotate += Random() * 2 - 0x100;
        self->velocityX = rcos(rotate) << 5;
        self->velocityY = rsin(rotate) << 5;
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        break;
    }
}

void EntityMagicTome(Entity* self) {
    RECT rect;
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s16 angle;
    s32 dx, dy;
    s32 i;
    s32 palette;
    u8* ptr;

    if ((self->flags & FLAG_DEAD) && self->step < 8) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMagicTome);
        self->hitboxState = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xC);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.spellbookMagicTome.unk7C = prim;
        palette = 0x25E;
        self->palette = palette;
        for (i = 0; i < 12; i++) {
            ptr = D_us_8018310C[i];
            if (i % 6 < 2) {
                prim->clut = palette + 0;
            } else {
                prim->clut = palette + 1;
            }
            prim->tpage = 0x15;
            prim->u0 = prim->u2 = ptr[0];
            prim->u1 = prim->u3 = ptr[2];
            prim->v0 = prim->v1 = ptr[1];
            prim->v2 = prim->v3 = ptr[3];
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            ptr += 4;
        }
        tempEntity = self + 1;
        CreateEntityFromCurrentEntity(E_ID_3E, tempEntity);
        tempEntity->params = 2;
        self->ext.spellbookMagicTome.unk9C.vx = 0x400;
        self->ext.spellbookMagicTome.unk8A = 0x300;
        SetStep(2);
        break;

    case 2:
        if (GetDistanceToPlayerX() < 0x68 && GetDistanceToPlayerY() < 0x60) {
            SetStep(3);
        }
        break;

    case 3:
        self->ext.spellbookMagicTome.unk8A -= 0x10;
        if (self->ext.spellbookMagicTome.unk8A < 0) {
            self->ext.spellbookMagicTome.unk8A = 0;
            self->hitboxState = 3;
            SetStep(4);
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->ext.spellbookMagicTome.unk8E = 0x60;
            self->step_s++;
            /* fallthrough */
        case 1:
            tempEntity = &PLAYER;
            dx = tempEntity->posX.i.hi - self->posX.i.hi;
            dy = tempEntity->posY.i.hi - self->posY.i.hi;
            if (abs(dx) > abs(dy)) {
                self->velocityY = 0;
                if (dx > 0) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
            } else {
                self->velocityX = 0;
                if (dy > 0) {
                    self->velocityY = FIX(2.0);
                } else {
                    self->velocityY = FIX(-2.0);
                }
            }
            self->ext.spellbookMagicTome.unkA4.vx = (Random() & 0x1F) - 0x10;
            self->ext.spellbookMagicTome.unkA4.vy = (Random() & 0x1F) - 0x10;
            self->ext.spellbookMagicTome.unkA4.vz = (Random() & 0x1F) - 0x10;
            self->ext.spellbookMagicTome.unk80 = 0x40;
            self->step_s++;
            /* fallthrough */
        case 2:
            MoveEntity();
            func_us_801D2108();
            if (!--self->ext.spellbookMagicTome.unk8E) {
                SetStep(5);
            }
            break;
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            tempEntity = &PLAYER;
            angle = GetAngleBetweenEntities(self, tempEntity);
            rect.x = 0x280;
            rect.y = angle + 0x800;
            rect.w = 0x440;
            rect.h = 0x20;
            func_us_801D1F50(&rect);
            self->ext.spellbookMagicTome.unk80 = 0x20;
            self->step_s++;
            /* fallthrough */
        case 1:
            func_us_801D2108();
            if (!--self->ext.spellbookMagicTome.unk80) {
                self->step_s++;
            }
            break;

        case 2:
            if (func_801CDC80(
                    &self->ext.spellbookMagicTome.unk82, 0x300, 0x10) != 0) {
                self->step_s++;
            }
            break;

        case 3:
            tempEntity = self + 1;
            tempEntity->ext.spellbookMagicTome.unk94 = 1;
            self->step_s++;
            break;

        case 4:
            tempEntity = self + 1;
            if (!tempEntity->ext.spellbookMagicTome.unk94) {
                self->step_s++;
            }
            break;

        case 5:
            if (func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0, 0x10)) {
                SetStep(4);
            }
            break;
        }
        break;

    case 8:
        if ((Random() & 0xF) == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->params = 1;
                tempEntity->posX.i.hi += self->ext.spellbookMagicTome.unk84 / 2;
                tempEntity->posY.i.hi += self->ext.spellbookMagicTome.unk86 / 2;
                tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->posY.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->zPriority = 0xC0;
            }
        }
        if ((g_Timer & 0xF) == 0) {
            PlaySfxPositional(SFX_EXPLODE_B);
        }
        switch (self->step_s) {
        case 0:
            self->ext.spellbookMagicTome.unkA4.vx = 0x40;
            self->ext.spellbookMagicTome.unkA4.vy = 0x40;
            self->ext.spellbookMagicTome.unkA4.vz = 0x40;
            self->ext.spellbookMagicTome.unk80 = 0x80;
            self->hitboxState = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0x200, 0x10);
            func_us_801D2108();
            if (g_Timer & 1) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID_31, self, tempEntity);
                    tempEntity->posX.i.hi +=
                        self->ext.spellbookMagicTome.unk84 / 2;
                    tempEntity->posY.i.hi +=
                        self->ext.spellbookMagicTome.unk86 / 2;
                    dx = self->ext.spellbookMagicTome.unk84;
                    dy = self->ext.spellbookMagicTome.unk86;
                    angle = ratan2(dy, dx);
                    tempEntity->rotate = angle;
                    tempEntity->zPriority = self->ext.spellbookMagicTome.unk88;
                    dx = (Random() & 0x1F) - 0x10;
                    tempEntity->posX.i.hi += (dx * rcos(angle + 0x400)) >> 0xC;
                    tempEntity->posY.i.hi += (dx * rsin(angle + 0x400)) >> 0xC;
                }
            }
            if ((self->ext.spellbookMagicTome.unk80 & 7) == 0) {
                g_api.PlaySfx(SFX_SPELLBOOK_DEATH);
            }
            if (!--self->ext.spellbookMagicTome.unk80) {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
                self->step_s++;
            }
            break;

        case 2:
            MoveEntity();
            func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0x700, 8);
            self->velocityY += FIX(0.0625);
            break;
        }
        break;
    }
    func_us_801D1BCC();
    self->hitboxOffX = self->ext.spellbookMagicTome.unk84 / 2;
    self->hitboxOffY = self->ext.spellbookMagicTome.unk86 / 2;
}

void func_us_801D35B8(Entity* self) {
    Entity* tempEntity;
    s32 x, y;
    s16 rotate;
    s32 temp_s5;
    unkBookStruct* ptr;

    ptr = &D_us_8018316C[self->params];
    switch (self->step) {
    case 0:
        InitializeEntity(*ptr->unk0);
        self->hitboxWidth = self->hitboxHeight = ptr->unkA;
        break;

    case 1:
        self->hitboxState = 0;
        if (self->ext.spellbookMagicTome.unk94) {
            PlaySfxPositional(SFX_MAGIC_TOME_ATTACK);
            SetStep(2);
        }
        tempEntity = self - 1;
        if (!tempEntity->entityId || tempEntity->flags & FLAG_DEAD) {
            DestroyEntity(self);
            return;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            tempEntity = self - 1;
            x = tempEntity->ext.spellbookMagicTome.unk84;
            y = tempEntity->ext.spellbookMagicTome.unk86;
            self->posX.i.hi = tempEntity->posX.i.hi + x / 2;
            self->posY.i.hi = tempEntity->posY.i.hi + y / 2;
            rotate = ratan2(y, x);
            self->animCurFrame = ptr->unkC;
            self->rotate = rotate + ptr->unk4;
            self->zPriority = tempEntity->ext.spellbookMagicTome.unk88;
            self->drawFlags =
                FLAG_DRAW_ROTATE | FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleX = self->scaleY = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            tempEntity = self - 1;
            self->zPriority = tempEntity->ext.spellbookMagicTome.unk88;
            self->scaleX = self->scaleY += 8;
            if (self->scaleX >= 0x120) {
                self->step_s = 2;
            }
            if (self->scaleX > 0x80) {
                self->hitboxState = 1;
                rotate = self->rotate - ptr->unk6;
                temp_s5 = ptr->unk8;
                x = (temp_s5 * self->scaleX * rcos(rotate)) >> 0x14;
                y = (temp_s5 * self->scaleX * rsin(rotate)) >> 0x14;
                self->hitboxOffX = x;
                self->hitboxOffY = y;
            }
            tempEntity = self - 1;
            if (tempEntity->flags & FLAG_DEAD) {
                self->hitboxState = 0;
                self->step_s = 2;
            }
            break;

        case 2:
            self->hitboxState = 0;
            self->scaleX = self->scaleY -= 4;
            tempEntity = self - 1;
            if (tempEntity->flags & FLAG_DEAD) {
                self->scaleX = self->scaleY -= 16;
            }
            if (self->scaleX & 0xF000) {
                self->animCurFrame = 0;
                self->ext.spellbookMagicTome.unk94 = 0;
                SetStep(1);
            }
            break;
        }
        break;
    }
}
