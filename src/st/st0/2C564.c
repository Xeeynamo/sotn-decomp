// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "sfx.h"

// D_801C2578 is initialized in 2DAC8.c, but the bss layout for psx does not
// allow for it to be defined in that file currently
#ifdef VERSION_PSP
extern u32 D_801C2578;                            // bss
static bool g_isDraculaFirstFormDefeated = false; // bss for pspeu
#else
u32 D_801C2578;                                   // bss
static bool g_isDraculaFirstFormDefeated = false; // bss for pspeu
s32 D_80180910 = 0;
#endif

static u8 D_80180914[] = {0x03, 0x01, 0x04, 0x02, 0x05, 0x03, 0x06, 0x04,
                          0x07, 0x05, 0x08, 0x06, 0x13, 0x07, 0xFF, 0x00};
static u8 D_80180924[] = {0x09, 0x07, 0x08, 0x06, 0x07, 0x05, 0x06, 0x04,
                          0x05, 0x03, 0x04, 0x02, 0x03, 0x01, 0xFF, 0x00};
static u8 D_80180934[] = {0x06, 0x01, 0x05, 0x08, 0x04, 0x09, 0x03,
                          0x0A, 0x06, 0x0B, 0x08, 0x0A, 0xFF, 0x00};
static u8 D_80180944[] = {0x09, 0x0A, 0x05, 0x0B, 0x05, 0x0A, 0x05,
                          0x09, 0x05, 0x08, 0x05, 0x01, 0xFF, 0x00};
static u8 D_80180954[] = {0x18, 0x01, 0x08, 0x02, 0x08, 0x0C, 0x08, 0x0D,
                          0x08, 0x0E, 0x08, 0x0F, 0x01, 0x10, 0xFF, 0x00};
static u8 D_80180964[] = {
    0x04, 0x3E, 0x04, 0x3F, 0x05, 0x40, 0x05, 0x41, 0x05, 0x42, 0x08,
    0x43, 0x05, 0x42, 0x05, 0x41, 0x05, 0x40, 0x04, 0x3F, 0xFF, 0x00};
static u8 D_8018097C[] = {0x01, 0x13, 0x01, 0x14, 0x01, 0x15, 0x01, 0x16, 0x01,
                          0x17, 0x01, 0x18, 0x01, 0x19, 0x01, 0x1A, 0x00, 0x00};
static u8 D_80180990[] = {0x02, 0x1B, 0x01, 0x27, 0x02, 0x1C, 0x01, 0x27, 0x02,
                          0x1D, 0x01, 0x27, 0x02, 0x1E, 0x01, 0x27, 0x00, 0x00};
static u8 D_801809A4[] = {
    0x02, 0x1F, 0x02, 0x20, 0x02, 0x21, 0x02, 0x22, 0x02, 0x23, 0xFF, 0x00};
static u8 D_801809B0[] = {
    0x05, 0x24, 0x04, 0x25, 0x03, 0x26, 0x02, 0x27, 0x01, 0x28, 0x01, 0x29,
    0x01, 0x2A, 0x01, 0x2B, 0x01, 0x2C, 0x01, 0x2D, 0x01, 0x2E, 0x01, 0x2F,
    0x01, 0x30, 0x01, 0x31, 0x01, 0x32, 0x01, 0x33, 0x02, 0x1B, 0x01, 0x27,
    0x02, 0x1C, 0x01, 0x27, 0x02, 0x1D, 0x01, 0x27, 0x02, 0x1E, 0xFF, 0x00};
static u8 D_801809E0[] = {
    0x03, 0x34, 0x03, 0x35, 0x03, 0x36, 0x03, 0x37, 0x03, 0x38, 0x03,
    0x39, 0x03, 0x3A, 0x03, 0x3B, 0x03, 0x3C, 0x03, 0x3D, 0xFF, 0x00};
static u8 D_801809F8_unused[] = {
    0x28, 0x47, 0x06, 0x48, 0x09, 0x49, 0x0A, 0x4A, 0x0B,
    0x4B, 0x07, 0x4C, 0x05, 0x4D, 0x28, 0x4E, 0xFF, 0x00};
