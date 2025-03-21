// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

// n.b.! this is the same as bo4/unk_46E7C.c

void func_us_801C648C(s32 arg0) {
    s32 move = DOPPLEGANGER.facingLeft != 0 ? -3 : 3;

    DOPPLEGANGER.posY.i.hi -= 22;
    DOPPLEGANGER.posX.i.hi = move + DOPPLEGANGER.posX.i.hi;
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(4, 1), 0);
    DOPPLEGANGER.posY.i.hi = DOPPLEGANGER.posY.i.hi + 22;
    DOPPLEGANGER.posX.i.hi = DOPPLEGANGER.posX.i.hi - move;

    if (arg0 & 1) {
        g_api.func_80102CD8(3);
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
    }
    if (arg0 & 2) {
        DOPPLEGANGER.velocityX = 0;
        DOPPLEGANGER.velocityY = 0;
    }
}

void SetPlayerAnim(u8 anim);
bool func_us_801C5650(s32 branchFlags);

extern PlayerState g_Dop;

void PlayerStepHighJump(void) {
    s32 temp;
    s32 var_s1;

    var_s1 = 0;
    g_Dop.unk4A++;
    if (func_us_801C5650(2) != 0) {
        return;
    }

    switch (DOPPLEGANGER.step_s) {
    case 0:
        if (g_Dop.vram_flag & 2) {
            func_us_801C648C(3);
            if (g_Dop.unk4A > 4) {
                DOPPLEGANGER.step_s = 2;
                DOPPLEGANGER.rotZ = 0x800;
                DOPPLEGANGER.rotPivotX = 0;
                DOPPLEGANGER.rotPivotY = 2;
                DOPPLEGANGER.drawFlags |= FLAG_DRAW_ROTZ;
                DOPPLEGANGER.facingLeft = (DOPPLEGANGER.facingLeft + 1) & 1;
                SetPlayerAnim(0x2B);
            } else {
                DOPPLEGANGER.step_s = 3;
            }
        } else if (g_Dop.unk4A > 28) {
            DOPPLEGANGER.step_s = 1;
            DOPPLEGANGER.velocityY = -0x60000;
            SetPlayerAnim(0x1B);
        }
        break;

    case 1:
        if (g_Dop.vram_flag & 2) {
            DOPPLEGANGER.step_s = 2;
            func_us_801C648C(3);
        } else {
            DOPPLEGANGER.velocityY = DOPPLEGANGER.velocityY + 0x6000;
            if (DOPPLEGANGER.velocityY > 0x8000) {
                var_s1 = 1;
            }
        }
        break;

    case 2:
        DOPPLEGANGER.drawFlags |= FLAG_DRAW_ROTZ;
        DOPPLEGANGER.rotPivotX = 0;
        DOPPLEGANGER.rotPivotY = 2;
        if (g_Dop.unk4A > 56) {
            SetPlayerAnim(0x2D);
            DOPPLEGANGER.rotZ = 0;
            DOPPLEGANGER.step_s = 4;
            DOPPLEGANGER.drawFlags &=
                FLAG_BLINK | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                FLAG_DRAW_UNK10 | FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY |
                FLAG_DRAW_ROTX;
            DOPPLEGANGER.facingLeft = (DOPPLEGANGER.facingLeft + 1) & 1;
        }
        break;
    case 3:
        if (g_Dop.unk4A > 20) {
            var_s1 = 1;
        }
        break;
    case 4:
        DOPPLEGANGER.velocityY += 0x1000;
        if (DOPPLEGANGER.animFrameDuration < 0) {
            var_s1 = 2;
        }
        break;
    }

    if (var_s1 != 0) {
        temp = 0; // TODO: !FAKE
        if ((var_s1 - 1) != temp) {
            SetPlayerAnim(0x1C);
        }
        DOPPLEGANGER.palette = PAL_OVL(0x200);
        DOPPLEGANGER.step_s = 1;
        DOPPLEGANGER.step = Dop_Jump;
    }
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_80113E68);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C68CC);

