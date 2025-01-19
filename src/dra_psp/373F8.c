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

u8 D_800ACF4C[] = {0x00, 0x11, 0x04, 0x15, 0x01, 0x10, 0x03, 0x23};

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
    0x04, 0x05, 0x0A, 0x0B, 0x0E, 0x0F, 0x1D, 0x1E, 0x04, 0x03, 0x00, 0x00,
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
        atLedge2 = atLedge; // stupid duplicate
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
        if (!(g_Player.unk46 & 0x8000)) {
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

void func_8010ED54(u8 anim) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SwordWarp);
    SetPlayerAnim(anim);
    // Factory 61 has child 31, EntityPlayerOutline
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(61, 20), 0);
    g_Player.unk48 = 0;
}

bool func_8010EDB8(void) {
    Entity* ent6C;
    bool var_s7; // Triggers on some kind of special move spell
    Equipment sp10;
    bool atLedge;
    Entity* ent;
    Equipment* equipped_item;

    s16 var_s2;         // mixed between anim and equip index
    u16 equipped_id;
    u16 hand;
    s16 animVariant;
    u32 attBtnsPressed;
    s32 i;

    var_s7 = false;

    atLedge = false;
    if (g_Player.pl_vram_flag & 0x20) {
        atLedge = true;
    }
    attBtnsPressed = g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE);

    if (attBtnsPressed != 0 && func_8010EB5C() == 0) {
        return true;
    }
    if (g_Player.unk48 == 0) {
        if ((GetEquipItemCategory(0) == ITEM_SHIELD) &&
            (g_Player.padPressed & PAD_SQUARE)) {
            attBtnsPressed |= PAD_SQUARE;
        }
        if ((GetEquipItemCategory(1) == ITEM_SHIELD) &&
            (g_Player.padPressed & PAD_CIRCLE)) {
            attBtnsPressed |= PAD_CIRCLE;
        }
    }
    if (attBtnsPressed == 0) {
        return false;
    }
    if (attBtnsPressed == PAD_CIRCLE) {
        g_Player.D_80072EF8 = PAD_CIRCLE;
        hand = 1;
    }
    if (attBtnsPressed == PAD_SQUARE) {
        g_Player.D_80072EF8 = PAD_SQUARE;
        hand = 0;
    }
    if (attBtnsPressed == (PAD_SQUARE | PAD_CIRCLE)) {
        if (!g_Player.unk72 && D_8013AEE4) {
            var_s2 = D_8013AEE4 & ~0x80000000;
            if (var_s2) {
                equipped_item = &g_EquipDefs[var_s2];
                equipped_id = var_s2;
            }
            g_Player.D_80072EF8 = PAD_SQUARE;
            if (D_8013AEE4 & 0x80000000) {
                hand = 1;
            } else {
                hand = 0;
            }
            if (CheckChainLimit(equipped_id, hand) >= 0 &&
                HasEnoughMp(g_EquipDefs[equipped_id].mpUsage, 0) == 0) {
                var_s7 = true;
                goto block_45;
            }
        }
        g_Player.D_80072EF8 = PAD_SQUARE;
        hand = 0;
    }

    equipped_item = &g_EquipDefs[g_Status.equipment[hand]];
    equipped_id = g_Status.equipment[hand];

    if (equipped_item->unk17 == equipped_item->specialMove &&
        equipped_item->unk17) { // Literally just the Combat Knife
        if (g_Entities[16].ext.entSlot16.unkAE == equipped_id) {
            var_s2 = equipped_item->unk17;
            equipped_item = &g_EquipDefs[var_s2];
            equipped_id = var_s2;
            if (CheckChainLimit(equipped_id, hand) < 0) {
                goto block_32;
            }
            goto block_45;
        } else if (g_Entities[16].ext.entSlot16.unkAE == equipped_item->unk17 &&
                   CheckChainLimit(equipped_id, hand) >= 0) {
            goto block_45;
        }
    }

