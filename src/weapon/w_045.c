// SPDX-License-Identifier: AGPL-3.0-only
// Weapon ID #45. Used by weapons:
// Unknown#216
#define FUNC_0C_S32
#include "weapon_private.h"
#include "w_045_1.h"
#include "w_045_2.h"
#define g_Animset w_045_1
#define g_Animset2 w_045_2
#include "sfx.h"

static u16 D_13F000_8017A330[] = {
    0x0000, 0x8822, 0x83E0, 0xECE5, 0xF68A, 0x8048, 0x884C, 0x88B5,
    0x8D39, 0x821C, 0x9CA4, 0xAD29, 0xBDAD, 0xD231, 0xE6B5, 0xEB7A,
    0x0000, 0xEB5A, 0xEAB1, 0xDE29, 0xE4E4, 0xA884, 0x8C00, 0x83E0,
    0x802D, 0x80DD, 0xAA5F, 0x84D1, 0x98C6, 0xB5AD, 0xC631, 0x8421,
};

static u16* g_WeaponCluts[] = {D_13F000_8017A330};
static s32 g_HandId = HAND_ID;

#include "shared.h"

extern s32 D_13F000_8017B3B8;
extern s32 D_13F000_8017B3BC;

int func_13F000_8017A718() {
    int var;
    if (!(g_Player.unk44 & 2)) {
        if (g_Entities[PLAYER_CHARACTER].facingLeft == 1) {
            if (g_Player.padPressed & PAD_RIGHT) {
                g_Entities[PLAYER_CHARACTER].facingLeft = 0;
                g_Player.unk4C = 1;
                return -1;
            }
            if (g_Player.padPressed & PAD_LEFT) {
                return 1;
            }
            do {
                var = 0;
            } while (0);
            return var;
        }
        if (!(g_Player.padPressed & PAD_RIGHT)) {
            if (g_Player.padPressed & PAD_LEFT) {
                g_Entities[PLAYER_CHARACTER].facingLeft = 1;
                g_Player.unk4C = 1;
                return -1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}

static void EntityWeaponAttack(Entity* self) {
    SetSpriteBank1(w_045_1);
    if (g_HandId != 0) {
        g_CurrentEntity->animSet = ANIMSET_OVL(0x12);
        g_CurrentEntity->palette = 0x128;
        g_CurrentEntity->unk5A = 0x66;
    } else {
        g_CurrentEntity->animSet = ANIMSET_OVL(0x10);
        g_CurrentEntity->palette = 0x110;
        g_CurrentEntity->unk5A = 0x64;
    }

    if (g_Player.pl_vram_flag & 1) {
        PLAYER.step = 0x28;
        PLAYER.step_s = 0;
        PLAYER.velocityX = PLAYER.velocityY = 0;
        PLAYER.ext.player.anim = 0xCF;
    } else {
        PLAYER.step = 0x2A;
        PLAYER.step_s = 0;
        PLAYER.velocityX = PLAYER.velocityY = 0;
        PLAYER.ext.player.anim = 0xCD;
    }
    PLAYER.animFrameIdx = 0;
    PLAYER.animFrameDuration = 0;
    LoadWeaponPalette(0);
}

static s32 func_ptr_80170004(Entity* self) {
    SetSpriteBank1(w_045_1);
    if (g_HandId != 0) {
        g_CurrentEntity->animSet = ANIMSET_OVL(0x12);
        g_CurrentEntity->palette = 0x128;
        g_CurrentEntity->unk5A = 0x66;
    } else {
        g_CurrentEntity->animSet = ANIMSET_OVL(0x10);
        g_CurrentEntity->palette = 0x110;
        g_CurrentEntity->unk5A = 0x64;
    }
    DecelerateX(FIX(0.125));
    if (!(g_Player.pl_vram_flag & 1)) {
        PLAYER.step = 0x2A;
        PLAYER.step_s = 0;
        PLAYER.velocityX = PLAYER.velocityY = 0;
        PLAYER.ext.player.anim = 0xD0;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
        return;
    }
    switch (PLAYER.step_s) {
    case 0:
        if (func_13F000_8017A718() != 0) {
            PLAYER.step = 0x29;
            PLAYER.step_s = 0;
            SetSpeedX(FIX(2.5));
            PLAYER.ext.player.anim = 0xCD;
            PLAYER.animFrameIdx = 0;
            PLAYER.animFrameDuration = 0;
        } else {
            if (g_Player.padTapped & PAD_SQUARE) {
                PLAYER.ext.player.anim = 0xCE;
                g_api.PlaySfx(SFX_UNK_6F0);
                PLAYER.animFrameIdx = 0;
                PLAYER.animFrameDuration = 0;
                PLAYER.step_s = 1;
                g_api.CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0, 0x57), 0);
                return;
            }
            if (g_Player.padTapped & PAD_CROSS) {
                if (g_Player.unk72 == 0) {
                    PLAYER.ext.player.anim = 0xD0;
                    PLAYER.step = 0x2A;
                    PLAYER.animFrameIdx = 0;
                    PLAYER.animFrameDuration = 0;
                    PLAYER.step_s = 0;
                    PLAYER.velocityY = FIX(-4);
                    func_13F000_8017A718();
                    return;
                }
            }
            if ((PLAYER.animFrameIdx == 1) || (PLAYER.animFrameIdx == 4) ||
                (PLAYER.animFrameIdx == 7)) {
                g_api.PlaySfx(SFX_UNK_6EE);
            }
            if (PLAYER.animFrameIdx == 10) {
                g_api.PlaySfx(SFX_UNK_6EF);
                return;
            }
            return;
        }
        break;
    case 1:
        if (PLAYER.animFrameDuration < 0) {
            PLAYER.step_s = 0;
            PLAYER.ext.player.anim = 0xCF;
            PLAYER.animFrameIdx = 0;
            PLAYER.animFrameDuration = 0;
        }
        break;
    }
}

static void func_ptr_80170008(Entity* self) {
    SetSpriteBank1(w_045_1);
    if (g_HandId != 0) {
        g_CurrentEntity->animSet = ANIMSET_OVL(0x12);
        g_CurrentEntity->palette = 0x128;
        g_CurrentEntity->unk5A = 0x66;
    } else {
        g_CurrentEntity->animSet = ANIMSET_OVL(0x10);
        g_CurrentEntity->palette = 0x110;
        g_CurrentEntity->unk5A = 0x64;
    }
    SetSpeedX(FIX(2.5));
    if (!(g_Player.pl_vram_flag & 1)) {
        PLAYER.step = 0x2A;
        PLAYER.step_s = 0;
        PLAYER.velocityY = 0;
        PLAYER.ext.player.anim = 0xD0;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
        return;
    }
    if (func_13F000_8017A718() == 0) {
        PLAYER.step = 0x28;
        PLAYER.step_s = 0;
        PLAYER.ext.player.anim = 0xCF;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
        PLAYER.velocityX >>= 1;
        return;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        PLAYER.ext.player.anim = 0xCE;
        g_api.PlaySfx(SFX_UNK_6F0);
        PLAYER.step = 0x28;
        PLAYER.step_s = 1;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
        PLAYER.velocityX >>= 1;
        g_api.CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0x57), 0);
        return;
    }
    if ((g_Player.padTapped & PAD_CROSS) && (g_Player.unk72 == 0)) {
        PLAYER.ext.player.anim = 0xD0;
        PLAYER.step = 0x2A;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
        PLAYER.step_s = 0;
        PLAYER.velocityY = FIX(-4);
        func_13F000_8017A718();
        return;
    }
    if (!(g_GameTimer & 7)) {
        g_api.PlaySfx(SFX_STOMP_SOFT_A);
        g_api.CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(0x100, 0x45), 0);
    }
}

