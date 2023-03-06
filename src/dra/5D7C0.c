#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

u32 CheckEquipmentItemCount(u32 itemId, u32 equipType) {
    if (equipType < 5) {
        switch (equipType) {
        case 0:
            return (g_playerEquip[0] == itemId) + (g_playerEquip[1] == itemId);
        case 1:
            return g_playerEquip[2] == itemId;
        case 2:
            return g_playerEquip[3] == itemId;
        case 3:
            return g_playerEquip[4] == itemId;
        case 4:
            return (g_playerEquip[5] == itemId) + (g_playerEquip[6] == itemId);
        }
    }
    // seems to require missing return
}

// fix missing padding at end of jump table.
// this probably indicates the end of a C file
const u32 rodataPadding_800DCBD8 = 0;

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", AddToInventory);
#else
void AddToInventory(u16 itemId, s32 itemCategory) {
    u8 temp_a1;
    s32 new_var2;
    u8* phi_a0;
    u8* phi_a0_2;
    long i;
    s32 phi_a1;
    s32 phi_a1_2;
    u8* cursorY = func_800FD744(itemCategory);
    u8* itemArray = func_800FD760(itemCategory);
    if (itemArray[itemId] < 99) {
        temp_a1 = itemArray[itemId];
        itemArray[itemId]++;
        if (itemArray[itemId] == 1) {
            itemArray[itemId] = temp_a1;
            phi_a1_2 = itemCategory;
            if (phi_a1_2 != 0) {
                i = D_800A7734[itemId].unk00;
            }
            phi_a0 = cursorY;
            for (phi_a1_2 = 0; true; phi_a1_2++) {
                if (phi_a0[phi_a1_2] == itemId) {
                    break;
                }
            }

            phi_a0_2++;
            phi_a0_2 = cursorY;
            for (phi_a1 = 0; true; phi_a1++) {
                if (((!itemArray[*phi_a0_2]) && phi_a1_2) &&
                    (i == D_800A7734[*phi_a0_2].unk00)) {
                    new_var2 = phi_a1;
                    cursorY[new_var2] = itemId;
                    break;
                }
            }

            itemArray[itemId]++;
            if (new_var2 < phi_a1_2) {
                cursorY[phi_a1_2] = cursorY[new_var2];
                cursorY[new_var2] = itemId;
            }
        }
    }
}
#endif

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FD9D4);

// TODO get rid of the asm volatile
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FDB18);
#else
s16 func_800FDB18(s32 arg0, s32 arg1) {
    s16 temp_v0;
    s32 ret;
    s32 var_v1;

    switch (arg0) {
    case 0:
        temp_v0 = arg1 - (D_80097BDC * 0x10);
        // asm volatile("move $16, $2");
        if (temp_v0 < 0x100) {
            ret = 0x100;
        }
        break;
    case 1:
        temp_v0 = arg1 - (D_80097BDC * 4);
        // asm volatile("move $16, $2");
        if (temp_v0 < 0x40) {
            ret = 0x40;
        }
        break;
    case 2:
        ret = arg1;
        var_v1 = (((rand() % 12) + D_80097BDC) - 9) / 10;
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        if (var_v1 > 4) {
            var_v1 = 4;
        }
        ret = ret - var_v1;
        break;
    case 3:
        ret = arg1 + (D_80097BE0 * 4);
        break;
    case 4:
    case 5:
        ret = arg1;
        if (CheckEquipmentItemCount(80, 4)) {
            ret += ((s32)(((s16)ret) + (((u32)(ret << 0x10)) >> 0x1F))) >> 1;
        }
        break;
    }

    return ret;
}
#endif

bool func_800FDC94(s32 arg0) {
    u8 temp = D_800A841C[arg0 * 0x1C];

    if (D_80097B9C.mp < (s32)temp) {
        return false;
    } else {
        D_80097B9C.mp -= temp;
        return true;
    }
}

// https://decomp.me/scratch/5ufgy
INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FDCE0);

bool func_800FDD44(s32 equipHeadIndex) {
    s32 equippedItem;
    u8 temp_s1;
    u8 temp_v0;

    equippedItem = g_playerEquip[equipHeadIndex];
    temp_s1 = D_800A4B1D[g_playerEquip[equipHeadIndex]].unk0;
    if (!CheckEquipmentItemCount(0x54, 4)) {
        if (temp_s1 != 0) {
            temp_v0 = D_8009798A[equippedItem];
            if (temp_v0 == 0) {
                g_playerEquip[equipHeadIndex] = 0;
                func_800F53A4();
                return true;
            }
            D_8009798A[equippedItem]--;
        }
    }
    return false;
}

