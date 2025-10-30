// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"

// Animations for EntityDraculaFinalForm
static u8 anim_80180AA4[] = {
    0x18, 0x01, 0x0F, 0x02, 0x0F, 0x03, 0x0F, 0x02, 0x00, 0x00};
static u8 anim_80180AB0[] = {
    0x07, 0x01, 0x07, 0x04, 0x0B, 0x03, 0x06, 0x05, 0x04, 0x06, 0x03, 0x07,
    0x02, 0x08, 0x02, 0x0F, 0x01, 0x14, 0x01, 0x13, 0x01, 0x14, 0xFF, 0x00};
static u8 anim_80180AC8[] = {
    0x0E, 0x14, 0x01, 0x10, 0x03, 0x0F, 0x07, 0x11, 0x06, 0x12, 0xFF, 0x00};
static u8 anim_80180AD4[] = {
    0x04, 0x06, 0x03, 0x05, 0x01, 0x04, 0x04, 0x03, 0x03, 0x02, 0x04,
    0x01, 0x02, 0x02, 0x02, 0x03, 0x05, 0x02, 0x10, 0x01, 0xFF, 0x00};
static u8 anim_80180AEC[] = {0x09, 0x01, 0x09, 0x09, 0x09, 0x0A, 0x08,
                             0x06, 0x07, 0x19, 0x10, 0x06, 0xFF, 0x00};
static u8 anim_80180AFC[] = {
    0x08, 0x06, 0x01, 0x1C, 0x07, 0x0A, 0x01, 0x1D, 0x07, 0x09, 0x01, 0x1E,
    0x05, 0x01, 0x01, 0x1F, 0x03, 0x16, 0x01, 0x20, 0x04, 0x17, 0x01, 0x21,
    0x08, 0x18, 0x01, 0x22, 0x06, 0x1A, 0x10, 0x1B, 0xFF, 0x00};
static u8 anim_80180B20[] = {
    0x01, 0x1B, 0x04, 0x1A, 0x09, 0x18, 0x03, 0x17, 0x03, 0x16, 0x02, 0x01,
    0x01, 0x09, 0x01, 0x0A, 0x02, 0x06, 0x05, 0x19, 0x10, 0x06, 0xFF, 0x00};
static u8 anim_80180B38_unused[] = {0x0C, 0x06, 0x0B, 0x0A, 0x09, 0x09, 0x04,
                                    0x01, 0x07, 0x02, 0x10, 0x01, 0xFF, 0x00};
static u8 anim_80180B48[] = {0x09, 0x01, 0x05, 0x0B, 0x05, 0x0C, 0x06,
                             0x23, 0x05, 0x0A, 0x10, 0x01, 0xFF, 0x00};
static u8 anim_80180B58[] = {0x09, 0x01, 0x06, 0x0D, 0x09, 0x0E, 0xFF, 0x00};
static u8 anim_80180B60[] = {
    0x10, 0x01, 0x09, 0x24, 0x09, 0x24, 0x10, 0x01, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_80180B6C[] = {
    0x18, 0x01, 0x05, 0x31, 0x04, 0x04, 0x08, 0x03, 0x02,
    0x28, 0x04, 0x29, 0x04, 0x2A, 0x02, 0x18, 0xFF, 0x00};
static u8 anim_80180B80[] = {
    0x0C, 0x18, 0x03, 0x2B, 0x02, 0x2C, 0x01, 0x2D, 0x01, 0x2E,
    0x02, 0x2F, 0x01, 0x30, 0x01, 0x32, 0x01, 0x33, 0x02, 0x34,
    0x02, 0x35, 0x03, 0x36, 0x06, 0x13, 0x10, 0x36, 0xFF, 0x00};
static u8 anim_80180BA0[] = {
    0x04, 0x3D, 0x04, 0x3E, 0x04, 0x3F, 0x04, 0x40, 0x04, 0x41, 0x04, 0x42,
    0x04, 0x43, 0x04, 0x44, 0x04, 0x45, 0x04, 0x46, 0x06, 0x47, 0xFF, 0x00};
static u8 anim_80180BB8[] = {
    0x02, 0x48, 0x02, 0x49, 0x02, 0x4A, 0x02, 0x4B, 0x02,
    0x4C, 0x02, 0x4D, 0x02, 0x4E, 0x02, 0x4F, 0x00, 0x00};
static u8 anim_80180BCC[] = {0x01, 0x50, 0x01, 0x51, 0x01, 0x52, 0x01,
                             0x53, 0x01, 0x54, 0x01, 0x55, 0x00, 0x00};
static u8 anim_80180BDC[] = {0x01, 0x56, 0x01, 0x57, 0x01, 0x58, 0xFF, 0x00};

static s16 D_80180BE4[][3][4] = {
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-24, -16, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {34, 49, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -2, 28, 33}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -2, 28, 33}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -2, 28, 33}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -2, 28, 33}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
};
static s16 D_801810F4[] = {0x180, 0x300, 0x200, -1};
static s16 D_801810FC[] = {0xFFF0, 0x0018, 0x0030, 0xFFE0, 0x0008, 0xFFFF};
static s16 D_80181108[] = {
    0x0000, 0x0000, 0x0024, 0x0000, 0xFFF0, 0x0040, 0x0018, 0x0010,
    0x0000, 0x0040, 0xFFE0, 0x0020, 0x0008, 0x0000, 0x0014, 0x0018,
    0x0000, 0x0000, 0x0024, 0x0000, 0xFFF0, 0x0040, 0x0018, 0x0010,
    0x0000, 0x0040, 0xFFE0, 0x0020, 0x0008, 0x0000, 0x0014, 0x0018};
static s32 D_80181148 = 0;
static u32 D_8018114C = 0;

#ifdef VERSION_PSP
#define BUTTON_SYMBOL PAD_CIRCLE

