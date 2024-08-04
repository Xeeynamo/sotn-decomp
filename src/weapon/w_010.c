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

extern SpriteParts D_4A000_8017A040[];
extern s8 D_4A000_8017AB20;
extern AnimationFrame* D_4A000_8017AB68;

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
        self->unk4C = D_4A000_8017ABA0;
        g_api.PlaySfx(SFX_UNK_664);
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

INCLUDE_ASM("weapon/nonmatchings/w_010", EntityWeaponShieldSpell);

INCLUDE_ASM("weapon/nonmatchings/w_010", func_ptr_80170024);

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
