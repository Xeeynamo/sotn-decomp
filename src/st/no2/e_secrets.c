// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

static s32 D_us_80180D48[][2] = {
    {FIX(-0.5), FIX(0.0)},      {FIX(-0.0625), FIX(-0.125)},
    {FIX(-0.375), FIX(0.0)},    {FIX(-0.03125), FIX(-0.125)},
    {FIX(-0.125), FIX(0.0625)}, {FIX(0.0), FIX(0.0625)},
    {FIX(0.0), FIX(0.25)},      {FIX(0.0), FIX(0.125)},
    {FIX(1.25), FIX(-1.75)},    {FIX(1.5), FIX(-1.875)},
    {FIX(0.5), FIX(-1.25)},     {FIX(0.75), FIX(-2.25)},
    {FIX(0.0), FIX(0.0)},       {FIX(0.0), FIX(0.125)},
    {FIX(0.0), FIX(0.21875)},   {FIX(0.0), FIX(0.375)},
};
static s16 D_us_80180DC8[] = {
    -0x040, 0x010, -0x030, 0x010, -0x020, 0x008, 0x000,  0x008, 0x060,
    0x100,  0x040, 0x020,  0x020, -0x018, 0x038, -0x030, 0x080, -0x080,
};

void func_us_801B59C4(Primitive* prim) {
    Collider collider;
    Entity* tempEntity;
    Primitive* prim2;
    s32 i;
    s16 posX;
    s16 posY;

    switch (prim->next->u2) {
    case 0:
        prim->tpage = 0xF;
        prim->clut = 0x33;
        if (prim->next->r3 % 2) {
            prim->u0 = prim->u2 = 0xB8;
            prim->u1 = prim->u3 = 0xA8;
        } else {
            prim->u0 = prim->u2 = 0xA8;
            prim->u1 = prim->u3 = 0xB8;
        }
        if ((prim->next->r3 % 4) < 2) {
            prim->v0 = prim->v1 = 0xC8;
            prim->v2 = prim->v3 = 0xD8;
        } else {
            prim->v0 = prim->v1 = 0xD8;
            prim->v2 = prim->v3 = 0xC8;
        }
        prim->priority = 0x68;
        prim->drawMode = DRAW_UNK02;
        LOW(prim->next->u0) = D_us_80180D48[prim->next->r3][0];
        LOW(prim->next->r1) = D_us_80180D48[prim->next->r3][1];
        LOH(prim->next->r2) = LOH(prim->next->b2) = 0x10;
        prim->next->u2 = 1;
        if (prim->next->r3 > 7 && prim->next->r3 < 12) {
            LOH(prim->next->r2) = LOH(prim->next->b2) = 8;
            prim->next->u2 = 4;
        }
        break;

    case 1:
        LOW(prim->next->r1) += 0x800;
        if (prim->next->r3 > 11) {
            LOW(prim->next->r1) += 0x1000;
        }
        LOH(prim->next->tpage) += D_us_80180DC8[prim->next->r3];

        posX = prim->next->x1;
        posY = prim->next->y0;
        posY += 4;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            posY += collider.unk18;
            for (i = 0; i < 3; i++) {
                prim2 = g_CurrentEntity->ext.breakableNo2.unk7C;
                prim2 = FindFirstUnkPrim2(prim2, 2);
                if (prim2 != NULL) {
                    UnkPolyFunc2(prim2);
                    prim2->next->u2 = 2;
                    prim2->next->y0 = posY - 8;
                    if (prim->next->r3 < 12) {
                        prim2->next->x1 = posX + i * 4;
                    } else {
                        prim2->next->x1 = posX;
                        prim2->next->u2 = 3;
                    }
                }
            }
            UnkPolyFunc0(prim);
            return;
        }
        break;

    case 2:
        prim->tpage = 0xF;
        prim->clut = 0x33;
        prim->u0 = prim->u2 = 0xB8;
        prim->u1 = prim->u3 = 0xC8;
        prim->v0 = prim->v1 = 0xC8;
        prim->v2 = prim->v3 = 0xD8;
        prim->priority = 0x6A;
        prim->drawMode = DRAW_UNK02;
        LOW(prim->next->u0) = -(Random() & 7) * 0x2800;
        LOW(prim->next->r1) = -0x18000 - ((Random() & 7) << 0xD);
        LOH(prim->next->r2) = LOH(prim->next->b2) = ((Random() & 3) * 2) + 8;
        prim->next->u2 = 4;
        break;

    case 3:
        prim->tpage = 0xF;
        prim->clut = 0x33;
        prim->u0 = prim->u2 = 0xB8;
        prim->u1 = prim->u3 = 0xC8;
        prim->v0 = prim->v1 = 0xC8;
        prim->v2 = prim->v3 = 0xD8;
        prim->priority = 0x6A;
        prim->drawMode = DRAW_UNK02;
        LOW(prim->next->u0) = 0xE000 - ((Random() & 7) << 0xE);
        LOW(prim->next->r1) = -0x18000 - ((Random() & 7) << 0xD);
        LOH(prim->next->r2) = LOH(prim->next->b2) = ((Random() & 3) * 2) + 8;
        if (LOW(prim->next->u0) > 0) {
            prim->next->r3 = 16;
        } else {
            prim->next->r3 = 17;
        }
        prim->next->u2 = 4;
        break;

    case 4:
        LOW(prim->next->r1) += 0x2000;
        if (prim->next->r3) {
            LOH(prim->next->tpage) += D_us_80180DC8[prim->next->r3];
        } else {
            LOH(prim->next->tpage) -= 0x40;
        }
        posX = prim->next->x1;
        posY = prim->next->y0;
        posY += LOH(prim->next->r2) / 2;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            prim->next->y0 += collider.unk18;
            LOW(prim->next->r1) = -LOW(prim->next->r1) / 2;
            if (LOW(prim->next->r1) > -0x4000) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_INTENSE_EXPLOSION, tempEntity);
                    tempEntity->posX.i.hi = posX;
                    tempEntity->posY.i.hi = posY;
                    tempEntity->params = 0x10;
                }
                UnkPolyFunc0(prim);
            }
        }
        break;
    }
    UnkPrimHelper(prim);
}

