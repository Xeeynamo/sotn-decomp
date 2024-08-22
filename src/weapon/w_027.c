// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #27. Used by weapons:
// Medusa shield, Unknown#211
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "w_027_1.h"
#include "w_027_2.h"
#define g_Animset w_027_1
#define g_Animset2 w_027_2
#include "shared.h"
#include "sfx.h"

extern SpriteParts D_C1000_8017A040[];
extern s8 D_C1000_8017AC0C[];
extern s32 D_C1000_8017AC54[];
extern AnimationFrame D_C1000_8017AC8C[];
extern AnimationFrame D_C1000_8017ACB4[];
extern s32 D_C1000_8017C6EC; // g_DebugWaitInfoTimer

static void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (D_C1000_8017C6EC++ & 4) {
        FntPrint("\no\n\0"); // TODO: remove extra NUL byte padding
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

static void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (!PadRead(0))
        DebugShowWaitInfo(msg);
}

// Duplicate of Weapon 28!
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
        SetSpriteBank1(D_C1000_8017A040);
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
        g_api.PlayAnimation(D_C1000_8017AC0C, D_C1000_8017AC54);
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

static int GetWeaponId(void) { return 27; }

static void EntityWeaponShieldSpell(Entity* self) {
    Primitive* prim;
    s16 selfPosX;
    s16 selfPosY;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(D_C1000_8017A040);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
            self->palette = 0x128;
            self->ext.shield.childPalette = 0x137;
            self->unk5A = 0x66;
            self->ext.shield.unk7C = 0;
            self->ext.shield.unk7D = 0x80;
        } else {
            self->animSet = ANIMSET_OVL(0x10);
            self->palette = 0x110;
            self->ext.shield.childPalette = 0x11F;
            self->unk5A = 0x64;
            self->ext.shield.unk7C = 0x80;
            self->ext.shield.unk7D = 0;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        self->posY.i.hi -= 8;
        self->zPriority = 0x1B6;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = 0x3E;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = self->rotY = 0;
        prim->clut = 0x19F;
        prim->tpage = 0x19;
        prim->u0 = prim->u2 = 0x80;
        prim->u1 = prim->u3 = 0x80 + 0x4F;
        prim->v0 = prim->v1 = self->ext.shield.unk7C;
        prim->v2 = prim->v3 = self->ext.shield.unk7C + 0x4F;
        self->ext.shield.unk82 = 0;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = 0x1B4;
        prim->drawMode = 0x75;
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
            self->rotY = self->rotX = 0x100;
            self->ext.shield.unk80 = 8;
            self->anim = D_C1000_8017AC8C;
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->flags |= FLAG_UNK_100000;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.shield.unk80 == 0) {
            self->anim = D_C1000_8017ACB4;
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->step++;
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        self->ext.shield.unk82 += 8;
        if (prim->b3 > 8) {
            prim->b3 -= 4;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        if (self->ext.shield.unk82 >= 160) {
            prim->b3 = 6;
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode |= 8;
            self->ext.shield.unk80 = 4;
            // Blueprint 98 has child 9, which makes func_ptr_80170024.
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xE) | 98, 0);
            self->ext.shield.unk80 = 80;
            g_unkGraphicsStruct.unk20 = 0;
            self->step++;
        }
        break;
    case 4:
        if (self->ext.shield.unk80 == 64) {
            self->anim = D_C1000_8017AC8C;
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
        }
        if (--self->ext.shield.unk80 == 0) {
            self->step++;
        }
        break;
    case 5:
        self->rotX -= 12;
        self->rotY = self->rotX;
        if (self->rotX < 0) {
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
    prim->x1 = prim->x3 = selfPosX + self->ext.shield.unk82 - 1;
    prim->y0 = prim->y1 = selfPosY - self->ext.shield.unk82;
    prim->y2 = prim->y3 = selfPosY + self->ext.shield.unk82 - 1;
    return;
}

