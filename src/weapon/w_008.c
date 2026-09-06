// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #8. Used by weapons:
// Leather shield, Unknown#203
#define SHIELDSPELL_S32
#include "weapon_private.h"
#include "gen/w_008_1.h"
#include "gen/w_008_2.h"
#define g_Animset w_008_1
#define g_Animset2 w_008_2
#include "sfx.h"

static u16 pal_0[N_ARRAY_PAL][COLORS_PER_PAL] = {
    {0x0000, 0x8421, 0x8444, 0x8467, 0x84AB, 0x88ED, 0x8D30, 0x9573, 0x9994,
     0x9DB6, 0xA1F7, 0xA619, 0xE2F4, 0xAE7C, 0xCA52, 0xB6DF},
    {0x0000, 0xD71D, 0xAD6F, 0x9D6D, 0x9972, 0xAA98, 0x9063, 0x9CC6, 0xA508,
     0xB16B, 0xB9CE, 0xC210, 0xCE73, 0xD6B5, 0xE318, 0xEF7B}};
static AnimationFrame anim_00[] = {POSE(2, 0x01, 1), POSE_LOOP(0)};
static AnimationFrame anim_01[] = {POSE(2, 0x02, 2), POSE_LOOP(0)};
static AnimationFrame anim_09[] = {
    POSE(2, 0x03, 3), POSE(2, 0x04, 3), POSE(2, 0x05, 3), POSE(2, 0x06, 3),
    POSE(2, 0x07, 3), POSE(2, 0x08, 3), POSE(2, 0x09, 4), POSE(2, 0x0A, 1),
    POSE(2, 0x0B, 1), POSE(2, 0x0C, 1), POSE_LOOP(0)};
static AnimationFrame anim_08[] = {
    POSE(3, 0x0D, 1),  POSE(3, 0x0E, 7),  POSE(3, 0x0F, 8),  POSE(3, 0x10, 9),
    POSE(3, 0x11, 10), POSE(3, 0x12, 11), POSE(3, 0x13, 12), POSE(3, 0x14, 13),
    POSE(3, 0x15, 14), POSE(3, 0x16, 13), POSE(3, 0x17, 12), POSE(3, 0x18, 11),
    POSE(3, 0x19, 10), POSE(3, 0x1A, 9),  POSE(3, 0x1B, 8),  POSE(3, 0x1C, 7),
    POSE_LOOP(0)};
static AnimationFrame anim_07[] = {
    POSE(1, 0x24, 1), POSE(1, 0x25, 1), POSE(1, 0x26, 1), POSE(1, 0x27, 1),
    POSE(1, 0x28, 1), POSE(1, 0x29, 1), POSE(1, 0x2A, 1), POSE(1, 0x2B, 1),
    POSE(1, 0x2C, 1), POSE(1, 0x2D, 1), POSE(1, 0x2E, 1), POSE(1, 0x2F, 1),
    POSE(1, 0x30, 1), POSE_LOOP(0)};
static AnimationFrame anim_06[] = {
    POSE(1, 0x2A, 1), POSE(1, 0x2B, 1), POSE(1, 0x2C, 1), POSE(1, 0x2D, 1),
    POSE(1, 0x2E, 1), POSE(1, 0x2F, 1), POSE(1, 0x30, 1), POSE_LOOP(0)};
static AnimationFrame anim_05[] = {
    POSE(2, 0x21, 1), POSE(2, 0x22, 1), POSE(2, 0x23, 1), POSE(2, 0x24, 1),
    POSE(2, 0x25, 1), POSE(2, 0x26, 1), POSE(2, 0x27, 1), POSE(2, 0x28, 1),
    POSE(2, 0x29, 1), POSE(2, 0x2A, 1), POSE(2, 0x2B, 1), POSE(2, 0x2C, 1),
    POSE(2, 0x2D, 1), POSE(2, 0x2E, 1), POSE(2, 0x2F, 1), POSE(2, 0x30, 1),
    POSE_LOOP(0)};
static AnimationFrame anim_10[] = {
    POSE(2, 0x31, 1), POSE(2, 0x32, 1), POSE(2, 0x33, 1), POSE_END};
static AnimationFrame anim_11[] = {
    POSE(2, 0x34, 2), POSE(2, 0x35, 2), POSE(2, 0x36, 2), POSE_END};
static AnimationFrame anim_12[] = {
    POSE(2, 0x33, 1), POSE(2, 0x32, 1), POSE(2, 0x31, 1), POSE_END};
static AnimationFrame anim_13[] = {
    POSE(2, 0x36, 2), POSE(2, 0x35, 2), POSE(2, 0x34, 2), POSE_END};
