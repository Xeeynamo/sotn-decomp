// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "objects.h"
#include "sfx.h"

// BSS
extern Point16 D_8013839C[32];
extern s32 D_8013841C;
extern RECT D_80138424;

// teleport effect like when using library card (ID 0x42)
void EntityTeleport(Entity* self) {
    Primitive* prim;
    s32 selfUnk7C;
    s32 selfUnk80;
    s32 yVar;
    s32 xVar;
    s32 upperParams;
    s32 i;
    s32 result;

    bool wasCase3 = false;
    bool var_s5 = false;

    upperParams = self->params & 0xFE00;
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, LEN(D_8013839C) + 4);
        if (self->primIndex == -1) {
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 2; i++) {
            prim->x0 = 0xC0 * i;
            prim->g0 = 0;
            prim->b0 = 0;
            prim->r0 = 0;
            prim->y0 = 0;
            prim->u0 = 0xC0;
            prim->v0 = 0xF0;
            prim->type = PRIM_TILE;
            prim->priority = 0x1FD;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            prim = prim->next;
        }
        for (i = 0; i < 2; i++) {
            prim->type = PRIM_G4;
            prim->priority = 0x1F8;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
        }
        for (i = 0; i < LEN(D_8013839C); i++) {
            xVar = PLAYER.posX.i.hi + (rand() % 28) - 14;
            yVar = rand();
            yVar = 0xE0 - (yVar & 0x3F);
            D_8013839C[i].x = xVar;
            D_8013839C[i].y = yVar;
            prim->clut = 0x1BA;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() & 0x1F) + 1;
            prim->priority = 0x1F0;
            prim->drawMode = DRAW_HIDE;
            prim->g2 = 0;
            prim = prim->next;
        }
        self->ext.teleport.unk7C = 0;
        self->ext.teleport.unk80 = 0x10;
        self->ext.teleport.unk88 = 0x80;
        if (self->params & 0x100) {
            var_s5 = true;
            self->ext.teleport.unk7C = 0x10;
            self->ext.teleport.unk80 = 0x100;
            self->ext.teleport.unk88 = 0x80;
            self->ext.teleport.unk90 = 0xFF;
            self->step = 0x14;
            PlaySfx(SFX_UNK_8BB);
        } else {
            self->ext.teleport.unk7C = 1;
            self->ext.teleport.unk90 = 0;
            self->ext.teleport.unk80 = 0x10;
            self->ext.teleport.unk88 = 0x80;
            self->step = 1;
            PlaySfx(SFX_TELEPORT_BANG_A);
            PlaySfx(NA_SE_PL_TELEPORT);
        }
        break;
    case 1:
        self->ext.teleport.unk80 += 0x20;
        if (self->ext.teleport.unk80 >= 0x101) {
            self->step++;
        }
        break;
    case 2:
        if (++self->ext.teleport.unk7C >= 0x10) {
            self->ext.teleport.unk7C = 0x10;
            self->ext.teleport.unk84 = 0x80;
            self->step++;
        }
        break;
    case 3:
        wasCase3 = true;
        self->ext.teleport.unk88 += 4;
        if (self->ext.teleport.unk88 >= 0x100) {
            self->ext.teleport.unk88 = 0x100;
        }
        if (--self->ext.teleport.unk84 == 0) {
            PLAYER.palette = 0x810D;
            self->step++;
        }
        break;
    case 4:
        PLAYER.palette = 0x810D;
        if (--self->ext.teleport.unk7C <= 0) {
            self->ext.teleport.unk7C = 0;
            self->step++;
        }
        break;
    case 5:
        var_s5 = true;
        PLAYER.palette = 0x810D;
        self->ext.teleport.unk90 += 4;
        if (self->ext.teleport.unk90 >= 0x100) {
            self->ext.teleport.unk90 = 0xFF;
            self->ext.teleport.unk84 = 0x20;
            self->step++;
        }
        break;
    case 6:
        var_s5 = true;
        PLAYER.palette = 0x810D;
        if (--self->ext.teleport.unk84 == 0) {
            self->ext.teleport.unk90 = 0;
            if (upperParams == 0) {
                D_80097C98 = 6;
            }
            if (upperParams == 0x200) {
                D_80097C98 = 4;
            }
            if (upperParams == 0x400) {
                D_80097C98 = 5;
            }
        }
        break;
    case 20:
        var_s5 = true;
        self->ext.teleport.unk90 = 0xFF;
        self->ext.teleport.unk84 = 0x20;
        self->step++;
        break;
    case 21:
        var_s5 = true;
        if (--self->ext.teleport.unk84 == 0) {
            self->step++;
        }
        break;
    case 22:
        var_s5 = true;
        self->ext.teleport.unk90 -= 4;
        if (self->ext.teleport.unk90 <= 0) {
            self->ext.teleport.unk90 = 0;
            self->step++;
        }
        break;
    case 23:
        if (--self->ext.teleport.unk7C < 2) {
            self->ext.teleport.unk7C = 0;
            self->ext.teleport.unk84 = 4;
            self->step++;
            g_Player.unk1C = 1;
            PlaySfx(SFX_TELEPORT_BANG_B);
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfUnk7C = self->ext.teleport.unk7C;
    selfUnk80 = self->ext.teleport.unk80;
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    xVar = PLAYER.posX.i.hi;
    yVar = PLAYER.posY.i.hi;
    for (i = 0; i < 2; i++) {
        prim->r0 = prim->b0 = prim->g0 = self->ext.teleport.unk90;
        prim->drawMode |= DRAW_HIDE;
        if (var_s5) {
            prim->drawMode &= ~DRAW_HIDE;
        }
        prim = prim->next;
    }
    prim->x1 = prim->x3 = xVar;
    prim->x0 = prim->x2 = xVar - selfUnk7C;
    func_80124164(prim, self->ext.teleport.unk88, yVar, selfUnk80, upperParams);
    prim = prim->next;
    prim->x1 = prim->x3 = xVar;
    prim->x0 = prim->x2 = xVar + selfUnk7C;
    func_80124164(prim, self->ext.teleport.unk88, yVar, selfUnk80, upperParams);
    prim = prim->next;
    if (wasCase3) {
        for (i = 0; i < LEN(D_8013839C); i++) {
            switch (prim->g0) {
            case 0:
                if (--prim->g1 == 0) {
                    prim->g0++;
                }
                break;
            case 1:
                result = func_80119E78(prim, D_8013839C[i].x, D_8013839C[i].y);
                D_8013839C[i].y -= 16;
                if (result < 0) {
                    prim->drawMode |= DRAW_HIDE;
                    prim->g0++;
                } else {
                    prim->drawMode &= ~DRAW_HIDE;
                }
                break;
            }
            prim = prim->next;
        }
        return;
    }

    // Potential bug? Should probably be doing prim = prim->next, right?
    for (i = 0; i < 32; i++) {
        prim->drawMode |= DRAW_HIDE;
    }
}

