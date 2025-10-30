// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

extern EInit g_EInitLargeSlime;
static s16 large_slime_sensors[] = {0, 0, 0, 4, 8, -4, -16, 0};
static u16 D_us_801827EC[] = {8, 16, 12, 18, 32, 0};

extern EInit g_EInitSlime;
static s16 slime_sensors[] = {0, 0, 0, 4, 8, -4, -16, 0};
static u16 D_us_80182808[] = {8, 16, 12, 18, 32, 0};

void func_us_801D3468(s32 primCount);
void EntityLargeSlime(Entity* self) {
    Primitive* prim;
    s32 i;
    Entity* child;
    s16 xOffset;
    s16 angle;
    s16 yOffset;
    Primitive* prevPrim;
    s32 primIndex;
    s32 pad[9];

    if (!(g_Timer % 8)) {
        self->ext.slime.largeSlimePaletteCycle ^= 1;
    }

    if (self->ext.slime.largeSlimePaletteCycle) {
        self->ext.slime.palette = PAL_UNK_204;
    } else {
        self->ext.slime.palette = PAL_UNK_205;
    }

    if (self->flags & FLAG_DEAD && self->step < 7) {
        self->hitboxState = 0;
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
        SetStep(7);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLargeSlime);
        self->ext.slime.deathTimer = 0x20;
        self->ext.slime.unk8C = 0;
        self->unk60 = self + 1;
        self->unk5C = NULL;
        // fallthrough
    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.slime.prim = prim;
            self->ext.slime.unk80 = prim;
        } else {
            DestroyEntity(self);
            return;
        }

        for (prim = self->ext.slime.unk80, i = 0; i < 8; prim = prim->next,
            i++) {
            if (self->params & 0x10) {
                prim->tpage = 0x13;
                prim->clut = PAL_UNK_204;
                prim->u0 = i * 8;
                prim->u1 = (i * 8) + 7;
                prim->u2 = i * 8;
                prim->u3 = (i * 8) + 7;
                prim->v0 = 0;
                prim->v1 = 0;
                prim->v2 = 0x1F;
                prim->v3 = 0x1F;
            } else {
                prim->tpage = 0x13;
                prim->clut = PAL_CC_GREEN_EFFECT_A;
                prim->u0 = (i * 8) + 0x40;
                prim->u1 = (i * 8) + 0x47;
                prim->u2 = (i * 8) + 0x40;
                prim->u3 = (i * 8) + 0x47;
                prim->v0 = 0;
                prim->v1 = 0;
                prim->v2 = 0x1F;
                prim->v3 = 0x1F;
            }

            PGREY(prim, 0) = 0x40;
            PGREY(prim, 1) = 0x40;
            PGREY(prim, 2) = 0x80;
            PGREY(prim, 3) = 0x80;
            prim->x0 = self->posX.i.hi;
            prim->x1 = prim->x2 = prim->x3 = prim->x0;
            prim->y0 = self->posY.i.hi;
            prim->y1 = prim->y2 = prim->y3 = prim->y0;
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            prim->p3 = 8;
            prevPrim = prim;
        }
        self->ext.slime.unk84 = prevPrim;

        child = self + 1;
        CreateEntityFromEntity(E_UNK_4B, self, child);
        child->posX.i.hi += 0x40;
#ifdef VERSION_US
        // BUG: likely unintended and seems removed on PSP side
        child->posY.i.hi = child->posY.i.hi;
