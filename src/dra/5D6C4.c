#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

s32 func_800FD6C4(s32 equipTypeFilter) {
    s32 var_a0;
    s32 var_v1;
    s32 var_a1;

    switch (equipTypeFilter) {
    case 0:
        return 0xA9;
    case 1:
        var_a1 = 0;
        break;
    case 2:
        var_a1 = 1;
        break;
    case 3:
        var_a1 = 2;
        break;
    case 4:
        var_a1 = 3;
    default:
        break;
    }
    var_a0 = 0;
    var_v1 = 0;
    do {
        if (D_800A7734[var_v1].unk00 == var_a1) {
            var_a0 += 1;
        }
        var_v1 += 1;
    } while (var_v1 < 90);

    return var_a0;
}

const u32 rodataPadding_jpt_800FD6E0 = 0;

u8* func_800FD744(s32 equipTypeFilter) {
    u8* begin = g_Status.equipHandOrder;
    if (equipTypeFilter != 0) {
        begin += sizeof(g_Status.equipHandOrder);
    }
    return begin;
}

u8* func_800FD760(s32 equipTypeFilter) {
    s8* begin = &g_Status.equipHandCount;
    if (equipTypeFilter != 0) {
        begin += sizeof(g_Status.equipHandCount);
    }
    return begin;
}

const char* GetEquipmentName(s32 equipTypeFilter, s32 equipId) {
    if (!equipTypeFilter) {
        return D_800A4B04[equipId].name;
    } else {
        return D_800A7718[equipId].name;
    }
}

u32 CheckEquipmentItemCount(u32 itemId, u32 equipType) {
    if (equipType < 5) {
        switch (equipType) {
        case 0:
            return (g_Status.equipment[0] == itemId) +
                   (g_Status.equipment[1] == itemId);
        case 1:
            return g_Status.equipment[2] == itemId;
        case 2:
            return g_Status.equipment[3] == itemId;
        case 3:
            return g_Status.equipment[4] == itemId;
        case 4:
            return (g_Status.equipment[5] == itemId) +
                   (g_Status.equipment[6] == itemId);
        }
    }
    // seems to require missing return
}

// fix missing padding at end of jump table.
// this probably indicates the end of a C file
const u32 rodataPadding_800DCBD8 = 0;

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", AddToInventory);
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

void func_800FD9D4(SpellDef* spell, s32 id) {
    *spell = g_SpellDefs[id];
    spell->attack += (g_player_total_int * 2 + (rand() % 12)) / 10;
    if (CheckEquipmentItemCount(0x15, 2) != 0) {
        spell->attack = spell->attack + spell->attack / 2;
    }
}

