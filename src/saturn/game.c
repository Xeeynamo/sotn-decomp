#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"

// __game_start
INCLUDE_ASM("asm/saturn/game/data", d6066000, d_06066000);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066040, func_06066040);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60661BC, func_060661BC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066330, func_06066330);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066400, func_06066400);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60664E0, func_060664E0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60665BC, func_060665BC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60666A4, func_060666A4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066854, func_06066854);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60668D4, func_060668D4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066B30, func_06066B30);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066B74, func_06066B74);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066CE0, func_06066CE0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066FE0, func_06066FE0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067090, func_06067090);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60674B8, func_060674B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067958, func_06067958);
INCLUDE_ASM("asm/saturn/game/data", d606797C, d_0606797C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067A04, func_06067A04);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606B6F8, func_0606B6F8);

// _READ_SUB_OUT_MODE
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606B760, func_0606B760);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606BB4C, func_0606BB4C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606BEE4, func_0606BEE4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C064, func_0606C064);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C088, func_0606C088);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C160, func_0606C160);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C3E4, func_0606C3E4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C504, func_0606C504);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C594, func_0606C594);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C774, func_0606C774);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606CA10, func_0606CA10);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D058, func_0606D058);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D2D0, func_0606D2D0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D358, func_0606D358);

// _PSX_POSITION_GET
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D3FC, func_0606D3FC);

// _PSX_TO_STAGE_NO_GET
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D554, func_0606D554);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D5FC, func_0606D5FC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D6DC, func_0606D6DC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D798, func_0606D798);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D804, func_0606D804);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D880, func_0606D880);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606DAE8, func_0606DAE8);

// _make_att
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606DC8C, func_0606DC8C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606DCF0, func_0606DCF0);

// _make_all
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606DF2C, func_0606DF2C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606DFA0, func_0606DFA0);

// _servant_work_clear
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606E020, func_0606E020);

// _init_work_sub_out_p
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606E074, func_0606E074);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606E0D0, func_0606E0D0);

// _MODE_GAME
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606EE28, func_0606EE28);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606EEF8, func_0606EEF8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F01C, func_0606F01C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F14C, func_0606F14C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F1C8, func_0606F1C8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F21C, func_0606F21C);

// PSX: func_800FD5BC
// SAT: func_0606F2C0
bool func_800FD5BC(Unkstruct_800FD5BC* arg0) {
    s32 temp;

    if (arg0->unk4 != 5) {
        if (((u32)arg0->unk4) >= 0x10U) {
            temp = g_Status.hpMax;
            if (g_Status.hpMax < 0) {
                temp += 7;
            }
            arg0->unk8 = temp >> 3;
        } else if ((arg0->unk8 * 0x14) <= g_Status.hpMax) { // reversed on PSX
            arg0->unk4 = 3;
        } else {
            arg0->unk4 = 2;
        }
    }
    if (g_Status.hp <= arg0->unk8) {
        g_Status.hp = 0;
        return true;
    } else {
        g_Status.hp -= arg0->unk8;
        return false;
    }
}

// SAT: func_0606F328
s32 func_800FD664(s32 arg0) {
    return g_StageId & STAGE_INVERTEDCASTLE_FLAG ? arg0 << 1 : arg0;
}

// SAT: func_0606F348
u8 GetEquipItemCategory(s32 equipId) {
    return g_EquipDefs[g_Status.equipment[equipId]].itemCategory;
}

// SAT: func_0606F378
// a little different from PSX version
s32 func_800FD6C4(s32 equipTypeFilter) {
    s32 itemCount;
    s32 i;
    s32 equipType;
    Unkstruct_800A7734* temp;

    switch (equipTypeFilter) {
    case 0:
        return 0xB0; // different
    case 1:
        equipType = 0;
        break;
    case 2:
        equipType = 1;
        break;
    case 3:
        equipType = 2;
        break;
    case 4:
        equipType = 3;
    default:
        break;
    }
    itemCount = 0;
    i = 0;
    temp = D_800A7734;
    do {
        // different offset accessed
        if (D_800A7734[i].unk03 == equipType) {
            itemCount++;
        }
        i += 1;
    } while (i < 92); // changed from 90

    return itemCount;
}

// SAT: func_0606F3D8
u8* GetEquipOrder(s32 equipTypeFilter) {
    if (equipTypeFilter == 0) {
        return g_Status.equipHandOrder;
    }
    return g_Status.equipBodyOrder;
}