#endif
        child->ext.slime.deathTimer = 0x20;
        child->ext.slime.unk8C = 0;
        child->params = self->params;
        self->step++;
        // fallthrough
    case 2:
        self->ext.slime.unk9C = 1;
        self->ext.slime.facingLeft = self->params & 1;
        self->step++;
        // fallthrough
    case 3:
        switch (self->step_s) {
        case 0:
            if (UnkCollisionFunc3(large_slime_sensors) & 1) {
                if ((self + 1)->step == 3) {
                    self->ext.slime.unk9C = 0;
                    self->velocityX = 0;
                    self->velocityY = 0;
                    self->ext.slime.unk88 = 0x50;
                    self->ext.slime.unk8A = 0;
                    (self + 1)->ext.slime.unk8A = 0;
                    self->step_s = self->ext.slime.facingLeft;
                    self->step++;
                }
            } else {
                self->velocityY -= FIX(0.125);
            }
            break;
        case 1:
            break;
        }
        break;
    case 4:
        if (!(--self->ext.slime.unk88)) {
            self->ext.slime.unk8C = 0;
            (self + 1)->ext.slime.unk8C = 0;
            SetStep(5);
        } else {
            if (!(self->ext.slime.unk88 % 4)) {
                if (self->step_s) {
                    self->ext.slime.unk8C = -6;
                    (self + 1)->ext.slime.unk8C = -6;
                } else {
                    self->ext.slime.unk8C = 6;
                    (self + 1)->ext.slime.unk8C = 6;
                }
                self->step_s ^= 1;
            }
        }

        xOffset = (self + 1)->posX.i.hi - self->posX.i.hi;
        if (xOffset > 0x38) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        self->ext.slime.unk8A = UnkCollisionFunc4(self->ext.slime.unk8A);
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            (self + 1)->step_s = 1;
            self->ext.slime.unk88 = 0x20;
            self->ext.slime.unk89 = D_us_801827EC[Random() & 3];
            self->ext.slime.unk8B = self->ext.slime.facingLeft ^ 1;
            (self + 1)->ext.slime.unk8B = self->ext.slime.facingLeft;
            self->velocityX = FIX(-0.5);
            if (self->ext.slime.facingLeft) {
                self->velocityX = FIX(0.5);
            }
            (self + 1)->velocityX = self->velocityX;
            self->step_s++;
            break;
        case 1:
            if (self->ext.slime.unk8B) {
                self->ext.slime.unk8A =
                    UnkCollisionFunc4(self->ext.slime.unk8A);
            }

            if (!(--self->ext.slime.unk88)) {
                self->ext.slime.unk88 = 0x10;
                if (self->ext.slime.unk8B) {
                    (self + 1)->ext.slime.unk8B = 1;
                } else {
                    (self + 1)->ext.slime.unk8B = 0;
                }
                self->ext.slime.unk8B ^= 1;
                self->ext.slime.unk89--;
            }

            if (!self->ext.slime.unk89) {
                if (self->ext.slime.unk8A & 3 ||
                    (self + 1)->ext.slime.unk8A & 3) {
                    self->ext.slime.unk88 = 0x10;
                    if ((self + 1)->ext.slime.unk8A & 3) {
                        self->ext.slime.facingLeft = 0;
                        self->ext.slime.unk8B = self->ext.slime.facingLeft;
                        (self + 1)->ext.slime.unk8B =
                            self->ext.slime.facingLeft ^ 1;
                    } else {
                        self->ext.slime.facingLeft = 1;
                        self->ext.slime.unk8B = self->ext.slime.facingLeft ^ 1;
                        (self + 1)->ext.slime.unk8B =
                            self->ext.slime.facingLeft;
                    }
                    self->velocityX = -self->velocityX;
                    self->velocityY = -self->velocityY;
                    (self + 1)->velocityX = -(self + 1)->velocityX;
                    (self + 1)->velocityY = -(self + 1)->velocityY;
                    self->ext.slime.unk89 = D_us_801827EC[4];
                }

                if (!self->ext.slime.unk89) {
                    SetStep(6);
                }
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            self->ext.slime.facingLeft ^= 1;
            (self + 1)->step = 4;
            if (self->ext.slime.facingLeft) {
                self->ext.slime.unk88 = 0x10;
                (self + 1)->ext.slime.unk88 = 1;
            } else {
                self->ext.slime.unk88 = 1;
                (self + 1)->ext.slime.unk88 = 0x10;
            }
            self->step_s++;
            break;
        case 1:
            if (!(--self->ext.slime.unk88)) {
                self->ext.slime.unk9C = 1;
                if (self->ext.slime.facingLeft) {
                    self->velocityX = FIX(0.25);
                } else {
                    self->velocityX = FIX(-0.25);
                }
                self->velocityY = FIX(-4.0);
                SetStep(3);
            }
            break;
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            (self + 1)->step = 5;
            (self + 1)->step_s = 0;
            self->ext.slime.dying = 1;
            self->ext.slime.largeSlimeDying = 1;
            self->ext.slime.deathColorCycle = 0x80;
            self->step_s++;
            break;
        case 1:
            if (UnkCollisionFunc3(large_slime_sensors) & 1) {
                self->velocityX = FIX(-0.0625);
                self->step_s++;
            }
            break;
        case 2:
            if (!(g_Timer % 2)) {
                self->ext.slime.unk8C = -6;
                (self + 1)->ext.slime.unk8C = -6;
            } else {
                self->ext.slime.unk8C = 6;
                (self + 1)->ext.slime.unk8C = 6;
            }

            if (!(g_Timer % 6)) {
                self->ext.slime.deathTimer--;
            }

            self->ext.slime.unk8A = UnkCollisionFunc4(self->ext.slime.unk8A);
            if (!(g_Timer % 2)) {
                self->ext.slime.deathColorCycle--;
            }
            if (!self->ext.slime.deathTimer) {
                self->step_s++;
            }
            break;
        case 3:
            DestroyEntity(self + 1);
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (self->ext.slime.prim != NULL) {
        child = self + 1;
        xOffset = child->posX.i.hi - self->posX.i.hi;
        yOffset = child->posY.i.hi - self->posY.i.hi;
        angle = ratan2(-yOffset, xOffset) + 0x400;
        self->ext.slime.unk92 =
            (rcos(angle) * self->ext.slime.deathTimer) >> 0xC;
        self->ext.slime.unk90 =
            (rsin(angle) * self->ext.slime.deathTimer) >> 0xC;
        func_us_801D3468(8);
    }

    xOffset = ((self + 1)->posX.i.hi - self->posX.i.hi);
    yOffset = ((self + 1)->posY.i.hi - self->posY.i.hi);
    xOffset /= 4;
    yOffset /= 4;
    angle = ratan2(-yOffset, xOffset) + 0x100;
    self->hitboxOffX = (rcos(angle) * 0x1C) >> 0xC;
    self->hitboxOffY = (rsin(angle) * -0x10) >> 0xC;
    self->hitboxWidth = 0x14;
    self->hitboxHeight = 0xE;
}