static u16 D_us_80180DEC[] = {
    0x44E, 0x44F, 0x47E, 0x47F, 0x4AE, 0x4AF, 0x4DE, 0x4DF, 0x50E, 0x50F,
};
static u16 D_us_80180E00[] = {
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x40C, 0x000, 0x598, 0x40B,
};

void func_us_801B5FB8(Entity* self) {
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 tileIdx;

    FntPrint("timer %x\n", self->ext.breakableNo2.unk80);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->animCurFrame = 0;
        if (g_CastleFlags[NO2_SECRET_WALL_OPEN]) {
            for (i = 0; i < 10; i++) {
                tileIdx = D_us_80180DEC[i];
                g_Tilemap.fg[tileIdx] = D_us_80180E00[i];
            }
            DestroyEntity(self);
            return;
        }
        self->zPriority = 0xA8;
        self->hitboxState = 2;
        self->hitPoints = 0x7FFF;
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0x28;
        break;

    case 1:
        if (self->hitFlags) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->ext.breakableNo2.unk80 = 0x10;
            self->ext.breakableNo2.unk88++;
            self->step++;
        }
        if (self->ext.breakableNo2.unk88 == 3) {
            self->hitboxState = 0;
            self->step = 3;
        }
        break;

    case 2:
        if (self->ext.breakableNo2.unk88 == 1) {
            self->animCurFrame = 12;
        }
        if (self->ext.breakableNo2.unk88 == 2) {
            self->animCurFrame = 13;
        }
        if (!--self->ext.breakableNo2.unk80) {
            self->step--;
        }
        break;

    case 3:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.breakableNo2.unk7C = prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            g_CastleFlags[NO2_SECRET_WALL_OPEN] |= 1;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(
                NO2_SECRET_WALL_OPEN);
            for (i = 0; i < 10; i++) {
                tileIdx = D_us_80180DEC[i];
                g_Tilemap.fg[tileIdx] = D_us_80180E00[i];
            }
            DestroyEntity(self);
            return;
        }
        prim = self->ext.breakableNo2.unk7C;
        for (i = 0; i < 2; i++) {
            prim->tpage = 0xF;
            prim->clut = 0x21;
            prim->u0 = prim->u2 = 0x80;
            prim->u1 = prim->u3 = 0x97;
            prim->v0 = prim->v1 = 0xF0;
            prim->v2 = prim->v3 = 0xFF;
            prim->x0 = prim->x2 = self->posX.i.hi + 0xFFEF;
            prim->x1 = prim->x3 = prim->x0 + 0x18;
            if (i != 0) {
                prim->y0 = prim->y1 = self->posY.i.hi + 0x10008;
            } else {
                prim->y0 = prim->y1 = self->posY.i.hi + 0xFFE8;
            }
            prim->y2 = prim->y3 = prim->y0 + 0x10;
            prim->priority = 0xA8;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        self->ext.breakableNo2.unk80 = 0x20;
        self->step++;
        break;

    case 4:
        if (!--self->ext.breakableNo2.unk80) {
            self->step++;
        }
        break;

    case 5:
        self->animCurFrame = 0;
        g_CastleFlags[NO2_SECRET_WALL_OPEN] |= 1;
        g_api.RevealSecretPassageAtPlayerPositionOnMap(NO2_SECRET_WALL_OPEN);
        for (i = 0; i < 10; i++) {
            tileIdx = D_us_80180DEC[i];
            g_Tilemap.fg[tileIdx] = D_us_80180E00[i];
        }
        prim = self->ext.breakableNo2.unk7C;
        for (i = 0; i < 8; i++) {
            UnkPolyFunc2(prim);
            prim->next->x1 = self->posX.i.hi - 8 + ((i % 2) * 0x10);
            prim->next->y0 = self->posY.i.hi - 24 + ((i / 2) * 0x10);
            prim->next->r3 = i;
            prim = prim->next;
            prim = prim->next;
        }
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->posY.i.hi += 0x20;
            tempEntity->params = 0x13;
            tempEntity->params += 0xAA00;
        }
        for (i = 0; i < 8; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, tempEntity);
                tempEntity->posX.i.hi += 0xF - (Random() & 0x1F);
                tempEntity->posY.i.hi += 0xF - (Random() & 0x1F);
                tempEntity->params = 0x10;
                tempEntity->params += 0xAA00;
            }
        }
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        self->ext.breakableNo2.unk80 = 0x180;
        self->step++;
        break;

    case 6:
        prim = self->ext.breakableNo2.unk7C;
        while (prim != NULL) {
            if (prim->p3 & 8) {
                func_us_801B59C4(prim);
            }
            prim = prim->next;
        }
        if (!--self->ext.breakableNo2.unk80) {
            g_CastleFlags[NO2_SECRET_WALL_OPEN] |= 2;
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801B65A4(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->hitboxState = 0;
        self->animCurFrame = 0;
        break;

    case 1:
        if (g_CastleFlags[NO2_SECRET_WALL_OPEN] & 2) {
            DestroyEntity(self);
            return;
        }
        if (g_CastleFlags[NO2_SECRET_WALL_OPEN]) {
            g_CastleFlags[NO2_SECRET_WALL_OPEN] |= 2;
        }
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.breakableNo2.unk7C = prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        prim = self->ext.breakableNo2.unk7C;
        for (i = 0; i < 4; i++) {
            UnkPolyFunc2(prim);
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            prim->next->r3 = i + 8;
            prim = prim->next;
            prim = prim->next;
        }
        self->step++;
        break;

    case 2:
        i = 1;
        prim = self->ext.breakableNo2.unk7C;
        while (prim != NULL) {
            if (prim->p3 & 8) {
                i = 0;
                func_us_801B59C4(prim);
            }
            prim = prim->next;
        }
        if (i != 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

void func_us_801B6794(Primitive* prim) {
    s32 x, y;

    if (!prim->g3) {
        prim->u0 = 1;
        prim->v0 = 1;
        prim->r0 = 0x80;
        prim->g0 = 0x80;
        prim->b0 = 0xC0;
        prim->drawMode = DRAW_UNK02;
        prim->x0 = g_CurrentEntity->posX.i.hi;
        prim->y0 = g_CurrentEntity->posY.i.hi + 8;
        prim->x1 = 0;
        prim->y1 = 0;
        LOW(prim->x2) = 0x7000 - ((Random() & 7) << 0xD);
        LOW(prim->x3) = 0x7000 - ((Random() & 7) << 0xD);
        prim->g3 = 1;
        prim->r3 = 0x20;
    }
#ifdef VERSION_US
    x = (prim->x0 << 0x10) + (u16)prim->x1;
#else
    x = (prim->x0 << 0x10) + prim->x1;
#endif
    x += LOW(prim->x2);
    prim->x0 = HIHU(x);
    prim->x1 = LOHU(x);
#ifdef VERSION_US
    y = (prim->y0 << 0x10) + (u16)prim->y1;
#else
    y = (prim->y0 << 0x10) + prim->y1;
#endif
    y += LOW(prim->x3);
    prim->y0 = HIH(y);
    prim->y1 = LOH(y);
    LOW(prim->x3) += 0x2000;
    prim->r3 -= 1;
    if (!prim->r3) {
        prim->g3 = 0;
        prim->drawMode = DRAW_HIDE;
        prim->p3 = 0;
    }
}

static u16 D_us_80180E14[] = {
    0x086, 0x087, 0x088, 0x089, 0x0F6, 0x0F7, 0x0F8, 0x0F9,
};
static u16 D_us_80180E24[][8] = {
    {0x005, 0x009, 0x004, 0x009, 0x00F, 0x00D, 0x00E, 0x00D},
    {0x496, 0x497, 0x4A9, 0x4AA, 0x498, 0x499, 0x4AB, 0x4AC},
};

void func_us_801B68EC(Entity* self) {
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 tileIdx;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->animCurFrame = 0;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->rotate = 0xC00;
        if (g_CastleFlags[NO2_SECRET_CEILING_OPEN]) {
            for (i = 0; i < 8; i++) {
                tileIdx = D_us_80180E14[i];
                g_Tilemap.fg[tileIdx] = D_us_80180E24[1][i];
            }
            DestroyEntity(self);
            return;
        }
        for (i = 0; i < 8; i++) {
            tileIdx = D_us_80180E14[i];
            g_Tilemap.fg[tileIdx] = D_us_80180E24[0][i];
        }
        self->hitboxState = 2;
        self->hitPoints = 0x80;
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0x28;
        primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 0x1E);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.breakableNo2.unk7C = prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim->priority = 0x68;
                self->ext.breakableNo2.unk84 = prim;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 1:
        if (self->hitFlags) {
            for (i = 0; i < 0x10; i++) {
                prim = self->ext.breakableNo2.unk7C;
                prim = FindFirstUnkPrim(prim);
                if (prim != NULL) {
                    prim->p3 = 1;
                }
            }
        }
        prim = self->ext.breakableNo2.unk7C;
        while (prim != NULL) {
            if (prim->p3) {
                func_us_801B6794(prim);
            }
            prim = prim->next;
        }
        prim = self->ext.breakableNo2.unk84;
        prim->x0 = prim->y0 = 0;
        prim->u0 = 0;
        prim->drawMode = DRAW_UNK02;
        if (self->flags & FLAG_DEAD) {
            self->animCurFrame = 0;
            self->step++;
        }
        break;

    case 2:
        primIndex = self->primIndex;
        g_api.FreePrimitives(primIndex);
        self->flags &= ~FLAG_HAS_PRIMS;
        g_CastleFlags[NO2_SECRET_CEILING_OPEN] = 1;
        g_api.RevealSecretPassageAtPlayerPositionOnMap(NO2_SECRET_CEILING_OPEN);
        for (i = 0; i < 8; i++) {
            tileIdx = D_us_80180E14[i];
            g_Tilemap.fg[tileIdx] = D_us_80180E24[1][i];
        }
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x18);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.breakableNo2.unk7C = prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        prim = self->ext.breakableNo2.unk7C;
        for (i = 0; i < 4; i++) {
            UnkPolyFunc2(prim);
            prim->next->x1 = self->posX.i.hi - 8 + ((i % 2) * 0x10);
            prim->next->y0 = self->posY.i.hi + ((i / 2) * 0x10);
            prim->next->r3 = i + 0xC;
            prim = prim->next;
            prim = prim->next;
        }
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->posY.i.hi += 0x20;
            tempEntity->params = 0x13;
            tempEntity->params += 0xAA00;
        }
        for (i = 0; i < 8; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, tempEntity);
                tempEntity->posX.i.hi += 0xF - (Random() & 0x1F);
                tempEntity->posY.i.hi += (Random() & 0x1F);
                tempEntity->params = 0x10;
                tempEntity->params += 0xAA00;
            }
        }
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        self->step++;
        break;

    case 3:
        i = 1;
        prim = self->ext.breakableNo2.unk7C;
        while (prim != NULL) {
            if (prim->p3 & 8) {
                i = 0;
                func_us_801B59C4(prim);
            }
            prim = prim->next;
        }
        if (i != 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}
