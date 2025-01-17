// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void func_8010E42C(u32 substep) {
    PLAYER.step = Player_Teleport;
    PLAYER.step_s = substep;

    if (substep & 1) {
        SetPlayerAnim(0xF5);
    } else {
        SetPlayerAnim(0xF4);
    }
}

u8 D_800ACF4C[] = {0x00, 0x11, 
                   0x04, 0x15, 
                   0x01, 0x10, 
                   0x03, 0x23};

void func_8010E470(s32 arg0, s32 arg1) {
    PLAYER.velocityX = arg1;
    PLAYER.velocityY = 0;
    PLAYER.step = Player_Crouch;
    PLAYER.step_s = (s16)D_800ACF4C[arg0 * 2 + 0];
    SetPlayerAnim(D_800ACF4C[arg0 * 2 + 1]);
}

// This may be the function that turns Alucard into stone
void func_8010E4D0(void) {
    func_80111CC0();

    PLAYER.palette = PAL_OVL(0x100);
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;

    if (g_Player.unk72 == 1 || g_Player.unk72 == 2) {
        SetPlayerAnim(0xC7);
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
        SetPlayerStep(Player_AlucardStuck);
        func_80111CC0();
        PlaySfx(SFX_VO_ALU_WHAT);
        return;
    }
    func_80111CC0();
    func_8010E470(0, 0);
}

u8 D_800ACF54[] = {
    0x04, 0x05, 
    0x0A, 0x0B, 
    0x0E, 0x0F, 
    0x1D, 0x1E, 
    0x04, 0x03, 
    0x00, 0x00,
};

// Corresponding RIC function is RicLandToTheGround (much simpler)
void func_8010E570(s32 arg0) {
    s32 anim = 0;
    bool atLedge = false;
    
    if (g_Player.pl_vram_flag & 0x20) {
        atLedge = true;
    }

    PLAYER.velocityX = arg0;
    PLAYER.velocityY = 0;
    SetPlayerStep(Player_Stand);
    if (g_Player.unk48) {
        PLAYER.step_s = 2;
        atLedge = false;
    }
    switch (g_Player.prev_step) {
    case Player_UnmorphBat:
        anim = 4;
        break;
    case Player_Walk:
        anim = 4;
        if (PLAYER.ext.player.anim == 9) {
            PLAYER.ext.player.anim = D_800ACF54[2 + atLedge];
            return;
        }
        if (PLAYER.ext.player.anim == 7) {
            anim = 0;
        }
        break;
    case Player_Jump:
    case Player_Fall:
        anim = 6;
        if (abs(PLAYER.velocityX) > FIX(2.5)) {
            anim = 4;
        }
        break;
    default:
        anim = 8;
        break;
    }
    anim += atLedge;
    SetPlayerAnim(D_800ACF54[anim]);
}

void func_8010E6AC(bool forceAnim13) {
    bool atLedge;

    atLedge = 0;
    if (g_Player.pl_vram_flag & 0x20) {
        atLedge = 1;
    }

    SetSpeedX(FIX(1.5));
    PLAYER.velocityY = 0;
    SetPlayerStep(Player_Walk);

    if (forceAnim13) {
        if (PLAYER.ext.player.anim != 13) {
            SetPlayerAnim(13);
        }
    } else {
        SetPlayerAnim(7);
        // Factory blueprint 1 has child 2, which is func_8011B5A4
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(1, 5), 0);
    }

    if (g_Player.unk4C) {
        PLAYER.ext.player.anim = 9;
    }

    if ((PLAYER.ext.player.anim == 7) && atLedge) {
        PLAYER.animFrameIdx = 1;
    }

    if (g_Player.prev_step == Player_Crouch) {
        PLAYER.animFrameIdx = 4;
    }
}

void func_8010E7AC(void) {
    SetPlayerStep(Player_Fall);

    if (g_Player.prev_step != Player_Walk) {
        SetPlayerAnim(28);
    }
    
    PLAYER.velocityX = 0;
    PLAYER.velocityY = FIX(2);
    g_Player.timers[ALU_T_6] = 8;

    if (g_Player.unk04 & 1) {
        g_Player.timers[ALU_T_5] = 8;
    } else {
        g_Player.timers[ALU_T_5] = 0;
    }

    g_Player.unk44 = 16;
}

void func_8010E83C(bool clearUnk44bit) {
    if (g_Player.unk72) {
        func_8010E7AC();
        return;
    } else if (CheckMoveDirection()) {
        SetPlayerAnim(26);
        SetSpeedX(FIX(1.5));
        g_Player.unk44 = 0;
    } else {
        SetPlayerAnim(22);
        PLAYER.velocityX = 0;
        g_Player.unk44 = 4;
    }

    PLAYER.velocityY = FIX(-4.875);
    SetPlayerStep(Player_Jump);

    if (g_Player.prev_step == Player_Walk) {
        g_Player.unk44 |= 0x10;
    }

    if (clearUnk44bit) {
        // clear the bit
        g_Player.unk44 &= ~1;
    } else {
        // set the bit
        g_Player.unk44 |= 1;
    }
}

