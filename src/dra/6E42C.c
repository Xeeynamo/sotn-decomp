// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

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

void func_8010E6AC(s32 arg0) {
    bool atLedge;

    atLedge = 0;
    if (g_Player.pl_vram_flag & 0x20) {
        atLedge = 1;
    }

    SetSpeedX(0x18000);
    PLAYER.velocityY = 0;
    SetPlayerStep(Player_Walk);

    if (arg0 != 0) {
        if (PLAYER.ext.player.anim != 0xD) {
            SetPlayerAnim(0xD);
        }
    } else {
        SetPlayerAnim(7);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(1, 5), 0);
    }

    if (g_Player.unk4C != 0) {
        PLAYER.ext.player.anim = 9;
    }

    if ((PLAYER.ext.player.anim == 7) && atLedge) {
        PLAYER.animFrameIdx = 1;
    }

    if (g_Player.prev_step == 2) {
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
    s32 nFound;
    s32 nEmpty;
    s32 i;
    // Iterate through entities 32-48 (which hold subweapons)
    // Any that match the proposed ID increments the count.
    // If at any point the count reaches the limit, return -1.
    entity = &g_Entities[32];
    for (i = 0, nFound = 0, nEmpty = 0; i < 16; i++, entity++) {
        if (entity->entityId == E_NONE) {
            nEmpty++;
        }
        if (entity->ext.subweapon.subweaponId != 0 &&
            entity->ext.subweapon.subweaponId == subwpnId) {
            nFound++;
        }
        if (nFound >= limit) {
            return -1;
        }
    }
    // This will indicate that there is an available entity slot
    // to hold the subweapon we're trying to spawn.
    // At the end, if this is zero, there are none available so return
    // -1 to indicate there is no room for the proposed subweapon.
    if (nEmpty == 0) {
        return -1;
    }
    return 0;
}