// TODO get rid of the asm volatile
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", func_800FDB18);
#else
s16 func_800FDB18(s32 arg0, s32 arg1) {
    s16 temp_v0;
    s32 ret;
    s32 var_v1;

    switch (arg0) {
    case 0:
        temp_v0 = arg1 - (g_player_total_con * 0x10);
        // asm volatile("move $16, $2");
        if (temp_v0 < 0x100) {
            ret = 0x100;
        }
        break;
    case 1:
        temp_v0 = arg1 - (g_player_total_con * 4);
        // asm volatile("move $16, $2");
        if (temp_v0 < 0x40) {
            ret = 0x40;
        }
        break;
    case 2:
        ret = arg1;
        var_v1 = (((rand() % 12) + g_player_total_con) - 9) / 10;
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        if (var_v1 > 4) {
            var_v1 = 4;
        }
        ret = ret - var_v1;
        break;
    case 3:
        ret = arg1 + (g_player_total_int * 4);
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

    if (g_Status.mp < (s32)temp) {
        return false;
    } else {
        g_Status.mp -= temp;
        return true;
    }
}

// DECOMP_ME_WIP func_800FDCE0 https://decomp.me/scratch/5ufgy
INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", func_800FDCE0);

bool func_800FDD44(s32 equipId) {
    s32 equippedItem;
    bool isConsumable;

    equippedItem = g_Status.equipment[equipId];
    isConsumable = D_800A4B04[equippedItem].isConsumable;
    if (!CheckEquipmentItemCount(0x54, 4)) {
        if (isConsumable) {
            if (g_Status.equipHandCount[equippedItem] == 0) {
                g_Status.equipment[equipId] = 0;
                func_800F53A4();
                return true;
            }
            g_Status.equipHandCount[equippedItem]--;
        }
    }
    return false;
}

void func_800FDE00(void) {
    D_80137960 = 0;
    D_80137964 = 0;
    D_80137968 = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", func_800FDE20);

INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", func_800FE044);

bool func_800FE3A8(s32 arg0) {
    /*
     * also matches without the temp like this:
     * return (g_Status.relics[arg0] & ~0xfd) != 0;
     * if that array contains a bitmask, it would make
     * more sense that way.
     */
    s32 temp = 2;

    return (g_Status.relics[arg0] & temp) != 0;
}

s32 func_800FE3C4(SubweaponDef* subwpn, s32 subweaponId, bool useHearts) {
    u32 accessoryCount;

    if (subweaponId == 0) {
        *subwpn = g_Subweapons[D_80097BFC];
        accessoryCount = CheckEquipmentItemCount(0x4D, 4);
        if (accessoryCount == 1) {
            subwpn->unk2 = subwpn->unk2 / 2;
        }
        if (accessoryCount == 2) {
            subwpn->unk2 = subwpn->unk2 / 3;
        }
        if (subwpn->unk2 <= 0) {
            subwpn->unk2 = 1;
        }
        if (g_Status.hearts >= subwpn->unk2) {
            if (useHearts) {
                g_Status.hearts -= subwpn->unk2;
            }
            return D_80097BFC;
        } else {
            return 0;
        }
    } else {
        *subwpn = g_Subweapons[subweaponId];
        if (CheckEquipmentItemCount(0x14, 2) != 0) {
            subwpn->attack += 10;
        }
        if (subweaponId == 4 || subweaponId == 12) {
            accessoryCount = CheckEquipmentItemCount(0x3D, 4);
            if (accessoryCount == 1) {
                subwpn->attack *= 2;
            }
            if (accessoryCount == 2) {
                subwpn->attack *= 3;
            }
        }
        subwpn->attack += ((g_player_total_int * 2) + (rand() % 12)) / 10;
        return subweaponId;
    }
}

void GetEquipProperties(s32 handId, Equipment* res, s32 equipId) {
    s32 criticalModRate;
    Equipment* var_a2;
    s32 criticalRate;
    u8 damageScale;

    var_a2 = &D_800A4B04[(s16)equipId]; // FAKE
    criticalModRate = 5;

    __builtin_memcpy(res, &D_800A4B04[equipId], sizeof(Equipment));
    criticalRate = res->criticalRate;
    criticalRate = criticalRate - criticalModRate +
                   SquareRoot0((g_Status.statsTotal[3] * 2) + (rand() & 0xF));
    if (criticalRate > 255) {
        criticalRate = 255;
    }
    if (criticalRate < 0) {
        criticalRate = 0;
    }
    if (g_StageId == STAGE_ST0) {
        criticalRate = 0;
    }

    res->criticalRate = criticalRate;
    func_800F4994();
    damageScale = D_800A4B04[equipId].damageScale;
    if (damageScale != 6 && damageScale != 10) {
        res->attack = func_800F4D38(equipId, g_Status.equipment[1 - handId]);
        do {
        } while (0); // FAKE
        if (D_80072F2C & 0x4000) {
            res->attack >>= 1;
        }
    }
}

bool HasEnoughMp(s32 mpCount, bool subtractMp) {
    if (g_Status.mp >= mpCount) {
        if (subtractMp != 0) {
            g_Status.mp -= mpCount;
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
    if (g_Status.hearts < g_Status.heartsMax) {
        g_Status.hearts += value;
        if (g_Status.heartsMax < g_Status.hearts) {
            g_Status.hearts = g_Status.heartsMax;
        }
        func_8011AAFC(g_EntityArray, 99, 0);
        PlaySfx(NA_SE_PL_COLLECT_HEART);
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", func_800FE97C);

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

INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", func_800FEEA4);

s32 func_800FF064(s32 arg0) {
    s32 playerMP;

    playerMP = g_Status.mp - 4;

    if (playerMP > 0) {
        if (arg0 != 0) {
            g_Status.mp = playerMP;
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

u16 func_800FF128(Entity* enemyEntity, Entity* arg1);
INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", func_800FF128);

s32 func_800FF460(s32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return arg0 + ((u32)(arg0 * g_player_total_lck[0]) >> 7);
}

// Determine what type of item to drop
s32 func_800FF494(EnemyDef* arg0) {
    // 0x4B is the item ID for Ring of Arcana
    // Ring of Arcana is an item that increases enemy item drop rates when
    // equipped
    s32 ringOfArcanaCount = CheckEquipmentItemCount(0x4B, 4);
    s32 rnd = rand() & 0xFF;

    rnd -= ((rand() & 0x1F) + g_player_total_lck[0]) / 20;

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
        rnd -= ((rand() & 0x1F) + g_player_total_lck[0]) / 20;

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
        if (g_Status.equipment[4] == D_800A2FBC[i]) {
            break;
        }

        if (D_800A2FBC[i] == -1) {
            break;
        }
        i += 2;
    }

    var_a0_2 = D_800A2FC0[i];
    if (g_Status.equipment[4] == 0x32 && g_Settings.isCloakLingingReversed) {
        var_a0_2++;
    }
    func_800EA5E4(var_a0_2);
    if (g_Status.equipment[4] == 0x38) {
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
    g_Status.equipment[arg1 + 2] = rnd;
}

// DECOMP_ME_WIP func_800FF7B8 https://decomp.me/scratch/Ti1u1
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", func_800FF7B8);
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
        if (g_Status.equipment[0] == 0x7B) {
            g_Status.equipment[0] = 0;
        } else if (g_Status.equipment[1] == 0x7B) {
            g_Status.equipment[1] = 0;
        } else if (D_80097A05 != 0) {
            D_80097A05--;
        }
        if (g_Status.equipment[0] == 0x10) {
            g_Status.equipment[0] = 0;
        } else if (g_Status.equipment[1] == 0x10) {
            g_Status.equipment[1] = 0;
        } else if (D_8009799A != 0) {
            D_8009799A--;
        }
        if (g_Status.equipment[2] == 0x2D) {
            g_Status.equipment[2] = 0x1A;
        } else if (D_80097A60 != 0) {
            D_80097A60--;
        }
        if (g_Status.equipment[3] == 0xF) {
            g_Status.equipment[3] = 0;
        } else if (D_80097A42 != 0) {
            D_80097A42--;
        }
        if (g_Status.equipment[4] == 0x38) {
            g_Status.equipment[4] = 0x30;
            func_800FF60C();
        } else if (D_80097A6B != 0) {
            D_80097A6B--;
        }
        if (g_Status.equipment[5] == 0x4E) {
            g_Status.equipment[5] = 0x39;
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
            g_Status.equipHandCount[var_s0_3] = 0;
            g_Status.equipHandOrder[var_s0_3] = var_s0_3;
        }

        var_s0_5 = 0;
        do {
            D_80097A33[var_s0_5] = 0;
            D_80097B36[var_s0_5] = var_s0_5;
            var_s0_5++;
        } while (var_s0_5 < 90);

        g_Status.equipHandCount[0] = 1;
        D_80097A4D = 1;
        D_80097A33[0] = 1;
        D_80097A63 = 1;
        D_80097A6C = 1;
        var_s0_6 = 7;
        var_a0 = g_Inventory - 1;
        for (; var_s0_6 >= 0; var_s0_6--) {
            *var_a0-- = 0;
        }

        thingPtr = &g_Status.unk0;
        g_Status.unk0 = 0;
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
            var_a1 = D_8003CAA4; // end of g_Settings.timeAttackRecords
            g_Status.relics[10] |= 2;
            g_Status.relics[11] |= 2;
            g_Status.relics[15] |= 2;
            g_Status.relics[16] |= 2;
            for (; var_s0_8 >= 0; var_s0_8--) {
                *var_a1-- = 0;
            }

            g_Settings.D_8003CB00 = 0;
            g_Settings.D_8003CB04 = 0;
            D_80097BFC.subWeapon = 0;
            if (g_StageId != STAGE_ST0 && g_StageId != STAGE_NO3) {
                D_80097BFC.subWeapon = (rand() % 9) + 1;
            }

            g_Status.hp = 50;
            g_Status.hpMax = 50;
            g_Status.hearts = 30;
            g_Status.heartsMax = 99;
            g_Status.mpMax = 20;
            g_Status.mp = 20;
            g_Status.statStr = 10;
            g_Status.statCon = 10;
            g_Status.statInt = 10;
            g_Status.statLck = 10;
            g_Status.equipment[2] = 0x1A;
            g_Status.equipment[4] = 0x30;
            g_Status.equipment[5] = 0x39;
            D_80097C18 = 0x39;
            g_playerGold = 0;
            g_Status.equipment[0] = 0;
            g_Status.equipment[1] = 0;
            g_Status.equipment[3] = 0;
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
                g_Status.statStr = 6;
                g_Status.statCon = 6;
                g_Status.statInt = 6;
                g_Status.statLck = 6;
                g_playerGold = 0;
                var_v0_2 = thingPtr;
                var_v0_2 -= 0x21B;
                for (var_s0_10 = 0x1D; var_s0_10 >= 0; var_s0_10--) {
                    *var_v1_3-- = 0;
                }

                if (D_801397FC != 0) { // maria saves Ricther flag
                    func_800FD874(159, 0);
                    var_s0_11 = 3;
                } else if (g_Status.hp == g_Status.hpMax) {
                    g_Status.statStr++;
                    g_Status.statCon++;
                    g_Status.statInt++;
                    g_Status.statLck++;
                    var_s0_11 = 0;
                } else {
                    var_s0_11 = 2;
                    if (g_Status.hp >=
                        (((s32)(g_Status.hpMax +
                                (((u32)g_Status.hpMax) >> 0x1F))) >>
                         1)) {
                        g_Status.statStr++;
                        var_s0_11 = 1;
                    } else {
                        g_Status.statCon++;
                    }
                }
                if (g_Status.hearts == 0 && var_s0_11 < 3) {
                    func_800FD874(0x8E, 0);
                }
                g_Status.hpMax = 70;
                if (var_s0_11 == 0) {
                    g_Status.hpMax = 75;
                }
                g_Status.hearts = 0xA;
                g_Status.heartsMax = 0x32;
                g_Status.mpMax = 0x14;
                if (D_80139008 >= 0x29) {
                    func_800FD874(0x47, 0);
                    g_Status.statInt++;
                } else {
                    g_Status.statStr++;
                }

                if (D_80097BFC.subWeapon == 4) {
                    if (var_s0_11 < 3) {
                        g_Status.heartsMax += 5;
                        g_Status.mpMax += 5;
                    }
                } else if (D_80097BFC.subWeapon == 3) {
                    if (var_s0_11 < 2) {
                        g_Status.heartsMax += 5;
                        player_stat_int++;
                    }
                } else {
                    switch (var_s0_11) {
                    case 0:
                        player_stat_lck += 5;
                        player_stat_con++;
                        player_stat_int++;

                    case 1:
                        g_Status.hpMax += 5;

                    case 2:
                        g_Status.statStr++;
                        break;
                    }
                }

                temp_v0 = func_800FD4C0(0, 0);
                if (temp_v0 < 101) {
                    g_Status.hpMax += 5;
                    g_Status.mpMax += 5;
                    g_Status.heartsMax += 5;
                    g_Status.statStr += 5;
                    g_Status.statCon += 5;
                    g_Status.statInt += 5;
                    g_Status.statLck += 5;
                } else if (temp_v0 < 201) {
                    g_Status.statLck += 2;
                } else if (temp_v0 < 301) {
                    g_Status.statLck += 1;
                } else if (temp_v0 >= 1000) {
                    g_Status.statCon += 1;
                }

                var_s0_12 = 0;
                var_a1_2 = D_800A300C;
                g_Status.equipment[0] = 0x7B;
                g_Status.equipment[1] = 0x10;
                g_Status.equipment[2] = 0x2D;
                g_Status.equipment[3] = 0xF;
                g_Status.equipment[4] = 0x38;
                g_Status.equipment[5] = 0x4E;
                D_80097BFC.subWeapon = 0;
                D_80097C18 = 0x39;
                g_Status.hp = g_Status.hpMax;
                g_Status.mp = g_Status.mpMax;

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
                    g_Status.heartsMax = 5;
                    g_Status.statStr = 1;
                    g_Status.statCon = 0;
                    g_Status.statInt = 0;
                    g_Status.hpMax = 25;
                    g_Status.mpMax = 1;
                    g_Status.hp = 25;
                    g_Status.hearts = 5;
                    g_Status.mp = 1;
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
                var_v0_4 = &D_8003CAA4; // end of g_Settings.timeAttackRecords
                do {
                    *var_v0_4 = 0;
                    var_s0_9--;
                    var_v0_4 -= 4;
                } while (var_s0_9 >= 0);
                g_Status.statStr = 6;
                g_Status.statCon = 6;
                g_Status.statInt = 6;
                player_stat_lck = 6;
                g_Status.hpMax = 70;
                g_Status.hp = 70;
                g_Status.hearts = 10;
                g_playerGold = 500000;
                g_Status.heartsMax = 50;
                g_Status.mp = 20;
                g_Status.mpMax = 20;
                g_Status.hearts = 1234;
                g_Status.heartsMax = 2000;
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
                } while ((s32)var_v1_5 < ((s32)((&g_Status.statStr) - 0x21A)));

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

                g_Status.equipment[0] = 0x13;
                g_Status.equipment[1] = 5;
                g_Status.equipment[2] = 0x1A;
                g_Status.equipment[3] = 2;
                g_Status.equipment[4] = 0x30;
                g_Status.equipment[5] = 0x39;
                D_80097C18 = 0x39;
                g_GameTimer.hours = 0;
                g_GameTimer.minutes = 0;
                g_GameTimer.seconds = 0;
                g_GameTimer.frames = 0;
                D_80097BFC.subWeapon = 0;
                g_Status.relics[10] = 3;
                (&g_Status.relics[10])[1] = 3;
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
INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", DrawHudRichter);
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
    poly = &g_PrimBuf[D_80137970];

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
    poly = &g_PrimBuf[D_80137974];
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

INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", func_80100B50);

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
    D_8013796C = g_Status.hp;

    if ((g_StageId == STAGE_ST0) ||
        (g_CurrentPlayableCharacter != PLAYER_ALUCARD)) {
        DrawHudRichter();
        return;
    }

    D_80137970 = func_800EDD9C(4, 14);
    poly = &g_PrimBuf[D_80137970];

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

INCLUDE_ASM("asm/us/dra/nonmatchings/5D6C4", func_80101A80);

void func_801024DC(void) {
    POLY_GT4* temp_v1;
    POLY_GT4* var_v1;
    s32 temp_v0_2;
    s32 var_a0;
    u32 temp_v0;
    temp_v0 = AllocPrimitives(1, 4);
    D_8013799C = temp_v0;
    var_v1 = &g_PrimBuf[temp_v0];
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
    temp_v0_2 = AllocPrimitives(4, 1);
    temp_v1 = &g_PrimBuf[temp_v0_2];
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

    poly = &g_PrimBuf[D_8013799C];

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
    POLY_GT4* poly = &g_PrimBuf[D_801379A0];

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
