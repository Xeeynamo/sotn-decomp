// SPDX-License-Identifier: AGPL-3.0-only
// Weapon ID #10. Used by weapons:
// Iron shield, Unknown#205
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_010_1.h"
#include "w_010_2.h"
#define g_Animset w_010_1
#define g_Animset2 w_010_2
#include "items.h"
#include "sfx.h"

extern SpriteParts D_4A000_8017A040[];
extern s8 D_4A000_8017AB20;
extern AnimationFrame* D_4A000_8017AB68;
extern s16 D_4A000_8017ABBC[];
extern s16 D_4A000_8017ABDC[];

extern s32 D_4A000_8017CC1C; // g_DebugWaitInfoTimer

static void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (D_4A000_8017CC1C++ & 4) {
        FntPrint("\no\n");
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
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
        self->step = 3;
    }
    if (self->step != 4) {
        self->posX.val = PLAYER.posX.val;
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
        self->ext.timer.t = 0x80;
        self->flags = FLAG_UNK_08000000;
        self->animCurFrame = 0x3E;
    }
    if ((PLAYER.step == Player_Crouch) && (PLAYER.step_s != 2)) {
        anim2++;
    }
    if (self->step == 1 || self->step == 2) {
        if (self->hitFlags != 0) {
            // Creates func_ptr_80170004
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 56, 0);
            g_api.func_8010E168(0, 0x60);
            self->hitFlags = 0;
        }
    }
    switch (self->step) {
    case 0:
        SetSpriteBank1(D_4A000_8017A040);
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
        self->ext.shield.anim = anim2 + 10;
        if (self->animFrameDuration < 0) {
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
            self->animFrameIdx = PLAYER.animFrameIdx;
            break;
        default:
            self->animFrameIdx = 0;
            anim1 += anim2;
            break;
        }
        self->ext.shield.anim = anim1;
        self->animFrameDuration = 2;
        break;
    case 3:
        g_Player.unk48 = 0;
        self->ext.shield.anim = anim2 + 12;
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
        if (--self->ext.timer.t < 0x10) {
            self->drawFlags |= FLAG_DRAW_UNK80;
        }
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->step != 4) {
        g_api.PlayAnimation(&D_4A000_8017AB20, &D_4A000_8017AB68);
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

extern AnimationFrame D_4A000_8017ABA0[];

s32 func_ptr_80170004(Entity* self) {
    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->ext.weapon.parent->ext.weapon.equipId != ITEM_IRON_SHIELD) {
        DestroyEntity(self);
        return;
    }
    FntPrint("charah:%02x\n", self->animSet);
    FntPrint("oya_ptr:%02x\n", self->ext.weapon.parent);
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->palette = PAL_OVL(0x194);
        self->zPriority = self->ext.weapon.parent->zPriority + 4;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->flags = FLAG_UNK_100000 | FLAG_UNK_40000 | FLAG_UNK_20000;
        self->anim = D_4A000_8017ABA0;
        g_api.PlaySfx(SFX_THUNDER_A);
        self->step++;
    } else if (self->animFrameDuration < 0) {
        DestroyEntity(self);
    }
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 10; }

