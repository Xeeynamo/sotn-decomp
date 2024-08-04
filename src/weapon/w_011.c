// Weapon ID #11. Used by weapons:
// AxeLord shield, Unknown#206
#include "weapon_private.h"
#include "shared.h"

extern SpriteParts D_51000_8017A040[];
extern s8 D_51000_8017AB4C;
extern AnimationFrame* D_51000_8017AB94;

extern AnimationFrame D_51000_8017ABCC[];
extern AnimationFrame D_51000_8017ABE8[];

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

INCLUDE_ASM("weapon/nonmatchings/w_011", EntityWeaponShieldSpell);

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
        g_api.PlaySfx(NA_SE_BREAK_CANDLE);
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