u8 func_us_801D3A50(Primitive* prim);
void func_us_801D3C1C(Primitive* prim);
void func_us_801D3468(s32 primCount) {
    Primitive* prim;
    Primitive* nextPrim;
    Entity* ent;
    s32 var_s6;
    s32 var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 i;
    s32 pad[9];

    prim = g_CurrentEntity->ext.slime.unk80;
    prim->x0 = g_CurrentEntity->posX.i.hi + g_CurrentEntity->ext.slime.unk92 +
               g_CurrentEntity->ext.slime.unk8C;
    prim->x2 = g_CurrentEntity->posX.i.hi;
    prim->y0 = g_CurrentEntity->posY.i.hi - g_CurrentEntity->ext.slime.unk90;
    prim->y2 = g_CurrentEntity->posY.i.hi;

    ent = g_CurrentEntity + 1;
    prim = g_CurrentEntity->ext.slime.unk84;
    prim->clut = g_CurrentEntity->ext.slime.palette;
    prim->x1 = ent->posX.i.hi + ent->ext.slime.unk92 + ent->ext.slime.unk8C;
    prim->x3 = ent->posX.i.hi;
    prim->y1 = ent->posY.i.hi - ent->ext.slime.unk90;
    prim->y3 = ent->posY.i.hi;
    if (g_CurrentEntity->ext.slime.dying) {
        prim->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        prim->r0 = g_CurrentEntity->ext.slime.deathColorCycle;
        prim->g0 = prim->b0 = prim->r0;
        PGREY(prim, 1) = prim->r0;
        PGREY(prim, 2) = prim->r0;
        PGREY(prim, 3) = prim->r0;
        if (g_CurrentEntity->ext.slime.largeSlimeDying && !(Random() & 0x3F)) {
            ent = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (ent != NULL) {
                CreateEntityFromCurrentEntity(E_INTENSE_EXPLOSION, ent);
                ent->params = 0x10;
                ent->posX.i.hi = prim->x3;
                ent->posY.i.hi = prim->y3;
                ent->posY.i.hi -= Random() & 7;
            }
        }
    }

    for (prim = g_CurrentEntity->ext.slime.unk80, i = 0; i < primCount - 1;
         prim = nextPrim, i++) {
        nextPrim = prim->next;
        prim->clut = g_CurrentEntity->ext.slime.palette;
        if (g_CurrentEntity->ext.slime.dying) {
            prim->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim->r0 = g_CurrentEntity->ext.slime.deathColorCycle;
            prim->g0 = prim->b0 = prim->r0;
            PGREY(prim, 1) = prim->r0;
            PGREY(prim, 2) = prim->r0;
            PGREY(prim, 3) = prim->r0;
            if (g_CurrentEntity->ext.slime.largeSlimeDying &&
                !(Random() & 0x3F)) {
                ent = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (ent != NULL) {
                    CreateEntityFromCurrentEntity(E_INTENSE_EXPLOSION, ent);
                    ent->params = 0x10;
                    ent->posX.i.hi = prim->x3;
                    ent->posY.i.hi = prim->y3;
                    ent->posY.i.hi -= Random() & 7;
                }
            }
        }

        var_s4 = nextPrim->x1 + prim->x0;
        var_s4 /= 2;
        var_s3 = (nextPrim->y1 + prim->y0);
        var_s3 /= 2;
        var_s6 = prim->x1 - var_s4;
        var_s5 = prim->y1 - var_s3;
        var_s6 = (var_s6 / 8) + var_s4;
        var_s5 = (var_s5 / 8) + var_s3;
        nextPrim->x0 = prim->x1 = var_s6;
        nextPrim->y0 = prim->y1 = var_s5;

        var_s4 = nextPrim->x3 + prim->x2;
        var_s4 /= 2;
        var_s3 = nextPrim->y3 + prim->y2;
        var_s3 /= 2;
        var_s6 = prim->x3 - var_s4;
        var_s5 = prim->y3 - var_s3;
        var_s6 = (var_s6 / 8) + var_s4;
        var_s5 = (var_s5 / 8) + var_s3;
        prim->x3 = var_s6;
        prim->y3 = var_s5;

        if (func_us_801D3A50(prim)) {
            if (i < primCount / 2) {
                prim->p2 = g_CurrentEntity->ext.slime.unk8A & 3;
            } else {
                prim->p2 = (g_CurrentEntity + 1)->ext.slime.unk8A & 3;
            }
        }
        if (!g_CurrentEntity->ext.slime.unk9C) {
            switch (prim->p2) {
            case 0:
                prim->y3 += 3;
                break;
            case 1:
                prim->y3 -= 3;
                break;
            case 2:
                prim->x3 += 3;
                break;
            case 3:
                prim->x3 -= 3;
                break;
            }
            func_us_801D3C1C(prim);
        }
        nextPrim->x2 = prim->x3;
        nextPrim->y2 = prim->y3;
    }

    for (prim = g_CurrentEntity->ext.slime.unk80, i = 0; i < primCount - 1;
         prim = nextPrim, i++) {
        nextPrim = prim->next;
        switch (prim->p2) {
        case 0:
            prim->y3 += 2;
            break;
        case 1:
            prim->y3 -= 2;
            break;
        case 2:
            prim->x3 += 2;
            break;
        case 3:
            prim->x3 -= 2;
            break;
        }
        func_us_801D3C1C(prim);
        nextPrim->x2 = prim->x3;
        nextPrim->y2 = prim->y3;
    }
}