void EntityWeaponShieldSpell(Entity* self) {
    Entity* unusedEnt;
    Primitive* prim;
    Primitive* prevPrim;
    Primitive* nextPrim;
    bool hide;
    s32 i;
    s16 selfX;
    s16 selfY;
    s16 angle;
    s32 uFlip;

    hide = false;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x21);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        SetSpriteBank1(D_4A000_8017A040);
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
        self->posY.i.hi -= 8;
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = 0x3E;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = self->rotY = 0;
        prim = &g_PrimBuf[self->primIndex];
        prim->clut = 0x19F;
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

        self->ext.shield.unk86 = 0;
        self->ext.shield.unk84 = 2;
        self->ext.shield.unk92 = 0;
        for (i = 0; i < 16; i++) {
            prim->clut = self->ext.shield.childPalette;
            prim->tpage = 0x19;
            // uFlip will flip our u1 and u3 coordinates if needed
            uFlip = 1;
            if (self->facingLeft) {
                uFlip = -1;
            }
            prim->u0 = 0xC0;
            prim->v0 = self->ext.shield.unk7D + 0x40;
            prim->u1 =
                ((((rcos((i + 1) * 0x100) >> 4) * 0x3E) >> 8) * uFlip) + 0xC0;
            prim->v1 = self->ext.shield.unk7D +
                       (0x40 - (((rsin((i + 1) * 0x100) >> 4) * 0x3E) >> 8));
            prim->u2 = 0xC0;
            prim->v2 = self->ext.shield.unk7D + 0x40;
            prim->u3 = ((((rcos(i * 0x100) >> 4) * 0x3E) >> 8) * uFlip) + 0xC0;
            prim->v3 = self->ext.shield.unk7D +
                       (0x40 - (((rsin(i * 0x100) >> 4) * 0x3E) >> 8));
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x80;
            prim->priority = 0x1B8;
            prim->drawMode = DRAW_HIDE;
            prevPrim = prim;
            prim = prim->next;
            nextPrim = prim->next;
            *prim = *prevPrim;
            prim->next = nextPrim;
            prim->clut = 0x15F;
            prim->priority = 0x1BA;
            prim->drawMode |=
                (DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP);
            prim = prim->next;
        }
        self->ext.shield.unk8A = 0xC0;
        self->ext.shield.unk90 = 0x100;
        DestroyEntityWeapon(1);
        SetSpeedX(FIX(-2));
        self->velocityY = 0;
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

        self->ext.shield.unk82 = self->rotX * 0x28 / 256;
        if (self->rotX >= 0x100) {
            self->ext.shield.unk82 = 0x28;
            self->rotY = self->rotX = 0x100;
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
        self->rotX -= 0x10;
        if (self->rotX <= 0) {
            self->rotX = 0;
        }
        self->rotY = self->rotX;
        if (--self->ext.shield.unk80 == 0) {
            self->animCurFrame = 0;
            prim = prim->next;
            for (i = 0; i < 32; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            g_api.PlaySfx(SFX_MAGIC_WEAPON_APPEAR_B);
            self->step++;
        }
        break;
    case 4:
        self->ext.shield.unk82 += 8;
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b3 > 8) {
            prim->b3 -= 4;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        self->ext.shield.unk84 += 2;
        self->ext.shield.unk86 += 2;
        if (self->ext.shield.unk84 >= 0x3E) {
            self->ext.shield.unk84 = 0x3E;
            prim->drawMode |= DRAW_HIDE;
            self->step++;
        }
        break;
    case 5:
        self->ext.shield.unk86 -= 2;
        if (self->ext.shield.unk86 <= 0) {
            self->ext.shield.unk86 = 0;
            // This probably has to be the two swords that fly all around
            unusedEnt = g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xE) + FACTORY(0, 88), 0);
            unusedEnt = g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xE) + FACTORY(0x100, 88), 0);
            g_unkGraphicsStruct.unk20 = 0;
            self->step++;
        }
        break;
    case 6:
        self->ext.shield.unk90 -= 8;
        if (self->ext.shield.unk90 <= 0) {
            self->ext.shield.unk90 = 0;
            self->step++;
            self->ext.shield.unk80 = 0x40;
        }
        break;
    case 7:
        if (--self->ext.shield.unk80 == 0) {
            self->step++;
        }
        break;
    case 8:
        self->ext.shield.unk90 += 12;
        if (self->ext.shield.unk90 > 0x120) {
            self->ext.shield.unk90 = 0x120;
        }
        self->ext.shield.unk86 += 3;
        if (self->ext.shield.unk86 >= 0x36) {
            self->ext.shield.unk86 = 0x36;
            hide = true;
            g_api.PlaySfx(SFX_TELEPORT_BANG_B);
            self->step++;
        }
        break;
    case 9:
        self->ext.shield.unk90 -= 8;
        if (self->ext.shield.unk90 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    if (prim->b3 > 8) {
        if (g_Timer & 1) {
            prim->drawMode |= DRAW_HIDE;
        } else {
            prim->drawMode &= ~DRAW_HIDE;
        }
    }
    prim->x0 = prim->x2 = selfX - self->ext.shield.unk82;
    prim->x1 = prim->x3 = (selfX + self->ext.shield.unk82) - 1;
    prim->y0 = prim->y1 = selfY - self->ext.shield.unk82;
    prim->y2 = prim->y3 = (selfY + self->ext.shield.unk82) - 1;
    prim = prim->next;
    for (i = 0; i < 16; i++) {
        // clang-format off
        prim->x0 = selfX + (((rcos((i+1)*0x100 + self->ext.shield.unk92) >> 4) * self->ext.shield.unk86) >> 8);
        prim->y0 = selfY - (((rsin((i+1)*0x100 + self->ext.shield.unk92) >> 4) * self->ext.shield.unk86) >> 8);
        prim->x1 = selfX + (((rcos((i+1)*0x100) >> 4) * self->ext.shield.unk84) >> 8);
        prim->y1 = selfY - (((rsin((i+1)*0x100) >> 4) * self->ext.shield.unk84) >> 8);
        prim->x2 = selfX + (((rcos(i*0x100 + self->ext.shield.unk92) >> 4) * self->ext.shield.unk86) >> 8);
        prim->y2 = selfY - (((rsin(i*0x100 + self->ext.shield.unk92) >> 4) * self->ext.shield.unk86) >> 8);
        prim->x3 = selfX + (((rcos(i*0x100) >> 4) * self->ext.shield.unk84) >> 8);
        prim->y3 = selfY - (((rsin(i*0x100) >> 4) * self->ext.shield.unk84) >> 8);
        // clang-format on
        if (hide != 0) {
            prim->drawMode |= DRAW_HIDE;
        }
        prevPrim = prim;
        prim = prim->next;
        nextPrim = prim->next;
        *prim = *prevPrim;
        prim->next = nextPrim;
        angle = D_4A000_8017ABBC[i];
        prim->r2 = prim->g2 = prim->b2 = prim->b3 = 0;
        prim->g3 = prim->r3 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        angle = D_4A000_8017ABBC[(i + 1) % 16];
        prim->r0 = prim->g0 = prim->b0 = prim->b1 = 0;
        prim->g1 = prim->r1 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        D_4A000_8017ABBC[i] += self->ext.shield.unk8A;
        prim->clut = 0x15F;
        prim->priority = 0x1BA;
        prim->drawMode = (DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP);
        prim = prim->next;
    }
}

