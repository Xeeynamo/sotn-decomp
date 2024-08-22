// SPDX-License-Identifier: AGPL-3.0-only
// Weapon ID #28. Used by weapons:
// Skull shield, Unknown#212
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_028_1.h"
#include "w_028_2.h"
#define g_Animset w_028_1
#define g_Animset2 w_028_2
#include "sfx.h"

extern SpriteParts D_C8000_8017A040[];
extern s8 D_C8000_8017AA98[];
extern s32 D_C8000_8017AAE0[];
extern s32 D_C8000_8017AB1C[];

static void EntityWeaponAttack(Entity* self) {
    s32 anim = 0;
    bool crouchCheck = false;
    s32 attackButton;

    if (g_HandId != 0) {
        attackButton = PAD_CIRCLE;
    } else {
        attackButton = PAD_SQUARE;
    }
    if (!(attackButton & g_Player.padPressed) && (self->step < 3)) {
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
        self->step = 3;
    }
    if (self->step != 4) {
        self->posX.val = g_Entities->posX.val;
        self->posY.val = PLAYER.posY.val;
        self->facingLeft = PLAYER.facingLeft;
    }
    if ((g_Player.unk0C & PLAYER_STATUS_UNK10000) && (self->step != 4)) {
        self->zPriority = PLAYER.zPriority + 2;
        self->step = 4;
        if (g_Player.pl_vram_flag & 1) {
            self->velocityX = PLAYER.velocityX;
        } else {
            self->velocityX = PLAYER.velocityX * 2;
        }
        self->velocityY = FIX(-3.5);
        self->ext.weapon.lifetime = 128;
        self->flags = FLAG_UNK_08000000;
        self->animCurFrame = 0x3E;
    }
    if ((PLAYER.step == Player_Crouch) && (PLAYER.step_s != 2)) {
        crouchCheck++;
    }
    switch (self->step) {
    case 0:
        SetSpriteBank1(D_C8000_8017A040);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
            self->palette = 0x128;
            self->unk5A = 0x66;
        } else {
            self->animSet = ANIMSET_OVL(0x10);
            self->palette = 0x110;
            self->unk5A = 0x64;
        }
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        g_Player.unk48 = 1;
        SetWeaponProperties(self, 0);
        self->step++;
        /* fallthrough */
    case 1:
        self->ext.weapon.anim = crouchCheck + 10;
        if (self->animFrameDuration < 0) {
            self->step++;
        }
        break;
    case 2:
        switch (PLAYER.ext.player.anim) {
        case 9:
        case 10:
        case 11:
            anim++;
            /* fallthrough */
        case 7:
            anim++;
            /* fallthrough */
        case 8:
            anim++;
            /* fallthrough */
        case 12:
            anim++;
            /* fallthrough */
        case 13:
            anim++;
            /* fallthrough */
        case 24:
        case 25:
            anim++;
            /* fallthrough */
        case 14:
        case 15:
            anim++;
            /* fallthrough */
        case 26:
            anim += 2;
            self->animFrameIdx = PLAYER.animFrameIdx;
            break;
        default:
            self->animFrameIdx = 0;
            anim += crouchCheck;
            break;
        }
        self->ext.weapon.anim = anim;
        self->animFrameDuration = 2;
        break;
    case 3:
        g_Player.unk48 = 0;
        self->ext.weapon.anim = crouchCheck + 12;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    case 4:
        self->hitboxState = 0;
        g_Player.unk48 = 0;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        self->velocityY += FIX(20.0 / 128);
        self->rotZ += 0x80;
        if (--self->ext.weapon.lifetime < 16) {
            self->drawFlags |= FLAG_DRAW_UNK80;
        }
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->step != 4) {
        g_api.PlayAnimation(D_C8000_8017AA98, D_C8000_8017AAE0);
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 28; }

extern s16 D_C8000_8017AB18;
extern s16 D_C8000_8017AB1A;

