// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

extern AnimationFrame D_us_80180F8C[];

void func_us_801B81E8(Entity* self) {
    if (self->ext.et_801B81E8.unkEntity->step != 4) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->velocityY = FIX(-3.0 / 8.0);
        self->velocityX = FIX(1.0 / 4.0);
        if (self->facingLeft) {
            self->velocityX = FIX(-0.25);
        }
        self->unk5A = 0x20;
        self->palette = PAL_OVL(0x19F);
        self->anim = &D_us_80180F8C;
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
        self->facingLeft = 0;
        self->posY.i.hi -= 16;
        self->posX.val += self->velocityX << 5;
        break;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
}

extern s32 D_us_801D637C;

void func_us_801B832C(s8* msg) {
    s32 temp_v0;

    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    temp_v0 = D_us_801D637C & 4;
    D_us_801D637C++;
    if (temp_v0 != 0) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

// dead code
INCLUDE_ASM("st/no1/nonmatchings/unk_381E8", func_us_801B83CC);

// Baby birds in the nest
extern AnimationFrame* D_us_80181000[];

void func_us_801B8430(Entity* self) {
    s8 index;
    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->flags &= ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                         FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA);
        self->animSet = ANIMSET_OVL(1);
        self->zPriority = PLAYER.zPriority + 4;
        self->animFrameDuration = self->animFrameIdx = 0;
        self->anim = D_us_80181000[g_CastleFlags[NO1_BIRD_CYCLE]];
    }
    g_api.UpdateAnim(NULL, NULL);
}

extern AnimationFrame D_us_80180FE0[];
extern AnimationFrame* D_us_80181020[];
extern AnimationFrame D_us_80181044[];
extern AnimationFrame D_us_80181060[];
extern AnimationFrame D_us_80181108[];
extern AnimationFrame* D_us_80181348[];
extern AnimationFrame* D_us_80181368[];
extern s32 D_us_80181388;

// The bird life cycle at the bottom of NO1
void func_us_801B84E4(Entity* self) {
    s16 posX;

    FntPrint("tori_w:%02x\n", g_CastleFlags[NO1_BIRD_CYCLE]);
    FntPrint("obj_step:%02x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->flags |= FLAG_UNK_10000000;
        self->flags &= ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                         FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                         FLAG_UNK_20000000 | FLAG_UNK_02000000);
        if (g_CastleFlags[NO1_BIRD_CYCLE] == 8) {
            self->step = 0xFF;
        } else {
            self->ext.et_801B84E4.unk7C =
                self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (g_CastleFlags[NO1_BIRD_CYCLE] >= 5) {
                self->ext.et_801B84E4.unk7C += 9;
            }
            self->ext.et_801B84E4.unk7E = self->ext.et_801B84E4.unk7C + 0x20;
            self->velocityX = FIX(-1.375);
            self->posY.i.hi -= 0x16;
            self->animSet = 0x8001;
            self->zPriority = PLAYER.zPriority;
            self->animFrameDuration = self->animFrameIdx = 0;
            self->anim = D_us_80181044;
        }
        break;

    case 1:
        self->posX.i.hi = 0x130;
        if (g_Tilemap.scrollY.i.hi >= 0x48) {
            self->step++;
        }
        break;

    case 2:
        self->posX.val += self->velocityX;
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if ((posX - self->ext.et_801B84E4.unk7E) < 0x28) {
            self->velocityX += 0x600;
        }
        if (posX <= self->ext.et_801B84E4.unk7E) {
            self->animFrameDuration = self->animFrameIdx = 0;
            self->anim = D_us_80181060;
            self->ext.et_801B84E4.unk80 = 0x90;
            if (g_CastleFlags[NO1_BIRD_CYCLE] == 7) {
                (self - 1)->anim = D_us_80180FE0;
                (self - 1)->animFrameDuration = (self - 1)->animFrameIdx = 0;
                self->ext.et_801B84E4.unk80 = 0x100;
                g_api.PlaySfx(0x7B7);
            }
            self->step++;
        }
        break;

    case 3:
        if (--self->ext.et_801B84E4.unk80 == 0) {
            self->velocityY = FIX(0.15625);
            self->velocityX = FIX(-0.5);
            self->step++;
            if (g_CastleFlags[NO1_BIRD_CYCLE] == 7) {
                self->velocityX = FIX(-1.375);
                self->step = 8;
                self->animFrameDuration = self->animFrameIdx = 0;
                self->anim = D_us_80181044;
                self->zPriority = PLAYER.zPriority + 8;
                (self - 1)->anim = D_us_80181020[g_CastleFlags[NO1_BIRD_CYCLE]];
            }
        }
        break;

    case 4:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (posX <= self->ext.et_801B84E4.unk7C) {
            self->animFrameDuration = self->animFrameIdx = 0;
            self->anim = D_us_80181348[g_CastleFlags[NO1_BIRD_CYCLE]];
            self->posY.i.hi = (self - 1)->posY.i.hi;
            if (g_CastleFlags[NO1_BIRD_CYCLE] == 2 ||
                g_CastleFlags[NO1_BIRD_CYCLE] == 3 ||
                g_CastleFlags[NO1_BIRD_CYCLE] == 4) {
                self->zPriority = PLAYER.zPriority + 8;
            }
            if (g_CastleFlags[NO1_BIRD_CYCLE] >= 5) {
                self->posY.i.hi -= 0x10;
            }
            self->step++;
        }
        break;

    case 5:
        if (self->animFrameDuration >= 0) {
            break;
        }
        self->step++;
        if (D_us_80181368[g_CastleFlags[NO1_BIRD_CYCLE]] != NULL) {
            self->animFrameDuration = self->animFrameIdx = 0;
            self->anim = D_us_80181368[g_CastleFlags[NO1_BIRD_CYCLE]];
            if (g_CastleFlags[NO1_BIRD_CYCLE]) {
                self->zPriority = PLAYER.zPriority + 8;
            }
            break;
        }
    case 6:
        if (self->animFrameDuration < 0) {
            g_api.PlaySfx(SFX_WING_FLAP_A);
            D_us_80181388 = 0;
            self->step++;
            self->animFrameDuration = self->animFrameIdx = 0;
            self->anim = D_us_80181108;
            self->posY.i.hi -= 20;
            if (g_CastleFlags[NO1_BIRD_CYCLE] >= 5) {
                self->posY.i.hi += 16;
            }
            self->zPriority = PLAYER.zPriority + 8;
            (self - 1)->anim = D_us_80181020[g_CastleFlags[NO1_BIRD_CYCLE]];
        }
        break;

    case 7:
        D_us_80181388++;
        if (D_us_80181388 < 0x31 && D_us_80181388 % 16 == 0) {
            g_api.PlaySfx(SFX_WING_FLAP_A);
        }
        if (self->animFrameDuration < 0) {
            self->velocityX = FIX(-1.375);
            self->animFrameDuration = self->animFrameIdx = 0;
            self->anim = D_us_80181044;
            self->step++;
        }
        break;

    case 8:
        D_us_80181388++;
        if (D_us_80181388 < 0x31 && D_us_80181388 % 16 == 0) {
            g_api.PlaySfx(SFX_WING_FLAP_A);
        }
        self->posX.val += self->velocityX;
        if (self->posX.i.hi < -0x28) {
            g_CastleFlags[NO1_BIRD_CYCLE]++;
            if (g_CastleFlags[NO1_BIRD_CYCLE] == 9) {
                g_CastleFlags[NO1_BIRD_CYCLE] = 0;
            }
            self->step++;
        }
        break;

    default:
        self->animSet = 0;
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
}

