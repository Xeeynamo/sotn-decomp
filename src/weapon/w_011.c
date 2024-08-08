// Weapon ID #11. Used by weapons:
// AxeLord shield, Unknown#206
#include "weapon_private.h"
#include "shared.h"
#include "sfx.h"

extern SpriteParts D_51000_8017A040[];
extern s8 D_51000_8017AB4C;
extern AnimationFrame* D_51000_8017AB94;

extern AnimationFrame D_51000_8017ABCC[];
extern AnimationFrame D_51000_8017ABE8[];

extern s32 D_51000_8017ABF4[];

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
        SetSpriteBank1(D_51000_8017A040);
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
        g_api.PlayAnimation(&D_51000_8017AB4C, &D_51000_8017AB94);
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

int GetWeaponId(void) { return 11; }

void EntityWeaponShieldSpell(Entity* self) {
    Primitive* prim;
    Primitive* prevPrim;
    Primitive* nextPrim;
    Entity* unusedEnt;
    s32 i;
    s16 baseCoord;
    s16 selfY;
    s16 angle;
    s16 back;
    s16 front;
    s16 top;
    s16 bottom;

    switch (self->step) {
    case 0:
        for (i = 0; i < 16; i++) {
            D_51000_8017ABF4[i] = (i << 9) * 2;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(D_51000_8017A040);
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
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x1F;
        prim->v0 = prim->v1 = self->ext.shield.unk7D + 0x30;
        prim->v2 = prim->v3 = self->ext.shield.unk7D + 0x6F;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = 0x1BC;
        prim->drawMode = DRAW_HIDE;
        for (i = 0; i < 8; i++) {
            prevPrim = prim;
            prim = prim->next;
            nextPrim = prim->next;
            *prim = *prevPrim;
            prim->next = nextPrim;
            prim->v0 = prim->v1 = self->ext.shield.unk7D + 0x30 + i * 64 / 8;
            prim->v2 = prim->v3 =
                self->ext.shield.unk7D + 0x30 + (i + 1) * 64 / 8 - 1;
            prim->clut = 0x15F;
            prim->priority = 0x1BE;
            prim->drawMode |=
                (DRAW_TPAGE2 + DRAW_TPAGE + DRAW_COLORS + DRAW_TRANSP);
        }
        self->ext.shield.unk92 = 0x120;
        self->ext.shield.unk94 = 0;
        self->ext.shield.unk84 = 0x10;
        self->ext.shield.unk86 = 0;
        self->ext.shield.unk8A = 0x40;
        self->ext.shield.unk90 = 0x100;
        SetSpeedX(FIX(-2));
        self->velocityY = 0;
        DestroyEntityWeapon(1);
        g_api.PlaySfx(SFX_UNK_641);
        g_unkGraphicsStruct.unk20 = 1;
        self->step++;
        break;
    case 1:
        DecelerateX(FIX(1.0 / 16));
        self->velocityY -= FIX(0.15625);
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
            prim = prim->next;
            for (i = 0; i < 8; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            self->ext.shield.unk80 = 0x20;
            g_api.PlaySfx(SFX_UNK_669);
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
        self->rotX += 0x10;
        if (self->rotX >= 0x100) {
            self->rotX = 0x100;
        }
        self->ext.shield.unk86 = self->rotX * 32 / 256;
        self->ext.shield.unk92 -= 12;
        if (self->ext.shield.unk92 <= 0) {
            self->ext.shield.unk92 = 0;
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            self->step++;
        }
        break;
    case 5:
        self->ext.shield.unk90 -= 0x10;
        if (self->ext.shield.unk90 < 0) {
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode |= DRAW_HIDE;
            self->ext.shield.unk90 = 0;
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            // Blueprint 88 is weapon function 9, func_ptr_80170024
            unusedEnt = g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xE) + FACTORY(0, 88), 0);
            g_unkGraphicsStruct.unk20 = 0;
            self->step++;
        }
        break;
    case 6:
        self->ext.shield.unk90 += 8;
        if (self->ext.shield.unk90 >= 0x80) {
            self->ext.shield.unk80 = 4;
            self->step++;
        }
        break;
    case 7:
        if (--self->ext.shield.unk80 == 0) {
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
    for (i = 0; i < 8; i++) {
        angle = D_51000_8017ABF4[i];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk92 / 256;
        prim->x0 = back + baseCoord;
        prim->x1 = (front + baseCoord) - 1;
        angle = D_51000_8017ABF4[(i + 1) % 8];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk92 / 256;
        prim->x2 = back + baseCoord;
        prim->x3 = (front + baseCoord) - 1;
        prim->y0 = prim->y1 = top + (((bottom - top) * i) / 8);
        prim->y2 = prim->y3 = top + (((bottom - top) * (i + 1)) / 8);
        angle = D_51000_8017ABF4[(i + 6) % 8];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk94 / 256;
        prim->y0 += baseCoord;
        prim->y2 += baseCoord;
        angle = D_51000_8017ABF4[(i + 7) % 8];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk94 / 256;
        prim->y1 += baseCoord;
        prim->y3 += baseCoord;
        angle = D_51000_8017ABF4[i];
        prim->g0 = prim->b0 = prim->g1 = prim->b1 = prim->b3 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        prim->r0 = prim->r1 = 0;
        angle = D_51000_8017ABF4[(i + 1) % 8];
        // @bug: Writing to prim->b3 twice
        prim->g2 = prim->b2 = prim->g3 = prim->b3 = prim->b3 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        prim->r2 = prim->r3 = 0;
        D_51000_8017ABF4[i] += self->ext.shield.unk8A;
        prim = prim->next;
    }
}

void func_ptr_80170024(Entity* self) {
    Collider collider;
    Entity* unusedEnt;

    s16 xOffset;
    s16 yOffset;
    s16 xVar;
    s16 yVar;

    switch (self->step) {
    case 0:
        if (self->ext.shield.parent->entityId == 0) {
            DestroyEntity(self);
            return;
        }
        self->animSet = self->ext.shield.parent->animSet;
        self->unk5A = self->ext.shield.parent->unk5A;
        self->zPriority = PLAYER.zPriority + 2;
        self->palette = self->ext.shield.parent->palette;
        self->facingLeft = self->ext.shield.parent->facingLeft;
        if (self->params & 0x7F00) {
            self->flags = FLAG_UNK_08000000;
            self->animCurFrame = self->ext.shield.parent->animCurFrame;
            self->drawFlags = FLAG_DRAW_UNK8;
            self->drawMode = DRAW_TPAGE;
            self->unk6C = 0x80;
            self->animFrameDuration = 0x18;
            self->zPriority -= 2;
            self->step = 4;
        } else {
            self->unk4C = D_51000_8017ABCC;
            self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
            self->ext.shield.unkAE = self->ext.shield.parent->ext.shield.unkAE;
            SetWeaponProperties(self, 0);
            self->hitboxWidth = 8;
            self->hitboxHeight = 20;
            SetSpeedX(FIX(1));
            self->step++;
        }
        break;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(1.0 / 8);
        if (self->velocityY > FIX(6)) {
            self->velocityY = FIX(6);
        }
        xOffset = 0;
        yOffset = 25;
        xVar = self->posX.i.hi + xOffset;
        yVar = self->posY.i.hi + yOffset;
        g_api.CheckCollision(xVar, yVar, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            g_api.PlaySfx(SFX_UNK_64B);
            self->step = 2;
            break;
        }
        if (!(collider.effects & EFFECT_UNK_8000)) {
            xOffset = 8;
            if (self->velocityX < 0) {
                xOffset = -xOffset;
            }
            yOffset = 22;
            xVar = self->posX.i.hi + xOffset;
            yVar = self->posY.i.hi + yOffset;
            g_api.CheckCollision(xVar, yVar, &collider, 0);
            if ((collider.effects & EFFECT_SOLID) &&
                !(collider.effects & EFFECT_UNK_8000)) {
                goto make_other_entity;
            }
            xOffset = 8;
            if (self->velocityX < 0) {
                xOffset = -xOffset;
            }
            yOffset = 8;
            xVar = self->posX.i.hi + xOffset;
            yVar = self->posY.i.hi + yOffset;
            g_api.CheckCollision(xVar, yVar, &collider, 0);
            if ((collider.effects & EFFECT_SOLID) &&
                !(collider.effects & EFFECT_UNK_8000)) {
                goto make_other_entity;
            }
        }
        xOffset = 8;
        if (self->velocityX < 0) {
            xOffset = -xOffset;
        }
        yOffset = -8;
        xVar = self->posX.i.hi + xOffset;
        yVar = self->posY.i.hi + yOffset;
        g_api.CheckCollision(xVar, yVar, &collider, 0);
        if ((collider.effects & EFFECT_SOLID) || (self->hitFlags)) {
            goto make_other_entity;
        }
        if (g_Timer % 4 == 0) {
            // Blueprint 90 is weapon entity 9, func_ptr_80170024, so ourself.
            unusedEnt = g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xE) + FACTORY(0x100, 90), 0);
        }
        break;
    case 2:
        SetSpeedX(FIX(2.5));
        if ((self->ext.timer.t % 10) == 0) {
            g_api.PlaySfx(SFX_UNK_64B);
        }
        xOffset = 0;
        yOffset = 25;
        xVar = self->posX.i.hi + xOffset;
        yVar = self->posY.i.hi + yOffset;
        g_api.CheckCollision(xVar, yVar, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
        } else {
            self->step = 1;
            self->velocityY = 0;
        }
        if (!(collider.effects & EFFECT_UNK_8000)) {
            xOffset = 8;
            if (self->velocityX < 0) {
                xOffset = -xOffset;
            }
            yOffset = 22;
            xVar = self->posX.i.hi + xOffset;
            yVar = self->posY.i.hi + yOffset;
            g_api.CheckCollision(xVar, yVar, &collider, 0);
            if ((collider.effects & EFFECT_SOLID) &&
                !(collider.effects & EFFECT_UNK_8000)) {
                goto make_other_entity;
            }
            xOffset = 8;
            if (self->velocityX < 0) {
                xOffset = -xOffset;
            }
            yOffset = 8;
            xVar = self->posX.i.hi + xOffset;
            yVar = self->posY.i.hi + yOffset;
            g_api.CheckCollision(xVar, yVar, &collider, 0);
            if ((collider.effects & EFFECT_SOLID) &&
                !(collider.effects & EFFECT_UNK_8000)) {
                goto make_other_entity;
            }
        }
        if ((((collider.effects & EFFECT_UNK_C000) == EFFECT_UNK_C000) &&
             (self->facingLeft)) ||
            (((collider.effects & EFFECT_UNK_C000) == EFFECT_UNK_8000) &&
             (self->facingLeft == 0))) {
            if (!(collider.effects &
                  (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID_FROM_BELOW))) {
                SetSpeedX(FIX(1.25));
            }
            // @bug: These next two if-statements are never true because the bit
            // flags don't match up. We're testing against 0x40 and 0x80 flags,
            // and seeing if they match 0x100 or 0x200.
            if ((collider.effects &
                 (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID_FROM_BELOW)) ==
                EFFECT_UNK_0100) {
                SetSpeedX(FIX(2));
            }
            if ((collider.effects &
                 (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID_FROM_BELOW)) ==
                EFFECT_UNK_0200) {
                SetSpeedX(FIX(2.25));
            }
        }
        xOffset = 8;
        if (self->velocityX < 0) {
            xOffset = -xOffset;
        }
        yOffset = -8;
        xVar = self->posX.i.hi + xOffset;
        yVar = self->posY.i.hi + yOffset;
        g_api.CheckCollision(xVar, yVar, &collider, 0);
        if (!(collider.effects & EFFECT_SOLID) && (!self->hitFlags)) {
            if (self->ext.timer.t % 4 == 0) {
                // Blueprint 90 is weapon entity 9, func_ptr_80170024, so
                // ourself.
                unusedEnt = g_api.CreateEntFactoryFromEntity(
                    self, ((g_HandId + 1) << 0xE) + FACTORY(0x100, 90), 0);
            }
            self->posX.val += self->velocityX;
        } else {
            goto make_other_entity;
        }
        break;
    case 3:
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    case 4:
        self->unk6C -= 2;
        if (--self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    // Not a switch case, but `break` skips this, so we put it in the switch.
    make_other_entity:
        g_api.PlaySfx(SFX_CANDLE_HIT);
        self->step = 3;
        self->unk4C = D_51000_8017ABE8;
        self->animFrameDuration = self->animFrameIdx = 0;
        // Blueprint 90 is weapon entity 9, func_ptr_80170024, so ourself.
        unusedEnt = g_api.CreateEntFactoryFromEntity(
            self, ((g_HandId + 1) << 0xE) + FACTORY(0x100, 90), 0);
    }
    self->ext.timer.t++;
}
void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
