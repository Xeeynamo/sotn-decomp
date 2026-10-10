// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", EntityRdaiUnk33);

#include "../e_imp_death_particle.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BBE58_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BC650_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCA5C_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCB9C_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCD80_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCE4C_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCFC8_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", StepTowards);

void func_us_801D5DC8(Primitive* prim) {
    s32 yPos;
    switch (prim->p2) {
    case 0:
        LOW(prim->x2) = Random() * 8;
        prim->x3 = (Random() & 0x1F) + 0x10;
        prim->drawMode = DRAW_UNK02;
        prim->p2 += 1;

    case 1:
        yPos = (prim->y0 << 0x10) + prim->y1;
        yPos = yPos + LOW(prim->x2);
        LOW(prim->x2) -= 0x1000;
        prim->y0 = yPos >> 0x10;
        prim->y1 = yPos & 0xffff;
        if (!(prim->x3 -= 1)) {
            prim->p2 = 0;
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }
        return;
    }
}

extern Primitive* FindFirstUnkPrim(Primitive*);

extern EInit g_EInitCaveTroll;
extern s16 D_us_80182344[];
extern u8 D_us_80182364[];
extern u8 D_us_8018236C[];
extern u8 D_us_80182374[];
extern u8 D_us_80182384[];
extern u8 D_us_8018238C[];
extern s8 D_us_801823C0[][4];
extern u8 D_us_801823D4[];