static AnimationFrame anim_04[] = {
    POSE(4, 0x1D, 1), POSE(4, 0x1E, 1), POSE_LOOP(0)};
static AnimationFrame anim_02[] = {
    POSE(2, 0x1F, 6), POSE(2, 0x20, 6), POSE_LOOP(0)};
static AnimationFrame anim_03[] = {
    POSE(3, 0x37, 17), POSE(3, 0x38, 17), POSE(3, 0x38, 17), POSE(3, 0x38, 16),
    POSE(3, 0x38, 15), POSE(3, 0x39, 1),  POSE(3, 0x3A, 1),  POSE(3, 0x3B, 1),
    POSE(3, 0x3C, 1),  POSE(3, 0x3D, 1),  POSE(3, 0x01, 1),  POSE(3, 0x01, 1),
    POSE(3, 0x01, 1),  POSE(3, 0x01, 1),  POSE(3, 0x01, 1),  POSE_LOOP(0)};

static s8 hitboxes[][4] = {
    {0, 0, 0, 0},    {14, -7, 4, 12},  {14, 13, 4, 12}, {-11, -7, 4, 12},
    {1, -5, 4, 12},  {-32, -31, 0, 0}, {22, -6, 4, 12}, {15, -6, 4, 12},
    {16, -5, 4, 12}, {17, -4, 4, 12},  {18, -3, 4, 12}, {19, -2, 4, 12},
    {20, -1, 4, 12}, {21, 0, 4, 12},   {22, 1, 4, 12},  {12, -5, 4, 12},
    {10, -3, 4, 12}, {8, -1, 4, 12}};

static AnimationFrame* anims[] = {
    anim_00, anim_01, anim_02, anim_03, anim_04, anim_05, anim_06,
    anim_07, anim_08, anim_09, anim_10, anim_11, anim_12, anim_13};

static s32 shieldAngles[] = {
    0x0000, 0x0200, 0x0400, 0x0600, 0x0800, 0x0A00, 0x0C00, 0x0E00,
    0x1000, 0x1200, 0x1400, 0x1600, 0x1800, 0x1A00, 0x1C00, 0x1E00};

static u16* g_WeaponCluts[] = {(u16*)pal_0, (u16*)pal_0};
static s32 g_HandId = HAND_ID;

#include "shared.h"

static void EntityWeaponAttack(Entity* self) {
    s32 anim1;
    s32 anim2;
    s32 attackButton;

    anim1 = 0;
    anim2 = 0;
    if (g_HandId) {
        attackButton = PAD_CIRCLE;
    } else {
        attackButton = PAD_SQUARE;
    }
    if (!(attackButton & g_Player.padPressed) && (self->step < 3)) {
        self->poseTimer = 0;
        self->pose = 0;
        self->step = 3;
    }
    if (self->step != 4) {
        self->posX.val = PLAYER.posX.val;
        self->posY.val = PLAYER.posY.val;
        self->facingLeft = PLAYER.facingLeft;
    }
    if ((g_Player.status & PLAYER_STATUS_UNK10000) && (self->step != 4)) {
        self->zPriority = PLAYER.zPriority + 2;
        self->step = 4;
        if (g_Player.vram_flag & TOUCHING_GROUND) {
            self->velocityX = PLAYER.velocityX;
        } else {
            self->velocityX = PLAYER.velocityX * 2;
        }
        self->velocityY = FIX(-3.5);
        self->ext.timer.t = 0x80;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animCurFrame = 0x3E;
    }
    if ((PLAYER.step == Player_Crouch) && (PLAYER.step_s != 2)) {
        anim2++;
    }
    switch (self->step) {
    case 0:
        SetSpriteBank1(g_Animset);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
            self->palette = PAL_UNK_128;
            self->unk5A = 0x66;
        } else {
            self->animSet = ANIMSET_OVL(0x10);
            self->palette = PAL_UNK_110;
            self->unk5A = 0x64;
        }
        self->flags = FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        g_Player.unk48 = 1;
        SetWeaponProperties(self, 0);
        self->step++;
        /* fallthrough */
    case 1:
        self->ext.shield.anim = anim2 + 10;
        if (self->poseTimer < 0) {
            self->step++;
        }
        break;
    case 2:
        switch (PLAYER.ext.player.anim) {
        case 9:
        case 10:
        case 11:
            anim1++;
            /* fallthrough */
        case 7:
            anim1++;
            /* fallthrough */
        case 8:
            anim1++;
            /* fallthrough */
        case 12:
            anim1++;
            /* fallthrough */
        case 13:
            anim1++;
            /* fallthrough */
        case 24:
        case 25:
            anim1++;
            /* fallthrough */
        case 14:
        case 15:
            anim1++;
            /* fallthrough */
        case 26:
            anim1 += 2;
            self->pose = PLAYER.pose;
            break;
        default:
            self->pose = 0;
            anim1 += anim2;
            break;
        }
        self->ext.shield.anim = anim1;
        self->poseTimer = 2;
        break;
    case 3:
        g_Player.unk48 = 0;
        self->ext.shield.anim = anim2 + 12;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    case 4:
        self->hitboxState = 0;
        g_Player.unk48 = 0;
        self->drawFlags |= ENTITY_ROTATE;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        self->velocityY += FIX(20.0 / 128);
        self->rotate += 0x80;
        if (--self->ext.timer.t < 0x10) {
            self->drawFlags |= ENTITY_BLINK;
        }
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->step != 4) {
        g_api.PlayAnimation(&hitboxes[0][0], anims);
    }
    self->drawFlags = PLAYER.drawFlags;
    self->scaleY = PLAYER.scaleY;
    self->rotPivotY = PLAYER.rotPivotY;
}

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 8; }