extern AnimationFrame D_us_80181044[];
extern AnimationFrame D_us_80181108[];
extern AnimationFrame D_us_8018132C[];

// Triggers in the bottom room of NO1
void func_us_801B8B00(Entity* self) {
    s16 offsetX;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->flags |= FLAG_UNK_10000000;
        self->flags &= ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                         FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                         FLAG_UNK_20000000 | FLAG_UNK_02000000);

        if (g_CastleFlags[NO1_BIRD_CYCLE] != 8) {
            self->step = 0xFF;
        } else {
            self->posY.i.hi -= 16;

            offsetX = -6;
            if (self->params) {
                offsetX = 6;
            }
            self->posX.i.hi += offsetX;

            self->animSet = ANIMSET_OVL(1);
            self->zPriority = PLAYER.zPriority;
            self->animFrameDuration = self->animFrameIdx = 0;
            self->anim = D_us_8018132C;

            if (self->params) {
                self->animFrameIdx = 3;
            }
        }
        break;

    case 1:
        if (g_Tilemap.scrollY.i.hi >= 72) {
            if (self->params) {
                self->ext.bird.timer = 0x300;
            } else {
                self->ext.bird.timer = 0x200;
            }
            self->step++;
        }
        break;

    case 2:
        if (--self->ext.bird.timer == 0) {
            self->animFrameDuration = self->animFrameIdx = 0;
            self->anim = D_us_80181108;
            self->posY.i.hi -= 4;
            g_api.PlaySfx(SFX_WING_FLAP_A);
            self->step++;
        }
        break;

    case 3:
        if (self->animFrameDuration < 0) {
            self->velocityX = FIX(-1.375);
            self->animFrameDuration = self->animFrameIdx = 0;
            self->anim = D_us_80181044;
            self->step++;
        }
        break;

    case 4:
        self->posX.val += self->velocityX;
        if (self->posX.i.hi < -0x28) {
            if (self->params) {
                g_CastleFlags[NO1_BIRD_CYCLE] = 0;
            }
            self->step++;
        }
        break;

    default:
        self->animSet = 0;
        break;
    }

    g_api.UpdateAnim(NULL, NULL);
}

INCLUDE_ASM("st/no1/nonmatchings/unk_381E8", func_us_801B8D30);

// entering doppleganger's room
INCLUDE_ASM("st/no1/nonmatchings/unk_381E8", func_us_801B8F50);

extern u16 D_us_8018142C[];
extern u16 D_us_80181440[];

// Seems to be some kind of helper for the chair next to the save room
// It spawns the table and chair sprite
void func_us_801B9028(Entity* self) {
    switch (self->step) { /* irregular */
    case 0:
        InitializeEntity(D_us_80180A4C);
        self->animCurFrame = self->params + 1;
        self->zPriority = D_us_8018142C[self->params];
        self->drawFlags = FLAG_DRAW_UNK8;
        self->unk6C = D_us_80181440[self->params];
        return;
    case 1:
        break;
    case 2:
#include "../../st/pad2_anim_debug.h"
    }
}

