// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "sfx.h"

static bool g_isDraculaFirstFormDefeated = false;
s32 D_80180910 = 0;
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
static u16 D_80180A48[] = {0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0, 0x90};
static Point16 D_80180A58[] = {{16, 28}, {20, 60}};
static Point16 D_80180A60[] = {
    {12, 12}, {12, -12}, {-12, 12}, {-12, -12}, {80, 64}, {48, 34},
    {26, 20}, {18, 16},  {15, 13},  {13, 12},   {12, 11}, {11, 10},
    {10, 10}, {9, 9},    {9, 8},    {8, 8},     {8, 4}};

// Helper function for EntityDracula
static u32 func_801ABBBC(s32 step, Entity* dracula) {
    draculaPrimitive* prim;
    s32 randVar;
    s32 randVar2;
    s32 colorLimit;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 i;
    s32 var_t0;
    s32 fake_a2;
    s32 color;
    u8* redPtr;
    u8* greenPtr;
    u8 constFF;

    switch (step) {
    case 0:
        prim = dracula->ext.dracula.prim;
        dracula->ext.dracula.unk80 = prim;
        for (i = 0; i < 16; i++) {
            prim->type = PRIM_LINE_G2_ALT;
            if (i == 15) {
                prim->type = PRIM_LINE_G2;
            }
            if (i & 1) {
                prim->x0 = prim->x1 = dracula->posX.i.hi + i / 2;
            } else {
                prim->x0 = prim->x1 = dracula->posX.i.hi - i / 2;
            }

            prim->y0 = prim->y1 = 0;
            prim->r0 = prim->g0 = prim->b0 = 0x70;
            prim->r1 = prim->g1 = prim->b1 = 0;
            randVar = Random();
            prim->r2 = (((randVar & 1) * 0x10) + 0x10);
            prim->g2 = (((randVar * 8) & 0x10) + 0x10);
            prim->b2 = (((randVar * 4) & 0x10) + 0x10);
            prim->priority = dracula->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            if (i == 0) {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        step++;
        dracula->ext.dracula.unk90 = 1;
        dracula->ext.dracula.unk92 = 0;
        dracula->ext.dracula.unk8C = 0;
        break;
    case 1:
        if (dracula->ext.dracula.unk8C++ >= 3) {
            dracula->ext.dracula.unk90 += 2;
            if (dracula->ext.dracula.unk90 >= 16) {
                dracula->ext.dracula.unk90 = 16;
            }
            dracula->ext.dracula.unk8C = 0;
        }
        prim = dracula->ext.dracula.unk80;
        i = 0;
        for (i = 0; i < dracula->ext.dracula.unk90; i++) {
            prim->y1 += 0x30;
            if (dracula->ext.dracula.unkA1 != 0) {
                if (prim->y1 >= 171) {
                    prim->y1 = 171;
                }
            } else if (prim->y1 >= 203) {
                prim->y1 = 203;
            }
            // Iterate through r1, g1, and b1.
            for (redPtr = &prim->r1, var_a1 = 0; var_a1 < 3; redPtr++,
                var_a1++) {
                color = *redPtr;
                if (color < 0xFF) {
                    // This ends up offsetting to r2, g2, and b2
                    color += redPtr[0xC];
                    if (color > 0xFF) {
                        color = 0xFF;
                    }
                }
                *redPtr = color;
            }
            prim = prim->next;
        }
        if (dracula->ext.dracula.unk92++ >= 25) {
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
            prim->r0 = prim->g0 = prim->b0 = 0x70;
            prim->r1 = prim->g1 = prim->b1 = 0x20;
            randVar2 = Random();
            prim->r2 = (((randVar2 & 1) * 4) + 4);
            prim->g2 = (((randVar2 * 2) & 4) + 4);
            prim->b2 = ((randVar2 & 4) + 4);
            if (i & 1) {
                prim->x0 = prim->x1 = dracula->posX.i.hi + i / 2;
            } else {
                prim->x0 = prim->x1 = dracula->posX.i.hi - i / 2;
            }
            if (dracula->ext.dracula.unkA1 != 0) {
                prim->y0 = prim->y1 = 171;
                if (i >= 0x22) {
                    prim->y0 = prim->y1 = -0x20;
                }
            } else {
                prim->y0 = prim->y1 = 203;
            }
            prim->y1_f32.i.lo = 0;
            prim->y1_f32.i.hi = prim->y1;
            // FAKE variable reuse
            color = (i >> 1);
            prim->y1_f32_velocity.val =
                ((color * color * color) << 8) + 0x80000;
            prim->priority = dracula->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            if (i == 0) {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        step++;
        dracula->ext.dracula.unk8C = 0;
        g_api.PlaySfx(SFX_TELEPORT_BANG_B);
        break;
    case 3:
        prim = dracula->ext.dracula.unk84;
        if (dracula->ext.dracula.unkA1 != 0) {
            var_a1 = 0x22;
        } else {
            var_a1 = 0x30;
        }
        for (i = 0; i < var_a1; prim = prim->next) {
            prim->y1_f32.i.hi = prim->y1;
            prim->y1_f32.val -= prim->y1_f32_velocity.val;
            prim->y1 = prim->y1_f32.i.hi;
            i++;
            if (prim->y1 < 0) {
                prim->y1 = 0U;
            }
        }
        if (++dracula->ext.dracula.unk8C < 9) {
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
        for (i = 0, constFF = 0xFF, colorLimit = 0xFF; i < 48; i++) {
            color = prim->r0;
            color += 4;
            prim->r0 = (color > colorLimit ? colorLimit : color);
            colorLimit -= 2;
            if (prim->r0 >= 0xFF) {
                prim->r0 = constFF;
                step = 4;
            }
            prim->b0 = prim->g0 = prim->r0;
            prim = prim->next;
        }
        var_a2 = 0xFF;
        prim = dracula->ext.dracula.unk84;
        for (i = 0; i < 48; i++) {
            redPtr = &prim->r1;
            for (var_a1 = 0; var_a1 < 3; var_a1 += 1) {
                color = *redPtr;
                color += redPtr[0xC];
                if (var_a2 < color) {
                    color = var_a2;
                }
                *redPtr = color;
                redPtr++;
            }
            prim = prim->next;
            var_a2 -= 2;
        }
        break;
    case 4:
        var_t0 = 1;
        prim = dracula->ext.dracula.unk84;
        for (i = 0, var_a3 = 0xFF; i < 48; i++) {

            for (redPtr = &prim->r1, var_a1 = 0, var_a2 = var_a3; var_a1 < 3;
                 redPtr++, var_a1++) {
                color = *redPtr;
                color += 0x18;
                if (var_a2 < color) {
                    color = var_a2;
                } else {
                    var_t0 = 0;
                }
                *redPtr = color;
            }
            prim = prim->next;
            var_a3 -= 2;
        }
        if (var_t0 != 0) {
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
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->y0 = 0;
        if (dracula->ext.dracula.unkA1 != 0) {
            prim->x0 = dracula->posX.i.hi - 17;
            prim->u0 = 0x22;
            prim->v0 = 0xAC;
        } else {
            prim->x0 = dracula->posX.i.hi - 24;
            prim->u0 = 0x30;
            prim->v0 = 0xCC;
        }
        step++;
        prim->priority = dracula->zPriority + 1;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        dracula->ext.dracula.unk8C = 0;
        break;
    case 6:
        var_t0 = 1;
        prim = dracula->ext.dracula.unk84;
        for (i = 0; i < 48; i++) {
            redPtr = &prim->r0;
            var_a1 = 0;
            greenPtr = &prim->g0;
            for (; var_a1 < 2;) {
                color = *redPtr;
                color -= 10;
                if (color < 0) {
                    color = 0;
                } else {
                    var_t0 = 0;
                }
                var_a1++;
                greenPtr[0] = greenPtr[1] = color;
                greenPtr += 0xC;
                *redPtr = color;
                redPtr += 0xC;
            }
            prim = prim->next;
        }
        prim = dracula->ext.dracula.unk80;
        prim->r0 += 7;
        if (prim->r0 > 0xE0) {
            prim->r0 = 0xE0;
        } else {
            var_t0 = 0;
        }
        prim->g0 = prim->b0 = prim->r0;
        if (var_t0 != 0) {
            prim = dracula->ext.dracula.unk84;
            for (i = 0; i < 48; i++) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            step++;
            dracula->drawFlags = DRAW_HIDE;
            dracula->unk6C = 0;
            dracula->ext.dracula.unkA0 = 1;
        }
        break;
    case 7:
        prim = dracula->ext.dracula.unk80;
        color = prim->r0;
        color -= 16;
        if (color < 0) {
            color = 0;
        }
        prim->g0 = prim->b0 = prim->r0 = color;
        if (prim->r0 < 16) {
            prim->drawMode = DRAW_HIDE;
            step++;
        }
        break;
    case 8:
        dracula->unk6C += 10;
        if (dracula->unk6C >= 0x80U) {
            step++;
            dracula->unk6C = 0x80U;
            dracula->drawFlags = FLAG_DRAW_DEFAULT;
        }
        break;
    case 9:
        prim = dracula->ext.dracula.prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        step = 0xFF;
        if (dracula->ext.dracula.unkA1 != 0) {
            dracula->ext.dracula.unkA1 = 0U;
        }
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
        e[1].drawFlags = FLAG_DRAW_ROTY;
        e[1].rotY = 0x600;
        e[1].animFrameIdx = 0;
        e[1].animFrameDuration = 0;
        e[1].step = 2;
        e[1].posX.i.hi = e->posX.i.hi;
        e[1].posY.i.hi = e->posY.i.hi + 16;

    case 1:
        e2 = &g_CurrentEntity[1];
        if (AnimateEntity(D_80180964, e2) == 0) {
            ret++;
        }
        if (e2->animFrameIdx == 6 && e2->animFrameDuration == 0) {
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
    s16 primIndex;
    Entity* newEntity;
    Primitive* prim;
    s16 temp_v1_8;
    u16 temp_v1_6;
    s32 var_a0_2;
    s16 temp_19;
    s16 temp_20;
    s32 var_a1;
    s32 index;
    u16 posX;
    s32 i;

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        self->hitboxState = 0;
        self[1].hitboxState = 0;
        SetStep(8);
    }

    index = 1; // !FAKE

    if (self->hitFlags == 1) {
        g_api.PlaySfx(NA_SE_VO_DR_HURT_2);
    }

    if (self->hitFlags == 2) {
        g_api.PlaySfx(NA_SE_VO_DR_HURT_3);
    }

    if (self->hitFlags == 3) {
        g_api.PlaySfx(NA_SE_VO_DR_HURT_4);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDracula);
        self->animCurFrame = 0x4F;
        self->ext.dracula.unkA1 = 1;
        self->hitboxState = 0;
        self->facingLeft = 1;
        CreateEntityFromCurrentEntity(E_DRACULA_UNK1D, &self[1]);
        self[1].zPriority = self->zPriority + 1;

        primIndex = g_api.AllocatePrimitives(PRIM_GT4, 128);
        if (primIndex == -1) {
            self->step = 0;
            break;
        }

        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.dracula.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
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
            if ((AnimateEntity(D_80180A0C, self) == 0) &&
                (g_CutsceneFlags & 0x20)) {
                SetSubStep(2);
            }
            break;

        case 2:
            if (AnimateEntity(D_80180A20, self) == 0) {
                g_CutsceneFlags |= 0x100;
            }
            if (g_CutsceneFlags & 0x40) {
                D_8003C744 = 1;
                SetSubStep(3);
            }
            if (self->animFrameIdx == 2 && self->animFrameDuration == 0) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_DRACULA_UNK1F, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->posX.i.hi -= 8;
                    newEntity->posY.i.hi -= 24;
                }
            }
            break;

        case 3:
            if (AnimateEntity(D_80180A2C, self) == 0) {
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

        case 1:
            self->ext.dracula.unk9C =
                func_801ABBBC(self->ext.dracula.unk9C, self);
            if (self->ext.dracula.unkA0 != 0) {
                g_api.PlaySfx(NA_SE_VO_DR_TAUNT_2);
                self->animCurFrame = 0;
                self->ext.dracula.unkA0 = 0;
            }
            if (self->ext.dracula.unk9C != 0xFF) {
                break;
            }
            self->step_s++;
            break;

        case 2:
            SetStep(5);
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            self->ext.dracula.unk8C = 0x80;
            self->step_s++;

        case 1:
            if (--self->ext.dracula.unk8C == 0) {
                posX = D_80180A48[Random() & 7];
                self->posY.i.hi = 0x82;
                self->ext.dracula.unk9C = 0;
                self->posX.i.hi = posX;
                self->step_s++;
            }
            break;

        case 2:
            self->ext.dracula.unk9C =
                func_801ABBBC(self->ext.dracula.unk9C, self);
            if (self->ext.dracula.unkA0 != 0) {
                g_api.PlaySfx(NA_SE_VO_DR_TAUNT_1);
                self->animCurFrame = 1;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->ext.dracula.unkA0 = 0;
            }
            if (self->ext.dracula.unk9C != 0xFF) {
                break;
            }
            self->step_s++;
            break;

        case 3:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.dracula.unkA2 = (self->ext.dracula.unkA2 + 1) & 3;
            self->hitboxState = 3;
            if (self->ext.dracula.unkA2 == 0) {
                SetStep(6);
                break;
            }
            SetStep(7);
        }
        break;

    case 7:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80180914, self) == 0) {
                self[1].animFrameDuration = 0;
                self[1].animFrameIdx = 0;
                SetSubStep(1);
                g_api.PlaySfx(NA_SE_VO_DR_HURT_1);
            }
            break;

        case 1:
            if (AnimateEntity(D_801809A4, &self[1]) == 0) {
                self[1].animCurFrame = 0;
                SetSubStep(2);
            }
            break;

        case 2:
            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_DRACULA_UNK1B, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->params = i;
                    if (self->facingLeft != 0) {
                        newEntity->posX.i.hi -= 24;
                    } else {
                        newEntity->posX.i.hi += 24;
                    }
                    newEntity->posY.i.hi += 44;
                }
            }
            self->step_s++;

        case 3:
            if (AnimateEntity(D_80180924, self) == 0) {
                SetStep(4);
            }
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80180934, self) == 0) {
                SetSubStep(1);
                self->ext.dracula.unk8C = 2;
                g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
                g_api.PlaySfx(NA_SE_VO_DR_HERE_IS_TRUE_POWER);
            }
            break;

        case 1:
        case 2:
            if (--self->ext.dracula.unk8C == 0) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_DRACULA_UNK1C, self, newEntity);
                    index = self->step_s - 1;
                    newEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft != 0) {
                        newEntity->posX.i.hi += D_80180A58[index].x;
                    } else {
                        newEntity->posX.i.hi -= D_80180A58[index].x;
                    }
                    newEntity->posY.i.hi += D_80180A58[index].y;
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->params = index;
                }
                self->ext.dracula.unk8C = 0x20;
                self->step_s++;
            }
            break;

        case 3:
            if (--self->ext.dracula.unk8C == 0) {
                self->step_s++;
            }
            break;

        case 4:
            if (AnimateEntity(D_80180944, self) == 0) {
                SetStep(4);
            }
        }
        break;

    case 8:
        switch (self->step_s) {
        case 0:
            prim = self->ext.dracula.prim;
            self->hitboxState = 0;
            g_isDraculaFirstFormDefeated = 1;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            g_api.PlaySfx(NA_SE_VO_DR_PLAYTIME_IS_OVER);
            self->step_s++;

        case 1:
            if (AnimateEntity(D_80180954, self) == 0) {
                self->ext.dracula.unk8C = 0x28;
                self->unk5A = 0x59;
                self->step_s++;
            }
            if (self->animFrameIdx == 5 && self->animFrameDuration == 0) {
                g_api.func_80102CD8(2);
            }
            break;

        case 2:
            if (--self->ext.dracula.unk8C == 0) {
                g_api.PlaySfx(NA_SE_VO_DR_GRANT_ME_POWER);
                self->step_s++;
            }
            break;

        case 3:
            prim = self->ext.dracula.prim;
            self->ext.dracula.unk94 = 0x40;
            self->ext.dracula.unk98 = 0;
            self->unk6C = 0x80;
            self->drawFlags |= FLAG_DRAW_UNK8;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->g0 = prim->b0 = self->ext.dracula.unk94;
            prim->priority = 0xC0;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = prim->r0 = prim->g0 = prim->b0 = 0;
            prim->y2 = prim->y3 = 0x100;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = self->ext.dracula.unk94;
            prim->priority = 0xC0;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            LOW(prim->r3) = LOW(prim->r1);
            prim = prim->next;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->g0 = prim->b0 = self->ext.dracula.unk94;
            prim->r1 = prim->g1 = prim->b1 = 0;
            prim->priority = 0xC0;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r1);
            self->ext.dracula.unk8C = 0x20;
            self->step_s++;

        case 4:
            prim = self->ext.dracula.prim;
            prim = prim->next;

            prim->x0 = prim->x2 = prim->x2 - 2;
            prim = prim->next;

            temp_19 = prim->x3 + 2;
            prim->x1 = prim->x3 = temp_19;
            if (self->posX.i.hi != (temp_19 - 0x30)) {
                break;
            }
            self->step_s++;
            break;

        case 5:
            var_a1 = 0;
            temp_20 = self->ext.dracula.unk98 + 4;
            var_a0_2 = self->posX.i.hi - temp_20;
            self->ext.dracula.unk98 = temp_20;
            if (var_a0_2 < 0) {
                var_a1 = 1;
                var_a0_2 = 0;
            }

            prim = self->ext.dracula.prim;
            temp_v1_6 = var_a0_2;
            prim->x0 = prim->x2 = temp_v1_6;
            prim = prim->next;
            prim->x0 = prim->x2 = temp_v1_6 - 0x30;
            prim->x1 = prim->x3 = temp_v1_6;

            var_a0_2 = self->posX.i.hi + self->ext.dracula.unk98;
            if (var_a0_2 > 0x100) {
                var_a1 += 1;
                var_a0_2 = 0x100;
            }
            temp_v1_8 = var_a0_2 + 0x30;

            prim = self->ext.dracula.prim;
            prim->x1 = prim->x3 = var_a0_2;
            prim = prim->next;

            prim = prim->next;
            prim->x0 = prim->x2 = var_a0_2;
            prim->x1 = prim->x3 = temp_v1_8;

            if (self->unk6C != 0) {
                self->unk6C += 0xF8;
            }

            if (self->ext.dracula.unk94 < 0xF0) {
                self->ext.dracula.unk94 += 8;
            }

            prim = self->ext.dracula.prim;
            prim->r0 = prim->g0 = prim->b0 = self->ext.dracula.unk94;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);

            prim = prim->next;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = self->ext.dracula.unk94;
            LOW(prim->r3) = LOW(prim->r1);

            prim = prim->next;
            prim->r0 = prim->g0 = prim->b0 = self->ext.dracula.unk94;
            prim->r1 = prim->g1 = prim->b1 = 0;
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r1);

            if (var_a1 == 2) {
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
            CreateEntityFromCurrentEntity(E_DRACULA_UNK2B, &self[2]);
            self[2].facingLeft = self->facingLeft;
            CreateEntityFromCurrentEntity(E_DRACULA_UNK20, &self[5]);
            self[5].facingLeft = self->facingLeft;
            self[5].posY.i.hi += 2;
            self->step_s++;
            break;

        case 7:
            if (PrimDecreaseBrightness(self->ext.dracula.prim, 7) == 0) {
                self->step_s++;
            }
            break;

        case 8:
            if (D_801C2578 == 0) {
                DestroyEntity(self);
            }
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
            if (self->params == 0) {
                self->animCurFrame++;
                self->params |= 1;
            } else {
                break;
            }
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame--;
                self->step_s |= 1;
                break;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
}

