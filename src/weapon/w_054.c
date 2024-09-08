// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #54. Used by weapons:
// Gurthang, Unknown#195
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_054_1.h"
#include "w_054_2.h"
#define g_Animset w_054_1
#define g_Animset2 w_054_2

extern WeaponAnimation D_17E000_8017AEC4[];
extern u16 D_17E000_8017AEF4[];
extern u16 D_17E000_8017AEFC[];

void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s16 animIndex;
    Primitive* prim;
    s32 i;
    s16 x;
    s32 y;
    s32 x2;
    s32 offsetIndex;
    u8 brightness;
    u16* xValues;
    s32 primIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    animIndex = (self->params >> 8) & 0x7F;

    if (g_Player.timers[11]) {
        animIndex = 2;
    }

    anim = &D_17E000_8017AEC4[animIndex];

    if (PLAYER.ext.player.anim < anim->frameStart ||
        PLAYER.ext.player.anim >= (anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = PAL_DRA(0x110);
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;

        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0xC);

        self->primIndex = primIndex;
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 12; i++) {
                if (i <= 3) {
                    prim->r2 = rand() & 3;
                    prim->b2 = 1;
                }
                if (i < 7) {
                    prim->r2 = rand() & 7;
                    prim->b2 = 1;
                } else if (i & 1) {
                    prim->r2 = rand() & 0xF;
                    prim->b2 = 2;
                } else {
                    prim->r2 = rand() & 7;
                    prim->b2 = 1;
                }
                prim->r3 = i / 6;
                if (i == 11) {
                    prim->r2 = 0x18;
                    prim->r3 = 2;
                    prim->b2 = 3;
                }
                prim->r0 = prim->r1 = 255;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = rand() & 0x1F;

                prim->priority = PLAYER.zPriority;
                prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_HIDE;
                prim = prim->next;
            }
        }

        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        SetWeaponProperties(self, 0);

        if (animIndex) {
            if (g_Player.timers[11]) {
                self->attack *= 2;
            }
            if (g_Player.timers[11] < 0x38) {
                g_Player.timers[11] = 0x38;
                if (animIndex == 1) {
                    g_api.CreateEntFactoryFromEntity(
                        self, FACTORY(61, 0x11), 0);
                }
            }
        }
        self->step++;
    }

    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;

    if (PLAYER.animFrameDuration == 1 &&
        PLAYER.animFrameIdx == anim->soundFrame) {
        g_api.PlaySfx(anim->soundId);
    }

    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;

    if (self->animCurFrame != 0xD && self->animCurFrame != 0x22 &&
        self->animCurFrame != 0x2C && self->animCurFrame != 0x3E) {
        return;
    }

    if (self->primIndex != -1) {
        i = 0;

        xValues = D_17E000_8017AEF4;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];

        for (; i < 12; i++) {
            switch (self->animCurFrame) {
            case 0xD:
                offsetIndex = 0;
                break;
            case 0x22:
                offsetIndex = 1;
                break;
            case 0x2C:
                offsetIndex = 2;
                break;
            case 0x3E:
                offsetIndex = 3;
                break;
            }

            x2 = -1;
            x = xValues[offsetIndex] - i;
            if (self->facingLeft != 0) {
                x = -x;
                x2 = 1;
            }
            prim->x2 = x2 + prim->x2;

            y = D_17E000_8017AEFC[offsetIndex] + (i / 6);

            prim->x0 = x + self->posX.i.hi;
            prim->x1 = prim->x0 + prim->x2;

            prim->y0 = y + self->posY.i.hi;
            prim->y1 = y + self->posY.i.hi + prim->r3;

            if (prim->r2 > prim->r3) {
                prim->r3 += prim->b2;
            }

            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
        }
    }
}

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 54; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
