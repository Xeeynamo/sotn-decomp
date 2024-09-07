// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #19. Used by weapons:
// Neutron bomb
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_019_1.h"
#include "w_019_2.h"
#define g_Animset w_019_1
#define g_Animset2 w_019_2

extern SpriteParts D_89000_8017A040[];
extern AnimationFrame D_89000_8017A52C[];

void EntityWeaponAttack(Entity* self) {
    Primitive* prim;
    u16 baseX, baseY;
    u16 offset;

    switch (self->step) {
    case 0:
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        SetSpriteBank1(D_89000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }

        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1A;
        prim->clut = 0x1B0;
        prim->u2 = prim->u0 = 0x40;
        prim->v0 = prim->v1 = 0xC0;
        prim->u3 = prim->u1 = 0x7F;
        prim->v2 = prim->v3 = 0xFF;
        prim->r3 = prim->g3 = prim->b3 = 0;
        prim->r2 = prim->g2 = prim->b2 = 0;
        prim->r1 = prim->g1 = prim->b1 = 0;
        prim->r0 = prim->g0 = prim->b0 = 0;

        prim->priority = PLAYER.zPriority + 4;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;

        self->ext.weapon.unk7E = 0x7F;
        self->facingLeft = 0;
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_40000;
        self->zPriority = PLAYER.zPriority + 4;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ;
        self->rotX = self->rotY = 0x100;

        g_api.PlaySfx(SFX_WEAPON_APPEAR);
        g_api.PlaySfx(SFX_EXPLODE_A);
        g_Player.timers[12] = 4;
        self->step++;
        break;
    case 1:
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        if (self->ext.weapon.unk7E > 8) {
            self->ext.weapon.unk7E -= 16;
        } else {
            g_PrimBuf[self->primIndex].drawMode = DRAW_HIDE;
            self->anim = D_89000_8017A52C;
            self->ext.weapon.unk7E = 0;
            self->flags |= FLAG_UNK_100000;
            SetWeaponProperties(self, 0);
            self->step++;
        }
        break;
    case 2:
        self->hitboxState = 0;
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        if (self->animFrameDuration == 1 && self->animFrameIdx == 3) {
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
        if (self->animFrameIdx == 5) {
            self->unk6C = 0x80;
            self->flags &= ~FLAG_UNK_40000;
            self->drawFlags |= FLAG_DRAW_UNK8;
            self->step++;
        }
        break;
    case 3:
        self->rotX += 0x10;
        self->rotY = self->rotX;
        self->rotZ += 0x40;
        if (self->unk6C >= 5) {
            self->unk6C += 0xFE;
        }
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    offset = self->ext.weapon.unk7E;
    baseX = self->posX.i.hi;
    baseY = self->posY.i.hi;
    prim->x0 = prim->x2 = baseX - offset;
    prim->x1 = prim->x3 = baseX + offset;
    prim->y0 = prim->y1 = baseY - offset;
    prim->y2 = prim->y3 = baseY + offset;
    prim->b3 += 0x10;
    if (prim->b3 >= 0x80) {
        prim->b3 = 0x80;
    }
    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 = prim->r2 =
        prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
}

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 19; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