// Attempts to use subweapon. Performs checks before activating.
// If it succeeds, factory is called to spawn the subweapon, and return 0.
// If it fails, return a number 1 through 4 indicating why.
static s32 func_8010EB5C(void) {
    SubweaponDef subWpn;
    s16 subWpnId;
    s32 atLedge;
    u8 anim;

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
    if (CheckSubwpnChainLimit(subWpnId, subWpn.chainLimit) < 0) {
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
    if (PLAYER.step_s < 64) {
        anim = subWpn.anim;
        if (PLAYER.step == 0) {
            SetPlayerAnim(anim + atLedge);
        }
        func_8010EA54(8);
    }
    return 0;
}

s32 CheckChainLimit(s32 itemId, s32 handId) {
    Entity* entity;
    s32 existing_count;
    s32 i;
    s32 chainLimit;

    chainLimit = g_EquipDefs[itemId].chainLimit;
    if (chainLimit & 0x80) {
        return -(s32)((u16)g_Player.unk46 >> 0xF);
    }
    entity = &g_Entities[16];
    for (i = 16, existing_count = 0; i < 64; i++, entity++) {
        // Hack to load unkAE as an s16 (struct has s8)
        // Longer term, figure out what g_Entites[16-64] are
        // and make dedicated ent extension.
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
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(61, 0x14), 0);
    g_Player.unk48 = 0;
}

bool func_8010EDB8(void) {
    s32 step;
    Equipment sp10;
    Entity* ent;
    Equipment* equipped_item;
    s16 var_s2; // mixed between anim and equip index
    u16 equipped_id;
    u16 hand;
    s16 animVariant;
    s32 attBtnsPressed;
    bool var_s7; // Triggers on some kind of special move spell
    s32 i;
    s32 atLedge;

    var_s7 = 0;
    attBtnsPressed = g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE);

    atLedge = 0;
    if (g_Player.pl_vram_flag & 0x20) {
        atLedge = 1;
    }

    if (attBtnsPressed != 0 && func_8010EB5C() == 0) {
        return 1;
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
        return 0;
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
        if ((g_Player.unk72 == 0) && (D_8013AEE4 != 0)) {
            var_s2 = D_8013AEE4;
            if (var_s2 != 0) {
                equipped_item = &g_EquipDefs[var_s2];
                equipped_id = var_s2;
            }
            g_Player.D_80072EF8 = 0x80;
            hand = ((D_8013AEE4 & (1 << 31)) != 0);
            if (CheckChainLimit(equipped_id, hand) >= 0) {
                if (HasEnoughMp(g_EquipDefs[equipped_id].mpUsage, 0) == 0) {
                    var_s7 = 1;
                    goto block_45;
                }
            }
        }
        g_Player.D_80072EF8 = 0x80;
        hand = 0;
    }

    equipped_id = g_Status.equipment[hand];
    equipped_item = &g_EquipDefs[g_Status.equipment[hand]];

    if (equipped_item->unk17 == equipped_item->specialMove &&
        equipped_item->unk17 != 0) { // Literally just the Combat Knife
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
    equipped_id = g_Status.equipment[hand];
    equipped_item = &g_EquipDefs[g_Status.equipment[hand]];
    if (g_ButtonCombo[COMBO_QCF].buttonsCorrect != COMBO_COMPLETE) {
        goto block_38c;
    }
    var_s2 = equipped_item->specialMove;
    if (var_s2 == 0 ||
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
        if (g_ButtonCombo[COMBO_BF].buttonsCorrect == 0xFF) {
            var_s2 = equipped_item->unk17;
            if (var_s2 != 0) {
                equipped_item = &g_EquipDefs[var_s2];
                equipped_id = var_s2;
                if (CheckChainLimit(equipped_id, hand) >= 0) {
                    goto block_45;
                }
            }
        }
        equipped_id = g_Status.equipment[hand];
        equipped_item = &g_EquipDefs[g_Status.equipment[hand]];
        if (CheckChainLimit(equipped_id, hand) < 0) {
            return 0;
        }
    }
block_45:
    if (equipped_id != 0) {
        if (equipped_item->unk13 == 55) {     // Medicines
            if (equipped_item->unk14 == 20) { // Library card!
                if (PLAYER.step == 0 || PLAYER.step == 1 || PLAYER.step == 2) {
                    func_8010E42C(0);
                    func_800FDD44(hand);
                    return 1;
                }
                return 0;
            }
            ent = &g_Entities[32];
            for (i = 32; i < 64; i++) {
                if (ent->entityId == 0x27) {
                    return 0;
                }
                ent++;
            }
            // TODO: FACTORY()
            if (CreateEntFactoryFromEntity(
                    g_CurrentEntity,
                    (((equipped_item->unk14 & 0x7F) + (hand << 7)) << 0x10) |
                        0x37,
                    equipped_id) == NULL) {
                return 0;
            }
        } else {
            if (g_Player.timers[1]) {
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(57, 1), 0);
                goto block_70;
            }
            if (var_s7 == 0) {
                // TODO: FACTORY()
                if (CreateEntFactoryFromEntity(
                        g_CurrentEntity,
                        equipped_item->unk13 + ((hand + 1) << 12) +
                            (((equipped_item->unk14 & 0x7F) + (hand << 7))
                             << 0x10),
                        equipped_id) == NULL) {
                    return 0;
                }
            } else {
                // TODO: FACTORY()
                if (CreateEntFactoryFromEntity(
                        g_CurrentEntity,
                        equipped_item->unk13 + ((hand + 1) << 14) +
                            (((equipped_item->unk14 & 0x7F) + (hand << 7))
                             << 0x10),
                        equipped_id) == NULL) {
                    return 0;
                }
            }
        }
    } else if (
        // TODO: FACTORY()
        CreateEntFactoryFromEntity(
            g_CurrentEntity, (hand + 42) + (hand << 23), 0) == NULL) {
        return 0;
    }
    func_800FDD44(hand);
    if (var_s7 != 0) {
        func_800FDD44((hand + 1) & 1);
    }
    HasEnoughMp(g_EquipDefs[equipped_id].mpUsage, 1);
    // 95 is Estoc
    if ((equipped_id == 95) && (g_Player.unk72 != 0)) {
        return 0;
    }

    var_s2 = equipped_item->playerAnim;
    switch (equipped_item->unk11) {
    case 29: // Muramasa
        GetEquipProperties(hand, &sp10, equipped_id);
        if (sp10.attack < 11) {
        case 13: // Red Rust
            if (!(rand() & 7)) {
            block_70:
                switch (PLAYER.step) {
                case 0:
                case 1:
                    SetPlayerAnim(0xB5);
                    PLAYER.step = 0;
                    break;
                case 2:
                    SetPlayerAnim(0xB6);
                    PLAYER.step = 2;
                    break;
                case 3:
                case 4:
                    SetPlayerAnim(0xB7);
                    PLAYER.step = 4;
                    break;
                }
                g_Player.unk46 = 0x8012;
                g_Player.unk54 = 0xFF;
                PLAYER.step_s = 0x51;
                PlaySfx(SFX_VO_ALU_PAIN_A);
                return 1;
            }
        }
        func_8010EA54(8);
        goto block_98;
    case 12: // Shotel
        // When shotel is thrown away, attempting to attack will make a punch
        if ((CheckChainLimit(equipped_item->specialMove, hand) < 0) ||
            (CheckChainLimit(equipped_item->specialMove, (hand + 1) & 1) < 0)) {
            equipped_item = &g_EquipDefs[0];
            // TODO: FACTORY()
            CreateEntFactoryFromEntity(
                g_CurrentEntity, (hand + 42) + (hand << 23), 0);
            var_s2 = g_EquipDefs[0].playerAnim;
        }
        func_8010EA54(8);
        goto block_98;
    case 19: // Unknown, not a direct equippable item
        D_80139824 = 0x28;
        PLAYER.step = 0;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 20: // Unknown, not a direct equippable item
        PLAYER.step = 0;
        D_80139824 = 0x28;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 21: // Unknown, not a direct equippable item
        PLAYER.step = 0;
        D_80139824 = 0x28;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 22: // Unknown, not a direct equippable item (but there are 4 of them)
        PLAYER.step = 0;
        D_80139824 = 0x28;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 28: // Unknown, not a direct equippable item
        PLAYER.step = 0;
        D_80139824 = 0xA;
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
        animVariant = atLedge;
        CheckMoveDirection();
        SetSpeedX(FIX(4));
        PLAYER.velocityX >>= 1;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        if (g_Player.pl_vram_flag & 1) {
            PLAYER.step = 0;
            g_CurrentEntity->velocityY = 0;
        } else {
            PLAYER.step = 4;
        }
        SetPlayerAnim(var_s2 + animVariant);
        g_Player.unk46 = equipped_item->unk11 - 0x7FFF;
        g_Player.unk54 = equipped_item->lockDuration;
        PLAYER.step_s = equipped_item->unk11 + 0x40;
        g_Player.timers[9] = 4;
        break;
    case 24: // Unknown, not a direct equippable item (but there are 2 of them)
        if (2 < PLAYER.step && PLAYER.step < 5) {
            PLAYER.step = 4;
        } else {
            PLAYER.step = 0;
        }
        D_80139824 = 0x80;
        g_CurrentEntity->velocityY = 0;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
    case 26: // Unknown, not a direct equippable item (but there are 2 of them)
        PLAYER.step = 0;
        D_80139824 = 0x28;
        g_CurrentEntity->velocityY = 0;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_VO_ALU_ATTACK_B);
        goto block_98;
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
        func_8010EA54(8);
    case 8:
    case 9: // Combat Knife
    case 10:
    case 25:
    block_98:
        switch (PLAYER.step) {
        case 0:
        case 1:
            g_CurrentEntity->velocityX >>= 1;
            PLAYER.step = 0;
            animVariant = atLedge;
            break;
        case 2:
            animVariant = 2;
            if (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) {
                animVariant = 3;
            }
            if (g_Player.unk72 == 0 && PLAYER.step_s == 2) {
                PLAYER.step = 0;
                animVariant = atLedge;
            }
            break;
        case 3:
        case 4:
            animVariant = 4;
            if (PLAYER.velocityY > 0) {
                animVariant = 5;
                if (equipped_item->unk11 == 0) {
                    if (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT) &&
                        g_Player.padPressed & PAD_DOWN) {
                        animVariant = 6;
                    }
                } else if (g_Player.padPressed & PAD_DOWN) {
                    animVariant = 6;
                }
            }
            break;
        }
        SetPlayerAnim(var_s2 + animVariant);
        g_Player.unk46 = equipped_item->unk11 - 0x7FFF;
        g_Player.unk54 = equipped_item->lockDuration;
        PLAYER.step_s = equipped_item->unk11 + 0x40;
        g_Player.timers[9] = 4;
        break;
    case 5: // Lots of unknown things
        step = PLAYER.step;
        if (step >= 0) {
            if (step < 3) {
                g_CurrentEntity->velocityX >>= 1;
                SetPlayerAnim(var_s2 + atLedge);
                g_Player.unk46 = equipped_item->unk11 - 0x7FFF;
                g_Player.unk54 = equipped_item->lockDuration;
                PLAYER.step = 0;
                PLAYER.step_s = equipped_item->unk11 + 0x40;
                g_CurrentEntity->velocityX = 0;
            }
        }
        func_8010EA54(8);
        break;
    case 128: // Shields
        var_s2 = equipped_item->playerAnim;
        switch (PLAYER.step) {
        case 0:
            PLAYER.step_s = 2;
            SetPlayerAnim(var_s2 + atLedge);
            break;
        case 2:
            PLAYER.step_s = 0;
            SetPlayerAnim(var_s2 + 2);
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
                SetPlayerAnim(var_s2 + atLedge);
                break;
            case 2:
                animVariant = 2;
                if (g_Player.unk72 == 0 && PLAYER.step_s == 2) {
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
    case 131: // Medicines
        if (PLAYER.step_s < 0x40) {
            var_s2 = equipped_item->playerAnim;
            if (PLAYER.step == 0) {
                SetPlayerAnim(var_s2 + atLedge);
            }
        }
        break;
    case 135: // Unknown
        PlaySfx(SFX_VO_ALU_ATTACK_C);
        g_Player.timers[9] = 4;
        func_8010ED54(equipped_item->playerAnim);
        break;
    }
    return 1;
}