INCLUDE_ASM("st/no1/nonmatchings/unk_381E8", func_us_801B9184);

extern s16 D_us_80181454[];
extern s16 D_us_80181464[];
extern s32 D_psp_091CE570;

void func_us_801B9304(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s16 angle;
    u8 count;

#ifdef VERSION_PSP
    if (D_psp_091CE570) {
        func_psp_0925F440();
    }
#endif
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
#ifdef VERSION_PSP
        func_psp_0925F440();
#endif
        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 0xE);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801B9304.unk7C = prim;
            self->ext.et_801B9304.unk84 = prim;
            for (i = 0; prim != NULL; i++, prim = prim->next,
                prim->drawMode &= ~DRAW_UNK02, prim = prim->next) {
                UnkPolyFunc2(prim);
                prim->tpage = 0x11;
                prim->clut = 0x19C;
#ifdef VERSION_PSP
                prim->u0 = prim->u2 = i * 18;
                prim->u1 = prim->u3 = prim->u0 + 0x12;
#else
                prim->u0 = prim->u2 = i * 16 + 8;
                prim->u1 = prim->u3 = prim->u0 + 0x10;
#endif
                prim->v0 = prim->v1 = 0x6C;
                prim->v2 = prim->v3 = prim->v0 + 0x10;
                prim->next->x1 = D_us_80181464[i];
                prim->next->x1 += D_us_80181454[i];
                prim->next->y0 = 0xA8;
                prim->next->r3 = i;
                LOH(prim->next->r2) = LOH(prim->next->b2) = 0x10;
                prim->next->b3 = 0;
                LOH(prim->next->u1) = 0x400;
                prim->priority = 0xB1;
                prim->drawMode = DRAW_HIDE;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801B9304.unk80 = 1;
        break;

    case 1:
        if (!--self->ext.et_801B9304.unk80) {
            self->ext.et_801B9304.unk80 = 8;
            prim = self->ext.et_801B9304.unk84;
            prim->next->u2 = 1;
            prim = prim->next;
            prim = prim->next;
            if (prim == NULL) {
                self->step++;
            } else {
                self->ext.et_801B9304.unk84 = prim;
            }
        }
        prim = self->ext.et_801B9304.unk7C;
        while (prim != NULL) {
            if (prim->p3 == 8) {
                func_us_801B9184(prim);
            }
            prim = prim->next;
        }
        break;

    case 2:
        count = 0;
        prim = self->ext.et_801B9304.unk7C;
        while (prim != NULL) {
            if (prim->p3 == 8) {
                count += func_us_801B9184(prim);
            }
            prim = prim->next;
        }
        if (count == 7) {
            self->step++;
        }
        break;

    case 3:
        prim = self->ext.et_801B9304.unk7C;
        while (prim != NULL) {
            UnkPolyFunc0(prim);
            prim = prim->next;
            prim = prim->next;
        }
        prim = self->ext.et_801B9304.unk7C;
        prim->tpage = 0x11;
        prim->clut = 0x19C;
#ifdef VERSION_PSP
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = prim->u0 + 0x7E;
#else
        prim->u0 = prim->u2 = 8;
        prim->u1 = prim->u3 = prim->u0 + 0x70;
#endif
        prim->v0 = prim->v1 = 0x6C;
        prim->v2 = prim->v3 = prim->v0 + 0x10;
        prim->x0 = prim->x2 = D_us_80181464[0] - 8;
        prim->x1 = prim->x3 = prim->x0 + 0x70;
        prim->y0 = prim->y1 = 0xA0;
        prim->y2 = prim->y3 = 0xB0;
        prim->priority = 0xB0;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        self->ext.et_801B9304.unk84 = prim;
        for (i = 0; i < 3; i++) {
            UnkPolyFunc2(prim);
            prim->tpage = 0x11;
            prim->clut = 0x19C;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v1 = 0x6C;
            prim->v2 = prim->v3 = prim->v0 + 0x10;
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = 0;
            prim->next->x1 = D_us_80181464[0] - 8;
            prim->next->y0 = 0xA8;
            prim->next->r3 = i * 2;
            LOH(prim->next->r2) = 0x12;
            LOH(prim->next->b2) = 0x12;
            prim->next->b3 = 0x48;
            LOH(prim->next->u1) = 0;
            prim->priority = 0xB1;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
            prim->drawMode &= ~DRAW_UNK02;
            prim = prim->next;
        }
        self->step++;
        /* fallthrough */
    case 4:
        count = 0;
        prim = self->ext.et_801B9304.unk84;
        for (i = 0; i < 3; i++) {
            if (prim->next->r3) {
                prim->next->r3 -= 1;
            } else {
                prim->next->x1 += 2;
                prim->u0 = prim->u2 += 2;
                prim->u1 = prim->u3 += 2;
                UnkPrimHelper(prim);
            }
            if (prim->u3 > 0x80) {
                prim->drawMode = DRAW_HIDE;
                count++;
            }
            prim = prim->next;
            prim = prim->next;
        }
        if (count == 3) {
            self->step++;
        }
        break;

    case 5:
        prim = self->ext.et_801B9304.unk84;
        for (i = 0; i < 3; i++) {
            UnkPolyFunc0(prim);
            prim = prim->next;
            prim = prim->next;
        }
        prim = self->ext.et_801B9304.unk84;
        prim->tpage = 0x1A;
        prim->clut = 0x19E;
        prim->u0 = prim->u2 = 0xA8;
        prim->u1 = prim->u3 = prim->u0 + 0x10;
        prim->v0 = prim->v1 = 0x60;
        prim->v2 = prim->v3 = prim->v0 + 0x10;
        prim->x0 = prim->x2 = 0x80;
        prim->x1 = prim->x3 = prim->x0;
        prim->y0 = prim->y1 = 0xA8;
        prim->y2 = prim->y3 = prim->y0;
        prim->x0 -= 6;
        prim->x1 += 4;
        prim->x2 -= 7;
        prim->x3 += 24;
        prim->y0 -= 9;
        prim->y1 -= 4;
        prim->y2 += 6;
        prim->y3 += 48;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xB1;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        self->ext.et_801B9304.unk88 = 8;
        prim = self->ext.et_801B9304.unk7C;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        self->step++;
        break;

    case 7:
        prim = self->ext.et_801B9304.unk7C;
        prim->x0 = prim->x2 -= 6;
        prim->x1 = prim->x3 += 6;
        PrimDecreaseBrightness(prim, 7);
        count = PrimDecreaseBrightness(self->ext.et_801B9304.unk84, 7);
        if (!count) {
            DestroyEntity(self);
            return;
        }
        /* fallthrough */
    case 6:
        prim = self->ext.et_801B9304.unk7C;
        if (prim->y0 < (prim->y2 - 2)) {
            prim->y0 = ++prim->y1;
            prim->y2 = --prim->y3;
        } else {
            prim->y0 = prim->y1 = prim->y2 - 1;
            self->step = 7;
        }
        self->ext.et_801B9304.unk88 += 0x40;
        prim = self->ext.et_801B9304.unk84;
        angle = self->ext.et_801B9304.unk88 + 0x600;
        prim->u0 = ((rcos(angle) * 0xC) >> 0xC) + 0xB0;
        prim->v0 = ((rsin(angle) * 0xC) >> 0xC) + 0x68;
        angle = self->ext.et_801B9304.unk88 + 0x200;
        prim->u1 = ((rcos(angle) * 0xC) >> 0xC) + 0xB0;
        prim->v1 = ((rsin(angle) * 0xC) >> 0xC) + 0x68;
        angle = self->ext.et_801B9304.unk88 + 0xA00;
        prim->u2 = ((rcos(angle) * 0xC) >> 0xC) + 0xB0;
        prim->v2 = ((rsin(angle) * 0xC) >> 0xC) + 0x68;
        angle = self->ext.et_801B9304.unk88 + 0xE00;
        prim->u3 = ((rcos(angle) * 0xC) >> 0xC) + 0xB0;
        prim->v3 = ((rsin(angle) * 0xC) >> 0xC) + 0x68;
        break;
    }
}