// SAT: func_0606F3F8
u8* GetEquipCount(s32 equipTypeFilter) {
    if (equipTypeFilter == 0) {
        return g_Status.equipHandCount;
    }
    return g_Status.equipBodyCount;
}

// SAT: func_0606F418
const char* GetEquipmentName(s32 equipTypeFilter, s32 equipId) {
    if (!equipTypeFilter) {
        return g_EquipDefs[equipId].name;
    } else {
        return g_AccessoryDefs[equipId].name;
    }
}

// CheckEquipmentItemCount
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F448, func_0606F448);

INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F4C4, func_0606F4C4);

// SAT: func_0606F59C
void func_800FD9D4(SpellDef* spell, s32 id) {
    *spell = g_SpellDefs[id];
    spell->attack += (g_Status.statsTotal[2] * 2 + (rand() % 12)) / 10;
    if (CheckEquipmentItemCount(0x15, 2) != 0) {
        spell->attack = spell->attack + spell->attack / 2;
    }
}

// _etc_hosei
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F65C, func_0606F65C);

// SAT: func_0606F760
bool CastSpell(SpellIds spellId) {
    u8 mpUsage = g_SpellDefs[spellId].mpUsage;

    if (g_Status.mp < mpUsage) {
        return false;
    } else {
        g_Status.mp -= mpUsage;
        return true;
    }
}

// _waza_work_set
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F798, func_0606F798);

// _reduce_weapon
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F800, func_0606F800);

// SAT: func_0606F884
// no return value on PSX?
s32 func_800FDE00(void) {
    D_80137960 = 0;
    D_80137964 = 0;
    D_80137968 = 0;
    return 0;
}

// _check_experience
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606F8A8, func_0606F8A8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606FA30, func_0606FA30);

// SAT: func_0606FC60
// sh2 compiler is more literal?
bool IsRelicActive(s32 arg0) {
    if ((g_Status.relics[arg0] & 2) != 0) {
        return 1;
    }

    return 0;
}

// SAT: func_0606FC80
s32 func_800FE3C4(SubweaponDef* subwpn, s32 subweaponId, bool useHearts) {
    u32 accessoryCount;

    if (subweaponId == 0) {
        *subwpn = g_SubwpnDefs[g_Status.subWeapon];
        accessoryCount = CheckEquipmentItemCount(0x4f, 4); // 4f instead of 4d
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
            return g_Status.subWeapon;
        } else {
            return 0;
        }
    } else {
        *subwpn = g_SubwpnDefs[subweaponId];
        if (CheckEquipmentItemCount(0x14, 2) != 0) {
            subwpn->attack += 10;
        }
        if (subweaponId == 4 || subweaponId == 12) {
            accessoryCount =
                CheckEquipmentItemCount(0x3e, 4); // 3e instead of 3d
            if (accessoryCount == 1) {
                subwpn->attack *= 2;
            }
            if (accessoryCount == 2) {
                subwpn->attack *= 3;
            }
        }
        subwpn->attack += ((g_Status.statsTotal[2] * 2) + (rand() % 12)) / 10;
        return subweaponId;
    }
}

// SAT: func_0606FE60
void GetEquipProperties(s32 handId, Equipment* res, s32 equipId) {
    s32 criticalModRate;
    s32 criticalRate;
    u8 itemCategory;

    criticalModRate = 5;

    *res = g_EquipDefs[equipId]; // hack not needed
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
    itemCategory = g_EquipDefs[equipId].itemCategory;
    if (itemCategory != ITEM_FOOD && itemCategory != ITEM_MEDICINE) {
        res->attack = func_800F4D38(equipId, g_Status.equipment[1 - handId]);
        if (g_Player.unk0C & 0x4000) {
            res->attack >>= 1;
        }
    }
}

// SAT: func_0606FFA0
bool HasEnoughMp(s32 mpCount, bool subtractMp) {
    if (!(mpCount > g_Status.mp)) { // condition swapped
        if (subtractMp != 0) {
            g_Status.mp -= mpCount;
        }
        return false;
    }
    return true;
}

// SAT: func_0606FFC8
void func_800FE8F0(void) {
    if (D_8013B5E8 == 0) {
        D_8013B5E8 = 0x40;
    }
}

