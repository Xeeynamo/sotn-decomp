// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #37. Used by weapons:
// Short sword, Jewel sword, Stone sword, Unknown#198
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_037_1.h"
#include "w_037_2.h"
#define g_Animset w_037_1
#define g_Animset2 w_037_2
#include "sfx.h"

extern WeaponAnimation D_107000_8017A6A4[];
extern s32 D_107000_8017BBE4;

static void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s8 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params & 0x7fff) >> 0x8;

    anim = &D_107000_8017A6A4[animIndex];

    if (PLAYER.ext.weapon.anim < anim->frameStart ||
        PLAYER.ext.weapon.anim >= (anim->frameStart + 7) || !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }

        self->palette += anim->palette;
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED;
        self->zPriority = PLAYER.zPriority - 2;
        SetWeaponProperties(self, 0);
        self->step++;
    }

    self->ext.weapon.anim = PLAYER.ext.weapon.anim - anim->frameStart;

    if (PLAYER.animFrameDuration == 1 &&
        PLAYER.animFrameIdx == anim->soundFrame) {
        g_api.PlaySfx(anim->soundId);
    }

    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }

    if (!D_107000_8017BBE4 && PLAYER.animFrameIdx == 1 &&
        (animIndex - 1) < 2U) {
        g_api.CreateEntFactoryFromEntity(
            self, WFACTORY(0x3a, 0) + (--animIndex << 0x10), 0);
    }

    D_107000_8017BBE4 = PLAYER.animFrameIdx;
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

extern u8 D_107000_8017A6E4[6][8];

