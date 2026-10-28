// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

// The panther's "liquid" animations are complicated and use many primitives.
// The panther holds 6 different prims in its ext!
// Comprehending this is going to be difficult - good luck!

void func_us_801C4B2C() {
    s32 i;
    s32 xVar2;
    s32 yVar2;
    s32 xVar1;
    s32 yVar1;
    Primitive* prim2;
    Primitive* prim;

    prim = g_CurrentEntity->ext.blackPanther.prim7C;
    for (i = 0; i < 7; i++) {
        prim2 = prim->next;
        xVar1 = prim2->x2 + prim->x0;
        xVar1 /= 2;
        yVar1 = prim2->y2 + prim->y0;
        yVar1 /= 2;
        xVar2 = prim->x2 - xVar1;
        yVar2 = prim->y2 - yVar1;

        xVar2 = xVar2 / 8 + xVar1;
        yVar2 = yVar2 / 8 + yVar1;
        prim2->x0 = prim->x2 = xVar2;
        prim2->y0 = prim->y2 = yVar2;

        xVar1 = prim2->x3 + prim->x1;
        xVar1 /= 2;
        yVar1 = prim2->y3 + prim->y1;
        yVar1 /= 2;
        xVar2 = prim->x3 - xVar1;
        yVar2 = prim->y3 - yVar1;

        xVar2 = xVar2 / 8 + xVar1;
        yVar2 = yVar2 / 8 + yVar1;
        prim2->x1 = prim->x3 = xVar2;
        prim2->y1 = prim->y3 = yVar2;
        prim = prim2;
    }
}