void func_800FDE00(void) {
    D_80137960 = 0;
    D_80137964 = 0;
    D_80137968 = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FDE20);

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FE044);

bool func_800FE3A8(s32 arg0) {
    /*
     * also matches without the temp like this:
     * return (D_80097964[arg0] & ~0xfd) != 0;
     * if that array contains a bitmask, it would make
     * more sense that way.
     */
    s32 temp = 2;

    return (D_80097964[arg0] & temp) != 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FE3C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FE728);

bool HasEnoughMp(s32 mpCount, bool subtractMp) {
    if (D_80097B9C.mp >= mpCount) {
        if (subtractMp != 0) {
            D_80097B9C.mp -= mpCount;
        }
        return false;
    }
    return true;
}

void func_800FE8F0(void) {
    if (D_8013B5E8 == 0) {
        D_8013B5E8 = 0x40;
    }
}

void AddHearts(s32 value) {
    if (D_80097B9C.hearts < D_80097B9C.heartsMax) {
        D_80097B9C.hearts += value;
        if (D_80097B9C.heartsMax < D_80097B9C.hearts) {
            D_80097B9C.hearts = D_80097B9C.heartsMax;
        }
        func_8011AAFC(g_EntityArray, 99, 0);
        PlaySfx(NA_SE_PL_COLLECT_HEART);
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FE97C);

// !FAKE: explicitly casting two pointers to s32
// before comparing them, that's weird
void func_800FEE6C(void) {
    s32* var_v1 = D_80139828;

    do {
        if (*var_v1 != 0) {
            *var_v1 -= 1;
        }
        var_v1++;
    } while ((s32)var_v1 < (s32)&D_80139828[0x10]);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FEEA4);

s32 func_800FF064(s32 arg0) {
    s32 playerMP;

    playerMP = D_80097B9C.mp - 4;

    if (playerMP > 0) {
        if (arg0 != 0) {
            D_80097B9C.mp = playerMP;
        }
        return 0;
    }
    return -1;
}

void func_800FF0A0(s32 context) { D_80139828[context] = 0; }

void func_800FF0B8(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        func_800FF0A0(i);
    }
}

void func_800FF0F4(s32 arg0) { D_80139828[arg0] = 0x1000; }

s32 func_800FF110(s32 arg0) { return D_80139828[arg0]; }

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FF128);

s32 func_800FF460(s32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return arg0 + ((u32)(arg0 * D_80097BE4[0]) >> 7);
}

// Determine what type of item to drop
s32 func_800FF494(Unkstruct_800FF494* arg0) {
    // 0x4B is the item ID for Ring of Arcana
    // Ring of Arcana is an item that increases enemy item drop rates when equipped
    s32 ringOfArcanaCount = CheckEquipmentItemCount(0x4B, 4);
    s32 rnd = rand() & 0xFF;

    rnd -= ((rand() & 0x1F) + D_80097BE4[0]) / 20;

    if (ringOfArcanaCount != 0) {
        rnd -= arg0->rareItemDropRate * ringOfArcanaCount;
    }

    if (rnd < arg0->rareItemDropRate) {
        return 0x40; // drop the enemy's rare item
    } else {
        // drop a common item, typically hearts or money
        rnd -= arg0->rareItemDropRate;
        if (ringOfArcanaCount != 0) {
            rnd -= arg0->uncommonItemDropRate * ringOfArcanaCount;
        }
        rnd -= ((rand() & 0x1F) + D_80097BE4[0]) / 20;

        if (rnd >= arg0->uncommonItemDropRate) {
            rnd = rand() % 28;
            if (arg0->rareItemDropRate == 0) {
                rnd++;
            }
            if (arg0->uncommonItemDropRate == 0) {
                rnd++;
            }
            return rnd + ringOfArcanaCount;
        } else {
            return 0x20; // drop the enemy's uncommon item
        }
    }
}