void func_us_801C6950(void) {
    if (DOPPLEGANGER.posX.i.hi <= PLAYER.posX.i.hi) {
        DOPPLEGANGER.entityRoomIndex = 0;
        return;
    }
    DOPPLEGANGER.entityRoomIndex = 1;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C6990);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C6EEC);

extern PlayerState g_Dop;
extern s16 D_us_80183B9A[];

bool BatFormFinished(void) {
    if ((DOPPLEGANGER.step_s == 0) || !(g_Dop.padTapped & 8)) {
        return false;
    }

    SetPlayerStep(10);
    SetPlayerAnim(202);
    D_us_80183B9A[0] = 6;
    DOPPLEGANGER.palette = PAL_OVL(0x20D);
    g_Dop.unk66 = 0;
    g_Dop.unk68 = 0;
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x21), 0);
    DOPPLEGANGER.velocityY >>= 1;
    return true;
}

void func_8011690C(s16 arg0) {
    if (DOPPLEGANGER.rotZ < arg0) {
        DOPPLEGANGER.rotZ += 16;
        if (arg0 < DOPPLEGANGER.rotZ) {
            DOPPLEGANGER.rotZ = arg0;
        }
    }
    if (arg0 < DOPPLEGANGER.rotZ) {
        DOPPLEGANGER.rotZ -= 16;
        if (DOPPLEGANGER.rotZ < arg0) {
            DOPPLEGANGER.rotZ = arg0;
        }
    }
}

static s32 func_us_801C781C(void) {
    // n.b.! Dop10 checks for padTapped
    if (g_Dop.padPressed & PAD_SQUARE) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C7834);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C82F0);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C84F4);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C854C);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C89D4);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", PlayerStepSwordWarp);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C8CA4);

#include "../../get_free_entity.h"

// this is the same as unionD_800ACFB4 in DRA
typedef union {
    u8 rawBytes[4];
    AnimationFrame af;
} unionD_us_801813F8;
extern unionD_us_801813F8 D_us_801813F8[];

extern u8 D_us_801D3324;
extern u8 D_us_801D3328;
extern u8 D_us_801D332C;
extern u8 D_us_801D3330;

void func_80118C28(s32 arg0) {
    // Break up the 4-byte struct D_us_8018136C[arg0] into individual bytes.
    D_us_801D3324 = D_us_801813F8[arg0].rawBytes[0];
    D_us_801D3328 = D_us_801813F8[arg0].rawBytes[1];
    D_us_801D332C = D_us_801813F8[arg0].rawBytes[2];
    D_us_801D3330 = D_us_801813F8[arg0].rawBytes[3];
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_80119E78);

extern Point16 D_us_801D3334[16];

void DopEntityHitByHoly(Entity* self) {
    s32 shouldHide;
    s16 xRand;
    s16 yRand;
    s32 i;
    s16 hitboxX;
    s16 hitboxY;
    Primitive* prim;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, LEN(D_us_801D3334));
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_CAMERA_LOCKED;
        hitboxX = DOPPLEGANGER.posX.i.hi + DOPPLEGANGER.hitboxOffX;
        hitboxY = DOPPLEGANGER.posY.i.hi + DOPPLEGANGER.hitboxOffY;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < LEN(D_us_801D3334); i++) {
            xRand = hitboxX + rand() % 24 - 12;
            yRand = hitboxY + rand() % 48 - 24;
            D_us_801D3334[i].x = xRand;
            D_us_801D3334[i].y = yRand;
            prim->clut = 0x1B2;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() & 7) + 1;
            prim->g2 = 0;
            prim->priority = DOPPLEGANGER.zPriority + 4;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_UNK02 | DRAW_TRANSP;
            if (rand() & 1) {
                prim->drawMode =
                    DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                    DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }
        self->step++;
        break;

    case 1:
        if (!(g_Dop.status & PLAYER_STATUS_UNK10000)) {
            DestroyEntity(self);
            return;
        }
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < LEN(D_us_801D3334); i++) {
        switch (prim->g0) {
        case 0:
            if (--prim->g1 == 0) {
                prim->g0++;
            }
            break;
        case 1:
            hitboxX = D_us_801D3334[i].x;
            hitboxY = D_us_801D3334[i].y;
            shouldHide = func_80119E78(prim, hitboxX, hitboxY);
            D_us_801D3334[i].y--;
            if (shouldHide < 0) {
                prim->drawMode |= DRAW_HIDE;
                prim->g0++;
            } else {
                prim->drawMode &= ~DRAW_HIDE;
            }
            break;
        }
        prim = prim->next;
    }
}

