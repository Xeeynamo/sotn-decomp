// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef GAME_H
#define GAME_H

#define DAMAGE_FLAG_NORMAL 0x0000
#define DAMAGE_FLAG_CRITICAL 0x4000
#define DAMAGE_FLAG_ABSORB 0x8000
#define DAMAGE_FLAG_IMMUNE 0xC000

extern EnemyDef g_EnemyDefs[];
extern s32 g_RoomCount;

// document g_Player.status
#define PLAYER_STATUS_POISON 0x00004000

typedef enum {
    DAMAGEKIND_0,
    DAMAGEKIND_1,
    DAMAGEKIND_2,
    DAMAGEKIND_3,
    DAMAGEKIND_4,
    DAMAGEKIND_5,
    DAMAGEKIND_6,
    DAMAGEKIND_7,
    DAMAGEKIND_8,
    DAMAGEKIND_9,
    DAMAGEKIND_10,
    DAMAGEKIND_11,
    DAMAGEKIND_12,
    DAMAGEKIND_13,
    DAMAGEKIND_14,
    DAMAGEKIND_15,
    DAMAGEKIND_16,
    DAMAGEKIND_17,
    DAMAGEKIND_18,
} DamageKind;

typedef struct {
    u32 effects;    // Curse, poison, fire, ice, etc.
    u32 damageKind; // informed by "dam_kind:%04x\n"
    s32 damageTaken;
    u32 unkC;
} DamageParam;

// items.h
typedef enum ItemSlots {
    LEFT_HAND_SLOT,
    RIGHT_HAND_SLOT,
    HEAD_SLOT,
    ARMOR_SLOT,
    CAPE_SLOT,
    ACCESSORY_1_SLOT,
    ACCESSORY_2_SLOT,
    NUM_ITEM_SLOTS,
} ItemSlots;

typedef enum {
    NUM_HAND_ITEMS = 0xB0,
} HandItems;

typedef enum {
    NUM_BODY_ITEMS = 92,
} BodyItems;

#endif