static s32 EntityWeaponShieldSpell(Entity* self) {
    s16 back;
    s16 front;
    s16 top;
    s16 bottom;

    Entity* unusedEnt;
    Primitive* prim;
    Primitive* prevPrim;
    Primitive* nextPrim;
    s32 i;
    s16 selfY;
    s16 baseCoord; // used for multiple stuff. Sometimes selfX, but not always

    s16 angle;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 11);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(g_Animset);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
            self->palette = PAL_UNK_128;
            self->ext.shield.childPalette = 0x129;
            self->unk5A = 0x66;
            self->ext.shield.unk7C = 0;
            self->ext.shield.unk7D = 0x80;
        } else {
            self->animSet = ANIMSET_OVL(0x10);
            self->palette = PAL_UNK_110;
            self->ext.shield.childPalette = PAL_UNK_111;
            self->unk5A = 0x64;
            self->ext.shield.unk7C = 0x80;
            self->ext.shield.unk7D = 0;
        }
        self->posY.i.hi -= 8;
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = 0x3E;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;

        self->scaleX = self->scaleY = 0;
        prim = &g_PrimBuf[self->primIndex];
        prim->clut = PAL_UNK_19F;
        prim->tpage = 0x19;

        prim->u0 = prim->u2 = 0x80;
        prim->u1 = prim->u3 = 0x80 + 0x4F;
        prim->v0 = prim->v1 = self->ext.shield.unk7C + 0;
        prim->v2 = prim->v3 = self->ext.shield.unk7C + 0x4F;

        self->ext.shield.unk82 = 0;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = self->zPriority - 4;
        prim->drawMode =
            DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim = prim->next;
        prim->clut = self->ext.shield.childPalette;
        prim->tpage = 0x19;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x47;
        prim->v0 = prim->v1 = self->ext.shield.unk7D + 0x30;
        prim->v2 = prim->v3 = self->ext.shield.unk7D + 0x67;
        self->ext.shield.unk84 = self->ext.shield.unk86 = 0;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = 0x1BC;
        prim->drawMode = DRAW_HIDE;
        for (i = 0; i < 9; i++) {
            prevPrim = prim;
            prim = prim->next;
            nextPrim = prim->next;
            *prim = *prevPrim;
            prim->next = nextPrim;
            prim->u0 = prim->u2 = i * 72 / 9;
            prim->u1 = prim->u3 = (i + 1) * 72 / 9 - 1;
            prim->clut = PAL_FILL_WHITE;
            prim->priority = 0x1BE;
            prim->drawMode |=
                (DRAW_TPAGE2 + DRAW_TPAGE + DRAW_COLORS + DRAW_TRANSP);
        }
        self->ext.shield.unk92 = self->ext.shield.unk94 = 0;
        self->ext.shield.unk8A = 0x40;
        self->ext.shield.unk90 = 0x100;
        SetSpeedX(FIX(-2));
        self->velocityY = 0;
        DestroyEntityWeapon(1);
        g_api.PlaySfx(SFX_ANIME_SWORD_C);
        g_unkGraphicsStruct.unk28 = 1;
        self->step++;
        break;
    case 1:
        DecelerateX(FIX(1.0 / 16));
        self->velocityY -= FIX(20.0 / 128);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->scaleX += 12;
        self->scaleY = self->scaleX;

        self->ext.shield.unk82 = self->scaleX * 0x28 / 256;
        if (self->scaleX >= 0x100) {
            self->ext.shield.unk82 = 0x28;
            self->scaleY = self->scaleX = 0x100;
            self->ext.shield.unk80 = 8;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.shield.unk80 == 0) {
            self->ext.shield.unk80 = 0x10;
            self->step++;
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        if (!(self->ext.shield.unk80 & 1)) {
            prim->priority = 0x1BC;
        } else {
            prim->priority = self->zPriority - 2;
        }
        self->scaleX -= 0x10;
        if (self->scaleX <= 0) {
            self->scaleX = 0;
        }
        self->scaleY = self->scaleX;
        if (--self->ext.shield.unk80 == 0) {
            self->animCurFrame = 0;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
            for (i = 0; i < 9; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            self->ext.shield.unk80 = 0x20;
            g_api.PlaySfx(SFX_TRANSFORM_3X);
            self->step++;
        }
        break;
    case 4:
        self->ext.shield.unk82 += 8;
        self->scaleX += 16;
        if (self->scaleX >= 0x100) {
            self->scaleX = 0x100;
        }
        self->ext.shield.unk84 = self->scaleX * 36 / 256;
        self->ext.shield.unk86 = self->scaleX * 28 / 256;
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b3 > 8) {
            prim->b3 -= 4;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        if (--self->ext.shield.unk80 == 0) {
            self->step++;
        }
        break;
    case 5:
        self->ext.shield.unk90 -= 4;
        if (self->ext.shield.unk90 < 0) {
            self->ext.shield.unk90 = 0;
            self->step++;
        }
        break;
    case 6:
        self->ext.shield.unk90 += 0x10;
        if (self->ext.shield.unk90 > 0x120) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            // Blueprint 55 has child 39, EntityPlayerPinkEffect
            g_api.CreateEntFactoryFromEntity(self, FACTORY(55, 8), 0);
            self->step++;
        }
        break;
    case 7:
        if (self->ext.shield.unk84 > 2) {
            self->ext.shield.unk86 -= 2;
        }
        if (self->ext.shield.unk90 > 8) {
            self->ext.shield.unk90 -= 8;
        }
        self->ext.shield.unk94 += 6;
        if (self->ext.shield.unk94 > 0xC0) {
            g_unkGraphicsStruct.unk28 = 0;
            DestroyEntity(self);
            return;
        }
        break;
    }
    baseCoord = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    if (prim->b3 > 8) {
        if (g_Timer & 1) {
            prim->drawMode |= DRAW_HIDE;
        } else {
            prim->drawMode &= ~DRAW_HIDE;
        }
    }
    prim->x0 = prim->x2 = baseCoord - self->ext.shield.unk82;
    prim->x1 = prim->x3 = (baseCoord + self->ext.shield.unk82) - 1;
    prim->y0 = prim->y1 = selfY - self->ext.shield.unk82;
    prim->y2 = prim->y3 = (selfY + self->ext.shield.unk82) - 1;
    prim = prim->next;
    top = prim->y0 = prim->y1 = selfY - self->ext.shield.unk86;
    bottom = prim->y2 = prim->y3 = (selfY + self->ext.shield.unk86) - 1;
    if (!self->facingLeft) {
        back = prim->x0 = prim->x2 = baseCoord - self->ext.shield.unk84;
        front = prim->x1 = prim->x3 = (baseCoord + self->ext.shield.unk84) - 1;
    } else {
        front = prim->x1 = prim->x3 = baseCoord - self->ext.shield.unk84;
        back = prim->x0 = prim->x2 = (baseCoord + self->ext.shield.unk84) - 1;
    }

    front++;
    bottom++;
    prim = prim->next;
    for (i = 0; i < 9; i++) {
        angle = shieldAngles[i];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk94 / 256;
        prim->y0 = top + baseCoord;
        prim->y2 = (bottom + baseCoord) - 1;
        angle = shieldAngles[(i + 1) % 9];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk94 / 256;
        prim->y1 = top + baseCoord;
        prim->y3 = (bottom + baseCoord) - 1;
        prim->x0 = prim->x2 = back + (((front - back) * i) / 9);
        prim->x1 = prim->x3 = back + (((front - back) * (i + 1)) / 9);
        angle = shieldAngles[(i + 6) % 9];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk92 / 256;
        prim->x0 += baseCoord;
        prim->x1 += baseCoord;
        angle = shieldAngles[(i + 7) % 9];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk92 / 256;
        prim->x2 += baseCoord;
        prim->x3 += baseCoord;
        angle = shieldAngles[i];
        prim->r0 = prim->g0 = prim->b0 = prim->r2 = prim->g2 = prim->b2 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        angle = shieldAngles[(i + 1) % 9];
        prim->r1 = prim->g1 = prim->b1 = prim->r3 = prim->g3 = prim->b3 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        shieldAngles[i] += self->ext.shield.unk8A;
        prim = prim->next;
    }
}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