static u8 D_80180A0C[] = {
    0x0E, 0x4F, 0x14, 0x50, 0x0B, 0x51, 0x08, 0x52, 0x4B, 0x53,
    0x09, 0x54, 0x05, 0x55, 0x20, 0x56, 0x01, 0x57, 0xFF, 0x00};
static u8 D_80180A20[] = {
    0x01, 0x57, 0x01, 0x47, 0x29, 0x58, 0x07, 0x47, 0xFF, 0x00};
static u8 D_80180A2C[] = {0x07, 0x47, 0x08, 0x48, 0x07, 0x49, 0x08, 0x4A, 0x1A,
                          0x4B, 0x07, 0x4C, 0x05, 0x4D, 0x28, 0x4E, 0xFF, 0x00};
static u8 D_80180A40[] = {0x02, 0x5A, 0x02, 0x5B, 0xFF, 0x00};
static s16 D_80180A48[] = {0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0, 0x90};
static Point16 D_80180A58[] = {{16, 28}, {20, 60}};
static Point16 D_80180A60[] = {{12, 12}, {12, -12}, {-12, 12}, {-12, -12}};
// Possible this is an unused u8 animation from the next file.
// It is stripped on PSP
static Point16 unused[] = {
    {80, 64}, {48, 34}, {26, 20}, {18, 16}, {15, 13}, {13, 12}, {12, 11},
    {11, 10}, {10, 10}, {9, 9},   {9, 8},   {8, 8},   {8, 4}};

#ifdef VERSION_PSP
extern u32 E_ID(DRACULA_UNK1B);
extern u32 E_ID(DRACULA_UNK1C);
extern u32 E_ID(DRACULA_UNK1D);
extern u32 E_ID(DRACULA_METEOR);
extern u32 E_ID(DRACULA_UNK1F);
extern u32 E_ID(DRACULA_UNK20);
extern u32 E_ID(DRACULA_UNK2B);
#endif