extern s32 E_ID(DRACULA_UNK20);
extern s32 E_ID(DRACULA_UNK21);
extern s32 E_ID(DRACULA_UNK23);
extern s32 E_ID(DRACULA_FIREBALL);
extern s32 E_ID(DRACULA_UNK2C);
extern s32 E_ID(DRACULA_UNK2E);
#endif

bool func_801ADAC8(s16 yOffset) {
    s16 yDiff;

    yDiff = g_CurrentEntity->posY.i.hi + yOffset;
    if (yDiff >= 0xD0) {
        yDiff = 0xD0 - yDiff;
        g_CurrentEntity->posY.i.hi += yDiff;
        return true;
    } else {
        return false;
    }
}

// Function unique to ST0. Has many similarities to ClutLerp.
// Unclear what it actually does; no known calls.
void func_801ADB10(u16* arg0, u16 arg1, u16 arg2, s32 steps, u8* arg4) {
    u16 buf[COLORS_PER_PAL];
    RECT bufRect;
    s32 temp_a2;
    s32 factor;
    s32 temp_v0;
    s32 i;
    s32 j;
    s32 var_v0;
    u16* palA;

    u32 t;
    u32 r, g, b;
    u32 tempR;
    u32 tempG;
    u32 tempB;

    bufRect.x = *arg0;
    bufRect.w = COLORS_PER_PAL;
    bufRect.h = 1;

    arg4[0] >>= 3;
    arg4[1] >>= 3;
    arg4[2] >>= 3;
    palA = &g_Clut[0][arg1 * COLORS_PER_PAL];

    for (i = 0; i < steps; arg2++, i++) {
        factor = i * 4096 / steps;
        for (j = 0; j < 16; j++) {
            if (j == 0) {
                buf[0] = *palA;
            } else {
                t = palA[j] & ALPHA_MASK;
                tempR = GET_RED(palA[j]);
                r = (tempR * (4096 - factor)) + (arg4[0] * factor);
                tempG = GET_GREEN(palA[j]);
                tempR = r >> 12;
                g = (tempG * (4096 - factor)) + (arg4[1] * factor);
                tempB = GET_BLUE(palA[j]);
                tempG = g >> 12;
                b = (tempB * (4096 - factor)) + (arg4[2] * factor);
                tempB = b >> 12;
                buf[j] = ((t | (tempR)) | (tempG << 5)) | (tempB << 10);
                (&g_Clut[0][arg2 * COLORS_PER_PAL])[j] = buf[j];
            }
        }
        temp_a2 = arg2 - 0x200;
        var_v0 = temp_a2;
        if (var_v0 < 0) {
            var_v0 = arg2 - 0x1F1;
        }
        temp_v0 = var_v0 >> 4;
        bufRect.y = temp_v0 + 0xF0;
        bufRect.x = ((temp_a2 - (temp_v0 * 0x10)) * 0x10) + 0x100;
        LoadImage(&bufRect, (u_long*)buf);
        g_ClutIds[arg2] = GetClut(bufRect.x, bufRect.y);
    }
}

extern s32 D_80180910;
void EntityDraculaFinalForm(Entity* self) {
    byte stackpad[56];
    Entity* entity;
    Primitive* prim;
    u32 primIndex;
    s32 i;
    s16* temp_s1;
    s16 xShift;
    s16 yShift;
    s32 timerDiff;
    s32 selfParams;

    if (self->flags & FLAG_DEAD) {
        self->hitboxState = 0;
        if (self->step < 6) {
            D_8003C744 = 3;
            SetStep(6);
        }
    }

    if (!self->params) {
        if (g_Timer & 1) {
            self->palette = PAL_DRA(0x202);
        } else {
            self->palette = PAL_DRA(0x204);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaFinalForm);
        self->hitboxWidth = self->hitboxHeight = 16;
        self->hitboxOffX = -24;
        self->hitboxOffY = -16;
        self->hitboxState = 0;
        if (!self->params) {
            D_8003C744 = 2;
            self->animCurFrame = 0;
            entity = self + 1;
            for (i = 1; i < 4; i++, entity++) {
                CreateEntityFromCurrentEntity(E_ID(DRACULA_UNK20), entity);
                entity->zPriority = self->zPriority + 2;
                entity->params = i;
                entity->unk60 = entity - 1;
                entity->unk5C = self;

                // seems hitPoints might be used for something else
                entity->hitPoints = 0x7FFE;
            }
            self->unk5C = NULL;
            self->unk60 = self + 3;
        } else {
            self->animCurFrame = 0;
            SetStep(16);
        }
        break;
    case 1:
        if (D_801C2578 == 0) {
            self->animCurFrame = 1;
        }
        if (D_80180910 != 0) {
            self->animCurFrame = 1;
            self->hitboxState = 3;
            self->opacity = 0x80;
            self->drawFlags = FLAG_DRAW_DEFAULT;
            SetStep(2);
        }
        break;
    case 2:
        if (!self->step_s) {
            self->ext.dracFinalForm.timer = 80;
            self->step_s++;
        }

        if (!AnimateEntity(anim_80180AA4, self) &&
            (((GetSideToPlayer() & 1) ^ 1) != self->facingLeft)) {
            SetStep(3);
        }

        if (!--self->ext.dracFinalForm.timer) {
            SetStep(5);
            if ((self->posX.i.hi < 152) && (self->facingLeft == 1)) {
                if (Random() & 1) {
                    SetStep(7);
                } else {
                    SetStep(4);
                }
            } else if ((self->posX.i.hi > 104) && (self->facingLeft == 0)) {
                if (Random() & 1) {
                    SetStep(7);
                } else {
                    SetStep(4);
                }
            } else if (Random() & 1) {
                SetStep(8);
            } else {
                SetStep(4);
            }
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(anim_80180AB0, self) == 0) {
                SetSubStep(2);
            }

            if (!self->poseTimer && self->pose == 5) {
                if (self->facingLeft) {
                    self->velocityX = FIX(0.5);
                } else {
                    self->velocityX = FIX(-0.5);
                }
                self->velocityY = FIX(-4.0);
            }
            MoveEntity();
            if (self->velocityY != 0) {
                self->velocityY += FIX(10.0 / 128);
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(10.0 / 128);
            if (self->velocityY >= 0) {
                AnimateEntity(anim_80180AC8, self);
            }
            if (func_801ADAC8(0x4C) != 0) {
                g_api.PlaySfx(SFX_START_SLAM_B);
                g_api.func_80102CD8(1);
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(anim_80180AD4, self) == 0) {
                SetStep(2);
            }
        }
        break;
    case 3:
        if (AnimateEntity(anim_80180B60, self) == 0) {
            if ((self->posX.i.hi < 160) && (self->facingLeft == 1)) {
                if (Random() & 1) {
                    SetStep(4);
                } else {
                    SetStep(7);
                }
            } else if ((self->posX.i.hi > 96) && (self->facingLeft == 0)) {
                if (Random() & 1) {
                    SetStep(4);
                } else {
                    SetStep(7);
                }
            } else {
                SetStep(2);
            }
        }
        if (!self->poseTimer && self->pose == 2) {
            self->facingLeft ^= 1;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_80180B48, self)) {
                g_api.PlaySfx(0x866);
                self->step_s++;
            }
            break;
        case 1:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(DRACULA_UNK21), self, entity);