// SAT: func_0606FFE4
void AddHearts(s32 value) {
    Entity* temp;
    if (g_Status.hearts < g_Status.heartsMax) {
        g_Status.hearts += value;
        if (g_Status.hearts > g_Status.heartsMax) { // swapped
            g_Status.hearts = g_Status.heartsMax;
        }
        temp = g_Entities;
        g_api.CreateEntFactoryFromEntity(temp, 99, 0); // g_api is new

        PlaySfx(SFX_HEART_PICKUP);
    }
}

const u16 pad_06070038 = 0xCCCC;
const u16 pad_0607003A = 0xCCCD;

// _get_damage_sub
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607003C, func_0607003C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60703DC, func_060703DC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6070410, func_06070410);

// SAT: func_06070540
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

// SAT: func_06070568
void func_800FF0A0(s32 context) { D_80139828[context] = 0; }

// probably PSX func_800FF0B8 but strange to match
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6070580, func_06070580);

// SAT: func_060705A0
REDACTED

// SAT: func_060705B8
REDACTED

// SAT: func_060705CC
u16 func_800FF128(Entity* enemyEntity, Entity* attackerEntity) {
    s32 stats[4];
    EnemyDef sp20;
    EnemyDef* enemy;
    u16 temp_v1;
    u16 elementMask;
    s32 higherStatIdx;
    s32 i;
    u16 element;
    u16 damage;
    u16 result;
    u16 stuff;

    enemy = &sp20;
    sp20 = g_EnemyDefs[enemyEntity->enemyId];
    if (CheckEquipmentItemCount(0x2D, 1) != 0) {
        enemy->defense /= 2;
    }

    element = attackerEntity->attackElement;
    damage = attackerEntity->attack;
    if (element == 0) {
        element = 0x20;
    }
    if (element & 0xFF80) {
        elementMask = 0xFF80;
    } else {
        elementMask = 0x7F;
    }

    result = 0;
    temp_v1 = element & elementMask;
    if (temp_v1 == (temp_v1 & (elementMask & enemy->immunes))) {
        result = DAMAGE_FLAG_IMMUNE;
    } else if (temp_v1 == (temp_v1 & (elementMask & enemy->absorbs))) {
        result = damage + DAMAGE_FLAG_ABSORB;
    } else {
        if (temp_v1 == (temp_v1 & (elementMask & enemy->strengths))) {
            damage /= 2;
        }
        if (element & enemy->weaknesses) {
            damage *= 2;
        }
        if (attackerEntity->entityRoomIndex > (rand() & 0xFF)) {
            for (i = 0; i < 4; i++) {
                stats[i] = (rand() & 0x3F) + g_Status.statsBase[i];
            }

            higherStatIdx = 0;
            for (i = 1; i < 4; i++) {
                if (stats[i] > stats[higherStatIdx]) {
                    higherStatIdx = i;
                }
            }

            switch (higherStatIdx) {
            case 0:
                damage *= 2;
                break;
            case 1:
                if (enemy->defense > damage) {
                    damage += enemy->defense / 2;
                } else {
                    damage += damage / 2;
                }
                break;
            case 2:
                damage += SquareRoot0(g_RoomCount);
                break;
            case 3:
                damage += (rand() % g_Status.statsTotal[3]) + 1;
                break;
            }
            result = DAMAGE_FLAG_CRITICAL;
        } else {
            result = DAMAGE_FLAG_NORMAL;
        }

        if (damage > enemy->defense) {
            damage = damage - enemy->defense;
        } else {
            damage = 1;
        }

        if (damage < 0 || damage >= 10000) {
            damage = 9999;
        }

        result += damage;
    }

    return result;
}

// SAT: func_060707F0
s32 func_800FF460(s32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return arg0 + ((u32)(arg0 * g_Status.statsTotal[3]) >> 7);
}

