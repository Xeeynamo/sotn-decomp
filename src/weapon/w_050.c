// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #50. Used by weapons:
// Icebrand, Unknown#181, Unknown#199, Unknown#200, Unknown#201
#include "weapon_private.h"
#include "gen/w_050_1.h"
#include "gen/w_050_2.h"
#define g_Animset w_050_1
#define g_Animset2 w_050_2
#include "sfx.h"

static u16 pal0[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x8000, 0xA821, 0x9DC0, 0xA821, 0xA821, 0xA821, 0xA821, 0x843F,
     0xB0E4, 0x9CA4, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2F3},
    {0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xED8C, 0xED8C, 0xED8C, 0x843F,
     0xBC00, 0xBC00, 0xED8C, 0xED8C, 0xED8C, 0xD294, 0xFFFF},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xE021, 0xE021, 0x801F,
     0x9C00, 0xB800, 0xE021, 0x0000, 0x0000, 0xD294, 0xEAD3},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xA0C0, 0x0000, 0x843F,
     0x0000, 0xA800, 0x0000, 0xF608, 0x0000, 0xD294, 0xE24C},
    {0x0000, 0x8000, 0x9C00, 0x9DC0, 0x9C00, 0x9C00, 0x9C00, 0x9C00, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2D1},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0xD400, 0xD400, 0xD400, 0xD400, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xCCA0, 0x0000, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xEA90}};
static u16 pal1[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x8007, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, 0x843F,
     0xB148, 0xA928, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x0000, 0x0000, 0x0000, 0xE717, 0xE717, 0xE717, 0x843F,
     0xA0E6, 0xA0E6, 0xE717, 0xE717, 0xE717, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xB56A, 0xA927, 0x801F,
     0x9062, 0x98C6, 0xB148, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xA4E6, 0x0000, 0x843F,
     0x0000, 0x9483, 0x0000, 0xA0C4, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x98C6, 0x9DC0, 0x98C6, 0x98C6, 0x98C6, 0x98C6, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x0000, 0x9DC0, 0xA94A, 0xA94A, 0xA94A, 0xA94A, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x94A5, 0x0000, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xEB5A}};
static u16 pal2[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x8000, 0x800F, 0x800F, 0x800F, 0x800F, 0x800F, 0x800F, 0x83E0,
     0x800F, 0x8CB4, 0x0000, 0x0000, 0x0000, 0xD294, 0xCF1C},
    {0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xA818, 0xB0B8, 0xAC38, 0x83E0,
     0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x8014, 0x940C, 0x83E0,
     0x8005, 0x844E, 0x807D, 0x0000, 0x0000, 0xD294, 0xE35C},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xA008, 0x0000, 0x83E0,
     0x0000, 0x8008, 0x0000, 0x806C, 0x0000, 0xD294, 0xBEBC},
    {0x0000, 0x8000, 0x800B, 0x9DC0, 0x800B, 0x800B, 0x800B, 0x800B, 0x83E0,
     0xB9C0, 0x800B, 0x0000, 0x0000, 0x0000, 0xD294, 0xAABC},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x8011, 0x8011, 0x8011, 0x8011, 0x83E0,
     0xB9C0, 0x8011, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x8008, 0x0000, 0x83E0,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0x9E1C}};
static u16 pal3[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x8000, 0x8900, 0x8900, 0x8900, 0x8900, 0x8902, 0x8904, 0x843F,
     0x9541, 0x95E1, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2D1},
    {0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xA208, 0xA208, 0xA208, 0x843F,
     0x9541, 0x9541, 0xA208, 0xA208, 0xA208, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x8160, 0x8920, 0x801F,
     0x8080, 0x88E1, 0x8160, 0x0000, 0x0000, 0xD294, 0xE796},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x94A0, 0x0000, 0x843F,
     0x0000, 0x8080, 0x0000, 0xA264, 0x0000, 0xD294, 0xAB8D},
    {0x0000, 0x8000, 0x80E0, 0x80E0, 0x80E0, 0x80E0, 0x80E0, 0x80E0, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2B2},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x8200, 0x8200, 0x8200, 0x8200, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0xA686, 0x0000, 0x0000, 0xA520, 0x0000, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xB792}};