u8 func_us_801D3A50(Primitive* prim) {
    TileCollision tileCollision;
    Collider collider;

    s16 x;
    s16 y;
    s16 var_s1;
    u8 var_s0;

    x = prim->x3;
    y = prim->y3;
    g_api.CheckCollision(x, y, &collider, 0);
    if (collider.effects & (EFFECT_UNK_0002 | EFFECT_SOLID)) {
#ifdef VERSION_PSP
        tileCollision.top = -collider.unk18 * 0x10;
        tileCollision.bottom = (collider.unk20 * 0x10) + 1;
        tileCollision.left = (-collider.unk14 * 0x10) + 2;
        tileCollision.right = (collider.unk1C * 0x10) + 3;
#else
        tileCollision.top = -LOHU(collider.unk18) * 0x10;
        tileCollision.bottom = (LOHU(collider.unk20) * 0x10) + 1;
        tileCollision.left = (-LOHU(collider.unk14) * 0x10) + 2;
        tileCollision.right = (LOHU(collider.unk1C) * 0x10) + 3;
#endif
        if (tileCollision.top < tileCollision.bottom) {
            var_s0 = 0;
        } else {
            var_s0 = 1;
        }
        if (tileCollision.left < (&tileCollision.top)[var_s0]) {
            var_s0 = 2;
        }
        if (tileCollision.right < (&tileCollision.top)[var_s0]) {
            var_s0 = 3;
        }
        var_s1 = (&tileCollision.top)[var_s0] & 0xF;
        if (!((var_s1 & 2) ^ (g_CurrentEntity->ext.slime.unk8A & 2))) {
            var_s1 = (var_s1 & 2) + (g_CurrentEntity->ext.slime.unk8A & 1);
        }
        prim->p2 = var_s1;
        switch (var_s1) {
        case 0:
            prim->y3 += collider.unk18;
            break;
        case 1:
            prim->y3 += collider.unk20;
            break;
        case 2:
            prim->x3 += collider.unk14;
            break;
        case 3:
            prim->x3 += collider.unk1C;
            break;
        }

        return 0;
    }

    return 1;
}