extern u32 D_psp_0929A690;
extern u32 D_psp_0929A6D8;

void func_us_801B9BE4(Entity* self) {
    Entity* tempEntity;
    s16 volume;
    s16 distance;
    s32 xOffset, yOffset;
    s32 dx, dy;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A1C);
        self->animCurFrame = 0x1C;
        self->zPriority = 0x6C;
        if (!self->params) {
#ifdef VERSION_PSP
            CreateEntityFromEntity(D_psp_0929A6D8, self, self + 1);
#else
            CreateEntityFromEntity(E_ID_33, self, self + 1);
#endif
            (self + 1)->params = 1;
            (self + 1)->posY.i.hi += 0x10;
            self->step = 3;
        } else {
            self->palette = 0x8041;
            self->hitboxState = 3;
            self->hitboxWidth = 6;
            self->hitboxHeight = 0x12;
            self->hitboxOffY = -4;
            self->drawFlags = FLAG_DRAW_ROTZ;
            self->rotZ = -0x80;
            self->animCurFrame = 0x1D;
            self->step = 1;
            if (g_CastleFlags[NO1_ELEVATOR_ACTIVATED]) {
                g_api.InitClutAnimation(0x8003);
                g_api.PlaySfxVolPan(0x7AA, 0, 0);
                self->hitboxState = 0;
                self->step = 2;
            }
        }
        break;

    case 1:
        self->hitboxOffX = -((rsin(self->rotZ) * 32) >> 0xC);
        self->hitboxOffY = ((rcos(self->rotZ) * 32) >> 0xC);
        xOffset = ((rsin(self->rotZ) * 18) >> 0xC);
        yOffset = -((rcos(self->rotZ) * 18) >> 0xC);
        tempEntity = self - 1;
        tempEntity->posX.i.hi = self->posX.i.hi + xOffset;
        tempEntity->posY.i.hi = self->posY.i.hi + yOffset;
        switch (self->step_s) {
        case 0:
            if (self->hitFlags) {
                g_api.PlaySfx(SFX_DOOR_OPEN);
                self->ext.et_801B9BE4.unk80 = 16;
                self->step_s++;
            }
            break;

        case 1:
            self->rotZ += 4;
            if (!--self->ext.et_801B9BE4.unk80) {
                self->step_s--;
            }
            if (self->rotZ >= 0x20) {
                self->hitboxState = 0;
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
#ifdef VERSION_PSP
                    CreateEntityFromEntity(D_psp_0929A690, self, tempEntity);
#else
                    CreateEntityFromEntity(E_ID_5E, self, tempEntity);
#endif
                }
                g_api.func_80102CD8(1);
                g_api.InitClutAnimation(0x8003);
                g_api.PlaySfx(SFX_WEAPON_APPEAR);
                g_api.PlaySfxVolPan(0x7AA, 0x7F, 0);
                g_CastleFlags[NO1_ELEVATOR_ACTIVATED] = 1;
                self->step = 2;
            }
            break;
        }
        break;

    case 2:
        self->rotZ = 0x20;
        xOffset = ((rsin(self->rotZ) * 18) >> 0xC);
        yOffset = -((rcos(self->rotZ) * 18) >> 0xC);
        tempEntity = self - 1;
        tempEntity->posX.i.hi = self->posX.i.hi + xOffset;
        tempEntity->posY.i.hi = self->posY.i.hi + yOffset;
        dx = self->posX.i.hi - 0x80;
        distance = (abs(dx) - 0x20) >> 5;
        if (distance > 8) {
            distance = 8;
        } else if (distance < 0) {
            distance = 0;
        }
        if (dx < 0) {
            distance = -distance;
        }
        dx = GetDistanceToPlayerX() / 2;
        dy = GetDistanceToPlayerY();
        dx = dx * dx + dy * dy;
        dx = SquareRoot0(dx);
        volume = 0xA0 - dx;
        if (volume > 0x7F) {
            volume = 0x7F;
        }
        if (volume < 0) {
            volume = 0;
        }
        g_api.SetVolumeCommand22_23(volume, distance);
        FntPrint("vol:%x\n", volume);
        break;
    }
}