void func_C8000_8017B3D4(void) {
    RECT rect;
    s16 temp;

    if (D_C8000_8017AB1A & 1) {
        if (++D_C8000_8017AB18 >= 0x20) {
            D_C8000_8017AB1A++;
            D_C8000_8017AB18 = 0x1F;
        }
    } else {
        if (--D_C8000_8017AB18 < 0) {
            D_C8000_8017AB1A++;
            D_C8000_8017AB18 = 0;
        }
    }

    temp = g_Clut[0x113B + g_HandId * 0x180];
    temp &= 0xFFE0;
    temp += D_C8000_8017AB18;
    g_Clut[0x113B + g_HandId * 0x180] = temp;

    rect.x = 0;
    rect.y = 0xF1;
    rect.w = 0x100;
    rect.h = 3;
    LoadImage(&rect, &g_Clut[0x1100]);
}

static void EntityWeaponShieldSpell(Entity* self) {
    s32 i;
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    Primitive* prim;
    Primitive* nextPrim;
    Primitive* basePrim;
    Primitive* nextPtr;
    s16 sine;
    s16 primTop;
    s16 primBottom;
    u16 selfPosX;
    u16 selfPosY;

    u32 newUnk86;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 13);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(D_C8000_8017A040);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
            self->palette = 0x128;
            self->ext.shield.childPalette = 0x129;
            self->unk5A = 0x66;
            self->ext.shield.unk7C = 0;
            self->ext.shield.unk7D = 0x80;
        } else {
            self->animSet = ANIMSET_OVL(0x10);
            self->palette = 0x110;
            self->ext.shield.childPalette = 0x111;
            self->unk5A = 0x64;
            self->ext.shield.unk7C = 0x80;
            self->ext.shield.unk7D = 0;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        self->posY.i.hi -= 8;
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = 62;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = self->rotY = 0;
        prim->clut = 0x19F;
        prim->tpage = 0x19;
        prim->u0 = prim->u2 = 128;
        prim->u1 = prim->u3 = 128 + 79;
        prim->v0 = prim->v1 = self->ext.shield.unk7C;
        prim->v2 = prim->v3 = self->ext.shield.unk7C + 79;
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
        prim->u1 = prim->u3 = 63;
        prim->v0 = prim->v1 = self->ext.shield.unk7D + 0x30;
        prim->v2 = prim->v3 = self->ext.shield.unk7D + 0x30 + 79;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = 0x1B6;
        prim->drawMode = DRAW_HIDE;
        // Logic to copy prims from each other; may be possible to simplify
        basePrim = prim;
        prim = prim->next;
        nextPrim = prim;
        nextPtr = prim->next;
        *nextPrim = *basePrim;
        prim->next = nextPtr;

        prim->clut = self->ext.shield.childPalette + 2;
        prim->priority = 0x1B4;

        for (i = 0; i < 10; i++) {
            basePrim = prim;
            prim = prim->next;
            nextPrim = prim;
            nextPtr = prim->next;
            *nextPrim = *basePrim;
            prim->next = nextPtr;
            prim->v0 = prim->v1 = self->ext.shield.unk7D + ((i * 8) + 0x30);
            prim->v2 = prim->v3 = self->ext.shield.unk7D + ((i + 1) * 8) + 0x2F;
            prim->clut = 0x15F;
            prim->drawMode |=
                (DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP);
            prim->priority = 0x1B8;
        }
        self->ext.shield.unk8A = 0x80;
        self->ext.shield.unk90 = 0x100;
        self->ext.shield.unk84 = 0;
        self->ext.shield.unk86 = 0;
        self->ext.shield.unk92 = 0;
        self->ext.shield.unk94 = 0;
        SetSpeedX(FIX(-2));
        self->velocityY = 0;
        DestroyEntityWeapon(1);
        g_api.PlaySfx(SFX_ANIME_SWORD_C);
        g_unkGraphicsStruct.unk20 = 1;
        self->step++;
        break;
    case 1:
        DecelerateX(FIX(1.0 / 16));
        self->velocityY -= FIX(20.0 / 128);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->rotX += 12;
        self->rotY = self->rotX;
        self->ext.shield.unk82 = self->rotX * 40 / 256;
        if (self->rotX >= 0x100) {
            self->ext.shield.unk82 = 0x28;
            self->rotX = 0x100;
            self->rotY = 0x100;
            self->ext.shield.unk80 = 8;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.shield.unk80 == 0) {
            self->ext.shield.unk80 = 16;
            self->step++;
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        if (!(self->ext.shield.unk80 & 1)) {
            prim->priority = 0x1B8;
        } else {
            prim->priority = self->zPriority - 2;
        }
        self->rotX -= 16;
        if (self->rotX <= 0) {
            self->rotX = 0;
        }
        self->rotY = self->rotX;
        if (--self->ext.shield.unk80 == 0) {
            self->animCurFrame = 0;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
            for (i = 0; i < 10; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            self->ext.shield.unk80 = 0;
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            self->step++;
        }
        break;
    case 4:
        self->ext.shield.unk82 += 8;
        self->rotX += 12;
        if (self->rotX >= 0x100) {
            self->rotX = 0x100;
        }

        // newUnk86 isn't used anywhere but here, but is needed for some reason.
        newUnk86 = self->ext.shield.unk84 = self->rotX / 8;
        self->ext.shield.unk86 = newUnk86;

        prim = &g_PrimBuf[self->primIndex];
        if (prim->b3 > 8) {
            prim->b3 -= 4;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        if (!(g_Timer & 1)) {
            self->ext.shield.unk92--;
        }
        if (self->ext.shield.unk92 < 0) {
            self->ext.shield.unk92 = 0;
        }
        if ((self->rotX == 0x100) && (self->ext.shield.unk92 == 0)) {
            prim = &g_PrimBuf[self->primIndex];
            prim->b3 = 4;
            prim->drawMode |= DRAW_HIDE;
            self->step++;
        }
        self->ext.shield.unk80 = self->ext.shield.unk80 + 1;
        break;
    case 5:
        self->ext.shield.unk90 -= 10;
        if (self->ext.shield.unk90 < 0) {
            self->ext.shield.unk90 = 0;
            self->ext.shield.unk80 = 0;
            self->step++;
        }
        break;
    case 6:
        if (self->ext.shield.unk80 == 64) {
            // Create factory with blueprint 88. Child is 9, so we call Weapon
            // function 9, or func_ptr_80170024.
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xE) | 88, 0);
            g_unkGraphicsStruct.unk20 = 0;
            self->ext.shield.unk9A = self->posY.i.hi;
            SetSpeedX(FIX(-3.5));
        }
        if (64 < self->ext.shield.unk80 && self->ext.shield.unk80 < 128) {
            self->posY.i.hi = self->ext.shield.unk9A - (g_Timer & 1);
            self->posX.val += self->velocityX;
            DecelerateX(FIX(22.0 / 128));
        }
        if (128 <= self->ext.shield.unk80 && self->ext.shield.unk80 < 160) {
            self->posY.i.hi = self->ext.shield.unk9A - ((g_Timer >> 1) & 1);
            self->posX.val += self->velocityX;
            DecelerateX(FIX(22.0 / 128));
        }
        if (++self->ext.shield.unk80 == 160) {
            self->step++;
        }
        break;
    case 7:
        self->ext.shield.unk90 += 16;
        if (self->ext.shield.unk90 > 0x120) {
            prim = g_PrimBuf[self->primIndex].next;
            prim->drawMode |= DRAW_HIDE;
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            self->ext.shield.unk80 = 0x18;
            self->ext.shield.unk8A = 0x20;
            self->step++;
        }
        break;
    case 8:
        self->ext.shield.unk92++;
        self->ext.shield.unk86 += 2;
        if (self->ext.shield.unk86 < 0) {
            self->ext.shield.unk86 = 0;
        }
        self->ext.shield.unk90 -= 10;
        if (self->ext.shield.unk90 < 0) {
            self->ext.shield.unk90 = 0;
        }
        if (--self->ext.shield.unk80 == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    selfPosX = self->posX.i.hi;
    selfPosY = self->posY.i.hi;
    if (prim->b3 > 8) {
        if (g_Timer & 1) {
            prim->drawMode |= DRAW_HIDE;
        } else {
            prim->drawMode &= ~DRAW_HIDE;
        }
    }
    prim->x0 = prim->x2 = selfPosX - self->ext.shield.unk82;
    prim->x1 = prim->x3 = (selfPosX + self->ext.shield.unk82) - 1;
    prim->y0 = prim->y1 = selfPosY - self->ext.shield.unk82;
    prim->y2 = prim->y3 = (selfPosY + self->ext.shield.unk82) - 1;
    prim = prim->next;
    prim->clut = self->ext.shield.childPalette + ((g_Timer >> 1) & 1);

    top = prim->y0 = prim->y1 = selfPosY - self->ext.shield.unk86;
    bottom = (selfPosY + self->ext.shield.unk86) - 1;
    prim->y2 = prim->y3 = bottom;

    if (!self->facingLeft) {
        left = prim->x0 = prim->x2 = selfPosX - self->ext.shield.unk84;
        right = prim->x1 = prim->x3 = (selfPosX + self->ext.shield.unk84) - 1;
    } else {
        right = prim->x1 = prim->x3 = selfPosX - self->ext.shield.unk84;
        left = prim->x0 = prim->x2 = (selfPosX + self->ext.shield.unk84) - 1;
    }
    prim = prim->next;
    prim->x0 = prim->x2 = left;
    prim->x1 = prim->x3 = right;
    prim->y0 = prim->y1 = top;
    prim->y2 = prim->y3 = bottom;
    right++;
    bottom++;
    prim = prim->next;
    for (i = 0; i < 10; i++) {
        sine = (rsin((s16)D_C8000_8017AB1C[i]) >> 5) * self->ext.shield.unk92 /
               256;
        prim->x0 = left + sine;
        prim->x1 = (right + sine) - 1;
        sine = (rsin((s16)D_C8000_8017AB1C[(i + 1) % 10]) >> 5) *
               self->ext.shield.unk92 / 256;
        prim->x2 = left + sine;
        prim->x3 = (right + sine) - 1;
        sine = (rsin((s16)D_C8000_8017AB1C[(i + 6) % 10]) >> 5) *
               self->ext.shield.unk94 / 256;
        primTop = top + ((bottom - top) * i) / 10;
        primBottom = top + ((bottom - top) * (i + 1)) / 10;
        prim->y0 = primTop - sine;
        prim->y2 = primBottom - sine;

        sine = (rsin((s16)D_C8000_8017AB1C[(i + 1) % 10]) >> 5) *
               self->ext.shield.unk94 / 256;
        prim->y1 = primTop - sine;
        prim->y3 = primBottom - sine;

        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            ((rsin((s16)D_C8000_8017AB1C[i]) + 0x1000) >> 6) *
            self->ext.shield.unk90 / 256;
        prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
            ((rsin((s16)D_C8000_8017AB1C[(i + 1) % 10]) + 0x1000) >> 6) *
            self->ext.shield.unk90 / 256;
        D_C8000_8017AB1C[i] += self->ext.shield.unk8A;
        prim = prim->next;
    }
    func_C8000_8017B3D4();
}

static void func_ptr_80170024(Entity* self) {
    Primitive* prim;
    s32 xShift;
    s16 selfPosX;
    s16 selfPosY;

    switch (self->step) {
    case 0:
        if (self->ext.shield.parent->entityId == 0) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.shield.unk7D = self->ext.shield.parent->ext.shield.unk7D;
        self->ext.shield.childPalette =
            self->ext.shield.parent->ext.shield.childPalette + 3;
        self->flags |= FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        if (self->facingLeft) {
            xShift = -24;
        } else {
            xShift = 24;
        }
        self->posX.i.hi = xShift + self->posX.i.hi;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1A;
        prim->clut = 0x15E;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 63;
        prim->v0 = prim->v1 = 192;
        prim->v2 = prim->v3 = 192 + 63;
        prim->drawMode = 0;
        prim->priority = 0x1BA;

        self->ext.shield.unk84 = self->ext.shield.unk86 = 0;
        prim = prim->next;

        prim->tpage = 0x19;
        prim->u0 = prim->u1 = 64;
        prim->u2 = prim->u3 = 64 + 63;
        prim->v3 = prim->v1 = self->ext.shield.unk7D + 64;
        prim->v2 = prim->v0 = self->ext.shield.unk7D + 64 + 63;
        prim->priority = 0x1BA;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
        prim = prim->next;

        prim->tpage = 0x19;

        prim->u0 = prim->u1 = 80;
        prim->u2 = prim->u3 = 80 + 31;
        prim->v3 = prim->v1 = self->ext.shield.unk7D + 56;
        prim->v2 = prim->v0 = self->ext.shield.unk7D + 56 + 7;
        prim->priority = 0x1BA;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
        self->ext.shield.unk80 = 0x40;
        self->step++;
        break;
    case 1:
        self->ext.shield.unk84 += 2;
        if (self->ext.shield.unk84 >= 32) {
            self->ext.shield.unk84 = 32;
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode |= DRAW_HIDE;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
            self->step++;
        }
        self->ext.shield.unk86 = self->ext.shield.unk84;
        break;
    case 2:
        self->ext.shield.unkAE = self->ext.shield.parent->ext.shield.unkAE;
        SetWeaponProperties(self, 0);
        if (!self->facingLeft) {
            self->hitboxWidth = (0x118 - self->posX.i.hi) / 2;
            self->hitboxOffX = (0x118 - self->posX.i.hi) / 2;
        } else {
            self->hitboxWidth = (self->posX.i.hi + 24) / 2;
            self->hitboxOffX = (self->posX.i.hi + 24) / 2;
        }
        self->hitboxHeight = 0x10;
        if (--self->ext.shield.unk80 == 0) {
            self->hitboxState = 0;
            self->step++;
        }
        break;
    case 3:
        self->ext.shield.unk84 -= 8;
        self->ext.shield.unk86 -= 8;
        if (self->ext.shield.unk84 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->facingLeft) {
        xShift = -24;
    } else {
        xShift = 24;
    }
    prim = &g_PrimBuf[self->primIndex];
    self->posX.i.hi = xShift + self->ext.shield.parent->posX.i.hi;
    selfPosX = self->posX.i.hi;
    selfPosY = self->posY.i.hi;

    prim->y0 = prim->y1 = selfPosY - self->ext.shield.unk86;
    prim->y2 = prim->y3 = selfPosY + self->ext.shield.unk86 - 1;
    if (!self->facingLeft) {
        prim->x0 = prim->x2 = selfPosX - self->ext.shield.unk84;
        prim->x1 = prim->x3 = selfPosX + self->ext.shield.unk84 - 1;
    } else {
        prim->x1 = prim->x3 = selfPosX - self->ext.shield.unk84;
        prim->x0 = prim->x2 = selfPosX + self->ext.shield.unk84 - 1;
    }
    prim = prim->next;
    prim->y0 = prim->y1 = selfPosY - self->ext.shield.unk86;
    prim->y2 = prim->y3 = (selfPosY + self->ext.shield.unk86) - 1;
    if (!self->facingLeft) {
        prim->x0 = prim->x2 = selfPosX - self->ext.shield.unk84;
        prim->x1 = prim->x3 = selfPosX + self->ext.shield.unk84 - 1;
    } else {
        prim->x1 = prim->x3 = selfPosX - self->ext.shield.unk84;
        prim->x0 = prim->x2 = selfPosX + self->ext.shield.unk84 - 1;
    }
    prim->clut = self->ext.shield.childPalette + ((g_Timer >> 1) & 1);
    prim = prim->next;
    prim->y0 = prim->y1 = selfPosY - (self->ext.shield.unk86 / 2);
    prim->y2 = prim->y3 = selfPosY + (self->ext.shield.unk86 / 2) - 1;
    if (!self->facingLeft) {
        prim->x0 = prim->x2 = selfPosX + self->ext.shield.unk84 - 1;
        prim->x1 = prim->x3 = 288 - 16;
    } else {
        prim->x1 = prim->x3 = selfPosX - self->ext.shield.unk84;
        prim->x0 = prim->x2 = -16;
    }
    prim->clut = self->ext.shield.childPalette + ((g_Timer >> 1) & 1);
    return;
}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