s32 func_107000_8017ADF8(Primitive* prim, s32 x, s32 y) {
    s32 size;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
    u8* uvPtr;

    // Should be able to do this as an array access but nope
    uvPtr = &D_107000_8017A6E4;
    uvPtr += prim->b0 * 8;

    if (prim->b0 >= 3) {
        size = 4;
    } else {
        size = 6;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    left = x - size;
    top = y - size;
    right = x + size;
    bottom = y + size;

    prim->x0 = left;
    prim->y0 = top;
    prim->x1 = right;
    prim->y1 = top;
    prim->x2 = left;
    prim->y2 = bottom;
    prim->x3 = right;
    prim->y3 = bottom;

    prim->u0 = *uvPtr++;
    prim->v0 = *uvPtr++;
    prim->u1 = *uvPtr++;
    prim->v1 = *uvPtr++;
    prim->u2 = *uvPtr++;
    prim->v2 = *uvPtr++;
    prim->u3 = *uvPtr++;
    prim->v3 = *uvPtr++;
    if (!(++prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}

extern s16 D_107000_8017A714[];

void func_107000_8017AEF0(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0xA7;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_107000_8017A714[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_107000_8017A714[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_107000_8017A714[idx * 4 + 2] * 2 / 3);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_107000_8017A714[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_107000_8017A714[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_107000_8017A714[idx * 4 + 2] * 2 / 3;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_107000_8017A714[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_107000_8017A714[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_107000_8017A714[idx * 4 + 3] * 2 / 3;
    }
}

void func_107000_8017B0AC(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0xA7;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_107000_8017A714[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_107000_8017A714[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_107000_8017A714[idx * 4 + 2] / 2);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_107000_8017A714[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_107000_8017A714[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_107000_8017A714[idx * 4 + 2] / 2;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_107000_8017A714[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_107000_8017A714[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_107000_8017A714[idx * 4 + 3] / 2;
    }
}

extern s16 D_107000_8017A74C[];
extern s32 D_107000_8017A758[];
extern Point16 D_107000_8017BBE8[];
extern s32 D_107000_8017BD28;

s32 func_ptr_80170004(Entity* self) {
    Point16 basePoint;
    Primitive* prim;
    s32 randy;
    s16 xVar;
    s16 yVar;
    s16 baseX;
    s16 baseY;
    s32 i;

    s16 temp_s3;
    s16 temp_s5;
    s16 temp_s0;

    s32 funcResult;

    u8 upperParams = (self->params >> 8) & 0x7F;

    switch (self->step) {
    case 0:
        for (i = 0; i < 16; i++) {
            D_107000_8017A758[i] = 0;
        }
        if (upperParams & 0x7F) {
            randy = rand() & 31; // rand int 0-31
            if (randy == 0) {
                for (i = 0; i < 16; i++) {
                    D_107000_8017A758[i] = 1;
                }
            } else {
                if (!(randy & 3)) {
                    for (i = 0; i < 16; i++) {
                        if (i % 3 == 0) {
                            D_107000_8017A758[i] = 1;
                        }
                    }
                }
                if ((randy & 3) == 3) {
                    for (i = 0; i < 16; i++) {
                        if (i % 9 == 0) {
                            D_107000_8017A758[i] = 1;
                        }
                    }
                } else {
                    for (i = 0; i < 16; i++) {
                        if (i % 5 == 0) {
                            D_107000_8017A758[i] = 1;
                        }
                    }
                }
            }
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        func_107000_8017B0AC(self, &basePoint, 0);
        // FAKE but makes register allocation work
        randy = basePoint.x;
        baseX = randy;
        baseY = basePoint.y;
        if (PLAYER.drawFlags & DRAW_UNK02) {
            if (0x42 < PLAYER.ext.player.anim &&
                PLAYER.ext.player.anim < 0x45) {
                self->posY.i.hi -= 1;
            } else {
                self->posY.i.hi -= 3;
            }
        }
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi;

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 8; i++) {
            temp_s5 = ((baseX * i) / 8) + xVar;
            temp_s0 = ((baseY * i) / 8) + yVar;
            temp_s3 = temp_s0 + (rand() % 10);
            temp_s0 = temp_s5 + (rand() % 4);

            D_107000_8017BBE8[i].x = temp_s0;
            D_107000_8017BBE8[i].y = temp_s3;

            prim->clut = D_107000_8017A74C[D_107000_8017BD28 % 6];
            prim->tpage = 0x1A;
            prim->g0 = prim->b1 = prim->b0 = 0;
            prim->g1 = i + 1;
            prim->g2 = 0;
            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            if (rand() & 1) {
                prim->drawMode =
                    DRAW_UNK_200 | DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 |
                    DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            }
            prim = prim->next;
            D_107000_8017BD28++;
        }
        self->ext.timer.t = 32;
        self->step++;
        break;
    case 1:
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        switch (prim->g0) {
        case 0:
            if (--prim->g1 == 0) {
                prim->g0++;
            }
            break;
        case 1:
            xVar = D_107000_8017BBE8[i].x;
            yVar = D_107000_8017BBE8[i].y;
            funcResult = func_107000_8017ADF8(
                prim, D_107000_8017BBE8[i].x, D_107000_8017BBE8[i].y);
            D_107000_8017BBE8[i].y--;
            if (funcResult < 0) {
                prim->drawMode |= DRAW_HIDE;
                if (D_107000_8017A758[i] != 0) {
                    temp_s0 = self->posX.i.hi;
                    temp_s3 = self->posY.i.hi;
                    self->posX.i.hi = xVar;
                    self->posY.i.hi = yVar;
                    g_api.CreateEntFactoryFromEntity(self, WFACTORY(64, 0), 0);
                    self->posX.i.hi = temp_s0;
                    self->posY.i.hi = temp_s3;
                }
                prim->g0++;
                break;
            }
            prim->drawMode &= ~DRAW_HIDE;
            break;
        }
        prim = prim->next;
    }
}

extern AnimationFrame D_107000_8017A798[];

static void func_ptr_80170008(Entity* self) {
    Collider collider;
    s16 distX;
    s16 distY;

    switch (self->step) {
    case 0:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            DestroyEntity(self);
            return;
        }

        self->anim = D_107000_8017A798;
        self->animSet = 3;
        self->zPriority = PLAYER.zPriority + 2;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        SetSpeedX(rand() + FIX(0.25));
        self->velocityY = -(rand() + FIX(1));
        self->step++;
        break;

    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(9.0 / 64.0);

        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi - 1, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk20;
            self->velocityY = FIX(1);
        }

        g_api.CheckCollision(
            self->posX.i.hi + 4, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posX.i.hi += collider.unk14;
            self->velocityX = -self->velocityX;
        }

        g_api.CheckCollision(
            self->posX.i.hi - 4, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posX.i.hi += collider.unk1C;
            self->velocityX = -self->velocityX;
        }

        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 7, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            self->ext.timer.t = 0x50;
            g_api.PlaySfx(SFX_GOLD_PICKUP);
            self->step++;
        }
        break;

    case 2:
        if (self->ext.timer.t == 0x10) {
            self->drawFlags = FLAG_DRAW_UNK80;
        }

        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    distX = PLAYER.posX.i.hi - self->posX.i.hi;
    distY = PLAYER.posY.i.hi - self->posY.i.hi;

    if (abs(distX) < 0xB) {
        if (abs(distY) < 0x1B) {
            g_Status.gold = CLAMP_MAX(g_Status.gold + 1, MAX_GOLD);
            g_api.PlaySfx(SFX_GOLD_PICKUP);
            DestroyEntity(self);
        }
    }
}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 37; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
