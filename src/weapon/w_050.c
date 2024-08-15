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
            g_api.PlaySfx(0x669);
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

INCLUDE_ASM("weapon/nonmatchings/w_050", func_ptr_80170008);

INCLUDE_ASM("weapon/nonmatchings/w_050", func_ptr_8017000C);

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