void func_us_801D3C1C(Primitive* prim) {
    Collider collider;
    u8 p2;
    s16 x;
    s16 y;

    p2 = prim->p2;
    x = prim->x3;
    y = prim->y3;
    g_api.CheckCollision(x, y, &collider, 0);
    if (collider.effects & (EFFECT_UNK_0002 | EFFECT_SOLID)) {
        switch (p2) {
        case 0:
            prim->y3 += collider.unk18;
            break;
        case 1:
            prim->y3 += collider.unk20;
            break;
        case 2:
            prim->x3 += collider.unk14;
            break;
        case 3:
            prim->x3 += collider.unk1C;
            break;
        }
    }
}

void func_us_801D3D08(Entity* self) {
    Entity* child;
    s16 xOffset;
    s16 angle;
    s16 hasPalette;
    s16 yOffset;
    Primitive* prim;

    prim = (self - 1)->ext.slime.prim;
    if (self->palette) {
        while (prim != NULL) {
            prim->clut = (self - 1)->palette & 0x7FFF;
            prim = prim->next;
        }
    } else {
        hasPalette = false;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLargeSlime);
        self->hitPoints = 0x7FFF;
        self->unk5C = self - 1;
        self->unk60 = self - 1;
        // fallthrough
    case 1:
    case 2:
        if (UnkCollisionFunc3(large_slime_sensors) & 1) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.slime.unk8B = 0;
            SetStep(3);
        } else {
            self->velocityY -= FIX(0.125);
        }
        break;
    case 3:
        if (self->step_s && self->ext.slime.unk8B) {
            self->ext.slime.unk8A = UnkCollisionFunc4(self->ext.slime.unk8A);
        }
        break;
    case 4:
        if (!(--self->ext.slime.unk88)) {
            (self - 1)->ext.slime.unk9C = 1;
            self->ext.slime.facingLeft = (self - 1)->ext.slime.facingLeft;
            if (self->ext.slime.facingLeft) {
                self->velocityX = FIX(0.25);
            } else {
                self->velocityX = FIX(-0.25);
            }
            self->velocityY = FIX(-4.0);
            self->step = 2;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->step_s++;
            break;
        case 1:
            if (UnkCollisionFunc3(large_slime_sensors) & 1) {
                self->velocityX = FIX(0.0625);
                self->step_s++;
            }
            break;
        case 2:
            if (!(g_Timer % 6)) {
                self->ext.slime.deathTimer--;
            }
            self->ext.slime.unk8A = UnkCollisionFunc4(self->ext.slime.unk8A);
            if (!self->ext.slime.deathTimer) {
                self->step_s++;
            }
            break;
        }
        break;
    }

    child = self - 1;
    xOffset = child->posX.i.hi - self->posX.i.hi;
    yOffset = child->posY.i.hi - self->posY.i.hi;
    angle = ratan2(yOffset, -xOffset) + 0x400;
    self->ext.slime.unk92 = (rcos(angle) * self->ext.slime.deathTimer) >> 0xC;
    self->ext.slime.unk90 = (rsin(angle) * self->ext.slime.deathTimer) >> 0xC;

    // Why does this not just reuse the child variable!
    xOffset = ((self - 1)->posX.i.hi - self->posX.i.hi);
    yOffset = ((self - 1)->posY.i.hi - self->posY.i.hi);
    xOffset /= 4;
    yOffset /= 4;
    angle = ratan2(-yOffset, xOffset) - 0x100;
    self->hitboxOffX = (rcos(angle) * 0x1C) >> 0xC;
    self->hitboxOffY = (rsin(angle) * -0x10) >> 0xC;
    self->hitboxWidth = 0x14;
    self->hitboxHeight = 0xE;
}