block_32:
    equipped_item = &g_EquipDefs[g_Status.equipment[hand]];
    equipped_id = g_Status.equipment[hand];
    if (g_ButtonCombo[COMBO_QCF].buttonsCorrect != COMBO_COMPLETE) {
        goto block_38c;
    }
    var_s2 = equipped_item->specialMove;
    if (!var_s2 ||
        // Sword of Dawn
        ((equipped_id == 0x11) && ((g_Player.pl_vram_flag & 0x41) != 1)) ||
        !(g_Player.pl_vram_flag & 1)) {
        goto block_38c;
    }
    // Load up the item's special move as the new "virtual" equipped item since
    // we're attacking with the special
    equipped_item = &g_EquipDefs[var_s2];
    equipped_id = var_s2;
    if (CheckChainLimit(equipped_id, hand) < 0 ||
        HasEnoughMp(g_EquipDefs[equipped_id].mpUsage, 0)) {
    block_38c:
        equipped_item = &g_EquipDefs[g_Status.equipment[hand]];
        equipped_id = g_Status.equipment[hand];

        if (g_ButtonCombo[COMBO_BF].buttonsCorrect == 0xFF) {
            var_s2 = equipped_item->unk17;
            if (var_s2) {
                equipped_item = &g_EquipDefs[var_s2];
                equipped_id = var_s2;
                if (CheckChainLimit(equipped_id, hand) >= 0) {
                    goto block_45;
                }
            }
        }
        equipped_item = &g_EquipDefs[g_Status.equipment[hand]];
        equipped_id = g_Status.equipment[hand];
        if (CheckChainLimit(equipped_id, hand) < 0) {
            return false;
        }
    }