void func_8010FAF4(void) {
    DestroyEntity(&g_Entities[E_WEAPON]);
    g_Player.unk46 = 0;
}

void PerformHellfire(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellHellfire);
    func_8010E168(1, 0x10);
    func_8010E3E0();
}

void PerformDarkMetamorphosis(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellDarkMetamorphosis);
    func_8010E3E0();
    SetPlayerAnim(0xBA);
    PlaySfx(SFX_VO_ALU_DARK_META);
    PlaySfx(SFX_UI_MP_FULL);
    g_Player.timers[11] =
        GetStatusAilmentTimer(STATUS_AILMENT_DARK_METAMORPHOSIS, 0x400);
    func_801092E8(1);
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(40, 0x11), 0);
    func_80118C28(0xB);
}

void PerformSoulSteal(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellSoulSteal);
    func_8010E3E0();
    SetPlayerAnim(0xDA);
    PlaySfx(SFX_VO_ALU_SOUL_STEAL);
    func_80118C28(0xC);
    g_Player.timers[12] = 4;
}

void PerformSummonSpirit(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellSummonSpirit);
    func_8010E3E0();
    CreateEntFactoryFromEntity(g_CurrentEntity, 117, 0);
    SetPlayerAnim(0xF0);
    PlaySfx(SFX_VO_ALU_ATTACK_D);
    g_Player.timers[12] = 4;
}

void PerformTetraSpirit(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellTetraSpirit);
    func_8010E3E0();
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(117, 1), 0);
    SetPlayerAnim(0xF1);
    PlaySfx(SFX_VO_ALU_ATTACK_D);
    g_Player.timers[12] = 4;
}

void PerformSwordBrothers(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellSwordBrothers);
    func_8010E3E0();
    SetPlayerAnim(0xF1);
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(40, 0x17), 0);
    g_Player.timers[12] = 4;
}

void func_8010FD88(void) {
    PLAYER.step = Player_Stand;
    PLAYER.step_s = 3;
    SetSpeedX(0xFFFC8000);
    g_CurrentEntity->velocityY = 0;
    SetPlayerAnim(0xDB);
    CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
    g_Player.unk46 = 0;
    PlaySfx(SFX_SCRAPE_C);
}
