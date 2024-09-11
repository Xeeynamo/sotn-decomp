// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"
#include "sfx.h"

// Entity ID 66. Made by blueprint 77 (the very last one).
// Created in 3 spots in 2 functions (total of 6 calls).
// DRA version is very similar.
static Point16 D_80175000[32];
void RicEntityTeleport(Entity* self) {
    Primitive* prim;
    s32 selfUnk7C;
    s32 selfUnk80;
    s32 yVar;
    s32 xVar;
    s32 upperParams;
    s32 i;
    s32 result;

    bool showParticles = false;
    bool var_s5 = false;

    upperParams = self->params & 0xFE00;
    FntPrint("pl_warp_flag:%02x\n", g_Player.unk1C);
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4 + LEN(D_80175000));
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
            prim->type = 1;
            prim->priority = 0x1FD;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            prim = prim->next;
        }
        for (i = 0; i < 2; i++) {
            prim->type = 3;
            prim->priority = 0x1F8;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
        }
        for (i = 0; i < LEN(D_80175000); i++) {
            xVar = PLAYER.posX.i.hi + (rand() % 28) - 14;
            yVar = rand();
            yVar = 0xE0 - (yVar & 0x3F);
            D_80175000[i].x = xVar;
            D_80175000[i].y = yVar;
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
            g_api.PlaySfx(0x8BB);
        } else {
            self->ext.teleport.unk7C = 1;
            self->ext.teleport.unk90 = 0;
            self->ext.teleport.unk80 = 0x10;
            self->ext.teleport.unk88 = 0x80;
            self->step = 1;
            g_api.PlaySfx(SFX_TELEPORT_BANG_A);
            g_api.PlaySfx(0x8BA);
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
        showParticles = true;
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
        func_80166024();
        if (--self->ext.teleport.unk7C <= 0) {
            self->ext.teleport.unk7C = 0;
            self->step++;
        }
        break;
    case 5:
        var_s5 = true;
        func_80166024();
        self->ext.teleport.unk90 += 4;
        if (self->ext.teleport.unk90 >= 0x100) {
            self->ext.teleport.unk90 = 0xFF;
            self->ext.teleport.unk84 = 0x20;
            self->step++;
        }
        break;
    case 6:
        var_s5 = true;
        func_80166024();
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
            g_api.PlaySfx(SFX_TELEPORT_BANG_B);
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
    func_80165DD8(prim, self->ext.teleport.unk88, yVar, selfUnk80, upperParams);
    prim = prim->next;
    prim->x1 = prim->x3 = xVar;
    prim->x0 = prim->x2 = xVar + selfUnk7C;
    func_80165DD8(prim, self->ext.teleport.unk88, yVar, selfUnk80, upperParams);
    prim = prim->next;
    if (showParticles) {
        for (i = 0; i < LEN(D_80175000); i++) {
            switch (prim->g0) {
            case 0:
                if (--prim->g1 == 0) {
                    prim->g0++;
                }
                break;
            case 1:
                result = func_8015FDB0(prim, D_80175000[i].x, D_80175000[i].y);
                D_80175000[i].y -= 16;
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
    } else {
        // Potential bug? Should probably be doing prim = prim->next, right?
        for (i = 0; i < LEN(D_80175000); i++) {
            prim->drawMode |= DRAW_HIDE;
        }
    }
}

// Entity #10, uses blueprint #10. Appears related to poisoning, due to call in
// RicDoAttack
static Point16 D_801559AC[] = {
    0x0007, 0xFFFE, 0x0010, 0xFFFE, 0x0005, 0xFFEE, 0xFFF2,
    0xFFEE, 0xFFE9, 0xFFFA, 0xFFE8, 0xFFFA, 0xFFE7, 0xFFFA};
static Point16 D_801559C8[] = {
    0x0007, 0x000B, 0x0010, 0x000B, 0x0005, 0xFFFB, 0xFFF2,
    0xFFFB, 0xFFE9, 0x000B, 0xFFE8, 0x000B, 0xFFE7, 0x000B};
static Point16 D_801559E4[] = {
    0xFFF1, 0xFFFC, 0xFFF2, 0xFFF2, 0xFFF7, 0xFFFA, 0xFFEE, 0xFFFA, 0xFFF7,
    0x0002, 0xFFF5, 0xFFF7, 0xFFF0, 0xFFF6, 0xFFF9, 0x0000, 0xFFF2, 0x0000};
static s16 D_80155A08[] = {0x000F, 0x000E, 0x0012, 0x0009, 0x0009,
                           0x0010, 0x000B, 0x000E, 0x0007, 0x0000};
static Point16 D_80155A1C[] = {
    0xFFF1, 0x0009, 0xFFF2, 0xFFFF, 0xFFF7, 0x0007, 0xFFEE, 0x0009, 0xFFF7,
    0x000F, 0xFFF5, 0x0004, 0xFFF0, 0x0003, 0xFFF9, 0x000D, 0xFFF2, 0x000D,
};
static s16 D_80155A40[] = {0x000F, 0x000E, 0x0012, 0x0009, 0x0009,
                           0x0010, 0x000B, 0x000E, 0x0007, 0x0000};
static Point16 D_80155A54[] = {
    0xFFF1, 0xFFFA, 0xFFF2, 0xFFF0, 0xFFF7, 0xFFF8, 0xFFEE, 0xFFFA, 0xFFF7,
    0x0000, 0xFFF5, 0xFFF5, 0xFFF0, 0xFFF4, 0xFFF9, 0xFFFE, 0xFFF2, 0xFFFE};
static s16 D_80155A78[] = {
    0x000F, 0x000E, 0x0012, 0x0009, 0x0009, 0x0010, 0x000B, 0x000E, 0x0007,
    0x0000, 0x0001, 0x0000, 0x0005, 0x0000, 0x0002, 0x0000, 0x0007, 0x0000,
    0x0004, 0x0000, 0x0008, 0x0000, 0x0003, 0x0000, 0x0006, 0x0000};
static Point32 D_80155AAC[] = {
    0x00040000, 0x00020000, 0x00040000, 0xFFFD8000, 0x00100000,
    0x00000000, 0x00100000, 0x00000000, 0xFFEC0000, 0x00000000,
    0xFFE00000, 0x00000000, 0xFFCC0000, 0x00000000};
static Point32 D_80155AE4[] = {
    0x00000000, 0x00000000, 0xFFFD8000, 0x00000000, 0xFFFFE000, 0x00020000,
    0xFFFFE000, 0xFFFE0000, 0x00008000, 0x00000000, 0xFFFE0000, 0x00018000,
    0xFFFE0000, 0xFFFE8000, 0x00008000, 0x00018000, 0x00008000, 0xFFFE8000};
static s32 D_80155B2C[][9] = {
    {1, 1, 5, 6, 0, 1, 1, 0, 0}, {2, 5, 2, 0, 7, 2, 0, 2, 0},
    {3, 6, 0, 3, 8, 0, 3, 0, 3}, {4, 0, 7, 8, 4, 0, 0, 4, 4},
    {5, 5, 5, 0, 0, 5, 1, 2, 0}, {6, 6, 0, 6, 0, 1, 6, 0, 3},
    {7, 0, 7, 0, 7, 1, 0, 7, 4}, {8, 0, 0, 8, 8, 4, 3, 7, 8},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};
static s16 D_80155C70[] = {0x8139, 0x813A, 0x813B, 0x0000};
static s16 D_80155C78[] = {
    0x0010, 0x000E, 0x000C, 0x000A, 0x0008, 0x0006, 0x0004, 0x0002,
    0x000F, 0x000D, 0x000B, 0x0009, 0x0007, 0x0005, 0x0003, 0x00FF};
static u16 D_80155C98[] = {
    0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15};
static u32 D_80175080;
static s32 D_80175084;
void RicEntityWhip(Entity* self) {
    byte stackpad[40];
    s32 sp38;
    s16 upperParams;
    s16 lowerParams;
    Primitive* prim;
    s16 angle;
    s32 var_s3;
#ifdef VERSION_PC
    // this can still be uninitialized when we get past the D_80155B2C section
    // not every combo of directions is covered
    s32 var_s4 = 0;
#else
    s32 var_s4;
#endif
    s32 var_s5;
    s32 temp_s6;
    s32 var_s7;
    s16 temp_a2;
    s32 temp_a3;
    s32 directionsPressed;

    s32 randy;

    s32 xDiff;
    s32 yDiff;

    s32 selfY;
    s32 selfX;
    f32 dumb_temp;
    u16 playerUnk46;

    s32 magSq;
    s32 ySq;
    s32 xSq;

    lowerParams = self->params & 0xFF;
    upperParams = self->params & 0xFF00;
    if (lowerParams == 0) {
        if (self->ext.whip.unkA6 != 0) {
            self->ext.whip.unkA6--;
        }
    }
    playerUnk46 = g_Player.unk46;
    if (playerUnk46 == 0) {
        DestroyEntity(self);
        return;
    }
    if ((self->step == 2) && (playerUnk46 == 2)) {
        self->step = 1;
        self->velocityX = 0;
        self->velocityY = 0;
        self->palette = 0x8148;
        if (!PLAYER.facingLeft) {
            self->ext.whip.unk88 = playerUnk46;
        } else {
            self->ext.whip.unk88 = 3;
        }
        self->ext.whip.unk8C = 0x600;
    }
    if (self->step != 0) {
        xDiff = self->posX.val - self->ext.whip.unk98;
        yDiff = self->posY.val - self->ext.whip.unk9C;
        self->ext.whip.unk7C.val += xDiff;
        self->ext.whip.unk80.val += yDiff;
    }
    directionsPressed = g_Player.padPressed & 0xF000;
    if (directionsPressed == PAD_UP) {
        var_s4 = D_80155B2C[0][self->ext.whip.unk88];
    }
    if (directionsPressed == PAD_DOWN) {
        var_s4 = D_80155B2C[3][self->ext.whip.unk88];
    }
    if (directionsPressed == PAD_RIGHT) {
        var_s4 = D_80155B2C[1][self->ext.whip.unk88];
    }
    if (directionsPressed == PAD_LEFT) {
        var_s4 = D_80155B2C[2][self->ext.whip.unk88];
    }
    if (directionsPressed == (PAD_UP + PAD_RIGHT)) {
        var_s4 = D_80155B2C[4][self->ext.whip.unk88];
    }
    if (directionsPressed == (PAD_UP + PAD_LEFT)) {
        var_s4 = D_80155B2C[5][self->ext.whip.unk88];
    }
    if (directionsPressed == (PAD_DOWN + PAD_RIGHT)) {
        var_s4 = D_80155B2C[6][self->ext.whip.unk88];
    }
    if (directionsPressed == (PAD_DOWN + PAD_LEFT)) {
        var_s4 = D_80155B2C[7][self->ext.whip.unk88];
    }
    if (directionsPressed == 0) {
        var_s4 = D_80155B2C[8][self->ext.whip.unk88];
    }
    self->ext.whip.unk86 = 0;
    if (lowerParams == 0) {
        if (self->step == 1) {
            if (PLAYER.step == PL_S_CROUCH) {
                if (!PLAYER.facingLeft) {
                    var_s3 = D_80155A40[var_s4];
                } else {
                    var_s3 = D_80155A1C[var_s4].x;
                }
                var_s5 = D_80155A1C[var_s4].y;
            } else {
                if (PLAYER.step == PL_S_STAND) {
                    if (!PLAYER.facingLeft) {
                        var_s3 = D_80155A08[var_s4];
                    } else {
                        var_s3 = D_801559E4[var_s4].x;
                    }
                } else if (!PLAYER.facingLeft) {
                    var_s3 = D_80155A78[var_s4];
                } else {
                    var_s3 = D_80155A54[var_s4].x;
                }
                var_s5 = D_801559E4[var_s4].y;
            }
        } else {
            if (PLAYER.step == PL_S_CROUCH) {
                var_s3 = D_801559C8[PLAYER.animFrameIdx].x;
                var_s5 = D_801559C8[PLAYER.animFrameIdx].y;
            } else {
                var_s3 = D_801559AC[PLAYER.animFrameIdx].x;
                var_s5 = D_801559AC[PLAYER.animFrameIdx].y;
            }
            if (!PLAYER.facingLeft) {
                var_s3 = -var_s3;
            }
        }
        var_s3 <<= 16;
        var_s5 <<= 16;
        var_s3 += PLAYER.posX.val;
        var_s5 += PLAYER.posY.val;
    } else {
        self--;
        var_s3 = self->posX.val;
        var_s5 = self->posY.val;
        self++;
    }
    switch (self->step) {
    case 0:
        self->animSet = -0x7FEE;
        self->animCurFrame = 0x1E;
        self->palette = 0x8138;
        self->unk5A = 0x46;
        if (lowerParams < 8) {
            self->hitboxWidth = 3;
            self->hitboxHeight = 3;
            self->hitboxOffX = 0;
            self->hitboxOffY = 0;
            self->ext.whip.unkB0 = PL_W_WHIP;
            RicSetSubweaponParams(self);
        }
        if (lowerParams == 0) {
            self->zPriority = PLAYER.zPriority - 2;
        }
        if (lowerParams == 7) {
            self->animCurFrame = 0x1F;
            self->hitboxWidth++;
            self->hitboxHeight++;
        }
        self->zPriority = PLAYER.zPriority + 4;
        self->posX.val = var_s3;
        self->posY.val = var_s5;
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_PLAYER_LOCKED |
                      FLAG_UNK_20000 | FLAG_UNK_10000;
        self->ext.whip.unk8C = 0x500;
        self->ext.whip.unk7C.val = self->posX.val;
        self->ext.whip.unk80.val = self->posY.val;
        self->ext.whip.unk98 = self->ext.whip.unk7C.val;
        self->ext.whip.unk9C = self->ext.whip.unk80.val;
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (self->primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[self->primIndex];
            prim->b0 = prim->g0 = prim->r0 = 0x7F;
            prim->b1 = prim->g1 = prim->r1 = 0x1F;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        }
        self->step = 2;
        RicEntityWhip(self);
        break;
    case 1:
        if (upperParams == 0) {
            if ((u16)(self->palette + 0x7EC0) < 8) {
                if (self->ext.whip.unkA4 != 0) {
                    self->ext.whip.unkA4--;
                } else {
                    self->palette++;
                }
            }
        } else if (self->ext.whip.unkA4 != 0) {
            if (!(lowerParams & 1)) {
                RicCreateEntFactoryFromEntity(self, BP_20, 0);
                self->ext.whip.unkA4 = 0;
            }
        }
        if (lowerParams < 8) {
            if (self->ext.whip.unk84 != 0) {
                if (--self->ext.whip.unk84 == 0) {
                    if (self->velocityY < 0) {
                        self->velocityY = 0;
                    }
                    self->velocityX = 0;
                }
            } else {
                self->velocityX = self->velocityX * 3 / 4;
            }
            if (self->ext.whip.unk88 == var_s4) {
                break;
            }

            // This block has a really weird extra instruction.
            //  Required a lot of faking to get it to match. The
            //  first if-statement really should not matter.
            if (lowerParams == 0) {
                s32 a1;
                Entity* a0;
                if (upperParams == 0) {
                    a1 = 18;
                } else {
                    a0 = self;
                }
                if (self->ext.whip.unkA6 == 0) {
                    g_api.PlaySfx(SFX_RIC_WHIP_RATTLE_A);
                    self->ext.whip.unkA6 = 0x20;
                }
                if (upperParams == 0) {
                    a0 = self;
                    a1 = FACTORY(BP_18, 0);
                } else {
                    a0 = self;
                    a1 = FACTORY(BP_18, 1);
                }
                RicCreateEntFactoryFromEntity(a0, a1, 0);
            }

            self->ext.whip.unk84 = 6;
            if (var_s4 == 0) {
                if (!PLAYER.facingLeft) {
                    xDiff = D_80155A08[0];
                } else {
                    xDiff = D_801559E4[0].x;
                }
                // This should be 2 simple lines, but I had to be pedantic about
                // the individual steps to get it to match.
                selfY = self->posY.val;
                selfX = self->posX.val;
                yDiff = D_801559E4[0].y;
                xDiff += PLAYER.posX.i.hi;
                yDiff += PLAYER.posY.i.hi;
                xDiff <<= 16;
                yDiff <<= 16;

                angle = ratan2(selfY - yDiff, xDiff - selfX);
                self->velocityX = (rcos(angle) << 7) >> 4;
                self->velocityY = -(rsin(angle) << 7) >> 4;
            } else {
                self->velocityY = D_80155AE4[var_s4].x;
                self->velocityX = D_80155AE4[var_s4].y;
            }
            self->ext.whip.unk88 = var_s4;
        }
        break;
    case 2:
        if (lowerParams >= 8) {
            if (self->flags & FLAG_HAS_PRIMS) {
                if (PLAYER.animFrameIdx == 5) {
                    g_api.FreePrimitives(self->primIndex);
                    self->flags &= ~FLAG_HAS_PRIMS;
                }
            }
            if (PLAYER.animFrameIdx == 6) {
                if ((PLAYER.animFrameDuration >= 0xF) ||
                    (PLAYER.animFrameDuration == 0)) {
                    self->palette = 0x8138;
                } else if ((PLAYER.animFrameDuration == 11 ||
                            PLAYER.animFrameDuration == 12) ||
                           (PLAYER.animFrameDuration == 13 ||
                            PLAYER.animFrameDuration == 14)) {
                    self->palette = 0x813C;
                } else {
// animFrameDuration can be -1 apparently.
// todo this should read the previous element out of bounds?
#ifdef VERSION_PC
                    if (PLAYER.animFrameDuration >= 0) {
                        self->palette =
                            D_80155C70[PLAYER.animFrameDuration % 3];
                    }
#else
                    self->palette = D_80155C70[PLAYER.animFrameDuration % 3];
#endif
                }
            }
        } else {
            self->velocityX = D_80155AAC[PLAYER.animFrameIdx].x;
            self->velocityY = D_80155AAC[PLAYER.animFrameIdx].y;
            switch (PLAYER.animFrameIdx) {
            case 0:
                angle = (rand() & 0x3FF) - 0x200;
                self->velocityX = (rcos(angle) << 0xB) >> 4;
                self->velocityY = -(rsin(angle) << 0xB) >> 4;
                break;
            case 1:
                randy = rand() | ~0x3FF;
                self->velocityX = (rcos(randy) << 0xB) >> 4;
                self->velocityY = -(rsin(randy) << 0xB) >> 3;
                self->ext.whip.unk8C = 0x600;
                break;
            case 4:
                self->ext.whip.unk8C = 0x3C0;
                if (PLAYER.animFrameDuration == 1) {
                    self->velocityX = FIX(-8);
                }
                break;
            case 5:
                self->ext.whip.unk8C += 0xC0;
                if (self->flags & FLAG_HAS_PRIMS) {
                    g_api.FreePrimitives(self->primIndex);
                    self->flags &= ~FLAG_HAS_PRIMS;
                }
                break;
            case 6:
                if (upperParams != 0) {
                    if (PLAYER.animFrameDuration == D_80155C78[lowerParams]) {
                        RicCreateEntFactoryFromEntity(self, BP_20, 0);
                    }
                }
                if (lowerParams == (0x10 - PLAYER.animFrameDuration)) {
                    self->ext.whip.unk8C = 0x600;
                }
                // This very well might be a switch
                if (PLAYER.animFrameDuration > 14) {
                    self->palette = 0x8138;
                } else if (PLAYER.animFrameDuration == 0) {
                    self->palette = 0x8138;
                } else if (PLAYER.animFrameDuration == 11 ||
                           PLAYER.animFrameDuration == 12) {
                    self->palette = 0x813C;
                } else if (PLAYER.animFrameDuration == 13 ||
                           PLAYER.animFrameDuration == 14) {
                    self->palette = 0x813C;
                } else {
// animFrameDuration can be -1 apparently.
// todo this should read the previous element out of bounds?
#ifdef VERSION_PC
                    if (PLAYER.animFrameDuration >= 0) {
                        self->palette =
                            D_80155C70[PLAYER.animFrameDuration % 3];
                    }
#else
                    self->palette = D_80155C70[PLAYER.animFrameDuration % 3];
#endif
                }
                break;
            }
            if (!PLAYER.facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->velocityX /= 2;
            self->velocityY /= 2;
        }
        break;
    }
    temp_a2 = self->ext.whip.unk8C;
    temp_s6 = self->posX.val;
    sp38 = self->posY.val;
    if (lowerParams == 0) {
        self->posX.val = var_s3;
        self->posY.val = var_s5;
    } else if (lowerParams >= 8) {
        // weird reuse of variables here
        xDiff = (self - 8)->posX.val;
        yDiff = (self - 8)->posY.val;
        temp_a3 = (self - 7)->posX.val;
        self->posX.val = (xDiff + temp_a3) / 2;
        var_s7 = (self - 7)->posY.val;
        self->posY.val = (yDiff + var_s7) / 2;
    } else {
        temp_a3 = temp_s6 - self->ext.whip.unk7C.val;
        var_s7 = sp38 - self->ext.whip.unk80.val;
        if (self->step == 1) {
            if (self->velocityY < FIX(0.5)) {
                self->posX.val = temp_a3 + temp_s6;
                self->posY.val += var_s7;
            }
            if ((u32)(self->velocityY - FIX(0.5)) < FIX(0.75)) {
                self->posX.val += temp_a3 * 15 / 16;
                self->posY.val += var_s7 * 15 / 16;
            }
            if ((u32)self->velocityY >= FIX(1.25)) {
                self->posX.val += temp_a3 * 13 / 16;
                self->posY.val += var_s7 * 13 / 16;
            }
        } else {
            self->posX.val = temp_a3 * 3 / 4 + temp_s6;
            self->posY.val += var_s7 * 3 / 4;
        }
        if ((self->velocityY < FIX(8)) || (self->velocityY < 0)) {
            self->velocityY += 0xA00;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;

        magSq = ((temp_a2 * temp_a2) >> 0x10);
        yDiff = self->posY.val - var_s5;
        ySq = (yDiff * (yDiff >> 0x10)) >> 0x10;
        xDiff = self->posX.val - var_s3;
        xSq = (xDiff * (xDiff >> 0x10)) >> 0x10;
        if (magSq < (ySq + xSq)) {
            angle = ratan2(-yDiff, xDiff);
            xDiff = (rcos(angle) * temp_a2) >> 4;
            yDiff = -(rsin(angle) * temp_a2) >> 4;
            self->posX.val = var_s3 + xDiff;
            self->posY.val = var_s5 + yDiff;
        }
    }
    self->ext.whip.unk7C.val = temp_s6;
    self->ext.whip.unk80.val = sp38;
    self->ext.whip.unkA0 = var_s7;
    self->ext.whip.unk98 = self->posX.val;
    self->ext.whip.unk9C = self->posY.val;
    if (lowerParams == 0) {
        D_80175080 = var_s4;
        D_80175084 = self->ext.whip.unk88;
    }
    if ((self->primIndex != -1) && (self->flags & FLAG_HAS_PRIMS)) {
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        // for some reason need this to make it use lh instead of lhu for x1 and
        // y1.
        dumb_temp = self->ext.whip.unk7C;
        prim->x1 = dumb_temp.i.hi;
        dumb_temp = self->ext.whip.unk80;
        prim->y1 = dumb_temp.i.hi;
        if (PLAYER.animFrameIdx == 4) {
            prim->priority = PLAYER.zPriority + 4;
        } else {
            prim->priority = PLAYER.zPriority + 2;
        }
    }
    if (upperParams != 0) {
        if (lowerParams != 7) {
            self->unk6C =
                (rsin(
                     (s16)((((g_GameTimer / 4) & 7) + D_80155C98[lowerParams]) *
                           512)) >>
                 6) -
                0x80;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
            self->drawFlags |= DRAW_HIDE;
        }
        self->palette = 0x8160;
    }
}

static s16 D_80155CB8[] = {0x000A, 0x000B, 0x000D, 0x0011, 0x000F,
                           0x000C, 0x0012, 0x000E, 0x0010, 0x0000};
static s16 D_80155CCC[] = {0x000A, 0x000B, 0x0011, 0x000D, 0x000F,
                           0x0012, 0x000C, 0x0010, 0x000E, 0x0000};
static s16 D_80155CE0[] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0006,
                           0x0003, 0x0009, 0x0005, 0x0007, 0x0000};
static s16 D_80155CF4[] = {0x0001, 0x0002, 0x0008, 0x0004, 0x0006,
                           0x0009, 0x0003, 0x0007, 0x0005, 0x0000};
static s16 D_80155D08[] = {0x0013, 0x0014, 0x0016, 0x001A, 0x0018,
                           0x0015, 0x001B, 0x0017, 0x0019, 0x0000};
static s16 D_80155D1C[] = {0x0013, 0x0014, 0x001A, 0x0016, 0x0018,
                           0x001B, 0x0015, 0x0019, 0x0017, 0x0000};
void RicEntityArmBrandishWhip(Entity* entity) {
    if (g_Player.unk46 == 0) {
        DestroyEntity(entity);
        return;
    }

    entity->facingLeft = PLAYER.facingLeft;
    if (entity->step == 0) {
        entity->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                        FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_10000;
        entity->animSet = ANIMSET_OVL(18);
        entity->unk5A = 0x46;
        entity->palette = 0x8120;
        entity->zPriority = PLAYER.zPriority + 2;
    }

    if (PLAYER.step == PL_S_CROUCH) {
        if (PLAYER.facingLeft) {
            entity->animCurFrame = D_80155CCC[D_80175080];
        } else {
            entity->animCurFrame = D_80155CB8[D_80175080];
        }
    } else if (PLAYER.step == 0) {
        if (PLAYER.facingLeft) {
            entity->animCurFrame = D_80155CF4[D_80175080];
        } else {
            entity->animCurFrame = D_80155CE0[D_80175080];
        }
    } else if (PLAYER.facingLeft) {
        entity->animCurFrame = D_80155D1C[D_80175080];
    } else {
        entity->animCurFrame = D_80155D08[D_80175080];
    }

    entity->posX.val = g_Entities->posX.val;
    entity->posY.val = PLAYER.posY.val;
}

static s16 D_80155D30[] = {0x10, 0x18, 0x11, 0x19, 0x12, 0x1A, 0x13, 0x1B, 0x14,
                           0x1C, 0x15, 0x1D, 0x16, 0x1E, 0x17, 0x00, 0x02, 0x01,
                           0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x00, 0x00};
void func_80167964(Entity* entity) {
    if (g_Player.unk46 != 0) {
        if (entity->step == 0) {
            entity->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_10000;
        }
        if (!(entity->params & 0xFF00)) {
            g_Entities[D_80155D30[entity->animFrameDuration]].palette =
                PAL_OVL(0x140);
        }
        g_Entities[D_80155D30[entity->animFrameDuration]].ext.player.unkA4 = 4;
        entity->animFrameDuration++;
        if (entity->animFrameDuration == 0xF) {
            DestroyEntity(entity);
        }
    } else {
        DestroyEntity(entity);
    }
}

void RicEntityNotImplemented1(Entity* self) {}

void RicEntityNotImplemented2(Entity* self) {}

void RicEntityNotImplemented3(Entity* self) {}

// Entity ID #35. Created by blueprint 40. No known FACTORY calls with
// blueprint 40. Duplicate of DRA EntityHolyWaterBreakGlass.
static s16 D_80155D64[4][6] = {
    {2, -2, 0, -4, 0, 0},
    {-3, -3, -1, 1, 2, 0},
    {-4, -3, 2, -2, -2, 2},
    {-1, 0, 0, -4, 3, 3},
};
void func_80167A70(Entity* self) {
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
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
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
                fakeprim->type = 1;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 =
                    (rand() & 0xF) | 0x30;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = rand() | 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 =
                    (rand() & 0x1F) + 0x30;
                randbit = rand() & 1;
                prim->drawMode = !(randbit) ? 6 : 0x37;
                posX = sp10[i - 8].x;
                posY = sp10[i - 8].y;
                arrIndex = i & 3;
                prim->u0 = arrIndex;
                prim->x0 = posX + D_80155D64[arrIndex][0];
                prim->y0 = posY + D_80155D64[arrIndex][1];
                prim->x1 = posX + D_80155D64[arrIndex][2];
                prim->y1 = posY + D_80155D64[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_80155D64[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_80155D64[arrIndex][5];
                prim->type = 3;
                prim->priority = PLAYER.zPriority + 2;
            }
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->ext.timer.t = 20;
        self->step++;
        break;

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
                prim->x0 = posX + D_80155D64[arrIndex][0];
                prim->y0 = posY + D_80155D64[arrIndex][1];
                prim->x1 = posX + D_80155D64[arrIndex][2];
                prim->y1 = posY + D_80155D64[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_80155D64[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_80155D64[arrIndex][5];
            }
        }
        break;
    }
}

// Entity ID #11. Created by blueprint 12.
// This is blueprintNum for subweapon ID 16.
// That is the crash for subweapon 3. That's holy water!
void RicEntityCrashHydroStorm(Entity* self) {
    PrimLineG2* line;
    s16 primcount;
    s32 trigresult;
    s32 trigtemp;

    if (self->params < 40) {
        primcount = 32;
    } else {
        primcount = 33 - ((self->params - 32) * 2);
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, primcount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.subweapon.subweaponId = PL_W_HYDROSTORM;
        RicSetSubweaponParams(self);
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000;
        line = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        self->facingLeft = 0;
        while (line != NULL) {
            line->r0 = 0x1F;
            line->g0 = 0x1F;
            line->b0 = 0x30;
            line->r1 = 0x3F;
            line->g1 = 0x50;
            line->b1 = 0x7F;
            line->x1 = line->x0 = rand() & 0x1FF;
            line->y0 = line->y1 = -(rand() & 0xF);
            line->preciseX.i.hi = line->x1;
            line->preciseY.i.hi = line->y1;

            // This whole block is weird. Why are we calculating rcos
            // and rsin on a fixed value at runtime? And why aren't
            // these simple multiplications?
            trigresult = rcos(0xB80);
            trigtemp = trigresult * 16;
            line->velocityX.val = (trigresult * 32 + trigtemp) * 4;
            trigresult = rsin(0xB80);
            trigtemp = trigresult * -16;
            line->velocityY.val = trigtemp * 12;

            line->timer = 0;
            line->delay = (rand() & 0xF) + 12;
            if (rand() & 1) {
                line->priority = PLAYER.zPriority + 2;
            } else {
                line->priority = PLAYER.zPriority - 2;
            }
            line->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            line = line->next;
        }
        if (self->params == 1) {
            g_api.func_801027C4(3);
        }
        self->ext.subweapon.timer = 0x160;
        if ((self->params < 32) && !(self->params & 3)) {
            g_api.PlaySfx(0x708);
        }
        self->step++;
        break;

    case 1:
        line = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        while (line != NULL) {
            if (line->timer == 0) {
                line->preciseX.i.hi = line->x1;
                line->preciseY.i.hi = line->y1;
                line->preciseX.val += line->velocityX.val;
                line->preciseY.val += line->velocityY.val;
                line->x1 = line->preciseX.i.hi;
                line->y1 = line->preciseY.i.hi;
                if (line->delay < line->y1) {
                    line->timer++;
                    line->xLength = line->x0 - line->x1;
                    line->yLength = line->y0 - line->y1;
                }
            } else {
                line->preciseX.i.hi = line->x1;
                line->preciseY.i.hi = line->y1;
                line->preciseX.val += line->velocityX.val;
                line->preciseY.val += line->velocityY.val;
                line->x1 = line->preciseX.i.hi;
                line->y1 = line->preciseY.i.hi;
                line->y0 = line->y1 + line->yLength;
                line->x0 = line->x1 + line->xLength;
                if (line->y0 >= 0xD8) {
                    self->step = 2;
                }
            }
            line = line->next;
        }
        self->ext.subweapon.timer++;
        break;

    case 2:
        DestroyEntity(self);
        break;
    }
    g_Player.timers[PL_T_3] = 16;
}

// Copy of DRA function
s32 RicCheckHolyWaterCollision(s32 baseY, s32 baseX) {
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

    g_api.CheckCollision(x, y, &res1, 0);
    colRes1 = res1.effects & colFullSet;
    g_api.CheckCollision(x, (s16)(y - 1 + res1.unk18), &res2, 0);
    y = baseY + (g_CurrentEntity->posY.i.hi + res1.unk18);

    if ((colRes1 & colSet1) == EFFECT_SOLID ||
        (colRes1 & colSet1) == (EFFECT_UNK_0800 | EFFECT_SOLID)) {
        colRes2 = res2.effects & colSetNo800;
        if (!((s16)res2.effects & 1)) {
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

s32 func_8016840C(s16 x, s16 y) {
    Collider collider;
    u16 temp;

    if (g_CurrentEntity->velocityX != 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi + y,
                             g_CurrentEntity->posY.i.hi + x, &collider, 0);
        if (g_CurrentEntity->velocityX > 0) {
            temp = collider.unk14;
        } else {
            temp = collider.unk1C;
        }
        if (!(collider.effects & EFFECT_UNK_0002)) {
            return 0;
        }
    } else {
        return 0;
    }
    g_CurrentEntity->posX.i.lo = 0;
    g_CurrentEntity->posX.i.hi += temp;
    return 2;
}