// Entity #66. Made by final blueprint, #122. Created in PlayerStepStand.
void EntityPlayerSleepZ(Entity* self) {
    if (PLAYER.step != Player_Stand || PLAYER.step_s != Player_Stand_ChairSit) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(17);
        self->velocityY = FIX(-0.375);
        SetSpeedX(FIX(0.25));
        self->unk5A = 0x50;
        self->palette = 0x819F;
        self->anim = D_800AE294;

        self->posY.i.hi -= 16;
        self->posX.val += self->velocityX << 5;
        self->flags = FLAG_UNK_100000;
        self->facingLeft = 0;
        self->step++;
        break;

    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// dagger thrown when using subweapon
void EntitySubwpnThrownDagger(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 offsetX;
    s16 offsetY;
    s16 angle_a;
    s16 angle_b;
    s16 angle_c;
    s16 angle_d;
    s16 selfY;
    s16 selfX;
    s16 var_s5;
    s32 cosine;
    s32 sine;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(4U, 2);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->facingLeft = PLAYER.facingLeft;
        func_8011A290(self);
        self->hitboxWidth = 4;
        self->hitboxHeight = 2;
        self->hitboxOffX = 4;
        self->hitboxOffY = 0;
        if (!(g_Player.status & PLAYER_STATUS_CROUCH)) {
            self->posY.i.hi -= 9;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1C;
        prim->clut = 0x1AB;
        prim->u0 = prim->u1 = 0x18;
        prim->v0 = prim->v2 = 0x18;
        prim->u2 = prim->u3 = 0x20;
        prim->v1 = prim->v3 = 0;
        prim->priority = PLAYER.zPriority + 2;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;

        prim = prim->next;
        prim->type = PRIM_LINE_G2;
        prim->priority = PLAYER.zPriority + 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
        prim->r0 = 0x7F;
        prim->g0 = 0x3F;
        prim->b0 = 0;
        SetSpeedX(FIX(8));
        PlaySfx(SFX_WEAPON_SWISH_C);
        g_Player.timers[10] = 4;
        self->step++;
        return;
    case 1:
        self->ext.timer.t++;
        if (self->velocityX > 0) {
            var_s5 = 8;
        }
        if (self->velocityX < 0) {
            var_s5 = -8;
        }
        if (self->hitFlags == 1) {
            self->ext.timer.t = 4;
            self->step = 3;
            self->hitboxState = 0;
            return;
        }
        for (i = 0; i < 8; i++) {
            if (self->velocityX > 0) {
                self->posX.i.hi++;
            }
            if (self->velocityX < 0) {
                self->posX.i.hi--;
            }
            CheckCollision(
                self->posX.i.hi + var_s5, self->posY.i.hi, &collider, 0);
            if (self->hitFlags == 2 ||
                collider.effects & (EFFECT_SOLID | EFFECT_UNK_0002)) {
                self->ext.timer.t = 64;
                self->velocityX = -(self->velocityX >> 3);
                self->velocityY = FIX(-2.5);
                self->hitboxState = 0;
                self->posX.i.hi += var_s5;
                CreateEntFactoryFromEntity(self, 10, 0);
                self->posX.i.hi -= var_s5;
                PlaySfx(SFX_UI_TINK);
                self->step++;
                return;
            }
        }
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        offsetX = 12;
        offsetY = 8;
        if (self->facingLeft) {
            offsetX = -offsetX;
            offsetY = -offsetY;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = selfX - offsetX;
        prim->y0 = selfY - 4;
        prim->x1 = selfX + offsetX;
        prim->y1 = selfY - 4;
        prim->x2 = selfX - offsetX;
        prim->y2 = selfY + 4;
        prim->x3 = selfX + offsetX;
        prim->y3 = selfY + 4;
        prim->clut = 0x1AB;
        (g_GameTimer >> 1) & 1; // no-op
        prim->drawMode &= ~DRAW_HIDE;
        prim = prim->next;
        prim->x0 = selfX - offsetY;
        prim->y0 = selfY - 1;
        prim->x1 = selfX - (offsetX * (self->ext.timer.t / 2));
        prim->y1 = selfY - 1;
        prim->drawMode &= ~DRAW_HIDE;
        if (self->step != 1) {
            prim->drawMode |= DRAW_HIDE;
            return;
        }
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.timer.t == 0x20) {
            prim->drawMode |=
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x60;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(0.125);
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        offsetX = 12;
        if (self->facingLeft == 0) {
            angle_a = 0x72E;
            angle_b = 0xD2;
            angle_c = 0x8D2;
            angle_d = -0xD2;

            self->rotZ -= 0x80;
        } else {
            angle_b = 0x72E;
            angle_a = 0xD2;
            // nb: order swapped
            angle_d = 0x8D2;
            angle_c = -0xD2;
            self->rotZ += 0x80;
        }
        angle_a += self->rotZ;
        angle_b += self->rotZ;
        angle_c += self->rotZ;
        angle_d += self->rotZ;
        if (self->facingLeft) {
            offsetX = -offsetX;
        }
        prim = &g_PrimBuf[self->primIndex];
        cosine = (rcos(angle_a) * 0xCA0) >> 0x14;
        sine = -(rsin(angle_a) * 0xCA0) >> 0x14;
        prim->x0 = selfX + cosine;
        prim->y0 = selfY - sine;
        cosine = (rcos(angle_b) * 0xCA0) >> 0x14;
        sine = -(rsin(angle_b) * 0xCA0) >> 0x14;
        prim->x1 = selfX + cosine;
        prim->y1 = selfY - sine;
        cosine = (rcos(angle_c) * 0xCA0) >> 0x14;
        sine = -(rsin(angle_c) * 0xCA0) >> 0x14;
        prim->x2 = selfX + cosine;
        prim->y2 = selfY - sine;
        cosine = (rcos(angle_d) * 0xCA0) >> 0x14;
        sine = -(rsin(angle_d) * 0xCA0) >> 0x14;
        prim->x3 = selfX + cosine;
        prim->y3 = selfY - sine;
        prim->clut = 0x1AB;

        (g_GameTimer >> 1) & 1; // no-op
        if (self->ext.timer.t < 0x21) {
            prim->r0 -= 2;
            prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 = prim->r2 =
                prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 = prim->r0;
        }
        prim->drawMode &= ~DRAW_HIDE;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;
        return;
    case 3:
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// axe thrown when using subweapon
// near-duplicate of RicEntitySubwpnAxe
void EntitySubwpnThrownAxe(Entity* self) {
    s32 sp10;
    s32 sp18;
    Primitive* prevPrim;
    Primitive* prim;
    s32 temp_v1_3;
    s16 var_a1;
    s16 var_s0;
    s16 var_s1;
    s16 var_s2;
    s16 var_s3;
    u16 temp_s4;
    u16 temp_s5;
    u8 temp_v0_4;

    u8* arr0;
    u8* arr1;
    u8* arr2;
    s32 twentyone;

    u8 rVal;
    u8 gVal;
    u8 bVal;

    u16 tempLeft;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 5);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(FIX(-2));
        self->velocityY = FIX(-6);
        tempLeft = self->facingLeft;
        self->ext.axeCrash.unk7C = tempLeft ? 0x400 : 0xC00;
        if (!(g_Player.status & PLAYER_STATUS_CROUCH)) {
            self->posY.i.hi = (u16)self->posY.i.hi - 0xC;
        }
        sp10 = 0;
        prim = &g_PrimBuf[self->primIndex];

        while (prim != NULL) {
            prim->tpage = 0x1C;
            prim->u0 = 0;
            prim->v0 = 0;
            prim->u1 = 0x18;
            prim->v1 = 0;
            prim->u2 = 0;
            prim->v2 = 0x28;
            prim->u3 = 0x18;
            prim->v3 = 0x28;
            prim->priority = PLAYER.zPriority - 2;
            if (sp10 != 0) {
                prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_HIDE | DRAW_COLORS | DRAW_TRANSP;
                self->ext.axeCrash.unk8B[sp10] = 0;
                self->ext.axeCrash.unk8B[sp10 + 4] = 0;
                self->ext.axeCrash.unk8B[sp10 + 8] = 0;
            } else {
                prim->drawMode = DRAW_UNK_100 | DRAW_HIDE;
            }
            prim = prim->next;
            sp10++;
        }
        func_8011A290(self);
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        PlaySfx(SFX_WEAPON_SWISH_C);
        g_Player.timers[10] = 4;
        self->ext.axeCrash.unk98 = 0x7F;
        self->step++;
        break;
    case 1:
        if (self->facingLeft) {
            var_a1 = -0x80;
        } else {
            var_a1 = 0x80;
        }
        self->ext.axeCrash.unk7C = var_a1 + self->ext.axeCrash.unk7C;
        if (!(self->ext.axeCrash.unk7C & 0x3FF)) {
            PlaySfxVolPan(SFX_WEAPON_SWISH_C, self->ext.axeCrash.unk98, 0);
            self->ext.axeCrash.unk98 -= 8;
            if (self->ext.axeCrash.unk98 < 0) {
                self->ext.axeCrash.unk98 = 0;
            }
        }
        self->velocityY += FIX(34.0 / 128);
        if (self->velocityY > FIX(8)) {
            self->velocityY = FIX(8);
        }
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->posY.i.hi < 0x101) {
            if (self->hitFlags == 2) {
                self->velocityY = FIX(-3);
                self->hitboxState = 0;
                self->step = 2;
                self->velocityX = -(self->velocityX / 2);
            }
            break;
        }
        DestroyEntity(self);
        return;
    case 2:
        if (self->facingLeft) {
            var_a1 = 0xC0;
        } else {
            var_a1 = -0xC0;
        }
        self->ext.axeCrash.unk7C = var_a1 + self->ext.axeCrash.unk7C;
        self->velocityY += FIX(18.0 / 128);
        if (self->velocityY > FIX(8)) {
            self->velocityY = FIX(8);
        }
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->posY.i.hi > 0x100) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (self->animFrameDuration == 0) {
        sp18 = self->animFrameIdx;
        self->ext.axeCrash.unk8B[sp18 + 1] = 0;
        self->ext.axeCrash.unk8B[sp18 + 5] = 1;
        self->ext.axeCrash.unk8B[sp18 + 9] = 1;
        sp18++;
        sp18 &= 3;
        self->animFrameIdx = sp18;
        self->animFrameDuration = 2;
    } else {
        self->animFrameDuration--;
    }
    sp10 = 0;
    prim = &g_PrimBuf[self->primIndex];
    prevPrim = prim;
    sp18 = ((g_GameTimer >> 1) & 1) + 0x1AB;
    while (prim != NULL) {
        prim->clut = sp18;
        if (sp10 == 0) {
            if (self->facingLeft != 0) {
                var_s0 = 0x560;
                var_s1 = 0x2A0;
                var_s2 = 0xAA0;
                var_s3 = 0xD60;
            } else {
                var_s1 = 0x560;
                var_s0 = 0x2A0;
                var_s3 = 0xAA0;
                var_s2 = 0xD60;
            }
            var_a1 = self->ext.axeCrash.unk7C;
            temp_s4 = self->posX.i.hi;
            temp_s5 = self->posY.i.hi;
            var_s0 += var_a1;
            var_s1 += var_a1;
            var_s2 += var_a1;
            var_s3 += var_a1;
            twentyone = 21;
            prim->x0 = temp_s4 + (((rcos(var_s0) << 4) * twentyone) >> 0x10);
            prim->y0 = temp_s5 - (((rsin(var_s0) << 4) * twentyone) >> 0x10);
            prim->x1 = temp_s4 + (((rcos(var_s1) << 4) * twentyone) >> 0x10);
            prim->y1 = temp_s5 - (((rsin(var_s1) << 4) * twentyone) >> 0x10);
            prim->x2 = temp_s4 + (((rcos(var_s2) << 4) * twentyone) >> 0x10);
            prim->y2 = temp_s5 - (((rsin(var_s2) << 4) * twentyone) >> 0x10);
            prim->x3 = temp_s4 + (((rcos(var_s3) << 4) * twentyone) >> 0x10);
            prim->y3 = temp_s5 - (((rsin(var_s3) << 4) * twentyone) >> 0x10);
            prim->drawMode &= ~DRAW_HIDE;
        } else if (self->ext.axeCrash.unk8B[sp10 + 4] != 0) {
            if (self->ext.axeCrash.unk8B[sp10 + 8] != 0) {
                self->ext.axeCrash.unk8B[sp10 + 8] = 0;
                prim->x0 = prevPrim->x0;
                prim->y0 = prevPrim->y0;
                prim->x1 = prevPrim->x1;
                prim->y1 = prevPrim->y1;
                prim->x2 = prevPrim->x2;
                prim->y2 = prevPrim->y2;
                prim->x3 = prevPrim->x3;
                prim->y3 = prevPrim->y3;
            }
            temp_v0_4 = self->ext.axeCrash.unk8B[sp10];
            self->ext.axeCrash.unk8B[sp10] = temp_v0_4 + 1;
            temp_v1_3 = temp_v0_4 & 0xFF;
            if ((temp_v1_3) < 0xA) {
                rVal = *(&D_800B0628[temp_v0_4][0]);
                gVal = *(&D_800B0628[temp_v0_4][1]);
                bVal = *(&D_800B0628[temp_v0_4][2]);
                prim->r0 = rVal;
                prim->g0 = gVal;
                prim->b0 = bVal;
                prim->r1 = rVal;
                prim->g1 = gVal;
                prim->b1 = bVal;
                prim->r2 = rVal;
                prim->g2 = gVal;
                prim->b2 = bVal;
                prim->r3 = rVal;
                prim->g3 = gVal;
                prim->b3 = bVal;
                prim->drawMode &= ~DRAW_HIDE;
            } else {
                self->ext.axeCrash.unk8B[sp10 + 4] = 0;
                prim->drawMode |= DRAW_HIDE;
            }
        }
        prim = prim->next;
        sp10++;
    }
}

// Same RIC function is func_801682B4
s32 CheckHolyWaterCollision(s32 baseY, s32 baseX) {
    s16 x;
    s16 y;
    Collider res1;
    Collider res2;
    s16 colRes1;
    s16 colRes2;

    const u32 colFullSet =
        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_1000 |
         EFFECT_UNK_0800 | EFFECT_SOLID);
    const u32 colSetNo800 = (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                             EFFECT_UNK_2000 | EFFECT_UNK_1000 | EFFECT_SOLID);
    const u32 colSet1 = (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
    const u32 colSet2 = (EFFECT_UNK_8000 | EFFECT_SOLID);
    x = baseX + g_CurrentEntity->posX.i.hi;
    y = baseY + g_CurrentEntity->posY.i.hi;

    CheckCollision(x, y, &res1, 0);
    colRes1 = res1.effects & colFullSet;
    CheckCollision(x, (s16)(y - 1 + res1.unk18), &res2, 0);
    y = baseY + (g_CurrentEntity->posY.i.hi + res1.unk18);

    if ((colRes1 & colSet1) == EFFECT_SOLID ||
        (colRes1 & colSet1) == (EFFECT_UNK_0800 | EFFECT_SOLID)) {
        colRes2 = res2.effects & colSetNo800;
        if (!((s16)res2.effects & EFFECT_SOLID)) {
            g_CurrentEntity->posY.i.hi = y;
            return 1;
        }
        if ((res2.effects & colSet2) == colSet2) {
            g_CurrentEntity->posY.i.hi = y + (s16)(res2.unk18 - 1);
            return colRes2;
        }
    } else if ((colRes1 & colSet2) == colSet2) {
        g_CurrentEntity->posY.i.hi = y;
        return colRes1 & colSetNo800;
    }
    return 0;
}

s32 func_80125B6C(s16 arg0, s16 arg1) {
    Collider collider;
    s16 var_a1;

    if (g_CurrentEntity->velocityX == 0) {
        return 0;
    }

    CheckCollision(g_CurrentEntity->posX.i.hi + arg1,
                   g_CurrentEntity->posY.i.hi + arg0, &collider, 0);
    if (g_CurrentEntity->velocityX > 0) {
        var_a1 = collider.unk14;
    } else {
        var_a1 = collider.unk1C;
    }

    if (collider.effects & EFFECT_UNK_0002) {
        g_CurrentEntity->posX.i.lo = 0;
        g_CurrentEntity->posX.i.hi += var_a1;
        return 2;
    }

    return 0;
}

void EntityHolyWater(Entity* self) {
    s16 xOffset;
    s32 collisionFlags = 0;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = ANIMSET_DRA(9);
        self->animCurFrame = 0x1D;
        self->zPriority = PLAYER.zPriority - 2;
        self->posY.i.hi += 8;
        SetSpeedX(FIX(1.25));
        self->velocityY = FIX(-3.125);
        func_8011A290(self);
        self->hitboxWidth = self->hitboxHeight = 4;
        g_Player.timers[10] = 4;
        self->step++;
        break;

    case 1:
        self->posY.val += self->velocityY;
        if (self->velocityY < FIX(4)) {
            self->velocityY += FIX(28.0 / 128);
        }

        collisionFlags = CheckHolyWaterCollision(0, 0);
        self->posX.val += self->velocityX;
        xOffset = 4;
        if (self->velocityX < 0) {
            xOffset = -xOffset;
        }
        collisionFlags |= func_80125B6C(-7, xOffset);

        if (collisionFlags & 2) {
            collisionFlags = 1;
        }

        if (collisionFlags & 1) {
            PlaySfx(SFX_FM_EXPLODE_GLASS_ECHO);
            // Factory 59 has child 40, EntityHolyWaterBreakGlass
            CreateEntFactoryFromEntity(self, FACTORY(59, 0), 0);
            self->animSet = ANIMSET_DRA(0);
            self->ext.holywater.timer = 16;
            self->step = 2;
        }
        break;

    case 2:
        if (!(self->ext.holywater.timer & 3)) {
            // Factory 28 has child 23, EntityHolyWaterFlame
            CreateEntFactoryFromEntity(
                self, FACTORY(28, D_8013841C), self->ext.holywater.unkB2 << 9);
            D_8013841C++;
        }
        if (--self->ext.holywater.timer == 0) {
            self->ext.holywater.timer = 4;
            self->step++;
        }
        break;

    case 3:
        if (--self->ext.holywater.timer == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// Glass breaking effect for holy water. Duplicate of RIC func_80167A70.
void EntityHolyWaterBreakGlass(Entity* self) {
    Point16 sp10[8];
    Primitive* prim;
    FakePrim* fakeprim;
    s32 velX;
    s32 i;
    u16 posY;
    u16 posX;
    u8 arrIndex;
    u8 randbit;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            if (i < 8) {
                fakeprim = (FakePrim*)prim;
                fakeprim->x0 = posX;
                fakeprim->posX.i.hi = posX;
                sp10[i].x = posX;
                fakeprim->y0 = posY;
                fakeprim->posY.i.hi = posY;
                sp10[i].y = posY;
                // Random velocity from 0.25 to 0.5
                velX = (rand() & 0x3FFF) + FIX(0.25);
                fakeprim->velocityX.val = velX;
                if (i & 1) {
                    fakeprim->velocityX.val = -velX;
                }
                fakeprim->velocityY.val = -((rand() * 2) + FIX(2.5));
                fakeprim->drawMode = DRAW_HIDE | DRAW_UNK02;
                fakeprim->type = PRIM_TILE;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 =
                    (rand() & 0xF) | 0x30;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = rand() | 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 =
                    (rand() & 0x1F) + 0x30;
                randbit = rand() & 1;
                prim->drawMode =
                    !(randbit) ? (DRAW_COLORS | DRAW_UNK02)
                               : (DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                  DRAW_UNK02 | DRAW_TRANSP);
                posX = sp10[i - 8].x;
                posY = sp10[i - 8].y;
                arrIndex = i & 3;
                prim->u0 = arrIndex;
                prim->x0 = posX + D_800B0658[arrIndex][0];
                prim->y0 = posY + D_800B0658[arrIndex][1];
                prim->x1 = posX + D_800B0658[arrIndex][2];
                prim->y1 = posY + D_800B0658[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_800B0658[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_800B0658[arrIndex][5];
                prim->type = PRIM_G4;
                prim->priority = PLAYER.zPriority + 2;
            }
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->ext.timer.t = 20;
        self->step++;
        return;

    case 1:
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            if (i < 8) {
                fakeprim = (FakePrim*)prim;
                fakeprim->posX.i.hi = fakeprim->x0;
                fakeprim->posY.i.hi = fakeprim->y0;
                fakeprim->posX.val += fakeprim->velocityX.val;
                fakeprim->posY.val += fakeprim->velocityY.val;
                fakeprim->velocityY.val += FIX(36.0 / 128);
                sp10[i].x = fakeprim->posX.i.hi;
                sp10[i].y = fakeprim->posY.i.hi;
                fakeprim->x0 = fakeprim->posX.i.hi;
                fakeprim->y0 = fakeprim->posY.i.hi;
            } else {
                posX = sp10[i - 8].x;
                posY = sp10[i - 8].y;
                arrIndex = prim->u0;
                prim->x0 = posX + D_800B0658[arrIndex][0];
                prim->y0 = posY + D_800B0658[arrIndex][1];
                prim->x1 = posX + D_800B0658[arrIndex][2];
                prim->y1 = posY + D_800B0658[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_800B0658[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_800B0658[arrIndex][5];
            }
        }
    }
}

// green flame when holy water explodes
void EntityHolyWaterFlame(Entity* self) {
    s16 sp10[5];
    s16 sp20[5];
    s16 pad[2];
    Primitive* prim;
    s16 temp_v0_4;
    s16 angleTemp;
    s32 angle;
    s32 temp_v0;
    s32 i;
    s32 hex80;
    u8 randR;
    u8 randG;
    u8 randB;
    u8 primUBase;
    u8 primVBase;

    s16* primYPtr;

    primUBase = D_800B0688[(g_GameTimer & 7)].x;
    primVBase = D_800B0688[(g_GameTimer & 7)].y;
    switch (self->step) {
    case 0:
        randR = (rand() & 0x1F) | 0x40;
        randG = (rand() & 0x1F) | 0x80;
        randB = (rand() & 0x1F) | 0x60;
        self->primIndex = AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = randR;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = randG;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = randB;
            prim->clut = 0x1B2;
            prim->tpage = 0x1A;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP |
                             DRAW_UNK02 | DRAW_COLORS | DRAW_HIDE;
            prim = prim->next;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        func_8011A290(self);
        self->hitboxWidth = 4;
        self->posY.i.hi = self->posY.i.hi - 0xA;
        CreateEntFactoryFromEntity(self, FACTORY(4, 7), 0);
        self->ext.holywater.timer = 0x50;
        self->posY.i.hi = self->posY.i.hi + 0xA;
        self->ext.holywater.unk80 = (rand() & 0xF) + 0x12;
        self->step += 1;
        return;
    case 1:
        angleTemp = self->ext.holywater.angle;
        self->ext.holywater.angle += 0x180;
        angle = angleTemp;
        for (i = 0; i < 4; i++) {
            sp10[i] = self->posX.i.hi + (rsin(angle) >> 0xA);
            angle += 0x400;
        }
        sp10[0] = self->posX.i.hi;
        sp10[4] = self->posX.i.hi;
        temp_v0_4 =
            (rsin((s16)((self->ext.holywater.timer * 64) + 0x800)) >> 8) +
            self->ext.holywater.unk80;
        sp20[0] = self->posY.i.hi - temp_v0_4;
        sp20[4] = self->posY.i.hi;
        sp20[2] = (sp20[0] + sp20[4]) / 2;
        sp20[1] = (sp20[0] + sp20[2]) / 2;
        sp20[3] = (sp20[2] + sp20[4]) / 2;
        prim = &g_PrimBuf[self->primIndex];
        if (self->ext.holywater.timer & 3) {
            self->hitboxState = 0;
        } else {
            self->hitboxState = 2;
        }
        if (--self->ext.holywater.timer < 0x11) {
            DestroyEntity(self);
            return;
        }
        i = 0;
        while (prim != NULL) {
            if (self->ext.holywater.timer < 0x29) {
                if (prim->g0 >= 17) {
                    prim->g0 -= 5;
                }
                if (prim->b0 >= 17) {
                    prim->b0 -= 5;
                }
                if (prim->r0 >= 17) {
                    prim->r0 -= 5;
                }
                prim->g1 = prim->g2 = prim->g3 = prim->g0;
                prim->r1 = prim->r2 = prim->r3 = prim->r0;
                prim->b1 = prim->b2 = prim->b3 = prim->b0;
            }
            prim->x0 = sp10[i] - 8;
            prim->x1 = sp10[i] + 8;
            prim->y0 = sp10[i + 8];
            prim->y1 = sp10[i + 8];
            prim->x2 = sp10[i + 1] - 8;
            prim->x3 = sp10[i + 1] + 8;
            prim->y2 = sp20[i + 1];
            prim->y3 = sp20[i + 1];
            prim->drawMode &= ~DRAW_HIDE;
            hex80 = 0x80;
            prim->u0 = prim->u1 = primUBase - ((i * 7) + hex80);
            prim->u2 = prim->u3 = primUBase - (((i + 1) * 7) + hex80);
            prim->v0 = prim->v2 = primVBase - hex80;
            prim->v1 = prim->v3 = primVBase - 0x70;
            i++;
            if ((sp20[4] - sp20[0]) < 7) {
                prim->drawMode |= DRAW_HIDE;
            }
            prim = prim->next;
        }
        self->hitboxHeight = temp_v0_4 >> 1;
        self->hitboxOffY = (-temp_v0_4 >> 1);
    }
}
// cross subweapon crash (full effect with all parts)
void EntitySubwpnCrashCross(Entity* self) {
    Primitive* prim;
    s16 right;
    s16 left;
    s32 var_v0;
    u16 temp_three;
    s8 temp_one;
    u16 three = 3;
    u32 one = 1;

    func_8010DFF0(1, 1);
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS;
        self->posY.i.hi = 0x78;
        self->ext.crashcross.unk80 = 1;
        self->zPriority = 0xC2;
        func_8011A290(self);
        LoadImage(&D_800B0788, D_800B06C8);
        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = prim->u2 = 1;
        prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
        prim->u1 = prim->u3 = 0x30;
        prim->b3 = 0x80;
        prim->tpage = 0x11C;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        PlaySfx(SFX_CRASH_CROSS);
        PlaySfx(SFX_TELEPORT_BANG_B);
        self->step += 1;
        g_Player.timers[12] = 4;
        break;
    case 1:
        self->ext.crashcross.unk7E = three + self->ext.crashcross.unk7E;
        self->ext.crashcross.unk82 += three * 2;
        if ((u8)self->ext.crashcross.unk7E >= 0x70U) {
            CreateEntFactoryFromEntity(self, 7, self->ext.factory.unkB2 << 9);
            CreateEntFactoryFromEntity(self, 8, 0);
            self->step += 1;
        }
        break;
    case 2:
        if (g_Timer & 1) {
            self->ext.crashcross.unk80 += one * 2;
            self->ext.crashcross.unk7C = one + self->ext.crashcross.unk7C;
            if (self->ext.crashcross.unk80 >= 0x2CU) {
                self->ext.crashcross.unk84 = 0x80;
                self->step += 1;
            }
        }
        break;
    case 3:
        if (--self->ext.crashcross.unk84 == 0) {
            left = self->posX.i.hi - self->ext.crashcross.unk7C;
            ;
            if (left < 0) {
                left = 0;
            }
            right = self->posX.i.hi + self->ext.crashcross.unk7C;
            if (right >= 0x100) {
                right = 0xFF;
            }
            self->step += 1;
            PlaySfx(SFX_WEAPON_APPEAR);
        }
        break;
    case 4:
        // this is so stupid
        temp_one = one;
        temp_three = temp_one * 2;
        temp_three |= temp_one;
        var_v0 = self->posX.i.hi - 0x80;
        self->ext.crashcross.unk7C =
            (((temp_three) * ((s16)(var_v0 > 0 ? var_v0 : -var_v0) + 0x80)) /
             112) +
            self->ext.crashcross.unk7C;

        left = self->posX.i.hi - self->ext.crashcross.unk7C;
        right = self->posX.i.hi + self->ext.crashcross.unk7C;
        if (right > 0x180 && left < -0x80) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    self->hitboxOffY = 0;
    self->hitboxHeight = self->ext.crashcross.unk7E;
    if (self->step == 4) {
        self->hitboxWidth = ((right - left) >> 1);
        self->hitboxOffX = ((left + right) >> 1) - self->posX.i.hi;
    } else {
        self->hitboxOffX = 0;
        self->hitboxWidth = self->ext.crashcross.unk7C;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - self->ext.crashcross.unk7C;
    prim->y1 = prim->y0 = self->posY.i.hi - self->ext.crashcross.unk7E;
    prim->x1 = prim->x3 = prim->x0 + self->ext.crashcross.unk80;
    prim->y2 = prim->y3 = prim->y0 + self->ext.crashcross.unk82;

    if (self->step == 4) {
        if (prim->b3 < 0xF8) {
            prim->b3 += 4;
        }
        prim->x0 = prim->x2 = left;
        prim->x1 = prim->x3 = right;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
    }
    prim->priority = self->zPriority;
    return;
}

// rising blue particles from cross crash
void EntitySubwpnCrashCrossParticles(Entity* self) {
    Primitive* prim;
    u16 rand63;

    if (self->step == 0) {
        self->primIndex = AllocPrimitives(PRIM_GT4, 64);
        if (self->primIndex != -1) {
            self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
            // entity lives for 192 frames
            self->ext.timer.t = 192;
            self->step++;
            return;
        }
        DestroyEntity(self);
        return;
    }
    // This is some kind of time to live, since it decrements and if 0 gets
    // destroyed.
    if (--self->ext.timer.t == 0) {
        DestroyEntity(self);
        return;
    }
    // On every third frame, as long as we have over 9 frames left alive
    if ((self->ext.timer.t >= 9) && !(self->ext.timer.t & 3)) {
        // iterate through primtives until we find one where r0 == 0, and set to
        // 1
        for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
             prim = prim->next) {
            if (prim->r0 == 0) {
                prim->r0 = 1;
                prim->r1 = 0;
                break;
            }
        }
    }

    for (prim = &g_PrimBuf[self->primIndex]; prim != NULL; prim = prim->next) {
        // for any of those prims with nonzero r0 values,
        if (prim->r0 != 0) {
            // r1 acts as a flag to show whether this has happened.
            if (prim->r1 == 0) {
                rand63 = rand() & 0x3F; // random integer 0-63
                prim->g0 = (rand() % 237) + 9;
                prim->g1 = -0x10 - (rand() & 0x20);
                prim->clut = 0x1B0;
                prim->tpage = 0x1A;
                prim->b0 = 0;
                prim->b1 = 0;
                prim->priority = (rand63 + PLAYER.zPriority) - 0x20;
                prim->drawMode = DRAW_DEFAULT;
                prim->g3 = (rand63 >> 2) + 4; // rand15 + 4 means 4 to 19
                prim->r1++;
            } else {
                prim->g1 -= prim->g3;
                if (((u8)prim->b0 >= 6U) || ((u8)prim->g1 < 0x18U)) {
                    prim->drawMode = DRAW_HIDE;
                    prim->r0 = 0;
                }
            }
            if (prim->r0 != 0) {
                func_80119E78(prim, prim->g0, prim->g1);
            }
        }
    }
}

void EntityHellfireHandler(Entity* self) {
    Primitive* prim;
    u16 selfPosX;
    s16 selfPosY;
    // These are probably adjustable variables but for now we don't
    // know what they are for so we just name them for their values
    s16 sixteen = 16;
    s16 four = 4;

    if (PLAYER.step != Player_SpellHellfire) {
        DestroyEntity(self);
        return;
    }

    FntPrint("light_timer:%02x\n", self->ext.hellfireHandler.unk80);
    self->posX.i.hi = PLAYER.posX.i.hi;
    selfPosX = self->posX.i.hi;
    switch (self->step) {
    case 0:
        g_Player.unk5C = 0;
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk5C = -1;
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS |
                      FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        self->posY.i.hi = 120;
        // I think this is to make the yellow laser beam?
        // it ends up looking like the library card effect.
        LoadImage(&D_800B0788, D_800B06C8);
        LoadImage(&D_800B0790, D_800B0728);
        prim = &g_PrimBuf[self->primIndex];
        prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
        prim->u0 = prim->u2 = 1;
        prim->u1 = prim->u3 = 0x30;
        prim->b3 = 0x80;
        prim->tpage = 0x11C;
        prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                         DRAW_TPAGE | DRAW_TRANSP;
        prim->priority = self->zPriority = 0x1C0;
        PlaySfx(SFX_TELEPORT_BANG_B);
        self->step++;
        break;
    case 1:
        self->ext.hellfireHandler.unk7E += sixteen;
        if (self->ext.hellfireHandler.unk7E >= 0x80) {
            self->step++;
        }
        break;
    case 2:
        self->ext.hellfireHandler.unk7C += four;
        if (self->ext.hellfireHandler.unk7C >= 0x16) {
            self->ext.hellfireHandler.unk80 = 0x20;
            self->step++;
        }
        break;
    case 3:
        if (--self->ext.hellfireHandler.unk80 == 0) {
            PLAYER.palette = 0x810D;
            self->step++;
        }
        break;
    case 4:
        PLAYER.palette = 0x810D;
        self->ext.hellfireHandler.unk7C -= four * 2;
        if (self->ext.hellfireHandler.unk7C < 0) {
            self->ext.hellfireHandler.unk80 = 0x2A;
            self->step++;
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode |= DRAW_HIDE;
            g_Player.unk5C = 1;
        }
        break;
    case 5:
        PLAYER.palette = 0x810D;
        if (self->ext.hellfireHandler.unk80 == 0x10) {
            CreateEntFactoryFromEntity(self, 38, 0);
        }
        if (--self->ext.hellfireHandler.unk80 == 0) {
            self->ext.hellfireHandler.unk7C = 0;
            self->step++;
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode &= ~DRAW_HIDE;
        }
        if (self->ext.hellfireHandler.unk80 == 2) {
            g_Player.unk5C = 2;
        }
        break;
    case 6:
        PLAYER.palette = 0x8100;
        self->ext.hellfireHandler.unk7C += four;
        if (self->ext.hellfireHandler.unk7C >= 0x16) {
            self->ext.hellfireHandler.unk80 = 0x60;
            self->step++;
        }
        break;
    case 7:
        if (self->ext.hellfireHandler.unk80 == 0x50) {
            g_Player.unk5C = 3;
        }
        if (self->ext.hellfireHandler.unk80 == 0x30) {
            // When you press up during hellfire, you get different fireballs.
            if (g_Player.padPressed & PAD_UP) {
                // Blueprint 35 makes child 27, the big black fireballs
                CreateEntFactoryFromEntity(self, 35, 0);
            } else {
                // Blueprint 34 makes child 26, the small, normal fireballs
                CreateEntFactoryFromEntity(self, 34, 0);
            }
        }
        if (self->ext.hellfireHandler.unk80 == 0x50) {
            CreateEntFactoryFromEntity(self, FACTORY(4, 10), 0);
        }
        if (self->ext.hellfireHandler.unk80 < 0x48) {
            self->ext.hellfireHandler.unk7C -= four;
            if (self->ext.hellfireHandler.unk7C < 0) {
                self->ext.hellfireHandler.unk7C = 0;
            }
        }
        if (--self->ext.hellfireHandler.unk80 == 0x28) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->posY.i.hi = 0x78;
    selfPosY = 0x78;
    prim = &g_PrimBuf[self->primIndex];
    if (g_GameTimer & 1) {
        prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
    } else {
        prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xFC;
    }
    prim->x0 = prim->x2 = selfPosX - self->ext.hellfireHandler.unk7C;
    prim->y1 = prim->y0 = selfPosY - self->ext.hellfireHandler.unk7E;
    prim->x1 = prim->x3 = selfPosX + self->ext.hellfireHandler.unk7C;
    prim->y2 = prim->y3 = selfPosY + self->ext.hellfireHandler.unk7E;
    if (self->step == 3) {
        if (prim->b3 < 0xF8) {
            prim->b3 += 4;
        }
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3;
    }
    if (self->step == 7) {
        if (prim->b3 >= 0x21) {
            prim->b3 -= 0x20;
        }
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3;
    }
    return;
}

// The fireball produced by Hellfire, when you do NOT press up
void EntityHellfireNormalFireball(Entity* entity) {
    switch (entity->step) {
    case 0:
        if (entity->params == 0) {
            PlaySfx(SFX_FIREBALL_SHOT_A);
        }
        entity->flags = FLAG_UNK_100000 | FLAG_POS_CAMERA_LOCKED;
        entity->animSet = ANIMSET_DRA(9);
        entity->anim = D_800B0798;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(D_800B0830[entity->params]);
        entity->velocityY = D_800B083C[entity->params];
        entity->ext.timer.t = 0x14;
        func_8011A328(entity, 2);
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 4;
        entity->step++;
        break;

    case 1:
        if (entity->hitFlags == 0) {
            entity->ext.timer.t--;
            if ((entity->ext.timer.t) == 0) {
                entity->step++;
            }
            entity->posX.val += entity->velocityX;
            entity->posY.val += entity->velocityY;
            break;
        }
        DestroyEntity(entity);
        break;

    case 2:
        if (entity->hitFlags != 0) {
            DestroyEntity(entity);
            break;
        }
        entity->posX.val += entity->velocityX;
        break;
    }
}

// Entity ID 45. Created by factory blueprint 81.
// That blueprint is used in ControlBatForm, when step_s is 4.
// Also, when bat familiar shoots a fireball, the blueprint
// is used in UpdateBatAttackMode.

void EntityBatFireball(Entity* self) {
    // This is a 1 when a bat familiar is shooting, and a 0
    // when the player (in bat form) is shooting the fireball.
    // Appears to have no impact on the behavior of this function.
    s8 params = (self->params >> 8) & 0x7F;

    switch (self->step) {
    case 0:
        PlaySfx(SFX_QUICK_STUTTER_EXPLODE_A);
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        self->animSet = 9;
        self->anim = D_800B0798;
        self->zPriority = PLAYER.zPriority - 2;

        // Wow, this is weird logic! But it's in the assembly.
        if (params == 0) {
            self->facingLeft = (PLAYER.facingLeft + 1) & 1;
        }
        self->facingLeft = (PLAYER.facingLeft + 1) & 1;

        SetSpeedX(FIX(-3.5));
        self->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        // Initial fireball size is 0x40 by 0x40
        self->rotX = self->rotY = 0x40;
        self->posX.val += self->velocityX * 2;
        self->posY.i.hi -= 4;
        func_8011A328(self, 9);
        self->hitboxWidth = 4;
        self->hitboxHeight = 8;
        g_Player.timers[10] = 4;
        self->step++;
        break;
    case 1:
        // Once the fireball hits something, destroy it.
        if (self->hitFlags != 0) {
            DestroyEntity(self);
            return;
        }
        self->posX.val += self->velocityX;
        // Much like the wing smash, these rot values are actually the size.
        // After shooting, the fireballs grow until they are 0x100 in size
        self->rotX += 0x10;
        self->rotY += 0x10;
        if (self->rotY >= 0x101) {
            self->rotY = 0x100;
        }
        if (self->rotX >= 0x181) {
            self->rotX = 0x180;
        }
    }
    return;
}

// Produced in Hellfire when you press UP during the casting
void EntityHellfireBigFireball(Entity* entity) {
    switch (entity->step) {
    case 0:
        if (entity->params != 0) {
            PlaySfx(SFX_QUICK_STUTTER_EXPLODE_B);
        }

        entity->flags = FLAG_UNK_100000 | FLAG_POS_CAMERA_LOCKED;

        if (entity->params != 0) {
            entity->posY.i.hi = entity->posY.i.hi + 16;
        } else {
            entity->posY.i.hi = entity->posY.i.hi - 4;
        }

        entity->animSet = ANIMSET_DRA(9);
        entity->rotZ = 0;
        entity->anim = D_800B07C8;
        entity->drawFlags |= FLAG_DRAW_ROTZ;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(-0x10);
        func_8011A328(entity, 2);
        entity->hitboxWidth = 8;
        entity->hitboxHeight = 8;
        entity->step++;
        break;

    case 1:
        if (entity->animFrameIdx >= 23) {
            if (!(g_GameTimer & 3)) {
                entity->rotZ += 0x400;
            }
            if (entity->velocityX < 0) {
                entity->velocityX -= FIX(0.09375);
            } else {
                entity->velocityX += FIX(0.09375);
            }
            if (!(g_GameTimer & 1) && (rand() & 1)) {
                CreateEntFactoryFromEntity(entity, FACTORY(36, 1), 0);
            }
            entity->posX.val += entity->velocityX;
            entity->posY.val += entity->velocityY;
        }
        break;
    }
}

// circle expands out of player
void EntityExpandingCircle(Entity* self) {
    Primitive* prim;

    if (PLAYER.facingLeft == 0) {
        self->posX.i.hi = PLAYER.posX.i.hi - 10;
    } else {
        self->posX.i.hi = PLAYER.posX.i.hi + 10;
    }
    self->posY.i.hi = PLAYER.posY.i.hi + 2;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.circleExpand.width = 22;
        self->ext.circleExpand.height = 26;
        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = prim->u2 = 64;
        prim->u1 = prim->u3 = 127;
        prim->v0 = prim->v1 = 192;
        prim->v2 = prim->v3 = 255;
        PRED(prim) = 128;
        PGRN(prim) = 128;
        PBLU(prim) = 64;

        prim->tpage = 0x1A;
        prim->clut = 0x15F;
        prim->priority = PLAYER.zPriority + 1;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        self->flags =
            FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->step++;
        break;

    case 1:
        self->ext.circleExpand.width += 2;
        self->ext.circleExpand.height += 2;
        if (self->ext.circleExpand.width > 56) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y0 = self->posY.i.hi - self->ext.circleExpand.height;

    prim->x1 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y1 = self->posY.i.hi - self->ext.circleExpand.height;

    prim->x2 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y2 = self->posY.i.hi + self->ext.circleExpand.height;

    prim->x3 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y3 = self->posY.i.hi + self->ext.circleExpand.height;

    if (self->ext.circleExpand.width > 40) {
        prim->r3 -= 12;
        prim->g3 -= 12;
        prim->b3 -= 6;
        prim->r0 = prim->r1 = prim->r2 = prim->r3;
        prim->g0 = prim->g1 = prim->g2 = prim->g3;
        prim->b0 = prim->b1 = prim->b2 = prim->b3;
    }
}

void func_80127CC8(Entity* entity) {
    Primitive* prim;
    s32 ret;

    if (PLAYER.step != 34) {
        DestroyEntity(entity);
        return;
    }

    entity->posX.i.hi = PLAYER.posX.i.hi;

    switch (entity->step) {
    case 0:
        ret = AllocPrimitives(PRIM_G4, 1);
        entity->primIndex = ret;

        if (ret == -1) {
            DestroyEntity(entity);
            g_Player.unk5C = -1;
            return;
        }

        entity->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                        FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[entity->primIndex];
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = 192;
        prim->g0 = prim->g1 = prim->g2 = prim->g3 = 64;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 64;
        prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE |
                         DRAW_COLORS | DRAW_TRANSP;
        entity->zPriority = 0x1C0;
        prim->priority = 0x1C0;
        entity->step++;
        break;

    case 1:
        if (entity->ext.timer.t++ >= 0xE) {
            DestroyEntity(entity);
            return;
        }
    }
    prim = &g_PrimBuf[entity->primIndex];
    prim->x0 = prim->x2 = entity->posX.i.hi - 3;
    prim->y1 = prim->y0 = 0;
    prim->x1 = prim->x3 = entity->posX.i.hi + 3;
    prim->y2 = prim->y3 = 240;

    if (g_GameTimer & 1) {
        prim->drawMode = prim->drawMode | DRAW_HIDE;
    } else {
        prim->drawMode = prim->drawMode & ~DRAW_HIDE;
    }
}

// These are a pair of helper functions used for the rebound stone rebounding.
// No clear reason why the first one puts the first line outside the
// if statement.

void ReboundStoneBounce1(s16 bounceAngle) {
    g_CurrentEntity->ext.reboundStone.stoneAngle =
        (bounceAngle * 2) - g_CurrentEntity->ext.reboundStone.stoneAngle;
    if (g_CurrentEntity->ext.reboundStone.unk82 == 0) {
        g_CurrentEntity->ext.reboundStone.unk80++;
        g_CurrentEntity->ext.reboundStone.unk82++;
    }
}

void ReboundStoneBounce2(s16 bounceAngle) {
    if (g_CurrentEntity->ext.reboundStone.unk82 == 0) {
        g_CurrentEntity->ext.reboundStone.stoneAngle =
            (bounceAngle * 2) - g_CurrentEntity->ext.reboundStone.stoneAngle;
        g_CurrentEntity->ext.reboundStone.unk80++;
        g_CurrentEntity->ext.reboundStone.unk82++;
    }
}
// Entity ID 20. Created by blueprint 24. This comes from BlueprintNum for
// the rebound stone SubweaponDef.
void EntitySubwpnReboundStone(Entity* self) {
    Collider collider;
    u16 playerX;
    u16 playerY;
    PrimLineG2* prim;
    s32 colliderFlags;
    s32 i;
    s32 deltaX;
    s32 deltaY;
    s32 currX;
    s32 currY;

    s32 speed = 0x400;
    s32 facingLeft;

    self->ext.reboundStone.unk82 = 0;
    playerX = self->posX.i.hi;
    playerY = self->posY.i.hi;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_LINE_G2, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        for (i = 0, prim = &g_PrimBuf[self->primIndex]; prim != NULL;
             prim = prim->next, i++) {
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                0xFF;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            if (i != 0) {
                prim->drawMode |= DRAW_HIDE;
            }
            prim->x0 = prim->x1 = playerX;
            prim->y0 = prim->y1 = playerY;
            prim->timer = 0x14;
        }
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->zPriority = PLAYER.zPriority + 2;

        facingLeft = PLAYER.facingLeft;
        self->ext.reboundStone.stoneAngle = facingLeft == 0 ? 0xE80 : 0x980;
        self->ext.reboundStone.stoneAngle += (rand() & 0x7F) - 0x40;

        self->ext.reboundStone.lifeTimer = 0x40;
        func_8011A290(self);
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        g_Player.timers[10] = 4;
        CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->ext.reboundStone.unk84 = 4;
        }
        self->step += 1;
        PlaySfx(SFX_WEAPON_SWISH_C);
        break;

    case 1:
        deltaX = rcos(self->ext.reboundStone.stoneAngle) * 0x10;
        deltaY = -rsin(self->ext.reboundStone.stoneAngle) * 0x10;
        currX = self->posX.val;
        currY = self->posY.val;
        if (self->ext.reboundStone.unk84 == 0) {
            for (i = 0; i < 6; i++) {
                CheckCollision(
                    FIX_TO_I(currX), FIX_TO_I(currY + deltaY), &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    colliderFlags =
                        collider.effects &
                        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                         EFFECT_UNK_1000 | EFFECT_UNK_0800);
                    if (deltaY > 0) {
                        if ((colliderFlags == 0) ||
                            (collider.effects & EFFECT_UNK_0800)) {
                            ReboundStoneBounce1(0x800);
                        }
                        if (colliderFlags == EFFECT_UNK_8000) {
                            ReboundStoneBounce2(0x200);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x12E);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xA0);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0x600);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x6D2);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x760);
                        }
                    }
                    if (deltaY < 0) {
                        if ((colliderFlags == 0) ||
                            (colliderFlags & EFFECT_UNK_8000)) {
                            ReboundStoneBounce1(0x800);
                        }
                        if (colliderFlags == EFFECT_UNK_0800) {
                            ReboundStoneBounce2(0xE00);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0xED2);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xF60);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0xA00);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x92E);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x8A0);
                        }
                    }
                }
                CheckCollision(
                    FIX_TO_I(currX + deltaX), FIX_TO_I(currY), &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    colliderFlags =
                        collider.effects &
                        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                         EFFECT_UNK_1000 | EFFECT_UNK_0800);
                    // Cases when traveling right
                    if (deltaX > 0) {
                        if ((colliderFlags == 0) ||
                            TEST_BITS(collider.effects, 0x4800) ||
                            TEST_BITS(collider.effects, 0xC000)) {
                            ReboundStoneBounce1(0x400);
                        }
                        if (colliderFlags == EFFECT_UNK_0800) {
                            ReboundStoneBounce2(0xE00);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0xED2);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xF60);
                        }
                        if (colliderFlags == EFFECT_UNK_8000) {
                            ReboundStoneBounce2(0x200);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x12E);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xA0);
                        }
                    }
                    // Cases when traveling left
                    if (deltaX < 0) {
                        if ((colliderFlags == 0) ||
                            ((colliderFlags & 0x4800) == 0x800) ||
                            ((colliderFlags & 0xC000) == 0x8000)) {
                            ReboundStoneBounce1(0x400);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0xA00);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x92E);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x8A0);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0x600);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x6D2);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x760);
                        }
                    }
                }
                currX += deltaX;
                if (self->ext.reboundStone.unk82 != 0) {
                    goto block_93;
                }
                currY += deltaY;
            }
        } else {
            self->ext.reboundStone.unk84--;
        }
        if (self->ext.reboundStone.unk82 != 0) {
        block_93:
            CreateEntFactoryFromEntity(self, 10, 0);
            PlaySfx(SFX_UI_TINK);
        }
        if (self->posX.i.hi < -0x40 || self->posX.i.hi > 0x140 ||
            self->posY.i.hi < -0x40 || self->posY.i.hi > 0x140 ||
            self->ext.reboundStone.unk80 == 15) {
            self->step = 2;
        } else {
            deltaX =
                ((rcos(self->ext.reboundStone.stoneAngle) << 4) * speed) >> 8;
            self->posX.val += deltaX;
            deltaY =
                -((rsin(self->ext.reboundStone.stoneAngle) << 4) * speed) >> 8;
            self->posY.val += deltaY;
        }
        break;
    case 2:
        if (--self->ext.reboundStone.lifeTimer == 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.reboundStone.lifeTimer == 0x20) {
            self->hitboxState = 0;
        }
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->timer = 0;
            prim = prim->next;
        }
        break;
    }

    i = 0;
    prim = &g_PrimBuf[self->primIndex];
    colliderFlags = self->step == 2 ? 4 : 2; // reused var, not colliderFlags
    // cleaner to use previous 3 lines than to put them in the for's initializer
    for (; prim != NULL; i++, prim = prim->next) {
        if (self->ext.reboundStone.unk82 != 0) {
            if (i == self->ext.reboundStone.unk80) {
                prim->x0 = playerX;
                prim->y0 = playerY;
                prim->drawMode &= ~DRAW_HIDE;
                // unusual nesting of the same condition
                if (i == self->ext.reboundStone.unk80) {
                    prim->x1 = self->posX.i.hi;
                    prim->y1 = self->posY.i.hi;
                }
            }
        } else if (i == self->ext.reboundStone.unk80) {
            prim->x1 = self->posX.i.hi;
            prim->y1 = self->posY.i.hi;
        }
        if (!(prim->drawMode & DRAW_HIDE)) {
            if (prim->timer != 0) {
                prim->timer--;
            } else {
                // again not colliderFlags, seems to control stone fading
                if (colliderFlags < prim->b1) {
                    prim->b1 -= colliderFlags;
                }
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1;
            }
        }
    }
}

