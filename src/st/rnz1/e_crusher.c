// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

static AnimateEntityFrame animCrusherTeeth[] = {
    {7, 7}, {7, 8}, {7, 9}, {7, 10}, POSE_LOOP(0)};

s16 UpdateCrusherChain(Primitive* prim, s32 arg1, s32 arg2) {
    prim->drawMode = DRAW_UNK02;
    prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - 8;
    prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + 8;
    prim->v2 = prim->v3 = 0x70;
    prim->y2 = prim->y3 = arg1;
    arg1 -= 0x60;
    if (arg1 < arg2) {
        arg1 = arg2 - arg1;
        prim->v0 = prim->v1 = arg1 + 0x10;
        prim->y0 = prim->y1 = arg2;
        arg1 = 0;
    } else {
        prim->v0 = prim->v1 = 0x10;
        prim->y0 = prim->y1 = arg1;
    }
    return arg1;
}

// NOTE: This function contains an ugly ifdef! It is seen in several other files
// including a few different e_secrets, and e_discus_lord. Search for:
// (prim->x0 << 0x10) + (u16)prim->x1; and you will find those others.
// This likely signals something we are doing wrongly! Maybe a weird union?
void func_us_801BD184(Primitive* prim) {
    u32 x;
    u32 y;
    s32 length;
    s16 angle;

    switch (prim->p1) {
    case 0:
        prim->r0 = 0x80;
        prim->g0 = 0x80;
        prim->b0 = 0xC0;
        prim->drawMode = DRAW_UNK02;
        prim->x1 = 0;
        prim->y1 = 0;
        prim->y0 = g_CurrentEntity->posY.i.hi + 0xC;
        length = (Random() & 0x1F) + 0x20;
        angle = (Random() * 6) + 0x900;
        LOW(prim->x2) = length * rcos(angle);
        LOW(prim->x3) = length * rsin(angle);
        prim->p1 = 1;
        prim->r3 = 0x10;
        /* fallthrough */
    case 1:
#ifdef VERSION_US
        x = (prim->x0 << 0x10) + (u16)prim->x1;
#else
        x = (prim->x0 << 0x10) + prim->x1;
#endif
        x += LOW(prim->x2);
        prim->x0 = HIHU(x);
        prim->x1 = LOHU(x);
#ifdef VERSION_US
        y = (prim->y0 << 0x10) + (u16)prim->y1;
#else
        y = (prim->y0 << 0x10) + prim->y1;
#endif
        y += LOW(prim->x3);
        prim->y0 = HIH(y);
        prim->y1 = LOH(y);
        LOW(prim->x3) += 0x2000;
        prim->r0 -= 5;
        prim->g0 -= 5;
        prim->b0 -= 9;
        prim->r3 -= 1;
        if (!prim->r3) {
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }
    }
}

// Grindy crushy platform things.
// params 0 = one-wide, params 1 = three-wide
extern EInit g_EInitCrusher;

void EntityCrusher(Entity* self) {
    Entity* crusherHead;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCrusher);
        self->hitboxState = 0;
        self->animCurFrame = 1;
        crusherHead = self + 1;
        CreateEntityFromEntity(E_CRUSHER_HEAD, self, crusherHead);
        crusherHead->posY.i.hi += 0x20;
        crusherHead->params = self->params;
    }
}

typedef enum {
    CRUSHER_INIT,
    CRUSHER_TOP_STUTTER,
    CRUSHER_FALL,
    CRUSHER_GRIND_FLOOR,
    CRUSHER_RAISE
} CrusherSteps;