void EntityDraculaBody(Entity* self) {
    if (g_isDraculaFirstFormDefeated) {
        DestroyEntity(self);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDracula);
        self->hitboxState = 1;
        self->hitPoints = 0x7FFF;
        self->hitboxOffX = 3;
        self->hitboxOffY = 0x27;
        self->hitboxWidth = 12;
        self->animCurFrame = 0;
        self->hitboxHeight = 34;
        break;
    case 1:
        self->facingLeft = self[-1].facingLeft;
        self->posX.i.hi = self[-1].posX.i.hi;
        self->posY.i.hi = self[-1].posY.i.hi;
        self->hitboxState = self[-1].hitboxState & 0xFFFD;
        break;
    case 2:
        self->hitboxState = 0;
        break;
    }

    if (g_isDraculaFirstFormDefeated) {
        self->hitboxState = 0;
    }
}

void EntityDraculaFireball(Entity* self) {
    if (g_isDraculaFirstFormDefeated) {
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
        self->pfnUpdate = EntityExplosion;
        self->step = 0;
        self->params = 2;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaFireball);

        if (self->facingLeft == 0) {
            self->velocityX = FIX(-2);
        } else {
            self->velocityX = FIX(2);
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

        if (--self->ext.dracula.unk8C == 0) {
            self->velocityY = 0;
        }
        return;
    }
}