#ifndef VERSION_PSP
                // Appears to be a bug on PSX.
                // Possibly supposed to be assigning from self
                entity->posX.i.hi = entity->posX.i.hi;
                entity->posY.i.hi = entity->posY.i.hi;
#endif
                entity->facingLeft = self->facingLeft;
                entity->params = 1;
            }
            self->ext.dracFinalForm.timer = 32;
            self->step_s++;
            break;
        case 2:
            if (!--self->ext.dracFinalForm.timer) {
                self->ext.dracFinalForm.unk84 = 0;
                self->step_s++;
            }
            break;
        case 3:
            if (self->ext.dracFinalForm.timer) {
                self->ext.dracFinalForm.timer--;
                break;
            }
            self->ext.dracFinalForm.timer = 48;
            temp_s1 = D_801810F4;
            temp_s1 += self->ext.dracFinalForm.unk84;
            if (*temp_s1 == -1) {
                SetStep(2);
                return;
            }
            if (self->facingLeft) {
                xShift = 32;
            } else {
                xShift = -32;
            }
            yShift = -4;
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
                CreateEntityFromEntity(E_ID(DRACULA_UNK21), self, entity);
                entity->posX.i.hi += xShift;
                entity->posY.i.hi += yShift;
                entity->rotate = *temp_s1;
                if (self->facingLeft) {
                    entity->rotate = (0x800 - entity->rotate);
                }
            }
            self->ext.dracFinalForm.unk84++;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.dracFinalForm.timer = 4;
            self->ext.dracFinalForm.unk84 = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(anim_80180B80, self)) {
                SetSubStep(2);
            }
            if (!self->poseTimer && self->pose == 3) {
                g_api.PlaySfx(0x866);
                self->velocityY = FIX(-7.0);
            }
            MoveEntity();
            if (self->velocityY != 0) {
                self->velocityY += FIX(0.09375);
            }
            if (!--self->ext.dracFinalForm.timer) {
                temp_s1 = D_801810FC;
                temp_s1 += self->ext.dracFinalForm.unk84;
                if (*temp_s1 == -1) {
                    self->ext.dracFinalForm.timer = 0x7FFF;
                    return;
                }
                self->ext.dracFinalForm.timer = 6;
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
                    CreateEntityFromEntity(
                        E_ID(DRACULA_FIREBALL), self, entity);
                    entity->posX.i.hi += *temp_s1;
                    entity->zPriority = (self->zPriority + 1);
                }
                self->ext.dracFinalForm.unk84++;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (self->velocityY >= 0) {
                AnimateEntity(anim_80180AC8, self);
            }
            if (func_801ADAC8(0x4C) != 0) {
                g_api.PlaySfx(SFX_START_SLAM_B);
                g_api.func_80102CD8(1);
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(anim_80180AD4, self) == 0) {
                SetStep(2);
            }
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(anim_80180AEC, self) == 0) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (AnimateEntity(anim_80180AFC, self) == 0) {
                g_api.PlaySfx(0x856);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(DRACULA_UNK2E), self, entity);
                    if (self->facingLeft) {
                        entity->posX.i.hi += 40;
                    } else {
                        entity->posX.i.hi -= 40;
                    }
                    entity->posY.i.hi += 16;
                    entity->facingLeft = self->facingLeft;
                }
                SetSubStep(2);
            }
            break;
        case 2:
            if (AnimateEntity(anim_80180B20, self) == 0) {
                SetSubStep(3);
            }
            break;
        case 3:
            self->ext.dracFinalForm.timer = 256;
            self->step_s++;
            break;
        case 4:
            if (!--self->ext.dracFinalForm.timer) {
                SetStep(2);
            }
        }
        break;
    case 16:
        entity = self - self->params;
        self->facingLeft = entity->facingLeft;
        self->hitboxState = entity->hitboxState;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        i = entity->animCurFrame - 1;
        temp_s1 = &D_80180BE4[0][0][0];
        temp_s1 += i * 12;
        temp_s1 += (self->params - 1) * 4;
        self->hitboxOffX = *temp_s1++;
        self->hitboxOffY = *temp_s1++;

        self->hitboxWidth = *temp_s1++;
        self->hitboxHeight = *temp_s1++;
        if (self->params == 1) {
            switch (self->step_s) {
            case 0:
                self->ext.dracFinalForm.timer = 100;
                self->step_s++;
                return;
            case 1:
                if (!--self->ext.dracFinalForm.timer) {
                    self->animCurFrame = 0x5A;
                    self->unk5A = 0x5E;
                    self->palette = PAL_FLAG(0x15F);
                    self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
                    self->drawFlags = FLAG_DRAW_OPACITY;
                    self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
                    self->opacity = 0x10;
                    self->scaleX = self->scaleY = 0x400;
                    g_api.PlaySfx(0x880);
                    self->step_s++;
                }
                break;
            case 2:
                self->scaleY -= 0x18;
                self->scaleX = self->scaleY;
                if (self->scaleY < 0x100) {
                    self->animCurFrame = 0;
                    self->drawMode = DRAW_DEFAULT;
                    self->drawFlags = FLAG_DRAW_DEFAULT;
                    self->step_s++;
                }
                break;
            case 3:
                if (D_801C2578 == 0) {
                    self->animCurFrame = 1;
                    self->unk5A = 0x50;
                    self->palette = PAL_FLAG(0x15F);
                    self->drawFlags = FLAG_DRAW_OPACITY;
                    self->opacity = 0;
                    self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
                    self->step_s++;
                }
                break;
            case 4:
                self->opacity += 4;
                self->animCurFrame = entity->animCurFrame;
                if (self->opacity > 0x60) {
                    self->step_s++;
                }
                break;
            case 5:
                self->opacity -= 4;
                self->animCurFrame = entity->animCurFrame;
                if (!self->opacity) {
                    self->animCurFrame = 0;
                    self->drawMode = DRAW_DEFAULT;
                    self->drawFlags = FLAG_DRAW_DEFAULT;
                    self->step_s++;
                }
                break;
            }
        }
        break;
    case 6: // Time attack call indicates this state is Dracula's defeat
        switch (self->step_s) {
        case 0:
            g_api.PlaySfx(0x866);
            self->hitboxState = 0;
            entity = self + 1;
            for (i = 0; i < 3; i++, entity++) {
                DestroyEntity(entity);
            }
            g_api.PlaySfx(0x80);
            self->ext.dracFinalForm.timer = 4;
            self->ext.dracFinalForm.unk84 = 0;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_DRACULA_DEFEAT, TIMEATTACK_SET_RECORD);
            g_PauseAllowed = false;
