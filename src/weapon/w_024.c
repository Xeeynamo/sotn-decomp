// Weapon ID #24. Used by weapons:
// Dark shield, Unknown#208
#include "weapon_private.h"
#include "shared.h"

extern SpriteParts D_AC000_8017A040[];
extern s8 D_AC000_8017ABD8;
extern AnimationFrame* D_AC000_8017AC20;
extern s16* D_AC000_8017ACF8[];

void EntityWeaponAttack(Entity* self) {
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
    switch (self->step) {
    case 0:
        SetSpriteBank1(D_AC000_8017A040);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
            self->ext.darkShield.pal = 0x128;
            self->unk5A = 0x66;
        } else {
            self->animSet = ANIMSET_OVL(0x10);
            self->ext.darkShield.pal = 0x110;
            self->unk5A = 0x64;
        }
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        g_Player.unk48 = 1;
        self->ext.darkShield.palettePtr = D_AC000_8017ACF8[rand() & 3];
        SetWeaponProperties(self, 0);
        self->step++;
        /* fallthrough */
    case 1:
        self->ext.darkShield.anim = anim2 + 10;
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
        self->ext.darkShield.anim = anim1;
        self->animFrameDuration = 2;
        break;
    case 3:
        g_Player.unk48 = 0;
        self->ext.darkShield.anim = anim2 + 12;
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
        g_api.PlayAnimation(&D_AC000_8017ABD8, &D_AC000_8017AC20);
    }
    if (self->ext.darkShield.unk80 == 0) {
        self->ext.darkShield.unk80 =
            self->ext.darkShield
                .palettePtr[self->ext.darkShield.childPalette * 2];
        self->palette =
            self->ext.darkShield
                .palettePtr[self->ext.darkShield.childPalette * 2 + 1] +
            self->ext.darkShield.pal;
    } else if (--self->ext.darkShield.unk80 == 0) {
        self->ext.darkShield.childPalette =
            self->ext.darkShield.childPalette + 1;
        self->ext.darkShield.unk80 =
            self->ext.darkShield
                .palettePtr[self->ext.darkShield.childPalette * 2];
        self->palette =
            self->ext.darkShield
                .palettePtr[self->ext.darkShield.childPalette * 2 + 1] +
            self->ext.darkShield.pal;
        if (self->ext.darkShield.unk80 == 0xFFFF) {
            self->ext.darkShield.childPalette = 0;
            self->ext.darkShield.unk80 = 0;
            self->ext.darkShield.palettePtr = D_AC000_8017ACF8[rand() & 3];
        }
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

int GetWeaponId(void) { return 24; }

INCLUDE_ASM("weapon/nonmatchings/w_024", EntityWeaponShieldSpell);

// Appears to be the entity for the rising rocks as part of the Shield Rod spell
void func_ptr_80170024(Entity* self) {
    Primitive* prim;
    s16 selfX;
    s16 selfY;

    switch (self->step) {
    case 0:
        if (self->ext.shield.parent->entityId == 0) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.shield.unk7D = self->ext.shield.parent->ext.shield.unk7D;
        self->ext.shield.childPalette =
            self->ext.shield.parent->ext.shield.childPalette + 1;
        self->flags |= FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        self->ext.shield.unk9A = rand() & 0xF;
        self->ext.shield.unk94 = self->posX.i.hi = (rand() % 248) + 4;
        self->posY.i.hi = (rand() & 0x3F) + 0xD8;
        self->facingLeft = rand() & 1;

        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x19;
        prim->clut = self->ext.shield.childPalette;
        if (self->ext.shield.unk9A < 8) {
            prim->u0 = prim->u2 = 0x50;
            prim->u1 = prim->u3 = 0x50 + 15;
            prim->v0 = prim->v1 = self->ext.shield.unk7D;
            prim->v2 = prim->v3 = self->ext.shield.unk7D + 0x1F;
            self->ext.shield.unk84 = ((self->ext.shield.unk9A + 8) * 8) / 10;
            self->ext.shield.unk86 = ((self->ext.shield.unk9A + 8) * 0x10) / 10;
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                -0x80 - ((7 - self->ext.shield.unk9A) * 0xF);
            prim->priority = 0x1B8;
        } else {
            prim->u0 = prim->u2 = 0x60;
            prim->u1 = prim->u3 = 0x60 + 31;
            prim->v0 = prim->v1 = self->ext.shield.unk7D;
            prim->v2 = prim->v3 = self->ext.shield.unk7D + 0x2F;
            self->ext.shield.unk84 = (self->ext.shield.unk9A * 0x10) / 10;
            self->ext.shield.unk86 = (self->ext.shield.unk9A * 0x18) / 10;
            prim->priority = 0x1BE;
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                -0x80 - ((0xF - self->ext.shield.unk9A) * 0xC);
        }
        prim->r1 = prim->g1 = prim->b1 = prim->r0 = prim->g0 = prim->b0 = 0x80;
        prim->drawMode = DRAW_COLORS;
        self->velocityY = -((self->ext.shield.unk9A * FIX(3.0 / 16)) + FIX(3));
        self->ext.shield.unkA0 = -((self->ext.shield.unk9A << 8) + 0x900);
        self->ext.shield.unkAE = self->ext.shield.parent->ext.shield.unkAE;
        SetWeaponProperties(self, 0);
        self->hitboxHeight = 0x40;
        self->hitboxWidth = 0x40;
        self->step += 1;
        break;
    case 1:
        self->posY.val += self->velocityY / 16;
        if (self->ext.shield.parent->step > 5) {
            self->ext.shield.unk80 = (rand() % 48) + 10;
            self->step += 1;
        }
        break;
    case 2:
        self->posX.i.hi = self->ext.shield.unk94 + (self->ext.shield.unk80 & 1);
        self->posY.val += self->velocityY / 32;
        if (--self->ext.shield.unk80 == 0) {
            self->velocityY /= 32;
            g_api.PlaySfx(SFX_DARK_SHIELD);
            self->step += 1;
        }
        break;
    case 3:
        self->posX.i.hi = self->ext.shield.unk94 + (self->ext.shield.unk80 & 1);
        self->posY.val += self->velocityY;
        self->velocityY += self->ext.shield.unkA0;
        if (self->posY.i.hi < 0x80) {
            self->ext.shield.unk92 += 2;
            self->ext.shield.unkA0 -= 0x2000;
        }
        // If we have risen off-screen, destroy us.
        if (self->posY.i.hi < -0x40) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    prim->y0 = prim->y1 = selfY - self->ext.shield.unk86;
    prim->y2 = prim->y3 =
        selfY + self->ext.shield.unk86 - 1 + self->ext.shield.unk92;
    if (self->facingLeft == 0) {
        prim->x0 = prim->x2 = selfX - self->ext.shield.unk84;
        prim->x1 = prim->x3 = (selfX + self->ext.shield.unk84) - 1;
    } else {
        prim->x1 = prim->x3 = selfX - self->ext.shield.unk84;
        prim->x0 = prim->x2 = (selfX + self->ext.shield.unk84) - 1;
    }
}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