// ash thrown when using vibhuti subweapon
void EntitySubwpnThrownVibhuti(Entity* self) {
    Collider collider;
    FakePrim* fakeprim;
    s16 fakeprimY;
    s16 collisionOffsetX;
    s16 randomAngle;
    s16 randomVelocity;
    s32 i;
    u16 selfX;
    u16 selfY;

    switch (self->step) {
    case 0:
        self->primIndex = func_800EDB58(PRIM_TILE_ALT, 13);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        func_8011A290(self);
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        self->hitboxWidth = self->hitboxHeight = 4;
        self->ext.subweapon.timer = 0x80;
        fakeprim = (FakePrim*)&g_PrimBuf[self->primIndex];
        fakeprimY = selfY - 8;
        while (1) {
            fakeprim->drawMode = DRAW_UNK02;
            fakeprim->priority = PLAYER.zPriority + 2;
            if (fakeprim->next == NULL) {
                fakeprim->y0 = fakeprim->x0 = fakeprim->w = 0;
                fakeprim->drawMode &= ~DRAW_HIDE;
                break;
            }
            fakeprim->posX.i.hi = selfX;
            fakeprim->posY.i.hi = fakeprimY;
            fakeprim->posX.i.lo = fakeprim->posY.i.lo = 0;
            randomAngle = (rand() & 0xFF) + 0x100;
            randomVelocity = (rand() & 0xFF) + 0x80;
            fakeprim->velocityX.val =
                ((rcos(randomAngle) << 4) * randomVelocity >> 9) + FIX(0.5);
            fakeprim->velocityY.val =
                -((rsin(randomAngle) << 4) * randomVelocity >> 9);
            fakeprim->velocityX.val = (fakeprim->velocityX.val * 3) >> 1;
            if (self->facingLeft) {
                fakeprim->velocityX.val = -fakeprim->velocityX.val;
            }
            fakeprim->delay = 1;
            fakeprim->posY.i.hi -= 4;
            fakeprim->b0 = fakeprim->g0 = fakeprim->r0 = 0xFF;
            fakeprim->h = fakeprim->w = 2;
            fakeprim->x0 = fakeprim->posX.i.hi;
            fakeprim->y0 = fakeprim->posY.i.hi;
            fakeprim = fakeprim->next;
        }
        PlaySfx(SFX_WEAPON_SWISH_C);
        g_Player.timers[10] = 4;
        self->step++;
        break;
    case 1:
        if (self->facingLeft) {
            collisionOffsetX = -2;
        } else {
            collisionOffsetX = 2;
        }

        if (!--self->ext.subweapon.timer) {
            DestroyEntity(self);
            return;
        }
        fakeprim = (FakePrim*)&g_PrimBuf[self->primIndex];
        i = 0;
        while (1) {
            if (fakeprim->next == NULL) {
                fakeprim->y0 = fakeprim->x0 = fakeprim->w = 0;
                fakeprim->drawMode &= ~DRAW_HIDE;
                break;
            }
            fakeprim->posX.i.hi = fakeprim->x0;
            fakeprim->posY.i.hi = fakeprim->y0;
            if (fakeprim->delay != 0) {
                if (fakeprim->velocityX.val != 0) {
                    fakeprim->posX.val += fakeprim->velocityX.val;
                    CheckCollision(fakeprim->posX.i.hi + collisionOffsetX,
                                   fakeprim->posY.i.hi, &collider, 0);
                    if (collider.effects & EFFECT_UNK_0002) {
                        fakeprim->velocityX.val = 0;
                    }
                }
                fakeprim->posY.val += fakeprim->velocityY.val;
                fakeprim->velocityY.val += FIX(12.0 / 128);
                if (fakeprim->velocityY.val > FIX(4)) {
                    fakeprim->velocityY.val = FIX(4);
                }
                if (fakeprim->velocityY.val > 0) {
                    CheckCollision(
                        fakeprim->posX.i.hi, fakeprim->posY.i.hi, &collider, 0);
                    if (collider.effects & EFFECT_SOLID) {
                        fakeprim->delay = 0;
                        fakeprim->posY.i.hi =
                            fakeprim->posY.i.hi + collider.unk18 - (i % 3 + 1);
                        fakeprim->w = fakeprim->h = 3;
                    }
                }
            }
            if ((self->ext.subweapon.timer & 7) == i) {
                self->posX.i.hi = fakeprim->posX.i.hi;
                self->posY.i.hi = fakeprim->posY.i.hi;
                if (fakeprim->drawMode & DRAW_HIDE) {
                    self->hitboxHeight = 0;
                    self->hitboxWidth = 0;
                } else {
                    self->hitboxWidth = self->hitboxHeight = 4;
                }
                if (fakeprim->delay != 0) {
                    self->hitboxOffY = 0;
                } else {
                    self->hitboxOffY = -6;
                }
            }
            if ((self->hitFlags != 0) &&
                (((self->ext.subweapon.timer + 1) & 7) == i)) {
                fakeprim->drawMode = DRAW_HIDE;
            }
            if ((self->ext.subweapon.timer - 1) == i) {
                fakeprim->drawMode = DRAW_HIDE;
            }
            fakeprim->x0 = fakeprim->posX.i.hi;
            fakeprim->y0 = fakeprim->posY.i.hi;
            fakeprim = fakeprim->next;
            i++;
        }
        self->hitFlags = 0;
        break;
    }
}