void func_80103EAC(void) { FntPrint("dummy set\n"); }

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C9624);

Entity* CreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s16 arg2) {
    Entity* newFactory = GetFreeEntity(0x44, 0x50);

    if (newFactory == NULL) {
        return NULL;
    }

    DestroyEntity(newFactory);
    newFactory->entityId = E_ENTITYFACTORY;
    newFactory->ext.factory.parent = source;
    newFactory->posX.val = source->posX.val;
    newFactory->posY.val = source->posY.val;
    newFactory->facingLeft = source->facingLeft;
    newFactory->zPriority = source->zPriority;
    newFactory->params = factoryParams & 0xFFF;
    newFactory->ext.factory.unkA0 = (factoryParams & 0xFF0000) >> 8;
    return newFactory;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C98BC);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801C9D58);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_8011B5A4);

extern s32 D_us_801D3374;
extern AnimationFrame D_us_801818B4[];

void DopEntityHitByDark(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_20000000 | FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x79;
        self->animSet = ANIMSET_DRA(14);
        self->zPriority = DOPPLEGANGER.zPriority + 2;
        self->palette = PAL_OVL(0x19F);

        if (D_us_801D3374 & 1) {
            self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        } else {
            self->drawMode = DRAW_TPAGE;
        }
        D_us_801D3374++;
        self->unk6C = 0xFF;
        self->drawFlags =
            FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20;
        self->rotX = self->rotY = 0x40;
        self->anim = D_us_801818B4;

        self->posY.i.hi += ((rand() % 35) - 15);
        self->posX.i.hi += ((rand() % 20) - 10);
        self->velocityY = FIX(-0.375) - (rand() & 0x3FFF);
        self->step++;
        break;
    case 1:
        if (self->unk6C > 16) {
            self->unk6C -= 8;
        }
        self->posY.val += self->velocityY;
        self->rotX += 8;
        self->rotY += 8;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_8011BD48);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801CA68C);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", EntityPlayerOutline);