// Helper function for EntityDracula
static s32 func_801ABBBC(s32 step, Entity* dracula) {
    Primitive* prim;
    u8* rgbPtr;
    bool unkBool;
    s32 i, j;
    s32 color;
    switch (step) {
    case 0:
        dracula->ext.dracula.unk80 = prim = dracula->ext.dracula.prim;
        for (i = 0; i < 16; i++) {
            prim->type = PRIM_LINE_G2_ALT;
            if (i == 15) {
                prim->type = PRIM_LINE_G2;
            }
            if (i % 2) {
                prim->x0 = prim->x1 = dracula->posX.i.hi + i / 2;
            } else {
                prim->x0 = prim->x1 = dracula->posX.i.hi - i / 2;
            }
            prim->y0 = prim->y1 = 0;
            PGREY(prim, 0) = 0x70;
            PGREY(prim, 1) = 0;
            color = Random() & 7;
            prim->r2 = ((color & 1) * 0x10) + 0x10;
            prim->g2 = (((color & 2) >> 1) * 0x10) + 0x10;
            prim->b2 = ((color >> 2) * 0x10) + 0x10;
            prim->priority = dracula->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            if (i == 0) {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }

        dracula->ext.dracula.unk90 = 1;
        dracula->ext.dracula.unk92 = 0;
        dracula->ext.dracula.unk8C = 0;
        step++;
        break;

    case 1:
        if (dracula->ext.dracula.unk8C++ > 2) {
            dracula->ext.dracula.unk90 += 2;
            if (dracula->ext.dracula.unk90 >= 16) {
                dracula->ext.dracula.unk90 = 16;
            }
            dracula->ext.dracula.unk8C = 0;
        }
        prim = dracula->ext.dracula.unk80;
        for (i = 0; i < dracula->ext.dracula.unk90; i++) {
            prim->y1 += 0x30;
            if (dracula->ext.dracula.unkA1) {
                if (prim->y1 >= 171) {
                    prim->y1 = 171;
                }
            } else if (prim->y1 >= 203) {
                prim->y1 = 203;
            }
            rgbPtr = &prim->r1;
            // Iterate through r1, g1, and b1.
            for (j = 0; j < 3; j++, rgbPtr++) {
                color = *rgbPtr;
                if (color < 0xFF) {
                    // This ends up offsetting to r2, g2, and b2
                    color += rgbPtr[0xC];
                    if (color > 0xFF) {
                        color = 0xFF;
                    }
                }
                *rgbPtr = color;
            }

            prim = prim->next;
        }

        if (dracula->ext.dracula.unk92++ > 24) {
            dracula->ext.dracula.unk92 = 0;
            step++;
        }
        break;

    case 2:
        prim = dracula->ext.dracula.unk80;
        for (i = 0; i < 16; i++) {
            prim = prim->next;
        }

        dracula->ext.dracula.unk84 = prim;
        for (i = 0; i < 48; i++) {
            prim->type = PRIM_LINE_G2_ALT;
            if (i == 47) {
                prim->type = PRIM_LINE_G2;
            }
            PGREY(prim, 0) = 0x70;
            PGREY(prim, 1) = 0x20;
            color = Random() & 7;
            prim->r2 = ((color & 1) * 4) + 4;
            prim->g2 = (((color & 2) >> 1) * 4) + 4;
            prim->b2 = ((color >> 2) * 4) + 4;
            if (i % 2) {
                prim->x0 = prim->x1 = dracula->posX.i.hi + i / 2;
            } else {
                prim->x0 = prim->x1 = dracula->posX.i.hi - i / 2;
            }
            if (dracula->ext.dracula.unkA1) {
                prim->y0 = prim->y1 = 171;
                if (i > 0x21) {
                    prim->y0 = prim->y1 = -0x20;
                }
            } else {
                prim->y0 = prim->y1 = 203;
            }
            F(prim->x2).i.lo = 0;
            F(prim->x2).i.hi = prim->y1;
            color = i >> 1;
            F(prim->x3).val = ((color * color * color) << 8) + 0x80000;
            prim->priority = dracula->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            if (i == 0) {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }

        dracula->ext.dracula.unk8C = 0;
        g_api.PlaySfx(SFX_TELEPORT_BANG_B);
        step++;
        break;

    case 3:
        prim = dracula->ext.dracula.unk84;
        if (dracula->ext.dracula.unkA1) {
            j = 0x22;
        } else {
            j = 0x30;
        }
        for (i = 0; i < j; i++) {
            F(prim->x2).i.hi = prim->y1;
            F(prim->x2).val -= F(prim->x3).val;
            prim->y1 = F(prim->x2).i.hi;
            if (prim->y1 < 0) {
                prim->y1 = 0;
            }
            prim = prim->next;
        }

        dracula->ext.dracula.unk8C++;
        if (dracula->ext.dracula.unk8C < 9) {
            prim = dracula->ext.dracula.unk80;
            for (i = 0; i < 16 - (dracula->ext.dracula.unk8C * 2); i++) {
                prim = prim->next;
            }

            for (; i < 16; i++) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        }
        prim = dracula->ext.dracula.unk84;
        for (i = 0; i < 48; i++) {
            color = prim->r0;
            color += 4;
            if ((0xFF - i * 2) < color) {
                color = 0xFF - i * 2;
            }
            prim->r0 = color;
            if (prim->r0 >= 0xFF) {
                prim->r0 = 0xFF;
                step = 4;
            }
            prim->b0 = prim->g0 = prim->r0;
            prim = prim->next;
        }

        prim = dracula->ext.dracula.unk84;
        for (i = 0; i < 48; i++) {
            rgbPtr = &prim->r1;
            for (j = 0; j < 3; j++, rgbPtr++) {
                color = *rgbPtr;
                color += rgbPtr[0xC];
                if ((0xFF - (i * 2)) < color) {
                    color = 0xFF - (i * 2);
                }
                *rgbPtr = color;
            }

            prim = prim->next;
        }

        break;

    case 4:
        unkBool = true;
        prim = dracula->ext.dracula.unk84;
        for (i = 0; i < 48; i++) {
            rgbPtr = &prim->r1;
            for (j = 0; j < 3; j++, rgbPtr++) {
                color = *rgbPtr;
                color += 0x18;
                if ((0xFF - i * 2) < color) {
                    color = 0xFF - i * 2;
                } else {
                    unkBool = false;
                }
                *rgbPtr = color;
            }

            prim = prim->next;
        }

        if (unkBool) {
            step = 5;
        }
        break;

    case 5:
        prim = dracula->ext.dracula.unk80;
        // @bug: They forgot to do prim = prim->next in this loop!
        for (i = 0; i < 16; i++) {
            prim->drawMode = DRAW_HIDE;
        }

        prim = dracula->ext.dracula.unk80;
        prim->type = PRIM_TILE;
        PGREY(prim, 0) = 0;
        prim->y0 = 0;
        if (dracula->ext.dracula.unkA1) {
            prim->x0 = dracula->posX.i.hi - 17;
            prim->u0 = 0x22;
            prim->v0 = 0xAC;
        } else {
            prim->x0 = dracula->posX.i.hi - 24;
            prim->u0 = 0x30;
            prim->v0 = 0xCC;
        }
        prim->priority = dracula->zPriority + 1;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        dracula->ext.dracula.unk8C = 0;
        step++;
        break;

    case 6:
        unkBool = true;
        prim = dracula->ext.dracula.unk84;
        for (i = 0; i < 48; i++) {
            rgbPtr = &prim->r0;
            for (j = 0; j < 2; j++, rgbPtr += 0xC) {
                color = (*rgbPtr);
                color -= 10;
                if (color < 0) {
                    color = 0;
                } else {
                    unkBool = false;
                }
                *rgbPtr = rgbPtr[1] = (rgbPtr[2] = color);
            }

            prim = prim->next;
        }

        prim = dracula->ext.dracula.unk80;
        prim->r0 += 7;
        if (prim->r0 > 0xE0) {
            prim->r0 = 0xE0;
        } else {
            unkBool = false;
        }
        prim->g0 = (prim->b0 = prim->r0);
        if (unkBool) {
            prim = dracula->ext.dracula.unk84;
            for (i = 0; i < 48; i++) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }

            dracula->drawFlags = DRAW_HIDE;
            dracula->opacity = 0;
            dracula->ext.dracula.unkA0 = 1;
            step++;
        }
        break;

    case 7:
        prim = dracula->ext.dracula.unk80;
        color = prim->r0;
        color -= 16;
        if (color < 0) {
            color = 0;
        }

        // note: rgb set backwards here
        prim->g0 = prim->b0 = prim->r0 = color;
        if (prim->r0 < 16) {
            prim->drawMode = DRAW_HIDE;
            step++;
        }
        break;

    case 8:
        dracula->opacity += 10;
        if (dracula->opacity >= 0x80) {
            dracula->opacity = 0x80;
            dracula->drawFlags = FLAG_DRAW_DEFAULT;
            step++;
        }
        break;

    case 9:
        prim = dracula->ext.dracula.prim;
        while (prim != 0) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        if (dracula->ext.dracula.unkA1) {
            dracula->ext.dracula.unkA1 = 0;
        }
        step = 0xFF;
        break;
    }

    return step;
}

// This function is not called from anywhere. Don't know what it's for.
static s32 func_801AC458(s16 arg0) {
    s32 ret = arg0;
    Entity* e;
    Entity* e2;

    switch (ret) {
    case 0:
        e = g_CurrentEntity;
        ret = 1;
        e[1].drawFlags = FLAG_DRAW_SCALEY;
        e[1].scaleY = 0x600;
        e[1].pose = 0;
        e[1].poseTimer = 0;
        e[1].step = 2;
        e[1].posX.i.hi = e->posX.i.hi;
        e[1].posY.i.hi = e->posY.i.hi + 16;

    case 1:
        e2 = &g_CurrentEntity[1];
        if (AnimateEntity(D_80180964, e2) == 0) {
            ret++;
        }
        if (e2->pose == 6 && e2->poseTimer == 0) {
            // Using dracula ext since this function is right after dracula.
            g_CurrentEntity->ext.dracula.unkA0 = 1;
        }
        break;

    case 2:
        e = &g_CurrentEntity[1];
        e->animCurFrame = 0;
        e->drawFlags = FLAG_DRAW_DEFAULT;
        e->step = 1;
        ret = 0xFF;
        break;
    }
    return ret;
}

extern u32 g_CutsceneFlags;
void EntityDracula(Entity* self) {
    Primitive* prim;
    Entity* entity;
    u32 rand;
    s32 i;
    s32 xOffset;
    u32 count;
    s32 primIndex;

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        self->hitboxState = 0;
        (self + 1)->hitboxState = 0;
        SetStep(8);
    }

    if (self->hitFlags == 1) {
        g_api.PlaySfx(SFX_DRACULA_PAIN_D);
    }

    if (self->hitFlags == 2) {
        g_api.PlaySfx(SFX_DRACULA_PAIN_E);
    }

    if (self->hitFlags == 3) {
        g_api.PlaySfx(SFX_DRACULA_PAIN_F);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDracula);
        self->animCurFrame = 0x4F;
        self->hitboxState = 0;
        self->ext.dracula.unkA1 = 1;
        self->facingLeft = 1;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID(DRACULA_UNK1D), entity);
        entity->zPriority = self->zPriority + 1;

        primIndex = g_api.func_800EDB58(PRIM_GT4, 128);
        if (primIndex == -1) {
            self->step = 0;
            break;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.dracula.prim = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        SetStep(2);
        break;

    case 2:
        SetStep(3);
        break;

    case 3:
        switch (self->step_s) {
        case 0:
            if (g_CutsceneFlags & 0x10) {
                SetSubStep(1);
            }
            break;

        case 1:
            if (!AnimateEntity(D_80180A0C, self) && (g_CutsceneFlags & 0x20)) {
                SetSubStep(2);
            }
            break;

        case 2:
            if (!AnimateEntity(D_80180A20, self)) {
                g_CutsceneFlags |= 0x100;
            }
            if (g_CutsceneFlags & 0x40) {
                D_8003C744 = 1;
                SetSubStep(3);
            }
            if (self->pose == 2 && !self->poseTimer) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(DRACULA_UNK1F), self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->posX.i.hi -= 8;
                    entity->posY.i.hi -= 24;
                }
            }
            break;

        case 3:
            if (!AnimateEntity(D_80180A2C, self)) {
                g_api.TimeAttackController(
                    TIMEATTACK_EVENT_DRACULA_DEFEAT, TIMEATTACK_SET_VISITED);
                SetStep(4);
            }
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->ext.dracula.unk9C = 0;
            self->step_s++;
            // fallthrough
        case 1:
            self->ext.dracula.unk9C =
                func_801ABBBC(self->ext.dracula.unk9C, self);
            if (self->ext.dracula.unkA0) {
                g_api.PlaySfx(SFX_DRACULA_LAUGH_B);
                self->animCurFrame = 0;
                self->ext.dracula.unkA0 = 0;
            }
            if (self->ext.dracula.unk9C == 0xFF) {
                self->step_s++;
            }
            break;

        case 2:
            SetStep(5);
            break;
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            self->ext.dracula.unk8C = 0x80;
            self->step_s++;
            // fallthrough
        case 1:
            if (!--self->ext.dracula.unk8C) {
                rand = Random() & 7;
                self->posX.i.hi = D_80180A48[rand];
                self->posY.i.hi = 0x82;
                self->ext.dracula.unk9C = 0;
                self->step_s++;
            }
            break;

        case 2:
            self->ext.dracula.unk9C =
                func_801ABBBC(self->ext.dracula.unk9C, self);
            if (self->ext.dracula.unkA0) {
                g_api.PlaySfx(SFX_DRACULA_LAUGH_A);
                self->animCurFrame = 1;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->ext.dracula.unkA0 = 0;
            }
            if (self->ext.dracula.unk9C == 0xFF) {
                self->step_s++;
            }
            break;

        case 3:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->hitboxState = 3;
            self->ext.dracula.unkA2++;
            self->ext.dracula.unkA2 &= 3;
            if (!self->ext.dracula.unkA2) {
                SetStep(6);
                break;
            }
            SetStep(7);
        }
        break;

    case 7:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_80180914, self)) {
                entity = self + 1;
                entity->poseTimer = 0;
                entity->pose = 0;
                SetSubStep(1);
#ifdef VERSION_PSP
                g_api.PlaySfx(SFX_PSP_DRACULA_PAIN_A);
#else
                g_api.PlaySfx(SFX_DRACULA_PAIN_A);
#endif
            }
            break;

        case 1:
            entity = self + 1;
            if (!AnimateEntity(D_801809A4, entity)) {
                entity->animCurFrame = 0;
                SetSubStep(2);
            }
            break;

        case 2:
            for (i = 0; i < 3; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(DRACULA_UNK1B), self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->zPriority = self->zPriority + 1;
                    entity->params = i;
                    if (self->facingLeft) {
                        entity->posX.i.hi -= 24;
                    } else {
                        entity->posX.i.hi += 24;
                    }
                    entity->posY.i.hi += 44;
                }
            }
            self->step_s++;

        case 3:
            if (!AnimateEntity(D_80180924, self)) {
                SetStep(4);
            }
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_80180934, self)) {
                SetSubStep(1);
                self->ext.dracula.unk8C = 2;
                g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
                g_api.PlaySfx(SFX_DRACULA_HERE_IS_TRUE_POWER);
            }
            break;

        case 1:
        case 2:
            if (!--self->ext.dracula.unk8C) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(DRACULA_UNK1C), self, entity);
                    i = self->step_s - 1;
                    entity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        entity->posX.i.hi += D_80180A58[i].x;
                    } else {
                        entity->posX.i.hi -= D_80180A58[i].x;
                    }
                    entity->posY.i.hi += D_80180A58[i].y;
                    entity->zPriority = self->zPriority + 1;
                    entity->params = i;
                }
                self->ext.dracula.unk8C = 0x20;
                self->step_s++;
            }
            break;

        case 3:
            if (!--self->ext.dracula.unk8C) {
                self->step_s++;
            }
            break;

        case 4:
            if (!AnimateEntity(D_80180944, self)) {
                SetStep(4);
            }
        }
        break;

    case 8:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            g_isDraculaFirstFormDefeated = true;
            prim = self->ext.dracula.prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            g_api.PlaySfx(SFX_DRACULA_PLAYTIME_IS_OVER);
            self->step_s++;

        case 1:
            if (!AnimateEntity(D_80180954, self)) {
                self->ext.dracula.unk8C = 0x28;
                self->unk5A = 0x59;
                self->step_s++;
            }
            if (!self->poseTimer && self->pose == 5) {
                g_api.func_80102CD8(2);
            }
            break;

        case 2:
            if (!--self->ext.dracula.unk8C) {
                g_api.PlaySfx(SFX_DRACULA_GRANT_ME_POWER);
                self->step_s++;
            }
            break;

        case 3:
            self->ext.dracula.unk94 = 0x40;
            self->ext.dracula.unk98 = 0;
            self->opacity = 0x80;
            self->drawFlags |= FLAG_DRAW_OPACITY;
            prim = self->ext.dracula.prim;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            PGREY(prim, 0) = self->ext.dracula.unk94;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0xC0;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;

            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            PGREY(prim, 0) = 0;
            LOW(prim->r2) = LOW(prim->r0);
            PGREY(prim, 1) = self->ext.dracula.unk94;
            LOW(prim->r3) = LOW(prim->r1);
            prim->priority = 0xC0;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;

            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            PGREY(prim, 0) = self->ext.dracula.unk94;
            LOW(prim->r2) = LOW(prim->r0);
            PGREY(prim, 1) = 0;
            LOW(prim->r3) = LOW(prim->r1);
            prim->priority = 0xC0;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            // This gets unused and is likely just a copy-paste mistake
            prim = prim->next;

            self->ext.dracula.unk8C = 0x20;
            self->step_s++;
            // fallthrough
        case 4:
            prim = self->ext.dracula.prim;
            prim = prim->next;

            prim->x0 = prim->x2 -= 2;
            prim = prim->next;

            prim->x1 = prim->x3 += 2;
            xOffset = prim->x1 - self->posX.i.hi;
            if (xOffset == 0x30) {
                self->step_s++;
            }

            break;

        case 5:
            count = 0;
            self->ext.dracula.unk98 += 4;
            xOffset = self->posX.i.hi - self->ext.dracula.unk98;
            if (xOffset < 0) {
                count++;
                xOffset = 0;
            }

            prim = self->ext.dracula.prim;
            prim->x0 = prim->x2 = xOffset;
            prim = prim->next;

            prim->x0 = prim->x2 = xOffset - 0x30;
            prim->x1 = prim->x3 = xOffset;

            xOffset = self->posX.i.hi + self->ext.dracula.unk98;
            if (xOffset > 0x100) {
                count++;
                xOffset = 0x100;
            }

            prim = self->ext.dracula.prim;
            prim->x1 = prim->x3 = xOffset;
            prim = prim->next;
            prim = prim->next;

            prim->x0 = prim->x2 = xOffset;
            prim->x1 = prim->x3 = xOffset + 0x30;

            if (self->opacity) {
                self->opacity -= 8;
            }

            if (self->ext.dracula.unk94 < 0xF0) {
                self->ext.dracula.unk94 += 8;
            }

            prim = self->ext.dracula.prim;
            PGREY(prim, 0) = self->ext.dracula.unk94;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;

            PGREY(prim, 0) = 0;
            LOW(prim->r2) = LOW(prim->r0);
            PGREY(prim, 1) = self->ext.dracula.unk94;
            LOW(prim->r3) = LOW(prim->r1);
            prim = prim->next;

            PGREY(prim, 0) = self->ext.dracula.unk94;
            LOW(prim->r2) = LOW(prim->r0);
            PGREY(prim, 1) = 0;
            LOW(prim->r3) = LOW(prim->r1);

            if (count == 2) {
                self->step_s++;
            }
            break;

        case 6:
            prim = self->ext.dracula.prim;
            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }

            entity = self + 2;
            CreateEntityFromCurrentEntity(E_ID(DRACULA_UNK2B), entity);
            entity->facingLeft = self->facingLeft;

            entity = self + 5;
            CreateEntityFromCurrentEntity(E_ID(DRACULA_UNK20), entity);
            entity->facingLeft = self->facingLeft;
            entity->posY.i.hi += 2;
            self->step_s++;
            break;

        case 7:
            prim = self->ext.dracula.prim;
            if (PrimDecreaseBrightness(prim, 7) == 0) {
                self->step_s++;
            }
            break;

        case 8:
            if (D_801C2578 == 0) {
                DestroyEntity(self);
            }
            break;
        }
        break;

    case 255:
        /**
         * Debug: Press SQUARE / CIRCLE on the second controller
         * to advance/rewind current animation frame
         * NOTE: This case is slightly different from other cases:
         * It does not have the "charal" print statement.
         */
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (!self->step_s) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
}