s32 DraPrimDecreaseBrightness(Primitive* prim, u8 amount) {
    u8 isEnd;
    s32 i;
    s32 j;
    u8* pColor;

    isEnd = 0;
    pColor = &prim->r0;
    for (i = 0; i < 4; i++, pColor += OFF(Primitive, r1) - OFF(Primitive, r0)) {
        for (j = 0; j < 3; j++) {
            pColor[j] -= amount;

            if (pColor[j] < 16) {
                pColor[j] = 16;
            } else {
                isEnd |= 1;
            }
        }
    }
    return isEnd;
}

// ID #17. Created by factory blueprint #22. This is the blueprint for the
// Agunea (lightning) subweapon.
void EntitySubwpnAgunea(Entity* self) {
    Entity* ent;
    Primitive* prim;
    s32 heartCost;
    u16 tempY;
    u16 tempX;
    u32 heartBroachesWorn;

    if (g_Player.status & (PLAYER_STATUS_TRANSFORM | PLAYER_STATUS_UNK10000)) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        } else {
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS;
            self->facingLeft = PLAYER.facingLeft;
            func_8011A290(self);
            self->hitboxHeight = 4;
            self->hitboxWidth = 4;
            self->hitboxOffX = 4;
            self->hitboxOffY = 0;
            self->posY.i.hi = self->ext.agunea.unk82 =
                PLAYER.posY.i.hi + PLAYER.hitboxOffY - 8;
            self->posX.i.hi = self->ext.agunea.unk80 = PLAYER.posX.i.hi;
            prim = &g_PrimBuf[self->primIndex];
            prim->type = PRIM_LINE_G2;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_TRANSP;
            prim->r1 = 0x60;
            prim->g1 = 0;
            prim->b1 = 0x80;
            SetSpeedX(FIX(6));
            PlaySfx(SFX_WEAPON_SWISH_C);
            CreateEntFactoryFromEntity(self, FACTORY(44, 0x52), 0);
            g_Player.timers[10] = 4;
            self->step++;
        }
        break;
    case 1:
        self->posX.val += self->velocityX;
        if (self->posX.i.hi < -0x40 || self->posX.i.hi > 0x140 ||
            self->posY.i.hi < -0x20 || self->posY.i.hi > 0x120) {
            self->step = 2;
        }
        if (self->hitFlags != 0) {
            self->step = 3;
            self->ext.agunea.parent = self->unkB8;
        }
        break;
    case 4:
        self->posX.i.hi = self->ext.agunea.parent->posX.i.hi;
        self->posY.i.hi = self->ext.agunea.parent->posY.i.hi;
        if (++self->ext.agunea.unk7C >= 16) {
            if (g_PrimBuf[self->primIndex].r1 < 5) {
                DestroyEntity(self);
                return;
            }
        }
        break;
    case 2:
        if (g_PrimBuf[self->primIndex].r1 < 5) {
            DestroyEntity(self);
            return;
        }
        break;
    case 3:
        if ((g_Player.padPressed & (PAD_UP + PAD_SQUARE)) !=
            (PAD_UP + PAD_SQUARE)) {
            self->step = 4;
        }
        ent = self->ext.agunea.parent;
        if (ent->entityId == 0 ||
            self->ext.agunea.unk7C != 0 &&
                (ent->hitPoints > 0x7000 || ent->hitPoints == 0 ||
                 ent->flags & FLAG_DEAD)) {
            self->step = 2;
            return;
        }

        tempX = self->posX.i.hi = self->ext.agunea.parent->posX.i.hi;
        tempY = self->posY.i.hi = self->ext.agunea.parent->posY.i.hi;
        if ((self->ext.agunea.unk7C % 12) == 0) {
            self->posX.i.hi += ((rand() & 0xF) - 8);
            self->posY.i.hi += ((rand() & 0xF) - 8);
            if (self->ext.agunea.unk84 == 0) {
                CreateEntFactoryFromEntity(self, 23, 0);
                PlaySfx(SFX_THUNDER_B);
                CreateEntFactoryFromEntity(self, FACTORY(61, 2), 0);
                self->ext.agunea.unk84++;
            } else {
                heartCost = 5;
                // 0x4d is the item ID for the heart broach.
                heartBroachesWorn =
                    CheckEquipmentItemCount(ITEM_HEART_BROACH, EQUIP_ACCESSORY);
                if (heartBroachesWorn == 1) {
                    heartCost = 2;
                }
                if (heartBroachesWorn == 2) {
                    heartCost /= 3;
                }
                if (heartCost <= 0) {
                    heartCost = 1;
                }
                if (g_Status.hearts >= heartCost) {
                    g_Status.hearts -= heartCost;
                    CreateEntFactoryFromEntity(self, 23, 0);
                    PlaySfx(SFX_THUNDER_B);
                    CreateEntFactoryFromEntity(self, FACTORY(61, 2), 0);
                } else {
                    self->step = 4;
                }
            }
        }
        self->posX.i.hi = tempX;
        self->posY.i.hi = tempY;
        self->ext.agunea.unk7C++;
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    if (prim->r1 >= 4) {
        prim->r1 -= 4;
    }
    if (prim->g1 >= 4) {
        prim->g1 -= 4;
    }
    if (prim->b1 >= 4) {
        prim->b1 -= 4;
    }
    tempX = prim->b1;
    if (tempX < 5) {
        prim->drawMode |= DRAW_HIDE;
    }
    prim->x0 = self->ext.agunea.unk80;
    prim->y0 = self->ext.agunea.unk82;
    prim->x1 = self->posX.i.hi;
    prim->y1 = self->posY.i.hi;
    return;
}