void func_800FF60C(void) {
    s32 var_a0_2;
    s32 i;

    func_800EA538(6);

    i = 0;
    while (1) {
        if (g_playerEquip[4] == D_800A2FBC[i]) {
            break;
        }

        if (D_800A2FBC[i] == -1) {
            break;
        }
        i += 2;
    }

    var_a0_2 = D_800A2FC0[i];
    if ((g_playerEquip[4] == 0x32) && (g_SettingsCloakMode != 0)) {
        var_a0_2++;
    }
    func_800EA5E4(var_a0_2);
    if (g_playerEquip[4] == 0x38) {
        func_800EA5E4(0x415);
    }
}

void func_800FF60C();

void func_800FF6C4(void) {
    if ((g_StageId != 0x1F) && (g_CurrentPlayableCharacter == PLAYER_ALUCARD)) {
        func_800FF60C();
    }
}

void func_800FF708(s32 arg0, s32 arg1) {
    s32 rnd;

    do {
    loop_1:
        rnd = rand() % 90;
        if (rnd == 0x19) {
            goto loop_1;
        }
    } while (D_800A7734[rnd].unk00 != arg0);
    g_playerEquip[arg1 + 2] = rnd;
}

// https://decomp.me/scratch/Ti1u1
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FF7B8);
#else
extern s8 D_8006C373[];
typedef struct {
    // part of a larger struct, maybe part of PlayerStats?
    s32 subWeapon;
} Unkstruct_80097BFC;
extern Unkstruct_80097BFC D_80097BFC; // g_SubWeapon
extern s32 D_800A872C[];