// SAT: func_06070820
// Determine what type of item to drop
s32 func_800FF494(EnemyDef* arg0) {
    // 0x4B is the item ID for Ring of Arcana
    // Ring of Arcana is an item that increases enemy item drop rates when
    // equipped
    s32 ringOfArcanaCount = CheckEquipmentItemCount(0x4D, 4); // 4d not 4b
    s32 rnd = rand() & 0xFF;

    rnd -= (g_Status.statsTotal[3] + (rand() & 0x1F)) / 20; // swapped

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
        rnd -= (g_Status.statsTotal[3] + (rand() & 0x1F)) / 20; // swapped

        if (rnd >= arg0->uncommonItemDropRate) {
            rnd = rand() % 28;
            if (arg0->rareItemDropRate == 0) {
                rnd++;
            }
            if (arg0->uncommonItemDropRate == 0) {
                rnd++;
            }
            return ringOfArcanaCount + rnd; // swapped
        } else {
            return 0x20; // drop the enemy's uncommon item
        }
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6070938, func_06070938);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6070988, func_06070988);
INCLUDE_ASM("asm/saturn/game/data", d6070A60, d_06070A60);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6071C3C, func_06071C3C);

// _INIT_ROOM
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60720F4, func_060720F4);

// _SET_DEFAULT_SCL_PRIORITY
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60726A8, func_060726A8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60727DC, func_060727DC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607284C, func_0607284C);
INCLUDE_ASM("asm/saturn/game/data", d60728B4, d_060728B4);

// _INIT_GAME_OVER
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6072BCC, func_06072BCC);

// _GAMEOVER_FADEIN
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6072C04, func_06072C04);

// _SUB_DISP
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6072C94, func_06072C94);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60731C0, func_060731C0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073280, func_06073280);

// _INIT_SUB_GAMEN
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60732E4, func_060732E4);

// _PSX_cursor_up_down
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60733A4, func_060733A4);

// SAT: func_0607356C
bool func_800FB1EC(s32 arg0) {
    if (D_801375CC == EQUIP_HAND) {
        if (arg0 == 0) {
            return true;
        }
    } else if ((arg0 == 0x1A) || (arg0 == 0) || (arg0 == 0x30) ||
               (arg0 == 0x3A)) { // 3A instead of 39
        return true;
    }

    return false;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f60735A4, func_060735A4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607360C, func_0607360C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607369C, func_0607369C);

// _PSX_id_init
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60736D4, func_060736D4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607371C, func_0607371C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073740, func_06073740);

// _goto_equip
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073770, func_06073770);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60737A0, func_060737A0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073E58, func_06073E58);

// _PSX_sort_item
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073EEC, func_06073EEC);

// _PSX_equip_id_init
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6073FEC, func_06073FEC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074048, func_06074048);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074068, func_06074068);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60740F8, func_060740F8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074278, func_06074278);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60743B8, func_060743B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074470, func_06074470);

// _EVENT_SCL_TRANS
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60744F8, func_060744F8);

// _SS_MOJI_SET
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60745A0, func_060745A0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074698, func_06074698);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074700, func_06074700);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074724, func_06074724);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074964, func_06074964);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60749F8, func_060749F8);

extern s32 DAT_06085c70;
s32* func_06074A98(void) { return &DAT_06085c70; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074AA8, func_06074AA8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074BF4, func_06074BF4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074C28, func_06074C28);

// _status_work_init
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6074CC8, func_06074CC8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6075838, func_06075838);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6075D24, func_06075D24);

// _status_pause
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60766DC, func_060766DC);

struct Unk_060860D8 {
    u8 pad[0x23];
    s32 unk24;
};

extern struct Unk_060860D8 DAT_060860D8;
s32 func_06076718(void) { return DAT_060860D8.unk24 == 0x15; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607672C, func_0607672C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6076A04, func_06076A04);

// _set_XYWH
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077148, func_06077148);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607718C, func_0607718C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60771B0, func_060771B0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60771D4, func_060771D4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077260, func_06077260);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077354, func_06077354);

// _set_life_num
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077764, func_06077764);

// _status_disp_init
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077B20, func_06077B20);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6077D88, func_06077D88);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078120, func_06078120);

extern s32 DAT_00292000;

s32* func_060784A8(void) { return &DAT_00292000; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f60784B8, func_060784B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078550, func_06078550);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078604, func_06078604);

// _disp_num_string
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078684, func_06078684);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607872C, func_0607872C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078748, func_06078748);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60787C8, func_060787C8);

// _SubDispSpecial
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078920, func_06078920);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60789C4, func_060789C4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078D58, func_06078D58);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078E80, func_06078E80);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6078F58, func_06078F58);

// _SubDispSortKind
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079008, func_06079008);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60790B4, func_060790B4);

