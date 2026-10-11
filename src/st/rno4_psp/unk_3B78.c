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
    Collider collider;
    Primitive* prim;
    Entity* explosion;
    Entity* player;
    s8* frameParts;

    s32 primIndex;
    s32 genericInt;
    s32 posX;
    s32 posY;
    s32 radius;
    s16 angle;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
        explosion = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (explosion) {
            CreateEntityFromEntity(E_EXPLOSION, self, explosion);
            explosion->params = 2;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0x0:
        InitializeEntity(g_EInitCaveTroll);
        self->animCurFrame = 1;

        primIndex = g_api.AllocPrimitives(0x11, 0x20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;

        prim = &g_PrimBuf[primIndex];
        self->ext.et_801D5E90.prim7C = prim;

        while (prim) {
            prim->u0 = (prim->v0 = 1);
            prim->r0 = 0x80;
            prim->g0 = 0x80;
            prim->b0 = 0xC0;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        break;

    case 0x1:
        if (UnkCollisionFunc3(D_us_80182344) & 1) {
            SetStep(2);
        }
        break;

    case 0x2:
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(3);
        }
        break;

    case 0x3:
        switch (self->step_s) {
        case 0:
            self->velocityY = FIX(-2.0);
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->step_s += 1;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (self->velocityY < 0) {
                self->animCurFrame = 2;
            }
            if (self->velocityY > FIX(-0.5)) {
                self->animCurFrame = 3;
            }
            if (self->velocityY > FIX(0.5)) {
                self->animCurFrame = 4;
            };
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 0x19;

            g_api.CheckCollision(posX, posY, &collider, 0);

            if (collider.effects & EFFECT_SOLID) {
                PlaySfxPositional(SFX_STOMP_HARD_D);
                genericInt = collider.unk18;
                posX = self->posX.i.hi;
                posY = self->posY.i.hi + 0x11;

                g_api.CheckCollision(posX, posY, &collider, 0);

                if (collider.effects & EFFECT_SOLID) {
                    SetSubStep(3);
                } else {
                    self->posY.i.hi += genericInt;
                    genericInt = (GetSideToPlayer() & 0x1) ^ 0x1;
                    posX = GetDistanceToPlayerX();

                    if ((genericInt != self->facingLeft) && (0x40 < posX)) {
                        SetSubStep(3);
                    } else {
                        SetSubStep(2);
                    }

                    if ((0x80 > posX) && (posX > 0x20)) {
                        genericInt = Random();
                        if (!(genericInt & 1)) {
                            SetStep(4);
                        }
                        if ((genericInt < 3) || (self->hitPoints < 0x10)) {
                            SetStep(5);
                        }
                    }
                }
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_80182364, self)) {
                SetSubStep(0);
            }
            break;

        case 3:
            if (!AnimateEntity(D_us_8018236C, self)) {
                self->facingLeft ^= 0x1;
                self->animCurFrame = 2;
                SetSubStep(0);
            }
        }

        break;

    case 0x4: {
        switch (self->step_s) {
        case 0:
            genericInt = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft == genericInt) {
                SetSubStep(2);
                break;
            }

        case 1:
            if (!AnimateEntity(D_us_8018236C, self, explosion)) {
                self->facingLeft ^= 0x1;
                self->animCurFrame = 1;
                SetSubStep(2);
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
            player = g_Entities;
            angle = GetAngleBetweenEntities(self, player);
            angle -= 0x400;
            angle &= 0xfff;

            if (self->facingLeft) {
                angle = 0x1000 - angle;
            }

            if (angle & 0x800) {
                SetSubStep(8);
                break;
            } else {
                self->ext.et_801D5E90.unk8C = angle;
                self->animCurFrame = 0x14;
                self->velocityY = 0;
                self->rotate = 0;
                self->drawFlags |= ENTITY_ROTATE;
                self->ext.et_801D5E90.unk91 = 1;
                self->step_s++;
            }

        case 5:
            FntPrint("angle %x\n", self->ext.et_801D5E90.unk8C);

            angle = self->ext.et_801D5E90.unk8C;
            angle -= 0x380;
            if (StepTowards(&self->rotate, angle, 0x28)) {
                self->step_s += 1;
            }
            break;

        case 6:
            explosion = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (explosion) {
                CreateEntityFromEntity(E_UNK_41, self, explosion);
                explosion->facingLeft = self->facingLeft;
                angle = self->ext.et_801D5E90.unk8C;

                if (self->facingLeft) {
                    explosion->posX.i.hi += (rsin(angle) * 9) >> 12;
                } else {
                    explosion->posX.i.hi -= (rsin(angle) * 9) >> 12;
                }

                explosion->posY.i.hi += (9 * rcos(angle)) >> 0xc;
                explosion->ext.et_801D5E90.unk8C = angle;
                explosion->ext.et_801D5E90.ent9C = self;
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
                posY = 9;
                SetSubStep(posY);
                self->pose = 1;
            }
            break;

        case 9:
            if (!AnimateEntity(D_us_80182364, self)) {
                genericInt = SetStep(3);
            }
            break;
        }

    } break; // case 0x4

    case 0x5:
        switch (self->step_s) {
        case 0:
            self->ext.et_801D5E90.unk90 = 0;
            genericInt = (GetSideToPlayer() & 0x1) ^ 0x1;

            if (self->facingLeft == genericInt) {
                SetSubStep(2);
                break;
            }

        case 1:
            if (!AnimateEntity(D_us_8018236C, self, explosion)) {
                self->facingLeft ^= 0x1;
                self->animCurFrame = 1;
                SetSubStep(2);
            }
            break;

        case 2:
            explosion = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (explosion) {
                PlaySfxPositional(SFX_RNO4_MAGIC_GLASS_BREAK);
                CreateEntityFromEntity(E_UNK_42, self, explosion);
                explosion->facingLeft = self->facingLeft;
                explosion->zPriority = self->zPriority + 1;
                explosion->ext.et_801D5E90.ent9C = self;
                SetSubStep(3);
            } else {
                SetStep(3);
                break;
            }

        case 3:
            if (!AnimateEntity(D_us_80182374, self)) {
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
        break; // case 0x5

    case 0xFF:
        FntPrint("charal %x\n", self->animCurFrame);
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
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
    }

    frameParts = &D_us_801823C0[0][0];
    genericInt = D_us_801823D4[self->animCurFrame];
    frameParts = frameParts;
    frameParts = frameParts + (genericInt * 4);

    self->hitboxOffX = *(frameParts++);
    self->hitboxOffY = *(frameParts++);
    self->hitboxWidth = *(frameParts++);
    self->hitboxHeight = *(frameParts++);

    if (self->ext.et_801D5E90.unk91) {
        prim = self->ext.et_801D5E90.prim7C;
        prim = FindFirstUnkPrim(prim);
        if (prim) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            angle = Random() << 4;
            radius = Random() & 0x1F;
            posX += (radius * rcos(angle)) >> 12;
            posY += (radius * rsin(angle)) >> 12;
            prim->x0 = posX;
            prim->y0 = posY;
            prim->p2 = 0;
            prim->p3 = 1;
        }
    }

    prim = self->ext.et_801D5E90.prim7C;
    while (prim) {
        if (prim->p3) {
            func_us_801D5DC8(prim);
        }

        // This might be a fake, at the very least it's very unconventional
        // to cast a pointer to s32 first and then to Primitve* later
        // But seeing as genericInt is an all-purpose variable anyways,
        // it might just be true
        genericInt = (s32)prim->next;
        if (!genericInt) {
            prim->x0 = 0;
            prim->y0 = 0;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        }
        prim = (Primitive*)genericInt;
    }
}
