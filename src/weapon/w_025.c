// Weapon ID #25. Used by weapons:
// Goddess shield, Unknown#209
#include "weapon_private.h"
#include "shared.h"

extern SpriteParts D_B3000_8017A040[];
extern s8 D_B3000_8017AA18;
extern AnimationFrame* D_B3000_8017AA60;

void func_B3000_8017AF14(const char* fmt, u_long end) {
    while (PadRead(0) != end) {
        FntPrint(fmt);
        DrawSync(0);
        VSync(0);
        FntFlush(-1);
    }
}

void EntityWeaponAttack(Entity* self) {
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

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 25; }

INCLUDE_ASM("weapon/nonmatchings/w_025", EntityWeaponShieldSpell);

// Goddess shield
void func_ptr_80170024(Entity* self) {
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

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