#ifndef VERSION_PSP
            D_80181148 = 0x800;
#endif
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(anim_80180B58, self) == 0) {
                self->step_s++;
            }
            break;
        case 2:
#ifdef VERSION_PSP
            if (g_api.func_80131F68() != true) {
                g_api.PlaySfx(0x35C);
                self->step_s++;
            }
#else
            if (g_api.func_80131F68() == true) {

                if (--D_80181148 == 0) {
                    D_80181148 = 0x800;
                    g_api.PlaySfx(0x80);
                }
            } else {
                g_api.PlaySfx(0x35E);
                D_8018114C = g_Timer;
                self->step_s++;
            }
#endif

            break;
        case 3:
#ifdef VERSION_PSP
            g_api.PlaySfx(SFX_EXPLODE_A);
            self->ext.dracFinalForm.unk82 = 0x80;
            self->step_s++;
#else
            if (g_api.func_80131F68() == false) {
                i = g_Timer - D_8018114C;
                if (i >= 0x301) {
                    g_api.PlaySfx(SFX_EXPLODE_A);
                    self->ext.dracFinalForm.unk82 = 0x80;
                    self->step_s++;
                    break;
                }
                g_api.func_80102CD8(1);
                D_80181148--;
                if (D_80181148 == 0) {
                    D_80181148 = 0x800;
                    g_api.PlaySfx(0x80);
                    self->step_s--;
                    break;
                }
            } else {
                g_api.PlaySfx(SFX_EXPLODE_A);
                self->ext.dracFinalForm.unk82 = 0x80;
                self->step_s++;
            }
#endif
            break;
        case 4:
            if (!--self->ext.dracFinalForm.unk82) {
                self->step_s++;
            }
            break;
        case 5:
            entity = self + 1;
            CreateEntityFromCurrentEntity(E_ID(DRACULA_UNK2C), entity);
            self->step_s++;
            primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
            if (primIndex == -1) {
                g_GameEngineStep = Engine_10;
                g_MenuStep = 0;
                return;
            }
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            PGREY(prim, 0) = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority + 0x10;
            prim->drawMode = DRAW_TRANSP | 0x30;
            self->step_s++;
        case 6:
            prim = self->ext.prim;
            prim->r0 += 0x18;
            prim->g0 = prim->b0 = prim->r0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            if (prim->r0 > 0x80) {
                self->step_s++;
            }
            break;
        case 7:
            break;
        }

        if (!--self->ext.dracFinalForm.timer) {
            g_api.PlaySfx(SFX_EXPLODE_B);
            self->ext.dracFinalForm.timer = 8;
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            temp_s1 = &D_80181108[self->ext.dracFinalForm.unk84 * 2];
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 3;
                entity->zPriority = (self->zPriority + 1);
                entity->posX.i.hi += temp_s1[0];
                entity->posY.i.hi += temp_s1[1];
            }
            self->ext.dracFinalForm.unk84++;
            self->ext.dracFinalForm.unk84 &= 0xF;
        }

        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
}