static s32 func_ptr_8017000C(Entity* self) {
    SetSpriteBank1(w_045_1);
    if (g_HandId != 0) {
        g_CurrentEntity->animSet = ANIMSET_OVL(0x12);
        g_CurrentEntity->palette = 0x128;
        g_CurrentEntity->unk5A = 0x66;
    } else {
        g_CurrentEntity->animSet = ANIMSET_OVL(0x10);
        g_CurrentEntity->palette = 0x110;
        g_CurrentEntity->unk5A = 0x64;
    }

    PLAYER.velocityY += FIX(11) / 32;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
    if (g_Player.pl_vram_flag & 1) {
        if (PLAYER.step_s != 0) {
            PLAYER.step = 0x28;
            PLAYER.velocityY = 0;
            PLAYER.velocityX = 0;
            g_api.PlaySfx(SFX_STOMP_SOFT_A);
            return;
        }
        if (func_13F000_8017A718() != 0) {
            PLAYER.step = 0x29;
            PLAYER.step_s = 0;
            PLAYER.velocityY = 0;
            SetSpeedX(FIX(2.5));
            PLAYER.ext.player.anim = 0xCD;
            PLAYER.animFrameIdx = 0;
            PLAYER.animFrameDuration = 0;
        } else {
            PLAYER.step = 0x28;
            PLAYER.step_s = 0;
            PLAYER.velocityX = PLAYER.velocityY = 0;
            PLAYER.ext.player.anim = 0xCF;
            PLAYER.animFrameIdx = 0;
            PLAYER.animFrameDuration = 0;
        }
        g_api.PlaySfx(SFX_STOMP_SOFT_A);
        return;
    }
    DecelerateX(FIX(1) / 16);
    if (func_13F000_8017A718() != 0) {
        SetSpeedX(FIX(0.75));
    }
    if (PLAYER.step_s == 0) {
        if (g_Player.padTapped & PAD_SQUARE) {
            PLAYER.ext.player.anim = 0xCE;
            g_api.PlaySfx(SFX_UNK_6F0);
            PLAYER.step_s = 1;
            PLAYER.animFrameIdx = 0;
            PLAYER.animFrameDuration = 0;
            g_api.CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0, 0x57), 0);
        }
    } else if (PLAYER.animFrameDuration < 0) {
        PLAYER.ext.player.anim = 0xD0;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
        PLAYER.step_s = 0;
    }
}