// _SubDispFace
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079208, func_06079208);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60792B8, func_060792B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079424, func_06079424);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079580, func_06079580);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079670, func_06079670);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607973C, func_0607973C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60797FC, func_060797FC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079958, func_06079958);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079A2C, func_06079A2C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079AF0, func_06079AF0);

// _normal_move
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079B74, func_06079B74);

void MoveEntity(Entity* entity) {
    entity->posX.val += entity->velocityX;
    entity->posY.val += entity->velocityY;
}

void func_06079BB4(s32* param_1) {
REDACTED
REDACTED
    if (temp != 0) {
        temp[0x14 / 4] = param_1[1];
        temp[0x18 / 4] = param_1[2];
    }
}

void func_06079BCC(s32* param_1) {
REDACTED
    if (temp != 0) {
        param_1[1] = temp[0x14 / 4];
        param_1[2] = temp[0x18 / 4];
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079BE4, func_06079BE4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079C04, func_06079C04);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079DEC, func_06079DEC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6079F60, func_06079F60);

// _v_side_hosei
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A030, func_0607A030);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A118, func_0607A118);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A1C8, func_0607A1C8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A290, func_0607A290);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A608, func_0607A608);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A88C, func_0607A88C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607A994, func_0607A994);

REDACTED
REDACTED
// Absolute distance from the specified entity to the player in the X Axis
s32 GetDistanceToPlayerX(Entity* self) {
REDACTED
REDACTED
REDACTED
REDACTED
    }
REDACTED
}

REDACTED
// Absolute distance from the specified entity to the player in the Y Axis
s32 GetDistanceToPlayerY(Entity* self) {
REDACTED
REDACTED
REDACTED
REDACTED
    }
REDACTED
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AA40, func_0607AA40);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AA74, func_0607AA74);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AAA4, func_0607AAA4);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AACC, func_0607AACC);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
s32 GetSideToPlayer(Entity* self) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AB1C, func_0607AB1C);

// _bicyousei_dir_0
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AB4C, func_0607AB4C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AB84, func_0607AB84);

// _hanten_dir_0
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607ABBC, func_0607ABBC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607ABF4, func_0607ABF4);

extern u8 DAT_06099811;
u8 func_0607AC2C(void) { return DAT_06099811; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AC40, func_0607AC40);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AE48, func_0607AE48);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AECC, func_0607AECC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AF0C, func_0607AF0C);

extern s16 DAT_06085e86[];
s32 func_0607AF28(u8 pos) { return DAT_06085e86[pos]; }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AF3C, func_0607AF3C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AF68, func_0607AF68);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AF94, func_0607AF94);

// _search_point
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607AFD8, func_0607AFD8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B014, func_0607B014);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B04C, func_0607B04C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B0AC, func_0607B0AC);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B0D0, func_0607B0D0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B104, func_0607B104);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B134, func_0607B134);

// SAT: func_0607B184
REDACTED
REDACTED
REDACTED
    while (current < end) {
        if (current->unk74 == 0) { // not entityId?
            DestroyEntity(current);
            return current;
        }
        current++;
    }
    return NULL;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B1C8, func_0607B1C8);

// SAT: func_0607B218
REDACTED
REDACTED
REDACTED
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

// SAT: func_0607B240
REDACTED
REDACTED
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

// _teki_init
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B264, func_0607B264);

extern u32 g_randomNext;

// SAT: func_0607B2F4
s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

void CreateEntityFromCurrentEntity(u16 id, Entity* entity) {
    DestroyEntity(entity);
    entity->unk74 = id;
    entity->pfnUpdate = (*PfnEntityUpdates)[id - 1]->func;
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B374, func_0607B374);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B3D0, func_0607B3D0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B448, func_0607B448);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B4B8, func_0607B4B8);

void func_0607B604(s32* param_1) {
REDACTED
    temp[0x14 / 4] = param_1[1];
    temp[0x18 / 4] = param_1[2];
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B618, func_0607B618);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B674, func_0607B674);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B714, func_0607B714);

void (*CheckCollision)(s32 x, s32 y, Collider* res, s32 unk);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607B7B4, func_0607B7B4);

INCLUDE_ASM("asm/saturn/game/f_nonmat", f607BE38, func_0607BE38);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607BED0, func_0607BED0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607C054, func_0607C054);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607C0A0, func_0607C0A0);

// _MTH_GetRand
INCLUDE_ASM("asm/saturn/game/f_nonmat", f607C0BC, func_0607C0BC);
