// Weapon ID #18. Used by weapons:
// Power of Sire
#include "weapon_private.h"
#include "shared.h"

extern const char D_82000_8017A73C[]; // "\no\n"
extern s32 D_82000_8017B1B4;          // g_DebugWaitInfoTimer

void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (D_82000_8017B1B4++ & 4) {
        FntPrint(D_82000_8017A73C); // TODO: inline
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (!PadRead(0))
        DebugShowWaitInfo(msg);
}

INCLUDE_ASM("weapon/nonmatchings/w_018", EntityWeaponAttack);

extern AnimationFrame D_82000_8017A724[];

s32 func_ptr_80170004(Entity* self) {
    s16 angle;
    s32 scale;

    if (self->ext.weapon.parent->ext.weapon.equipId != 0x48) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
        }

        if (self->ext.weapon.parent->palette >= 0x128U) {
            self->palette = PAL_DRA(0x128);
        } else {
            self->palette = PAL_DRA(0x110);
        }

        self->unk5A = self->ext.weapon.parent->unk5A;
        self->facingLeft = 0;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->unk4C = D_82000_8017A724;
        self->rotX = self->rotY = 256;

        angle = rand();
        self->velocityX = rcos(angle) << 7;
        self->velocityY = -(rsin(angle) << 7);

        scale = rand() & 7;
        self->posX.val += scale * self->velocityX;
        self->posY.val += (scale + 2) * self->velocityY;

        g_api.PlaySfx(SFX_UNK_69D);
        self->ext.timer.t = 6;
        self->step++;
        break;

    case 1:
        self->ext.timer.t--;
        if (self->ext.timer.t == 0) {
            self->step++;
        }
        break;

    case 2:
        if (self->rotX < 512) {
            self->rotX += 16;
        }
        self->rotY = self->rotX;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    }
}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 18; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