extern u16 D_us_80180A04[];

void func_us_801BA034(Entity* self) {
    Entity* entity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A04);
        if (g_CastleFlags[NO1_UNKNOWN_FLAG]) {
            self->posY.i.hi = 0xC3;
            self->step = 3;
        }
        break;
    case 1:
        self->posY.i.hi = 0xC0;
        if (GetPlayerCollisionWith(self, 16, 7, 4) & 0xFF) {
            self->step++;
        }
        break;
    case 2:
        GetPlayerCollisionWith(self, 16, 7, 4);
        if (!(g_Timer & 0xF)) {
            self->posY.i.hi++;
        }
        if (self->posY.i.hi > 0xC2) {
            g_api.func_80102CD8(1);
            g_CastleFlags[NO1_UNKNOWN_FLAG] = 1;
            self->step++;
        }
        if (g_Timer % 10 == 0) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(6, self, entity);
                entity->params = 0x10;
                entity->posY.i.hi = 0xBC;
                entity->rotZ = -0x300;
                entity->posX.i.hi -= 11;
                entity->drawFlags |= FLAG_DRAW_ROTZ;
            }
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(6, self, entity);
                entity->params = 0x10;
                entity->posY.i.hi = 0xBC;
                entity->rotZ = 0x300;
                entity->posX.i.hi += 11;
                entity->drawFlags |= FLAG_DRAW_ROTZ;
            }
        }
        break;
    case 3:
        self->posY.i.hi = 0xC3;
        break;
    }
}

extern s16 D_us_80181474[][3];
extern s16 D_us_801814B4[];
extern u8 D_us_801814C4[];
extern SVECTOR D_us_801814D0;
extern s32 D_psp_0929A6D0;