void EntityAguneaHitEnemy(Entity* self) {
    Entity* sine;
    Primitive* prim;
    Primitive* temp_s3;
    Primitive* var_a0;
    s16 somethingY;
    s16 somethingX;
    s16 angle;
    s16 xOffset;
    s16 yOffset;
    u8 var_s2;
    s16 temp_s2;
    u8 var_s3;
    s32 i;
    s32 randy;

    sine = self->ext.et_801291C4.parent;
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = (PLAYER.posY.i.hi + PLAYER.hitboxOffY) - 8;

    if (self->ext.et_801291C4.parent->entityId != 0x11) {
        switch (self->step) {
        case 0:
            DestroyEntity(self);
            return;
        case 1:
        case 2:
        case 4:
            self->step = 3;
        }
    }
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 0x28);
        if (self->primIndex == -1) {
        block_71:
            DestroyEntity(self);
            break;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;

        self->facingLeft = PLAYER.facingLeft;
        self->ext.et_801291C4.unk84 = ((rand() & 0x3FF) - 0x200) & 0xFFF;
        prim = &g_PrimBuf[self->primIndex];
        self->ext.et_801291C4.prim1 = prim;
        self->ext.et_801291C4.prim2 = prim;
        self->ext.et_801291C4.unk90 = (self->params >> 8);
        for (i = 0; prim != NULL;) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->u0 = prim->u1 = i * 0x10 - 0x70;
            prim->u2 = prim->u3 = i * 0x10 - 0x60;
            prim->v0 = prim->v2 = 0xD0;
            prim->v1 = prim->v3 = 0xC0;
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            prim->x2 = self->posX.i.hi;
            prim->y2 = self->posX.i.hi;
            prim->r0 = prim->g0 = prim->b0 = 0xF0;
            i += 1;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            if (i >= 6) {
                i = 0;
            }
        }
        prim = self->ext.et_801291C4.prim1;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->x1 = prim->x0;
        prim->y1 -= 0x10;
        prim->x2 = self->posX.i.hi;
        prim->y2 = self->posY.i.hi;
        prim->x3 = prim->x2;
        prim->y3 = prim->y2 - 0x10;
        self->ext.et_801291C4.prim2 = prim;
        while (prim != NULL) {
            prim->clut = 0x194;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.et_801291C4.unk88 = 0;
        self->step += 1;
        break;
    case 1:

        for (i = 0; i < 2; i++) {
            prim = self->ext.et_801291C4.prim2;
            temp_s2 = self->ext.et_801291C4.unk84;
            somethingX = sine->posX.i.hi - prim->x2;
            somethingY = sine->posY.i.hi - prim->y2;
            var_s3 = 0;
            if ((abs(somethingX) < 8) && (abs(somethingY) < 8)) {
                self->step++;
                break;
            }
            if (abs(somethingX) < 0x40) {
                var_s3 = abs(somethingY) < 0x40;
            }
            if (self->ext.et_801291C4.unk88 == 0) {
                self->ext.et_801291C4.unk88 = 4;
                if (var_s3 != 0) {
                    self->ext.et_801291C4.unk88 = 2;
                }
                angle = ratan2(-somethingY, somethingX) - temp_s2;
                if (angle >= 0x801) {
                    angle = 0x1000 - angle;
                }
                if (angle < -0x800) {
                    angle += 0x1000;
                }
                if (var_s3 == 0) {
                    angle = angle / 4;
                } else {
                    angle = angle / 2;
                }
                self->ext.et_801291C4.unk86 = angle;
            }
            temp_s2 = temp_s2 + self->ext.et_801291C4.unk86;
            if (var_s3 == 0) {
                randy = rand();
                temp_s2 += 0x180;
                temp_s2 -= ((randy & 3) << 8);
            }
            temp_s2 = temp_s2 & 0xFFF;
            temp_s3 = prim->next;
            if (temp_s3 == NULL) {
                self->step += 1;
                break;
            }
            LOW(temp_s3->x0) = LOW(prim->x2);
            LOW(temp_s3->x1) = LOW(prim->x3);
            self->ext.et_801291C4.unk84 = temp_s2;
            self->ext.et_801291C4.prim2 = temp_s3;
            xOffset = (rcos(temp_s2) * 0xC) >> 0xC;
            yOffset = (rsin(temp_s2) * 0xC) >> 0xC;
            temp_s2 = temp_s2 - 0x400;
            temp_s3->x2 = xOffset + temp_s3->x0;
            temp_s3->y2 = temp_s3->y0 - yOffset;
            var_s2 = 0x10 - (self->params * 4);
            xOffset = (var_s2 * rcos(temp_s2)) >> 0xC;
            yOffset = (var_s2 * rsin(temp_s2)) >> 0xC;
            temp_s3->x3 = xOffset + temp_s3->x2;
            temp_s3->y3 = temp_s3->y2 - yOffset;
            temp_s3->drawMode = DRAW_COLORS | DRAW_UNK02;
            self->ext.et_801291C4.unk88--;
        }
        return;
    case 2:
        if (self->step_s == 0) {
            prim = self->ext.et_801291C4.prim1;
            while (prim != NULL) {
                prim->clut = 0x15F;
                prim = prim->next;
            }
            self->step_s += 1;
            return;
        }
        prim = self->ext.et_801291C4.prim1;
        while (prim != NULL) {
            prim->clut = 0x194;
            prim->r0 = prim->g0 = prim->b0 = 0x60;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        self->step_s = 0;
        self->step += 1;
        break;
    case 3:
        prim = self->ext.et_801291C4.prim1;
        var_s2 = 1;
        while (prim != NULL) {
            if (DraPrimDecreaseBrightness(prim, 4) & 0xFF) {
                var_s2 = 0;
            } else {
                var_s2 &= 1;
            }
            prim = prim->next;
        }
        if (var_s2 != 0) {
            prim = self->ext.et_801291C4.prim1;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            DestroyEntity(self);
        }
        break;
    }
}