void EntitySlime(Entity* self) {
    Primitive* prim;
    s32 i;
    Entity* child;
    s16 angle;
    Primitive* prevPrim;
    s32 primIndex;
    s16 xOffset;
    s16 yOffset;
    s32 pad[9];

    if (self->flags & FLAG_DEAD && self->step < 6) {
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_B);
        self->hitboxState = 0;
        SetStep(6);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSlime);
        self->ext.slime.deathTimer = 0x10;
        self->ext.slime.unk8C = 0;
        // fallthrough
    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.slime.prim = prim;
            self->ext.slime.unk80 = prim;
        } else {
            DestroyEntity(self);
            return;
        }

        for (prim = self->ext.slime.unk80, i = 0; i < 4; prim = prim->next,
            i++) {
            prim->tpage = 0x13;
            prim->clut = PAL_CC_GREEN_EFFECT_A;
            prim->u0 = (i * 0x10) + 0x40;
            prim->u1 = (i * 0x10) + 0x4F;
            prim->u2 = (i * 0x10) + 0x40;
            prim->u3 = (i * 0x10) + 0x4F;
            prim->v0 = 0;
            prim->v1 = 0;
            prim->v2 = 0x1F;
            prim->v3 = 0x1F;
            PGREY(prim, 0) = 0x40;
            PGREY(prim, 1) = 0x40;
            PGREY(prim, 2) = 0x80;
            PGREY(prim, 3) = 0x80;
            prim->x0 = self->posX.i.hi;
            prim->x1 = prim->x2 = prim->x3 = prim->x0;
            prim->y0 = self->posY.i.hi;
            prim->y1 = prim->y2 = prim->y3 = prim->y0;
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim->p3 = 8;
            prevPrim = prim;
        }

        child = self + 1;
        CreateEntityFromEntity(E_UNK_4D, self, child);
        child->posX.i.hi += 0x18;
#ifdef VERSION_US
        // BUG: likely unintended and seems removed on PSP side
        child->posY.i.hi = child->posY.i.hi;
#endif
        child->ext.slime.deathTimer = 0x10;
        child->ext.slime.unk8C = 0;
        child->params = self->params;
        self->ext.slime.unk84 = prevPrim;
        self->step++;
    case 2:
        self->ext.slime.facingLeft = self->params & 1;
        self->step++;
    case 3:
        if (UnkCollisionFunc3(slime_sensors) & 1) {
            if ((self + 1)->step == 3) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->ext.slime.unk88 = 0x20;
                self->ext.slime.unk8A = 0;
                (self + 1)->ext.slime.unk8A = 0;
                self->step_s = self->ext.slime.facingLeft;
                self->step++;
            }
        } else {
            self->velocityY -= FIX(0.125);
        }
        break;
    case 4:
        if (!--self->ext.slime.unk88) {
            self->ext.slime.unk8C = 0;
            (self + 1)->ext.slime.unk8C = 0;
            SetStep(5);
        } else if (!(self->ext.slime.unk88 % 4)) {
            if (self->step_s) {
                self->ext.slime.unk8C = -4;
                (self + 1)->ext.slime.unk8C = -4;
            } else {
                self->ext.slime.unk8C = 4;
                (self + 1)->ext.slime.unk8C = 4;
            }
            self->step_s ^= 1;
        }

        xOffset = (self + 1)->posX.i.hi - self->posX.i.hi;
        if (xOffset > 0x18) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        self->ext.slime.unk8A = UnkCollisionFunc4(self->ext.slime.unk8A);
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            (self + 1)->step_s = 1;
            self->ext.slime.unk88 = 0x10;
            self->ext.slime.unk89 = D_us_80182808[Random() & 3];
            self->ext.slime.unk8B = self->ext.slime.facingLeft ^ 1;
            (self + 1)->ext.slime.unk8B = self->ext.slime.facingLeft;
            self->velocityX = FIX(-0.5);
            if (self->ext.slime.facingLeft) {
                self->velocityX = FIX(0.5);
            }
            (self + 1)->velocityX = self->velocityX;
            self->step_s++;
            break;
        case 1:
            if (self->ext.slime.unk8B) {
                self->ext.slime.unk8A =
                    UnkCollisionFunc4(self->ext.slime.unk8A);
            }

            if (!--self->ext.slime.unk88) {
                self->ext.slime.unk88 = 0x10;
                if (self->ext.slime.unk8B) {
                    (self + 1)->ext.slime.unk8B = 1;
                } else {
                    (self + 1)->ext.slime.unk8B = 0;
                }
                self->ext.slime.unk8B ^= 1;
                self->ext.slime.unk89--;
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            (self + 1)->step = 4;
            (self + 1)->step_s = 0;
            self->velocityX = self->velocityX / 4;
            self->velocityY = self->velocityY / 4;
            if (self->ext.slime.facingLeft) {
                self->velocityX = -self->velocityX;
                self->velocityY = -self->velocityY;
            }
            self->ext.slime.dying = 1;
            self->ext.slime.largeSlimeDying = 0;
            self->ext.slime.deathColorCycle = 0x80;
            self->step_s++;
            break;
        case 1:
            if (!(g_Timer % 2)) {
                self->ext.slime.unk8C = -3;
                (self + 1)->ext.slime.unk8C = -3;
            } else {
                self->ext.slime.unk8C = 3;
                (self + 1)->ext.slime.unk8C = 3;
            }

            if (!(g_Timer % 6)) {
                self->ext.slime.deathTimer--;
            }
            self->ext.slime.unk8A = UnkCollisionFunc4(self->ext.slime.unk8A);
            self->ext.slime.deathColorCycle--;
            if (!self->ext.slime.deathTimer) {
                self->step_s++;
            }
            break;
        case 2:
            DestroyEntity(self + 1);
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (self->ext.slime.prim != NULL) {
        child = self + 1;
        xOffset = child->posX.i.hi - self->posX.i.hi;
        yOffset = child->posY.i.hi - self->posY.i.hi;
        angle = ratan2(-yOffset, xOffset) + 0x400;
        self->ext.slime.unk92 =
            (rcos(angle) * self->ext.slime.deathTimer) >> 0xC;
        self->ext.slime.unk90 =
            (rsin(angle) * self->ext.slime.deathTimer) >> 0xC;
        angle -= 0x300;
        self->hitboxOffX = (rcos(angle) * 0x14) >> 0xC;
        self->hitboxOffY = (-rsin(angle) * 0x14) >> 0xC;
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        func_us_801D3468(4);
    }
}