// Probably the swords that fly all around
void func_ptr_80170024(Entity* self) {
    s16 left;
    s16 left2;
    s16 top;
    s16 top2;
    s16 right;
    s16 right2;
    s16 bottom;
    s16 bottom2;
    FakePrim* fakePrim;
    Primitive* prevPrim;
    Primitive* nextPrim;
    Primitive* prim;
    s16 angle;
    s32 xShift;
    s32 yShift;
    s32 i;
    s16 selfX;
    s16 selfY;
    s16 upperParams;

    upperParams = (self->params & 0x7F00) >> 8;
    if (self->ext.shield.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        self->facingLeft = self->ext.shield.parent->facingLeft;
        self->ext.shield.childPalette =
            self->ext.shield.parent->ext.shield.childPalette + 1 + upperParams;
        self->ext.shield.unk7D = self->ext.shield.parent->ext.shield.unk7D;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x12);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        fakePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
        fakePrim->drawMode = DRAW_HIDE;
        fakePrim->priority = 0;
        fakePrim->posY.val = self->posY.val;
        fakePrim->posX.val = self->posX.val;
        fakePrim->x0 = self->posX.i.hi;
        fakePrim->y0 = self->posY.i.hi;
        fakePrim->velocityX.val = FIX(2.25);
        if (self->facingLeft) {
            fakePrim->velocityX.val = -fakePrim->velocityX.val;
        }
        prim = (Primitive*)fakePrim->next;
        prim->clut = self->ext.shield.childPalette;
        prim->tpage = 0x19;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x7F;
        prim->v0 = prim->v1 = self->ext.shield.unk7D + 0x30;
        prim->v2 = prim->v3 = self->ext.shield.unk7D + 0x4F;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = 0x1BC;
        prim->drawMode = 0;
        for (i = 0; i < 16; i++) {
            prevPrim = prim;
            prim = prim->next;
            nextPrim = prim->next;
            *prim = *prevPrim;
            prim->next = nextPrim;
            prim->u0 = prim->u2 = i * 128 / 16;
            prim->u1 = prim->u3 = ((i + 1) * 128) / 16 - 1;
            prim->clut = 0x15F;
            prim->priority = 0x1BE;
            prim->drawMode |=
                (DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP);
        }
        self->ext.shield.unk8A = 0x80;
        self->ext.shield.unk90 = 0x100;
        if (!((self->facingLeft ^ upperParams) & 1)) {
            self->ext.shield.unk9E = -0x100;
            self->ext.shield.unk9C = 0x800;
            self->rotZ = 0x200;
        } else {
            self->ext.shield.unk9E = 0x100;
            self->ext.shield.unk9C = 0;
            self->rotZ = 0x600;
        }
        self->ext.shield.unkAE = self->ext.shield.parent->ext.shield.unkAE;
        SetWeaponProperties(self, 0);
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0x10;
        self->ext.shield.unkA0 = 0x20;
        g_api.PlaySfx(SFX_UNK_69D);
        self->step += 1;
        break;
    case 1:
        self->ext.shield.unk90 -= 8;
        if (self->ext.shield.unk90 < 0) {
            self->ext.shield.unk90 = 0;
        }
        if (self->ext.shield.unkA0) {
            if (--self->ext.shield.unkA0 == 0) {
                self->flags |= FLAG_UNK_08000000;
                self->flags &= ~FLAG_UNK_04000000;
            }
        } else {
            if (self->ext.shield.unk9A < 0x280) {
                self->ext.shield.unk9A += 0x18;
            }
            self->rotZ += self->ext.shield.unk9E * 7 / 4;
            // Not really sure how this block works. xShift is probably a fake
            // variable reuse.
            xShift = self->ext.shield.unk9C;
            self->ext.shield.unk9C += self->ext.shield.unk9E;
            if (((xShift ^ self->ext.shield.unk9C) & 0x1000) &&
                (self->params & 0x100)) {
                g_api.PlaySfx(SFX_UNK_689);
            }

            fakePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
            fakePrim->posX.i.hi = fakePrim->x0;
            fakePrim->posY.i.hi = fakePrim->y0;
            fakePrim->posX.val += fakePrim->velocityX.val;
            fakePrim->x0 = fakePrim->posX.i.hi;
            fakePrim->y0 = fakePrim->posY.i.hi;
        }
        break;
    }
    fakePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
    angle = self->ext.shield.unk9C;
    xShift = rcos(angle) * self->ext.shield.unk9A;
    yShift = -rsin(angle) * self->ext.shield.unk9A;
    self->posX.val = fakePrim->posX.val + xShift;
    self->posY.val = fakePrim->posY.val + yShift;
    self->ext.shield.unk98++;
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = (Primitive*)fakePrim->next;
    angle = self->rotZ + 0x787;
    prim->x0 = left = selfX + (((rcos(angle) >> 4) * 0x42) >> 8);
    prim->y0 = top = selfY - (((rsin(angle) >> 4) * 0x42) >> 8);
    angle = self->rotZ + 0x79;
    prim->x1 = right = selfX + (((rcos(angle) >> 4) * 0x42) >> 8);
    prim->y1 = bottom = selfY - (((rsin(angle) >> 4) * 0x42) >> 8);
    angle = self->rotZ + 0x879;
    prim->x2 = left2 = selfX + (((rcos(angle) >> 4) * 0x42) >> 8);
    prim->y2 = top2 = selfY - (((rsin(angle) >> 4) * 0x42) >> 8);
    angle = self->rotZ + 0xF87;
    prim->x3 = right2 = selfX + (((rcos(angle) >> 4) * 0x42) >> 8);
    prim->y3 = bottom2 = selfY - (((rsin(angle) >> 4) * 0x42) >> 8);
    prim = prim->next;
    for (i = 0; i < 16; i++) {
        prim->x0 = left + (right - left) * i / 16;
        prim->x1 = left + (right - left) * (i + 1) / 16;
        prim->x2 = left2 + (right2 - left2) * i / 16;
        prim->x3 = left2 + (right2 - left2) * (i + 1) / 16;
        prim->y0 = top + (bottom - top) * i / 16;
        prim->y1 = top + (bottom - top) * (i + 1) / 16;
        prim->y2 = top2 + (bottom2 - top2) * i / 16;
        prim->y3 = top2 + (bottom2 - top2) * (i + 1) / 16;
        angle = D_4A000_8017ABDC[i];
        prim->r0 = prim->g0 = prim->b0 = prim->r2 = prim->g2 = prim->b2 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        angle = D_4A000_8017ABDC[(i + 1) % 16];
        prim->r1 = prim->g1 = prim->b1 = prim->r3 = prim->g3 = prim->b3 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        D_4A000_8017ABDC[i] += self->ext.shield.unk8A;
        prim = prim->next;
    }
}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