static void func_us_801C4C4C(void) {
    Primitive* prim2;
    Primitive* prim;
    s32 primIndex;
    s32 i;

    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->hitboxState = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 20);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.blackPanther.prim7C = prim;
        } else {
            DestroyEntity(g_CurrentEntity);
            return;
        }
        for (i = 0; i < 8; i++) {
            prim->tpage = 0x12;
            prim->clut = 0x164;
            if (g_CurrentEntity->facingLeft) {
                prim->u0 = 64;
                prim->u1 = 0;
                prim->u2 = 64;
                prim->u3 = 0;
            } else {
                prim->u0 = 0;
                prim->u1 = 64;
                prim->u2 = 0;
                prim->u3 = 64;
            }
            prim->v0 = ((i * 2) + 181);
            prim->v1 = ((i * 2) + 181);
            prim->v2 = ((i * 2) + 184);
            prim->v3 = ((i * 2) + 184);
            PGREY(prim, 0) = 0x80;
            PGREY(prim, 1) = 0x80;
            PGREY(prim, 2) = 0x80;
            PGREY(prim, 3) = 0x80;
            if (g_CurrentEntity->facingLeft) {
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x30;
            } else {
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x10;
            }
            prim->x1 = prim->x0 + 64;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->y0 = g_CurrentEntity->posY.i.hi - 7 + (i * 2) - 3;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 4;
            prim->y3 = prim->y2;
            prim->priority = (g_CurrentEntity->zPriority + 2);
            prim->drawMode = DRAW_UNK02;
            prim2 = prim;
            prim = prim->next;
        }
        g_CurrentEntity->ext.blackPanther.prim80 = prim2;
        prim->tpage = 0x12;
        prim->clut = 0x164;
        prim->u0 = 0;
        prim->u1 = 64;
        prim->u2 = 0;
        prim->u3 = 64;
        prim->v0 = 0xEE;
        prim->v1 = 0xEE;
        prim->v2 = 0xEF;
        prim->v3 = 0xEF;
        PGREY(prim, 0) = 0x80;
        PGREY(prim, 1) = 0x80;
        PGREY(prim, 2) = 0x80;
        PGREY(prim, 3) = 0x80;
        if (g_CurrentEntity->facingLeft) {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x30;
        } else {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x10;
        }
        prim->x1 = prim->x0 + 64;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->y0 = g_CurrentEntity->posY.i.hi + 8;
        prim->y1 = prim->y0;
        prim->y2 = prim->y0;
        prim->y3 = prim->y2;
        prim->priority = ((g_CurrentEntity->zPriority) + 3);
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        g_CurrentEntity->ext.blackPanther.prim88 = prim;
        prim = prim->next;
        prim->tpage = 0x12;
        prim->clut = 0x164;
        prim->u0 = 64;
        prim->u1 = 0x7F;
        prim->u2 = 64;
        prim->u3 = 0x7F;
        prim->v0 = 0xC8;
        prim->v1 = 0xC8;
        prim->v2 = 0xC9;
        prim->v3 = 0xC9;
        PGREY(prim, 0) = 0x80;
        PGREY(prim, 1) = 0x80;
        PGREY(prim, 2) = 0x80;
        PGREY(prim, 3) = 0x80;
        if (g_CurrentEntity->facingLeft) {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x30;
        } else {
            prim->x0 = g_CurrentEntity->posX.i.hi - 0x10;
        }
        prim->x1 = prim->x0 + 64;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->y0 = g_CurrentEntity->posY.i.hi + 8;
        prim->y1 = prim->y0;
        prim->y2 = prim->y0;
        prim->y3 = prim->y2;
        prim->priority = ((g_CurrentEntity->zPriority) + 2);
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        g_CurrentEntity->ext.blackPanther.prim8C = prim;
        prim = prim->next;
        UnkPolyFunc2(prim);
        prim->tpage = 0x12;
        prim->clut = 0x164;
        prim->u0 = 0x5C;
        prim->u1 = 0x64;
        prim->u2 = 0x5C;
        prim->u3 = 0x64;
        prim->v0 = 0xC0;
        prim->v1 = 0xC0;
        prim->v2 = 0xC8;
        prim->v3 = 0xC8;
        if (g_CurrentEntity->facingLeft) {
            prim->next->x1 = g_CurrentEntity->posX.i.hi - 0x12;
        } else {
            prim->next->x1 = g_CurrentEntity->posX.i.hi + 0x12;
        }
        prim->next->y0 = g_CurrentEntity->posY.i.hi - 0x28;
        LOW(prim->next->u0) = 0;
        LOW(prim->next->r1) = 0;
        LOH(prim->next->r2) = 8;
        LOH(prim->next->b2) = 8;
        prim->next->b3 = 0x80;
        prim->priority = ((g_CurrentEntity->zPriority) + 2);
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        g_CurrentEntity->ext.blackPanther.prim90 = prim;
        prim = prim->next;
        prim = prim->next;
        UnkPolyFunc2(prim);
        prim->tpage = 0x12;
        prim->clut = 0x164;
        if (g_CurrentEntity->facingLeft) {
            prim->u0 = 0x3C;
            prim->u1 = 0;
            prim->u2 = 0x3C;
            prim->u3 = 0;
        } else {
            prim->u0 = 0;
            prim->u1 = 0x3C;
            prim->u2 = 0;
            prim->u3 = 0x3C;
        }
        prim->v0 = 0xD0;
        prim->v1 = 0xD0;
        prim->v2 = 0xDD;
        prim->v3 = 0xDD;
        if (g_CurrentEntity->facingLeft) {
            prim->next->x1 = g_CurrentEntity->posX.i.hi - 0x12;
        } else {
            prim->next->x1 = g_CurrentEntity->posX.i.hi + 0x12;
        }
        prim->next->y0 = g_CurrentEntity->posY.i.hi + 2;
        LOW(prim->next->u0) = 0;
        LOW(prim->next->r1) = 0;
        LOH(prim->next->r2) = 2;
        LOH(prim->next->b2) = 1;
        prim->next->b3 = 0x80;
        prim->priority = ((g_CurrentEntity->zPriority) + 2);
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        g_CurrentEntity->ext.blackPanther.prim9C = prim;
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
        g_CurrentEntity->step_s++;
        g_CurrentEntity->ext.blackPanther.unk84 = 0x10;
        g_CurrentEntity->animCurFrame = 0;
        break;
    case 1:
        if (!--g_CurrentEntity->ext.blackPanther.unk84) {
            g_CurrentEntity->ext.blackPanther.unk94 = 0;
            g_CurrentEntity->ext.blackPanther.unk95 = 0;
            g_CurrentEntity->ext.blackPanther.unk96 = 0;
            g_CurrentEntity->ext.blackPanther.unk97 = 0;
            g_CurrentEntity->ext.blackPanther.unk98 = 0;
            g_CurrentEntity->ext.blackPanther.unk99 = 0x24;
            g_CurrentEntity->ext.blackPanther.unk9A = 0x30;
            g_CurrentEntity->ext.blackPanther.unk9B = 0;
            g_CurrentEntity->step_s++;
        }
        break;
    case 2:
        g_CurrentEntity->ext.blackPanther.unk84++;
        switch (g_CurrentEntity->ext.blackPanther.unk94) {
        case 0:
            func_us_801C4B2C();
            prim = g_CurrentEntity->ext.blackPanther.prim7C;
            prim->y0 -= 3;
            prim->y1 -= 3;
            if ((g_CurrentEntity->ext.blackPanther.unk84 % 2) != 0) {
                prim->x0++;
                prim->x1--;
            }
            if ((prim->x1 - prim->x0) < 0x20) {
                g_CurrentEntity->ext.blackPanther.unk84 = 0xC;
                g_CurrentEntity->ext.blackPanther.unk94++;
            }
            prim = prim->next;
            for (i = 0; i < 6; i++) {
                prim->x2 += 2;
                prim->x3 -= 2;
                prim = prim->next;
            }
            break;
        case 1:
            func_us_801C4B2C();
            prim = g_CurrentEntity->ext.blackPanther.prim7C;
            prim->y0 += 6;
            prim->y1 += 6;
            prim = prim->next;
            for (i = 0; i < 6; i++) {
                prim->x2++;
                prim->x3 -= 1;
                prim = prim->next;
            }
            if (g_CurrentEntity->ext.blackPanther.unk84 % 2) {
                prim = g_CurrentEntity->ext.blackPanther.prim80;
                prim->x2++;
                prim->x3 -= 2;
            }
            prim = g_CurrentEntity->ext.blackPanther.prim7C;
            if (prim->y0 > (g_CurrentEntity->posY.i.hi + 8)) {
                for (i = 0; i < 8; i++) {
                    prim->drawMode |= DRAW_HIDE;
                    prim = prim->next;
                }
            }
            break;
        }
        switch (g_CurrentEntity->ext.blackPanther.unk95) {
        case 0:
            if (!--g_CurrentEntity->ext.blackPanther.unk99) {
                prim = g_CurrentEntity->ext.blackPanther.prim88;
                prim->drawMode &= ~DRAW_HIDE;
                g_CurrentEntity->ext.blackPanther.unk99 = 0xF;
                g_CurrentEntity->ext.blackPanther.unk95++;
            }
            break;
        case 1:
            prim = g_CurrentEntity->ext.blackPanther.prim88;
            prim->v2++;
            prim->v3 = prim->v2;
            prim->y0 -= 2;
            prim->y1 = prim->y0;
            if (g_CurrentEntity->ext.blackPanther.unk84 % 4 == 0) {
                prim->x0--;
                prim->x1++;
            }
            if (!--g_CurrentEntity->ext.blackPanther.unk99) {
                g_CurrentEntity->ext.blackPanther.unk95++;
            }
            break;
        case 2:
            prim = g_CurrentEntity->ext.blackPanther.prim88;
            if ((g_CurrentEntity->ext.blackPanther.unk84 % 3) == 0) {
                prim->v2--;
                prim->v3 = prim->v2;
            }
            prim->y0++;
            prim->y1 = prim->y0;
            if (prim->y0 > prim->y2) {
                prim->drawMode |= DRAW_HIDE;
                g_CurrentEntity->ext.blackPanther.unk95 = 8;
            }
            break;
        }
        switch (g_CurrentEntity->ext.blackPanther.unk96) {
        case 0:
            if (!--g_CurrentEntity->ext.blackPanther.unk9A) {
                prim = g_CurrentEntity->ext.blackPanther.prim8C;
                prim->drawMode &= ~DRAW_HIDE;
                g_CurrentEntity->ext.blackPanther.unk96++;
                return;
            }
            break;
        case 1:
            prim = g_CurrentEntity->ext.blackPanther.prim8C;
            prim->v2 += 4;
            prim->v3 = prim->v2;
            prim->y0 -= 4;
            prim->y1 = prim->y0;
            if (prim->v2 > 0xF8) {
                prim = g_CurrentEntity->ext.blackPanther.prim90;
                prim->drawMode &= ~DRAW_HIDE;
                LOW(prim->next->r1) = 0xFFFF0000;
                prim = g_CurrentEntity->ext.blackPanther.prim9C;
                prim->drawMode &= ~DRAW_HIDE;
                g_CurrentEntity->ext.blackPanther.unk96++;
                return;
            }
            break;
        case 2:
            prim = g_CurrentEntity->ext.blackPanther.prim8C;
            prim->y0++;
            prim->y1 = prim->y0;
            if (prim->y0 == prim->y3) {
                g_CurrentEntity->ext.blackPanther.unk84 = 1;
                g_CurrentEntity->ext.blackPanther.unk9B = 0;
                prim->drawMode |= DRAW_HIDE;
                g_CurrentEntity->step_s++;
            }
            prim = g_CurrentEntity->ext.blackPanther.prim90;
            UnkPrimHelper(prim);
            LOW(prim->next->r1) += 0x1000;
            prim = g_CurrentEntity->ext.blackPanther.prim9C;
            UnkPrimHelper(prim);
            if (LOH((prim->next)->b2) < 0xD) {
                LOH((prim->next)->b2)++;
            }
            if (LOH((prim->next)->r2) < 0x3C) {
                LOH((prim->next)->r2) += 2;
            }
            break;
        }
        break;
    case 3:
        g_CurrentEntity->ext.blackPanther.unk84++;
        prim = g_CurrentEntity->ext.blackPanther.prim9C;
        UnkPrimHelper(prim);
        if (g_CurrentEntity->ext.blackPanther.unk84 % 4 == 0) {
            g_CurrentEntity->ext.blackPanther.unk9B ^= 1;
        }
        if (LOH((prim->next)->b2) < 0xD) {
            LOH((prim->next)->b2)++;
        }
        if (LOH((prim->next)->r2) < 0x3C) {
            LOH((prim->next)->r2)++;
        }
        prim = g_CurrentEntity->ext.blackPanther.prim90;
        UnkPrimHelper(prim);
        LOW(prim->next->r1) += 0x1000;
        if (prim->next->y0 > (g_CurrentEntity->posY.i.hi + 6)) {
            prim->drawMode |= DRAW_HIDE;
            g_CurrentEntity->step_s++;
        }
        break;
    case 4:
        break;
    }
}