static s16 D_80181150[][2] = {
    {0x00, 0x00}, {0x03, 0x04}, {0x07, 0x06}, {0x01, 0x0B}, {0x03, 0x0C},
    {0x08, 0x09}, {0x05, 0x0D}, {0x19, 0x06}, {0x19, 0x06}, {0x19, 0x06},
    {0x19, 0x06}, {0x11, 0x08}, {0x1E, 0x03}, {0x1F, 0x13}, {0x28, 0x0B},
    {0x3B, 0x0B}, {0x2B, 0x1C}, {0x39, 0x11}, {0x3D, 0x11}, {0x1D, 0x0B},
    {0x42, 0x0F}, {0x3F, 0x06}, {0x46, 0x0D}, {0x45, 0x08}, {0x39, 0x11},
    {0x3D, 0x11}, {0x2B, 0x1C}, {0x28, 0x1C}, {0x27, 0x1E}, {0x1B, 0x19},
    {0x1F, 0x0E}, {0x3E, 0x1D}, {0x25, 0x22}, {0x1B, 0x1E}, {0x21, 0x0B},
    {0x20, 0x0D}, {0x1F, 0x0F}, {0x16, 0x1D}, {0x16, 0x21}, {0x1A, 0x0A},
    {0x1B, 0x0D}, {0x1C, 0x0F}, {0x15, 0x26}, {0x1C, 0x2A}, {0x1C, 0x2D},
    {0x1D, 0x2D}, {0x26, 0x26}, {0x18, 0x53}, {0x20, 0x3A}, {0x26, 0x26},
    {0x26, 0x32}, {0x27, 0x3C}, {0x22, 0x3F}, {0x24, 0x4A}, {0x2A, 0x4A},
    {0x25, 0x4E}, {0x2B, 0x4F}, {0x25, 0x53}, {0x2E, 0x53}, {0x15, 0x3B},
    {0x1B, 0x3D}, {0x16, 0x41}, {0x1C, 0x45}, {0x15, 0x4C}, {0x1A, 0x4C},
    {0x13, 0x4F}, {0x10, 0x53}, {0x16, 0x53}, {0x1C, 0x53}, {0x26, 0x32},
    {0x28, 0x53}, {0x42, 0x53}, {0x3D, 0x28}, {0x3D, 0x32}, {0x3D, 0x3D},
    {0x3E, 0x43}, {0x3F, 0x4E}, {0x05, 0x1F}, {0x05, 0x2C}, {0x05, 0x3B},
    {0x06, 0x4D}, {0x05, 0x53}, {0x11, 0x1B}};
static s16 D_8018129C[][2] = {
    {0x00, 0x00}, {0x00, 0x1C}, {0x00, 0x13}, {0x0F, 0x1B}, {0x0F, 0x16},
    {0x09, 0x0C}, {0x0F, 0x13}, {0x14, 0x05}, {0x12, 0x16}, {0x1B, 0x06},
    {0x1A, 0x1D}, {0x1C, 0x02}, {0x23, 0x04}, {0x2F, 0x0B}, {0x3E, 0x02},
    {0x5E, 0x07}, {0x3D, 0x1A}, {0x50, 0x12}, {0x5D, 0x1A}, {0x67, 0x17},
    {0x56, 0x25}, {0x6F, 0x26}, {0x59, 0x29}, {0x62, 0x31}, {0x51, 0x18},
    {0x56, 0x1A}, {0x48, 0x1D}, {0x52, 0x1F}, {0x51, 0x29}, {0x38, 0x2B},
    {0x34, 0x22}, {0x53, 0x35}, {0x4C, 0x34}, {0x38, 0x31}, {0x2E, 0x1D},
    {0x25, 0x28}, {0x25, 0x2E}, {0x2E, 0x30}, {0x2F, 0x35}, {0x0F, 0x1C},
    {0x0E, 0x22}, {0x20, 0x33}, {0x28, 0x38}, {0x3C, 0x47}, {0x39, 0x4A},
    {0x42, 0x4C}, {0x50, 0x39}, {0x42, 0x54}, {0x49, 0x56}, {0x5A, 0x38},
    {0x61, 0x45}, {0x5F, 0x53}, {0x4E, 0x62}, {0x5C, 0x65}, {0x68, 0x67},
    {0x5F, 0x6A}, {0x72, 0x6A}, {0x5D, 0x74}, {0x78, 0x74}, {0x11, 0x4F},
    {0x26, 0x58}, {0x18, 0x5B}, {0x2A, 0x5D}, {0x20, 0x67}, {0x28, 0x69},
    {0x13, 0x6B}, {0x0E, 0x74}, {0x24, 0x74}, {0x31, 0x74}, {0x5C, 0x4C},
    {0x49, 0x56}, {0x78, 0x74}, {0x4C, 0x34}, {0x5C, 0x4C}, {0x5F, 0x53},
    {0x68, 0x67}, {0x72, 0x6A}, {0x2E, 0x30}, {0x28, 0x38}, {0x18, 0x5B},
    {0x20, 0x67}, {0x0E, 0x74}, {0x25, 0x28}};
static u8 D_801813E8[] = {
    0x02, 0x04, 0x01, 0x03, 0x05, 0x06, 0x02, 0x04, 0x11, 0x0F, 0x12, 0x13,
    0x12, 0x13, 0x14, 0x15, 0x14, 0x15, 0x16, 0x17, 0x1D, 0x1C, 0x21, 0x20,
    0x25, 0x1D, 0x26, 0x21, 0x26, 0x21, 0x2B, 0x20, 0x26, 0x2B, 0x2A, 0x2C,
    0x2A, 0x2C, 0x3B, 0x3C, 0x3B, 0x3C, 0x3D, 0x3E, 0x3D, 0x3E, 0x3F, 0x40,
    0x3F, 0x40, 0x43, 0x44, 0x41, 0x3F, 0x42, 0x43, 0x2B, 0x20, 0x2D, 0x2E,
    0x2D, 0x2E, 0x30, 0x45, 0x30, 0x45, 0x34, 0x33, 0x34, 0x33, 0x35, 0x36,
    0x35, 0x36, 0x37, 0x38, 0x37, 0x38, 0x39, 0x3A, 0x2C, 0x2D, 0x2F, 0x46,
    0x11, 0x12, 0x1B, 0x1F, 0x1B, 0x1F, 0x20, 0x48, 0x20, 0x48, 0x45, 0x49,
    0x45, 0x49, 0x33, 0x4A, 0x33, 0x4A, 0x36, 0x4B, 0x36, 0x4B, 0x38, 0x4C,
    0x38, 0x4C, 0x3A, 0x47, 0x06, 0x52, 0x4D, 0x25, 0x4D, 0x25, 0x4E, 0x2A,
    0x4E, 0x2A, 0x4F, 0x3D, 0x4F, 0x3D, 0x50, 0x3F, 0x50, 0x3F, 0x51, 0x42,
    0x0E, 0x0F, 0x1E, 0x11, 0x1E, 0x11, 0x24, 0x10, 0x24, 0x10, 0x0D, 0x1B,
    0x0D, 0x1B, 0x1D, 0x1C, 0x0C, 0x0E, 0x22, 0x1E, 0x23, 0x22, 0x24, 0x1E,
    0x0C, 0x22, 0x0A, 0x23, 0x0A, 0x23, 0x27, 0x24, 0x28, 0x29, 0x27, 0x24,
    0x0B, 0x0A, 0x05, 0x27, 0x27, 0x28, 0x05, 0x29, 0x24, 0x0D, 0x29, 0x1D,
    0x52, 0x29, 0x25, 0x1D, 0x06, 0x05, 0x52, 0x29, 0x00, 0x00, 0x00, 0x00};