block_45:
    if (equipped_id) {
        if (equipped_item->unk13 == 55) {     // Medicines
            if (equipped_item->unk14 == 20) { // Library card!
                if (PLAYER.step == Player_Stand || PLAYER.step == Player_Walk ||
                    PLAYER.step == Player_Crouch) {
                    func_8010E42C(0);
                    func_800FDD44(hand);
                    return true;
                }
                return false;
            }
            // Check if there is already an instance of entity 39,
            // EntityPlayerPinkEffect
            for (ent = &g_Entities[32], i = 32; i < 64; i++, ent++) {
                if (ent->entityId == 39) {
                    return false;
                }
            }
            // There isn't one, so we create one.
            // Blueprint 55, child 39. EntityPlayerPinkEffect
            ent6C = CreateEntFactoryFromEntity(
                g_CurrentEntity,
                FACTORY(55, (equipped_item->unk14 & 0x7F) + (hand << 7)),
                equipped_id);
        } else if (g_Player.timers[ALU_T_CURSE]) {
            // Blueprint 57, child 31. EntityPlayerOutline
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(57, 1), 0);
            goto block_70;
        } else if (!var_s7) {
            ent6C = CreateEntFactoryFromEntity(
                g_CurrentEntity,
                FACTORY(equipped_item->unk13 + ((hand + 1) << 12),
                        (equipped_item->unk14 & 0x7F) + (hand << 7)),
                equipped_id);
        } else {
            ent6C = CreateEntFactoryFromEntity(
                g_CurrentEntity,
                FACTORY(equipped_item->unk13 + ((hand + 1) << 14),
                        (equipped_item->unk14 & 0x7F) + (hand << 7)),
                equipped_id);
        }
    } else {
        ent6C = CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY((hand + 42), (hand << 7)), 0);
    }

    if (ent6C == NULL) {
        return false;
    }

    func_800FDD44(hand);
    if (var_s7) {
        func_800FDD44((hand + 1) & 1);
    }
    HasEnoughMp(g_EquipDefs[equipped_id].mpUsage, 1);
    // 95 is Estoc
    if ((equipped_id == 95) && g_Player.unk72) {
        return false;
    }

    var_s2 = equipped_item->playerAnim;
    switch (equipped_item->unk11) {
    case 29: // Muramasa
        GetEquipProperties(hand, &sp10, equipped_id);
        // Muramasa with sufficient attack is a normal sword.
        if (sp10.attack >= 11) {
            goto block_1000;
        }
    // Muramasa with low attack, or Red Rust, has chance to fail.
    case 13: // Red Rust
        if (rand() & 7) {
            goto block_1000;
        }
    block_70:
        switch (PLAYER.step) {
        case Player_Stand:
        case Player_Walk:
            SetPlayerAnim(0xB5);
            PLAYER.step = Player_Stand;
            break;
        case Player_Crouch:
            SetPlayerAnim(0xB6);
            PLAYER.step = Player_Crouch;
            break;
        case Player_Fall:
        case Player_Jump:
            SetPlayerAnim(0xB7);
            PLAYER.step = Player_Jump;
            break;
        }
        g_Player.unk46 = 0x8012;
        g_Player.unk54 = 0xFF;
        PLAYER.step_s = 0x51;
        PlaySfx(SFX_VO_ALU_PAIN_A);
        return true;

    case 12: // Shotel
        // When shotel is thrown away, attempting to attack will make a punch
        if (CheckChainLimit(equipped_item->specialMove, hand) >= 0 &&
            CheckChainLimit(equipped_item->specialMove, (hand + 1) & 1) >= 0) {
            goto block_1000;
        }
        equipped_item = &g_EquipDefs[0];
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY((hand + 42), (hand << 7)), 0);
        var_s2 = equipped_item->playerAnim;
        goto block_1000;

    case 19: // Unknown, not a direct equippable item
        D_80139824 = 40;
        PLAYER.step = 0;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 20: // Unknown, not a direct equippable item
        PLAYER.step = 0;
        D_80139824 = 40;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 21: // Unknown, not a direct equippable item
        PLAYER.step = 0;
        D_80139824 = 40;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 22: // Unknown, not a direct equippable item (but there are 4 of them)
        PLAYER.step = 0;
        D_80139824 = 40;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 28: // Unknown, not a direct equippable item
        PLAYER.step = 0;
        D_80139824 = 10;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 23: // Unknown, not a direct equippable item (but there are 4 of them)
        PLAYER.step = 0;
        CheckMoveDirection();
        SetSpeedX(FIX(5));
        g_CurrentEntity->velocityY = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 27: // Estoc
        CheckMoveDirection();
        SetSpeedX(FIX(4));
        PLAYER.velocityX >>= 1;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        animVariant = atLedge;
        if (g_Player.pl_vram_flag & 1) {
            PLAYER.step = 0;
            g_CurrentEntity->velocityY = 0;
        } else {
            PLAYER.step = 4;
        }
        SetPlayerAnim(var_s2 + animVariant);
        g_Player.unk46 = equipped_item->unk11 + 0x7FFF + 2;
        g_Player.unk54 = equipped_item->lockDuration;
        PLAYER.step_s = equipped_item->unk11 + 0x40;
        g_Player.timers[ALU_T_9] = 4;
        break;
    case 24: // Unknown, not a direct equippable item (but there are 2 of them)
        if (PLAYER.step == Player_Fall || PLAYER.step == Player_Jump) {
            PLAYER.step = Player_Jump;
        } else {
            PLAYER.step = Player_Stand;
        }
        D_80139824 = 0x80;
        g_CurrentEntity->velocityY = 0;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 26: // Unknown, not a direct equippable item (but there are 2 of them)
        PLAYER.step = 0;
        D_80139824 = 40;
        g_CurrentEntity->velocityY = 0;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;

    block_1000:
        func_8010EA54(8);

    case 8:
    case 9: // Combat Knife
    case 10:
    case 25:
    block_98:
        switch (PLAYER.step) {
        case 0:
        case 1:
            g_CurrentEntity->velocityX = g_CurrentEntity->velocityX >> 1;
            PLAYER.step = 0;
            animVariant = atLedge;
            break;
        case 2:
            animVariant = 2;
            if (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) {
                animVariant++;
            }
            if (!g_Player.unk72 && PLAYER.step_s == 2) {
                animVariant = atLedge;
                PLAYER.step = 0;
            }
            break;
        case 3:
        case 4:
            animVariant = 4;
            if (PLAYER.velocityY > 0) {
                animVariant++;
                if (equipped_item->unk11 == 0) {
                    if (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT) &&
                        g_Player.padPressed & PAD_DOWN) {
                        animVariant++;
                    }
                } else if (g_Player.padPressed & PAD_DOWN) {
                    animVariant++;
                }
            }
            break;
        }
        SetPlayerAnim(var_s2 + animVariant);
        g_Player.unk46 = equipped_item->unk11 + 0x7FFF + 2;
        g_Player.unk54 = equipped_item->lockDuration;
        PLAYER.step_s = equipped_item->unk11 + 0x40;
        g_Player.timers[ALU_T_9] = 4;
        break;
    case 0: // Most normal swords come in this range
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 11:
    case 14:
    case 15:
    case 16:
    case 18:
        goto block_1000;
    case 5: // Lots of unknown things
        switch (PLAYER.step) {
        case 0:
        case 1:
        case 2:
            g_CurrentEntity->velocityX = g_CurrentEntity->velocityX >> 1;
            animVariant = atLedge;
            SetPlayerAnim(var_s2 + animVariant);
            g_Player.unk46 = equipped_item->unk11 + 0x7FFF + 2;
            g_Player.unk54 = equipped_item->lockDuration;
            PLAYER.step = 0;
            PLAYER.step_s = equipped_item->unk11 + 0x40;
            g_CurrentEntity->velocityX = 0;
        case 3:
        case 4:
            break;
        }
        func_8010EA54(8);
        break;
    case 128: // Shields
        var_s2 = equipped_item->playerAnim;
        switch (PLAYER.step) {
        case 0:
            PLAYER.step_s = 2;
            animVariant = atLedge;
            SetPlayerAnim(var_s2 + animVariant);
            break;
        case 2:
            animVariant = 2;
            PLAYER.step_s = 0;
            // Block can never happen, we just set step_s to 0.
            if (!g_Player.unk72 && PLAYER.step_s == 2) {
                animVariant = atLedge;
                PLAYER.step = 0;
                PLAYER.step_s = 2;
            }
            SetPlayerAnim(var_s2 + animVariant);
            break;
        case 1:
        case 3:
        case 4:
            break;
        }
        break;
    case 134: // Holbein Dagger and Blue Knuckles
        func_8010DFF0(1, 0x20);
    case 129: // Consumable weapons (throwing stars, etc)
    case 130:
        func_8010EA54(8);
    case 132: // Food
        if (PLAYER.step_s < 0x40) {
            var_s2 = equipped_item->playerAnim;
            switch (PLAYER.step) {
            case 0:
                animVariant = atLedge;
                SetPlayerAnim(var_s2 + animVariant);
                break;
            case 2:
                animVariant = 2;
                if (!g_Player.unk72 && PLAYER.step_s == 2) {
                    animVariant = atLedge;
                    SetPlayerStep(Player_Stand);
                }
                SetPlayerAnim(var_s2 + animVariant);
            case 1:
            case 3:
            case 4:
                break;
            }
        }
        break;
    case 17:
        break;
    case 131: // Medicines
        if (PLAYER.step_s < 0x40) {
            var_s2 = equipped_item->playerAnim;
            switch (PLAYER.step) {
            case 0:
                animVariant = atLedge;
                SetPlayerAnim(var_s2 + animVariant);
                break;
            case 2:
            case 1:
            case 3:
            case 4:
                break;
            }
        }
        break;
    case 135: // Unknown
        PlaySfx(SFX_VO_ALU_ATTACK_C);
        g_Player.timers[ALU_T_9] = 4;
        func_8010ED54(equipped_item->playerAnim);
        break;
    }
    return true;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_8010FAF4);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformHellfire);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformDarkMetamorphosis);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformSoulSteal);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformSummonSpirit);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformTetraSpirit);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", PerformSwordBrothers);

INCLUDE_ASM("dra_psp/psp/dra_psp/373F8", func_8010FD88);

// Next func in PSP is SetPlayerStep; next in US is func_8010FDF8. File split.