static void func_us_801C5AA0(void) {
    u8 wasFacingLeft;
    s32 primIndex;
    Primitive* prim2;
    Primitive* prim;
    s32 i;

    switch (g_CurrentEntity->step_s) {
    case 0:
        wasFacingLeft = g_CurrentEntity->facingLeft;
        g_CurrentEntity->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        if (wasFacingLeft ^ g_CurrentEntity->facingLeft) {
            if (g_CurrentEntity->facingLeft) {
                g_CurrentEntity->posX.i.hi += 0x18;
            } else {
                g_CurrentEntity->posX.i.hi -= 0x18;
            }
        }
        prim = g_CurrentEntity->ext.blackPanther.prim7C;
        for (i = 0; i < 8; i++) {
            prim->tpage = 0x12;
            prim->clut = 0x164;
            if (g_CurrentEntity->facingLeft) {
                prim->u0 = 64;
                prim->u1 = 0;
                prim->u2 = 64;
                prim->u3 = 0;
            } else {
                prim->u0 = 0;
                prim->u1 = 64;
                prim->u2 = 0;
                prim->u3 = 64;
            }
            prim->v0 = ((i * 2) + 181);
            prim->v1 = ((i * 2) + 181);
            prim->v2 = ((i * 2) + 182);
            prim->v3 = ((i * 2) + 182);
            PGREY(prim, 0) = 0x80;
            PGREY(prim, 1) = 0x80;
            PGREY(prim, 2) = 0x80;
            PGREY(prim, 3) = 0x80;
            if (g_CurrentEntity->facingLeft) {
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x30;
            } else {
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x10;
            }
            prim->x1 = prim->x0 + 64;
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->y0 = g_CurrentEntity->posY.i.hi + 8;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0;
            prim->y3 = prim->y2;
            prim->priority = ((g_CurrentEntity->zPriority) + 2);
            prim->drawMode = DRAW_UNK02;
            prim2 = prim;
            prim = prim->next;
        }
        func_us_801C4B2C();
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
        g_CurrentEntity->step_s++;
        g_CurrentEntity->ext.blackPanther.unk99 = 8;
        break;
    case 1:
        prim = g_CurrentEntity->ext.blackPanther.prim9C;
        prim->y0 -= 2;
        prim->y1 -= 2;
        if (!--g_CurrentEntity->ext.blackPanther.unk99) {
            g_CurrentEntity->ext.blackPanther.unk99 = 0x10;
            g_CurrentEntity->step_s++;
        }
        break;
    case 2:
        prim = g_CurrentEntity->ext.blackPanther.prim9C;
        prim->y0--;
        prim->y1--;
        prim = g_CurrentEntity->ext.blackPanther.prim7C;
        prim->y0 -= 4;
        prim->y1 -= 4;
        func_us_801C4B2C();
        if (!--g_CurrentEntity->ext.blackPanther.unk99) {
            g_CurrentEntity->ext.blackPanther.unk99 = 0xF;
            g_CurrentEntity->step_s++;
        }
        break;
    case 3:
        prim = g_CurrentEntity->ext.blackPanther.prim9C;
        prim->y0 += 2;
        prim->y1 += 2;
        if (prim->y0 > g_CurrentEntity->posY.i.hi) {
            prim->drawMode |= DRAW_HIDE;
        }
        prim = g_CurrentEntity->ext.blackPanther.prim7C;
        prim->y0 -= 2;
        prim->y1 -= 2;
        func_us_801C4B2C();
        if (!--g_CurrentEntity->ext.blackPanther.unk99) {
            g_CurrentEntity->ext.blackPanther.unk99 = 0xF;
            g_CurrentEntity->step_s++;
        }
        break;
    case 4:
        prim = g_CurrentEntity->ext.blackPanther.prim9C;
        prim->y0 += 2;
        prim->y1 += 2;
        if (prim->y0 > g_CurrentEntity->posY.i.hi) {
            prim->drawMode |= DRAW_HIDE;
        }
        prim = g_CurrentEntity->ext.blackPanther.prim7C;
        prim->y0 += 2;
        prim->y1 += 2;
        func_us_801C4B2C();
        if (prim->y0 > g_CurrentEntity->posY.i.hi - 6) {
            g_CurrentEntity->step_s++;
        }
        break;
    case 5:
        g_CurrentEntity->animCurFrame = 1;
        g_CurrentEntity->hitEffect = g_CurrentEntity->palette;
        g_CurrentEntity->palette = PAL_FLAG(PAL_CC_DARK_EFFECT);
        g_CurrentEntity->ext.blackPanther.unk98 = 0x18;
        primIndex = g_CurrentEntity->primIndex;
        g_api.FreePrimitives(primIndex);
        g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
        g_CurrentEntity->step_s++;
        break;
    case 6:
        if (!--g_CurrentEntity->ext.blackPanther.unk98) {
            g_CurrentEntity->palette = g_CurrentEntity->hitEffect;
            g_CurrentEntity->hitboxState = 3;
            g_CurrentEntity->step_s++;
        }
        break;
    case 7:
        break;
    }
}