static u8 D_801814A8[] = {
    0x02, 0x04, 0x01, 0x03, 0x05, 0x06, 0x02, 0x04, 0x05, 0x07, 0x06, 0x08,
    0x07, 0x09, 0x08, 0x0A, 0x07, 0x0B, 0x09, 0x0C, 0x09, 0x0C, 0x0A, 0x0D,
    0x0C, 0x0E, 0x0D, 0x0F, 0x0D, 0x0F, 0x10, 0x11, 0x11, 0x0F, 0x12, 0x13,
    0x11, 0x12, 0x18, 0x19, 0x10, 0x11, 0x1A, 0x18, 0x18, 0x19, 0x1A, 0x1B,
    0x19, 0x12, 0x1B, 0x14, 0x12, 0x13, 0x14, 0x15, 0x14, 0x15, 0x16, 0x17,
    0x1B, 0x14, 0x1C, 0x16, 0x1C, 0x16, 0x20, 0x1F, 0x0D, 0x10, 0x22, 0x1E,
    0x1E, 0x10, 0x1D, 0x1A, 0x1A, 0x1B, 0x1D, 0x1C, 0x1D, 0x1C, 0x21, 0x20,
    0x22, 0x1E, 0x23, 0x1D, 0x23, 0x1D, 0x26, 0x21, 0x25, 0x1D, 0x26, 0x21,
    0x26, 0x21, 0x2B, 0x20, 0x26, 0x2B, 0x2A, 0x2C, 0x2A, 0x2C, 0x3B, 0x3C,
    0x3B, 0x3C, 0x3D, 0x3E, 0x3D, 0x3E, 0x3F, 0x40, 0x3F, 0x40, 0x43, 0x44,
    0x41, 0x3F, 0x42, 0x43, 0x2B, 0x20, 0x2D, 0x2E, 0x2D, 0x2E, 0x30, 0x45,
    0x31, 0x32, 0x2E, 0x45, 0x30, 0x45, 0x34, 0x33, 0x34, 0x33, 0x35, 0x36,
    0x35, 0x36, 0x37, 0x38, 0x37, 0x38, 0x39, 0x3A, 0x2B, 0x2D, 0x2C, 0x30,
    0x28, 0x27, 0x29, 0x08, 0x29, 0x08, 0x24, 0x0A, 0x24, 0x0A, 0x22, 0x0D,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void EntityDraculaMegaFireball(Entity* self) {
    s16 angle;

    if (!self->step) {
        InitializeEntity(g_EInitDraculaMegaFireball);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        if (!self->params) {
            self->drawFlags |=
                FLAG_DRAW_ROTATE | FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleX = self->scaleY = 0x80;
            angle = self->rotate;
            self->rotate = 0x1C0;
            self->rotate -= angle;
            if (self->facingLeft) {
                self->velocityX = rcos(angle) * 0x60;
            } else {
                self->velocityX = rcos(angle) * -0x60;
            }
            self->velocityY = rsin(angle) * 0x60;
        }
    }

    if (self->params) {
        if (!AnimateEntity(anim_80180BA0, self)) {
            DestroyEntity(self);
        }
        if (g_Timer & 1) {
            self->animCurFrame = 0;
        }
        return;
    }

    if (self->scaleX < 0x100) {
        self->scaleX = self->scaleY += 0x10;
    }

    AnimateEntity(anim_80180BB8, self);
    MoveEntity();
}

extern EInit g_EInitDraculaRainAttack;
void EntityDraculaRainAttack(Entity* self) {
    Entity* newEntity;
    s32 rand;
    s16 angle;
    s32 i;

    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 2;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaRainAttack);
        if (self->params) {
            self->hitboxState = 0;
            self->animCurFrame = 0x59;
            rand = (Random() & 0x1F) + 0x10;
            angle = (Random() * 6) + 0x900;
            self->velocityX = rand * rcos(angle);
            self->velocityY = rand * rsin(angle);
            self->step = 3;
            break;
        }
        self->velocityY = FIX(4);

    case 1:
        MoveEntity();
        AnimateEntity(anim_80180BCC, self);
        if (func_801ADAC8(0x14) != 0) {
            SetStep(2);
        }
        break;

    case 2:
        if (AnimateEntity(anim_80180BDC, self) == 0) {

            for (i = 0; i < 4; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(DRACULA_FIREBALL), self, newEntity);
                    newEntity->posY.i.hi += 12;
                    newEntity->params = 1;
                }
            }
            DestroyEntity(self);
        }
        break;

    case 3:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->posY.i.hi > 0xF0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_801AF380(void) {
    Primitive* prim;
    s16* points;
    s32 i;
    u8* indexes;
    u8 uBase;
    u8 vBase;

    prim = g_CurrentEntity->ext.et_801AF774.prim1;
    points = *D_80181150;
    indexes = D_801813E8;
    uBase = 0;
    vBase = 0;
    for (i = 0; i < 47; i++) {
        prim->tpage = 0x17;
        prim->clut = 0x200;
        // This should REALLY be done using Point16, but no,
        // that would make too much sense for SOTN
        prim->u0 = uBase + points[*indexes * 2];
        prim->v0 = vBase + (&points[*indexes++ * 2])[1];

        prim->u1 = uBase + points[*indexes * 2];
        prim->v1 = vBase + (&points[*indexes++ * 2])[1];

        prim->u2 = uBase + points[*indexes * 2];
        prim->v2 = vBase + (&points[*indexes++ * 2])[1];

        prim->u3 = uBase + points[*indexes * 2];
        prim->v3 = vBase + (&points[*indexes++ * 2])[1];

        PGREY(prim, 0) = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xA0;
        prim->drawMode = DRAW_TRANSP | 0x34;
        prim = prim->next;
    }
    g_CurrentEntity->ext.et_801AF774.prim2 = prim;
    points = *D_8018129C;
    indexes = D_801814A8;
    uBase = 0;
    vBase = 0x80;
    for (i = 0; i < 42; i++) {
        prim->tpage = 0x17;
        prim->clut = 0x204;
        prim->u0 = uBase + points[*indexes * 2];
        prim->v0 = vBase + (&points[*indexes++ * 2])[1];

        prim->u1 = uBase + points[*indexes * 2];
        prim->v1 = vBase + (&points[*indexes++ * 2])[1];

        prim->u2 = uBase + points[*indexes * 2];
        prim->v2 = vBase + (&points[*indexes++ * 2])[1];

        prim->u3 = uBase + points[*indexes * 2];
        prim->v3 = vBase + (&points[*indexes++ * 2])[1];

        PGREY(prim, 0) = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xA0;
        prim->drawMode = DRAW_TRANSP | 0x34;
        prim = prim->next;
    }

    points = *D_80181150;
    for (i = 0; i < LEN(D_80181150); i++) {
        D_801BEB64[i][0] = (points[0] - 0x1E) << 0x10;
        points++;
        D_801BEB64[i][1] = (points[0] - 0x53) << 0x10;
        points++;
    }
}