void EntityCrusherHead(Entity* self) {
    Collider sp3C;
    bool hitPlayer;
    s32 primIndex;
    s32 xVar;
    s32 anchorY;
    s32 i;
    Entity* other;
    s32 yVar;
    Primitive* prim;

    if (!self->params) {
        xVar = 24;
    } else {
        xVar = 50;
    }
    hitPlayer = GetPlayerCollisionWith(self, xVar, 0x10, 4);
    switch (self->step) {
    case CRUSHER_INIT:
        InitializeEntity(g_EInitCrusher);
        if (!self->params) {
            self->animCurFrame = 3;
            self->hitboxState = 1;
            self->hitboxWidth = 20;
            self->hitboxHeight = 4;
            self->hitboxOffY = 0x10;
            self->attackElement = ELEMENT_CUT | ELEMENT_UNK_10;
            self->attack = 15;
        } else {
            self->animCurFrame = 6;
            self->hitboxOffY = 26;
            other = self + 1;
            for (i = 0; i < 3; i++, other++) {
                CreateEntityFromEntity(E_CRUSHER_SPINNING_TEETH, self, other);
                other->params = i;
            }
        }
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.crusher.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0x14;
            prim->clut = 0x232;
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xF0;
            prim->priority = (self->zPriority - 1);
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;
    case CRUSHER_TOP_STUTTER:
        if (!self->step_s) {
            self->ext.crusher.timer = 0x20;
            self->step_s++;
        }
        if (self->ext.crusher.timer & 1) {
            self->posY.i.hi--;
        } else {
            self->posY.i.hi++;
        }
        if (!--self->ext.crusher.timer) {
            SetStep(CRUSHER_FALL);
        }
        break;
    case CRUSHER_FALL:
        if (!self->step_s) {
            self->velocityY = FIX(0.5);
            self->step_s++;
        }
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_METAL_RATTLE_C);
        }
        MoveEntity();
        if (self->params) {
            self->velocityY += FIX(0.25);
        }
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi;
        if (!self->params) {
            yVar += 16;
        } else {
            yVar += 28;
        }
        g_api.CheckCollision(xVar, yVar, &sp3C, 0);
        if (sp3C.effects & EFFECT_SOLID) {
            PlaySfxPositional(SFX_START_SLAM_B);
            self->posY.i.hi += sp3C.unk18;
            SetStep(CRUSHER_GRIND_FLOOR);
            if (self->params) {
                g_api.func_80102CD8(1);
            }
        }
        break;
    case CRUSHER_GRIND_FLOOR:
        if (!self->step_s) {
            if (!self->params) {
                self->ext.crusher.timer = 0x20;
            } else {
                self->ext.crusher.timer = 0x40;
            }
            self->step_s++;
        }
        self->ext.crusher.floorGrinding = true;
        if (self->params && !(self->ext.crusher.timer & 3)) {
            PlaySfxPositional(SFX_EXPLODE_FAST_A);
        }
        if (!--self->ext.crusher.timer) {
            self->ext.crusher.floorGrinding = false;
            SetStep(CRUSHER_RAISE);
        }
        break;
    case CRUSHER_RAISE:
        if (!self->step_s) {
            self->velocityY = FIX(-0.5);
            self->step_s++;
        }
        other = self - 1;
        anchorY = other->posY.i.hi + 0x20;
        if ((g_Timer % 12) == 0) {
            PlaySfxPositional(SFX_METAL_RATTLE_B);
        }
        MoveEntity();
        // If we have moved above the "anchor" at the top of the chain,
        if (self->posY.i.hi < anchorY) {
            self->velocityY = 0;
            self->posY.i.hi = anchorY;
            SetStep(CRUSHER_TOP_STUTTER);
        }
        if (hitPlayer && (g_Player.vram_flag & TOUCHING_CEILING)) {
            self->velocityY = 0;
            SetStep(CRUSHER_FALL);
        }
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
    if (hitPlayer) {
        other = &PLAYER;
        yVar = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        yVar -= self->ext.crusher.yOff;
        other->posY.i.hi += yVar;
        g_api.func_8010DFF0(0, 1);
    }
    yVar = self->posY.i.hi - 0x10;
    prim = self->ext.crusher.prim;
    other = self - 1;
    anchorY = other->posY.i.hi;
    while (prim != NULL) {
        yVar = UpdateCrusherChain(prim, yVar, anchorY);
        prim = prim->next;
        if (yVar == 0) {
            break;
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    self->ext.crusher.yOff = (self->posY.i.hi + g_Tilemap.scrollY.i.hi);
    if (!self->params) {
        if (self->hitFlags) {
            self->ext.crusher.bloodyTimer = 55;
        }
        if (self->ext.crusher.bloodyTimer) {
            self->ext.crusher.bloodyTimer--;
        }
        self->palette =
            (g_EInitCrusher[3] + (self->ext.crusher.bloodyTimer >> 3));
    }
}

void EntityCrusherSpinningTeeth(Entity* self) {
    Entity* other;
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCrusher);
        self->hitboxState = 1;
        self->hitboxOffY = 7;
        self->hitboxWidth = 13;
        self->hitboxHeight = 5;
        self->attackElement = 0x50;
        self->attack = 15;
        primIndex = g_api.AllocPrimitives(PRIM_TILE_ALT, 32);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        for (self->ext.crusher.prim = prim; prim != NULL; prim = prim->next) {
            prim->u0 = prim->v0 = 1;
            prim->r0 = 0x40;
            prim->g0 = 0x40;
            prim->b0 = 0x40;
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_HIDE;
        }
    case 1:
        AnimateEntity(animCrusherTeeth, self);
        other = self - self->params - 1;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi + 0x12;
        self->posX.i.hi += ((self->params * 36) - 36);
        if (other->ext.crusher.floorGrinding) {
            if (g_Timer & 1) {
                other = AllocEntity(&g_Entities[224], &g_Entities[240]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, other);
                    other->params = 0x10;
                    other->zPriority = (self->zPriority + 1);
                    other->posY.i.hi += 12;
                    other->posX.i.hi += ((Random() & 0x1F) - 0x10);
                }
            }
            prim = self->ext.crusher.prim;
            prim = FindFirstUnkPrim(prim);
            if (prim != NULL) {
                prim->p1 = 0;
                prim->y0 = self->posY.i.hi + 12;
                prim->x0 = (self->posX.i.hi + (Random() & 0x1F)) - 0x10;
                prim->p3 = 2;
            }
        }
    }
    if (self->hitFlags) {
        self->ext.crusher.bloodyTimer = 55;
    }
    if (self->ext.crusher.bloodyTimer) {
        self->ext.crusher.bloodyTimer -= 1;
    }
    self->palette = (g_EInitCrusher[3] + (self->ext.crusher.bloodyTimer >> 3));
    for (prim = self->ext.crusher.prim; prim->next != NULL; prim = prim->next) {
        if (prim->p3 & 2) {
            func_us_801BD184(prim);
        }
    }
    prim->p3 = 2;
    prim->x0 = prim->y0 = -0x10;
    prim->priority = (self->zPriority + 2);
    prim->drawMode = DRAW_UNK02;
}
