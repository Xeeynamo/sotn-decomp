// Weapon ID #23. Used by weapons:
// Herald shield, Unknown#207
#include "weapon_private.h"
#include "shared.h"

extern SpriteParts D_A5000_8017A040[];
extern s8 D_A5000_8017AAD8;
extern AnimationFrame* D_A5000_8017AB20;

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
    if (self->step == 1 || self->step == 2) {
        if (self->ext.shield.unk84 == 0) {
            if (self->hitFlags == 3) {
                g_api.AddHearts(1);
                self->hitFlags = 0;
                self->ext.shield.unk84 = 0x20;
            }
        }
    }
    if (self->ext.shield.unk84 != 0) {
        self->ext.shield.unk84--;
    }
    switch (self->step) {
    case 0:
        SetSpriteBank1(D_A5000_8017A040);
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
        g_api.PlayAnimation(&D_A5000_8017AAD8, &D_A5000_8017AB20);
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

int GetWeaponId(void) { return 23; }

INCLUDE_ASM("weapon/nonmatchings/w_023", EntityWeaponShieldSpell);

INCLUDE_ASM("weapon/nonmatchings/w_023", func_ptr_80170024);

extern AnimationFrame D_A5000_8017AB58[];

void func_ptr_80170028(Entity* self) {

    switch (self->step) {
    case 0:
        self->palette = self->ext.weapon.parent->palette;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->unk4C = D_A5000_8017AB58;
        self->flags |= (FLAG_UNK_04000000 | FLAG_UNK_100000);
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;

        self->rotX = self->rotY = 0;
        self->posY.i.hi += 40;
        self->velocityY = FIX(-1.5);
        self->ext.weapon.unk7E = 0;
        // Note: This is a weird use of the lifetime, it's not a lifetime! It's
        // just caching the initial X position.
        self->ext.weapon.lifetime = self->posX.i.hi;
        self->animFrameIdx = rand() % 5;
        self->animFrameDuration = 2;
        self->ext.weapon.unk7E = 0x400;
        self->ext.weapon.unk80 = (self->params & 0xFF) * 4;
        self->step++;
        return;
    case 1:
        // Actually, looks like it's using unk80 as the life timer.
        if (--self->ext.weapon.unk80 == 0) {
            self->animSet = self->ext.weapon.parent->animSet;
            self->ext.weapon.unk80 = 0x40;
            self->step++;
        }
        return;
    case 2:
        if (--self->ext.weapon.unk80 == 0) {
            DestroyEntity(self);
            return;
        }
        self->posY.val += self->velocityY;
        self->ext.weapon.unk7E = (self->ext.weapon.unk7E + 0x80) & 0xFFF;
        self->posX.i.hi = self->ext.weapon.lifetime +
                          ((rcos(self->ext.weapon.unk7E) * 2) >> 8);
        if (self->ext.weapon.unk7E < 0x800) {
            self->zPriority = 0x1B4;
        } else {
            self->zPriority = 0x1BC;
        }
        self->rotX = self->rotY = -(rsin(self->ext.weapon.unk7E) >> 5) + 0xC0;
        break;
    }
}
void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