void func_801AF6D0(void) {
    s16* ptrOne;
    s16* ptrTwo;
    s32 i;
    s32 constOne, constTwo, constThree, constFour;
    s32 valOne, valTwo;

    ptrOne = *D_80181150;
    ptrTwo = *D_8018129C;

    constOne = -0x1E;
    constTwo = -0x53;
    constThree = -0x38;
    constFour = -0x75;

    for (i = 0; i < LEN(D_80181150); i++) {
        valOne = (constThree + *ptrTwo) - (constOne + *ptrOne);
#ifdef VERSION_PSP
        valOne = (valOne << 0x10) / 0x80;
#else
        valOne = (valOne << 9);
#endif
        D_801BEB64[i][0] = valOne + D_801BEB64[i][0];
        ptrOne++;
        ptrTwo++;

        valTwo = (constFour + *ptrTwo) - (constTwo + *ptrOne);
#ifdef VERSION_PSP
        valTwo = (valTwo << 0x10) / 0x80;
#else
        valTwo = (valTwo << 9);
#endif
        D_801BEB64[i][1] = valTwo + D_801BEB64[i][1];
        ptrOne++;
        ptrTwo++;
    }
}

void func_801AF774(Entity* self) {
    Entity* entity;
    RECT rect;
    DRAWENV drawEnv;
    Primitive* prim;
    DR_ENV* drEnv;
    u8* indexes;
    s32* points;
    s32 primIndex;
    s32 i;
    u8 rgb;
    s16 xBase, yBase;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDracula);
        self->hitboxState = 0;
        self->animCurFrame = 0;
        self->drawMode |= (DRAW_TPAGE | 0x20);
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        D_801C2578 = 1;
        self->ext.et_801AF774.unk90 = 1;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x5C);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801AF774.prim3 = prim;
            prim->tpage = 0x110;
            if (!self->facingLeft) {
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = prim->u0 + 0x80;
            } else {
                prim->u1 = prim->u3 = 0;
                prim->u0 = prim->u2 = prim->u1 + 0x7F;
            }
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = prim->v0 + 0x80;

            // Bug? Code is the same in both paths
            // Usually the +/- are flipped for else
            if (!self->facingLeft) {
                prim->x0 = prim->x2 = self->posX.i.hi - 0x40;
                prim->x1 = prim->x3 = self->posX.i.hi + 0x40;
            } else {
                prim->x0 = prim->x2 = self->posX.i.hi - 0x40;
                prim->x1 = prim->x3 = self->posX.i.hi + 0x40;
            }

            prim->y0 = prim->y1 = self->posY.i.hi - 0x25;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x5B;
            PGREY(prim, 0) = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_UNK02 | DRAW_HIDE;
            prim->priority = 0xA8;
            prim = prim->next;

            self->ext.et_801AF774.prim4 = prim;
            drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
            if (drEnv == NULL) {
                g_api.FreePrimitives(primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                self->step = 0;
                return;
            }
            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
            if (prim == NULL) {
                g_api.FreePrimitives(primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                self->step = 0;
                return;
            }
            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            self->ext.et_801AF774.prim1 = prim;
            while (prim != NULL) {
                prim->priority = 0xA0;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            self->step = 0;
            FntPrint("can't get effect works!\n");
            return;
        }
    case 1:
        prim = self->ext.et_801AF774.prim4;
        drawEnv = g_CurrentBuffer->draw;
        drawEnv.isbg = 1;
        drawEnv.r0 = 0;
        drawEnv.g0 = 0;
        drawEnv.b0 = 0;
        rect.x = 0;
        rect.y = 0x100;
        rect.w = 0x7f;
        rect.h = 0xff;
#ifdef VERSION_PSP
        drawEnv.dtd = 0;
#endif
        drawEnv.clip = rect;
        drawEnv.ofs[0] = 0;
        drawEnv.ofs[1] = 0x100;
        drEnv = (DR_ENV*)LOW(prim->r1);
        SetDrawEnv(drEnv, &drawEnv);
        prim->priority = 0x9F;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->priority = 0xA1;
        prim->drawMode = DRAW_UNK_800;
        self->step++;
        break;

    case 2:
        func_801AF380();
        prim = self->ext.et_801AF774.prim4;
        drEnv = (DR_ENV*)LOW(prim->r1);
        drawEnv = g_CurrentBuffer->draw;
        drawEnv.isbg = 1;
        drawEnv.isbg = 0;
        // Bug? This seems odd.
        drawEnv.dtd = 1;
        drawEnv.dtd = 0;
        rect.x = 0;
        rect.y = 0x100;
        rect.w = 0x80;
        rect.h = 0x80;
#ifdef VERSION_PSP
        drawEnv.dtd = 0;
#endif
        drawEnv.clip = rect;
        drawEnv.ofs[0] = 0;
        drawEnv.ofs[1] = 0x100;
        SetDrawEnv(drEnv, &drawEnv);
        prim->priority = 0x9F;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->priority = 0xA1;
        prim->drawMode = DRAW_UNK_800;
        self->ext.et_801AF774.unk8E = 0x80;
        self->ext.et_801AF774.unk8C = 0x8000;
        self->step_s = 0;
        self->step++;
        return;
    case 3:
        prim = self->ext.et_801AF774.prim3;
        prim->drawMode =
            DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        if (self->ext.et_801AF774.unk8E > 0) {
            func_801AF6D0();
        }
        rgb = self->ext.et_801AF774.unk8C >> 8;
        if (rgb > 0x80) {
            rgb = 0x80;
        }
        rgb >>= 3;
        prim = self->ext.et_801AF774.prim1;
        xBase = 0x40;
        yBase = 0x70;
        points = *D_801BEB64;
        indexes = D_801813E8;

        for (i = 0; i < 47; i++) {
            // The way this is written is horrendous
            // but required for match on PSP
            prim->x0 = (((*indexes * 2)[points]) >> 16) + xBase;
            prim->y0 = (((*indexes++ * 2)[points + 1]) >> 16) + yBase;

            prim->x1 = (((*indexes * 2)[points]) >> 16) + xBase;
            prim->y1 = (((*indexes++ * 2)[points + 1]) >> 16) + yBase;

            prim->x2 = (((*indexes * 2)[points]) >> 16) + xBase;
            prim->y2 = (((*indexes++ * 2)[points + 1]) >> 16) + yBase;

            prim->x3 = (((*indexes * 2)[points]) >> 16) + xBase;
            prim->y3 = (((*indexes++ * 2)[points + 1]) >> 16) + yBase;

            PGREY(prim, 0) = rgb;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        rgb = self->ext.et_801AF774.unk8C >> 8;
        if (rgb > 0x80) {
            rgb = 0x80;
        }
        rgb = (0x80 - rgb);
        rgb >>= 3;
        prim = self->ext.et_801AF774.prim2;
        points = *D_801BEB64;
        indexes = D_801814A8;
        xBase = 0x40;
        yBase = 0x70;
        for (i = 0; i < 42; i++) {
            prim->x0 = (((*indexes * 2)[points]) >> 16) + xBase;
            prim->y0 = (((*indexes++ * 2)[points + 1]) >> 16) + yBase;

            prim->x1 = (((*indexes * 2)[points]) >> 16) + xBase;
            prim->y1 = (((*indexes++ * 2)[points + 1]) >> 16) + yBase;

            prim->x2 = (((*indexes * 2)[points]) >> 16) + xBase;
            prim->y2 = (((*indexes++ * 2)[points + 1]) >> 16) + yBase;

            prim->x3 = (((*indexes * 2)[points]) >> 16) + xBase;
            prim->y3 = (((*indexes++ * 2)[points + 1]) >> 16) + yBase;

            PGREY(prim, 0) = rgb;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        self->ext.et_801AF774.unk8E--;
#ifdef VERSION_PSP
        self->ext.et_801AF774.unk8C = self->ext.et_801AF774.unk8E << 8;
#else
        self->ext.et_801AF774.unk8C = self->ext.et_801AF774.unk8E << 0x10 >> 8;
#endif
        if (self->ext.et_801AF774.unk8E < 0) {
            self->step = 4;
        }
        if (self->ext.et_801AF774.unk90 && self->ext.et_801AF774.unk8E < 0x10) {
            self->ext.et_801AF774.unk90 = 0;
            entity = self + 1;
            CreateEntityFromCurrentEntity(E_ID(DRACULA_UNK23), entity);
        }
        break;
    case 4:
        D_801C2578 = 0;
        prim = self->ext.et_801AF774.prim3;
        prim->drawMode =
            DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;

        for (prim = prim->next; prim != NULL; prim = prim->next) {
            prim->drawMode = DRAW_HIDE;
        }

        self->ext.et_801AF774.unk8E = 0x10;
        self->step++;
        break;
    case 5:
        if (!--self->ext.et_801AF774.unk8E) {
            self->step++;
        }
        break;

    case 6:
        self->step++;
        break;

    case 7:
        prim = self->ext.et_801AF774.prim3;
        if (!PrimDecreaseBrightness(prim, 7)) {
            D_80180910 = 1;
            DestroyEntity(self);
        }
        break;
    }
}
