// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #20. Used by weapons:
// Karma Coin
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_020_1.h"
#include "w_020_2.h"
#define g_Animset w_020_1
#define g_Animset2 w_020_2
#include "sfx.h"

extern SpriteParts D_90000_8017A040[];
extern AnimationFrame D_90000_8017A850[];
extern AnimationFrame D_90000_8017A864[];
extern AnimationFrame D_90000_8017A8C8[];
extern AnimationFrame D_90000_8017A8D8[];
extern AnimationFrame D_90000_8017A8E8[];
extern AnimationFrame D_90000_8017A954[];
extern AnimationFrame D_90000_8017A9D8[];
extern FrameProperty D_90000_8017A9E0;
extern u16 D_90000_8017AA10[];
extern u8 D_90000_8017AA1C;
extern s32 D_90000_8017AADC[];
extern s32 D_90000_8017AB44[];
extern s32 D_90000_8017C238;

static void EntityWeaponAttack(Entity* self) {
    Collider sp10;
    Entity* child;
    Primitive* prim;

    u16 var_s4;
    s16 angle_s3;
    s32 var_s2;
    u8* var_s1;

    s16 xVar;
    s16 yVar;

    s16 xOffset;
    s16 yOffset;
    s16 sp6a;
    s16 sp68;
    s16 sp66;
    s16 sp64;
    s16 sp62;
    u16 sp60;
    s16 var_s8;
    s16 var_s7;

    sp60 = D_90000_8017AA10[g_GameTimer % 3] % 0x8000;
    var_s4 = 0;
    if (g_HandId != 0) {
        sp60 += 0x18;
        var_s4 += 0x80;
    }
    switch (self->step) {
    default:
        return;
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 0x1A);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode = DRAW_HIDE;
        SetSpriteBank1(D_90000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = PLAYER.facingLeft;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS | FLAG_UNK_100000;
        self->anim = D_90000_8017A850;
        SetSpeedX((rand() & 0x3FFF) + 0xE000);
        self->velocityY = FIX(-4.0);
        self->facingLeft = 0;
        DestroyEntityWeapon(1);
        self->step += 1;
        return;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(0.15625);
        xOffset = 0;
        yOffset = 1;
        xVar = self->posX.i.hi + xOffset;
        yVar = self->posY.i.hi + yOffset;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->posY.i.hi += sp10.unk18;
            self->animFrameDuration = self->animFrameIdx = 0;
            self->anim = D_90000_8017A864;
            g_api.PlaySfx(SFX_GOLD_PICKUP);
            self->step += 1;
            return;
        }
        xOffset = 4;
        if (self->velocityX < 0) {
            xOffset = -xOffset;
        }
        yOffset = 0;
        xVar = self->posX.i.hi + xOffset;
        yVar = self->posY.i.hi + yOffset;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_UNK_0002) {
            if (xOffset < 0) {
                self->posX.i.hi += sp10.unkC;
            } else {
                self->posX.i.hi += sp10.unk4;
            }
            self->velocityX = -(self->velocityX / 2);
        }
        xOffset = 0;
        yOffset = -8;
        xVar = self->posX.i.hi + xOffset;
        yVar = self->posY.i.hi + yOffset;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->posY.i.hi += sp10.unk20 + 1;
            self->velocityY = FIX(1.0);
            self->velocityX = self->velocityX / 2;
        }
        return;
    case 2:
        if (((self->animFrameIdx % 8) == 5) && (self->animFrameDuration == 1)) {
            g_api.PlaySfxVolPan(SFX_GOLD_PICKUP,
                                D_90000_8017AB44[self->ext.karmacoin.unk84], 0);
            self->ext.karmacoin.unk84++;
        }
        if (self->animFrameDuration < 0) {
            self->animFrameDuration = self->animFrameIdx = 0;
            // This appears to be the actual Karma Coin coin-flip, deciding
            // heads/tails
            if (rand() & 1) {
                // Heads
                self->anim = D_90000_8017A8C8;
            } else {
                // Tails
                self->anim = D_90000_8017A8D8;
            }
            self->step += 1;
        }
        return;
    case 3:
        if ((self->animFrameIdx == 1) && (self->animFrameDuration == 0x38)) {
            // Useless if-statement
            if (self->anim == D_90000_8017A8C8) {
                g_api.PlaySfx(SFX_KARMA_COIN_JINGLE);
            } else {
                g_api.PlaySfx(SFX_KARMA_COIN_JINGLE);
            }
        }
        if (self->animFrameDuration < 0) {
            // Tails: A small head pops up, and lightning strikes the coin
            if (self->anim == D_90000_8017A8D8) {
                g_Player.timers[10] = 4;
                self->anim = D_90000_8017A8E8;
                self->animFrameDuration = self->animFrameIdx = 0;
                self->zPriority = 0x1B6;
                self->flags &= ~FLAG_UNK_100000;
                g_api.func_80118C28(7);
                g_api.PlaySfx(SFX_THUNDER_B);
                SetWeaponProperties(self, 0);
                self->step = 4;
            } else {
                // Heads: A giant angelic figure appears, with a soul-steal
                // effect. Not clear what part of the function triggers
                // soul-steal.
                g_Player.timers[12] = 4;
                self->drawFlags = FLAG_BLINK;
                self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
                self->posY.i.hi = 0;
                self->posX.i.hi = 0x80;
                self->zPriority = 0x1BA;
                self->animCurFrame = 0x1D;
                self->flags &= ~(FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000);
                self->ext.karmacoin.timer = 0xE0;
                self->unk6C = 0x80;
                g_api.func_80118C28(8);
                g_api.PlaySfx(SFX_TRANSFORM_3X);
                prim = &g_PrimBuf[self->primIndex];
                prim->r0 = prim->g0 = prim->b0 = 0x5F;
                prim->r1 = prim->g1 = prim->b1 = 0x5F;
                prim->r2 = prim->g2 = prim->b2 = 0x1F;
                prim->r3 = prim->g3 = prim->b3 = 0x1F;
                prim->priority = 0x1BC;
                prim = prim->next;

                prim->x0 = prim->x2 = 0x54;
                prim->x1 = prim->x3 = 0xAC;
                prim->y0 = prim->y1 = 0x30;
                prim->y2 = prim->y3 = 0x98;
                prim->v0 = prim->v1 = var_s4;
                prim->v2 = prim->v3 = var_s4 + 0x67;
                prim->u0 = prim->u2 = 0x80;
                prim->u1 = prim->u3 = 0x80 + 0x57;
                prim->type = PRIM_GT4;
                prim->priority = 0x1B4;

                prim->drawMode = DRAW_HIDE;
                prim->tpage = 0x19;
                prim->clut = sp60;
                prim = prim->next;
                var_s1 = &D_90000_8017AA1C;
                for (var_s2 = 0; var_s2 < 24; var_s2++) {
                    prim->x0 = *var_s1++;
                    prim->u0 = prim->x0 + 0x80;
                    prim->x0 += 0x54;
                    prim->y0 = *var_s1++;
                    prim->v0 = var_s4 + prim->y0;
                    prim->y0 += 0x30;
                    prim->x2 = *var_s1++;
                    prim->u2 = prim->x2 + 0x80;
                    prim->x2 += 0x54;
                    prim->y2 = *var_s1++;
                    prim->v2 = var_s4 + prim->y2;
                    prim->y2 += 0x30;
                    prim->x1 = *var_s1++;
                    prim->u1 = prim->x1 + 0x80;
                    prim->x1 += 0x54;
                    prim->y1 = *var_s1++;
                    prim->v1 = var_s4 + prim->y1;
                    prim->y1 += 0x30;
                    prim->x3 = *var_s1++;
                    prim->u3 = prim->x3 + 0x80;
                    prim->x3 += 0x54;
                    prim->y3 = *var_s1++;
                    prim->v3 = var_s4 + prim->y3;
                    prim->y3 += 0x30;
                    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                        prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                            prim->g3 = prim->b3 = 0x80;
                    prim->type = PRIM_GT4;
                    prim->priority = 0x1B6;
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE |
                                     DRAW_COLORS | DRAW_TRANSP;
                    prim->tpage = 0x19;
                    prim->clut = sp60;
                    prim = prim->next;
                }
                self->ext.karmacoin.unk8A = 0x40;
                self->ext.karmacoin.unk90 = 0;
                self->ext.karmacoin.unk92 = self->ext.karmacoin.unk94 = 0x100;
                self->ext.karmacoin.unk7E = 0x20;
                self->attack = 4;
                self->attackElement = 0x20;
                self->hitboxState = 0x82;
                self->nFramesInvincibility = 0x50;
                self->stunFrames = 4;
                self->hitEffect = 2;
                self->entityRoomIndex = 0;
                g_api.func_80118894(self);
                self->step = 5;
            }
        }
        return;
    case 4:
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
        g_api.UpdateAnim(&D_90000_8017A9E0, NULL);
        return;
    case 5:
        if (!(g_GameTimer & 3)) {
            self->ext.karmacoin.unk7E++;
        }
        if (self->ext.karmacoin.unk7E >= 0x61) {
            self->ext.karmacoin.unk7E = 0x60;
        }
        self->ext.karmacoin.unk90 += 8;
        if (self->ext.karmacoin.unk90 > 0x120) {
            self->ext.karmacoin.unk90 = 0x120;
        }
        self->ext.karmacoin.unk92 -= 4;
        if (self->ext.karmacoin.unk92 < 0x28) {
            self->ext.karmacoin.unk92 = 0x28;
            child =
                g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x54, 0), 0);
            self->step++;
        }
        self->ext.karmacoin.unk94 = self->ext.karmacoin.unk92;
        break;

    case 6:
        if (!(g_GameTimer & 3)) {
            self->ext.karmacoin.unk7E++;
        }
        if (self->ext.karmacoin.unk7E >= 0x61) {
            self->ext.karmacoin.unk7E = 0x60;
        }
        --self->ext.karmacoin.unk92;
        if (self->ext.karmacoin.unk92 < 0) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            self->ext.karmacoin.unk92 = 0;
            self->step++;
        }
        self->ext.karmacoin.unk94 = self->ext.karmacoin.unk92;
        break;
    case 7:
        self->ext.karmacoin.unk90 -= 0x10;
        if (self->ext.karmacoin.unk90 < 0) {
            self->ext.karmacoin.unk90 = 0;
        }
        if (--self->ext.karmacoin.timer < 0) {
            self->step += 1;
        }
        if (!(g_GameTimer & 3)) {
            self->ext.karmacoin.unk7E++;
        }
        if (self->ext.karmacoin.unk7E >= 0x61) {
            self->ext.karmacoin.unk7E = 0x60;
        }
        prim = &g_PrimBuf[self->primIndex];
        if (!(self->ext.karmacoin.timer & 1) && (prim->b3 > 1)) {
            prim->b3--;
        }
        prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        break;
    case 8:
        self->drawFlags |= FLAG_DRAW_UNK8;
        self->unk6C--;
        if (self->unk6C < 4) {
            self->unk6C = 4;
        }
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b1 > 8) {
            prim->b1 -= 2;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1;
        self->ext.karmacoin.unk90 += 0x10;
        if (self->ext.karmacoin.unk90 > 0x120) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            g_api.PlaySfx(SFX_TELEPORT_BANG_B);
            self->step += 1;
        }
        break;
    case 9:
        self->drawFlags |= FLAG_DRAW_UNK8;
        self->unk6C -= 2;
        if (self->unk6C < 4) {
            self->unk6C = 4;
        }
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b1 >= 9) {
            prim->b1 -= 2;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1;
        self->ext.karmacoin.unk90 -= 8;
        if (self->ext.karmacoin.unk90 < 0) {
            self->ext.karmacoin.unk90 = 0;
        }
        self->ext.karmacoin.unk92 += 12;
        if (self->ext.karmacoin.unk92 > 0x200) {
            DestroyEntity(self);
            return;
        }
        self->ext.karmacoin.unk94 = self->ext.karmacoin.unk92;
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = 0x74;
    prim->x1 = 0x8C;
    prim->x2 = 0x80 - self->ext.karmacoin.unk7E;
    prim->x3 = self->ext.karmacoin.unk7E + 0x80;
    prim->y0 = prim->y1 = 0;
    prim->y2 = prim->y3 = 0xF0;

    prim->drawMode =
        DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
    prim = prim->next;
    prim->clut = sp60;
    prim = prim->next;
    var_s1 = &D_90000_8017AA1C;
    for (var_s2 = 0; var_s2 < 24; var_s2++) {
        prim->drawMode &= ~DRAW_HIDE;
        if (var_s2 == 0) {
            angle_s3 = D_90000_8017AADC[var_s2];
            yVar = -(rsin(angle_s3) >> 5) * self->ext.karmacoin.unk94 / 256;
            xVar = (rcos(angle_s3) >> 5) * self->ext.karmacoin.unk92 / 256;
            prim->x0 = *var_s1++;
            prim->x0 += xVar + 0x54;
            prim->y0 = *var_s1++;
            prim->y0 += yVar + 0x30;
            prim->x2 = *var_s1++;
            prim->x2 += xVar + 0x54;
            prim->y2 = *var_s1++;
            prim->y2 += yVar + 0x30;
        } else {
            prim->x0 = sp68;
            prim->y0 = sp66;
            prim->x2 = sp64;
            prim->y2 = sp62;
            var_s1 += 4;
        }
        var_s7 = D_90000_8017AADC[(var_s2 + 1) % 24];
        var_s8 = -(rsin(var_s7) >> 5) * self->ext.karmacoin.unk94 / 256;
        sp6a = (rcos(var_s7) >> 5) * self->ext.karmacoin.unk92 / 256;
        prim->x1 = *var_s1++;
        sp68 = prim->x1 += sp6a + 0x54;
        prim->y1 = *var_s1++;
        sp66 = prim->y1 += var_s8 + 0x30;
        prim->x3 = *var_s1++;
        sp64 = prim->x3 += sp6a + 0x54;
        prim->y3 = *var_s1++;
        sp62 = prim->y3 += var_s8 + 0x30;
        angle_s3 = D_90000_8017AADC[var_s2];
        prim->b0 = prim->b2 = prim->g0 = prim->g2 = prim->r0 = prim->r2 =
            ((rsin(angle_s3) + 0x1000) >> 6) * self->ext.karmacoin.unk90 / 256;
        angle_s3 = D_90000_8017AADC[(var_s2 + 1) % 24];
        prim->b1 = prim->b3 = prim->g1 = prim->g3 = prim->r1 = prim->r3 =
            ((rsin(angle_s3) + 0x1000) >> 6) * self->ext.karmacoin.unk90 / 256;
        D_90000_8017AADC[var_s2] += self->ext.karmacoin.unk8A;
        prim = prim->next;
    }
}

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {
    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority;

        if (D_90000_8017C238 % 4 == 1) {
            self->velocityX = FIX(8.0 / 128);
            self->velocityY = FIX(34.0 / 128);
            self->anim = D_90000_8017A9D8;
            self->posX.i.hi = 140;
            self->posY.i.hi = 100;
            self->zPriority = PLAYER.zPriority - 4;
        } else {
            self->zPriority = PLAYER.zPriority;
            self->anim = D_90000_8017A954;
            self->animFrameIdx = rand() & 0x1F;
            self->posX.i.hi = (D_90000_8017C238 % 3) * 10 + 148;
            self->posY.i.hi = (D_90000_8017C238 % 3) * 10 + 76;
            self->velocityX = FIX(19.0 / 256); // strange, FIX is usually /128
            self->velocityY = (rand() & 0x1FFF) + FIX(0.25);
        }
        D_90000_8017C238++;
        self->step++;
    }
    self->palette = D_90000_8017AA10[g_GameTimer % 3];
    if (g_HandId != 0) {
        self->palette += 0x18;
    }
    self->posX.val += self->velocityX;
    self->posY.val += self->velocityY;
}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 20; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