static void func_ptr_80170024(Entity* self) {
    Primitive* prim;
    Primitive* basePrim;
    s16 angle;
    s16 temp_s1;
    s16 temp_v0_8;
    s16 var_s4;
    s16 var_v0;
    s32 temp_a2_2;

    s32 i;
    u16 selfPosX;
    u16 selfPosY;

    s16 bottom;
    s16 right;
    s16 top;
    s16 left;

    s16 iterations;

    s32 xShift;
    s32 yShift;

    s32 var_s7 = 0;
    s32 var_s8 = 0;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 18);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        if (g_HandId != 0) {
            self->ext.medshieldlaser.childPalette = 0x129;
            self->ext.medshieldlaser.unk7D = 0x80;
        } else {
            self->ext.medshieldlaser.childPalette = 0x111;
            self->ext.medshieldlaser.unk7D = 0;
        }
        self->flags |= FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        if ((self->params & 0xFF) != 0) {
            if (self->facingLeft) {
                self->posX.i.hi -= 14;
            } else {
                self->posX.i.hi += 14;
            }
        } else if (self->facingLeft) {
            self->posX.i.hi -= 6;
        } else {
            self->posX.i.hi += 6;
        }
        if (!self->facingLeft) {
            self->ext.medshieldlaser.unk86 =
                0x700 - ((self->params & 0xFF) << 9);
        } else {
            self->ext.medshieldlaser.unk86 =
                ((self->params & 0xFF) << 9) + 0x100;
        }
        self->ext.medshieldlaser.unk96 = 0x50;
        self->ext.medshieldlaser.unk8A = 0x1000;
        self->ext.medshieldlaser.unk9C = 0x400;
        self->ext.medshieldlaser.unk9E = -0x58;
        self->ext.medshieldlaser.unk98 = 0;
        self->ext.medshieldlaser.target = g_api.func_80118970();
        self->ext.medshieldlaser.unk94 = 1;
        for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
             prim = prim->next) {
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x80;
            angle = self->ext.medshieldlaser.unk86 + 0x400;
            prim->x0 = self->posX.i.hi + (rcos(angle) >> 9);
            prim->y0 = self->posY.i.hi - (rsin(angle) >> 9);
            angle = self->ext.medshieldlaser.unk86 - 0x400;
            prim->x2 = self->posX.i.hi + (rcos(angle) >> 9);
            prim->y2 = self->posY.i.hi - (rsin(angle) >> 9);
            prim->tpage = 0x19;
            prim->clut = self->ext.medshieldlaser.childPalette;
            prim->priority = 0x1BC;
            prim->drawMode = 0x39;
        }
        self->ext.medshieldlaser.unkA0 = 0x300;
        self->ext.medshieldlaser.unk80 = 0;
        g_api.PlaySfx(0x6B2);
        self->step++;
        break;
    case 1:
        if ((self->ext.medshieldlaser.unk9C & 0x800) &&
            !(self->ext.medshieldlaser.unkA4 & 0x800) &&
            (-0x120 <= self->posX.i.hi && self->posX.i.hi <= 0x120) &&
            (0 <= self->posY.i.hi && self->posY.i.hi <= 0x100)) {
            g_api.PlaySfx(0x6B2);
        }
        self->ext.medshieldlaser.unkA4 = self->ext.medshieldlaser.unk9C;
        temp_v0_8 = g_api.func_80118B18(
            self, self->ext.medshieldlaser.target, self->facingLeft);
        if (temp_v0_8 >= 0) {
            temp_a2_2 = self->ext.medshieldlaser.unk86 & 0xFFF;
            // This use of "right" is so fake it's not even funny.
            right = temp_a2_2;
            var_v0 = abs(right - temp_v0_8);
            if (var_v0 < self->ext.medshieldlaser.unk96) {
                self->ext.medshieldlaser.unk96 = var_v0;
            }
            if ((right < temp_v0_8) && (var_v0 >= 0x800) ||
                (right >= temp_v0_8) && (var_v0 < 0x800)) {
                self->ext.medshieldlaser.unk86 =
                    (temp_a2_2 - self->ext.medshieldlaser.unk96) & 0xFFF;
            } else {
                self->ext.medshieldlaser.unk86 =
                    (self->ext.medshieldlaser.unk96 + temp_a2_2) & 0xFFF;
            }
        }
        self->ext.medshieldlaser.unk9C += self->ext.medshieldlaser.unk9E;
        temp_s1 =
            SquareRoot0(0x01000000 - (rsin(self->ext.medshieldlaser.unk9C) *
                                      rsin(self->ext.medshieldlaser.unk9C)));
        self->ext.medshieldlaser.unk98 -=
            ((rsin(self->ext.medshieldlaser.unk9C) << 0xC) >> 8);

        temp_s1 -= self->ext.medshieldlaser.unkA0 *
                   self->ext.medshieldlaser.unk98 / 0x10000;
        if (--self->ext.medshieldlaser.unkA0 < 0) {
            self->ext.medshieldlaser.unkA0 = 0;
        }
        xShift = ((rcos(self->ext.medshieldlaser.unk86) * temp_s1) >> 7) * 3;
        yShift = -((rsin(self->ext.medshieldlaser.unk86) * temp_s1) >> 7) * 3;

        self->posX.val += xShift;
        self->posY.val += yShift;
        var_s7 = -(self->ext.medshieldlaser.unk98 >> 0xF);

        self->ext.medshieldlaser.unk96 += 8;
        if (self->ext.medshieldlaser.unk96 > 0x100) {
            self->ext.medshieldlaser.unk96 = 0x100;
        }
        if (++self->ext.medshieldlaser.unk94 > 0x80) {
            self->ext.medshieldlaser.unk94 = 0x80;
        }
        break;
    }

    if ((self->posX.i.hi < -0x200 || self->posX.i.hi > 0x200) ||
        (self->posY.i.hi < -0xC0 || self->posY.i.hi > 0x1A0)) {
        DestroyEntity(self);
        return;
    }
    if (!(g_Timer & 1)) {
        // Blueprint 100 has child 10, to spawn func_ptr_80170028
        g_api.CreateEntFactoryFromEntity(
            self, ((g_HandId + 1) << 0xE) | 100, 0);
    }
    selfPosX = self->posX.i.hi;
    selfPosY = self->posY.i.hi;
    if (self->ext.medshieldlaser.unk98 > 0) {
        var_s4 = 8 - (self->ext.medshieldlaser.unk98 >> 16);
        if (var_s4 < 0) {
            var_s4 = 1;
        }
    } else {
        var_s4 = 8 - (self->ext.medshieldlaser.unk98 >> 0x13);
        if (var_s4 > 16) {
            var_s4 = 16;
        }
    }
    // This variable literally never gets set anywhere in this function.
    // I hate this game.
    if (var_s8 != 0) {
        var_s4 = 1;
    }
    prim = &g_PrimBuf[self->primIndex];
    left = prim->x0;
    top = prim->y0;
    right = prim->x2;
    bottom = prim->y2;
    if (self->ext.medshieldlaser.unk94 < 0x13) {
        for (i = 0; i < self->ext.medshieldlaser.unk94; i++) {
            if (i == self->ext.medshieldlaser.unk94 - 1) {
                prim->x0 = left;
                prim->y0 = top;
                prim->x2 = right;
                prim->y2 = bottom;
                angle = self->ext.medshieldlaser.unk86 + 0x400;
                prim->x1 = selfPosX + (((rcos(angle) >> 4) * var_s4) >> 8);
                prim->y1 =
                    var_s7 + (selfPosY - (((rsin(angle) >> 4) * var_s4) >> 8));
                angle = self->ext.medshieldlaser.unk86 - 0x400;
                prim->x3 = selfPosX + (((rcos(angle) >> 4) * var_s4) >> 8);
                prim->y3 =
                    var_s7 + (selfPosY - ((rsin(angle) >> 4) * var_s4 >> 8));
                prim->drawMode &= ~DRAW_HIDE;
            }
            left = prim->x1;
            top = prim->y1;
            right = prim->x3;
            bottom = prim->y3;
            prim = prim->next;
        }
    } else {
        for (i = 0; i < 17; i++) {
            basePrim = prim;
            prim = prim->next;
            *basePrim = *prim;
            basePrim->next = prim;
        }
        prim->x0 = prim->x1;
        prim->y0 = prim->y1;
        prim->x2 = prim->x3;
        prim->y2 = prim->y3;
        angle = self->ext.medshieldlaser.unk86 + 0x400;
        prim->x1 = selfPosX + (((rcos(angle) >> 4) * var_s4) >> 8);
        prim->y1 = var_s7 + (selfPosY - (((rsin(angle) >> 4) * var_s4) >> 8));
        angle = self->ext.medshieldlaser.unk86 - 0x400;
        prim->x3 = selfPosX + (((rcos(angle) >> 4) * var_s4) >> 8);
        prim->y3 = var_s7 + (selfPosY - (((rsin(angle) >> 4) * var_s4) >> 8));
    }
    iterations = self->ext.medshieldlaser.unk94;
    if (self->ext.medshieldlaser.unk94 >= 0x13) {
        iterations = 0x12;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < iterations; i++) {
        prim->u0 = prim->u2 = ((i * 3) << 5) / iterations;
        prim->u1 = prim->u3 = (((i + 1) * 0x60) / iterations) - 1;
        prim->v0 = prim->v1 = self->ext.medshieldlaser.unk7D + 0x30;
        prim->v2 = prim->v3 = self->ext.medshieldlaser.unk7D + 0x3F;
        prim = prim->next;
    }
}

static void func_ptr_80170028(Entity* self) {
    Entity* parent = self->ext.medshieldlaser.parent;
    if (parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->ext.weapon.equipId = parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->hitboxHeight = 6;
        self->hitboxWidth = 6;
        self->ext.medshieldlaser.unk80 = 6;
        self->step++;
    } else if (--self->ext.medshieldlaser.unk80 == 0) {
        DestroyEntity(self);
    }

    if (self->hitFlags != 0) {
        if (++self->ext.medshieldlaser.unkA2 >= 6) {
            self->ext.medshieldlaser.parent->ext.weapon.unk90 = 0;
        }
        self->hitFlags = 0;
    }
}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