void func_8010E940(void) {
    g_Player.unk44 |= (0x20 | 0x01);
    SetPlayerAnim(32);
    PLAYER.step_s = 0;
    PLAYER.velocityY = FIX(-4.25);
    if (g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

void DoGravityJump(void) {
    if (CheckMoveDirection() != 0) {
        SetSpeedX(FIX(3));
    } else {
        PLAYER.velocityX = 0;
    }

    if (PLAYER.step == Player_Jump) {
        g_Player.unk44 |= 1;
    } else {
        g_Player.unk44 = 0;
    }
    // Factory with blueprint 2, creates child entity 3 which is
    // EntityGravityBootBeam
    CreateEntFactoryFromEntity(g_CurrentEntity, 2, 0);
    SetPlayerStep(Player_HighJump);
    PLAYER.velocityY = FIX(-12);
    SetPlayerAnim(0x21);
    g_Player.unk4A = 0;
}

s16 g_SfxAttackGrunts[] = {
    SFX_VO_ALU_ATTACK_A,
    SFX_VO_ALU_ATTACK_B,
    SFX_VO_ALU_ATTACK_C,
    SFX_VO_ALU_ATTACK_D,
    #ifndef VERSION_PSP
    0x0000,
    0x0000
    #endif
    };

void func_8010EA54(s32 arg0) {
    s16 temp_hi;

    if (arg0 != 0) {
        temp_hi = rand() % arg0;
        if (temp_hi < 4) {
            PlaySfx(g_SfxAttackGrunts[temp_hi]);
        }
    }
}

static s32 CheckSubwpnChainLimit(s16 subwpnId, s16 limit) {
    Entity* entity;
    s32 i;
    s32 nFound;
    s32 nEmpty;
    // Iterate through entities 32-48 (which hold subweapons)
    // Any that match the proposed ID increments the count.
    // If at any point the count reaches the limit, return -1.
    entity = &g_Entities[32];
    for (i = 0, nFound = 0, nEmpty = 0; i < 16; i++, entity++) {
        if (!entity->entityId) {
            nEmpty++;
        }
        if (entity->ext.subweapon.subweaponId &&
            entity->ext.subweapon.subweaponId == subwpnId) {
            nFound++;
        }
        if (nFound >= limit) {
            return -1;
        }
    }
    // This will indicate that there is an available entity slot
    // to hold the subweapon we're trying to spawn.
    if (nEmpty) {
        return 0;
    }
    // if none is empty, return -1 to prevent spawning the subwpn
    return -1;
}

// Attempts to use subweapon. Performs checks before activating.
// If it succeeds, factory is called to spawn the subweapon, and return 0.
// If it fails, return a number 1 through 4 indicating why.
static s32 func_8010EB5C(void) {
    SubweaponDef subWpn;
    s16 chainLimit;
    s16 subWpnId;
    s16 anim;
    s16 atLedge2;
    s32 atLedge;

    atLedge = 0;
    // If control is not pressed
    if (!(g_Player.padPressed & PAD_UP)) {
        return 1;
    }
    if (g_Player.pl_vram_flag & 0x20) {
        atLedge = 1;
    }
    subWpnId = func_800FE3C4(&subWpn, 0, false);
    // If we don't have a subweapon obtained
    if (subWpnId == 0) {
        return 1;
    }
    // If it's the stopwatch, but we're already paused
    if (subWpnId == SUBWPN_STOPWATCH && g_unkGraphicsStruct.pauseEnemies) {
        return 4;
    }
    // If we already have too many of the subweapon active
    chainLimit = subWpn.chainLimit;
    if (CheckSubwpnChainLimit(subWpnId, chainLimit) < 0) {
        return 2;
    }
    // Should be if we don't have enough hearts?
    subWpnId = func_800FE3C4(&subWpn, 0, true);
    if (subWpnId == 0) {
        return 3;
    }
    CreateEntFactoryFromEntity(
        g_CurrentEntity, subWpn.blueprintNum, subWpnId << 9);
    g_Player.timers[10] = 4;
    if (PLAYER.step_s >= 64) {
        return 0;
    }
    anim = subWpn.anim;
    switch (PLAYER.step) {
        case Player_Stand:
        atLedge2 = atLedge; //stupid duplicate
        SetPlayerAnim(anim + atLedge2);
        break;
        case Player_Crouch:
        case Player_Walk:
        case Player_Fall:
        case Player_Jump:
        break;
    }
    func_8010EA54(8);
    return 0;
}

// Checks for deployed weapons that exist and determines if more are allowed.
// Example: You can only have 3 Buffalo Stars thrown per hand. Returns 0 if
// allowed to deploy another, -1 if limit is reached.
s32 CheckChainLimit(s32 itemId, s32 handId) {
    Entity* entity;
    s32 existing_count;
    s32 i;
    s32 chainLimit;
    Equipment* eDef = &g_EquipDefs[itemId];

    chainLimit = eDef->chainLimit;
    if (chainLimit & 0x80) {
        if(!(g_Player.unk46 & 0x8000)){
            return 0;
        }
        return -1;
    }
    entity = &g_Entities[16];
    for (i = 16, existing_count = 0; i < 64; i++, entity++) {
        if (entity->ext.weapon.equipId != itemId) {
            continue;
        }

        if (handId != 0) {
            if (entity->params & 0x8000) {
                existing_count++;
            }
        } else {
            if (!(entity->params & 0x8000)) {
                existing_count++;
            }
        }

        if (!(existing_count < chainLimit)) {
            return -1;
        }
    }
    return 0;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_091149C8);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_psp_09114A38);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_8010FAF4);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformHellfire);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformDarkMetamorphosis);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformSoulSteal);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformSummonSpirit);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformTetraSpirit);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformSwordBrothers);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_8010FD88);

// Next func in PSP is SetPlayerStep; next in US is func_8010FDF8. File split.
