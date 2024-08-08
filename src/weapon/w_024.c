// Weapon ID #24. Used by weapons:
// Dark shield, Unknown#208
#include "weapon_private.h"
#include "shared.h"
#include "sfx.h"

extern SpriteParts D_AC000_8017A040[];
extern s8 D_AC000_8017ABD8;
extern AnimationFrame* D_AC000_8017AC20;
extern s16* D_AC000_8017ACF8[];
extern s32 D_AC000_8017AD08[];

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

void EntityWeaponShieldSpell(Entity* self) {
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

    g_Player.unk20 = 8;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x12);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(D_AC000_8017A040);
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
        self->posY.i.hi -= 8;
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = 0x3E;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = self->rotY = 0;

        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = 0;
        prim->y0 = 0;
        prim->u0 = 0x90;
        prim->v0 = 0xE8;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->type = PRIM_TILE;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        prim->priority = 0x1B4;
        prim = prim->next;

        prim->x0 = 0x90;
        prim->y0 = 0;
        prim->u0 = 0x90;
        prim->v0 = 0xE8;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->type = PRIM_TILE;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        prim->priority = 0x1B4;
        prim = prim->next;

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
        prim->priority = self->zPriority - 10;
        prim->drawMode =
            DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim = prim->next;

        prim->clut = self->ext.shield.childPalette;
        prim->tpage = 0x19;
        prim->u0 = prim->u1 = 0;
        prim->u2 = prim->u3 = 0x6F;
        prim->v3 = prim->v1 = self->ext.shield.unk7D + 0x30;
        prim->v2 = prim->v0 = self->ext.shield.unk7D + 0x67;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = 0x1B8;
        prim->drawMode = DRAW_HIDE;

        for (i = 0; i < 14; i++) {
            prevPrim = prim;
            prim = prim->next;
            nextPrim = prim->next;
            *prim = *prevPrim;
            prim->next = nextPrim;
            prim->u1 = prim->u0 = i * 8;
            prim->u2 = prim->u3 = (i + 1) * 8 - 1;
            prim->clut = 0x15F;
            prim->priority = 0x1BA;
            prim->drawMode |=
                (DRAW_TPAGE2 + DRAW_TPAGE + DRAW_COLORS + DRAW_TRANSP);
        }
        self->ext.shield.unk8A = 0x80;
        self->ext.shield.unk90 = 0x100;
        self->ext.shield.unk84 = 0x1C;
        self->ext.shield.unk86 = 0x38;
        self->ext.shield.unk92 = 0x20;
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
            g_api.func_80102CD8(4);
            self->step += 1;
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
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
            for (i = 0; i < 14; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            self->ext.shield.unk80 = 0;
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            self->step++;
        }
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b0 < 0xF8) {
            prim->b0 += 2;
        }
        prim->r0 = prim->g0 = prim->b0;
        prim = prim->next;
        if (prim->b0 < 0xF8) {
            prim->b0 += 2;
        }
        prim->r0 = prim->g0 = prim->b0;
        break;
    case 4:
        self->ext.shield.unk82 += 8;
        self->rotX += 6;
        if (self->rotX >= 0x100) {
            self->rotX = 0x100;
        }

        if (--self->ext.shield.unk92 < 0) {
            self->ext.shield.unk92 = 0;
        }

        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
        if (prim->b3 > 8) {
            prim->b3 -= 4;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;

        if (self->rotX >= 0x80) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim = prim->next;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
        }
        if (self->ext.shield.unk80 >= 35) {
            self->hitboxState = 0;
        }
        if (self->ext.shield.unk80 == 32) {
            // This should spawn the rocks that rise in the background?
            unusedEnt = g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xE) + FACTORY(0, 96), 0);
            g_unkGraphicsStruct.unk20 = 0;
            SetWeaponProperties(self, 0);
            self->hitboxWidth = self->hitboxHeight = 0x7F;
        }
        if (self->rotX == 0x100) {
            prim->b3 = 6;
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            self->hitboxState = 0;
            self->step++;
        }
        self->ext.shield.unk80++;
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b0 < 0xF8) {
            prim->b0 += 3;
        }
        prim->r0 = prim->g0 = prim->b0;
        prim = prim->next;
        if (prim->b0 < 0xF8) {
            prim->b0 += 3;
        }
        prim->r0 = prim->g0 = prim->b0;
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
        if (++self->ext.shield.unk80 == 0x70) {
            self->step += 1;
        }
        break;
    case 7:
        self->ext.shield.unk90 += 8;
        if (self->ext.shield.unk90 > 0x120) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim = prim->next;
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            self->step++;
        }
        break;
    case 8:
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b0 > 8) {
            prim->b0 -= 8;
        }
        prim->r0 = prim->g0 = prim->b0;
        prim = prim->next;
        if (prim->b0 > 8) {
            prim->b0 -= 8;
        }
        prim->r0 = prim->g0 = prim->b0;
        self->ext.shield.unk90 -= 8;
        self->ext.shield.unk92++;
        if (self->ext.shield.unk90 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    prim = prim->next;
    prim = prim->next;
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
    for (i = 0; i < 14; i++) {
        angle = D_AC000_8017AD08[i];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk92 / 256;
        prim->x0 = back + baseCoord;
        prim->x1 = (front + baseCoord) - 1;
        angle = D_AC000_8017AD08[(i + 1) % 14];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk92 / 256;
        prim->x2 = back + baseCoord;
        prim->x3 = (front + baseCoord) - 1;
        angle = D_AC000_8017AD08[(i + 6) % 14];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk94 / 256;
        prim->y0 = top + (((bottom - top) * i) / 14) - baseCoord;
        prim->y2 = top + (((bottom - top) * (i + 1)) / 14) - baseCoord;
        angle = D_AC000_8017AD08[(i + 1) % 14];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk94 / 256;
        prim->y1 = top + ((i * (bottom - top)) / 14) - baseCoord;
        prim->y3 = top + (((bottom - top) * (i + 1)) / 14) - baseCoord;
        angle = D_AC000_8017AD08[i];
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        angle = D_AC000_8017AD08[(i + 1) % 14];
        prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        D_AC000_8017AD08[i] += self->ext.shield.unk8A;
        prim = prim->next;
    }
}

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
        self->ext.weapon.accelerationY =
            -((self->ext.shield.unk9A << 8) + 0x900);
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
            g_api.PlaySfx(SFX_START_SLAM_A);
            self->step += 1;
        }
        break;
    case 3:
        self->posX.i.hi = self->ext.shield.unk94 + (self->ext.shield.unk80 & 1);
        self->posY.val += self->velocityY;
        self->velocityY += self->ext.weapon.accelerationY;
        if (self->posY.i.hi < 0x80) {
            self->ext.shield.unk92 += 2;
            self->ext.weapon.accelerationY -= FIX(1.0 / 8);
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