void func_us_801D5E90(Entity* self) {
    Collider sp3C;
    Primitive* s0;
    Primitive* t;
    s32 s1;
    Entity* s2;
    s32 s4;
    s32 st;
    s16 s3;
    s32 s6;
    s32 s7;
    s16 t16;
    s8* s32_p_0;
    Entity* new_var;
    Entity* sp38;
    ;
    ;
    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
        // s2 = AllocEntity(&g_Entities[0xE0], D_80097C98); // D_80097C98
        s2 = AllocEntity(
            &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]); // FAKE!!
        if (s2) {
            CreateEntityFromEntity(E_EXPLOSION, self, s2);
            s2->params = 2;
        }
        DestroyEntity(self);
        return;
    };
    switch (self->step) {
    case 0x0:
        InitializeEntity(g_EInitCaveTroll);
        self->animCurFrame = 1;
        s7 = g_api_AllocPrimitives(0x11, 0x20);
        if (s7 == (-1)) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = s7;
        s0 = &g_PrimBuf[s7];
        self->ext.et_801D5E90.prim7C = s0;
        while (s0) {
            s0->u0 = (s0->v0 = 1);
            s0->r0 = 0x80;
            s0->g0 = 0x80;
            s0->b0 = 0xC0;
            s0->priority = self->zPriority + 1;
            s0->drawMode = DRAW_HIDE;
            s0 = s0->next;
        }

        break;

    case 0x1:
        if (UnkCollisionFunc3(D_us_80182344) & 1) {
            SetStep(2);
        }
        break;
        ;

    case 0x2:
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(3);
        }
        break;

    case 0x3:
        switch (self->step_s) {
        case 0:
            self->velocityY = 0xfffe0000;
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = 0xfffe8000;
            }
            self->step_s += 1;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (self->velocityY < 0) {
                self->animCurFrame = 2;
            }
            if (self->velocityY > (-0x8000)) {
                self->animCurFrame = 3;
            }
            if (self->velocityY > FIX(0.5)) {
                self->animCurFrame = 4;
            };
            s4 = self->posX.i.hi;
            s6 = self->posY.i.hi + 0x19;
            g_api_CheckCollision(s4, s6, &sp3C, 0);
            if (sp3C.effects & EFFECT_SOLID) {
                PlaySfxPositional(SFX_STOMP_HARD_D);
                s1 = sp3C.unk18;
                s4 = self->posX.i.hi;
                s6 = self->posY.i.hi + 0x11;
                g_api_CheckCollision(s4, s6, &sp3C, 0);
                if (sp3C.effects & EFFECT_SOLID) {
                    SetSubStep(3);
                } else {
                    self->posY.i.hi += s1;
                    s1 = (GetSideToPlayer() & 0x1) ^ 0x1;
                    s4 = GetDistanceToPlayerX();
                    if ((s1 != self->facingLeft) && (0x40 < s4)) {
                        SetSubStep(3);
                    } else {
                        SetSubStep(2);
                    }
                    if ((0x80 > s4) && (s4 > 0x20)) {
                        s1 = Random();
                        if (!(s1 & 1)) {
                            SetStep(4);
                        }
                        if ((s1 < 3) || (self->hitPoints < 0x10)) {
                            SetStep(5);
                        }
                    }
                }
            }
            break;

        case 2:
            if (AnimateEntity(D_us_80182364, self) == 0) {
                SetSubStep(0);
            }
            break;

        case 3: {
            if (AnimateEntity(D_us_8018236C, self) == 0) {
                self->facingLeft ^= 0x1;
                self->animCurFrame = 2;
                SetSubStep(0);
            }
        }
        }

        break;

    case 0x4: {
        switch (self->step_s) {
        case 0:
            s1 = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft == s1) {
                SetSubStep(2);
                break;
            }
            {
            case 1:
                if (AnimateEntity(D_us_8018236C, self, s2) == 0) {
                    self->facingLeft ^= 0x1;
                    self->animCurFrame = 1;
                    SetSubStep(2);
                }
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_8018238C, self)) {
                self->velocityX = 0;
                self->velocityY = 0xfffa0000;
                self->animCurFrame = 0x13;
                PlaySfxPositional(SFX_STOMP_HARD_E);
                self->step_s += 1;
            }
            break;

        case 3:
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if (self->velocityY > 0) {
                self->step_s += 1;
            }
            break;

        case 4:
            sp38 = g_Entities;
            s3 = GetAngleBetweenEntities(self, sp38);
            s3 -= 0x400;
            s3 &= 0xfff;
            if (self->facingLeft) {
                s3 = 0x1000 - s3;
            }
            if (s3 & 0x800) {
                SetSubStep(8);
            } else {
                self->ext.et_801D5E90.unk8C = s3;
                self->animCurFrame = 0x14;
                self->velocityY = 0;
                self->rotate = 0;
                self->drawFlags |= ENTITY_ROTATE;
                self->ext.et_801D5E90.unk91 = 1;
                self->step_s++;
            case 5:
                FntPrint("angle %x\n", self->ext.et_801D5E90.unk8C);

                s3 = self->ext.et_801D5E90.unk8C;
                s3 -= 0x380;
                if (StepTowards(&self->rotate, s3, 0x28)) {
                    self->step_s += 1;
                }
            }
            break;

        case 6:
            s2 = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (s2) {
                CreateEntityFromEntity(E_UNK_41, self, s2);
                s2->facingLeft = self->facingLeft;
                s3 = self->ext.et_801D5E90.unk8C;
                if (self->facingLeft) {
                    s2->posX.i.hi += (rsin(s3) * 9) >> 12;
                } else {
                    ;
                    s2->posX.i.hi -= (rsin(s3) * 9) >> 12;
                }
                s2->posY.i.hi += (9 * rcos(s3)) >> 0xc;
                s2->ext.et_801D5E90.unk8C = s3;
                s2->ext.et_801D5E90.ent9C = self;
            }
            self->ext.et_801D5E90.unk80 = 0x40;
            PlaySfxPositional(SFX_GUARD_TINK);
            self->step_s += 1;
            break;

        case 7:
            if (!(self->ext.et_801D5E90.unk80 -= 1)) {
                self->animCurFrame = 0x13;
                self->ext.et_801D5E90.unk91 = 0;
                self->step_s += 1;
            }
            break;

        case 8:
            StepTowards(&self->rotate, 0, 0x40);
            if (UnkCollisionFunc3(D_us_80182344) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                self->drawFlags = ENTITY_DEFAULT;
                s6 = 9;
                SetSubStep(s6);
                self->pose = 1;
            }
            break;

        case 9:
            if (AnimateEntity(D_us_80182364, self) == 0) {
                s1 = SetStep(3);
            }
            break;
        }

    } break;

    case 0x5:
        s4 = self->step_s;
        switch (s4) {
        case 0:
            self->ext.et_801D5E90.unk90 = 0;
            s1 = (GetSideToPlayer() & 0x1) ^ 0x1;
            if (self->facingLeft == s1) {
                SetSubStep(2);
            } else {
            case 1:
                if (AnimateEntity(D_us_8018236C, self, s2) == 0) {
                    self->facingLeft ^= 0x1;
                    self->animCurFrame = 1;
                    SetSubStep(2);
                }
            }
            break;

        case 2:
            s2 = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (s2) {
                PlaySfxPositional(SFX_RNO4_MAGIC_GLASS_BREAK);
                CreateEntityFromEntity(E_UNK_42, self, s2);
                s2->facingLeft = self->facingLeft;
                s2->zPriority = self->zPriority + 1;
                s2->ext.et_801D5E90.ent9C = self;
                SetSubStep(3);
            } else {
                SetStep(3);
                break;
            }

        case 3:
            if (AnimateEntity(D_us_80182374, self) == 0) {
                self->ext.et_801D5E90.unk90 = 1U;
                SetSubStep(4);
            }
            break;

        case 4:
            AnimateEntity(D_us_80182384, self);
            if (!self->ext.et_801D5E90.unk90) {
                SetStep(3);
            }
            break;
        }

        break;

    case 0xFF:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & 0x8000) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
    }

    s32_p_0 = &D_us_801823C0[0][0];
    s1 = D_us_801823D4[self->animCurFrame];
    s32_p_0 = s32_p_0;
    s32_p_0 = s32_p_0 + (s1 * 4);
    self->hitboxOffX = *(s32_p_0++);
    self->hitboxOffY = *(s32_p_0++);
    self->hitboxWidth = *(s32_p_0++);
    self->hitboxHeight = *(s32_p_0++);
    if (self->ext.et_801D5E90.unk91) {
        s0 = self->ext.et_801D5E90.prim7C;
        s0 = FindFirstUnkPrim(s0);
        if (s0) {
            s4 = self->posX.i.hi;
            s6 = self->posY.i.hi;
            s3 = Random() << 4;
            st = Random() & 0x1F;
            s4 += (st * rcos(s3)) >> 12;
            s6 += (st * rsin(s3)) >> 0xc;
            s0->x0 = s4;
            s0->y0 = s6;
            s0->p2 = 0;
            s0->p3 = 1;
        }
    }
    s0 = self->ext.et_801D5E90.prim7C;
    while (s0) {
        if (s0->p3) {
            func_us_801D5DC8(s0);
        }

        // This might be a fake, at the very least it's very unconventional
        // to cast a pointer to s32 first and then to Primitve* later
        s1 = (s32)s0->next;
        if (!s1) {
            s0->x0 = 0;
            s0->y0 = 0;
            s0->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        }
        s0 = (Primitive*)s1;
    }
}

