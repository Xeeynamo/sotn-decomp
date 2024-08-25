// Weapon ID #50. Used by weapons:
// Icebrand, Unknown#181, Unknown#199, Unknown#200, Unknown#201
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_050_1.h"
#include "w_050_2.h"
#define g_Animset w_050_1
#define g_Animset2 w_050_2
#include "sfx.h"

extern WeaponAnimation D_162000_8017AFC0[];
extern SpriteParts D_162000_8017A040[];
extern s32 D_162000_8017CBF8;

void EntityWeaponAttack(Entity* self) {
    s8 animIndex = (self->params & 0x7FFF) >> 8;
    WeaponAnimation* anim = &D_162000_8017AFC0[animIndex];
    s32 hand, temp;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    if ((PLAYER.ext.player.anim < anim->frameStart) ||
        (PLAYER.ext.player.anim >= anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(D_162000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }

        self->palette += anim->palette;
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;

        if (animIndex == 1) {
            g_api.PlaySfx(SFX_MAGIC_WEAPON_APPEAR_A);
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x3A, 0);
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x40, 0);
        }
        SetWeaponProperties(self, 0);
        D_162000_8017CBF8 = 0;
        self->step++;
    }
    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
    if ((PLAYER.animFrameDuration == 1) &&
        (PLAYER.animFrameIdx == anim->soundFrame)) {
        g_api.PlaySfx(anim->soundId);
    }
    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    if ((D_162000_8017CBF8 == 0) && (PLAYER.animFrameIdx == 1)) {

        if (animIndex == PLAYER.animFrameIdx) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x44, 0);
            g_api.PlaySfx(SFX_FM_EXPLODE_B);
            g_api.PlaySfx(SFX_UNK_69D);
        }
        hand = (g_HandId + 1) << 0xC;
        temp = ((animIndex << 0x10) + 0x61);
        g_api.CreateEntFactoryFromEntity(self, hand + temp, 0);
    }
    D_162000_8017CBF8 = PLAYER.animFrameIdx;
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

extern u8 D_162000_8017B000[6][8];

s32 func_162000_8017B784(Primitive* prim, s32 x, s32 y) {
    s32 size;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
    u8* uvPtr;

    // Should be able to do this as an array access but nope
    uvPtr = &D_162000_8017B000;
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

extern s16 D_162000_8017B030[];

void func_162000_8017B87C(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0x41;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] * 2 / 3);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] * 2 / 3;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_162000_8017B030[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] * 2 / 3;
    }
}

void func_162000_8017BA38(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0x41;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] / 2);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] / 2;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_162000_8017B030[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] / 2;
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_050", func_ptr_80170004);

void func_ptr_80170008(Entity* self) {
    const int PrimCount = 16;
    Primitive* prim;
    s16 angle;
    s32 magnitude;
    s32 i;
    s16 offsetX, offsetY;
    s16 baseX, baseY;
    u8 color;

    if (PLAYER.ext.player.anim <= 0x40 || PLAYER.ext.player.anim >= 0x48 ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }
    offsetX = 0xC;
    if (PLAYER.facingLeft) {
        offsetX = -0xC;
    }
    self->posX.i.hi = PLAYER.posX.i.hi + offsetX;

    offsetY = PLAYER.posY.i.hi;
    self->posY.i.hi = offsetY - 0x1A;
    if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
        self->posY.i.hi = offsetY - 0x1F;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_40000 | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            angle = i << 8;
            prim->u0 = +0x20 + ((rcos(angle) * 2) >> 8);
            prim->v0 = -0x20 - ((rsin(angle) * 2) >> 8);
            angle = (i + 1) << 8;
            prim->u1 = +0x20 + ((rcos(angle) * 2) >> 8);
            prim->v1 = -0x20 - ((rsin(angle) * 2) >> 8);
            if (prim->v0 < 4) {
                prim->v0 = 0xFF;
            }
            if (prim->v1 < 4) {
                prim->v1 = 0xFF;
            }
            prim->u2 = prim->u3 = 0x20;
            prim->v2 = prim->v3 = 0xE0;
            prim->clut = 0x15F;
            prim->tpage = 0x1A;
            prim->r1 = prim->b1 = prim->g1 = 0;
            prim->r0 = prim->b0 = prim->g0 = 0;
            prim->b2 = prim->b3 = prim->g2 = prim->g3 = prim->r2 = prim->r3 =
                0xFF;
            prim->type = PRIM_GT4;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.weapon.lifetime = 4;
        self->ext.weapon.unk7E = 0x28;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->step++;
        break;
    case 1:
        if (self->ext.weapon.lifetime < 0x28) {
            self->ext.weapon.lifetime += 6;
        }
        if (--self->ext.weapon.unk7E == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->hitboxWidth = self->ext.weapon.lifetime - 4;
    self->hitboxHeight = self->ext.weapon.lifetime - 4;

    color = 0x80;
    if (self->ext.weapon.unk7E < 0x10) {
        color = self->ext.weapon.unk7E * 0x10;
    }

    baseX = self->posX.i.hi;
    baseY = self->posY.i.hi;
    magnitude = self->ext.weapon.lifetime;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        angle = i << 8;
        prim->x3 = baseX;
        prim->x2 = baseX;
        prim->y3 = baseY;
        prim->y2 = baseY;
        prim->r2 = prim->r3 = prim->b2 = prim->b3 = prim->g2 = prim->g3 = color;
        prim->x0 = baseX + (((rcos(angle) >> 4) * magnitude) >> 8);
        prim->y0 = baseY - (((rsin(angle) >> 4) * magnitude) >> 8);
        angle = (i + 1) << 8;
        prim->x1 = baseX + (((rcos(angle) >> 4) * magnitude) >> 8);
        prim->y1 = baseY - (((rsin(angle) >> 4) * magnitude) >> 8);
        prim = prim->next;
    }
}

void func_ptr_8017000C(Entity* self) {
    const int PrimCount = 0x20;
    Primitive* prim;
    Point16 point;
    s16 posX, posY;
    s16 offsetX, offsetY;
    s16 randomX, randomY;
    s32 i;

    func_162000_8017B87C(self, &point, true);
    self->facingLeft = PLAYER.facingLeft;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_40000 | FLAG_UNK_20000;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        offsetX = point.x;
        offsetY = point.y;

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            prim->r1 = 0x20;
            prim->g1 = 0x20;
            prim->b1 = 0x20;

            prim->r0 = (rand() & 0x1F) - 0x80;
            prim->g0 = (rand() & 0x1F) + 0x60;
            prim->b0 = (rand() & 0x1F) + 0xE0;

            randomY = (rand() % 24) - 12;
            randomX = (rand() % 24) - 12;

            prim->x0 = posX + randomX;
            prim->y0 = posY + randomY;

            prim->x1 = offsetX + prim->x0;
            prim->y1 = offsetY + prim->y0;

            prim->r2 = 0;
            prim->r3 = (rand() % 5) + 1;
            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_HIDE | DRAW_COLORS | DRAW_TRANSP;

            prim = prim->next;
        }

        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxOffX = 0x18;
        self->hitboxWidth = 0x18;
        self->hitboxHeight = 8;
        self->hitboxOffY = 0;
        self->ext.weapon.lifetime = 8;
        self->step++;
        break;
    case 1:
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        switch (prim->r2) {
        case 0:
            if (--prim->r3 == 0) {
                prim->drawMode &= ~DRAW_HIDE;
                prim->r2++;
            }
            break;
        case 1:
            prim->drawMode |= DRAW_HIDE;
            prim->r2++;
            break;
        }
        prim = prim->next;
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_050", func_ptr_80170010);

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 50; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