static s32 func_ptr_80170010(Entity* self) {
    D_13F000_8017B3BC += 0x80;
    SetSpriteBank1(w_045_1);
    if (g_HandId != 0) {
        g_CurrentEntity->animSet = ANIMSET_OVL(0x12);
        g_CurrentEntity->palette = 0x128;
        g_CurrentEntity->unk5A = 0x66;
    } else {
        g_CurrentEntity->animSet = ANIMSET_OVL(0x10);
        g_CurrentEntity->palette = 0x110;
        g_CurrentEntity->unk5A = 0x64;
    }
    PLAYER.drawFlags = FLAG_DRAW_ROTZ;
    switch (PLAYER.step_s) {
    case 0:
        if (PLAYER.entityRoomIndex == PLAYER.facingLeft) {
            PLAYER.rotZ = -0x200;
        } else {
            PLAYER.rotZ = 0x200;
        }
        PLAYER.rotPivotY = 0x14;
        PLAYER.step_s++;
        return;
    case 1:
        PLAYER.velocityY += FIX(22.0 / 128);
        if (PLAYER.velocityY > FIX(7)) {
            PLAYER.velocityY = FIX(7);
        }
        if (g_Player.pl_vram_flag & 2) {
            PLAYER.velocityY = FIX(1);
        }
        if (g_Player.pl_vram_flag & 1) {
            if (PLAYER.entityRoomIndex == PLAYER.facingLeft) {
                PLAYER.rotZ = -0x380;
            } else {
                PLAYER.rotZ = 0x380;
            }
            PLAYER.step_s = 2;
            PLAYER.velocityY = 0;
            D_13F000_8017B3B8 = 0x30;
            g_api.PlaySfx(SFX_STOMP_SOFT_A);
            // Blueprint 0 makes child 2, func_8011B5A4
            g_api.CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
            return;
        }
        return;
    case 2:
        PLAYER.drawFlags = FLAG_DRAW_UNK8 | FLAG_DRAW_ROTZ;
        PLAYER.unk6C = (rsin(D_13F000_8017B3BC) >> 7) - 0x40;
        if (!(g_Player.pl_vram_flag & 1)) {
            PLAYER.step = Player_AxearmorJump;
            PLAYER.step_s = 0;
            PLAYER.velocityY = 0;
            PLAYER.ext.player.anim = 0xD0;
            PLAYER.animFrameIdx = 0;
            PLAYER.animFrameDuration = 0;
            PLAYER.rotZ = 0;
            PLAYER.drawFlags = FLAG_DRAW_DEFAULT;
            return;
        }
        DecelerateX(FIX(16.0 / 128));
        if (D_13F000_8017B3B8 == 5) {
            if (PLAYER.entityRoomIndex == PLAYER.facingLeft) {
                PLAYER.rotZ = -0x200;
            } else {
                PLAYER.rotZ = 0x200;
            }
        }
        if (!--D_13F000_8017B3B8) {
            PLAYER.step = Player_AxearmorStand;
            PLAYER.step_s = 0;
            PLAYER.velocityY = 0;
            PLAYER.ext.player.anim = 0xCF;
            PLAYER.animFrameIdx = 0;
            PLAYER.animFrameDuration = 0;
            PLAYER.rotZ = 0;
            PLAYER.drawFlags = FLAG_DRAW_DEFAULT;
        }
        break;
    }
}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 45; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