void EntityDraculaBody(Entity* self) {
    Entity* parent;
    if (g_isDraculaFirstFormDefeated) {
        DestroyEntity(self);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDracula);
        self->hitboxState = 1;
        self->hitPoints = 0x7FFF;
        self->animCurFrame = 0;
        self->hitboxOffX = 3;
        self->hitboxOffY = 0x27;
        self->hitboxWidth = 12;
        self->hitboxHeight = 34;
        break;
    case 1:
        parent = self - 1;
        self->facingLeft = parent->facingLeft;
        self->posX.i.hi = parent->posX.i.hi;
        self->posY.i.hi = parent->posY.i.hi;
        self->hitboxState = parent->hitboxState;
        self->hitboxState &= 0xFFFD;
        break;
    case 2:
        self->hitboxState = 0;
        break;
    }

#ifndef VERSION_PSP
    if (g_isDraculaFirstFormDefeated) {
        self->hitboxState = 0;
    }
#endif
}

void EntityDraculaFireball(Entity* self) {
    if (g_isDraculaFirstFormDefeated) {
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
        self->step = 0;
        self->pfnUpdate = EntityExplosion;
        self->params = 2;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaFireball);

        if (self->facingLeft) {
            self->velocityX = FIX(2);
        } else {
            self->velocityX = FIX(-2);
        }

        if (self->params == 1) {
            self->velocityY = FIX(-0.5);
        }

        if (self->params == 2) {
            self->velocityY = FIX(0.5);
        }
        self->ext.dracula.unk8C = 0x28;

    case 1:
        AnimateEntity(D_8018097C, self);
        MoveEntity();

        if (!--self->ext.dracula.unk8C) {
            self->velocityY = 0;
        }
        return;
    }
}