// This is the spyglass at the bottom of NO1
void func_us_801BA290(Entity* self) {
    long unusedA;
    long unusedB;
    s32 pad[23];
    SVECTOR rotA, rotB, rotC, rotD;
    VECTOR trans;
    MATRIX m;
    s32 pad2[18];
    DRAWENV drawEnv;
    RECT clipRect;

    s16 dy;
    DR_ENV* dr_env;
    Primitive* prim;
    Primitive* prim2;
    s32 primIndex;
    u8 rnd;
    s32 i;
    Entity* tempEntity;

    if (self->step > 1 && self->step < 7) {
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 2;
        g_api.ResetAfterImage(0, 1);
        g_api.SetPlayerBlinkTimer(1, 0x20);
    }
    if (self->ext.et_801BA290.unkA4) {
        PLAYER.animCurFrame = 0;
        self->animCurFrame = 0;
    } else {
        self->animCurFrame = 0x3D;
    }
    self->ext.et_801BA290.unk9C = g_CastleFlags[NO1_WEATHER] & 1;
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809C8);
        self->animCurFrame = 0x3D;
        self->facingLeft = 1;
        self->hitboxState = 1;
        self->hitPoints = 0x7FFE;
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->flags |= FLAG_NOT_AN_ENEMY;
        self->ext.et_801BA290.unkA4 = 0;
        break;

    case 1:

        if (self->hitFlags && (g_pads[0].pressed & PAD_UP) &&
#ifdef VERSION_PSP
            !(g_Player.status + 0xF0000000)) {
#else
            (g_Player.status == PLAYER_STATUS_UNK10000000)) {
#endif
            g_Player.padSim = 0;
            g_Player.D_80072EFC = 2;
            g_PauseAllowed = false;
            g_api.PlaySfx(SFX_TINK_JINGLE);
            self->step++;
        }
        break;

    case 2:
        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 0x19);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BA290.unkAC = prim;
            dr_env = g_api.AllocateDrawEnvironment((POLY_GT4*)prim);
            if (dr_env == NULL) {
                g_PauseAllowed = true;
                DestroyEntity(self);
                return;
            }

            prim->type = PRIM_ENV;
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 0;
            drawEnv.r0 = 0;
            drawEnv.g0 = 0;
            drawEnv.b0 = 0;
            drawEnv.dtd = 0;
            drawEnv.ofs[0] = 0;
            clipRect.x = 0;
            clipRect.w = 0x100;
            clipRect.y = 0x14;
            clipRect.h = 0;
            drawEnv.clip = clipRect;
            SetDrawEnv(dr_env, &drawEnv);
            prim->priority = 0x4D;
            prim->drawMode = DRAW_UNK_1000 | DRAW_HIDE;
            prim = prim->next;

            dr_env = g_api.AllocateDrawEnvironment((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }

            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_UNK_800 | DRAW_HIDE;
            prim->priority = 0xDE;
            prim = prim->next;

            self->ext.et_801BA290.unk7C = prim;
            while (prim != NULL) {
                prim->r0 = prim->g0 = prim->b0 = 0x80;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim = prim->next;
            }
            self->step++;
            break;
        }
        g_PauseAllowed = true;
        DestroyEntity(self);
        break;

    case 3:
        prim = self->ext.et_801BA290.unk7C;
        for (i = 0; i < 2; i++) {
            prim->tpage = 0xE;
            if (self->ext.et_801BA290.unk9C != 0) {
                prim->clut = 0x204;
            } else {
                prim->clut = 0x206;
            }
            prim->u0 = 1;
            prim->u1 = 0x7F;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0x80;
            prim->v1 = prim->v0;
            prim->v2 = 0xEF;
            prim->v3 = prim->v2;
            prim->r0 = 0xC0;
            prim->g0 = 0xC0;
            prim->b0 = 0x60;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0x47;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            prim = prim->next;
        }
        for (i = 0; i < 2; i++) {
            prim->tpage = 0xE;
            if (self->ext.et_801BA290.unk9C != 0) {
                prim->clut = 0x203;
            } else {
                prim->clut = 0x205;
            }
            prim->u0 = 1;
            prim->u1 = 0x7F;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0x41;
            prim->v1 = prim->v0;
            prim->v2 = 0x51;
            prim->v3 = prim->v2;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0x47;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            prim = prim->next;
        }
        for (i = 0; i < 8; i++) {
            prim->tpage = 0xE;
            if (self->ext.et_801BA290.unk9C != 0) {
                prim->clut = 0x203;
            } else {
                prim->clut = 0x205;
            }
            prim->u0 = 1;
            prim->u1 = 0x7F;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0x5A;
            prim->v1 = prim->v0;
            prim->v2 = 0x79;
            prim->v3 = prim->v2;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0x47;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            prim = prim->next;
        }
        self->ext.et_801BA290.unk88 = prim;
        for (i = 0; i < 2; i++) {
            prim->type = PRIM_TILE;
            prim->x0 = 0;
            prim->x1 = 0x104;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->y0 = 0;
            prim->y1 = prim->y0;
            prim->y2 = 0xFF;
            prim->y3 = prim->y2;
            prim->u0 = 0xFF;
            prim->v0 = 0xFF;
            prim->r0 = 0;
            prim->b0 = 0;
            prim->g0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0xE4 + i * 2;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.et_801BA290.unk8C = prim;
        for (i = 0; i < 2; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            prim->u0 = 0;
            prim->u1 = 0x3F;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xC0;
            prim->v1 = prim->v0;
            prim->v2 = 0xFF;
            prim->v3 = prim->v2;
            prim->x0 = 0x50;
            prim->x1 = 0xB0;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->y0 = 0x50;
            prim->y1 = prim->y0;
            prim->y2 = 0xB0;
            prim->y3 = prim->y2;
            prim->r0 = 0;
            prim->b0 = 0;
            prim->g0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0xE3 + i * 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.et_801BA290.unk90 = prim;
        for (i = 0; i < 2; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x19F;
            prim->u0 = 0;
            prim->u1 = 0x3F;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xC0;
            prim->v1 = prim->v0;
            prim->v2 = 0xFF;
            prim->v3 = prim->v2;
            prim->x0 = 0x40;
            prim->x1 = 0xC0;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->y0 = 0x40;
            prim->y1 = prim->y0;
            prim->y2 = 0xC0;
            prim->y3 = prim->y2;
            prim->r0 = 0;
            prim->b0 = 0;
            prim->g0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0xE3 + i * 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.et_801BA290.unk84 = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0xE;
        prim->clut = 0x44;
        prim->u0 = 0xD0;
        prim->u1 = 0xF8;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 0;
        prim->v1 = prim->v0;
        prim->v2 = 0x18;
        prim->v3 = prim->v2;
        LOH(prim->next->r2) = 0x28;
        LOH(prim->next->b2) = 0x18;
        LOH(prim->next->u1) = 0xB80;
        prim->next->b3 = 0x80;
        prim->next->x1 = 0x80;
        prim->next->y0 = 0x7E;
        prim->priority = 0x48;
        prim->drawMode = DRAW_UNK02;
        rnd = Random() & 3;
        if (!rnd) {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        prim = prim->next;

        self->ext.et_801BA290.unk98 = prim;
        prim->tpage = 0xE;
        prim->clut = 0x19F;
        prim->u0 = 0xD0;
        prim->u1 = 0xF8;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 0;
        prim->v1 = prim->v0;
        prim->v2 = 0x16;
        prim->v3 = prim->v2;
        prim->r0 = 0x10;
        prim->g0 = 0x10;
        prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->p1 = 0;
        prim->p2 = 0;
        prim->priority = 0x44;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        if (self->ext.et_801BA290.unk9C == 0) {
            prim->drawMode = DRAW_HIDE;
        }
        if (!rnd) {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;

        self->ext.et_801BA290.unk94 = prim;
        prim->type = PRIM_TILE;
        prim->x0 = 0;
        prim->y0 = 0;
        prim->u0 = 0xFF;
        prim->v0 = 0x80;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0xE8;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        prim->type = PRIM_TILE;
        prim->x0 = 0;
        prim->y0 = 0x80;
        prim->u0 = 0xFF;
        prim->v0 = 0x80;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0xE8;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        self->ext.et_801BA290.unk80 = 0xB80;
        self->step++;
        break;

    case 4:
        prim = self->ext.et_801BA290.unk88;
        prim->type = PRIM_G4;
        prim->r0 += 4;
        prim->g0 = prim->b0 = prim->r0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        if (prim->r0 > 0xF0) {
            prim->type = PRIM_TILE;
            self->ext.et_801BA290.unkA4 = 1;
            g_Tilemap.flags ^= 1;
            prim = self->ext.et_801BA290.unkAC;
            for (i = 0; i < 2; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            self->step_s = 0;
            self->step++;
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            prim = self->ext.et_801BA290.unk94;
            prim->x0 = 0;
            prim->y0 = 0U;
            prim->u0 = 0x50;
            prim->v0 = 0xFF;
            prim->drawMode = DRAW_DEFAULT;
            prim2 = prim->next;
            prim = prim2;

            prim->x0 = 0xB0;
            prim->y0 = 0;
            prim->u0 = 0x50;
            prim->v0 = 0xFF;
            prim->drawMode = DRAW_DEFAULT;
            prim = self->ext.et_801BA290.unk88;
            for (i = 0; i < 2; i++) {
                prim->x0 = prim->x2 = 0x50;
                prim->x1 = prim->x3 = 0xB0;
                prim->u0 = 0x60;
#ifdef VERSION_PSP
                prim->r0 = 0x40;
#else
                prim->r0 = 0x80;
#endif
                prim->g0 = prim->b0 = prim->r0;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim = prim->next;
            }
            self->step_s++;
            break;

        case 1:
            prim = self->ext.et_801BA290.unk90;
            for (i = 0; i < 2; i++) {
                prim->r0++;
                prim->g0 = prim->b0 = prim->r0;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                if (prim->r0 == 0x30) {
                    g_api.PlaySfx(0x7AC);
                    self->step_s = 2;
                }
                prim = prim->next;
            }
            break;

        case 2:
            prim = self->ext.et_801BA290.unk8C;
            for (i = 0; i < 2; i++) {
                prim->r0++;
                prim->g0 = prim->b0 = prim->r0;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                if (prim->r0 == 0x20) {
                    self->step_s = 3;
                }
                prim = prim->next;
            }
            break;

        case 3:
            self->ext.et_801BA290.unk80 -= 8;
            if (self->ext.et_801BA290.unk80 < 0x380) {
                self->ext.et_801BA290.unk82 = 0x80;
                self->step_s++;
                prim = self->ext.et_801BA290.unk84;
                LOW(prim->next->u0) = -0x1000;
                for (i = 0; i < 3; i++) {
                    tempEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (tempEntity != NULL) {
#ifdef VERSION_PSP
                        CreateEntityFromCurrentEntity(
                            D_psp_0929A6D0, tempEntity);
#else
                        CreateEntityFromCurrentEntity(0x34, tempEntity);
#endif
                        rnd = Random() & 7;
                        if (!(Random() & 1)) {
                            rnd = 7;
                        }
                        tempEntity->posX.i.hi = D_us_80181474[rnd][0];
                        tempEntity->posY.i.hi = D_us_80181474[rnd][1];
                        tempEntity->rotX = D_us_80181474[rnd][2];
                    }
                }
            }
            break;

        case 4:
            if (!--self->ext.et_801BA290.unk82) {
                g_api.PlaySfx(0x7AC);
                self->step_s = 0;
                self->step++;
            }
            break;
        }
        SetGeomScreen(0x400);
        rotD.vx = 0;
        rotD.vy = 0;
        rotD.vz = 0;
        RotMatrix(&D_us_801814D0, &m);
        trans.vx = -0x80;
        trans.vy = -0x80;
        trans.vz = self->ext.et_801BA290.unk80;
        TransMatrix(&m, &trans);
        SetRotMatrix(&m);
        SetTransMatrix(&m);
        SetGeomOffset(0x80, 0x80);
        for (i = 0; i < 7; i++) {
            rotA.vx = 0;
            rotB.vx = 0x8F;
            rotC.vx = 0xFE;
            rotA.vy = D_us_801814B4[i];
            rotB.vy = D_us_801814B4[i];
            rotC.vy = D_us_801814B4[i];
            rotA.vz = 0;
            rotB.vz = 0;
            rotC.vz = 0;
            rotA.pad = 0;
            rotB.pad = 0;
            rotC.pad = 0;
#ifdef VERSION_PSP
            RotTransPers3(&rotA, &rotB, &rotC, ((long*)(i * 12)) + (0x4000 | 0),
                          ((long*)(i * 12)) + (0x4000 | 1),
                          ((long*)(i * 12)) + (0x4000 | 2), &unusedA, &unusedB);
#else
            RotTransPers3(
                &rotA, &rotB, &rotC, ((long*)(i * 12)) + (0x7E00000 | 0),
                ((long*)(i * 12)) + (0x7E00000 | 1),
                ((long*)(i * 12)) + (0x7E00000 | 2), &unusedA, &unusedB);
#endif
        }
        prim = self->ext.et_801BA290.unk7C;
        for (rnd = 0, i = 0; i < 6; rnd += 3, i++) {
            LOW(prim->x0) = *(SPAD(i * 3) + 0);
            LOW(prim->x1) = *(SPAD(i * 3) + 1);
            LOW(prim->x2) = *(SPAD(i * 3) + 3);
            LOW(prim->x3) = *(SPAD(i * 3) + 4);
            prim = prim->next;

            LOW(prim->x0) = *(SPAD(i * 3) + 1);
            LOW(prim->x1) = *(SPAD(i * 3) + 2);
            LOW(prim->x2) = *(SPAD(i * 3) + 4);
            LOW(prim->x3) = *(SPAD(i * 3) + 5);
            prim = prim->next;
        }
        prim = self->ext.et_801BA290.unk84;
        LOH(prim->next->u1) = 0x400 - self->ext.et_801BA290.unk80;
        UpdateAnimation(D_us_801814C4, prim);
        UnkPrimHelper(prim);
        prim2 = self->ext.et_801BA290.unk98;
        UpdateAnimation(D_us_801814C4, prim2);
        prim2->x2 = prim->x2;
        prim2->x3 = prim->x3;
        prim2->x0 = prim2->x2;
        prim2->x1 = prim2->x3;
        prim2->y2 = prim->y2;
        prim2->y3 = prim->y3;
        dy = prim->y2 - prim->y0;
        prim2->y0 = dy + prim2->y2;
        prim2->y1 = dy + prim2->y3;
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            prim = self->ext.et_801BA290.unk8C;
            for (i = 0; i < 2; i++) {
                if (prim->y0 != 0x80) {
                    prim->y0 += 2;
                    prim->y1 = prim->y0;
                }
                if (prim->y2 != 0x80) {
                    prim->y2 -= 2;
                    prim->y3 = prim->y2;
                }
                prim = prim->next;
            }
            prim = self->ext.et_801BA290.unk90;
            for (i = 0; i < 2; i++) {
                if (prim->y0 != 0x80) {
                    prim->y0 += 2;
                    prim->y1 = prim->y0;
                }
                if (prim->y2 != 0x80) {
                    prim->y2 -= 2;
                    prim->y3 = prim->y2;
                } else {
                    self->step_s = 1;
                }
                prim = prim->next;
            }
            break;

        case 1:
            g_Tilemap.flags ^= 1;
            self->ext.et_801BA290.unkA4 = 0;
            prim = self->ext.et_801BA290.unk7C;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                if (prim == self->ext.et_801BA290.unk94) {
                    break;
                }
            }
            prim = self->ext.et_801BA290.unkAC;
            for (i = 0; i < 2; i++) {
                prim->drawMode |= DRAW_HIDE;
                prim = prim->next;
            }
            prim = self->ext.et_801BA290.unk94;
            prim->x0 = 0;
            prim->y0 = 0;
            prim->u0 = 0xFF;
            prim->v0 = 0x80;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;

            prim->x0 = 0;
            prim->y0 = 0x80;
            prim->u0 = 0xFF;
            prim->v0 = 0x80;
            prim->drawMode = DRAW_DEFAULT;
            self->step_s++;
            break;

        case 2:
            prim = self->ext.et_801BA290.unk94;
            prim->y0 -= 8;
            prim = prim->next;

            prim->y0 += 8;
            if (prim->y0 > 0x100) {
                self->step_s++;
            }
            break;

        case 3:
            primIndex = self->primIndex;
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
            self->hitboxState = 0;
            g_PauseAllowed = true;
            self->step++;
            break;
        }
        break;
    }
}

// Triggers when fully zoomed in after interacting with the spyglass
// Likely the fish function
extern u16 D_us_80180A34[];
extern u8 D_us_801814E0[];
extern s16 D_us_801814F8[];

void func_us_801BB4C0(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A34);
        self->zPriority = 0x49;
        self->animCurFrame = 0;
        self->drawFlags |= FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        self->rotY = self->rotX;
        self->ext.fish.timer = D_us_801814F8[Random() & 7];
        if (self->rotX < 0x100) {
            self->zPriority -= 4;
        }
        break;
    case 1:
        if (!--self->ext.fish.timer) {
            self->step++;
            return;
        }
        break;
    case 2:
        if (!AnimateEntity(D_us_801814E0, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