void EntityGravityBootBeam(Entity* self) {
    Primitive* prim;
    s16 halfWidth;
    s32 i;
    s16 yOffset = -12;

    switch (self->step) {
    case 0:
        self->posY.i.hi = DOPPLEGANGER.posY.i.hi + 37;
        self->ext.timer.t = 1536;
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;

        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
            prim = prim->next) {
            halfWidth = (self->ext.timer.t >> 8) - i; // unused in this loop
            prim->r0 = 0;
            prim->g0 = 0;
            prim->b0 = 0xC0;
            prim->r1 = 0;
            prim->g1 = 0;
            prim->b1 = 0xC0;
            prim->r2 = 0x40;
            prim->g2 = 0x40;
            prim->b2 = 0x40;
            prim->r3 = 0x40;
            prim->g3 = 0x40;
            prim->b3 = 0x40;

            prim->priority = DOPPLEGANGER.zPriority - 2;
            prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        }
        self->step++;
        break;

    case 1:
        if (DOPPLEGANGER.velocityY > FIX(-1.5)) {
            self->step = 2;
        }
        // If transformed, timer drains faster
        if (g_Dop.status & (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) {
            self->step = 3;
        }
        break;

    case 3:
        // note that with the fallthrough these decrements stack
        self->ext.timer.t -= 160;
    case 2:
        self->ext.timer.t -= 96;
        if (self->ext.timer.t < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
        prim = prim->next) {
        // As timer counts down, beam gets narrower.
        halfWidth = (self->ext.timer.t >> 8) - i;
        if (halfWidth < 0) {
            halfWidth = 0;
        }
        prim->x0 = self->posX.i.hi - halfWidth;
        prim->x1 = self->posX.i.hi + halfWidth;
        prim->x2 = DOPPLEGANGER.posX.i.hi - halfWidth;
        prim->x3 = DOPPLEGANGER.posX.i.hi + halfWidth;
        prim->y2 = prim->y3 = DOPPLEGANGER.posY.i.hi - yOffset;
        prim->y0 = prim->y1 = self->posY.i.hi;
    }
}

// The blue outlines of the bat that show up when wing smashing
void EntityWingSmashTrail(Entity* self) {
    if (!(DOPPLEGANGER.step_s == 3 && DOPPLEGANGER.step == Dop_MorphBat)) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = DOPPLEGANGER.animSet;
        self->animCurFrame = DOPPLEGANGER.animCurFrame | ANIM_FRAME_LOAD;
        self->unk5A = 8;
        self->zPriority = DOPPLEGANGER.zPriority - 2;
        self->drawFlags = DOPPLEGANGER.drawFlags |
                          (FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX);
        self->unk6C = 0x80; // a lifetime counter
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->rotZ = DOPPLEGANGER.rotZ;
        self->facingLeft = DOPPLEGANGER.facingLeft;
        self->palette = PAL_OVL(0x202);
        self->rotX = self->rotY = 0x100;
        self->step++;
        return;
    }
    // This actually makes the wing smashes shrink over time, not rotate.
    self->rotX -= 8;
    self->rotY -= 8;
    self->animCurFrame = DOPPLEGANGER.animCurFrame | ANIM_FRAME_LOAD;
    // Unclear why we count down by 5's instead of just making unk6C start
    // smaller
    if (self->unk6C >= 5) {
        self->unk6C -= 5;
    } else {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801CC788);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_8011EDA8);

extern u16 D_us_80181E38[2];