extern EInit g_EInitDraculaMeteorball;
void EntityDraculaMeteorball(Entity* entity) {
    Entity* newEntity;
    s32 randomPosXYIndex;
    s32 speedX;

    if (g_isDraculaFirstFormDefeated) {
        entity->entityId = E_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->step = 0;
        entity->step_s = 0;
        entity->params = 1;
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitDraculaMeteorball);
        entity->drawFlags |= FLAG_DRAW_ROTATE;
        entity->hitboxState = 0;
        break;
    case 1:
        if (AnimateEntity(D_801809B0, entity) == 0) {
            entity->hitboxState = 1;
            SetStep(2);
        }
        break;
    case 2:
        AnimateEntity(D_80180990, entity);
        MoveEntity();
        entity->rotate += 4;

        if (entity->params) {
            speedX = 0xE00;
        } else {
            speedX = 0x1000;
        }

        if (entity->facingLeft) {
            entity->velocityX += speedX;
        } else {
            entity->velocityX -= speedX;
        }

        if (!(g_Timer & 3)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != 0) {
                CreateEntityFromEntity(E_ID(DRACULA_METEOR), entity, newEntity);
                newEntity->zPriority = entity->zPriority + 1;
                randomPosXYIndex = (Random() & 3);
                newEntity->posX.i.hi += D_80180A60[randomPosXYIndex].x;
                newEntity->posY.i.hi += D_80180A60[randomPosXYIndex].y;
            }
        }
        break;
    }
}