extern u16 D_us_80180B6C;

void func_us_801D68E0(Entity* self) {
    Primitive* prim;
    Entity* ent;
    s32 xPosition;
    s32 primIndex;
    s32 yPosition;
    s16 angle;

    if (self->hitFlags && !(self->hitFlags & 0x80)) {
        self->hitboxState = 0;
        SetStep(2);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180B6C);
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);

        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801D68E0.unk7C = prim;

        prim->x0 = (prim->x1 = self->posX.i.hi);
        prim->y0 = (prim->y1 = self->posY.i.hi);
        prim->r0 = 0xFF;
        prim->g0 = 0x60;
        prim->b0 = 0x60;
        prim->r1 = 0x80;
        prim->g1 = 0x40;
        prim->b1 = 0x40;
        prim->priority = self->zPriority;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;

        angle = self->ext.et_801D68E0.unk8C;

        if (self->facingLeft) {
            angle = -angle;
        }

        self->velocityX = rsin((s32)angle) * (-0x80);
        self->velocityY = rcos((s32)angle) << 7;
        self->ext.et_801D68E0.unk80 = 0x20;

    case 1:
        MoveEntity();

        prim = self->ext.et_801D68E0.unk7C;
        xPosition = (prim->x0 = self->posX.i.hi);
        yPosition = (prim->y0 = self->posY.i.hi);

        if (!(self->ext.et_801D68E0.unk80 -= 1)) {
            self->step = 2;
        }

        break;

    case 2:
        self->velocityX = -self->velocityX;
        self->velocityY = -self->velocityY;
        self->step++;

    case 3:
        MoveEntity();

        prim = self->ext.et_801D68E0.unk7C;
        xPosition = (prim->x0 = self->posX.i.hi);
        yPosition = (prim->y0 = self->posY.i.hi);

        prim = self->ext.et_801D68E0.unk7C;
        xPosition -= prim->x1;
        yPosition -= prim->y1;

        if ((abs(xPosition) < 8) && (abs(yPosition) < 8)) {
            DestroyEntity(self);
        }
    }

    ent = self->ext.et_801D68E0.unk9C;
#if defined(VERSION_PSP) || defined(FIX_UB)
    // Non-PSX versions fix a null pointer here
    if (ent != NULL) {
#else
    if (1) {
#endif
        if (ent->entityId != 0x40) {
            DestroyEntity(self);
        }
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801D6B8C);