void func_800FF7B8(s32 arg0) {
    s32 temp_v0;
    s32 var_a0_2;
    s32 var_s0;
    s32 var_s0_10;
    s32 var_s0_11;
    s32 var_s0_12;
    s32 var_s0_13;
    s32 var_s0_14;
    s32 var_s0_15;
    s32 i;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_6;
    s32 var_s0_7;
    s32 var_s0_8;
    s32 var_s0_9;
    s32 var_v0_3;
    s32 var_v1_2;
    s32* var_a1;
    s32* var_v0_4;
    s32* var_v0_10;
    s32* var_v1;
    s32* var_v1_4;
    s8* var_v1_5;
    s32 var_s0_5;
    s8* var_a0;
    s8* var_v0;
    s8* var_v0_2;
    s8* var_v0_5;
    s8* var_v0_6;
    s8* var_v1_3;
    u8 var_s0_4;
    u8* var_a1_2;
    u8* var_a1_3;
    u8 temp_var_1;
    u8 temp_var_2;
    u8 temp_var_3;
    s32* thingPtr;
    int new_var;

    if (D_8003C730 != 0) {
        func_800F53A4();
        func_800FF60C();
        return;
    }
    if (arg0 == 1) { // First block fully matching
        if (g_playerEquip[0] == 0x7B) {
            g_playerEquip[0] = 0;
        } else if (g_playerEquip[1] == 0x7B) {
            g_playerEquip[1] = 0;
        } else if (D_80097A05 != 0) {
            D_80097A05--;
        }
        if (g_playerEquip[0] == 0x10) {
            g_playerEquip[0] = 0;
        } else if (g_playerEquip[1] == 0x10) {
            g_playerEquip[1] = 0;
        } else if (D_8009799A != 0) {
            D_8009799A--;
        }
        if (g_playerEquip[2] == 0x2D) {
            g_playerEquip[2] = 0x1A;
        } else if (D_80097A60 != 0) {
            D_80097A60--;
        }
        if (g_playerEquip[3] == 0xF) {
            g_playerEquip[3] = 0;
        } else if (D_80097A42 != 0) {
            D_80097A42--;
        }
        if (g_playerEquip[4] == 0x38) {
            g_playerEquip[4] = 0x30;
            func_800FF60C();
        } else if (D_80097A6B != 0) {
            D_80097A6B--;
        }
        if (g_playerEquip[5] == 0x4E) {
            g_playerEquip[5] = 0x39;
        } else if (D_80097C18 == 0x4E) {
            D_80097C18 = 0x39;
        } else if (D_80097A81 != 0) {
            D_80097A81--;
        }
    } else { // 220
        var_s0 = 0x7FF;
        var_v0 = &D_8006BB74[var_s0];
        for (; var_s0 >= 0; var_s0--) {
            *var_v0-- = 0;
        }

        var_s0_2 = 3;
        var_v0_10 = &D_80097BF8;
        var_v1 = var_v0_10 - 9;
        g_roomCount = 0;
        *var_v0_10 = 0;
        for (; var_s0_2 >= 0; var_s0_2--) {
            *var_v1-- = 0;
        }

        var_s0_3 = 0;
        g_playerExp = 0;
        g_playerLevel = 1;
        g_killCount = 0;
        do {
            D_80097C44[var_s0_3].level = 1;
            D_80097C44[var_s0_3].exp = 0;
            D_80097C44[var_s0_3].killCount = 0;
            var_s0_3++;
        } while (var_s0_3 < FAMILIAR_COUNT);

        for (var_s0_3 = 0; var_s0_3 < 0xA9; var_s0_3++) {
            D_8009798A[var_s0_3] = 0;
            D_80097A8D[var_s0_3] = var_s0_3;
        }

        var_s0_5 = 0;
        do {
            D_80097A33[var_s0_5] = 0;
            D_80097B36[var_s0_5] = var_s0_5;
            var_s0_5++;
        } while (var_s0_5 < 90);

        D_8009798A[0] = 1;
        D_80097A4D = 1;
        D_80097A33[0] = 1;
        D_80097A63 = 1;
        D_80097A6C = 1;
        var_s0_6 = 7;
        var_a0 = D_8009798A - 1;
        for (; var_s0_6 >= 0; var_s0_6--) {
            *var_a0-- = 0;
        }

        thingPtr = &D_80097B9C.unk0;
        D_80097B9C.unk0 = 0;
        if (g_StageId == STAGE_ST0 ||
            g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
            temp_var_3 = 1;
            var_s0_7 = 0x1D;
            var_v0_2 = thingPtr;
            var_v0_2 -= 0x21B;
            for (; var_s0_7 >= 0; var_s0_7--) {
                *var_v0_2-- = temp_var_3;
            }

            var_s0_8 = 0x1F;
            var_a1 = D_8003CAA4;
            D_80097964[10] |= 2;
            D_80097964[11] |= 2;
            D_80097964[15] |= 2;
            D_80097964[16] |= 2;
            for (; var_s0_8 >= 0; var_s0_8--) {
                *var_a1-- = 0;
            }

            *D_8003CB00 = 0;
            D_8003CB04 = 0;
            D_80097BFC.subWeapon = 0;
            if (g_StageId != STAGE_ST0 && g_StageId != STAGE_NO3) {
                D_80097BFC.subWeapon = (rand() % 9) + 1;
            }

            D_80097B9C.hp = 50;
            D_80097B9C.hpMax = 50;
            D_80097B9C.hearts = 30;
            D_80097B9C.heartsMax = 99;
            D_80097B9C.mpMax = 20;
            D_80097B9C.mp = 20;
            D_80097B9C.statStr = 10;
            D_80097B9C.statCon = 10;
            D_80097B9C.statInt = 10;
            D_80097B9C.statLck = 10;
            g_playerEquip[2] = 0x1A;
            g_playerEquip[4] = 0x30;
            g_playerEquip[5] = 0x39;
            D_80097C18 = 0x39;
            g_playerGold = 0;
            g_playerEquip[0] = 0;
            g_playerEquip[1] = 0;
            g_playerEquip[3] = 0;
            if (g_StageId == STAGE_NO3) {
                func_800FD4C0(26, 1);
                func_800FD4C0(9, 1);
                func_800FD4C0(4, 1);
                func_800FD4C0(14, 1);
                func_800FD4C0(12, 1);
            }
            g_GameTimer.hours = 0;
            D_80097C34 = 0;
            D_80097C38->unk0 = 0;
            D_80097C3C = 0;
        } else {
            if (g_StageId == STAGE_NO3) {
                D_80097B9C.statStr = 6;
                D_80097B9C.statCon = 6;
                D_80097B9C.statInt = 6;
                D_80097B9C.statLck = 6;
                g_playerGold = 0;
                var_v0_2 = thingPtr;
                var_v0_2 -= 0x21B;
                for (var_s0_10 = 0x1D; var_s0_10 >= 0; var_s0_10--) {
                    *var_v1_3-- = 0;
                }

                if (D_801397FC != 0) { // maria saves Ricther flag
                    func_800FD874(159, 0);
                    var_s0_11 = 3;
                } else if (D_80097B9C.hp == D_80097B9C.hpMax) {
                    D_80097B9C.statStr++;
                    D_80097B9C.statCon++;
                    D_80097B9C.statInt++;
                    D_80097B9C.statLck++;
                    var_s0_11 = 0;
                } else {
                    var_s0_11 = 2;
                    if (D_80097B9C.hp >=
                        (((s32)(D_80097B9C.hpMax +
                                (((u32)D_80097B9C.hpMax) >> 0x1F))) >>
                         1)) {
                        D_80097B9C.statStr++;
                        var_s0_11 = 1;
                    } else {
                        D_80097B9C.statCon++;
                    }
                }
                if (g_playerHeart == 0 && var_s0_11 < 3) {
                    func_800FD874(0x8E, 0);
                }
                D_80097B9C.hpMax = 70;
                if (var_s0_11 == 0) {
                    D_80097B9C.hpMax = 75;
                }
                g_playerHeart = 0xA;
                g_playerHeartMax = 0x32;
                g_playerMpMax = 0x14;
                if (D_80139008 >= 0x29) {
                    func_800FD874(0x47, 0);
                    D_80097B9C.statInt++;
                } else {
                    D_80097B9C.statStr++;
                }

                if (D_80097BFC.subWeapon == 4) {
                    if (var_s0_11 < 3) {
                        g_playerHeartMax += 5;
                        g_playerMpMax += 5;
                    }
                } else if (D_80097BFC.subWeapon == 3) {
                    if (var_s0_11 < 2) {
                        g_playerHeartMax += 5;
                        player_stat_int++;
                    }
                } else {
                    switch (var_s0_11) {
                    case 0:
                        player_stat_lck += 5;
                        player_stat_con++;
                        player_stat_int++;

                    case 1:
                        D_80097B9C.hpMax += 5;

                    case 2:
                        D_80097B9C.statStr++;
                        break;
                    }
                }

                temp_v0 = func_800FD4C0(0, 0);
                if (temp_v0 < 101) {
                    D_80097B9C.hpMax += 5;
                    g_playerMpMax += 5;
                    g_playerHeartMax += 5;
                    D_80097B9C.statStr += 5;
                    D_80097B9C.statCon += 5;
                    D_80097B9C.statInt += 5;
                    D_80097B9C.statLck += 5;
                } else if (temp_v0 < 201) {
                    D_80097B9C.statLck += 2;
                } else if (temp_v0 < 301) {
                    D_80097B9C.statLck += 1;
                } else if (temp_v0 >= 1000) {
                    D_80097B9C.statCon += 1;
                }

                var_s0_12 = 0;
                var_a1_2 = D_800A300C;
                g_playerEquip[0] = 0x7B;
                g_playerEquip[1] = 0x10;
                g_playerEquip[2] = 0x2D;
                g_playerEquip[3] = 0xF;
                g_playerEquip[4] = 0x38;
                g_playerEquip[5] = 0x4E;
                D_80097BFC.subWeapon = 0;
                D_80097C18 = 0x39;
                D_80097B9C.hp = D_80097B9C.hpMax;
                g_playerMP = g_playerMpMax;

                // checks for the cheat code "x-x!v''q"
            loop_103:
                if (g_SaveName[var_s0_12] == *var_a1_2++) {
                    var_s0_12++;
                    if (var_s0_12 < 8) {
                        goto loop_103;
                    }
                }

                if (var_s0_12 == 8) {
                    player_stat_lck = 99;
                    g_playerHeartMax = 5;
                    D_80097B9C.statStr = 1;
                    D_80097B9C.statCon = 0;
                    D_80097B9C.statInt = 0;
                    D_80097B9C.hpMax = 25;
                    g_playerMpMax = 1;
                    D_80097B9C.hp = 25;
                    g_playerHeart = 5;
                    g_playerMP = 1;
                    D_80097C18 = 70;
                }

                if (g_IsTimeAttackUnlocked != false) {
                    // checks for "axearmor"
                    var_a1_3 = D_800A3010;
                    var_s0_13 = 0;
                loop_109:
                    if (g_SaveName[var_s0_13] == *var_a1_3++) {
                        var_s0_13++;
                        if (var_s0_13 < 8) {
                            goto loop_109;
                        }
                    }
                    if (var_s0_13 == 8) {
                        func_800FD874(0x19, 2);
                    }
                }
            } else {
                var_s0_9 = 0x1F;
                var_v0_4 = &D_8003CAA4;
                do {
                    *var_v0_4 = 0;
                    var_s0_9--;
                    var_v0_4 -= 4;
                } while (var_s0_9 >= 0);
                D_80097B9C.statStr = 6;
                D_80097B9C.statCon = 6;
                D_80097B9C.statInt = 6;
                player_stat_lck = 6;
                D_80097B9C.hpMax = 70;
                D_80097B9C.hp = 70;
                g_playerHeart = 10;
                g_playerGold = 500000;
                g_playerHeartMax = 50;
                g_playerMP = 20;
                g_playerMpMax = 20;
                g_playerHeart = 1234;
                g_playerHeartMax = 2000;
                g_playerExp = 11000;
                g_playerLevel = 20;
                var_s0_9 = 0x10;
                if (g_StageId & 0x20) {
                    g_playerExp = 110000;
                }

                new_var = 3;
                var_v1_5 = thingPtr - 0x238; // 0x80097964
                var_a0_2 = 0;
                do {
                    var_a0_2 += var_s0_9;
                    if (D_800A872C[var_a0_2] != 0) {
                        *var_v1_5 = 1;
                    } else {
                        *var_v1_5 = new_var;
                    }
                    var_v1_5++;
                } while ((s32)var_v1_5 <
                         ((s32)((&D_80097B9C.statStr) - 0x21A)));

                temp_var_2 = 0x32;
                var_s0_14 = 0xA8;
                var_v0_5 = D_80097A32;
                for (; var_s0_14 >= 0; var_s0_14--) {
                    *var_v0_5-- = temp_var_2;
                }

                temp_var_1 = 1;
                var_s0_15 = 0x59;
                var_v0_6 = D_80097A8C;
                for (; var_s0_15 >= 0; var_s0_15--) {
                    *var_v0_6-- = temp_var_1;
                }

                g_playerEquip[0] = 0x13;
                g_playerEquip[1] = 5;
                g_playerEquip[2] = 0x1A;
                g_playerEquip[3] = 2;
                g_playerEquip[4] = 0x30;
                g_playerEquip[5] = 0x39;
                D_80097C18 = 0x39;
                g_GameTimer.hours = 0;
                g_GameTimer.minutes = 0;
                g_GameTimer.seconds = 0;
                g_GameTimer.frames = 0;
                D_80097BFC.subWeapon = 0;
                D_8009796E = 3;
                (&D_8009796E)[1] = 3;
                D_80097973 = 3;
                *D_80097964 = 3;
                D_80097965 = 3;
                D_80097968 = 3;
                D_80097969 = 3;
                D_8009796A = 3;
                D_8009796B = 3;
                D_80097970 = 3;
                D_80097971 = 3;
                func_800FD874(0x6F, 0);
                func_800FD874(0x70, 0);
                func_800FD874(0x71, 0);
                func_800FD874(0x62, 0);
                func_800FD874(0x80, 0);
                func_800FD874(0x64, 0);
                func_800FD874(6, 0);
                func_800FD874(7, 0);
                func_800FD874(0x12, 0);
                func_800FD874(0x17, 0);
                func_800FD874(0x55, 0);
                func_800FD874(0x58, 0);
                func_800FD874(1, 2);
                func_800FD874(3, 2);
                func_800FD874(4, 2);
                func_800FD874(5, 2);
                func_800FD874(6, 2);
                func_800FD874(7, 2);
                func_800FD874(0xA, 2);
                func_800FD874(0xD, 2);
                func_800FD874(0x1F, 1);
                func_800FD874(0x21, 1);
                func_800FD874(0x23, 1);
                func_800FD874(0x31, 3);
                func_800FD874(0x33, 3);
                func_800FD874(0x35, 3);
                func_800FD874(0x32, 3);
                func_800FD874(0x52, 4);
                func_800FD874(0x4F, 4);

                for (i = 0; i < 0x50; i++) {
                    func_800FD874(0x9F, 0);
                }

                for (i = 0; i < 10; i++) {
                    func_800FD874(0x19, 0);
                    func_800FD874(0x45, 0);
                    func_800FD874(0x43, 0);
                    func_800FD874(0x90, 0);
                    func_800FD874(0x51, 0);
                    func_800FD874(0x52, 0);
                    func_800FD874(0x49, 0);
                }
            }
        }
    }
    func_800F53A4();
}
#endif