void func_80129864(Entity* self) {
    s32 a = 11;
    s32 b = 25;
    Primitive* prim;
    s32 s1;
    s32 s3;
    s32 s4;
    s32 i;
    s32 s6;
    s32 s7;
    s32 action;

    u8 temp_u;
    u8 temp_v;
    s32 angle_diff;
    s32 angle_offset;
    s32 otherX, otherY;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(4, 0x10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 8; i++) {
            prim->type = PRIM_TILE;
            prim->u0 = 1;
            prim->v0 = 1;
            prim->drawMode = DRAW_UNK02;
            prim->priority = 0;
            prim = prim->next;
            prim->priority = 0x1C2;
            prim->drawMode =
                DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            prim->tpage = 0x1A;
            prim->clut = 0x19F;
            prim = prim->next;
        }
        self->facingLeft = (PLAYER.facingLeft + 1) & 1; // !PLAYER.facingLeft
        self->ext.et_80129864.unk80 = D_800B0858[(u8)self->params];
        self->animSet = 9;
        self->anim = D_800B0798;
        self->palette = PAL_OVL(0x19F);
        self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        self->zPriority = 0x1C3;
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
            FLAG_HAS_PRIMS | FLAG_UNK_100000 | FLAG_UNK_20000 | FLAG_UNK_10000;
        self->drawFlags = FLAG_DRAW_ROTZ;
        if (self->params & 0x7F00) {
            func_8011A328(self, 3);
        } else {
            func_8011A328(self, 1);
        }
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->step++;
        break;
    case 1:
        s1 = rcos(self->ext.et_80129864.unk82) >> 8;
        self->ext.et_80129864.unk82 += 0x80;
        self->ext.et_80129864.unk80 += s1;

        if (self->posY.i.hi < -0x20) {
            self->ext.et_80129864.ent = func_80118970();
            self->ext.et_80129864.unk84 = 0;
            self->ext.et_80129864.unk80 = 0xC00;
            if ((self->params & 0xFF) > 1) {
                self->facingLeft = (self->facingLeft + 1) & 1;
            }
            self->step++;
        }
        break;
    case 2:
        if (self->ext.et_80129864.unk84 < 0x18) {
            angle_offset = 0x10;
        } else if (self->ext.et_80129864.unk84 < 0x28) {
            angle_offset = 0x20;
        } else if (self->ext.et_80129864.unk84 < 0x38) {
            angle_offset = 0x40;
        } else {
            angle_offset = 0x80;
        }

        if (self->ext.et_80129864.ent != NULL) {
            if (!self->ext.et_80129864.ent->entityId) {
                self->step++;
                break;
            } else {
                otherX = self->ext.et_80129864.ent->posX.i.hi;
                otherY = self->ext.et_80129864.ent->posY.i.hi;
            }
        } else {
            if (self->facingLeft) {
                otherX = 0x140;
                otherY = 0xA0;
            } else {
                otherX = -0x40;
                otherY = 0xA0;
            }
            if (self->params & 1) {
                otherY += 0x40;
            }
        }

        s1 = ratan2(self->posY.i.hi - otherY, otherX - self->posX.i.hi) & 0xFFF;
        s3 = self->ext.et_80129864.unk80 & 0xFFF;
        angle_diff = abs(s3 - s1);
        angle_offset = CLAMP_MAX(angle_offset, angle_diff);
        if (s3 < s1) {
            if (angle_diff < 0x800) {
                s3 += angle_offset;
            } else {
                s3 -= angle_offset;
            }
        } else {
            if (angle_diff < 0x800) {
                s3 -= angle_offset;
            } else {
                s3 += angle_offset;
            }
        }
        self->ext.et_80129864.unk80 = s3 & 0xFFF;
        if (++self->ext.et_80129864.unk84 > 0x60) {
            self->step++;
        }
        break;
    case 3:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS |
                      FLAG_UNK_100000 | FLAG_UNK_10000;
        s1 = rcos(self->ext.et_80129864.unk82) >> 8;
        self->ext.et_80129864.unk82 += 0x80;
        self->ext.et_80129864.unk80 += s1;
        break;
    }

    self->velocityX = rcos(self->ext.et_80129864.unk80) << 6;
    self->velocityY = -(rsin(self->ext.et_80129864.unk80) << 6);
    self->posX.val += self->velocityX;
    self->posY.val += self->velocityY;

    if (self->facingLeft) {
        self->rotZ = self->ext.et_80129864.unk80;
    } else {
        self->rotZ = 0x800 - self->ext.et_80129864.unk80;
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        if (self->ext.et_80129864.unk86 == i) {
            prim->x1 = 1;
        }

        switch (prim->x1) {
        case 0:
            action = 0;
            break;
        case 1:
            action = 1;
            prim->x1 += 1;
            prim->y1 = 0x100;
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            prim->x2 = self->ext.et_80129864.unk80;
            break;
        case 2:
            prim->y1 -= 16;
            action = 2;
            break;
        }

        s3 = prim->x2;
        s6 = prim->x0;
        s7 = prim->y0;
        s4 = prim->y1;
        prim = prim->next;

        switch (action) {
        case 0:
            prim->drawMode |= DRAW_HIDE;
            break;
        case 1:
#ifdef VERSION_PC
            // self->animCurFrame starts at 0. Seems like an out of bounds
            // bug in original?
            temp_u = D_800B0848[(self->animCurFrame) * 2];
            temp_v = D_800B0848[(self->animCurFrame) * 2 + 1];
#else
            temp_u = D_800B0848[(self->animCurFrame - 1) * 2];
            temp_v = D_800B0848[(self->animCurFrame - 1) * 2 + 1];
#endif
            prim->u0 = prim->u2 = temp_u;
            prim->u1 = prim->u3 = temp_u + 31;
            prim->v0 = prim->v1 = temp_v;
            prim->v2 = prim->v3 = temp_v + 15;
            prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
                prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 =
                    prim->g3 = 0x80;
            prim->drawMode &= ~DRAW_HIDE;
            break;
        case 2:
            if (prim->g3 > 4) {
                prim->g3 -= 12;
            }
            prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
                prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 = prim->g3;

            break;
        }

        if (action) {
            s1 = s3 - 0x200;
            prim->x0 = s6 + ((((rcos(s1) >> 4) * a >> 8) * s4) >> 8);
            prim->y0 = s7 - ((((rsin(s1) >> 4) * a >> 8) * s4) >> 8);
            s1 = s3 + 0x200;
            prim->x2 = s6 + ((((rcos(s1) >> 4) * a >> 8) * s4) >> 8);
            prim->y2 = s7 - ((((rsin(s1) >> 4) * a >> 8) * s4) >> 8);
            s1 = s3 - 0x734;
            prim->x1 = s6 + ((((rcos(s1) >> 4) * b >> 8) * s4) >> 8);
            prim->y1 = s7 - ((((rsin(s1) >> 4) * b >> 8) * s4) >> 8);
            s1 = s3 + 0x734;
            prim->x3 = s6 + ((((rcos(s1) >> 4) * b >> 8) * s4) >> 8);
            prim->y3 = s7 - ((((rsin(s1) >> 4) * b >> 8) * s4) >> 8);
        }
        prim = prim->next;
    }

    self->ext.et_80129864.unk86 += 1;
    self->ext.et_80129864.unk86 = self->ext.et_80129864.unk86 % 8;
}

