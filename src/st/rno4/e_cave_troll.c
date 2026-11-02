// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

extern Primitive* FindFirstUnkPrim(Primitive*);

extern EInit D_us_80180B6C;
extern EInit g_EInitCaveTroll;
extern EInit D_us_80180B78;

#if defined(VERSION_US)
static s16 D_us_80182344[] = {
    0x0000, 0x0019, 0x0000, 0x0004, 0x0008, 0xFFFC, 0xFFF0, 0x0000,
    0x0000, 0x0019, 0x000C, 0x0000, 0x0206, 0x0306, 0x0440, 0x00FF};
#else
static s16 D_us_80182344[] = {
    0x0000, 0x0019, 0x0000, 0x0004, 0x0008, 0xFFFC, 0xFFF0, 0x0000};
#endif

static AnimateEntityFrame D_us_80182364[] = {
    {0x04, 0x05}, {0x06, 0x01}, {0x04, 0x06}, {0xFF, 0x00}};
static AnimateEntityFrame D_us_8018236C[] = {
    {0x06, 0x07}, {0x08, 0x08}, {0x06, 0x09}, {0xFF, 0x00}};
static AnimateEntityFrame D_us_80182374[] = {
    {0x10, 0x01}, {0x02, 0x0A}, {0x02, 0x0B}, {0x14, 0x0A},
    {0x01, 0x12}, {0x01, 0x11}, {0x01, 0x10}, {0xFF, 0x00}};
static AnimateEntityFrame D_us_80182384[] = {
    {0x01, 0x0D}, {0x01, 0x0E}, {0x00, 0x00}, {0x00, 0x00}};
static AnimateEntityFrame D_us_8018238C[] = {
    {0x08, 0x01}, {0x16, 0x0C}, {0x01, 0x0E}, {0x01, 0x0D},
    {0x01, 0x0F}, {0x01, 0x11}, {0x01, 0x12}, {0xFF, 0x00}};
static AnimateEntityFrame D_us_8018239C[] = {
    {0x01, 0x15}, {0x01, 0x16}, {0x01, 0x17}, {0x01, 0x18}, {0x01, 0x19},
    {0x01, 0x1A}, {0x01, 0x1B}, {0x01, 0x1C}, {0x01, 0x00}, {0xFF, 0x00},
};
static AnimateEntityFrame D_us_801823B0[] = {
    {0x02, 0x1D}, {0x02, 0x1E}, {0x02, 0x1F}, {0x02, 0x20},
    {0x02, 0x21}, {0x02, 0x22}, {0x00, 0x00}, {0x00, 0x00}};
static s8 D_us_801823C0[][4] = {
    {0x00, 0x00, 0x00, 0x00}, {0x01, 0x07, 0x04, 0x12},
    {0x01, 0x03, 0x07, 0x0E}, {0x04, 0x00, 0x04, 0x18},
    {0x00, 0x05, 0x05, 0x14},
};
static u8 D_us_801823D4[] = {
    0x00, 0x01, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x00, 0x00, 0x00};

static bool StepTowards(s16* val, s32 target, s32 step) {
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

void func_us_801D5E90(Entity* self) {
    Collider collider;
    Primitive* prim;
    Entity* explosion;
    Entity* player;
    s8* frameParts;

    s32 primIndex;
    long genericInt;
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
        genericInt = (long)prim->next;
        if (!genericInt) {
            prim->x0 = 0;
            prim->y0 = 0;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        }
        prim = (Primitive*)genericInt;
    }
}

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
        InitializeEntity(D_us_80180B6C);
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

        self->velocityX = rsin(angle) * (-0x80);
        self->velocityY = rcos(angle) << 7;
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
        if (ent->entityId != E_UNK_40) {
            DestroyEntity(self);
        }
    }
}

void func_us_801D6B8C(Entity* self) {
    Entity* ent;
    s32 dx;
    s32 dy;
    s16 angle;
    s32 distance;
    s32 size;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B78);
        self->animCurFrame = 0;
        break;

    case 1:
        ent = self->ext.et_801D6B8C.unk9C;
        if (ent->pose == 4) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_us_8018239C, self);
        ent = self->ext.et_801D6B8C.unk9C;
        if (ent->ext.et_801D6B8C.unk90) {
            self->facingLeft = 0;
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = (self->scaleY = 0x180);
            self->ext.et_801D6B8C.unk80 = 0x60;
            self->zPriority = ent->zPriority - 1;
            SetStep(3);
        }
        break;

    case 3:
        AnimateEntity(D_us_801823B0, self);
        if (self->scaleX < 0x200) {
            self->scaleX = (self->scaleY += 0x20);
        } else if (!(self->ext.et_801D6B8C.unk80 -= 1)) {
            SetStep(4);
        }

    case 4:
        AnimateEntity(D_us_801823B0, self);
        if (self->scaleX) {
            self->scaleX = (self->scaleY -= 4);
        } else {
            ent = self->ext.et_801D6B8C.unk9C;
            ent->ext.et_801D6B8C.unk90 = 0;
            DestroyEntity(self);
            return;
        }
        ent = g_Entities;
        angle = GetAngleBetweenEntities(self, ent);
        size = (self->scaleX * 30) >> 8;
        dx = GetDistanceToPlayerX();
        dy = GetDistanceToPlayerX();
        distance = SquareRoot0(SQ(dx) + SQ(dy));
        distance -= 4;
        if (distance < size) {
            size = distance;
        }
        self->hitboxOffX = (size * rcos(angle)) >> 0xC;
        self->hitboxOffY = (size * rsin(angle)) >> 0xC;
    }

    if (g_Timer & 1) {
        self->palette = PAL_FLAG(PAL_CC_CRITICAL_EFFECT);
    } else {
        self->palette = PAL_FLAG(PAL_UNK_19C);
    }
    ent = self->ext.et_801D6B8C.unk9C;
    if (ent->entityId != 0x40) {
        DestroyEntity(self);
    }
    return;
}
