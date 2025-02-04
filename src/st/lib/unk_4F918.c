// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

INCLUDE_ASM("st/lib/nonmatchings/unk_4F918", func_us_801CF918);

INCLUDE_ASM("st/lib/nonmatchings/unk_4F918", func_us_801CFA00);

INCLUDE_ASM("st/lib/nonmatchings/unk_4F918", func_us_801D00C4);

INCLUDE_ASM("st/lib/nonmatchings/unk_4F918", func_us_801D01C8);

INCLUDE_ASM("st/lib/nonmatchings/unk_4F918", func_us_801D02D0);

INCLUDE_ASM("st/lib/nonmatchings/unk_4F918", func_us_801D0304);

extern u16 D_us_801809E0[];
extern s32 D_us_80181ACC;
extern u8 D_us_80182E3C[];
extern u8 D_us_80182E4C[];
extern s16 D_us_80182E70[];
extern s16 D_us_80182E80[];
extern s32 D_us_80182E88[][2];

void func_us_801D064C(Entity* self) {
    Entity* tempEntity;
    Entity* tempEntity2;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 colRet;

    if (D_us_80181ACC & 2) {
        self->flags |= FLAG_DEAD;
    }
    if ((self->flags & FLAG_DEAD) && self->step < 10) {
        self->step = 10;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809E0);
        self->zPriority = 0x78;
        tempEntity2 = AllocEntity(&g_Entities[64], &g_Entities[192]);
        if (tempEntity2 != NULL) {
            CreateEntityFromEntity(E_ID_4E, self, tempEntity2);
            tempEntity2->ext.et_801D064C.unk9C = self;
        }
        self->hitboxState = 0;
        self->flags |= FLAG_UNK_2000;
        self->ext.et_801D064C.unk84 = 0;
        self->ext.et_801D064C.unk81 = 0;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->unk60 = NULL;
        break;

    case 1:
        if (UnkCollisionFunc3(D_us_80182E70) & 1) {
            self->step++;
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.et_801D064C.unk7C = prim;
                prim->tpage = 0x14;
                prim->clut = 0x277;
                prim->u0 = 0x80;
                prim->u1 = 0xA0;
                prim->u2 = 0x80;
                prim->u3 = 0xA0;
                prim->v0 = 0x80;
                prim->v1 = 0x80;
                prim->v2 = 0xA8;
                prim->v3 = 0xA8;
                PGREY(prim, 0) = 0x80;
                PGREY(prim, 1) = 0x80;
                PGREY(prim, 2) = 0x42;
                PGREY(prim, 3) = 0x42;
                prim->priority = self->zPriority + 2;
                prim->drawMode |= DRAW_UNK02;
                prim->drawMode |= DRAW_COLORS;
                prim->x0 = self->posX.i.hi + 1;
                prim->x1 = prim->x2 = prim->x3 = prim->x0;
                prim->y0 = self->posY.i.hi + 0x14;
                prim->y2 = self->posY.i.hi + 0x16;
                prim->y1 = prim->y0;
                prim->y3 = prim->y2;
            } else {
                DestroyEntity(self);
                return;
            }
        }
        break;
    case 2:
        if (g_Timer % 2 == 0) {
            prim = self->ext.et_801D064C.unk7C;
            if (self->ext.et_801D064C.unk80 == 0x10) {
                if (self->facingLeft) {
                    prim->x0 -= 8;
                } else {
                    prim->x0 += 8;
                }
            }
            if (self->ext.et_801D064C.unk80 < 0x10) {
                if (self->facingLeft) {
                    prim->x0++;
                    prim->x1--;
                } else {
                    prim->x0--;
                    prim->x1++;
                }
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
            } else {
                prim->y1--;
                if (self->ext.et_801D064C.unk80 >= 0x20) {
                    prim->y0--;
                }
                if (self->ext.et_801D064C.unk80 >= 0x36) {
                    prim->y1++;
                    prim->y0--;
                }
            }
            if (self->ext.et_801D064C.unk80 >= 0x3D) {
                if (self->facingLeft) {
                    prim->x0++;
                } else {
                    prim->x0--;
                }
            }
            self->ext.et_801D064C.unk80++;
            PGREY(prim, 2) = (self->ext.et_801D064C.unk80 * 2) + 4;
            PGREY(prim, 3) = (self->ext.et_801D064C.unk80 * 2) + 4;
            if (self->ext.et_801D064C.unk80 >= 0x3E) {
                self->ext.et_801D064C.unk80 = 0;
                self->step++;
            }
        }
        break;

    case 3:
        if (g_Timer % 6 == 0) {
            self->step_s = 6;
            prim = self->ext.et_801D064C.unk7C;
            if (self->facingLeft) {
                prim->x0++;
            } else {
                prim->x0--;
            }
            if (self->ext.et_801D064C.unk80++ > 3) {
                prim = self->ext.et_801D064C.unk7C;
                primIndex = prim - g_PrimBuf;
                g_api.FreePrimitives(primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                if (self->facingLeft) {
                    self->velocityX = FIX(0.25);
                } else {
                    self->velocityX = FIX(-0.25);
                }
                self->animCurFrame = 1;
                self->ext.et_801D064C.unk80 = 0;
                self->step = 6;
            }
        }
        break;

    case 4:
        if (g_Timer % 2 == 0) {
            prim = self->ext.et_801D064C.unk7C;
            if (self->ext.et_801D064C.unk80 < 0x10) {
                if (self->facingLeft) {
                    prim->x0++;
                    prim->x1--;
                } else {
                    prim->x0--;
                    prim->x1++;
                }
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
            } else {
                prim->y1--;
                if (self->ext.et_801D064C.unk80 >= 0x20) {
                    prim->y0--;
                }
                if (self->ext.et_801D064C.unk80 >= 0x36) {
                    prim->y1++;
                    prim->y0--;
                }
            }
            self->ext.et_801D064C.unk80++;
            PGREY(prim, 2) = (self->ext.et_801D064C.unk80 * 2) + 4;
            PGREY(prim, 3) = (self->ext.et_801D064C.unk80 * 2) + 4;
            if (self->ext.et_801D064C.unk80 >= 0x3E) {
                prim = self->ext.et_801D064C.unk7C;
                primIndex = prim - g_PrimBuf;
                g_api.FreePrimitives(primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                if (self->facingLeft) {
                    self->velocityX = FIX(0.25);
                } else {
                    self->velocityX = FIX(-0.25);
                }
                self->animCurFrame = 1;
                self->step = 6;
            }
        }
        break;

    case 5:
        if (g_Timer % 2 == 0) {
            prim = self->ext.et_801D064C.unk7C;
            if (self->ext.et_801D064C.unk80 < 0x3E) {
                if (self->facingLeft) {
                    prim->x0++;
                    prim->x1--;
                } else {
                    prim->x0--;
                    prim->x1++;
                }
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
            } else {
                prim->y1--;
                prim->y0--;
                if (self->facingLeft) {
                    prim->x0--;
                    prim->x1++;
                } else {
                    prim->x0++;
                    prim->x1--;
                }
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
            }
            self->ext.et_801D064C.unk80++;
            if (self->ext.et_801D064C.unk80 >= 0x6B) {
                prim = self->ext.et_801D064C.unk7C;
                primIndex = prim - g_PrimBuf;
                g_api.FreePrimitives(primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                if (self->facingLeft) {
                    self->velocityX = FIX(0.25);
                } else {
                    self->velocityX = FIX(-0.25);
                }
                self->animCurFrame = 1;
                self->step = 6;
            }
        }
        break;

    case 6:
        AnimateEntity(D_us_80182E3C, self);
        colRet = UnkCollisionFunc2(D_us_80182E80);
        self->hitboxState = 3;
        if (GetDistanceToPlayerX() < 0x40) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->step = 7;
        }
        if (colRet & 0xE0) {
            self->step = 8;
        }
        break;

    case 7:
        if (AnimateEntity(D_us_80182E4C, self) == 0) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->ext.et_801D064C.unk81 = 1;
            self->step = 6;
        }
        if (!self->animFrameDuration && self->animFrameIdx == 3) {
            PlaySfxPositional(0x78C);
        }
        break;

    case 8:
        prim = self->ext.et_801D064C.unk7C;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801D064C.unk7C = prim;
            prim->tpage = 0x14;
            prim->clut = 0x277;
            prim->u0 = 0x80;
            prim->u1 = 0xA0;
            prim->u2 = 0x80;
            prim->u3 = 0xA0;
            prim->v0 = 0x80;
            prim->v1 = 0x80;
            prim->v2 = 0xA8;
            prim->v3 = 0xA8;
            PGREY(prim, 0) = 0x80;
            PGREY(prim, 1) = 0x80;
            PGREY(prim, 2) = 0x80;
            PGREY(prim, 3) = 0x80;
            prim->priority = self->zPriority + 2;
            prim->drawMode |= DRAW_UNK02;
            prim->drawMode |= DRAW_COLORS;
            if (self->facingLeft) {
                prim->x0 = self->posX.i.hi + 0x11;
                prim->x1 = self->posX.i.hi - 0xF;
            } else {
                prim->x0 = self->posX.i.hi - 0xF;
                prim->x1 = self->posX.i.hi + 0x11;
            }
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->y0 = self->posY.i.hi - 0x13;
            prim->y1 = prim->y0;
            prim->y2 = self->posY.i.hi + 0x15;
            prim->y3 = prim->y2;
        } else {
            DestroyEntity(self);
            return;
        }
        self->animCurFrame = 0;
        self->ext.et_801D064C.unk80 = 0;
        self->step_s = 0;
        self->hitboxState = 0;
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
        self->step++;
        break;

    case 9:
        if (g_Timer % 2 == 0) {
            prim = self->ext.et_801D064C.unk7C;
            if (self->ext.et_801D064C.unk80 < 0x10) {
                if (self->facingLeft) {
                    prim->x0 -= 1;
                    prim->x1 -= 0;
                    prim->x2 -= 0;
                    prim->x3 -= 0;
                } else {
                    prim->x0 += 1;
                    prim->x1 += 0;
                    prim->x2 += 0;
                    prim->x3 += 0;
                }
            }
            if (self->ext.et_801D064C.unk80 < 0x26) {
                prim->y1++;
                prim->y0++;
            }
            if (self->ext.et_801D064C.unk80++ > 0x26) {
                DestroyEntity(self);
                return;
            }
        }
        break;

    case 10:
        for (i = 0; i < 4; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                MakeEntityFromId(E_ID_4D, self, tempEntity);
                tempEntity->animCurFrame = (Random() & 1) + 0x10;
                tempEntity->step = 11;
                tempEntity->velocityX = D_us_80182E88[i][0];
                tempEntity->velocityY = D_us_80182E88[i][1];
                tempEntity->flags |= FLAG_UNK_2000;
            }
        }
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 2;
        }
        PlaySfxPositional(SFX_SKELETON_DEATH_C);
        DestroyEntity(self);
        break;

    case 11:
        MoveEntity();
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->velocityY += FIX(0.25);
        break;

    case 16:
        if (g_pads[0].pressed & PAD_SQUARE) {
            if (!self->params) {
                self->animCurFrame++;
                self->params |= 1;
            }
        } else {
            self->params = 0;
        }
        break;
    }
}

INCLUDE_ASM("st/lib/nonmatchings/unk_4F918", func_us_801D1298);