void DopEntityHitByLightning(Entity* self) {
    s16 xBase;
    s16 yBase;
    s32 xOffset;
    s32 yOffset;
    bool var_s0 = false;
    s32 temp_s2;
    s16 temp_s1_2;
    s16 temp_s0;
    s32 i;
    Primitive* prevPrim;
    Primitive* prim;

    if ((self->params & 0xFF00) != 0) {
        if ((++self->ext.hitbylightning.unk9C) > 0xA8) {
            var_s0 = true;
        }
    } else if (DOPPLEGANGER.step != 11) {
        var_s0 = true;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x3F);
        self->ext.hitbylightning.unk80 = rand() & PSP_RANDMASK;
        self->ext.hitbylightning.unk82 = (rand() & 0x1FF) + 0x100;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
            prim->tpage = 0x1A;
            prim->clut = D_us_80181E38[rand() & 1];
            prim->priority = DOPPLEGANGER.zPriority - 2;
            PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) =
                0x80;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        if ((DOPPLEGANGER.velocityY != 0) && (DOPPLEGANGER.step != 17)) {
            self->ext.hitbylightning.unk92 = 1;
        }
        self->ext.hitbylightning.unk94 = 16;
        g_api.PlaySfx(SFX_MAGIC_SWITCH);
        g_api.PlaySfx(SFX_THUNDER_B);
        self->step++;
        break;
    case 1:
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x1FF);
        temp_s2 = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xOffset = ((rcos(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) * 12;
        // This should probably be * -14 but that doesn't work.
        yOffset =
            -((rsin(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) * 7 << 1;
        self->posX.val = xOffset + DOPPLEGANGER.posX.val;
        self->posY.val = yOffset + DOPPLEGANGER.posY.val;
        if ((self->ext.hitbylightning.unk92) && (g_Dop.vram_flag & 0xE)) {
            var_s0 = true;
        }
        if (var_s0) {
            self->ext.hitbylightning.unk90 = (rand() & 0xF) + 0x10;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.hitbylightning.unk90 == 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.hitbylightning.unk94 > 0) {
            self->ext.hitbylightning.unk94--;
        }
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0xFF);
        temp_s2 = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xOffset = (((rcos(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) *
                   ((rand() % 8) + 8));
        yOffset = (-((rsin(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) *
                   ((rand() % 8) + 10)) +
                  self->ext.hitbylightning.unk98;
        self->posX.val = DOPPLEGANGER.posX.val + xOffset;
        self->posY.val = DOPPLEGANGER.posY.val + yOffset;
        self->ext.hitbylightning.unk98 -= 0x8000;
        prim = &g_PrimBuf[self->primIndex];
        break;
    }
    xBase = (self->posX.i.hi + (rand() & 7)) - 4;
    yBase = (self->posY.i.hi + (rand() & 0x1F)) - 0x18;
    temp_s1_2 = self->ext.hitbylightning.unk94;
    temp_s1_2 = (temp_s1_2 * rsin(self->ext.hitbylightning.unk80)) >> 0xC;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 5; i++) {
        prevPrim = prim;
        prim = prim->next;
        *prevPrim = *prim;
        prevPrim->next = prim;
        prevPrim->u0 = prevPrim->u2 = (i * 0x10) + 0x90;
        prevPrim->u1 = prevPrim->u3 = ((i + 1) * 0x10) + 0x90;
        prevPrim->v0 = prevPrim->v1 = 0xC0;
        prevPrim->v2 = prevPrim->v3 = 0xCF;
    }
    prim->x0 = prim->x1;
    prim->y0 = prim->y1;
    prim->x2 = prim->x3;
    prim->y2 = prim->y3;
    temp_s0 = self->ext.hitbylightning.unk7C + 0x400;
    prim->x1 = xBase + (((rcos(temp_s0) >> 4) * temp_s1_2) >> 8);
    prim->y1 = yBase - (((rsin(temp_s0) >> 4) * temp_s1_2) >> 8);
    temp_s0 = self->ext.hitbylightning.unk7C - 0x400;
    prim->x3 = xBase + (((rcos(temp_s0) >> 4) * temp_s1_2) >> 8);
    prim->y3 = yBase - (((rsin(temp_s0) >> 4) * temp_s1_2) >> 8);

    temp_s0 = (self->ext.hitbylightning.unk80 & 0xFFF);
    if (temp_s0 < 0x400) {
        prim->priority = DOPPLEGANGER.zPriority + 2;
    } else if (temp_s0 < 0xC00) {
        prim->priority = DOPPLEGANGER.zPriority - 2;
    } else {
        prim->priority = DOPPLEGANGER.zPriority + 2;
    }
    prim->u0 = prim->u2 = (i << 4) + 0x90;
    prim->u1 = prim->u3 = (i + 1 << 4) + 0x90;
    prim->v0 = prim->v1 = 0xC0;
    prim->v2 = prim->v3 = 0xCF;
}

// player gets frozen
extern Point16* D_us_80181E84[];

void EntityHitByIce(Entity* self) {
    s32 i;
    s16 xShift;
    s16 yShift;
    s32 size;
    s16 primYshift;
    s16 selfX;
    s16 selfY;
    Point16* offset;
    bool sp18;

    s16 angle;

    Primitive* prim;

    self->posX.i.hi = DOPPLEGANGER.posX.i.hi;
    self->posY.i.hi = DOPPLEGANGER.posY.i.hi;

    sp18 = false;
    if (!(g_Dop.status & PLAYER_STATUS_UNK10000)) {
        sp18 = true;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT3, 24);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS;
        for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
             prim = prim->next) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = (rand() & 0xF) + 0x30;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = (rand() & 0x7F) + 0x80;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = (rand() & 0x1F) + 0x30;
            if (rand() & 1) {
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            } else {
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            }
            prim->type = PRIM_G4;
            prim->priority = DOPPLEGANGER.zPriority + 2;
        }
        if (DOPPLEGANGER.velocityY != 0) {
            self->ext.hitbyice.unk7E = 1;
        }
        if (DOPPLEGANGER.step == Dop_Kill) {
            self->ext.hitbyice.unk80 = 1;
            self->ext.hitbyice.unk82 = 0x14;
            self->ext.hitbyice.unk7E = 0;
        }
        if (DOPPLEGANGER.velocityY != 0) {
            if (DOPPLEGANGER.facingLeft) {
                self->rotZ = 0x100;
            } else {
                self->rotZ = -0x100;
            }
        } else {
            if (DOPPLEGANGER.velocityX > 0) {
                self->rotZ = 0x80;
            } else {
                self->rotZ = 0xF80;
            }
        }
        self->step++;
        break;
    case 1:
        if (self->ext.hitbyice.unk80 && --self->ext.hitbyice.unk82 == 0) {
            sp18 = true;
        }
        // Could rewrite as a series of && and || but that would probably reduce
        // readability
        if (self->ext.hitbyice.unk7E) {
            if (g_Dop.vram_flag & 0xC) {
                sp18 = true;
            }
            if (DOPPLEGANGER.step == Dop_Hit && DOPPLEGANGER.step_s == 5) {
                sp18 = true;
            }
        }
        if (sp18) {
            self->ext.hitbyice.unk7C = 0x40;
            g_api.PlaySfx(SFX_MAGIC_SWITCH);
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.hitbyice.unk7C == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    for (prim = &g_PrimBuf[self->primIndex], i = 0; i < 24; prim = prim->next,
        i++) {
        offset = D_us_80181E84[i * 3];
        if (prim->u0 < 2) {
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotZ + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x0 = selfX + xShift;
            prim->y0 = selfY + yShift;

            offset = D_us_80181E84[i * 3 + 1];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotZ + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x1 = selfX + xShift;
            prim->y1 = selfY + yShift;

            offset = D_us_80181E84[i * 3 + 2];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotZ + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x2 = prim->x3 = selfX + xShift;
            prim->y2 = prim->y3 = selfY + yShift;
        }
        if ((prim->u0 == 0) && (sp18 != 0)) {
            prim->u0++;
            prim->v0 = (rand() & 15) + 1;
        }
        if (prim->u0 == 1) {
            if (--prim->v0 == 0) {
                prim->u0++;
                prim->v0 = 0x20;
                prim->u2 = 0xF0;
            }
        }
        if (prim->u0 == 2) {
            if ((prim->u2 < 0x70) || (prim->u2 > 0xD0)) {
                prim->u2 += 4;
            }
            primYshift = (s8)prim->u2 >> 4;
            prim->y0 += primYshift;
            prim->y1 += primYshift;
            prim->y2 += primYshift;
            prim->y3 += primYshift;
            if (prim->r3 < 4) {
                prim->r3 -= 4;
            }
            if (prim->g3 < 4) {
                prim->g3 -= 4;
            }
            if (prim->b3 < 4) {
                prim->b3 -= 4;
            }
            prim->r0 = prim->r1 = prim->r2 = prim->r3;
            prim->b0 = prim->b1 = prim->b2 = prim->b3;
            prim->g0 = prim->g1 = prim->g2 = prim->g3;

            prim->drawMode &= ~DRAW_UNK02;
            if (--prim->v0 == 0) {
                prim->drawMode |= DRAW_HIDE;
            }
        }
    }
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_80121F14);

#include "../../dra/mist.h"

extern Primitive D_us_801D34D8[8];
extern u32 D_us_80182024[8];
extern u32 D_us_80182044[8];
extern mistStruct D_us_801D3378[16];

Primitive* func_80121F58(bool arg0, s32 arg1, Primitive* arg2, s16 facingLeft) {
    s32 primU0;
    s32 tempU;
    s32 tempV;
    s32 primU1;
    s32 primV0;
    s32 primV1;
    s16 angle1;
    s16 angle2;
    Primitive* prim;
    s32 i;

    if (arg0 == false) {
        if (facingLeft) {
            prim = &D_us_801D34D8[D_us_80182024[arg1 >> 1]];
            primU0 = prim->u0;
            tempU = prim->u1;
            primV0 = prim->v0;
            tempV = prim->v1;
        } else {
            prim = &D_us_801D34D8[D_us_80182044[arg1 >> 1]];
            primU0 = prim->u1;
            tempU = prim->u0;
            primV0 = prim->v1;
            tempV = prim->v0;
        }

        primU1 = (prim->u0 + prim->u1) / 2;
        primV1 = (prim->v0 + prim->v1) / 2;

        if (arg1 & 1) {
            primU0 = primU1;
            primU1 = tempU;
            primV0 = primV1;
            primV1 = tempV;
        }
        arg2->u0 = primU0;
        arg2->v0 = primV0;
        arg2->u1 = primU1;
        arg2->v1 = primV1;
        arg2->u3 = arg2->u2 = prim->u2;
        arg2->v3 = arg2->v2 = prim->v2;
        if (DOPPLEGANGER.animSet == 0xF) {
            arg2->tpage = 0x118;
        } else {
#ifdef VERSION_PSP
            arg2->tpage = 0x18;
#else
            arg2->tpage = 0x10;
#endif
        }
        arg2->clut = 0x20F;
        arg2->priority = DOPPLEGANGER.zPriority + 2;
        arg2->drawMode = DRAW_UNK_400 | DRAW_UNK_100 | DRAW_TPAGE2 |
                         DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        arg2 = arg2->next;
    } else {
        angle1 = D_us_801D3378[arg1].angle1;
        angle2 = D_us_801D3378[(arg1 + 1) % 16].angle1;

        for (i = 0; i < 4; i++) {
            // nb: the cos/sin arguments seem to be invariant, could've been
            // extracted outside the loop
            arg2->u0 = 0x60 + ((((rcos(angle1) >> 4) * 8) * (i + 1)) >> 8);
            arg2->v0 = 0xA0 - ((((rsin(angle1) >> 4) * 8) * (i + 1)) >> 8);
            arg2->u1 = 0x60 + ((((rcos(angle2) >> 4) * 8) * (i + 1)) >> 8);
            arg2->v1 = 0xA0 - ((((rsin(angle2) >> 4) * 8) * (i + 1)) >> 8);

            if (i == 3) {
                if (arg2->u0 < 4) {
                    arg2->u0 = -1;
                }
                if (arg2->u1 < 4) {
                    arg2->u1 = -1;
                }
                if (arg2->v0 < 4) {
                    arg2->v0 = -1;
                }
                if (arg2->v1 < 4) {
                    arg2->v1 = -1;
                }
            }

            arg2->u2 = 0x60 + ((((rcos(angle1) >> 4) * 8) * i) >> 8);
            arg2->v2 = 0xA0 - ((((rsin(angle1) >> 4) * 8) * i) >> 8);
            arg2->u3 = 0x60 + ((((rcos(angle2) >> 4) * 8) * i) >> 8);
            arg2->v3 = 0xA0 - ((((rsin(angle2) >> 4) * 8) * i) >> 8);

            arg2->tpage = 0x18;
            arg2->clut = 0x20F;
            arg2->priority = DOPPLEGANGER.zPriority + 4;
            arg2->drawMode =
                DRAW_UNK_400 | DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            arg2 = arg2->next;
        }
    }
    return arg2;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", EntityMist);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801CF8C4);

#include "../../rebound_stone.h"

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801D038C);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801D0BD8);

INCLUDE_ASM("boss/rbo5/nonmatchings/unk_4648C", func_us_801D0D98);