static u16 pal4[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x8000, 0x817F, 0x81B6, 0x81DF, 0x827F, 0xA2FE, 0xD77F, 0x843F,
     0x819E, 0x9A1F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xB77D, 0xB77D, 0xB77D, 0x843F,
     0x811E, 0x811E, 0xB77D, 0xB77D, 0xB77D, 0xD294, 0xFFFF},
    {0x0000, 0x8000, 0x0000, 0x9A1F, 0x0000, 0x0000, 0x8E3F, 0x99DF, 0x801F,
     0x80B0, 0x811A, 0x9ADF, 0x0000, 0x0000, 0xD294, 0xE35C},
    {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x80FE, 0x0000, 0x843F,
     0x0000, 0x80B1, 0x0000, 0x8157, 0x0000, 0xD294, 0xD31C},
    {0x0000, 0x8000, 0x8158, 0x81B6, 0x819B, 0x823D, 0xA2FF, 0xD31F, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0xB77D, 0xB77D, 0xB77D, 0xB77D, 0xB77D, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
    {0x0000, 0x8000, 0x0000, 0x819E, 0x0000, 0x0000, 0x811E, 0x0000, 0x843F,
     0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C}};
static u16 anim0[] = {
    WPOSE(1, 1),  WPOSE(2, 2),  WPOSE(3, 2),  WPOSE(4, 2), WPOSE(5, 2),
    WPOSE(6, 3),  WPOSE(7, 3),  WPOSE(8, 3),  WPOSE(9, 3), WPOSE(10, 4),
    WPOSE(11, 4), WPOSE(12, 4), WPOSE(13, 4), WPOSE_END};
static u16 anim1[] = {
    WPOSE(14, 5), WPOSE(15, 6), WPOSE(16, 6), WPOSE(17, 6), WPOSE(18, 6),
    WPOSE(19, 7), WPOSE(20, 7), WPOSE(21, 7), WPOSE(22, 7), WPOSE(31, 4),
    WPOSE(32, 4), WPOSE(33, 4), WPOSE(34, 4), WPOSE_END};
static u16 anim2[] = {
    WPOSE(14, 5),  WPOSE(23, 8),  WPOSE(24, 9),  WPOSE(25, 8),  WPOSE(26, 9),
    WPOSE(27, 10), WPOSE(28, 10), WPOSE(29, 10), WPOSE(30, 10), WPOSE(31, 4),
    WPOSE(32, 4),  WPOSE(33, 4),  WPOSE(34, 4),  WPOSE_END};
static u16 anim3[] = {
    WPOSE(35, 11), WPOSE(36, 12), WPOSE(37, 12), WPOSE(38, 12),
    WPOSE(39, 12), WPOSE(40, 13), WPOSE(41, 13), WPOSE(42, 13),
    WPOSE(43, 13), WPOSE(44, 4),  WPOSE_END};
static u16 anim4[] = {
    WPOSE(45, 14), WPOSE(46, 15), WPOSE(47, 15), WPOSE(48, 15),
    WPOSE(49, 15), WPOSE(50, 16), WPOSE(51, 16), WPOSE(52, 16),
    WPOSE(53, 16), WPOSE(62, 4),  WPOSE_END};
static u16 anim5[] = {
    WPOSE(45, 14), WPOSE(54, 17), WPOSE(55, 17), WPOSE(56, 17),
    WPOSE(57, 17), WPOSE(58, 18), WPOSE(59, 18), WPOSE(60, 18),
    WPOSE(61, 18), WPOSE(62, 4),  WPOSE_END};
static s8 hitboxes[][4] = {
    {0, 0, 0, 0},     {4, -23, 8, 5},   {30, -17, 35, 8}, {30, -14, 18, 4},
    {-32, -31, 0, 0}, {-4, -6, 8, 5},   {22, 0, 35, 8},   {22, 3, 18, 4},
    {29, 22, 13, 11}, {12, 7, 19, 12},  {14, 14, 18, 4},  {1, -25, 8, 5},
    {27, -19, 35, 8}, {27, -16, 18, 4}, {-8, -26, 8, 5},  {24, -17, 35, 8},
    {24, -14, 18, 4}, {23, 0, 27, 14},  {18, 2, 21, 11},  {29, -14, 34, 4},
    {21, 3, 34, 4},   {28, 21, 12, 10}, {26, -16, 34, 4}, {23, -14, 34, 4},
    {22, 3, 26, 10}};