extern EInit g_EInitDraculaFireball;
extern u8 D_801809E0[];
void func_801AD838(Entity* entity) {
    if (g_isDraculaFirstFormDefeated) {
        DestroyEntity(entity);
        return;
    }

    if (!entity->step) {
        InitializeEntity(g_EInitDraculaFireball);
        entity->animCurFrame = 0;
        entity->hitboxState = 0;
        entity->velocityY = FIX(-1);
    }
    MoveEntity();

    if (!AnimateEntity(D_801809E0, entity)) {
        DestroyEntity(entity);
    }
}

extern EInit g_EInitDraculaFireball;
extern u8 D_80180A40[];
void EntityDraculaGlass(Entity* entity) {
    Entity* glassShardEntity;
    s32 i;
    s32 speed;
    s16 radians;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitDraculaFireball);
        entity->animCurFrame = 0x59;
        entity->hitboxState = 0;
        entity->drawFlags = FLAG_DRAW_ROTATE;
        entity->velocityX = FIX(-1);
        entity->velocityY = 0;
        if (entity->params) {
            entity->animCurFrame = 0x5C;
            speed = (Random() & 0x1F) + 0x10;
            radians = (Random() * 6) + 0x900;
            entity->velocityX = speed * rcos(radians);
            entity->velocityY = speed * rsin(radians);
            SetStep(3);
        }
    case 1:
        MoveEntity();
        entity->rotate += 0x20;
        entity->velocityY += FIX(0.125);
        if (entity->posY.i.hi > 204) {
            g_api.PlaySfx(SFX_DRA_GLASS_BREAK); // "What is a man?!"
            entity->posY.i.hi = 204;
            SetStep(2);
        }
        break;
    case 2:
        entity->drawFlags = FLAG_DRAW_DEFAULT;
        if (!AnimateEntity(D_80180A40, entity)) {
            for (i = 0; i < 8; i++) {
                glassShardEntity =
                    AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (glassShardEntity != 0) {
                    CreateEntityFromEntity(
                        E_ID(DRACULA_UNK1F), entity, glassShardEntity);
                    glassShardEntity->params = 1;
                }
            }
            DestroyEntity(entity);
        }
        break;
    case 3:
        MoveEntity();
        entity->velocityY += FIX(0.125);
        if (entity->posY.i.hi > 204) {
            DestroyEntity(entity);
        }
        break;
    }
}
