// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #25. Used by weapons:
// Goddess shield, Unknown#209
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "w_025_1.h"
#include "w_025_2.h"
#define g_Animset w_025_1
#define g_Animset2 w_025_2
#include "shared.h"
#include "sfx.h"

extern SpriteParts D_B3000_8017A040[];
extern s8 D_B3000_8017AA18;
extern AnimationFrame* D_B3000_8017AA60;
extern s32 D_B3000_8017AA98[];

void func_B3000_8017AF14(const char* fmt, u_long end) {
    while (PadRead(0) != end) {
        FntPrint(fmt);
        DrawSync(0);
        VSync(0);
        FntFlush(-1);
    }
}

static void EntityWeaponAttack(Entity* self) {
    s32 anim1;
    s32 anim2;
    s32 attackButton;

    anim1 = 0;
    anim2 = 0;
    if (self->params & 0x8000) {
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
    switch (self->step) {
    case 0:
        SetSpriteBank1(D_B3000_8017A040);
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
        g_api.PlayAnimation(&D_B3000_8017AA18, &D_B3000_8017AA60);
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

static int GetWeaponId(void) { return 25; }

static void EntityWeaponShieldSpell(Entity* self) {
    Entity* unusedEnt;
    Primitive* prim;
    Primitive* prevPrim;
    Primitive* nextPrim;
    s32 i;
    s16 selfY;
    s16 selfX;

    s16 angle;
    s16 baseCoord;
    s16 back;
    s16 front;
    s16 top;
    s16 bottom;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x11);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(D_B3000_8017A040);
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
        prim->clut = self->ext.shield.childPalette;
        prim->tpage = 0x19;
        prim->u0 = prim->u2 = 0x60;
        prim->u1 = prim->u3 = 0x60 + 0x1F;
        prim->v0 = prim->v1 = self->ext.shield.unk7D + 0;
        prim->v2 = prim->v3 = self->ext.shield.unk7D + 0x77;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = 0x1B8;
        prim->drawMode = DRAW_HIDE;
        for (i = 0; i < 15; i++) {
            prevPrim = prim;
            prim = prim->next;
            nextPrim = prim->next;
            *prim = *prevPrim;
            prim->next = nextPrim;
            prim->v0 = prim->v1 = self->ext.shield.unk7D + (i * 120) / 15;
            prim->v2 = prim->v3 =
                (self->ext.shield.unk7D + ((i + 1) * 120) / 15) - 1;
            prim->clut = 0x15F;
            prim->priority = 0x1BA;
            prim->drawMode |=
                (DRAW_TPAGE2 + DRAW_TPAGE + DRAW_COLORS + DRAW_TRANSP);
        }
        self->ext.shield.unk8A = 0x80;
        self->ext.shield.unk90 = 0x100;
        self->ext.shield.unk84 = 0;
        self->ext.shield.unk86 = 0x78;
        self->ext.shield.unk92 = 0x20;
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
            self->step += 1;
        }
        if ((self->ext.shield.unk80 % 10) == 0) {
            // Make a func_ptr_80170024 entity
            unusedEnt = g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xE) + FACTORY(0x100, 90), 0);
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        if (!(self->ext.shield.unk80 & 1)) {
            prim->priority = 0x1B8;
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
            prim = prim->next;
            for (i = 0; i < 15; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            self->ext.shield.unk80 = 0;
            g_api.PlaySfx(SFX_KARMA_COIN_HEADS);
            self->step++;
        }
        if (self->ext.shield.unk80 % 10 == 0) {
            // Make a func_ptr_80170024 entity
            unusedEnt = g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xE) + FACTORY(0x100, 90), 0);
        }
        break;
    case 4:
        self->ext.shield.unk82 += 8;
        self->rotX += 12;
        if (self->rotX >= 0x100) {
            self->rotX = 0x100;
        }
        self->ext.shield.unk84 = self->rotX * 16 / 256;
        self->ext.shield.unk86 = (0x100 - self->rotX) * 60 / 256 + 60;
        if ((g_Timer & 7) == 0) {
            self->ext.shield.unk92--;
        }
        if (self->ext.shield.unk92 < 0) {
            self->ext.shield.unk92 = 0;
        }
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b3 > 8) {
            prim->b3 -= 4;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;

        if ((g_Timer & 1) == 0) {
            self->ext.shield.unk92--;
        }
        if (self->ext.shield.unk92 < 0) {
            self->ext.shield.unk92 = 0;
        }
        if (self->rotX == 0x100) {
            if (self->ext.shield.unk92 == 0) {
                prim = &g_PrimBuf[self->primIndex];
                prim = prim->next;
                prim->drawMode &= ~DRAW_HIDE;
                self->step++;
            }
        }
        self->ext.shield.unk80++;
        if (self->ext.shield.unk80 % 10 == 0) {
            // Make a func_ptr_80170024 entity
            unusedEnt = g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xE) + FACTORY(0x100, 90), 0);
        }
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
        if (++self->ext.shield.unk80 == 0x40) {
            self->step += 1;
            // Blueprint 55 has child 39, EntityPlayerPinkEffect
            g_api.CreateEntFactoryFromEntity(self, FACTORY(0xF00, 55), 0);
        }
        break;
    case 7:
        self->ext.shield.unk90 += 0x10;
        if (self->ext.shield.unk90 > 0x120) {
            prim = g_PrimBuf[self->primIndex].next;
            prim->drawMode |= DRAW_HIDE;
            self->ext.shield.unk80 = 0x10;
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
        self->ext.shield.unk90 -= 0x10;
        if (self->ext.shield.unk90 < 0) {
            self->ext.shield.unk90 = 0;
        }
        if (--self->ext.shield.unk80 == 0) {
            self->ext.shield.unk80 = 0x40;
            self->step++;
        }
        break;
    case 9:
        self->ext.shield.unk90 -= 0x10;
        if (self->ext.shield.unk90 < 0) {
            self->ext.shield.unk90 = 0;
        }
        if (--self->ext.shield.unk80 == 0) {
            g_unkGraphicsStruct.unk20 = 0;
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    if (prim->b3 >= 9U) {
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
    top = prim->y0 = prim->y1 = selfY - self->ext.shield.unk86;
    bottom = prim->y2 = prim->y3 = (selfY + self->ext.shield.unk86) - 1;
    if (self->facingLeft == 0) {
        back = prim->x0 = prim->x2 = selfX - self->ext.shield.unk84;
        front = prim->x1 = prim->x3 = (selfX + self->ext.shield.unk84) - 1;
    } else {
        front = prim->x1 = prim->x3 = selfX - self->ext.shield.unk84;
        back = prim->x0 = prim->x2 = (selfX + self->ext.shield.unk84) - 1;
    }
    front++;
    bottom++;
    prim = prim->next;
    for (i = 0; i < 15; i++) {
        angle = D_B3000_8017AA98[i];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk92 / 256;
        prim->x0 = back + baseCoord;
        prim->x1 = (front + baseCoord) - 1;
        angle = D_B3000_8017AA98[(i + 1) % 15];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk92 / 256;
        prim->x2 = back + baseCoord;
        prim->x3 = (front + baseCoord) - 1;
        angle = D_B3000_8017AA98[(i + 6) % 15];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk94 / 256;
        prim->y0 = top + (((bottom - top) * i) / 15) - baseCoord;
        prim->y2 = top + (((bottom - top) * (i + 1)) / 15) - baseCoord;
        angle = D_B3000_8017AA98[(i + 1) % 15];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk94 / 256;
        prim->y1 = top + ((i * (bottom - top)) / 15) - baseCoord;
        prim->y3 = top + (((bottom - top) * (i + 1)) / 15) - baseCoord;
        angle = D_B3000_8017AA98[i];
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        angle = D_B3000_8017AA98[(i + 1) % 15];
        prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        D_B3000_8017AA98[i] += self->ext.shield.unk8A;
        prim = prim->next;
    }
}

// Probably the dancing clouds of fog that appear with the shield spell?
static void func_ptr_80170024(Entity* self) {
    Primitive* prim;
    s16 angle;
    s16 xSize;
    s16 ySize;
    s16 xVar;
    s16 yVar;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(D_B3000_8017A040);
        if (g_HandId != 0) {
            self->animSet += 2;
            self->ext.shield.childPalette = 0x12A;
            self->ext.shield.unk7D = 0x80;
        } else {
            self->ext.shield.childPalette = 0x112;
            self->ext.shield.unk7D = 0;
        }
        self->posX.i.hi =
            (self->ext.shield.parent->posX.i.hi + (rand() % 160)) - 80;
        self->posY.i.hi =
            (self->ext.shield.parent->posY.i.hi + (rand() % 192)) - 64;
        self->flags |= FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        self->facingLeft = PLAYER.facingLeft;
        self->rotX = self->rotY = 0;
        self->rotZ = 0;

        prim = &g_PrimBuf[self->primIndex];
        prim->clut = self->ext.shield.childPalette;
        prim->tpage = 0x19;

        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x5F;
        prim->v0 = prim->v1 = self->ext.shield.unk7D + 0x28;
        prim->v2 = prim->v3 = self->ext.shield.unk7D + 0x28 + 0x57;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        if (rand() & 3) {
            prim->priority = 0x1BC;
        } else {
            prim->priority = 0x1B6;
        }
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        self->ext.shield.unk80 = (rand() & 7) + 8;
        self->ext.shield.unk96 = rand() % 16 - 8;
        if (self->ext.shield.unk96 >= 0) {
            self->ext.shield.unk96++;
        }
        // PSP has rand() & 0x7FFF here, don't know why
        self->ext.shield.unk98 = rand();
        self->step++;
        break;
    case 1:
        self->rotX += 8;
        self->rotY += 8;
        if (!self->ext.shield.unk80) {
            self->ext.shield.unk80 = (rand() & 0x3F) + 0x60;
            self->step++;
        }
        break;
    case 2:
        self->rotX += 2;
        self->rotY += 2;
        if (!self->ext.shield.unk80) {
            self->step++;
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b3 >= 6) {
            prim->b3 -= 6;
        }
        if (prim->b3 < 7) {
            DestroyEntity(self);
            return;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        break;
    }
    self->ext.shield.unk80--;
    self->ext.shield.unk98 += 0x40;
    if (!(self->ext.shield.unk80 & 3)) {
        if (self->ext.shield.parent->entityId) {
            angle = self->ext.shield.unk98;
            xVar = self->ext.shield.parent->posX.i.hi;
            yVar = self->ext.shield.parent->posY.i.hi - 0x20;
            yVar -= (((rsin(angle) >> 4) * 64) >> 8);
            xVar += (((rcos(angle) >> 4) * 48) >> 8);
            angle = ratan2(-(yVar - self->posY.i.hi), xVar - self->posX.i.hi);
            self->velocityX = rcos(angle) * 8;
            self->velocityY = -rsin(angle) * 8;
        } else {
            self->velocityY = 0;
            self->velocityX = 0;
            self->step = 3;
        }
    }
    self->posX.val += self->velocityX;
    self->posY.val += self->velocityY;
    self->rotZ += self->ext.shield.unk96;
    xVar = self->posX.i.hi;
    yVar = self->posY.i.hi;

    xSize = self->rotX * 0x43 / 256;
    ySize = self->rotY * 0x43 / 256;
    prim = &g_PrimBuf[self->primIndex];
    angle = self->rotZ + 0x639;
    prim->x0 = xVar + (((rcos(angle) >> 4) * xSize) >> 8);
    prim->y0 = yVar - (((rsin(angle) >> 4) * ySize) >> 8);
    angle = self->rotZ + 0x1C7;
    prim->x1 = xVar + (((rcos(angle) >> 4) * xSize) >> 8);
    prim->y1 = yVar - (((rsin(angle) >> 4) * ySize) >> 8);
    angle = self->rotZ + 0x9C7;
    prim->x2 = xVar + (((rcos(angle) >> 4) * xSize) >> 8);
    prim->y2 = yVar - (((rsin(angle) >> 4) * ySize) >> 8);
    angle = self->rotZ + 0xE39;
    prim->x3 = xVar + (((rcos(angle) >> 4) * xSize) >> 8);
    prim->y3 = yVar - (((rsin(angle) >> 4) * ySize) >> 8);
}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