// matches with ASPSX
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", DrawHudRichter);
#else
void DrawHudRichter(void) {
    POLY_GT4* poly;

    D_80137978 = 400;
    D_8013797C = 400;
    D_801397FC = 0;
    D_80139008 = 0;
    D_80137994 = 0;
    D_8003C744 = 0;
    D_80137980 = 48;
    D_80137984 = 0;
    D_80137990.unk0 = 0;
    D_8013798C = 40000 / D_80137978;
    D_80137988 = 40000 / D_8013797C;
    D_80137970 = func_800EDD9C(4, 9);
    poly = &D_80086FEC[D_80137970];

    func_80107360(poly, 2, 22, 32, 96, 0, 0);
    poly->tpage = 0x1B;
    poly->clut = 0x101;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, D_80137980 + 216, 22, 32, 96, 32, 0);
    poly->tpage = 0x1BU;
    poly->clut = 0x100;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0x2000U;
    poly = poly->tag;

    func_80107360(poly, 4, 112, 9, 3, 64, 89);
    poly->tpage = 0x1B;
    poly->clut = 0x105;
    poly->pad2 = 0x1F0;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, D_80137980 + 228, 112, 9, 3, 64, 89);
    poly->tpage = 0x1BU;
    poly->clut = 0x103U;
    poly->pad2 = 0x1F0U;
    poly->pad3 = 0x2000U;
    poly->p1 = 0;
    poly->p2 = 6;
    poly = poly->tag;

    func_80107360(poly, D_80137980 + 236, 112, 9, 3, 64, 89);
    poly->tpage = 0x1B;
    poly->clut = 0x103;
    poly->pad2 = 0x1F0;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, 14, 27, 8, 8, 0, 96);
    poly->tpage = 0x1BU;
    poly->clut = 0x103U;
    poly->pad2 = 0x1F0U;
    poly->pad3 = 0x2000U;
    poly = poly->tag;

    func_80107360(poly, 22, 27, 8, 8, 0, 96);
    poly->tpage = 0x1B;
    poly->clut = 0x103;
    poly->pad2 = 0x1F0;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, 18, 38, 8, 8, 0, 0);
    poly->tpage = 0x1BU;
    poly->clut = 0x102;
    poly->pad2 = 0x1F0U;
    poly->pad3 = 0x2000U;
    poly = poly->tag;

    func_80107360(poly, 33, 20, 64, 24, 64, 40);
    poly->tpage = 0x1B;
    poly->clut = 0x103;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0x2000;

    D_80137974 = func_800EDD9C(4, 16);
    poly = &D_80086FEC[D_80137974];
    if (poly != 0) {
        s32 phi_s1 = 0x20;
        s32 phi_s0 = 0xD8;
        do {
            func_80107360(poly, phi_s0, 22, 2, 96, phi_s1, 0);
            func_801072DC(poly);
            poly->tpage = 0x1B;
            poly->clut = 0x100;
            poly->pad2 = 0x1EE;
            poly->pad3 = 8;
            poly->p1 = (rand() & 0x3F) + 1;
            poly->p2 = 0;
            poly = poly->tag;
            phi_s1 += 2;
            phi_s0 += 2;
        } while (poly != 0);
    }
}
#endif

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_80100B50);