// opens hole in backround and spirit comes out (ID 0x40)
void EntitySummonSpirit(Entity* self) {
    Primitive* prim;
    s32 timer;
    s32 selfX;
    s32 selfY;
    s32 i;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_20000 | FLAG_UNK_10000;
        g_unkGraphicsStruct.unk20 = 3;
        self->ext.summonspirit.spawnTimer = 10;
        func_80118C28(13);
        self->step++;
        return;

    case 1:
        if (--self->ext.summonspirit.spawnTimer) {
            return;
        }
        self->primIndex = AllocPrimitives(4, 9);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->posX.i.hi = 0x80;
        self->posY.i.hi = 0x60;
        if (PLAYER.posY.i.hi - 0x30 > 0x40) {
            self->posY.i.hi = PLAYER.posY.i.hi - 0x30;
        } else {
            self->posY.i.hi = PLAYER.posY.i.hi + 0x40;
        }
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        prim = &g_PrimBuf[self->primIndex];

        prim->type = PRIM_G4;
        prim->drawMode = DRAW_UNK_100 | DRAW_UNK02;
        prim->x2 = prim->x0 = selfX - 0x20;
        prim->x3 = prim->x1 = selfX + 0x1F;
        prim->y1 = prim->y0 = selfY - 0x20;
        prim->y2 = prim->y3 = selfY + 0x1F;
        D_80138424.x = prim->x0;
        if (g_CurrentBuffer->disp.disp.x == 0) {
            D_80138424.x += 0x100;
        }
        D_80138424.y = prim->y0;
        D_80138424.w = 0x3F;
        D_80138424.h = 0x3F;
        MoveImage(&D_80138424, 0x200, 0x1C0);
        prim->priority = 0x1C0;
        prim = prim->next;
        for (i = 0; i < 8; i++) {
            // These should have been Point16 :(
            prim->x1 = selfX + D_800B0860[(i + 1) * 2];
            prim->y1 = selfY + D_800B0860[(i + 1) * 2 + 1];
            prim->x3 = selfX + D_800B0860[i * 2];
            prim->y3 = selfY + D_800B0860[i * 2 + 1];
            prim->u1 = D_800B0860[(i + 1) * 2] + 0x20;
            prim->v1 = D_800B0860[(i + 1) * 2 + 1] + 0xE0;
            prim->u3 = D_800B0860[i * 2] + 0x20;
            prim->v3 = D_800B0860[i * 2 + 1] + 0xE0;
            prim->u0 = prim->u2 = 0x20;
            prim->v0 = prim->v2 = 0xE0;
            prim->priority = 0x1C1;
            if (i >= 4) {
                prim->priority += 3;
            }
            prim->drawMode = DRAW_UNK_100 | DRAW_UNK02;
            prim->tpage = 0x118;
            prim = prim->next;
        }
        self->ext.summonspirit.timer = 0;
        // This just adds FLAG_HAS_PRIMS. Not sure why it wasn't an |=.
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000 | FLAG_UNK_10000;
        self->step++;
        break;

    case 2:
        self->ext.summonspirit.timer++;
        if (self->ext.summonspirit.timer > 10) {
            // Both blueprints have child 61, but 118 has a couple 4s in the
            // other args. 61 is func_80129864. Not yet decompiled.
            if (self->params) {
                CreateEntFactoryFromEntity(self, 118, 0);
            } else {
                CreateEntFactoryFromEntity(self, 116, 0);
            }
            // Blueprint 44 is child 11. EntityPlayerBlinkWhite
            CreateEntFactoryFromEntity(self, FACTORY(44, 0x67), 0);
            PlaySfx(SFX_UI_MP_FULL);
            self->step++;
        }
        break;
    case 3:
        self->ext.summonspirit.timer--;
        if (self->ext.summonspirit.timer < 0) {
            g_unkGraphicsStruct.unk20 = 0;
            DestroyEntity(self);
            return;
        }
        break;
    }
    timer = self->ext.summonspirit.timer;
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    prim = prim->next;
    for (i = 0; i < 8; i++) {
        prim->x2 = selfX + (((rcos(i << 9) >> 4) * timer) >> 8);
        prim->y2 = selfY - (((rsin(i << 9) >> 4) * timer) >> 8);
        prim->x0 = selfX + (((rcos((i + 1) << 9) >> 4) * timer) >> 8);
        prim->y0 = selfY - (((rsin((i + 1) << 9) >> 4) * timer) >> 8);
        prim = prim->next;
    }
}