static u16* anims[] = {anim0, anim0, anim1, anim2, anim3, anim4, anim5};
static WeaponAnimation D_162000_8017AFC0[] = {
    {anims, hitboxes, 0, SFX_WEAPON_SWISH_C, 0x41, 4},
    {anims, hitboxes, 0, SFX_WEAPON_SWISH_C, 0x41, 2},
    {anims, hitboxes, 0, SFX_FIRE_SHOT, 0x41, 4},
    {anims, hitboxes, 0, SFX_FIRE_SHOT, 0x41, 4}};
static u8 uv_coords[6][8] = {
    {0x00, 0x50, 0x10, 0x50, 0x00, 0x60, 0x10, 0x60},
    {0x10, 0x50, 0x20, 0x50, 0x10, 0x60, 0x20, 0x60},
    {0x70, 0x40, 0x80, 0x40, 0x70, 0x50, 0x80, 0x50},
    {0x70, 0x30, 0x78, 0x30, 0x70, 0x38, 0x78, 0x38},
    {0x78, 0x30, 0x80, 0x30, 0x78, 0x38, 0x80, 0x38},
    {0x70, 0x38, 0x78, 0x38, 0x77, 0x40, 0x78, 0x40}};
static s16 D_162000_8017B030[] = {
    24, -14, 64, 0,   24, -14, 64, 0,   20, 2, 64, 0, 18, 14,
    48, 34,  24, -16, 64, 0,   24, -14, 64, 0, 24, 4, 48, 34};
static u16* g_WeaponCluts[] = {pal1, pal4, pal0, pal2, pal3};
static s32 g_HandId = HAND_ID;

static s32 prev_player_pose;
static Point16 D_162000_8017CBFC[80];

#include "shared.h"

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
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = PAL_UNK_110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }

        self->palette += anim->palette;
        self->flags = FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;

        if (animIndex == 1) {
            g_api.PlaySfx(SFX_MAGIC_WEAPON_APPEAR_A);
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x3A, 0), 0);
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x40, 0), 0);
        }
        SetWeaponProperties(self, 0);
        prev_player_pose = 0;
        self->step++;
    }
    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
    if ((PLAYER.poseTimer == 1) && (PLAYER.pose == anim->soundFrame)) {
        g_api.PlaySfx(anim->soundId);
    }
    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    if ((prev_player_pose == 0) && (PLAYER.pose == 1)) {

        if (animIndex == PLAYER.pose) {
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x44, 0), 0);
            g_api.PlaySfx(SFX_FM_EXPLODE_B);
            g_api.PlaySfx(SFX_MAGIC_SWITCH);
        }
        hand = (g_HandId + 1) << 0xC;
        temp = FACTORY(0x61, animIndex);
        g_api.CreateEntFactoryFromEntity(self, hand + temp, 0);
    }
    prev_player_pose = PLAYER.pose;
    self->drawFlags = PLAYER.drawFlags;
    self->scaleY = PLAYER.scaleY;
    self->rotPivotY = PLAYER.rotPivotY;
}