extern Unkstruct_80137990 D_80137990;

bool func_8010183C(s32 arg0) {
    if (arg0 == 0) {
        if (D_80137990.unk0 == 0) {
            D_80137990.unk0 = 1;
            return true;
        }
        return false;
    } else if (arg0 == 1) {
        if (D_80137990.unk0 == 0x15) {
            D_80137990.unk0 = 0x33;
            return true;
        }
        return false;
    }
    return true;
}
void DrawHudRichter(void);

void func_8010189C(void) {
    POLY_GT4* poly;
    s32 i;
    u16* new_var;

    D_8013B5E8 = 0;
    D_80137998 = 0;
    D_8013796C = D_80097B9C.hp;

    if ((g_StageId == STAGE_ST0) ||
        (g_CurrentPlayableCharacter != PLAYER_ALUCARD)) {
        DrawHudRichter();
        return;
    }

    D_80137970 = func_800EDD9C(4, 14);
    poly = &D_80086FEC[D_80137970];

    if (poly != NULL) {
        for (i = 0; poly != NULL; i++) {
            func_80107360(poly, D_800A2EE8[i], D_800A2EF8[i], D_800A2F28[i],
                          D_800A2F38[i], D_800A2F08[i], D_800A2F18[i]);
            poly->tpage = 0x1F;
            new_var = &D_800A2F48[i];
            poly->clut = *new_var;
            poly->pad2 = 0x1F0;
            poly->pad3 = D_800A2F64[i];

            if (i == 5) {
                SetPolyRect(poly, D_800A2EED, D_800A2EFD, D_800A2F3D,
                            D_800A2F2D);
                poly->y0 = poly->y2;
                poly->x1 = poly->x0;
                poly->x2 = poly->x3;
                poly->y3 = poly->y1;
            }

            if (i == 1) {
                poly->p1 = 0;
                poly->p2 = rand() + 8;
                poly->p3 = (7 & rand()) + 1;
            }

            poly = (POLY_GT4*)poly->tag;
        }
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_80101A80);

void func_801024DC(void) {
    POLY_GT4* temp_v1;
    POLY_GT4* var_v1;
    s32 temp_v0_2;
    s32 var_a0;
    u32 temp_v0;
    temp_v0 = AllocPolygons(1, 4);
    D_8013799C = temp_v0;
    var_v1 = &D_80086FEC[temp_v0];
    var_a0 = 0;
    if (var_v1 != 0) {
        do {
            var_v1->x0 = (var_a0 & 1) << 7;
            var_v1->u0 = 0x80;
            var_v1->v0 = 0xF0;
            var_v1->pad2 = 0x1FD;
            var_v1->pad3 = 8;
            var_v1 = (POLY_GT4*)var_v1->tag;
            var_a0 += 1;
        } while (var_v1 != 0);
    }
    D_801379A8 = 0;
    D_801379A4 = 0;
    temp_v0_2 = AllocPolygons(4, 1);
    temp_v1 = &D_80086FEC[temp_v0_2];
    D_801379A0 = temp_v0_2;
    temp_v1->u1 = 0xFF;
    temp_v1->v2 = 0xFF;
    temp_v1->u3 = 0xFF;
    temp_v1->v3 = 0xFF;
    temp_v1->tpage = 0x1D;
    temp_v1->clut = 0x1C0;
    temp_v1->pad2 = 0x1FE;
    temp_v1->u0 = 0;
    temp_v1->v0 = 0;
    var_v1 = temp_v1;
    var_v1->v1 = 0;
    var_v1->u2 = 0;
    var_v1->pad3 = 8;
}

extern Unkstruct_80086FFA D_80086FFA[];

u16 func_801025F4(void) { return D_80086FFA[D_8013799C].unk0; }

void func_80102628(s32 arg0) {
    POLY_GT4* poly;
    s32 temp;
    s32 i = 0;

    poly = &D_80086FEC[D_8013799C];

    if (poly != NULL) {
        temp = arg0 / 2;
        while (poly != NULL) {
            poly->y0 = 0;
            poly->u0 = (u8)temp;
            poly->v0 = 0xF0;
            poly->b0 = 0;
            poly->g0 = 0;
            poly->r0 = 0;
            poly->pad2 = 0x1FD;
            poly->pad3 = 8;
            poly->x0 = temp * (i & 1);
            poly = (POLY_GT4*)poly->tag;
            i++;
        }
    }
}

void func_801026BC(s32 arg0) {
    POLY_GT4* poly = &D_80086FEC[D_801379A0];

    if (arg0 == 0) {
        poly->pad3 = 8;
        return;
    } else if (!(g_StageId & 0x20)) {
        SetPolyRect(poly, 0, 1, 255, 255);
    } else {
        poly->x2 = 255;
        poly->x0 = 255;
        poly->y1 = 240;
        poly->y0 = 240;
        poly->x3 = 0;
        poly->x1 = 0;
        poly->y3 = -15;
        poly->y2 = -15;
    }

    func_80107250(poly, arg0 * 2);

    if (arg0 == 0x40) {
        poly->pad3 = 0;
    } else {
        poly->pad3 = 0x35;
    }
}

void func_801027A4(void) { func_801026BC(0); }
