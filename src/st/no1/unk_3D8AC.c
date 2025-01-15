// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

extern s32 D_us_80181570;
extern u16 g_EInitInteractable[];
extern s32 D_psp_0929A6C0;
extern s32 D_psp_0929A6B0;
extern s32 D_psp_0929A6A8;

void func_us_801BD8AC(Entity* self) {
    Entity* tempEntity;
    s32 i;

    switch (self->step) {
    case 0:

        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->animCurFrame = 0;
        tempEntity = self + 1;
        for (i = 1; i < 6; i++) {
#ifdef VERSION_PSP
            CreateEntityFromEntity(D_psp_0929A6C0, self, tempEntity);
#else
            CreateEntityFromEntity(E_ID_36, self, tempEntity);
#endif
            tempEntity->params = i + 0x100;
            tempEntity++;
#ifdef VERSION_PSP
            CreateEntityFromEntity(D_psp_0929A6C0, self, tempEntity);
#else
            CreateEntityFromEntity(E_ID_36, self, tempEntity);
#endif
            tempEntity->params = i;
            tempEntity++;
        }
#ifdef VERSION_PSP
        CreateEntityFromEntity(D_psp_0929A6B0, self, tempEntity);
        tempEntity++;
        CreateEntityFromEntity(D_psp_0929A6A8, self, tempEntity);
#else
        CreateEntityFromEntity(E_ID_38, self, tempEntity);
        tempEntity++;
        CreateEntityFromEntity(E_ID_39, self, tempEntity);
#endif
        break;

    case 1:
        if (D_us_80181570 & 1) {
            self->step += 2;
        }
        break;

    case 2:
        if (!--self->ext.et_801BDA0C.unk9C) {
            self->step++;
        }
        break;

    case 3:
        tempEntity = self + 1;
        tempEntity->ext.et_801BDA0C.unk84 = 1;
        tempEntity++;
        tempEntity->ext.et_801BDA0C.unk84 = 1;
        self->step++;
        break;
    }
}

extern u16 D_us_801809C8[];
extern s32 D_us_80181570;
extern s16 D_us_80181574[];
extern s16 D_us_80181580[];
extern s16 D_us_8018158C[];
extern u8 D_us_80181598[];
extern u8 D_us_801815A0[];
extern u8 D_us_801815A8[];
extern u8 D_us_801815B0[];

void func_us_801BDA0C(Entity* self) {
    s32 flag;
    s32 primIndex;
    s16 xOffset, yOffset;
    s16 magnitude;
    Entity* tempEntity;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809C8);
        self->drawFlags |=
            FLAG_DRAW_UNK8 | FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        if ((self->params & 0xF) > 1) {
            self->unk6C = 0x20;
        } else {
            self->unk6C = 0x80;
        }
        self->rotX = D_us_8018158C[self->params & 0xF];
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
        self->palette = 0x804F;
        if (self->ext.et_801BDA0C.unk84) {
            self->step++;
        }
        break;

    case 2:
        flag = self->params & 0xFF;
        if (flag != 1) {
            self->step++;
        } else {
            if (self->params & 0x100) {
                AnimateEntity(D_us_801815A0, self);
            } else {
                AnimateEntity(D_us_80181598, self);
            }
            if ((g_Timer & 0xF) == 0) {
                g_api.PlaySfx(SFX_STONE_MOVE_B);
            }
            if (D_us_80181570 & 8) {
                self->step++;
            }
        }
        break;

    case 3:
        if (g_Timer % 2 == 0) {
            self->palette++;
            if (self->palette > 0x8058) {
                g_api.PlaySfx(SFX_ELECTRICITY);
                self->palette = 0x804F;
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
            AnimateEntity(D_us_801815A0, self);
        } else {
            AnimateEntity(D_us_80181598, self);
        }
        if ((g_Timer & 0xF) == 0) {
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        if (self->params & 0x100) {
            self->ext.et_801BDA0C.unk88 -= D_us_80181574[self->params & 0xF];
        } else {
            self->ext.et_801BDA0C.unk88 += D_us_80181574[self->params & 0xF];
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
        if (tempEntity->unk6C < 0x80) {
            tempEntity->unk6C++;
        }
        break;

    case 5:
        tempEntity = self + 2;
        if (tempEntity->unk6C < 0x80) {
            tempEntity->unk6C += 2;
        }
        magnitude = self->ext.et_801BDA0C.unk80 / 0x10000;
        xOffset = (rcos(self->rotZ - 0x400) * magnitude) >> 0xC;
        yOffset = (rsin(self->rotZ - 0x400) * magnitude) >> 0xC;
        prim = self->ext.et_801BDA0C.unk7C;
        self->posX.i.hi = prim->x0 + xOffset;
        self->posY.i.hi = prim->y0 + yOffset;
        if (self->params & 0x100) {
            AnimateEntity(D_us_801815B0, self);
        } else {
            AnimateEntity(D_us_801815A8, self);
        }
        self->rotZ += D_us_80181580[self->params & 0xF];
        if (self->params & 0x100) {
            self->ext.et_801BDA0C.unk88 -= D_us_80181574[self->params & 0xF];
        } else {
            self->ext.et_801BDA0C.unk88 += D_us_80181574[self->params & 0xF];
        }
        self->ext.et_801BDA0C.unk80 += self->ext.et_801BDA0C.unk88;
        if (self->ext.et_801BDA0C.unk80 > FIX(64)) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/no1/nonmatchings/unk_3D8AC", func_us_801BDF9C);

INCLUDE_RODATA("st/no1/nonmatchings/unk_3D8AC", D_us_801B4808);

INCLUDE_ASM("st/no1/nonmatchings/unk_3D8AC", func_us_801BE2C8);