s32 func_162000_8017B784(Primitive* prim, s16 x, s16 y) {
    s16 size;
    u8* uvPtr;

    // Should be able to do this as an array access but nope
    uvPtr = (u8*)uv_coords;
    uvPtr += (prim->b0 * 8);

    if (prim->b0 >= 3) {
        size = 4;
    } else {
        size = 6;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    prim->x0 = x - size;
    prim->y0 = y - size;
    prim->x1 = x + size;
    prim->y1 = y - size;
    prim->x2 = x - size;
    prim->y2 = y + size;
    prim->x3 = x + size;
    prim->y3 = y + size;

    prim->u0 = *uvPtr++;
    prim->v0 = *uvPtr++;
    prim->u1 = *uvPtr++;
    prim->v1 = *uvPtr++;
    prim->u2 = *uvPtr++;
    prim->v2 = *uvPtr++;
    prim->u3 = *uvPtr++;
    prim->v3 = *uvPtr;
    prim->b1++;
    if (!(prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}

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

s32 func_ptr_80170004(Entity* self) {
    Primitive* prim;
    s32 i;
    s16 prim_x, prim_y;
    s16 x, y;
    s16 angle;
    s32 magnitude;
    s16 xOffset;
    s32 params;

    if (PLAYER.ext.player.anim <= 0x40 || PLAYER.ext.player.anim >= 0x48 ||
        !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }

    params = self->params & 0xFF; // unused, for PSP

    xOffset = 0xC;
    if (PLAYER.facingLeft) {
        xOffset = -xOffset;
    }
    x = PLAYER.posX.i.hi + xOffset;
    y = PLAYER.posY.i.hi - 26;
    if (PLAYER.drawFlags & ENTITY_SCALEY) {
        y -= 5;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 80);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 80; i++) {
            prim->clut = PAL_UNK_1B0;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() % 24) + 1;
            prim->g2 = 0;
            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.weapon.lifetime = 40;
        self->step++;
        break;
    case 1:
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < LEN(D_162000_8017CBFC); i++) {
        switch (prim->g0) {
        case 0:
            if (--prim->g1 == 0) {
                angle = rand();
                magnitude = (rand() & 0x1F) + 32;
                D_162000_8017CBFC[i].x =
                    x + (((rcos(angle) >> 4) * magnitude) >> 8);
                D_162000_8017CBFC[i].y =
                    y - (((rsin(angle) >> 4) * magnitude) >> 8);
                prim->g0++;
            }
            break;
        case 1:
            prim_x = D_162000_8017CBFC[i].x -
                     (D_162000_8017CBFC[i].x - x) * prim->g2 / 15;
            // n.b.! this should simplify to something similar to `prim_x`
            // above, and on PSP that simplified version matches, but
            // currently it does not match on PSX.
            prim_y = D_162000_8017CBFC[i].y -
                     (D_162000_8017CBFC[i].y -
                      (D_162000_8017CBFC[i].y -
                       (D_162000_8017CBFC[i].y - y) * prim->g2)) /
                         15;
            prim->g2++;
            if (((s16)func_162000_8017B784(prim, prim_x, prim_y)) < 0) {
                prim->drawMode |= DRAW_HIDE;
                prim->g0++;
            } else {
                prim->drawMode &= ~DRAW_HIDE;
            }
            break;
        }
        prim = prim->next;
    }
}

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
    if (PLAYER.drawFlags & ENTITY_SCALEY) {
        self->posY.i.hi = offsetY - 0x1F;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
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
            prim->clut = PAL_FILL_WHITE;
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

        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
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

s32 func_ptr_80170010(Entity* self) {
    const int PrimCount = 8;
    Primitive* prim;
    Point16 point;
    s32 params;
    s32 i;
    s16 x, y;
    s16 baseX, baseY;
    s16 prim_x, prim_y;
    s32 result;

    if (PLAYER.ext.player.anim < 0x41 || PLAYER.ext.player.anim > 0x47 ||
        !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }

    params = (self->params & 0x7F00) >> 8;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        if (params == 1) {
            func_162000_8017BA38(self, &point, true);
        } else {
            func_162000_8017BA38(self, &point, false);
        }

        baseX = point.x;
        baseY = point.y;

        if (PLAYER.drawFlags & ENTITY_SCALEY) {
            if ((PLAYER.ext.player.anim - 0x41) == 2 ||
                (PLAYER.ext.player.anim - 0x41) == 3) {
                self->posY.i.hi -= 1;
            } else {
                self->posY.i.hi -= 3;
            }
        }

        x = self->posX.i.hi;
        y = self->posY.i.hi;

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            prim_x = baseX * i / 8 + x;
            prim_y = baseY * i / 8 + y;

            prim_y += rand() % 10;
            prim_x += rand() % 4;

            D_162000_8017CBFC[i].x = prim_x;
            D_162000_8017CBFC[i].y = prim_y;
            prim->clut = PAL_UNK_1B0;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (i * 2) + 1;
            prim->g2 = 0;
            prim->priority = PLAYER.zPriority;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            if (params == 0) {
                prim->drawMode =
                    DRAW_UNK_200 | DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 |
                    DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            }
            prim = prim->next;
        }
        self->ext.weapon.lifetime = 0x18;
        self->step++;
        break;

    case 1:
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        switch (prim->g0) {
        case 0:
            if (--prim->g1 == 0) {
                prim->g0++;
            }
            break;
        case 1:
            x = D_162000_8017CBFC[i].x;
            y = D_162000_8017CBFC[i].y;
            result = func_162000_8017B784(prim, x, y);
            D_162000_8017CBFC[i].y--;
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
}

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