void func_us_801D4744(Entity* self) {
    Primitive* prim;
    Entity* parent;
    s16 angle;
    s16 xOffset;
    s16 yOffset;
    s32 hasPalette;

    prim = (self - 1)->ext.slime.prim;
    if ((self - 1)->palette) {
        while (prim != NULL) {
            prim->clut = (self - 1)->palette & 0x7FFF;
            prim = prim->next;
        }
    } else {
        hasPalette = false;
        while (prim != NULL) {
            prim->clut = PAL_CC_GREEN_EFFECT_A;
            prim = prim->next;
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSlime);
        self->hitboxState = 0;
        // fallthrough
    case 1:
    case 2:
        if (UnkCollisionFunc3(slime_sensors) & 1) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.slime.unk8B = 0;
            SetStep(3);
        } else {
            self->velocityY -= FIX(0.125);
        }
        break;
    case 3:
        if (self->step_s && self->ext.slime.unk8B) {
            self->ext.slime.unk8A = UnkCollisionFunc4(self->ext.slime.unk8A);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->step_s++;
            self->velocityX = -self->velocityX / 4;
            self->velocityY = -self->velocityY / 4;
            if ((self - 1)->ext.slime.facingLeft) {
                self->velocityX = -self->velocityX;
                self->velocityY = -self->velocityY;
            }
            break;
        case 1:
            if (!(g_Timer % 6)) {
                self->ext.slime.deathTimer--;
            }
            self->ext.slime.unk8A = UnkCollisionFunc4(self->ext.slime.unk8A);
            if (!self->ext.slime.deathTimer) {
                self->step_s++;
            }
            break;
        }
        break;
    }

    parent = self - 1;
    xOffset = parent->posX.i.hi - self->posX.i.hi;
    yOffset = parent->posY.i.hi - self->posY.i.hi;

    angle = ratan2(yOffset, -xOffset) + 0x400;
    self->ext.slime.unk92 = (rcos(angle) * self->ext.slime.deathTimer) >> 0xC;
    self->ext.slime.unk90 = (rsin(angle) * self->ext.slime.deathTimer) >> 0xC;
}
