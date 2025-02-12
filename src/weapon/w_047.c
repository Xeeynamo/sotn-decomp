// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #47. Used by weapons:
// Dynamite
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_047_1.h"
#include "w_047_2.h"
#define g_Animset w_047_1
#define g_Animset2 w_047_2
#include "sfx.h"

extern AnimationFrame D_14D000_8017A528[];
extern s16 D_14D000_8017A468[0x20];
extern s16 D_14D000_8017A488[0x20];
extern unsigned long D_14D000_8017A4A8[]; // image data
extern s32 D_14D000_8017B6A4;

void EntityWeaponAttack(Entity* self) {
    Collider collider;
    RECT rect;
    Primitive* prim;
    s32 unk84;
    s16 offsetX, offsetY;
    s32 i;
    s16 xVar, yVar;

    switch (self->step) {
    case 0:
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->unk5A = 0x65;
        self->palette = 0x110;
        self->ext.weapon_047.unk88 = 0;
        if (g_HandId != 0) {
            self->palette += 0x18;
            self->unk5A += 2;
            self->animSet += 2;
            self->ext.weapon_047.unk88 = 0x80;

            rect.x = 0x260;
            rect.w = 4;
            rect.h = 0x10;
            rect.y = 0x180;
            LoadImage(&rect, D_14D000_8017A4A8);
        } else {
            rect.x = 0x260;
            rect.w = 4;
            rect.h = 0x10;
            rect.y = 0x100;
            LoadImage(&rect, D_14D000_8017A4A8);
        }
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority - 6;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        if (rand() & 7) {
            self->primIndex = g_api.AllocPrimBuffers(PRIM_TILE, 0x20);
            if (self->primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
            }
        }
        if (self->flags & FLAG_HAS_PRIMS) {
            prim = &g_PrimBuf[self->primIndex];
            while (prim != NULL) {
                prim->r0 = 0x80;
                prim->g0 = 0x40;
                prim->b0 = 0;
                prim->u0 = prim->v0 = 1;
                prim->x1 = rand() & 0xF;
                prim->x2 = 0;
                prim->x3 = rand() & 0xF;
                prim->priority = self->zPriority - 4;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE |
                                 DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }
        }
        self->velocityY = -FIX(2.5);
        SetSpeedX(rand() + FIX(1.5));
        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY - 8;
        if (PLAYER.step != Player_Crouch) {
            self->posY.i.hi -= 6;
        }
        DestroyEntityWeapon(true);
        g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        self->ext.weapon_047.unk7C = 0x80;
        D_14D000_8017B6A4 = 0;
        g_Player.timers[10] = 4;
        self->step++;
        return;
    case 1:
        self->animCurFrame = 1;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->velocityY < FIX(7)) {
            self->velocityY += FIX(0.125);
        }
        if (self->hitFlags) {
            self->velocityX = (self->velocityX * 2) / 3;
            self->hitFlags = 0;
            return;
        }

        offsetX = 4;
        if (self->velocityX < 0) {
            offsetX = -offsetX;
        }
        offsetY = 0;

        xVar = self->posX.i.hi + offsetX;
        yVar = self->posY.i.hi + offsetY;
        g_api.CheckCollision(xVar, yVar, &collider, 0);
        if (collider.effects & EFFECT_UNK_0002) {
            if (offsetX < 0) {
                self->posX.i.hi += collider.unkC;
            } else {
                self->posX.i.hi += collider.unk4;
            }
            self->velocityX = -(self->velocityX / 2);
        }

        offsetX = 0;
        offsetY = -4;

        xVar = self->posX.i.hi + offsetX;
        yVar = self->posY.i.hi + offsetY;
        g_api.CheckCollision(xVar, yVar, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk20 + 1;
            self->velocityY = FIX(1);
            self->velocityX = self->velocityX / 2;
        }

        offsetX = 0;
        offsetY = 4;

        xVar = self->posX.i.hi + offsetX;
        yVar = self->posY.i.hi + offsetY;
        g_api.CheckCollision(xVar, yVar, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (D_14D000_8017B6A4 == 0) {
                g_api.PlaySfx(SFX_STOMP_SOFT_A);
                D_14D000_8017B6A4++;
            }
            self->posY.i.hi += collider.unk18;
            self->velocityX = 0;
            self->velocityY = 0;
        }

        if (--self->ext.weapon_047.unk7C == 0) {
            self->ext.weapon_047.unk7C = 0x28;
            if (self->flags & FLAG_HAS_PRIMS) {
                g_api.func_80102CD8(6);
                self->step++;

                prim = &g_PrimBuf[self->primIndex];
                while (prim != NULL) {
                    prim->drawMode |= DRAW_HIDE;
                    prim = prim->next;
                }

                prim = &g_PrimBuf[self->primIndex];
                for (i = 0; prim != NULL; i++) {
                    prim->u0 = (rcos(i << 7) >> 4 << 6 >> 8) + 0xC0;
                    prim->v0 = (self->ext.weapon_047.unk88 + 0x40) -
                               ((rsin(i << 7) >> 4 << 6) >> 8);
                    if (prim->u0 < 4) {
                        prim->u0 = 0xFF;
                    }
                    prim->u1 = (rcos((i + 1) << 7) >> 4 << 6 >> 8) + 0xC0;
                    prim->v1 = (self->ext.weapon_047.unk88 + 0x40) -
                               ((rsin((i + 1) << 7) >> 4 << 6) >> 8);
                    if (prim->u1 < 4) {
                        prim->u1 = 0xFF;
                    }
                    if (self->ext.weapon_047.unk88 != 0) {
                        if (prim->v1 < 4) {
                            prim->v1 = 0xFF;
                        }
                        if (prim->v0 < 4) {
                            prim->v0 = 0xFF;
                        }
                    }

                    prim->u2 = prim->u3 = 0xC0;
                    prim->v2 = prim->v3 = self->ext.weapon_047.unk88 + 0x40;
                    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                        prim->b1 = 0;
                    prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                        prim->b3 = 0xFF;
                    prim->clut = 0x159;
                    prim->tpage = 0x19;
                    prim->priority = PLAYER.zPriority + 8;
                    prim->type = PRIM_GT4;
                    prim = prim->next;
                }

                g_api.PlaySfx(SFX_EXPLODE_A);
                self->hitboxWidth = 4;
                self->hitboxHeight = 4;
                SetWeaponProperties(self, 0);
                g_api.func_80118894(self);
                return;
            }
            self->step = 4;
            self->ext.weapon_047.unk7C = 0x18;
        } else {
            xVar = self->posX.i.hi;
            yVar = self->posY.i.hi;
            if (self->flags & FLAG_HAS_PRIMS) {
                if (!(g_GameTimer & 7)) {
                    g_api.PlaySfx(SFX_WATER_DAMAGE_SWISHES);
                }

                prim = &g_PrimBuf[self->primIndex];
                while (prim != NULL) {
                    if (prim->x3 == 0) {
                        if (self->facingLeft) {
                            prim->x0 =
                                xVar - 8 -
                                ((D_14D000_8017A468[prim->x1] * prim->x2) / 15);
                        } else {
                            prim->x0 =
                                xVar + 8 +
                                ((D_14D000_8017A468[prim->x1] * prim->x2) / 15);
                        }
                        prim->y0 =
                            yVar +
                            (D_14D000_8017A488[prim->x1] * prim->x2) / 15;
                        prim->x2++;
                        if (prim->x2 > 15) {
                            prim->x2 = 0;
                            prim->x1 = rand() & 0xF;
                        }
                        prim->drawMode &= ~DRAW_HIDE;
                    } else {
                        prim->x3--;
                    }
                    prim = prim->next;
                }
            }
        }
        break;
    case 2:
        if (self->hitboxWidth < 0x60) {
            self->hitboxWidth += 6;
            self->hitboxHeight += 6;
        }
        self->animCurFrame = 0;
        if (self->ext.weapon_047.unk84 < 0x8000) {
            self->ext.weapon_047.unk84 += 0x480;
        }
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi;
        unk84 = self->ext.weapon_047.unk84 >> 8;
        i = 0;
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b3 > 0x58) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x3A, 0);
        }
        if (prim->b3 < 5) {
            DestroyEntity(self);
            break;
        }
        while (prim != NULL) {
            prim->x0 = xVar + (((rcos(i << 7) >> 8) * unk84) >> 4);
            prim->y0 = yVar - (((rsin(i << 7) >> 8) * unk84) >> 4);
            prim->x1 = xVar + (((rcos((i + 1) << 7) >> 8) * unk84) >> 4);
            prim->y1 = yVar - (((rsin((i + 1) << 7) >> 8) * unk84) >> 4);
            prim->x2 = prim->x3 = xVar;
            prim->y2 = prim->y3 = yVar;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;

            if (prim->b3 >= 4) {
                prim->b3 -= 4;
            }
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
            prim = prim->next;
            i++;
        }
        break;
    case 3:
        break;
    case 4:
        self->drawFlags |= FLAG_BLINK;
        if (--self->ext.weapon_047.unk7C == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

s32 func_ptr_80170004(Entity* self) {
    s16 speed;

    if (self->step == 0) {
        if (self->ext.factory.parent->entityId == 0) {
            DestroyEntity(self);
        } else {
            SetSpriteBank2(g_Animset2);
            self->animSet = ANIMSET_OVL(0x11);
            self->unk5A = 0x64;
            self->palette = 0x111;
            if (g_HandId != 0) {
                self->palette = 0x129;
                self->unk5A += 2;
                self->animSet += 2;
            }
            self->anim = D_14D000_8017A528;
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
            self->zPriority = PLAYER.zPriority + 2;
            speed = (rand() % 1535) + 0x100;
            self->velocityX = rcos((s32)speed) << 7;
            self->velocityY = -(rsin((s32)speed) << 7);
            self->posX.val += self->velocityX * 2;
            self->posY.val += self->velocityY * 2;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
            if (rand() & 1) {
                self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
            }
            self->step += 1;
        }
        return;
    }
    self->posY.val += self->velocityY;
    self->posX.val += self->velocityX;
    if (self->animFrameDuration < 0) {
        DestroyEntity(self);
    }
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 47; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