static s16 sensors1[] = {-64, 0, -64, 16, 255, 0};
static s16 sensors2[] = {0, 8, 0, 4, 8, -4, -16, 0};
static s16 sensors3[] = {0, 8, 16, 0};
static AnimateEntityFrame anim_running[] = {
    {6, 2}, {3, 3}, {5, 4}, {3, 3},  {3, 6},
    {3, 7}, {2, 8}, {2, 9}, {2, 10}, POSE_LOOP(0)};
static AnimateEntityFrame anim_twitchy_run[] = {
    {3, 2}, {2, 3}, {3, 4}, {4, 5}, {2, 3}, POSE_END};

extern EInit g_EInitBlackPanther;

void EntityBlackPanther(Entity* self) {
    Collider sp2C;
    s32 playerSide;
    Entity* player;
    s16 yVar;
    Entity* other;
    s16 xVar;
    Primitive* prim;

    if ((self->flags & FLAG_DEAD) && (self->step < 16)) {
        self->hitboxState = 0;
        SetStep(16);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBlackPanther);
        self->hitboxOffX = 2;
        self->hitboxOffY = -4;
        self->animCurFrame = 1;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(sensors2) & 1) {
            self->step++;
        }
        break;
    case 2:
        self->animCurFrame = 1;
        self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        if (GetDistanceToPlayerX() < 0x70) {
            self->step++;
        }
        break;
    case 3:
        UnkCollisionFunc2(sensors3);
        if (self->facingLeft) {
            self->velocityX = FIX(2.5);
        } else {
            self->velocityX = FIX(-2.5);
        }
        if (AnimateEntity(anim_running, self) == 0) {
            PlaySfxPositional(SFX_STOMP_HARD_D);
            if (CheckColliderOffsets(sensors1, self->facingLeft ^ 1) ^ 1) {
                SetStep(4);
            }
        }
        player = &PLAYER;
        playerSide = GetSideToPlayer() & 1;
        if ((player->facingLeft != playerSide) &&
            (GetDistanceToPlayerX() < 0x50) &&
            (g_Player.status & (PLAYER_STATUS_SPELLCAST | PLAYER_STATUS_SUBWPN |
                                PLAYER_STATUS_UNK400))) {
            SetStep(7);
        }
        xVar = self->posX.i.hi;
        if (self->facingLeft) {
            xVar += 0x18;
        } else {
            xVar -= 0x18;
        }
        yVar = self->posY.i.hi;
        g_api.CheckCollision(xVar, yVar, &sp2C, 0);
        if (sp2C.effects != EFFECT_NONE) {
            SetStep(6);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->velocityY = FIX(-3.5);
            self->step_s++;
            break;
        case 1:
            AnimateEntity(anim_twitchy_run, self);
            if (UnkCollisionFunc3(sensors2) & 1) {
                self->step_s++;
            }
            xVar = self->posX.i.hi;
            if (self->facingLeft) {
                xVar += 0x18;
            } else {
                xVar -= 0x18;
            }
            yVar = self->posY.i.hi;
            g_api.CheckCollision(xVar, yVar, &sp2C, 0);
            if (sp2C.effects != EFFECT_NONE) {
                SetStep(6);
            }
            break;
        case 2:
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            SetStep(3);
            break;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 9;
            self->velocityX = 0;
            self->velocityY = FIX(-4.0);
            self->step_s++;
            break;
        case 1:
            if (UnkCollisionFunc3(sensors2) & 1) {
                self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
                SetStep(3);
            }
            break;
        }
        break;
    case 6:
        if (!self->step_s) {
            self->animCurFrame = 0xB;
            if (self->facingLeft) {
                self->velocityX = FIX(-2.5);
            } else {
                self->velocityX = FIX(2.5);
            }
            self->velocityY = FIX(-3.0);
            self->drawFlags |= ENTITY_ROTATE;
            self->rotate = 0;
            self->step_s++;
        }
        self->rotate += ROT(22.5);
        if (UnkCollisionFunc3(sensors2) & 1) {
            self->drawFlags &=
                ENTITY_BLINK | ENTITY_MASK_B | ENTITY_MASK_G | ENTITY_MASK_R |
                ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
            SetStep(3);
        } else {
            self->velocityY -= FIX(0.0625);
        }
        break;
    case 7:
        func_us_801C4C4C();
        if (self->step_s == 4) {
            SetStep(8);
        }
        break;
    case 8:
        if (!self->step_s) {
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }
            self->ext.blackPanther.unk84 = 0x30;
            self->step_s++;
        } else {
            UnkCollisionFunc2(sensors3);
            prim = self->ext.blackPanther.prim9C;
            if (self->facingLeft) {
                prim->next->x1 = self->posX.i.hi - 0x12;
            } else {
                prim->next->x1 = self->posX.i.hi + 0x12;
            }
            prim->next->y0 = self->posY.i.hi + 2;
            UnkPrimHelper(prim);
            if (!--self->ext.blackPanther.unk84) {
                SetStep(9);
            }
        }
        break;
    case 9:
        func_us_801C5AA0();
        if ((self->step_s) == 7) {
            SetStep(3);
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            self->drawFlags |= ENTITY_ROTATE;
            self->rotate = 0;
            self->animCurFrame = 0xB;
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->velocityY = FIX(-3.5);
            self->step_s++;
            break;
        case 1:
            self->rotate -= ROT(11.25);
            if (UnkCollisionFunc3(sensors2) & 1) {
                self->step_s++;
            }
            break;
        case 2:
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, other);
                other->params = 2;
            }
            PlaySfxPositional(SFX_EXPLODE_SMALL);
            DestroyEntity(self);
            return;
        }
        break;
    case 32:
#include "../pad2_anim_debug.h"
    }

    if (self->animCurFrame == 1) {
        self->hitboxOffX = 9;
        self->hitboxOffY = 2;
        self->hitboxWidth = 0x11;
        self->hitboxHeight = 4;
    }
    if (self->animCurFrame == 2) {
        self->hitboxOffX = 5;
        self->hitboxOffY = -5;
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0xA;
    }
    if (self->animCurFrame > 2) {
        self->hitboxOffX = 4;
        self->hitboxOffY = -0xC;
        self->hitboxWidth = 0x17;
        self->hitboxHeight = 6;
    }
    if (self->animCurFrame > 5) {
        self->hitboxOffX = -2;
        self->hitboxOffY = -4;
        self->hitboxWidth = 0xB;
        self->hitboxHeight = 0xB;
    }
}
