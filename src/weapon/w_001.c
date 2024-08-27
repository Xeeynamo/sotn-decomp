// Weapon ID #1. Used by weapons:
// Knuckle duster, Jewel knuckles, Iron Fist, Fist of Tulkas, Unknown#186,
// Unknown#187, Unknown#188
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_001_1.h"
#include "w_001_2.h"
#define g_Animset w_001_1
#define g_Animset2 w_001_2
#include "sfx.h"

INCLUDE_ASM("weapon/nonmatchings/w_001", EntityWeaponAttack);

extern WeaponAnimation D_B000_8017AF44[];
extern uvPair D_B000_8017AFB8[];

s32 func_ptr_80170004(Entity* self) {
    Primitive* prim;
    s32 i;
    u8 handOffset;
    s16 x, y;
    s16 xOffset, yOffset;
    s16 posX, posY;
    uvPair* p;
    s16 animIndex;
    WeaponAnimation* anim;

    handOffset = 0;
    if (g_HandId) {
        handOffset = 1 << 7;
    }

    animIndex = (self->params & 0x7FFF) >> 8;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    anim = &D_B000_8017AF44[animIndex];
    if (PLAYER.ext.player.anim < anim->frameStart ||
        PLAYER.ext.player.anim >= (anim->frameStart + 7) || !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        prim = &g_PrimBuf[self->primIndex];

        for (i = 0; i < 16; i++) {
            prim->clut = 0x100;
            prim->tpage = 0x19;
            p = D_B000_8017AFB8;

            prim->u0 = p[0].u;
            prim->v0 = p[0].v + handOffset;
            prim->u1 = p[1].u;
            prim->v1 = p[1].v + handOffset;
            prim->u2 = p[2].u;
            prim->v2 = p[2].v + handOffset;
            prim->u3 = p[3].u;
            prim->v3 = p[3].v + handOffset;

            prim->r0 = i + 1;

            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_UNK_40 |
                             DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            prim = prim->next;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_40000 | FLAG_UNK_20000;
        SetWeaponProperties(self, 0);
        self->ext.weapon.lifetime = 128;
        self->hitboxWidth = 18;
        self->hitboxHeight = 10;
        self->hitboxOffX = 28;
        self->hitboxOffY = -12;
        self->step++;
    } else {
        if ((self->ext.weapon.lifetime & 7) == 7) {
            g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        }
        if (--self->ext.weapon.lifetime == 0) {
            g_api.PlaySfx(SFX_UNK_6F0);
            DestroyEntity(self);
            return;
        }
    }

    prim = &g_PrimBuf[self->primIndex];

    xOffset = 26;
    yOffset = -6;
    if (PLAYER.facingLeft) {
        xOffset = -xOffset;
    }

#ifdef VERSION_PSP
    xOffset = PLAYER.posX.i.hi + xOffset;
    yOffset = PLAYER.posY.i.hi + yOffset;
    if (PLAYER.drawFlags & 2) {
        yOffset -= 3;
    }
#else
    posX = xOffset + PLAYER.posX.i.hi;
    posY = yOffset + PLAYER.posY.i.hi;
    if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
        posY -= 3;
    }
#endif

    for (i = 0; i < 16; i++) {
        switch (prim->r1) {
        case 0:
            if (--prim->r0 == 0) {
#ifdef VERSION_PSP
                x = xOffset + (rand() % 24) - 12;
                y = yOffset + (rand() % 18) - 9;
#else
                x = posX + (rand() % 24) - 12;
                y = posY + (rand() % 18) - 9;
#endif

                if (!PLAYER.facingLeft) {
                    prim->x0 = prim->x2 = x - 8;
                    prim->x1 = prim->x3 = x + 8;
                } else {
                    prim->x0 = prim->x2 = x + 8;
                    prim->x1 = prim->x3 = x - 8;
                }

                prim->y0 = prim->y1 = y - 8;
                prim->y2 = prim->y3 = y + 8;
                prim->drawMode &= ~DRAW_HIDE;
                prim->r0 = 2;
                prim->r1++;
            }
            break;
        case 1:
            if (--prim->r0 == 0) {
                prim->u0 += 48;
                prim->u1 += 48;
                prim->u2 += 48;
                prim->u3 += 48;
                prim->r0 = 2;
                prim->r1++;
            }
            break;
        case 2:
            if (--prim->r0 == 0) {
                prim->u0 -= 48;
                prim->u1 -= 48;
                prim->u2 -= 48;
                prim->u3 -= 48;
                prim->r0 = 2;
                prim->r1 = 0;
                prim->drawMode |= DRAW_HIDE;
            }
            break;
        }
        prim = prim->next;
    }
}

extern AnimationFrame D_B000_8017AFC8[];

static void func_ptr_80170008(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->animSet = 9;
        self->anim = D_B000_8017AFC8;
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(FIX(-4.5));
        self->palette = PAL_OVL(0x1B0);
        self->drawMode = 0x30;
        self->posX.val += self->velocityX * 6;
        self->posY.i.hi -= 0xD;
        if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
            self->posY.i.hi -= 0x3;
        }
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotY = 0x60;
        self->rotX = 0x60;
        self->ext.factory.unkAE = self->ext.factory.parent->ext.factory.unkAE;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.factory.parent->enemyId;
        self->hitboxWidth = 10;
        self->hitboxHeight = 8;
        g_api.PlaySfx(SFX_FIRE_SHOT);
        self->step++;
        break;

    case 1:
        if (self->hitFlags) {
            DestroyEntity(self);
            return;
        }
        self->posX.val += self->velocityX;
        self->rotX += 0x10;
        self->rotY += 0x10;
        if (self->rotY >= 0x101) {
            self->rotY = 0x100;
        }
        if (self->rotX >= 0x181) {
            self->rotX = 0x180;
        }
        break;
    }
}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 1; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