extern EInit g_EInitDraculaMeteorball;
void EntityDraculaMeteorball(Entity* entity) {
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
        entity->hitboxState = 0;
        entity->drawFlags |= FLAG_DRAW_ROTZ;
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
        entity->rotZ += 4;
        speedX = 0x1000;
        if (entity->params != 0) {
            speedX = 0xE00;
        }

        if (entity->facingLeft != 0) {
            entity->velocityX += speedX;
        } else {
            entity->velocityX -= speedX;
        }

        if (!(g_Timer & 3)) {
            Entity* newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != 0) {
                s32 randomPosXYIndex;
                CreateEntityFromEntity(E_DRACULA_METEOR, entity, newEntity);
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

    if (entity->step == 0) {
        InitializeEntity(g_EInitDraculaFireball);
        entity->animCurFrame = 0;
        entity->hitboxState = 0;
        entity->velocityY = FIX(-1);
    }
    MoveEntity();

    if (AnimateEntity(D_801809E0, entity) == 0) {
        DestroyEntity(entity);
    }
}

extern EInit g_EInitDraculaFireball;
extern u8 D_80180A40[];
void EntityDraculaGlass(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitDraculaFireball);
        entity->animCurFrame = 0x59;
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->hitboxState = 0;
        entity->velocityX = FIX(-1);
        entity->velocityY = 0;
        if (entity->params) {
            s16 radians;
            s32 speed;
            entity->animCurFrame = 0x5C;
            speed = (Random() & 0x1F) + 0x10;
            radians = (Random() * 6) + 0x900;
            entity->velocityX = speed * rcos(radians);
            entity->velocityY = speed * rsin(radians);
            SetStep(3);
        }
    case 1:
        MoveEntity();
        entity->rotZ += 0x20;
        entity->velocityY += FIX(0.125);
        if (entity->posY.i.hi >= 205) {
            g_api.PlaySfx(SFX_DRA_GLASS_BREAK); // "What is a man?!"
            entity->posY.i.hi = 204;
            SetStep(2);
        }
        break;
    case 2:
        entity->drawFlags = FLAG_DRAW_DEFAULT;
        if (AnimateEntity(D_80180A40, entity) == 0) {
            s32 i;
            for (i = 0; i < 8; i++) {
                Entity* glassShardEntity =
                    AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (glassShardEntity != 0) {
                    CreateEntityFromEntity(
                        E_DRACULA_UNK1F, entity, glassShardEntity);
                    glassShardEntity->params = 1;
                }
            }
            DestroyEntity(entity);
        }
        break;
    case 3:
        MoveEntity();
        entity->velocityY += FIX(0.125);
        if (entity->posY.i.hi >= 205) {
            DestroyEntity(entity);
        }
        break;
    }
}
